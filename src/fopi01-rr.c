#include <stdio.h>
#include <unistd.h>

float ave(float total, int n) {
        return total / n;
}

int main() {
        int n, time_quantum;
        printf("Enter the number of processes: ");
        scanf("%d", &n);

        int bt[n], at[n], process[n];
        for (int i = 0; i < n; i++) {
                printf("AT | BT %d: ", i + 1);
                scanf("%d %d", &at[i], &bt[i]);
        }

        printf("Enter the time quantum: ");
        scanf("%d", &time_quantum);

        int wt[n], tat[n], rt[n];
        int time = 0, completed = 0;
        float total_wt = 0, total_tat = 0;

        // Remaining times
        for (int i = 0; i < n; i++) {
                rt[i] = bt[i];
        }

        // RR scheduling
        while (completed != n) {
                int done = 1;
                for (int i = 0; i < n; i++) {
                        if (at[i] <= time && rt[i] > 0) {
                                done = 0;
                                if (rt[i] > time_quantum) {
                                        time += time_quantum;
                                        rt[i] -= time_quantum;
                                } else {
                                        time += rt[i];
                                        wt[i] = time - bt[i] - at[i];
                                        tat[i] = time - at[i];
                                        total_wt += wt[i];
                                        total_tat += tat[i];
                                        rt[i] = 0;
                                        completed++;
                                }
                        }
                }
                if (done) {
                        time++;
                }
        }

        printf("\nRR Scheduling:\n");
        printf("Average Turn Around Time: %.2f\n", ave(total_tat, n));
        printf("Average Waiting Time: %.2f\n", ave(total_wt, n));

        return 0;
}
