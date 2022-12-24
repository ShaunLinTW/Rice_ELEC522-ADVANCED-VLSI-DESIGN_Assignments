// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xcordic.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XCordic_CfgInitialize(XCordic *InstancePtr, XCordic_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Hls_treeadd_periph_bus_BaseAddress = ConfigPtr->Hls_treeadd_periph_bus_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XCordic_Start(XCordic *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_AP_CTRL) & 0x80;
    XCordic_WriteReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_AP_CTRL, Data | 0x01);
}

u32 XCordic_IsDone(XCordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XCordic_IsIdle(XCordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XCordic_IsReady(XCordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XCordic_EnableAutoRestart(XCordic *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCordic_WriteReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_AP_CTRL, 0x80);
}

void XCordic_DisableAutoRestart(XCordic *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCordic_WriteReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_AP_CTRL, 0);
}

void XCordic_Set_state(XCordic *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCordic_WriteReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_STATE_DATA, Data);
}

u32 XCordic_Get_state(XCordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_STATE_DATA);
    return Data;
}

void XCordic_Set_theta(XCordic *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCordic_WriteReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_THETA_DATA, Data);
}

u32 XCordic_Get_theta(XCordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_THETA_DATA);
    return Data;
}

void XCordic_Set_x(XCordic *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCordic_WriteReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_X_DATA, Data);
}

u32 XCordic_Get_x(XCordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_X_DATA);
    return Data;
}

void XCordic_Set_y(XCordic *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCordic_WriteReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_Y_DATA, Data);
}

u32 XCordic_Get_y(XCordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_Y_DATA);
    return Data;
}

u32 XCordic_Get_s(XCordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_S_DATA);
    return Data;
}

u32 XCordic_Get_s_vld(XCordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_S_CTRL);
    return Data & 0x1;
}

u32 XCordic_Get_c(XCordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_C_DATA);
    return Data;
}

u32 XCordic_Get_c_vld(XCordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_C_CTRL);
    return Data & 0x1;
}

u32 XCordic_Get_t(XCordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_T_DATA);
    return Data;
}

u32 XCordic_Get_t_vld(XCordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_T_CTRL);
    return Data & 0x1;
}

void XCordic_InterruptGlobalEnable(XCordic *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCordic_WriteReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_GIE, 1);
}

void XCordic_InterruptGlobalDisable(XCordic *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCordic_WriteReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_GIE, 0);
}

void XCordic_InterruptEnable(XCordic *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_IER);
    XCordic_WriteReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_IER, Register | Mask);
}

void XCordic_InterruptDisable(XCordic *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_IER);
    XCordic_WriteReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_IER, Register & (~Mask));
}

void XCordic_InterruptClear(XCordic *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    //XCordic_WriteReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_ISR, Mask);
}

u32 XCordic_InterruptGetEnabled(XCordic *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_IER);
}

u32 XCordic_InterruptGetStatus(XCordic *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    // Current Interrupt Clear Behavior is Clear on Read(COR).
    return XCordic_ReadReg(InstancePtr->Hls_treeadd_periph_bus_BaseAddress, XCORDIC_HLS_TREEADD_PERIPH_BUS_ADDR_ISR);
}

