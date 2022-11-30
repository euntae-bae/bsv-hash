package Murmur3;

import StmtFSM::*;
// import ClientServer::*;
// import Connectable::*;

/*
msg: 48 65 6c 6c 6f 20 57 6f 72 6c 64 
seed: 1429907438
len: 11

48 65 6c 6c             --> 6c6c6548
scramble(6c6c6548)      --> 0153080c
h=f441e025
6f 20 57 6f             --> 6f57206f
scramble(6f57206f)      --> 87809459
h=cf2233bc

Hello World --> f4b237e0
elapsed time (ms): 0.000032
*/

function Bit#(32) fn_convert_endian_32(Bit#(32) num);
    Bit#(32) result = { num[7:0], num[15:8], num[23:16], num[31:24] };
    return result;
endfunction

function Bit#(32) fn_rol(Bit#(32) num, int shamt);
    Bit#(32) n = (num << shamt) | (num >> 32 - shamt);
    return n;
endfunction

// k: four byte chunk (key의 4바이트 조각)
function Bit#(32) fn_murmur_32_scramble(Bit#(32) k);
    // 1. multiply by c1
    // 2. ROL15
    // 3. multiply by c2
    Bit#(32) c1 = 'hcc9e2d51;
    Bit#(32) c2 = 'h1b873593;
    Bit#(32) key = k;
    key = key * c1;
    key = fn_rol(key, 15);
    key = key * c2;
    return key;
endfunction

// Hello World
// 48 65 6c 6c / 6f 20 57 6f / 72 6c 64 
function Bit#(32) fn_mem_read(Bit#(64) addr, Bit#(64) len);
    return case (addr)
        'h00: return 'h48656c6c;
        'h04: return 'h6f20576f;
        'h08: return 'h726c6400;
        default: return 0;
    endcase;
endfunction

interface Murmur3_IFC;
    method Action start();
    method Bool done; // or busy?
    method Bit#(32) result;
    method Action setSeed(Bit#(32) s);
    method Action setMsgAddress(Bit#(64) addr);
    method Action setMsgLength(Bit#(64) len);
endinterface

// hash를 seed로 초기화한다.

// 4바이트를 메모리에서 읽는다 (데이터캐시로 read 요청을 보낸다.)
// 리틀엔디안 순서로 정렬하여 key 레지스터에 저장한다.
// scramble(key)를 구한다.

// hash와 scrambled key를 XOR한다.


// murmur3.setseed
// murmur3.setlen
// murmur3.set

// murmur3.setseed seed(값이 저장된 레지스터)
// murmur3 dest, src, len

(* synthesize *)
module mkMurmur3(Murmur3_IFC);
    // Config registers
    Reg#(Bit#(64)) msgAddr  <- mkReg(0);    // 메시지가 있는 메모리 주소
    Reg#(Bit#(64)) msgLen   <- mkReg(0);    // 메시지의 길이
    Reg#(Bit#(32)) seed     <- mkReg(0);    // 시드 값 (랜덤) -> 시드 값을 설정하는 명령어를 만들 수도 있음

    Reg#(Bit#(32)) memRead  <- mkReg(0);    // 메모리에서 읽어온 값을 임시 저장
    Reg#(Bit#(32)) key      <- mkReg(0);    // 현재 루프에서 처리할 메시지 (4바이트 단위)
    Reg#(Bit#(64)) rembyte  <- mkReg(0);    // 현재 루프에서 (처리해야 할) 메시지의 남은(remained) 바이트 수
    Reg#(Bit#(32)) hash     <- mkReg(0);    // 해시값 (결과값)
    
    // Constants
    Bit#(32) c1 = 'hcc9e2d51;
    Bit#(32) c2 = 'h1b873593;
    Bit#(32) m  = 'h5;
    Bit#(32) n  = 'he6546b64;

    Stmt stmt = seq
        action
            hash <= seed;
            rembyte <= msgLen;
        endaction

        // action
        //     $display("seed: %d", seed);
        //     $display("addr: %d", msgAddr);
        //     $display("leng: %d", msgLen[31:0]);
        // endaction

        // rembyte가 4 이상이면 메모리에 4바이트 읽기 요청을 보낸다.
        // 응답이 오면 리틀엔디안 바이트 순서에 맞게 정렬해서 key에 저장한다. (RISC-V는 리틀엔디안 머신이다.)
        // -> 레지스터에 4바이트 데이터가 리틀엔디안 순서로 저장된다.
        //await();
        while (rembyte >= 4) seq
            memRead <= fn_mem_read(msgAddr, 4);
            key <= fn_convert_endian_32(memRead);
                $display("key: %08x", key);
            action
                key <= fn_convert_endian_32(memRead);
                msgAddr <= msgAddr + 4;
                rembyte <= rembyte - 4;
            endaction
            action
                Bit#(32) k = fn_murmur_32_scramble(key);
                Bit#(32) h = hash;
                h = h ^ k;
                h = fn_rol(h, 13);
                h = (h * m) + n;
                hash <= h;
                    $display("h: %08x", h);
            endaction
        endseq

        // rembyte가 4보다 작으면 메모리에 rembyte만큼 읽기 요청을 보낸다.
        // 응답이 오면 리틀 엔디안 순서로 key에 저장
        memRead <= fn_mem_read(msgAddr, rembyte);
        key <= fn_convert_endian_32(memRead);
        $display("key: %08x", key);

        action
            Bit#(32) k = fn_murmur_32_scramble(key);
            Bit#(32) h = hash;
            h = h ^ k;

            // finalize
            h = h ^ msgLen[31:0];
            h = h ^ (h >> 16);
            h = h * 'h85ebca6b;
            h = h ^ (h >> 13);
            h = h * 'hc2b2ae35;
            h = h ^ (h >> 16);
            hash <= h;
        endaction
        $display("hash: %x at %d", hash, $time);
    endseq;

    FSM fsm <- mkFSM(stmt);

    // request FIFO가 empty가 아닐 때 실행
    // rule rl_start;
    //     //hash <= seed;
    //     //rembyte <= msgLen;
    //     fsm.start();
    // endrule

    // rule rl_done;
    // endrule

    method Action start() if (fsm.done);
        fsm.start();
    endmethod

    method Bool done;
        return fsm.done;
    endmethod

    method Bit#(32) result() if (fsm.done);
        return hash;
    endmethod

    method Action setSeed(Bit#(32) s) if (fsm.done);
        seed <= s;
    endmethod

    method Action setMsgAddress(Bit#(64) addr) if (fsm.done);
        msgAddr <= addr;
    endmethod

    method Action setMsgLength(Bit#(64) len) if (fsm.done);
        msgLen <= len;
    endmethod
endmodule

/* 
- operating on four bytes at a time
-> mkMurmur이랑 분리된 mkMurmurEngine을 따로 두는 게 좋을까? (4바이트 단위로 처리해주는 모듈)
-> 그래서 mkMurmur은 4바이트씩 메모리에서 가져와서 mkMurmurEngine으로 4바이트 값을 전달(request)하여 연산 결과를 얻어오는(response) 방식
- ROL15
- ROL13 
-> fn_rol로 일반화
*/

endpackage