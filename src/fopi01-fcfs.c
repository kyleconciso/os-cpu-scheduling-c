#include <stdio.h>
#include <unistd.h>

float ave(float total, int n) {
        return total / n;
}

int main() {
        int n, i, j;
        printf("Enter the number of processes: ");
        scanf("%d", &n);
        
        int bt[n], process[n];
        printf("Enter the burst time for each process:\n");
        for(i = 0; i < n; i++) {
                printf("Process %d: ", i + 1);
                scanf("%d", &bt[i]);
                process[i] = i + 1;
        }
        
        // First process
        int wt[n], tat[n], rt[n];
        wt[0] = 0;
        rt[0] = 0;
        
        // Waiting and Response time
        for(i = 1; i < n; i++) {
                wt[i] = wt[i - 1] + bt[i - 1];
                rt[i] = wt[i];
        }
        
        // Turnaround Time
        float total_wt = 0, total_tat = 0, total_rt = 0;
        for(i = 0; i < n; i++) {
                tat[i] = bt[i] + wt[i];
                total_wt += wt[i];
                total_tat += tat[i];
                total_rt += rt[i];
        }
        
        float avg_wt = ave(total_wt, n);
        float avg_tat = ave(total_tat, n);
        float avg_rt = ave(total_rt, n);
        
        printf("\nFCFS Scheduling:\n");
        printf("Process\t\tBurst Time\tWaiting Time\tTurn Around Time\tResponse Time\n");
        for(i = 0; i < n; i++) {
                printf("P%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", process[i], bt[i], wt[i], tat[i], rt[i]);
        }
        
        printf("\nAverage Waiting Time: %.2f", avg_wt);
        printf("\nAverage Turn Around Time: %.2f", avg_tat);
        printf("\nAverage Response Time: %.2f\n", avg_rt);
        
        // Displaying Gantt Chart
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
