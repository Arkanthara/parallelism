import matplotlib.pyplot as plt
import numpy as np

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

view_2 = [
        8.38126,
        3.96818,
        3.23257,
        2.37587,
        0.860725,
        0.949961,
        0.610521,
        0.572536,
        0.536241,
        0.484519,
        0.585521,
        0.624764,
        0.737935,
        0.75883
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
plt.plot(threads, iterations_32)
plt.xscale('log', base=2)
plt.xlabel("Number of iterations")
plt.ylabel("Time execution")
plt.legend()
plt.show()

plt.figure()
plt.plot(threads, view, label='tl(-1, -1) & br(1, 1)')
plt.plot(threads, view_2, label='tl(-1, -1) & br(1, 1)')
plt.plot(threads, nthreads, label='tl(-2, -2) & br(2, 2)')
plt.plot(threads, nthreads_2, label='tl(-2, -2) & br(2, 2)')
plt.xlabel("Number of threads")
plt.ylabel("Time execution")
plt.legend()
plt.xscale('log', base=2)
plt.show()


view = np.array(view)
view_2 = np.array(view_2)
nthreads = np.array(nthreads)
nthreads_2 = np.array(nthreads_2)

average_view = (view + view_2) / 2
average_nthreads = (nthreads + nthreads_2) / 2

speed_up_view = average_view[0]/average_view
speed_up_nthreads = average_nthreads[0]/average_nthreads

plt.figure()
plt.plot(threads, speed_up_view, label='tl(-1, -1) & br(1, 1)')
plt.plot(threads, speed_up_nthreads, label='tl(-1, -1) & br(1, 1)')
plt.xlabel("Number of threads")
plt.ylabel("Speed up")
plt.xscale('log', base=2)
plt.legend()
plt.show()



