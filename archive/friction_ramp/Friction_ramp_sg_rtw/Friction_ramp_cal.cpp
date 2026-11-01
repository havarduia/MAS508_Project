#include "Friction_ramp_cal.h"
#include "Friction_ramp.h"

/* Storage class 'PageSwitching' */
Friction_ramp_cal_type Friction_ramp_cal_impl = {
  /* Expression: 0.3
   * Referenced by: '<Root>/Hold voltage'
   */
  0.3,

  /* Expression: 5
   * Referenced by: '<Root>/Constant2'
   */
  5.0,

  /* Expression: 0
   * Referenced by: '<Root>/Constant1'
   */
  0.0,

  /* Computed Parameter: Setup1_P1_Size
   * Referenced by: '<Root>/Setup1'
   */
  { 1.0, 1.0 },

  /* Expression: parModuleId
   * Referenced by: '<Root>/Setup1'
   */
  1.0,

  /* Computed Parameter: Setup1_P2_Size
   * Referenced by: '<Root>/Setup1'
   */
  { 1.0, 1.0 },

  /* Expression: parPciSlot
   * Referenced by: '<Root>/Setup1'
   */
  -1.0,

  /* Computed Parameter: Setup1_P3_Size
   * Referenced by: '<Root>/Setup1'
   */
  { 1.0, 1.0 },

  /* Expression: parDaSimult
   * Referenced by: '<Root>/Setup1'
   */
  1.0,

  /* Computed Parameter: Setup1_P4_Size
   * Referenced by: '<Root>/Setup1'
   */
  { 1.0, 1.0 },

  /* Expression: parAdCoupling
   * Referenced by: '<Root>/Setup1'
   */
  1.0,

  /* Computed Parameter: Setup1_P5_Size
   * Referenced by: '<Root>/Setup1'
   */
  { 1.0, 1.0 },

  /* Expression: parAdRange
   * Referenced by: '<Root>/Setup1'
   */
  4.0,

  /* Computed Parameter: Setup1_P6_Size
   * Referenced by: '<Root>/Setup1'
   */
  { 1.0, 1.0 },

  /* Expression: parAdChannelLow
   * Referenced by: '<Root>/Setup1'
   */
  1.0,

  /* Computed Parameter: Setup1_P7_Size
   * Referenced by: '<Root>/Setup1'
   */
  { 1.0, 1.0 },

  /* Expression: parAdChannelHigh
   * Referenced by: '<Root>/Setup1'
   */
  1.0,

  /* Computed Parameter: Setup1_P8_Size
   * Referenced by: '<Root>/Setup1'
   */
  { 1.0, 5.0 },

  /* Computed Parameter: Setup1_P8
   * Referenced by: '<Root>/Setup1'
   */
  { 91.0, 49.0, 32.0, 50.0, 93.0 },

  /* Computed Parameter: Setup1_P9_Size
   * Referenced by: '<Root>/Setup1'
   */
  { 1.0, 1.0 },

  /* Expression: parDaRange
   * Referenced by: '<Root>/Setup1'
   */
  2.0,

  /* Computed Parameter: Setup1_P10_Size
   * Referenced by: '<Root>/Setup1'
   */
  { 1.0, 1.0 },

  /* Expression: parIOPullReferenceFront
   * Referenced by: '<Root>/Setup1'
   */
  1.0,

  /* Computed Parameter: Setup1_P11_Size
   * Referenced by: '<Root>/Setup1'
   */
  { 1.0, 1.0 },

  /* Expression: parIOPullReferenceRear
   * Referenced by: '<Root>/Setup1'
   */
  1.0,

  /* Expression: 0.00526
   * Referenced by: '<Root>/Initial Payload PositionX0[m] '
   */
  0.00526,

  /* Computed Parameter: SpeedgoatAnalogInput1_P1_Size
   * Referenced by: '<Root>/Speedgoat Analog Input1'
   */
  { 1.0, 1.0 },

  /* Expression: parModuleId
   * Referenced by: '<Root>/Speedgoat Analog Input1'
   */
  1.0,

  /* Computed Parameter: SpeedgoatAnalogInput1_P2_Size
   * Referenced by: '<Root>/Speedgoat Analog Input1'
   */
  { 1.0, 1.0 },

  /* Expression: parPciSlot
   * Referenced by: '<Root>/Speedgoat Analog Input1'
   */
  -1.0,

  /* Computed Parameter: SpeedgoatAnalogInput1_P3_Size
   * Referenced by: '<Root>/Speedgoat Analog Input1'
   */
  { 1.0, 1.0 },

  /* Expression: parSampTime
   * Referenced by: '<Root>/Speedgoat Analog Input1'
   */
  -1.0,

  /* Computed Parameter: SpeedgoatAnalogInput1_P4_Size
   * Referenced by: '<Root>/Speedgoat Analog Input1'
   */
  { 1.0, 1.0 },

  /* Expression: parAdChannelLow
   * Referenced by: '<Root>/Speedgoat Analog Input1'
   */
  1.0,

  /* Computed Parameter: SpeedgoatAnalogInput1_P5_Size
   * Referenced by: '<Root>/Speedgoat Analog Input1'
   */
  { 1.0, 1.0 },

  /* Expression: parAdChannelHigh
   * Referenced by: '<Root>/Speedgoat Analog Input1'
   */
  1.0,

  /* Expression: [0.3 0.3 1.5 0.3 0.3 -0.6 0.3 0.3]
   * Referenced by: '<Root>/Ramp profile'
   */
  { 0.3, 0.3, 1.5, 0.3, 0.3, -0.6, 0.3, 0.3 },

  /* Expression: [0 2 22 23 24 44 46 50]
   * Referenced by: '<Root>/Ramp profile'
   */
  { 0.0, 2.0, 22.0, 23.0, 24.0, 44.0, 46.0, 50.0 },

  /* Expression: 0.012
   * Referenced by: '<Root>/Cutoff latch'
   */
  0.012,

  /* Expression: -1
   * Referenced by: '<Root>/Cutoff latch'
   */
  -1.0,

  /* Expression: 1
   * Referenced by: '<Root>/Cutoff latch'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Cutoff latch'
   */
  0.0,

  /* Expression: 0.5
   * Referenced by: '<Root>/After cutoff'
   */
  0.5,

  /* Expression: 1
   * Referenced by: '<Root>/Gain'
   */
  1.0,

  /* Expression: 5
   * Referenced by: '<Root>/Saturation Input: [0, 5] V2'
   */
  5.0,

  /* Expression: -5
   * Referenced by: '<Root>/Saturation Input: [0, 5] V2'
   */
  -5.0,

  /* Expression: 5
   * Referenced by: '<Root>/Saturation Input: [0, 5] V1'
   */
  5.0,

  /* Expression: 0
   * Referenced by: '<Root>/Saturation Input: [0, 5] V1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Switch'
   */
  0.0,

  /* Computed Parameter: SpeedgoatAnalogOutput1_P1_Size
   * Referenced by: '<Root>/Speedgoat Analog Output1'
   */
  { 1.0, 1.0 },

  /* Expression: parModuleId
   * Referenced by: '<Root>/Speedgoat Analog Output1'
   */
  1.0,

  /* Computed Parameter: SpeedgoatAnalogOutput1_P2_Size
   * Referenced by: '<Root>/Speedgoat Analog Output1'
   */
  { 1.0, 1.0 },

  /* Expression: parPciSlot
   * Referenced by: '<Root>/Speedgoat Analog Output1'
   */
  -1.0,

  /* Computed Parameter: SpeedgoatAnalogOutput1_P3_Size
   * Referenced by: '<Root>/Speedgoat Analog Output1'
   */
  { 1.0, 1.0 },

  /* Expression: parSampTime
   * Referenced by: '<Root>/Speedgoat Analog Output1'
   */
  -1.0,

  /* Computed Parameter: SpeedgoatAnalogOutput1_P4_Size
   * Referenced by: '<Root>/Speedgoat Analog Output1'
   */
  { 1.0, 2.0 },

  /* Expression: parDaChannels
   * Referenced by: '<Root>/Speedgoat Analog Output1'
   */
  { 1.0, 2.0 },

  /* Computed Parameter: SpeedgoatAnalogOutput1_P5_Size
   * Referenced by: '<Root>/Speedgoat Analog Output1'
   */
  { 1.0, 4.0 },

  /* Expression: parDaInit
   * Referenced by: '<Root>/Speedgoat Analog Output1'
   */
  { 0.0, 5.0, 0.0, 0.0 },

  /* Computed Parameter: SpeedgoatAnalogOutput1_P6_Size
   * Referenced by: '<Root>/Speedgoat Analog Output1'
   */
  { 1.0, 4.0 },

  /* Expression: parDaReset
   * Referenced by: '<Root>/Speedgoat Analog Output1'
   */
  { 1.0, 1.0, 1.0, 1.0 },

  /* Computed Parameter: SpeedgoatAnalogOutput1_P7_Size
   * Referenced by: '<Root>/Speedgoat Analog Output1'
   */
  { 1.0, 1.0 },

  /* Expression: parDaSimult
   * Referenced by: '<Root>/Speedgoat Analog Output1'
   */
  1.0
};

Friction_ramp_cal_type *Friction_ramp_cal = &Friction_ramp_cal_impl;
