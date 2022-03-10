#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int main(int argc, char *argv[])
{
    int count = 0;
    struct pstat ps;
    getpinfo(&ps);
    printf(1, "\n------------ Initially assigned Tickets = %d ----------\n", InitialTickets);
    printf(1, "\nProcessID\tRunnable(0/1)\tTickets\t\tTicks\n");
    for (int i = 0; i < NPROC; i++)
    {
        if (ps.pid[i] && ps.ticket[i] > 0)
        {
            printf(1, "%d\t\t%d\t\t%d\t\t%d\n", ps.pid[i], ps.inuse[i], ps.ticket[i], ps.tick[i]);
            count += ps.tick[i];
        }
    }
    printf(1, "\n------------------- Total Ticks = %d -----------------\n\n", count);
    exit();
}