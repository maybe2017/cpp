//
// 深入理解c++的内存分配及释放
// 1. delete 和 delete[] 都会完全释放new开辟的所有内存；只是delete只会调用一次析构函数(可能是正序或者逆序的第一个元素)
// 2. 系统资源不被释放的后果:
//    ==>> 如果是Socket，导致端口号一直被占用，就可能出现不能上网等情况;
//    ==>> 如果是File，导致不能修改或读这个文件 (除非注销或重器系统);
//    ==>> 如果是Thread，导致它一直在后台运行，浪费内存和CPU资源;
// 3. 在释放内存时，仅仅释放new出来的对象的内存往往是远远不够的，因为对象还可能申请了其他内存或系统资源，必须在对象的析构函数中将这些申请的资源统统释放掉
//
#include "selfClass/Conversation.h"
#include <iomanip>
#include <iostream>
using namespace std;

void explainNewExpression();
void explainDeleteExpression();

int main() {
    explainNewExpression();
    explainDeleteExpression();
}

// new 表达式的实现(==>> operator new ==>> malloc)
// malloc 申请空间失败时，返回的是 NULL，因此使用时必须判空，new 不需要，但是 new 需要捕获异常
// malloc 和 free 是函数，new 和 delete 是操作符
void explainNewExpression() {
    using mayu::Person;
    auto *p = new Person();
    delete p;

    // new表达式 编译器的实现
    // 第一步: malloc分配内存, 返回一个任意类型的指针, 如果分配失败返回空指针？失败就不会调用构造函数
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

// delete 表达式的实现(先析构 ==>> operator delete ==>> free)
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
    // operator new来分配空间之后 会马上为每个元素调用构造函数
    // p指向了数组首元素的地址
    auto *p = new Person[3];

    // 如果用delete p; 只是调用一次析构函数(可能是正序或者逆序的第一个元素), 那么就可能会造成内存泄露
    // 注意: delete 和 delete[] 都会完全释放new开的所有的内存, 内存泄露的原因在于析构函数只被调用了一次
    // 如果类中使用了操作系统资源(Socket、File、Thread等)
    // 因为没有调用对象的析构函数会导致系统资源不被释放，如果是Socket则会造成Socket资源不被释放，最明显的就是端口号不被释放，系统最大的端口号是65535(216 _ 1，因为还有0)，如果端口号被占用了，你就不能上网了，呵呵。如果File资源不被释放，你就永远不能修改这个文件，甚至不能读这个文件(除非注销或重器系统)。如果线程不被释放，这它总在后台运行，浪费内存和CPU资源。这些资源的释放必须依靠这些类的析构函数
    // delete []p; malloc分配内存的时候会有个cookie保存了分配的长度3, 所以可以知道应该调用多少次析构函数
    delete []p;
}

