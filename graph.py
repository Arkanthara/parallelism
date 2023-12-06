import matplotlib.pyplot as plt
import numpy as np

iterations_32 = np.array([
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
        ])

# tl(-1, -1) & br(1, 1)
view_1_1 = np.array([
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
        ])

view_1_2 = np.array([
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
        ])


# tl(-2, -2) & br(2, 2)
view_2_1 = np.array([
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
        ])

view_2_2 = np.array([
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
        ])



# tl(-0.25, -0.25) & br(0.25, 0.25)
view_3_1 = np.array([
        14.9778,
        7.95445,
        4.03104,
        2.06516,
        1.48374,
        1.14348,
        1.08737,
        0.968812,
        0.986789,
        0.953168,
        0.990705,
        1.01887,
        1.06153,
        1.2483
        ])

view_3_2 = np.array([
        15.6937,
        7.79096,
        3.97119,
        2.17845,
        1.44077,
        1.14504,
        0.967001,
        1.00167,
        0.951699,
        0.956886,
        0.945903,
        0.983777,
        1.06618,
        1.17135
        ])

# tl(3, 3) & br(4, 4)
view_4_1 = np.array([
        0.268012,
        0.1202,
        0.0855985,
        0.0747839,
        0.0846812,
        0.0756484,
        0.0833982,
        0.135596,
        0.122969,
        0.112528,
        0.163694,
        0.17875,
        0.266643,
        0.449709
        ])

view_4_2 = np.array([
        0.276957,
        0.182151,
        0.147815,
        0.103847,
        0.0785679,
        0.129736,
        0.0872423,
        0.123586,
        0.105965,
        0.135596,
        0.155276,
        0.201097,
        0.302228,
        0.451074
        ])

threads = [2**i for i in range(14)]

view_1 = (view_1_1 + view_1_2) / 2
view_2 = (view_2_1 + view_2_2) / 2
view_3 = (view_3_1 + view_3_2) / 2
view_4 = (view_4_1 + view_4_2) / 2

plt.figure()
plt.plot(threads, iterations_32)
plt.xscale('log', base=2)
plt.yscale('log', base=2)
plt.xlabel("Number of iterations")
plt.ylabel("Time execution")
plt.legend()
plt.show()

plt.figure()
plt.plot(threads, view_1, label='tl(-1, -1) & br(1, 1)')
plt.plot(threads, view_2, label='tl(-2, -2) & br(2, 2)')
plt.plot(threads, view_3, label='tl(-0.25, -0.25) & br(0.25, 0.25)')
plt.plot(threads, view_4, label='tl(3, 3) & br(4, 4)')
plt.xlabel("Number of threads")
plt.ylabel("Time execution")
plt.legend()
plt.xscale('log', base=2)
plt.show()


speed_up_view_1 = view_1[0]/view_1
speed_up_view_2 = view_2[0]/view_2
speed_up_view_3 = view_3[0]/view_3
speed_up_view_4 = view_4[0]/view_4

plt.figure()
plt.plot(threads, speed_up_view_1, label='tl(-1, -1) & br(1, 1)')
plt.plot(threads, speed_up_view_2, label='tl(-2, -2) & br(2, 2)')
plt.plot(threads, speed_up_view_3, label='tl(-0.25, -0.25) & br(0.25, 0.25)')
plt.plot(threads, speed_up_view_4, label='tl(3, 3) & br(4, 4)')
plt.xlabel("Number of threads")
plt.ylabel("Speed up")
plt.xscale('log', base=2)
plt.legend()
plt.show()



