// Copyright 2018 Baidu Inc. All Rights Reserved.
// Author: xiaoxiangyuTF
//
// 日志类
//
// Created by map on 18-11-12.
//

#ifndef COMMON_LIB_GLOG_HELPER_H
#define COMMON_LIB_GLOG_HELPER_H

#include <string>

#include <glog/logging.h>
#include <glog/raw_logging.h>

#include "file_system_helper.h"

namespace common_lib{
class GlogHelper {
public:
    GlogHelper();
    ~GlogHelper();
    bool init_log();
};
}

#endif //COMMON_LIB_GLOG_HELPER_H
