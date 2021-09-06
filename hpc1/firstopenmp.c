#include <omp.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	//begining of parallel region
	#pragma omp parallel
	{
	
		printf("Hello World...2018BTECS00069....from thread = %d\n", omp_get_thread_num());
	}
	//end of parallel region
}
