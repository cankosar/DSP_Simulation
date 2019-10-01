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
#include "../../inc/modules/comb.hpp"


void comb::init(void){



	//Resetting buffer
	reset_buffer();

	//Status set
	status=1;

}

void comb::reset(void){

	//Resetting chorus
//	printf("Resetting reverb\n");

	//Fill the delay buffer with zeros
	reset_buffer();

}

void comb::reset_buffer(void){
	//Fill the delay buffer with zeros
	//The size of the float is 4

//	memset(cbuf, 0, chorus_len*sizeof(*cbuf));
}

void comb::update(float* param_arr){



}


float comb::process(float x){

	float y;

	y = buffer[cptr];
//	undenormalise(output);

	filterstore = (y*damp2) + (filterstore*damp1);
//	undenormalise(filterstore);

	buffer[cptr] = x + (filterstore*feedback);

	if(++cptr>=bufsize) cptr = 0;

	return y;
}
