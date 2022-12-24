// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XCIRCULAR_CORDIC_H
#define XCIRCULAR_CORDIC_H

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
#include "xcircular_cordic_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Control_BaseAddress;
} XCircular_cordic_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XCircular_cordic;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XCircular_cordic_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XCircular_cordic_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XCircular_cordic_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XCircular_cordic_ReadReg(BaseAddress, RegOffset) \
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
int XCircular_cordic_Initialize(XCircular_cordic *InstancePtr, u16 DeviceId);
XCircular_cordic_Config* XCircular_cordic_LookupConfig(u16 DeviceId);
int XCircular_cordic_CfgInitialize(XCircular_cordic *InstancePtr, XCircular_cordic_Config *ConfigPtr);
#else
int XCircular_cordic_Initialize(XCircular_cordic *InstancePtr, const char* InstanceName);
int XCircular_cordic_Release(XCircular_cordic *InstancePtr);
#endif

void XCircular_cordic_Start(XCircular_cordic *InstancePtr);
u32 XCircular_cordic_IsDone(XCircular_cordic *InstancePtr);
u32 XCircular_cordic_IsIdle(XCircular_cordic *InstancePtr);
u32 XCircular_cordic_IsReady(XCircular_cordic *InstancePtr);
void XCircular_cordic_Continue(XCircular_cordic *InstancePtr);
void XCircular_cordic_EnableAutoRestart(XCircular_cordic *InstancePtr);
void XCircular_cordic_DisableAutoRestart(XCircular_cordic *InstancePtr);

void XCircular_cordic_Set_angle(XCircular_cordic *InstancePtr, u32 Data);
u32 XCircular_cordic_Get_angle(XCircular_cordic *InstancePtr);
void XCircular_cordic_Set_cosine(XCircular_cordic *InstancePtr, u64 Data);
u64 XCircular_cordic_Get_cosine(XCircular_cordic *InstancePtr);
void XCircular_cordic_Set_sine(XCircular_cordic *InstancePtr, u64 Data);
u64 XCircular_cordic_Get_sine(XCircular_cordic *InstancePtr);

void XCircular_cordic_InterruptGlobalEnable(XCircular_cordic *InstancePtr);
void XCircular_cordic_InterruptGlobalDisable(XCircular_cordic *InstancePtr);
void XCircular_cordic_InterruptEnable(XCircular_cordic *InstancePtr, u32 Mask);
void XCircular_cordic_InterruptDisable(XCircular_cordic *InstancePtr, u32 Mask);
void XCircular_cordic_InterruptClear(XCircular_cordic *InstancePtr, u32 Mask);
u32 XCircular_cordic_InterruptGetEnabled(XCircular_cordic *InstancePtr);
u32 XCircular_cordic_InterruptGetStatus(XCircular_cordic *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
