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

	//Initialize reverb
	inst_reverb.init();

	//Initialize tuner
	inst_tuner.init();

	//Initialize tremolo
	inst_tremolo.init();

	//Initialize rotary
	inst_rotary.init();

	//Initialize rotary
	inst_compressor.init();

	//Set status
	status=1;

}

int dsp::process(int* x){

	//Convert to float
	float y=(float) *x;

	//Main routine: Check the status of the components and feed them
	if(status){

		//Pass through compressor
		if(inst_compressor.status){
			y=inst_compressor.process_lg(y);
		}

		//Pass through the EQ section
		unsigned short i;
		for(i=0;i<n_EQ;i++){
			if(inst_biquad[i].status){
				y=inst_biquad[i].process(y);
			}
		}

		//Pass through delay
		if(inst_delay.status){
			y=inst_delay.process(y);
		}

		//Pass through chorus
		if(inst_chorus.status){
			y=inst_chorus.process(y);
		}

		//Pass through rotary
		if(inst_rotary.status){
			y=inst_rotary.process(y);
		}

		//Pass through tremolo
		if(inst_tremolo.status){
			y=inst_tremolo.process(y);
		}
		//Pass through the overdrive
		if(inst_overdrive.status){
			y=inst_biquad[3].process(y);	//Pre filter
			y=inst_overdrive.process(y);	//Overdrive
			y=inst_biquad[4].process(y);	//Post filter
		}

		//Pass through reverb
		if(inst_reverb.status){
			y=inst_reverb.process(y);
		}
	}

	if(inst_tuner.status){
		inst_tuner.process(y);
	}

	//Convert to int and return
	return (int)y;

}

void dsp::stop(void){


	//This routine reset all the DSP functionalities

	//Reset status
	status=0;

	//Reset biquads
	unsigned int i;
	for(i=0;i<n_biquad;i++){
		inst_biquad[i].stop();
	}

	//Reset delay
	inst_delay.stop();

	//Reset chorus
	inst_chorus.stop();

	//Reset overdrive
	inst_overdrive.stop();

	//Reset reverb
	inst_reverb.stop();

	//Reset tremolo
	inst_tremolo.reset();

	//Reset rotary
	inst_rotary.reset();

	//Reset status
	status=0;

}

void dsp::start(void){
	status=1;
}


void dsp::update(void){

	/*Here comes the update hash */

	//Dummy hash
	unsigned banks=0b000000000101;

	//General DSP bank
	if(banks&(1<<c_dsp_bank)){
		start();
	}else{
		stop();
	}

	bool dsp_state_store=0;
	//Tuner bank
	if(banks&(1<<c_tuner_bank)){
		//Store DSP state while entering tuner mode
		dsp_state_store=status;

		//Deactivate DSP bank
		status=0;

		//Reset all banks
		stop();

		//Activate tuner bank
		inst_tuner.status=1;

	}else{

		//Deactivate tuner
		inst_tuner.status=0;
		if(inst_tuner.status){
			inst_tuner.reset();
		}

		//Restore old dsp status
		inst_tuner.status=dsp_state_store;
	}




	//EQ banks
	unsigned i;
	for(i=0;i<n_EQ;i++){
		//EQ banks
		if(banks&(1<<(i+c_EQ_bank))){
			inst_biquad[i].start();
		}else{
			inst_biquad[i].stop();
		}
	}

	//Delay bank
	if(banks&(1<<(c_delay_bank))){
		inst_delay.start();
	}else{
		inst_delay.stop();
	}

	//Chorus bank
	if(banks&(1<<(c_chorus_bank))){
		inst_chorus.start();
	}else{
		inst_chorus.stop();
	}

	//Overdrive bank
	if(banks&(1<<(c_overdrive_bank))){
		inst_overdrive.start();
		inst_biquad[c_overdrive_prefilter_id].start();
		inst_biquad[c_overdrive_postfilter_id].start();
	}else{
		inst_overdrive.stop();
		inst_biquad[c_overdrive_prefilter_id].stop();
		inst_biquad[c_overdrive_postfilter_id].stop();
	}

	//Reverb bank
	if(banks&(1<<(c_reverb_bank))){
		inst_reverb.start();
	}else{
		inst_reverb.stop();
	}

//	//Tremolo bank
//	if(banks&(1<<(c_tremolo_bank))){
//		inst_tremolo.start();
//	}else{
//		inst_tremolo.stop();
//	}
//
//	//Rotary bank
//	if(banks&(1<<(c_rotary_bank))){
//		inst_rotary.start();
//	}else{
//		inst_rotary.stop();
//	}
//
//	//Compressor bank
//	if(banks&(1<<(c_compressor_bank))){
//		inst_compressor.start();
//	}else{
//		inst_compressor.stop();
//	}
}
