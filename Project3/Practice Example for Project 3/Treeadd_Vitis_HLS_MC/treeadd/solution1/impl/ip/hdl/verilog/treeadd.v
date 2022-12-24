// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Version: 2022.1
// Copyright (C) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="treeadd_treeadd,hls_ip_2022_1,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xc7a12ti-csg325-1L,HLS_INPUT_CLOCK=10.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=6.183000,HLS_SYN_LAT=1,HLS_SYN_TPT=none,HLS_SYN_MEM=0,HLS_SYN_DSP=0,HLS_SYN_FF=18,HLS_SYN_LUT=146,HLS_VERSION=2022_1}" *)

module treeadd (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        a,
        b,
        c,
        d,
        e,
        f,
        g,
        h,
        r,
        r_ap_vld
);

parameter    ap_ST_fsm_state1 = 2'd1;
parameter    ap_ST_fsm_state2 = 2'd2;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [15:0] a;
input  [15:0] b;
input  [15:0] c;
input  [15:0] d;
input  [15:0] e;
input  [15:0] f;
input  [15:0] g;
input  [15:0] h;
output  [15:0] r;
output   r_ap_vld;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg r_ap_vld;

(* fsm_encoding = "none" *) reg   [1:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
wire   [15:0] add_ln29_5_fu_105_p2;
reg   [15:0] add_ln29_5_reg_135;
wire    ap_CS_fsm_state2;
wire   [15:0] add_ln29_4_fu_99_p2;
wire   [15:0] add_ln29_3_fu_93_p2;
wire   [15:0] add_ln29_1_fu_117_p2;
wire   [15:0] add_ln29_fu_111_p2;
wire   [15:0] add_ln29_2_fu_123_p2;
reg   [1:0] ap_NS_fsm;
reg    ap_ST_fsm_state1_blk;
wire    ap_ST_fsm_state2_blk;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 2'd1;
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state1)) begin
        add_ln29_5_reg_135 <= add_ln29_5_fu_105_p2;
    end
end

always @ (*) begin
    if ((ap_start == 1'b0)) begin
        ap_ST_fsm_state1_blk = 1'b1;
    end else begin
        ap_ST_fsm_state1_blk = 1'b0;
    end
end

assign ap_ST_fsm_state2_blk = 1'b0;

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        r_ap_vld = 1'b1;
    end else begin
        r_ap_vld = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((ap_start == 1'b1) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            ap_NS_fsm = ap_ST_fsm_state1;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln29_1_fu_117_p2 = (c + d);

assign add_ln29_2_fu_123_p2 = (add_ln29_1_fu_117_p2 + add_ln29_fu_111_p2);

assign add_ln29_3_fu_93_p2 = (e + f);

assign add_ln29_4_fu_99_p2 = (g + h);

assign add_ln29_5_fu_105_p2 = (add_ln29_4_fu_99_p2 + add_ln29_3_fu_93_p2);

assign add_ln29_fu_111_p2 = (b + a);

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign r = (add_ln29_5_reg_135 + add_ln29_2_fu_123_p2);

endmodule //treeadd
