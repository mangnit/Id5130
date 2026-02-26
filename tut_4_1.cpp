#include <stdio.h>
#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int N;
    cout << "enter mat dim\n" ;
    cin >> N;
    float A[200][200], B[200][200], C[200][200];

    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++) {
            A[i][j] = i+j;
            B[i][j] = i-j;
        }
    
    int threadlist[3] = {2 ,4, 8};

    for (int k = 0; k < 3; k ++) {
        int threads = threadlist[k];
        omp_set_num_threads(threads);
        double start = omp_get_wtime();
        #pragma omp parallel for
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                C[i][j] = A[i][j] + B[i][j];

        double end = omp_get_wtime();

        printf("Time taken with %d threads: %f seconds\n", threads, end - start);

    }
    return 0;

}