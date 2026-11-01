/*
 * Friction_ramp.h
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

#ifndef Friction_ramp_h_
#define Friction_ramp_h_
#include <logsrv.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "verify/verifyIntrf.h"
#include "Friction_ramp_types.h"
#include <stddef.h>
#include <cstring>
#include "Friction_ramp_cal.h"

extern "C"
{

#include "rt_nonfinite.h"

}

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetSampleHitArray
#define rtmGetSampleHitArray(rtm)      ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmGetStepSize
#define rtmGetStepSize(rtm)            ((rtm)->Timing.stepSize)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
#define rtmGet_TimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

#ifndef rtmGetTimeOfLastOutput
#define rtmGetTimeOfLastOutput(rtm)    ((rtm)->Timing.timeOfLastOutput)
#endif

/* Block signals (default storage) */
struct B_Friction_ramp_T {
  real_T SpeedgoatAnalogInput1;        /* '<Root>/Speedgoat Analog Input1' */
  real_T Xm;                           /* '<Root>/Sum' */
  real_T Ramptime;                     /* '<Root>/Ramp time' */
  real_T Rampprofile;                  /* '<Root>/Ramp profile' */
  real_T Cutofflatch;                  /* '<Root>/Cutoff latch' */
  real_T Aftercutoff;                  /* '<Root>/After cutoff' */
  real_T Gain;                         /* '<Root>/Gain' */
  real_T u;                           /* '<Root>/Saturation Input: [0, 5] V2' */
  real_T Abs1;                         /* '<Root>/Abs1' */
  real_T u_c;                         /* '<Root>/Saturation Input: [0, 5] V1' */
  real_T polarity;                     /* '<Root>/Switch' */
  real_T Nomorelift;                   /* '<Root>/No more lift' */
  real_T y;                            /* '<S1>/BAW033k' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_Friction_ramp_T {
  void *Setup1_PWORK;                  /* '<Root>/Setup1' */
  void *SpeedgoatAnalogInput1_PWORK;   /* '<Root>/Speedgoat Analog Input1' */
  void *SpeedgoatAnalogOutput1_PWORK;  /* '<Root>/Speedgoat Analog Output1' */
  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_After;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Cutof;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Satur;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Sat_h;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Sum_a;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Switc;   /* synthesized block */

  int32_T sfEvent;                     /* '<S1>/BAW033k' */
  int_T Setup1_IWORK[8];               /* '<Root>/Setup1' */
  int_T SpeedgoatAnalogInput1_IWORK[5];/* '<Root>/Speedgoat Analog Input1' */
  int_T SpeedgoatAnalogOutput1_IWORK[5];/* '<Root>/Speedgoat Analog Output1' */
  boolean_T Cutofflatch_Mode;          /* '<Root>/Cutoff latch' */
  boolean_T doneDoubleBufferReInit;    /* '<S1>/BAW033k' */
};

/* External outputs (root outports fed by signals with default storage) */
struct ExtY_Friction_ramp_T {
  real_T PayloadpositionXm;            /* '<Root>/Payload position X[m]' */
};

/* Real-time Model Data Structure */
struct tag_RTM_Friction_ramp_T {
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;

  /*
   * NonInlinedSFcns:
   * The following substructure contains information regarding
   * non-inlined s-functions used in the model.
   */
  struct {
    RTWSfcnInfo sfcnInfo;
    time_T *taskTimePtrs[1];
    SimStruct childSFunctions[3];
    SimStruct *childSFunctionPtrs[3];
    struct _ssBlkInfo2 blkInfo2[3];
    struct _ssSFcnModelMethods2 methods2[3];
    struct _ssSFcnModelMethods3 methods3[3];
    struct _ssSFcnModelMethods4 methods4[3];
    struct _ssStatesInfo2 statesInfo2[3];
    ssPeriodicStatesInfo periodicStatesInfo[3];
    struct _ssPortInfo2 inputOutputPortInfo2[3];
    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      uint_T attribs[11];
      mxArray *params[11];
      struct _ssDWorkRecord dWork[2];
      struct _ssDWorkAuxRecord dWorkAux[2];
    } Sfcn0;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortOutputs outputPortInfo[1];
      struct _ssOutPortUnit outputPortUnits[1];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[1];
      uint_T attribs[5];
      mxArray *params[5];
      struct _ssDWorkRecord dWork[2];
      struct _ssDWorkAuxRecord dWorkAux[2];
    } Sfcn1;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[2];
      struct _ssInPortUnit inputPortUnits[2];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[2];
      uint_T attribs[7];
      mxArray *params[7];
      struct _ssDWorkRecord dWork[2];
      struct _ssDWorkAuxRecord dWorkAux[2];
    } Sfcn2;
  } NonInlinedSFcns;

  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T options;
    int_T numContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[1];
    time_T offsetTimesArray[1];
    int_T sampleTimeTaskIDArray[1];
    int_T sampleHitArray[1];
    int_T perTaskSampleHitsArray[1];
    time_T tArray[1];
  } Timing;
};

/* Block signals (default storage) */
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_Friction_ramp_T Friction_ramp_B;

#ifdef __cplusplus

}

#endif

/* Block states (default storage) */
extern struct DW_Friction_ramp_T Friction_ramp_DW;

#ifdef __cplusplus

extern "C"
{

#endif

  /* External outputs (root outports fed by signals with default storage) */
  extern struct ExtY_Friction_ramp_T Friction_ramp_Y;

#ifdef __cplusplus

}

#endif

#ifdef __cplusplus

extern "C"
{

#endif

  /* Model entry point functions */
  extern void Friction_ramp_initialize(void);
  extern void Friction_ramp_step(void);
  extern void Friction_ramp_terminate(void);

#ifdef __cplusplus

}

#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_Friction_ramp_T *const Friction_ramp_M;

#ifdef __cplusplus

}

#endif

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Friction_ramp'
 * '<S1>'   : 'Friction_ramp/Inductive Sensor '
 * '<S2>'   : 'Friction_ramp/Inductive Sensor /BAW033k'
 */
#endif                                 /* Friction_ramp_h_ */
