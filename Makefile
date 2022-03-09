all:add.c add_f.c
	gcc add.c add_f.c -o add

clean:
	rm add
