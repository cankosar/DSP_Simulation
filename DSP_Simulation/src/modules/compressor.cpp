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
	ptr=0;

	//Init parameter
	comp_gain=0;
	target_gain=0;

	input_gain=2;
	output_gain=3;
	threshold=9;
	ratio=2;
	slope=1-1/ratio;
	t_attack=10;	//In ms
	t_release=200;	//In ms
	t_rms=25;		//In ms
	limit_gain=1/ratio;


	natlogof2=log(2);
	diffsum=0;

	t_main=0;

	i_attack=(unsigned long) (t_attack*(float)FSms);
	i_release=(unsigned long) (t_release*(float)FSms);
	delay_len=(unsigned long) (t_main*(float)FSms);

	rms_len=(unsigned long) (t_rms*(float)FSms);

	stepsize_attack=1/(float)i_attack;
	stepsize_release=1/(float)i_release;

//	printf("i_attack:%d, i_release:%d, ss_attack:%f, ss_release:%f main delay len:%d\n",i_attack,i_release,stepsize_attack,stepsize_release,delay_len);
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
	memset(buf, 0, buf_max*sizeof(*buf));
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

	c_rms=log2(c_rms);

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

	//Update main buf

	//Output is the last value on the buffer
	float y;
	y=buf[ptr];

	//Set the new value to the buffer
	buf[ptr]=x;

	//Increment
	ptr++;

	if(ptr>=delay_len){
		ptr=0;;
	}


	//Apply gain

	//Set output
//	y=x;

	//Hard knee
	if(c_rms>threshold){

		//Attack
		if(comp_gain>limit_gain){
		comp_gain-=stepsize_attack;
//		printf("At:%.3f\n",comp_gain);
		}else{
			comp_gain=limit_gain;
		}


	}else{

		//Release
		if(comp_gain<1){
		comp_gain+=stepsize_release;
//		printf("Rl:%.3f\n",comp_gain);
		}else{
			comp_gain=1;
		}

	}

		y=y*comp_gain*output_gain;

//	if(comp_gain!=1){
//		printf("x:%f, y:%f, \tG=%f \t RMS: %f\n",x,y,comp_gain,c_rms);
//	}

	return y;
//	return 0;
}


float compressor::process_lg(float x){



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

	//Get logarithmic value
	c_rms=fast_log2(c_rms);

	//Update the buffer
	rmsbuf[rptr]=x;

	//Increment
	rptr++;

	if(rptr>=rms_len){
		rptr=0;;
	}

	//Update main buf

	//Output is the last value on the buffer
	float y;
	y=buf[ptr];

	//Set the new value to the buffer
	buf[ptr]=x;

	//Increment
	ptr++;

	if(ptr>=delay_len){
		ptr=0;;
	}

	//Apply gain

	//Get the difference
//	float diff;
//
//	float deviation;
//	float tg2;

	//Calculating attenuation
	float exponent;

	if(c_rms>threshold){

		//Calculating exponent according Udo Zölzer
		exponent=-1*(c_rms-threshold)*slope;
//		target_gain=pow(2,exponent);

		//Exponents smaller than -1500 are making fast algorithms unstable
		if(exponent<-100){
			target_gain=0;
		}else{
			target_gain=fastPow(2,exponent);
//			target_gain=exp_fast(natlogof2*attenuation);
//			target_gain=pow(2,exponent);

		}
	}else{
		target_gain=1;
	}



	//Attack and release


	if(comp_gain>target_gain){

		//Attack
		comp_gain-=stepsize_attack;
//		printf("attack:%.3f\n",comp_gain);

		//Break decreasing
		if(comp_gain<=target_gain){
			comp_gain=target_gain;
		}
//		printf("Attack: Target:%.3f\t Current:%.3f\n",target_gain, comp_gain);

	}else{

		//Release
		comp_gain+=stepsize_release;

		//Break increasing
		if(comp_gain>=1){
			comp_gain=1;
		}

//		printf("Release: Target:%.3f\t Current:%.3f\n",target_gain, comp_gain);
	}





	y=y*comp_gain*output_gain;

	if(comp_gain>0.1){
//		printf("Release: Target:%.3f\t Current:%.3f\n",target_gain, comp_gain);
//		printf("x:%f, y:%f, \tG=%f \t RMS: %f\n",x,y,comp_gain,c_rms);
	}

	return y;
//	return 0;
}




