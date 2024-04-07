#include <philo.h>

int check_all_ate(t_table *table)
{
    int i;
    int done_eating;

    i = 0;
    done_eating = 0;
    if (table->n_limit_meals == -1)
    {
        return 0;
    }
    while (i<table->n_philos)
    {
        safe_lock_handle(&table->philos[i].philo_lock, LOCK);
        if (table->philos[i].meals_counter >= table->n_limit_meals)
        {
            done_eating++;
        }
        safe_lock_handle(&table->philos[i].philo_lock, UNLOCK);
        i++;  
    }
    if (done_eating == table->n_philos)
    {
        return 1;
    }
    return 0;
}

bool get_bool(t_mtx *mtx, bool *value)
{
    bool res;

    safe_lock_handle(mtx, LOCK);
    res = *value;
    safe_lock_handle(mtx, UNLOCK);  
    return (res);
}

void set_bool(t_mtx *mtx, bool *dest, bool value)
{
    safe_lock_handle(mtx, LOCK);
    *dest = value;
    safe_lock_handle(mtx, UNLOCK);
}


bool simulation_finished(t_table *table)
{
    return(get_bool(&table->table_lock, &table->end_simulation));
}


void *monitor(void *pointer)
{
    t_table *table;
    int i;

    // i = -1;

    table = (t_table *)pointer;
    while (!simulation_finished(table))
    {
        i = -1;
        // while (++i<table->n_philos && !simulation_finished(table))
        // {
        //     // print_action(&table->philos[i], "simul not finished");
        //     // ft_usleep(2000);
        //     // if (check_all_ate(table) == 1)
        //     // {
        //     //     set_bool(&table->table_lock, &table->end_simulation, true);
        //     //     print_action(&table->philos[i], "ALL ATE!");
        //     // }
        // }
        while (++i<table->n_philos)
        {
            // printf("hello!\n");
            print_action(&table->philos[i], "simul not finished");
            ft_usleep(2000);
        }
        
        printf("simulation not finished!\n");
        ft_usleep(2000);
    }
    return (NULL);
}