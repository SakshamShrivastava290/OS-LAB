#include <stdio.h>

int main() {
    int n, m, i, j, k;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int allocation[n][m], max[n][m], need[n][m], available[m];
    int finish[n], ans[n], ind = 0;

    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter the MAX Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter the Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &available[i]);

    // Calculate Need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Initialize finish array
    for (i = 0; i < n; i++)
        finish[i] = 0;

    // Banker's algorithm to find safe sequence
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (!flag) {
                    for (j = 0; j < m; j++)
                        available[j] += allocation[i][j];
                    ans[ind++] = i;
                    finish[i] = 1;
                }
            }
        }
    }

    // Check if all processes could finish
    int safe = 1;
    for (i = 0; i < n; i++) {
        if (!finish[i]) {
            safe = 0;
            printf("The following system is not safe\n");
            break;
        }
    }

    if (safe) {
        printf("Following is the SAFE Sequence\n");
        for (i = 0; i < n - 1; i++)
            printf(" P%d ->", ans[i]);
        printf(" P%d\n", ans[n - 1]);
    }

    return 0;
}
