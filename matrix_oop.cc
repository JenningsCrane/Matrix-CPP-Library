#include "matrix_oop.h"

void Matrix::MatrixAllocateMemory() {
  if (rows_ >= 0 && cols_ >= 0) {
    matrix_ = new double*[rows_]();
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]();
    }
  }
}

void Matrix::MatrixDeallocateMemory() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}

bool Matrix::IsSquareMtx() const { return this->rows_ != this->cols_; }

bool Matrix::EqSizeMtx(const Matrix& other) const {
  return (this->rows_ != other.rows_ || this->cols_ != other.cols_);
}

Matrix::Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

Matrix::Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  this->MatrixAllocateMemory();
}

Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = nullptr;
  MatrixAllocateMemory();
  for (int i = 0; i < rows_; i++) {
    std::memcpy(matrix_[i], other.matrix_[i], cols_ * sizeof(double));
  }
}

Matrix::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

Matrix::~Matrix() { MatrixDeallocateMemory(); }

int Matrix::GetRows() const { return rows_; }

int Matrix::GetCols() const { return cols_; }

void Matrix::SetRows(int rows) {
  if (rows < 0) throw std::invalid_argument("Отрицательное значение rows.");
  if (rows != this->rows_) ResizeMatrix(rows, cols_);
}

void Matrix::SetCols(int cols) {
  if (cols < 0) throw std::invalid_argument("Отрицательное значение cols.");
  if (cols != this->cols_) ResizeMatrix(rows_, cols);
}

void Matrix::ResizeMatrix(int rows, int cols) {
  Matrix result(rows, cols);
  for (int i = 0; i < std::min(rows, this->rows_); i++)
    std::memcpy(result.matrix_[i], this->matrix_[i],
                std::min(cols, this->cols_) * sizeof(double));
  this->MatrixDeallocateMemory();
  *this = result;
}

Matrix Matrix::operator+(const Matrix& other) const {
  Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
  Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
  Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

Matrix Matrix::operator*(const double num) const {
  Matrix result(*this);
  result.MulNumber(num);
  return result;
}

Matrix operator*(const double num, const Matrix& other) {
  return other * num;
}

bool Matrix::operator==(const Matrix& other) const {
  return this->EqMatrix(other);
}

Matrix& Matrix::operator=(Matrix other) {
  if (this == &other) return *this;
  std::swap(this->rows_, other.rows_);
  std::swap(this->cols_, other.cols_);
  std::swap(this->matrix_, other.matrix_);
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  SumMatrix(other);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  SubMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  MulMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double& Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_)
    throw std::invalid_argument(
        "Отрицательное значение rows и/или cols и/или вводимое их количество "
        "превышает количество rows и/или cols в текущей матрице.");
  return matrix_[i][j];
}

bool Matrix::EqMatrix(const Matrix& other) const {
  if (EqSizeMtx(other)) return false;
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (floor(this->matrix_[i][j] * pow(10, 7)) !=
          floor(other.matrix_[i][j] * pow(10, 7))) {
        return false;
      }
    }
  }
  return true;
}

void Matrix::SumMatrix(const Matrix& other) {
  if (EqSizeMtx(other))
    throw std::logic_error(
        "Нельзя проводить операцию сложения над матрицами разных размеров.");
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::SubMatrix(const Matrix& other) {
  if (EqSizeMtx(other))
    throw std::logic_error(
        "Нельзя проводить операцию вычитания над матрицами разных размеров.");
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void Matrix::MulNumber(const double num) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix& other) {
  if (this->cols_ != other.rows_)
    throw std::logic_error(
        "Число столбцов первой матрицы не равно числу строк второй матрицы.");
  Matrix result(*this);
  ResizeMatrix(result.rows_, other.cols_);
  double sum = 0.0;
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      for (int k = 0; k < result.cols_; k++) {
        sum += result.matrix_[i][k] * other.matrix_[k][j];
      }
      this->matrix_[i][j] = sum;
      sum = 0.0;
    }
  }
}

Matrix Matrix::Transpose() const {
  Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = this->matrix_[j][i];
    }
  }
  return result;
}

Matrix Matrix::CalcComplements() {
  if (this->IsSquareMtx())
    throw std::logic_error("Матрица не является квадратной");
  Matrix result(this->rows_, this->cols_);
  if (this->rows_ == 1 && this->cols_ == 1)
    result.matrix_[0][0] = this->matrix_[0][0];
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      result.matrix_[i][j] = MinorMtx(i, j).Determinant() * pow(-1, i + j);
    }
  }
  return result;
}

Matrix Matrix::MinorMtx(int rows, int columns) {
  Matrix minor(this->rows_ - 1, this->cols_ - 1);
  for (int i = 0, z_i = 0; i < rows_; i++) {
    if (i != rows) {
      for (int j = 0, z_j = 0; j < cols_; j++) {
        if (j != columns) {
          minor.matrix_[z_i][z_j] = matrix_[i][j];
          z_j++;
        }
      }
      z_i++;
    }
  }
  return minor;
}

double Matrix::Determinant() {
  if (this->IsSquareMtx())
    throw std::logic_error("Матрица не является квадратной");
  double result = 0.0;
  if (this->cols_ == 1) {
    result = this->matrix_[0][0];
  } else if (this->cols_ == 2) {
    result = this->matrix_[0][0] * this->matrix_[1][1] -
             this->matrix_[0][1] * this->matrix_[1][0];
  } else if (this->cols_ > 2) {
    for (int i = 0; i < this->cols_; i++) {
      result += pow(-1, i) * this->matrix_[i][0] * MinorMtx(i, 0).Determinant();
    }
  }
  return result;
}

Matrix Matrix::InverseMatrix() {
  double det = Determinant();
  if (fabs(det) < 1e-7)
    throw std::logic_error("Нельзя, чтобы детерминант был равен нулю.");
  Matrix result = CalcComplements().Transpose();
  result.MulNumber(1.0 / det);
  return result;
}
