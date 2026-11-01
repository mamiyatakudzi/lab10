#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

double fa(double x);
double fb(double x);

double cot_stand(double x);
double cot_n(double x, int N);
double cot_eps(double x, double eps);

float area_triangle(float a);
void info_triangle(void);
void draw_triangle(char sign, int side_a);

int main(void)
{
    setlocale(LC_ALL, "RU_ru.utf8");

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

    printf("Введите x (0 < |x| < pi) для расчета cot(x): ");
    scanf("%lf", &x_cot);
    printf("Введите количество членов ряда N: ");
    scanf("%d", &n_cot);
    printf("Введите точность вычислений eps: ");
    scanf("%lf", &eps_cot);

    double r1 = cot_stand(x_cot);
    double r2 = cot_n(x_cot, n_cot);
    double r3 = cot_eps(x_cot, eps_cot);

    printf("\nСравнение результатов вычислений:\n");
    printf("1) Стандартная библиотека: %10.7lf\n", r1);
    printf("2) Через сумму N членов:   %10.7lf (Отклонение: %10.7e)\n", r2, r2 - r1);
    printf("3) Через точность eps:     %10.7lf (Отклонение: %10.7e)\n", r3, r3 - r1);
    printf("\n");

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
        printf("Введите размер катета 'a': ");
        scanf("%d", &shape_side);
        printf("Площадь прямоугольного равнобедренного треугольника: %.2f\n", area_triangle((float)shape_side));
    }
    else if (menu3 == 2)
    {
        info_triangle();
    }
    else if (menu3 == 3)
    {
        printf("Введите символ для построения фигуры: ");
        while (getchar() != '\n');
        scanf("%c", &shape_sign);

        printf("Введите размер стороны 'a': ");
        scanf("%d", &shape_side);

        printf("\nКонтур фигуры:\n\n");
        draw_triangle(shape_sign, shape_side);
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
        y = x * x * x + 3.0;
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

double cot_n(double x, int N)
{
    double sum = 0.0;
    double coeffs[4] = { 1.0 / 3.0, 1.0 / 45.0, 2.0 / 945.0, 2.0 / 4725.0 };
    int k;

    for (k = 0; k < N; k++)
    {
        if (k < 4)
        {
            sum += coeffs[k] * pow(x, 2 * k + 1);
        }
    }

    return (1.0 / x) - sum;
}

double cot_eps(double x, double eps)
{
    double sum = 0.0;
    double coeffs[4] = { 1.0 / 3.0, 1.0 / 45.0, 2.0 / 945.0, 2.0 / 4725.0 };
    int k = 0;
    double term = coeffs[0] * x;

    while (fabs(term) > eps && k < 4)
    {
        sum += term;
        k++;
        if (k < 4)
        {
            term = coeffs[k] * pow(x, 2 * k + 1);
        }
    }

    return (1.0 / x) - sum;
}

float area_triangle(float a)
{
    return 0.5f * a * a;
}

void info_triangle(void)
{
    printf("Определение: Перевернутый прямоугольный равнобедренный треугольник.\n");
    printf("Имеет один прямой угол (90 градусов) снизу и два равных катета 'a'.\n");
}

void draw_triangle(char sign, int side_a)
{
    int i, j;
    int line_width = side_a * 2 - 1;

    for (j = 0; j < line_width; j++)
    {
        printf("%c", sign);
    }
    printf("\n");

    for (i = 1; i < side_a - 1; i++)
    {
        for (j = 0; j < i; j++)
        {
            printf(" ");
        }

        printf("%c", sign);

        int spaces = (side_a - i - 1) * 2 - 1;
        for (j = 0; j < spaces; j++)
        {
            printf(" ");
        }

        printf("%c\n", sign);
    }

    for (j = 0; j < side_a - 1; j++)
    {
        printf(" ");
    }
    printf("%c\n", sign);
}