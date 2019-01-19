# can总线

## 介绍
  Canbus接受并执行控制命令，收集底盘状态作为反馈进行控制。  

## 输入
  * 控制命令  

## 输出
  * 底盘状态  
  * 机箱详细信息状态  

## 使用
  Canbus模块的主要部件有：  
  * can客户端  
  * 车辆包括车辆控制器和信息管理器  

  
 通过从`can client`类继承，您自己的`can client`可以在* can_client *的文件夹中实现。记住在`canclientfactory`中注册您的can客户端。  

 通过继承`vehicle controller`和`message manager`，您自己的车辆控制器和消息管理器可以在* vehicle *的文件夹中实现。记住在`vehicle factory`登记您的车辆。  
