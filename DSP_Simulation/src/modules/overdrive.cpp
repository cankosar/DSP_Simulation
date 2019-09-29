/*
 * overdrive.cpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */
#include "math.h"
#include "../../inc/modules/overdrive.hpp"




void overdrive::init(void){

	gain=10;
	upscaler=1000;
	downscaler=1/upscaler;


}

void overdrive::reset(void){



}

void overdrive::update(float *param_arr){



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


