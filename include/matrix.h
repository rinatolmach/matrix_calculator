
#pragma once

/**
 * @file matrix.h
 * @brief Библиотека для работы с матрицами.
 * @version 1.0
 */

namespace lab3 {

/**
 * @brief Структура матрицы.
 */
struct Matrix {
    double** data;
    int rows;
    int cols;
};

/**
 * @brief Создание матрицы.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Матрица, заполненная нулями.
 * @exception std::invalid_argument Неверные размеры.
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Освобождение памяти.
 * @param m Матрица для удаления.
 */
void free_matrix(Matrix m);

/**
 * @brief Сложение матриц.
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Матрица суммы.
 */
Matrix matrix_add(Matrix a, Matrix b);

/**
 * @brief Умножение матриц.
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Матрица произведения.
 */
Matrix matrix_multiply(Matrix a, Matrix b);

/**
 * @brief Вывод матрицы.
 * @param m Матрица для вывода.
 */
void print_matrix(Matrix m);

/**
 * @brief Создание матрицы из массива.
 * @param data Исходный массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Созданная матрица.
 */
Matrix matrix_from_array(double* data, int rows, int cols);

/**
 * @brief Транспонирование матрицы.
 * @param m Исходная матрица.
 * @return Транспонированная матрица.
 */
Matrix matrix_transpose(Matrix m);

/**
 * @brief Загрузка матрицы из файла.
 * @param filename Путь к файлу.
 * @return Загруженная матрица.
 */
Matrix matrix_from_file(const char* filename);

} // namespace lab3
