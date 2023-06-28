//
// 数组指针相关的理解
// 指针数组、及以 数组为元素的 数组指针的区别
//

#include <iomanip>
#include <iostream>
using namespace std;

void oneDimensionalArray();
void initArry();

int main() {
    initArry();
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

    // 减法运算的值为两个指针在内存中的距离（以数组元素的长度为单位，而非字节）
    ptrdiff_t diff = (&arr + 1) - &arr;
    cout << "&arr的值(地址): " << (long) &arr << ", (&arr + 1)的值(地址): " << (long) (&arr + 1) << ", (&arr + 1) - &arr: " << diff << endl;

    // arr称为数组名、数组指针
    // []和()的优先级比星号（星号的名字叫做'指针运算符'）要高, []和()同级就按从左到右
    // l是一个数组类型元素的指针(试着用int类型理解), 这个元素具体的特点是: 类型是长度为10的数组 (类型是int[10])
    // 定义了一个(称为数组指针的数组), l指向第一个一维数组的首地址 (实际上，l相当于是一个二维指针)
    // 要特别注意指针的类型(长度为10的一维数组类型)  类型就决定了运算的时候移动多少距离(4*10)
    int (*l)[10] = (&arr + 1);
    cout << "第一个一维数组的首地址: " << (long )*l << ", 第二个一维数组的首地址: " << (long )(*(l + 1)) << endl;


    // 指针数组
    // 按优先级看 int * (pl[2]); pl首先是个数组, 数组元素是指针类型
    int *pl[2];
}

// 数组的定义
void initArry() {
    int length = 5;
    new int(5);

    // 这样定义时 元素的默认值是随机的
    int arr[length];
    cout << "数组中的元素不会默认初始化" << setw(20) << "地址" << setw(26) << "值" << endl;
    for(int i = 0; i < length; i++) {
        cout << "arr + " << i << setw(27) << long(arr + i) << setw(25) << *(arr + i) << endl;
    }

    cout << "=======================" << endl;

    // 用static修饰时 长度不能用变量length指定.. 而需要用常量/常量表达式指定
    // 这样定义时 元素的默认值为0
    const int staticLength = 5;
    static int staticArr[staticLength];
    cout << "数组名称直接运算" << setw(20) << "地址" << setw(26) << "值" << endl;
    for(int i = 0; i < length; i++) {
        cout << "staticArr + " << i << setw(27) << long(staticArr + i) << setw(25) << *(staticArr + i) << endl;
    }
}
