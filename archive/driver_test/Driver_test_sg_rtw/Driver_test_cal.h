#ifndef Driver_test_cal_h_
#define Driver_test_cal_h_
#include "rtwtypes.h"

/* Storage class 'PageSwitching', for system '<Root>' */
struct Driver_test_cal_type {
  real_T samesign_const;               /* Mask Parameter: samesign_const
                                        * Referenced by: '<S5>/Constant'
                                        */
  real_T zero_Value;                   /* Expression: 0
                                        * Referenced by: '<S3>/zero'
                                        */
  real_T Constant2_Value;              /* Expression: 5
                                        * Referenced by: '<Root>/Constant2'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T Setup1_P1_Size[2];            /* Computed Parameter: Setup1_P1_Size
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P1;                    /* Expression: parModuleId
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P2_Size[2];            /* Computed Parameter: Setup1_P2_Size
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P2;                    /* Expression: parPciSlot
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P3_Size[2];            /* Computed Parameter: Setup1_P3_Size
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P3;                    /* Expression: parDaSimult
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P4_Size[2];            /* Computed Parameter: Setup1_P4_Size
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P4;                    /* Expression: parAdCoupling
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P5_Size[2];            /* Computed Parameter: Setup1_P5_Size
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P5;                    /* Expression: parAdRange
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P6_Size[2];            /* Computed Parameter: Setup1_P6_Size
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P6;                    /* Expression: parAdChannelLow
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P7_Size[2];            /* Computed Parameter: Setup1_P7_Size
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P7;                    /* Expression: parAdChannelHigh
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P8_Size[2];            /* Computed Parameter: Setup1_P8_Size
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P8[5];                 /* Computed Parameter: Setup1_P8
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P9_Size[2];            /* Computed Parameter: Setup1_P9_Size
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P9;                    /* Expression: parDaRange
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P10_Size[2];           /* Computed Parameter: Setup1_P10_Size
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P10;                   /* Expression: parIOPullReferenceFront
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P11_Size[2];           /* Computed Parameter: Setup1_P11_Size
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T Setup1_P11;                   /* Expression: parIOPullReferenceRear
                                        * Referenced by: '<Root>/Setup1'
                                        */
  real_T InitialPayloadPositionX0m_Value;/* Expression: 0.00526
                                          * Referenced by: '<Root>/Initial Payload PositionX0[m] '
                                          */
  real_T SpeedgoatAnalogInput1_P1_Size[2];
                            /* Computed Parameter: SpeedgoatAnalogInput1_P1_Size
                             * Referenced by: '<Root>/Speedgoat Analog Input1'
                             */
  real_T SpeedgoatAnalogInput1_P1;     /* Expression: parModuleId
                                        * Referenced by: '<Root>/Speedgoat Analog Input1'
                                        */
  real_T SpeedgoatAnalogInput1_P2_Size[2];
                            /* Computed Parameter: SpeedgoatAnalogInput1_P2_Size
                             * Referenced by: '<Root>/Speedgoat Analog Input1'
                             */
  real_T SpeedgoatAnalogInput1_P2;     /* Expression: parPciSlot
                                        * Referenced by: '<Root>/Speedgoat Analog Input1'
                                        */
  real_T SpeedgoatAnalogInput1_P3_Size[2];
                            /* Computed Parameter: SpeedgoatAnalogInput1_P3_Size
                             * Referenced by: '<Root>/Speedgoat Analog Input1'
                             */
  real_T SpeedgoatAnalogInput1_P3;     /* Expression: parSampTime
                                        * Referenced by: '<Root>/Speedgoat Analog Input1'
                                        */
  real_T SpeedgoatAnalogInput1_P4_Size[2];
                            /* Computed Parameter: SpeedgoatAnalogInput1_P4_Size
                             * Referenced by: '<Root>/Speedgoat Analog Input1'
                             */
  real_T SpeedgoatAnalogInput1_P4;     /* Expression: parAdChannelLow
                                        * Referenced by: '<Root>/Speedgoat Analog Input1'
                                        */
  real_T SpeedgoatAnalogInput1_P5_Size[2];
                            /* Computed Parameter: SpeedgoatAnalogInput1_P5_Size
                             * Referenced by: '<Root>/Speedgoat Analog Input1'
                             */
  real_T SpeedgoatAnalogInput1_P5;     /* Expression: parAdChannelHigh
                                        * Referenced by: '<Root>/Speedgoat Analog Input1'
                                        */
  real_T xN_gainval;                   /* Computed Parameter: xN_gainval
                                        * Referenced by: '<S3>/xN'
                                        */
  real_T xN_IC;                        /* Expression: 0
                                        * Referenced by: '<S3>/xN'
                                        */
  real_T Observer_C[25];               /* Expression: eye(5)
                                        * Referenced by: '<S3>/Observer'
                                        */
  real_T Observer_D[10];               /* Expression: zeros(5, 2)
                                        * Referenced by: '<S3>/Observer'
                                        */
  real_T Observer_InitialCondition;    /* Expression: 0
                                        * Referenced by: '<S3>/Observer'
                                        */
  real_T steporcontrol_Threshold;      /* Expression: 0.5
                                        * Referenced by: '<S1>/step or control'
                                        */
  real_T Gain_Gain;                    /* Expression: 1
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T SaturationInput05V2_UpperSat; /* Expression: 5
                                        * Referenced by: '<Root>/Saturation Input: [0, 5] V2'
                                        */
  real_T SaturationInput05V2_LowerSat; /* Expression: -5
                                        * Referenced by: '<Root>/Saturation Input: [0, 5] V2'
                                        */
  real_T SaturationInput05V1_UpperSat; /* Expression: 5
                                        * Referenced by: '<Root>/Saturation Input: [0, 5] V1'
                                        */
  real_T SaturationInput05V1_LowerSat; /* Expression: 0
                                        * Referenced by: '<Root>/Saturation Input: [0, 5] V1'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<Root>/Switch'
                                        */
  real_T SpeedgoatAnalogOutput1_P1_Size[2];
                           /* Computed Parameter: SpeedgoatAnalogOutput1_P1_Size
                            * Referenced by: '<Root>/Speedgoat Analog Output1'
                            */
  real_T SpeedgoatAnalogOutput1_P1;    /* Expression: parModuleId
                                        * Referenced by: '<Root>/Speedgoat Analog Output1'
                                        */
  real_T SpeedgoatAnalogOutput1_P2_Size[2];
                           /* Computed Parameter: SpeedgoatAnalogOutput1_P2_Size
                            * Referenced by: '<Root>/Speedgoat Analog Output1'
                            */
  real_T SpeedgoatAnalogOutput1_P2;    /* Expression: parPciSlot
                                        * Referenced by: '<Root>/Speedgoat Analog Output1'
                                        */
  real_T SpeedgoatAnalogOutput1_P3_Size[2];
                           /* Computed Parameter: SpeedgoatAnalogOutput1_P3_Size
                            * Referenced by: '<Root>/Speedgoat Analog Output1'
                            */
  real_T SpeedgoatAnalogOutput1_P3;    /* Expression: parSampTime
                                        * Referenced by: '<Root>/Speedgoat Analog Output1'
                                        */
  real_T SpeedgoatAnalogOutput1_P4_Size[2];
                           /* Computed Parameter: SpeedgoatAnalogOutput1_P4_Size
                            * Referenced by: '<Root>/Speedgoat Analog Output1'
                            */
  real_T SpeedgoatAnalogOutput1_P4[2]; /* Expression: parDaChannels
                                        * Referenced by: '<Root>/Speedgoat Analog Output1'
                                        */
  real_T SpeedgoatAnalogOutput1_P5_Size[2];
                           /* Computed Parameter: SpeedgoatAnalogOutput1_P5_Size
                            * Referenced by: '<Root>/Speedgoat Analog Output1'
                            */
  real_T SpeedgoatAnalogOutput1_P5[4]; /* Expression: parDaInit
                                        * Referenced by: '<Root>/Speedgoat Analog Output1'
                                        */
  real_T SpeedgoatAnalogOutput1_P6_Size[2];
                           /* Computed Parameter: SpeedgoatAnalogOutput1_P6_Size
                            * Referenced by: '<Root>/Speedgoat Analog Output1'
                            */
  real_T SpeedgoatAnalogOutput1_P6[4]; /* Expression: parDaReset
                                        * Referenced by: '<Root>/Speedgoat Analog Output1'
                                        */
  real_T SpeedgoatAnalogOutput1_P7_Size[2];
                           /* Computed Parameter: SpeedgoatAnalogOutput1_P7_Size
                            * Referenced by: '<Root>/Speedgoat Analog Output1'
                            */
  real_T SpeedgoatAnalogOutput1_P7;    /* Expression: parDaSimult
                                        * Referenced by: '<Root>/Speedgoat Analog Output1'
                                        */
};

/* Storage class 'PageSwitching' */
extern Driver_test_cal_type Driver_test_cal_impl;
extern Driver_test_cal_type *Driver_test_cal;

#endif                                 /* Driver_test_cal_h_ */
