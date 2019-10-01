/*
 * delay.hpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#ifndef INC_MODULES_DELAY_HPP_
#define INC_MODULES_DELAY_HPP_


class delay{

	public:
		//Methods
		void init(void);
		void reset(void);
		void update(float* param_arr);
		float process(float x);
		void reset_buffer(void);

		//Variables
		bool status;

	private:
		//Variables
		float G_fb; 		//Feedback gain
		float G_d; 			//Dry gain (Dry/Wet mix)
		float G_w; 			//Wet gain (Dry/Wet mix)
		float delay_time; 	//Delay time in seconds
		static const unsigned delay_len=96000;
		float* dbuf = new float[delay_len];
		unsigned long dptr;
		unsigned long n_distance;
};



#endif /* INC_MODULES_DELAY_HPP_ */
