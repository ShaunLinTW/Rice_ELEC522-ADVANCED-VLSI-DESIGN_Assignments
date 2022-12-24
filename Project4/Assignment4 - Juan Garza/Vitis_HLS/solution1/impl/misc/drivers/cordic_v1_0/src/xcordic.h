// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XCORDIC_H
#define XCORDIC_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xcordic_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Hls_treeadd_periph_bus_BaseAddress;
} XCordic_Config;
#endif

typedef struct {
    u64 Hls_treeadd_periph_bus_BaseAddress;
    u32 IsReady;
} XCordic;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XCordic_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XCordic_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XCordic_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XCordic_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XCordic_Initialize(XCordic *InstancePtr, u16 DeviceId);
XCordic_Config* XCordic_LookupConfig(u16 DeviceId);
int XCordic_CfgInitialize(XCordic *InstancePtr, XCordic_Config *ConfigPtr);
#else
int XCordic_Initialize(XCordic *InstancePtr, const char* InstanceName);
int XCordic_Release(XCordic *InstancePtr);
#endif

void XCordic_Start(XCordic *InstancePtr);
u32 XCordic_IsDone(XCordic *InstancePtr);
u32 XCordic_IsIdle(XCordic *InstancePtr);
u32 XCordic_IsReady(XCordic *InstancePtr);
void XCordic_EnableAutoRestart(XCordic *InstancePtr);
void XCordic_DisableAutoRestart(XCordic *InstancePtr);

void XCordic_Set_state(XCordic *InstancePtr, u32 Data);
u32 XCordic_Get_state(XCordic *InstancePtr);
void XCordic_Set_theta(XCordic *InstancePtr, u32 Data);
u32 XCordic_Get_theta(XCordic *InstancePtr);
void XCordic_Set_x(XCordic *InstancePtr, u32 Data);
u32 XCordic_Get_x(XCordic *InstancePtr);
void XCordic_Set_y(XCordic *InstancePtr, u32 Data);
u32 XCordic_Get_y(XCordic *InstancePtr);
u32 XCordic_Get_s(XCordic *InstancePtr);
u32 XCordic_Get_s_vld(XCordic *InstancePtr);
u32 XCordic_Get_c(XCordic *InstancePtr);
u32 XCordic_Get_c_vld(XCordic *InstancePtr);
u32 XCordic_Get_t(XCordic *InstancePtr);
u32 XCordic_Get_t_vld(XCordic *InstancePtr);

void XCordic_InterruptGlobalEnable(XCordic *InstancePtr);
void XCordic_InterruptGlobalDisable(XCordic *InstancePtr);
void XCordic_InterruptEnable(XCordic *InstancePtr, u32 Mask);
void XCordic_InterruptDisable(XCordic *InstancePtr, u32 Mask);
void XCordic_InterruptClear(XCordic *InstancePtr, u32 Mask);
u32 XCordic_InterruptGetEnabled(XCordic *InstancePtr);
u32 XCordic_InterruptGetStatus(XCordic *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
