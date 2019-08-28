# 低功耗适配例程
## 写在前面
本OpenCPU例程基于Lierda NB86-G EVK设计，集成NB86-G模组（基于海思Boudica 150 Hi2115芯片方案），EVK集成多种传感器：
- 温湿度
- 光强度
- 加速度
- GPS

支持两种NB-IoT应用的开发方式：
- 传统方式：传感器+MCU+NB86-G模组，即MCU作为应用载体，同时控制传感器采集状态并通过NB86-G模组收发数据
- OpenCPU：传感器+NB86-G模组，NB86-G模组同时作为应用软件及通信能力的载体，模组直接控制传感器采样，并将采集到的数据经过应用处理后与云端联动
> **OpenCPU开发方式相对于传统方式具有诸多优势**
> - 降低BOM成本，不再需要MCU
> - 降低功耗
> - 提高终端安全性
> - 提高集成度，对小尺寸终端设计有很大帮助
> - 模组内的应用可直接通过模组FOTA能力进行差分升级，方便后期维护
### 相关资料
NB86-G EVK资料获取请移步：[NB86 EVK相关资料集](http://bbs.lierda.com/forum.php?mod=viewthread&tid=86&page=1&extra=&_dsign=91f69885)  
NB86-G EVK获取请移步：[NB86 EVK](https://item.taobao.com/item.htm?spm=a1z10.5-c.w4002-21080581561.13.565878241Htgvt&id=578262725191)<br>
LiteOS入门操作指南请移步[LiteOS内核教程](https://liteos.github.io/tutorials/kernel/)
### Lierda NB86 EVK
 ![NB86EVK](../../Picture/NB86EVK黑色.png)  
### 1 简介

本例程为低功耗适配的控制例程，对应目录如下：

- ProjectLight
  - src
    - lib
      - Demo

### 2 要点

- 操作系统任务阻塞相关接口的常规用法
- 低功耗适配的注意事项

### 3 实验条件

硬件：Lierda NB86 EVK/NB86-G模组  
软件：USB转串口驱动  
集成开发环境：Eclipse  

### 4 电气连接
![三轴传感器连接示意图](../../Picture/三轴1.png)  
![三轴传感器连接示意图](../../Picture/三轴2.png)  

### 5 实验步骤
5.1 将`ProjectLight`文件夹导入eclipse，导入方法详见[《Lierda NB-IoT模组 OpenCPU DemoCode说明文档》
](../../Doc/基本资料/Lierda_NB-IoT模组OpenCPU_DEMO说明文档V1.8_190403.pdf)
5.2 打开`Demo`文件夹下示例代码：  
![示例代码](../../Picture/光感示例代码1.png)

5.3 例程详解  
5.3.1 涉及库函数及对应头文件  
- 三轴传感器相关库函数  
头文件：  
`#include "lierdaI2C.h"`  
库函数：  
`HAL_StatusTypeDef lierdaI2CInit(I2C_HandleTypeDef *hi2c);	//I2C初始化`  

`I2C_RET lierdaI2CWrite(I2C_HandleTypeDef *hi2c,uint8 i2c_slave_addr,uint8 *data,uint8 data_len);	//I2C写数据函数`  

`I2C_RET lierdaI2CRead(I2C_HandleTypeDef *hi2c,uint8 i2c_slave_addr,uint8 *data, uint8 data_len); 	//I2C读取数据函数`  
- 操作系统相关库函数  
头文件：  
`#include "cmsis_os2.h"`  
库函数：  
`osMessageQueueId_t osMessageQueueNew (uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr);//创建队列`  
`osStatus_t osMessageQueuePut (osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout);//发送队列`  
`osStatus_t osMessageQueueGet (osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout);//接收队列`  


5.3.3  编译工程，如没有错误则编译通过：  
![编译结果](../../Picture/编译结果.jpg)  
编译成功后，烧写固件，烧写过程详见[《Lierda NB-IoT模组 OpenCPU DemoCode说明文档》
](../../Doc/基本资料/Lierda_NB-IoT模组OpenCPU_DEMO说明文档V1.8_190403.pdf)
5.3.4 烧写完毕，打开串口助手，选择AT串口，波特率为9600，可看到如下结果：  
![结果展示](../../Picture/低功耗结果.png)

### 6 注意事项
队列的发送不可在中断中进行。
 

### 7 参考资料

| 技术论坛 |
| :----------- |
| [物联网开发者社区](http://bbs.lierda.com) |
