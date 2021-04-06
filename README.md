# Parallel Programming Solutions
YSU 3rd course problem solutions 
## Table of contents
[1. Shmem Singleton Class](#shmem-singleton-class)\
[2. Test Platform](#test-platform)\
[3. Message Queue](#message-queue)\
[4. Job Manager](#job-manager)

## Shmem Singleton Class
###### Description:
Implementation of cross-process shared singleton class using shared memory.

###### Usage:
```console
foo@bar:~$ make shmem
foo@bar:~$ ./output.out
```

### Test Platform
###### Description:
Simulated Platform of Tests that run inside child processes and collect status information inside parent.

###### Usage:
```console
foo@bar:~$ make test
foo@bar:~$ ./output.out
```

### Message Queue
###### Description:
Class that implements queue of messages, where handlers wait for the messages to get posted and broadcast those messages to other external functions.

###### Usage:
```console
foo@bar:~$ make msgqueue
foo@bar:~$ ./output.out
```

### Job Manager
###### Description:
Job manager that runs in the background implements FIFO for desiding the order and executes the Jobs in a specified order.

###### Usage:
```console
foo@bar:~$ find . -maxdepth 1 -type p -delete
foo@bar:~$ make jobmngr
foo@bar:~$ ./jobScheduler ./consumer
foo@bar:~$ make cleaner
```
