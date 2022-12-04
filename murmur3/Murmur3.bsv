package Murmur3;

import StmtFSM::*;

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

/*
// Hello HELLO World
// 48 65 6C 6C 6F 20 48 45 4C 4C 4F 20 57 6F 72 6C 64
// 메모리 데이터를 4바이트씩 반환
function Bit#(32) fn_mem_read(Bit#(64) addr);
    return case (addr)
        // first 12 bytes
        'h00: return 'h48656C6C;
        'h04: return 'h6F204845;
        'h08: return 'h4C4C4F20;
        // last 5 bytes
        'h0c: return 'h576F726C;
        'h10: return 'h64000000;
        'h14: return 'h00000000;
        default: return 0;
    endcase;
endfunction
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


interface Murmur3_IFC;
    method Action init(Bit#(32) sd, Bit#(64) len);
    method Action load(Bit#(32) msgChunk, Bit#(32) len);
    method Action step;
    method Bit#(32) result;
    //method Bool done;
    //method Action load(Bit#(32) wmsg, Bit#(64) len);
endinterface

// hash를 seed로 초기화한다.

// 4바이트를 메모리에서 읽는다 (데이터캐시로 read 요청을 보낸다.)
// 리틀엔디안 순서로 정렬하여 key 레지스터에 저장한다.
// scramble(key)를 구한다.

// hash와 scrambled key를 XOR한다.


// murmur3.setseed
// murmur3.setlen
// murmur3.hash rd
// murmur3.hash rd rs1 rs2
// INST rd rs1 rs2 31..25=0 14..12=0 6..2=0x02 1..0=3

// murmur3.setseed seed(값이 저장된 레지스터)
// murmur3 dest, src, len

(* synthesize *)
module mkMurmur3(Murmur3_IFC);
    // Config registers
    Reg#(Bit#(64)) msgLen   <- mkReg(0);    // 메시지의 길이
    //Reg#(Bit#(32)) seed     <- mkReg(0);    // 시드 값 (랜덤) -> 시드 값을 설정하는 명령어를 만들 수도 있음

    Reg#(Bit#(32)) key      <- mkReg(0);    // 현재 루프에서 처리할 메시지 (4바이트 단위) -> 사용하려면 먼저 메모리에서 load해와야 한다.
    Reg#(Bit#(32)) chunkLen <- mkReg(0);    // 현재 루프에서 처리할 메시지 길이
    Reg#(Bit#(32)) hash     <- mkReg(0);    // 해시값 (결과값)
    
    // Constants
    Bit#(32) c1 = 'hcc9e2d51;
    Bit#(32) c2 = 'h1b873593;
    Bit#(32) m  = 'h5;
    Bit#(32) n  = 'he6546b64;

    method Action init(Bit#(32) sd, Bit#(64) len);
        action
            //seed <= sd;
            hash <= sd;
            msgLen <= len;
        endaction
    endmethod

    method Action load(Bit#(32) msgChunk, Bit#(32) len);
        action
            key <= msgChunk; //fn_convert_endian_32(msgChunk); - 이미 레지스터에 리틀 엔디안 순서로 읽은 상태라면 순서를 뒤집을 필요가 없다 (Tb에서 호출할 것)
            chunkLen <= len;
        endaction
    endmethod

    method Action step;
        //fsm.start();
        if (chunkLen >= 4) action
//                $display("key: %08x", key);
            Bit#(32) k = fn_murmur_32_scramble(key);
            Bit#(32) h = hash;
            h = h ^ k;
            h = fn_rol(h, 13);
            h = (h * m) + n;
            hash <= h;
//                $display("h: %08x", h);
        endaction
        else action
//                $display("finalize ---- key: %08x", key);
        
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
 //               $display("hash: %x at %d", hash, $time);
        endaction
    endmethod

    // method Bool done;
    //     return fsm.done;
    // endmethod

    method Bit#(32) result; //if (fsm.done);
        return hash;
    endmethod
endmodule

endpackage