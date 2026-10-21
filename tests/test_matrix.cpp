
#include "matrix.h"

#include <gtest/gtest.h>
#include <stdexcept>

// 1. НОРМАЛЬНЫЕ СЛУЧАИ

TEST(MatrixTest, CreateMatrix_NormalCase) {
    lab3::Matrix A = lab3::create_matrix(3, 4);

    EXPECT_EQ(A.rows, 3);
    EXPECT_EQ(A.cols, 4);
    EXPECT_NE(A.data, nullptr);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_DOUBLE_EQ(A.data[i][j], 0.0);
        }
    }

    lab3::free_matrix(A);
}

TEST(MatrixTest, Addition_NormalCase) {
    double a[] = {1, 2, 3, 4};
    double b[] = {5, 6, 7, 8};

    lab3::Matrix A = lab3::matrix_from_array(a, 2, 2);
    lab3::Matrix B = lab3::matrix_from_array(b, 2, 2);

    lab3::Matrix C = lab3::matrix_add(A, B);

    EXPECT_DOUBLE_EQ(C.data[0][0], 6.0);
    EXPECT_DOUBLE_EQ(C.data[0][1], 8.0);
    EXPECT_DOUBLE_EQ(C.data[1][0], 10.0);
    EXPECT_DOUBLE_EQ(C.data[1][1], 12.0);

    lab3::free_matrix(A);
    lab3::free_matrix(B);
    lab3::free_matrix(C);
}

TEST(MatrixTest, Multiplication_NormalCase) {
    double a[] = {1, 2, 3, 4};
    double b[] = {5, 6, 7, 8};

    lab3::Matrix A = lab3::matrix_from_array(a, 2, 2);
    lab3::Matrix B = lab3::matrix_from_array(b, 2, 2);

    lab3::Matrix C = lab3::matrix_multiply(A, B);

    EXPECT_DOUBLE_EQ(C.data[0][0], 19.0);
    EXPECT_DOUBLE_EQ(C.data[0][1], 22.0);
    EXPECT_DOUBLE_EQ(C.data[1][0], 43.0);
    EXPECT_DOUBLE_EQ(C.data[1][1], 50.0);

    lab3::free_matrix(A);
    lab3::free_matrix(B);
    lab3::free_matrix(C);
}

TEST(MatrixTest, Transpose_NormalCase) {
    double a[] = {1, 2, 3, 4, 5, 6};

    lab3::Matrix A = lab3::matrix_from_array(a, 2, 3);
    lab3::Matrix T = lab3::matrix_transpose(A);

    EXPECT_EQ(T.rows, 3);
    EXPECT_EQ(T.cols, 2);

    EXPECT_DOUBLE_EQ(T.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(T.data[0][1], 4.0);
    EXPECT_DOUBLE_EQ(T.data[1][0], 2.0);
    EXPECT_DOUBLE_EQ(T.data[1][1], 5.0);
    EXPECT_DOUBLE_EQ(T.data[2][0], 3.0);
    EXPECT_DOUBLE_EQ(T.data[2][1], 6.0);

    lab3::free_matrix(A);
    lab3::free_matrix(T);
}

TEST(MatrixTest, FreeMatrix_NormalCase) {
    lab3::Matrix A = lab3::create_matrix(3, 3);
    EXPECT_NO_THROW(lab3::free_matrix(A));
}

// 2. ГРАНИЧНЫЕ СЛУЧАИ

TEST(MatrixTest, CreateMatrix_MinimumSize) {
    lab3::Matrix A = lab3::create_matrix(1, 1);

    EXPECT_EQ(A.rows, 1);
    EXPECT_EQ(A.cols, 1);
    EXPECT_DOUBLE_EQ(A.data[0][0], 0.0);

    lab3::free_matrix(A);
}

TEST(MatrixTest, Multiplication_RowTimesColumn_1x1) {
    double a[] = {1, 2, 3};
    double b[] = {4, 5, 6};

    lab3::Matrix A = lab3::matrix_from_array(a, 1, 3);
    lab3::Matrix B = lab3::matrix_from_array(b, 3, 1);

    lab3::Matrix C = lab3::matrix_multiply(A, B);

    EXPECT_EQ(C.rows, 1);
    EXPECT_EQ(C.cols, 1);
    EXPECT_DOUBLE_EQ(C.data[0][0], 32.0);

    lab3::free_matrix(A);
    lab3::free_matrix(B);
    lab3::free_matrix(C);
}

TEST(MatrixTest, TransposeTwice_ReturnsOriginal) {
    double a[] = {1, 2, 3, 4, 5, 6};

    lab3::Matrix A = lab3::matrix_from_array(a, 2, 3);
    lab3::Matrix T = lab3::matrix_transpose(A);
    lab3::Matrix TT = lab3::matrix_transpose(T);

    EXPECT_EQ(TT.rows, 2);
    EXPECT_EQ(TT.cols, 3);

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_DOUBLE_EQ(TT.data[i][j], A.data[i][j]);
        }
    }

    lab3::free_matrix(A);
    lab3::free_matrix(T);
    lab3::free_matrix(TT);
}

// 3. НЕКОРРЕКТНЫЕ СЛУЧАИ

TEST(MatrixTest, CreateMatrix_ZeroRows) {
    EXPECT_THROW(
        lab3::create_matrix(0, 3),
        std::invalid_argument
    );
}

TEST(MatrixTest, CreateMatrix_NegativeCols) {
    EXPECT_THROW(
        lab3::create_matrix(3, -1),
        std::invalid_argument
    );
}

TEST(MatrixTest, Addition_SizeMismatch) {
    lab3::Matrix A = lab3::create_matrix(2, 2);
    lab3::Matrix B = lab3::create_matrix(3, 3);

    EXPECT_THROW(
        lab3::matrix_add(A, B),
        std::invalid_argument
    );

    lab3::free_matrix(A);
    lab3::free_matrix(B);
}

TEST(MatrixTest, Multiplication_SizeMismatch) {
    lab3::Matrix A = lab3::create_matrix(2, 3);
    lab3::Matrix B = lab3::create_matrix(2, 2);

    EXPECT_THROW(
        lab3::matrix_multiply(A, B),
        std::invalid_argument
    );

    lab3::free_matrix(A);
    lab3::free_matrix(B);
}

TEST(MatrixTest, FreeMatrix_EmptyIsSafe) {
    lab3::Matrix empty{nullptr, 0, 0};

    EXPECT_NO_THROW(lab3::free_matrix(empty));
    EXPECT_NO_THROW(lab3::free_matrix(empty));
}
