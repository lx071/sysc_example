#include <systemc.h>

SC_MODULE(Counter) {
    sc_in<bool> clock;  // 输入时钟信号
    sc_in<bool> reset; // 输入复位信号
    sc_out<int> count; // 输出计数值

    int counter; // 计数器变量

    void count_process() {
        while (true) {
            if (reset.read()) { // 如果复位信号为高电平
                counter = 0;    // 计数器清零
            } else {
                counter++; // 计数器加1
            }

            count.write(counter); // 将计数器值写入输出端口

            cout << "Counter: " << counter << endl; // 打印计数器值

            wait(); // 等待下一个时钟周期
        }
    }

    SC_CTOR(Counter) {
        SC_THREAD(count_process); // 注册计数进程
        sensitive << clock.pos(); // 对上升沿敏感
    }
};

int sc_main(int argc, char* argv[]) {
    sc_clock clock("clock", 10, SC_NS); // 创建一个时钟信号，周期为10ns
    sc_signal<bool> reset; // 创建一个复位信号
    sc_signal<int> count; // 创建一个计数信号

    Counter counter("counter"); // 实例化计数器模块
    counter.clock(clock); // 连接时钟信号
    counter.reset(reset); // 连接复位信号
    counter.count(count); // 连接计数信号

    reset = true; // 设置复位信号为高电平
    sc_start(5, SC_NS); // 等待一段时间
    reset = false; // 设置复位信号为低电平

    sc_start(50, SC_NS); // 运行仿真，仿真时间为50ns

    return 0;
}