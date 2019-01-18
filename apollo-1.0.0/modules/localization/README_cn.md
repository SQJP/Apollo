# 定位 #
===========
  ## 介绍 ##
-----------
     该模块提供定位服务。它实现了基于RTK的定位，其中包含GPS和IMU信息。

  ## 输入 ##
----------
    在提供的RTK定位方法中，有两个输入：
     * GPS全球定位系统。
     * IMU惯性测量单元。

  ## 输出 ##
----------
     * 由Protobuf消息“LocalizationEstimate”定义的对象实例，可以在文件`localization / proto / localization.proto`中找到。

  ## 添加定位实施 ##
----------
      目前，基于RTK的定位是在“RTKLocalization”类中实现的。如果需要使用诸如“FooLocalization”之类的名称实现新的定位方法，则可以按照以下步骤操作：
      1.在`proto / localization_config.proto`中，在`LocalizationType`枚举类型中添加`FOO`。
      2.转到`modules / localization`目录，创建一个`foo`目录。在`foo`目录中，在`rtk`目录中的`RTKLocalization`类之后实现类        `FooLocalization`。 `FooLocalization`必须是`LocalizationBase`的子类。还要在文件`rtk / BUILD`之后创建文件foo / BUILD。
      3.你需要在函数`Localization :: RegisterLocalizationMethods（）`中注册`FooLocalizatoin`类，它位于cpp文件`localization.cc`中。您可以通过在函数末尾插入以下代码进行注册： 
    localization_factory_.Register（LocalizationConfing :: FOO，[]（） - > LocalizationBase * {return new FooLocalization（）;}）;确保通过包含定义类`FooLocalization`的头文件来编译代码。
      4.现在你可以回到`apollo`根目录并使用命令`bash apollo.sh build`构建你的代码。
