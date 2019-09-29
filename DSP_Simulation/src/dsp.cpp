/*
 * dsp.cpp
 *
 *  Created on: 27.09.2019
 *      Author: KOS2ST
 */

#include "stdio.h"
#include <array>
#include "../inc/dsp.hpp"

void dsp::init(void){

	//Initialize Biquad filters
	unsigned short int i;
	for(i=0;i<n_biquad;i++){
		//Initialize
		inst_biquad[i].init();
		//Apply neutral filters
		inst_biquad[i].apply_filter(0,0,1,1);	//Neutral filter

	}

	//Dummy EQ filter
	inst_biquad[0].apply_filter(2,0,1000,1);
	inst_biquad[1].apply_filter(3,0,200,1);
	inst_biquad[2].apply_filter(4,0,5000,1);

	//Overdrive filter
	inst_biquad[3].apply_filter(1,0,300,1);
	inst_biquad[4].apply_filter(0,0,4000,1);

	//Initialize delay
	inst_delay.init();

	//Initialize chorus
	inst_chorus.init();

	//Initialize overdrive
	inst_overdrive.init();

}

int dsp::process(int* x){

	//Convert to float
	float y=(float) *x;

	//Pass through the EQ section
	unsigned short i;
	for(i=0;i<n_EQ;i++){
		y=inst_biquad[i].process(y);
	}

	//Pass through delay
	y=inst_delay.process(y);

	//Pass through chorus
	y=inst_chorus.process(y);

	//Pass through the overdrive
	y=inst_biquad[3].process(y);	//Pre filter
	y=inst_overdrive.process(y);	//Overdrive
	y=inst_biquad[4].process(y);	//Post filter

	//Convert to int and return
	return (int)y;

}

void dsp::reset(void){


	//Reset every bank



}

void dsp::update(void){

	/*Here comes the update hash */

	unsigned banks[]={1,0,0,0,1,1,0};
	//Check activations


	//General DSP bank
	if(banks[0]){		//Bank active
		status=1;

	}else{				//Bank inactive
		if(status){		//If bank was active before
			reset();
		}

	}

	//EQ banks



}
