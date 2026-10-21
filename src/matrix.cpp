
#include "matrix.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

namespace lab3 {

// 1. Создание матрицы
Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument(
            "Matrix dimensions must be positive"
        );
    }

    Matrix mat{};
    mat.rows = rows;
    mat.cols = cols;

    mat.data = new double*[rows]{};

    try {
        for (int i = 0; i < rows; ++i) {
            mat.data[i] = new double[cols]{};
        }
    } catch (...) {
        for (int i = 0; i < rows; ++i) {
            delete[] mat.data[i];
        }
        delete[] mat.data;
        throw;
    }

    return mat;
}

// 2. Освобождение памяти
void free_matrix(Matrix m) {
    if (m.data == nullptr) {
        return;
    }

    for (int i = 0; i < m.rows; ++i) {
        delete[] m.data[i];
    }

    delete[] m.data;
}

// 3. Сложение матриц
Matrix matrix_add(Matrix a, Matrix b) {
    if (a.data == nullptr || b.data == nullptr ||
        a.rows <= 0 || a.cols <= 0 ||
        b.rows <= 0 || b.cols <= 0 ||
        a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument(
            "Invalid dimensions for addition"
        );
    }

    Matrix result = create_matrix(a.rows, a.cols);

    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < a.cols; ++j) {
            result.data[i][j] =
                a.data[i][j] + b.data[i][j];
        }
    }

    return result;
}

// 4. Умножение матриц
Matrix matrix_multiply(Matrix a, Matrix b) {
    if (a.data == nullptr || b.data == nullptr ||
        a.rows <= 0 || a.cols <= 0 ||
        b.rows <= 0 || b.cols <= 0 ||
        a.cols != b.rows) {
        throw std::invalid_argument(
            "Invalid dimensions for multiplication"
        );
    }

    Matrix result = create_matrix(a.rows, b.cols);

    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < b.cols; ++j) {
            for (int k = 0; k < a.cols; ++k) {
                result.data[i][j] +=
                    a.data[i][k] * b.data[k][j];
            }
        }
    }

    return result;
}

// 5. Вывод матрицы
void print_matrix(Matrix m) {
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        std::cout << "[Empty matrix]\n";
        return;
    }

    std::cout << std::fixed << std::setprecision(2);

    constexpr int MAX_ROWS = 10;
    constexpr int MAX_COLS = 8;

    bool large =
        m.rows > MAX_ROWS || m.cols > MAX_COLS;

    if (!large) {
        for (int i = 0; i < m.rows; ++i) {
            std::cout << "[";

            for (int j = 0; j < m.cols; ++j) {
                std::cout << std::setw(7)
                          << m.data[i][j];
            }

            std::cout << " ]\n";
        }
        return;
    }

    for (int i = 0; i < m.rows; ++i) {
        if (m.rows > MAX_ROWS && i == 5) {
            std::cout << "[ ... ]\n";
            i = m.rows - 5;
        }

        std::cout << "[";

        for (int j = 0; j < m.cols; ++j) {
            if (m.cols > MAX_COLS && j == 4) {
                std::cout << "  ...";
                j = m.cols - 4;
            }

            std::cout << std::setw(7)
                      << m.data[i][j];
        }

        std::cout << " ]\n";
    }

    std::cout << "Matrix " << m.rows
              << " x " << m.cols << '\n';
}

// 6. Создание матрицы из массива
Matrix matrix_from_array(
    double* data, int rows, int cols
) {
    if (data == nullptr) {
        throw std::invalid_argument(
            "Array pointer is null"
        );
    }

    Matrix result = create_matrix(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i * cols + j];
        }
    }

    return result;
}

// 7. Транспонирование матрицы
// Используется в тестах части 3
Matrix matrix_transpose(Matrix m) {
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        throw std::invalid_argument(
            "Invalid matrix"
        );
    }

    Matrix result = create_matrix(m.cols, m.rows);

    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            result.data[j][i] = m.data[i][j];
        }
    }

    return result;
}

// 8. Загрузка матрицы из файла
// Функция из части 2, вариант 22
Matrix matrix_from_file(const char* filename) {
    if (filename == nullptr || filename[0] == '\0') {
        throw std::invalid_argument(
            "Invalid filename"
        );
    }

    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Cannot open file"
        );
    }

    int rows = 0;
    int cols = 0;

    if (!(file >> rows >> cols)) {
        throw std::runtime_error(
            "Cannot read matrix dimensions"
        );
    }

    if (rows <= 0 || cols <= 0) {
        throw std::runtime_error(
            "Invalid matrix dimensions"
        );
    }

    Matrix result = create_matrix(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(file >> result.data[i][j])) {
                free_matrix(result);

                throw std::runtime_error(
                    "Invalid matrix data"
                );
            }
        }
    }

    std::string extra;

    if (file >> extra) {
        free_matrix(result);

        throw std::runtime_error(
            "Extra data in matrix file"
        );
    }

    return result;
}

} // namespace lab3
