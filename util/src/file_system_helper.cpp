// Copyright 2018 Baidu Inc. All Rights Reserved.
// Author: xiaoxiangyuTF
//
// 文件操作类
//
// Created by map on 18-11-12.
//

#include <sstream>
#include <fstream>
#include <exception>

#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/operators.hpp"
#include "boost/format.hpp"
#include "boost/algorithm/string.hpp"

#include "../include/file_system_helper.h"

namespace common_lib{
    FileSystemHelper::FileSystemHelper(void) {
    }

    FileSystemHelper::~FileSystemHelper(void) {
    }

    bool FileSystemHelper::is_file_exist(const std::string& file_path) {
        return boost::filesystem::is_regular_file(file_path.c_str()) &&
               boost::filesystem::exists(file_path.c_str());
    }

    std::string FileSystemHelper::get_current_work_dir() {
        return boost::filesystem::initial_path<boost::filesystem::path>().string();
    }

    std::string FileSystemHelper::get_execute_path() {
        return boost::filesystem::initial_path<boost::filesystem::path>().string();
    }

    std::string FileSystemHelper::combine_path(
            const std::string& dir,
            const std::string& file_name) {
        boost::filesystem::path path(dir.c_str());
        path /= file_name;
        return path.string();
    }

    std::string FileSystemHelper::get_file_name(const std::string& path) {
        return boost::filesystem::path(path.c_str()).filename().string();
    }

    std::string FileSystemHelper::get_directory_name(const std::string& path) {
        return boost::filesystem::path(path.c_str()).parent_path().string();
    }

    std::string FileSystemHelper::get_file_base_name(const std::string& path) {
        return boost::filesystem::path(path.c_str()).stem().string();
    }

    std::string FileSystemHelper::get_file_extension(const std::string& path) {
        return boost::filesystem::path(path.c_str()).extension().string();
    }

    std::string FileSystemHelper::get_cur_time_string(
            std::string time_format /*= "%Y-%m-%d %H:%M:%S"*/) {
        boost::posix_time::ptime now = boost::posix_time::second_clock::universal_time();
        std::stringstream format_date;
        boost::posix_time::time_facet* tfacet =
                new boost::posix_time::time_facet(time_format.c_str());
        format_date.imbue(std::locale(format_date.getloc(), tfacet));
        format_date << now;
        return format_date.str();
    }

    void FileSystemHelper::get_pattern_files_path(
            std::vector<std::string>& files_vec,
            const std::string& src_dir,
            boost::regex reg,
            const std::string extension/* = "."*/,
            search_option_t search_option /*= TopDirectoryOnly*/) {
        std::vector<std::string> allfiles;
        get_directory_files(allfiles, src_dir, extension, search_option);

        for (int i = 0; i < allfiles.size(); ++i) {
            std::string base_name = get_file_base_name(allfiles[i]);

            if (boost::regex_search(base_name, reg)) {
                files_vec.push_back(allfiles[i]);
            }
        }
    }

    void FileSystemHelper::get_directory_files(
            std::vector<std::string>& files_vec,
            const std::string& src_dir,
            const std::string extension/* = "."*/,
            search_option_t search_option /*= TopDirectoryOnly*/) {
        boost::filesystem::path src_path(src_dir.c_str());

        if (!boost::filesystem::exists(src_path)) {
            return;
        }

        typedef boost::filesystem::directory_iterator d_iterator;

        if (boost::filesystem::is_directory(src_path)) {
            d_iterator tmp_dir_end;
            d_iterator tmp_dir_iter(src_path);

            for (; tmp_dir_iter != tmp_dir_end; ++tmp_dir_iter) {
                if (boost::filesystem::is_directory(*tmp_dir_iter)) {
                    if (ALL_DIRECTORIES == search_option) {
                        get_directory_files(
                                files_vec,
                                tmp_dir_iter->path().string(),
                                extension,
                                search_option);
                    }
                } else if (boost::filesystem::is_regular_file(*tmp_dir_iter)) {
                    if (0 == extension.compare(".")) {
                        files_vec.push_back(tmp_dir_iter->path().string());
                    } else {
                        if (is_file_end_with(tmp_dir_iter->path().string(), extension)) {
                            files_vec.push_back(tmp_dir_iter->path().string());
                        }
                    }
                }
            }
        } else {
            if (is_file_end_with(src_dir, extension)) {
                files_vec.push_back(src_dir);
            }
        }
    }

    bool FileSystemHelper::is_file_end_with(
            const std::string& path,
            const std::string& end_str) {
        std::string file_path = get_file_name(path);
        return boost::algorithm::ends_with(file_path.c_str(), end_str.c_str());
    }

    bool FileSystemHelper::is_file_start_with(
            const std::string& path,
            const std::string& end_str) {
        std::string file_path = get_file_name(path);
        return boost::algorithm::starts_with(file_path.c_str(), end_str.c_str());
    }

    bool FileSystemHelper::read_file_text(
            const std::string& file_path,
            std::vector<std::string>& text_vec) {
        std::fstream fin;

        if (!is_file_exist(file_path)) {
            return false;
        }

        fin.open(file_path.c_str(), std::ios::in);

        if (!fin.is_open()) {
            std::cerr << "can not open file, file: " << file_path << std::endl;
            return false;
        }

        while (!fin.eof()) {
            std::string str_line;
            std::getline(fin, str_line);
            text_vec.push_back(str_line);
        }

        if (fin.is_open()) {
            fin.close();
        }

        return true;
    }

    bool FileSystemHelper::write_file_text(
            const std::string& file_path,
            const std::vector<std::string>& text_vec) {
        std::fstream fout;
        fout.open(file_path.c_str(), std::ios::out);

        if (!fout.is_open()) {
            std::cerr << "can not open the file, file: " << file_path << std::endl;
            return false;
        }

        for (int i = 0; i < text_vec.size(); ++i) {
            fout << text_vec[i] << std::endl;
        }

        if (!fout.is_open()) {
            fout.close();
        }

        return true;
    }

    std::string FileSystemHelper::change_file_postfix(
            const std::string& src_path,
            const std::string& old_postfix,
            const std::string& new_postfix) {
        std::string file_dir = get_directory_name(src_path);
        std::string old_file_name = get_file_name(src_path);
        boost::format form("%s%s");
        form % old_postfix % "$";
        boost::regex reg(form.str());
        std::string new_file_name =
                boost::regex_replace(old_file_name, reg, new_postfix);
        return combine_path(file_dir, new_file_name);
    }

    bool FileSystemHelper::create_dirs(const std::string& dir) {
        boost::filesystem::path path(dir.c_str());

        if (!boost::filesystem::exists(path)) {
            return boost::filesystem::create_directories(path);
        }

        return true;
    }

    bool FileSystemHelper::delete_dirs(const std::string& dir) {
        try {
            boost::system::error_code ec;
            boost::filesystem::remove_all(boost::filesystem::path(dir.c_str()), ec);
            std::cout << ec.message() << std::endl;
        } catch (...) {
            std::cout << "delete dir failed. dir: " << dir << std::endl;
            return false;
        }

        return true;
    }

    bool FileSystemHelper::copy_file(
            const std::string& src_file_path,
            const std::string& dst_file_path,
            bool is_overwrite /*= false*/) {
        auto copy_opt = boost::filesystem::copy_option::none;
        copy_opt = is_overwrite  ?  boost::filesystem::copy_option::overwrite_if_exists :
                   boost::filesystem::copy_option::fail_if_exists;
        boost::filesystem::copy_file(src_file_path, dst_file_path, copy_opt);
        return true;
    }

    std::string FileSystemHelper::replace_file_dir(
            const std::string& src_file_path,
            const std::string& src_dir,
            const std::string& dst_dir) {
        std::string dst_file_path(src_file_path);
        boost::replace_first(dst_file_path, src_dir, dst_dir);
        return dst_file_path;
    }

    std::string FileSystemHelper::join_string_with_separator(
            const std::vector<std::string>& str_vec,
            std::string separator /*= " "*/) {
        return boost::join(str_vec, separator.c_str());
    }

    std::vector<std::string> FileSystemHelper::split_string_to_vec(
            const std::string& str,
            std::string separator /*= " "*/) {
        std::vector<std::string> str_vec;
        boost::split(str_vec, str, boost::is_any_of(separator.c_str()), boost::token_compress_on);
        return str_vec;
    }

    bool FileSystemHelper::copy_dir(
            const std::string& src_dir,
            const std::string& dst_dir,
            const boost::regex& reg,
            const std::string extension /*= "."*/,
            search_option_t search_option /*= search_option_t::TopDirectoryOnly*/,
            bool is_overwrite /*= false*/,
            bool is_show_copy_info /*= true*/) {
        std::vector<std::string> file_vec;
        get_pattern_files_path(file_vec, src_dir, reg, extension, search_option);

        for (int i = 0; i < file_vec.size(); ++i) {
            std::string src_file_path = file_vec[i];
            std::string dst_file_path = replace_file_dir(src_file_path, src_dir, dst_dir);
            std::string dst_file_dir = get_directory_name(dst_file_path);

            if (!create_dirs(dst_file_dir)) {
                return false;
            }

            boost::format form("[%d/%d]: form:[%s] --> to:[%s]");
            form % (i + 1) % file_vec.size() % src_file_path % dst_file_path;

            if (is_show_copy_info) {
                std::cout << form.str() << std::endl;
            }

            if (!copy_file(src_file_path, dst_file_path, is_overwrite)) {
                return false;
            }
        }

        return true;
    }

    std::string FileSystemHelper::trim_head_tail_chars(
            const std::string src_str,
            const std::string trim_str) {
        std::string str_left =
                boost::algorithm::trim_left_copy_if(src_str, boost::is_any_of(trim_str));
        std::string str_right =
                boost::algorithm::trim_right_copy_if(str_left, boost::is_any_of(trim_str));
        return str_right;
    }

    bool FileSystemHelper::is_start_with(
            const std::string& str,
            const std::string& part) {
        if (part.size() > str.size()) {
            return false;
        }

        std::string tmp = str.substr(0, part.size());

        if (std::strcmp(tmp.c_str(), part.c_str()) == 0) {
            return true;
        } else {
            return false;
        }
    }

    std::string FileSystemHelper::string_to_lower(const std::string& str) {
        return boost::to_lower_copy(str);
    }

    std::string FileSystemHelper::string_to_upper(const std::string& str) {
        return boost::to_upper_copy(str);
    }
}



