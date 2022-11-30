package Jhash;

import StmtFSM::*;
import Vector::*;

function Bit#(32) fn_convert_endian_32(Bit#(32) num);
    Bit#(32) result = { num[7:0], num[15:8], num[23:16], num[31:24] };
    return result;
endfunction

function Bit#(32) fn_rol(Bit#(32) num, int shamt);
    Bit#(32) n = (num << shamt) | (num >> 32 - shamt);
    return n;
endfunction

function Vector#(3, Bit#(32)) fn_jhash_mix(Bit#(32) va, Bit#(32) vb, Bit#(32) vc);
    Bit#(32) a = va;
    Bit#(32) b = vb;
    Bit#(32) c = vc;
    Vector#(3, Bit#(32)) abc = newVector;
    
    // a -= c;  a ^= rol32(c, 4);  c += b;
    a = a - c;
    a = a ^ fn_rol(c, 4);
    c = c + b;

    // b -= a;  b ^= rol32(a, 6);  a += c;
    b = b - a;
    b = b ^ fn_rol(a, 6);
    a = a + c;

    // c -= b;  c ^= rol32(b, 8);  b += a;
    c = c - b;
    c = c ^ fn_rol(b, 8);
    b = b + a;

    // a -= c;  a ^= rol32(c, 16); c += b;
    a = a - c;
    a = a ^ fn_rol(c, 16);
    c = c + b;

    // b -= a;  b ^= rol32(a, 19); a += c;
    b = b - a;
    b = b ^ fn_rol(a, 19);
    a = a + c;

    // c -= b;  c ^= rol32(b, 4);  b += a;
    c = c - b;
    c = c ^ fn_rol(b, 4);
    b = b + a;

    abc[0] = a;
    abc[1] = b;
    abc[2] = c;
    return abc;
endfunction

function Vector#(3, Bit#(32)) fn_jhash_final(Bit#(32) va, Bit#(32) vb, Bit#(32) vc);
    Bit#(32) a = va;
    Bit#(32) b = vb;
    Bit#(32) c = vc;
    Vector#(3, Bit#(32)) abc = newVector;

    // c ^= b; c -= rol32(b, 14);
    c = c ^ b;
    c = c - fn_rol(b, 14);

    // a ^= c; a -= rol32(c, 11);
    a = a ^ c;
    a = a - fn_rol(c, 11);

    // b ^= a; b -= rol32(a, 25);
    b = b ^ a;
    b = b - fn_rol(a, 25);

    // c ^= b; c -= rol32(b, 16);
    c = c ^ b;
    c = c - fn_rol(b, 16);

    // a ^= c; a -= rol32(c, 4);
    a = a ^ c;
    a = a - fn_rol(c, 4);

    // b ^= a; b -= rol32(a, 14);
    b = b ^ a;
    b = b - fn_rol(a, 14);

    // c ^= b; c -= rol32(b, 24);
    c = c ^ b;
    c = c - fn_rol(b, 24);

    abc[0] = a;
    abc[1] = b;
    abc[2] = c;
    return abc;
endfunction

// Hello HELLO World
// 48 65 6C 6C 6F 20 48 45 4C 4C 4F 20 57 6F 72 6C 64
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

interface Jhash_IFC;
    method Action start();
    method Bool done;
    method Bit#(32) result;
    method Action setMsgAddress(Bit#(64) addr);
    method Action setMsgLength(Bit#(32) len);
    method Action setInitval(Bit#(32) val);
endinterface

module mkJhash(Jhash_IFC);
    Reg#(Bit#(64)) msgAddr  <- mkReg(0);
    Reg#(Bit#(32)) msgLen   <- mkReg(0);

    Vector#(3, Reg#(Bit#(32))) vecMemRead <- replicateM(mkReg(0));
    Reg#(Bit#(32)) initval  <- mkReg(0);
    Reg#(Bit#(32)) a        <- mkReg(0);
    Reg#(Bit#(32)) b        <- mkReg(0);
    Reg#(Bit#(32)) c        <- mkReg(0);
    Reg#(Bit#(32)) rembyte  <- mkReg(0);
    Reg#(Bit#(32)) hash     <- mkReg(0);

    /* constants */
    Bit#(32) c_jhash_initval    = 'hdeadbeef;
    Bit#(32) c_initval          = 'hdeadbeea;

    Stmt stmt = seq
        action
            //setInitval(c_initval);
            initval <= c_initval;
            rembyte <= msgLen;
        endaction

        action
            Bit#(32) initialValue = c_jhash_initval + msgLen + initval;
            a <= initialValue;
            b <= initialValue;
            c <= initialValue;
        endaction

        // 12바이트(3워드)씩 읽어서 처리
        // all but the last block: affect some 32 bits of (a, b, c)
        while (rembyte > 12) seq
            // 32비트 레지스터에 저장할 때 리틀 엔디안 바이트 순서로 뒤집어서 저장해야 하나?
            // --> 리틀 엔디안으로 저장해야 한다.
            vecMemRead[0] <= fn_convert_endian_32(fn_mem_read(msgAddr));
            vecMemRead[1] <= fn_convert_endian_32(fn_mem_read(msgAddr+4));
            vecMemRead[2] <= fn_convert_endian_32(fn_mem_read(msgAddr+8));
            action
                a <= a + vecMemRead[0];
                b <= b + vecMemRead[1];
                c <= c + vecMemRead[2];
                $display("a=%08x", a + vecMemRead[0]);
                $display("b=%08x", b + vecMemRead[1]);
                $display("c=%08x", c + vecMemRead[2]);
            endaction

            action
                Vector#(3, Bit#(32)) abc = fn_jhash_mix(a, b, c);
                a <= abc[0];
                b <= abc[1];
                c <= abc[2];
                rembyte <= rembyte - 12;
                msgAddr <= msgAddr + 12;
                $display("a=%08x", abc[0]);
                $display("b=%08x", abc[1]);
                $display("c=%08x", abc[2]);
            endaction
        endseq

        // last block: affect all 32 bits of (c)
        // all the case statements fall through
        action
            vecMemRead[0] <= fn_convert_endian_32(fn_mem_read(msgAddr));
            vecMemRead[1] <= fn_convert_endian_32(fn_mem_read(msgAddr + 4));
            vecMemRead[2] <= fn_convert_endian_32(fn_mem_read(msgAddr + 8));
        endaction

        if (rembyte > 0) action
            c <= c + vecMemRead[2];
            b <= b + vecMemRead[1];
            a <= a + vecMemRead[0];
        endaction

        action
            Vector#(3, Bit#(32)) abc = fn_jhash_final(a, b, c);
            //a <= abc[0];
            //b <= abc[1];
            c <= abc[2];
            $display("a=%08x", abc[0]);
            $display("b=%08x", abc[1]);
            $display("c=%08x", abc[2]);
        endaction
        hash <= c;
    endseq;

    FSM fsm <- mkFSM(stmt);

    method Action start();
        fsm.start();
    endmethod

    method Bool done;
        return fsm.done;
    endmethod

    method Bit#(32) result if (fsm.done);
        return hash;
    endmethod

    method Action setMsgAddress(Bit#(64) addr) if (fsm.done);
        msgAddr <= addr;
    endmethod

    method Action setMsgLength(Bit#(32) len) if (fsm.done);
        msgLen <= len;
    endmethod

    method Action setInitval(Bit#(32) val);
        initval <= val;
    endmethod
endmodule

endpackage