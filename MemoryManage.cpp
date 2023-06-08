//
// include引入头文件, 头文件中只是包含了常量、变量、方法、对象等声明
// 头文件只是作用与Bulid的预处理阶段 不会被编译
//
#include <iomanip>
#include <iostream>
using namespace std;

// 预声明
int *testReturnAddress();
int *testReturnDumpAddress();
void testDeleteArray();
unsigned long calcArrayLength(int arr[]);
void testTypeId();

int main() {
    cout << "-----------函数返回栈上变量的指针-----------" << endl;
    // 地址给了p 但是马上栈内存被回收了
    int *p = testReturnAddress();
    // ？为啥第一次仍然可以用地址去取值？ 编译器会暂存？
    cout << (int) *p << endl;
    // 第二次就不行了，因为test函数的栈内存已经被回收
    cout << (int) *p << endl;

    cout << "-----------函数返回堆上对象的指针-----------" << endl;

    // 堆上地址给dump 但是堆上对象是没有被回收的 所以用该地址永远能访问到该对象
    int *dumpP = testReturnDumpAddress();
    cout << (int) *dumpP << endl;
    cout << (int) *dumpP << endl;

    cout << "-----------数组的定义及删除-----------" << endl;
    testDeleteArray();


    cout << "-----------数组计算长度的测试-----------" << endl;
    int arr[10] = {0, 1, 2};
    cout << "arr的长度: " << calcArrayLength(arr) << endl;

    cout << "-----------typeid操作符的测试-----------" << endl;
    testTypeId();
    return 0;
}

// 返回栈上变量的地址
int *testReturnAddress() {
    // 栈上分配
    int a = 10;
    return &a;
}

// 返回堆上对象的地址 特别注意new关键字 用以在堆上创建一个对象，返回一个指针
// 动态分配堆区内存，必须手动释放，否则只能等到程序运行结束由操作系统回收
int *testReturnDumpAddress() {
    // 创建一个int类型的对象 值为10
    return new int(10);
}

// 数组的定义初始化 及 删除
void testDeleteArray() {
    // ？
    constexpr size_t size = 5;

    // 栈上分配 初始化的元素个数不能大于 指定的size, 未被初始化的内存位置值为默认值0？
    int arr[size] = {1};
    int *arr_p = arr;
    // 自动计算size
    int arr1[] = {1, 2, 3};

    cout << "数组名arr的值: " << arr << ", arr[0]的地址: " << &arr[0] << endl;

    // 计算数组size -> 用sizeof(arr): 计算arr数据占用的字节数
    // sizeof 是一个运算符，不是函数；sizeof 运算符的结果结果类型是size_t

    // size_t 是由 typedef 机制定义出来的”新”类型；通常做为作为无符号长整型 unsigned long 的别名，表示目标平台上最大可能对象的大小;
    // 该类型所占大小与指针一致，都是32位系统占4字节；适合表达指针地址值
    // ptrdiff_t是有符号整数，从字面意思就能知道: 两个指针地址(无正负)的差(有正负)
    // size_t 可能会提高代码的可移植性、有效性或者可读性(它语义上代表字节大小或数组索引)
    // https://code-examples.net/zh-CN/q/202db
    size_t arrSize = sizeof(arr);
    cout << "arr数组占用字节数 -> sizeof(arr) : " << (int) arrSize << ", arr数组长度: " << sizeof(arr) / sizeof arr[0] << endl;

    // setw(n) 只对紧跟其后的输出内容有效 设置输出内容的宽度，不够n字节数则用空格填充
    cout << setw(7) << "arr数组下标" << setw(20) << "位置存储的值" << endl;
    for (int i = 0; i < size; ++i) {
        cout << setw(7) << i << setw(15) << arr[i] << endl;
    }


    cout << "中文'数组'子面量占用字节数:" << sizeof "数组" << endl;
    cout << "中文'数组'子面量所属类型:" << typeid("数组").name() << endl;

    cout << "指针变量arr_p 的类型:" << typeid(arr_p).name() << ", arr_p(表示指向数组的第一个元素的地址) 的值为: " << arr_p << endl;


    // typeid 运算符, 会把获取到的类型信息保存到一个 type_info 类型的对象里面，并返回该对象的常引用
    // 当需要具体的类型信息时，可以通过该对象的成员函数来提取



    // &arr 类型是PA3_i，表示指向arr类型的指针
    const type_info *typeOfArr1 = &typeid(&arr);
    cout << "&arr 的类型: " << typeid(&arr).name() << ", &arr所属类型占字节数: " << sizeof(typeOfArr1) << ", &arr 的值为: " << &arr << endl;
    // 数组名arr的类型并不是指针类型
    const type_info *typeOfArr = &typeid(arr);
    cout << "数组名arr 真正的类型: " << typeid(arr).name() << ", arr所属类型占字节数: " << sizeof(typeOfArr) << ", arr的值为: " << arr << endl;

    // 堆上分配
    //    int *arrPointer = new int[] {1, 2, 3};
}

// 为啥计算出来的长度要么输出1要么输出2 ??
unsigned long calcArrayLength(int arr[]) {
    size_t length = sizeof(arr) / sizeof(arr[0]);
    return length;
}

// 测试typeid 操作符的用法
void testTypeId() {
    // 测试是否能输出普通类型
    int i = 10;
    int *p = &i;

    long l = 100L;
    long *lp = &l;

    const type_info &iInfo = typeid(i);
    const type_info &pInfo = typeid(p);
    const type_info &lpInfo = typeid(lp);

    cout << "变量i 的类型name:" << iInfo.name() << endl;
    cout << "指针变量p 的类型name:" << pInfo.name() << endl;
    cout << "指针变量lp 的类型name:" << lpInfo.name() << endl;


}