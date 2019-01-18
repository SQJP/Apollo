## 1.安装原版ubuntu 14.04
http://www.ubuntu.org.cn/download/alternative-downloads

## 2.安装对应ubuntu 14.04的indigo版ROS
http://wiki.ros.org/indigo/Installation/Ubuntu

## 3.安装Apollo Kernel
https://github.com/ApolloAuto/apollo-kernel
为运行Apollo软件提供了kernel层面的支持。
从这里下载linux-4.4.32-apollo-1.0.0.tar.gz：
https://github.com/ApolloAuto/apollo-kernel/releases
解压安装：
tar zxvf linux-4.4.32-apollo-1.0.0.tar.gz
cd install
sudo ./install_kernel.sh
重启系统。

## 4.安装Apollo本体
https://github.com/ApolloAuto/apollo
下载资源：
git clone https://github.com/ApolloAuto/apollo.git
安装docker环境：
cd ~/apollo
bash docker/scripts/install_docker.sh
先注销再重新登录，然后测试一下docker是否安装成功：
docker ps
设置环境：
bash docker/scripts/dev_start.sh
bash docker/scripts/dev_into.sh
编译：
bash apollo.sh build

## 5.安装Apollo ROS支持
https://github.com/ApolloAuto/apollo-platform
相对于原版ROS，做出了如下改进：
。增强了ROS的去中心化特性；
。基于共享内存的更高效的通信；
。支持Protobuf；
从这里下载ros-indigo-apollo-1.0.0.x86_64.tar.gz：
https://github.com/ApolloAuto/apollo-platform/releases
解压缩：
tar zxvf ros-indigo-apollo-1.0.0.x86_64.tar.gz
将解压后的文件夹ros拷贝到apollo工程中：
rsync -av ros/ ~/apollo/third_party/ros_x86_64
source ~/apollo/third_party/ros_x86_64/setup.bash



##6.运行Apollo
cd ~/apollo
bash scripts/hmi.sh
在浏览器输入http://localhost:8887后回车，在Debug中开启Dreamview，然后点击右上方的Dreamview。
在另一个终端里输入：
rosbag play -l ./docs/demo_guide/demo.bag
然后就可以看到界面播放demo.bag数据啦：
![tupian](docs/demo_guide/images/dv_trajectory.png)
当然，这只是播放录像而已，要搭建一个真实的无人车所需要的硬件诸如工业电脑IPC、GPS、IMU、CANBUS卡等

