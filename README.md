<h1 align="center">
  OpenCPU Demo
</h1>

<h4 align="center">
  👋 Lierda NB-IoT Team
</h4>

<p align="center">
  <!-- <a href="https://travis-ci.org/lierda-nb-iot-team/OpenCPUdemo"> -->
    <img alt="Progress Status" src="http://progressed.io/bar/90?title=progress">
  <!-- </a> -->
  <a href="https://github.com/lierda-nb-iot-team/OpenCPUdemo/releases/tag/v1.0">
    <img alt="Version" src="https://img.shields.io/github/release/lierda-nb-iot-team/OpenCPUdemo.svg">
  </a>
</p>

<!-- <h3 align="center">
  <a href="./README_EN.md">
  Change to English
</h3> -->


# 1 OpenCPU 相关例程说明
#### 写在前面  
以下例程基于LiteOS设计，LiteOS入门操作指南请移步[LiteOS内核教程](https://liteos.github.io/tutorials/kernel/)

## 目录构成:

*每个工程文件夹内包含`.fwpkg固件包`可直接烧录看现象*

| 目录 | 内容 |
| :----------- | :--------------- |
| OpenCPU Peripheral   | 包含各种传感器和外设的使用例程|
| Network Communication | 包含网络通信例程|
| Application Demo| 包含综合应用例程|
| Doc | 包含所有使用上的详细说明|
| Tool Chain | 包含固件升级以及UElog查看等工具|

## OpenCPU Peripheral目录包含:

| 目录              | 内容 |
| :--------------- | :---------------------------- |
| VBAT voltage acquisition| Vbat脚电压相关使用例程及说明文档|
| Temperature and humidity sensor data acquisition| HDC1000温湿度传感器相关使用例程及说明文档|
| Acceleration sensor| LIS3DH三轴加速度传感器相关类使用例程及说明文档|
| LED flashing| LED灯使用例程及说明文档 |
| Light sensor| 光线传感器使用例程及说明文档 |
| GPS sensor data acquisition| GPS芯片相关使用例程及说明文档|
| Button| 按键中断相关使用例程及明文档|
| Analog measurement（ADC）| ADC采样相关使用例程及说明文档|
| Analog output（DAC）| DAC输出相关使用例程及说明文档|
| Low power adaptation | 低功耗使用例程及说明文档 |
| Breathing light | 呼吸灯PWM输出使用例程及说明文档 |
| Flash memory | SPI读写FLASH使用例程及说明文档 |

## Network Communication目录包含: 

| 目录              | 内容 |
| :--------------- | :---------------------------- |
| Search network and Attach| 网络连接相关使用例程及说明文档|
| UDP send and receive data| UDP数据收发相关使用例程及说明文档|
| TCP send and receive data| TCP数据收发相关使用例程及说明文档|
| LwM2M send and receive data| LWM2M数据收发相关使用例程及说明文档|
| FOTA adaptation and testing| FOTA适配相关使用例程及说明文档|

## Application Demo目录包含: 

| 目录              | 内容 |
| :--------------- | :---------------------------- |
| Temperature and humidity collector simulation| 温湿度采集器应用相关使用例程及说明文档|
| Street light simulation| 路灯应用相关使用例程及说明文档|
| Tracker simulation| 定位器应用相关使用例程及说明文档|
