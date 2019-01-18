## 需要注意的是：你的本地共组库和github远程库之间传输信息是通过SSH Key加密实现的，所以，在将本地库上传到远程库之前，必须设置SSH（只需要设置一次）。步骤如下：  

#### 步骤1：创建SSH Key   
     首先查看用户主目录下是否有.ssh文件（.ssh文件可通过Ctrl+h快捷键调出查看）。若有，再查看该文件下是否有id_rsa和id_ras.pub文件，然后转到步骤2；若没有，则在linux终端下执行如下命令：ssh-keygen -t rsa -C "youremail@example.com"  其中，“ ”中的内容是你自己在github上创建账户时留下的邮箱地址。在执行该命令后一路回车，使用默认值即可。  
    若一切顺利，此时你可以在用户主目录下找到.ssh文件，里面有id_rsa和id_rsa.pub两个文件。这两个就是SSH Key的秘钥对，id_rsa是私钥，不能泄露出去，id_rsa.pub是公钥，可以放心地告诉任何人。  

#### 步骤2：添加SSH Key  
     登录你的github账号，点击右上角用户下的“Settings”,进入下一界面，在该界面左侧栏找到“SSH and GPG keys”。然后点“New SSH Key”，填上任意Title，在Key文本框里粘贴id_rsa.pub文件的内容。最后点“Add SSH Key”就能看到已经添加的Key。至此，SSH Key设置完成。  
![P1](Apollo/apollo-1.0.0/docs/demo_guide/images/P1.png)  
![P2](Apollo/apollo-1.0.0/docs/demo_guide/images/P2.png)  
注意：GitHub允许你添加多个Key。假定你有若干电脑，你一会儿在公司提交，一会儿在家里提交，只要把每台电脑的Key都添加到GitHub，就可以在每台电脑上往GitHub推送了。  
  
git工具的具体使用请访问：https://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000

