#include "record_logs/log.h"
#include <cstdio>
#include <cstdarg>
#include <ctime>
#include <string>
#include <mutex>
#include <sys/stat.h>
#include <unistd.h>

// 静态全局变量（内部链接，仅在此文件内可见，所有函数共享）
static FILE *log_file = nullptr;
static std::string current_date;
static std::string log_dir = "/home/zzs/catkin_ws/logs";
static std::mutex log_mutex;

// 内部函数：检查日期并切换文件
static void check_date_and_rotate()
{
    time_t now = time(nullptr);
    struct tm *tm_info = localtime(&now);
    char date_buf[11];
    strftime(date_buf, sizeof(date_buf), "%Y-%m-%d", tm_info);
    std::string new_date(date_buf);

    if (new_date != current_date)
    {
        if (log_file)
        {
            fclose(log_file);
            log_file = nullptr;
        }
        std::string filename = log_dir + "/record_log" + new_date + ".log";
        log_file = fopen(filename.c_str(), "a");
        if (log_file)
        {
            current_date = new_date;
        }
        else
        {
            printf("log_dir:%s\n", log_dir.c_str());
            fprintf(stderr, "Failed to open log file: %s\n", filename.c_str());
        }
    }
}

void init_log(const char *dir)
{
    std::lock_guard<std::mutex> lock(log_mutex);
    log_dir = dir;
    printf("日志地址:%s\n", log_dir.c_str());

    // 创建目录（如果不存在）
    if (access(log_dir.c_str(), 0) == -1)
    {
        mkdir(log_dir.c_str(), 0755);
    }
}

void log_printf(const char *format, ...)
{
    std::lock_guard<std::mutex> lock(log_mutex);

    // 检查日期并可能切换文件
    check_date_and_rotate();

    // 获取当前时间戳字符串（用于文件）
    char timestamp[20];
    time_t now = time(nullptr);
    struct tm *tm_info = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    va_list args;
    va_start(args, format);

    // 终端输出
    vprintf(format, args);
    printf("\n");
    fflush(stdout);

    // 文件输出
    if (log_file)
    {
        // 重置 args，因为第一次 vprintf 消耗了参数列表
        va_end(args);
        va_start(args, format);
        // 写入时间戳（不加换行）
        fprintf(log_file, "%s ", timestamp);
        // 写入格式化消息
        vfprintf(log_file, format, args);
        fprintf(log_file, "\n");
        fflush(log_file);
    }

    va_end(args);
}