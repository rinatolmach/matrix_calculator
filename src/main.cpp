
#include "matrix.h"

#include <exception>
#include <iostream>

int main() {

    // ЧАСТЬ 1. Базовые операции с матрицами

    // Исходные данные для матриц A и B
    double a_data[] = {1, 2, 3, 4};
    double b_data[] = {5, 6, 7, 8};

    // Создание матриц размером 2x2
    lab3::Matrix A =
        lab3::matrix_from_array(a_data, 2, 2);

    lab3::Matrix B =
        lab3::matrix_from_array(b_data, 2, 2);

    // Сложение матриц
    lab3::Matrix sum = lab3::matrix_add(A, B);

    // Умножение матриц
    lab3::Matrix product =
        lab3::matrix_multiply(A, B);

    // Вывод исходных матриц
    std::cout << "Matrix A:\n";
    lab3::print_matrix(A);

    std::cout << "\nMatrix B:\n";
    lab3::print_matrix(B);

    // Вывод суммы
    std::cout << "\nSum A+B:\n";
    lab3::print_matrix(sum);

    // Вывод произведения
    std::cout << "\nProduct A*B:\n";
    lab3::print_matrix(product);

    // Освобождение памяти
    lab3::free_matrix(A);
    lab3::free_matrix(B);
    lab3::free_matrix(sum);
    lab3::free_matrix(product);


    // ЧАСТЬ 2. Индивидуальное задание №22
    // Загрузка матрицы из текстового файла

    std::cout << "\nVariant 22: Load matrix from file\n";

    try {
        // Загрузка матрицы из файла matrix.txt
        lab3::Matrix loaded =
            lab3::matrix_from_file("matrix.txt");

        // Вывод загруженной матрицы
        std::cout << "\nLoaded matrix:\n";
        lab3::print_matrix(loaded);

        // Освобождение памяти
        lab3::free_matrix(loaded);

    } catch (const std::exception& error) {

        // Обработка ошибки при чтении файла
        std::cerr << "Error: "
                  << error.what() << '\n';

        return 1;
    }

    return 0;
}
