/*
 * chorus.hpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#ifndef INC_MODULES_ROTARY_HPP_
#define INC_MODULES_ROTARY_HPP_

class rotary{

	public:

		//Methods
		void init(void);
		void reset(void);
		float process(float x);
		void update(float* update_params);

		//Variables
		bool status;

	private:

		//Methods
		void reset_buffer(void);
		float get_current_delay(void);
		float lfo(void);

		//Chorus parameter
		float depth; 		//Depth
		float d_base;		//Base delay in ms
		float rate;			//Rate

		//Chorus buffer
		static const unsigned rotary_len=1200;
		float* rbuf = new float[rotary_len];
		unsigned rptr;

		//LFO
		float a_step;
		float a_lfo;

};



#endif /* INC_MODULES_ROTARY_HPP_ */
