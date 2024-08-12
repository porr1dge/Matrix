#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_
#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double **matrix_;  // Pointer to the memory where the matrix is allocated
  void create_matrix(int rows, int cols);
  void remove_matrix();
  double get_determinant();
  void minor_matrix(int rows, int cols, const S21Matrix &t);

 public:
  int get_rows();
  int get_cols();
  void set_rows(int rows);
  void set_cols(int cols);
  double **get_matrix();
  S21Matrix();  // Default constructor
  S21Matrix(int rows);
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();  // Destructor

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  S21Matrix operator+(const S21Matrix &other);
  void operator+=(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  void operator-=(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double n);
  void operator*=(const double n);
  void operator*=(const S21Matrix &other);
  void operator=(const S21Matrix &other);
  bool operator==(const S21Matrix &other);
  double &operator()(int i, int j);
};
#endif  // SRC_MATRIX_H_
