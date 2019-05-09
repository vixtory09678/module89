from Manual_Path import *

def onHome():
    print("hello home")

def onReadSwitch(level):
    print("switch is " + level)

def onStart():
    print("hello start")

manual = Manual_Path('COM25')
manual.setCallOnHome(onHome)
manual.setCallOnReadSwitch(onReadSwitch)
manual.setCallStart(onStart)

manual.sendPath(1114)

while(1):
    pass

