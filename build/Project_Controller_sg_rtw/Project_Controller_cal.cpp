#include "Project_Controller_cal.h"
#include "Project_Controller.h"

/* Storage class 'PageSwitching' */
Project_Controller_cal_type Project_Controller_cal_impl = {
  /* Mask Parameter: samesign_const
   * Referenced by: '<S3>/Constant'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/zero'
   */
  0.0,

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

  /* Computed Parameter: xN_gainval
   * Referenced by: '<S1>/xN'
   */
  0.0001,

  /* Expression: eye(size(Ao, 1))
   * Referenced by: '<S1>/Observer'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },

  /* Expression: zeros(size(Ao, 1), 2)
   * Referenced by: '<S1>/Observer'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

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
  1.0,

  /* Computed Parameter: Reference_A
   * Referenced by: '<Root>/Reference'
   */
  { 1.9993334444320996, -0.99933355550618086, 1.0 },

  /* Computed Parameter: Reference_B
   * Referenced by: '<Root>/Reference'
   */
  0.000244140625,

  /* Computed Parameter: Reference_C
   * Referenced by: '<Root>/Reference'
   */
  { 0.00022750499397474678, 0.00022745444292638964 },

  /* Expression: 1
   * Referenced by: '<Root>/pulse'
   */
  1.0,

  /* Computed Parameter: pulse_Period
   * Referenced by: '<Root>/pulse'
   */
  120000.0,

  /* Computed Parameter: pulse_Duty
   * Referenced by: '<Root>/pulse'
   */
  60000.0,

  /* Expression: 2
   * Referenced by: '<Root>/pulse'
   */
  2.0
};

Project_Controller_cal_type *Project_Controller_cal =
  &Project_Controller_cal_impl;
