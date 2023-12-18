import matplotlib.pyplot as plt
import numpy as np


cpu_results = np.array([
        0.003,
        0.001,
        0.002,
        0.002,
        0.003,
        0.01,
        0.008,
        0.03,
        0.031,
        0.06,
        0.034,
        0.048,
        0.052,
        0.06,
        0.076,
        0.122,
        0.221,
        0.395,
        0.665,
        1.231,
        3.148,
        3.556,
        3.701,
        4.613,
        5.924,
        8.738,
        14.239,
        24.8,
        48.332,
        88.346
    ])

gpu_results = np.array([
        0.269,
        0.24,
        0.239,
        0.239,
        0.227,
        0.23,
        0.227,
        0.233,
        0.242,
        0.233,
        0.246,
        0.25,
        0.258,
        0.236,
        0.237,
        0.286,
        0.254,
        0.27,
        0.298,
        0.349,
        1.837,
        1.846,
        1.899,
        1.965,
        2.085,
        2.41,
        2.959,
        4.096,
        6.377,
        11.002
    ])

cpu_results = cpu_results.reshape(3, -1)
gpu_results = gpu_results.reshape(3, -1)

iterations = [2**i for i in range(10)]
size = [100, 1000, 10000]

for i in range(3):
    plt.figure()
    plt.title(f"Grid of size {size[i]}x{size[i]}, CPUs vs GPU")
    plt.plot(iterations, cpu_results[i], label="32 CPUs")
    plt.plot(iterations, gpu_results[i], label="1 GPU")
    plt.xscale('log', base = 2)
    plt.xlabel("Number of iterations")
    plt.ylabel("Execution time")
    plt.legend()
    plt.show()

