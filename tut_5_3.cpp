#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int myid, size, i, tag = 11;
    float send_val, recv_val;
    float sum = 0.0;

    MPI_Status status;

    /* Start MPI */
    MPI_Init(&argc, &argv);

    /* Get total processes */
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* Get process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    
    if (myid != 0)
    {
        
        send_val = (float) myid;   
        //(buffer,count,dtype,dest,tag,comm)
        MPI_Send(&send_val, 1, MPI_FLOAT,
                 0, tag, MPI_COMM_WORLD);
    }

    
    else
    {
        sum = 0.0;

        for (i = 1; i < size; i++)
        {   //(buffer,count,dtype,srce,tag,comm,status)
            MPI_Recv(&recv_val, 1, MPI_FLOAT,
                     i, tag, MPI_COMM_WORLD, &status);

            sum += recv_val;
        }

        printf("Final sum received at host = %f\n", sum);
    }

    
    MPI_Finalize();

    return 0;
}
