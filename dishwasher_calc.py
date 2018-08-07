import numpy as np
import serial

vibration_threshold=20
ser = serial.Serial('/dev/cu.usbmodem14411')
ser.flushInput()

data_z=[]
readings=[]
while True:
    if len(data_z) ==10:
        stdev=np.std(data_z)
        readings.append(stdev)
        if len(readings)==10:
            median_reading=np.median(readings)
            if median_reading>vibration_threshold:
                ser.write(b'1')
                print(median_reading)
            readings=[]
        data_z=[]
    data_z.append(float(str(ser.readline().strip(), 'ascii').split(",")[2])*1000)
