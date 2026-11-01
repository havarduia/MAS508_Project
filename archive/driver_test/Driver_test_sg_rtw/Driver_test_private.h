/*
 * Driver_test_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Driver_test".
 *
 * Model version              : 15.10
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C++ source code generated on : Thu Oct 29 21:21:54 2026
 *
 * Target selection: speedgoat.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Driver_test_private_h_
#define Driver_test_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "Driver_test_types.h"
#include "Driver_test.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern real_T rt_powd_snf(real_T u0, real_T u1);
extern void* slrtRegisterSignalToLoggingService(uintptr_t sigAddr);
extern "C" void sg_IO183_setup_s(SimStruct *rts);
extern "C" void sg_IO183_ad_s(SimStruct *rts);
extern "C" void sg_IO183_da_s(SimStruct *rts);

#endif                                 /* Driver_test_private_h_ */
