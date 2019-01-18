#用于介绍modules文件夹下各文件夹和文件的作用
#modules / common

```
包含非特定于模块的代码。
```

## apollo_app
```
“apollo_app”构建目标定义了抽象类ApolloApp，
由所有模块实现，以及宏APOLLO_MAIN，
用于启动每个模块。
```

## log
```
“log”构建目标将Google Log系统包装到项目特定的宏中，
允许对日志记录级别进行更精细的控制。
```

##宏
```
“宏”构建目标定义了一些常用的特定于类的宏。
```

##适配器
```
不同模块使用适配器来彼此通信。
AdapterManager类承载所有特定适配器并对其进行管理。
需要使用宏REGISTER_ADAPTER注册适配器。
Adapter类充当一个抽象层
Apollo模块和I / O机制（例如ROS）。
```


## configs / data
```
这些指定了车辆配置。
```
#math
#数学
```
实现了许多有用的数学库。
```

## monitor
```
定义日志记录系统。
```

## proto
```
定义了许多项目范围的协议缓冲区。
```
## status
# 状态
```
用于确定某些功能是否成功执行，
否则提供有用的错误消息。
```
## time
# 时间
```
辅助功能与时间有关。
```

## util
```
包含注册的工厂设计模式的实现，
一些字符串解析函数，以及一些用于解析的实用程序
文件中的协议缓冲区。
```

## vehicle_state
```
此类指定车辆的当前状态（例如位置，速度，
标题等）。
```
