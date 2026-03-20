
all: check_rdseed.o

%.o: %.c 
	@g++ -g -std=c++11 $< -lm -o $@ -Wall -O3 

clean: 
	@rm -f *.o massif.out.*
