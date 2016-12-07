gcc:
	gcc BMS.c -o bms

test: test1 test2

test1:	
	./bms BMSData1.txt
	vim BMSOut.txt
test2:
	./bms BMSData2.txt
	vim BMSOut.txt
