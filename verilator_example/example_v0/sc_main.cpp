// SystemC global header
#include <systemc>

// Include common routines
#include <verilated.h>
#if VM_TRACE
#include <verilated_vcd_sc.h>
#endif

// Include model header, generated from Verilating "top.v"
#include "Vtop.h"

using namespace sc_core;

int sc_main(int argc, char* argv[]) {
    
#if VM_TRACE
    // Before any evaluation, need to know to calculate those signals only used for tracing
    Verilated::traceEverOn(true);
#endif

    // Pass arguments so Verilated code can see them, e.g. $value$plusargs
    // This needs to be called before you create any model
    Verilated::commandArgs(argc, argv);

    // Define clocks
    sc_clock clk("clk", 10, SC_NS);  // 创建周期为 10 的时钟信号对象，名称为 "clk"

    // Define interconnect
    sc_signal<bool> reset_l;
    sc_signal<uint32_t> A;
    sc_signal<uint32_t> B;
    sc_signal<uint32_t> res;

    // Construct the Verilated model, from inside Vtop.h
    // Using unique_ptr is similar to "Vtop* top = new Vtop" then deleting at end
    const std::unique_ptr<Vtop> top{new Vtop{"top"}};

    // Attach Vtop's signals to this upper model
    top->clk_i(clk);
    top->reset_i(reset_l);
    top->A_s(A);
    top->B_s(B);
    top->res_o(res);
    
    // input   clk_i,
    // input   reset_i,
    // input   [7:0] A_s,
    // input   [7:0] B_s,
    // output  reg [7:0] res_o

    // You must do one evaluation before enabling waves, in order to allow
    // SystemC to interconnect everything for testing.
    sc_start(SC_ZERO_TIME);

#if VM_TRACE
    // If verilator was invoked with --trace argument,
    // and if at run time passed the +trace argument, turn on tracing
    VerilatedVcdSc* tfp = nullptr;
    const char* flag = Verilated::commandArgsPlusMatch("trace");
    if (flag && 0 == std::strcmp(flag, "+trace")) {
        std::cout << "Enabling waves into logs/vlt_dump.vcd...\n";
        tfp = new VerilatedVcdSc;
        top->trace(tfp, 99);  // Trace 99 levels of hierarchy
        Verilated::mkdir("logs");
        tfp->open("logs/vlt_dump.vcd");
    }
#endif

    int num = 0;

    // Simulate until $finish
    while (!Verilated::gotFinish()) {
#if VM_TRACE
        // Flush the wave files each cycle so we can immediately see the output
        // Don't do this in "real" programs, do it in an abort() handler instead
        if (tfp) tfp->flush();
#endif

        // Apply inputs
        if (sc_time_stamp() > sc_time(1, SC_NS) && sc_time_stamp() < sc_time(10, SC_NS)) {
            reset_l = 1;  // Assert reset
        } else {
            reset_l = 0;  // Deassert reset
        }
        
        num ++;
        A = num % 100;
        B = num % 100;

        // Simulate 5ns
        sc_start(10, SC_NS);

        if (sc_time_stamp() > sc_time(10, SC_NS)) cout << A << " + " << B << " = " << res << endl;

        if(num > 100) 
        {
            num = 0;
            break;
        }
    }

    // Final model cleanup
    top->final();

    // Close trace if opened
#if VM_TRACE
    if (tfp) {
        tfp->close();
        tfp = nullptr;
    }
#endif

    // Return good completion status
    return 0;
}