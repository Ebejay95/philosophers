# philosophers

A project to solve the classic "Dining Philosophers" problem using threads and synchronization mechanisms in C.

This project implements the "Dining Philosophers" problem, focusing on coordinating between competing threads. The goal is to avoid deadlocks and ensure philosophers can safely eat and think by properly synchronizing the forks (resources).

## Structure

### src/

The `src` directory contains all source code and the implementation of the philosophers simulation:

- philosophers.c: The main file that starts philosopher threads, manages their life cycles, and initiates the simulation.
- actions.c: Defines the actions of the philosophers, such as `eating`, `thinking`, and `waiting`, as well as the management of forks.
- utils.c: Contains helper functions for timing, status updates, and console output.
- sync.c: Provides synchronization mechanisms to prevent deadlocks and ensure philosophers act without resource collisions.

### include/

The `include` directory contains the header files:

- philosophers.h: Declares structures, global variables, and function prototypes to maintain consistency across source files.

### Makefile

The Makefile automates the build process. It compiles all source files and creates the final executable.

## Features

- Synchronization and Threading: Uses threads for each philosopher and mutexes for the forks to avoid conflicts.
- Deadlock Prevention: Implements strategies to avoid deadlocks and race conditions.
- Flexible Parameters: Allows customization of the number of philosophers and time parameters for thinking and eating.

## Usage

To compile the project, run:

    make

Start the simulation with:

    ./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_think] [optional: number_of_meals]

### Example

    ./philosophers 5 800 200 200

This command starts a simulation with 5 philosophers and specific time values for death, eating, and thinking.
