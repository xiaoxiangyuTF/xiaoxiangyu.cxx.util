// Copyright 2018 Baidu Inc. All Rights Reserved.
// Author: xiaoxiangyuTF
//
// 文件操作类
//
// Created by map on 18-10-02.
//

#ifndef LANE_DETECTOR_FILE_SYSTEM_HELPER_H
#define LANE_DETECTOR_FILE_SYSTEM_HELPER_H

#include <iostream>
#include <string>

#include <boost/regex.hpp>

namespace common_lib{
enum search_option_t {
    TOP_DIRECTOYR_ONLY = 1,
    ALL_DIRECTORIES = 2,
};

class FileSystemHelper {
public:
    FileSystemHelper(void);
    ~FileSystemHelper(void);

    /// check file exist
    static bool is_file_exist(const std::string& file_path); // file exist or not

    /// change file postfix
    static std::string change_file_postfix(
            const std::string& src_path,
            const std::string& old_postfix,
            const std::string& new_postfix);

    /// get current work directory
    static std::string get_current_work_dir();

    /// get current execute path
    static std::string get_execute_path();

    /// combine path
    static std::string combine_path(
            const std::string& dir,
            const std::string& file_name);

    /// get file name
    static std::string get_file_name(const std::string& path);

    /// get directory name
    static std::string get_directory_name(const std::string& path);

    /// get file base name
    static std::string get_file_base_name(const std::string& path);

    /// get file extension
    static std::string get_file_extension(const std::string& path);

    /// replace file directory
    static std::string replace_file_dir(
            const std::string& src_file_path,
            const std::string& src_dir,
            const std::string& dst_dir);

    /// join string with separator
    static std::string join_string_with_separator(
            const std::vector<std::string>& str_vec,
            std::string separator = " ");

    /// split string to string vector
    static std::vector<std::string> split_string_to_vec(
            const std::string& str,
            std::string separator = " ");

    /// path is end with end_str
    static bool is_file_end_with(
            const std::string& path,
            const std::string& end_str);

    /// path is start with start_str
    static bool is_file_start_with(const std::string& path,
                                   const std::string& end_str);

    /// get necessary files.
    static void get_pattern_files_path(
            std::vector<std::string>& files_vec,
            const std::string& cur_dir,
            boost::regex reg,
            const std::string extension = ".",
            search_option_t search_option = TOP_DIRECTOYR_ONLY);

    /// get files from directory
    static void get_directory_files(
            std::vector<std::string>& files_vec,
            const std::string& cur_dir,
            const std::string extension = ".",
            search_option_t search_option = TOP_DIRECTOYR_ONLY); // get all extension files

    /// read and write file.
    static bool read_file_text(
            const std::string& file_path,
            std::vector<std::string>& text_vec);

    static bool write_file_text(
            const std::string& file_path,
            const std::vector<std::string>& text_vec);

    /// file and folder process.
    static bool create_dirs(const std::string& dir);
    static bool delete_dirs(const std::string& dir);

    /// copy files
    static bool copy_file(
            const std::string& src_file_path,
            const std::string& dst_file_path,
            bool is_overwrite = false);

    /// copy directory
    static bool copy_dir(
            const std::string& src_dir,
            const std::string& dst_dir,
            const boost::regex& reg,
            const std::string extension = ".",
            search_option_t search_option = TOP_DIRECTOYR_ONLY,
            bool is_overwrite = false,
            bool is_show_copy_info = true);

    /// get time
    static std::string get_cur_time_string(
            std::string time_format = "%Y-%m-%d %H:%M:%S"); // get current time

    /// deal with string
    static std::string trim_head_tail_chars(
            const std::string src_str,
            const std::string trim_str);


    /// is start with
    static bool is_start_with(
            const std::string& str,
            const std::string& part);

    /// tolower
    static std::string string_to_lower(const std::string& str);
    /// toupper
    static std::string string_to_upper(const std::string& str);

};
}

#endif // LANE_DETECTOR_FILE_SYSTEM_HELPER_H