main: otehrs scheduler

scheduler:	
	gcc -O2 FIFO.c FIFO.h -o FIFO
	#gcc -O2 RR.c common.c merge_sort.c -o RR
	#gcc -O2 SJF.c common.c merge_sort.c heap.c -o SJF
	#gcc -O2 PSJF.c common.c merge_sort.c heap.c -o PSJF
	gcc -O2 scheduler.c -o scheduler

otehrs:
	gcc -O2 control.c control.h -o control

clean:
	@rm process scheduler FIFO SJF RR PSJF calc