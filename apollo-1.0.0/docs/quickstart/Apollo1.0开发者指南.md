# Apollo 1.0 开发者快速开始指南 
## 内容
*[关于这篇指南]（#关于这篇指南）
*[介绍]（#介绍）
*[编译Apollo的内核]（#编译Apollo的内核）
*[访问Apollo dev 容器]（#访问Apollo dev 容器）
*[编译Apollo ROS]（#编译Apollo ROS）
*[发布]（#发布）

# 关于这篇指南
*Apollo 1.0开发者快速开始，提供基本介绍，编译Apollo内核，ROS，和apollo。
## 文档规约

下表列出了本文档中使用的归约：

| **Icon**                            | **描述**                                   |
| ----------------------------------- | ---------------------------------------- |
| **粗体**                              | 重要                                       |
| `等宽字体`                              | 代码，类型数据                                  |
| _斜体_                                | 文件标题，章节和标题使用的术语                          |
| ![info](images/info_icon.png)       | **Info**  包含可能有用的信息。忽略信息图标没有消极的后果        |
| ![tip](images/tip_icon.png)         | **Tip**. 包括有用的提示或可能有助于您完成任务的捷径。          |
| ![online](images/online_icon.png)   | **Online**. 提供指向特定网站的链接，您可以在其中获取更多信息     |
| ![warning](images/warning_icon.png) | **Warning**. 包含**不**能忽略的信息，或者执行某个任务或步骤时，您将面临失败风险 |
# 介绍
假设您已阅读并执行配套指南* Apollo 1.0快速入门指南*中的说明，以设置基本环境。 使用本指南构建自己的Apollo Kernel，ROS和Apollo版本。 还有关于如何将自己的Apollo容器发布给可能希望以您开发的内容为基础的其他人的说明。 强烈建议您在Apollo预先指定的开发Docker容器中构建所有组件（Apollo Kernel，ROS和Apollo）。
# 构建Apollo的内核
车辆中的Apollo运行时需要[Apollo Kernel]（https://github.com/ApolloAuto/apollo-kernel）。 强烈建议您安装预构建的内核。
# 使用预先构建的Apollo Kernel
你可以通过下面的命令安装构建内核
1.在github发布区域上下载已发布的包
```
https://github.com/ApolloAuto/apollo-kernel/releases
```
2.安装内核
在下载到发布的包之后
```
tar zxvf linux-4.4.32-apollo-1.0.0.tar.gz
cd install
sudo ./install_kernel.sh
```
3.构建ESD-CAN驱动的源码
你需要通过[ESDCAN-README.md](https://github.com/ApolloAuto/apollo-kernel/blob/master/linux/ESDCAN-README.md)文件进行ESD-CAN构建。
4.重启系统
'''
reboot
'''
## 构建属于自己的内核
如果你改变了内核，或者重新构建了内核不是你的平台需要的内核，你可以构建属于自己的内核，通过一下的步骤：
1.从仓库Clone代码
```
git clone https://github.com/ApolloAuto/apollo-kernel.git
cd apollo-kernel
```
2.构建ESD-CAN驱动源码通过[ESDCAN-README.md](https://github.com/ApolloAuto/apollo-kernel/blob/master/linux/ESDCAN-README.md)文件。
3.通过下面命令构建内核
```
bash build.sh
```
4.以与使用预先构建的Apollo内核相同的方式安装内核。
# 访问Apollo dev 容器
1.请依据[快速开始指南](https://github.com/ApolloAuto/apollo/blob/master/docs/quickstart/apollo_1_0_quick_start.md) clone Apollo的源代码。
！[tip]（images / tip_icon.png）在以下部分中，假设Apollo目录位于`$ APOLLO_HOME`中。
2.Apollo提供了一个构建环境Docker镜像：`dev-latest`。 运行以下命令以使用构建镜像启动容器：
```
cd $APOLLO_HOME
bash docker/scripts/dev_start.sh
```
3.运行以下命令以登录容器：
```
bash docker/scripts/dev_into.sh
```
在容器中，默认目录位于`/ apollo`中，其中包含已安装的源代码库。
# 构建Apollo ROS
从下面的路径检测Apollo ROS [github source](https://github.com/ApolloAuto/apollo-platform):
```bash
git clone https://github.com/ApolloAuto/apollo-platform.git apollo-platform
cd apollo-platform/ros
bash build.sh build
```

# 构建Apollo
在进行构建之前，请在下面的路径文件中获取ESD-CAN库[ESD CAN README](https://github.com/ApolloAuto/apollo/blob/master/third_party/can_card_library/esd_can/README.md).
运行下面的命令：
```bash
cd $APOLLO_HOME
bash apollo.sh build
```
# 发布
Apollo使用Docker镜像发布包。 **对于高级开发人员**：您可以生成新的Docker镜像以在实际车辆中进行测试。 Apollo已经建立了一个基础Docker镜像环境来测试Apollo构建。
这个镜像叫做`run-env-latest`.
1.运行下面的命令：
```
bash apollo.sh release
```
发布命令生成一个发布目录，其中包含：

 -  ROS环境
 - 运行脚本
 - 二进制文件
 - 依赖共享库（`.so`文件）
2.打开一个新终端并在Docker之外的Apollo源目录中运行以下命令：
```
cd $APOLLO_HOME
bash apollo_docker.sh gen
```
这个命令在发布路径下生成一个新的docker镜像
这个发布镜像的标签的名称`release-yyyymmdd_hhmm`.已存在的发布镜像的标签`release-latest`总是指向最新版本。
使用从容器外部设置的Docker注册表在线推送您的版本映像：

```
cd $APOLLO_HOME
bash apollo_docker.sh push
```
该命令将新构建的Docker镜像推送到Docker注册表版本。 要设置新的Docker注册表，请参阅[本页]（https://docs.docker.com/registry）。
