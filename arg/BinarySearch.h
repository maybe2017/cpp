/**
 * C++的Build阶段:
 * -> 预处理(宏替换、.h头文件引入、条件编译、去掉注释, 生成.i文件)
 * -> 编译(语法检查, 生成汇编代码, 生成.s文件)
 * -> 汇编(把汇编代码转为机器指令, 一般每个源文件.cpp生成一个二进制文件.o)
 * -> 链接(符号引用->直接引用? 找到指令的内存地址; 将多个.o文件链接成一个可执行文件或库文件等)
 */

#ifndef C_CODES_BINARYSEARCH_H
#define C_CODES_BINARYSEARCH_H

// 在cpp文件中，完成函数的实现，在h文件中进行函数的声明

class BinarySearch {

public:
    int binarySearch(const int (&arr)[], int target);
    int binarySearch(const int* const arr, int target);
};


#endif//C_CODES_BINARYSEARCH_H
