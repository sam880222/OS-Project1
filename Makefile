CFLAG = -DDEBUG -std=c99 -Wall 

main: schedule.o
	gcc $(CFLAG) schedule.o -o schedule
scheduler.o: schedule.c
	gcc $(CFLAG) schedule.c -c
clean:
	rm -rf *o