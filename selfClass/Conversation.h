#ifndef C_CODES_CONVERSATION_H
#define C_CODES_CONVERSATION_H
#include <iostream>
namespace mayu {
    class Person {
    private:
        int age = 0;
        std::string sex;
        bool married = false;

    public:
        Person();
        Person(int age, std::string sex, bool married);
//        virtual ~Person();
        ~Person();
        friend std::ostream &operator<<(std::ostream &os, const Person &person);

        // 用const修饰 表示常函数，在函数内不能再修改类变量的值： 因为相当于用const 再修饰了this指针 ==>> const this (即不能通过this去更改属性值，除非属性加上了mutable修饰)
        int getAge() const;

        void setAge(int age);
        const std::string &getSex() const;
        void setSex(const std::string &sex);
        bool isMarried() const;
        void setMarried(bool married);
    };

}// namespace mayu

#endif//C_CODES_CONVERSATION_H
