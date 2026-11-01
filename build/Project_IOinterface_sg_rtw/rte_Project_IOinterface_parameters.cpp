#include "rte_Project_IOinterface_parameters.h"
#include "Project_IOinterface.h"
#include "Project_IOinterface_cal.h"

extern Project_IOinterface_cal_type Project_IOinterface_cal_impl;
namespace slrealtime
{
  /* Description of SEGMENTS */
  SegmentVector segmentInfo {
    { (void*)&Project_IOinterface_cal_impl, (void**)&Project_IOinterface_cal,
      sizeof(Project_IOinterface_cal_type), 2 }
  };

  SegmentVector &getSegmentVector(void)
  {
    return segmentInfo;
  }
}                                      // slrealtime
