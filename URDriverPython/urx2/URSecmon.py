import socket
from threading import Thread
from urx2.ParseUtils import ParserUtils

class URScemon(Thread):
    def __init__(self, ip):
        super(URScemon, self).__init__()
        self.conn = socket.create_connection((ip, 30002))

        self._parser = ParserUtils()
        self._dict = {}
        self._dataqueue = bytes()
        # 开启
        self.start()



    def run(self):
        '''子线程'''
        while True:
            data = self._get_data()
            tmpdict = self._parser.parse(data)
            self._dict = tmpdict

    def _get_data(self):
        """
        returns something that looks like a packet, nothing is guaranted
        """
        while True:
            # self.logger.debug("data queue size is: {}".format(len(self._dataqueue)))
            ans = self._parser.find_first_packet(self._dataqueue[:])
            if ans:
                self._dataqueue = ans[1]
                # self.logger.debug("found packet of size {}".format(len(ans[0])))
                return ans[0]
            else:
                # self.logger.debug("Could not find packet in received data")
                tmp = self.conn.recv(1024)
                self._dataqueue += tmp

    def movej(self, joints, a=1.4, v=1.05):
        msg = self.__format_script('movej', joints, a, v)
        self.conn.send(msg)

    def movel(self, pose, a=1.2, v=0.25):
        msg = self.__format_script('movel', pose, a, v, prefix='p')
        self.conn.send(msg)

    def __format_script(self, command, data, a, v, prefix=''):
        '''拼接脚本'''
        msg = '{}({}[{},{},{},{},{},{}], a={}, v={}, t=0, r=0)\n'.format(command, prefix, *data, a, v)
        return msg.encode()

    def is_program_running(self, wait=False):
        """
        return True if robot is executing a program
        Rmq: The refresh rate is only 10Hz so the information may be outdated
        """
        # return True
        return self._dict["RobotModeData"]["isProgramRunning"]
