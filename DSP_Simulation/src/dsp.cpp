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
	for(i=0;i<n_EQ;i++){
		//Initialize
		inst_biquad[i].init();
	}

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
			y=inst_compressor.process(y);
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
			y=inst_overdrive.process(y);	//Overdrive
		}

		//Pass through reverb
		if(inst_reverb.status){
			y=inst_reverb.process(y);
		}
	}else if(inst_tuner.status){
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
	for(i=0;i<n_EQ;i++){
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
	inst_tremolo.stop();

	//Reset rotary
	inst_rotary.stop();
}

void dsp::start(void){
	status=1;
}


void dsp::update(void){

	/*Here comes the update hash */
	//Dummy hash
	unsigned banks=0b000100000001;


	//General DSP bank
	if(banks&(1<<c_dsp_bank)){
		start();
	}else{
		stop();
	}

	//Tuner bank
	if(banks&(1<<c_tuner_bank)){
		//Stop DSP
		stop();
		inst_tuner.start();

	}else{
		inst_tuner.stop();
		//Start DSP
		start();
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
	}else{
		inst_overdrive.stop();
	}

	//Reverb bank
	if(banks&(1<<(c_reverb_bank))){
		inst_reverb.start();
	}else{
		inst_reverb.stop();
	}

	//Tremolo bank
	if(banks&(1<<(c_tremolo_bank))){
		inst_tremolo.start();
	}else{
		inst_tremolo.stop();
	}

	//Rotary bank
	if(banks&(1<<(c_rotary_bank))){
		inst_rotary.start();
	}else{
		inst_rotary.stop();
	}

	//Compressor bank
	if(banks&(1<<(c_compressor_bank))){
		inst_compressor.start();
	}else{
		inst_compressor.stop();
	}
}
