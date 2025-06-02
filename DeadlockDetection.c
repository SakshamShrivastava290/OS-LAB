#include <stdio.h>

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[n][m], request[n][m], available[m];
    int finish[n], i, j;

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Request Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &available[i]);

    for (i = 0; i < n; i++)
        finish[i] = 0;

    int changed = 1;
    while (changed) {
        changed = 0;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                int can_allocate = 1;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > available[j]) {
                        can_allocate = 0;
                        break;
                    }
                }
                if (can_allocate) {
                    for (j = 0; j < m; j++)
                        available[j] += allocation[i][j];
                    finish[i] = 1;
                    changed = 1;
                }
            }
        }
    }

    int deadlocked = 0;
    for (i = 0; i < n; i++) {
        if (!finish[i]) {
            printf("Process P%d is in Deadlock\n", i);
            deadlocked = 1;
        }
    }

    if (!deadlocked)
        printf("No Deadlock Detected. System is Safe.\n");

    return 0;
}
