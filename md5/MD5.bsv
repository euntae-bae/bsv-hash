package MD5;

import StmtFSM::*;
import Vector::*;

function Bit#(32) fn_convert_endian_32(Bit#(32) num);
    Bit#(32) result = { num[7:0], num[15:8], num[23:16], num[31:24] };
    return result;
endfunction

function Bit#(64) fn_convert_endian_64(Bit#(64) num);
    Bit#(64) result = {
        num[7:0], num[15:8], num[23:16], num[31:24],
        num[39:32], num[47:40], num[55:48], num[63:56]
    };
    return result;
endfunction

function Bit#(32) fn_rol(Bit#(32) num, int shamt);
    Bit#(32) n = (num << shamt) | (num >> 32 - shamt);
    return n;
endfunction

function Bit#(32) fn_genK(Bit#(32) sel);
    return case (sel)
        0: 32'hd76aa478;
        1: 32'he8c7b756;
        2: 32'h242070db;
        3: 32'hc1bdceee;
        4: 32'hf57c0faf;
        5: 32'h4787c62a;
        6: 32'ha8304613;
        7: 32'hfd469501;
        8: 32'h698098d8;
        9: 32'h8b44f7af;
        10: 32'hffff5bb1;
        11: 32'h895cd7be;
        12: 32'h6b901122;
        13: 32'hfd987193;
        14: 32'ha679438e;
        15: 32'h49b40821;
        16: 32'hf61e2562;
        17: 32'hc040b340;
        18: 32'h265e5a51;
        19: 32'he9b6c7aa;
        20: 32'hd62f105d;
        21: 32'h02441453;
        22: 32'hd8a1e681;
        23: 32'he7d3fbc8;
        24: 32'h21e1cde6;
        25: 32'hc33707d6;
        26: 32'hf4d50d87;
        27: 32'h455a14ed;
        28: 32'ha9e3e905;
        29: 32'hfcefa3f8;
        30: 32'h676f02d9;
        31: 32'h8d2a4c8a;
        32: 32'hfffa3942;
        33: 32'h8771f681;
        34: 32'h6d9d6122;
        35: 32'hfde5380c;
        36: 32'ha4beea44;
        37: 32'h4bdecfa9;
        38: 32'hf6bb4b60;
        39: 32'hbebfbc70;
        40: 32'h289b7ec6;
        41: 32'heaa127fa;
        42: 32'hd4ef3085;
        43: 32'h04881d05;
        44: 32'hd9d4d039;
        45: 32'he6db99e5;
        46: 32'h1fa27cf8;
        47: 32'hc4ac5665;
        48: 32'hf4292244;
        49: 32'h432aff97;
        50: 32'hab9423a7;
        51: 32'hfc93a039;
        52: 32'h655b59c3;
        53: 32'h8f0ccc92;
        54: 32'hffeff47d;
        55: 32'h85845dd1;
        56: 32'h6fa87e4f;
        57: 32'hfe2ce6e0;
        58: 32'ha3014314;
        59: 32'h4e0811a1;
        60: 32'hf7537e82;
        61: 32'hbd3af235;
        62: 32'h2ad7d2bb;
        63: 32'heb86d391;
        default: 0;
    endcase;
endfunction

function Bit#(32) fn_shamt(Bit#(32) sel);
    return case (sel)
        0: 7;
        1: 12;
        2: 17;
        3: 22;
        4: 7;
        5: 12;
        6: 17;
        7: 22;
        8: 7;
        9: 12;
        10: 17;
        11: 22;
        12: 7;
        13: 12;
        14: 17;
        15: 22;
        16: 5;
        17: 9;
        18: 14;
        19: 20;
        20: 5;
        21: 9;
        22: 14;
        23: 20;
        24: 5;
        25: 9;
        26: 14;
        27: 20;
        28: 5;
        29: 9;
        30: 14;
        31: 20;
        32: 4;
        33: 11;
        34: 16;
        35: 23;
        36: 4;
        37: 11;
        38: 16;
        39: 23;
        40: 4;
        41: 11;
        42: 16;
        43: 23;
        44: 4;
        45: 11;
        46: 16;
        47: 23;
        48: 6;
        49: 10;
        50: 15;
        51: 21;
        52: 6;
        53: 10;
        54: 15;
        55: 21;
        56: 6;
        57: 10;
        58: 15;
        59: 21;
        60: 6;
        61: 10;
        62: 15;
        63: 21;
    endcase;
endfunction

// round 0
function Bit#(32) fn_F(Bit#(32) x, Bit#(32) y, Bit#(32) z);
    return ((x & y) | (~x & z));
endfunction

// round 1
function Bit#(32) fn_G(Bit#(32) x, Bit#(32) y, Bit#(32) z);
    return ((x & z) | (y & ~z));
endfunction

// round 2
function Bit#(32) fn_H(Bit#(32) x, Bit#(32) y, Bit#(32) z);
    return x ^ y ^ z;
endfunction

// round3
function Bit#(32) fn_I(Bit#(32) x, Bit#(32) y, Bit#(32) z);
    return (y ^ (x | ~z));
endfunction

interface MD5_IFC;
    method Action start();
    method Bool done;
    method Bit#(128) result;
    method Action setMsgAddress(Bit#(64) addr);
    method Action setMsgLength(Bit#(64) len);
endinterface

// Hello World
// 48 65 6c 6c / 6f 20 57 6f / 72 6c 64 
function Bit#(32) fn_mem_read(Bit#(64) addr, Bit#(64) len);
    // return case (addr)
    //     'h00: return 'h48656c6c;
    //     'h04: return 'h6f20576f;
    //     'h08: return 'h726c6400;
    //     default: return 0;
    // endcase;
    return 'h48656c6c6f20576f726c64;
endfunction

(* synthesize *)
module mkMD5(MD5_IFC);
    // Config registers
    Reg#(Bit#(64)) msgAddr      <- mkReg(0);
    Reg#(Bit#(64)) msgLen       <- mkReg(0);
    Reg#(int) step              <- mkReg(0);
    Reg#(Bit#(512)) msgChunk    <- mkReg(0);                    // 메시지를 512 비트 청크 단위로 처리
    Vector#(16, Reg#(Bit#(32)) words <- replicateM(mkReg(0));   // 512비트 청크를 16개의 32비트 워드로 분할 (리틀 엔디안)

    Reg#(Bit#(128)) digest  <- mkReg(0);

    Stmt stmt = seq
        // read message from memory
        /* pre-processing */
        action
            Bit#(512) msgTemp = { fn_mem_read(msgAddr, msgLen), 1 };
            msgTemp = msgTemp << sh;
            msgChunk <= { msgTemp, fn_convert_endian_64(msgLen) };
            //msg <= { fn_mem_read(msgAddr, msgLen), 1 };
            //msg <= msg << ; // padding
            //msg <= { msg, fn_convert_endian_64(msgLen) };
        endaction

        action
            words[0] <= fn_convert_endian_32(msgChunk[31:0]);
            words[1] <= fn_convert_endian_32(msgChunk[63:32]);
            words[2] <= fn_convert_endian_32(msgChunk[95:64]);
            words[3] <= fn_convert_endian_32(msgChunk[127:96]);
            words[4] <= fn_convert_endian_32(msgChunk[159:128]);
            words[5] <= fn_convert_endian_32(msgChunk[191:160]);
            words[6] <= fn_convert_endian_32(msgChunk[223:192]);
            words[7] <= fn_convert_endian_32(msgChunk[255:224]);

            words[8]  <= fn_convert_endian_32(msgChunk[287:256]);
            words[9]  <= fn_convert_endian_32(msgChunk[319:288]);
            words[10] <= fn_convert_endian_32(msgChunk[351:320]);
            words[11] <= fn_convert_endian_32(msgChunk[383:352]);
            words[12] <= fn_convert_endian_32(msgChunk[415:384]);
            words[13] <= fn_convert_endian_32(msgChunk[447:416]);
            words[14] <= fn_convert_endian_32(msgChunk[479:448]);
            words[15] <= fn_convert_endian_32(msgChunk[511:480]);
        endaction
    endseq;

    FSM fsm <- mkFSM(stmt);

    method Action start();
        fsm.start();
    endmethod

    method Bool done;
        return fsm.done;
    endmethod

    method Bit#(128) result;
    endmethod

    method Action setMsgAddress(Bit#(64) addr);
    endmethod

    method Action setMsgLength(Bit#(64) len);
    endmethod
endmodule



endpackage