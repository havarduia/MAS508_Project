#ifndef Project_Controller_cal_h_
#define Project_Controller_cal_h_
#include "rtwtypes.h"

/* Storage class 'PageSwitching', for system '<Root>' */
struct Project_Controller_cal_type {
  real_T Ao[36];                       /* Variable: Ao
                                        * Referenced by: '<S1>/Observer'
                                        */
  real_T Bo[12];                       /* Variable: Bo
                                        * Referenced by: '<S1>/Observer'
                                        */
  real_T K[6];                         /* Variable: K
                                        * Referenced by: '<S1>/K'
                                        */
  real_T Ke;                           /* Variable: Ke
                                        * Referenced by: '<S1>/Ke'
                                        */
  real_T rHigh;                        /* Variable: rHigh
                                        * Referenced by: '<Root>/step size'
                                        */
  real_T rLow;                         /* Variable: rLow
                                        * Referenced by:
                                        *   '<Root>/rLow'
                                        *   '<Root>/step size'
                                        */
  real_T tExc;                         /* Variable: tExc
                                        * Referenced by: '<S1>/time since tExc'
                                        */
  real_T uLim[2];                      /* Variable: uLim
                                        * Referenced by: '<S1>/limit'
                                        */
  real_T vBias;                        /* Variable: vBias
                                        * Referenced by: '<S1>/vBias'
                                        */
  real_T xN0;                          /* Variable: xN0
                                        * Referenced by: '<S1>/xN'
                                        */
  real_T xPre0[2];                     /* Variable: xPre0
                                        * Referenced by: '<Root>/Reference'
                                        */
  real_T xhat0[6];                     /* Variable: xhat0
                                        * Referenced by: '<S1>/Observer'
                                        */
  real_T samesign_const;               /* Mask Parameter: samesign_const
                                        * Referenced by: '<S3>/Constant'
                                        */
  real_T zero_Value;                   /* Expression: 0
                                        * Referenced by: '<S1>/zero'
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
                                        * Referenced by: '<S1>/xN'
                                        */
  real_T Observer_C[36];               /* Expression: eye(size(Ao, 1))
                                        * Referenced by: '<S1>/Observer'
                                        */
  real_T Observer_D[12];               /* Expression: zeros(size(Ao, 1), 2)
                                        * Referenced by: '<S1>/Observer'
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
  real_T Reference_A[3];               /* Computed Parameter: Reference_A
                                        * Referenced by: '<Root>/Reference'
                                        */
  real_T Reference_B;                  /* Computed Parameter: Reference_B
                                        * Referenced by: '<Root>/Reference'
                                        */
  real_T Reference_C[2];               /* Computed Parameter: Reference_C
                                        * Referenced by: '<Root>/Reference'
                                        */
  real_T pulse_Amp;                    /* Expression: 1
                                        * Referenced by: '<Root>/pulse'
                                        */
  real_T pulse_Period;                 /* Computed Parameter: pulse_Period
                                        * Referenced by: '<Root>/pulse'
                                        */
  real_T pulse_Duty;                   /* Computed Parameter: pulse_Duty
                                        * Referenced by: '<Root>/pulse'
                                        */
  real_T pulse_PhaseDelay;             /* Expression: 12
                                        * Referenced by: '<Root>/pulse'
                                        */
};

/* Storage class 'PageSwitching' */
extern Project_Controller_cal_type Project_Controller_cal_impl;
extern Project_Controller_cal_type *Project_Controller_cal;

#endif                                 /* Project_Controller_cal_h_ */
