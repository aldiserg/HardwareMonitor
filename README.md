# HardwareMonitor Arduino + python
Analog of https://github.com/AlexGyver/PCdisplay for linux OS. Just displayed system perfomance info 

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

or

sudo chown username:usergroup /dev/ttyUSBx
```
Check tty device path
```
ls -l /dev/ttyUSB*
```
Run for check allright
```
python3 hwm.py
```

Change hwm.service to correct user and path to script, after that copy and start service (will be added to startup of system)
```
sudo cp hwm.service /etc/systemd/system/hwm.service
systemctl enable hwm --now
```
