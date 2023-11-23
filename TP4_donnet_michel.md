---
title: TP4 Calculating π using Riemann Sum in C++ with OpenMP
author: Michel Donnet
date: \today
---

# Explanation of the code

My code is all done in the main.cpp.
We can execute my code like this:
```bash
./build/tp4
```
Or like this:
```bash
./build/tp4 1000000
```
Or like this:
```bash
./build/tp4 1000000 16
```

At the begining, I look after parameters, to set up the number of thread (stored in the variable 'n') and the number of circumscribed rectangles (stored in the variable 'nthread').

To change the default number of thread used, which is 8, I make:
```C++
omp_set_num_threads(nthread);
```
This function defined in 'omp.h' allow us to change the number of thread used to execute parallel sections of our code.

Then, I store the current time to compute at the end of the code the execution time like this:
```C++
double start = omp_get_wtime();
```
This function is also defined in 'omp.h' and give the current time in second, which is stored, in my case, in the variable 'start'.

I use a lambda expression to define the function $\frac{4}{1 + x^2}$. Here I put a 4 instead of a 1, because the integration of the function $\frac{1}{1 + x^2}$ in range [0, 1] give us an approximation of $\frac{\pi}{4}$, that's why I multiply the function $\frac{1}{1 + x^2}$ by 4 to compute directly an approximation of $\pi$.

# Explanation of the parallelization using OpenMP.
# Presentation of the execution time results with varying thread counts.
# Graphs depicting the scaling of execution times.
# Observations and conclusions based on your findings.
