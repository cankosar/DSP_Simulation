/*
 * overdrive.hpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#ifndef INC_MODULES_OVERDRIVE_HPP_
#define INC_MODULES_OVERDRIVE_HPP_

class overdrive{

	public:
		//Methods
		void init(void);
		void reset(void);
		float process(float x);
		void update(float* param_arr);

		//Variables
		bool status;

	private:
		//Variables
		float downscaler;
		float upscaler;
		float gain;

};



#endif /* INC_MODULES_OVERDRIVE_HPP_ */
