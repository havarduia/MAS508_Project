/*
 * Project_IOinterface.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Project_IOinterface".
 *
 * Model version              : 15.9
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C++ source code generated on : Wed Oct 21 15:49:57 2026
 *
 * Target selection: speedgoat.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Project_IOinterface.h"
#include "rtwtypes.h"
#include "Project_IOinterface_cal.h"
#include <cmath>
#include "Project_IOinterface_private.h"
#include <cstring>

extern "C"
{

#include "rt_nonfinite.h"

}

/* Named constants for MATLAB Function: '<S1>/BAW033k' */
const int32_T Project_IOinterface_CALL_EVENT = -1;

/* Block signals (default storage) */
B_Project_IOinterface_T Project_IOinterface_B;

/* Block states (default storage) */
DW_Project_IOinterface_T Project_IOinterface_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Project_IOinterface_T Project_IOinterface_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Project_IOinterface_T Project_IOinterface_Y;

/* Real-time model */
RT_MODEL_Project_IOinterface_T Project_IOinterface_M_ =
  RT_MODEL_Project_IOinterface_T();
RT_MODEL_Project_IOinterface_T *const Project_IOinterface_M =
  &Project_IOinterface_M_;

/* Model step function */
void Project_IOinterface_step(void)
{
  real_T u0;
  real_T u1;
  real_T u2;

  /* S-Function (sg_IO183_setup_s): '<Root>/Setup1' */

  /* Level2 S-Function Block: '<Root>/Setup1' (sg_IO183_setup_s) */
  {
    SimStruct *rts = Project_IOinterface_M->childSfunctions[0];
    sfcnOutputs(rts,0);
  }

  /* S-Function (sg_IO183_ad_s): '<Root>/Speedgoat Analog Input1' */

  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Input1' (sg_IO183_ad_s) */
  {
    SimStruct *rts = Project_IOinterface_M->childSfunctions[1];
    sfcnOutputs(rts,0);
  }

  /* MATLAB Function: '<S1>/BAW033k' */
  Project_IOinterface_DW.sfEvent = Project_IOinterface_CALL_EVENT;
  Project_IOinterface_B.y = 0.004 * Project_IOinterface_B.SpeedgoatAnalogInput1;

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<Root>/Initial Payload PositionX0[m] '
   */
  Project_IOinterface_B.Xm = Project_IOinterface_B.y -
    Project_IOinterface_cal->InitialPayloadPositionX0m_Value;

  /* Outport: '<Root>/Payload position X[m]' */
  Project_IOinterface_Y.PayloadpositionXm = Project_IOinterface_B.Xm;

  /* Gain: '<Root>/Gain' incorporates:
   *  Constant: '<Root>/Constant'
   */
  Project_IOinterface_B.Gain = Project_IOinterface_cal->Gain_Gain *
    Project_IOinterface_cal->Constant_Value;

  /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
  u0 = Project_IOinterface_B.Gain;
  u1 = Project_IOinterface_cal->SaturationInput05V2_LowerSat;
  u2 = Project_IOinterface_cal->SaturationInput05V2_UpperSat;
  if (u0 > u2) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
    Project_IOinterface_B.u = u2;
  } else if (u0 < u1) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
    Project_IOinterface_B.u = u1;
  } else {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
    Project_IOinterface_B.u = u0;
  }

  /* End of Saturate: '<Root>/Saturation Input: [0, 5] V2' */

  /* Abs: '<Root>/Abs1' */
  Project_IOinterface_B.Abs1 = std::abs(Project_IOinterface_B.u);

  /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
  u0 = Project_IOinterface_B.Abs1;
  u1 = Project_IOinterface_cal->SaturationInput05V1_LowerSat;
  u2 = Project_IOinterface_cal->SaturationInput05V1_UpperSat;
  if (u0 > u2) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
    Project_IOinterface_B.u_c = u2;
  } else if (u0 < u1) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
    Project_IOinterface_B.u_c = u1;
  } else {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
    Project_IOinterface_B.u_c = u0;
  }

  /* End of Saturate: '<Root>/Saturation Input: [0, 5] V1' */

  /* Switch: '<Root>/Switch' */
  if (Project_IOinterface_B.u > Project_IOinterface_cal->Switch_Threshold) {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant2'
     */
    Project_IOinterface_B.polarity = Project_IOinterface_cal->Constant2_Value;
  } else {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    Project_IOinterface_B.polarity = Project_IOinterface_cal->Constant1_Value;
  }

  /* End of Switch: '<Root>/Switch' */

  /* S-Function (sg_IO183_da_s): '<Root>/Speedgoat Analog Output1' */

  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Output1' (sg_IO183_da_s) */
  {
    SimStruct *rts = Project_IOinterface_M->childSfunctions[2];
    sfcnOutputs(rts,0);
  }

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  Project_IOinterface_B.PulseGenerator =
    (Project_IOinterface_DW.clockTickCounter <
     Project_IOinterface_cal->PulseGenerator_Duty) &&
    (Project_IOinterface_DW.clockTickCounter >= 0) ?
    Project_IOinterface_cal->PulseGenerator_Amp : 0.0;

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  if (Project_IOinterface_DW.clockTickCounter >=
      Project_IOinterface_cal->PulseGenerator_Period - 1.0) {
    Project_IOinterface_DW.clockTickCounter = 0;
  } else {
    Project_IOinterface_DW.clockTickCounter++;
  }

  /* Sum: '<Root>/Sum1' */
  Project_IOinterface_B.Sum1 = Project_IOinterface_B.PulseGenerator;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Project_IOinterface_M->Timing.clockTick0)) {
    ++Project_IOinterface_M->Timing.clockTickH0;
  }

  Project_IOinterface_M->Timing.t[0] = Project_IOinterface_M->Timing.clockTick0 *
    Project_IOinterface_M->Timing.stepSize0 +
    Project_IOinterface_M->Timing.clockTickH0 *
    Project_IOinterface_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Project_IOinterface_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  rtsiSetSolverName(&Project_IOinterface_M->solverInfo,"FixedStepDiscrete");
  Project_IOinterface_M->solverInfoPtr = (&Project_IOinterface_M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Project_IOinterface_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    Project_IOinterface_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Project_IOinterface_M->Timing.sampleTimes =
      (&Project_IOinterface_M->Timing.sampleTimesArray[0]);
    Project_IOinterface_M->Timing.offsetTimes =
      (&Project_IOinterface_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Project_IOinterface_M->Timing.sampleTimes[0] = (0.0001);

    /* task offsets */
    Project_IOinterface_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Project_IOinterface_M, &Project_IOinterface_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Project_IOinterface_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Project_IOinterface_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Project_IOinterface_M, -1);
  Project_IOinterface_M->Timing.stepSize0 = 0.0001;
  Project_IOinterface_M->solverInfoPtr = (&Project_IOinterface_M->solverInfo);
  Project_IOinterface_M->Timing.stepSize = (0.0001);
  rtsiSetFixedStepSize(&Project_IOinterface_M->solverInfo, 0.0001);
  rtsiSetSolverMode(&Project_IOinterface_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  (void) std::memset((static_cast<void *>(&Project_IOinterface_B)), 0,
                     sizeof(B_Project_IOinterface_T));

  /* states (dwork) */
  (void) std::memset(static_cast<void *>(&Project_IOinterface_DW), 0,
                     sizeof(DW_Project_IOinterface_T));

  /* external inputs */
  Project_IOinterface_U.U = 0.0;

  /* external outputs */
  Project_IOinterface_Y.PayloadpositionXm = 0.0;

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &Project_IOinterface_M->NonInlinedSFcns.sfcnInfo;
    Project_IOinterface_M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(Project_IOinterface_M)));
    Project_IOinterface_M->Sizes.numSampTimes = (1);
    rtssSetNumRootSampTimesPtr(sfcnInfo,
      &Project_IOinterface_M->Sizes.numSampTimes);
    Project_IOinterface_M->NonInlinedSFcns.taskTimePtrs[0] = (&rtmGetTPtr
      (Project_IOinterface_M)[0]);
    rtssSetTPtrPtr(sfcnInfo,Project_IOinterface_M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(Project_IOinterface_M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(Project_IOinterface_M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput
      (Project_IOinterface_M));
    rtssSetStepSizePtr(sfcnInfo, &Project_IOinterface_M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested(Project_IOinterface_M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &Project_IOinterface_M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo,
      &Project_IOinterface_M->zCCacheNeedsReset);
    rtssSetContTimeOutputInconsistentWithStateAtMajorStepPtr(sfcnInfo,
      &Project_IOinterface_M->CTOutputIncnstWithState);
    rtssSetSampleHitsPtr(sfcnInfo, &Project_IOinterface_M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo,
      &Project_IOinterface_M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &Project_IOinterface_M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &Project_IOinterface_M->solverInfoPtr);
  }

  Project_IOinterface_M->Sizes.numSFcns = (3);

  /* register each child */
  {
    (void) std::memset(static_cast<void *>
                       (&Project_IOinterface_M->NonInlinedSFcns.childSFunctions
                        [0]), 0,
                       3*sizeof(SimStruct));
    Project_IOinterface_M->childSfunctions =
      (&Project_IOinterface_M->NonInlinedSFcns.childSFunctionPtrs[0]);
    Project_IOinterface_M->childSfunctions[0] =
      (&Project_IOinterface_M->NonInlinedSFcns.childSFunctions[0]);
    Project_IOinterface_M->childSfunctions[1] =
      (&Project_IOinterface_M->NonInlinedSFcns.childSFunctions[1]);
    Project_IOinterface_M->childSfunctions[2] =
      (&Project_IOinterface_M->NonInlinedSFcns.childSFunctions[2]);

    /* Level2 S-Function Block: Project_IOinterface/<Root>/Setup1 (sg_IO183_setup_s) */
    {
      SimStruct *rts = Project_IOinterface_M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod =
        Project_IOinterface_M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset =
        Project_IOinterface_M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = Project_IOinterface_M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) std::memset(static_cast<void*>(sfcnPeriod), 0,
                         sizeof(time_T)*1);
      (void) std::memset(static_cast<void*>(sfcnOffset), 0,
                         sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Project_IOinterface_M->NonInlinedSFcns.blkInfo2[0]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Project_IOinterface_M->NonInlinedSFcns.inputOutputPortInfo2[0]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Project_IOinterface_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Project_IOinterface_M->
                           NonInlinedSFcns.methods2[0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Project_IOinterface_M->
                           NonInlinedSFcns.methods3[0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Project_IOinterface_M->
                           NonInlinedSFcns.methods4[0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &Project_IOinterface_M->NonInlinedSFcns.statesInfo2[0]);
        ssSetPeriodicStatesInfo(rts,
          &Project_IOinterface_M->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* path info */
      ssSetModelName(rts, "Setup1");
      ssSetPath(rts, "Project_IOinterface/Setup1");
      ssSetRTModel(rts,Project_IOinterface_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 11);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)Project_IOinterface_cal->Setup1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)Project_IOinterface_cal->Setup1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)Project_IOinterface_cal->Setup1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)Project_IOinterface_cal->Setup1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)Project_IOinterface_cal->Setup1_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)Project_IOinterface_cal->Setup1_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)Project_IOinterface_cal->Setup1_P7_Size);
        ssSetSFcnParam(rts, 7, (mxArray*)Project_IOinterface_cal->Setup1_P8_Size);
        ssSetSFcnParam(rts, 8, (mxArray*)Project_IOinterface_cal->Setup1_P9_Size);
        ssSetSFcnParam(rts, 9, (mxArray*)
                       Project_IOinterface_cal->Setup1_P10_Size);
        ssSetSFcnParam(rts, 10, (mxArray*)
                       Project_IOinterface_cal->Setup1_P11_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &Project_IOinterface_DW.Setup1_IWORK[0]);
      ssSetPWork(rts, (void **) &Project_IOinterface_DW.Setup1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 2);

        /* IWORK */
        ssSetDWorkWidthAsInt(rts, 0, 8);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Project_IOinterface_DW.Setup1_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidthAsInt(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Project_IOinterface_DW.Setup1_PWORK);
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

    /* Level2 S-Function Block: Project_IOinterface/<Root>/Speedgoat Analog Input1 (sg_IO183_ad_s) */
    {
      SimStruct *rts = Project_IOinterface_M->childSfunctions[1];

      /* timing info */
      time_T *sfcnPeriod =
        Project_IOinterface_M->NonInlinedSFcns.Sfcn1.sfcnPeriod;
      time_T *sfcnOffset =
        Project_IOinterface_M->NonInlinedSFcns.Sfcn1.sfcnOffset;
      int_T *sfcnTsMap = Project_IOinterface_M->NonInlinedSFcns.Sfcn1.sfcnTsMap;
      (void) std::memset(static_cast<void*>(sfcnPeriod), 0,
                         sizeof(time_T)*1);
      (void) std::memset(static_cast<void*>(sfcnOffset), 0,
                         sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Project_IOinterface_M->NonInlinedSFcns.blkInfo2[1]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Project_IOinterface_M->NonInlinedSFcns.inputOutputPortInfo2[1]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Project_IOinterface_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Project_IOinterface_M->
                           NonInlinedSFcns.methods2[1]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Project_IOinterface_M->
                           NonInlinedSFcns.methods3[1]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Project_IOinterface_M->
                           NonInlinedSFcns.methods4[1]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &Project_IOinterface_M->NonInlinedSFcns.statesInfo2[1]);
        ssSetPeriodicStatesInfo(rts,
          &Project_IOinterface_M->NonInlinedSFcns.periodicStatesInfo[1]);
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn1.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Project_IOinterface_M->
          NonInlinedSFcns.Sfcn1.outputPortCoSimAttribute[0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &Project_IOinterface_B.SpeedgoatAnalogInput1));
        }
      }

      /* path info */
      ssSetModelName(rts, "Speedgoat Analog Input1");
      ssSetPath(rts, "Project_IOinterface/Speedgoat Analog Input1");
      ssSetRTModel(rts,Project_IOinterface_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn1.params;
        ssSetSFcnParamsCount(rts, 5);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Project_IOinterface_cal->SpeedgoatAnalogInput1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Project_IOinterface_cal->SpeedgoatAnalogInput1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       Project_IOinterface_cal->SpeedgoatAnalogInput1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       Project_IOinterface_cal->SpeedgoatAnalogInput1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       Project_IOinterface_cal->SpeedgoatAnalogInput1_P5_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *)
                 &Project_IOinterface_DW.SpeedgoatAnalogInput1_IWORK[0]);
      ssSetPWork(rts, (void **)
                 &Project_IOinterface_DW.SpeedgoatAnalogInput1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn1.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn1.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 2);

        /* IWORK */
        ssSetDWorkWidthAsInt(rts, 0, 5);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Project_IOinterface_DW.SpeedgoatAnalogInput1_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidthAsInt(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Project_IOinterface_DW.SpeedgoatAnalogInput1_PWORK);
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

    /* Level2 S-Function Block: Project_IOinterface/<Root>/Speedgoat Analog Output1 (sg_IO183_da_s) */
    {
      SimStruct *rts = Project_IOinterface_M->childSfunctions[2];

      /* timing info */
      time_T *sfcnPeriod =
        Project_IOinterface_M->NonInlinedSFcns.Sfcn2.sfcnPeriod;
      time_T *sfcnOffset =
        Project_IOinterface_M->NonInlinedSFcns.Sfcn2.sfcnOffset;
      int_T *sfcnTsMap = Project_IOinterface_M->NonInlinedSFcns.Sfcn2.sfcnTsMap;
      (void) std::memset(static_cast<void*>(sfcnPeriod), 0,
                         sizeof(time_T)*1);
      (void) std::memset(static_cast<void*>(sfcnOffset), 0,
                         sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Project_IOinterface_M->NonInlinedSFcns.blkInfo2[2]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Project_IOinterface_M->NonInlinedSFcns.inputOutputPortInfo2[2]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Project_IOinterface_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Project_IOinterface_M->
                           NonInlinedSFcns.methods2[2]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Project_IOinterface_M->
                           NonInlinedSFcns.methods3[2]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Project_IOinterface_M->
                           NonInlinedSFcns.methods4[2]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &Project_IOinterface_M->NonInlinedSFcns.statesInfo2[2]);
        ssSetPeriodicStatesInfo(rts,
          &Project_IOinterface_M->NonInlinedSFcns.periodicStatesInfo[2]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 2);
        ssSetPortInfoForInputs(rts,
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn2.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts,
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn2.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn2.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        ssSetInputPortUnit(rts, 1, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn2.inputPortCoSimAttribute
          [0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);
        ssSetInputPortIsContinuousQuantity(rts, 1, 0);

        /* port 0 */
        {
          ssSetInputPortRequiredContiguous(rts, 0, 1);
          ssSetInputPortSignal(rts, 0, &Project_IOinterface_B.u_c);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 1);
        }

        /* port 1 */
        {
          ssSetInputPortRequiredContiguous(rts, 1, 1);
          ssSetInputPortSignal(rts, 1, &Project_IOinterface_B.polarity);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidthAsInt(rts, 1, 1);
        }
      }

      /* path info */
      ssSetModelName(rts, "Speedgoat Analog Output1");
      ssSetPath(rts, "Project_IOinterface/Speedgoat Analog Output1");
      ssSetRTModel(rts,Project_IOinterface_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn2.params;
        ssSetSFcnParamsCount(rts, 7);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Project_IOinterface_cal->SpeedgoatAnalogOutput1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Project_IOinterface_cal->SpeedgoatAnalogOutput1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       Project_IOinterface_cal->SpeedgoatAnalogOutput1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       Project_IOinterface_cal->SpeedgoatAnalogOutput1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       Project_IOinterface_cal->SpeedgoatAnalogOutput1_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)
                       Project_IOinterface_cal->SpeedgoatAnalogOutput1_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)
                       Project_IOinterface_cal->SpeedgoatAnalogOutput1_P7_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *)
                 &Project_IOinterface_DW.SpeedgoatAnalogOutput1_IWORK[0]);
      ssSetPWork(rts, (void **)
                 &Project_IOinterface_DW.SpeedgoatAnalogOutput1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn2.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Project_IOinterface_M->NonInlinedSFcns.Sfcn2.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 2);

        /* IWORK */
        ssSetDWorkWidthAsInt(rts, 0, 5);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Project_IOinterface_DW.SpeedgoatAnalogOutput1_IWORK
                   [0]);

        /* PWORK */
        ssSetDWorkWidthAsInt(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Project_IOinterface_DW.SpeedgoatAnalogOutput1_PWORK);
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
    SimStruct *rts = Project_IOinterface_M->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (sg_IO183_ad_s): '<Root>/Speedgoat Analog Input1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Input1' (sg_IO183_ad_s) */
  {
    SimStruct *rts = Project_IOinterface_M->childSfunctions[1];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (sg_IO183_da_s): '<Root>/Speedgoat Analog Output1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Output1' (sg_IO183_da_s) */
  {
    SimStruct *rts = Project_IOinterface_M->childSfunctions[2];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for DiscretePulseGenerator: '<Root>/Pulse Generator' */
  Project_IOinterface_DW.clockTickCounter = -20000;

  /* SystemInitialize for MATLAB Function: '<S1>/BAW033k' */
  Project_IOinterface_DW.sfEvent = Project_IOinterface_CALL_EVENT;
}

/* Model terminate function */
void Project_IOinterface_terminate(void)
{
  /* Terminate for S-Function (sg_IO183_setup_s): '<Root>/Setup1' */
  /* Level2 S-Function Block: '<Root>/Setup1' (sg_IO183_setup_s) */
  {
    SimStruct *rts = Project_IOinterface_M->childSfunctions[0];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_IO183_ad_s): '<Root>/Speedgoat Analog Input1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Input1' (sg_IO183_ad_s) */
  {
    SimStruct *rts = Project_IOinterface_M->childSfunctions[1];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_IO183_da_s): '<Root>/Speedgoat Analog Output1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Output1' (sg_IO183_da_s) */
  {
    SimStruct *rts = Project_IOinterface_M->childSfunctions[2];
    sfcnTerminate(rts);
  }
}
