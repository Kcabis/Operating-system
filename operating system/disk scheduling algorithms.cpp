//Program to implement Disk scheduling algorithms
#include <stdio.h>
#include <stdlib.h>

void fcfs(int requests[], int n, int head) {
    printf("\n=== FCFS Disk Scheduling ===\n");
    int seek_time = 0;
    printf("Head movement: %d -> ", head);

    for (int i = 0; i < n; i++) {
        seek_time += abs(requests[i] - head);
        printf("%d -> ", requests[i]);
        head = requests[i];
    }
    printf("END\n");
    printf("Total Seek Time: %d\n", seek_time);
}

void sstf(int requests[], int n, int head) {
    printf("\n=== SSTF Disk Scheduling ===\n");
    int seek_time = 0, completed[n];
    for (int i = 0; i < n; i++) completed[i] = 0;

    printf("Head movement: %d -> ", head);

    for (int i = 0; i < n; i++) {
        int shortest = -1, min_distance = 1e9;

        for (int j = 0; j < n; j++) {
            if (!completed[j] && abs(requests[j] - head) < min_distance) {
                shortest = j;
                min_distance = abs(requests[j] - head);
            }
        }

        seek_time += min_distance;
        head = requests[shortest];
        completed[shortest] = 1;
        printf("%d -> ", head);
    }

    printf("END\n");
    printf("Total Seek Time: %d\n", seek_time);
}

void scan(int requests[], int n, int head, int disk_size, int direction) {
    printf("\n=== SCAN Disk Scheduling ===\n");
    int seek_time = 0;
    int sorted[n + 1], count = 0;
    for (int i = 0; i < n; i++) sorted[i] = requests[i];
    sorted[n] = head; 
    n++;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    int head_index;
    for (int i = 0; i < n; i++) {
        if (sorted[i] == head) {
            head_index = i;
            break;
        }
    }

    printf("Head movement: %d -> ", head);

    if (direction == 1) { 
        for (int i = head_index; i < n; i++) {
            seek_time += abs(sorted[i] - head);
            printf("%d -> ", sorted[i]);
            head = sorted[i];
        }
        if (head != disk_size - 1) {
            seek_time += abs(disk_size - 1 - head);
            printf("%d -> ", disk_size - 1);
            head = disk_size - 1;
        }
        for (int i = head_index - 1; i >= 0; i--) {
            seek_time += abs(sorted[i] - head);
            printf("%d -> ", sorted[i]);
            head = sorted[i];
        }
    } else { 
        for (int i = head_index; i >= 0; i--) {
            seek_time += abs(sorted[i] - head);
            printf("%d -> ", sorted[i]);
            head = sorted[i];
        }
        if (head != 0) {
            seek_time += abs(0 - head);
            printf("%d -> ", 0);
            head = 0;
        }
        for (int i = head_index + 1; i < n; i++) {
            seek_time += abs(sorted[i] - head);
            printf("%d -> ", sorted[i]);
            head = sorted[i];
        }
    }
    printf("END\n");
    printf("Total Seek Time: %d\n", seek_time);
}

void cscan(int requests[], int n, int head, int disk_size) {
    printf("\n=== C-SCAN Disk Scheduling ===\n");
    int seek_time = 0;
    int sorted[n + 1], count = 0;
    for (int i = 0; i < n; i++) sorted[i] = requests[i];
    sorted[n] = head; 
    n++;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    int head_index;
    for (int i = 0; i < n; i++) {
        if (sorted[i] == head) {
            head_index = i;
            break;
        }
    }

    printf("Head movement: %d -> ", head);
    for (int i = head_index; i < n; i++) {
        seek_time += abs(sorted[i] - head);
        printf("%d -> ", sorted[i]);
        head = sorted[i];
    }
    if (head != disk_size - 1) {
        seek_time += abs(disk_size - 1 - head);
        printf("%d -> ", disk_size - 1);
        head = disk_size - 1;
    }
    seek_time += disk_size - 1;
    printf("%d -> ", 0);
    head = 0;
    for (int i = 0; i < head_index; i++) {
        seek_time += abs(sorted[i] - head);
        printf("%d -> ", sorted[i]);
        head = sorted[i];
    }

    printf("END\n");
    printf("Total Seek Time: %d\n", seek_time);
}

int main() {
    int n, head, disk_size, choice, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    while (1) {
        printf("\nDisk Scheduling Algorithms\n");
        printf("1. FCFS\n2. SSTF\n3. SCAN\n4. C-SCAN\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(requests, n, head);
                break;
            case 2:
                sstf(requests, n, head);
                break;
            case 3:
                printf("Enter direction (1 for up, 0 for down): ");
                scanf("%d", &direction);
                scan(requests, n, head, disk_size, direction);
                break;
            case 4:
                cscan(requests, n, head, disk_size);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

