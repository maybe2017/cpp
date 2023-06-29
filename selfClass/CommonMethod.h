//
// 一些公共方法
//

#ifndef C_CODES_COMMONMETHOD_H
#define C_CODES_COMMONMETHOD_H

#include "iostream"

namespace mayu {
    class CommonMethod {
    public:
        void printArr(const int arr[], size_t length);
    };
}

// 定义函数指针类型，那么就可以让其作为形式参数
typedef void (mayu::CommonMethod::*P_FUNCTION_OF_PRINT_ARR) (const int *, size_t);

#endif//C_CODES_COMMONMETHOD_H
