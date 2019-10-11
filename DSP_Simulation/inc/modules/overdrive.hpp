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
		void start(void);
		void stop(void);
		float process(float x);

		//Variables
		bool status;

	private:
		//Variables
		float downscaler;
		float upscaler=1000;
		float gain=10;

};



#endif /* INC_MODULES_OVERDRIVE_HPP_ */
