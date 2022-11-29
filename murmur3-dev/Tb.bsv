package Tb;

import StmtFSM::*;

function Bit#(32) fn_convert_endian_32(Bit#(32) num);
    Bit#(32) result = { num[7:0], num[15:8], num[23:16], num[31:24] };
    return result;
endfunction

function Bit#(32) fn_rol(Bit#(32) num, int shamt);
    Bit#(32) n = (num << shamt) | (num >> 32 - shamt);
    return n;
endfunction

function Bit#(32) fn_bit_arith(Bit#(32) num);
    Bit#(32) n = num;
    Bit#(32) c1 = 'hcc9e2d51;
    Bit#(32) c2 = 'h1b873593;

    n = n * c1;
    n = n ^ c2;

    return n;
endfunction

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

(* synthesize *)
module mkTb(Empty);
    Reg#(Bit#(32)) val <- mkReg(0);
    Reg#(Bool) done <- mkReg(False);
    Reg#(int) fsmCnt <- mkReg(0);

    Reg#(Bit#(32)) hash <- mkReg('h1234);
    Bit#(32) m  = 'h5;
    Bit#(32) n  = 'he6546b64;

    Stmt stmt = seq
        val <= 'h12345678;
        val <= 'h11223344;
        val <= 'h01020304;
        val <= 'habcdef01;
        action
            Bit#(32) k = fn_murmur_32_scramble(val);
            Bit#(32) h = hash;
            h = h ^ k;
            h = fn_rol(h, 13);
            h = (h * m) + n;
            hash <= h;
            val <= h;
        endaction
        val <= 'h636f7272;
        val <= 'h72726f63;
        val <= 'h6c6c6548;
        val <= 'h6f57206f;
        done <= True;
        $display("\t** final action **");
    endseq;

    FSM fsm <- mkFSM(stmt);

    // 이 rule은 매 사이클 실행되나?
    // => 그렇지 않음. fsm이 한 번 실행되면 끝나기 전까지 실행되지 않음
    // fsm의 seq 블록의 실행이 완료되면 rl_start가 다시 실행된다. 그러면 fsm.start() 역시 다시 호출된다.
    rule rl_display_fsm_done;
        $display("fsm.done: %d at %d", fsm.done, $time);
    endrule
    
    rule rl_start (!done);
        $display("rl_start at", $time);
        fsm.start();
    endrule

    rule rl_step (!fsm.done && (val != 0));
        $display("endian:\t%08x, %08x at %d", val, fn_convert_endian_32(val), $time);
        // $display("arith:\t%08x, %08x at %d", val, fn_bit_arith(val), $time);
        // $display("ROL13:\t%08x, %08x at %d", val, fn_rol(val, 13), $time);
        // $display("ROL15:\t%08x, %08x at %d", val, fn_rol(val, 15), $time);
        $display("scram:\t%08x, %08x at %d", val, fn_murmur_32_scramble(val), $time);
    endrule

    rule rl_done (done);
        $display("done at", $time);
        //$finish;
        val <= 0;
        done <= False;
        fsmCnt <= fsmCnt + 1;
    endrule

    rule rl_finish (fsmCnt > 0);
        $display("finished at", $time);
        $finish;
    endrule
endmodule

endpackage


// pack: various types to Bit#(n)
// unpack: Bit#(n) to various types