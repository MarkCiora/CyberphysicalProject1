/*
 * my_fsm.c
 *
 *  Created on: Mar 17, 2022
 *      Author: Mark
 */

#include <stdint.h>
#include "my_fsm.h"
/*
#define cntr      &fsm2[0]
#define lctr1     &fsm2[1]
#define lctr2     &fsm2[2]
#define lctr3     &fsm2[3]
#define lctr4     &fsm2[4]
#define lctr5     &fsm2[5]
#define stop      &fsm2[6]
#define ctrR      &fsm2[7]
#define ctrL      &fsm2[8]
#define rght      &fsm2[9]
#define lrgt1     &fsm2[10]
#define lrgt2     &fsm2[11]
#define lrgt3     &fsm2[12]
#define lrgt4     &fsm2[13]
#define lrgt5     &fsm2[14]
#define left      &fsm2[15]
#define llft1     &fsm2[16]
#define llft2     &fsm2[17]
#define llft3     &fsm2[18]
#define llft4     &fsm2[19]
#define llft5     &fsm2[20]
State_t fsm2[21]={
  {{4000, 4000}, { ctrR, ctrR, ctrL, ctrL, lctr1 }},  // center
  {{3500, 3500}, {ctrR, cntr, cntr, ctrL, lctr2 }},  // lost center  // center
  {{3500, 3500}, {ctrR, cntr, cntr, ctrL, lctr3 }},
  {{3250, 3250}, {ctrR, cntr, cntr, ctrL, lctr4 }},
  {{3250, 3250}, {ctrR, cntr, cntr, ctrL, lctr5 }},
  {{3250, 3250}, {ctrR, cntr, cntr, ctrL, stop }},
  {{0000, 0000}, { stop, stop, stop, stop, stop }},   // stop
  {{4000, 4000}, { rght, ctrR, cntr, ctrL, lrgt1 }},   // center right
  {{3750, 3250}, { ctrR, cntr, ctrL, left, llft1 }},   // center left
  {{-5000, 5000}, { rght, ctrR, ctrR, cntr, lrgt1 }},  // right
  {{-5000, 5000}, { rght, ctrR, ctrR, cntr, lrgt2 }},  // lost right
  {{-5000, 5000}, { rght, ctrR, ctrR, cntr, lrgt3 }},
  {{-5000, 5000}, { rght, ctrR, ctrR, cntr, lrgt4 }},
  {{-5000, 5000}, { rght, ctrR, ctrR, cntr, lrgt5 }},
  {{-5000, 5000}, { rght, ctrR, ctrR, cntr, stop }},
  {{5000, -5000}, { cntr, ctrL, ctrL, left, llft1 }},   // left
  {{5000, -5000}, { cntr, ctrL, ctrL, left, llft2 }},   // lost left
  {{5000, -5000}, { cntr, ctrL, ctrL, left, llft3 }},
  {{5000, -5000}, { cntr, ctrL, ctrL, left, llft4 }},
  {{5000, -5000}, { cntr, ctrL, ctrL, left, llft5 }},
  {{5000, -5000}, { cntr, ctrL, ctrL, left, stop }}
};
*/
#define cntr      &fsm2[0]
#define lctr     &fsm2[1]
#define ctrR      &fsm2[2]
#define ctrL      &fsm2[3]
#define rght      &fsm2[4]
#define lrgt     &fsm2[5]
#define left      &fsm2[6]
#define llft     &fsm2[7]
State_t fsm2[8]={
  {{8000, 8000}, { ctrR, ctrR, cntr, ctrL, ctrL, lctr }},  // center
  {{8000, 8000}, {ctrR, cntr, cntr, cntr, ctrL, lctr }}, //lost center
  {{8000, 8000}, { rght, ctrR, cntr, cntr, ctrL, lrgt }},   // center right
  {{8000, 8000}, { ctrR, cntr, cntr, ctrL, left, llft }},   // center left
  {{-2000, 10000}, { rght, ctrR, ctrR, ctrR, cntr, lrgt }},  // right
  {{-6000, 8000}, { rght, ctrR, ctrR, ctrR, cntr, lrgt }},  // lost right
  {{10000, -2000}, { cntr, ctrL, ctrL, ctrL, left, llft }},   // left
  {{8000, -6000}, { cntr, ctrL, ctrL, ctrL, left, llft }},  //lost left
};


State_t *ptr;

void set_state_start(){
    ptr = cntr;
}

void next_state_and_output(int32_t *input, int16_t output[2]){
    uint32_t next_num=2;
    if (*input < -30000){
        next_num = 0;
    }else if(*input < -15000){
        next_num = 1;
    }else if (*input < 15000){
        next_num = 2;
    }else if(*input <= 30000){
        next_num = 3;
    }else if(*input <= 33400){
        next_num = 4;
    }else if(*input == 1000000){
        next_num = 5;
    }
    ptr = ptr->next[next_num];
    if (ptr == ctrR){
        output[0] = ptr->out[1];
        output[1] = ptr->out[0] + ((*input - 15000) / 5);
    }else if (ptr == ctrL){
        output[0] = ptr->out[1] - ((*input + 15000) / 5);
        output[1] = ptr->out[0];
    }else {
        output[0] = ptr->out[1];
        output[1] = ptr->out[0];
    }
}
