MODULES = chip8 decoder display inputs sound main
OBJS := $(MODULES:%=bin/%.o)

bin/main : $(OBJS)
	gcc $(OBJS) -o bin/main

$(OBJS) : bin/%.o: src/%/%.c
	gcc -c $< -o $@