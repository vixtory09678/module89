import serial
import threading
import json
import struct
import time

class ProcessRobot(object):
    def __init__(self):
        self.process_time = 0.0
        self.process_timeOut = 0.0

class Protocol(object):

    def __init__(self, comport = 'COM13'):
        self.ser = serial.Serial(comport, 115200)
        self.ser.timeout = 1

        self.process = ProcessRobot()

        # set thread
        self.thread = threading.Thread(target=self.readSerial,args=(self.ser,))
        self.thread.daemon = True
        self.thread.start()

        # set callback
        self.callRaw = None
        self.callSwitch = None
        self.callStatus = None
        self.callRelay = None
        self.callProcessTimeOut = None
        self.debug = False

        #time variable
        self.startTime = 0.0
        self.endTime = 0.0
        self.TIMEOUT = 6.0
        self.isStartTimer = False

    def __del__(self):
        if (self.thread.isAlive()):
            self.thread.join()
        if (self.ser.is_open):
            self.ser.close()

    def setDebugMode(self,debug):
        self.debug = debug

    def setTimeoutProcess(self, time_out):
        self.TIMEOUT = time_out

    def on(self,mode='read',call = None):
        if (mode == 'raw'):
            if (call):
                self.callRaw = call
        elif (mode == 'switch_box'):
            if (call):
                self.callSwitch = call
        elif (mode == 'status'):
            if (call):
                self.callStatus = call
        elif (mode == 'relay'):
            if (call):
                self.callRelay = call
        elif (mode == 'process_timeout'):
            if (call):
                self.callProcessTimeOut = call
        else:
            if (self.debug):
                print("error event callback name")

    def is_json(self, myjson):
        try:
            json_object = json.loads(myjson)
        except ValueError:
            return False, None
        return True, json_object

    def readSerial(self, ser):
        while(1):
            if (ser.in_waiting):
                readSerial = ser.readline().decode('ascii')

                complete, jsonObj = self.is_json(readSerial)

                if (complete == False): continue

                if(self.callRaw):
                    self.callRaw(readSerial)

                if (jsonObj["cmd"] == 'status'):
                    if (self.callStatus):

                        if jsonObj["data"] == "working":
                            self.startTime = time.time()
                            self.process.process_time = 0
                            self.isStartTimer = True
                        if jsonObj["data"] == "all stop":
                            self.endTime = time.time() - self.startTime
                            self.process.process_time = self.endTime
                            print("process time is " + str(self.process.process_time))
                            self.isStartTimer = False


                        self.callStatus(jsonObj["data"])


                elif (jsonObj["cmd"] == 'relay'):
                    if (self.callRelay):
                        self.callRelay(jsonObj["data"])
                elif (jsonObj["cmd"] == 'switch_box'):
                    if (self.callSwitch):
                        self.callSwitch(jsonObj["data"])
            
            if (self.isStartTimer == True):
                if (time.time() - self.startTime) > self.TIMEOUT :
                    if (self.callProcessTimeOut):
                        self.process.process_time = time.time() - self.startTime
                        self.callProcessTimeOut(self.process)
                        self.isStartTimer = False
  

    def send(self, data):
        # convert into JSON:
        y = json.dumps(data)
        y = y + '\n'

        # the result is a JSON string:
        out = bytes(y,'utf-8')
        if (self.debug):
            print(y)
        # send data to low level
        self.ser.write(out)