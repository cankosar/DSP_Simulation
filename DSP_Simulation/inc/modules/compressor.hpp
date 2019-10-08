/*
 * chorus.hpp
 *
 *  Created on: 29.09.2019
 *      Author: Can
 */

#ifndef INC_MODULES_COMPRESSOR_HPP_
#define INC_MODULES_COMPRESSOR_HPP_

class compressor{

	public:

		//Methods
		void init(void);
		void reset(void);
		float process(float x);
		float process_lg(float x);
		void update(float* update_params);
		double natlogof2;
		inline float fast_log2 (float val)
		{
		   int * const    exp_ptr = reinterpret_cast <int *> (&val);
		   int            x = *exp_ptr;
		   const int      log_2 = ((x >> 23) & 255) - 128;
		   x &= ~(255 << 23);
		   x += 127 << 23;
		   *exp_ptr = x;

		   val = ((-1.0f/3) * val + 2) * val - 2.0f/3;   // (1)

		   return (val + log_2);
		};

		inline float fast_sqroot(float number){

			    const float threehalfs = 1.5F;

			    float x2 = number * 0.5F;
			    float y = number;

			    // evil floating point bit level hacking
			    long i = * ( long * ) &y;

			    // value is pre-assumed
			    i = 0x5f3759df - ( i >> 1 );
			    y = * ( float * ) &i;

			    // 1st iteration
			    y = y * ( threehalfs - ( x2 * y * y ) );

			    // 2nd iteration, this can be removed
			    // y = y * ( threehalfs - ( x2 * y * y ) );


			return y*number;
		//	return 0;
		};

		inline double fastPow(double a, double b) {
		    union {
		        double d;
		        int x[2];
		    } u = { a };
		    u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
		    u.x[0] = 0;
		    return u.d;
		};

		inline 	double exp1(double x) {
		  x = 1.0 + x / 256.0;
		  x *= x; x *= x; x *= x; x *= x;
		  x *= x; x *= x; x *= x; x *= x;
		  return x;
		}
		inline double exp2(double x) {
		  x = 1.0 + x / 1024;
		  x *= x; x *= x; x *= x; x *= x;
		  x *= x; x *= x; x *= x; x *= x;
		  x *= x; x *= x;
		  return x;
		}
		double exp_fast(double a)
		{
		   union { double d; long long x; } u;
		   u.x = (long long)(6497320848556798LL * a + 0x3fef127e83d16f12LL);
		   return u.d;
		}
		//Variables
		bool status;

		//Parameter
		float input_gain;
		float output_gain;
		float ratio;
		float slope;
		float threshold;
		float t_attack;
		float t_release;
		float t_rms;

		float diffsum;

	private:

		//Methods
		void reset_buffer(void);

		//Parameter
		float comp_gain, target_gain;
		float limit_gain;
		unsigned long i_attack,i_release;
		float stepsize_attack,stepsize_release;

		//RMS value
		float rms_sum;
		float c_rms;
		unsigned rms_len;

		//Monitor RMS
		unsigned update_rate;
		unsigned i_update;

		//Compressor buffer
		static const unsigned rms_max=1200;
		float* rmsbuf = new float[rms_max];
		unsigned rptr;

		//Main buffer
		float t_main;
		unsigned long delay_len;
		static const unsigned buf_max=1200; 	//25ms
		float* buf = new float[buf_max];
		unsigned ptr;
};



#endif /* INC_MODULES_COMPRESSOR_HPP_ */
