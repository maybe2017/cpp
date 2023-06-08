//
// 理解c++中的指针与引用
//
#include <iomanip>
#include <iostream>
#include "arg/BinarySearch.h"

using namespace std;

void testPointer();
void testRef();

int main() {
    testPointer();
    testRef();
}

// 指针变量保存了一个内存地址
// 这个地址是一个数值 那么就可能为0(空指针) 也可能指向一个没有权限的内存地址(野指针)
// 所以在函数中, 要对形参是指针的变量, 进行空判断
// 指针本身占用内存都是一致的, 为啥需要类型? 1: 决定了解引用时能够访问的空间大小(操作的字节数); 2: 决定了指针运算时一步能走多远（指针的步长）
void testPointer() {
    int i = 10;
    int *p = &i;

    // typeid 会把获取到的类型信息保存到一个 type_info 类型的对象里面，并返回该对象的常引用
    // typeid 操作数可以是普通变量、对象、内置类型（int、float等）、自定义类型（结构体和类），还可以是一个表达式
    // 可以是指针吗？指针变量也是一个对象
    const type_info &info = typeid(p); //？
    cout << "指针变量p的类型: " << info.name() << ", 该类型所占字节数: " << sizeof(info) << endl;
}

// 引用的实质是一个指针常量, 保存的内存地址值不能改变, 但是可以通过这个地址来改变地址上对象的内容
// 可以理解为: 引用也同指针一样, 保存了一个地址。这个地址不能再改变, 所以表现为refI不能再绑定其他对象
// 引用变量依附于(绑定)另一个变量 所以不能为空?

// 引用已经决定了指向对象的地址不能变, 加上const只是需要讨论指向对象的内容是否能变
// 常量引用可以绑定常量, 也可以绑定变量, 只是不能通过其去改变 保存的内存地址对应对象的内容


// 在函数形参上 用引用: 避免直接使用对象拷贝传参方式的缺点 (大对象拷贝需要时间、空间)
void testRef() {

    int *i = nullptr;
    int &refI = *i; // 居然不会提前报错...
    cout << "refI: " << refI << endl;

    // 定义一个常量
    const int j = 0;
    // 常量必须用常量引用来绑定 绑定后就不能通过 refJ这个引用 来改变地址上对象的内容了
    const int &refJ = j;

    // 定义一个变量
    int y = 10;
    // 变量也可以常量引用 绑定, 只是后续也不能 通过refY这个引用 来改变地址上对象的内容了
    const int &refY = y;


}

// 使用引用做函数 形参
void invokeFunctionByUseRefParam() {

}
