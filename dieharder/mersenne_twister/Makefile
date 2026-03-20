
all: example.o mt.o

%.o: %.cc 
	g++ -std=c++11 $< -lm -o $@ -Wall -O3 

run: mt.o 
	./mt.o $(ITERS) $(RATE) | dieharder -d $(TEST_NUM) -n $(NTUP) -g 200

example: example.o 
	./example.o $(SEED) | dieharder -a -g 200 | tee data/$(TRIAL)_$(SEED).txt

clean: 
	@rm -f *.o
