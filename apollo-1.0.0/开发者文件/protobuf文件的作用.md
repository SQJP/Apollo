##什么是protocol 文件
是一个消息格式文件，在该文件中可以通过描述性语言来定义程序中用到的数据格式，可以理解为存放数据结构的文件。  
## 为什么需要protocol文件？
最直观的体会是保存了原有数据本身的格式，避免了数据解析时需要对数据格式进行转化。  
通常情况下，我们会将接受到的雷达数据写入文本文件记录下来，在需要的时候再进行读取，这时候就需要对数据进行解析。从文本中读入的数据是string格式，而往往我们的数据可能包含了多种数据格式，可能有整形、字符型、浮点型、枚举等，这时就需要我们按照数据本身的类型进行数据转化，这样会造成工作量大，且通用性差等问题。.proto就是为了解决这些问题而开发的。  
##环境咋样配置
需要安装protobuf, [http://code.google.com/p/protobuf/downloads/list](http://code.google.com/p/protobuf/downloads/list)上可以下载 Protobuf 的源代码。   
安装步骤如下：  
```
tar -xzf protobuf-2.1.0.tar.gz 
cd protobuf-2.1.0 
./configure --prefix=$INSTALL_DIR 
make 
make check 
make install
```
##咋样使用protobuf? 
1.写一个proto文件，在其中定义需要的数据结构，命名为test.proto。  
```
package lm; 
message helloworld 
{ 
   required int32     id = 1;  // ID 
   required string    str = 2;  // str 
   optional int32     opt = 3;  //optional field 
}
```
2.使用proto文件编译器把写的proto文件编译为cpp类。进入到test.proto所在文件夹路径下执行：  
```
protoc -I=./ --cpp_out=./ test.proto  
```
![tupian](docs/demo_guide/images/protocol.png)
将会生成两个文件, test.pb.h 和test.pb.cpp。test.pb.h文件中定义了 C++ 类的头文件，test.pb.cpp为C++ 类的实现文件。
在生成的头文件中，定义了一个 C++ 类 helloworld，后面的 Writer 和 Reader 将使用这个类来对消息进行操作。诸如对消息的成员进行赋值，将消息序列化等等都有相应的方法。  
3.把第二步生成的类包含到你写的程序中, 就可以使用它了.这一步主要是实例化类的对象，然后调用类中的函数给.proto中数据结构赋值。  
这里编写编写 writer 和 Reader来说明C++ 类 helloworld的使用。在 Writer 代码中，Writer 需要 include 该头文件，然后便可以使用这个类了。将要存入磁盘的结构化数据由一个 lm::helloworld 类的对象表示，它提供了一系列的 get/set 函数用来修改和读取结构化数据中的数据成员。并且lm::helloworld 已经提供相应的方法来把一个复杂的数据变成一个字节序列，我们可以将这个字节序列写入磁盘。  
###Writer 的主要代码
```
#include "lm.helloworld.pb.h"

 
 int main(void) 
 { 
   
  lm::helloworld msg1; 
  msg1.set_str(“testname”); 
  msg1.set_id(655384); 
  
     
  // Write the new address book back to disk. 
  fstream output("./log", ios::out | ios::trunc | ios::binary); 
         
  if (!msg1.SerializeToOstream(&output)) { 
      cerr << "Failed to write msg." << endl; 
      return -1; 
  }         
  //序列化输出
   int len = pinfo->ByteSize();
    uint8_t *buf = new uint8_t[len];
    msg1->SerializeToArray(buf, len);
    for(int i = 0; i < len; i++)
    {
        printf("%02x ",buf[i]);
    }
    printf("\n");
    delete buf;
   return 0; 
 }
```
Msg1 是一个 helloworld 类的对象，set_id() 用来设置 id 的值。SerializeToOstream 将对象序列化后写入一个 fstream 流。   
读取这个数据的程序来说，也只需要使用类 lm::helloworld 的相应反序列化方法来将这个字节序列重新转换会结构化数据。  
序列化的值为：
```
0a 08 74 65 73 74 6e 61 6d 65 10 98 80 28
```
###Reader 的主要代码
```
#include "lm.helloworld.pb.h" 

 void ListMsg(const lm::helloworld & msg) { 
  cout << msg.id() << endl; 
  cout << msg.str() << endl; 
 } 
  
 int main(int argc, char* argv[]) { 
 
  lm::helloworld msg1; 
  
  { 
    fstream input("./log", ios::in | ios::binary); 
    if (!msg1.ParseFromIstream(&input)) { 
      cerr << "Failed to parse address book." << endl; 
      return -1; 
    } 
  } 
  
  ListMsg(msg1); 

 }
```
同样，Reader 声明类 helloworld 的对象 msg1，然后利用 ParseFromIstream 从一个 fstream 流中读取信息并反序列化。此后，ListMsg 中采用 get 方法读取消息的内部信息，并进行打印输出操作。  
##总结
protocol 解决了读写磁盘数据时需要的字符串转化问题，只需按照protocol书写规则存放数据结构，用protoc进行编译，生成数据处理类，其他的就是在自己的代码中调用类中的方法，实现自己的功能。由于是二进制存储，所以protocol具有占用空间小，传送速度快等优点。在js中json文件和protocol类似。
##参考
Google Protocol Buffer 的使用和原理:[https://www.ibm.com/developerworks/cn/linux/l-cn-gpb/index.html](https://www.ibm.com/developerworks/cn/linux/l-cn-gpb/index.html)  

protobuf 归纳:[https://blog.csdn.net/mynameislu/article/details/78645880](https://blog.csdn.net/mynameislu/article/details/78645880)  
google protobuf学习笔记二：使用和原理:[https://blog.csdn.net/majianfei1023/article/details/45112415/](https://blog.csdn.net/majianfei1023/article/details/45112415/)  

