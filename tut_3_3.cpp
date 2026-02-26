#include <iostream>
#include <cmath>
#include <omp.h>

double f(double x) {
    return 1.0 + sin(x);
}

int main() {
    int n = 128;    
    int p = 4;   // number of threads
    double a = 0.0;
    double b = M_PI;

    

    double h = (b - a) / n;

    double odd_sum = 0.0;
    double even_sum = 0.0;

    

    // Parallel region
    #pragma omp parallel for num_threads(4) reduction(+:odd_sum)
    for (int i = 1; i < n; i += 2) {
        double x = a + i * h;
        odd_sum += f(x);
    }

    #pragma omp parallel for reduction(+:even_sum)
    for (int i = 2; i < n; i += 2) {
        double x = a + i * h;
        even_sum += f(x);
    }

    double result = (h / 3.0) * (f(a) + f(b) + 4.0 * odd_sum + 2.0 * even_sum);

    std::cout << "Simpson Result = " << result << std::endl;
    std::cout << "Exact Value = " << M_PI + 2 << std::endl;
    std::cout << "Error = " << fabs(result - (M_PI + 2)) << std::endl;

    return 0;
}
