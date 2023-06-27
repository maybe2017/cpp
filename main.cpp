#include <iostream>
#include "selfClass/Conversation.h"
#include "selfClass/TestImport.h"
class Test {
private:
    double price;
    int age; // 实例变量 对象
    mayu::Person *p;
    static int count; // 类变量 类
public:
    Test() {
    }
    Test(double price, int age) {
        this->price = price;
        this->age = age;
        this->p = new mayu::Person();
    }
    ~Test(){
        std::cout << &(*this) << ",析构函数被调用 "<< std::endl;
        if (p != nullptr) {
            delete p;
            p = nullptr;
        }
    }

    int getAge() {
        // 隐式包含
        return this->age;
    }

    void getPersonMarried() {
        std::cout << this->p->isMarried() << std::endl;
    }

    double getPrice() {
        // 隐式包含
        return this->price;
    }

    static int getAgeOfStatic() {

        return count;
    }

    static int setAgeOfStatic() {
        return count = 5;
    }
};
// 编译期 运行时
int Test::count = 4;

void handle();
Test * testReturnPointer();
int main() {
    Test *t =  testReturnPointer();
    std::cout << "函数体外指针变量本身的地址: " << &t << std::endl;

    mayu::Person p = mayu::Person(30, "男", true);
    std::cout << p << std::endl;

//    TestImport *i = new TestImport(30);
//    std::cout << i->getAge() << std::endl;

    // 栈上
//    Test testA(20.0, 30);
//    Test testB;
//    std::cout << testA.getAge() << std::endl;
//    std::cout << testB.getAge() << std::endl;
//    std::cout << testA.getPrice() << std::endl;

}

void handle() {
    // 堆上
    Test *p1 = new Test(20.0, 30);
//    Test *p2 = new Test();
    std::cout << p1->getAge() << std::endl;
    delete p1;
}

// 测试返回值为指针时 是否进行了拷贝操作
Test * testReturnPointer() {
    Test *p1 = new Test(20.0, 30);
    std::cout << "函数体内指针变量本身的地址: " << &p1 << std::endl;
    return p1;
}