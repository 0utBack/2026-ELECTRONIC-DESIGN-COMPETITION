# 2026电赛H题代码

[![Platform](https://img.shields.io/badge/platform-TI_MSPM0-CC0000.svg?logo=texasinstruments&logoColor=white)]()

##项目简介
本次代码主用采用8路灰度传感器解决基础巡线问题，配合DBS300舵机驱动摆杆装置使钢珠居中于摆杆装置。通过串口接收上位机下发的四字节位置信息（50Hz），钢球相对中点的ΔPosition和每一帧的移动速度ΔSpeed（帧头0XAA）。
主要控制代码采用同步双串PID(位置环、小球速度环)。
通过实测无论载具在发生横向、纵向运动时，钢球位置偏移不超±2CM。

##硬件选型
- MSPM0G3507官方评估板（主控） 
- 亚博K230(上位机)
- TB6612双路有刷驱动模块
- 8路灰度传感器

## 📁 目录结构
```text
project/
├── Control/        # 电机、舵机控制代码
├── Encoder/        # 编码器
├── GYRO/           # 废弃
├── Key/            # 按键状态机
├── MPU6050/        # 陀螺仪驱动
├── OLED/           # OLED 硬件I2C驱动
├── Sensor/         # 八路灰度传感器
├── sys/            # 一些delay、debug代码
