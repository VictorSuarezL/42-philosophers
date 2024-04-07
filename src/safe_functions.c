#include <philo.h>

void safe_lock_handle(t_mtx *mutex, t_code code)
{
    if (code == LOCK)
        pthread_mutex_lock(mutex);
    else if (code == UNLOCK)
        pthread_mutex_unlock(mutex);
    else if (code == INIT)
        pthread_mutex_init(mutex, NULL);
    else if (code == DESTROY)
        pthread_mutex_destroy(mutex);
    else
        ft_error("Wrong code for lock!");
}