# HardwareMonitor Arduino + python
Analog of https://github.com/AlexGyver/PCdisplay for linux OS. Just display (NVidia GPU only)

![How it looks like](https://github.com/aldiserg/HardwareMonitor/blob/main/view.png?raw=true)

# Setup
Upload sketch to arduino via arduino ide

Install libs + add access:

For NVIDIA gpu
```
pip3 install pyserial psutil nvitop
```

For AMD gpu
```
pip3 install pyserial psutil pyamdgpuinfo
```

Add permistion to /dev/ttyUSBx
```
sudo gpasswd -a username tty
sudo gpasswd -a username uucp
```
Check tty device path
```
ls -l /dev/ttyUSB*
```
Run for check allright
```
python3 hwm.py
```

Copy hwm.service and start + add to startup
```
sudo cp hwm.service /etc/systemd/system/hwm.service
systemctl enable hwm --now
```
