/*
 * dsp.hpp
 *
 *  Created on: 27.09.2019
 *      Author: KOS2ST
 */

#ifndef INC_DSP_HPP_
#define INC_DSP_HPP_

#include "../inc/modules/biquad.hpp"
#include "../inc/modules/delay.hpp"
#include "../inc/modules/chorus.hpp"
#include "../inc/modules/overdrive.hpp"
#include "../inc/modules/reverb.hpp"
#include "../inc/modules/tuner.hpp"
#include "../inc/modules/tremolo.hpp"

class dsp{
	public:
		//Methods
		void init(void);
		void reset(void);
		int process(int* x);
		void update(void);

		//Variables
		bool status;

		//The bank positions
		static const unsigned short c_dsp_bank=0;
		static const unsigned short c_tuner_bank=1;
		static const unsigned short c_EQ_bank=2;
		static const unsigned short c_delay_bank=5;
		static const unsigned short c_chorus_bank=6;
		static const unsigned short c_overdrive_bank=7;
		static const unsigned short c_reverb_bank=8;
		static const unsigned short c_tremolo_bank=9;

		static const unsigned short c_overdrive_prefilter_id=3;
		static const unsigned short c_overdrive_postfilter_id=4;

	private:
		const static unsigned short int n_biquad=5;
		const static unsigned short int n_EQ=3;
		biquad inst_biquad[n_biquad];
		delay inst_delay;
		chorus inst_chorus;
		overdrive inst_overdrive;
		reverb inst_reverb;
		tuner inst_tuner;
		tremolo inst_tremolo;
};


#endif /* INC_DSP_HPP_ */
