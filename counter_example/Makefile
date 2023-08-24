all: compile

compile:
	g++ -o counter counter2.cpp -I /usr/local/systemc-2.3.4/include -L /usr/local/systemc-2.3.4/lib-linux64 -l systemc

run:
	./counter

clean:
	rm -rf counter *.vcd

