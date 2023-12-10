/**
 * @file main.cpp
 * @brief напишите программу, которая читает из файла текст состоящий из букв и знаков пунктуации (,.').
 * Необходимый текст находится в файле "input.txt".
 * Нужно для каждого предложения вывести не уникальные слова, это те слова, которые встречаются дважды и более раз в одном предложении.
 * Слова следует учитывать без учёта регистра.
 * Слово не должно содержать знаков пунктуации, но может содержать символ "\'", а концом предложения является только символ ".". Внутри предложения может присутствовать ",".
 * Для каждого такого случая вывести в std::cout номер предложения, а после символа : все неуникальные слова рядом с номером через запятую.
 * В конце списка слов вывести '\n', а не запятую.
 *   подсказка: std::cout << "\b \n"; - код для удаления последнего символа и вместо него вывод перехода на новую строку
 * Если в предложении все слова уникальны, то для этого предложения ничего не нужно выводить
 * пример вывода:
0:the\n
1:a\n
2:one,the\n
3:a,the\n
 *
 */

#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>


std::string removePunctuation(const std::string& text) {
    std::string result;
    for (char c : text) {
        if (!std::ispunct(c)) {
            result += c;
        }
    }
    return result;
}


int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Невозможно открыть файл" << std::endl;
        return 1;
    }
    std::string line;
    int sentenceNumber = 0;

    while (std::getline(inputFile, line)) {
        std::string cleanedLine = removePunctuation(line);
        std::transform(cleanedLine.begin(), cleanedLine.end(), cleanedLine.begin(), ::tolower);

        std::istringstream iss(cleanedLine);
        std::map<std::string, int> wordCount;
        std::string word;

        while (iss >> word) {
            wordCount[word]++;
        }

        std::vector<std::string> nonUniqueWords;
        for (const auto& pair : wordCount) {
            if (pair.second > 1) {
                nonUniqueWords.push_back(pair.first);
            }
        }

        if (!nonUniqueWords.empty()) {
            std::cout << ++sentenceNumber << ": ";
            for (size_t i = 0; i < nonUniqueWords.size(); ++i) {
                std::cout << nonUniqueWords[i];
                if (i != nonUniqueWords.size() - 1) {
                    std::cout << ",";
                }
            }
            std::cout << "\n";
        }
    }

    inputFile.close();

    return 0;
}