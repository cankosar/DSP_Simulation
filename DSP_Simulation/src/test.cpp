/*
 * test.cpp
 *
 *  Created on: 30.09.2019
 *      Author: KOS2ST
 */



#include "stdio.h"


//Class definition of buffer
class mybuffertype{

	public:
		mybuffertype(int size);
		int bufsize;
		float *buffer;

};

//Constructor of buffer
mybuffertype::mybuffertype(int size){
	bufsize=size;
//	buffer=new float[bufsize];		//Dynamic allocation works
	float buffer[bufsize]; 		//This static allocation doesn't work
}


//Class definition of container
class container{

	private:
		mybuffertype mybuffers[n_buffers];

	public:
		container();
		static const int n_buffers=3;
		const int n_sizes[n_buffers]={4,5,6};


};

//Constructor of container
container::container(void){


	int i;
	for(i=0;i<n_buffers;i++){
		mybuffertype mybuffers[i]= mybuffertype(n_sizes[i]);
	}


}

//Main
int main(void){

	container obj;

	int i;
	for(i=0;i<obj.n_buffers;i++){
		printf("Size: %d \t 1st element: %f\n",
				obj.mybuffers[i].size,
				obj.mybuffers[i].buffer[0]);
	}
}




