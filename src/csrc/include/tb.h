#ifndef TB_H
#define TB_H

#include <stdio.h>
#include "verilated.h"
#include "verilated_vcd_c.h"

// 打印 SELECT_MODULE 的值（调试用）
#pragma message("SELECT_MODULE is set to: " TOSTRING(SELECT_MODULE))

// 动态选择模块
#if defined(SELECT_MODULE_test)
#  include "Vtest.h"
   using Module = Vtest;
#  pragma message("Using Module: Vtest")
#elif defined(SELECT_MODULE_test1)
#  include "Vtest1.h"
   using Module = Vtest1;
#  pragma message("Using Module: Vtest1")
#else
#  error "Invalid SELECT_MODULE value."
#endif

// 仿真逻辑声明（模板方式）
template <typename T>
void simulate_module(T* top);

#endif // TB_H
