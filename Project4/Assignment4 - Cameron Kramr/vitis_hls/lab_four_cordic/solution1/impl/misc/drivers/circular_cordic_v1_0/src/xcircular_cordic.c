// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xcircular_cordic.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XCircular_cordic_CfgInitialize(XCircular_cordic *InstancePtr, XCircular_cordic_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XCircular_cordic_Start(XCircular_cordic *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCircular_cordic_ReadReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_AP_CTRL) & 0x80;
    XCircular_cordic_WriteReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XCircular_cordic_IsDone(XCircular_cordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCircular_cordic_ReadReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XCircular_cordic_IsIdle(XCircular_cordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCircular_cordic_ReadReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XCircular_cordic_IsReady(XCircular_cordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCircular_cordic_ReadReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XCircular_cordic_Continue(XCircular_cordic *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCircular_cordic_ReadReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_AP_CTRL) & 0x80;
    XCircular_cordic_WriteReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_AP_CTRL, Data | 0x10);
}

void XCircular_cordic_EnableAutoRestart(XCircular_cordic *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCircular_cordic_WriteReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XCircular_cordic_DisableAutoRestart(XCircular_cordic *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCircular_cordic_WriteReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_AP_CTRL, 0);
}

void XCircular_cordic_Set_angle(XCircular_cordic *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCircular_cordic_WriteReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_ANGLE_DATA, Data);
}

u32 XCircular_cordic_Get_angle(XCircular_cordic *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCircular_cordic_ReadReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_ANGLE_DATA);
    return Data;
}

void XCircular_cordic_Set_cosine(XCircular_cordic *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCircular_cordic_WriteReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_COSINE_DATA, (u32)(Data));
    XCircular_cordic_WriteReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_COSINE_DATA + 4, (u32)(Data >> 32));
}

u64 XCircular_cordic_Get_cosine(XCircular_cordic *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCircular_cordic_ReadReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_COSINE_DATA);
    Data += (u64)XCircular_cordic_ReadReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_COSINE_DATA + 4) << 32;
    return Data;
}

void XCircular_cordic_Set_sine(XCircular_cordic *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCircular_cordic_WriteReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_SINE_DATA, (u32)(Data));
    XCircular_cordic_WriteReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_SINE_DATA + 4, (u32)(Data >> 32));
}

u64 XCircular_cordic_Get_sine(XCircular_cordic *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCircular_cordic_ReadReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_SINE_DATA);
    Data += (u64)XCircular_cordic_ReadReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_SINE_DATA + 4) << 32;
    return Data;
}

void XCircular_cordic_InterruptGlobalEnable(XCircular_cordic *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCircular_cordic_WriteReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_GIE, 1);
}

void XCircular_cordic_InterruptGlobalDisable(XCircular_cordic *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCircular_cordic_WriteReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_GIE, 0);
}

void XCircular_cordic_InterruptEnable(XCircular_cordic *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XCircular_cordic_ReadReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_IER);
    XCircular_cordic_WriteReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_IER, Register | Mask);
}

void XCircular_cordic_InterruptDisable(XCircular_cordic *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XCircular_cordic_ReadReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_IER);
    XCircular_cordic_WriteReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_IER, Register & (~Mask));
}

void XCircular_cordic_InterruptClear(XCircular_cordic *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    //XCircular_cordic_WriteReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_ISR, Mask);
}

u32 XCircular_cordic_InterruptGetEnabled(XCircular_cordic *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCircular_cordic_ReadReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_IER);
}

u32 XCircular_cordic_InterruptGetStatus(XCircular_cordic *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    // Current Interrupt Clear Behavior is Clear on Read(COR).
    return XCircular_cordic_ReadReg(InstancePtr->Control_BaseAddress, XCIRCULAR_CORDIC_CONTROL_ADDR_ISR);
}

