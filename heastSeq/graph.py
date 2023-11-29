import matplotlib.pyplot as plt

size64_1 = [
0.000623263,
0.00318022,
0.0291533,
0.287789,
2.85652,
28.6201
]

size128_1 = [
0.00216731,
0.0126726,
0.115047,
1.13957,
11.3812,
113.64
]

size256_1 = [
0.00864186,
0.0499757,
0.458653,
4.54542,
45.4236,
449.604
]
size64_2 = [
0.0394493,
0.0407327,
0.0558461,
0.215324,
1.81312,
17.8895
]
size128_2 = [
0.0398728,
0.04833,
0.104653,
0.697467,
6.68459,
66.5839
]
size256_2 = [
0.0516994,
0.0751354,
0.311651,
2.55946,
26.0479,
251.321
]
size64_4 = [
0.0989108,
0.104366,
0.123236,
0.241459,
1.52731,
14.5659
]
size128_4 = [
0.0997522,
0.103488,
0.14062,
0.508588,
4.19725,
41.2854
]
size256_4 = [
0.111641,
0.124484,
0.262489,
1.6335,
15.3542,
150.245
]
size64_8 = [
0.109853,
0.109043,
0.123314,
0.236151,
1.43218,
13.4493
]
size128_8 = [
0.226787,
0.231291,
0.261097,
0.561691,
3.29824,
30.9902
]
size256_8 = [
0.235403,
0.248443,
0.330519,
1.28058,
10.3525,
106.393
]
size64_16 = [
0.132749,
0.133123,
0.141318,
0.269313,
1.46697,
13.18
]
size128_16 = [
0.131627,
0.144436,
0.166157,
0.419513,
3.01988,
29.0374
]
size256_16 = [
0.421932,
0.430781,
0.514254,
1.16464,
7.66321,
73.1513
]

iterations = [1, 10, 100, 1000, 10000, 100000]
process = [1, 2, 4, 8, 16]
size_64 = [size64_1, size64_2, size64_4, size64_8, size64_16] 
size_128 = [size128_1, size128_2, size128_4, size128_8, size128_16] 
size_256 = [size256_1, size256_2, size256_4, size256_8, size256_16] 


plt.figure()
for i in range(len(process)):
    plt.plot(iterations, size_64[i], label=f"Number of processors: {process[i]}")
    plt.xlabel("Iterations")
    plt.ylabel("Time (s)")
    plt.xscale('log')
plt.title(f"Grid of size 64x64")
plt.legend()
plt.show()
plt.figure()
for i in range(len(process)):
    plt.plot(iterations, size_128[i], label=f"Number of processors: {process[i]}")
    plt.xlabel("Iterations")
    plt.ylabel("Time (s)")
    plt.xscale('log')
plt.title(f"Grid of size 128x128")
plt.legend()
plt.show()
plt.figure()
for i in range(len(process)):
    plt.plot(iterations, size_256[i], label=f"Number of processors: {process[i]}")
    plt.xlabel("Iterations")
    plt.ylabel("Time (s)")
    plt.xscale('log')
plt.title(f"Grid of size 256x256")
plt.legend()
plt.show()
'''
for i in range(len(process)):
    plt.figure()
    plt.plot(iterations, size_128[i])
    plt.title(f"Grid of size 128x128 with {process[i]} processors")
    plt.xlabel("Iterations")
    plt.ylabel("Time (s)")
    plt.xscale('log')
    plt.yscale('log')
    plt.yticks(size_128[i], size_128[i])
    plt.show()
for i in range(len(process)):
    plt.figure()
    plt.plot(iterations, size_256[i])
    plt.title(f"Grid of size 256x256 with {process[i]} processors")
    plt.xlabel("Iterations")
    plt.ylabel("Time (s)")
    plt.xscale('log')
    plt.yscale('log')
    plt.yticks(size_256[i], size_256[i])
    plt.show()
'''
max_iter_64 = []
max_iter_128 = []
max_iter_256 = []
for i in range(len(process)):
    max_iter_64.append(size_64[i][-1])
    max_iter_128.append(size_128[i][-1])
    max_iter_256.append(size_256[i][-1])

print(max_iter_64)

plt.figure()
plt.plot(process, max_iter_64, label = "grid 64x64")
plt.plot(process, max_iter_128, label = "grid 128x128")
plt.xlabel("Number of processors")
plt.ylabel("Time (s)")
plt.title(f"Grid with $10^5$ iterations")
plt.legend()
plt.show()
