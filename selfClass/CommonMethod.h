//
// 一些公共方法
//

#ifndef C_CODES_COMMONMETHOD_H
#define C_CODES_COMMONMETHOD_H

#include "iostream"

// 定义函数指针类型，那么就可以让其作为形式参数
typedef void (*P_FUNCTION_OF_EXAMPLE) (const int *, size_t);

namespace mayu {
    class CommonMethod {
    public:
        void printArr(const int arr[], size_t length);
    };
}
#endif//C_CODES_COMMONMETHOD_H
