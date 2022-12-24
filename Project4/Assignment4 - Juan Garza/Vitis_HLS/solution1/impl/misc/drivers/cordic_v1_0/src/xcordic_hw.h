// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// HLS_TREEADD_PERIPH_BUS
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
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
// 0x10 : Data signal of state
//        bit 0  - state[0] (Read/Write)
//        others - reserved
// 0x14 : reserved
// 0x18 : Data signal of theta
//        bit 15~0 - theta[15:0] (Read/Write)
//        others   - reserved
// 0x1c : reserved
// 0x20 : Data signal of x
//        bit 15~0 - x[15:0] (Read/Write)
//        others   - reserved
// 0x24 : reserved
// 0x28 : Data signal of y
//        bit 15~0 - y[15:0] (Read/Write)
//        others   - reserved
// 0x2c : reserved
// 0x30 : Data signal of s
//        bit 15~0 - s[15:0] (Read)
//        others   - reserved
// 0x34 : Control signal of s
//        bit 0  - s_ap_vld (Read/COR)
//        others - reserved
// 0x40 : Data signal of c
//        bit 15~0 - c[15:0] (Read)
//        others   - reserved
// 0x44 : Control signal of c
//        bit 0  - c_ap_vld (Read/COR)
//        others - reserved
// 0x50 : Data signal of t
//        bit 15~0 - t[15:0] (Read)
//        others   - reserved
// 0x54 : Control signal of t
//        bit 0  - t_ap_vld (Read/COR)
//        others - reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_AP_CTRL    0x00
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_GIE        0x04
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_IER        0x08
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_ISR        0x0c
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_STATE_DATA 0x10
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_BITS_STATE_DATA 1
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_THETA_DATA 0x18
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_BITS_THETA_DATA 16
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_X_DATA     0x20
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_BITS_X_DATA     16
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_Y_DATA     0x28
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_BITS_Y_DATA     16
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_S_DATA     0x30
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_BITS_S_DATA     16
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_S_CTRL     0x34
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_C_DATA     0x40
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_BITS_C_DATA     16
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_C_CTRL     0x44
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_T_DATA     0x50
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_BITS_T_DATA     16
#define XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_T_CTRL     0x54

