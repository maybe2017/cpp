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

    // 拷贝构造函数(如果只提供了拷贝构造函数，编译器就不会再提供其他默认构造函数)
    // TODO 试试编译器提供的默认拷贝 看看属性是怎么赋值的 ==>> (编译器只是提供了对属性的浅拷贝)，如果属性中存在堆中对象，可能会被析构多次（两个对象的属性的地址相同，同一地址被释放了两次）
    Test(const Test &test) {
        std::cout << "Test拷贝构造函数被调用: "<< std::endl;
        this->price = test.price;
        this->age = test.age;
//        this->p = test.p;
        this->p = new mayu::Person();
    }

    ~Test(){
        std::cout << &(*this) << ",Test析构函数被调用 "<< std::endl;
        if (p != nullptr) {
            delete p;
            p = nullptr;
        }
    }

    int getAge() {
        // 隐式包含
        std::cout << this->age << std::endl;
        return this->age;
    }
    int getAge2() {
        std::cout << "getAge2被成功调用!" << std::endl;
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
void testCopyConstructor();
int main() {
//    testCopyConstructor();
    std::cout << "-----------------------"  << std::endl;

//
//    Test *t =  testReturnPointer();
//    std::cout << "函数体外指针变量本身的地址: " << &t << std::endl;
//
//    mayu::Person p = mayu::Person(30, "男", true);
//    std::cout << p << std::endl;

//    TestImport *i = new TestImport(30);
//    std::cout << i->getAge() << std::endl;

    // 栈上
//    Test testA(20.0, 30);

    // 空指针也可以访问类函数 注意函数内是否用到this
//    Test *testB = nullptr;
//    testB->getAge2();
//    testB->getAge();

    // const的涵义 表示只读 不能修改
    // 常对象 只能调用 常函数：目的都是为了不能更改属性值(确保只读)
//    system("pause");
}

// 编译器提供的 默认拷贝构造函数 的问题
void testCopyConstructor() {
    Test t3 = Test(50, 100);
    Test t4(t3);
    std::cout << t3.getAge() << "," << t3.getPrice() << std::endl;
    std::cout << t4.getAge() << "," << t4.getPrice() << std::endl;
}

// 编译器提供的 赋值浅拷贝 的问题
void testAssign() {
    Test t3 = Test(50, 100);
    Test t4 = Test(60, 900);
    t4 = t3;

    std::cout << t3.getAge() << "," << t3.getPrice() << std::endl;
    std::cout << t4.getAge() << "," << t4.getPrice() << std::endl;
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