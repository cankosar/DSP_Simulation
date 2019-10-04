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
#include "../../inc/modules/compressor.hpp"


void compressor::init(void){

	//Parameter

	//Init pointer
	rptr=0;

	//Init parameter
	input_gain=2;
	output_gain=1;
	threshold=1500;
	ratio=4;
	t_attack=10;	//In ms
	t_release=200;	//In ms
	t_rms=25;		//In ms
	limit_gain=1/ratio;



	i_attack=(unsigned long) (t_attack*(float)FSms);
	i_release=(unsigned long) (t_release*(float)FSms);

	rms_len=(unsigned long) (t_rms*(float)FSms);

	stepsize_attack=(1-limit_gain)/i_attack;
	stepsize_release=(1-limit_gain)/i_attack;

//	printf("i_attack:%d, i_release:%d, ss_attack:%f, ss_release:%f\n",i_attack,i_release,stepsize_attack,stepsize_release);
	//RMS Update rate
	update_rate=1000;
	i_update=0;

	//Resetting buffer
	reset_buffer();

	//Status set
	status=1;

}

void compressor::reset(void){

	//Fill the delay buffer with zeros
	reset_buffer();

}

void compressor::reset_buffer(void){
	//Fill the delay buffer with zeros
	//The size of the float is 4

	memset(rmsbuf, 0, rms_max*sizeof(*rmsbuf));
}

void compressor::update(float* param_arr){



}


float compressor::process(float x){



	x*=input_gain;
	//Calculate RMS

	//Subtract oldest the value (rmsbuf[rptr]) from the sum
	rms_sum-=(rmsbuf[rptr]*rmsbuf[rptr])/rms_len;

	//Add the newest value to the sum
	rms_sum+=(x*x)/rms_len;

	if(rms_sum<0){
		printf("Warning: RMS sum negaive %f\n",rms_sum);
		rms_sum=0;
	}

	//Update the RMS Value
	c_rms=fast_sqroot(rms_sum);

//	printf("x:%f, Sum:%f\t SQRT:%f\n",x,rms_sum,c_rms);

//	if(i_update>=update_rate){
//		printf("Sum:%f\t SQRT:%f\n",rms_sum,c_rms);
//		i_update=0;
//
//	}
//		i_update++;

	//Update the buffer
	rmsbuf[rptr]=x;

	//Increment
	rptr++;

	if(rptr>=rms_len){
		rptr=0;;
	}



	//Apply gain
	float y;
	//Set output
	y=x;

	//Hard knee
	if(c_rms>threshold){

		//Attack
		if(comp_gain>limit_gain){
		comp_gain-=stepsize_attack;
		}else{
			comp_gain=limit_gain;
		}

	}else{

		//Release
		if(comp_gain<1){
		comp_gain+=stepsize_release;
		}else{
			comp_gain=1;
		}
	}


//	comp_gain=0.5;

//	if(x>=0){
//		y=threshold+(x-threshold)*comp_gain;
//	}else{
//		y=-1*threshold+(x+threshold)*comp_gain;
//	}

	y=x*comp_gain*output_gain;

//	if(comp_gain!=1){
//		printf("x:%f, y:%f, \tG=%f \t RMS: %f\n",x,y,comp_gain,c_rms);
//	}

	return y;
//	return 0;
}

float compressor::fast_sqroot(float number){

	    const float threehalfs = 1.5F;

	    float x2 = number * 0.5F;
	    float y = number;

	    // evil floating point bit level hacking
	    long i = * ( long * ) &y;

	    // value is pre-assumed
	    i = 0x5f3759df - ( i >> 1 );
	    y = * ( float * ) &i;

	    // 1st iteration
	    y = y * ( threehalfs - ( x2 * y * y ) );

	    // 2nd iteration, this can be removed
	    // y = y * ( threehalfs - ( x2 * y * y ) );


	return y*number;
//	return 0;
}

