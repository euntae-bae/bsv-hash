/*
 * Generated by Bluespec Compiler, version 2022.01-29-gc526ff54 (build c526ff54)
 * 
 * On Wed Nov 30 19:24:30 KST 2022
 * 
 */
#include "bluesim_primitives.h"
#include "model_mkTb.h"

#include <cstdlib>
#include <time.h>
#include "bluesim_kernel_api.h"
#include "bs_vcd.h"
#include "bs_reset.h"


/* Constructor */
MODEL_mkTb::MODEL_mkTb()
{
  mkTb_instance = NULL;
}

/* Function for creating a new model */
void * new_MODEL_mkTb()
{
  MODEL_mkTb *model = new MODEL_mkTb();
  return (void *)(model);
}

/* Schedule functions */

static void schedule_posedge_CLK(tSimStateHdl simHdl, void *instance_ptr)
       {
	 MOD_mkTb &INST_top = *((MOD_mkTb *)(instance_ptr));
	 tUInt8 DEF_INST_top_DEF_fsm_abort_whas_AND_fsm_abort_wget_OR_fsm_state_ETC___d137;
	 tUInt8 DEF_INST_top_DEF_fsm_abort_whas_AND_fsm_abort_wget___d6;
	 tUInt8 DEF_INST_top_DEF_NOT_fsm_start_wire_whas_OR_NOT_fsm_start_wire__ETC___d11;
	 tUInt8 DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28;
	 tUInt8 DEF_INST_top_DEF_fsm_abort_whas_AND_fsm_abort_wget_OR_fsm_state_ETC___d35;
	 tUInt8 DEF_INST_top_DEF_fsm_start_reg_1_2_AND_NOT_fsm_state_fired_3_4___d25;
	 tUInt8 DEF_INST_top_DEF_fsm_state_mkFSMstate_read__1_EQ_0___d32;
	 tUInt8 DEF_INST_top_DEF_fsm_state_mkFSMstate_read__1_EQ_14___d34;
	 tUInt8 DEF_INST_top_DEF_fsm_start_reg__h26219;
	 tUInt8 DEF_INST_top_DEF_fsm_start_wire_wget____d9;
	 tUInt8 DEF_INST_top_DEF_fsm_start_wire_whas____d7;
	 tUInt8 DEF_INST_top_DEF_fsm_start_reg_1__h20958;
	 tUInt8 DEF_INST_top_DEF_fsm_abort_wget____d5;
	 tUInt8 DEF_INST_top_DEF_fsm_abort_whas____d4;
	 tUInt8 DEF_INST_top_DEF_fsm_state_fired__h20960;
	 tUInt8 DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31;
	 tUInt8 DEF_INST_top_DEF_done___d142;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_start_reg__dreg_update;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_fsm_start_reg__dreg_update;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_state_handle_abort;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_fsm_state_handle_abort;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_state_fired__dreg_update;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_fsm_state_fired__dreg_update;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_state_every;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_fsm_state_every;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_restart;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_fsm_restart;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l87c13;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l88c13;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l89c13;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l90c13;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l91c9;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l100c9;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l106c9;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l110c9;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l114c13;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l115c13;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l116c13;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l117c13;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l118c14;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l119c9;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_idle_l86c17;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_fsm_idle_l86c17;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_fsm_start;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_fsm_fsm_start;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_rl_start;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_rl_start;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_rl_step;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_rl_step;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_rl_done;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_rl_done;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE_RL_rl_finish;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE_RL_rl_finish;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE___me_check_5;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE___me_check_5;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE___me_check_6;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE___me_check_6;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE___me_check_7;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE___me_check_7;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE___me_check_8;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE___me_check_8;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE___me_check_9;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE___me_check_9;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE___me_check_10;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE___me_check_10;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE___me_check_11;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE___me_check_11;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE___me_check_12;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE___me_check_12;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE___me_check_13;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE___me_check_13;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE___me_check_14;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE___me_check_14;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE___me_check_15;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE___me_check_15;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE___me_check_16;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE___me_check_16;
	 tUInt8 DEF_INST_top_DEF_CAN_FIRE___me_check_17;
	 tUInt8 DEF_INST_top_DEF_WILL_FIRE___me_check_17;
	 DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 = INST_top.INST_fsm_state_mkFSMstate.METH_read();
	 DEF_INST_top_DEF_fsm_abort_whas____d4 = INST_top.INST_fsm_abort.METH_whas();
	 DEF_INST_top_DEF_fsm_abort_wget____d5 = INST_top.INST_fsm_abort.METH_wget();
	 DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 = !DEF_INST_top_DEF_fsm_abort_whas____d4 || !DEF_INST_top_DEF_fsm_abort_wget____d5;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l100c9 = DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)5u;
	 INST_top.DEF_WILL_FIRE_RL_fsm_action_l100c9 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l100c9;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l106c9 = DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)6u;
	 INST_top.DEF_WILL_FIRE_RL_fsm_action_l106c9 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l106c9;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l110c9 = DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)7u;
	 INST_top.DEF_WILL_FIRE_RL_fsm_action_l110c9 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l110c9;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l114c13 = DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)8u;
	 INST_top.DEF_WILL_FIRE_RL_fsm_action_l114c13 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l114c13;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l115c13 = DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)9u;
	 INST_top.DEF_WILL_FIRE_RL_fsm_action_l115c13 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l115c13;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l116c13 = DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)10u;
	 INST_top.DEF_WILL_FIRE_RL_fsm_action_l116c13 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l116c13;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l117c13 = DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)11u;
	 INST_top.DEF_WILL_FIRE_RL_fsm_action_l117c13 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l117c13;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l118c14 = DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)12u;
	 INST_top.DEF_WILL_FIRE_RL_fsm_action_l118c14 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l118c14;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l119c9 = DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)13u;
	 INST_top.DEF_WILL_FIRE_RL_fsm_action_l119c9 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l119c9;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l88c13 = DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)1u;
	 INST_top.DEF_WILL_FIRE_RL_fsm_action_l88c13 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l88c13;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l90c13 = DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)3u;
	 INST_top.DEF_WILL_FIRE_RL_fsm_action_l90c13 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l90c13;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l89c13 = DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)2u;
	 INST_top.DEF_WILL_FIRE_RL_fsm_action_l89c13 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l89c13;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l91c9 = DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)4u;
	 INST_top.DEF_WILL_FIRE_RL_fsm_action_l91c9 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l91c9;
	 DEF_INST_top_DEF_fsm_state_fired__h20960 = INST_top.INST_fsm_state_fired.METH_read();
	 DEF_INST_top_DEF_fsm_start_reg_1__h20958 = INST_top.INST_fsm_start_reg_1.METH_read();
	 DEF_INST_top_DEF_fsm_start_reg__h26219 = INST_top.INST_fsm_start_reg.METH_read();
	 DEF_INST_top_DEF_fsm_state_mkFSMstate_read__1_EQ_14___d34 = DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)14u;
	 DEF_INST_top_DEF_fsm_state_mkFSMstate_read__1_EQ_0___d32 = DEF_INST_top_DEF_fsm_state_mkFSMstate_read____d31 == (tUInt8)0u;
	 DEF_INST_top_DEF_fsm_abort_whas_AND_fsm_abort_wget___d6 = DEF_INST_top_DEF_fsm_abort_whas____d4 && DEF_INST_top_DEF_fsm_abort_wget____d5;
	 DEF_INST_top_DEF_fsm_abort_whas_AND_fsm_abort_wget_OR_fsm_state_ETC___d35 = (DEF_INST_top_DEF_fsm_abort_whas_AND_fsm_abort_wget___d6 || DEF_INST_top_DEF_fsm_state_mkFSMstate_read__1_EQ_0___d32) || DEF_INST_top_DEF_fsm_state_mkFSMstate_read__1_EQ_14___d34;
	 DEF_INST_top_DEF_fsm_abort_whas_AND_fsm_abort_wget_OR_fsm_state_ETC___d137 = DEF_INST_top_DEF_fsm_abort_whas_AND_fsm_abort_wget_OR_fsm_state_ETC___d35 && (!DEF_INST_top_DEF_fsm_start_reg_1__h20958 || DEF_INST_top_DEF_fsm_state_fired__h20960);
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_fsm_start = DEF_INST_top_DEF_fsm_abort_whas_AND_fsm_abort_wget_OR_fsm_state_ETC___d137 && DEF_INST_top_DEF_fsm_start_reg__h26219;
	 DEF_INST_top_DEF_WILL_FIRE_RL_fsm_fsm_start = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_fsm_start;
	 DEF_INST_top_DEF_fsm_start_reg_1_2_AND_NOT_fsm_state_fired_3_4___d25 = DEF_INST_top_DEF_fsm_start_reg_1__h20958 && !DEF_INST_top_DEF_fsm_state_fired__h20960;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_restart = DEF_INST_top_DEF_fsm_start_reg_1_2_AND_NOT_fsm_state_fired_3_4___d25 && DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28;
	 DEF_INST_top_DEF_WILL_FIRE_RL_fsm_restart = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_restart;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_start_reg__dreg_update = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE_RL_fsm_start_reg__dreg_update = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_start_reg__dreg_update;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_state_every = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE_RL_fsm_state_every = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_state_every;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_state_fired__dreg_update = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE_RL_fsm_state_fired__dreg_update = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_state_fired__dreg_update;
	 INST_top.DEF_b__h26672 = INST_top.INST_fsmCnt.METH_read();
	 DEF_INST_top_DEF_CAN_FIRE_RL_rl_finish = !primSLE8(1u,
							    32u,
							    (tUInt32)(INST_top.DEF_b__h26672),
							    32u,
							    0u);
	 DEF_INST_top_DEF_WILL_FIRE_RL_rl_finish = DEF_INST_top_DEF_CAN_FIRE_RL_rl_finish;
	 DEF_INST_top_DEF_done___d142 = INST_top.INST_done.METH_read();
	 DEF_INST_top_DEF_CAN_FIRE_RL_rl_done = DEF_INST_top_DEF_done___d142;
	 DEF_INST_top_DEF_WILL_FIRE_RL_rl_done = DEF_INST_top_DEF_CAN_FIRE_RL_rl_done;
	 DEF_INST_top_DEF_CAN_FIRE_RL_rl_start = (DEF_INST_top_DEF_fsm_abort_whas_AND_fsm_abort_wget_OR_fsm_state_ETC___d137 && !DEF_INST_top_DEF_fsm_start_reg__h26219) && !DEF_INST_top_DEF_done___d142;
	 DEF_INST_top_DEF_WILL_FIRE_RL_rl_start = DEF_INST_top_DEF_CAN_FIRE_RL_rl_start;
	 INST_top.DEF_k__h26496 = INST_top.INST_val.METH_read();
	 DEF_INST_top_DEF_CAN_FIRE_RL_rl_step = ((((DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && !DEF_INST_top_DEF_fsm_state_mkFSMstate_read__1_EQ_0___d32) && !DEF_INST_top_DEF_fsm_state_mkFSMstate_read__1_EQ_14___d34) || DEF_INST_top_DEF_fsm_start_reg_1_2_AND_NOT_fsm_state_fired_3_4___d25) || DEF_INST_top_DEF_fsm_start_reg__h26219) && !((INST_top.DEF_k__h26496) == 0u);
	 DEF_INST_top_DEF_WILL_FIRE_RL_rl_step = DEF_INST_top_DEF_CAN_FIRE_RL_rl_step;
	 DEF_INST_top_DEF_CAN_FIRE___me_check_10 = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE___me_check_10 = DEF_INST_top_DEF_CAN_FIRE___me_check_10;
	 DEF_INST_top_DEF_CAN_FIRE___me_check_11 = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE___me_check_11 = DEF_INST_top_DEF_CAN_FIRE___me_check_11;
	 DEF_INST_top_DEF_CAN_FIRE___me_check_12 = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE___me_check_12 = DEF_INST_top_DEF_CAN_FIRE___me_check_12;
	 DEF_INST_top_DEF_CAN_FIRE___me_check_13 = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE___me_check_13 = DEF_INST_top_DEF_CAN_FIRE___me_check_13;
	 DEF_INST_top_DEF_CAN_FIRE___me_check_14 = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE___me_check_14 = DEF_INST_top_DEF_CAN_FIRE___me_check_14;
	 DEF_INST_top_DEF_CAN_FIRE___me_check_15 = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE___me_check_15 = DEF_INST_top_DEF_CAN_FIRE___me_check_15;
	 DEF_INST_top_DEF_CAN_FIRE___me_check_16 = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE___me_check_16 = DEF_INST_top_DEF_CAN_FIRE___me_check_16;
	 DEF_INST_top_DEF_CAN_FIRE___me_check_6 = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE___me_check_6 = DEF_INST_top_DEF_CAN_FIRE___me_check_6;
	 DEF_INST_top_DEF_CAN_FIRE___me_check_17 = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE___me_check_17 = DEF_INST_top_DEF_CAN_FIRE___me_check_17;
	 DEF_INST_top_DEF_CAN_FIRE___me_check_5 = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE___me_check_5 = DEF_INST_top_DEF_CAN_FIRE___me_check_5;
	 DEF_INST_top_DEF_CAN_FIRE___me_check_7 = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE___me_check_7 = DEF_INST_top_DEF_CAN_FIRE___me_check_7;
	 DEF_INST_top_DEF_CAN_FIRE___me_check_8 = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE___me_check_8 = DEF_INST_top_DEF_CAN_FIRE___me_check_8;
	 DEF_INST_top_DEF_CAN_FIRE___me_check_9 = (tUInt8)1u;
	 DEF_INST_top_DEF_WILL_FIRE___me_check_9 = DEF_INST_top_DEF_CAN_FIRE___me_check_9;
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_fsm_restart)
	   INST_top.RL_fsm_restart();
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_rl_start)
	   INST_top.RL_rl_start();
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_rl_step)
	   INST_top.RL_rl_step();
	 if (INST_top.DEF_WILL_FIRE_RL_fsm_action_l88c13)
	   INST_top.RL_fsm_action_l88c13();
	 if (INST_top.DEF_WILL_FIRE_RL_fsm_action_l89c13)
	   INST_top.RL_fsm_action_l89c13();
	 if (INST_top.DEF_WILL_FIRE_RL_fsm_action_l90c13)
	   INST_top.RL_fsm_action_l90c13();
	 if (INST_top.DEF_WILL_FIRE_RL_fsm_action_l91c9)
	   INST_top.RL_fsm_action_l91c9();
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_rl_finish)
	   INST_top.RL_rl_finish();
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_rl_done)
	   INST_top.RL_rl_done();
	 if (INST_top.DEF_WILL_FIRE_RL_fsm_action_l100c9)
	   INST_top.RL_fsm_action_l100c9();
	 if (INST_top.DEF_WILL_FIRE_RL_fsm_action_l106c9)
	   INST_top.RL_fsm_action_l106c9();
	 if (INST_top.DEF_WILL_FIRE_RL_fsm_action_l110c9)
	   INST_top.RL_fsm_action_l110c9();
	 if (INST_top.DEF_WILL_FIRE_RL_fsm_action_l114c13)
	   INST_top.RL_fsm_action_l114c13();
	 if (INST_top.DEF_WILL_FIRE_RL_fsm_action_l115c13)
	   INST_top.RL_fsm_action_l115c13();
	 if (INST_top.DEF_WILL_FIRE_RL_fsm_action_l116c13)
	   INST_top.RL_fsm_action_l116c13();
	 if (INST_top.DEF_WILL_FIRE_RL_fsm_action_l117c13)
	   INST_top.RL_fsm_action_l117c13();
	 if (INST_top.DEF_WILL_FIRE_RL_fsm_action_l118c14)
	   INST_top.RL_fsm_action_l118c14();
	 if (INST_top.DEF_WILL_FIRE_RL_fsm_action_l119c9)
	   INST_top.RL_fsm_action_l119c9();
	 if (DEF_INST_top_DEF_WILL_FIRE___me_check_6)
	   INST_top.__me_check_6();
	 if (DEF_INST_top_DEF_WILL_FIRE___me_check_7)
	   INST_top.__me_check_7();
	 if (DEF_INST_top_DEF_WILL_FIRE___me_check_8)
	   INST_top.__me_check_8();
	 if (DEF_INST_top_DEF_WILL_FIRE___me_check_9)
	   INST_top.__me_check_9();
	 if (DEF_INST_top_DEF_WILL_FIRE___me_check_10)
	   INST_top.__me_check_10();
	 if (DEF_INST_top_DEF_WILL_FIRE___me_check_12)
	   INST_top.__me_check_12();
	 if (DEF_INST_top_DEF_WILL_FIRE___me_check_11)
	   INST_top.__me_check_11();
	 if (DEF_INST_top_DEF_WILL_FIRE___me_check_13)
	   INST_top.__me_check_13();
	 if (DEF_INST_top_DEF_WILL_FIRE___me_check_14)
	   INST_top.__me_check_14();
	 if (DEF_INST_top_DEF_WILL_FIRE___me_check_15)
	   INST_top.__me_check_15();
	 if (DEF_INST_top_DEF_WILL_FIRE___me_check_16)
	   INST_top.__me_check_16();
	 if (DEF_INST_top_DEF_WILL_FIRE___me_check_17)
	   INST_top.__me_check_17();
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_fsm_fsm_start)
	   INST_top.RL_fsm_fsm_start();
	 DEF_INST_top_DEF_fsm_start_wire_whas____d7 = INST_top.INST_fsm_start_wire.METH_whas();
	 DEF_INST_top_DEF_fsm_start_wire_wget____d9 = INST_top.INST_fsm_start_wire.METH_wget();
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l87c13 = ((DEF_INST_top_DEF_fsm_start_wire_whas____d7 && DEF_INST_top_DEF_fsm_start_wire_wget____d9) && DEF_INST_top_DEF_fsm_abort_whas_AND_fsm_abort_wget_OR_fsm_state_ETC___d35) && !((((DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l119c9 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l118c14) || (DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l117c13 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l116c13)) || ((DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l115c13 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l114c13) || (DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l110c9 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l106c9))) || (((DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l100c9 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l91c9) || (DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l90c13 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l89c13)) || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l88c13));
	 INST_top.DEF_WILL_FIRE_RL_fsm_action_l87c13 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l87c13;
	 DEF_INST_top_DEF_NOT_fsm_start_wire_whas_OR_NOT_fsm_start_wire__ETC___d11 = !DEF_INST_top_DEF_fsm_start_wire_whas____d7 || !DEF_INST_top_DEF_fsm_start_wire_wget____d9;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_idle_l86c17 = (DEF_INST_top_DEF_NOT_fsm_start_wire_whas_OR_NOT_fsm_start_wire__ETC___d11 && (DEF_INST_top_DEF_NOT_fsm_abort_whas_6_OR_NOT_fsm_abort_wget_7___d28 && DEF_INST_top_DEF_fsm_state_mkFSMstate_read__1_EQ_14___d34)) && !((((DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l119c9 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l118c14) || (DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l117c13 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l116c13)) || ((DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l115c13 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l114c13) || (DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l110c9 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l106c9))) || (((DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l100c9 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l91c9) || (DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l90c13 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l89c13)) || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l88c13));
	 DEF_INST_top_DEF_WILL_FIRE_RL_fsm_idle_l86c17 = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_idle_l86c17;
	 DEF_INST_top_DEF_CAN_FIRE_RL_fsm_state_handle_abort = (DEF_INST_top_DEF_fsm_abort_whas_AND_fsm_abort_wget___d6 && DEF_INST_top_DEF_NOT_fsm_start_wire_whas_OR_NOT_fsm_start_wire__ETC___d11) && !((((DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l119c9 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l118c14) || (DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l117c13 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l116c13)) || ((DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l115c13 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l114c13) || (DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l110c9 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l106c9))) || (((DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l100c9 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l91c9) || (DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l90c13 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l89c13)) || (DEF_INST_top_DEF_CAN_FIRE_RL_fsm_action_l88c13 || DEF_INST_top_DEF_CAN_FIRE_RL_fsm_restart)));
	 DEF_INST_top_DEF_WILL_FIRE_RL_fsm_state_handle_abort = DEF_INST_top_DEF_CAN_FIRE_RL_fsm_state_handle_abort;
	 if (INST_top.DEF_WILL_FIRE_RL_fsm_action_l87c13)
	   INST_top.RL_fsm_action_l87c13();
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_fsm_start_reg__dreg_update)
	   INST_top.RL_fsm_start_reg__dreg_update();
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_fsm_state_handle_abort)
	   INST_top.RL_fsm_state_handle_abort();
	 if (DEF_INST_top_DEF_WILL_FIRE___me_check_5)
	   INST_top.__me_check_5();
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_fsm_idle_l86c17)
	   INST_top.RL_fsm_idle_l86c17();
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_fsm_state_every)
	   INST_top.RL_fsm_state_every();
	 if (DEF_INST_top_DEF_WILL_FIRE_RL_fsm_state_fired__dreg_update)
	   INST_top.RL_fsm_state_fired__dreg_update();
	 INST_top.INST_fsm_state_fired_1.clk((tUInt8)1u, (tUInt8)1u);
	 INST_top.INST_fsm_state_overlap_pw.clk((tUInt8)1u, (tUInt8)1u);
	 INST_top.INST_fsm_state_set_pw.clk((tUInt8)1u, (tUInt8)1u);
	 INST_top.INST_fsm_abort.clk((tUInt8)1u, (tUInt8)1u);
	 INST_top.INST_fsm_start_reg_2.clk((tUInt8)1u, (tUInt8)1u);
	 INST_top.INST_fsm_start_wire.clk((tUInt8)1u, (tUInt8)1u);
	 if (do_reset_ticks(simHdl))
	 {
	   INST_top.INST_val.rst_tick__clk__1((tUInt8)1u);
	   INST_top.INST_done.rst_tick__clk__1((tUInt8)1u);
	   INST_top.INST_fsmCnt.rst_tick__clk__1((tUInt8)1u);
	   INST_top.INST_hash.rst_tick__clk__1((tUInt8)1u);
	   INST_top.INST_fsm_start_reg.rst_tick__clk__1((tUInt8)1u);
	   INST_top.INST_fsm_start_reg_1.rst_tick__clk__1((tUInt8)1u);
	   INST_top.INST_fsm_state_mkFSMstate.rst_tick__clk__1((tUInt8)1u);
	   INST_top.INST_fsm_state_fired.rst_tick__clk__1((tUInt8)1u);
	   INST_top.INST_fsm_state_can_overlap.rst_tick__clk__1((tUInt8)1u);
	 }
       };

/* Model creation/destruction functions */

void MODEL_mkTb::create_model(tSimStateHdl simHdl, bool master)
{
  sim_hdl = simHdl;
  init_reset_request_counters(sim_hdl);
  mkTb_instance = new MOD_mkTb(sim_hdl, "top", NULL);
  bk_get_or_define_clock(sim_hdl, "CLK");
  if (master)
  {
    bk_alter_clock(sim_hdl, bk_get_clock_by_name(sim_hdl, "CLK"), CLK_LOW, false, 0llu, 5llu, 5llu);
    bk_use_default_reset(sim_hdl);
  }
  bk_set_clock_event_fn(sim_hdl,
			bk_get_clock_by_name(sim_hdl, "CLK"),
			schedule_posedge_CLK,
			NULL,
			(tEdgeDirection)(POSEDGE));
  (mkTb_instance->INST_fsm_start_wire.set_clk_0)("CLK");
  (mkTb_instance->INST_fsm_start_reg_2.set_clk_0)("CLK");
  (mkTb_instance->INST_fsm_abort.set_clk_0)("CLK");
  (mkTb_instance->INST_fsm_state_set_pw.set_clk_0)("CLK");
  (mkTb_instance->INST_fsm_state_overlap_pw.set_clk_0)("CLK");
  (mkTb_instance->INST_fsm_state_fired_1.set_clk_0)("CLK");
  (mkTb_instance->set_clk_0)("CLK");
}
void MODEL_mkTb::destroy_model()
{
  delete mkTb_instance;
  mkTb_instance = NULL;
}
void MODEL_mkTb::reset_model(bool asserted)
{
  (mkTb_instance->reset_RST_N)(asserted ? (tUInt8)0u : (tUInt8)1u);
}
void * MODEL_mkTb::get_instance()
{
  return mkTb_instance;
}

/* Fill in version numbers */
void MODEL_mkTb::get_version(char const **name, char const **build)
{
  *name = "2022.01-29-gc526ff54";
  *build = "c526ff54";
}

/* Get the model creation time */
time_t MODEL_mkTb::get_creation_time()
{
  
  /* Wed Nov 30 10:24:30 UTC 2022 */
  return 1669803870llu;
}

/* State dumping function */
void MODEL_mkTb::dump_state()
{
  (mkTb_instance->dump_state)(0u);
}

/* VCD dumping functions */
MOD_mkTb & mkTb_backing(tSimStateHdl simHdl)
{
  static MOD_mkTb *instance = NULL;
  if (instance == NULL)
  {
    vcd_set_backing_instance(simHdl, true);
    instance = new MOD_mkTb(simHdl, "top", NULL);
    vcd_set_backing_instance(simHdl, false);
  }
  return *instance;
}
void MODEL_mkTb::dump_VCD_defs()
{
  (mkTb_instance->dump_VCD_defs)(vcd_depth(sim_hdl));
}
void MODEL_mkTb::dump_VCD(tVCDDumpType dt)
{
  (mkTb_instance->dump_VCD)(dt, vcd_depth(sim_hdl), mkTb_backing(sim_hdl));
}
