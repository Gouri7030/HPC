/* 
For 2D Matrix Addition of size 2000, Write a OpenMP code with the following: 
Use DYNAMIC schedule and set the loop iteration chunk size to various sizes 
when changing the size of your matrix. Analyze the speedup. 
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//size of resultant matrix - N*M

//size of matrix = 50*40 = 2000
#define N 50 /* number of rows */
#define M 40 /* number of columns */
#define threads_cnt 16

int main (int argc, char *argv[])
{
    
	double time = omp_get_wtime();
    int tid, nthreads, i, j, k;
    int a[N][M], b[N][M], c[N][M];
    /*** Create a parallel region explicitly scoping all variables ***/

    omp_set_num_threads(threads_cnt);

    int n_per_thread = N*M / threads_cnt;
    printf("\nNumber of Threads : %d",threads_cnt);
    printf("\nChunk Size : %d\n\n",n_per_thread);
    #pragma omp parallel default(shared) 
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Starting matrix multiple example with %d threads\n",nthreads);
            printf("Initializing matrices...\n");
        }

        /*** Initialize matrices ***/
        #pragma omp for schedule(dynamic,n_per_thread )
            for (i=0; i<N; i++)
                for (j=0; j<M; j++)
                    a[i][j]= i+j;
        
        #pragma omp for schedule(dynamic,n_per_thread )
            for (i=0; i<N; i++)
                for (j=0; j<M; j++)
                    b[i][j]= i*j;
         
        #pragma omp for schedule(dynamic,n_per_thread )
            for (i=0; i<N; i++)
                for (j=0; j<M; j++)
                    c[i][j]= 0;

        
        printf("Thread %d starting matrix addition...\n",tid);
        #pragma omp for schedule(dynamic,n_per_thread )
            for (i=0; i<N; i++)
            {
                printf("Thread=%d did row=%d\n",tid,i);
                for(j=0; j<M; j++)
                	c[i][j] += a[i][j] + b[i][j];
            }
     } 
    
   

   	printf("First Matrix:\n");
    for (i=0; i<N; i++)
    {
        for (j=0; j<M; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
    printf("\n");
    
    printf("Second Matrix:\n");
    for (i=0; i<N; i++)
    {
        for (j=0; j<M; j++)
            printf("%d ", b[i][j]);
        printf("\n");
    }
    printf("\n");

    printf("Resultant Matrix:\n");
    for (i=0; i<N; i++)
    {
        for (j=0; j<M; j++)
            printf("%d ", c[i][j]);
        printf("\n");
    }
    
    printf("\n");

    
    printf ("\nTime taken: %f Seconds",omp_get_wtime() - time); 
    return(0);
}