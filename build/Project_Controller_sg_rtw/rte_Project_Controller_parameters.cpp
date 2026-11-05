#include "rte_Project_Controller_parameters.h"
#include "Project_Controller.h"
#include "Project_Controller_cal.h"

extern Project_Controller_cal_type Project_Controller_cal_impl;
namespace slrealtime
{
  /* Description of SEGMENTS */
  SegmentVector segmentInfo {
    { (void*)&Project_Controller_cal_impl, (void**)&Project_Controller_cal,
      sizeof(Project_Controller_cal_type), 2 }
  };

  SegmentVector &getSegmentVector(void)
  {
    return segmentInfo;
  }
}                                      // slrealtime
