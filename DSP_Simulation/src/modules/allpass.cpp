/*
 * chorus.cpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

//#include "stdio.h"
//#include "string.h"
//#include "math.h"
//#include "../../inc/constants.hpp"
#include "../../inc/modules/allpass.hpp"


void allpass::init(void){



	//Resetting buffer
	reset_buffer();

	//Status set
	status=1;

}

void allpass::reset(void){

	//Resetting chorus
//	printf("Resetting reverb\n");

	//Fill the delay buffer with zeros
	reset_buffer();

}

void allpass::reset_buffer(void){
	//Fill the delay buffer with zeros
	//The size of the float is 4

//	memset(cbuf, 0, chorus_len*sizeof(*cbuf));
}

void allpass::update(float* param_arr){



}


float allpass::process(float x){

	float y;


	return y;
}
