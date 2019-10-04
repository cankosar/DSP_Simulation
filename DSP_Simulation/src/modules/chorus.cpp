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
#include "../../inc/modules/chorus.hpp"


void chorus::init(void){

	//Chorus parameter
	G_d=0.9; //Dry gain (Dry/Wet mix)
	G_w=0.3; //Wet gain (Dry/Wet mix)
	depth=2; //Depth
	d_base=10;	//Base delay in ms /Max 25
	rate=1;

	//Chorus pointer
	cptr=0;

	//Angle step
	a_step=(rate*2*PI)/(FS);

	//Current angle of LFO
	a_lfo=0;

	//Resetting buffer
	reset_buffer();

	//Status set
	status=1;

}

void chorus::reset(void){

	//Fill the delay buffer with zeros
	reset_buffer();

}

void chorus::reset_buffer(void){
	//Fill the delay buffer with zeros
	//The size of the float is 4

	memset(cbuf, 0, chorus_len*sizeof(*cbuf));
}

void chorus::update(float* param_arr){



}


float chorus::process(float x){

	float y;

	float t_c;	//Current delay

	//Get tap distance
	t_c=get_current_delay(); //Tap distance

	//Calculate the position of the pointer
	int wptr;

	wptr=cptr-lrint(t_c*FSms);

	if(wptr<0){
		wptr+=chorus_len;
	}

	//Calculate output
	y=G_d*x + G_w*cbuf[wptr];

	//Update the buffer
	cbuf[cptr]=x;

	//Increment
	cptr++;
	if(cptr>=chorus_len){
		cptr-=chorus_len;
	}

	return y;
}


float chorus::get_current_delay(void){

	//Calculate time
	float t;
	t=d_base+depth*lfo();

	//Return the delay time
	return t;

}


float chorus::lfo(void){

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
