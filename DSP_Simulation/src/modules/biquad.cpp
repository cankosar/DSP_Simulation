/*
 * biquad.cpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#include "math.h"
#include "../../inc/constants.hpp"
#include "../../inc/modules/biquad.hpp"


void biquad::init(void){

	x1=0;
	x2=0;
	y1=0;
	y2=0;
	y=0;
}

void biquad::reset(void){


}

void biquad::apply_filter(unsigned short type, float g, float f0, float Q){


	double A,w0,cosw0,sinw0,alpha,a0;
	//Intermediate vars
	A=pow(10,g/40);
	w0=2*PI*(f0/FS);
	cosw0=cos(w0);
	sinw0=sin(w0);
	alpha=sinw0/(2*Q);

//	printf("\nA:\t%f\nw0:\t%f\ncosw0:\t%f\nsinw0:\t%f\nalpha:\t%f\n\n",A,w0,cosw0,sinw0,alpha);
//	printf("Type: %d\n",bqf[fid].type);
	switch(type){

		case 0: //Lowpass filter
//			printf("Low pass\n");
			a0=1+alpha;
			param[0]=(float)((1-cosw0)*0.5/a0);
			param[1]=(float)((1-cosw0)/a0);
			param[2]=(float)((1-cosw0)*0.5/a0);
			param[3]=(float)((-2*cosw0)/a0);
			param[4]=(float)((1-alpha)/a0);
			break;

		case 1: //Highpass filter
//			printf("Highpass\n");
			a0=1+alpha;
			param[0]=(float)((1+cosw0)*0.5/a0);
			param[1]=(float)(-(1+cosw0)/a0);
			param[2]=(float)((1+cosw0)*0.5/a0);
			param[3]=(float)(-2*cosw0/a0);
			param[4]=(float)((1-alpha)/a0);
			break;
		case 2: //Peak filter
//			printf("Peak filter\n");
			a0=1+alpha/A;
			param[0]=(float)((1+alpha*A)/a0);
			param[1]=(float)((-2*cosw0)/a0);
			param[2]=(float)((1-alpha*A)/a0);
			param[3]=(float)((-2*cosw0)/a0);
			param[4]=(float)((1-alpha/A)/a0);
			break;
		case 3: //Low shelf filter
//			printf("Low shelf filter\n");
			a0=(A+1)+(A-1)*cosw0+2*sqrt(A)*alpha;
			param[0]=(float)((A*((A+1)-(A-1)*cosw0+2*sqrt(A)*alpha))/a0);
			param[1]=(float)((2*A*((A-1)-(A+1)*cosw0))/a0);
			param[2]=(float)((A*((A+1)-(A-1)*cosw0-2*sqrt(A)*alpha))/a0);
			param[3]=(float)((-2*((A-1)+(A+1)*cosw0))/a0);
			param[4]=(float)(((A+1)+(A-1)*cosw0-2*sqrt(A)*alpha)/a0);
			break;
		case 4:
//			printf("High shelf filter\n");
			a0=(A+1)-(A-1)*cosw0+2*sqrt(A)*alpha;
			param[0]=(float)((A*((A+1)+(A-1)*cosw0+2*sqrt(A)*alpha))/a0);
			param[1]=(float)((-2*A*((A-1)+(A+1)*cosw0))/a0);
			param[2]=(float)((A*((A+1)+(A-1)*cosw0-2*sqrt(A)*alpha))/a0);
			param[3]=(float)((2*((A-1)-(A+1)*cosw0))/a0);
			param[4]=(float)(((A+1)-(A-1)*cosw0-2*sqrt(A)*alpha)/a0);
			break;
	}






}


void biquad::update(float* param_arr){

	unsigned int i;

	for(i=0;i<5;i++){
		param[i]=param_arr[i];
	}

}

float biquad::process(float x){

	//Process biquad filter
	y=
		  x*param[0]
		+x1*param[1]
		+x2*param[2]
		-y1*param[3]
		-y2*param[4];

	//Update the history array
	x2=x1;
	y2=y1;
	x1=x;
	y1=y;

	return y;

}


