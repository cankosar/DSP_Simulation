#include "stdio.h"
#include <iostream>

#include "../inc/main.hpp"
#include "../inc/ser_deser.hpp"




int main(void) {

	//Create the instances

	printf("Creating instances\n");
	ser_deser inst_ser;

	printf("Initializing\n");
	inst_ser.init();
	printf("Processing\n");
	inst_ser.process();
	printf("Processed successfully\n");
	inst_ser.finish();

	return 0;
}
