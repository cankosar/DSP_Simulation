/*
 * biquad.hpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#ifndef INC_MODULES_BIQUAD_HPP_
#define INC_MODULES_BIQUAD_HPP_

class biquad{

	public:
		//Methods
		void init(void);
		void reset(void);
		void update(float* param_arr);
		float process(float);
		void apply_filter(unsigned short type, float g, float f0, float Q);

		//Variables
		bool status;

	private:
		//Variables
		float y,y1,y2,x1,x2;
		float param[5];

};


#endif /* INC_MODULES_BIQUAD_HPP_ */
