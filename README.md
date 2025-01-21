# Philosophers


The Philosophers project is a concurrency challenge that simulates a group of philosophers seated at a round table. Each philosopher alternates between eating, thinking, and sleeping. The goal is to ensure that no philosopher starves while managing resource contention using threading and synchronization techniques. This project introduces fundamental concepts such as threads, mutexes, and process synchronization in C.

## Features:

Simulation of philosophers eating, sleeping, and thinking.
Prevention of deadlock and starvation using mutexes or semaphores.
Real-time logging of actions with timestamps for each philosopher.
Support for both thread-based (mandatory) and process-based (bonus) implementations.
To run the project, clone the repository, navigate to the project directory, and compile it using the provided Makefile:

```
git clone https://github.com/echiu99/philosophers.git
cd philosophers
make  
```
## Usage:

The program simulates the behavior of philosophers and forks based on the provided command-line arguments. Run the executable as follows:

./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]  

- number_of_philosophers: Total number of philosophers and forks.
- time_to_die: Maximum time (in milliseconds) a philosopher can go without eating before starving.
- time_to_eat: Time (in milliseconds) a philosopher spends eating.
- time_to_sleep: Time (in milliseconds) a philosopher spends sleeping.
- number_of_times_each_philosopher_must_eat (optional): If provided, the simulation ends when each philosopher has eaten the specified number of times.

### Example:
./philo 5 800 200 200  

This runs a simulation with 5 philosophers where each must eat every 800 ms, and eating and sleeping both take 200 ms.

## Logs:
Philosopher state changes are logged in real time. Each message includes a timestamp and the philosopher's ID. Example log entries:

200 1 has taken a fork  
201 1 is eating  

Possible states include:

- <timestamp> X has taken a fork
- <timestamp> X is eating
- <timestamp> X is sleeping
- <timestamp> X is thinking
- <timestamp> X died

The program ensures no data races occur, and state messages are displayed in the correct order.

## Mandatory Implementation:

The mandatory part (philo) uses threads and mutexes. Each philosopher is represented by a thread, and forks are shared resources protected by mutexes. The simulation stops when a philosopher dies or when all philosophers have eaten the required number of times.

## Acknowledgments:

This project is part of the 42 curriculum and is designed to teach the fundamentals of threading, synchronization, and process management. Special thanks to the 42 network for the learning opportunity.
