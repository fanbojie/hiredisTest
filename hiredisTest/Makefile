#
# make file for redis_test (x86)
#

# 工程目录
TOPDIR = $(shell pwd)
PJNAME = redis_test

ifeq ($(M32), 1)
BITS = 32
else
BITS = 64
endif
#
# 编译器设置
#
# 交叉编译工具前缀，空着表示x86
CROSS = 
# debug还是release，可以在make时加参数，如“make DEBUG=1”
DEBUG = 0
# 编译出的二进制类型，目前支持静态库static，动态库shared，可执行程序exec
BINARY = exec
ifeq ($(BINARY), exec)
TARGET = $(PJNAME)
else ifeq ($(BINARY), static)
TARGET = lib$(PJNAME).a
else ifeq ($(BINARY), shared)
TARGET = lib$(PJNAME).so
endif
# 二进制输出路径
ifeq ($(DEBUG), 0)	
INSTALL_PATH = $(TOPDIR)/Bin/Release
else
INSTALL_PATH = $(TOPDIR)/Bin/Debug
endif

#
# 目录设置
#
# 源文件目录路径
SRCPATH = $(TOPDIR)/Src
# 需要编译的源文件子目录（必须在源文件目录路径之下）
ifeq ($(BINARY), exec)
SRCSUBDIR = main 
endif

# 头文件目录
INCDIR = $(TOPDIR)/Include 

# 链接的库路径（静态库不用）
LIBDIR = $(TOPDIR)/Lib 

# 链接的库（静态库不用）
LIBS = hiredis
# 一些自定义的编译flags（debug和release的一些选项已在common.mk中包含）
CFLAGS = -Wall -fPIC

# 一些自定义的链接flags（静态库不用）
LDFLAGS = 

# 进入实质处理
include $(TOPDIR)/Build/common.mk
