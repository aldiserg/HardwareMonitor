# Importing Libraries
import serial
import time
import nvidia_smi
import psutil

arduino = serial.Serial(port='/dev/ttyUSB1', baudrate=9600, timeout=.1)

nvidia_smi.nvmlInit()
while True:
    handle = nvidia_smi.nvmlDeviceGetHandleByIndex(0)
    gpu = nvidia_smi.nvmlDeviceGetUtilizationRates(handle)
    
#   cpuJson = str(psutil.sensors_temperatures())
#   cpuTemp = int(cpuJson.split(",")[1][9:11])

    ram = int(psutil.virtual_memory().percent)

    cpu = int(psutil.cpu_percent())

    array = [cpu, gpu.gpu, gpu.memory, ram]
    print(f'cpu: {cpu}%, gpu: {gpu.gpu}%, gpuMem: {gpu.memory}%, ram: {ram}%')

    data = bytearray(array)
    arduino.write(data)
    print(arduino.readline())
    time.sleep(1)
    
