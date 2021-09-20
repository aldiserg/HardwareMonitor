# Importing Libraries
from serial import Serial
import time
from nvitop import Device
import psutil
import json

arduino = Serial(port='/dev/ttyUSB1', baudrate=9600, timeout=.1)
nvidia0 = Device(0)
while True:
    gpu = nvidia0.as_snapshot()
    gpuTemp = gpu.temperature
    gpuUsage = gpu.gpu_utilization
    gpuMem = int(gpu.memory_utilization)

    cpuJson = json.dumps(psutil.sensors_temperatures())
    cpuTemp = int(json.loads(cpuJson)["k10temp"][0][1])

    ram = int(psutil.virtual_memory().percent)

    cpu = int(psutil.cpu_percent())

    array = [cpu, gpuUsage, gpuMem, ram, cpuTemp, gpuTemp]
    print(f'cpu: {cpu}%, gpu: {gpuUsage}%, gpuMem: {gpuMem}%, ram: {ram}%, cpuTemp: {cpuTemp}%, gpuTemp: {gpuTemp}%')

    data = bytearray(array)
    arduino.write(data)
    time.sleep(1)
    
