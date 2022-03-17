/*
 * my_fsm.h
 *
 *  Created on: Mar 17, 2022
 *      Author: Mark
 */

#ifndef MY_FSM_H_
#define MY_FSM_H_


//outputs correspond to ranges:
// -4 <= p < -1,    -1 <= p < 0,    0 <= p <= 1,    1 < p <= 4
struct State1 {
    uint8_t out;                // 2-bit output
    uint8_t state;                // current state
    uint8_t variable_speeds; //center, left, right
  const struct State *next[5]; // Next if 2-bit input is 0-3
};
typedef const struct State1 State_t;

#define cntr      &fsm[0]
#define lctr      &fsm[1]
#define stop      &fsm[2]
#define ctrR      &fsm[3]
#define ctrL      &fsm[4]
#define rght      &fsm[5]
#define lrgt      &fsm[6]
#define left      &fsm[7]
#define llft      &fsm[8]
State_t fsm[9]={
  {0xFF, 0x00, 0x00, { ctrR, ctrR, ctrL, ctrL, lctr }},  // center
  {0xF0, 0x01, 0x00, { ctrR, cntr, cntr, ctrL, stop }},  // lost center
  {0x00, 0x02, 0x00, { stop, stop, stop, stop, stop }},   // stop
  {0xFF, 0x03, 0x00, { rght, ctrR, cntr, ctrL, lrgt }},   // center right
  {0xFF, 0x04, 0x00, { ctrR, cntr, ctrL, left, llft }},   // center left
  {0x0F, 0x05, 0xF0, { rght, ctrR, ctrR, cntr, lrgt }},  // right
  {0x0F, 0x06, 0x00, { rght, ctrR, ctrR, cntr, stop }},  // lost right
  {0xF0, 0x07, 0x0F, { cntr, ctrL, ctrL, left, llft }},   // left
  {0xF0, 0x08, 0x00, { cntr, ctrL, ctrL, left, stop }}   // lost left
};

void next_state_and_output(uint32_t *input, uint32_t *output);

#endif /* MY_FSM_H_ */
