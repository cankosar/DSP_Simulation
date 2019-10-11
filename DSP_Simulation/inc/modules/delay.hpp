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
		void set_wet(float* wet);
		void set_dry(float* dry);
		void set_time(float* time);
		void set_feedback(float* fb);
		void start(void);
		void stop(void);
		float process(float x);

		//Variables
		bool status=0;

	private:
		//Methods
		void reset_buffer(void);

		//Parameters with default values
		float G_fb=0.3; 		//Feedback gain
		float G_d=1; 			//Dry gain (Dry/Wet mix)
		float G_w=0.2; 			//Wet gain (Dry/Wet mix)
		float delay_time=0.5; 	//Delay time in seconds

		//Buffers
		static const unsigned delay_len=100000;
		float* dbuf = new float[delay_len];
		unsigned long dptr;
		unsigned long n_distance;
};



#endif /* INC_MODULES_DELAY_HPP_ */
