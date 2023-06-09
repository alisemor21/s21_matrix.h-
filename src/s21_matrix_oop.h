#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <string>
using namespace std;

#define OK 0
#define BAD_MATRIX 1
#define CALC_ERROR 2

class S21Matrix {
 public:
  S21Matrix();
  ~S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);

  void InitMatrix();
  int GetRows() const;
  int GetCols() const;
  void SetRows(const int rows);
  void SetCols(const int cols);

  double &operator()(int i, int j);
  double operator()(int i, int j) const;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const double &num);
  S21Matrix &operator*=(const S21Matrix &first);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other);

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  double Determinant() const;
  double Det(double **a, int n) const;
  S21Matrix CalcComplements() const;
  S21Matrix MinorCreate(int rows, int cols) const;
  S21Matrix InverseMatrix() const;

  bool IsValidMatrix() const;
  void PrintMatrix();
  void NewPointer(double **a, double *b) const;

 private:
  int rows_, cols_;
  double **matrix_;
};

S21Matrix operator+(const S21Matrix &first, const S21Matrix &second);
S21Matrix operator-(const S21Matrix &first, const S21Matrix &second);
S21Matrix operator*(const S21Matrix &first, const S21Matrix &second);
S21Matrix operator*(const S21Matrix &first, const double &num);
S21Matrix operator*(const double &num, const S21Matrix &second);

#endif  // SRC_S21_MATRIX_OOP_H_
