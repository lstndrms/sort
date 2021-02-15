#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#define LOW -(double)10000//INT_MAX
#define HIGH (double)10000//INT_MAX

void rand_d(double *a, int n) {
    for (int i = 0;i < n;i++) {
        double d = (double)rand()/((double)RAND_MAX + 1);
        d = LOW + d * (HIGH - LOW);
        a[i] = d;
    }
}

void shellsort(double *a, int n) {
    int j;
    for (int s = n / 2;s > 0;s /= 2) {
        for (int i = s; i < n;i++) {
            double tmp = a[i];
            for (j = i;(j >= s) && (fabs(a[j - s]) < fabs(tmp));j -= s) {
                a[j] = a[j - s];
            }
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

    time_t t = time(0);
    srand(t);
    int n;
    scanf("%d", &n);
    double *a = (double*)malloc(n * sizeof(double));
    rand_d(a, n);

    //shellsort(a, n);

    //heapsort(a, n);
    for (int i = 0;i < n;i++) {
        printf("%f ", a[i]);
    }
    free(a);
    return 0;
}
