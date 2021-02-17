#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#define LOW -(double)INT_MAX
#define HIGH (double)INT_MAX

void rand_d(double *a, int n, int type) {
    for (int i = 0;i < n;i++) {
        if (type == 1) {//сгенерированный массив упорядочен
            a[i] = (double)(n - i);
        }
        else if (type == 2) {//упорядочен в обратном порядке
            a[i] = (double)i;
        }
        else {
            double d = (double)rand()/((double)RAND_MAX + 17);// (0, 1)
            d = LOW + d * (HIGH - LOW);// случайное число между LOW и HIGH
            a[i] = d;
        }
    }
}

void shellsort(double *a, int n) {
    int j;
    //последовательность шагов может быть любой убывающей и заканчивающейся 1
    //n/2, n/4,..., 1 - простейшая, но не самая эффективная
    //последовательности Седжвика или Пратта дают лучшую асимптотику
    for (int s = n / 2;s > 0;s /= 2) {//s - шаг
        //выполним сортировку вставками для подможества элементов на расстоянии s
        for (int i = s; i < n;i++) {
            double tmp = a[i];
            for (j = i;(j >= s) && (fabs(a[j - s]) < fabs(tmp));j -= s) {
                a[j] = a[j - s];
            }
            a[j] = tmp;
        }
    }
}
//построение кучи из поддерева с корнем в i
void heapify(double *a, int n, int i) {
    int lg = i;
    int l = 2 * i + 1, r = 2 * i + 2;
    //просеивание элемента из корня вниз
    if (l < n && fabs(a[l]) - fabs(a[lg])<= 0) {
        lg = l;
    }
    if (r < n && fabs(a[r]) - fabs(a[lg]) <= 0)
        lg = r;
    //если элемент i "упал" в поддерево построим кучу для поддерева
    if (lg != i) {
        double tmp = a[i];
        a[i] = a[lg];
        a[lg] = tmp;
        heapify(a, n, lg);
    }
}

void heapsort(double *a, int n) {
    //построение
    for (int i = n / 2 - 1;i>=0;i--){
        heapify(a, n, i);
    }
    for (int i = n - 1; i > 0;i--){
        double tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        heapify(a, i, 0);
    }
}

signed main(void) {
    srand((int)time(0));
    //количество тестов
    int test_cases;
    printf("Number of tests: ");
    scanf("%d", &test_cases);
    printf("\n");
    for (int t = 0;t < test_cases;t++) {
        //input
        //type - тип сгенерированного массива, вводится
        //type = 1 - упорядочен
        //type = 2 - обратный порядок
        //type > 2 - случайные числа
        //n - длина массива
        int n, type;
        printf("Array length: ");
        scanf("%d", &n);
        printf("\nArray type(1 - straight, 2 - reverse, 3 - random): ");
        scanf("%d", &type);
        printf("\n");
        //end of input

        double *a = (double*)malloc(n * sizeof(double)),
               *b = (double*)malloc(n * sizeof(double));
        rand_d(a, n, type);

        printf("n = %d\n", n);

        for (int i = 0;i < n;i++) {
            b[i] = a[i];
            printf("%f ", a[i]);
        }
        printf("\n");

        int cnt_swap_shell = 0, cnt_swap_heap = 0,
            cnt_cmp_shell = 0, cnt_cmp_heap = 0;

        shellsort(a, n);
        heapsort(b, n);
        //кол-во сравнений и перестановок
        /*
        printf("SHELL:\ncompares: %d, swaps: %d\n", cnt_cmp_shell, cnt_swap_shell);
        printf("HEAP:\ncompares: %d, swaps: %d\n", cnt_cmp_heap, cnt_swap_heap);
        */

        if (n == 10) {
            printf("\nShellsorted:\n");
            for (int i = 0;i < n;i++) {
                printf("%f ", a[i]);
            }
            printf("\nHeapsorted:\n");
            for (int i = 0;i < n;i++) {
                printf("%f ", b[i]);
            }
            printf("\n");
        }

        free(a);
        free(b);
    }
    return 0;
}
