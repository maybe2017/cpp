//
// cpp文件中，为引入的.h头文件中的只是声明了的方法 进行定义
// 疑问: 自己定义h文件中的声明, 已经在cpp里面真正的定义了，可以理解;
// 但是比如引用的是#include <iostream>这类标准库的h文件, 定义cpp文件是在什么时候、如何加载的呢？
//

#include "BinarySearch.h"
int BinarySearch::binarySearch(const int (&arr)[], int target) {
    return 0;
}
int BinarySearch::binarySearch(const int *const arr, int target) {
    return 0;
}
