/*
 * delay.cpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */
#include "stdio.h"
#include "string.h"

#include "../../inc/constants.hpp"
#include "../../inc/modules/delay.hpp"

void delay::init(void){

	//Set parameters
	set_wet(&initial_wet);
	set_dry(&initial_dry);
	set_feedback(&initial_fb);
	set_time(&initial_time);

	//Clean buffer
	reset_buffer();

}

void delay::reset_buffer(void){
	//Fill the delay buffer with zeros

	memset(dbuf, 0, delay_max*sizeof(*dbuf));

	//Delay array pointer
	dptr=0;
}

void delay::set_wet(float *wet){

	G_w=*wet*0.01;

}

void delay::set_dry(float *dry){

	G_d=*dry*0.01;

}

void delay::set_time(float *time){

	delay_time=*time*0.001;		//Should be unnecessary
	n_distance=(unsigned long)(*time*FSms);

	//Security for delay length
	if(n_distance>delay_max){
		n_distance=delay_max;
	}

	reset_buffer();

}

void delay::set_feedback(float* fb){

	G_fb=*fb*0.009;		//Max value: 0.9 for stability reasons

}

void delay::start(void){

	status=1;

}

void delay::stop(void){

	status=0;
	reset_buffer();

}

float delay::process(float x){

	float y;

	//Calculate output
	y=dbuf[dptr]*G_w+x*G_d;

	//Update buffer
	dbuf[dptr]=x+dbuf[dptr]*G_fb;

	//Increment pointer
	dptr++;

	if(dptr>=n_distance){
		dptr=0;
	}


	return y;
}
