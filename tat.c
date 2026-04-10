#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int id, at, bt, pr, wt, tat, ct, rt;
} Process;

void display(Process p[], int n, char *name)
{
    float sw = 0, st = 0;
    printf("\n%s\nID\tAT\tBT\tWT\tTAT\n", name);
    for (int i = 0; i < n; i++)
    {
        sw += p[i].wt;
        st += p[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }
    printf("AVG WT: %.2f\nAVG TAT: %.2f\n", sw / n, st / n);
}

void reset(Process base[], Process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i] = base[i];
        p[i].rt = p[i].bt;
    }
}

void fcfs(Process base[], int n)
{
    Process p[n];
    reset(base, p, n);
    int t = 0;
    for (int i = 0; i < n; i++)
    {
        if (t < p[i].at)
            t = p[i].at;
        p[i].ct = t + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        t = p[i].ct;
    }
    display(p, n, "FCFS");
}

void rr(Process base[], int n)
{
    Process p[n];
    reset(base, p, n);
    int t = 0, done = 0, q = 4;
    while (done < n)
    {
        int idle = 1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= t && p[i].rt > 0)
            {
                idle = 0;
                int ex = (p[i].rt > q) ? q : p[i].rt;
                t += ex;
                p[i].rt -= ex;
                if (p[i].rt == 0)
                {
                    p[i].ct = t;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    done++;
                }
            }
        }
        if (idle)
            t++;
    }
    display(p, n, "RR");
}

void sjf(Process base[], int n)
{
    Process p[n];
    reset(base, p, n);
    int t = 0, done = 0, f[100] = {0};
    while (done < n)
    {
        int s = -1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= t && !f[i])
            {
                if (s == -1 || p[i].bt < p[s].bt)
                    s = i;
            }
        }
        if (s != -1)
        {
            p[s].ct = t + p[s].bt;
            p[s].tat = p[s].ct - p[s].at;
            p[s].wt = p[s].tat - p[s].bt;
            t = p[s].ct;
            f[s] = 1;
            done++;
        }
        else
            t++;
    }
    display(p, n, "SJF");
}

void srtn(Process base[], int n)
{
    Process p[n];
    reset(base, p, n);
    int t = 0, done = 0;
    while (done < n)
    {
        int s = -1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= t && p[i].rt > 0)
            {
                if (s == -1 || p[i].rt < p[s].rt)
                    s = i;
            }
        }
        if (s != -1)
        {
            p[s].rt--;
            t++;
            if (p[s].rt == 0)
            {
                p[s].ct = t;
                p[s].tat = p[s].ct - p[s].at;
                p[s].wt = p[s].tat - p[s].bt;
                done++;
            }
        }
        else
            t++;
    }
    display(p, n, "SRTN");
}

void priority(Process base[], int n)
{
    Process p[n];
    reset(base, p, n);
    int t = 0, done = 0, f[100] = {0};
    while (done < n)
    {
        int s = -1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= t && !f[i])
            {
                if (s == -1 || p[i].pr < p[s].pr)
                    s = i;
            }
        }
        if (s != -1)
        {
            p[s].ct = t + p[s].bt;
            p[s].tat = p[s].ct - p[s].at;
            p[s].wt = p[s].tat - p[s].bt;
            t = p[s].ct;
            f[s] = 1;
            done++;
        }
        else
            t++;
    }
    display(p, n, "PRIORITY");
}

int main()
{
    int algo, n;
    srand(time(NULL));

    printf("root# CPUSimulator\n");
    printf("Hi! Welcome to CPU Scheduling Simulator. Please give me required parameters.\n");
    printf("Scheduling algorithm - (1) FCFS (2) RR (3) SJF (4) SRTN (5) Priority (6) All\n");
    scanf("%d", &algo);
    printf("No. of Processes in the system : ");
    scanf("%d", &n);

    Process base[n];
    for (int i = 0; i < n; i++)
    {
        base[i].id = i + 1;
        base[i].at = rand() % 20;
        base[i].bt = (rand() % 10) + 1;
        base[i].pr = (rand() % 10) + 1;
    }

    printf("Wait.... Generating Schedules...\nDONE.\n");

    if (algo == 1 || algo == 6)
        fcfs(base, n);
    if (algo == 2 || algo == 6)
        rr(base, n);
    if (algo == 3 || algo == 6)
        sjf(base, n);
    if (algo == 4 || algo == 6)
        srtn(base, n);
    if (algo == 5 || algo == 6)
        priority(base, n);

    return 0;
}