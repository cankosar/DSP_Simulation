/*
 * chorus.cpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#include "stdio.h"
#include "string.h"
#include "math.h"
#include "../../inc/constants.hpp"
#include "../../inc/modules/rotary.hpp"


void rotary::init(void){

	//Chorus parameter
	depth=0.5; //Depth
	d_base=5;	//Base delay in ms
	rate=5;		//Max. 25

	//Chorus pointer
	rptr=0;

	//Angle step
	a_step=(rate*2*PI)/(FS);

	//Current angle of LFO
	a_lfo=0;

	//Resetting buffer
	reset_buffer();

	//Status set
	status=1;

}

void rotary::reset(void){

	//Fill the delay buffer with zeros
	reset_buffer();

}

void rotary::reset_buffer(void){
	//Fill the delay buffer with zeros
	//The size of the float is 4

	memset(rbuf, 0, rotary_len*sizeof(*rbuf));
}

void rotary::update(float* param_arr){



}


float rotary::process(float x){

	float y;

	float t_c;	//Current delay

	//Get current delay
	t_c=get_current_delay(); //Delay time

	//Calculate the position of the pointer
	int wptr;

	wptr=rptr-lrint(t_c*FSms);

//	printf("Ptr:%d Dist: %d\n",wptr,lrint(t_c*FSms));

	if(wptr<0){
		wptr+=rotary_len;
	}

	//Calculate output
	y=rbuf[wptr];

	//Update the buffer
	rbuf[rptr]=x;

	//Increment
	rptr++;
	if(rptr>=rotary_len){
		rptr-=rotary_len;
	}

	return y;
}


float rotary::get_current_delay(void){

	//Calculate time
	float t;
	t=d_base+depth*lfo();

	//Return the delay time
	return t;

}


float rotary::lfo(void){

	float y_lfo;

	//Calculate LFO value
	y_lfo=sin(a_lfo);

	//Update angle
	a_lfo+=a_step;
	if(a_lfo>=2*PI){
		a_lfo=a_lfo-2*PI;
	}

	return y_lfo;
}
