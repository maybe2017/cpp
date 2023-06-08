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
        virtual ~Person();
        friend std::ostream &operator<<(std::ostream &os, const Person &person);
        int getAge() const;
        void setAge(int age);
        const std::string &getSex() const;
        void setSex(const std::string &sex);
        bool isMarried() const;
        void setMarried(bool married);
    };

}// namespace mayu

#endif//C_CODES_CONVERSATION_H
