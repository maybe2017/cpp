//
// 数组指针相关的理解
//

#include <iomanip>
#include <iostream>
using namespace std;

void oneDimensionalArray();

int main() {
    oneDimensionalArray();
}

// 数组名+1，是+数组元素大小的字节数；数组名的地址+1，是+整个数组大小的字节数
// 指针+1，是+指针类型对应字节数；指针的地址+1，是+8
void oneDimensionalArray() {
    // 栈上分配
    int arr[10] = {1, 2, 5, 8, 15, 28, 31, 64, 70, 88};
    // 数组名 表示数组的首地址 即第0号元素地址
    cout << "数组名arr的值为: " << arr << ", &arr[0]: " << &arr[0] << endl;

    // 数组名就是指向第一个元素的指针 可直接用于指针运算
    cout << "数组名称直接运算" << setw(20) << "地址" << setw(26) << "值" << endl;
    for (int i = 0; i < size(arr); ++i) {
        cout << "arr + " << i << setw(27) << long(arr + i) << setw(25) << *(arr + i) << endl;
    }

    // 定义一个指针指向数组首地址
    int *p = arr;
    cout << "指针变量运算" << setw(20) << "地址" << setw(26) << "值" << endl;
    for (int i = 0; i < size(arr); ++i) {
        cout << "p + " << i << setw(27) << (long) p << setw(25) << *p++ << endl;
    }

    // 数组名取地址 &arr 它表示指向这个数据arr对象的地址(注意, 主体不再是数据首元素, 而是针对整个数组对象)
    // 所以 &arr + 1 表示的是, 指针向高地址移动整个数组对象字节长度，后的地址
    // 一般而言，对指针进行加1操作，得到的将是下一个元素的地址，一个类型为T的指针移动，是以sizeof(T)为移动单位。
    cout << "&arr的值(地址): " << (long) &arr << ", (&arr + 1)的值(地址): " << (long) (&arr + 1) << endl;

    // 定义了一个(称为数组指针??)指向了一个一维数组 int(*)[n]
    // 要特别注意指针的类型 类型就决定了运算的时候移动多少距离
    int(*l)[10] = (&arr + 1);
    cout << **l << endl;
}
