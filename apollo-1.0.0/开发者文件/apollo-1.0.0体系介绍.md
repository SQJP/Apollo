## apollo-1.0.0 主要功能
通过交互界面采集GPS导航点，实现了一个在封闭的、平坦的地面上对横向和纵向的控制，也就是寻迹。
## apollo-1.0.0搭建的环境
apollo-1.0.0软件系统是安装在ubuntu14.04.3系统下，使用docker来部署apollo的运行环境，应用ros实现模块间的信息传递，并对ros内核进行了修改，使其实时性更高。apollo-1.0.0项目包含了10多种文件格式，其中配置文件包含sh、workspace、BUILD、.proto、conf、dockfile、JSON、XML等。sh文件是apollo环境构建的主要指令，其中包含了shell脚本和Linux文件、文档操作命令。BUILD是文件编译格式，是采用bazel作为代码编译构建工具，编译项目中的各个模块，所以每个源码文件夹下有一个BUILD文件。workspace用于指定当前文件夹就是一个Bazel的工作区。.proto是便于文件和磁盘间处理数据格式而开发的，避免了数据间格式转化。在每一个模块中几乎都会包含一个conf文件夹，里边是XXX.conf里边是该模块的配置信息。dockfile文件包含一系列命令和参数构成的脚本，这些命令主要用于创建一个新的自定义镜像，这里需要说的是Apollo本身是一个docker镜像文件，是通过dockfile构建的。JSON和xml是hwi(人机交互)模块下web开发时用到的数据结构。
## 为什么要使用docker
首先docker是一个封闭的环境，是用来搭建工程镜像的，其可以在dockerhub上下载官方的镜像，也可以修改自定义镜像。其次docker便于封装镜像文件，封装后可以提供给开发者使用，方便快捷，有助于快速开发。说直白点，就是百度为了便于开发者开发，避免安装配置过程中不必要的错误，将Apollo 打包成一个镜像文件，形成傻瓜式配置，最终的目的是简化配置过程。
## apollo-1.0.0 组成文件介绍
1.docker文件夹主要是配置项目的docker环境，包括安装配置的shell脚本以及构建apollo镜像的dockerfile文件。     
2.docs文件夹存放的是apollo官方给出的指导性文件，包括Apollo软硬件系统搭建，如何添加车辆，如何加载镜像，如何添加GPS接收器，咋样启动DREAMVIEWER等。  
3.modules是Apollo无人车各功能模块的代码部分，主要包含了以下文件：  
（1）canbus -汽车CAN总线控制模块，接收控制指令，同时给控制模块control发送车身状态信息。  
（2）common - 公共源码模块。包括如日志，工厂模式的实现，日志系统，监控模块，数学算法等。  
（3）control -控制模块。基于决策规划的输出路径及车身的状态使用不同的控制算法来输出控制命令，如转向、加速、刹车等。  
（4）decision - 决策模块。  
（5）dreamview -可视化模块。查看规划的轨迹及实时的转向刹车油门信息  
（6）drivers -驱动模块。各种传感器驱动。  
（7）hmi-人机交互模块。  
（8）localization-定位模块  
（9）monitor -监控模块。监控硬件状态，同时把状态发给交互界面。  
（10）perception -感知模块。包括视觉、毫米波、激光雷达。  
（11）planning    -局部决策规划模块。  
（12）prediction  -预测模块。输出感知的障碍物信息及自定位信息输出障碍物未来的轨迹。  
（13）tools       -通用监控与可视化工具  
4.scripts 存放Apollo各模块安装配置脚本。  
5.third_party存放apollo构建过程中用到的第三方库的构建文件。  
6.tools 编译工具文件夹  
7.apollo.doxygen 是Apollo程序中的批注转换成为说明文件。  
8.是Apollo构建文件。  
9.Apollo_docker构建文件。  
10.AUTHORS.md 作者介绍。  
11.Apollo项目编译格式文件  
12.CPPLINT.cfg  
13.LICENSE  
14.README.md 项目说明文档  
15.WORKSPACE指定bazel构建的第三方库文件  

