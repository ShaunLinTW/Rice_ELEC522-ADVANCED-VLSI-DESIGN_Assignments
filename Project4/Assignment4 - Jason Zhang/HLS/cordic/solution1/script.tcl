############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project cordic
set_top cordic
add_files ../basic_cordic.cpp
add_files ../basic_cordic.h
add_files -tb ../basic_cordic_tb.cpp -cflags "-DHW_COSIM -Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7a12ti-csg325-1L}
create_clock -period 10 -name default
config_export -format ip_catalog -rtl verilog
source "./cordic/solution1/directives.tcl"
csim_design -setup
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
