/*
 * ser_deser.hpp
 *
 *  Created on: 27.09.2019
 *      Author: KOS2ST
 */

#ifndef INC_SER_DESER_HPP_
#define INC_SER_DESER_HPP_


#include "../inc/wave.hpp"

class ser_deser{

	public:
		//Methods

		int init(void);
		int process(void);
		void finish(void);

		//Variable members
		static const int buffer_size=240;
		int dsp_buf[2][buffer_size];
		bool p_w, p_r;
		unsigned long p_offset;
		unsigned long p_offset_o;
		wave inst_wav;
	private:

		//Methods
		int get_next_buffer(void);
		void flip_ser_ptr(void);



};













#endif /* INC_SER_DESER_HPP_ */
