//
// Created by 马瑜 on 2023/5/24.
//
#include <cstdio>
#include <iostream>
#define DEFAULT_CHANNEL "default"

void testBaseType();
void printCurrentCompilerInfo();

int main(){
    using namespace std;
    // 常量
    const int weekDay = 7;
    testBaseType();
    std::cout << "---------当前编译器信息---------" << std::endl;
    printCurrentCompilerInfo();
}

// 基本类型 char1 boolean1 short2 int4 long4(32bit) long8 / long long8 float4 double8
void testBaseType() {
    using namespace std;

    // 8位至多表示256个字符 可以存储一个ASCII码值
    // 许多外文字符集所含的字符数目超过256个，char型无法表示
    char c = 130;

    cout << "如果存一个大于127的数字，截断后的值为: " << (int)c << endl;

    // wchar_t 通常用于表示Unicode字符集，而Unicode字符集中的每个字符通常需要两个字节的存储空间
    // Windows下，宽字符类型wchar_t占2个字节（byte）；在Linux下，wchar_t占4个字节
    wchar_t wc = 'A';

    cout << "窄字符char占字节数: " << sizeof c << ", 当前编译器对char的范围: " << CHAR_MIN << "--" << CHAR_MAX<< endl;
    cout << "宽字符类型wchar_t占字节数: " << sizeof wc << ", 当前编译器对wchar_t的范围: " << WCHAR_MIN << "--" << WCHAR_MAX << endl;
    cout << "64bit系统上long占字节数: " << sizeof(long) << ", long long占字节数: " << sizeof(long long) << endl;

    bool t1 = true;
    bool t2 = false;
    std::cout << "bool变量值为true的打印值: " << t1 << "\t" << "bool变量值为false的打印值: " << t2 << endl;
}
/**
 *  __cplusplus: 表示C++版本是否支持，如果为2011年或更高版本，则返回1,否则返回0。
 *  __DATE__: 表示编译器编译的日期。
 *  __TIME__: 表示编译器编译的时间。
 *  __VERSION__: 表示编译器的版本号。
 *  __PRETTY_FUNCTION__: 表示当前函数的完整定义，包括参数列表
 */
void printCurrentCompilerInfo() {
    std::cout << "Compiler information:" << std::endl;
    std::cout << "Compiled as C++ " << __cplusplus << '.' << __VERSION__ << std::endl;
    std::cout << "Date compiled: " << __DATE__ << std::endl;
    std::cout << "Time compiled: " << __TIME__ << std::endl;
    std::cout << "Function: " << __PRETTY_FUNCTION__ << std::endl;
}