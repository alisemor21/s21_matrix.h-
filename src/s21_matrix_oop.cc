#include "s21_matrix_oop.h"
using namespace std;

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (IsValidMatrix()) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = NULL;
    cols_ = 0;
    rows_ = 0;
  }
}

S21Matrix::S21Matrix(int rows, int cols) {
  matrix_ = new double *[rows]();
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols]();
  }
  cols_ = cols;
  rows_ = rows;
};

S21Matrix::S21Matrix(const S21Matrix &other)
    : S21Matrix(other.rows_, other.cols_)  // Конструктор копирования
{
  operator=(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) {  // Конструктор переноса
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.cols_ = 0;
  other.rows_ = 0;
  other.matrix_ = nullptr;
}

void S21Matrix::InitMatrix() {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] = i + j;
    }
  }
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(const int rows) {
  if (rows < 1) throw std::logic_error("error invalid size");
  if (rows != rows_) {
    S21Matrix temp(rows, cols_);
    for (int i = 0; i < rows_ && i < temp.rows_; i++) {
      for (int j = 0; j < cols_ && j < temp.cols_; j++) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = std::move(temp);
  }
}

void S21Matrix::SetCols(const int cols) {
  if (cols < 1) throw std::logic_error("error invalid size");
  if (cols != cols_) {
    S21Matrix temp(rows_, cols);
    for (int i = 0; i < rows_ && i < temp.rows_; i++) {
      for (int j = 0; j < cols_ && j < temp.cols_; j++) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }

    *this = std::move(temp);
  }
}

bool S21Matrix::IsValidMatrix() const {
  if (matrix_ == nullptr) {
    return false;
  } else {
    return true;
  }
}

void S21Matrix::PrintMatrix() {
  cout << "\n---------------\n";
  for (int i = 0; i < GetRows(); i++) {
    for (int j = 0; j < GetCols(); j++) {
      cout << matrix_[i][j] << " ";
    }
    cout << "\n";
  }
  cout << "---------------\n";
}

void S21Matrix::NewPointer(double **a, double *b) const { *a = b; }

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool res = true;

  if (GetRows() != other.GetRows() || GetCols() != other.GetCols()) {
    res = false;
  } else {
    for (int i = 0; i < GetRows(); i++) {
      for (int j = 0; j < GetCols(); j++) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          res = false;
        }
      }
    }
  }

  return res;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!IsValidMatrix() || !other.IsValidMatrix()) {
    throw std::logic_error("Invalid Matrix");
  }

  if (other.GetRows() == GetRows() && other.GetCols() == GetCols()) {
    for (int i = 0; i < GetRows(); i++) {
      for (int j = 0; j < GetCols(); j++) {
        matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
      }
    }
  } else {
    throw std::logic_error("Invalid sizes of matrices");
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!IsValidMatrix() || !other.IsValidMatrix()) {
    throw std::logic_error("Invalid Matrix");
  }

  if (other.GetRows() == GetRows() && other.GetCols() == GetCols()) {
    for (int i = 0; i < GetRows(); i++) {
      for (int j = 0; j < GetCols(); j++) {
        matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
      }
    }
  } else {
    throw std::logic_error("Invalid sizes of matrices");
  }
}

void S21Matrix::MulNumber(const double num) {
  if (!IsValidMatrix()) {
    throw std::logic_error("Invalid Matrix");
  }
  for (int i = 0; i < GetRows(); i++) {
    for (int j = 0; j < GetCols(); j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (GetCols() == other.GetRows() && GetRows() == other.GetCols()) {
    S21Matrix result = S21Matrix(GetRows(), other.GetCols());
    for (int i = 0; i < GetRows(); i++) {
      for (int j = 0; j < other.GetCols(); j++) {
        for (int k = 0; k < GetCols(); k++) {
          result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    *this = S21Matrix(std::move(result));
  } else {
    throw std::logic_error("Invalid Matrix");
  }
}

S21Matrix S21Matrix::Transpose() {
  if (!IsValidMatrix()) {
    throw std::logic_error("Invalid Matrix");
  }
  S21Matrix tmp(GetCols(), GetRows());
  for (int i = 0; i < GetRows(); i++) {
    for (int j = 0; j < GetCols(); j++) {
      tmp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return tmp;
}

double S21Matrix::Determinant() const {
  if (!IsValidMatrix()) {
    throw std::logic_error("Invalid matrix");
  }
  if (GetRows() != GetCols()) {
    throw std::logic_error("Invalid operation");
  }
  return Det(matrix_, GetRows());
}

double S21Matrix::Det(double **a, int n) const {
  if (n == 1) return a[0][0];
  if (n == 2) return a[0][0] * a[1][1] - a[0][1] * a[1][0];

  int number = 0;
  double sum = 0;
  double **temp = new double *[n - 1];
  for (int i = 0; i < n; i++) {
    number = 0;
    for (int j = 0; j < n; j++) {
      if (i != j) NewPointer(&temp[number++], a[j]);
    }
    sum += pow(-1, i + n - 1) * a[i][n - 1] * Det(temp, n - 1);
  }
  delete[] temp;
  return sum;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (!IsValidMatrix()) {
    throw std::logic_error("Invalid matrix");
  }
  if (rows_ != cols_) throw std::logic_error("error invalid size");
  S21Matrix Result(rows_, cols_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      S21Matrix Minor = this->MinorCreate(i + 1, j + 1);
      Result.matrix_[i][j] = Minor.Determinant() * pow(-1, (i + j));
    }
  }
  return Result;
}
S21Matrix S21Matrix::MinorCreate(int rows, int cols) const {
  S21Matrix Minor(rows_ - 1, cols_ - 1);
  rows--;
  cols--;
  auto i_minor = 0;
  for (auto i = 0; i < rows_; i++) {
    auto j_minor = 0;
    for (auto j = 0; j < cols_; j++) {
      if (i != rows && j != cols) {
        Minor.matrix_[i_minor][j_minor] = this->matrix_[i][j];
        j_minor++;
      }
    }
    if (i != rows) i_minor++;
  }
  return Minor;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (!IsValidMatrix()) {
    throw std::logic_error("Invalid matrix");
  }
  double Det = this->Determinant();
  if (fabs(Det - 0) < 01E-7) throw std::logic_error("determinant equal zero");
  S21Matrix Result = this->CalcComplements();
  Result.Transpose();
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      Result.matrix_[i][j] = Result.matrix_[i][j] / Det;
    }
  }
  return Result;
}

double &S21Matrix::operator()(int i, int j) {
  if (i > rows_ || i < 0 || j > cols_ || j < 0)
    throw std::logic_error("index is outside the matrix");
  return matrix_[i][j];
}

double S21Matrix::operator()(int i, int j) const {
  if (i > rows_ || i < 0 || j > cols_ || j < 0)
    throw std::logic_error("index is outside the matrix");
  return matrix_[i][j];
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}
S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}
S21Matrix &S21Matrix::operator*=(const double &num) {
  MulNumber(num);
  return *this;
}
S21Matrix &S21Matrix::operator*=(const S21Matrix &first) {
  MulMatrix(first);
  return *this;
}
S21Matrix operator+(const S21Matrix &first, const S21Matrix &second) {
  S21Matrix result = first;
  result += second;
  return result;
}
S21Matrix operator-(const S21Matrix &first, const S21Matrix &second) {
  S21Matrix result = first;
  result -= second;
  return result;
}
S21Matrix operator*(const S21Matrix &first, const S21Matrix &second) {
  S21Matrix result = first;
  result *= second;
  return result;
}
S21Matrix operator*(const S21Matrix &first, const double &num) {
  S21Matrix result = first;
  result *= num;
  return result;
}
S21Matrix operator*(const double &num, const S21Matrix &second) {
  S21Matrix result = second;
  result *= num;
  return result;
}
bool S21Matrix::operator==(const S21Matrix &other) {
  bool res = EqMatrix(other);
  return res;
}
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (!other.IsValidMatrix()) {
    throw std::logic_error("Invalid matrix");
  }
  if (this != &other) {
    this->~S21Matrix();
    auto temp = S21Matrix(other.rows_, other.cols_);
    for (int i = 0; i < temp.rows_; i++) {
      for (int j = 0; j < temp.cols_; j++) {
        temp.matrix_[i][j] = other.matrix_[i][j];
      }
    }
    this->rows_ = temp.rows_;
    this->cols_ = temp.cols_;
    this->matrix_ = temp.matrix_;
    temp.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this == &other) return *this;
  this->~S21Matrix();
  cols_ = other.cols_;
  rows_ = other.rows_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  return *this;
}
