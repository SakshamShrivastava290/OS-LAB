#include<stdio.h>
#define MAX 10
void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX];
    for (int i = 0; i < processes; i++) allocation[i] = -1;

    for (int i = 0; i < processes; i++) {
        int best = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (best == -1 || blockSize[j] < blockSize[best]) best = j;
            }
        }
        if (best != -1) {
            allocation[i] = best;
            blockSize[best] -= processSize[i];
        }
    }

    printf("\nBest-Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        if (allocation[i] != -1)
            printf("Process %d of size %d -> Block %d\n", i + 1, processSize[i], allocation[i] + 1);
        else
            printf("Process %d of size %d -> Not Allocated\n", i + 1, processSize[i]);
    }
}

int main() {
    int blockSize[MAX], processSize[MAX], blocks, processes;

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);
    printf("Enter size of each block:\n");
    for (int i = 0; i < blocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter size of each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    bestFit(blockSize, blocks, processSize, processes);
    return 0;
}