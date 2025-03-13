Philosophers is a concurrency and synchronization project in the 42 School curriculum that introduces students to multithreading, mutexes, and race conditions using C and POSIX threads (pthread).

Concept:

The project is based on the Dining Philosophers Problem, a classic problem in computer science that illustrates the challenges of deadlocks, starvation, and synchronization in multithreaded systems.
Key Features:

 - Simulates a group of philosophers who alternate between thinking, eating, and sleeping.
 - Philosophers share a limited number of forks, requiring synchronization to prevent deadlocks.
 - Implements mutexes to handle fork usage and avoid race conditions.
 - Manages thread execution and timing constraints to respect the simulation rules.
