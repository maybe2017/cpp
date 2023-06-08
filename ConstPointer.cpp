//
// 常量指针 与 指针常量
//
#include <iostream>
using namespace std;

void testConstPointer();

int main() {
    testConstPointer();
}

// 常量指针 (记忆:指向常量的指针)
// 强调: 不能通过指针改变指向对象的值
void testConstPointer() {
    int i = 10;
    const int *p = &i;
    // *p = 100; // error 不能通过指针改变指向对象的值
    cout << "常量指针p保存的地址: " << p << endl;

    // 但是可以指向另一个常量
    int j = 100;
    p = &j;
    cout << "常量指针p保存的地址: " << p << endl;
}

// 指针常量 (记忆:指针保存的地址是常量, 只读) ==>> 引用的本质
// 强调: 不能改变指针 的指向, 即保存的地址
void testPointConst() {
    int i = 10;
    int* const p = &i;

    // 可以通过指针来改指向对象的值
    *p = 100;

    // 但是不能指向另一个地址
    int j = 100;
//    p = &j;
}
