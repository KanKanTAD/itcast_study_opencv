import urx
import math
'''
joint1Edit = new QLineEdit("-144.98");
joint2Edit = new QLineEdit("-97.67");
joint3Edit = new QLineEdit("-102.98");
joint4Edit = new QLineEdit("-68.95");
joint5Edit = new QLineEdit("83.07");
joint6Edit = new QLineEdit("58.15");
'''

DE2R = math.pi/180


robot = urx.Robot("192.168.36.28")
robot.movej([-144.98*DE2R,-97.67*DE2R,-102.98*DE2R,-68.95*DE2R,83.07*DE2R,58.15*DE2R],1.5,1.05)

'''
xEdit = new QLineEdit("-54.16");
yEdit = new QLineEdit("-324.52");
zEdit = new QLineEdit("183.76");
rxEdit = new QLineEdit("3.1225");
ryEdit = new QLineEdit("0.5556");
rzEdit = new QLineEdit("0.2693");
'''

robot.movel([-54.16/1000,-324.52/1000,183.76/1000,3.1225,0.5556,0.2693],1.2,0.25)
