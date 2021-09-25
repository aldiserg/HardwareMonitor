# HardwareMonitor Arduino + python
Analog of https://github.com/AlexGyver/PCdisplay for linux OS. Just display (NVidia GPU only)

![How it looks like](https://github.com/aldiserg/HardwareMonitor/blob/main/view.png?raw=true)

# Setup
Upload sketch to arduino via arduino ide

Install libs + add access:
```
pip3 install pyserial psutil nvitop
sudo gpasswd -a dmitry tty
sudo gpasswd -a dmitry uucp
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
