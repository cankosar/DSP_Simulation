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

	//Set status
	status=1;

}

int dsp::process(int* x){

	//Convert to float
	float y=(float) *x;

	//Main routine: Check the status of the components and feed them
	if(status){

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

	//Convert to int and return
	return (int)y;

}

void dsp::reset(void){


	//This routine reset all the DSP functionalities

	//Reset biquads
	unsigned int i;
	for(i=0;i<n_biquad;i++){
		inst_biquad[i].reset();
	}

	//Reset delay
	inst_delay.reset();

	//Reset chorus
	inst_chorus.reset();

	//Reset overdrive
	inst_overdrive.reset();

	//Reset reverb
	inst_reverb.reset();

}

void dsp::update(void){

	/*Here comes the update hash */

	//Dummy hash
	unsigned banks=0b10000001;

	//General DSP bank
	if(banks&(1<<c_dsp_bank)){		//Bank active
		status=1;
	}else{				//Bank inactive
		if(status){		//If bank was active before
			reset();
		}
		status=0;
	}

	//EQ banks
	unsigned i;
	for(i=0;i<n_EQ;i++){
		//EQ banks
		if(banks&(1<<(i+c_EQ_bank))){		//Bank active
			inst_biquad[i].status=1;
		}else{				//Bank inactive
			if(inst_biquad[i].status){		//If bank was active before
				inst_biquad[i].reset();
			}
			inst_biquad[i].status=0;
		}
	}

	//Delay bank
	if(banks&(1<<(c_delay_bank))){		//Bank active
		inst_delay.status=1;
	}else{								//Bank inactive
		if(inst_delay.status){			//If bank was active before
			inst_delay.reset();
		}
		inst_delay.status=0;
	}

	//Chorus bank
	if(banks&(1<<(c_chorus_bank))){		//Bank active
		inst_chorus.status=1;
	}else{								//Bank inactive
		if(inst_chorus.status){			//If bank was active before
			inst_chorus.reset();
		}
		inst_chorus.status=0;
	}

	//Overdrive bank
	if(banks&(1<<(c_overdrive_bank))){		//Bank active
		inst_overdrive.status=1;
		inst_biquad[c_overdrive_prefilter_id].status=1;
		inst_biquad[c_overdrive_postfilter_id].status=1;
	}else{										//Bank inactive
		if(inst_overdrive.status){				//If bank was active before
			inst_overdrive.reset();
			inst_biquad[c_overdrive_prefilter_id].reset();
			inst_biquad[c_overdrive_postfilter_id].reset();
		}
		inst_overdrive.status=0;
		inst_biquad[c_overdrive_prefilter_id].status=0;
		inst_biquad[c_overdrive_postfilter_id].status=0;
	}

	//Reverb bank
	if(banks&(1<<(c_reverb_bank))){		//Bank active
		inst_reverb.status=1;
	}else{								//Bank inactive
		if(inst_reverb.status){			//If bank was active before
			inst_reverb.reset();
		}
		inst_reverb.status=0;
	}


}
