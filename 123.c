#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#define LOW -(double)INT_MAX
#define HIGH (double)INT_MAX

void rand_d(double *a, int n) {
    for (int i = 0;i < n;i++) {
        double d = (double)rand()/((double)RAND_MAX + 1);
        d = LOW + d * (HIGH - LOW);
        a[i] = d;
    }
}

void shellsort(double *a, int n, int c_cmp, int c_swap) {
    int j;
    for (int s = n / 2;s > 0;s /= 2) {
        for (int i = s; i < n;i++) {
            double tmp = a[i];
            for (j = i;(j >= s) && (fabs(a[j - s]) < fabs(tmp));j -= s) {
                a[j] = a[j - s];
                c_cmp++;
                c_swap++;
            }
            if (j != i)
                c_swap++;
            a[j] = tmp;
        }
    }
}

void heapify(double *a, int n, int i) {
    int lg = i;
    int l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && fabs(a[l]) - fabs(a[lg]) >= 0) {
        lg = l;
    }
    if (r < n && fabs(a[r]) - fabs(a[lg]) >= 0)
        lg = r;
    if (lg != i) {
        double tmp = a[i];
        a[i] = a[lg];
        a[lg] = tmp;
        heapify(a, n, lg);
    }
}

void heapsort(double *a, int n) {
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
    int test_case[4] = {10, 100, 1000, 10000};
    for (int t = 0;t < 4;t++) {
        int n = test_case[t];
        double *a = (double*)malloc(n * sizeof(double)),
               *b = (double*)malloc(n * sizeof(double));
        rand_d(a, n);
        for (int i = 0;i < n;i++) {
            b[i] = a[i];
        }
        int cnt_swap_shell = 0, cnt_swap_heap = 0,
            cnt_cmp_shell = 0, cnt_cmp_heap = 0;
        shellsort(a, n, cnt_cmp_shell, cnt_swap_shell);
        heapsort(b, n);//, cnt_cmp_heap, cnt_swap_heap);
        printf("n = %d\n", n);
        printf("SHELL:\ncompare times: %d, swaps: %d\n", cnt_cmp_shell, cnt_swap_shell);
        printf("HEAP:\ncompare times: %d, swaps: %d\n", cnt_cmp_heap, cnt_swap_heap);

        if (n == 10) {
            for (int i = 0;i < n;i++) {
                printf("%f ", a[i]);
            }
            printf("\n");
            for (int i = 0;i < n;i++) {
                printf("%f ", b[i]);
            }
            printf("\n");
        }

        free(a);
    }
    return 0;
}
