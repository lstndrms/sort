#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#define LOW -(double)(INT_MAX / 2 - 1)
#define HIGH (double)(INT_MAX / 2 - 1)

void rand_d(double *a, int n, int type) {
    for (int i = 0; i < n; i++) {
        if (type == 1) {//сгенерированный массив упорядочен
            a[i] = (double)(n - i);
        }
        else if (type == 2) {//упорядочен в обратном порядке
            a[i] = (double)i;
        }
        else {
            double d = (double)rand()/((double)RAND_MAX + 1);// (0, 1)
            d = LOW + d * (HIGH - LOW);// случайное число между LOW и HIGH
            a[i] = d;
        }
    }
}

void shellsort(double *a, int n, int *c_swp, int *c_cmp) {
    int j;

    //последовательность шагов может быть любой убывающей и заканчивающейся 1
    //n/2, n/4,..., 1 - простейшая, но не самая эффективная
    //последовательности Седжвика или Пратта дают лучшую асимптотику
    for (int s = n / 2; s > 0; s /= 2) {//s - шаг
        //выполним сортировку вставками для подможества элементов на расстоянии s
        for (int i = s; i < n; i++) {
            double tmp = a[i];
            for (j = i; (j >= s) && (fabs(a[j - s]) < fabs(tmp)); j -= s) {
                a[j] = a[j - s];
                (*c_cmp)++;
                (*c_swp)++;
            }
            (*c_cmp)++;
            if (j != i)
                (*c_swp)++;
            a[j] = tmp;
        }
    }
}
//построение кучи из поддерева с корнем в i
void heapify(double *a, int n, int i, int *c_swp, int *c_cmp) {
    int lg = i;
    int l = 2 * i + 1, r = 2 * i + 2;
    //просеивание элемента из корня вниз
    if (l < n && fabs(a[l]) - fabs(a[lg]) <= .0) {
        lg = l;
    }
    if (r < n && fabs(a[r]) - fabs(a[lg]) <= .0)
        lg = r;
    (*c_cmp) += 2;
    //если элемент i "упал" в поддерево построим кучу для поддерева
    if (lg != i) {
        double tmp = a[i];
        a[i] = a[lg];
        a[lg] = tmp;
        (*c_swp)++;
        heapify(a, n, lg, c_swp, c_cmp);
    }
}

void heapsort(double *a, int n, int *c_swp, int *c_cmp) {
    //построение
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(a, n, i, c_swp, c_cmp);
    }
    for (int i = n - 1; i >= 0; i--){
        double tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        (*c_swp)++;
        heapify(a, i, 0, c_swp, c_cmp);
    }
}

int main(void) {
    srand((int)time(NULL));
    //количество тестов
    int test_cases = -1;

    while (test_cases <= 0) {
        printf("Number of tests: ");
        scanf("%d", &test_cases);
        printf("\n");
        if (test_cases <= 0)
            printf("Wrong value: expected positive integer\n");
    }

    for (int t = 0; t < test_cases; t++) {
        //input
        //type - тип сгенерированного массива, вводится
        //type = 1 - упорядочен
        //type = 2 - обратный порядок
        //type = 3 - случайные числа
        //n - длина массива
        int n, type;
        input_begin: ;
        getchar();
        printf("Array length: ");
        scanf("%d", &n);
        while (n <= 0) {
            printf("\nWrong value: expected positive integer\nArray length: ");
            scanf("%d", &n);
        }
        printf("\nArray type(1 - straight, 2 - reverse, 3 - random): ");
        scanf("%d", &type);
        while (type <= 0 || type > 3) {
            printf("\nWrong value: 1, 2, 3 expected\nArray type(1 - straight, 2 - reverse, 3 - random): ");
            scanf("%d", &type);

        }
        //end of input

        double *a = (double*)calloc(n, sizeof(double)),
               *b = (double*)calloc(n, sizeof(double)),
               *inp = (double*)calloc(n, sizeof(double));

        if (!a || !b || !inp) {
            printf("Memory allocation fault\n");
            goto input_begin;
        }
        getchar();
        char flg;
        printf("Print input and result (Y/N): ");
        scanf("%c", &flg);
        while (flg != 'Y' && flg != 'y' && flg != 'n' && flg != 'N') {
            getchar();
            printf("Print input and result (Y/N): ");
            scanf("%c", &flg);
        }
        rand_d(a, n, type);

        if (flg == 'Y' || flg == 'y')
            printf("Input\n");
        for (int i = 0; i < n; i++) {
            inp[i] = a[i];
            b[i] = a[i];
            if (flg == 'Y' || flg == 'y') {
                printf("%f ", a[i]);
            }
        }
        if (flg == 'Y' || flg == 'y')
            printf("\n");




        int cnt_swap_shell = 0, cnt_swap_heap = 0,
            cnt_cmp_shell = 0, cnt_cmp_heap = 0;

        shellsort(a, n, &cnt_swap_shell, &cnt_cmp_shell);
        heapsort(b, n, &cnt_swap_heap, &cnt_cmp_heap);

        //кол-во сравнений и перестановок
        printf("\n------>\nSHELL:\ncompares: %d, swaps: %d\n", cnt_cmp_shell, cnt_swap_shell);
        printf("HEAP:\ncompares: %d, swaps: %d\n------>\n", cnt_cmp_heap, cnt_swap_heap);

        //проверка на корректность
        _Bool correct = 1;
        for (int i = 0; (i < n - 1) && correct; i++) {
            if (fabs(b[i]) - fabs(b[i + 1]) < .0 || fabs(a[i]) - fabs(a[i + 1]) < .0) {
                correct = 0;
            }

        }
        if (flg == 'Y' || flg == 'y') {
            printf("Result:\n");
            for (int i = 0; i < n; i++) {
                printf("%f ", b[i]);
            }
            printf("\n");
        }
        correct = 0;
        if (!correct) {
            printf("An error  occurred\n");
            if (flg != 'Y' && flg != 'y') {
                printf("Debug (Y/N): ");
                getchar();
                scanf("%c", &flg);
                if (flg == 'Y' || flg == 'y') {
                    printf("\nInput: \n");
                    for (int i = 0; i < n; i++) {
                        printf("%f ", inp[i]);
                    }
                    printf("\n\nResult (shell):\n");
                    for (int i = 0; i < n; i++) {
                        printf("%f ", a[i]);
                    }
                    printf("\n");
                    printf("\nResult (heap):\n");
                    for (int i = 0; i < n; i++) {
                        printf("%f ", b[i]);
                    }
                    printf("\n\n\n");
                }
            }
        }


        free(a);
        free(b);
        free(inp);
    }
    return 0;
}
