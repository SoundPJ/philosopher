#include "philo.h"

int philo_take_fork(t_philo *philo)
{
    printf("%ld #%d has taken a fork.\n", get_timestamp(philo->data), philo->name);
    return (1);
}

void philo_put_fork(t_philo *philo)
{
    printf("%ld #%d is putting a fork.\n", get_timestamp(philo->data), philo->name);
}

void philo_eat(t_philo *philo)
{
    printf("%ld #%d is eating.\n", get_timestamp(philo->data), philo->name);
    sleep_ms(philo->data->teat);
    philo_put_fork(philo);
    philo->nate++;
    if (philo->nate >= philo->data->neat)
        philo->data->stop = 1;        
}

void philo_sleep(t_philo *philo)
{
    printf("%ld #%d is sleeping.\n", get_timestamp(philo->data), philo->name);
    sleep_ms(philo->data->tsleep);
}

void philo_think(t_philo *philo)
{
    printf("%ld #%d is thinking.\n", get_timestamp(philo->data), philo->name);
}
