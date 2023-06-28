//
// static关键字的使用
// 修饰全局成员: 全局普通成员作用域(默认是extern的)是整个源程序，其他源文件可以访问，而static全局成员作用域是本文件（const修饰的变量可以通过extern来对外暴露）；
// 修饰类成员: 属于类层级，类的静态成员变量、函数在类加载的时候就会分配内存
// 修饰类对象: 普通对象可以通过extern跨文件访问，静态对象只能本文件访问

// 内存初始化的时机：全局变量、静态全局变量和类的静态成员变量在main执行之前的静态初始化过程中分配内存并初始化；局部静态变量在第一次使用时分配内存并初始化
// 静态对象如果在函数内，执行的时候才会构造，在函数外，全局static类对象在main前构造。

#include "iostream"
using namespace std;

void testStaticOfVar(int initValue);
void printArr(const int arr[], size_t length);
void testStaticOfArr(int initValue);

int main() {

    // 多次调用，但是static修饰的局部变量只会被初始化一次
    testStaticOfVar(1);
    testStaticOfVar(2);

    // 在函数内部，普通数组中的元素值不会被默认初始化，随机的；但是static修饰的数组，元素均会被默认初始化为0
    testStaticOfArr(10);
}

void testStaticOfVar(int initValue) {
    // 内存初始化的时机：第一次使用时分配内存并初始化(毕竟是函数体内部)
    static int i = initValue;
    cout << "static修饰局部变量(静态局部变量) i: " << i << endl;
}

void testStaticOfArr(int initValue) {
    int arr[initValue];
    printArr(arr, initValue);

    // 不能用变量去定义static数组的长度 需要编译期就能得到结果的常量表达式 来定义数组的长度
    const int initValueOfStatic = 10;
    static int staticArr[initValueOfStatic];
    printArr(staticArr, initValueOfStatic);
}

void printArr(const int arr[], size_t length) {
    cout << "----遍历开始----" << endl;
    if (arr) {
        for (size_t i = 0; i < length; ++i) {
            cout << "数组arr[" << i << "]: " << *(arr + i) << endl;
        }
    }
    cout << "----遍历结束----" << endl;
}