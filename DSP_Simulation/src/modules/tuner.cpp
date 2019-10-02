/*
 * overdrive.cpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */
#include "stdio.h"
#include "math.h"
#include "../../inc/modules/tuner.hpp"
#include "../../inc/constants.hpp"




void tuner::init(void){

	//Reset the pointer
	tptr=0;
	maptr=0;


	//Set status
	status=1;

}

void tuner::reset(void){

}

void tuner::update(float *param_arr){

}

void tuner::process(float x){

//	printf("tptr:%d\n",tptr);

	if(tptr<bufsize){
		//Fill until the half buffer is full
		buffer[tptr]=x;
		//Increment pointer
		tptr++;

	}else{
		//If one half full =>Process the buffer
		tptr=0;
		detect_pitch();
	}

}


void tuner::detect_pitch(void){

	//Declare and initialize variables
	unsigned long i=0;
//	float freq;


//	printf("dp\n");

//	printf("Dist:%d, AC:%d\n",p2,sizeof(note_bins)/4);


	//Auto-correlation algorithm for the first iteration
	for(i=0; i<s_bins;i++){
		//Calculate auto-correlation normalized score
//		printf("Bin:%d\n",note_bins[i]);
		arr_ac[i]=calc_ac(note_bins[i]);
//		printf("%d: %d, %f\n",i, note_bins[i],arr_ac[i]);
	}

	//Find the major peaks of the first iteration
	find_peaks();
//	printf("f_M1: %fHz [%d] \t f_M2 :%f[%d]\n",((double)FS/(double)note_bins[p1]),p1,((double)FS/(double)note_bins[p2]),p2);

	//Find the exact distance

	//Find the exact lower frequency

//	printf("Dist:%d, AC:%d\n",p2,s_bins);
	if(note_bins[p1]>note_bins[p2]){
		p=get_exact_peak_linear(p1);
	}else{
		p=get_exact_peak_linear(p2);
	}

//	printf("Peak: %f [Distance: %d]\n",  (double)FS/(double)p,p);

//	printf("Peaks: %d,%d\n", (int32_t)FS/arr_ac[peaks.p1],(int32_t) (FS/arr_ac[peaks.p2]));
//	printf("Peaks: %f,%f\n", (float)FS/p1,(float)FS/p2);

	//freq=estimate_freq(p);
	estimate_freq();
////	printf("Freq: %f\n",ctrl_tx[tuner_freq_reg].f32);
//	printf("Freq: %d\n",(int32_t)ctrl_tx[tuner_freq_reg].f32);

}


float tuner::calc_ac(unsigned dist){

	unsigned i=0;
	float ac_score;

	ac_score=0;
	unsigned l_acbuf;
	unsigned l_max;

	//Length of samples we need
	l_acbuf=n_waves_ac*dist;
	l_max=bufsize-dist;

	if(l_acbuf>l_max){
		l_acbuf=l_max;
	}

	for(i=0;i<l_acbuf;i++){
		ac_score+=buffer[i]*buffer[i+dist];
	}

	//Norming AC Score: Divide by the count of the samples
	ac_score=ac_score/l_acbuf;

	return ac_score;
}

void tuner::find_peaks(void){

	p1=0;
	p2=0;


	unsigned n_peak;	//Peak count
	unsigned i;
	//Finding the peaks
	n_peak=0;											//Number of found peaks
		for(i=1; i<s_bins-1;i++){
//			fprintf(fptr, "%f,%f\n",(float)(FS/note_bins[i]),arr_ac[i]);
	//		printf("%f,%f\n",(float)(FS/note_bins[i]),arr_ac[i]);
			if(arr_ac[i]>0){								//Find only positive peaks
				if(arr_ac[i]>arr_ac[i-1] && arr_ac[i]>arr_ac[i+1]){	//Peak found
//					printf("Peak found:%f \t%f\n",(float)(FS/note_bins[i]),arr_ac[i]);
					n_peak++;								//Number of found peaks
					if(n_peak==1){							//Check if the found peak is the first peak
						p1=i;							//Initialize first peak (distance)
					}else if(n_peak==2){					//Check if the found peak is the second peak
						p2=i;							//Initialize second peak (distance)
					}

					if(arr_ac[p1]<arr_ac[i]){			//If the current peak distance is greater than the last peak distance
						p2=p1;						//Update the peak distances: Shift the next greatest to the second place
						p1=i;							//Set the greatest
					}else if(arr_ac[p2]<arr_ac[i]){		//If the current peak distance is greater than the second peak distance
						p2=i;							//Update the second peak
					}
				}
			}
		}

}

unsigned tuner::get_exact_peak_linear(unsigned index){


	unsigned dist=note_bins[index];


	float ac_prev=calc_ac(dist-1);
	float ac=arr_ac[index];
	float ac_next=calc_ac(dist+1);

	unsigned n=0;		//Loop counter
	unsigned n_exit=100;	//Emergency exit

	//Get gradient
	while(n<n_exit){
		n++;

		if(ac>=ac_prev){

			if(ac<ac_next){
				//Gradient positive
				dist++;
				ac_prev=ac;
				ac=ac_next;
				ac_next=calc_ac(dist+1);

			}else if(ac>=ac_next){
				//Found peak
				break;
			}
		}else if(ac<ac_prev){
			//Gradient negative
			if(ac>=ac_next){
				dist--;
				ac_next=ac;
				ac=ac_prev;
				ac_prev=calc_ac(dist-1);
			}else{
				//Negative peak
				dist=0;
				break;
			}

		}

	}

//	printf("AC-Prev:%.5f \tAC:%.5f \tAC-Next:%.5f \n",ac_prev,ac,ac_next);
//	printf("Found: %f \t Iterations:%d\n", (float)FS/dist,n);



	return dist;
}


/*This function uses methods of stochastics to estimate the frequency*/
void tuner::estimate_freq(void){

	float ma;					//Value of moving average
	float minimum, maximum;		//Minimum and maximum values of one array
	double deviation;			//Current deviation in the array
	float fin;



	fin=(float)FS/(float)p;		//Input frequency

	//Moving average filter

	//Insert value
	buf_maf[maptr]=fin;

	//Update pointer
	maptr++;

	if(maptr>=l_maf){
		maptr=0;
	}

	//Calculate moving average

	ma=0;
	minimum=buf_maf[0];
	maximum=buf_maf[0];

	unsigned i=0;
	for(i=0;i<l_maf;i++){
		//Update moving average
		ma+=buf_maf[i];

		//Find the minimum value of array
		if(buf_maf[i]<minimum){
			minimum=buf_maf[i];
		}

		//Find the minimum value of array
		if(buf_maf[i]>maximum){
			maximum=buf_maf[i];
		}
	}

	//Moving average value
	ma=ma/l_maf;

	//Deviation
	deviation=maximum/minimum;
//	printf("ma:%f \t max: %f \t min: %f \t dev: %f \n",ma, maximum, minimum, deviation);

	//Check if deviation is within the tolerance band
	if(deviation<=devtol){		//Note confidence good=>Everything fine
		last_conf_f=ma;

//		last_conf_t=HAL_GetTick(); //Commented out for Win
//		printf("Set up t:%lu \n",last_conf_t);
		fc=ma;

	}else{												//Note confidence bad => Set a timer
//		if((HAL_GetTick()-last_conf_t)<conf_timeout){ //Commented out for Win
		if(1){
//			printf("Holding t:%lu \t LC:%lu\n",HAL_GetTick(),last_conf_t);
			fc=last_conf_f;

		}else{
			//Timeout
//			printf("Timeout t:%lu \t LC:%lu\n",HAL_GetTick(),last_conf_t);
			last_conf_f=0;
			last_conf_t=0;
			fc=0;
		}

	}

//	printf("Fc=%.2f\n",fc);

}
