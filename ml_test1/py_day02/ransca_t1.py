#!/usr/bin/env python
# -*- coding:utf-8 -*-


import numpy as np
import open3d as o3d
import matplotlib.pyplot as plt


class Ransca_t1:

    def __init__(self, pts):
        self.__pts = pts
        self.set_sample_nums(2)
        self.set_thresh(0.3)

    def set_sample_nums(self, nums):
        self.__nums = nums

    def set_thresh(self, thresh):
        self.__thresh = thresh

    def doit(self, times=10):
        lenz = self.__pts.shape[1]
        indies = np.int0(np.linspace(0, lenz-1, lenz))
        mx, w, b = float('-inf'), 0, 0
        for _ in range(times):
            index = np.random.choice(indies, size=(1, self.__nums)).flatten()
            xy = self.__pts[:, index]
            x = xy[0, :]
            y = xy[1, :]
            reval = self.__it(x, y)
            if mx < reval[0]:
                [mx, w, b] = reval
        return w, b

    def __it(self, pts_x, pts_y):
        [w, b] = np.polyfit(pts_x, pts_y, 1)

        def in_it(x, y) -> bool:
            nonlocal w, b
            return -b - self.__thresh <= (w * x - y) <= -b + self.__thresh

        res = 0
        for i in range(pts.shape[1]):
            res += 1 if in_it(self.__pts[0, i], self.__pts[1, i]) else 0
        return res, w, b


if __name__ == "__main__":
    pts2d = np.random.normal(0, 2, size=(2, 300))
    x = np.linspace(-5, 5, 100)
    w = np.random.random(2)
    y = w[0] * x + w[1]
    # plt.plot(x, y, color=(0, 0, 0))
    y += np.random.normal(0, 0.3, 100)
    plt.scatter(x, y, edgecolors=(0, 0, 0))
    z = np.array([x, y])
    pts = np.empty((2, 300+100))
    pts[:, :300] = pts2d
    pts[:, 300:] = z
    plt.scatter(pts[0, :], pts[1, :])

    [w, b] = np.polyfit(pts[0, :], pts[1, :], 1)
    print(w, b)
    y_hat = w * x + b
    plt.plot(x, y_hat, color=(1, 0, 0))

    sca = Ransca_t1(pts)
    sca.set_sample_nums(20)

    w, b = sca.doit(times=30)
    y_bar = w*x + b
    plt.plot(x, y_bar, color=(0, 1, 0))

    plt.show()
