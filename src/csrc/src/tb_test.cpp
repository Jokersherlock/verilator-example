#include "tb.h"
#include "sim_utils.h"
#include <cstdio>

template <>
void simulate_module<Vtest>(Vtest* top) {
    VerilatedContext* contextp = nullptr;
    VerilatedVcdC* tfp = nullptr;

    // 为模块 test 设置专属波形文件路径
    std::string wave_path = "wave/test.vcd";

    sim_init(top, contextp, tfp, wave_path);

    tet_exec_once(top, contextp, tfp);

    sim_exit(top, contextp, tfp);
}
