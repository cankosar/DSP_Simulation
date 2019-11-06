/*
 * volume.hpp
 *
 *  Created on: 06.11.2019
 *      Author: KOS2ST
 */

#ifndef INC_MODULES_VOLUME_HPP_
#define INC_MODULES_VOLUME_HPP_





#endif /* INC_MODULES_VOLUME_HPP_ */


class c_volume{

	public:
		void init(void);
		void set_volume(float v);
		float process(float v);
	private:
		float gain;
		float initial_volume=50;

		inline double fastPow(double a, double b) {
			union {
				double d;
				int x[2];
			} u = { a };
			u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
			u.x[0] = 0;
			return u.d;
		};
};
