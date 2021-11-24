#include<iostream>
#include "mpi.h"

using namespace std;
int main(int argv, char* argc[]) {
	int rank = 0;
	int data = 0;
	int* buffer = NULL;
	MPI_Init(&argv, &argc);


	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
		buffer = a;
	}
	cout << "\nData value before the Scatter Msg (rank|data):" << rank << "->" << data << "\n";
	
	MPI_Scatter(buffer, 1, MPI_INT, &data, 1, MPI_INT, 0, MPI_COMM_WORLD);
	cout << "\nData value After the Scatter Msg (rank|data):" << rank << "->" << data << "\n";

	cout << "\n";
	MPI_Finalize();
	return 0;
}
