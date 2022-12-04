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
    method Action init(Bit#(32) iv, Bit#(32) len);
    method Action loadv0(Bit#(32) msgChunk); // copy 4 byte message chunk into vecMemRead[0]
    method Action loadv1(Bit#(32) msgChunk); // copy 4 byte message chunk into vecMemRead[1]
    method Action loadv2(Bit#(32) msgChunk); // copy 4 byte message chunk into vecMemRead[2]
    method Action step;
    method Bit#(32) result;
endinterface

// rdsize

(* synthesize *)
module mkJhash(Jhash_IFC);
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
    //Bit#(32) c_initval          = 'hdeadbeea;

    method Action init(Bit#(32) iv, Bit#(32) len);
        action
            Bit#(32) initialValue = c_jhash_initval + len + iv;
            msgLen <= len;
            rembyte <= len;
            a <= initialValue;
            b <= initialValue;
            c <= initialValue;
            vecMemRead[0] <= 0;
            vecMemRead[1] <= 0;
            vecMemRead[2] <= 0;
            hash <= 0;
            $display("initialValue=%08x", initialValue);
        endaction
    endmethod

    method Action loadv0(Bit#(32) msgChunk);
        vecMemRead[0] <= msgChunk;
    endmethod

    method Action loadv1(Bit#(32) msgChunk);
        vecMemRead[1] <= msgChunk;
    endmethod

    method Action loadv2(Bit#(32) msgChunk);
        vecMemRead[2] <= msgChunk;
    endmethod

    method Action step;
        if (rembyte > 12) action
            // 4바이트 단위 메시지 청크들은 각각 리틀 엔디안 순서로 레지스터에 저장되어 있어야 한다.
            Bit#(32) va = a + vecMemRead[0];
            Bit#(32) vb = b + vecMemRead[1];
            Bit#(32) vc = c + vecMemRead[2];
            Vector#(3, Bit#(32)) abc = fn_jhash_mix(va, vb, vc);
            a <= abc[0];
            b <= abc[1];
            c <= abc[2];
            rembyte <= rembyte - 12;
            $display("memRead0=%08x", vecMemRead[0]);
            $display("memRead1=%08x", vecMemRead[1]);
            $display("memRead2=%08x", vecMemRead[2]);

            $display("a=%08x", abc[0]);
            $display("b=%08x", abc[1]);
            $display("c=%08x", abc[2]);
        endaction

        // last block
        else action
            Bit#(32) va = a;
            Bit#(32) vb = b;
            Bit#(32) vc = c;

            if (rembyte > 0) begin
                vc = vc + vecMemRead[2];
                vb = vb + vecMemRead[1];
                va = va + vecMemRead[0];
            end

            $display("memRead0=%08x", vecMemRead[0]);
            $display("memRead1=%08x", vecMemRead[1]);
            $display("memRead2=%08x", vecMemRead[2]);

            Vector#(3, Bit#(32)) abc = fn_jhash_final(va, vb, vc);
            hash <= abc[2];
            $display("a=%08x", abc[0]);
            $display("b=%08x", abc[1]);
            $display("c=%08x", abc[2]);
        endaction
    endmethod

    method Bit#(32) result;
        return hash;
    endmethod
endmodule

endpackage