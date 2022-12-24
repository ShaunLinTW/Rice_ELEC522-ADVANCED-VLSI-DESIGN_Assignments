// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xcircular_cordic.h"

extern XCircular_cordic_Config XCircular_cordic_ConfigTable[];

XCircular_cordic_Config *XCircular_cordic_LookupConfig(u16 DeviceId) {
	XCircular_cordic_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XCIRCULAR_CORDIC_NUM_INSTANCES; Index++) {
		if (XCircular_cordic_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XCircular_cordic_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XCircular_cordic_Initialize(XCircular_cordic *InstancePtr, u16 DeviceId) {
	XCircular_cordic_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XCircular_cordic_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XCircular_cordic_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

