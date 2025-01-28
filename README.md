# Verilator仿真框架
## 文件存放
- 存放Verilog源文件的文件夹：`src/rtl`
- 存放c的文件夹：`src/csrc/src`
- 存放头文件的文件夹：`src/csrc/include`

## 命名规则
- 仿真文件名：`tb_<module_name>.cpp`

## 使用
添加新的需要仿真的模块需要修改tb.h，添加模块
- 编译：`make SELECT_MODULE=<module_name>`
- 运行：`make run SELECT_MODULE=<module_name>`
- 清理：`make clean`

