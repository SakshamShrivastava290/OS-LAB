#include <stdio.h>
#include <limits.h>

void optimal(int pages[], int n, int capacity) {
    int frames[capacity], faults = 0;

    for (int i = 0; i < capacity; i++) frames[i] = -1;

    printf("\nOptimal Page Replacement\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int opt_index = -1, farthest = i;
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1) {
                    opt_index = j;
                    break;
                }
                int k;
                for (k = i + 1; k < n; k++) {
                    if (pages[k] == frames[j]) break;
                }
                if (k > farthest) {
                    farthest = k;
                    opt_index = j;
                }
            }
            frames[opt_index] = pages[i];
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

    optimal(pages, n, capacity);
    return 0;
}
