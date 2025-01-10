//Program to implement Process scheduling algorithms
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct {
    int pid;    // Process ID
    int bt;     // Burst time
    int at;     // Arrival time
    int pr;     // Priority (for Priority scheduling)
    int wt;     // Waiting time
    int tat;    // Turnaround time
    int rt;     // Remaining time (for preemptive algorithms)
} Process;

void calculateAvgTimes(Process p[], int n) {
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }
    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
}

// First Come First Serve (Non-Preemptive)
void fcfs(Process p[], int n) {
    printf("\n=== FCFS (Non-Preemptive) ===\n");
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at)
            currentTime = p[i].at; // Wait if CPU is idle
        p[i].wt = currentTime - p[i].at;
        currentTime += p[i].bt;
        p[i].tat = p[i].wt + p[i].bt;
        printf("Process %d: WT = %d, TAT = %d\n", p[i].pid, p[i].wt, p[i].tat);
    }
    calculateAvgTimes(p, n);
}

// Shortest Job First (Non-Preemptive)
void sjf(Process p[], int n) {
    printf("\n=== SJF (Non-Preemptive) ===\n");
    int completed = 0, currentTime = 0, shortest;
    int isCompleted[n];
    for (int i = 0; i < n; i++) isCompleted[i] = 0;

    while (completed < n) {
        shortest = -1;
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && p[i].at <= currentTime) {
                if (shortest == -1 || p[i].bt < p[shortest].bt)
                    shortest = i;
            }
        }
        if (shortest == -1) {
            currentTime++;
            continue;
        }
        p[shortest].wt = currentTime - p[shortest].at;
        currentTime += p[shortest].bt;
        p[shortest].tat = p[shortest].wt + p[shortest].bt;
        isCompleted[shortest] = 1;
        completed++;
        printf("Process %d: WT = %d, TAT = %d\n", p[shortest].pid, p[shortest].wt, p[shortest].tat);
    }
    calculateAvgTimes(p, n);
}

// Priority Scheduling (Non-Preemptive)
void priorityScheduling(Process p[], int n) {
    printf("\n=== Priority Scheduling (Non-Preemptive) ===\n");
    int completed = 0, currentTime = 0, highestPriority;
    int isCompleted[n];
    for (int i = 0; i < n; i++) isCompleted[i] = 0;

    while (completed < n) {
        highestPriority = -1;
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && p[i].at <= currentTime) {
                if (highestPriority == -1 || p[i].pr < p[highestPriority].pr)
                    highestPriority = i;
            }
        }
        if (highestPriority == -1) {
            currentTime++;
            continue;
        }
        p[highestPriority].wt = currentTime - p[highestPriority].at;
        currentTime += p[highestPriority].bt;
        p[highestPriority].tat = p[highestPriority].wt + p[highestPriority].bt;
        isCompleted[highestPriority] = 1;
        completed++;
        printf("Process %d: WT = %d, TAT = %d\n", p[highestPriority].pid, p[highestPriority].wt, p[highestPriority].tat);
    }
    calculateAvgTimes(p, n);
}

// Round Robin (Preemptive)
void roundRobin(Process p[], int n, int timeQuantum) {
    printf("\n=== Round Robin (Preemptive, Time Quantum = %d) ===\n", timeQuantum);
    int currentTime = 0, completed = 0;
    int remBurstTime[n];
    for (int i = 0; i < n; i++) remBurstTime[i] = p[i].bt;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && remBurstTime[i] > 0) {
                int timeSpent = (remBurstTime[i] > timeQuantum) ? timeQuantum : remBurstTime[i];
                remBurstTime[i] -= timeSpent;
                currentTime += timeSpent;

                if (remBurstTime[i] == 0) {
                    completed++;
                    p[i].tat = currentTime - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    printf("Process %d: WT = %d, TAT = %d\n", p[i].pid, p[i].wt, p[i].tat);
                }
            }
        }
    }
    calculateAvgTimes(p, n);
}

int main() {
    int n, choice, timeQuantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d\n", i + 1);
        p[i].pid = i + 1;
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Priority: ");
        scanf("%d", &p[i].pr);
        p[i].wt = p[i].tat = p[i].rt = 0;
    }

    while (1) {
        printf("\nCPU Scheduling Algorithms\n");
        printf("1. FCFS\n2. SJF\n3. Priority Scheduling\n4. Round Robin\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(p, n);
                break;
            case 2:
                sjf(p, n);
                break;
            case 3:
                priorityScheduling(p, n);
                break;
            case 4:
                printf("Enter Time Quantum: ");
                scanf("%d", &timeQuantum);
                roundRobin(p, n, timeQuantum);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

