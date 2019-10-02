/*
 * chorus.hpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#ifndef INC_MODULES_TREMOLO_HPP_
#define INC_MODULES_TREMOLO_HPP_

class tremolo{

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
		float get_current_attenuation(void);
		float lfo(void);

		//Rotary parameter
		float depth; 		//Depth
		float frequency;			//Rate


		//LFO
		float a_step;
		float t_step;
		float i_lfo;

		//Type of wave generator
		unsigned type;		//0:triangle 1:square 2: sinus
};



#endif /* INC_MODULES_CHORUS_HPP_ */
