#ifndef MATRIX_OOP_H_
#define MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <iostream>

class Matrix {
 public:
  // Базовый конструктор, инициализирующий матрицу нулями.
  Matrix();

  // Параметризированный конструктор с количеством строк и столбцов.
  Matrix(int rows, int cols);

  // Конструктор копирования
  Matrix(const Matrix& other);

  // Конструктор переноса
  Matrix(Matrix&& other) noexcept;

  // Деструктор
  ~Matrix();

  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  double& operator()(int i, int j);
  bool operator==(const Matrix& other) const;
  Matrix& operator=(Matrix other);
  Matrix& operator*=(const double num);
  Matrix operator*(const double num) const;
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix operator+(const Matrix& other) const;
  Matrix operator-(const Matrix& other) const;
  Matrix operator*(const Matrix& other) const;
  friend Matrix operator*(const double num, const Matrix& other);

  double Determinant();
  void MulNumber(const double num);
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulMatrix(const Matrix& other);
  bool EqMatrix(const Matrix& other) const;
  Matrix Transpose() const;
  Matrix InverseMatrix();
  Matrix CalcComplements();

 private:
  int rows_, cols_;
  double** matrix_;
  bool IsSquareMtx() const;
  void MatrixAllocateMemory();
  void MatrixDeallocateMemory();
  void ResizeMatrix(int rows, int cols);
  bool EqSizeMtx(const Matrix& other) const;
  Matrix MinorMtx(int rows, int columns);
};

#endif  // MATRIX_OOP_H_
