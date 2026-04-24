#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <chrono>
#include <ctime>

class Logger {
public:
    virtual void log(const std::string& msg) = 0;
    virtual ~Logger() = default;
};

// ConsoleLogger — вывод в stdout
class ConsoleLogger : public Logger {
public:
    void log(const std::string& msg) override {
        std::cout << "[CONSOLE] " << msg << std::endl;
    }
};

// FileLogger — запись в файл
class FileLogger : public Logger {
private:
    std::ofstream file_;
    
public:
    FileLogger(const std::string& filename = "app.log") 
        : file_(filename, std::ios::app)
    {}
    
    void log(const std::string& msg) override {
        if (file_.is_open()) {
            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);
            file_ << "[FILE] " << std::ctime(&time_t) << "  " << msg << std::endl;
        }
    }
    
    ~FileLogger() {
        if (file_.is_open()) {
            file_.close();
        }
    }
};

// NullLogger — ничего не делает (для тестов)
class NullLogger : public Logger {
public:
    void log(const std::string& msg) override {
        // Абсолютно ничего не делаем
        // Используется для тестирования, чтобы не засорять вывод
        (void)msg;  // подавляем warning о неиспользуемом параметре
    }
};

// Абстрактная фабрика
class LoggerFactory {
public:
    virtual std::unique_ptr<Logger> createLogger() = 0;
    virtual ~LoggerFactory() = default;
};

// Фабрика ConsoleLogger
class ConsoleLoggerFactory : public LoggerFactory {
public:
    std::unique_ptr<Logger> createLogger() override {
        return std::make_unique<ConsoleLogger>();
    }
};

// Фабрика FileLogger
class FileLoggerFactory : public LoggerFactory {
private:
    std::string filename_;
    
public:
    FileLoggerFactory(const std::string& filename = "app.log")
        : filename_(filename)
    {}
    
    std::unique_ptr<Logger> createLogger() override {
        return std::make_unique<FileLogger>(filename_);
    }
};

// Фабрика NullLogger
class NullLoggerFactory : public LoggerFactory {
public:
    std::unique_ptr<Logger> createLogger() override {
        return std::make_unique<NullLogger>();
    }
};

class Application {
private:
    std::unique_ptr<Logger> logger_;
    
public:
    Application(std::unique_ptr<LoggerFactory> factory)
        : logger_(factory->createLogger())
    {}

    void run() {
        logger_->log("Application started");
        logger_->log("Performing business logic...");
        
        for (int i = 1; i <= 3; ++i) {
            logger_->log("Processing step " + std::to_string(i));
        }
        
        logger_->log("Application finished successfully");
    }
};

int main() {
    std::cout << "========== Фабричный метод ==========\n\n";
    std::cout << "--- Тест ConsoleLogger ---" << std::endl;
    auto consoleApp = Application(std::make_unique<ConsoleLoggerFactory>());
    consoleApp.run();
    
    std::cout << "\n--- Тест FileLogger ---" << std::endl;
    auto fileApp = Application(std::make_unique<FileLoggerFactory>("test.log"));
    fileApp.run();
    std::cout << "Check 'test.log' file for output" << std::endl;
    
    std::cout << "\n--- Тест NullLogger (silent mode) ---" << std::endl;
    auto nullApp = Application(std::make_unique<NullLoggerFactory>());
    nullApp.run();
    std::cout << "NullLogger produced no output" << std::endl;   
    return 0;
}