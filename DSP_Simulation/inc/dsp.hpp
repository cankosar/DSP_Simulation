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
#include "../inc/modules/rotary.hpp"
#include "../inc/modules/flanger.hpp"
#include "../inc/modules/autowah.hpp"
#include "../inc/modules/compressor.hpp"


class dsp{
	public:
		//Methods
		void init(void);
		int process(int* x);
		void start(void);
		void stop(void);
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
		static const unsigned short c_rotary_bank=10;
		static const unsigned short c_compressor_bank=11;
		static const unsigned short c_flanger_bank=12;
		static const unsigned short c_autowah_bank=13;


	private:
		const static unsigned short int n_EQ=3;
		c_biquad biquad[n_EQ];
		c_delay delay;
		c_chorus chorus;
		c_overdrive overdrive;
		c_reverb reverb;
		c_tuner tuner;
		c_tremolo tremolo;
		c_rotary rotary;
		c_compressor compressor;
		c_flanger flanger;
		c_autowah autowah;
};


#endif /* INC_DSP_HPP_ */
