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

	//Process
	printf("Processing\n");
	inst_ser.process();

	//Finish and write the output file
	printf("Processed successfully\n");
	inst_ser.finish();

	return 0;
}
