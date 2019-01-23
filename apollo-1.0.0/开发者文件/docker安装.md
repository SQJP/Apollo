docker安装
========
# 前提条件
Docker 要求 Ubuntu 系统的内核版本高于 3.10 ，查看本页面的前提条件来验证你的 Ubuntu 版本是否支持 Docker。   
通过`uname -r`命令查看你当前的内核版本。  
针对ubuntu16.04使用脚本安装Docker  
参照官网教程https://docs.docker.com/install/linux/docker-ce/ubuntu/
以选择国内的云服务商，这里选择阿里云为例  
运行`curl -sSL http://acs-public-mirror.oss-cn-hangzhou.aliyuncs.com/docker-engine/internet | sh -`  
## 安装所需要的包  
运行`sudo apt-get install linux-image-extra-$(uname -r) linux-image-extra-virtual`
## 添加使用 HTTPS 传输的软件包以及 CA 证书  
运行`sudo apt-get update`  
运行`sudo apt-get install apt-transport-https ca-certificates`  
## 添加GPG密钥  
运行`sudo apt-key adv --keyserver hkp://p80.pool.sks-keyservers.net:80 --recv-keys 58118E89F3A912897C070ADBF76221572C52609D`  
## 添加软件源
运行`echo "deb https://apt.dockerproject.org/repo ubuntu-xenial main" | sudo tee /etc/apt/sources.list.d/docker.list`  
## 添加成功后更新软件包缓存
运行`sudo apt-get update`  
## 安装docker
运行`sudo apt-get install docker-engine`  
## 启动 docker
运行`sudo systemctl enable docker`  
运行`sudo systemctl start docker` （发现sudo service docker start去启动docker服务，输入docker的指令后却没有反应，然后sudo service docker stop + sudo service docker start/sudo service docker restart重启docker 服务却没有反应，请ps -ef|grep docker察看所有docker进程，并且kill掉它们，再sudo service docker start就没有问题了）  
## 如果是非root用户可以执行  
运行`sudo usermod -aG docker runoob`  
用helloworld测试安装的docker  
===========
# 测试hello-world
运行`sudo docker run ubuntu:15.10 /bin/echo "Hello world"`  （如果本地库中没有系统会自动从dockerhub远程库中进行下载）  
各个参数解析：  
* docker: Docker 的二进制执行文件。  
* run:与前面的 docker 组合来运行一个容器。  
* ubuntu:15.10指定要运行的镜像，Docker首先从本地主机上查找镜像是否存在，如果不存在，Docker 就会从镜像仓库 Docker Hub 下载公共镜像。  
* /bin/echo "Hello world": 在启动的容器里执行的命令  
以上命令完整的意思可以解释为：Docker 以 ubuntu15.10 镜像创建一个新容器，然后在容器里执行 bin/echo "Hello world"，然后输出结果。  
