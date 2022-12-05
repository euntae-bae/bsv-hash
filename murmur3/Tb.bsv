package Tb;

import StmtFSM::*;
import Murmur3::*;

// sample messages
//import fnlorem::*;
import fnhello::*;

(* synthesize *)
module mkTb(Empty);
    Reg#(Bool) done <- mkReg(False);
    Murmur3_IFC acc <- mkMurmur3;
    Reg#(Bit#(32)) hash <- mkReg(0);

    Reg#(Bit#(64)) msgAddr  <- mkReg(0);
    Reg#(Bit#(64)) msgLen   <- mkReg(0);
    Reg#(Bit#(32)) remByte  <- mkReg(0);
    Reg#(Bit#(64)) memRead  <- mkReg(0);

    Bit#(32) c_msglen   = 17; // or 736
    Bit#(32) c_seed     = 1429907438;

    Stmt stmt = seq
        action
            msgAddr <= 0;
            msgLen  <= zeroExtend(c_msglen);
            remByte <= c_msglen;
        endaction
        
        acc.init(c_seed, msgLen);

        while (remByte >= 4) seq
            //$display("memRead: %08x", fn_mem_read(msgAddr));
            memRead <= zeroExtend(fn_convert_endian_32(fn_mem_read(msgAddr))); // == memcpy(&chunk, msgaddr, sizeof(uint32_t));
            action
                $display("memRead(%04x): %016x", msgAddr, memRead);
                acc.load(truncate(memRead), 4);
            endaction
            action
                acc.step;
                $display("hash: %08x", acc.result);
                msgAddr <= msgAddr + 4;
                remByte <= remByte - 4;
            endaction
        endseq

        // finalize
        memRead <= zeroExtend((fn_mem_read(msgAddr)));  // big-endian (리틀 엔디안으로의 변환은 mkMurmur3에서 수행)
        action
            $display("memRead(%04x): %016x", msgAddr, memRead);
            acc.load(truncate(memRead), remByte);
        endaction
        acc.step;

        $display("murmur3.hash: %08x at %d", acc.result, $time);
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