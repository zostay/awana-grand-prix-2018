# Gemma IO demo
# Welcome to CircuitPython :)

from touchio import *
from digitalio import *
from analogio import *
from board import *
#from adafruit_hid.keyboard import Keyboard
#from adafruit_hid.keycode import Keycode
import dotstar
import time
import random

# One pixel connected internally!
dot = dotstar.DotStar(APA102_MOSI, APA102_SCK, 1, brightness=0.2)

# Built in red LED
led = DigitalInOut(D13)
led.direction = Direction.OUTPUT

# Analog output on A0
aout = AnalogOut(A0)

# Analog input on A1
analog1in = AnalogIn(A1)

# Capacitive touch on A2
touch2 = TouchIn(A2)

# Used if we do HID output, see below
# kbd = Keyboard()

######################### HELPERS ##############################

# Helper to convert analog input to voltage
def getVoltage(pin):
    return (pin.value * 3.3) / 65536

# Helper to give us a nice color swirl
def wheel(pos):
    # Input a value 0 to 255 to get a color value.
    # The colours are a transition r - g - b - back to r.
    if (pos < 0):
        return [0, 0, 0]
    if (pos > 255):
        return [0, 0, 0]
    if (pos < 85):
        return [int(pos * 3), int(255 - (pos*3)), 0]
    elif (pos < 170):
        pos -= 85
        return [int(255 - pos*3), 0, int(pos*3)]
    else:
        pos -= 170
        return [0, int(pos*3), int(255 - pos*3)]

bang_step = 0
def fade(from_val, to_val):
    if bang_step < from_val:
        return 255
    elif bang_step > to_val:
        return 0
    else:
        num = bang_step - from_val
        den = to_val - from_val
        return int(255 - 255 * num / den)

######################### MAIN LOOP ##############################

def BANG_WHITE():  return 0
def BANG_FLASHY(): return 4
def BANG_YELLOW(): return 10
def BANG_RED():    return 14
def BANG_BLACK():  return 30

def BANG_DELAY():  return 60

def minn(a, b): return a if a < b else b

while True:
    bang_step += 1

    if bang_step > BANG_DELAY():
        bang_step = BANG_WHITE()
    
    if bang_step == BANG_WHITE():
        dot[0] = [255, 255, 255]
    elif bang_step <= BANG_FLASHY():
        dot[0] = [
            int(random.random()*255), 
            int(random.random()*255), 
            int(random.random()*255),
        ]
    else:
        dot[0] = [
            min(fade(BANG_WHITE(), BANG_RED()), fade(BANG_WHITE(), BANG_BLACK())),
            min(fade(BANG_WHITE(), BANG_YELLOW()), fade(BANG_WHITE(), BANG_BLACK())),
            min(fade(BANG_RED(), BANG_BLACK()), fade(BANG_WHITE(), BANG_BLACK())),
        ]
    
  # spin internal LED around!
  # dot[0] = wheel(i)
    dot.show()

    time.sleep(0.05)

  # set analog output to 0-3.3V (0-65535 in increments)
  #aout.value = i * 256

  # Read analog voltage on A1
  #print("A1: %0.2f" % getVoltage(analog1in))

  # use A2 as capacitive touch to turn on internal LED
  # if touch2.value:
  #       print("A2 touched!")
  #       # optional! uncomment below & save to have it sent a keypress
  #       #kbd.press(Keycode.A)
  #       #kbd.release_all()
  # led.value = touch2.value


  # i = (i+1) % 256  # run from 0 to 255
