// Copyright 2018 Baidu Inc. All Rights Reserved.
// Author: xiaoxiangyuTF
//
// test类
//
// Created by map on 18-11-13.
//

#include <iostream>
#include <gtest/gtest.h>

#include "../util/include/config_helper.h"


TEST(ConfInstatanceTest, ConfInstatanceTestCase){
    auto conf = common_lib::ConfigHelper::get_instance();
    ASSERT_NE(nullptr, conf);
}

TEST(GetStringValueTest, GetStringValueTestCase){
    auto conf = common_lib::ConfigHelper::get_instance();
    ASSERT_EQ("./log", conf->get_string_value("log:log_dir", ""));
}

TEST(GetBooleanValueTest, GetBooleanValueTestCase){
    auto conf = common_lib::ConfigHelper::get_instance();
    ASSERT_TRUE(conf->get_boolean_value("log:color_to_std", 0));
}

TEST(GetIntValueTest, GetIntValueTestCase){
    auto conf = common_lib::ConfigHelper::get_instance();
    ASSERT_EQ(100, conf->get_int_value("log:max_size", 0));
}

TEST(GetDoubleValueTest, GetDoubleValueTestCase){
    auto conf = common_lib::ConfigHelper::get_instance();
    ASSERT_EQ(100, conf->get_double_value("log:max_size", 0.0));
}

int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}