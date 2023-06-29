//
// 函数相关
// 1. 普通指针 -> 用于读写目标内存里的值；函数指针 -> 用于调用目标函数!【当知道了一个函数的地址和类型，就能够调用这个函数】
// 2. 全局函数指针 与 类的成员函数指针是不兼容的，因为类的成员函数需要类的实例对象才能进行调用，获取全局、类成员函数地址的方式也不同!
// 3. 函数名就是函数的首地址，指向该函数的指针 也是指向了首地址，但是两者类型不同，例: 函数是
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
         // 也可以通过(*p)(100,200)调用
         p(100, 200);
    }
};


// 函数类型: 返回值为void，参数为(int,int)的函数
// 指向改函数的指针类型: void (int,int)*
// 声明指向这个函数的指针: void (*p)(int,int)
void example(int a, int b) {
    printf("example被调用: a = %d, b = %d; 执行结果: %d\n", a, b, a + b);
}

typedef void (*P_FUNCTION_OF_EXAMPLE) (const int *, size_t);

// 通过函数指针做形参 来调用函数
// 如果传递的是成员函数 它的调用需要依赖于实例对象
// 此处自定义的类实例指针当作上下文对象，通过context传入到你最终的回调函数里面
// 在C++11时期，用std::function来传递函数指针。由于std::function可以绑定一个类成员函数和类实例，因此可以像全局函数那样调用一个类成员函数
void doInvokeFunction(P_FUNCTION_OF_PRINT_ARR p_func, void* context, const int *arr, size_t arrLength) {
    mayu::CommonMethod* t = reinterpret_cast<mayu::CommonMethod*>(context);
    (t->*p_func)(arr, arrLength);
//    // 1. 通过指针调用
//    p_func(arr, arrLength);
//    // 2. 也可以通过函数调用 (函数指针解引用后 就是函数本体)
//    (*p_func)(arr, arrLength);
}

void printArrOfGlobal(const int *arr, size_t length) {
    std::cout << "----遍历开始----" << std::endl;
    if (arr) {
         for (size_t i = 0; i < length; ++i) {
             std::cout << "数组arr[" << i << "]: " << *(arr + i) << std::endl;
         }
    }
    std::cout << "----遍历结束----" << std::endl;
}

template<typename dst_type, typename src_type>
dst_type pointer_cast(src_type src) {
    return *static_cast<dst_type*>(static_cast<void*>(&src));
}

int main() {
//    Book *c = new Book("c++");
//    // 1. 把全局函数的指针做参数 传给类函数
//    c -> getFunctionAddress(&example);

    // 2. 全局函数指针做参数 传给全局函数
    // 下面这两种方式想打印出函数的地址 输出却是1，原因是 << 运算符没有对该函数类型进行重载
//    std::cout << "函数地址为: " << &printArrOfGlobal << std::endl;
//    std::cout << "函数地址为: " << printArrOfGlobal << std::endl;
//
//    // %p表示输出以内存中实际存储一个变量格式的值 (十六进制、视机器而定)
//    printf("地址:%p \n", &printArrOfGlobal);
//    printf("地址:%p \n", printArrOfGlobal);
//
    int arr[10];
//    P_FUNCTION_OF_EXAMPLE p_func = &printArrOfGlobal;
//    doInvokeFunction(p_func, arr, 10);

    // 3. 将类的成员函数做参数 给全局函数使用
    // 要输出动态函数(类中的非静态的成员函数)的地址，必须通过对象来获取。【为什么要取成员函数的地址? 因为可以通过一定的手段 让成员函数作为回调函数, 而不再使用全局的静态函数】
    using namespace mayu;
    CommonMethod commonMethod;
//    P_FUNCTION_OF_PRINTARR p_func_printArr = &commonMethod.printArr;

    P_FUNCTION_OF_PRINT_ARR p_func_test = &CommonMethod::printArr;
    doInvokeFunction(p_func_test, arr, 10);

//    P_FUNCTION_OF_PRINT_ARR p_func_printArr1 = pointer_cast<P_FUNCTION_OF_PRINT_ARR>(&CommonMethod::printArr);
//    doInvokeFunction<P_FUNCTION_OF_PRINT_ARR>(p_func_printArr1, arr, 10);

}


