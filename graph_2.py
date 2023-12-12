import matplotlib.pyplot as plt
import numpy as np

result = np.array([
        9.92393,
        9.9577,
        4.56408,
        4.55787,
        1.91288,
        1.91381,
        5.01694,
        5.04492,
        2.32204,
        2.33358,
        1.00025,
        1.01361,
        2.53762,
        2.55697,
        1.20244,
        1.20796,
        0.528632,
        0.54867,
        1.32465,
        1.34207,
        0.639346,
        0.66506,
        0.319712,
        0.378627,
        0.789043,
        0.820028,
        0.418412,
        0.447315,
        0.207129,
        0.295152,
        9.91862,
        9.99789,
        4.53536,
        4.56192,
        1.89838,
        1.90871,
        5.00815,
        5.01453,
        2.3103,
        2.33023,
        0.984073,
        1.00263,
        2.5383,
        2.59395,
        1.2039,
        1.21402,
        0.530357,
        0.537065,
        1.31549,
        1.3284,
        0.654001,
        0.659013,
        0.310618,
        0.338442,
        0.789271,
        0.800312,
        0.38705,
        0.421116,
        0.206272,
        0.254029,
        9.91601,
        9.96095,
        4.55577,
        4.54251,
        1.90684,
        1.92251,
        5.00701,
        5.05233,
        2.34174,
        2.33694,
        1.00243,
        1.00015,
        2.55023,
        2.54809,
        1.19648,
        1.20318,
        0.53826,
        0.545015,
        1.31934,
        1.34441,
        0.674249,
        0.666143,
        0.326433,
        0.333796,
        0.826238,
        0.797081,
        0.396253,
        0.406923,
        0.20578,
        0.246336,
        9.91783,
        9.95781,
        4.544,
        4.56644,
        1.91293,
        1.92706,
        5.02133,
        5.04018,
        2.33292,
        2.32131,
        1.005,
        0.999006,
        2.54279,
        2.56661,
        1.19326,
        1.22229,
        0.532915,
        0.5588,
        1.34948,
        1.34592,
        0.710725,
        0.672924,
        0.366452,
        0.382471,
        0.787525,
        0.790332,
        0.39952,
        0.401307,
        0.234272,
        0.208728,
        9.91856,
        9.92313,
        4.53915,
        4.55635,
        1.90496,
        1.89631,
        5.00893,
        5.0081,
        2.30969,
        2.30669,
        0.991512,
        0.987299,
        2.55543,
        2.53884,
        1.18976,
        1.19057,
        0.530262,
        0.534647,
        1.32002,
        1.31958,
        0.649114,
        0.634145,
        0.32669,
        0.310223,
        0.806507,
        0.809144,
        0.399939,
        0.402701,
        0.215363,
        0.213451,
        9.9184,
        9.97064,
        4.57262,
        4.55435,
        1.90657,
        1.89971,
        5.00372,
        4.99891,
        2.31144,
        2.31832,
        0.99246,
        0.985881,
        2.54057,
        2.56428,
        1.20573,
        1.20403,
        0.523388,
        0.53872,
        1.32363,
        1.31295,
        0.666954,
        0.635458,
        0.326509,
        0.307504,
        0.796788,
        0.792777,
        0.396047,
        0.390315,
        0.214394,
        0.215645
        ])
print(result[::6])
chunk_size = [2**i for i in range(6)]
threads_number = [2**i for i in range(4)]
threads_number.append(14)
print(threads_number)
print(chunk_size)
index = 1

plt.figure()
for i in range(5):
    plt.subplot(5, 3, index)
    index += 1
    plt.title(f"Region 1: {threads_number[i]} threads")
    plt.plot(chunk_size, result[6*i::30], label='static')
    plt.plot(chunk_size, result[6*i + 1::30], label='dynamic')
    plt.xscale('log', base=2)
    plt.xlabel("chunk_size")
    plt.ylabel("time")
    plt.legend()
    plt.subplot(5, 3, index)
    index += 1
    plt.title(f"Region 2: {threads_number[i]} threads")
    plt.plot(chunk_size, result[6*i + 2::30], label='static')
    plt.plot(chunk_size, result[6*i + 3::30], label='dynamic')
    plt.xscale('log', base=2)
    plt.xlabel("chunk_size")
    plt.ylabel("time")
    plt.legend()
    plt.subplot(5, 3, index)
    index += 1
    plt.title(f"Region 3: {threads_number[i]} threads")
    plt.plot(chunk_size, result[6*i + 4::30], label='static')
    plt.plot(chunk_size, result[6*i + 5::30], label='dynamic')
    plt.xscale('log', base=2)
    plt.xlabel("chunk_size")
    plt.ylabel("time")
    plt.legend()
plt.show()
for i in range(6):
    plt.figure()
    plt.subplot(1, 3, 1)
    plt.title(f"Region 1: chunk size: {chunk_size[i]}")
    plt.plot(threads_number, result[30*i:30*(i + 1):6], label='static')
    plt.plot(threads_number, result[30*i + 1:30*(i + 1):6], label='dynamic')
    plt.xscale('log', base=2)
    plt.yscale('log')
    plt.xlabel("threads")
    plt.ylabel("time")
    plt.legend()
    plt.subplot(1, 3, 2)
    plt.title(f"Region 2: chunk size: {chunk_size[i]}")
    plt.plot(threads_number, result[30*i + 2:30*(i + 1):6], label='static')
    plt.plot(threads_number, result[30*i + 3:30*(i + 1):6], label='dynamic')
    plt.xscale('log', base=2)
    plt.yscale('log')
    plt.xlabel("threads")
    plt.ylabel("time")
    plt.legend()
    plt.subplot(1, 3, 3)
    plt.title(f"Region 3: chunk size: {chunk_size[i]}")
    plt.plot(threads_number, result[30*i + 4:30*(i + 1):6], label='static')
    plt.plot(threads_number, result[30*i + 5:30*(i + 1):6], label='dynamic')
    plt.xscale('log', base=2)
    plt.yscale('log')
    plt.xlabel("threads")
    plt.ylabel("time")
    plt.legend()
    plt.show()


'''
plt.figure()
plt.plot(chunk_size, region_1[::2], label='region_1 static schedule')
plt.plot(chunk_size, region_1[1::2], label='region_1 dynamic schedule')
plt.plot(chunk_size, region_2[::2], label='region_2 static schedule')
plt.plot(chunk_size, region_2[1::2], label='region_2 dynamic schedule')
plt.xlabel("Chunk size")
plt.ylabel("Time execution")
plt.legend()
plt.xscale('log', base=2)
plt.show()
'''
