############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project A4HLS
set_top cordic
add_files A4HLS/src/cordic.h
add_files A4HLS/src/cordic.cpp
add_files -tb A4HLS/src/tb_cordic.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z020-clg484-1}
create_clock -period 10 -name default
config_export -format ip_catalog -output C:/ELEC522/sl186/Assignment4/HLS/A4HLS -rtl verilog
source "./A4HLS/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -output C:/ELEC522/sl186/Assignment4/HLS/A4HLS
