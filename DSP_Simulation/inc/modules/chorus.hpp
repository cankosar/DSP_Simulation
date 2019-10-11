/*
 * chorus.hpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#ifndef INC_MODULES_CHORUS_HPP_
#define INC_MODULES_CHORUS_HPP_

class chorus{

	public:

		//Methods
		void init(void);
		void start(void);
		void stop(void);
		float process(float x);

		void set_wet(float *w);
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
		float G_d=0.9; 			//Dry gain (Dry/Wet mix)
		float G_w=0.3; 			//Wet gain (Dry/Wet mix)
		float depth=2; 		//Depth
		float d_base=25;		//Base delay in ms
		float rate=1;			//Rate

		//Chorus buffer
		static const unsigned chorus_len=1200;
		float* cbuf = new float[chorus_len];
		unsigned cptr;

		//LFO
		float a_step;
		float a_lfo;

};



#endif /* INC_MODULES_CHORUS_HPP_ */
