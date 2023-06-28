//
// 函数相关
// 普通指针 -> 用于读写目标内存里的值；函数指针 -> 用于调用目标函数!【当知道了一个函数的地址和类型，就能够调用这个函数】
//

#include "selfClass/CommonMethod.h"
#include <iostream>
#include <string>
// 当使用前向引用声明时，只能使用被声明的符号，而不能涉及类的任何细节
// 只能定义指针、引用、以及用于函数形参的指针和引用
class Book;
class Person;

class Person{
private:
    // Book book; 错误, 类声明不完整, 不能定义该对象
    // 因为此时编译器只知道这是个类，还不知道这个类的大小有多大
    Book *book = nullptr; // 可以用指针 指针所占内存字节数是固定的 32位系统4字节 64位系统8字节
public:
    void printBookDetails(Book book); // 可以在函数声明 形参使用
};

class Book{
private:
    std::string bookName;
public:
    Book(){}
    Book(std::string name) {
        this->bookName = name;
    }

    std::string getName() {
        return this ->bookName;
    };

    // 这个函数指针的类型是: void (int,int)*
    static void getFunctionAddress(void (*p)(int,int)) {
         std::cout << "函数地址为: " << &p << ", 通过函数指针进行函数调用: " << std::endl;
         p(100, 200);
    }
};


// 函数类型: 返回值为void，参数为(int,int)的函数
// 指向改函数的指针类型: void (int,int)*
// 声明指向这个函数的指针: void (*p)(int,int)
void example(int a, int b) {
    printf("example被调用: a = %d, b = %d; 执行结果: %d\n", a, b, a + b);
}

//typedef void (*P_FUNCTION_OF_EXAMPLE) (const int *, size_t);

// 通过函数指针做形参 来调用函数
void doInvokeFunction(P_FUNCTION_OF_EXAMPLE p_func, const int *arr, size_t arrLength) {
    p_func(arr, arrLength);
}
void printArr(const int *arr, size_t length) {
    std::cout << "----遍历开始----" << std::endl;
    if (arr) {
         for (size_t i = 0; i < length; ++i) {
             std::cout << "数组arr[" << i << "]: " << *(arr + i) << std::endl;
         }
    }
    std::cout << "----遍历结束----" << std::endl;
}

int main() {
    Book *c = new Book("c++");
    c -> getFunctionAddress(&example);
    int arr[10];
//    P_FUNCTION_OF_EXAMPLE p_func = &printArr;
    using namespace mayu;
    P_FUNCTION_OF_EXAMPLE p_func = &CommonMethod::printArr;
//    doInvokeFunction(&mayu::CommonMethod::printArr, arr, 10);
    doInvokeFunction(p_func, arr, 10);
}


