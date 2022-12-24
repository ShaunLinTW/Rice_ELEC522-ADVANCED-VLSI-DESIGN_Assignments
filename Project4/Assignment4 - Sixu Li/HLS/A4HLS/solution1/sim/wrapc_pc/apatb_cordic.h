// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================

extern "C" void AESL_WRAP_cordic (
char select_r,
short CS_I_T,
short IA_I_S,
short IA_I_C,
volatile void* CS_O_SIN,
volatile void* CS_O_COS,
volatile void* IA_O_IAT,
volatile void* done);
