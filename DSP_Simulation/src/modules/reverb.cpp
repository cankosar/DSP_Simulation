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


	comb inst_comb((unsigned)2);

	inst_comb.init();
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

	y=x;

//	y=inst_comb.process(y);

	return y;
}
