//
// 继承
// 1. 创建子类对象的时候，也会先创建父类的对象(这点需要理解，先调用父类构造函数，再调子类构造函数，析构时相反)
// 2. 菱形继承的问题，用virtual虚继承解决(派生类 不再是继承 虚基类 的真实数据成员，而是继承的是一个虚基类指针virtual base class pointer -> 虚基类表(保存了内存偏移))
// 3. 如何理解虚继承？ ==>> 一旦有了虚基类，调用基类成员的时候就要在运行时才能推断对应成员的地址偏移量; 大部分编译器实现为此引入了虚基类表，因此要为每个对象额外保存虚基类指针来进行间接引用
// 4. 如何理解地址早绑定？为什么父类虚函数就能实现晚绑定？(父类引用或指针 调用函数时) ==>> 一旦有了虚函数，调用函数的时候就要在运行时才能推断对应的函数入口
// 5. 每个实际对象都在自己的“头部” hold 着一个或多个虚函数表地址。对象头顶的这些虚函数表地址，实际上就定义了这个对象具有的个性化行为。注意，多态，延迟绑定，动态绑定，是面向对象思想的精髓
// 6. 思考: 能否都用虚继承和虚析构函数？如果都可以，那么非虚继承与非虚析构存在的意义是什么？

// 多态
// 1. 当类中有虚函数时，类创建对象时，会让对象拥有一个虚函数表指针【虚函数表指针是属于对象的，每个对象都会有一个，与成员变量一样，占用固定字节数】
// 虚函数表指针 指向了一个 虚函数表【这个表内记录了类中所有虚函数的地址】

// 2. 当子类继承 有虚函数的父类时，子类对象也会继承 父类对象的虚函数表指针【如果继承多个父类，子类对象是否只有一个虚函数表指针?】
// 存疑: 父类的虚函数表指针、与子类的虚函数表指针是一样的吗？ ==>> 虚表都不一样，指针肯定不一样咯!
// 子类也会有一个虚函数表【子类和父类各自拥有虚函数表，只是在子类没有重写父类虚函数时，表中的虚函数地址一样】

// 3. 当子类覆写了父类的虚函数，子类的虚函数表中，对应的虚函数地址就会被 覆盖(用子类自己的函数地址)

// ==>> 那么导致，当再用父类引用或指针指向子类对象，且调用成员函数时，(此处要先理解为啥函数地址没有早绑定，其次是成员函数的调用实际上是 __thiscall调用)，会通过实例对象 的虚函数表指针，去虚函数表找到 函数地址，进而进行调用。


// 多态的注意点
// 1. 用delete释放父类引用或指针时，只会调用父类的析构，不会调用子类的析构（为什么？还是地址早绑定的问题？） ==>> 解决办法：使父类析构函数为虚函数
// 2. 疑问点：析构函数能否被继承？有没有子类重写父类析构的说法？？ ==>> 析构函数不能被继承，这是规定，同样不能被继承的还有构造函数、赋值运算符和友元函数。
// 3. C++标准规定了编译器实现，派生类对象析构时，会自动(隐含)地调用父类的析构函数。【这点务必要理解】

#include <iostream>
class Base{
private:
    int i;
public:
    Base(){
        std::cout << "Base构造被调用" << std::endl;
    }
    // 纯虚析构(强制子类重写析构)
//    virtual ~Base() = 0;
    virtual ~Base(){
        std::cout << "Base虚析构被调用" << std::endl;
    };

    // 虚函数
    virtual void print() {
        std::cout << "Base print被调用" << std::endl;
    }

    // 纯虚函数
    virtual void fun() = 0;

    // final 不允许子类重写
    virtual void funcOfFinal() final {
        std::cout << "Base funcOfFinal被调用" << std::endl;
    };
};
//Base::~Base() {
//    std::cout << "Base析构被调用" << std::endl;
//    //
//}

// 被声明为final的类不能继续派生
class Child final : public Base {
private:
    int self;
public:
    Child(){
        std::cout << "Child构造被调用" << std::endl;
    }
    ~Child(){
        std::cout << "Child析构被调用" << std::endl;
    }
    void print() override {
        std::cout << "Child print被调用" << std::endl;
    }
    virtual void fun(){

    }
};

class Child2 : public Base {
private:
    int self;
public:
    Child2(){
        std::cout << "Child2构造被调用" << std::endl;
    }
//    ~Child2(){
//        std::cout << "Child2析构被调用" << std::endl;
//    }
    virtual void print() override {
        std::cout << "Child2 print被调用" << std::endl;
    }
    virtual void fun() {
        std::cout << "Child2 fun被调用" << std::endl;
    }
};

typedef long long u64;
typedef void(*VIRTUAL_FUNC)();

void testPolymorphism();
void testGetVfptrAndInvoke();
int main() {
    // testPolymorphism();
    testGetVfptrAndInvoke();
}

// 测试通过对象拿到虚函数表指针、通过表指针去调用虚函数
void testGetVfptrAndInvoke() {
    std::cout << "-------测试通过对象拿到虚函数表指针、通过表指针去调用虚函数--------" << std::endl;
    Child2 a;
    // 将(&a)强制类型转换为(u64 *)，来把从&a开始的8个字节当作一个整体，这8个字节就是vfptr存储的值
    u64 *addrOfA = (u64 *)&a;
    // 然后对其进行解引用，就相当于取出这8个字节中的数据，8个字节编码后的值就是虚函数表的首地址 (等同u64* arr = (u64*)*addrOfA;)
    long long  vaule = *addrOfA;
    // 将数值转为地址(指针)类型，此时就拿到了 指向虚函数表 的指针
    u64* vfptr = (u64*)vaule;

    // 用指针进行虚函数的调用
    std::cout << "-------虚函数调用开始--------" << std::endl;
    std::cout << "--> 调用vfptr[0]: ";
    auto f0 = (VIRTUAL_FUNC)vfptr[0];
    f0();
    std::cout << "--> 调用vfptr[1]: ";
    auto f1 = (VIRTUAL_FUNC)vfptr[1];
    f1();
    std::cout << "--> 调用vfptr[2]: ";
    auto f2 = (VIRTUAL_FUNC)vfptr[2];
    f2();
    std::cout << "-------虚函数调用结束--------" << std::endl;
}

// 测试多态性
void testPolymorphism() {
    std::cout << "-------多态性的测试--------" << std::endl;
    Base *base = new Child2; // 继承关系，父类的指针指向子类对象，子类重写父类的虚函数 ==>> 根据对象的实际类型调用 该类型中的函数。
    base->print(); // 通过子类对象里面的 vfptr 找到虚函数表 ，再从表里面找到函数地址，通过函数地址找到函数地址进行调用 （空间、时间 换来了灵活性，减少了代码量）
    delete base;
    Child child;
    std::cout << sizeof(child) << std::endl;
}