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
#include "../../inc/modules/reverb.hpp"


void c_reverb::init(void){

	//Initialize comb filters
	comb[0].init(bufcomb1,sbuf_comb_1);
	comb[1].init(bufcomb2,sbuf_comb_2);
	comb[2].init(bufcomb3,sbuf_comb_3);
	comb[3].init(bufcomb4,sbuf_comb_4);
	comb[4].init(bufcomb5,sbuf_comb_5);
	comb[5].init(bufcomb6,sbuf_comb_6);
	comb[6].init(bufcomb7,sbuf_comb_7);
	comb[7].init(bufcomb8,sbuf_comb_8);


	//Initialize allpass filters
	allpass[0].init(bufap1,sbuf_ap_1);
	allpass[1].init(bufap1,sbuf_ap_2);
	allpass[2].init(bufap1,sbuf_ap_3);
	allpass[3].init(bufap1,sbuf_ap_4);

	//Initialize with default values
	set_wet(&initial_wet);
	set_size(&initial_size);
	set_damp(&initial_damp);

	//Resetting buffer
	reset_buffer();


}

void c_reverb::start(void){

	//Start comb filters
	unsigned i;
	for(i=0;i<n_comb;i++){
		comb[i].start();
	}

	//Start allpass filters
	for(i=0;i<n_allpass;i++){
		allpass[i].start();
	}

	//Set status
	status=1;

}

void c_reverb::stop(void){

	//Set status
	status=0;

	//Fill the delay buffer with zeros
	reset_buffer();

	//Stop comb filters
	unsigned i;
	for(i=0;i<n_comb;i++){
		comb[i].stop();
	}

	//Stop allpass filters
	for(i=0;i<n_allpass;i++){
		allpass[i].stop();
	}
}

void c_reverb::reset_buffer(void){

	//Fill the delay buffer with zeros
	unsigned i;
	for(i=0;i<n_comb;i++){
		comb[i].reset();
	}

	//Update the parameter of allpass filters (Pointer on 2nd element: Roomsize)
	for(i=0;i<n_allpass;i++){
		allpass[i].reset();
	}

}

void c_reverb::set_wet(float* w){

	//Update the dry&wet mix
	wetmix=*w*0.01;
	drymix=1-wetmix;

}

void c_reverb::set_size(float* s){

	//Scale and set feedback parameter
	float feedback;

	feedback=(*s*0.01*scaleroom) + offsetroom;

	//Update the parameter of comb filters (Pointer on 2nd element: Roomsize)
	unsigned i;
	for(i=0;i<n_comb;i++){
		comb[i].set_feedback(&feedback);
	}

	//Update the parameter of allpass filters (Pointer on 2nd element: Roomsize)
	for(i=0;i<n_allpass;i++){
		allpass[i].set_feedback(&feedback);
	}

}

void c_reverb::set_damp(float* d){

	//Scale and set damp
	float damp=*d*0.01*scaledamp;

	//Update the parameter of comb filters (Pointer on 2nd element: Roomsize)
	unsigned i;
	for(i=0;i<n_comb;i++){
		comb[i].set_damp(&damp);
	}

}


float c_reverb::process(float x){

	float y;
	y=0;

	//Feed the parallel comb filters
	unsigned i;
	for(i=0;i<n_comb;i++){
		y+=comb[i].process(x);
	}

	//Pass through the serial allpass filters
	for(i=0;i<n_allpass;i++){
		y=allpass[i].process(y);
	}

	//Attenuate output and mix wet& dry
	y=y*fixedgain*wetmix+x*drymix;

	return y;
}
