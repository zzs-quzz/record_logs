#include "record_logs/log.h"
#include <string>

int main(int argc, char **argv)
{
    std::string log_dir = "/home/zzs/catkin_ws/logs"; // 需修改
    init_log(log_dir.c_str());
    for (size_t i = 0; i < 5; i++)
    {
        log_printf("i=%d", i);
    }
    return 0;
}
