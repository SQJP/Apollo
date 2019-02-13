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
 * apollo内部定义了一系列的状态码用于标识各个模块的工作状态，状态码的含义可以在modules/common/proto/error_code.proto文件查看
 */

#ifndef MODULES_COMMON_STATUS_STATUS_H_
#define MODULES_COMMON_STATUS_STATUS_H_

#include <string>

#include "google/protobuf/descriptor.h"
#include "modules/common/proto/error_code.pb.h"

/**
 * @namespace apollo::common
 * @brief apollo::common
 */
namespace apollo {
namespace common {

/**
 * @class Status
 *
 * @brief A general class to denote the return status of an API call. It
 * can either be an OK status for success, or a failure status with error
 * message and error code enum.
 * 用于表示API调用的返回状态的通用类。 它可以是成功的OK状态，也可以是带有错误消息和错误代码枚举的故障状态。
*/
class Status {
 public:
  /**
   * @brief Create a success status.
   */
  Status() : code_(ErrorCode::OK), msg_() {}
  ~Status() = default;

  /**
   * @brief Create a status with the specified error code and msg as a
   * human-readable string containing more detailed information.
   * @param code the error code.
   * @param msg the message associated with the error.
   * 使用指定的错误代码创建状态，并将msg作为包含更多详细信息的人类可读字符串。
   */
  Status(ErrorCode code, const std::string& msg) : code_(code), msg_(msg) {}

  /**
   * @brief generate a success status.
   * @returns a success status
   */
  static Status OK() { return Status(); }

  /**
   * @brief check whether the return status is OK.
   * @returns true if the code is ErrorCode::OK
   *          false otherwise
   * 是否调用成功。
   */
  bool ok() const { return code_ == ErrorCode::OK; }

  /**
   * @brief get the error code
   * @returns the error code
   * 错误码
   */
  ErrorCode code() const { return code_; }

  /**
   * @brief defines the logic of testing if two Status are equal
   * 如果两个Status相等，则定义测试逻辑
   */
  bool operator==(const Status& rh) const {
    return (this->code_ == rh.code_) && (this->msg_ == rh.msg_);
  }

  /**
   * @brief defines the logic of testing if two Status are unequal
   */
  bool operator!=(const Status& rh) const { return !(*this == rh); }

  /**
   * @brief returns the error message of the status, empty if the status is
   * OK.
   * @returns the error message
   */
  const std::string& error_message() const { return msg_; }

  /**
   * @brief returns a string representation in a readable format.
   * @returns the string "OK" if success.
   *          the internal error message otherwise.
   * 以可读格式返回字符串表示形式。
   */
  std::string ToString() const {
    if (ok()) {
      return "OK";
    }
    return ErrorCode_Name(code_) + ": " + msg_;
  }

  /**
   * @brief save the error_code and error message to protobuf
   * @param the Status protobuf that will store the message.
   * 将错误代码和信息保存到protobuf
   */
  void Save(StatusPb* status_pb) {
    if (!status_pb) {
      return;
    }
    status_pb->set_error_code(code_);
    if (!msg_.empty()) {
      status_pb->set_msg(msg_);
    }
  }

 private:
  ErrorCode code_;
  std::string msg_;
};

inline std::ostream& operator<<(std::ostream& os, const Status& s) {
  os << s.ToString();
  return os;
}

}  // namespace common
}  // namespace apollo

#endif  // MODULES_COMMON_STATUS_STATUS_H_
