/*
 * ser_deser.cpp
 *
 *  Created on: 27.09.2019
 *      Author: KOS2ST
 */


#include "../inc/ser_deser.hpp"
#include "../inc/dsp.hpp"
#include "stdio.h"

int ser_deser::init(void){

	//Pointer of buffer
	p_offset=0;
	p_offset_o=0;

	//Set the input&output files
	inst_wav.input_file= "samples/Guitar_Rythm_dry_16bit_mono.wav";
	inst_wav.output_file= "samples/Guitar_Rythm_16bit_processed.wav";

	//Read wave file
	inst_wav.read_wav();

//	printf("Num samples %d",inst_wav.num_samples);
	//Set pointers
	p_r=0;
	p_w=1;

	return 0;
}
int ser_deser::get_next_buffer(void){

	bool status=0;
	unsigned long i=0;
	flip_ser_ptr();
	for(i=0;i<buffer_size;i++){

		dsp_buf[p_r][i]=inst_wav.iodat->datin[p_offset+i];


	}

	p_offset+=buffer_size;


	if(p_offset>inst_wav.num_samples){
		status=0;
	}else{
		status=1;
	}

	return status;
}

/*
 *Flip write read indicators
 */
void ser_deser::flip_ser_ptr(void){

	p_w=!p_w;
	p_r=!p_r;

}

int ser_deser::process(void){

	//Instance DSP
	dsp inst_dsp;

	//Initialize DSP
	inst_dsp.init();

	//Update parameter once
	inst_dsp.update();

	//Serialize
	unsigned int i=0;

	while(get_next_buffer()){

//		for(i=0;i<1;i++){
		for(i=0;i<buffer_size;i++){

			dsp_buf[p_w][i]=inst_dsp.process(&dsp_buf[p_r][i]);
			inst_wav.iodat->datout[p_offset_o+i]=dsp_buf[p_w][i];
		}
		p_offset_o+=buffer_size;

//		if(p_offset_o>1000){
//			break;
//		}
	}

	return 0;
}

void ser_deser::finish(void){

	inst_wav.write_wav();

}
