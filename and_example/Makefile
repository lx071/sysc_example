all: compile

compile:
	g++ -o and tb.cpp and.cpp -I /usr/local/systemc-2.3.4/include -L /usr/local/systemc-2.3.4/lib-linux64 -l systemc

run:
	./and

clean:
	rm -rf and *.vcd

