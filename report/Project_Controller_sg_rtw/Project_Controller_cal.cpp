#include "Project_Controller_cal.h"
#include "Project_Controller.h"

/* Storage class 'PageSwitching' */
Project_Controller_cal_type Project_Controller_cal_impl = {
  /* Variable: Ao
   * Referenced by: '<S1>/Observer'
   */
  { 0.933377605842641, 6.6018904927479041E-9, 0.00013053795739864334,
    3.5161590569421942E-15, 1.1927085309442718E-10, 7.5775987413817939E-18,
    0.0010866050062159865, 0.99999996012846915, -0.00078623601679351184,
    1.2906871633161236E-6, 0.025815652054341925, 4.0151054137888754E-9,
    -2.73225594519381, 9.9993739526732633E-5, 0.99981326796672276,
    9.007718851518006E-11, 2.2318592069683766E-6, 2.4697362238168395E-13,
    0.4581675290224666, -0.0025815856872101637, -0.0094000834266839885,
    0.99955235663122322, -0.0732188899834147, 0.0092302227361795563,
    1.5296041586476932E-5, -8.6362339646082257E-8, -2.7298389122351667E-7,
    9.9984990567383378E-5, 0.99999618232647636, 4.6489376099311491E-7,
    96.5548311899045, -0.54335852761887171, -2.1415211895561095,
    -0.094106992275212631, -9.978324306552258, 0.95697220843728481 },

  /* Variable: Bo
   * Referenced by: '<S1>/Observer'
   */
  { 0.11958431418232265, 2.7388448209125713E-10, 8.1698394857585748E-6,
    1.0021591746327627E-16, 4.3514162153532976E-12, 1.7704744915798965E-19,
    -97.014085323933173, 0.54594015317761269, 2.1517075089995878,
    0.094553344956826033, 10.025727544481333, 0.033797564811430231 },

  /* Variable: K
   * Referenced by: '<S1>/K'
   */
  { 0.64927283209661546, 3500.0520919684532, 65.486337041810117,
    -1537.496750264834, 254.04569775122593, 52.998100875366816 },

  /* Variable: Ke
   * Referenced by: '<S1>/Ke'
   */
  5000.0000000005994,

  /* Variable: rHigh
   * Referenced by: '<Root>/step size'
   */
  0.015,

  /* Variable: rLow
   * Referenced by:
   *   '<Root>/rLow'
   *   '<Root>/step size'
   */
  0.005,

  /* Variable: tExc
   * Referenced by: '<S1>/time since tExc'
   */
  5.0,

  /* Variable: uLim
   * Referenced by: '<S1>/limit'
   */
  { -5.0, 5.0 },

  /* Variable: vBias
   * Referenced by: '<S1>/vBias'
   */
  0.6,

  /* Variable: xN0
   * Referenced by: '<S1>/xN'
   */
  0.0006449771016251983,

  /* Variable: xPre0
   * Referenced by: '<Root>/Reference'
   */
  { 3.5167970380470019, 3.5167970380470019 },

  /* Variable: xhat0
   * Referenced by: '<S1>/Observer'
   */
  { 0.0, 0.0016, 0.0, 0.0016, 0.0, 0.0016 },

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
  240000.0,

  /* Computed Parameter: pulse_Duty
   * Referenced by: '<Root>/pulse'
   */
  120000.0,

  /* Expression: 12
   * Referenced by: '<Root>/pulse'
   */
  12.0
};

Project_Controller_cal_type *Project_Controller_cal =
  &Project_Controller_cal_impl;
