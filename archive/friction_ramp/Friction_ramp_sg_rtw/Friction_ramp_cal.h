#ifndef Friction_ramp_cal_h_
#define Friction_ramp_cal_h_
#include "rtwtypes.h"

/* Storage class 'PageSwitching', for system '<Root>' */
struct Friction_ramp_cal_type {
  real_T Holdvoltage_Value;            /* Expression: 0.3
                                        * Referenced by: '<Root>/Hold voltage'
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
  real_T Rampprofile_tableData[8];
                               /* Expression: [0.3 0.3 1.5 0.3 0.3 -0.6 0.3 0.3]
                                * Referenced by: '<Root>/Ramp profile'
                                */
  real_T Rampprofile_bp01Data[8];      /* Expression: [0 2 22 23 24 44 46 50]
                                        * Referenced by: '<Root>/Ramp profile'
                                        */
  real_T Cutofflatch_OnVal;            /* Expression: 0.012
                                        * Referenced by: '<Root>/Cutoff latch'
                                        */
  real_T Cutofflatch_OffVal;           /* Expression: -1
                                        * Referenced by: '<Root>/Cutoff latch'
                                        */
  real_T Cutofflatch_YOn;              /* Expression: 1
                                        * Referenced by: '<Root>/Cutoff latch'
                                        */
  real_T Cutofflatch_YOff;             /* Expression: 0
                                        * Referenced by: '<Root>/Cutoff latch'
                                        */
  real_T Aftercutoff_Threshold;        /* Expression: 0.5
                                        * Referenced by: '<Root>/After cutoff'
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
extern Friction_ramp_cal_type Friction_ramp_cal_impl;
extern Friction_ramp_cal_type *Friction_ramp_cal;

#endif                                 /* Friction_ramp_cal_h_ */
