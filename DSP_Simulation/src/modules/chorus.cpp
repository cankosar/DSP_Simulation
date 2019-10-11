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

	//Chorus pointer
	cptr=0;

	//Current angle of LFO
	a_lfo=0;

	//Angle step
	a_step=(rate*2*PI)/FS;

	//Resetting buffer
	reset_buffer();
}

void chorus::stop(void){

	//Status set
	status=0;

	//Fill the delay buffer with zeros
	reset_buffer();

}

void chorus::start(void){

	//Status set
	status=1;
}

void chorus::set_wet(float *w){
	G_w=*w*0.01;
	G_d=1-G_w;
}

void chorus::set_depth(float *d){
	depth=*d;
}

void chorus::set_rate(float *r){
	rate=*r;
	a_step=(rate*2*PI)/FS;
}

void chorus::reset_buffer(void){
	//Fill the delay buffer with zeros
	//The size of the float is 4

	memset(cbuf, 0, chorus_len*sizeof(*cbuf));
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
