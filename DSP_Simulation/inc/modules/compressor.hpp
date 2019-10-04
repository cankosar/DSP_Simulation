/*
 * chorus.hpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#ifndef INC_MODULES_COMPRESSOR_HPP_
#define INC_MODULES_COMPRESSOR_HPP_

class compressor{

	public:

		//Methods
		void init(void);
		void reset(void);
		float process(float x);
		void update(float* update_params);
		float fast_sqroot(float x);

		//Variables
		bool status;

		//Parameter
		float input_gain;
		float output_gain;
		float ratio;
		float threshold;
		float t_attack;
		float t_release;
		float t_rms;

	private:

		//Methods
		void reset_buffer(void);

		//Parameter
		float comp_gain;
		float limit_gain;
		unsigned long i_attack,i_release;
		float stepsize_attack,stepsize_release;

		//RMS value
		float rms_sum;
		float c_rms;
		unsigned rms_len;

		//Monitor RMS
		unsigned update_rate;
		unsigned i_update;


		//Chorus buffer
		static const unsigned rms_max=1200;
		float* rmsbuf = new float[rms_max];
		unsigned rptr;


};



#endif /* INC_MODULES_COMPRESSOR_HPP_ */
