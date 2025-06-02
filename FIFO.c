#include <stdio.h>

void fifo(int pages[], int n, int capacity) {
    int frames[capacity], index = 0, faults = 0;
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    printf("\nFIFO Page Replacement\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % capacity;
            faults++;
        }

        printf("Page %d → Frames: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == -1) printf(" - ");
            else printf(" %d ", frames[j]);
        }
        printf("\n");
    }
    printf("Total Page Faults: %d\n", faults);
}

int main() {
    int n, capacity;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    fifo(pages, n, capacity);
    return 0;
}
