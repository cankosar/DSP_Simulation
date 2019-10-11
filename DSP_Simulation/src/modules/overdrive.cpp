/*
 * overdrive.cpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */
#include "stdio.h"
#include "math.h"
#include "../../inc/modules/overdrive.hpp"




void overdrive::init(void){

	//Init help parameters
	downscaler=1/upscaler;

}

void overdrive::start(void){

	//Set status
	status=1;
}

void overdrive::stop(void){

	//Set status
	status=0;
}

float overdrive::process(float x){

	float y;
	x=x*downscaler*gain;

	//Algorithm 1: y=sign(x)*(1-e(sign(x)*x))
	if(x>0){
		y=1-exp(-1*x);
	}else{
		y=-1+exp(x);
	}

	y=y*upscaler;

	return y;
}


