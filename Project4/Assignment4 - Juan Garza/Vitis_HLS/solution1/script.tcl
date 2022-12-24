############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project cordic
set_top cordic
add_files cordic.cpp
add_files -tb cordic-top.cpp
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg484-1}
create_clock -period 10 -name default
config_export -format ip_catalog -output C:/ELEC522/jag33/proj3/Modelcompser -rtl verilog
#source "./cordic/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -output C:/ELEC522/jag33/proj3/Modelcompser
