/*
 * my_fsm.h
 *
 *  Created on: Mar 17, 2022
 *      Author: Mark
 */

#ifndef MY_FSM_H_
#define MY_FSM_H_

#include <stdint.h>


//outputs correspond to ranges:
// -4 <= p < -1,    -1 <= p < 0,    0 <= p <= 1,    1 < p <= 4
struct State1 {
    int16_t out[2];
    uint8_t state;                // current state
  const struct State1 *next[5]; // Next if 2-bit input is 0-3
};
typedef const struct State1 State_t;

void set_state_start();

void next_state_and_output(int32_t *input, int16_t output[2]);

#endif /* MY_FSM_H_ */
