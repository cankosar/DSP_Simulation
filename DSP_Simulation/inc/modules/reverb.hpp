/*
 * overdrive.hpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#ifndef INC_MODULES_REVERB_HPP_
#define INC_MODULES_REVERB_HPP_

#include "comb.hpp"
#include "allpass.hpp"
#include "reverb_parameters.hpp"

class reverb{

	public:
		//Methods
		void init(void);
		void reset(void);
		float process(float x);
		void update(float* param_arr);

		//Variables
		bool status;

	private:
		//Methods
		void reset_buffer(void);

		//Buffer arrays

		//Instances
		allpass inst_allpass[n_allpass];



};



#endif /* INC_MODULES_REVERB_HPP_ */
