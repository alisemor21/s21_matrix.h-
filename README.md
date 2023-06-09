# s21_matrix+

Реализация библиотеки s21_matrix_oop.h


## Introduction

В данном проекте вам предстоит еще раз реализовать уже знакомую вам по проекту **s21_matrix** библиотеку для работы с матрицами, но на этот раз, используя объектно-ориентированный подход (см. материалы). Объектно-ориентированный подход позволяет реализовать библиотеку для работы с матрицами в виде отдельного класса, над объектами которого определены операции, представленные как методами, так и стандартными операторами +, -, * и т.д.


## Information


### Пример класса матрицы на C++

```cpp
class S21Matrix {
    private:
        // Attributes
        int rows_, cols_;         // Rows and columns
        double **matrix_;         // Pointer to the memory where the matrix is allocated

    public:
        S21Matrix();              // Default constructor
        ~S21Matrix();             // Destructor

        void SumMatrix(const S21Matrix& other); 
        // Other methods..
}
```

### Напоминание основных положений о матрице

Матрица - прямоугольная таблица чисел, расположенных в m стрках и n столбцах

```
    1 2 3
A = 4 5 6
    7 8 9
```

```
     1  2  3  4
В =  5  6  7  8
     9 10 11 12
```

Получить нужный элемент можно при помощи индексов, так
A[1,1] = 1, где первый индекс - номер строки, второй - номер столбца.

Порядок матрицы — это число ее строк или столбцов. \
Главная диагональ квадратной матрицы — это диагональ, идущая из левого верхнего в правый нижний угол. \
Прямоугольная матрица (В) — это матрица, у которой число строк не равно числу столбцов. \
Квадратная матрица (А) — это матрица у которой число строк равно числу столбцов.

### Операции над матрицами

Ниже представлено краткое описание операций над матрицами, которые необходимо реализовать в разрабатываемой библиотеке. Они похожи на операции выполненные вами ранее в блоке "Структурного Программирования" и более подробное описание каждой из них можно посмотреть там. Обратите внимание, что некоторые операции имеют исключительные ситуации, требующие специальной обработки с использованием механизма исключений. 

| Операция    | Описание   | Исключительные ситуации |
| ----------- | ----------- | ----------- |
| `bool EqMatrix(const S21Matrix& other)` | Проверяет матрицы на равенство между собой |  |
| `void SumMatrix(const S21Matrix& other)` | Прибавляет вторую матрицы к текущей | различная размерность матриц |
| `void SubMatrix(const S21Matrix& other)` | Вычитает из текущей матрицы другую | различная размерность матриц |
| `void MulNumber(const double num)` | Умножает текущую матрицу на число |  |
| `void MulMatrix(const S21Matrix& other)` | Умножает текущую матрицу на вторую | число столбцов первой матрицы не равно числу строк второй матрицы |
| `S21Matrix Transpose()` | Создает новую транспонированную матрицу из текущей и возвращает ее |  |
| `S21Matrix CalcComplements()` | Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее | матрица не является квадратной |
| `double Determinant()` | Вычисляет и возвращает определитель текущей матрицы | матрица не является квадратной |
| `S21Matrix InverseMatrix()` | Вычисляет и возвращает обратную матрицу | определитель матрицы равен 0 |

Помимо реализации данных операций, необходимо также реализовать конструкторы и деструкторы:

| Метод    | Описание   |
| ----------- | ----------- |
| `S21Matrix()` | Базовый конструктор, инициализирующий матрицу некоторой заранее заданной размерностью |  
| `S21Matrix(int rows, int cols)` | Параметризированный конструктор с количеством строк и столбцов | 
| `S21Matrix(const S21Matrix& other)` | Конструктор копирования |
| `S21Matrix(S21Matrix&& other)` | Конструктор переноса |
| `~S21Matrix()` | Деструктор |

А также нужно перегрузить следующие операторы, частично соответствующие операциям выше:

| Оператор    | Описание   | Исключительные ситуации |
| ----------- | ----------- | ----------- |
| `+`      | Сложение двух матриц  | различная размерность матриц |
| `-`   | Вычитание одной матрицы из другой | различная размерность матриц |
| `*`  | Умножение матриц и умножение матрицы на число | число столбцов первой матрицы не равно числу строк второй матрицы |
| `==`  | Проверка на равенство матриц (`EqMatrix`) | |
| `=`  | Присвоение матрице значений другой матрицы | |
| `+=`  | Присвоение сложения (`SumMatrix`)   | различная размерность матриц |
| `-=`  | Присвоение разности (`SubMatrix`) | различная размерность матриц |
| `*=`  | Присвоение умножения (`MulMatrix`/`MulNumber`) | число столбцов первой матрицы не равно числу строк второй матрицы |
| `(int i, int j)`  | Индексация по элементам матрицы (строка, колонка) | индекс за пределами матрицы |




## Реализация функции библиотеки s21_matrix_oop.h

- Программа должна быть разработана на языке C++ стандарта C++17 с использованием компилятора gcc
- Код программы должен находиться в папке src
- При написании кода необходимо придерживаться Google Style
- Реализовать матрицу в виде класса `S21Matrix`
- Хранить только приватные поля `matrix_`, `rows_` и `cols_`
- Реализовать доступ к приватным полям `rows_` и `cols_` через accessor и mutator. При увеличении размера - матрица дополняется нулевыми элементами, при уменьшении - лишнее просто отбрасывается
- Оформить решение как статическую библиотеку (с заголовочным файлом s21_matrix_oop.h)
- Реализовать операции, описанные [выше](#операции-над-матрицами)
- Перегрузить операторы в соответствии с таблицой в разделе [выше](#операции-над-матрицами).
- Подготовить полное покрытие unit-тестами функций библиотеки c помощью библиотеки GTest
- Предусмотреть Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_matrix_oop.a)

