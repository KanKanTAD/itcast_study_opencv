# 拼接指令  发送socket给机器人
import socket
import math

DE2R = math.pi/180

# 创建socket连接
conn = socket.create_connection(('192.168.36.28',30002))
# 发送指令
msg = 'movej([{},{},{},{},{},{}], a=1.4, v=1.05, t=0, r=0)\n'.format(-144.98 * DE2R, -97.67 * DE2R, -102.98 * DE2R,-68.95 * DE2R, 83.07 * DE2R, 58.15 * DE2R)
# conn.send(msg.encode())

movelMsg = 'movel(p[{},{},{},{},{},{}], a=1.2, v=0.25, t=0, r=0)\n'.format(-54.16/1000,-324.52/1000,183.76/1000,3.1225,0.5556,0.2693)
conn.send(movelMsg.encode())