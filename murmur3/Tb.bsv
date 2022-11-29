package Tb;

import StmtFSM::*;
import Murmur3::*;

(* synthesize *)
module mkTb(Empty);
    Reg#(Bool) done <- mkReg(False);
    Murmur3_IFC acc <- mkMurmur3;
    Reg#(Bit#(32)) hash <- mkReg(0);

    Stmt stmt = seq
        acc.setSeed(1429907438);
        acc.setMsgAddress(0);
        acc.setMsgLength(11);

        acc.start();
        //await(fifo.notEmpty() == False);
        await(acc.done);
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