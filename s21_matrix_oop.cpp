#include "s21_matrix_oop.h"
using namespace std;

int S21Matrix::get_rows() { return this->rows_; }

int S21Matrix::get_cols() { return this->cols_; }

void S21Matrix::set_rows(int rows) {
  int t = 0;
  if (rows < 1) {
    throw out_of_range("Error");
  }
  S21Matrix tmp(rows, this->cols_);
  if (this->rows_ < rows) {
    t = this->rows_;
  } else {
    t = rows;
  }
  for (int i = 0; i < t; i++) {
    for (int j = 0; j < this->cols_; j++) {
      tmp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = tmp;
}

void S21Matrix::set_cols(int cols) {
  int t = 0;
  if (cols < 1) {
    throw out_of_range("Error");
  }
  S21Matrix tmp(this->rows_, cols);
  if (this->cols_ < cols) {
    t = this->cols_;
  } else {
    t = cols;
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < t; j++) {
      tmp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = tmp;
}

double **S21Matrix::get_matrix() { return this->matrix_; }

S21Matrix::S21Matrix() {
  this->rows_ = 0;
  this->cols_ = 0;
  this->matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) { this->create_matrix(rows, cols); }

S21Matrix::S21Matrix(int rows) : S21Matrix(rows, rows) {}

S21Matrix::S21Matrix(const S21Matrix &other) {
  if (!(other.rows_ > 0 && other.cols_ > 0 && this->matrix_)) {
    throw out_of_range("Error, other matrix does not exist!!!");
  }
  this->create_matrix(other.rows_, other.cols_);
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++)
      for (int j = 0; j < this->cols_; j++)
        this->matrix_[i][j] = other.matrix_[i][j];
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  if (!(other.rows_ > 0 && other.cols_ > 0 && this->matrix_)) {
    throw out_of_range("Error, other matrix does not exist!!!");
  }
  this->create_matrix(other.rows_, other.cols_);
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++)
      for (int j = 0; j < this->cols_; j++)
        this->matrix_[i][j] = other.matrix_[i][j];
    other.remove_matrix();
  }
}

S21Matrix::~S21Matrix() { remove_matrix(); }

void S21Matrix::create_matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw out_of_range("Dimensional error!!!");
  } else {
    this->rows_ = rows;
    this->cols_ = cols;
    matrix_ = new double *[rows_];
    if (matrix_ == nullptr) {
    } else {
      for (int i = 0; i < rows_; i++) {
        matrix_[i] = new double[cols_];
        if (matrix_[i] == nullptr) {
          for (int j = 0; j < i; j++) {
            delete[] matrix_[j];
          }
          delete[] matrix_;
          matrix_ = nullptr;
          rows_ = 0;
          cols_ = 0;
        }
      }
    }
  }
}

void S21Matrix::remove_matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool res = true;
  if (this->matrix_ == nullptr || other.matrix_ == nullptr ||
      this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    res = false;
  }
  for (int i = 0; i < this->rows_ && res; i++) {
    for (int j = 0; j < this->cols_ && res; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) res = false;
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (other.matrix_ == nullptr || this->matrix_ == nullptr) {
    throw out_of_range("Error, other matrix does not exist!!!");
  }
  if ((this->rows_ == other.rows_) && (this->cols_ == other.cols_)) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] += other.matrix_[i][j];
      }
    }
  } else {
    throw length_error("Error, matrix addition is not possible!!!");
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (other.matrix_ == nullptr || this->matrix_ == nullptr) {
    throw out_of_range("Error, other matrix does not exist!!!");
  }
  if ((this->rows_ == other.rows_) && (this->cols_ == other.cols_)) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  } else {
    throw length_error("Error, matrix addition is not possible!!!");
  }
}

void S21Matrix::MulNumber(const double num) {
  if (this->matrix_ == nullptr) {
    throw out_of_range("Error, the matrix does not exist!!!");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] *= num;
      }
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->matrix_ == nullptr || other.matrix_ == nullptr || this->rows_ < 1 ||
      other.rows_ < 1) {
    throw out_of_range("Error, other matrix does not exist!!!");
  } else {
    if (this->cols_ == other.rows_) {
      S21Matrix res(this->rows_, other.cols_);
      for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < other.cols_; j++)
          for (int k = 0; k < other.rows_; k++)
            res.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      this->remove_matrix();
      this->create_matrix(res.rows_, res.cols_);
      if (this->matrix_ != nullptr) {
        for (int i = 0; i < res.rows_; i++) {
          for (int j = 0; j < res.cols_; j++)
            this->matrix_[i][j] = res.matrix_[i][j];
        }
      }
    } else {
      throw length_error("Error, matrix addition is not possible!!!");
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  if (this->matrix_ == nullptr && this->rows_ < 1) {
    throw out_of_range("Error, other matrix does not exist!!!");
  }
  S21Matrix res(this->cols_, this->rows_);
  if (res.matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++)
      for (int j = 0; j < this->cols_; j++)
        res.matrix_[j][i] = this->matrix_[i][j];
  }
  return res;
}

double S21Matrix::Determinant() {
  double res = 0;
  if (this->matrix_ == nullptr && this->rows_ < 1) {
    throw out_of_range("Error, other matrix does not exist!!!");
  }
  if (this->rows_ == this->cols_) {
    res = get_determinant();
  } else {
    throw length_error("Error, matrix addition is not possible!!!");
  }
  return res;
}

double S21Matrix::get_determinant() {
  double res = 0;
  if (this->rows_ == 1)
    res = this->matrix_[0][0];
  else {
    S21Matrix t(this->rows_ - 1, this->cols_ - 1);
    for (int i = 0; i < this->cols_; i++) {
      this->minor_matrix(0, i, t);
      if (i % 2) {
        res -= this->matrix_[0][i] * t.get_determinant();
      } else {
        res += this->matrix_[0][i] * t.get_determinant();
      }
    }
  }
  return res;
}

void S21Matrix::minor_matrix(int rows, int cols, const S21Matrix &tmp) {
  int q = 0;
  int k = 0;
  for (int i = 0; i < this->rows_; i++) {
    if (i == rows) {
      continue;
    }
    k = 0;
    for (int j = 0; j < this->cols_; j++) {
      if (j == cols) {
        continue;
      }
      tmp.matrix_[q][k] = this->matrix_[i][j];
      k++;
    }
    q++;
  }
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix res(this->rows_, this->cols_);
  if (this->matrix_ == nullptr || this->rows_ < 1) {
    throw out_of_range("Error, the matrix does not exist!!!");
  }
  if (this->rows_ == this->cols_) {
    S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
    for (int i = 0; i < this->rows_; ++i)
      for (int j = 0; j < this->cols_; ++j) {
        minor_matrix(i, j, minor);
        double d = minor.Determinant();
        res.matrix_[i][j] = d * pow(-1.0, i + j);
      }
  } else {
    throw length_error("Error, matrix addition is not possible!!!");
  }
  return res;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

void S21Matrix::operator+=(const S21Matrix &other) { this->SumMatrix(other); }

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

void S21Matrix::operator-=(const S21Matrix &other) { this->SubMatrix(other); }

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double n) {
  S21Matrix res(*this);
  res.MulNumber(n);
  return res;
}

void S21Matrix::operator*=(const double num) { this->MulNumber(num); }

void S21Matrix::operator*=(const S21Matrix &other) { this->MulMatrix(other); }

void S21Matrix::operator=(const S21Matrix &other) {
  if (other.matrix_ == nullptr || other.rows_ < 1) {
    throw out_of_range("Error, other matrix does not exist!!!");
  }
  this->remove_matrix();
  this->create_matrix(other.rows_, other.cols_);
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}

bool S21Matrix::operator==(const S21Matrix &other) {
  bool res = this->EqMatrix(other);
  return res;
}

double &S21Matrix::operator()(int i, int j) {
  if (i >= this->rows_ || j >= this->cols_ || i < 0 || j < 0)
    throw out_of_range("Error, wrong index i or index j!!!");
  return this->matrix_[i][j];
}

S21Matrix S21Matrix::InverseMatrix() {
  if (!(this->rows_ > 0 && this->cols_ > 0 && this->matrix_ != nullptr)) {
    throw out_of_range("Error, other matrix does not exist!!!");
  }
  double d = Determinant();
  if (!d) {
    throw logic_error("Error, сalculation error");
  }
  S21Matrix res = this->CalcComplements().Transpose();
  res *= 1.0 / d;
  return res;
}