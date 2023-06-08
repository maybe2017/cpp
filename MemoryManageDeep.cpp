//
// 深入理解c++的内存分配及释放
//
#include "selfClass/Conversation.h"
#include <iomanip>
#include <iostream>
using namespace std;

void explainNewExpression();
void explainDeleteExpression();

int main() {
    explainNewExpression();
//    explainDeleteExpression();
}

// new 表达式的实现(==>> operator new ==>> malloc)
void explainNewExpression() {
    using mayu::Person;
    auto *p = new Person();

    // new表达式 编译器的实现
    // 第一步: 分配内存, 返回一个任意类型的指针, 如果分配失败返回空指针？失败就不会调用构造函数
    // (operator new底层是用malloc实现的, while中提供回调函数供释放内存, 以使下一次循环能成功分配)
    void *p1 = ::operator new(sizeof(Person));
    // 第二步: 强转指针为Person类型
    auto *p2 = static_cast<Person *>(p1);
    // 第三步: 调用构造函数
    //    p2 -> Person::Person(); // error 不能直接调用 vc可以 gunc不行

    // 可以用placement new实现 (内存已经分配好了 定点调用构造函数)
//    new (p2) Person();
    new (p2) Person(30, "男", true);

    cout << "对象内容: " << p2 << endl;
}

// delete 表达式的实现(==>> operator delete ==>> free)
void explainDeleteExpression() {
    using mayu::Person;
    auto *p = new Person();
    // 这样就释放了
//    delete p;


    // delete表达式 编译器的实现
    // 第一步: 调用析构函数(如果有)
    p -> Person::~Person();
    // 第二步: operator delete 释放内存, 底层是用free(p);
    ::operator delete (p);
}

// array new 与array delete
void explainArrayNewOrDelete() {

    // 对于非指针类型的数组 如基本类型的数组
    int *pi = new int[3];
    // delete p 效果等同delete []p; 因为基本类型不存在析构函数
    delete []pi;


    using mayu::Person;
    // 必须要有默认构造函数 才能定义数组类型
    // p指向了数组首元素的地址
    auto *p = new Person[3];

    // 如果用delete p; 只是调用一次析构函数, 那么就会造成内存泄露
    // delete []p; malloc分配内存的时候会有个cookie保存了分配的长度3, 所以可以知道应该调用多少次析构函数
    delete []p;
}

