/*
 * Friction_ramp.cpp
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

#include "Friction_ramp.h"
#include "rtwtypes.h"
#include "Friction_ramp_cal.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include <cmath>
#include "Friction_ramp_private.h"
#include <cstring>

/* Named constants for MATLAB Function: '<S1>/BAW033k' */
const int32_T Friction_ramp_CALL_EVENT = -1;

/* Block signals (default storage) */
B_Friction_ramp_T Friction_ramp_B;

/* Block states (default storage) */
DW_Friction_ramp_T Friction_ramp_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Friction_ramp_T Friction_ramp_Y;

/* Real-time model */
RT_MODEL_Friction_ramp_T Friction_ramp_M_ = RT_MODEL_Friction_ramp_T();
RT_MODEL_Friction_ramp_T *const Friction_ramp_M = &Friction_ramp_M_;
real_T look1_binlcpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = 1.0;
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

/* Model step function */
void Friction_ramp_step(void)
{
  real_T u0;
  real_T u1;
  real_T u2;

  /* S-Function (sg_IO183_setup_s): '<Root>/Setup1' */

  /* Level2 S-Function Block: '<Root>/Setup1' (sg_IO183_setup_s) */
  {
    SimStruct *rts = Friction_ramp_M->childSfunctions[0];
    sfcnOutputs(rts,0);
  }

  /* S-Function (sg_IO183_ad_s): '<Root>/Speedgoat Analog Input1' */

  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Input1' (sg_IO183_ad_s) */
  {
    SimStruct *rts = Friction_ramp_M->childSfunctions[1];
    sfcnOutputs(rts,0);
  }

  /* MATLAB Function: '<S1>/BAW033k' */
  Friction_ramp_DW.sfEvent = Friction_ramp_CALL_EVENT;
  Friction_ramp_B.y = 0.004 * Friction_ramp_B.SpeedgoatAnalogInput1;

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<Root>/Initial Payload PositionX0[m] '
   */
  Friction_ramp_B.Xm = Friction_ramp_B.y -
    Friction_ramp_cal->InitialPayloadPositionX0m_Value;

  /* Outport: '<Root>/Payload position X[m]' */
  Friction_ramp_Y.PayloadpositionXm = Friction_ramp_B.Xm;

  /* DigitalClock: '<Root>/Ramp time' */
  Friction_ramp_B.Ramptime = Friction_ramp_M->Timing.t[0];

  /* Lookup_n-D: '<Root>/Ramp profile' incorporates:
   *  DigitalClock: '<Root>/Ramp time'
   */
  Friction_ramp_B.Rampprofile = look1_binlcpw(Friction_ramp_B.Ramptime,
    Friction_ramp_cal->Rampprofile_bp01Data,
    Friction_ramp_cal->Rampprofile_tableData, 7U);

  /* Relay: '<Root>/Cutoff latch' */
  u1 = Friction_ramp_B.Xm;
  Friction_ramp_DW.Cutofflatch_Mode = ((u1 >=
    Friction_ramp_cal->Cutofflatch_OnVal) || ((!(u1 <=
    Friction_ramp_cal->Cutofflatch_OffVal)) && Friction_ramp_DW.Cutofflatch_Mode));
  if (Friction_ramp_DW.Cutofflatch_Mode) {
    /* Relay: '<Root>/Cutoff latch' */
    Friction_ramp_B.Cutofflatch = Friction_ramp_cal->Cutofflatch_YOn;
  } else {
    /* Relay: '<Root>/Cutoff latch' */
    Friction_ramp_B.Cutofflatch = Friction_ramp_cal->Cutofflatch_YOff;
  }

  /* End of Relay: '<Root>/Cutoff latch' */

  /* Switch: '<Root>/After cutoff' */
  if (Friction_ramp_B.Cutofflatch > Friction_ramp_cal->Aftercutoff_Threshold) {
    /* MinMax: '<Root>/No more lift' incorporates:
     *  Constant: '<Root>/Hold voltage'
     */
    u0 = Friction_ramp_B.Rampprofile;
    u1 = Friction_ramp_cal->Holdvoltage_Value;
    if ((u0 <= u1) || rtIsNaN(u1)) {
      u1 = u0;
    }

    /* MinMax: '<Root>/No more lift' */
    Friction_ramp_B.Nomorelift = u1;

    /* Switch: '<Root>/After cutoff' */
    Friction_ramp_B.Aftercutoff = Friction_ramp_B.Nomorelift;
  } else {
    /* Switch: '<Root>/After cutoff' */
    Friction_ramp_B.Aftercutoff = Friction_ramp_B.Rampprofile;
  }

  /* End of Switch: '<Root>/After cutoff' */

  /* Gain: '<Root>/Gain' */
  Friction_ramp_B.Gain = Friction_ramp_cal->Gain_Gain *
    Friction_ramp_B.Aftercutoff;

  /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
  u0 = Friction_ramp_B.Gain;
  u1 = Friction_ramp_cal->SaturationInput05V2_LowerSat;
  u2 = Friction_ramp_cal->SaturationInput05V2_UpperSat;
  if (u0 > u2) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
    Friction_ramp_B.u = u2;
  } else if (u0 < u1) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
    Friction_ramp_B.u = u1;
  } else {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
    Friction_ramp_B.u = u0;
  }

  /* End of Saturate: '<Root>/Saturation Input: [0, 5] V2' */

  /* Abs: '<Root>/Abs1' */
  Friction_ramp_B.Abs1 = std::abs(Friction_ramp_B.u);

  /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
  u0 = Friction_ramp_B.Abs1;
  u1 = Friction_ramp_cal->SaturationInput05V1_LowerSat;
  u2 = Friction_ramp_cal->SaturationInput05V1_UpperSat;
  if (u0 > u2) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
    Friction_ramp_B.u_c = u2;
  } else if (u0 < u1) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
    Friction_ramp_B.u_c = u1;
  } else {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
    Friction_ramp_B.u_c = u0;
  }

  /* End of Saturate: '<Root>/Saturation Input: [0, 5] V1' */

  /* Switch: '<Root>/Switch' */
  if (Friction_ramp_B.u > Friction_ramp_cal->Switch_Threshold) {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant2'
     */
    Friction_ramp_B.polarity = Friction_ramp_cal->Constant2_Value;
  } else {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    Friction_ramp_B.polarity = Friction_ramp_cal->Constant1_Value;
  }

  /* End of Switch: '<Root>/Switch' */

  /* S-Function (sg_IO183_da_s): '<Root>/Speedgoat Analog Output1' */

  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Output1' (sg_IO183_da_s) */
  {
    SimStruct *rts = Friction_ramp_M->childSfunctions[2];
    sfcnOutputs(rts,0);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Friction_ramp_M->Timing.clockTick0)) {
    ++Friction_ramp_M->Timing.clockTickH0;
  }

  Friction_ramp_M->Timing.t[0] = Friction_ramp_M->Timing.clockTick0 *
    Friction_ramp_M->Timing.stepSize0 + Friction_ramp_M->Timing.clockTickH0 *
    Friction_ramp_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Friction_ramp_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  rtsiSetSolverName(&Friction_ramp_M->solverInfo,"FixedStepDiscrete");
  Friction_ramp_M->solverInfoPtr = (&Friction_ramp_M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Friction_ramp_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    Friction_ramp_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Friction_ramp_M->Timing.sampleTimes =
      (&Friction_ramp_M->Timing.sampleTimesArray[0]);
    Friction_ramp_M->Timing.offsetTimes =
      (&Friction_ramp_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Friction_ramp_M->Timing.sampleTimes[0] = (0.0001);

    /* task offsets */
    Friction_ramp_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Friction_ramp_M, &Friction_ramp_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Friction_ramp_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Friction_ramp_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Friction_ramp_M, -1);
  Friction_ramp_M->Timing.stepSize0 = 0.0001;
  Friction_ramp_M->solverInfoPtr = (&Friction_ramp_M->solverInfo);
  Friction_ramp_M->Timing.stepSize = (0.0001);
  rtsiSetFixedStepSize(&Friction_ramp_M->solverInfo, 0.0001);
  rtsiSetSolverMode(&Friction_ramp_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  (void) std::memset((static_cast<void *>(&Friction_ramp_B)), 0,
                     sizeof(B_Friction_ramp_T));

  /* states (dwork) */
  (void) std::memset(static_cast<void *>(&Friction_ramp_DW), 0,
                     sizeof(DW_Friction_ramp_T));

  /* external outputs */
  Friction_ramp_Y.PayloadpositionXm = 0.0;

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &Friction_ramp_M->NonInlinedSFcns.sfcnInfo;
    Friction_ramp_M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(Friction_ramp_M)));
    Friction_ramp_M->Sizes.numSampTimes = (1);
    rtssSetNumRootSampTimesPtr(sfcnInfo, &Friction_ramp_M->Sizes.numSampTimes);
    Friction_ramp_M->NonInlinedSFcns.taskTimePtrs[0] = (&rtmGetTPtr
      (Friction_ramp_M)[0]);
    rtssSetTPtrPtr(sfcnInfo,Friction_ramp_M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(Friction_ramp_M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(Friction_ramp_M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput(Friction_ramp_M));
    rtssSetStepSizePtr(sfcnInfo, &Friction_ramp_M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested(Friction_ramp_M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &Friction_ramp_M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo, &Friction_ramp_M->zCCacheNeedsReset);
    rtssSetContTimeOutputInconsistentWithStateAtMajorStepPtr(sfcnInfo,
      &Friction_ramp_M->CTOutputIncnstWithState);
    rtssSetSampleHitsPtr(sfcnInfo, &Friction_ramp_M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo,
      &Friction_ramp_M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &Friction_ramp_M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &Friction_ramp_M->solverInfoPtr);
  }

  Friction_ramp_M->Sizes.numSFcns = (3);

  /* register each child */
  {
    (void) std::memset(static_cast<void *>
                       (&Friction_ramp_M->NonInlinedSFcns.childSFunctions[0]), 0,
                       3*sizeof(SimStruct));
    Friction_ramp_M->childSfunctions =
      (&Friction_ramp_M->NonInlinedSFcns.childSFunctionPtrs[0]);
    Friction_ramp_M->childSfunctions[0] =
      (&Friction_ramp_M->NonInlinedSFcns.childSFunctions[0]);
    Friction_ramp_M->childSfunctions[1] =
      (&Friction_ramp_M->NonInlinedSFcns.childSFunctions[1]);
    Friction_ramp_M->childSfunctions[2] =
      (&Friction_ramp_M->NonInlinedSFcns.childSFunctions[2]);

    /* Level2 S-Function Block: Friction_ramp/<Root>/Setup1 (sg_IO183_setup_s) */
    {
      SimStruct *rts = Friction_ramp_M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod = Friction_ramp_M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset = Friction_ramp_M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = Friction_ramp_M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) std::memset(static_cast<void*>(sfcnPeriod), 0,
                         sizeof(time_T)*1);
      (void) std::memset(static_cast<void*>(sfcnOffset), 0,
                         sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Friction_ramp_M->NonInlinedSFcns.blkInfo2[0]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Friction_ramp_M->NonInlinedSFcns.inputOutputPortInfo2[0]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Friction_ramp_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Friction_ramp_M->NonInlinedSFcns.methods2[0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Friction_ramp_M->NonInlinedSFcns.methods3[0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Friction_ramp_M->NonInlinedSFcns.methods4[0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Friction_ramp_M->NonInlinedSFcns.statesInfo2[0]);
        ssSetPeriodicStatesInfo(rts,
          &Friction_ramp_M->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* path info */
      ssSetModelName(rts, "Setup1");
      ssSetPath(rts, "Friction_ramp/Setup1");
      ssSetRTModel(rts,Friction_ramp_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Friction_ramp_M->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 11);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)Friction_ramp_cal->Setup1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)Friction_ramp_cal->Setup1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)Friction_ramp_cal->Setup1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)Friction_ramp_cal->Setup1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)Friction_ramp_cal->Setup1_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)Friction_ramp_cal->Setup1_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)Friction_ramp_cal->Setup1_P7_Size);
        ssSetSFcnParam(rts, 7, (mxArray*)Friction_ramp_cal->Setup1_P8_Size);
        ssSetSFcnParam(rts, 8, (mxArray*)Friction_ramp_cal->Setup1_P9_Size);
        ssSetSFcnParam(rts, 9, (mxArray*)Friction_ramp_cal->Setup1_P10_Size);
        ssSetSFcnParam(rts, 10, (mxArray*)Friction_ramp_cal->Setup1_P11_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &Friction_ramp_DW.Setup1_IWORK[0]);
      ssSetPWork(rts, (void **) &Friction_ramp_DW.Setup1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Friction_ramp_M->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Friction_ramp_M->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 2);

        /* IWORK */
        ssSetDWorkWidthAsInt(rts, 0, 8);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Friction_ramp_DW.Setup1_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidthAsInt(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Friction_ramp_DW.Setup1_PWORK);
      }

      /* registration */
      sg_IO183_setup_s(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.0001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCsAsInt(rts, 0);

      /* Update connectivity flags for each port */
      /* Update the BufferDstPort flags for each input port */
    }

    /* Level2 S-Function Block: Friction_ramp/<Root>/Speedgoat Analog Input1 (sg_IO183_ad_s) */
    {
      SimStruct *rts = Friction_ramp_M->childSfunctions[1];

      /* timing info */
      time_T *sfcnPeriod = Friction_ramp_M->NonInlinedSFcns.Sfcn1.sfcnPeriod;
      time_T *sfcnOffset = Friction_ramp_M->NonInlinedSFcns.Sfcn1.sfcnOffset;
      int_T *sfcnTsMap = Friction_ramp_M->NonInlinedSFcns.Sfcn1.sfcnTsMap;
      (void) std::memset(static_cast<void*>(sfcnPeriod), 0,
                         sizeof(time_T)*1);
      (void) std::memset(static_cast<void*>(sfcnOffset), 0,
                         sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Friction_ramp_M->NonInlinedSFcns.blkInfo2[1]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Friction_ramp_M->NonInlinedSFcns.inputOutputPortInfo2[1]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Friction_ramp_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Friction_ramp_M->NonInlinedSFcns.methods2[1]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Friction_ramp_M->NonInlinedSFcns.methods3[1]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Friction_ramp_M->NonInlinedSFcns.methods4[1]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Friction_ramp_M->NonInlinedSFcns.statesInfo2[1]);
        ssSetPeriodicStatesInfo(rts,
          &Friction_ramp_M->NonInlinedSFcns.periodicStatesInfo[1]);
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Friction_ramp_M->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Friction_ramp_M->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Friction_ramp_M->NonInlinedSFcns.Sfcn1.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Friction_ramp_M->NonInlinedSFcns.Sfcn1.outputPortCoSimAttribute[0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &Friction_ramp_B.SpeedgoatAnalogInput1));
        }
      }

      /* path info */
      ssSetModelName(rts, "Speedgoat Analog Input1");
      ssSetPath(rts, "Friction_ramp/Speedgoat Analog Input1");
      ssSetRTModel(rts,Friction_ramp_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Friction_ramp_M->NonInlinedSFcns.Sfcn1.params;
        ssSetSFcnParamsCount(rts, 5);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Friction_ramp_cal->SpeedgoatAnalogInput1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Friction_ramp_cal->SpeedgoatAnalogInput1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       Friction_ramp_cal->SpeedgoatAnalogInput1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       Friction_ramp_cal->SpeedgoatAnalogInput1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       Friction_ramp_cal->SpeedgoatAnalogInput1_P5_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &Friction_ramp_DW.SpeedgoatAnalogInput1_IWORK[0]);
      ssSetPWork(rts, (void **) &Friction_ramp_DW.SpeedgoatAnalogInput1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Friction_ramp_M->NonInlinedSFcns.Sfcn1.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Friction_ramp_M->NonInlinedSFcns.Sfcn1.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 2);

        /* IWORK */
        ssSetDWorkWidthAsInt(rts, 0, 5);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Friction_ramp_DW.SpeedgoatAnalogInput1_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidthAsInt(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Friction_ramp_DW.SpeedgoatAnalogInput1_PWORK);
      }

      /* registration */
      sg_IO183_ad_s(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.0001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCsAsInt(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);

      /* Update the BufferDstPort flags for each input port */
    }

    /* Level2 S-Function Block: Friction_ramp/<Root>/Speedgoat Analog Output1 (sg_IO183_da_s) */
    {
      SimStruct *rts = Friction_ramp_M->childSfunctions[2];

      /* timing info */
      time_T *sfcnPeriod = Friction_ramp_M->NonInlinedSFcns.Sfcn2.sfcnPeriod;
      time_T *sfcnOffset = Friction_ramp_M->NonInlinedSFcns.Sfcn2.sfcnOffset;
      int_T *sfcnTsMap = Friction_ramp_M->NonInlinedSFcns.Sfcn2.sfcnTsMap;
      (void) std::memset(static_cast<void*>(sfcnPeriod), 0,
                         sizeof(time_T)*1);
      (void) std::memset(static_cast<void*>(sfcnOffset), 0,
                         sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Friction_ramp_M->NonInlinedSFcns.blkInfo2[2]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Friction_ramp_M->NonInlinedSFcns.inputOutputPortInfo2[2]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Friction_ramp_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Friction_ramp_M->NonInlinedSFcns.methods2[2]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Friction_ramp_M->NonInlinedSFcns.methods3[2]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Friction_ramp_M->NonInlinedSFcns.methods4[2]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Friction_ramp_M->NonInlinedSFcns.statesInfo2[2]);
        ssSetPeriodicStatesInfo(rts,
          &Friction_ramp_M->NonInlinedSFcns.periodicStatesInfo[2]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 2);
        ssSetPortInfoForInputs(rts,
          &Friction_ramp_M->NonInlinedSFcns.Sfcn2.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts,
          &Friction_ramp_M->NonInlinedSFcns.Sfcn2.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &Friction_ramp_M->NonInlinedSFcns.Sfcn2.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        ssSetInputPortUnit(rts, 1, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &Friction_ramp_M->NonInlinedSFcns.Sfcn2.inputPortCoSimAttribute[0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);
        ssSetInputPortIsContinuousQuantity(rts, 1, 0);

        /* port 0 */
        {
          ssSetInputPortRequiredContiguous(rts, 0, 1);
          ssSetInputPortSignal(rts, 0, &Friction_ramp_B.u_c);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 1);
        }

        /* port 1 */
        {
          ssSetInputPortRequiredContiguous(rts, 1, 1);
          ssSetInputPortSignal(rts, 1, &Friction_ramp_B.polarity);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidthAsInt(rts, 1, 1);
        }
      }

      /* path info */
      ssSetModelName(rts, "Speedgoat Analog Output1");
      ssSetPath(rts, "Friction_ramp/Speedgoat Analog Output1");
      ssSetRTModel(rts,Friction_ramp_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Friction_ramp_M->NonInlinedSFcns.Sfcn2.params;
        ssSetSFcnParamsCount(rts, 7);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Friction_ramp_cal->SpeedgoatAnalogOutput1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Friction_ramp_cal->SpeedgoatAnalogOutput1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       Friction_ramp_cal->SpeedgoatAnalogOutput1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       Friction_ramp_cal->SpeedgoatAnalogOutput1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       Friction_ramp_cal->SpeedgoatAnalogOutput1_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)
                       Friction_ramp_cal->SpeedgoatAnalogOutput1_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)
                       Friction_ramp_cal->SpeedgoatAnalogOutput1_P7_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &Friction_ramp_DW.SpeedgoatAnalogOutput1_IWORK[0]);
      ssSetPWork(rts, (void **) &Friction_ramp_DW.SpeedgoatAnalogOutput1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Friction_ramp_M->NonInlinedSFcns.Sfcn2.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Friction_ramp_M->NonInlinedSFcns.Sfcn2.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 2);

        /* IWORK */
        ssSetDWorkWidthAsInt(rts, 0, 5);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Friction_ramp_DW.SpeedgoatAnalogOutput1_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidthAsInt(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Friction_ramp_DW.SpeedgoatAnalogOutput1_PWORK);
      }

      /* registration */
      sg_IO183_da_s(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.0001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCsAsInt(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetInputPortConnected(rts, 1, 1);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
      ssSetInputPortBufferDstPort(rts, 1, -1);
    }
  }

  /* Start for S-Function (sg_IO183_setup_s): '<Root>/Setup1' */
  /* Level2 S-Function Block: '<Root>/Setup1' (sg_IO183_setup_s) */
  {
    SimStruct *rts = Friction_ramp_M->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (sg_IO183_ad_s): '<Root>/Speedgoat Analog Input1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Input1' (sg_IO183_ad_s) */
  {
    SimStruct *rts = Friction_ramp_M->childSfunctions[1];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (sg_IO183_da_s): '<Root>/Speedgoat Analog Output1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Output1' (sg_IO183_da_s) */
  {
    SimStruct *rts = Friction_ramp_M->childSfunctions[2];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* SystemInitialize for MATLAB Function: '<S1>/BAW033k' */
  Friction_ramp_DW.sfEvent = Friction_ramp_CALL_EVENT;
}

/* Model terminate function */
void Friction_ramp_terminate(void)
{
  /* Terminate for S-Function (sg_IO183_setup_s): '<Root>/Setup1' */
  /* Level2 S-Function Block: '<Root>/Setup1' (sg_IO183_setup_s) */
  {
    SimStruct *rts = Friction_ramp_M->childSfunctions[0];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_IO183_ad_s): '<Root>/Speedgoat Analog Input1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Input1' (sg_IO183_ad_s) */
  {
    SimStruct *rts = Friction_ramp_M->childSfunctions[1];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_IO183_da_s): '<Root>/Speedgoat Analog Output1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Output1' (sg_IO183_da_s) */
  {
    SimStruct *rts = Friction_ramp_M->childSfunctions[2];
    sfcnTerminate(rts);
  }
}
