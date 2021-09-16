# HardwareMonitor Arduino + python
Analog of https://github.com/AlexGyver/PCdisplay for linux OS. Just display (GPU is NVidia only)

![How it looks like](hhttps://github.com/aldiserg/HardwareMonitor/blob/main/view.png?raw=true)

# Setup
Upload sketch to arduino via arduino ide

Install libs:
```
pip3 install nvidia_smi
```
Check tty device path

Run for check allright
```
python3 hwm.py
```

Copy hwm.service and start + add to startup
```
cp hwm.service /etc/systemd/system/hwm.service
systemctl enable hwm --now
```
