This project has been created as part of the 42 curriculum by _mkhoubaz_.

# Codexion

## Description

this is a concurrency project that use multithreading and mutexes to solve the dining philosophers problem (coders in this case). The project is implemented in C and demonstrates the use of threads and synchronization mechanisms to manage shared resources among multiple threads with use heap by edf and fifo schedule.

## Instructions

### To compile the project, run the following command in the terminal

* Compile the project:

```bash
make
```

* Run the project:

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug
time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

* Clean the project:

```bash
make fclean
```

## Resources

* POSIX Threads (pthreads): [geeksforgeeks](https://www.geeksforgeeks.org/operating-systems/posix-threads-in-os/) [medium](https://medium.com/@akshatarhabib/understanding-threads-in-c-c9feb5e9372a) [Jacob Sorber](https://youtu.be/uA8X5zNOGw8?si=HZ0lKNXSNWRZ6CoM) [CodeVault](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
* CPU Scheduling: [Core Dump](https://www.youtube.com/watch?v=O2tV9q6784k) [Jacob Sorber](https://www.youtube.com/watch?v=Jkmy2YLUbUY)
* Heap (EDF and FIFO): [Hassan EL BAHI](https://youtu.be/YvVoYF8_xv8?si=oiPEDRaryDt0wO-U)

## Blocking cases handled

The work with threads are so complex and can lead to many blocking cases, so I have handled the following cases:

* Deadlock: I have implemented a solution to prevent deadlock by ensuring that the odds coders pick up the dongles (resources) first then the even coders, This prevents circular wait conditions.
* Coffman conditions: I have ensured that the necessary conditions for deadlock are not met by implementing a resource hierarchy and ensuring that coders acquire resources in a specific order.
* Starvation: I use heap scheduling (EDF and FIFO) to ensure that all coders get a fair chance to access the resources, preventing starvation of any thread.
* Data Races: I have used mutexes to protect shared resources and ensure that only one thread can access a resource at a time, preventing data races.
* Burnout: I create a thread that monitors the time since each coder last compiled and if it exceeds the burnout time, the coder is considered burned out and the simulation ends.

## Thread synchronization mechanisms

I use 'pthread_mutex_t' to create mutexes for each dongle (resource) and for the shared data structures. I also use 'pthread_cond_t' to create condition variables that allow threads to wait for certain conditions to be met before proceeding. each coder thread will lock the mutexes for the dongles it needs to access, and will wait on the condition variable if the dongle is not available. When a coder finishes using a dongle, it will unlock the mutex and signal the condition variable to wake up any waiting threads. monitor thread will also use mutexes and condition variables to safely access shared data structures and check for burnout conditions.

Example of how mutex prevents data races:

```c
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int shared_counter = 0;

void *increment(void *arg) {
    pthread_mutex_lock(&lock);
    shared_counter++;          // critical section
    pthread_mutex_unlock(&lock);
    return NULL;
}
```

Example of how coders threads communication with monitor thread safely using condition variables:

```c
#include <pthread.h>
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int burnout_time = 10; // example burnout time
void *monitor(void *arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        // Check for burnout condition
        if (/* condition to check burnout */) {
            // Signal coders about burnout
            pthread_cond_broadcast(&cond);
        }
        pthread_mutex_unlock(&lock);
        sleep(1); // Monitor periodically
    }
}
```
