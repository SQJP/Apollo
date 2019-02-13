/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 * ApolloApp类用于各个模块注册信息。各个模块每调用一次APOLLO_MAIN(APP)，
 * 即创建一个module模块进程， ApolloApp类规范了每个模块APP类的公有接口。 
 * 正常情况下，该进程将持续运行。ApolloApp是纯虚函数。
 * 这意味着每个模块需要重写多个纯虚函数接口才能实例化本模块。
 * 而重写的正是每个模块不同的地方。
 */

#ifndef MODULES_APOLLO_APP_H_
#define MODULES_APOLLO_APP_H_

#include <csignal>
#include <string>

#include "gflags/gflags.h"
#include "modules/common/log.h"
#include "modules/common/status/status.h"
#include "modules/hmi/utils/hmi_status_helper.h"

#include "third_party/ros/include/ros/ros.h"

/**
 * @namespace apollo::common
 * @brief apollo::common
 */
namespace apollo {
namespace common {

/**
 * @class ApolloApp
 *
 * @brief The base module class to define the interface of an Apollo app.
 * An Apollo app runs infinitely until being shutdown by SIGINT or ROS. Many
 * essential components in Apollo, such as localization and control are examples
 * of Apollo apps. The APOLLO_MAIN macro helps developer to setup glog, gflag
 * and ROS in one line.
 * 用于定义Apollo应用程序界面的基本模块类。
   Apollo应用程序无限运行，直到被SIGINT或ROS关闭。 Apollo中的许多基本组件，例如本地化和控制都是Apollo应用程序的示例。 APOLLO_MAIN宏可以帮助开发人员在一行中设置glog，gflag和ROS。
 */
class ApolloApp {
 public:
  /**
   * @brief module name. It is used to uniquely identify the app.
   */
  virtual std::string Name() const = 0;

  /**
   * @brief this is the entry point of an Apollo App. It initializes the app,
   * starts the app, and stop the app when the ros has shutdown.
   * 这是Apollo应用程序的切入点。 它初始化应用程序，启动应用程序，并在ros关闭时停止应用程序。
   */
  //初始化模块app的信息，并持续运行直到shutdown
  virtual int Spin();

  /**
   * The default destructor.
   */
  virtual ~ApolloApp() = default;

 protected:
  /**
   * @brief The module initialization function. This is the first function being
   * called when the App starts. Usually this function loads the configurations,
   * subscribe the data from sensors or other modules.
   * @return Status initialization status
   */
  //执行初始化加载配置文件和传感器数据等任务。
  virtual apollo::common::Status Init() = 0;

  /**
   * @brief The module start function. Apollo app usually triggered to execute
   * in two ways: 1. Triggered by upstream messages, or 2. Triggered by timer.
   * If an app is triggered by upstream messages, the Start() function usually
   * register a call back function that will be called when an upstream message
   * is received. If an app is triggered by timer, the Start() function usually
   * register a timer callback function.
   * @return Status start status
   *  阿波罗应用程序通常会触发执行，开始执行模块任务。若由上层message到来触发，则执行与message相关的回调函数。
   * 若由定时器time触发，则调用时间处理回调函数
   */
  virtual apollo::common::Status Start() = 0;

  /**
   * @brief The module stop function. This function will be called when
   * after ros::shutdown() has finished. In the default APOLLO_MAIN macro,
   * ros::shutdown() is called when SIGINT is received.
   * 模块停止运行。在ros::shutdown()执行完毕后的清理工作
   */
  virtual void Stop() = 0;

  /**
   * @brief report module status to HMI
   * @param status HMI status
   * 向HMI人机交互界面发送状态status码。
   */
  virtual void ReportModuleStatus(
      const apollo::hmi::ModuleStatus::Status status);

  apollo::hmi::ModuleStatus status_;
};

void apollo_app_sigint_handler(int signal_num);

}  // namespace common
}  // namespace apollo

#define APOLLO_MAIN(APP)                                       \
  int main(int argc, char **argv) {                            \
    google::InitGoogleLogging(argv[0]);                        \
    google::ParseCommandLineFlags(&argc, &argv, true);         \
    signal(SIGINT, apollo::common::apollo_app_sigint_handler); \
    APP apollo_app_;                                           \
    ros::init(argc, argv, apollo_app_.Name());                 \
    apollo_app_.Spin();                                        \
    return 0;                                                  \
  }

#endif  // MODULES_APOLLO_APP_H_
