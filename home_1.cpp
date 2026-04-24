#include <iostream>
#include <string>
#include <type_traits>

class Animal {
public:
    virtual ~Animal() = default;

    virtual void makeSound() const = 0;
    virtual void move() const = 0;
};

class Cat : public Animal {
public:
    void makeSound() const override {
        std::cout << "Meow! Meow!" << std::endl;
    }
    void move() const override {
        std::cout << "Cat jumps gracefully." << std::endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() const override {
        std::cout << "Woof! Woof!" << std::endl;
    }
    void move() const override {
        std::cout << "Dog runs happily." << std::endl;
    }
};

class Bird : public Animal {
public:
    void makeSound() const override {
        std::cout << "Chirp! Chirp!" << std::endl;
    }
    void move() const override {
        std::cout << "Bird flies in the sky." << std::endl;
    }
};

class Car {
public:
    void drive() const {
        std::cout << "Car is driving on the road." << std::endl;
    }
};

template<typename T>
void feedAnimal(const T& creature) {
    if constexpr (std::is_base_of_v<Animal, T>) {
        std::cout << "Feeding the animal: ";
        creature.makeSound();
    } else {
        std::cout << "Error: Cannot feed a non-animal object!" << std::endl;
    }
}

template<typename T>
void checkAnimalType(const T& creature) {
    static_assert(std::is_base_of_v<Animal, T>,
                  "checkAnimalType: T must be derived from Animal!");
    std::cout << "Type check passed. Animal sounds: ";
    creature.makeSound();
}

int main() {
    std::cout << "========== Testing hierarchy ==========" << std::endl;
    Cat cat;
    Dog dog;
    Bird bird;
    Car car;

    std::cout << "\n--- Cat ---" << std::endl;
    cat.makeSound();
    cat.move();

    std::cout << "\n--- Dog ---" << std::endl;
    dog.makeSound();
    dog.move();

    std::cout << "\n--- Bird ---" << std::endl;
    bird.makeSound();
    bird.move();

    std::cout << "\n--- Car ---" << std::endl;
    car.drive();

    std::cout << "\n========== Testing feedAnimal ==========" << std::endl;
    feedAnimal(cat);
    feedAnimal(dog);
    feedAnimal(bird);
    feedAnimal(car);

    std::cout << "\n========== Testing checkAnimalType ==========" << std::endl;
    checkAnimalType(cat);
    checkAnimalType(dog);
    checkAnimalType(bird);
    // checkAnimalType(car);

    std::cout << "\nAll tests completed successfully!" << std::endl;
    return 0;
}