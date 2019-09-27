/*
 * wave.h
 *
 *  Created on: 23.05.2019
 *      Author: Can
 */

#ifndef WAVE_HPP
#define WAVE_HPP

const unsigned len_container = 1000000;

class container{
	public:
		container(){};
	//	const unsigned long len_container=48000000;
		int datin[len_container];
		int datout[len_container];

};

class wave{
	public:

		unsigned long num_samples;
		const char* input_file;
		const char* output_file;
		int read_wav(void);
		int write_wav(void);
		int init_container(void);
		container* iodat = new container();
};

struct HEADER {
	unsigned char riff[4];						// RIFF string
	unsigned int overall_size	;				// overall size of file in bytes
	unsigned char wave[4];						// WAVE string
	unsigned char fmt_chunk_marker[4];			// fmt string with trailing null char
	unsigned int length_of_fmt;					// length of the format data
	unsigned int format_type;					// format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
	unsigned int channels;						// no.of channels
	unsigned int sample_rate;					// sampling rate (blocks per second)
	unsigned int byterate;						// SampleRate * NumChannels * BitsPerSample/8
	unsigned int block_align;					// NumChannels * BitsPerSample/8
	unsigned int bits_per_sample;				// bits per sample, 8- 8bits, 16- 16 bits etc
	unsigned char data_chunk_header [4];		// DATA string or FLLR string
	unsigned int data_size;						// NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
};



#endif /* WAVE_HPP */
