#include <iostream>
#include <iomanip>
#include <cmath>
#include <memory>
#include <string>
#include "Integrate.hpp"

/*!
* Интегрируемая функция.
*/
double f(double x) {
    return sin(x);
}

/*!
* Получение метода интегрирования.
*/
shared_ptr<IntegrationMethod> GetIntegrationMethod(double a, double b, double eps) {
    /// Выбираемый метод.
    int method; 
    cout << "Select method for find integrate: " << endl;
    cout << "1. Square left" << endl;
    cout << "2. Square center" << endl;
    cout << "3. Square right" << endl;
    cout << "4. Trapecy" << endl;
    cout << "5. Simpson (parabols)" << endl;
    cout << "6. Bull" << endl;
    cout << "7. Three-eights (3/8)" << endl;
    cin >> method;
    /*!
    * Проверка и выбор метода интегрирования.
    */
    while (method < 1 || method > 7) {
        cout << "Imvalid method number, try again: ";
        /// Считываем метод.
        cin >> method; 
    }

    /// Возвращение выбранного метода.
    switch (method) {
        case 1:
            return shared_ptr<IntegrationMethod>(new SquareLeftMethod(a, b, eps));

        case 2:
            return shared_ptr<IntegrationMethod>(new SquareCenterMethod(a, b, eps));

        case 3:
            return shared_ptr<IntegrationMethod>(new SquareRightMethod(a, b, eps));

        case 4:
            return shared_ptr<IntegrationMethod>(new TrapecyMethod(a, b, eps));

        case 5:
            return shared_ptr<IntegrationMethod>(new SimpsonMethod(a, b, eps));

        case 6:
            return shared_ptr<IntegrationMethod>(new BullMethod(a, b, eps));

        case 7:
            return shared_ptr<IntegrationMethod>(new ThreeEightsMethod(a, b, eps));
    }

    return nullptr;
}
/*!
* Считывает интервал, точность, получает метод и выводит значение интеграла.
*/
int main() {
    /// Левая граница интегрирования.
    double a; 
    /// Правая граница интегрирования.
    double b; 
    /// точность.
    double eps; 

    cout << "Enter a, b: ";
    /// Считываем отрезок интегрирования.
    cin >> a >> b; 
    cout << "Enter eps: ";
    /// Считываем точность.
    cin >> eps; 
    /// Получаем метод.
    shared_ptr<IntegrationMethod> method = GetIntegrationMethod(a, b, eps); 

    cout << "Integrate by method '" << method->GetName() << "': " << setprecision(15) << method->Integrate(f) << endl;

}