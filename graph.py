import matplotlib.pyplot as plt
import numpy as np

region_1 = np.array([
        0.947764,
        0.857157,
        0.934655,
        0.845376,
        0.791432,
        0.837257,
        0.791632,
        0.847664,
        0.78248,
        0.83769,
        0.78367,
        0.812687,
        0.790908,
        0.838961,
        0.786244,
        0.858046,
        0.782479,
        0.825561,
        0.805382,
        0.838357,
        1.07631,
        0.835852,
        0.825237,
        0.834147,
        1.26594,
        0.880962,
        1.02186,
        0.85442
        ])

region_2 = np.array([
        0.394522,
        0.452613,
        0.407947,
        0.416857,
        0.556707,
        0.440989,
        0.410292,
        0.432819,
        0.39752,
        0.421749,
        0.39078,
        0.43319,
        0.391721,
        0.443573,
        0.401217,
        0.449566,
        0.389355,
        0.420713,
        0.39951,
        0.423068,
        0.399521,
        0.574281,
        0.394868,
        0.405525,
        0.651942,
        0.427185,
        0.450496,
        0.438987
        ])

chunk_size = [2**i for i in range(14)]

plt.figure()
plt.plot(chunk_size, region_1[::2], label='region_1 static schedule', color='r')
plt.plot(chunk_size, region_1[1::2], label='region_1 dynamic schedule', color='g')
plt.plot(chunk_size, region_2[::2], label='region_2 static schedule', color='r')
plt.plot(chunk_size, region_2[1::2], label='region_2 dynamic schedule', color='g')
plt.xlabel("Chunk size")
plt.ylabel("Time execution")
plt.legend()
plt.xscale('log', base=2)
plt.show()
