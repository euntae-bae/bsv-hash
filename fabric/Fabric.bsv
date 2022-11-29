// Interconnect Fabric
package Fabric;

import GetPut::*;
import ClientServer::*;
import Connectable::*;
// import dcache_types::*;

/*
  typedef struct{
    Bit#(addr)    address;
    Bit#(esize)   epochs;
    Bit#(3)       size;
    Bool          fence;
    Bit#(2)       access;
    Bit#(data)    writedata;
  `ifdef atomic
    Bit#(5)       atomic_op;
  `endif
  `ifdef supervisor
    Bool          sfence;
    Bool          ptwalk_req;
    Bool          ptwalk_trap;
  `endif
  } DMem_request#(numeric type addr,
                  numeric type data,
                  numeric type esize ) deriving(Bits, Eq, FShow);

  typedef struct{
    Bit#(data)        word;
    Bool              trap;
    Bit#(`causesize)  cause;
    Bit#(esize)       epochs;
  } DMem_core_response#( numeric type data, numeric type esize) deriving (Bits, Eq, FShow);
*/

// // function to send the memory request to the data memory subsystem
// function Action send_memory_request(Bit#(`vaddr) address, Bit#(1) epochs, Bit#(3) funct3,
//                                     Access_type memaccess, Bit#(4) fn, Bit#(ELEN) data) = action
//     let req = DMem_request{address      : address,
//                             epochs       : epochs,
//                             size         : funct3
//                             ,fence       : memaccess == FenceI || memaccess == Fence
//                             ,access      : truncate(pack(memaccess))
//                             ,writedata   : data
//                         `ifdef atomic
//                             ,atomic_op   : {funct3[0], fn}
//                         `endif
//                         `ifdef supervisor
//                             ,sfence      : memaccess == SFence
//                             ,ptwalk_req  : False
//                             ,ptwalk_trap : False
//                         `endif } ;
//     wr_memory_request <= req;
// endaction;

interface Fabric_IFC;
    interface Server#(Req_t, Resp_t) ipf;   // processor to fabric
    interface Client#(Req_t, Resp_t) ifa;   // fabric to accelerator
endinterface

(* synthesize *)
module mkFabric(Fabric_IFC);
    FIFOF#(Req_t) p2f;                      // processor to fabric (request)
    FIFOF#(Resp_t) f2p;                     // fabric to processor (response)
    FIFOF#(Req_t) f2a;                      // fabric to accelerator (request)
    FIFOF#(Resp_t) a2f;                     // accelerator to fabric (response)
endmodule


endpackage