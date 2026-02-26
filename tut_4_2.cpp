#include <iostream>
#include <stdio.h>
#include <omp.h>
using namespace std;

int main() {
    int N;
    cout << "enter N\n" ;
    cin >> N;

    float A[100][100], B[100][100], C[100][100];

    // Initialize
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = i+j;
            B[i][j] = i-j;
            //C[i][j] = 0.0;
        }

    int threadsList[3] = {2, 4, 8};

    for (int k = 0; k < 3; k++) {
        int threads = threadsList[k];

        // Reset C
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                C[i][j] = 0.0;

        double start = omp_get_wtime();

        #pragma omp parallel for collapse(2) num_threads(threads)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                float sum = 0.0;
                for (int p = 0; p < N; p++) {
                    sum += A[i][p] * B[p][j];
                }
                C[i][j] = sum;
            }
        }

        double end = omp_get_wtime();

        printf("Time taken with %d threads: %f seconds\n", threads, end - start);
    }

    return 0;
}