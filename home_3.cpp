#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

template<typename T>
class MiniSmartList {
private:
    std::vector<T> data;

public:
    void push_back(const T& val) { data.push_back(val); }
    void pop_back() { if (!data.empty()) data.pop_back(); }
    size_t size() const { return data.size(); }
    void clear() { data.clear(); }
    
    // Доступ по индексу
    const T& operator[](size_t i) const { return data[i]; }

    template<typename U = T>
    auto sum() const -> std::enable_if_t<std::is_arithmetic_v<U>, U> {
        U result = 0;
        for (const auto& x : data) result += x;
        return result;
    }

    template<typename U = T>
    auto sort() -> decltype(std::declval<U>() < std::declval<U>(), void()) {
        std::sort(data.begin(), data.end());
    }

    template<typename U = T>
    auto print() const -> decltype(std::cout << std::declval<U>(), void()) {
        std::cout << "[ ";
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i];
            if (i + 1 < data.size()) std::cout << ", ";
        }
        std::cout << " ]\n";
    }

    void debug_print() const {
        std::cout << "[ ";
        for (size_t i = 0; i < data.size(); ++i) {
            if constexpr (std::is_pointer_v<T>) {
                if (data[i] == nullptr) std::cout << "nullptr";
                else std::cout << "addr:" << data[i] << "(" << *data[i] << ")";
            } else {
                std::cout << data[i];
            }
            if (i + 1 < data.size()) std::cout << ", ";
        }
        std::cout << " ]\n";
    }

    template<typename U>
    bool contains(U&& value) const {
        using Clean = std::remove_cv_t<std::remove_reference_t<U>>;
        Clean target = std::forward<U>(value);
        for (const auto& item : data) {
            if (item == target) return true;
        }
        return false;
    }
};

int main() {
    // ----- Тест для int -----
    MiniSmartList<int> intList;
    intList.push_back(5);
    intList.push_back(2);
    intList.push_back(8);
    
    intList.print();
    intList.sort();
    intList.print();
    std::cout << "Сумма: " << intList.sum() << "\n";
    std::cout << "Количество 5: " << intList.contains(5) << "\n\n"; 

    // ----- Тест для указателей -----
    int a=10, b=20, c=30;
    MiniSmartList<int*> ptrList;
    ptrList.push_back(&a);
    ptrList.push_back(&b);
    ptrList.push_back(&c);
    ptrList.debug_print();

    // ----- Тест для string -----
    MiniSmartList<std::string> strList;
    strList.push_back("бананчик");
    strList.push_back("яблочкоооо");
    strList.sort();
    strList.print();
    
    // strList.sum(); //ошибочка
    return 0;
}