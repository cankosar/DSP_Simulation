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
	lowshelf.init();
	lowshelf.set_filter_type(3);
	lowshelf.set_freq(100);
	lowshelf.set_gain(0);
	lowshelf.set_quality(1);

	highshelf.init();
	highshelf.set_filter_type(4);
	highshelf.set_freq(5000);
	highshelf.set_gain(0);
	highshelf.set_quality(1);

	//Initialize delay
	delay.init();

	//Initialize chorus
	chorus.init();

	//Initialize overdrive
	overdrive.init();

	//Initialize reverb
	reverb.init();

	//Initialize tuner
	tuner.init();

	//Initialize tremolo
	tremolo.init();

	//Initialize rotary
	rotary.init();

	//Initialize rotary
	compressor.init();

	//Initialize flanger
	flanger.init();

	//Initialize autowah
	autowah.init();

	//Initialize volume
	volume.init();

	//Set status
	status=1;

}

int dsp::process(int* x){

	//Convert to float
	float y=(float) *x;

	//Main routine: Check the status of the components and feed them
	if(status){

		//Pass through the EQ
		if(lowshelf.status){
			y=lowshelf.process(y);
		}

		if(highshelf.status){
			y=highshelf.process(y);
		}

		//Pass through compressor
		if(compressor.status){
			y=compressor.process(y);
		}


		//Pass through delay
		if(delay.status){
			y=delay.process(y);
		}

		//Pass through chorus
		if(chorus.status){
			y=chorus.process(y);
		}

		//Pass through rotary
		if(rotary.status){
			y=rotary.process(y);
		}

		//Pass through tremolo
		if(tremolo.status){
			y=tremolo.process(y);
		}

		//Pass through flanger
		if(flanger.status){
			y=flanger.process(y);
		}

		//Pass through flanger
		if(autowah.status){
			y=autowah.process(y);
		}

		//Pass through the overdrive
		if(overdrive.status){
			y=overdrive.process(y);	//Overdrive
		}

		//Pass through reverb
		if(reverb.status){
			y=reverb.process(y);
		}

		//Pass through volume
		y=volume.process(y);

	}else if(tuner.status){
		tuner.process(y);
	}

	//Convert to int and return
	return (int)y;

}

void dsp::stop(void){


	//This routine reset all the DSP functionalities

	//Reset status
	status=0;

	//Reset biquads
	lowshelf.stop();
	highshelf.stop();


	//Reset delay
	delay.stop();

	//Reset chorus
	chorus.stop();

	//Reset overdrive
	overdrive.stop();

	//Reset reverb
	reverb.stop();

	//Reset tremolo
	tremolo.stop();

	//Reset rotary
	rotary.stop();

	//Reset flanger
	flanger.stop();

	//Autowah flanger
	autowah.stop();
}

void dsp::start(void){
	status=1;
}


void dsp::update(void){

	/*Here comes the update hash */
	//Dummy hash
	unsigned banks=0b100000000000001;


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
		tuner.start();

	}else{
		tuner.stop();
		//Start DSP
		start();
	}

	//EQ banks
	if(banks&(1<<(c_lowshelf_bank))){
		lowshelf.start();
	}else{
		lowshelf.stop();
	}

	if(banks&(1<<(c_highshelf_bank))){
		highshelf.start();
	}else{
		highshelf.stop();
	}

	//Delay bank
	if(banks&(1<<(c_delay_bank))){
		delay.start();
	}else{
		delay.stop();
	}

	//Chorus bank
	if(banks&(1<<(c_chorus_bank))){
		chorus.start();
	}else{
		chorus.stop();
	}

	//Overdrive bank
	if(banks&(1<<(c_overdrive_bank))){
		overdrive.start();
	}else{
		overdrive.stop();
	}

	//Reverb bank
	if(banks&(1<<(c_reverb_bank))){
		reverb.start();
	}else{
		reverb.stop();
	}

	//Tremolo bank
	if(banks&(1<<(c_tremolo_bank))){
		tremolo.start();
	}else{
		tremolo.stop();
	}

	//Rotary bank
	if(banks&(1<<(c_rotary_bank))){
		rotary.start();
	}else{
		rotary.stop();
	}

	//Flanger bank
	if(banks&(1<<(c_autowah_bank))){
		autowah.start();
	}else{
		autowah.stop();
	}

	//Autowah bank
	if(banks&(1<<(c_flanger_bank))){
		flanger.start();
	}else{
		flanger.stop();
	}

	//Compressor bank
	if(banks&(1<<(c_compressor_bank))){
		compressor.start();
	}else{
		compressor.stop();
	}
}
