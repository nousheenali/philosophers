# Philosophers
This project helps understand process synchronisation and resource sharing.

The Dining Philosopher Problem states that N philosophers seated around a circular table with one fork between each pair of philosophers. A philosopher may eat if he can pick up the two forks adjacent to him. The philosophers alternatively eat, think, or sleep. When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.

![Unknown](https://user-images.githubusercontent.com/66158938/200158848-f1ae3e0b-f647-48a6-8a7d-2ded08f9211b.jpeg)

image reference: wikipedia


The program should take the following arguments:

- number_of_philosophers
- time_to_die 
- time_to_eat 
- time_to_sleep 
- [number_of_times_each_philosopher_must_eat] (optional)

## Mandatory part

Implementing dining philosophers problem with philosophers as threads.
Use mutex locks for process synchronization and resource sharing.

To run the program:

./philo/philo 4 410 200 200 5

## Bonus part

Implementing dining philosophers problem with philosophers as processes.
Use semaphores for process synchronization and resource sharing.

To run the program:

./philo_bonus/philo_bonus 4 410 200 200 5
