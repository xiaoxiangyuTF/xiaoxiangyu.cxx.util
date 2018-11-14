# xiaoxiangyuTF.cxx.util

目前,只支持C++11

| 文件名称 | 文件描述　| 备注　|
| ---- | ---- | ---- |
| glog_helper | 封装google日志操作类　|  | 
| file_system_helper　| 封装boost对文件操作 |  |
| config_helper　| 封装iniparser对配置文件操作 |  |

-----

常用库及对应的git链接

| 库描述 | 地址　| 备注　|
| ---- | ---- | ---- |
| json(nlohmann) | https://github.com/xiaoxiangyuTF/json　|  | 
| iniparser4　| https://github.com/xiaoxiangyuTF/iniparser |  |
| cmdline　| https://github.com/xiaoxiangyuTF/cmdline |  |

使用方法雷同，例如：
cd test
cmake .
make 
./test_util
目前，只覆盖了ｃｏｎｆｉｇ_helper的测试
