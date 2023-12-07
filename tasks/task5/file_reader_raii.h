#include <cstdio>
#include <exception>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <stdexcept>

 
class CannotOpenFileException:
    public std::runtime_error{
public:
    CannotOpenFileException() : std::runtime_error("Cannot open file") {} 
};
 
class FileRaiiWrapper {
private:
    std::FILE* f; // тот самый файловый дескриптор, который мы оборачиваем

public:
    // если файл не открылся, например его нет на диске, то нужно выбросить ошибку CannotOpenFileException
    FileRaiiWrapper(const std::string& name)  {
        // реализации открытия файла и выброса ошибки тут
        f=std::fopen(name.c_str(), "r"); {
            if (!f) {
                throw CannotOpenFileException();
            }
        }

    }

    FileRaiiWrapper(const FileRaiiWrapper&) = delete;
    FileRaiiWrapper& operator = (const FileRaiiWrapper&) = delete;


// File&& — ссылка на временный объект
// забираем владение дескриптором у временного объекта other
    // Конструктор перемещения
    FileRaiiWrapper(FileRaiiWrapper&& other) noexcept : f(other.f) {
        other.f = nullptr;
        std::swap(f, other.f);
    }

    // Оператор присваивания с семантикой перемещения
    FileRaiiWrapper& operator=(FileRaiiWrapper&& other) noexcept {
        if (this != &other) {
            if (f) {
                std::fclose(f);
            }
            f = nullptr;

            std::swap(f, other.f);
        }
        return *this;
    }

    // Закрываем файл, но только если он валидный
    ~FileRaiiWrapper() noexcept {
        // реализация закрытия валидного файла тут
        if (f) {
            std::fclose(f);
        }
    }

    // функция для чтения строки длинной bytes_count из файла
    std::string ReadBytes(const size_t bytes_count) const {
        if (!f) {
            return "";
        }
        else {
            std::unique_ptr<char[]> buf(new char[bytes_count + 1] {});
            std::fgets(buf.get(), bytes_count, f);
            std::string result(buf.get());
            return result;
        }
    }
};