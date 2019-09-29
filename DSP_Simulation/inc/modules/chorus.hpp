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
		void reset(void);
		float process(float x);
		void update(float* update_params);

		//Variables
		bool status;

	private:
		//Methods
		float get_current_delay(void);
		float lfo(void);

		//Chorus parameter
		float G_d; 			//Dry gain (Dry/Wet mix)
		float G_w; 			//Wet gain (Dry/Wet mix)
		float depth; 		//Depth
		float d_base;		//Base delay in ms
		float rate;			//Rate

		//Chorus buffer
		static const unsigned chorus_len=4800;
		float* cbuf = new float[chorus_len];
		unsigned cptr;

		//LFO
		float a_step;
		float a_lfo;

};



#endif /* INC_MODULES_CHORUS_HPP_ */
