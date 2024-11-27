# Philosophers

**I never thought philosophy would be so deadly!**

---

## Summary

The **Philosophers** project simulates the classic "Dining Philosophers" problem, focusing on process synchronization and thread management. Through this project, you will learn to create threads, manage shared resources with mutexes, and ensure safe execution without deadlocks.

---

## Features

### Core Functionality

- **Thread-Based Simulation**:
  - Each philosopher is represented by a thread.
  - Synchronization mechanisms ensure safe resource allocation (forks).

- **Dynamic Parameters**:
  - Adjustable number of philosophers and timings:
    - `number_of_philosophers`
    - `time_to_die`
    - `time_to_eat`
    - `time_to_sleep`
    - `[optional] number_of_times_each_philosopher_must_eat`

- **Actions**:
  - Philosophers alternate between:
    - Eating (requires two forks).
    - Sleeping.
    - Thinking.

- **Log Outputs**:
  - Displays events such as:
    - `timestamp_in_ms X has taken a fork`
    - `timestamp_in_ms X is eating`
    - `timestamp_in_ms X is sleeping`
    - `timestamp_in_ms X is thinking`
    - `timestamp_in_ms X died`

---

## Structure

### Directories and Files

#### `philo/` (Mandatory)

- **`philosophers.c`**:
  Handles initialization, thread creation, and simulation lifecycle.
- **`actions.c`**:
  Implements eating, thinking, and sleeping behaviors.
- **`sync.c`**:
  Provides synchronization logic using mutexes.
- **`utils.c`**:
  Contains helper functions for logging, time management, and error handling.

#### `includes/`

- **`philosophers.h`**:
  Declares structures, macros, and function prototypes for consistency.

### Key Files

- **Makefile**:
  Automates compilation with targets:
  - `all`, `clean`, `fclean`, `re`, and `bonus`.

---

## Example Usage

### Compilation

1. **Compile Mandatory Part**:
   ```bash
   make
   ```
   
Run Simulation
Mandatory:

   ```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
   ```
Example:


   ```
./philo 5 800 200 200
   ```

Rules and Constraints
**Global Variables:**
Forbidden to use global variables.

**Thread Safety:**
Mutexes ensure no data races.

**Error Handling:**
Exits cleanly with explicit error messages for invalid inputs or runtime issues.
Learning Outcomes

**Threading Basics:**
Create and manage threads using pthread_create and pthread_join.
Synchronization Mechanisms:
Prevent race conditions with mutexes and semaphores.
Performance Optimization:

Minimize resource contention and ensure smooth execution.
Philosophers – Bringing concurrency and synchronization to life! 🍝





