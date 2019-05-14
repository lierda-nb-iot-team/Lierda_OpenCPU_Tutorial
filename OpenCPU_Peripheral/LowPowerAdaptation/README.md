# 低功耗适配例程

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
![DAC示意图](../../Picture/DAC示意图1.png)

### 5 实验步骤
5.1 将`ProjectLight`文件夹导入eclipse，导入方法详见[《Lierda NB-IoT模组 OpenCPU DemoCode说明文档》
](../../Doc/基本资料/Lierda_NB-IoT模组OpenCPU_DEMO说明文档V1.8_190403.pdf)
5.2 打开`Demo`文件夹下示例代码：  
![示例代码](../../Picture/光感示例代码1.png)

5.3 例程详解  
5.3.1 涉及库函数及对应头文件  
- DAC相关库函数  
头文件：  
`#include "lierdaDAC.h"`  
库函数：  
`LIERDA_DAC_RET lierdaDACInit(void);//DAC初始化`  
`LIERDA_DAC_RET lierdaDACWriteRaw(uint32 value);//DAC输出`  
`LIERDA_DAC_RET lierdaDACConnect(uint32 aio);//初始化输出的IO口`  
`LIERDA_DAC_RET lierdaDACSetRange(DAC_VOLTAGE_RANGE range);//设置电压范围`  

5.3.3  编译工程，如没有错误则编译通过：  
![编译结果](../../Picture/编译结果.jpg)  
编译成功后，烧写固件，烧写过程详见[《Lierda NB-IoT模组 OpenCPU DemoCode说明文档》
](../../Doc/基本资料/Lierda_NB-IoT模组OpenCPU_DEMO说明文档V1.8_190403.pdf)
5.3.4 烧写完毕，打开串口助手，选择AT串口，波特率为9600，可看到如下结果：  
![结果展示](../../Picture/DAC结果展示.png)

### 6 注意事项

注意在DAC输出前需要设定电压范围和连接到要输出的IO口  

### 7 参考资料

| 技术论坛 |
| :----------- |
| [物联网开发者社区](http://bbs.lierda.com) |