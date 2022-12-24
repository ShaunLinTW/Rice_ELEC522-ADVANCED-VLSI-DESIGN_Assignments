############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project cordic_raw
set_top cordic
add_files ../fpga_hls_raw/cordic.cpp
add_files -tb ../fpga_hls_raw/cordic_test.cpp
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg484-1}
create_clock -period 10 -name default
#source "./cordic_raw/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
