import socket

class URRobot:
    def __init__(self,ip):
        self.conn = socket.create_connection((ip,30002))

    def movej(self,joints,a=1.4,v=1.05):
        msg = self.__format_script('movej',joints,a,v)
        self.conn.send(msg)

    def movel(self,pose,a=1.2,v=0.25):
        msg = self.__format_script('movel',pose,a,v,prefix='p')
        self.conn.send(msg)

    def __format_script(self,command,data,a,v,prefix=''):
        '''拼接脚本'''
        msg = '{}({}[{},{},{},{},{},{}], a={}, v={}, t=0, r=0)\n'.format(command,prefix,*data,a,v)
        return msg.encode()
