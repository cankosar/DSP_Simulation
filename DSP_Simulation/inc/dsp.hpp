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

class dsp{
	public:
		//Methods
		void init(void);
		void reset(void);
		int process(int* x);
		void update(void);

		//Variables
		bool status;

	private:
		const static unsigned short int n_biquad=5;
		const static unsigned short int n_EQ=3;
		biquad inst_biquad[n_biquad];
		delay inst_delay;
		chorus inst_chorus;
		overdrive inst_overdrive;
};


#endif /* INC_DSP_HPP_ */
