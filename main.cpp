// Copyright 2018 Baidu Inc. All Rights Reserved.
// Author: xiaoxiangyuTF
//
// main
//
// Created by map on 18-11-13.
//

#include <iostream>
#include <thread>
#include "util/include/glog_helper.h"
#include "util/include/config_helper.h"

int main() {
    /// 初始化log
    common_lib::GlogHelper glog_helper;
    glog_helper.init_log();

    ///　读取配置文件
    common_lib::ConfigHelper* conf_instance = common_lib::ConfigHelper::get_instance();
    std::cout << "log_dir: " << conf_instance->get_string_value("log:log_dir", "") << std::endl;

    for (int i = 0; i < 1000; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        LOG(INFO) << "info" << i << std::endl;
        LOG(WARNING) << "info" << i << std::endl;
        LOG(ERROR) << "error" << i << std::endl;
    }
    return EXIT_SUCCESS;
}