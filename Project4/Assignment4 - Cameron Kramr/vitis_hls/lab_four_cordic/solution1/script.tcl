############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project lab_four_cordic
set_top circular_cordic
add_files ../code/cordic.cpp
add_files -tb ../code/cordic_test.cpp -cflags "-DHW_COSIM -Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vitis
set_part {xc7a12ti-csg325-1L}
create_clock -period 10 -name default
config_interface -m_axi_alignment_byte_size 64 -m_axi_latency 64 -m_axi_max_widen_bitwidth 512
config_rtl -register_reset_num 3
#source "./lab_four_cordic/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
