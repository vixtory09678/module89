from commu import Protocol
from path import *
import time

class Manual_Path:

    def readStatus(self, status):
        if status == "all stop":
            if self.index < (self.size - 1):
                self.index = self.index + 1
                self.pro.send({"cmd":"reset","data":[1,1,1]})
                time.sleep(1)
                self.pro.send(self.data[self.index])
            else:
                self.data = []
                self.index = 0
                self.size = 0
                if (self.callHome):
                    self.callHome()

        elif status == "working":
            pass

    def readSwitch(self, level):
        if (self.callReadSwitch):
            self.callReadSwitch(level)

    def readRelay(self, level):
        if self.index < (self.size - 1):
            self.index = self.index + 1
            self.pro.send({"cmd":"reset","data":[1,1,1]})
            time.sleep(1)
            self.pro.send(self.data[self.index])
        else:
            self.data = []
            self.index = 0
            self.size = 0
            if (self.callHome):
                self.callHome()

    def readRaw(self, str):
        print ("raw " + str)

    def readTimeOut(self, process):
        print("reset time is " + str(process.process_time))
        self.pro.send({"cmd":"reset","data":[1,1,1]})
        time.sleep(1)
        self.pro.send(self.data[self.index])

    def __init__(self, port):
        self.pro = Protocol(port)
        # pro.on('raw',readRawSerial)
        self.pro.setDebugMode(True)
        self.pro.setTimeoutProcess(6.5)
        self.pro.on('raw',self.readRaw)
        self.pro.on('status', self.readStatus)
        self.pro.on('switch_box', self.readSwitch)
        self.pro.on('relay', self.readRelay)
        self.pro.on('process_timeout', self.readTimeOut)

        self.callHome = None
        self.callReadSwitch = None
        self.callStart = None

        self.path = Path()
        self.size = 0
        self.index = 0
        self.data = 0


    def sendPath(self, cmd):
        if (self.callStart):
            self.callStart()
        self.data, self.size = self.path.Path(cmd)
        self.pro.send({"cmd":"reset","data":[1,1,1]})
        time.sleep(1)
        self.pro.send(self.data[self.index])
    
    def setCallOnHome(self, call):
        if (call):
            self.callHome = call

    def setCallOnReadSwitch(self, call):
        if (call):
            self.callReadSwitch = call

    def setCallStart(self, call):
        if (call):
            self.callStart = call

