import numpy as np
import serial
import json
import time

vibration_threshold=15
ser = serial.Serial('/dev/cu.usbmodem14511')
ser.flushInput()

data_z=[]
readings=[]
data={}
while True:
    if len(data_z) ==36:
        stdev=np.std(data_z)
        readings.append(stdev)
        if len(readings)==5:
            median_reading=np.median(readings)
            if median_reading>vibration_threshold:
                ser.write(b'1')
                data['Status']='Dishwasher Running'
                data['Timestamp']=int(time.time())
                with open('data.json', 'w') as outfile:
                    json.dump(data, outfile)
            readings=[]
        data_z=[]
    data_z.append(float(str(ser.readline().strip(), 'ascii').split(",")[2]))
