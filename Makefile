files = main.cpp person.cpp
shmem: $(files)
		g++ $(files) -o output.out

main: main.cpp
		g++ main.cpp -o output.out

person: person.cpp
		g++ person.cpp -o output.out

test: test.cpp
		g++ test.cpp -o output.out