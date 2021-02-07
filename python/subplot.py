# encoding:utf-8
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

in_data = np.loadtxt("input.csv", delimiter = ",")
dt = {
    'time'    : in_data[:, 0],
    'data1'   : in_data[:, 1],
    'data2'   : in_data[:, 2],
    'data3    : in_data[:, 3],
}
data = pd.DataFrame(dt)

plt.figure(tight_layout=True)

plt.subplot(221, xlabel='time(s)', ylabel='dataX')
plt.plot(data['time'], data['data1'], label='data1')
plt.plot(data['time'], data['data1'], label='data2')
plt.plot(data['time'], data['data1'], label='data3')
plt.axvline(1.3, ls='--', lw=0.75, color='r')
plt.legend()

plt.subplot(222, xlabel='time(s)', ylabel='dataY')
plt.plot(data['time'], data['data1'], label='data1')
plt.plot(data['time'], data['data1'], label='data2')
plt.legend()

plt.subplot(223, xlabel='time(s)', ylabel='dataZ')
plt.plot(data['time'], data['data1'], label='data1')
plt.legend()

plt.show()
