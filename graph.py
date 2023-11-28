import matplotlib.pyplot as plt


nthreads = []
power = 2
nthreads
for i in range(14):
    nthreads.append(power**i)

execution_time_1 = [
        1.76764,
        0.898974,
        0.451589,
        0.229376,
        0.118068,
        0.0963341,
        0.0795154,
        0.0760501,
        0.0790963,
        0.0840177,
        0.0994335,
        0.135562,
        0.210895,
        0.371931
        ]

print(nthreads)

plt.figure()
plt.title("Execution time result with variyng thread counts")
plt.plot(nthreads, execution_time)
plt.xlabel("Number of threads")
plt.ylabel("Execution time (s)")
plt.xscale('log', base=2)
plt.legend()
plt.show()
