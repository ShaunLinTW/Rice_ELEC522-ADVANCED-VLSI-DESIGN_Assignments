; ModuleID = 'C:/ELEC522/jag33/proj3/cordic/solution1/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>" = type { %"struct.ap_fixed_base<16, 3, true, AP_TRN, AP_WRAP, 0>" }
%"struct.ap_fixed_base<16, 3, true, AP_TRN, AP_WRAP, 0>" = type { %"struct.ssdm_int<16, true>" }
%"struct.ssdm_int<16, true>" = type { i16 }

; Function Attrs: argmemonly noinline
define void @apatb_cordic_ir(i1 zeroext %state, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* nocapture readonly %theta, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* nocapture readonly %x, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* nocapture readonly %y, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* noalias nocapture nonnull dereferenceable(2) %s, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* noalias nocapture nonnull dereferenceable(2) %c, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* noalias nocapture nonnull dereferenceable(2) %t) local_unnamed_addr #0 {
entry:
  %s_copy = alloca i16, align 512
  %c_copy = alloca i16, align 512
  %t_copy = alloca i16, align 512
  call fastcc void @copy_in(%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* nonnull %s, i16* nonnull align 512 %s_copy, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* nonnull %c, i16* nonnull align 512 %c_copy, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* nonnull %t, i16* nonnull align 512 %t_copy)
  call void @apatb_cordic_hw(i1 %state, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %theta, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %x, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %y, i16* %s_copy, i16* %c_copy, i16* %t_copy)
  call void @copy_back(%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %s, i16* %s_copy, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %c, i16* %c_copy, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %t, i16* %t_copy)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_in(%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* noalias readonly, i16* noalias align 512, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* noalias readonly, i16* noalias align 512, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* noalias readonly, i16* noalias align 512) unnamed_addr #1 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"(i16* align 512 %1, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %0)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"(i16* align 512 %3, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %2)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"(i16* align 512 %5, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %4)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_out(%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* noalias, i16* noalias readonly align 512, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* noalias, i16* noalias readonly align 512, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* noalias, i16* noalias readonly align 512) unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>.7"(%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %0, i16* align 512 %1)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>.7"(%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %2, i16* align 512 %3)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>.7"(%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %4, i16* align 512 %5)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @"onebyonecpy_hls.p0struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>.7"(%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* noalias, i16* noalias readonly align 512) unnamed_addr #3 {
entry:
  %2 = icmp eq %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %0, null
  %3 = icmp eq i16* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  %.01.0.05 = getelementptr %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>", %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %0, i32 0, i32 0, i32 0, i32 0
  %5 = load i16, i16* %1, align 512
  store i16 %5, i16* %.01.0.05, align 512
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @"onebyonecpy_hls.p0struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"(i16* noalias align 512, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* noalias readonly) unnamed_addr #3 {
entry:
  %2 = icmp eq i16* %0, null
  %3 = icmp eq %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  %.0.0.04 = getelementptr %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>", %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %1, i32 0, i32 0, i32 0, i32 0
  %5 = load i16, i16* %.0.0.04, align 2
  store i16 %5, i16* %0, align 512
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

declare void @apatb_cordic_hw(i1, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"*, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"*, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"*, i16*, i16*, i16*)

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_back(%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* noalias, i16* noalias readonly align 512, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* noalias, i16* noalias readonly align 512, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* noalias, i16* noalias readonly align 512) unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>.7"(%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %0, i16* align 512 %1)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>.7"(%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %2, i16* align 512 %3)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>.7"(%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %4, i16* align 512 %5)
  ret void
}

define void @cordic_hw_stub_wrapper(i1, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"*, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"*, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"*, i16*, i16*, i16*) #4 {
entry:
  %7 = alloca %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"
  %8 = alloca %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"
  %9 = alloca %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"
  call void @copy_out(%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %7, i16* %4, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %8, i16* %5, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %9, i16* %6)
  call void @cordic_hw_stub(i1 %0, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %1, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %2, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %3, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %7, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %8, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %9)
  call void @copy_in(%"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %7, i16* %4, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %8, i16* %5, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"* %9, i16* %6)
  ret void
}

declare void @cordic_hw_stub(i1, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"*, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"*, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"*, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"*, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"*, %"struct.ap_fixed<16, 3, AP_TRN, AP_WRAP, 0>"*)

attributes #0 = { argmemonly noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyout" }
attributes #3 = { argmemonly noinline norecurse "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #4 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
