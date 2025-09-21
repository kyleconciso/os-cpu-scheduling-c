#include <stdio.h>
#include <unistd.h>

float ave(float total, int n) {
        return total / n;
}

int main() {
        int n;
        printf("Enter the number of processes: ");
        scanf("%d", &n);

        int bt[n], at[n], process[n];
        for (int i = 0; i < n; i++) {
                printf("BT | AN | PN %d: ", i + 1);
                scanf("%d %d %d", &bt[i], &at[i], &process[i]);
        }

        int wt[n], tat[n], ct[n], rt[n];
        int time = 0, min_index, min_remaining, completed = 0;
        float total_wt = 0, total_tat = 0;

        // Remaining times
        for (int i = 0; i < n; i++) {
                rt[i] = bt[i];
        }

        // SRTF scheduling
        while (completed != n) {
                min_index = -1;
                min_remaining = 9999;

                // SRT process
                for (int i = 0; i < n; i++) {
                        if (at[i] <= time && rt[i] > 0 && rt[i] < min_remaining) {
                                min_remaining = rt[i];
                                min_index = i;
                        }
                }

                if (min_index == -1) {
                        time++;
                        continue;
                }

                rt[min_index]--;
                time++;

                if (rt[min_index] == 0) {
                        completed++;
                        ct[min_index] = time;
                        wt[min_index] = ct[min_index] - bt[min_index] - at[min_index];
                        tat[min_index] = ct[min_index] - at[min_index];
                        total_wt += wt[min_index];
                        total_tat += tat[min_index];
                }
        }

        printf("\nSRTF Scheduling:\n");
        printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurn Around Time\n");
        for (int i = 0; i < n; i++) {
                printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", process[i], at[i], bt[i], wt[i], tat[i]);
        }

        printf("\nAverage Waiting Time: %.2f\n", ave(total_wt,n));
        printf("Average Turn Around Time: %.2f\n", ave(total_tat,n));

        return 0;
}
