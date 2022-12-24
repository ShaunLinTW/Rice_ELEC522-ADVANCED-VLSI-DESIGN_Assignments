// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 4  - ap_continue (Read/Write/SC)
//        bit 7  - auto_restart (Read/Write)
//        bit 9  - interrupt (Read)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0 - enable ap_done interrupt (Read/Write)
//        bit 1 - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/COR)
//        bit 0 - ap_done (Read/COR)
//        bit 1 - ap_ready (Read/COR)
//        others - reserved
// 0x10 : Data signal of angle
//        bit 15~0 - angle[15:0] (Read/Write)
//        others   - reserved
// 0x14 : reserved
// 0x18 : Data signal of cosine
//        bit 31~0 - cosine[31:0] (Read/Write)
// 0x1c : Data signal of cosine
//        bit 31~0 - cosine[63:32] (Read/Write)
// 0x20 : reserved
// 0x24 : Data signal of sine
//        bit 31~0 - sine[31:0] (Read/Write)
// 0x28 : Data signal of sine
//        bit 31~0 - sine[63:32] (Read/Write)
// 0x2c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XCIRCULAR_CORDIC_CONTROL_ADDR_AP_CTRL     0x00
#define XCIRCULAR_CORDIC_CONTROL_ADDR_GIE         0x04
#define XCIRCULAR_CORDIC_CONTROL_ADDR_IER         0x08
#define XCIRCULAR_CORDIC_CONTROL_ADDR_ISR         0x0c
#define XCIRCULAR_CORDIC_CONTROL_ADDR_ANGLE_DATA  0x10
#define XCIRCULAR_CORDIC_CONTROL_BITS_ANGLE_DATA  16
#define XCIRCULAR_CORDIC_CONTROL_ADDR_COSINE_DATA 0x18
#define XCIRCULAR_CORDIC_CONTROL_BITS_COSINE_DATA 64
#define XCIRCULAR_CORDIC_CONTROL_ADDR_SINE_DATA   0x24
#define XCIRCULAR_CORDIC_CONTROL_BITS_SINE_DATA   64

