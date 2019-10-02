/*
 * chorus.cpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#include "stdio.h"
#include "string.h"
//#include "math.h"
//#include "../../inc/constants.hpp"
#include "../../inc/modules/reverb_parameters.hpp"
#include "../../inc/modules/comb.hpp"
#include "../../inc/modules/denormals.h"

void comb::init(float* bufptr, unsigned size){

	//Set the buffer to the incoming pointer
	buffer=bufptr;
	bufsize=size;

	//Initialize pointer
	cptr=0;
	filterstore=0;

	//Resetting buffer
	reset_buffer();

	//Status set
	status=1;

}

void comb::reset(void){

	//Fill the delay buffer with zeros
	reset_buffer();

}

void comb::reset_buffer(void){

	//Fill the delay buffer with zeros
	memset(buffer, 0, bufsize*sizeof(*buffer));

//	unsigned i;
//	for(i=0;i<bufsize;i++){
//		buffer[i]=0;
//	}
}

void comb::update(float feedback_in, float damp){

	//Scale and set damp
	damp1=damp;
	//Helping variable damp2
	damp2=1-damp1;

	//Scale and set feedback parameter
	feedback=(feedback_in*scaleroom) + offsetroom;

}


float comb::process(float x){

	float y;

	y = buffer[cptr];
//	undenormalise(y);

	filterstore = (y*damp2) + (filterstore*damp1);
//	undenormalise(filterstore);

	buffer[cptr] = x + (filterstore*feedback);

	if(++cptr>=bufsize) cptr = 0;
//
	return y;
}
