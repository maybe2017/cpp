//
// 函数相关
//

#include <string>

class Person;

int main() {
    typedef Person P;
    P mayu = new P();
}

// 当使用前向引用声明时，只能使用被声明的符号，而不能涉及类的任何细节
// 只能定义指针、引用、以及用于函数形参的指针和引用
class Book;

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
};