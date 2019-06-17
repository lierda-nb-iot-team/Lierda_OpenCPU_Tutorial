#  工程导入及代码编译

## 1 OpenCPU 工程导入

`注意：工程的路径和工程名不能包含中文；工程的路径尽量不要太深，5 层以内`

1.点击选项栏 `File`  
2.点击 `File` 子选项栏的 `Import... `进入导入工程界面如图 3-1，点击 `c/c++`选项栏，选择  `New SCons project from existing source`  单击下一步  

![图 2-1-1](../../Picture/图2-1-1.png)

3.选择要导入的工程文件路径点击确定，填写相关信息，点击 `Finish`。  

![图 2-1-2](../../Picture/图2-1-2.png)  

## 2 代码编译
### 2.1编译相关配置
单机要编译的工程，快捷键Alt+Enter进入配置界面（或者鼠标右击要编译的工程 -> properties –>进入配置界面），点击SCons，选项框填写：target=ref-2115 如图
![图 编译说明01](../../Picture/编译说明01.png)  
### 2.2编译步骤
选中工程鼠标右击要编译的工程 --> Build Project  
`NOTE：编译之前要对写好的工程进行保存，否则编译生成的application.bin文件没被更新`  
出现‘ done building targets’表示编译成功，如图
![图 编译说明02](../../Picture/编译说明02.png)  
### 2.3常见编译出错解决办法
#### 2.3.1编译后报找不到xx.a库
若编译出错，如下图类似错误，请先Clean Project工程一下，然后在进行编译。若还是报错建议重复此操作多试几次。Clean Project工程方法：选中工程鼠标右击要Clean的工程 --> Clean Project.如图类似错误
![图 编译说明03](../../Picture/编译说明03.png)  
#### 2.3.2编译后报.py导入出错
pyyaml库导入失败，如下图，解决办法：尝试重新安装pyyaml解决问题，安装方法见《OpenCPU开发环境搭建指南》 如图类似错误
![图 编译说明04](../../Picture/编译说明04.png) 
#### 2.3.3环境变量未添加导致编译出错
若出现编译报找不到gcc编译器或者python找不到，请检查环境变量是否添加，确保环境变量添加成功。
#### 2.3.4编译后报编码问题
编译后报编码出错如下图，解决办法：工程路径中坚决不能出现中文路径，存放工程的路径不能太深，建议5层以内。如图类似错误
![图 编译说明05](../../Picture/编译说明05.png) 

至此代码导入及代码编译已经完成，固件生成及烧录见下一小节

## 7 参考资料  

| 技术论坛 | OpenCPU资料 | NB86 EVK资料
| :----------- | :----------- | :----------- |
| [物联网开发者社区](http://bbs.lierda.com) |  [OpenCPU基本资料集](https://github.com/lierda-nb-iot-team/Lierda_OpenCPU_SDK) |  [NB86 EVK基本资料集](https://github.com/lierda-nb-iot-team/Lierda_NB86_EVK) |
