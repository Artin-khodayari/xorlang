exec = xorlang
sources = $(wildcard src/*.c)
object = $(sources:.c=.o)
flags = -g


$(exec): $(object)
	gcc $(object) $(flags) -lcurl -lm -o $(exec)

%.o: %.c
	gcc -c $(flags) $< -o $@

clean:
	rm -f $(object) $(exec) src/*.o *.c *.out
