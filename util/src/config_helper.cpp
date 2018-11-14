// Copyright 2018 Baidu Inc. All Rights Reserved.
// Author: xiaoxiangyuTF
//
// 文件配置类
//
// Created by map on 18-11-12.
//

#include "../include/config_helper.h"

namespace common_lib{

    ConfigHelper* ConfigHelper::_conf_instance = nullptr;
    std::string ConfigHelper::_ini_file = "./conf/conf.ini";
    dictionary* ConfigHelper::_ini_dict = nullptr;
    std::mutex ConfigHelper::_mtx;

    ConfigHelper::ConfigHelper() {}
    ConfigHelper::~ConfigHelper() {
        if (nullptr != _conf_instance){
            if (nullptr != _ini_dict){
                iniparser_freedict(_ini_dict);
                _ini_dict = nullptr;
            }
            free(_conf_instance);
            _conf_instance = nullptr;
        }
    }

    bool ConfigHelper::init_conf() {
        _ini_dict = iniparser_load(_ini_file.c_str());
        if (nullptr == _ini_dict){
            std::cerr << "can not load ini file: " << _ini_file << std::endl;
            return false;
        }
        return true;
    }

    ConfigHelper* ConfigHelper::get_instance() {
        if (nullptr == _conf_instance){
            std::unique_lock<std::mutex>lck(_mtx);
            if(nullptr == _conf_instance){
                if (init_conf()){
                    _conf_instance = new ConfigHelper;
                }
            }
            lck.unlock();
        }
        return _conf_instance;
    }

    std::string ConfigHelper::get_string_value(const std::string& section_name, const std::string& default_value) {
        return iniparser_getstring(_ini_dict, section_name.c_str(), default_value.c_str());
    }

    bool ConfigHelper::get_boolean_value(const std::string &section_name, int default_value) {
        return static_cast<bool>(iniparser_getboolean(_ini_dict, section_name.c_str(), default_value));
    }

    int ConfigHelper::get_int_value(const std::string &section_name, int default_value) {
        return iniparser_getint(_ini_dict, section_name.c_str(), default_value);
    }

    double ConfigHelper::get_double_value(const std::string &section_name, double default_value) {
        return iniparser_getdouble(_ini_dict, section_name.c_str(), default_value);
    }


}
