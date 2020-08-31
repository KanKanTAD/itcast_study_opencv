from urx2.URSecmon import URScemon

class URRobot:
    def __init__(self,ip):
        self.secmon = URScemon(ip)

    def movej(self,joints,a=1.4,v=1.05):
        self.secmon.movej(joints,a,v)
        # 等待 当前执行完成
        self.waiting_for_running()

    def movel(self,pose,a=1.2,v=0.25):
        self.secmon.movel(pose,a,v)
        # 等待当前执行完成
        self.waiting_for_running()

    def waiting_for_running(self):
        while self.secmon.is_program_running():
            pass

