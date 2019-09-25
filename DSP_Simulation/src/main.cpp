#include "stdio.h"
#include <iostream>

#include "../inc/main.hpp"
#include "../inc/wave.hpp"




int main(void) {

	wave waveinst;

	printf("Instance created\n");
	waveinst.input_file= "samples/Guitar_Rythm_dry_16bit_mono.wav";
	waveinst.output_file= "samples/Guitar_Rythm_16bit_processed.wav";

//	waveinst.init_container();
	waveinst.read_wav();

	printf("Data read\n");

	long unsigned i=0;
//	long unsigned lendat=waveinst.iodat->len_container;

	for(i=0;i<len_container;i++){
//		printf("%d\n",waveinst.iodat->datin[i]);
		waveinst.iodat->datout[i]=waveinst.iodat->datin[i]/2;
	}
	waveinst.write_wav();

	printf("Data written\n");

	return 0;
}
