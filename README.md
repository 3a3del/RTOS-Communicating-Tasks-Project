# RTOS Communicating Tasks Project

## Overview
                                                 
This project is part of the ELC 2080 course and focuses on implementing Real-Time Operating System (RTOS) concepts using `FreeRTOS`. The main objective is to apply knowledge from the embedded programming course and gain hands-on experience with RTOS concepts such as tasks, timers, queues, and semaphores.

## Objectives

- **Tasks**: Implement and manage multiple tasks.
- **Timers**: Use timers to control task execution.
- **Queues**: Implement inter-task communication using queues.
- **Semaphores**: Synchronize tasks using semaphores.

## Project Specifications

The project involves four tasks that communicate via a queue with a fixed size:

- **Sender Tasks**: Three sender tasks (two with the same priority and one with higher priority) send messages containing the current system time in ticks after sleeping for a random period. The tasks handle message blocking and transmission, keeping counters for both.
- **Receiver Task**: One receiver task that sleeps for a fixed period, checks the queue for messages, and processes one message at a time, incrementing a counter for received messages.
- **Timers and Semaphores**: Timers control the sleep/wake cycles of the tasks, with semaphores used to unblock tasks.
  
### The workflow of the project                                                            
![Class Diagram](https://github.com/adouldoula/RTOS-Communicating-Tasks-Project/blob/main/Flowchart%20of%20the%20workflow.png)                                        
  
### Message Sequences                                                            
![Class Diagram](https://github.com/adouldoula/RTOS-Communicating-Tasks-Project/blob/main/Message%20Sequence.png)   

### Reset Function

The receiver task's timer callback calls a reset function after receiving 1000 messages, which performs the following:
1. Prints statistics of sent, blocked, and received messages.
2. Resets counters and clears the queue.
3. Adjusts the sender timer periods to the next values in specified arrays.
4. Destroys timers and stops execution if all array values are used.
5. Fixes the receiver timer period at 100 ms.

## Analysis

- Plot the number of sent messages as a function of the average sender timer period.
- Plot the number of blocked messages as a function of the average sender timer period.
- Compare results for high and low priority sender tasks.
- Repeat experiments with queue sizes of 3 and 10, analyzing the effects of increased queue size.

## Documentation

The documentation should include:
1. **System Design**: Illustrate the program flow and task communication/synchronization.
2. **Results**: Include the requested graphs and their interpretation.
3. **References**: List any references used.

## Important Notes

- You can check out the specifications of the project in details in the `RTOS_Prjct - 2024`                    
- You will gain practical experience in implementing RTOS concepts and handling inter-task communication and synchronization in embedded systems.                                                                                                    
  
  
  
  
  
