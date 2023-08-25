#include "matrix_oop.h"

#include <gtest/gtest.h>

void InitMatrix(Matrix *matrix, double num) {
  for (int i = 0; i < matrix->GetRows(); i++) {
    for (int j = 0; j < matrix->GetCols(); j++) {
      (*matrix)(i, j) = num;
    }
  }
}

void InitMatrix2(Matrix *matrix, double num) {
  for (int i = 0; i < matrix->GetRows(); i++) {
    for (int j = 0; j < matrix->GetCols(); j++) {
      (*matrix)(i, j) = num;
      num++;
    }
  }
}

void InitMatrix3(Matrix *matrix) {
  double num = 1;
  for (int i = 0; i < matrix->GetRows(); i++) {
    for (int j = 0; j < matrix->GetCols(); j++) {
      if (i == 0 && j > 0)
        (*matrix)(i, j) = 3;
      else
        (*matrix)(i, j) = num;
      num++;
    }
  }
}

TEST(Operation, eqMatrix) {
  Matrix matrix1;
  matrix1.SetRows(3);
  matrix1.SetCols(3);
  Matrix matrix2 = Matrix(3, 3);
  InitMatrix(&matrix1, 48.4765765);
  InitMatrix(&matrix2, 48.4765765);
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(Operation, eqMatrix2) {
  Matrix matrix1 = Matrix(3, 3);
  Matrix matrix2 = Matrix(3, 3);
  InitMatrix(&matrix1, 48.5765765);
  InitMatrix(&matrix2, 48.4765765);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(Operation, eqMatrix3) {
  Matrix matrix1 = Matrix(3, 4);
  Matrix matrix2 = Matrix(3, 3);
  InitMatrix(&matrix1, 48.5765765);
  InitMatrix(&matrix2, 48.5765765);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(Operation, sumMatrix) {
  Matrix matrix1 = Matrix(5, 5);
  Matrix matrix2 = Matrix(5, 5);
  Matrix sum = Matrix(5, 5);
  InitMatrix(&matrix1, 18.4765765);
  InitMatrix(&matrix2, 15.0765765);
  InitMatrix(&sum, 33.553153);
  matrix1.SumMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(sum));
}

TEST(Operation, sumMatrix2) {
  Matrix matrix1 = Matrix(5, 5);
  Matrix matrix2 = Matrix(5, 5);
  Matrix sum = Matrix(5, 5);
  InitMatrix(&matrix1, 25.7765765);
  InitMatrix(&matrix2, 15.0765765);
  InitMatrix(&sum, 33.4765765);
  matrix1.SubMatrix(matrix2);
  EXPECT_FALSE(matrix1.EqMatrix(sum));
}

TEST(Operation, subMatrix) {
  Matrix matrix1 = Matrix(5, 5);
  Matrix matrix2 = Matrix(5, 5);
  Matrix sub = Matrix(5, 5);
  InitMatrix(&matrix1, 50.6765765);
  InitMatrix(&matrix2, 15.0765765);
  InitMatrix(&sub, 35.6000000);
  matrix1.SubMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(sub));
}

TEST(Operation, subMatrix2) {
  Matrix matrix1 = Matrix(5, 5);
  Matrix matrix2 = Matrix(5, 5);
  Matrix sub = Matrix(5, 5);
  InitMatrix(&matrix1, 50.6765765);
  InitMatrix(&matrix2, 15.0765765);
  InitMatrix(&sub, 11.5765765);
  matrix1.SubMatrix(matrix2);
  EXPECT_FALSE(matrix1.EqMatrix(sub));
}

TEST(Operation, mulMatrix) {
  Matrix matrix1 = Matrix(5, 4);
  Matrix matrix2 = Matrix(4, 6);
  Matrix mul = Matrix(5, 6);
  InitMatrix(&matrix1, -1);
  InitMatrix(&matrix2, 4);
  InitMatrix(&mul, -16);
  matrix1.MulMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(mul));
}

TEST(Operation, mulNumber) {
  Matrix matrix1 = Matrix(5, 4);
  Matrix mul = Matrix(5, 4);
  InitMatrix(&matrix1, -1);
  InitMatrix(&mul, -16);
  matrix1.MulNumber(16);
  EXPECT_TRUE(matrix1.EqMatrix(mul));
}

TEST(Operation, mulNumber2) {
  Matrix matrix1 = Matrix(5, 4);
  Matrix mul = Matrix(5, 4);
  InitMatrix(&matrix1, -1);
  InitMatrix(&mul, -16);
  Matrix result = Matrix(16 * matrix1);
  EXPECT_TRUE(result.EqMatrix(mul));
}

TEST(Operation, transpose) {
  Matrix matrix = Matrix(7, 3);
  Matrix res = Matrix(3, 7);
  InitMatrix(&matrix, -1);
  InitMatrix(&res, -1);
  Matrix transpose = matrix.Transpose();
  EXPECT_TRUE(transpose.EqMatrix(res));
}

TEST(Operation, calcComplements) {
  Matrix matrix = Matrix(3, 3);
  Matrix dop = Matrix(3, 3);
  InitMatrix2(&matrix, 1);
  dop(0, 0) = -3.0;
  dop(0, 1) = 6.0;
  dop(0, 2) = -3.0;
  dop(1, 0) = 6.0;
  dop(1, 1) = -12;
  dop(1, 2) = 6;
  dop(2, 0) = -3;
  dop(2, 1) = 6;
  dop(2, 2) = -3;
  Matrix res = matrix.CalcComplements();
  EXPECT_TRUE(res.EqMatrix(dop));
}

TEST(Operation, inverseMatrix) {
  Matrix matrix = Matrix(3, 3);
  InitMatrix3(&matrix);
  Matrix dop = Matrix(3, 3);
  dop(0, 0) = -1.0 / 2.0;
  dop(0, 1) = -1.0 / 2.0;
  dop(0, 2) = 1.0 / 2.0;
  dop(1, 0) = 1.0;
  dop(1, 1) = -2.0;
  dop(1, 2) = 1.0;
  dop(2, 0) = -1.0 / 2.0;
  dop(2, 1) = 13.0 / 6.0;
  dop(2, 2) = -7.0 / 6.0;
  Matrix res = matrix.InverseMatrix();
  EXPECT_TRUE(res.EqMatrix(dop));
}

TEST(Operation, operatorSum) {
  Matrix matrix1(2, 2);
  Matrix matrix2(2, 2);
  Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 3;
  dop(1, 0) = 5;
  dop(1, 1) = 7;
  Matrix sum = matrix1 + matrix2;
  EXPECT_TRUE(sum == dop);
}

TEST(Operation, operatorSum2) {
  Matrix matrix1(2, 2);
  Matrix matrix2(2, 2);
  Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 3;
  dop(1, 0) = 5;
  dop(1, 1) = 7;
  matrix1 += matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(dop));
}

TEST(Operation, operatorSub) {
  Matrix matrix1(2, 2);
  Matrix matrix2(2, 2);
  Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 1;
  dop(1, 0) = 1;
  dop(1, 1) = 1;
  Matrix sum = matrix1 - matrix2;
  EXPECT_TRUE(sum == dop);
}

TEST(Operation, operatorSub2) {
  Matrix matrix1(2, 2);
  Matrix matrix2(2, 2);
  Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 1;
  dop(1, 0) = 1;
  dop(1, 1) = 1;
  matrix1 -= matrix2;
  EXPECT_TRUE(matrix1 == dop);
}

TEST(Operation, operatorMulMatrix) {
  Matrix matrix1(5, 4);
  Matrix matrix2(4, 6);
  Matrix dop(5, 6);
  InitMatrix(&matrix1, -1);
  InitMatrix(&matrix2, 4);
  InitMatrix(&dop, -16);
  Matrix mul = matrix1 * matrix2;
  EXPECT_TRUE(mul == dop);
}

TEST(Operation, operatorMulMatrix2) {
  Matrix matrix1(5, 4);
  Matrix matrix2(4, 6);
  Matrix dop(5, 6);
  InitMatrix(&matrix1, -1);
  InitMatrix(&matrix2, 4);
  InitMatrix(&dop, -16);
  matrix1 *= matrix2;
  EXPECT_TRUE(matrix1 == dop);
}

TEST(Operation, operatorMulNumber) {
  Matrix matrix(2, 2);
  Matrix dop(2, 2);
  InitMatrix(&matrix, 1);
  InitMatrix(&dop, 4);
  Matrix mul = matrix * 4;
  EXPECT_TRUE(mul == dop);
}

TEST(Operation, operatorMulNumber2) {
  Matrix matrix(2, 2);
  Matrix dop(2, 2);
  InitMatrix(&matrix, 1);
  InitMatrix(&dop, 4);
  matrix *= 4;
  EXPECT_TRUE(matrix == dop);
}

TEST(GetAndSet, setSize) {
  Matrix matrix1(3, 6);
  Matrix matrix2(5, 4);
  matrix2.SetRows(3);
  matrix2.SetCols(6);
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(GetAndSet, getRows) {
  Matrix matrix(4, 7);
  int rows = matrix.GetRows();
  EXPECT_TRUE(rows == 4);
}

TEST(GetAndSet, getCols) {
  Matrix matrix(4, 7);
  int cols = matrix.GetCols();
  EXPECT_TRUE(cols == 7);
}

TEST(Construct, moveMatrix) {
  Matrix matrix(4, 5);
  InitMatrix2(&matrix, 1);
  Matrix dop(matrix);
  Matrix result(std::move(matrix));
  EXPECT_TRUE(result == dop);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
