PROJECT = verificador

SRC			= $(wildcard *.c)

OBJS		= $(patsubst %.c, %.o, $(SRC))

CC			= gcc

LIBS		= -lm
 
C_FLAGS =	-Wall		\
					-O0			\
					-Werror		\
					-std=c11	\
					-Wextra		\
					-Wno-sign-compare	\
					-Wno-unused-parameter	\
					-Wno-unused-variable	\
					-Wshadow

.PHONY: all

all: $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(PROJECT)

%.o: %.c
	$(CC) $(C_FLAGS) -c $(SRC)

clean:
	rm -rf $(OBJS) $(PROJECT)

run: $(PROJECT)
	./$(PROJECT) -d ../dics/Portugues.txt -t ../input/input_ptBR_1.txt -avl

memcheck: $(PROJECT)
	valgrind --tool=memcheck --leak-check=full ./$(PROJECT) -d ../dics/Portugues.txt -t ../input/input_ptBR_1.txt -avl

