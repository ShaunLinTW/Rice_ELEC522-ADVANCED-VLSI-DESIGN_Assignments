############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project treeadd
set_top treeadd
add_files treeadd.cpp
add_files -tb treeadd_test.cpp -cflags "-DHW_COSIM"
open_solution "solution1" -flow_target vivado
set_part {xc7a12ticsg325-1L}
create_clock -period 10 -name default
config_export -format sysgen -output C:/ELEC522/hl116/Project3/Treeadd_Vitis_HLS_MC/treeadd/solution1
#source "./treeadd/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format sysgen -output C:/ELEC522/hl116/Project3/Treeadd_Vitis_HLS_MC/treeadd/solution1
