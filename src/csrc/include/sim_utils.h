#ifndef SIM_UTILS_H
#define SIM_UTILS_H

#include "verilated.h"
#include "verilated_vcd_c.h"
#include <cstdio>
#include <string>

template <typename T>
void sim_init(T*& top, VerilatedContext*& contextp, VerilatedVcdC*& tfp, const std::string& wave_path) {
    contextp = new VerilatedContext;
    tfp = new VerilatedVcdC;
    top = new T;

    contextp->traceEverOn(true);
    top->trace(tfp, 0);
    tfp->open(wave_path.c_str()); // 动态设置波形文件路径

    top->rstn = 0; top->clk = 0; top->eval(); contextp->timeInc(1); tfp->dump(contextp->time());
    top->rstn = 0; top->clk = 1; top->eval(); contextp->timeInc(1); tfp->dump(contextp->time());
    top->rstn = 1; top->clk = 0; top->eval(); contextp->timeInc(1); tfp->dump(contextp->time());
}

template <typename T>
void tet_exec_once(T* top, VerilatedContext* contextp, VerilatedVcdC* tfp) {
    top->clk ^= 1; top->eval(); contextp->timeInc(1); tfp->dump(contextp->time());
    top->clk ^= 1; top->eval(); contextp->timeInc(1); tfp->dump(contextp->time());
}

template <typename T>
void sim_exit(T* top, VerilatedContext* contextp, VerilatedVcdC* tfp) {
    contextp->timeInc(1);
    tfp->dump(contextp->time());
    tfp->close();

    printf("The wave data has been saved to wave/dump.vcd\n");

    delete top;
    delete tfp;
    delete contextp;
}

#endif // SIM_UTILS_H
