# 顶层模块名称
SELECT_MODULE ?= test

# 自动根据模块名称设置宏定义
CFLAGS_MODULE = -DSELECT_MODULE_$(shell echo $(SELECT_MODULE) | tr 'a-z' 'A-Z')

# 项目路径
PROJECT_ROOT = $(CURDIR)
RTL_DIR = $(PROJECT_ROOT)/src/rtl
CSRC_DIR = $(PROJECT_ROOT)/src/csrc
INCLUDE_DIR = $(CSRC_DIR)/include
CPP_DIR = $(CSRC_DIR)/src
OBJ_DIR = $(PROJECT_ROOT)/obj_dir
WAVE_DIR = wave

# Verilator
VERILATOR = verilator

# Verilator 选项（忽略警告导致的错误，但仍显示警告）
VERILATOR_FLAGS = --timing --error-limit 0 \
    --Wno-PINMISSING --Wno-WIDTHTRUNC --Wno-CASEINCOMPLETE --Wno-UNUSED

# 递归搜索 Verilog 文件（包含子目录）
VERILOG_FILES = $(shell find $(RTL_DIR) -type f -name "*.v")

# 动态匹配与 SELECT_MODULE 对应的仿真文件
SIM_FILE = $(CPP_DIR)/tb_$(SELECT_MODULE).cpp

# 主程序文件
MAIN_FILE = $(CPP_DIR)/main.cpp

# 检查仿真文件是否存在
ifeq ($(wildcard $(SIM_FILE)),)
  $(error Simulation file not found for module '$(SELECT_MODULE)'. Expected file: $(SIM_FILE))
endif

# 目标
all: run

# 确保波形文件目录存在
$(WAVE_DIR):
	mkdir -p $(WAVE_DIR)

# 编译 Verilog 模块和选定的仿真文件
$(OBJ_DIR)/V$(SELECT_MODULE): $(VERILOG_FILES) $(SIM_FILE) $(MAIN_FILE) | $(WAVE_DIR)
	$(VERILATOR) --cc $(VERILOG_FILES) --trace --exe $(MAIN_FILE) $(SIM_FILE) \
	    -I$(INCLUDE_DIR) -CFLAGS "-I$(INCLUDE_DIR) $(CFLAGS_MODULE)" \
	    -top-module $(SELECT_MODULE) \
	    --Mdir $(OBJ_DIR) $(VERILATOR_FLAGS)  # 添加 VERILATOR_FLAGS
	make -j -C $(OBJ_DIR) -f V$(SELECT_MODULE).mk V$(SELECT_MODULE)

# 运行仿真
run: $(OBJ_DIR)/V$(SELECT_MODULE)
	$(OBJ_DIR)/V$(SELECT_MODULE)

# 清理
clean:
	rm -rf $(OBJ_DIR) $(WAVE_DIR)
