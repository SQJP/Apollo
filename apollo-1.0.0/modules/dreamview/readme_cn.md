## Dreamvew
## 介绍
该模块提供一个Web应用程序，帮助用户可视化相关自主驾驶模块的当前输出，例如规划轨迹、汽车定位、底盘状态等。  
## 输入
目前它显示以下消息：  
* 本地化由protobuf消息“localizationEstimate”定义，可在文件“localization/proto/localization.proto”中找到。  
* 由protobuf消息'chassis'定义的底盘，可在文件'canbus/proto/chassis.proto'中找到。  
* 由protobuf消息“adctrajectory”定义的规划，可在“planning/proto/planning.proto”文件中找到。  
* 由protobuf消息“monitor message”定义的显视器，可在文件“common/monitor/proto/monitor.proto”中找到。  
