#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#define PI 3.14159265358979323846
#define MAX_K 12

double fa(double x);
double fb(double x);

double cot_stand(double x);
double get_cot_coeff(int k);
double cot_n(double x, int N);
double cot_eps(double x, double eps);

float area_triangle(float a);
char get_triangle_char(char sign, int side_a, int i, int j);

int main(void)
{
    setlocale(LC_ALL, ".UTF-8");

    printf("--- Задание 1 ---\n\n");

    double x_val;
    int menu1;

    printf("Введите значение x: ");
    scanf("%lf", &x_val);

    printf("Выберите действие:\n");
    printf("1 - Расчет F1(x)\n");
    printf("2 - Расчет F2(x)\n");
    printf("3 - Произведение, разность квадратов и удвоенная сумма функций\n");
    printf("Ваш выбор: ");
    scanf("%d", &menu1);

    if (menu1 == 1)
    {
        printf("fa(x) = %lf\n", fa(x_val));
    }
    else if (menu1 == 2)
    {
        printf("fb(x) = %lf\n", fb(x_val));
    }
    else if (menu1 == 3)
    {
        double res_a = fa(x_val);
        double res_b = fb(x_val);

        printf("fa(x) = %lf, fb(x) = %lf\n", res_a, res_b);
        printf("Произведение: %lf\n", res_a * res_b);
        printf("Разность квадратов: %lf\n", (res_a * res_a) - (res_b * res_b));
        printf("Удвоенная сумма: %lf\n", 2.0 * (res_a + res_b));
    }
    printf("\n");

    printf("--- Задание 2 ---\n\n");

    double x_cot, eps_cot;
    int n_cot;

    do {
        printf("Введите x (0 < |x| < pi) для расчета cot(x): ");
        if (scanf("%lf", &x_cot) != 1 || fabs(x_cot) <= 1e-9 || fabs(x_cot) >= PI) {
            printf("Ошибка ОДЗ! Значение x должно быть в интервале (-pi; pi) и не равно 0.\n");
            while (getchar() != '\n');
        }
        else {
            break;
        }
    } while (1);

    do {
        printf("Введите количество членов ряда N (N > 0): ");
        if (scanf("%d", &n_cot) != 1 || n_cot <= 0) {
            printf("Ошибка! N должно быть положительным числом.\n");
            while (getchar() != '\n');
        }
        else {
            break;
        }
    } while (1);

    do {
        printf("Введите точность вычислений eps (eps > 0): ");
        if (scanf("%lf", &eps_cot) != 1 || eps_cot <= 0) {
            printf("Ошибка! Точность eps должна быть больше 0.\n");
            while (getchar() != '\n');
        }
        else {
            break;
        }
    } while (1);

    double r1 = cot_stand(x_cot);
    double r2 = cot_n(x_cot, n_cot);
    double r3 = cot_eps(x_cot, eps_cot);

    printf("\n=== Сравнение результатов вычислений ===\n");
    printf("1) Стандартная библиотека: %10.7lf\n", r1);
    printf("2) Через сумму N членов:   %10.7lf (Отклонение: %10.7e)\n", r2, fabs(r2 - r1));
    printf("3) Через точность eps:     %10.7lf (Отклонение: %10.7e)\n", r3, fabs(r3 - r1));
    printf("\n");

    printf("--- Таблица отклонений ---\n");
    printf("-----------------------------------------\n");
    printf("| Метод расчета   | Значение   | Погрешность |\n");
    printf("-----------------------------------------\n");
    printf("| Стандартный     | %10.7lf | ----------  |\n", r1);
    printf("| Ряд (N членов)  | %10.7lf | %10.2e  |\n", r2, fabs(r2 - r1));
    printf("| Ряд (Точность)  | %10.7lf | %10.2e  |\n", r3, fabs(r3 - r1));
    printf("-----------------------------------------\n\n");

    printf("--- Задание 3 ---\n\n");

    int menu3;
    char shape_sign;
    int shape_side;

    printf("Выберите операцию для треугольника:\n");
    printf("1) Рассчитать площадь\n");
    printf("2) Вывести определение фигуры\n");
    printf("3) Нарисовать фигуру\n");
    printf("Ваш выбор: ");
    scanf("%d", &menu3);

    if (menu3 == 1)
    {
        do {
            printf("Введите размер катета 'a': ");
            if (scanf("%d", &shape_side) != 1 || shape_side <= 0) {
                printf("Ошибка! Сторона должна быть положительным числом.\n");
                while (getchar() != '\n');
            }
            else {
                break;
            }
        } while (1);

        printf("Площадь прямоугольного равнобедренного треугольника: %.2f\n", area_triangle((float)shape_side));
    }
    else if (menu3 == 2)
    {
        printf("Определение: Перевернутый прямоугольный равнобедренный треугольник.\n");
        printf("Имеет один прямой угол (90 градусов) снизу и два равных катета 'a'.\n");
    }
    else if (menu3 == 3)
    {
        printf("Введите символ для построения фигуры: ");
        while (getchar() != '\n');
        scanf("%c", &shape_sign);

        do {
            printf("Введите размер стороны 'a': ");
            if (scanf("%d", &shape_side) != 1 || shape_side <= 0) {
                printf("Ошибка! Сторона должна быть положительным числом.\n");
                while (getchar() != '\n');
            }
            else {
                break;
            }
        } while (1);

        printf("\nКонтур фигуры:\n\n");

        int line_width = shape_side * 2 - 1;
        for (int i = 0; i < shape_side; i++)
        {
            for (int j = 0; j < line_width; j++)
            {
                printf("%c", get_triangle_char(shape_sign, shape_side, i, j));
            }
            printf("\n");
        }
    }

    system("pause");
    return 0;
}

double fa(double x)
{
    double y;
    if (x <= 3.0)
    {
        y = x * x - 3.0 * x + 9.0;
    }
    else
    {
        y = 1.0 / (x * x * x + 3.0);
    }
    return y;
}

double fb(double x)
{
    double y;
    y = x * exp(sin(x * x));
    return y;
}

double cot_stand(double x)
{
    return 1.0 / tan(x);
}

double get_cot_coeff(int k)
{
    switch (k)
    {
    case 1:  return 1.0 / 3.0;
    case 2:  return 1.0 / 45.0;
    case 3:  return 2.0 / 945.0;
    case 4:  return 1.0 / 4725.0;
    case 5:  return 2.0 / 93555.0;
    case 6:  return 1382.0 / 638512875.0;
    case 7:  return 4.0 / 18243225.0;
    case 8:  return 3617.0 / 162828875985.0;
    case 9:  return 87734.0 / 38979295480125.0;
    case 10: return 349222.0 / 1531329465290625.0;
    case 11: return 310732.0 / 13447856940643125.0;
    case 12: return 472728182.0 / 201919571963756521875.0;
    default: return 0.0;
    }
}

double cot_n(double x, int N)
{
    double sum = 0.0;
    double current_x_pow = x;
    int limit = N;

    if (limit > MAX_K)
    {
        printf("Предупреждение: число членов ряда ограничено лимитом %d.\n", MAX_K);
        limit = MAX_K;
    }

    for (int k = 1; k <= limit; k++)
    {
        sum += current_x_pow * get_cot_coeff(k);
        current_x_pow *= x * x;
    }

    return (1.0 / x) - sum;
}

double cot_eps(double x, double eps)
{
    double sum = 0.0;
    double current_x_pow = x;
    double term = 0.0;
    int k = 1;

    while (1)
    {
        if (k > MAX_K)
        {
            printf("Предупреждение: заданная точность eps не достигнута при остановке по лимиту (%d членов).\n", MAX_K);
            break;
        }

        term = current_x_pow * get_cot_coeff(k);
        if (fabs(term) <= eps)
        {
            break;
        }

        sum += term;
        current_x_pow *= x * x;
        k++;
    }

    return (1.0 / x) - sum;
}

float area_triangle(float a)
{
    return 0.5f * a * a;
}

char get_triangle_char(char sign, int side_a, int i, int j)
{
    char res = ' ';
    int line_width = side_a * 2 - 1;

    if (i == 0 || (i == side_a - 1 && j == side_a - 1) || j == i || j == (line_width - 1 - i))
    {
        res = sign;
    }

    return res;
}
