/*
 * chorus.cpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#include "stdio.h"
//#include "string.h"
//#include "math.h"
//#include "../../inc/constants.hpp"
#include "../../inc/modules/allpass.hpp"
#include "../../inc/modules/reverb_parameters.hpp"
#include "../../inc/modules/denormals.h"

void allpass::init(float* bufptr, unsigned size){

	//Set the buffer to the incoming pointer
	buffer=bufptr;
	bufsize=size;

	//Initialize pointer
	aptr=0;

	//Resetting buffer
	reset_buffer();

	float inithash[]={0.999};
	update(inithash);

	printf("Feedback:%f\n",feedback);
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

	unsigned i;
	for(i=0;i<bufsize;i++){
		buffer[i]=0;
	}
}

void allpass::update(float* param_arr){

	feedback=param_arr[0];

}


float allpass::process(float x){

	float y;
	float bufout;

	bufout = buffer[aptr];
//	printf("aptr=%d\n",aptr);
	undenormalise(bufout);

//	y = -x + bufout;
//	buffer[aptr] = x + (bufout*feedback);

	buffer[aptr] = x + (bufout*feedback);
	y = -buffer[aptr]*feedback + bufout;

	if(++aptr>=bufsize) aptr = 0;

	return y;
}
