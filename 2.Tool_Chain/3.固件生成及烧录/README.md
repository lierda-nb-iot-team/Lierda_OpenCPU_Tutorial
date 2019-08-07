#  固件生成及烧录
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
## 1 Package包生成

由生成Package包的命令比较复杂，这里只对批处理的方式做说明，命令行方式详见《Lierda NB-IoT模组OpenCPU DEMO说明文档》第4小节。  
### 1.1	UpdatePackage软件安装
点击安装UpdatePackage固件生成软件。
![图 固件生成01](../../Picture/固件生成01.png)  
NOTE: 需要安装与工程所对应的UpdatePackage版本  
### 1.2	Package包生成  
1、工程文件，进入fwpkg文件，找到make_fwpkg.exe文件如图，其中底包SourceFirmware.fwpkg文件根据自己的所使用的的硬件选择，这里提供B500SP1X0A固件底包，若跟换底包需将底包名改为“SourceFirmware.fwpkg”。 
 ![图 固件生成02_1](../../Picture/固件生成02_1.png)   
2、点击运行该批处理文件，若无异常出现则表示固件生成成功，如图 
 ![图 固件生成03_1](../../Picture/固件生成03_1.png) 
3、make_fwpkg.exe文件运行完成后，在fwpkg_new文件夹下就会生成相应的固件如图
 ![图 固件生成04](../../Picture/固件生成04.png) 


## 2固件烧录
### 2.1UEUpdaterUI软件安装
![图 固件烧录01](../../Picture/固件烧录01.png)  
点击安装UEUpdaterUI软件。  
`NOTE：需要安装与工程所对应的UEUpdaterUI版本。`

### 2.2固件烧录
选择1.2小节生成固件，UEUpdaterUI软件中勾选write KV，点击update进行烧录如图。
![图 固件烧录02](../../Picture/固件烧录02.png)  
`NOTE:烧录前需保证生成的固件是和开发的模组硬件相符合（Package包生成时保证底包无误）。若不符合可能会出现异常，若出现异常请参考《Lierda NB-IoT模组OpenCPU DEMO说明文档》5小节进行烧录。`  

## 3 参考资料  
| 技术论坛 | OpenCPU资料 | NB86 EVK资料
| :----------- | :----------- | :----------- |
| [物联网开发者社区](http://bbs.lierda.com) |  [OpenCPU基本资料集](https://github.com/lierda-nb-iot-team/Lierda_OpenCPU_SDK) |  [NB86 EVK基本资料集](https://github.com/lierda-nb-iot-team/Lierda_NB86_EVK) |
