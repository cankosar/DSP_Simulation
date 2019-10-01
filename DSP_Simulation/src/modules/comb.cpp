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
//	float inithash[]={initialroom,initialdamp};
	float inithash[]={0.99,0.8};
	update(inithash);

//	printf("Feedback:%f, Damp1:%f, Damp2:%f\n",feedback,damp1,damp2);
//	printf("Buffer Start: %#X with length:%d\n",&buffer,bufsize);
//	unsigned i;
//	for(i=0;i<bufsize;i++){
//		printf("%d:%.0f\n",i,buffer[i]);
//	}




//	printf("Feedback:%f, Damp1:%f, Damp2:%f\n",feedback,damp1,damp2);
//	printf("Size:%d\n",bufsize);
//	unsigned i;
//	for(i=0;i<bufsize;i++){
//		printf("%d:%.0f\n",i,buffer[i]);
//	}
//


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

//	printf("Sizeofbuf:%d\n",bufsize*sizeof(*buffer));
//	memset(buffer, (float)3, bufsize*4);

	unsigned i;
	for(i=0;i<bufsize;i++){
		buffer[i]=0;
	}
}

void comb::update(float* param_arr){


	damp1=param_arr[0];
	damp2=1-damp1;
	feedback=param_arr[1];

}


float comb::process(float x){

	float y;

	y = buffer[cptr];
	undenormalise(y);

	filterstore = (y*damp2) + (filterstore*damp1);
	undenormalise(filterstore);

	buffer[cptr] = x + (filterstore*feedback);

	if(++cptr>=bufsize) cptr = 0;
//
	return y;
}
