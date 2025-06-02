#include <stdio.h>

#define MAX 10

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a[], int n) {
    int res = a[0];
    for (int i = 1; i < n; i++)
        res = res * a[i] / gcd(res, a[i]);
    return res;
}

int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    int exec[MAX], period[MAX], remain[MAX], next[MAX];
    for (int i = 0; i < n; i++) {
        printf("Enter execution time and period for Task %d: ", i + 1);
        scanf("%d%d", &exec[i], &period[i]);
        remain[i] = 0;
        next[i] = 0;
    }

    int sim_time = lcm(period, n);
    for (int t = 0; t < sim_time; t++) {
        for (int i = 0; i < n; i++) {
            if (t == next[i]) {
                remain[i] = exec[i];
                next[i] += period[i];
            }
        }

        int current = -1;
        for (int i = 0; i < n; i++) {
            if (remain[i] > 0) {
                if (current == -1 || period[i] < period[current])
                    current = i;
            }
        }

        if (current != -1) {
            printf("Time %d: Task %d\n", t, current + 1);
            remain[current]--;
        } else {
            printf("Time %d: Idle\n", t);
        }
    }

    return 0;
}
