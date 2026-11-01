#ifndef _RTE_DRIVER_TEST_PARAMETERS_H
#define _RTE_DRIVER_TEST_PARAMETERS_H
#include "rtwtypes.h"
#include "SegmentInfo.hpp"
#include "multiword_types.h"
#include "Driver_test_types.h"

struct RTE_Param_Service_T {
  real_T Ao[25];
  real_T Bo[10];
  real_T K[5];
  real_T Ke;
  real_T tExc;
  real_T vBias;
  real_T vMax;
};

extern RTE_Param_Service_T RTE_Param_Service;
extern RTE_Param_Service_T *RTE_Param_Service_ptr;
real_T* get_Ao(void);
real_T* get_Bo(void);
real_T* get_K(void);
real_T* get_Ke(void);
real_T* get_tExc(void);
real_T* get_vBias(void);
real_T* get_vMax(void);
namespace slrealtime
{
  SegmentVector &getSegmentVector(void);
}                                      // slrealtime

#endif
