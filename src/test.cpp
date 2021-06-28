#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
#include "Integrate.hpp"

using namespace std;

// константная функция
double Constant(double x) {
    return 1;
}

// линейная функция
double Linear(double x) {
    return x;
}

// параболическая функция
double Parabola(double x) {
    return x*x;
}
// нелинейная функция
double NonLinear(double x) {
    return x*x*x * (exp(x) - 1);
}

void MakeTest(string name, double (*f)(double), double a, double b, double eps, double integral) {
    // вектор методов
    vector<shared_ptr<IntegrationMethod>> methods = {
        shared_ptr<IntegrationMethod>(new SquareCenterMethod(a, b, eps)),
        shared_ptr<IntegrationMethod>(new TrapecyMethod(a, b, eps)),
        shared_ptr<IntegrationMethod>(new SimpsonMethod(a, b, eps)),
        shared_ptr<IntegrationMethod>(new BullMethod(a, b, eps)),
        shared_ptr<IntegrationMethod>(new ThreeEightsMethod(a, b, eps))
    };

    cout << name << " (a = " << a << ", b = " << b << ", eps = " << eps << ", need integral = " << integral << ")" << endl;

    for (size_t i = 0; i < methods.size(); i++) {
        cout << " - " << methods[i]->GetName() << ": ";

        double result = methods[i]->Integrate(f); // вычисляем интеграл

        if (fabs(result - integral) < eps) {
            cout << "OK" << endl;
        }
        else {
            cout << "Failed (" << result << " != " << integral << ")" << endl;
        }
    }

    cout << endl;
}

int main() {
    MakeTest("Constant test", Constant, 0, 1, 1e-15, 1);
    MakeTest("Constant test", Constant, -5, 12, 1e-15, 17);

    MakeTest("Linear test", Linear, 0, 1, 1e-15, 0.5);
    MakeTest("Linear test", Linear, -2, 3, 1e-15, 2.5);

    MakeTest("Parabola test", Parabola, 0, 1, 1e-10, 1/3.);
    MakeTest("Parabola test", Parabola, -2, 3, 1e-10, 35/3.);
    
    MakeTest("Non linear test", NonLinear, 0, 3, 1e-10, 12*exp(3) - 14.25);
    system("pause");
}