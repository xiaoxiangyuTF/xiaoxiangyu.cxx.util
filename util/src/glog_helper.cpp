// Copyright 2018 Baidu Inc. All Rights Reserved.
// Author: xiaoxiangyuTF
//
// 日志类
//
// Created by map on 18-11-12.
//
#include <fstream>

#include "../include/glog_helper.h"
#include "../include/config_helper.h"

namespace common_lib{

    //将信息输出到单独的文件和 LOG(ERROR)
    void SignalHandle(const char* data, int size)
    {
        std::ofstream fs("glog_dump.log",std::ios::app);
        std::string str = std::string(data,size);
        fs<<str;
        fs.close();
        LOG(ERROR)<<str;
    }

    GlogHelper::GlogHelper() {

    }

    GlogHelper::~GlogHelper() {
        google::ShutdownGoogleLogging();
    }

    bool common_lib::GlogHelper::init_log() {
        auto conf_instance = common_lib::ConfigHelper::get_instance();

        /// 获取当前执行程序路径
        std::string current_execute_path = FileSystemHelper::get_execute_path();
        std::string log_dir = conf_instance->get_string_value("log:log_dir", "./");
        google::InitGoogleLogging(current_execute_path.c_str());

        /// 设置屏幕输出级别
        int std_lever = conf_instance->get_int_value("log:std_lerver", 0);
        google::SetStderrLogging(std_lever);

        /// 设置输出屏幕的日志显示相应颜色
        bool color_to_std = conf_instance->get_boolean_value("log:color_to_std", 1);
        FLAGS_colorlogtostderr = color_to_std;

        /// 设置日志分级输出
        if (!FileSystemHelper::is_file_exist(log_dir)){
            FileSystemHelper::create_dirs(log_dir);
        }

        google::SetLogDestination(google::INFO, FileSystemHelper::combine_path(log_dir, "info_").c_str());
        google::SetLogDestination(google::ERROR, FileSystemHelper::combine_path(log_dir, "error_").c_str());

        /// 缓冲日志输出时间
        int buf_secs = conf_instance->get_int_value("log:buf_secs", 0);
        FLAGS_logbufsecs = buf_secs;

        /// 最大日志大小
        int max_size = conf_instance->get_int_value("log:max_size", 0);
        FLAGS_max_log_size = max_size;
        FLAGS_stop_logging_if_full_disk = true;

        /// 日志名扩展
        std::string execute_base_name = FileSystemHelper::get_file_base_name(current_execute_path);
        std::string prefix_name = conf_instance->get_string_value("log:prefix_name", execute_base_name);
        google::SetLogFilenameExtension(prefix_name.c_str());

        /// 捕捉core dump
        google::InstallFailureSignalHandler();
        google::InstallFailureWriter(&SignalHandle);

        return true;
    }
}
