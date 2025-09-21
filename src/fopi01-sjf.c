#include <stdio.h>
#include <unistd.h>

float ave(float total, int n) {
        return total / n;
}

int main() {
        int n, i, j, temp;
        printf("Enter the number of processes: ");
        scanf("%d", &n);

        int bt[n], process[n], at[n];
        printf("Enter the burst time[BT] and process number[PN] (use space to separate):\n");
        for(i = 0; i < n; i++) {
                printf("%d . BT / PN: ", i+1);
                scanf("%d %d", &bt[i], &process[i]);
                at[i] = 0;
        }

        // Soring by proc. times
        for(i = 0; i < n - 1; i++) {
                for(j = i + 1; j < n; j++) {
                        if(bt[i] > bt[j]) {
                                temp = bt[i];
                                bt[i] = bt[j];
                                bt[j] = temp;

                                temp = process[i];
                                process[i] = process[j];
                                process[j] = temp;
                        }
                }
        }

        int wt[n], tat[n];
        wt[0] = 0;
        
        float total_wt = 0, total_tat = 0;
        for(i = 1; i < n; i++) {
                wt[i] = wt[i - 1] + bt[i - 1];
                total_wt += wt[i];
        }

        for(i = 0; i < n; i++) {
                tat[i] = bt[i] + wt[i];
                total_tat += tat[i];
        }

        float avg_wt = ave(total_wt, n);
        float avg_tat = ave(total_tat, n);

        printf("\nSJF Scheduling:\n");
        printf("Process\t\tBurst Time\tWaiting Time\tTurn Around Time\n");
        for(i = 0; i < n; i++) {
                printf("P%d\t\t%d\t\t%d\t\t%d\n", process[i], bt[i], wt[i], tat[i]);
        }

        printf("\nAverage Waiting Time: %.2f", avg_wt);
        printf("\nAverage Turn Around Time: %.2f\n", avg_tat);

        printf("\nGANTT CHART:\n");
        for(i = 0; i < n; i++) {
                printf("+-------");
        }
        printf("+\n|");
        for(i = 0; i < n; i++) {
                printf("  P%d   |", process[i]);
        }
        printf("\n");
        for(i = 0; i < n; i++) {
                printf("+-------");
        }
        printf("+\n|");
        for(i = 0; i < n; i++) {
                for(j = 0; j < bt[i]; j++) {
                        printf("   *   |");
                        sleep(0.1);
                }
                printf("   %d  |", bt[i]);
        }
        printf("\n");
        for(i = 0; i < n; i++) {
                printf("+-------");
        }
        printf("+\n");

        return 0;
}