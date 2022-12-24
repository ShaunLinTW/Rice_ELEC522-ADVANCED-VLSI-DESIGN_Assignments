// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xcordic.h"

extern XCordic_Config XCordic_ConfigTable[];

XCordic_Config *XCordic_LookupConfig(u16 DeviceId) {
	XCordic_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XCORDIC_NUM_INSTANCES; Index++) {
		if (XCordic_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XCordic_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XCordic_Initialize(XCordic *InstancePtr, u16 DeviceId) {
	XCordic_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XCordic_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XCordic_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

