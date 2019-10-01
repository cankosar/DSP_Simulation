/*
 * overdrive.hpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#ifndef INC_MODULES_ALLPASS_HPP_
#define INC_MODULES_ALLPASS_HPP_

class allpass{

	public:
		//Methods
		void init(float* bufptr, unsigned size);
		void reset(void);
		float process(float x);
		void update(float* param_arr);

		//Variables
		bool status;

	private:
		//Methods
		void reset_buffer(void);

		//Variables
		float feedback;

		//Buffer
		unsigned long bufsize;
		float *buffer;
		unsigned long aptr;

};



#endif /* INC_MODULES_REVERB_HPP_ */
