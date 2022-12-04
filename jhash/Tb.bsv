package Tb;

import StmtFSM::*;
import Jhash::*;

import fnhello::*;

(* synthesize *)
module mkTb(Empty);
    Reg#(Bool) done <- mkReg(False);
    Jhash_IFC acc <- mkJhash;
    Reg#(Bit#(32)) hash <- mkReg(0);

    Reg#(Bit#(64)) msgAddr  <- mkReg(0);
    Reg#(Bit#(64)) msgLen   <- mkReg(0);
    Reg#(Bit#(32)) remByte  <- mkReg(0);
    Reg#(Bit#(64)) memRead0 <- mkReg(0);
    Reg#(Bit#(64)) memRead1 <- mkReg(0);
    Reg#(Bit#(64)) memRead2 <- mkReg(0);

    Bit#(32) c_msglen   = 17;
    Bit#(32) c_seed     = 1429907438;
    Bit#(32) c_initval  = 'hdeadbeea;

    Stmt stmt = seq
        action
            msgAddr <= 0;
            msgLen  <= zeroExtend(c_msglen);
            remByte <= c_msglen;
        endaction

        acc.init(c_initval, c_msglen);

        while (remByte > 12) seq
            memRead0 <= zeroExtend(fn_convert_endian_32(fn_mem_read(msgAddr)));
            memRead1 <= zeroExtend(fn_convert_endian_32(fn_mem_read(msgAddr + 4)));
            memRead2 <= zeroExtend(fn_convert_endian_32(fn_mem_read(msgAddr + 8)));

            acc.loadv0(truncate(memRead0));
            acc.loadv1(truncate(memRead1));
            acc.loadv2(truncate(memRead2));

            action
                acc.step;
                remByte <= remByte - 12;
                msgAddr <= msgAddr + 12;
            endaction
        endseq

        memRead0 <= zeroExtend(fn_convert_endian_32(fn_mem_read(msgAddr)));
        memRead1 <= zeroExtend(fn_convert_endian_32(fn_mem_read(msgAddr + 4)));
        memRead2 <= zeroExtend(fn_convert_endian_32(fn_mem_read(msgAddr + 8)));

        acc.loadv0(truncate(memRead0));
        acc.loadv1(truncate(memRead1));
        acc.loadv2(truncate(memRead2));

        acc.step;

        hash <= acc.result;
        done <= True;
    endseq;

    FSM fsm <- mkFSM(stmt);

    rule rl_start(!done);
        fsm.start();
    endrule

    rule rl_done (done);
        $display("hash: %08x at", hash, $time);
        $finish;
    endrule
endmodule

endpackage