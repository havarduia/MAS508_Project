/*
 * Friction_ramp_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Friction_ramp".
 *
 * Model version              : 15.10
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C++ source code generated on : Thu Oct 29 20:55:26 2026
 *
 * Target selection: speedgoat.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Friction_ramp_private_h_
#define Friction_ramp_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "Friction_ramp_types.h"
#include "Friction_ramp.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern void* slrtRegisterSignalToLoggingService(uintptr_t sigAddr);
extern real_T look1_binlcpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
extern "C" void sg_IO183_setup_s(SimStruct *rts);
extern "C" void sg_IO183_ad_s(SimStruct *rts);
extern "C" void sg_IO183_da_s(SimStruct *rts);

#endif                                 /* Friction_ramp_private_h_ */
