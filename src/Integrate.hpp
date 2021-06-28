#include <iostream>
#include <cmath>
#include <string>

using namespace std;
/*!
* Класс для выбора метода интегрирования, пределов интегрирования и точности.
*/
class IntegrationMethod {
protected:
    /// Левая граница интегрирования
    double a;
    /// Правая граница интегрирования
    double b;
    /// Точность
    double eps; 
    /// Название метода
    string name;
    
public:
    /// Конструктор принимающий принимает числа двойной точности с плавающей запятой.
    IntegrationMethod(string name, double a, double b, double eps);
    /// Получение названия метода константы. 
    string GetName() const;
    /// Виртуалная функция интегрирования. 
    virtual double Integrate(double (*f)(double)) = 0; 
};

/*!
* Класс для метода левых прямоугольников.
*/
class SquareLeftMethod : public IntegrationMethod {
public:
    /// Конструктор метода левых прямоугольников.
    SquareLeftMethod(double a, double b, double eps); 
    /// Функция интегрирования
    double Integrate(double (*f)(double));
};

/*!
* Класс для метода прямоугольников.
*/
class SquareCenterMethod : public IntegrationMethod {
public:
    /// Конструктор метода прямоугольников.
    SquareCenterMethod(double a, double b, double eps); 
    /// Функция интегрирования
    double Integrate(double (*f)(double)); 
};

/*!
* Класс для метода правых прямоугольников.
*/
class SquareRightMethod : public IntegrationMethod {
public:
    /// Конструктор метода правых прямоугольников.
    SquareRightMethod(double a, double b, double eps); 
    // Функция интегрирования.
    double Integrate(double (*f)(double)); 
};

/*!
* Класс для метода трапеций.
*/
class TrapecyMethod : public IntegrationMethod {
public:
    /// конструктор метода трапеций.
    TrapecyMethod(double a, double b, double eps); 
    /// функция интегрирования.
    double Integrate(double (*f)(double)); 
};

/*!
* Класс для метода Симпсона(парабол).
*/
class SimpsonMethod : public IntegrationMethod {
public:
    // Конструктор метода Симпсона.
    SimpsonMethod(double a, double b, double eps);
    // Функция интегрирования.
    double Integrate(double (*f)(double)); 
};

/*!
* Класс для метода Буля.
*/
class BullMethod : public IntegrationMethod {
public:
    /// Конструктор метода Буля.
    BullMethod(double a, double b, double eps); 
    /// Функция интегрирования.
    double Integrate(double (*f)(double)); 
};

/*!
* Класс для метода 3/8.
*/
class ThreeEightsMethod : public IntegrationMethod {
public:
    /// Конструктор метода 3/8.
    ThreeEightsMethod(double a, double b, double eps); 
    /// Функция интегрирования.
    double Integrate(double (*f)(double)); 
};

/*!
*Конструктор базового класса
*Запоминает переданные параметры — название метода, границы интегрирования и точность
*/
IntegrationMethod::IntegrationMethod(string name, double a, double b, double eps) {
    this->name = name;
    this->a = a;
    this->b = b;
    this->eps = eps;
}

/// Получение названия метода.
string IntegrationMethod::GetName() const {
    /// Возвращаем имя.
    return name; 
}

/// Конструктор метода левых прямоугольников.
SquareLeftMethod::SquareLeftMethod(double a, double b, double eps) : IntegrationMethod("Square left", a, b, eps) {

}

/// Конструктор метода центральных прямоугольников.
SquareCenterMethod::SquareCenterMethod(double a, double b, double eps) : IntegrationMethod("Square center", a, b, eps) {

}

/// Конструктор метода правых прямоугольников.
SquareRightMethod::SquareRightMethod(double a, double b, double eps) : IntegrationMethod("Square right", a, b, eps) {

}

/// Конструктор метода трапеций.
TrapecyMethod::TrapecyMethod(double a, double b, double eps) : IntegrationMethod("Trapecy", a, b, eps) {

}

/// Конструктор метода Симпсона.
SimpsonMethod::SimpsonMethod(double a, double b, double eps) : IntegrationMethod("Simpson", a, b, eps) {

}

/// Конструктор метода Буля.
BullMethod::BullMethod(double a, double b, double eps) : IntegrationMethod("Bull", a, b, eps) {

}

/// Конструктор метода 3/8.
ThreeEightsMethod::ThreeEightsMethod(double a, double b, double eps) : IntegrationMethod("Three eights (3/8)", a, b, eps) {

}

/*!
* Интегрирование методом левых прямоугольников с заданной точностью.
*/
double SquareLeftMethod::Integrate(double (*f)(double)) {
    /// Начальное количество разбиений.
    long n = 2; 
    /// Вычисляем шаг интегрирования.
    double h = (b - a) / n; 
    // Вычисляем значение интеграла для n = 2.
    double sum = (f(a) + f(a + h)) * h; 
    double sum1;

    do {
        /// Обновляем старое значение суммы.
        sum1 = sum; 
        /// Сбрасываем текущее значение суммы.
        sum = 0; 
        /// Уменьшаем шаг в два раза.
        h /= 2; 
        /// Увеличиваем количество интервалов в два раза.
        n *= 2; 

        /// Считаем более точное значение интеграла.
        for (int i = 0; i <= n - 1; i++)
            sum += f(a + i * h);

        sum *= h;
    /// Повторяем, пока не достигнем нужной точности.
    } while (fabs(sum - sum1) > eps); 
    /// Возвращаем найденное значение интеграла.
    return sum; 
}

/*!
* Интегрирование методом прямоугольников с заданной точностью.
*/
double SquareCenterMethod::Integrate(double (*f)(double)) {
    /// Начальное количество разбиений.
    long n = 2; 
    /// Вычисляем шаг интегрирования.
    double h = (b - a) / n; 
    /// Вычисляем значение интеграла для n = 2.
    double sum = (f(a + 0.5*h) + f(a + 1.5*h)) * h; 
    double sum1;
    
    do {
        /// Обновляем старое значение суммы.
        sum1 = sum; 
        /// Сбрасываем текущее значение суммы.
        sum = 0; 
        /// Уменьшаем шаг в два раза.
        h /= 2;
        /// Увеличиваем количество интервалов в два раза.
        n *= 2; 

        /// Считаем более точное значение интеграла.
        for (int i = 0; i < n; i++)
            sum += f(a + (i + 0.5) * h);

        sum *= h;
    /// Повторяем, пока не достигнем нужной точности.
    } while (fabs(sum - sum1) > eps); 
    /// Возвращаем найденное значение интеграла.
    return sum; 
}

/*!
* Интегрирование методом правых прямоугольников с заданной точностью.
*/
double SquareRightMethod::Integrate(double (*f)(double)) {
    /// Начальное количество разбиений.
    long n = 2; 
    /// Вычисляем шаг интегрирования.
    double h = (b - a) / n; 
    /// Вычисляем значение интеграла для n = 2.
    double sum = (f(a + h) + f(a + 2*h)) * h; 
    double sum1;

    do {
        /// Обновляем старое значение суммы.
        sum1 = sum; 
        /// Сбрасываем текущее значение суммы.
        sum = 0; 
        /// Уменьшаем шаг в два раза.
        h /= 2; 
        /// Увеличиваем количество интервалов в два раза.
        n *= 2; 

        /// Считаем более точное значение интеграла.
        for (int i = 1; i <= n; i++)
            sum += f(a + i * h);

        sum *= h;
    /// Повторяем, пока не достигнем нужной точности.
    } while (fabs(sum - sum1) > eps); 
    /// Возвращаем найденное значение интеграла.
    return sum; 
}

/*!
* Интегрирование методом трапеций с заданной точностью.
*/
double TrapecyMethod::Integrate(double (*f)(double)) {
    /// Начальное количество разбиений.
    long n = 2; 
    /// Вычисляем шаг интегрирования.
    double h = (b - a) / n; 
    /// Вычисляем значение интеграла для n = 2.
    double sum = (f(a) / 2 + f(a + h) + f(b) / 2) * h; 

    double sum1;

    do {
        /// Обновляем старое значение суммы.
        sum1 = sum; 
        /// Сбрасываем текущее значение суммы.
        sum = (f(a) + f(b)) / 2; 
        /// Уменьшаем шаг в два раза.
        h /= 2; 
        /// Увеличиваем количество интервалов в два раза.
        n *= 2; 

        /// Считаем более точное значение интеграла.
        for (int i = 1; i < n; i++)
            sum += f(a + i * h);

        sum *= h;
      /// Повторяем, пока не достигнем нужной точности.
    } while (fabs(sum1 - sum) > eps); 
    /// Возвращаем найденное значение интеграла.
    return sum; 
}

/*!
* Интегрирование методом парабол(Симпсона) с заданной точностью.
*/
double SimpsonMethod::Integrate(double (*f)(double)) {
    /// Начальное количество разбиений.
    long n = 2; 
    /// Вычисляем шаг интегрирования.
    double h = (b - a) / n; 
    /// Вычисляем значение интеграла для n = 2.
    double sum = (f(a) + 4 * f(a + h) + f(b)) * h / 3; 
    double sum1;

    do {
        /// Обновляем старое значение суммы.
        sum1 = sum; 
        /// Сбрасываем текущее значение суммы.
        sum = f(a) + f(b); 
        /// Уменьшаем шаг в два раза.
        h /= 2; 
        /// Увеличиваем количество интервалов в два раза.
        n *= 2;

        /// Считаем более точное значение интеграла.
        for (int i = 1; i <= n / 2; i++)
            sum += 4 * f(a + (2 * i - 1) * h);

        for (int i = 1; i < n / 2; i++)
            sum += 2 * f(a + 2 * i * h);

        sum *= h / 3;
    /// Повторяем, пока не достигнем нужной точности.
    } while (fabs(sum1 - sum) > eps); 
    /// Возвращаем найденное значение интеграла.
    return sum; 
}

/*!
* Интегрирование методом Буля с заданной точностью.
*/
double BullMethod::Integrate(double (*f)(double)) {
    /// Начальное количество разбиений.
    long n = 4; 
    /// Вычисляем шаг интегрирования.
    double h = (b - a) / n; 
    /// Вычисляем значение интеграла для n = 4.
    double sum = (7*(f(a) + f(b)) + 32*(f(a + h) + f(a + 3 * h)) + 12*f(a + 2 * h)) * 2 * h / 45; 
    double sum1;

    do {
        /// Обновляем старое значение суммы.
        sum1 = sum; 
        /// Сбрасываем текущее значение суммы.
        sum = 7 * (f(a) + f(b)); 
        /// Уменьшаем шаг в два раза
        h /= 2; 
        /// Увеличиваем количество интервалов в два раза.
        n *= 2; 

        /// Находим сумму по формуле Буля.
        for (int i = 1; i < n / 4; i++)
            sum += 14 * f(a + 4 * i * h);

        for (int i = 1; i <= n / 2; i++)
            sum += 32 * f(a + (2 * i - 1) * h);

        for (int i = 1; i <= n / 4; i++)
            sum += 12 * f(a + (4 * i - 2) * h);
        /// Возвращаем найденное значение интеграла.
        sum *= 2 * h / 45; 
      /// Повторяем, пока не достигнем нужной точности.
    } while (fabs(sum - sum1) > eps); 
    /// Возвращаем найденное значение интеграла.
    return sum; 
}

/*!
* Интегрирование методом 3/8 с заданной точностью.
*/
double ThreeEightsMethod::Integrate(double (*f)(double)) {
    /// Начальное количество разбиений.
    long n = 3; 
    /// Вычисляем шаг интегрирования.
    double h = (b - a) / n; 
    /// Вычисляем значение интеграла для n = 3.
    double sum = (f(a) + 3*f(a + h) + 3*f(a + 2*h) + f(b)) * h * 3 / 8; 
    double sum1;

    do {
        /// Обновляем старое значение суммы.
        sum1 = sum; 
        /// Сбрасываем текущее значение суммы.
        sum = f(a) + f(b); 
        /// Уменьшаем шаг в два раза.
        h /= 2; 
        /// Увеличиваем количество интервалов в два раза.
        n *= 2; 

        /// Считаем более точное значение интеграла.
        for (int i = 1; i < n; i++) {
            if (i % 3 == 0) {
                sum += 2 * f(a + i * h);
            }
            else {
                sum += 3 * f(a + i * h);
            }
        }

        sum *= 3.0 / 8 * h;
      /// Повторяем, пока не достигнем нужной точности.
    } while (fabs(sum1 - sum) > eps); 
    /// Возвращаем найденное значение интеграла.
    return sum; 
}
