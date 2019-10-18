#include "stdio.h"
#include <iostream>

#include "../inc/main.hpp"
#include "../inc/ser_deser.hpp"

int main(void) {

	//Create the instances
	ser_deser inst_ser;

	//Initialize
	printf("Initializing\n");

  inst_ser.init();

	//Set the input&output files
	inst_ser.inst_wav.input_file= "samples/Guitar_Rythm_dry_16bit_mono.wav";
	inst_ser.inst_wav.output_file= "samples/Guitar_Rythm_16bit_processed.wav";

	//Read wave file
	inst_ser.inst_wav.read_wav();

	//Process
	printf("Processing\n");
	inst_ser.process();

	//Finish and write the output file
	printf("Processed successfully\n");
	inst_ser.finish();

	return 0;
}
