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


void reverb::init(void){

	printf("Init reverb\n");

	//Init array

//	unsigned i;
//
//	for(i=0;i<sbuf_comb_1;i++){
//		bufcomb1[i]=i*2;
//	}


	//Initialize comb filters
	inst_comb[0].init(bufcomb1,sbuf_comb_1);
	inst_comb[1].init(bufcomb2,sbuf_comb_2);
	inst_comb[2].init(bufcomb3,sbuf_comb_3);
	inst_comb[3].init(bufcomb4,sbuf_comb_4);
	inst_comb[4].init(bufcomb5,sbuf_comb_5);
	inst_comb[5].init(bufcomb6,sbuf_comb_6);
	inst_comb[6].init(bufcomb7,sbuf_comb_7);
	inst_comb[7].init(bufcomb8,sbuf_comb_8);


	//Initialize allpass filters
	inst_allpass[0].init(bufap1,sbuf_ap_1);
	inst_allpass[1].init(bufap1,sbuf_ap_2);
	inst_allpass[2].init(bufap1,sbuf_ap_3);
	inst_allpass[3].init(bufap1,sbuf_ap_4);




	//Resetting buffer
	reset_buffer();

	//Status set
	status=1;

}

void reverb::reset(void){

	//Resetting chorus
	printf("Resetting reverb\n");

	//Fill the delay buffer with zeros
	reset_buffer();

}

void reverb::reset_buffer(void){
	//Fill the delay buffer with zeros
	//The size of the float is 4

//	memset(cbuf, 0, chorus_len*sizeof(*cbuf));
}

void reverb::update(float* param_arr){



}


float reverb::process(float x){

	float y;
	y=0;

//	//Attenuate input, because 8 filters in parallel
	x=x*fixedgain;

	unsigned i;
	for(i=0;i<n_comb;i++){
		y+=inst_comb[i].process(x);
	}

//	y=x;

	for(i=0;i<n_allpass;i++){
		y=inst_allpass[i].process(y);
	}

//	y=inst_allpass[0].process(y);
//
//	y=inst_allpass[1].process(y);


	return y;
}
