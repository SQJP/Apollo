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
# 测试hello-world
运行`sudo docker run ubuntu:15.10 /bin/echo "Hello world"`  （如果本地库中没有系统会自动从dockerhub远程库中进行下载）  
各个参数解析：  
* docker: Docker 的二进制执行文件。  
* run:与前面的 docker 组合来运行一个容器。  
* ubuntu:15.10指定要运行的镜像，Docker首先从本地主机上查找镜像是否存在，如果不存在，Docker 就会从镜像仓库 Docker Hub 下载公共镜像。  
* /bin/echo "Hello world": 在启动的容器里执行的命令  
以上命令完整的意思可以解释为：Docker 以 ubuntu15.10 镜像创建一个新容器，然后在容器里执行 bin/echo "Hello world"，然后输出结果。  
# 容器对话
通过docker的两个参数 -i -t，让docker运行的容器实现"对话"的能力  
`docker run -i -t ubuntu:15.10 /bin/bash`  
各个参数解析：  
* -t:在新容器内指定一个伪终端或终端。  
* -i:允许你对容器内的标准输入 (STDIN) 进行交互。  
此时我们已进入一个 ubuntu15.10系统的容器,通过运行exit命令或者使用CTRL+D来退出容器。  
* 通过 `docker ps` 来查看容器运行状态  
* `sudo docker ps -a` 查看所有容器  
* `sudo docker ps -l` 查看最后一次运行的容器  
* 在容器内使用`docker logs`命令，查看容器内的标准输出  
* 使用 `docker stop` 命令来停止容器  
# 容器的使用（动态）
以运行一个web应用为例   
`docker pull training/webapp`  
`docker run -d -P training/webapp python app.py`(或者`docker run -d -p 5000:5000 training/webapp python app.py `)  
参数说明:  
* -d:让容器在后台运行。  
* -P:将容器内部使用的网络端口映射到我们使用的主机上。  
* 使用 `docker port CONTAINER ID` 或 `docker port NAMES` 来查看容器端口的映射情况。  
* `docker logs  -f [ID或者名字] `可以查看容器内部的标准输出。  
* 使用 `docker top [ID或者名字] ` 来查看容器内部运行的进程  
* 使用 `docker inspect [ID或者名字]` 来查看 Docker 的底层信息  
* 使用 `docker stop [ID或者名字]`来停止容器  
* 使用 `docker rm [ID或者名字]`来删除容器  
# 镜像的使用（静态）
* 通过 `docker images`查看已有镜像  
* 同一仓库源可以有多个 TAG，代表这个仓库源的不同个版本  
* 我们使用版本为14.04的ubuntu系统镜像来运行容器时，命令为`docker run -t -i ubuntu:14.04 /bin/bash`  
*  获取一个新镜像，命令为`docker pull ubuntu:13.10`  
*  使用`docker search httpd`查看docker hub上的镜像文件  
*  `sudo docker login` 登陆docker 账户  
* 
# 容器连接
# dockerfiles
开发者把需要什么系统，需要装什么软件，需要怎么配置环境等等全部都写进Dockerfile里面，相当于是一个基于docker的全自动生成镜像的一个脚本。  
## 从当前目录下的Dockerfile(命名dockerfile好像也能识别，其他就不行了)建立镜像  
sudo docker build -t reponame:tag .  
# 启动容器  
`sudo docker run -it --name blabla -p <物理机>:<容器>(e.g. 127.0.0.1:3306:3306) -v /your/local/path/:/map/path/in/docker/ -v /etc/localtime:/etc/localtime --net =host -d reponame:tag`   
-it 是启动交互和伪终端  
-p  <IP>:<宿主机端口>:<容器端口>  将宿主机（物理机)映射或者可以理解为绑定,<IP>可以指定，也可以不指定，不指定默认是0.0.0.0,建议还是指定  
-v  是挂载本机目录到到docker目录,最好每次都把-v /etc/localtime:/etc/localtime也带上，确保docker 容器内时间和服务器时间一致]  
-d  是daemonize的意思，就是使容器成为守护进程，后台运作  
--net是设置docker的网络模式，默认不设置的话就是bridge模式，现在设置为和物理机网络绑定的host模式，更多可以看 Docker的4种网络模式(http://www.cnblogs.com/gispathfinder/p/5871043.html)  
--link 是容器链接  
# 复习几个特别的IP：
①127.0.0.1是本地回环地址，代指本机; [对于绑定在127.0.0.1的端口而言，外部无法访问，不对外打开，仅仅对内打开]  
②0.0.0.0 代表所有不清楚的IP，安全性差，也是指本机？;[对于绑定在0.0.0.0的端口而言，外部可以访问]   
③255.255.255.255 用人类的话说：“嘿，这屋子的所有人听着了！”   
④localhost 这个是域名，一般都是127.0.0.1，这种对应关系写在你的/etc/hosts里面   
`sudo docker start/stop/restart/rm blabla` 启动/停止/重启/删除 容器   
`sudo docker cp blabla:/app/file.txt .` 把docker里面/app目录下的file.txt文件复制出来到现在所在的目录   
`sudo docker exec -it blabla /bin/bash` #在启动的容器blabla中运行/bin/bash   
`sudo docker exec -it blabla /the/path/of/your/command sudo docker commit blabla repo:tag` 提交保存容器到一个新的镜像repo:tag   
`sudo docker rmi repo:tag` 删除镜像   
# 容器的导出和导入 
`sudo docker export `  
`sudo docker import`   
镜像的导出和导入 [文件]   
`sudo docker save repo:tag > backup.tar `  
`sudo docker load < backup.tar`   
[dockerhub]  
`sudo docker login`  
` sudo docker push repo:tag`  
` sudo docker pull repo:tag`  
# 常用组合命令  
停止所有docker容器 `sudo docker kill $(sudo docker ps -q)`  
删除所有docker容器 `sudo docker rm $(sudo docker ps -aq)`  
贴标签`docker tag 860c279d2fec runoob/centos:dev`
# 基于已有的image，创建docker image
第一个方法：在运行的container中安装service然后导出为image  
整体思路：运行一个容器，在运行容器的基础上添加需要的服务，然后导出为新的images。  
`docker run -it docker.io/centos`//根据image运行容器  
`yum -y install ****`            //安装一些服务  
`exit` //退出  
命令中 i 、t 的参数可以docker run –help查看  
现在的容器很明显已经被我们改动了，然后通过以下命令新建images：  
`docker commit -m “Description” -a “users <users@163.com>” 845e8472f250 centos:v1`  
-m：来指定提交的说明信息  
-a：指定更新的作者和邮箱  
命令中的一串数字是刚才运行container’s ID  
数字后面的是新建镜像的repository：tag  
第二个方法：基于dockerfile文件来创建新的image  
整体思路：新建一个dockerfile，文件名必须是dockerfile，写入命令。创建完使用docker build命令来创建新image。  
dockerfile文件中基本分为4部分：  
1.注释部分  
2.基础镜像地址  
3.维护者信息  
4.命令部分  
`mkdir -p /docker/httpd`  
`cd /docker/httpd`  
`vim  dockerfile`                         //这里文件名必须为dockerfile  
`#This is http service`                   //注释部分，类似于文件说明  
`FROM docker.io/centos：latest`           //以哪个image作为基础  
`MAINTAINER user <user@163.com> `         //维护者的信息  
`RUN yum -y install apr apr-utils  `      //在创建镜像中运行以下命令  
`RUN yum -y install httpd`  
根据dockerfile创建新images：  
`docker build -t=centos:v2 /docker/httpd`  
-t：添加镜像name：tag信息  
后面的/docker/httpd路径为dockerfile的绝对路径，也可在/docker/httpd的当前路径下使用 “.”来代替绝对路径  
说明：dockerfile中的指令被一行一行的执行，每执行完一行命令都要创建一个新的容器。当所有命令都执行完，会返回一个镜像ID，中间步骤所产生的所有容器ID都会被清除。一个镜像不能超过127层  
基于已有image进行创建的时候，可能会因为下载国外网站的镜像很慢。如果你在本地有镜像，可以通过以下命令本地导入镜像，这里再贴出导出镜像的命令  
`docker load -input` 镜像名称：标签                          //本地导入镜像  
`docker save -output`  创建归档文件名 镜像名称：标签           //本地导出镜像  
