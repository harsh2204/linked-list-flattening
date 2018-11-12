OBJS = list.o test.o
list: $(OBJS)
	$(CC) -o $@ $?
clean:
	rm $(OBJS) list

