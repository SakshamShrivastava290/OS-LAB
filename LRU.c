#include <stdio.h>

void lru(int pages[], int n, int capacity) {
    int frames[capacity], recent[capacity], faults = 0;

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        recent[i] = -1;
    }

    printf("\nLRU Page Replacement\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                recent[j] = i;
                found = 1;
                break;
            }
        }

        if (!found) {
            int lru_index = 0;
            for (int j = 1; j < capacity; j++) {
                if (frames[j] == -1 || recent[j] < recent[lru_index]) {
                    lru_index = j;
                }
            }
            frames[lru_index] = pages[i];
            recent[lru_index] = i;
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

    lru(pages, n, capacity);
    return 0;
}
