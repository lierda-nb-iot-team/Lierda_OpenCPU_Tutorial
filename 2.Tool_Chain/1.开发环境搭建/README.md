#  OpenCPU 环境搭建说明
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
 
## 1 编译器 -gcc
B500 编译调用 的 GCC 编译器 版本与 B300SP2&B300SP5 不一样，若要支持B300SP2&B300SP5 和 B500SP1 则需要安装两个不同版本的 GCC 编译器。具体的安装方法如下：  
### 1.1 B300SP2&B300SP5  
下载 [GCC 编译器安装文件](https://launchpad.net/gcc-arm-embedded/+download)
进入软件下载界面下载所需的软件安装包如图 1-1  

![图 1-1](../../Picture/图1-1.png)  

点击下载好的软件进行安装，需要注意的是安装完成后，确保选择了“添加环境变量的路径”选项如图 1-2  

![图 1-2](../../Picture/图1-2.png)  

进入windows 命令行输入 arm-none-eabi-gcc -v 检查 gcc 版本，判断 gcc 是否安装成功，如图 1-3  

![图 1-3](../../Picture/图1-3.png)  

如果查不到版本信息，检查环境变量是否添加成功如图 1-4.如果环境变量里查不到 gcc 的安装路径，请根据自己 gcc 安装的路径添加环境变量。  

![图 1-4](../../Picture/图1-4.png)  

### 1.2 B500SP1
下载[GCC 编译器安装文件](https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/7-2017q4/gcc-arm-none-eabi-7-2017-q4-major-win32.zip)并安装，只需将下载的zip 文件解压放到 C 盘的根目录即可，如图 1-5  

![图 1-5](../../Picture/图1-5.png)  

然后，添加环境变量 ` C:\gcc-arm-none-eabi-7-2017-q4-major-win32\bin `
如图 1-6  

![图 1-6](../../Picture/图1-6.png)

## 2 Python 2.7  
### 2.1 Python 2.7 安装  
Scons 是一个用于基于 Python2.7 的软件构建的工具。确保在安装 Scons 之前安装 [Python 2.7](https://www.python.org/downloads/release/python-2710/)
如图 2-1  

![图 2-1](../../Picture/图2-1.png)  

点击下载好的软件进行安装，需要注意的是在安装过程中，确保选择了“添加环境变量的路径”选项如图 2-2 所示。点击下一步完成安装。

![图 2-2](../../Picture/图2-2.png)  

### 2.2 pywin32 安装
下载对应的[pywin32](https://sourceforge.net/projects/pywin32/files/pywin32/Build%20221/)

`注意：下载的版本和 Python 2.7 相对应` 

如图 2-3  

![图 2-3](../../Picture/图2-3.png)  

点击下载好的.exe 文件安装。

`注意：检查系统环境变量中是否添加了 C:\Python27\;C:\Python27\Scripts`

如果没有添加，一定要添加上去如图 2-4  

![图 2-4](../../Picture/图2-4.png)  

### 2.3. 安装 Python PyYAML 库

进入windows 命令行输入 python 检查Python 是否安装成功，如图 3-1  

![图 2-5](../../Picture/图2-5.png)  

`注意：若果没有安装成功请检查环境变量是否添加正确`

安装PyYAML 库，在命令行输入 `pip install pyyaml` 

如图 2-6  

![图 2-5](../../Picture/图2-6.png)

### 2.4 Scons 安装

下载 [Scons](https://sourceforge.net/projects/scons/files/scons/2.4.0/ )  

`注意：Scon 应该安装在 Python 的脚本文件夹(.\Python 27\Script)中`

## 3 IDE – Eclipse 安装  

`注意：检查Java 是否安装，进入命令行，输入 java -version`  

若没安装请先安装 [Java](https://www.java.com/en/download/)

如图 3-1  

![图 3-1](../../Picture/图3-1.png)  

下载 [Eclipse](https://www.eclipse.org/downloads/packages/release/mars/2/eclipse-ide-cc-developers)  

Eclipse 插件安装（Scons）  
打开Eclipse，按一下操作步骤进入 Scons 安装界面  

如图 3-2  

![图 3-2](../../Picture/图3-2.png)  

1.点击选项栏：`Help`  
2.点击help 下子选项栏：`Install New Software...`  
3.点击 `Work with` 后的 `Add`      
4.填入下列信息 `Scons http://sconsolidator.com/update`

如图 3-3  

![图 3-3](../../Picture/图3-3.png) 

5.从插件列表中为 scons 选择 Eclipse 插件  
6.单击 Next，并按照说明执行  
至此OpenCPU开发环境搭建完成，工程导入及编译见下一小节。
## 4 参考资料  

| 技术论坛 | OpenCPU资料 | NB86 EVK资料
| :----------- | :----------- | :----------- |
| [物联网开发者社区](http://bbs.lierda.com) |  [OpenCPU基本资料集](https://github.com/lierda-nb-iot-team/Lierda_OpenCPU_SDK) |  [NB86 EVK基本资料集](https://github.com/lierda-nb-iot-team/Lierda_NB86_EVK) |
