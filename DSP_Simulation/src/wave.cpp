/**
 * Read and parse a wave file
 *
 **/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/wave.hpp"

#define TRUE 1
#define FALSE 0

// WAVE header structure

unsigned char buffer4[4];
unsigned char buffer2[2];

//char* seconds_to_time(float seconds);


 FILE *ptr;

 struct HEADER header;

int wave::read_wav(void) {


	// open file
	 printf("Opening  file %s\n",input_file);

	 ptr = fopen(input_file, "rb");
	 if (ptr == NULL) {
		printf("Error opening file\n");
		exit(1);
	 }

	 int read = 0;

	 // read header parts
	// read = fread(header_chunk_in, sizeof(header_chunk_in), 1, ptr);

	 read = fread(header.riff, sizeof(header.riff), 1, ptr);
	 //printf("(1-4): %s \n", header.riff);

	 read = fread(buffer4, sizeof(buffer4), 1, ptr);
	 //printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);

	 // convert little endian to big endian 4 byte int
	 header.overall_size  = buffer4[0] |
							(buffer4[1]<<8) |
							(buffer4[2]<<16) |
							(buffer4[3]<<24);

	 //printf("(5-8) Overall size: bytes:%u, Kb:%u \n", header.overall_size, header.overall_size/1024);

	 read = fread(header.wave, sizeof(header.wave), 1, ptr);
	 //printf("(9-12) Wave marker: %s\n", header.wave);

	 read = fread(header.fmt_chunk_marker, sizeof(header.fmt_chunk_marker), 1, ptr);
	 //printf("(13-16) Fmt marker: %s\n", header.fmt_chunk_marker);

	 read = fread(buffer4, sizeof(buffer4), 1, ptr);
	 //printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);

	 // convert little endian to big endian 4 byte integer
	 header.length_of_fmt = buffer4[0] |
								(buffer4[1] << 8) |
								(buffer4[2] << 16) |
								(buffer4[3] << 24);
	 //printf("(17-20) Length of Fmt header: %u \n", header.length_of_fmt);

	 read = fread(buffer2, sizeof(buffer2), 1, ptr); //printf("%u %u \n", buffer2[0], buffer2[1]);

	 header.format_type = buffer2[0] | (buffer2[1] << 8);
	 char format_name[10] = "";
	 if (header.format_type == 1)
	   strcpy(format_name,"PCM");
	 else if (header.format_type == 6)
	  strcpy(format_name, "A-law");
	 else if (header.format_type == 7)
	  strcpy(format_name, "Mu-law");

	 //printf("(21-22) Format type: %u %s \n", header.format_type, format_name);

	 read = fread(buffer2, sizeof(buffer2), 1, ptr);
	 //printf("%u %u \n", buffer2[0], buffer2[1]);

	 header.channels = buffer2[0] | (buffer2[1] << 8);
	 //printf("(23-24) Channels: %u \n", header.channels);

	 read = fread(buffer4, sizeof(buffer4), 1, ptr);
	 //printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);

	 header.sample_rate = buffer4[0] |
							(buffer4[1] << 8) |
							(buffer4[2] << 16) |
							(buffer4[3] << 24);

	 //printf("(25-28) Sample rate: %u\n", header.sample_rate);

	 read = fread(buffer4, sizeof(buffer4), 1, ptr);
	 //printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);

	 header.byterate  = buffer4[0] |
							(buffer4[1] << 8) |
							(buffer4[2] << 16) |
							(buffer4[3] << 24);
	 //printf("(29-32) Byte Rate: %u , Bit Rate:%u\n", header.byterate, header.byterate*8);

	 read = fread(buffer2, sizeof(buffer2), 1, ptr);
	 //printf("%u %u \n", buffer2[0], buffer2[1]);

	 header.block_align = buffer2[0] |
						(buffer2[1] << 8);
	 //printf("(33-34) Block Alignment: %u \n", header.block_align);

	 read = fread(buffer2, sizeof(buffer2), 1, ptr);
	 //printf("%u %u \n", buffer2[0], buffer2[1]);


	 header.bits_per_sample = buffer2[0] |
						(buffer2[1] << 8);
	 //printf("(35-36) Bits per sample: %u \n", header.bits_per_sample);

	 read = fread(header.data_chunk_header, sizeof(header.data_chunk_header), 1, ptr);
	 //printf("(37-40) Data Marker: %s \n", header.data_chunk_header);


	 read = fread(buffer4, sizeof(buffer4), 1, ptr);
	 //printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);


	 header.data_size = buffer4[0] |
					(buffer4[1] << 8) |
					(buffer4[2] << 16) |
					(buffer4[3] << 24 );
	// printf("(41-44) Size of data chunk: %u \n", header.data_size);


	 // calculate no.of samples
	 num_samples = (8 * header.data_size) / (header.channels * header.bits_per_sample);
	// printf("Number of samples:%lu \n", num_samples);

	 unsigned long size_of_each_sample = (header.channels * header.bits_per_sample) / 8;
	 //printf("Size of each sample:%ld bytes\n", size_of_each_sample);

	 // calculate duration of file
	// float duration_in_seconds = (float) header.overall_size / header.byterate;
	 //printf("Approx.Duration in seconds=%f\n", duration_in_seconds);
	 //printf("Approx.Duration in h:m:s=%s\n", seconds_to_time(duration_in_seconds));



	 // read each sample from data chunk if PCM
	 if (header.format_type == 1) { // PCM

			unsigned long i =0;
			char data_buffer[size_of_each_sample];
			int  size_is_correct = TRUE;

			// make sure that the bytes-per-sample is completely divisible by num.of channels
			unsigned long bytes_in_each_channel = (size_of_each_sample / header.channels);
	//		printf("%u\n",size_of_each_sample);

			if ((bytes_in_each_channel  * header.channels) != size_of_each_sample) {
				//printf("Error: %ld x %ud <> %ld\n", bytes_in_each_channel, header.channels, size_of_each_sample);
				size_is_correct = FALSE;
			}

			if (size_is_correct) {
						// the valid amplitude range for values based on the bits per sample
				long low_limit = 0l;
				long high_limit = 0l;

				switch (header.bits_per_sample) {
					case 8:
						low_limit = -128;
						high_limit = 127;
						break;
					case 16:
						low_limit = -32768;
						high_limit = 32767;
						break;
					case 32:
						low_limit = -2147483648LL;
						high_limit = 2147483647;
						break;
				}

	//			printf("Int size: %d\n",sizeof(int));
				//printf("\n\n.Valid range for data values : %ld to %ld \n", low_limit, high_limit);
				for (i =1; i <= num_samples; i++) {
	//			for (i =1; i <= 100; i++) {
	//				//printf("==========Sample %ld / %ld=============\n", i, num_samples);
					read = fread(data_buffer, sizeof(data_buffer), 1, ptr);
					if (read == 1) {

						// dump the data read
						unsigned int  xchannels = 0;
						short data_in_channel = 0;

						for (xchannels = 0; xchannels < header.channels; xchannels ++ ) {
	//						//printf("Channel#%d : ", (xchannels+1));
							// convert data from little endian to big endian based on bytes in each channel sample
							if (bytes_in_each_channel == 4) {
								data_in_channel =	data_buffer[0] |
													(data_buffer[1]<<8) |
													(data_buffer[2]<<16) |
													(data_buffer[3]<<24);
							}
							else if (bytes_in_each_channel == 2) {
	//							data_in_channel = data_buffer[0] |(data_buffer[1] << 8);
								data_in_channel=(0b0000000011111111&data_buffer[0])|(data_buffer[1] << 8);
	//							if(data_in_channel<0){
	//								printf("Negative buf: %d(%#X) ->\t (%#X %#X) \t%#X\n",data_in_channel,data_in_channel,data_buffer[0],data_buffer[1],dummy);
	//							}

							}
							else if (bytes_in_each_channel == 1) {
								data_in_channel = data_buffer[0];
							}

							//Write to the data buffer
							if(1){ //If mono

								if(xchannels==0){
									iodat->datin[i]=data_in_channel;
	//								printf("(Mono:%d\n)",datin[i]);
								}

							}else{
								iodat->datin[i]=data_in_channel;
							}

	//						//printf("%d ", data_in_channel);

							// check if value was in range
							if (data_in_channel < low_limit || data_in_channel > high_limit)
								printf("**value out of range\n");

	//						//printf(" | ");
						}

	//					//printf("\n");
					}
					else {
						//printf("Error reading file. %d bytes\n", read);
						break;
					}

				} // 	for (i =1; i <= num_samples; i++) {

			} // 	if (size_is_correct) {
	 }else{

	//	 int print_len=100;
	//	 float test=3.54;
	//
	//	 char hash[print_len*8];
	//	 float dat[print_len];
	//
	//	 fread(hash, print_len*8, 1, ptr);
	//
	//	 //printf("Here\n");
	//	 int n=0;
	//
	//
	//	 for(n=0;n<print_len*8;n++){
	//		 //printf("hash%d = %#X\n",n,hash[n]);
	//
	//	 }
	//
	//	 for(n=0;n<print_len;n++){
	//	 dat[n]=hash[4*n] |
	//				(hash[4*n+1]<<8) |
	//				(hash[4*n+2]<<16) |
	//				(hash[4*n+3]<<24);
	//	 //printf("Float %d=%f\n",n,dat[n]);
	//	 }


	 }


	 //  if (header.format_type == 1) {

	 //printf("Closing file..\n");
	 fclose(ptr);

	  // cleanup before quitting
//	 free(input_file);

	 return 0;

}

int wave::write_wav(void) {

	//Sample data swap buf
	char buf[2];

	//Header
	unsigned char header_chunk[]={0x52,0x49,0x46,0x46,0x26,0x01,0x1D,0x00,0x57,0x41,0x56,0x45,0x66,0x6D,0x74,0x20,0x10,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x80,0xBB,0x00,0x00,0x00,0x77,0x01,0x00,0x02,0x00,0x10,0x00,0x64,0x61,0x74,0x61,0x02,0x01,0x1D,0x00};

	//Size of bytes
	char sizebuf[4];
	sizebuf[0]=header.data_size;
	sizebuf[1]=header.data_size>>8;
	sizebuf[2]=header.data_size>>16;
	sizebuf[3]=header.data_size>>24;

	//Open file
	ptr = fopen(output_file, "wb");
	fwrite(header_chunk, 40, 1, ptr);
	fwrite(sizebuf, 4, 1, ptr);

	//Write data buffer into the file
	for(unsigned i=1; i<=num_samples;i++){
		buf[0]=(char)(iodat->datout[i]);
		buf[1]=(char)(iodat->datout[i]>>8);
		fwrite(buf, 2, 1, ptr);
	}

	//Close file
	fclose(ptr);

	  // cleanup before quitting
//	free(filename);
	return 0;
}

/**
 * Convert seconds into hh:mm:ss format
 * Params:
 *	seconds - seconds value
 * Returns: hms - formatted string
 **/
// char* seconds_to_time(float raw_seconds) {
//  char *hms;
//  int hours, hours_residue, minutes, seconds, milliseconds;
//  hms = (char*) malloc(100);
//
//  //printf(hms, "%f", raw_seconds);
//
//  hours = (int) raw_seconds/3600;
//  hours_residue = (int) raw_seconds % 3600;
//  minutes = hours_residue/60;
//  seconds = hours_residue % 60;
//  milliseconds = 0;
//
//  // get the decimal part of raw_seconds to get milliseconds
//  char *pos;
//  pos = strchr(hms, '.');
//  int ipos = (int) (pos - hms);
//  char decimalpart[15];
//  memset(decimalpart, ' ', sizeof(decimalpart));
//  strncpy(decimalpart, &hms[ipos+1], 3);
//  milliseconds = atoi(decimalpart);
//
//
//  //printf(hms, "%d:%d:%d.%d", hours, minutes, seconds, milliseconds);
//  return hms;
//}
