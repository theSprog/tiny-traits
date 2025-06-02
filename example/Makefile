# 编译器
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -O2

# 源文件和目标文件
SRCS := $(wildcard *.cpp)
BINS := $(patsubst %.cpp, build/%, $(SRCS))

# 默认目标：编译所有二进制文件
all: $(BINS)

# 规则：将每个 .cpp 编译成 build/ 中的同名二进制
build/%: %.cpp | build
	$(CXX) $(CXXFLAGS) $< -o $@

# 生成 build 目录
build:
	mkdir -p build

# 清理生成的二进制文件
clean:
	rm -rf build

.PHONY: all clean

