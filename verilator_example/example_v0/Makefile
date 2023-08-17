all: compile

compile:
	verilator --trace --timing -sc --exe --build --top-module top -j hdl/top.v hdl/Add.v sc_main.cpp

run:
	./obj_dir/Vtop

clean:
	-rm -rf obj_dir *.log *.dmp *.vpd core dump.vcd