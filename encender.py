import time
from flux_led import WifiLedBulb

bulbipaddress = "192.168.1.66"

def main():
    bulb = WifiLedBulb(bulbipaddress)
    print (bulb)
    bulb.refreshState()
    redcolor, greencolor, bluecolor = bulb.getRgb()
    bulbstatus = bulb.isOn()
    brightnessval = bulb.brightness

    '''print("Turn off bulb")
    bulb.turnOff()
    time.sleep(2)'''
    print("Turn on bulb")
    bulb.turnOn()
    '''time.sleep(2)
    print("Set Red color + 20% brightness")
    bulb.setRgb(255,0,0, brightness=20)
    bulb.set_levels(255, 0, 0, 0, 0, True, 250, 3)
    time.sleep(2)
    print("Set Green color + 50% brightness")
    bulb.setRgb(0,255,0, brightness=50)
    time.sleep(2)
    print("Set Blue color + 100% brightness")
    bulb.setRgb(0,0,255, brightness=100)
    time.sleep(2)
    print("Set default color")
    bulb.refreshState()
    bulb.setRgb(redcolor, greencolor, bluecolor, brightness=brightnessval)'''
    
if __name__ == '__main__':
    main()