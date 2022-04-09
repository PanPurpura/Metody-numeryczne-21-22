.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`

NAME = num1

EXEC = $(NAME).x

OBJS = $(NAME).o

FLAGS = -lm

CO = g++
LD = $(CO)

%.o: %.cpp
	$(CO) $(FLAGS) -c $<

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJS)
	$(LD) -o $@ $(FLAGS) $^

run: $(EXEC)
	./$(EXEC)

.PHONY: clean tar
clean:
	rm -f *.o *.~ *.x
	
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR) )