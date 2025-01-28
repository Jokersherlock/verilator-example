#include "tb.h"

int main(int argc, char* argv[]) {
    Module* top = nullptr;

    // 动态选择模块对应的仿真逻辑
    simulate_module(top);

    return 0;
}
