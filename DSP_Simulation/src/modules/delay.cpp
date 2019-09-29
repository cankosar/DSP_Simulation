/*
 * delay.cpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#include "../../inc/constants.hpp"
#include "../../inc/modules/delay.hpp"

void delay::init(void){

	//Dummy delay parameter
	G_fb=0.2; //Feedback gain
	G_d=1; //Dry gain (Dry/Wet mix)
	G_w=0.0; //Wet gain (Dry/Wet mix)
	delay_time=0.6; //Delay time in seconds

	n_distance=delay_time*FS;

	//Delay array pointer
	dptr=0;

	//Clean buffer
	long unsigned i;
	for(i=0;i<delay_len;i++){
		dbuf[i]=0;
	}

}

void delay::reset(){



}

void delay::update(float *param_arr){



}

float delay::process(float x){

	float y;

	//Calculate output
	y=dbuf[dptr]*G_w+x*G_d;

	//Calculate update pointer
	long int wptr;	//Write pointer
	wptr=dptr-n_distance;
	if(wptr<0){
		wptr+=delay_len;
	}

	//Update buffer
	dbuf[wptr]=x+dbuf[dptr]*G_fb;

	//Increment pointer
	dptr++;

	if(dptr>=delay_len){
		dptr-=delay_len;
	}


	return y;
}
