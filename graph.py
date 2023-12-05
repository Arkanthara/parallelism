import matplotlib.pyplot as plt

iterations_32 = [
        0.0927524,
        0.0849673,
        0.0959054,
        0.110115,
        0.0996613,
        0.124463,
        0.169174,
        0.199028,
        0.301991,
        0.478377,
        0.898569,
        1.6809,
        3.18388
        ]

nthreads = [
        1.76043,
        0.913848,
        0.902653,
        0.501021,
        0.28755,
        0.23615,
        0.207469,
        0.192964,
        0.189018,
        0.205916,
        0.234047,
        0.320818,
        0.656128
        ]

view = [
        5.74042,
        3.1114,
        2.36198,
        1.39129,
        0.738005,
        0.582171,
        0.483359,
        0.436722,
        0.405562,
        0.426821,
        0.429562,
        0.466096,
        0.512826,
        0.640315
        ]

threads = [2**i for i in range(13)]

plt.figure()
plt.plot(threads, iterations_32, label='iterations')
plt.legend()
plt.show()

plt.figure()
plt.plot(threads, view, label='view changed')
plt.plot(threads, nthreads, label='Change number of threads')
plt.legend()
plt.xscale('log', base=2)
plt.show()


