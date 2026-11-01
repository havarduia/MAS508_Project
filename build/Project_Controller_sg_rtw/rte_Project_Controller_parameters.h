#ifndef _RTE_PROJECT_CONTROLLER_PARAMETERS_H
#define _RTE_PROJECT_CONTROLLER_PARAMETERS_H
#include "rtwtypes.h"
#include "SegmentInfo.hpp"
#include "multiword_types.h"
#include "Project_Controller_types.h"

struct RTE_Param_Service_T {
  real_T Ao[36];
  real_T Bo[12];
  real_T K[6];
  real_T Ke;
  real_T rHigh;
  real_T rLow;
  real_T tExc;
  real_T uLim[2];
  real_T vBias;
  real_T xN0;
  real_T xPre0[2];
  real_T xhat0[6];
};

extern RTE_Param_Service_T RTE_Param_Service;
extern RTE_Param_Service_T *RTE_Param_Service_ptr;
real_T* get_Ao(void);
real_T* get_Bo(void);
real_T* get_K(void);
real_T* get_Ke(void);
real_T* get_rHigh(void);
real_T* get_rLow(void);
real_T* get_tExc(void);
real_T* get_uLim(void);
real_T* get_vBias(void);
real_T* get_xN0(void);
real_T* get_xPre0(void);
real_T* get_xhat0(void);
namespace slrealtime
{
  SegmentVector &getSegmentVector(void);
}                                      // slrealtime

#endif
