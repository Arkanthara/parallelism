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
        3.18388,
        9.54489
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

nthreads = [
        2.85318,
        1.45077,
        1.41677,
        1.2684,
        0.706657,
        0.476348,
        0.453911,
        0.297427,
        0.218366,
        0.264218,
        0.28844,
        0.319663,
        0.401562,
        0.653384
        ]

nthreads_2 = [
        2.58466,
        1.03524,
        1.46482,
        1.03745,
        0.883901,
        0.723237,
        0.281151,
        0.197465,
        0.279353,
        0.235694,
        0.317157,
        0.240116,
        0.365295,
        0.59358
        ]

threads = [2**i for i in range(14)]

plt.figure()
plt.plot(threads, iterations_32, label='iterations')
plt.xscale('log', base=2)
plt.legend()
plt.show()

plt.figure()
plt.plot(threads, view, label='view changed')
plt.plot(threads, nthreads, label='Change number of threads')
plt.plot(threads, nthreads_2, label='Change number of threads')
plt.legend()
plt.xscale('log', base=2)
plt.show()


