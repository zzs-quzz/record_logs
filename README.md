# 记录日志
## 1. 项目介绍
在Linux系统中，使用c++记录日志信息。
## 2. 使用方法
本项目开发平台信息如下：
- 系统版本：Ubuntu 20.04
- ROS_DISTRO：Noetic
### 2.1 下载
使用git clone下载安装
```shell
git clone https://github.com/zzs-quzz/record_log.git
```
### 2.2 安装依赖
无需依赖
### 2.3 运行
1. 构建功能包
```
catkin_make
```
2. 运行测试程序
```
./devel/lib/record_logs/ceshi
```
## 3. 其他功能包使用
- 修改CMakeLists.txt：注释add_executable和target_link_libraries
## 4. 作者
- [zzsquzz](https://github.com/zzs-quzz)