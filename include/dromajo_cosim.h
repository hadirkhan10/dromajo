/*
 * API for Dromajo-based cosimulation
 *
 * Copyright (C) 2018,2019, Esperanto Technologies Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License")
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _DROMAJO_COSIM_H
#define _DROMAJO_COSIM_H 1

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct dromajo_cosim_state_st dromajo_cosim_state_t;

//  Struct for MPDT cosim

typedef struct Dromajo_cosim_front_step_t
{
    uint64_t plus_pc;
    uint32_t plus_insn;
    int most_recently_written_reg;
    int most_recently_written_fp_reg;
    uint64_t plus_wdata;
    int status_code;
    int interp64_status;
    uint64_t plus_prev_pc;
    int plus_prev_delta;
    int plus_priv;
} dromajo_cosim_front_step_t;


/*
 * dromajo_cosim_init --
 *
 * Creates and initialize the state of the RISC-V ISA golden model
 * Returns NULL upon failure.
 */
dromajo_cosim_state_t *dromajo_cosim_init(int argc, char *argv[]);

/* dromajo_cosim_front_init
*/

dromajo_cosim_front_step_t* dormajo_cosim_front_init(dromajo_cosim_front_step_t* front_pointer);


/*
 * dromajo_cosim_fini --
 *
 * Destroys the states and releases the resources.
 */
void dromajo_cosim_fini(dromajo_cosim_state_t *state);

/*
 * dromajo_cosim_step --
 *
 * executes exactly one instruction in the golden model and returns
 * zero if the supplied expected values match and execution should
 * continue.  A non-zero value signals termination with the exit code
 * being the upper bits (ie., all but LSB).  Caveat: the DUT is
 * assumed to provide the instructions bit after expansion, so this is
 * only matched on non-compressed instruction.
 *
 * There are a number of situations where the model cannot match the
 * DUT, such as loads from IO devices, interrupts, and CSRs cycle,
 * time, and instret.  For all these cases the model will override
 * with the expected values.
 */
int dromajo_cosim_step(dromajo_cosim_state_t *state,
                       int                    hartid,
                       uint64_t               dut_pc,
                       uint32_t               dut_insn,
                       uint64_t               dut_wdata,
                       uint64_t               mstatus,
                       bool                   check);




//int dromajo_cosim_step(dromajo_cosim_state_t *state, int hartid, uint64_t dut_pc);
/*  Dormajo Cosim Front Step.
*   This function is to cosimulate and check fetch addresses. 
*   It takes the state, hartID, and fetch address as arguements
*   returns 0 if correct, and not 0 if not, enclonsed in dromajo_cosim_front_step_t
*/
void dromajo_cosim_front_step(dromajo_cosim_state_t* state_plus, dromajo_cosim_front_step_t* front_returner, 
                                int hartid, uint64_t dut_fetch_addr); 


/*
 * dromajo_cosim_raise_trap --
 *
 * DUT raises a trap (exception or interrupt) and provides the cause.
 * MSB indicates an asynchronous interrupt, synchronous exception
 * otherwise.
 */
void dromajo_cosim_raise_trap(dromajo_cosim_state_t *state,
                              int                   hartid,
                              uint64_t              dut_pc,
                              uint32_t              dut_insn,
                              int64_t               cause);
#ifdef __cplusplus
} // extern C
#endif

#endif
