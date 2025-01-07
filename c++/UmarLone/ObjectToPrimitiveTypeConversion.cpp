//
// Created by USER on 1/6/2025.
//
#include <memory>
#include <iostream>

class Employee {
    int id{1};
public:
    Employee(int x) {
        id = x;
    }

    operator int() {
        return id;
    }

    int getId() const {
        return id;
    }
};

std::ostream &operator<<(std::ostream &os, std::unique_ptr<Employee> &e) {
    os << " id is =" << e->getId() << std::endl;
    return os;
}

//int main() {
//    Employee a = 10;
//    int id11 = a;
//    std::cout << id11;
//    std::unique_ptr<Employee> employee = std::make_unique<Employee>(10);
//    std::cout << employee;
//    std::unique_ptr<Employee> e1{new Employee(11)};
//    std::cout << e1;
//}