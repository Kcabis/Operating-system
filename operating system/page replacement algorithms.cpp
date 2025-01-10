//Program to implement Page replacement algorithms
#include <stdio.h>
#include <stdlib.h>
void fifo(int pages[], int n, int capacity) {
    printf("\n=== FIFO Page Replacement ===\n");
    int frame[capacity];
    for (int i = 0; i < capacity; i++) frame[i] = -1;

    int faults = 0, index = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frame[index] = pages[i];
            index = (index + 1) % capacity;
            faults++;
        }

        printf("Page: %d -> Frames: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("X ");
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", faults);
}

void opr(int pages[], int n, int capacity) {
    printf("\n=== Optimal Page Replacement ===\n");
    int frame[capacity];
    for (int i = 0; i < capacity; i++) frame[i] = -1;

    int faults = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (i < capacity) {
                frame[i] = pages[i];
            } else {
                int farthest = -1, index = -1;

                for (int j = 0; j < capacity; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frame[j] == pages[k])
                            break;
                    }
                    if (k == n || k > farthest) {
                        farthest = k;
                        index = j;
                    }
                }

                frame[index] = pages[i];
            }
            faults++;
        }

        printf("Page: %d -> Frames: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("X ");
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", faults);
}

void lru(int pages[], int n, int capacity) {
    printf("\n=== LRU Page Replacement ===\n");
    int frame[capacity], use_time[capacity];
    for (int i = 0; i < capacity; i++) frame[i] = use_time[i] = -1;

    int faults = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                use_time[j] = i;
                break;
            }
        }

        if (!found) {
            int lru = 0;
            for (int j = 1; j < capacity; j++) {
                if (use_time[j] < use_time[lru]) lru = j;
            }
            frame[lru] = pages[i];
            use_time[lru] = i;
            faults++;
        }

        printf("Page: %d -> Frames: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("X ");
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", faults);
}

void mru(int pages[], int n, int capacity) {
    printf("\n=== MRU Page Replacement ===\n");
    int frame[capacity], use_time[capacity];
    for (int i = 0; i < capacity; i++) frame[i] = use_time[i] = -1;

    int faults = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                use_time[j] = i;
                break;
            }
        }

        if (!found) {
            int mru = 0;
            for (int j = 1; j < capacity; j++) {
                if (use_time[j] > use_time[mru]) mru = j;
            }
            frame[mru] = pages[i];
            use_time[mru] = i;
            faults++;
        }

        printf("Page: %d -> Frames: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("X ");
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", faults);
}

int main() {
    int n, capacity, choice;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the pages: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    while (1) {
        printf("\nPage Replacement Algorithms\n");
        printf("1. FIFO\n2. OPR (Optimal)\n3. LRU\n4. MRU\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                fifo(pages, n, capacity);
                break;
            case 2:
                opr(pages, n, capacity);
                break;
            case 3:
                lru(pages, n, capacity);
                break;
            case 4:
                mru(pages, n, capacity);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

