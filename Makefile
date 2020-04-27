main: scheduler.o FIFO.o control.o
	gcc -O2 scheduler.o FIFO.o control.o -o scheduler
scheduler.o: scheduler.c
	gcc -O2 scheduler.c -c
FIFO.o: FIFO.c FIFO.h
	gcc -O2 FIFO.c -c
control.o: control.c control.h
	gcc -O2 control.c -c
clean:
	rm -rf *o