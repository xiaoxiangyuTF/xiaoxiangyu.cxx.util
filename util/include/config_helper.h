// Copyright 2018 Baidu Inc. All Rights Reserved.
// Author: xiaoxiangyuTF
//
// 文件配置类
//
// Created by map on 18-11-12.
//

#ifndef COMMON_LIB_CONFIG_HELPER_H
#define COMMON_LIB_CONFIG_HELPER_H

#include <iostream>
#include <mutex>

#include "iniparser/iniparser.h"
#include "iniparser/dictionary.h"

namespace common_lib{
class ConfigHelper {
public:

    static ConfigHelper * get_instance();

    /// get int value
    int get_int_value(const std::string& section_name, int default_value);

    /// get string value
    std::string get_string_value(const std::string& section_name, const std::string& default_value);

    /// get bool value
    bool get_boolean_value(const std::string& section_name, int default_value);

    /// get double value
    double get_double_value(const std::string& section_name, double default_value);

private:
    ConfigHelper();
    virtual ~ConfigHelper();
    ConfigHelper(const ConfigHelper&);
    ConfigHelper& operator=(const ConfigHelper&);

    /// init conf dict
    static bool init_conf();

    /// configure file
    static std::string _ini_file;

    /// configure dictionary
    static dictionary* _ini_dict;

    /// ConfigHelper instance
    static ConfigHelper* _conf_instance;

    /// mutex
    static std::mutex _mtx;
};
}


#endif //COMMON_LIB_CONFIG_HELPER_H
