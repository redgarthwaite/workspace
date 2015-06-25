COMPILER=g++
FLAGS= -w -Wall -Werror -pedantic -ansi

all: client.cpp server.cpp
	$(COMPILER) $(FLAGS) -o client client.cpp
	$(COMPILER) $(FLAGS) -o server server.cpp
	$(COMPILER) $(FLAGS) -o threads threads.cpp -lpthread
	$(COMPILER) $(FLAGS) -o mutex mutex.cpp -lpthread
	$(COMPILER) $(FLAGS) -o server2 server2.cpp -lpthread
	$(COMPILER) $(FLAGS) -o client2 client2.cpp

	@echo "NOTE:"
	@echo "  Use 'client' with 'server'"
	@echo "  Use 'client2' with 'server2'"
	@echo "  Programs 'threads' and 'mutex' are standalone"
	@echo

clean:
	rm -rf *~ client server threads mutex server2 client2

