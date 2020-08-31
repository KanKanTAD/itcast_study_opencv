from urx1.URRobot import URRobot

import math

DE2R = math.pi/180

robot = URRobot('192.168.36.28')
# robot.movej([-144.98 * DE2R, -97.67 * DE2R, -102.98 * DE2R,-68.95 * DE2R, 83.07 * DE2R, 58.15 * DE2R])
robot.movel([-54.16/1000,-324.52/1000,183.76/1000,3.1225,0.5556,0.2693])