#include "rte_Friction_ramp_parameters.h"
#include "Friction_ramp.h"
#include "Friction_ramp_cal.h"

extern Friction_ramp_cal_type Friction_ramp_cal_impl;
namespace slrealtime
{
  /* Description of SEGMENTS */
  SegmentVector segmentInfo {
    { (void*)&Friction_ramp_cal_impl, (void**)&Friction_ramp_cal, sizeof
      (Friction_ramp_cal_type), 2 }
  };

  SegmentVector &getSegmentVector(void)
  {
    return segmentInfo;
  }
}                                      // slrealtime
