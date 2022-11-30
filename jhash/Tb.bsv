package Tb;

import StmtFSM::*;
import Jhash::*;

(* synthesize *)
module mkTb(Empty);
    Reg#(Bool) done <- mkReg(False);
    //Murmur3_IFC acc <- mkMurmur3;
    Jhash_IFC acc <- mkJhash;
    Reg#(Bit#(32)) hash <- mkReg(0);

    Stmt stmt = seq
        //acc.setSeed(1429907438);
        acc.setMsgAddress(0);
        acc.setMsgLength(17);

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