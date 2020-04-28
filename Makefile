main: scheduler.o FIFO.o SJF.o PSJF.o RR.o control.o
	gcc -O2 scheduler.o FIFO.o SJF.o PSJF.o RR.o control.o -o scheduler
scheduler.o: scheduler.c
	gcc -O2 scheduler.c -c
FIFO.o: FIFO.c FIFO.h
	gcc -O2 FIFO.c -c
SJF.o: SJF.c SJF.h
	gcc -O2 SJF.c -c
SJF.o: PSJF.c PSJF.h
	gcc -O2 PSJF.c -c
RR.o: RR.c RR.h
	gcc -O2 RR.c -c	
control.o: control.c control.h
	gcc -O2 control.c -c
clean:
	rm -rf *o