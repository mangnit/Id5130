#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    int N = 4;   // matrix size (NxN)

    vector<vector<int>> A(N, vector<int>(N));
    vector<vector<int>> B(N, vector<int>(N));
    vector<vector<int>> C(N, vector<int>(N));

    // Initialize matrices
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    // Parallel matrix addition
    #pragma omp parallel for
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // Print result
    cout << "Result Matrix C:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << C[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
