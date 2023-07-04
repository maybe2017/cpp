//
// 模板的使用
// 1. 普通函数调用时，参数默认可以发生类型隐式转换；
// 2. 而模板函数，在指定模板具体参数类型时，才会发生类型隐式转换；如果是自动类型推导式的调用，就不会发生。（建议使用显示指定类型调用的方式）
// 3. 空模板参数列表<>，用这个可强制调用模板函数，忽略同名普通函数优先级高的规则。
// 4. template<> bool compare(Person &p1, Person &p2), 用这种写法-具体化类型的模板，解决一些运算符号等通用的问题（也可以在类中重载运算符）

// 5. 类模板声明时，参数列表中声明类型的时候，可以指定默认具体类型，后续调用时，可以不指定。
// 6. 类模板的成员函数不是一开始就创建的，而是在被调用时才创建(运行时动态生成)。 ==>> 模板类不分为.h与.cpp文件，声明与实现统一放入一个.hpp文件（约定俗成），用于其他cpp文件的引入。
// 7. 类模板对象作为参数，3中方式
// 8. 子类继承类模板时，需要指定父模板类的参数类型（可以继续用虚拟类型，也可以用实参）

#include "iostream"
#include "string"
using namespace std;

// 坑: 友元全局函数【参数用占位类型】在模板类 外部实现的时候，不仅仅需要将 全局模板函数 的声明提前，还要将模板类的声明提前。。 ==>> 所以一般 友元全局函数的实现 直接写在模板类里面
// 需要让编译器提前知道 这个模板函数的存在
template<class NameType, class AgeType>
class Student;

template<class NameType, class AgeType>
std::ostream& operator<<(ostream& cout, Student<NameType, AgeType> &student) {
    cout << "Student: {name: " << student.getName() << ", age: "<< student.getAge() << "}";
    return cout;
}


template<class NameType, class AgeType>
class Student {
    // 注意: 全局函数【参数用占位类型】的在类中的声明， 要用<>表明是个模板函数，而不是普通函数
    friend std::ostream& operator<< <>(ostream& cout, Student<NameType, AgeType> &student);
private:
    NameType name;
    AgeType age;
public:
    Student(NameType name, AgeType age) {
        this->age = age;
        this->name = name;
    }

    [[nodiscard]] NameType getName() const {
        return name;
    }

    [[nodiscard]] AgeType getAge() const {
        return age;
    }
};




// 指定具体的模板对象类型 优先用这个
void printInfo(Student<string, int> &student) {
    cout << "printInfo(Student<string, int>)被调用! " << " " << endl;
}

// 将模板对象的参数 继续模板化
template<class NameType, class AgeType>
void printInfo(Student<NameType, AgeType> &student) {
    cout << "template1被调用! " << "NameType的具体类型是： " << typeid(NameType).name() << ",AgeType的具体类型是： " << typeid(AgeType).name() << endl;
}

// 将模板对象 整个模板化
template<typename T>
void printInfo(T &student) {
    cout << "template2被调用! " << "T的具体类型是: " << typeid(T).name() << endl;
}


// 子类继承父模板类 需要指定父模板类的参数类型
template<class ScoreType, class NameType, class AgeType>
class GoodStudent : public Student<NameType, AgeType> {

    friend std::ostream& operator<<(ostream& cout, GoodStudent<double, string, int> &student);

private:
    ScoreType score;
public:
    // 注意如何在子类构造函数中调用 父模板类的构造方法（需要显示指定 父模板类的 参数类型列表）
    GoodStudent(ScoreType score, NameType name, AgeType age) : Student<NameType, AgeType>(name, age)  {
        this->score = score;
    }

    [[nodiscard]] ScoreType getScore() const {
        return score;
    }

    // 模板类的成员函数
    void printGoodStudentInfo();
};

std::ostream& operator<<(ostream& cout, GoodStudent<double, string, int> &student) {
    // 友元函数不能被继承，需要转化为父类类型，然后调用其中的友元函数
    cout << "GoodStudent: {score: " << student.getScore() << ", " << static_cast<Student<string, int>&>(student) << "}";
    return cout;
}


// 模板类的成员函数 如何在类外进行实现
template<class ScoreType, class NameType, class AgeType>
void GoodStudent<ScoreType, NameType, AgeType>::printGoodStudentInfo() {
    cout << "INFO: ==>> " << *this << endl;
}


int main() {
    // 类模板对象
    Student<string, int> student("罗京", 18);
    // 做函数的参数
    printInfo(student);
    // 强制调用模板参数
    printInfo<string, int>(student);
    // 奇怪 上面三种函数都存在时(都只是调用模板函数1) 如何调用第三种方式的函数呢？？
    printInfo<>(student);


    cout << "----------------模板继承--------------"<< endl;
    GoodStudent<double, string, int> goodStudent( 99.0, "罗京", 20);
    goodStudent.printGoodStudentInfo();
}