#ifndef LOG_H
#define LOG_H

// 初始化日志目录（必须在首次调用 log_printf 前调用）
void init_log(const char *log_dir = "./logs");
// 日志打印函数，用法同 printf，自动加换行
void log_printf(const char *format, ...);

#endif // LOG_HPP