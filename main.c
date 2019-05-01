#include <stdio.h>
#include <quadmath.h>
#include <string.h>
#include <stdlib.h>

typedef __float128 long_double_q_t;

long_double_q_t function_x (long_double_q_t x) {
    long_double_q_t answ = powq(x, 2.0Q) - 4.0Q * x - 3.0Q;
    return answ;
}

long_double_q_t fibonacci_count(int number) {
    long_double_q_t tau = (sqrtq(5.0Q) - 1.0Q) / 2.0Q;
    long_double_q_t answ = (powq((1.0Q / tau), number + 1) - powq((-tau), number + 1)) / sqrtq(5.0Q);
    return answ;
}

void print_a_b(long_double_q_t* a, long_double_q_t* b, const int* accuracy_case_operator) {
    char answa[128];
    char answb[128];
    switch (*accuracy_case_operator) {
        case 1:
            quadmath_snprintf(answa, sizeof(answa), "%.5Qf", *a);
            quadmath_snprintf(answb, sizeof(answb), "%.5Qf", *b);
            break;
        case 2:
            quadmath_snprintf(answa, sizeof(answa), "%.8Qf", *a);
            quadmath_snprintf(answb, sizeof(answb), "%.8Qf", *b);
            break;
        case 3:
            quadmath_snprintf(answa, sizeof(answa), "%.14Qf", *a);
            quadmath_snprintf(answb, sizeof(answb), "%.14Qf", *b);
            break;
    }
    printf("a: %s\nb: %s\n", answa, answb);
}

void print_answer (long_double_q_t* x, long_double_q_t* y, const int* accuracy_case_operator) {
    char answx[128];
    char answy[128];
    switch (*accuracy_case_operator) {
        case 1:
            quadmath_snprintf(answx, sizeof(answx), "%.5Qf", *x);
            quadmath_snprintf(answy, sizeof(answy), "%.5Qf", *y);
            break;
        case 2:
            quadmath_snprintf(answx, sizeof(answx), "%.8Qf", *x);
            quadmath_snprintf(answy, sizeof(answy), "%.8Qf", *y);
            break;
        case 3:
            quadmath_snprintf(answx, sizeof(answx), "%.14Qf", *x);
            quadmath_snprintf(answy, sizeof(answy), "%.14Qf", *y);
            break;
    }
    printf("X: %s\nY: %s\n", answx, answy);
}

void print_accuracy (long_double_q_t* accuracy, const int* accuracy_case_operator) {
    char answ[64];
    switch (*accuracy_case_operator) {
        case 1:
            quadmath_snprintf(answ, sizeof(answ), "%.3Qf", *accuracy);
            break;
        case 2:
            quadmath_snprintf(answ, sizeof(answ), "%.6Qf", *accuracy);
            break;
        case 3:
            quadmath_snprintf(answ, sizeof(answ), "%.12Qf", *accuracy);
            break;
    }
    printf("Accuracy: %s\n", answ);
}


int main() {
    char flag = 0;
    int inp = 0;
    long_double_q_t accuracy = 0.0Q;
    while (!flag) {
        printf("Select the accuracy of searching of minimum: (use numbers)\n");
        printf("1: 10^-3\n2: 10^-6\n3: 10^-12\n");
        scanf("%d", &inp);
        switch (inp) {
            case 1:
                accuracy = 0.001Q;
                flag = 1;
                break;
            case 2:
                accuracy = 0.000001Q;
                flag = 1;
                break;
            case 3:
                accuracy = 0.000000000001Q;
                flag = 1;
                break;
            default:
                printf("Incorrect input! Try again\n");
                flag = 0;
                break;
        }
    }
    print_accuracy(&accuracy, &inp);
    long_double_q_t tau = (sqrtq(5.0Q) - 1.0Q) / 2.0Q;
    long_double_q_t a = 0, b = 2 * M_PIq;
    long_double_q_t length = b - a;
    int i = 0;
    while (length > accuracy) {
        i++;
        long_double_q_t x_1 = b - tau * length;
        long_double_q_t x_2 = a + tau * length;
        if (function_x(x_1) < function_x(x_2)) {
            b = x_2;
        }
        else {
            a = x_1;
        }
        length = b - a;
        long_double_q_t xMin = (a + b) / 2;
        long_double_q_t yMin = function_x(xMin);
        printf("Iteration #%d\n", i);
        print_answer(&xMin, &yMin, &inp);
        print_a_b(&a, &b, &inp);
        printf("--------------------------------------------------\n");
    }
    long_double_q_t xMin = (a + b) / 2;
    long_double_q_t yMin = function_x(xMin);
    print_answer(&xMin, &yMin, &inp);
    return 0;
}