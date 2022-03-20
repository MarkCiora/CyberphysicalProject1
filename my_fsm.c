/*
 * my_fsm.c
 *
 *  Created on: Mar 17, 2022
 *      Author: Mark
 */

#include <stdint.h>
#include "my_fsm.h"

#define cntr      &fsm2[0]
#define lctr      &fsm2[1]
#define stop      &fsm2[2]
#define ctrR      &fsm2[3]
#define ctrL      &fsm2[4]
#define rght      &fsm2[5]
#define lrgt      &fsm2[6]
#define left      &fsm2[7]
#define llft      &fsm2[8]
State_t fsm2[9]={
  {{2500, 2500}, 0x00, { ctrR, ctrR, ctrL, ctrL, lctr }},  // center
  {{2500, -2500}, 0x01, {ctrR, cntr, cntr, ctrL, stop }},  // lost center
  {{0x0000, 0x0000}, 0x02, { stop, stop, stop, stop, stop }},   // stop
  {{2500, 2500}, 0x03, { rght, ctrR, cntr, ctrL, lrgt }},   // center right
  {{2500, 2500}, 0x04, { ctrR, cntr, ctrL, left, llft }},   // center left
  {{-2500, 2500}, 0x05, { rght, ctrR, ctrR, cntr, lrgt }},  // right
  {{-2500, 2500}, 0x06, { rght, ctrR, ctrR, cntr, stop }},  // lost right
  {{2500, -2500}, 0x07, { cntr, ctrL, ctrL, left, llft }},   // left
  {{2500, -2500}, 0x08, { cntr, ctrL, ctrL, left, stop }}   // lost left
};

State_t *ptr;

void set_state_start(){
    ptr = cntr;
}

void next_state_and_output(int32_t *input, int16_t output[2]){
    uint32_t next_num=2;
    if (*input < -4800*2){
        next_num = 0;
    }else if(*input < 0){
        next_num = 1;
    }else if(*input < 4800*2){
        next_num = 2;
    }else if(*input < 33400){
        next_num = 3;
    }else if(*input == 1000000){
        next_num = 4;
    }
    ptr = ptr->next[next_num];
    output[0] = ptr->out[1];
    output[1] = ptr->out[0];
    int j = 0;
}
