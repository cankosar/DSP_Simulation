/*
 * biquad.cpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#include "math.h"
#include "../../inc/constants.hpp"
#include "../../inc/modules/volume.hpp"
#include "stdio.h"


void c_volume::init(void){

	set_volume(initial_volume);

}

void c_volume::set_volume(float v){

	if(v>1){
		gain=fastPow(10,(double)v*0.003)-1;
	}else{
		//Absolute silence
		gain=0;
	}

}

float c_volume::process(float x){

	return x*gain;

}


