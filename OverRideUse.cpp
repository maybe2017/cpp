//
// 运算符重载
// 先说为什么需要重载，为了让自定义的数据类型可以使用
//
#include <iostream>

// 1. 函数名称是编译器起的 operate+ .. operate++(++i: 前置 => 反正加1后的自身， 后置需要用int做形参占位符告诉编译器)
// 2. 可以通过成员函数(类中) 或者全局函数重载
// 3. operator= 赋值运算符的重载 (默认的赋值逻辑: 浅拷贝【与默认的拷贝构造函数有相同的问题】)
// 4. 关系运算符(判断运算符 > < =)的重载  简单
// 5. 函数调用运算符operator()重载 ==>> 仿函数(重载后使用起来类似函数的调用) 灵活(返回值与参数，没有特别要求，随机应变)
class Person {
private:
    int money;
    int age;
    int *height;
public:
    Person(){}
    Person(int money){
        this->money = money;
    }
    Person(int money, int age, int height){
        this->money = money;
        this->age = age;
        this->height = new int (height);
    }


    int getMoney() const {
        return this->money;
    }
    int getAge() const {
        return this->age;
    }


    // 1+1
    // 成员函数: 外部调用的本质：p1.operator+(p2) ==>> 只是可以简化成 p1 + p2 (注意这个形式，被调用者在左边，形参在右边)
    Person operator+(Person &p) {
        return Person(p.money + this-> money);
    }

    // 为什么不能用成员函数重载 左移运算符 << :因为最终的函数调用形式变成了p << count



    // 解决默认赋值运算符 可能导致的析构函数释放多次 相同地址内存的问题（深拷贝解决）
    // 返回值的问题？
    Person& operator=(const Person &p) {
        // 需要先将要占用的指针指向的内存 释放，后续再指向新内存地址
        this->money = p.money;
        this->age = p.age;
        if (this->height != nullptr) {
            delete this->height;
            this->height = nullptr;
        }
        this->height = new int (*p.height);

        return *this;
    }
};

// 全局函数：调用的本质：operator+(p1, p2) ==>> 只是可以简化成 p1 + p2

std::ostream &operator<<(std::ostream &os, const Person &person) {
    os << "money: " << person.getMoney() << ", sex: " << person.getAge();
    return os;
}

int main() {
    Person person1(10000, 20, 170);
    Person person2(20000, 30, 160);
    Person person3;

    person2.operator=(person1);
    person3 = person2 = person1;

    std::cout << person1 << std::endl;

    std::cout << person1.operator+(person2) << std::endl;
    std::cout << person1 + person2 << std::endl;


    // TODO 匿名对象的理解 Person();
    // TODO 匿名函数对象的理解 Person()();
}