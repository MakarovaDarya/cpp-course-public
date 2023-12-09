/**
 * @file main.cpp
 * @brief задача написать программу, которая будет высчитывать значение интеграла через метод трапеций
 * Особенность этой задачи: использовать потоки(threads) для ускорения вычислений (нужно разделить задачу для вычисления части интеграла на каждый поток)
 *
 * на вход программе при запуске(это в argv[]) подается 3 числа: a, b, n, tn где [a, b] - интервал (целочисленный, неотрицательный и не больше 50 для задачи), n - количество разбиений, tn - threads number - количество потоков для подсчёта
 * примечание: n - количество разбиений в тестах будет явно нацело делиться на tn - количество потоков.
 *
 * на выход программе выведите значение интеграла через метод трапеций (вывод в стандартный поток std::cout, в конце выведите '\n'), вывод в поток с точностью до 4 знака
 * в функции trapezoidalIntegral есть переменная const std::function<double (double)> &f, при вызове подсчётов передайте ссылку на функцию из задания
 * реализовать подсчёт интеграла S(a, b) = (1+e^x)^0.5 dx
 * 
 *
 * литература:
 * https://ru.wikipedia.org/wiki/Метод_трапеций
 * https://habr.com/ru/articles/420867/
 */

#include <cmath>
#include <string>
#include <functional>
#include <numeric>
#include <vector>
#include <thread>
#include <iostream>
#include <algorithm>
#include <iomanip>


class Integral {
private:
    int a, b, n, tn;

public:
    Integral(int& argc, char** argv) {
        if (argc != 5) {
            throw std::invalid_argument("Wrong number of arguments");
        }
        a = std::stoi(argv[1]);
        b = std::stoi(argv[2]);
        n = std::stoi(argv[3]);
        tn = std::stoi(argv[4]);
    }


    static double integralFunction(double x) {
        // тут нужно реализовать функцию интеграла S(a, b) = (1+e^x)^0.5 dx
        return std::sqrt(1 + std::exp(x));
    }


    double calculateIntegral() {
        // в зависимости от количество потоков (tn) реализуйте подсчёт интеграла
        double h = static_cast<double>(b - a) / n;
        double sum = 0.0;
        std::vector<double> partialSums(tn);

        std::vector<std::thread> threads(tn);

        for (int i = 0; i < tn; i++) {
            threads[i] = std::thread([this, i, h, &partialSums]() {
                double partialSum = 0.0;
                for (int j = i; j < n; j += tn) {
                    double x = a + j * h;
                    double y = integralFunction(x);
                    if (j == 0 || j == n - 1) {
                        partialSum += 0.5 * y;
                    }
                    else {
                        partialSum += y;
                    }
                }
                partialSums[i] = partialSum;
                });
        }

        for (auto& thread : threads) {
            thread.join();
        }

        sum = std::accumulate(partialSums.begin(), partialSums.end(), 0.0);

        return sum * h;
    }


};



int main(int argc, char** argv)
{
    try {
        auto i = Integral(argc, argv);
        std::cout << std::fixed << std::setprecision(4);
        std::cout << i.calculateIntegral() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}


    