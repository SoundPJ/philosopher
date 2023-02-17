#include "philo.h"

int philo_take_fork(t_philo *philo)
{
    pthread_mutex_lock(&(philo->fork));
    pthread_mutex_lock(&(philo->next->fork));
    pthread_mutex_lock(&(philo->data->printq));
    printf("%ld #%d has taken a fork.\n", get_timestamp(philo->data), philo->name);
    pthread_mutex_unlock(&(philo->data->printq));
    return (1);
}

void philo_put_fork(t_philo *philo)
{
    pthread_mutex_unlock(&(philo->fork));
    pthread_mutex_unlock(&(philo->next->fork));
    pthread_mutex_lock(&(philo->data->printq));
    printf("%ld #%d is putting a fork.\n", get_timestamp(philo->data), philo->name);
    pthread_mutex_unlock(&(philo->data->printq));    
}

void philo_eat(t_philo *philo)
{
    philo->tseat = get_timestamp(philo->data);

    pthread_mutex_lock(&(philo->data->printq));    
    // printf("%ld #%d is eating.\n", get_timestamp(philo->data), philo->name);
    printf("%ld #%d is eating.\n", philo->tseat, philo->name);
    pthread_mutex_unlock(&(philo->data->printq));
    long diff = get_timestamp(philo->data) - philo->tseat; 
    while (diff < philo->data->teat)
    {
        diff = get_timestamp(philo->data) - philo->tseat;
        printf("diff = %ld\n", diff);
        sleep_ms(100);
    }
    philo_put_fork(philo);
    philo->nate++;
    if (philo->nate >= philo->data->neat)
        philo->data->stop = 1;        
}

void philo_sleep(t_philo *philo)
{
    // philo->tssleep = get_timestamp
    pthread_mutex_lock(&(philo->data->printq));
    printf("%ld #%d is sleeping.\n", get_timestamp(philo->data), philo->name);
    pthread_mutex_unlock(&(philo->data->printq));
    sleep_ms(philo->data->tsleep);
}

void philo_think(t_philo *philo)
{
    pthread_mutex_lock(&(philo->data->printq));
    printf("%ld #%d is thinking.\n", get_timestamp(philo->data), philo->name);
    pthread_mutex_unlock(&(philo->data->printq));
}
