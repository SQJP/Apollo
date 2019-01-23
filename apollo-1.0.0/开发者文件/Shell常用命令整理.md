### 在shell脚本中可以使用三类命令：
#### 1)Unix 命令:
 虽然在shell脚本中可以使用任意的unix命令，但是还是由一些相对更常用的命令。这些命令通常是用来进行文件和文字操作的。  
 常用命令语法及功能  
 echo “some text”: 将文字内容打印在屏幕上  
 ls: 文件列表  
 wc –l filewc -w filewc -c file: 计算文件行数计算文件中的单词数计算文件中的字符数  
 cp sourcefile destfile: 文件拷贝  
 mv oldname newname : 重命名文件或移动文件  
 rm file: 删除文件  
 grep ‘pattern’ file: 在文件内搜索字符串比如：grep ’searchstring’ file.txt  
 cut -b colnum file: 指定欲显示的文件内容范围，并将它们输出到标准输出设备比如：输出每行第5个到第9个字符cut -b5-9 file.txt千万不要和cat命令混淆，这是两个完全不同的命令  
 cat file.txt: 输出文件内容到标准输出设备（屏幕）上  
 file somefile: 得到文件类型  
 read var: 提示用户输入，并将输入赋值给变量  
 sort file.txt: 对file.txt文件中的行进行排序  
 uniq: 删除文本文件中出现的行列比如： sort file.txt | uniq  
 expr: 进行数学运算Example: add 2 and 3expr 2 “+” 3  
 find: 搜索文件比如：根据文件名搜索find . -name filename -print  
 tee: 将数据输出到标准输出设备(屏幕) 和文件比如：somecommand | tee outfile  
 basename file: 返回不包含路径的文件名比如： basename /bin/tux将返回 tux  
 dirname file: 返回文件所在路径比如：dirname /bin/tux将返回 /bin  
 head file: 打印文本文件开头几行  
 tail file : 打印文本文件末尾几行  
 sed: Sed是一个基本的查找替换程序。可以从标准输入（比如命令管道）读入文本，并将结果输出到标准输出（屏幕）。该命令采用正则表达式（见参考）进行搜索。不要和shell中的通配符相混淆。比如：将linuxfocus替换为 LinuxFocus ：cat text.file | sed ’s/linuxfocus/LinuxFocus/’ >newtext.fileawk: awk 用来从文本文件中提取字段。缺省地，字段分割符是空格，可以使用-F指定其他分割符。  
 catfile.txt | awk -F, ‘{print $1 “,” $3}’这里我们使用，作为字段分割符，同时打印第一个和第三个字段。如果该文件内容如下： Adam Bor, 34, IndiaKerryMiller, 22, USA命令输出结果为：Adam Bor, IndiaKerry Miller, USA  
#### 2) 管道, 重定向和 backtick
 这些不是系统命令，但是他们真的很重要。  
 （1）| :将一个命令的输出作为另外一个命令的输入，例如：  
 grep “hello” file.txt | wc -l  
 在file.txt中搜索包含有”hello”的行并计算其行数。在这里grep命令的输出作为wc命令的输入。当然您可以使用多个命令。  
 （2）重定向：将命令的结果输出到文件，而不是标准输出（屏幕）。  
 ">"：写入文件并覆盖旧文件  
 ">>"：加到文件的尾部，保留旧文件内容。  
 （3）反短斜线/：使用反短斜线可以将一个命令的输出作为另外一个命令的一个命令行参数。  
 （4）find命令，例如：  
 find . -mtime -1 -type f -print  
 用来查找过去24小时（-mtime –2则表示过去48小时）内修改过的文件。如果您想将所有查找到的文件打一个包，则可以使用以下linux 脚本：  
 #!/bin/bash  
 tar -zcvf lastmod.tar.gz `find . -mtime -1 -type f -print`  
注意：find . -mtime -1 -type f -print语句用反单引号引起来。
#### 3) 流程控制
 1.if
  “if” 表达式 如果条件为真则执行then后面的部分：  
 if ….; then  
  ….  
  elif ….; then  
  ….  
  else  
  ….  
  fi  
  大多数情况下，可以使用测试命令来对条件进行测试。比如可以比较字符串、判断文件是否存在及是否可读等等…  
 通常用” [ ] “来表示条件测试。注意这里的空格很重要。要确保方括号的空格。  
 [ -f "somefile" ] ：判断是否是一个文件  
 [ -x "/bin/ls" ] ：判断/bin/ls是否存在并有可执行权限  
 [ -n "$var" ] ：判断$var变量是否有值  
 [ "$a" = "$b" ] ：判断$a和$b是否相等  
 执行man test可以查看所有测试表达式可以比较和判断的类型。  

