#!/usr/bin/env python

# -*- coding:utf-8 -*-


import socket
from typing import Tuple, List
import threading


class ur_robot:

    def __init__(self, ip, port=30002):
        self.ip = ip
        self.port = port

        self.is_running = False

        self.cmd_queue = []

    def _append_cmd(self, str_cmd):
        self.cmd_queue.append(str_cmd)

    def run_cmd_queue(self):
        if self.is_running:
            return

        def target():
            while len(self.cmd_queue) > 0:
                cmd = self.cmd_queue[0]
                self.__accept_cmd(cmd)
                del self.cmd_queue[0]

            self.is_running = False

        t = threading.Thread(target=target)
        t.run()

    def __accept_cmd(self, str_cmd):
        self.socket.send(str_cmd)

    def connect_to_robot(self):
        self.socket = socket.create_connection((self.ip, self.port))

    def __move(self, str_cmd):
        self._append_cmd(cmd)
        self.run_cmd_queue()

    def movej(self, joints: List[float], a=0.1, v=0.1):

        str_joints = "[" + ("".join(joints)) + "]"

        cmd = "movej( {} ,a={},v={},t={})".format(str_joints, a, v, 1.0)
        self.__move(cmd)

    def movel(self, pose: List[float], a, v):
        str_pose = "p["+("".join(pose))+"]"
        cmd = "movel( {},a={},v={},t={})".format(str_pose, a, v, 1.0)
        self.__move(cmd)
