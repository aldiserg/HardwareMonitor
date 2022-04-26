# Importing Libraries
from serial import Serial
import time
import psutil
import json
import pyamdgpuinfo

arduino = Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=.1)
n_devices = pyamdgpuinfo.detect_gpus()
while True:
    gpu = pyamdgpuinfo.get_gpu(0)
    gpuTemp = int(gpu.query_temperature())
    gpuUsage = int(gpu.query_load()*100)
    gpuMem = int(gpu.query_vram_usage())
    gpuMemPercentUsage = int((gpuMem/1000000)/120)

    cpuJson = json.dumps(psutil.sensors_temperatures())
    cpuTemp = int(json.loads(cpuJson)["k10temp"][0][1])

    ram = int(psutil.virtual_memory().percent)

    cpu = int(psutil.cpu_percent())

    array = [cpu, gpuUsage, gpuMemPercentUsage, ram, cpuTemp, gpuTemp]
    print(f'cpu: {cpu}%, gpu: {gpuUsage}%, gpuMemPercentUsage: {gpuMemPercentUsage}%, ram: {ram}%, cpuTemp: {cpuTemp}%, gpuTemp: {gpuTemp}%')

    data = bytearray(array)
    arduino.write(data)
    time.sleep(1)
    
