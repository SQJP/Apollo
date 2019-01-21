# 介绍
这是GNSS设备（如Novatel、Applanix和U-Blox）的驱动程序。GNSS设备通常包括来自GNSS接收器、IMU、车轮编码器接口和融合引擎这些传感器的信息。  
# 目的
我们驱动的目标是：
-清晰的C++代码，更好的代码结构，以及更好的性能（超过开源的NoToLL驱动程序）。  
-发布独立传感器的协议信息，如传感器/GPS、传感器/IMU、传感器/INS、传感器/车轮。   
-支持各种传感器：Novatel、U-Blox、Stim300、车轮编码器等。  
-记录和重放原始数据。日志将用于IE后处理。  
-支持对GPS接收器进行流式RTK校正。  
# 设计
驱动程序有两个节点：流节点和分析器节点。Nodelet负责主机和设备之间的通信，以及从NTRIP主机获取RTK数据。这个解析器nodelet从流nodelet订阅原始数据，解析数据并发布Protobuf消息。  
# 输入
GNSS设备生成的数据，如Novatel，支持TCP/USB/UDP/NTRIP连接方法。  
# 输出
* 全球导航卫星系统状态  
* 惯导状态  
* 流状态  
* IMU数据  
* 本地化数据  
# 配置
我们使用protobuf来存储驱动程序需要的所有配置。配置文件存储在路径中`share/gnss_driver/conf/`由gnss_driver.launch引用。文件gnss_driver.launch存储在路径中`share/gnss_driver/launch/`。  
使用GNSSU驱动程序时，应注意以下事项。
* 现在位置使用UTM投影，必须在gnss_driver.launch中检查区域ID配置。  
* 杠杆臂距离检查。  
* 确认IMU安装方法，这会影响框架和方向计算。  
