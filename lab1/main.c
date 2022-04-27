#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void comp_sys(int *t_arv, int *t_end, int *t_wait, int *t_down,
              const int a_size_que, int *a_que, int *a_t_insys);

void comp_sys(int *t_arv, int *t_end, int *t_wait, int *t_down,
              const int a_size_que, int *a_que, int *a_t_insys)
{
    int i;
    int t_ex;

    *a_t_insys = 0;

    *t_arv += rand() % 3 + 1;
    while ((a_que[0] < *t_arv) && (a_que[0] != -1))
    {
        for (i = 0; i < a_size_que - 1; i++)
            a_que[i] = a_que[i + 1];

        a_que[a_size_que - 1] = -1;
    }
    t_ex = rand() % 7 + 1;

    if (*t_arv < *t_end)
    {
        if (a_que[a_size_que - 1] == -1)
        {
            *t_wait += *t_end - *t_arv;
            for (i = 0; a_que[i] != -1; i++);
            a_que[i] = *t_end;
            *t_end += t_ex;
        }
    }
    else
    {
        *t_down += *t_arv - *t_end;
        *t_end = *t_arv + t_ex;
    }

    *a_t_insys = *t_end - *t_arv;
}

int main()
{
    const int count_tasks = 1000, count_exp = 100;
    const int size_que = 2;

    int i, k;
    int t1_arv, t1_end, t1_wait, t1_down, que1[size_que];
    int t2_arv, t2_end, t2_wait, t2_down, que2[size_que];
    int t3_arv, t3_end, t3_wait, t3_down, que3[size_que];
    int t_insys, avr_t_insys;
    double avr_t_inque;
    double prb1_t_down, prb2_t_down, prb3_t_down;

    srand(time(NULL));

    for (k = 0; k < count_exp; k++)
    {
        t1_arv = 0; t1_end = 0; t1_wait = 0; t1_down = 0;
        t2_arv = 0; t2_end = 0; t2_wait = 0; t2_down = 0;
        t3_arv = 0; t3_end = 0; t3_wait = 0; t3_down = 0;
        avr_t_insys = 0;

        for (i = 0; i < size_que; i++)
        {
            que1[i] = -1;
            que2[i] = -1;
            que3[i] = -1;
        }

        for (i = 0; i < count_tasks; i++)
        {
            switch (rand() % 10)
            {
                case 0: case 1:
                    comp_sys(&t1_arv, &t1_end, &t1_wait, &t1_down,
                             size_que, que1, &t_insys);
                    break;
                case 2: case 3: case 4:
                    comp_sys(&t2_arv, &t2_end, &t2_wait, &t2_down,
                             size_que, que2, &t_insys);
                    break;
                case 5: case 6: case 7: case 8: case 9:
                    comp_sys(&t3_arv, &t3_end, &t3_wait, &t3_down,
                             size_que, que3, &t_insys);
                    break;
            }

            avr_t_insys += t_insys;
        }

        avr_t_insys /= count_tasks;
        avr_t_inque = (double)(t1_wait + t2_wait + t3_wait) / (double)(3 * count_tasks);
        prb1_t_down = (double)(t1_down) / (double)(t1_end);
        prb2_t_down = (double)(t2_down) / (double)(t2_end);
        prb3_t_down = (double)(t3_down) / (double)(t3_end);

        printf("\n\n#################################################\n\n");
        printf("Average time in system: %d\n", avr_t_insys);
        printf("Average time in queue: %.2f\n\n", avr_t_inque);
        printf("SYS1: Probability of downtime: %.3f\n", prb1_t_down);
        printf("SYS2: Probability of downtime: %.3f\n", prb2_t_down);
        printf("SYS3: Probability of downtime: %.3f\n", prb3_t_down);
        printf("\n#################################################\n\n");
    }


    return 0;
}
