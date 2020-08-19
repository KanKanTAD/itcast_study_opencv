#!/usr/bin/env python
# -*- coding:utf-8 -*-


import numpy as np
import open3d as o3d
import matplotlib.pyplot as plt


if __name__ == "__main__":
    lz = 20
    lz_l = 300

    x = np.linspace(0, lz, lz_l)
    w = np.array([10])
    b = 20
    y = x * w + b

    y += np.random.normal(0, 1, lz_l)

    a = np.polyfit(x, y, 1)
    print(a)

    y_hat = x * a[0] + a[1]

    plt.plot(x, y)
    plt.plot(x, y_hat)
    plt.show()
