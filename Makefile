#1. Shmem Singleton Class
shmem:
		g++ ./SingletonClass/main.cpp ./SingletonClass/person.cpp -o output.out

main: ./SingletonClass/main.cpp
		g++ ./SingletonClass/main.cpp -o output.out

person: ./SingletonClass/person.cpp
		g++ ./SingletonClass/person.cpp -o output.out

#2. Test Platform
test: 
		g++ ./TestPlatform/test.cpp -o output.out

#3. Message Queue
msgqueue: 
		g++ ./MessageQueue/main.cpp ./MessageQueue/MessageQueue.cpp -pthread -o output.out

#4. Job Manager
jobmngr: cleaner jobScheduler job consumer
#	create symbolic links to jobs
	ln -s job 1
	ln -s job 2
	ln -s job 3
	ln -s job 4

jobScheduler: 
	g++ ./JobManager/jobScheduler.cpp -o jobScheduler

job: 
	g++ ./JobManager/job.cpp -o job

consumer: 
	g++ ./JobManager/consumer.cpp -o consumer

cleaner:
	rm -f job consumer jobScheduler
#	delete symlinks
	rm -f 1 2 3 4
#	delete all pipe type files in the current directory
	find . -maxdepth 1 -type p -delete