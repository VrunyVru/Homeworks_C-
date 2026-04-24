#include <iostream>
#include <string>
#include <vector>

template<typename T>
class Printer {
public:
    void print(const T& value) const {
        std::cout << "Value: " << value << std::endl;
    }
};

template<>
class Printer<bool> {
public:
    void print(bool value) const {
        if (value) {
            std::cout << "true" << std::endl;
        } else {
            std::cout << "false" << std::endl;
        }
    }
};

template<typename T>
class Printer<T*> {
public:
    void print(T* ptr) const {
        if (ptr == nullptr) {
            std::cout << "Address: (nullptr)" << std::endl;
        } else {
            std::cout << "Address: " << ptr 
                      << ", Value: " << *ptr << std::endl;
        }
    }
};

int main() {
    std::cout << "========== Тестирование Printer ==========\n\n";

    // 1. Общий шаблон для int
    std::cout << "--- Общий шаблон (int) ---" << std::endl;
    Printer<int> p1;
    p1.print(42);

    std::cout << "\n--- Общий шаблон (double) ---" << std::endl;
    Printer<double> p2;
    p2.print(3.14);

    std::cout << "\n--- Общий шаблон (string) ---" << std::endl;
    Printer<std::string> p3;
    p3.print("Hello");

    // 2. Полная специализация для bool
    std::cout << "\n--- Полная специализация (bool) ---" << std::endl;
    Printer<bool> p4;
    p4.print(true);
    p4.print(false);

    // 3. Частичная специализация для указателей
    std::cout << "\n--- Частичная специализация (указатели) ---" << std::endl;
    
    int x = 100;
    Printer<int*> p5;
    p5.print(&x);

    double y = 5.5;
    Printer<double*> p6;
    p6.print(&y);

    std::string s = "World";
    Printer<std::string*> p7;
    p7.print(&s);

    // 4. Проверка с nullptr
    std::cout << "\n--- Проверка nullptr ---" << std::endl;
    int* nullPtr = nullptr;
    p5.print(nullPtr);

    std::cout << "\n========== Тестирование завершено ==========" << std::endl;
    
    return 0;
}