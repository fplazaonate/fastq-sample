EXEC = subsampling_reads

CC = g++
CFLAGS = -Wall -Wextra -O3 -march=native -fopenmp
BOOST_LIBS= -lboost_program_options -fopenmp
LDFLAGS = $(BOOST_LIBS) 

SRC = $(wildcard *.cc)
OBJECTS = $(patsubst %.cc, %.o, $(SRC))

.PHONY : clean

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) *.o
