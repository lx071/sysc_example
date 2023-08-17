#include <systemc.h>
#include "and.h"

int sc_main(int argc, char* argv[]) {
    sc_signal<sc_uint<1>> a, b, f; // 信号线声明
    sc_clock clk("clock", 10, SC_NS); // 10ns周期的时钟信号
    
    // 模块实例化
    and2 and_gate("and_gate");
    and_gate.a(a);
    and_gate.b(b);
    and_gate.f(f);
    and_gate.clk(clk);

    // 波形跟踪设置
    sc_trace_file* trace_file = sc_create_vcd_trace_file("waveform");
    sc_trace(trace_file, a, "a");
    sc_trace(trace_file, b, "b");
    sc_trace(trace_file, f, "f");
    sc_trace(trace_file, clk, "clk");


    // 仿真开始
    a = 0; // 设置输入端口 a 的值为 0
    b = 0; // 设置输入端口 b 的值为 0

    sc_start(10, SC_NS); // 仿真运行 10ns
    a = 1; // 设置输入端口 a 的值为 1

    sc_start(10, SC_NS); // 仿真运行 10ns
    b = 1; // 设置输入端口 b 的值为 1

    sc_start(20, SC_NS); // 仿真运行 20ns

    // 仿真结束
    sc_close_vcd_trace_file(trace_file);

    return 0;
}