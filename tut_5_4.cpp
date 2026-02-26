#include <stdio.h>
#include <cmath>
#include <mpi.h>

double f(double x)
{
    return 1 + std::sin(x);
}

/* local trapezoidal computation */
double Trap(double local_a, double local_b,
            int local_n, double h)
{
    double integral;
    double x;
    int i;

    integral = (f(local_a) + f(local_b)) / 2.0;

    for (i = 1; i < local_n; i++)
    {
        x = local_a + i * h;
        integral += f(x);
    }

    return integral * h;
}

int main(int argc, char** argv)
{
    int myid, size, i;
    double a = 0.0, b = 10.0;
    int n = 1000;

    double h;
    int local_n;
    double local_a, local_b;

    double local_int, total_int = 0;
    double temp;

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    h = (b - a) / n;
    local_n = n / size;

    local_a = a + myid * local_n * h;
    local_b = local_a + local_n * h;

    /* each process computes */
    local_int = Trap(local_a, local_b, local_n, h);


    if (myid != 0)
    {
        
        MPI_Send(&local_int, 1, MPI_DOUBLE,
                 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        total_int = local_int;

        for (i = 1; i < size; i++)
        {
            MPI_Recv(&temp, 1, MPI_DOUBLE,
                     i, 0, MPI_COMM_WORLD, &status);

            total_int += temp;
        }

        printf("Integral = %f\n", total_int);
    }

    MPI_Finalize();
    return 0;
}
