/*
 * Driver_test.cpp
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

#include "Driver_test.h"
#include "rtwtypes.h"
#include "Driver_test_cal.h"
#include "rte_Driver_test_parameters.h"
#include <cmath>
#include "Driver_test_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include <cstring>

/* Named constants for MATLAB Function: '<S1>/schedule' */
const int32_T Driver_test_CALL_EVENT = -1;

/* Block signals (default storage) */
B_Driver_test_T Driver_test_B;

/* Block states (default storage) */
DW_Driver_test_T Driver_test_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Driver_test_T Driver_test_Y;

/* Real-time model */
RT_MODEL_Driver_test_T Driver_test_M_ = RT_MODEL_Driver_test_T();
RT_MODEL_Driver_test_T *const Driver_test_M = &Driver_test_M_;
real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = std::abs(u0);
    tmp_0 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = (rtNaN);
    } else {
      y = std::pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void Driver_test_step(void)
{
  real_T xnew[5];
  real_T Observer;
  real_T clock_tmp;
  real_T k;
  int_T i;
  int_T j;
  static const real_T b[18] = { 0.4, 0.05, 0.5, -0.05, 0.6, -0.1, 0.8, -0.2, 1.0,
    -0.3, 1.3, -0.5, 1.6, -0.8, 2.0, -1.2, 0.3, 0.1 };

  real_T tmp_0;
  real_T tmp_1;
  real_T *tmp;

  /* Sum: '<S3>/minus bias' incorporates:
   *  Constant: '<S3>/vBias'
   */
  tmp_1 = *get_vBias();

  /* Saturate: '<S3>/limit' */
  tmp_0 = *get_vMax();

  /* Update for DiscreteStateSpace: '<S3>/Observer' */
  tmp = get_Bo();

  /* S-Function (sg_IO183_setup_s): '<Root>/Setup1' */

  /* Level2 S-Function Block: '<Root>/Setup1' (sg_IO183_setup_s) */
  {
    SimStruct *rts = Driver_test_M->childSfunctions[0];
    sfcnOutputs(rts,0);
  }

  /* S-Function (sg_IO183_ad_s): '<Root>/Speedgoat Analog Input1' */

  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Input1' (sg_IO183_ad_s) */
  {
    SimStruct *rts = Driver_test_M->childSfunctions[1];
    sfcnOutputs(rts,0);
  }

  /* MATLAB Function: '<S2>/BAW033k' */
  Driver_test_DW.sfEvent = Driver_test_CALL_EVENT;
  Driver_test_B.y = 0.004 * Driver_test_B.SpeedgoatAnalogInput1;

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<Root>/Initial Payload PositionX0[m] '
   */
  Driver_test_B.Xm = Driver_test_B.y -
    Driver_test_cal->InitialPayloadPositionX0m_Value;

  /* Outport: '<Root>/Payload position X[m]' */
  Driver_test_Y.PayloadpositionXm = Driver_test_B.Xm;

  /* DigitalClock: '<S1>/clock' incorporates:
   *  DigitalClock: '<S3>/clock'
   */
  clock_tmp = Driver_test_M->Timing.t[0];

  /* DigitalClock: '<S1>/clock' */
  Driver_test_B.clock = clock_tmp;

  /* MATLAB Function: '<S1>/schedule' */
  Driver_test_DW.sfEvent_f = Driver_test_CALL_EVENT;
  Driver_test_B.rCtrl = 0.012;
  Driver_test_B.active = 0.0;
  Driver_test_B.vStep = 0.0;
  k = std::floor((Driver_test_B.clock - 6.0) / 3.4);
  if ((!(Driver_test_B.clock < 6.0)) && (!(k >= 18.0))) {
    if (k != Driver_test_DW.lastK) {
      Driver_test_DW.aborted = false;
      Driver_test_DW.lastK = k;
    }

    if ((Driver_test_B.clock - 6.0) - k * 3.4 >= 3.0) {
      Driver_test_DW.aborted = ((Driver_test_B.Xm < 0.003) || (Driver_test_B.Xm >
        0.021) || Driver_test_DW.aborted);
      if (!Driver_test_DW.aborted) {
        Driver_test_B.active = 1.0;
        Driver_test_B.vStep = b[static_cast<int32_T>(k + 1.0) - 1];
        Driver_test_B.rCtrl = Driver_test_B.Xm;
      }
    }
  }

  /* End of MATLAB Function: '<S1>/schedule' */

  /* DiscreteIntegrator: '<S3>/xN' */
  Driver_test_B.xN = Driver_test_DW.xN_DSTATE;

  /* Gain: '<S3>/Ke' */
  Driver_test_B.Ke_d = *get_Ke() * Driver_test_B.xN;

  /* Gain: '<S3>/K' */
  k = 0.0;
  for (i = 0; i < 5; i++) {
    /* DiscreteStateSpace: '<S3>/Observer' */
    Observer = 0.0;
    for (j = 0; j < 5; j++) {
      Observer += Driver_test_cal->Observer_C[5 * j + i] *
        Driver_test_DW.Observer_DSTATE[j];
    }

    /* DiscreteStateSpace: '<S3>/Observer' */
    Driver_test_B.Observer[i] = Observer;

    /* Gain: '<S3>/K' */
    k += (get_K())[i] * Observer;
  }

  /* Gain: '<S3>/K' */
  Driver_test_B.K_h = k;

  /* DigitalClock: '<S3>/clock' */
  Driver_test_B.clock_f = clock_tmp;

  /* Bias: '<S3>/time since tExc' */
  k = -*get_tExc();

  /* Bias: '<S3>/time since tExc' */
  Driver_test_B.timesincetExc = Driver_test_B.clock_f + k;

  /* Fcn: '<S3>/chirp' */
  k = Driver_test_B.timesincetExc;
  k = rt_powd_snf(k, 2.0);

  /* Fcn: '<S3>/chirp' */
  Driver_test_B.chirp = static_cast<real_T>(Driver_test_B.timesincetExc > 0.0) *
    0.5 * static_cast<real_T>(Driver_test_B.timesincetExc < 60.0) * std::sin
    ((0.3 * Driver_test_B.timesincetExc + 0.16416666666666666 * k) *
     6.2831853071795862);

  /* Sum: '<S3>/uCmd' */
  Driver_test_B.uCmd = (Driver_test_B.Ke_d - Driver_test_B.K_h) +
    Driver_test_B.chirp;

  /* Sum: '<S3>/plus bias' incorporates:
   *  Constant: '<S3>/vBias'
   */
  Driver_test_B.plusbias = Driver_test_B.uCmd + tmp_1;

  /* Saturate: '<S3>/limit' */
  k = -tmp_0;
  clock_tmp = Driver_test_B.plusbias;
  Observer = tmp_0;
  if (clock_tmp > Observer) {
    /* Saturate: '<S3>/limit' */
    Driver_test_B.limit = Observer;
  } else if (clock_tmp < k) {
    /* Saturate: '<S3>/limit' */
    Driver_test_B.limit = k;
  } else {
    /* Saturate: '<S3>/limit' */
    Driver_test_B.limit = clock_tmp;
  }

  /* Switch: '<S1>/step or control' */
  if (Driver_test_B.active > Driver_test_cal->steporcontrol_Threshold) {
    /* Switch: '<S1>/step or control' */
    Driver_test_B.steporcontrol = Driver_test_B.vStep;
  } else {
    /* Switch: '<S1>/step or control' */
    Driver_test_B.steporcontrol = Driver_test_B.limit;
  }

  /* End of Switch: '<S1>/step or control' */

  /* Gain: '<Root>/Gain' */
  Driver_test_B.Gain = Driver_test_cal->Gain_Gain * Driver_test_B.steporcontrol;

  /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
  clock_tmp = Driver_test_B.Gain;
  k = Driver_test_cal->SaturationInput05V2_LowerSat;
  Observer = Driver_test_cal->SaturationInput05V2_UpperSat;
  if (clock_tmp > Observer) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
    Driver_test_B.u = Observer;
  } else if (clock_tmp < k) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
    Driver_test_B.u = k;
  } else {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
    Driver_test_B.u = clock_tmp;
  }

  /* End of Saturate: '<Root>/Saturation Input: [0, 5] V2' */

  /* Abs: '<Root>/Abs1' */
  Driver_test_B.Abs1 = std::abs(Driver_test_B.u);

  /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
  clock_tmp = Driver_test_B.Abs1;
  k = Driver_test_cal->SaturationInput05V1_LowerSat;
  Observer = Driver_test_cal->SaturationInput05V1_UpperSat;
  if (clock_tmp > Observer) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
    Driver_test_B.u_c = Observer;
  } else if (clock_tmp < k) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
    Driver_test_B.u_c = k;
  } else {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
    Driver_test_B.u_c = clock_tmp;
  }

  /* End of Saturate: '<Root>/Saturation Input: [0, 5] V1' */

  /* Switch: '<Root>/Switch' */
  if (Driver_test_B.u > Driver_test_cal->Switch_Threshold) {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant2'
     */
    Driver_test_B.polarity = Driver_test_cal->Constant2_Value;
  } else {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    Driver_test_B.polarity = Driver_test_cal->Constant1_Value;
  }

  /* End of Switch: '<Root>/Switch' */

  /* S-Function (sg_IO183_da_s): '<Root>/Speedgoat Analog Output1' */

  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Output1' (sg_IO183_da_s) */
  {
    SimStruct *rts = Driver_test_M->childSfunctions[2];
    sfcnOutputs(rts,0);
  }

  /* Sum: '<S3>/error' */
  Driver_test_B.error = Driver_test_B.rCtrl - Driver_test_B.Xm;

  /* Sum: '<S3>/minus bias' incorporates:
   *  Constant: '<S3>/vBias'
   */
  Driver_test_B.minusbias = Driver_test_B.limit - tmp_1;

  /* SignalConversion generated from: '<S3>/Observer' */
  Driver_test_B.TmpSignalConversionAtObserverIn[0] = Driver_test_B.minusbias;
  Driver_test_B.TmpSignalConversionAtObserverIn[1] = Driver_test_B.Xm;

  /* RelationalOperator: '<S3>/saturated' */
  Driver_test_B.saturated = (Driver_test_B.plusbias != Driver_test_B.limit);

  /* Signum: '<S3>/sign e' */
  clock_tmp = Driver_test_B.error;
  if (rtIsNaN(clock_tmp)) {
    /* Signum: '<S3>/sign e' */
    Driver_test_B.signe = (rtNaN);
  } else if (clock_tmp < 0.0) {
    /* Signum: '<S3>/sign e' */
    Driver_test_B.signe = -1.0;
  } else {
    /* Signum: '<S3>/sign e' */
    Driver_test_B.signe = (clock_tmp > 0.0);
  }

  /* End of Signum: '<S3>/sign e' */

  /* Signum: '<S3>/sign u' */
  clock_tmp = Driver_test_B.uCmd;
  if (rtIsNaN(clock_tmp)) {
    /* Signum: '<S3>/sign u' */
    Driver_test_B.signu = (rtNaN);
  } else if (clock_tmp < 0.0) {
    /* Signum: '<S3>/sign u' */
    Driver_test_B.signu = -1.0;
  } else {
    /* Signum: '<S3>/sign u' */
    Driver_test_B.signu = (clock_tmp > 0.0);
  }

  /* End of Signum: '<S3>/sign u' */

  /* Product: '<S3>/sign product' */
  Driver_test_B.signproduct = Driver_test_B.signe * Driver_test_B.signu;

  /* RelationalOperator: '<S5>/Compare' incorporates:
   *  Constant: '<S5>/Constant'
   */
  Driver_test_B.Compare = (Driver_test_B.signproduct >
    Driver_test_cal->samesign_const);

  /* Logic: '<S3>/integrate' */
  Driver_test_B.integrate = ((!Driver_test_B.saturated) ||
    (!Driver_test_B.Compare));

  /* Switch: '<S3>/anti-windup' */
  if (Driver_test_B.integrate) {
    /* Switch: '<S3>/anti-windup' */
    Driver_test_B.antiwindup = Driver_test_B.error;
  } else {
    /* Switch: '<S3>/anti-windup' incorporates:
     *  Constant: '<S3>/zero'
     */
    Driver_test_B.antiwindup = Driver_test_cal->zero_Value;
  }

  /* End of Switch: '<S3>/anti-windup' */

  /* Update for DiscreteIntegrator: '<S3>/xN' */
  Driver_test_DW.xN_DSTATE += Driver_test_cal->xN_gainval *
    Driver_test_B.antiwindup;

  /* Update for DiscreteStateSpace: '<S3>/Observer' */
  for (i = 0; i < 5; i++) {
    clock_tmp = 0.0;
    for (j = 0; j < 5; j++) {
      clock_tmp += (get_Ao())[5 * j + i] * Driver_test_DW.Observer_DSTATE[j];
    }

    clock_tmp += tmp[i] * Driver_test_B.TmpSignalConversionAtObserverIn[0];
    clock_tmp += tmp[i + 5] * Driver_test_B.TmpSignalConversionAtObserverIn[1];
    xnew[i] = clock_tmp;
  }

  for (i = 0; i < 5; i++) {
    Driver_test_DW.Observer_DSTATE[i] = xnew[i];
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
  if (!(++Driver_test_M->Timing.clockTick0)) {
    ++Driver_test_M->Timing.clockTickH0;
  }

  Driver_test_M->Timing.t[0] = Driver_test_M->Timing.clockTick0 *
    Driver_test_M->Timing.stepSize0 + Driver_test_M->Timing.clockTickH0 *
    Driver_test_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Driver_test_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  rtsiSetSolverName(&Driver_test_M->solverInfo,"FixedStepDiscrete");
  Driver_test_M->solverInfoPtr = (&Driver_test_M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Driver_test_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    Driver_test_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Driver_test_M->Timing.sampleTimes = (&Driver_test_M->
      Timing.sampleTimesArray[0]);
    Driver_test_M->Timing.offsetTimes = (&Driver_test_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    Driver_test_M->Timing.sampleTimes[0] = (0.0001);

    /* task offsets */
    Driver_test_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Driver_test_M, &Driver_test_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Driver_test_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Driver_test_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Driver_test_M, -1);
  Driver_test_M->Timing.stepSize0 = 0.0001;
  Driver_test_M->solverInfoPtr = (&Driver_test_M->solverInfo);
  Driver_test_M->Timing.stepSize = (0.0001);
  rtsiSetFixedStepSize(&Driver_test_M->solverInfo, 0.0001);
  rtsiSetSolverMode(&Driver_test_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  (void) std::memset((static_cast<void *>(&Driver_test_B)), 0,
                     sizeof(B_Driver_test_T));

  /* states (dwork) */
  (void) std::memset(static_cast<void *>(&Driver_test_DW), 0,
                     sizeof(DW_Driver_test_T));

  /* external outputs */
  Driver_test_Y.PayloadpositionXm = 0.0;

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &Driver_test_M->NonInlinedSFcns.sfcnInfo;
    Driver_test_M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(Driver_test_M)));
    Driver_test_M->Sizes.numSampTimes = (1);
    rtssSetNumRootSampTimesPtr(sfcnInfo, &Driver_test_M->Sizes.numSampTimes);
    Driver_test_M->NonInlinedSFcns.taskTimePtrs[0] = (&rtmGetTPtr(Driver_test_M)
      [0]);
    rtssSetTPtrPtr(sfcnInfo,Driver_test_M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(Driver_test_M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(Driver_test_M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput(Driver_test_M));
    rtssSetStepSizePtr(sfcnInfo, &Driver_test_M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested(Driver_test_M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &Driver_test_M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo, &Driver_test_M->zCCacheNeedsReset);
    rtssSetContTimeOutputInconsistentWithStateAtMajorStepPtr(sfcnInfo,
      &Driver_test_M->CTOutputIncnstWithState);
    rtssSetSampleHitsPtr(sfcnInfo, &Driver_test_M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo,
      &Driver_test_M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &Driver_test_M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &Driver_test_M->solverInfoPtr);
  }

  Driver_test_M->Sizes.numSFcns = (3);

  /* register each child */
  {
    (void) std::memset(static_cast<void *>
                       (&Driver_test_M->NonInlinedSFcns.childSFunctions[0]), 0,
                       3*sizeof(SimStruct));
    Driver_test_M->childSfunctions =
      (&Driver_test_M->NonInlinedSFcns.childSFunctionPtrs[0]);
    Driver_test_M->childSfunctions[0] =
      (&Driver_test_M->NonInlinedSFcns.childSFunctions[0]);
    Driver_test_M->childSfunctions[1] =
      (&Driver_test_M->NonInlinedSFcns.childSFunctions[1]);
    Driver_test_M->childSfunctions[2] =
      (&Driver_test_M->NonInlinedSFcns.childSFunctions[2]);

    /* Level2 S-Function Block: Driver_test/<Root>/Setup1 (sg_IO183_setup_s) */
    {
      SimStruct *rts = Driver_test_M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod = Driver_test_M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset = Driver_test_M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = Driver_test_M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) std::memset(static_cast<void*>(sfcnPeriod), 0,
                         sizeof(time_T)*1);
      (void) std::memset(static_cast<void*>(sfcnOffset), 0,
                         sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Driver_test_M->NonInlinedSFcns.blkInfo2[0]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Driver_test_M->NonInlinedSFcns.inputOutputPortInfo2[0]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Driver_test_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Driver_test_M->NonInlinedSFcns.methods2[0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Driver_test_M->NonInlinedSFcns.methods3[0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Driver_test_M->NonInlinedSFcns.methods4[0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Driver_test_M->NonInlinedSFcns.statesInfo2[0]);
        ssSetPeriodicStatesInfo(rts,
          &Driver_test_M->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* path info */
      ssSetModelName(rts, "Setup1");
      ssSetPath(rts, "Driver_test/Setup1");
      ssSetRTModel(rts,Driver_test_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Driver_test_M->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 11);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)Driver_test_cal->Setup1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)Driver_test_cal->Setup1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)Driver_test_cal->Setup1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)Driver_test_cal->Setup1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)Driver_test_cal->Setup1_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)Driver_test_cal->Setup1_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)Driver_test_cal->Setup1_P7_Size);
        ssSetSFcnParam(rts, 7, (mxArray*)Driver_test_cal->Setup1_P8_Size);
        ssSetSFcnParam(rts, 8, (mxArray*)Driver_test_cal->Setup1_P9_Size);
        ssSetSFcnParam(rts, 9, (mxArray*)Driver_test_cal->Setup1_P10_Size);
        ssSetSFcnParam(rts, 10, (mxArray*)Driver_test_cal->Setup1_P11_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &Driver_test_DW.Setup1_IWORK[0]);
      ssSetPWork(rts, (void **) &Driver_test_DW.Setup1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Driver_test_M->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Driver_test_M->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 2);

        /* IWORK */
        ssSetDWorkWidthAsInt(rts, 0, 8);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Driver_test_DW.Setup1_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidthAsInt(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Driver_test_DW.Setup1_PWORK);
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

    /* Level2 S-Function Block: Driver_test/<Root>/Speedgoat Analog Input1 (sg_IO183_ad_s) */
    {
      SimStruct *rts = Driver_test_M->childSfunctions[1];

      /* timing info */
      time_T *sfcnPeriod = Driver_test_M->NonInlinedSFcns.Sfcn1.sfcnPeriod;
      time_T *sfcnOffset = Driver_test_M->NonInlinedSFcns.Sfcn1.sfcnOffset;
      int_T *sfcnTsMap = Driver_test_M->NonInlinedSFcns.Sfcn1.sfcnTsMap;
      (void) std::memset(static_cast<void*>(sfcnPeriod), 0,
                         sizeof(time_T)*1);
      (void) std::memset(static_cast<void*>(sfcnOffset), 0,
                         sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Driver_test_M->NonInlinedSFcns.blkInfo2[1]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Driver_test_M->NonInlinedSFcns.inputOutputPortInfo2[1]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Driver_test_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Driver_test_M->NonInlinedSFcns.methods2[1]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Driver_test_M->NonInlinedSFcns.methods3[1]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Driver_test_M->NonInlinedSFcns.methods4[1]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Driver_test_M->NonInlinedSFcns.statesInfo2[1]);
        ssSetPeriodicStatesInfo(rts,
          &Driver_test_M->NonInlinedSFcns.periodicStatesInfo[1]);
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Driver_test_M->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Driver_test_M->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Driver_test_M->NonInlinedSFcns.Sfcn1.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Driver_test_M->NonInlinedSFcns.Sfcn1.outputPortCoSimAttribute[0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &Driver_test_B.SpeedgoatAnalogInput1));
        }
      }

      /* path info */
      ssSetModelName(rts, "Speedgoat Analog Input1");
      ssSetPath(rts, "Driver_test/Speedgoat Analog Input1");
      ssSetRTModel(rts,Driver_test_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Driver_test_M->NonInlinedSFcns.Sfcn1.params;
        ssSetSFcnParamsCount(rts, 5);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Driver_test_cal->SpeedgoatAnalogInput1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Driver_test_cal->SpeedgoatAnalogInput1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       Driver_test_cal->SpeedgoatAnalogInput1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       Driver_test_cal->SpeedgoatAnalogInput1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       Driver_test_cal->SpeedgoatAnalogInput1_P5_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &Driver_test_DW.SpeedgoatAnalogInput1_IWORK[0]);
      ssSetPWork(rts, (void **) &Driver_test_DW.SpeedgoatAnalogInput1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Driver_test_M->NonInlinedSFcns.Sfcn1.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Driver_test_M->NonInlinedSFcns.Sfcn1.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 2);

        /* IWORK */
        ssSetDWorkWidthAsInt(rts, 0, 5);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Driver_test_DW.SpeedgoatAnalogInput1_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidthAsInt(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Driver_test_DW.SpeedgoatAnalogInput1_PWORK);
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

    /* Level2 S-Function Block: Driver_test/<Root>/Speedgoat Analog Output1 (sg_IO183_da_s) */
    {
      SimStruct *rts = Driver_test_M->childSfunctions[2];

      /* timing info */
      time_T *sfcnPeriod = Driver_test_M->NonInlinedSFcns.Sfcn2.sfcnPeriod;
      time_T *sfcnOffset = Driver_test_M->NonInlinedSFcns.Sfcn2.sfcnOffset;
      int_T *sfcnTsMap = Driver_test_M->NonInlinedSFcns.Sfcn2.sfcnTsMap;
      (void) std::memset(static_cast<void*>(sfcnPeriod), 0,
                         sizeof(time_T)*1);
      (void) std::memset(static_cast<void*>(sfcnOffset), 0,
                         sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Driver_test_M->NonInlinedSFcns.blkInfo2[2]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Driver_test_M->NonInlinedSFcns.inputOutputPortInfo2[2]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Driver_test_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Driver_test_M->NonInlinedSFcns.methods2[2]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Driver_test_M->NonInlinedSFcns.methods3[2]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Driver_test_M->NonInlinedSFcns.methods4[2]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Driver_test_M->NonInlinedSFcns.statesInfo2[2]);
        ssSetPeriodicStatesInfo(rts,
          &Driver_test_M->NonInlinedSFcns.periodicStatesInfo[2]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 2);
        ssSetPortInfoForInputs(rts,
          &Driver_test_M->NonInlinedSFcns.Sfcn2.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts,
          &Driver_test_M->NonInlinedSFcns.Sfcn2.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &Driver_test_M->NonInlinedSFcns.Sfcn2.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        ssSetInputPortUnit(rts, 1, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &Driver_test_M->NonInlinedSFcns.Sfcn2.inputPortCoSimAttribute[0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);
        ssSetInputPortIsContinuousQuantity(rts, 1, 0);

        /* port 0 */
        {
          ssSetInputPortRequiredContiguous(rts, 0, 1);
          ssSetInputPortSignal(rts, 0, &Driver_test_B.u_c);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 1);
        }

        /* port 1 */
        {
          ssSetInputPortRequiredContiguous(rts, 1, 1);
          ssSetInputPortSignal(rts, 1, &Driver_test_B.polarity);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidthAsInt(rts, 1, 1);
        }
      }

      /* path info */
      ssSetModelName(rts, "Speedgoat Analog Output1");
      ssSetPath(rts, "Driver_test/Speedgoat Analog Output1");
      ssSetRTModel(rts,Driver_test_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Driver_test_M->NonInlinedSFcns.Sfcn2.params;
        ssSetSFcnParamsCount(rts, 7);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Driver_test_cal->SpeedgoatAnalogOutput1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Driver_test_cal->SpeedgoatAnalogOutput1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       Driver_test_cal->SpeedgoatAnalogOutput1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       Driver_test_cal->SpeedgoatAnalogOutput1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       Driver_test_cal->SpeedgoatAnalogOutput1_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)
                       Driver_test_cal->SpeedgoatAnalogOutput1_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)
                       Driver_test_cal->SpeedgoatAnalogOutput1_P7_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &Driver_test_DW.SpeedgoatAnalogOutput1_IWORK[0]);
      ssSetPWork(rts, (void **) &Driver_test_DW.SpeedgoatAnalogOutput1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Driver_test_M->NonInlinedSFcns.Sfcn2.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Driver_test_M->NonInlinedSFcns.Sfcn2.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 2);

        /* IWORK */
        ssSetDWorkWidthAsInt(rts, 0, 5);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Driver_test_DW.SpeedgoatAnalogOutput1_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidthAsInt(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Driver_test_DW.SpeedgoatAnalogOutput1_PWORK);
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
    SimStruct *rts = Driver_test_M->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (sg_IO183_ad_s): '<Root>/Speedgoat Analog Input1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Input1' (sg_IO183_ad_s) */
  {
    SimStruct *rts = Driver_test_M->childSfunctions[1];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (sg_IO183_da_s): '<Root>/Speedgoat Analog Output1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Output1' (sg_IO183_da_s) */
  {
    SimStruct *rts = Driver_test_M->childSfunctions[2];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  {
    int32_T i;

    /* InitializeConditions for DiscreteIntegrator: '<S3>/xN' */
    Driver_test_DW.xN_DSTATE = Driver_test_cal->xN_IC;

    /* InitializeConditions for DiscreteStateSpace: '<S3>/Observer' */
    for (i = 0; i < 5; i++) {
      Driver_test_DW.Observer_DSTATE[i] =
        Driver_test_cal->Observer_InitialCondition;
    }

    /* End of InitializeConditions for DiscreteStateSpace: '<S3>/Observer' */

    /* SystemInitialize for MATLAB Function: '<S2>/BAW033k' */
    Driver_test_DW.sfEvent = Driver_test_CALL_EVENT;

    /* SystemInitialize for MATLAB Function: '<S1>/schedule' */
    Driver_test_DW.aborted = false;
    Driver_test_DW.aborted_not_empty = true;
    Driver_test_DW.lastK = -1.0;
    Driver_test_DW.lastK_not_empty = true;
    Driver_test_DW.sfEvent_f = Driver_test_CALL_EVENT;
  }
}

/* Model terminate function */
void Driver_test_terminate(void)
{
  /* Terminate for S-Function (sg_IO183_setup_s): '<Root>/Setup1' */
  /* Level2 S-Function Block: '<Root>/Setup1' (sg_IO183_setup_s) */
  {
    SimStruct *rts = Driver_test_M->childSfunctions[0];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_IO183_ad_s): '<Root>/Speedgoat Analog Input1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Input1' (sg_IO183_ad_s) */
  {
    SimStruct *rts = Driver_test_M->childSfunctions[1];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_IO183_da_s): '<Root>/Speedgoat Analog Output1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Output1' (sg_IO183_da_s) */
  {
    SimStruct *rts = Driver_test_M->childSfunctions[2];
    sfcnTerminate(rts);
  }
}
