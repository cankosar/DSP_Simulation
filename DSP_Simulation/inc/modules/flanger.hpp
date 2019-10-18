/*
 * chorus.hpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#ifndef INC_MODULES_FLANGER_HPP_
#define INC_MODULES_FLANGER_HPP_

class c_flanger{

	public:

		//Methods
		void init(void);
		void start(void);
		void stop(void);
		float process(float x);

//		void set_wet(float *w);
		void set_depth(float *d);
		void set_rate(float *r);

		//Variables
		bool status;

	private:

		//Methods
		void reset_buffer(void);
		float get_current_delay(void);
		float lfo(void);

		//Chorus parameter with initializers
		float G_d; 			//Dry gain (Dry/Wet mix)
		float G_w; 			//Wet gain (Dry/Wet mix)
		float depth; 		//Depth
		float rate;			//Rate

		//Config parameters
		float d_base=10;		//Base delay in ms

		//Initial parameters
//		float initial_wet=30; 			//Wet gain (Dry/Wet mix)
		float initial_depth=50; 		//Depth
		float initial_rate=1;


		//Chorus buffer
		static const unsigned flanger_len=1300;
		float* fbuf = new float[flanger_len];
		unsigned fptr;

		//LFO
		float a_step;
		float a_lfo;

};



#endif /* INC_MODULES_CHORUS_HPP_ */
