#include <stdio.h>

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], rt[n], wt[n], tat[n], pid[n];
    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("P%d: ", pid[i]);
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // Initialize remaining time
        wt[i] = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int time = 0, done;
    printf("\nGantt Chart:\n|");
    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0) {
                done = 0;
                if (rt[i] > tq) {
                    printf(" P%d |", pid[i]);
                    time += tq;
                    rt[i] -= tq;
                } else {
                    printf(" P%d |", pid[i]);
                    time += rt[i];
                    wt[i] = time - bt[i];  // Waiting time
                    rt[i] = 0;
                }
            }
        }
    } while (!done);

    // Calculate turnaround time
    for (int i = 0; i < n; i++)
        tat[i] = wt[i] + bt[i];

    // Print table
    printf("\n\nProcess\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", pid[i], bt[i], wt[i], tat[i]);
    }

    return 0;
}
