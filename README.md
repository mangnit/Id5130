# ID5130 — OpenMP and MPI Tutorials

This repository contains practice programs and tutorial implementations for learning **parallel programming** using:

- OpenMP (shared-memory parallelism)
- MPI (message passing interface)
- C++ in WSL Ubuntu environment

## Files

- `tut_3_x.cpp` — OpenMP basics
- `tut_4_x.cpp` — Parallel constructs and synchronization
- `tut_5_x.cpp` — Initial MPI programs

## Compilation

### OpenMP
```bash
g++ -fopenmp file.cpp -o program
./program
```

### MPI
```bash
mpic++ file.cpp -o program
mpirun -np 4 ./program
```
