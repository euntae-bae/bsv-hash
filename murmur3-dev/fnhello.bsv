function Bit#(32) fn_mem_read(Bit#(64) addr);
	return case (addr)
		'h0000000000000000: return 'h48656c6c;
		'h0000000000000004: return 'h6f204845;
		'h0000000000000008: return 'h4c4c4f20;
		'h000000000000000c: return 'h576f726c;
		'h0000000000000010: return 'h64000000;
		default: return 0;
	endcase;
endfunction
