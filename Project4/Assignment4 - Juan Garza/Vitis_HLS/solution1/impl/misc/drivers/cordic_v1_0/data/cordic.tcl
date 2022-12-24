# ==============================================================
# Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
# Tool Version Limit: 2022.04
# Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
# ==============================================================
proc generate {drv_handle} {
    xdefine_include_file $drv_handle "xparameters.h" "XCordic" \
        "NUM_INSTANCES" \
        "DEVICE_ID" \
        "C_S_AXI_HLS_TREEADD_PERIPH_BUS_BASEADDR" \
        "C_S_AXI_HLS_TREEADD_PERIPH_BUS_HIGHADDR"

    xdefine_config_file $drv_handle "xcordic_g.c" "XCordic" \
        "DEVICE_ID" \
        "C_S_AXI_HLS_TREEADD_PERIPH_BUS_BASEADDR"

    xdefine_canonical_xpars $drv_handle "xparameters.h" "XCordic" \
        "DEVICE_ID" \
        "C_S_AXI_HLS_TREEADD_PERIPH_BUS_BASEADDR" \
        "C_S_AXI_HLS_TREEADD_PERIPH_BUS_HIGHADDR"
}

