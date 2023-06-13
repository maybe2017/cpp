
#include "Conversation.h"
#include <iostream>
#include <utility>
namespace mayu {

    const int age_defalut = 30;
    Person::Person() = default;
    Person::Person(int age, std::string sex, bool married) : age(age), sex(std::move(sex)), married(married) {
        this->age = age;
        this->sex = "男";
        this->married = true;
    }
    int Person::getAge() const {
        return age;
    }
    void Person::setAge(int age) {
        Person::age = age;
    }
    const std::string &Person::getSex() const {
        return sex;
    }
    void Person::setSex(const std::string &sex) {
        Person::sex = sex;
    }
    bool Person::isMarried() const {
        return married;
    }
    void Person::setMarried(bool married) {
        Person::married = married;
    }

    Person::~Person() {
       std::cout << "Person的析构函数被调用！" << std::endl;
    }

    std::ostream &operator<<(std::ostream &os, const Person &person) {
        os << "age: " << person.age << " sex: " << person.sex << " married: " << person.married;
        return os;
    }

}// namespace mayu