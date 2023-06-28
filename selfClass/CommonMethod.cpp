#include "iostream"
#include "CommonMethod.h"
namespace mayu {
    void CommonMethod::printArr(const int *arr, size_t length) {
        std::cout << "----遍历开始----" << std::endl;
        if (arr) {
            for (size_t i = 0; i < length; ++i) {
                std::cout << "数组arr[" << i << "]: " << *(arr + i) << std::endl;
            }
        }
        std::cout << "----遍历结束----" << std::endl;
    }
}