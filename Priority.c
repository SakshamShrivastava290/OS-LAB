#include <stdio.h>

int main() {
    int n, bt[10], priority[10], pid[10], wt[10], tat[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter burst time and priority for process %d: ", pid[i]);
        scanf("%d %d", &bt[i], &priority[i]);
    }

    // Sort processes by priority (lower number = higher priority)
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (priority[j] < priority[i]) {
                // Swap burst time
                int temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                // Swap priority
                temp = priority[i]; priority[i] = priority[j]; priority[j] = temp;
                // Swap pid
                temp = pid[i]; pid[i] = pid[j]; pid[j] = temp;
            }

    wt[0] = 0;
    tat[0] = bt[0];

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = wt[i] + bt[i];
    }

    printf("\nPID\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t\t%d\t%d\n", pid[i], bt[i], priority[i], wt[i], tat[i]);

    return 0;
}
