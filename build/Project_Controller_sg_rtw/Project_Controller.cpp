/*
 * Project_Controller.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Project_Controller".
 *
 * Model version              : 15.10
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C++ source code generated on : Sun Nov  1 21:26:34 2026
 *
 * Target selection: speedgoat.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Project_Controller.h"
#include "rtwtypes.h"
#include "Project_Controller_cal.h"
#include "rte_Project_Controller_parameters.h"
#include "Project_Controller_private.h"
#include <cmath>

extern "C"
{

#include "rt_nonfinite.h"

}

#include <cstring>

/* Named constants for MATLAB Function: '<S2>/BAW033k' */
const int32_T Project_Controller_CALL_EVENT = -1;

/* Block signals (default storage) */
B_Project_Controller_T Project_Controller_B;

/* Block states (default storage) */
DW_Project_Controller_T Project_Controller_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Project_Controller_T Project_Controller_Y;

/* Real-time model */
RT_MODEL_Project_Controller_T Project_Controller_M_ =
  RT_MODEL_Project_Controller_T();
RT_MODEL_Project_Controller_T *const Project_Controller_M =
  &Project_Controller_M_;
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
void Project_Controller_step(void)
{
  real_T xnew[6];
  real_T tmp[2];
  real_T Observer;
  real_T tmp_2;
  real_T tmp_3;
  real_T u0;
  real_T u2;
  real_T *tmp_0;
  real_T *tmp_1;
  int_T i;
  int_T j;

  /* Sum: '<S1>/minus bias' incorporates:
   *  Constant: '<S1>/vBias'
   */
  tmp_3 = *get_vBias();

  /* Gain: '<Root>/step size' */
  tmp_2 = *get_rLow();

  /* Saturate: '<S1>/limit' */
  tmp_1 = get_uLim();

  /* Update for DiscreteStateSpace: '<S1>/Observer' */
  tmp_0 = get_Bo();
  for (i = 0; i < 2; i++) {
    tmp[i] = (get_xPre0())[i];
  }

  /* S-Function (sg_IO183_setup_s): '<Root>/Setup1' */

  /* Level2 S-Function Block: '<Root>/Setup1' (sg_IO183_setup_s) */
  {
    SimStruct *rts = Project_Controller_M->childSfunctions[0];
    sfcnOutputs(rts,0);
  }

  /* S-Function (sg_IO183_ad_s): '<Root>/Speedgoat Analog Input1' */

  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Input1' (sg_IO183_ad_s) */
  {
    SimStruct *rts = Project_Controller_M->childSfunctions[1];
    sfcnOutputs(rts,0);
  }

  /* MATLAB Function: '<S2>/BAW033k' */
  Project_Controller_DW.sfEvent = Project_Controller_CALL_EVENT;
  Project_Controller_B.y = 0.004 * Project_Controller_B.SpeedgoatAnalogInput1;

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<Root>/Initial Payload PositionX0[m] '
   */
  Project_Controller_B.Xm = Project_Controller_B.y -
    Project_Controller_cal->InitialPayloadPositionX0m_Value;

  /* Outport: '<Root>/Payload position X[m]' */
  Project_Controller_Y.PayloadpositionXm = Project_Controller_B.Xm;

  /* DiscreteIntegrator: '<S1>/xN' */
  Project_Controller_B.xN = Project_Controller_DW.xN_DSTATE;

  /* Gain: '<S1>/Ke' */
  Project_Controller_B.Ke_b = *get_Ke() * Project_Controller_B.xN;

  /* Gain: '<S1>/K' */
  u0 = 0.0;
  for (i = 0; i < 6; i++) {
    /* DiscreteStateSpace: '<S1>/Observer' */
    Observer = 0.0;
    for (j = 0; j < 6; j++) {
      Observer += Project_Controller_cal->Observer_C[6 * j + i] *
        Project_Controller_DW.Observer_DSTATE[j];
    }

    /* DiscreteStateSpace: '<S1>/Observer' */
    Project_Controller_B.Observer[i] = Observer;

    /* Gain: '<S1>/K' */
    u0 += (get_K())[i] * Observer;
  }

  /* Gain: '<S1>/K' */
  Project_Controller_B.K_l = u0;

  /* DigitalClock: '<S1>/clock' */
  Project_Controller_B.clock = Project_Controller_M->Timing.t[0];

  /* Bias: '<S1>/time since tExc' */
  Observer = -*get_tExc();

  /* Bias: '<S1>/time since tExc' */
  Project_Controller_B.timesincetExc = Project_Controller_B.clock + Observer;

  /* Fcn: '<S1>/chirp' */
  u2 = Project_Controller_B.timesincetExc;
  Observer = rt_powd_snf(u2, 2.0);

  /* Fcn: '<S1>/chirp' */
  Project_Controller_B.chirp = std::sin((0.3 *
    Project_Controller_B.timesincetExc + 0.16416666666666666 * Observer) *
    6.2831853071795862) * 0.0 + std::sin((Project_Controller_B.timesincetExc +
    5.0) * 628.31853071795865) * 0.0;

  /* Sum: '<S1>/uCmd' */
  Project_Controller_B.uCmd = (Project_Controller_B.Ke_b -
    Project_Controller_B.K_l) + Project_Controller_B.chirp;

  /* Sum: '<S1>/plus bias' incorporates:
   *  Constant: '<S1>/vBias'
   */
  Project_Controller_B.plusbias = Project_Controller_B.uCmd + tmp_3;

  /* Saturate: '<S1>/limit' */
  Observer = tmp_1[0];
  u2 = tmp_1[1];
  u0 = Project_Controller_B.plusbias;
  if (u0 > u2) {
    /* Saturate: '<S1>/limit' */
    Project_Controller_B.limit = u2;
  } else if (u0 < Observer) {
    /* Saturate: '<S1>/limit' */
    Project_Controller_B.limit = Observer;
  } else {
    /* Saturate: '<S1>/limit' */
    Project_Controller_B.limit = u0;
  }

  /* Fcn: '<Root>/inverse driver' */
  Project_Controller_B.inversedriver = ((Project_Controller_B.limit /
    1.0178760197630929 + 0.104) * static_cast<real_T>(Project_Controller_B.limit
    >= 0.0) + (Project_Controller_B.limit / 0.68886558913259832 + 0.214) *
    static_cast<real_T>(Project_Controller_B.limit < 0.0)) * 0.0 +
    Project_Controller_B.limit;

  /* Gain: '<Root>/Gain' */
  Project_Controller_B.Gain = Project_Controller_cal->Gain_Gain *
    Project_Controller_B.inversedriver;

  /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
  u0 = Project_Controller_B.Gain;
  Observer = Project_Controller_cal->SaturationInput05V2_LowerSat;
  u2 = Project_Controller_cal->SaturationInput05V2_UpperSat;
  if (u0 > u2) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
    Project_Controller_B.u = u2;
  } else if (u0 < Observer) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
    Project_Controller_B.u = Observer;
  } else {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V2' */
    Project_Controller_B.u = u0;
  }

  /* End of Saturate: '<Root>/Saturation Input: [0, 5] V2' */

  /* Abs: '<Root>/Abs1' */
  Project_Controller_B.Abs1 = std::abs(Project_Controller_B.u);

  /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
  u0 = Project_Controller_B.Abs1;
  Observer = Project_Controller_cal->SaturationInput05V1_LowerSat;
  u2 = Project_Controller_cal->SaturationInput05V1_UpperSat;
  if (u0 > u2) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
    Project_Controller_B.u_c = u2;
  } else if (u0 < Observer) {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
    Project_Controller_B.u_c = Observer;
  } else {
    /* Saturate: '<Root>/Saturation Input: [0, 5] V1' */
    Project_Controller_B.u_c = u0;
  }

  /* End of Saturate: '<Root>/Saturation Input: [0, 5] V1' */

  /* Switch: '<Root>/Switch' */
  if (Project_Controller_B.u > Project_Controller_cal->Switch_Threshold) {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant2'
     */
    Project_Controller_B.polarity = Project_Controller_cal->Constant2_Value;
  } else {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    Project_Controller_B.polarity = Project_Controller_cal->Constant1_Value;
  }

  /* End of Switch: '<Root>/Switch' */

  /* S-Function (sg_IO183_da_s): '<Root>/Speedgoat Analog Output1' */

  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Output1' (sg_IO183_da_s) */
  {
    SimStruct *rts = Project_Controller_M->childSfunctions[2];
    sfcnOutputs(rts,0);
  }

  /* DiscreteStateSpace: '<Root>/Reference' */
  {
    Project_Controller_B.Reference = (Project_Controller_cal->Reference_C[0])*
      Project_Controller_DW.Reference_DSTATE[0]
      + (Project_Controller_cal->Reference_C[1])*
      Project_Controller_DW.Reference_DSTATE[1];
  }

  /* Sum: '<S1>/error' */
  Project_Controller_B.error = Project_Controller_B.Reference -
    Project_Controller_B.Xm;

  /* Sum: '<S1>/minus bias' incorporates:
   *  Constant: '<S1>/vBias'
   */
  Project_Controller_B.minusbias = Project_Controller_B.limit - tmp_3;

  /* SignalConversion generated from: '<S1>/Observer' */
  Project_Controller_B.TmpSignalConversionAtObserverIn[0] =
    Project_Controller_B.minusbias;
  Project_Controller_B.TmpSignalConversionAtObserverIn[1] =
    Project_Controller_B.Xm;

  /* RelationalOperator: '<S1>/saturated' */
  Project_Controller_B.saturated = (Project_Controller_B.plusbias !=
    Project_Controller_B.limit);

  /* Signum: '<S1>/sign e' */
  u0 = Project_Controller_B.error;
  if (rtIsNaN(u0)) {
    /* Signum: '<S1>/sign e' */
    Project_Controller_B.signe = (rtNaN);
  } else if (u0 < 0.0) {
    /* Signum: '<S1>/sign e' */
    Project_Controller_B.signe = -1.0;
  } else {
    /* Signum: '<S1>/sign e' */
    Project_Controller_B.signe = (u0 > 0.0);
  }

  /* End of Signum: '<S1>/sign e' */

  /* Signum: '<S1>/sign u' */
  u0 = Project_Controller_B.uCmd;
  if (rtIsNaN(u0)) {
    /* Signum: '<S1>/sign u' */
    Project_Controller_B.signu = (rtNaN);
  } else if (u0 < 0.0) {
    /* Signum: '<S1>/sign u' */
    Project_Controller_B.signu = -1.0;
  } else {
    /* Signum: '<S1>/sign u' */
    Project_Controller_B.signu = (u0 > 0.0);
  }

  /* End of Signum: '<S1>/sign u' */

  /* Product: '<S1>/sign product' */
  Project_Controller_B.signproduct = Project_Controller_B.signe *
    Project_Controller_B.signu;

  /* RelationalOperator: '<S3>/Compare' incorporates:
   *  Constant: '<S3>/Constant'
   */
  Project_Controller_B.Compare = (Project_Controller_B.signproduct >
    Project_Controller_cal->samesign_const);

  /* Logic: '<S1>/integrate' */
  Project_Controller_B.integrate = ((!Project_Controller_B.saturated) ||
    (!Project_Controller_B.Compare));

  /* Switch: '<S1>/anti-windup' */
  if (Project_Controller_B.integrate) {
    /* Switch: '<S1>/anti-windup' */
    Project_Controller_B.antiwindup = Project_Controller_B.error;
  } else {
    /* Switch: '<S1>/anti-windup' incorporates:
     *  Constant: '<S1>/zero'
     */
    Project_Controller_B.antiwindup = Project_Controller_cal->zero_Value;
  }

  /* End of Switch: '<S1>/anti-windup' */

  /* DiscretePulseGenerator: '<Root>/pulse' */
  Project_Controller_B.pulse = (Project_Controller_DW.clockTickCounter <
    Project_Controller_cal->pulse_Duty) &&
    (Project_Controller_DW.clockTickCounter >= 0) ?
    Project_Controller_cal->pulse_Amp : 0.0;

  /* DiscretePulseGenerator: '<Root>/pulse' */
  if (Project_Controller_DW.clockTickCounter >=
      Project_Controller_cal->pulse_Period - 1.0) {
    Project_Controller_DW.clockTickCounter = 0;
  } else {
    Project_Controller_DW.clockTickCounter++;
  }

  /* Gain: '<Root>/step size' */
  Observer = *get_rHigh() - tmp_2;

  /* Gain: '<Root>/step size' */
  Project_Controller_B.stepsize = Observer * Project_Controller_B.pulse;

  /* Sum: '<Root>/reference step' incorporates:
   *  Constant: '<Root>/rLow'
   */
  Project_Controller_B.referencestep = Project_Controller_B.stepsize + tmp_2;

  /* Update for DiscreteIntegrator: '<S1>/xN' */
  Project_Controller_DW.xN_DSTATE += Project_Controller_cal->xN_gainval *
    Project_Controller_B.antiwindup;

  /* Update for DiscreteStateSpace: '<S1>/Observer' */
  for (i = 0; i < 6; i++) {
    u0 = 0.0;
    for (j = 0; j < 6; j++) {
      u0 += (get_Ao())[6 * j + i] * Project_Controller_DW.Observer_DSTATE[j];
    }

    u0 += tmp_0[i] * Project_Controller_B.TmpSignalConversionAtObserverIn[0];
    u0 += tmp_0[i + 6] * Project_Controller_B.TmpSignalConversionAtObserverIn[1];
    xnew[i] = u0;
  }

  for (i = 0; i < 6; i++) {
    Project_Controller_DW.Observer_DSTATE[i] = xnew[i];
  }

  /* Update for DiscreteStateSpace: '<Root>/Reference' */
  {
    real_T xnew[2];
    xnew[0] = (Project_Controller_cal->Reference_A[0])*
      Project_Controller_DW.Reference_DSTATE[0]
      + (Project_Controller_cal->Reference_A[1])*
      Project_Controller_DW.Reference_DSTATE[1];
    xnew[0] += Project_Controller_cal->Reference_B*
      Project_Controller_B.referencestep;
    xnew[1] = (Project_Controller_cal->Reference_A[2])*
      Project_Controller_DW.Reference_DSTATE[0];
    (void) std::memcpy(&Project_Controller_DW.Reference_DSTATE[0], xnew,
                       sizeof(real_T)*2);
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
  if (!(++Project_Controller_M->Timing.clockTick0)) {
    ++Project_Controller_M->Timing.clockTickH0;
  }

  Project_Controller_M->Timing.t[0] = Project_Controller_M->Timing.clockTick0 *
    Project_Controller_M->Timing.stepSize0 +
    Project_Controller_M->Timing.clockTickH0 *
    Project_Controller_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Project_Controller_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  rtsiSetSolverName(&Project_Controller_M->solverInfo,"FixedStepDiscrete");
  Project_Controller_M->solverInfoPtr = (&Project_Controller_M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Project_Controller_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    Project_Controller_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Project_Controller_M->Timing.sampleTimes =
      (&Project_Controller_M->Timing.sampleTimesArray[0]);
    Project_Controller_M->Timing.offsetTimes =
      (&Project_Controller_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Project_Controller_M->Timing.sampleTimes[0] = (0.0001);

    /* task offsets */
    Project_Controller_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Project_Controller_M, &Project_Controller_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Project_Controller_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Project_Controller_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Project_Controller_M, -1);
  Project_Controller_M->Timing.stepSize0 = 0.0001;
  Project_Controller_M->solverInfoPtr = (&Project_Controller_M->solverInfo);
  Project_Controller_M->Timing.stepSize = (0.0001);
  rtsiSetFixedStepSize(&Project_Controller_M->solverInfo, 0.0001);
  rtsiSetSolverMode(&Project_Controller_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  (void) std::memset((static_cast<void *>(&Project_Controller_B)), 0,
                     sizeof(B_Project_Controller_T));

  /* states (dwork) */
  (void) std::memset(static_cast<void *>(&Project_Controller_DW), 0,
                     sizeof(DW_Project_Controller_T));

  /* external outputs */
  Project_Controller_Y.PayloadpositionXm = 0.0;

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &Project_Controller_M->NonInlinedSFcns.sfcnInfo;
    Project_Controller_M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(Project_Controller_M)));
    Project_Controller_M->Sizes.numSampTimes = (1);
    rtssSetNumRootSampTimesPtr(sfcnInfo,
      &Project_Controller_M->Sizes.numSampTimes);
    Project_Controller_M->NonInlinedSFcns.taskTimePtrs[0] = (&rtmGetTPtr
      (Project_Controller_M)[0]);
    rtssSetTPtrPtr(sfcnInfo,Project_Controller_M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(Project_Controller_M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(Project_Controller_M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput
      (Project_Controller_M));
    rtssSetStepSizePtr(sfcnInfo, &Project_Controller_M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested(Project_Controller_M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &Project_Controller_M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo,
      &Project_Controller_M->zCCacheNeedsReset);
    rtssSetContTimeOutputInconsistentWithStateAtMajorStepPtr(sfcnInfo,
      &Project_Controller_M->CTOutputIncnstWithState);
    rtssSetSampleHitsPtr(sfcnInfo, &Project_Controller_M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo,
      &Project_Controller_M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &Project_Controller_M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &Project_Controller_M->solverInfoPtr);
  }

  Project_Controller_M->Sizes.numSFcns = (3);

  /* register each child */
  {
    (void) std::memset(static_cast<void *>
                       (&Project_Controller_M->NonInlinedSFcns.childSFunctions[0]),
                       0,
                       3*sizeof(SimStruct));
    Project_Controller_M->childSfunctions =
      (&Project_Controller_M->NonInlinedSFcns.childSFunctionPtrs[0]);
    Project_Controller_M->childSfunctions[0] =
      (&Project_Controller_M->NonInlinedSFcns.childSFunctions[0]);
    Project_Controller_M->childSfunctions[1] =
      (&Project_Controller_M->NonInlinedSFcns.childSFunctions[1]);
    Project_Controller_M->childSfunctions[2] =
      (&Project_Controller_M->NonInlinedSFcns.childSFunctions[2]);

    /* Level2 S-Function Block: Project_Controller/<Root>/Setup1 (sg_IO183_setup_s) */
    {
      SimStruct *rts = Project_Controller_M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod =
        Project_Controller_M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset =
        Project_Controller_M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = Project_Controller_M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) std::memset(static_cast<void*>(sfcnPeriod), 0,
                         sizeof(time_T)*1);
      (void) std::memset(static_cast<void*>(sfcnOffset), 0,
                         sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Project_Controller_M->NonInlinedSFcns.blkInfo2[0]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Project_Controller_M->NonInlinedSFcns.inputOutputPortInfo2[0]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Project_Controller_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Project_Controller_M->NonInlinedSFcns.methods2
                           [0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Project_Controller_M->NonInlinedSFcns.methods3
                           [0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Project_Controller_M->NonInlinedSFcns.methods4
                           [0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Project_Controller_M->
                         NonInlinedSFcns.statesInfo2[0]);
        ssSetPeriodicStatesInfo(rts,
          &Project_Controller_M->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* path info */
      ssSetModelName(rts, "Setup1");
      ssSetPath(rts, "Project_Controller/Setup1");
      ssSetRTModel(rts,Project_Controller_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Project_Controller_M->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 11);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)Project_Controller_cal->Setup1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)Project_Controller_cal->Setup1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)Project_Controller_cal->Setup1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)Project_Controller_cal->Setup1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)Project_Controller_cal->Setup1_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)Project_Controller_cal->Setup1_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)Project_Controller_cal->Setup1_P7_Size);
        ssSetSFcnParam(rts, 7, (mxArray*)Project_Controller_cal->Setup1_P8_Size);
        ssSetSFcnParam(rts, 8, (mxArray*)Project_Controller_cal->Setup1_P9_Size);
        ssSetSFcnParam(rts, 9, (mxArray*)Project_Controller_cal->Setup1_P10_Size);
        ssSetSFcnParam(rts, 10, (mxArray*)
                       Project_Controller_cal->Setup1_P11_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &Project_Controller_DW.Setup1_IWORK[0]);
      ssSetPWork(rts, (void **) &Project_Controller_DW.Setup1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Project_Controller_M->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Project_Controller_M->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 2);

        /* IWORK */
        ssSetDWorkWidthAsInt(rts, 0, 8);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Project_Controller_DW.Setup1_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidthAsInt(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Project_Controller_DW.Setup1_PWORK);
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

    /* Level2 S-Function Block: Project_Controller/<Root>/Speedgoat Analog Input1 (sg_IO183_ad_s) */
    {
      SimStruct *rts = Project_Controller_M->childSfunctions[1];

      /* timing info */
      time_T *sfcnPeriod =
        Project_Controller_M->NonInlinedSFcns.Sfcn1.sfcnPeriod;
      time_T *sfcnOffset =
        Project_Controller_M->NonInlinedSFcns.Sfcn1.sfcnOffset;
      int_T *sfcnTsMap = Project_Controller_M->NonInlinedSFcns.Sfcn1.sfcnTsMap;
      (void) std::memset(static_cast<void*>(sfcnPeriod), 0,
                         sizeof(time_T)*1);
      (void) std::memset(static_cast<void*>(sfcnOffset), 0,
                         sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Project_Controller_M->NonInlinedSFcns.blkInfo2[1]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Project_Controller_M->NonInlinedSFcns.inputOutputPortInfo2[1]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Project_Controller_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Project_Controller_M->NonInlinedSFcns.methods2
                           [1]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Project_Controller_M->NonInlinedSFcns.methods3
                           [1]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Project_Controller_M->NonInlinedSFcns.methods4
                           [1]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Project_Controller_M->
                         NonInlinedSFcns.statesInfo2[1]);
        ssSetPeriodicStatesInfo(rts,
          &Project_Controller_M->NonInlinedSFcns.periodicStatesInfo[1]);
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Project_Controller_M->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        ssSetPortInfoForOutputs(rts,
          &Project_Controller_M->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Project_Controller_M->NonInlinedSFcns.Sfcn1.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &Project_Controller_M->NonInlinedSFcns.Sfcn1.outputPortCoSimAttribute
          [0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &Project_Controller_B.SpeedgoatAnalogInput1));
        }
      }

      /* path info */
      ssSetModelName(rts, "Speedgoat Analog Input1");
      ssSetPath(rts, "Project_Controller/Speedgoat Analog Input1");
      ssSetRTModel(rts,Project_Controller_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Project_Controller_M->NonInlinedSFcns.Sfcn1.params;
        ssSetSFcnParamsCount(rts, 5);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Project_Controller_cal->SpeedgoatAnalogInput1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Project_Controller_cal->SpeedgoatAnalogInput1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       Project_Controller_cal->SpeedgoatAnalogInput1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       Project_Controller_cal->SpeedgoatAnalogInput1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       Project_Controller_cal->SpeedgoatAnalogInput1_P5_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *)
                 &Project_Controller_DW.SpeedgoatAnalogInput1_IWORK[0]);
      ssSetPWork(rts, (void **)
                 &Project_Controller_DW.SpeedgoatAnalogInput1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Project_Controller_M->NonInlinedSFcns.Sfcn1.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Project_Controller_M->NonInlinedSFcns.Sfcn1.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 2);

        /* IWORK */
        ssSetDWorkWidthAsInt(rts, 0, 5);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Project_Controller_DW.SpeedgoatAnalogInput1_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidthAsInt(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Project_Controller_DW.SpeedgoatAnalogInput1_PWORK);
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

    /* Level2 S-Function Block: Project_Controller/<Root>/Speedgoat Analog Output1 (sg_IO183_da_s) */
    {
      SimStruct *rts = Project_Controller_M->childSfunctions[2];

      /* timing info */
      time_T *sfcnPeriod =
        Project_Controller_M->NonInlinedSFcns.Sfcn2.sfcnPeriod;
      time_T *sfcnOffset =
        Project_Controller_M->NonInlinedSFcns.Sfcn2.sfcnOffset;
      int_T *sfcnTsMap = Project_Controller_M->NonInlinedSFcns.Sfcn2.sfcnTsMap;
      (void) std::memset(static_cast<void*>(sfcnPeriod), 0,
                         sizeof(time_T)*1);
      (void) std::memset(static_cast<void*>(sfcnOffset), 0,
                         sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Project_Controller_M->NonInlinedSFcns.blkInfo2[2]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Project_Controller_M->NonInlinedSFcns.inputOutputPortInfo2[2]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Project_Controller_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Project_Controller_M->NonInlinedSFcns.methods2
                           [2]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Project_Controller_M->NonInlinedSFcns.methods3
                           [2]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Project_Controller_M->NonInlinedSFcns.methods4
                           [2]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Project_Controller_M->
                         NonInlinedSFcns.statesInfo2[2]);
        ssSetPeriodicStatesInfo(rts,
          &Project_Controller_M->NonInlinedSFcns.periodicStatesInfo[2]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 2);
        ssSetPortInfoForInputs(rts,
          &Project_Controller_M->NonInlinedSFcns.Sfcn2.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts,
          &Project_Controller_M->NonInlinedSFcns.Sfcn2.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &Project_Controller_M->NonInlinedSFcns.Sfcn2.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        ssSetInputPortUnit(rts, 1, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &Project_Controller_M->NonInlinedSFcns.Sfcn2.inputPortCoSimAttribute[0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);
        ssSetInputPortIsContinuousQuantity(rts, 1, 0);

        /* port 0 */
        {
          ssSetInputPortRequiredContiguous(rts, 0, 1);
          ssSetInputPortSignal(rts, 0, &Project_Controller_B.u_c);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 1);
        }

        /* port 1 */
        {
          ssSetInputPortRequiredContiguous(rts, 1, 1);
          ssSetInputPortSignal(rts, 1, &Project_Controller_B.polarity);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidthAsInt(rts, 1, 1);
        }
      }

      /* path info */
      ssSetModelName(rts, "Speedgoat Analog Output1");
      ssSetPath(rts, "Project_Controller/Speedgoat Analog Output1");
      ssSetRTModel(rts,Project_Controller_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &Project_Controller_M->NonInlinedSFcns.Sfcn2.params;
        ssSetSFcnParamsCount(rts, 7);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       Project_Controller_cal->SpeedgoatAnalogOutput1_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       Project_Controller_cal->SpeedgoatAnalogOutput1_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       Project_Controller_cal->SpeedgoatAnalogOutput1_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       Project_Controller_cal->SpeedgoatAnalogOutput1_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       Project_Controller_cal->SpeedgoatAnalogOutput1_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)
                       Project_Controller_cal->SpeedgoatAnalogOutput1_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)
                       Project_Controller_cal->SpeedgoatAnalogOutput1_P7_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *)
                 &Project_Controller_DW.SpeedgoatAnalogOutput1_IWORK[0]);
      ssSetPWork(rts, (void **)
                 &Project_Controller_DW.SpeedgoatAnalogOutput1_PWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Project_Controller_M->NonInlinedSFcns.Sfcn2.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Project_Controller_M->NonInlinedSFcns.Sfcn2.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        ssSetNumDWorkAsInt(rts, 2);

        /* IWORK */
        ssSetDWorkWidthAsInt(rts, 0, 5);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Project_Controller_DW.SpeedgoatAnalogOutput1_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidthAsInt(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Project_Controller_DW.SpeedgoatAnalogOutput1_PWORK);
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
    SimStruct *rts = Project_Controller_M->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (sg_IO183_ad_s): '<Root>/Speedgoat Analog Input1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Input1' (sg_IO183_ad_s) */
  {
    SimStruct *rts = Project_Controller_M->childSfunctions[1];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (sg_IO183_da_s): '<Root>/Speedgoat Analog Output1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Output1' (sg_IO183_da_s) */
  {
    SimStruct *rts = Project_Controller_M->childSfunctions[2];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for DiscretePulseGenerator: '<Root>/pulse' */
  Project_Controller_DW.clockTickCounter = -20000;

  {
    real_T tmp[2];
    int32_T i;

    /* InitializeConditions for DiscreteIntegrator: '<S1>/xN' */
    Project_Controller_DW.xN_DSTATE = *get_xN0();

    /* InitializeConditions for DiscreteStateSpace: '<S1>/Observer' */
    for (i = 0; i < 6; i++) {
      Project_Controller_DW.Observer_DSTATE[i] = (get_xhat0())[i];
    }

    /* End of InitializeConditions for DiscreteStateSpace: '<S1>/Observer' */
    for (i = 0; i < 2; i++) {
      tmp[i] = (get_xPre0())[i];
    }

    /* InitializeConditions for DiscreteStateSpace: '<Root>/Reference' */
    Project_Controller_DW.Reference_DSTATE[0] = get_xPre0()[0];
    Project_Controller_DW.Reference_DSTATE[1] = get_xPre0()[1];

    /* SystemInitialize for MATLAB Function: '<S2>/BAW033k' */
    Project_Controller_DW.sfEvent = Project_Controller_CALL_EVENT;
  }
}

/* Model terminate function */
void Project_Controller_terminate(void)
{
  /* Terminate for S-Function (sg_IO183_setup_s): '<Root>/Setup1' */
  /* Level2 S-Function Block: '<Root>/Setup1' (sg_IO183_setup_s) */
  {
    SimStruct *rts = Project_Controller_M->childSfunctions[0];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_IO183_ad_s): '<Root>/Speedgoat Analog Input1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Input1' (sg_IO183_ad_s) */
  {
    SimStruct *rts = Project_Controller_M->childSfunctions[1];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_IO183_da_s): '<Root>/Speedgoat Analog Output1' */
  /* Level2 S-Function Block: '<Root>/Speedgoat Analog Output1' (sg_IO183_da_s) */
  {
    SimStruct *rts = Project_Controller_M->childSfunctions[2];
    sfcnTerminate(rts);
  }
}
