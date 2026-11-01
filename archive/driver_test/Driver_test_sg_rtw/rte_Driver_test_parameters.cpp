#include "rte_Driver_test_parameters.h"
#include "Driver_test.h"
#include "Driver_test_cal.h"

RTE_Param_Service_T RTE_Param_Service = {
  { 0.9334536910863247, 3.8485463562491067E-9, 7.6097610140543829E-5,
    2.035463304789765E-15, 6.95261359487569E-11, 0.00063929394885868442,
    0.99999992555482542, -0.00045847509186959252, 1.277731260930199E-6,
    0.025813682567267147, -2.7323285120838379, 9.9996347350456716E-5,
    0.99989114527813072, 8.9281183677210485E-11, 2.2317795085208191E-6,
    13.64206026578767, -0.11885518937559372, -0.31579607245192115,
    0.96977871425254869, -4.5932822759972289, 0.000685948999931411,
    -5.9728829322094513E-6, -1.5863394067539254E-5, 9.8485047735660886E-5,
    0.99976824612773574 },

  { 0.079724992592930713, 1.0643936518390492E-10, 3.1750507906334543E-6,
    3.8724608144611649E-17, 1.6910495623598827E-12, -13.642699559736529,
    0.11885526382076832, 0.31625454754379079, 0.030220008016190326,
    4.5674685934299619 },

  { 0.542947631478922, 4935.6390857833476, 104.61213809610098, -979.581296455713,
    329.13560367151928 },
  10000.000000000244,
  5.0,
  0.3,
  5.0
};

RTE_Param_Service_T *RTE_Param_Service_ptr = &RTE_Param_Service;
real_T* get_Ao(void)
{
  return RTE_Param_Service_ptr->Ao;
}

real_T* get_Bo(void)
{
  return RTE_Param_Service_ptr->Bo;
}

real_T* get_K(void)
{
  return RTE_Param_Service_ptr->K;
}

real_T* get_Ke(void)
{
  return &RTE_Param_Service_ptr->Ke;
}

real_T* get_tExc(void)
{
  return &RTE_Param_Service_ptr->tExc;
}

real_T* get_vBias(void)
{
  return &RTE_Param_Service_ptr->vBias;
}

real_T* get_vMax(void)
{
  return &RTE_Param_Service_ptr->vMax;
}

extern Driver_test_cal_type Driver_test_cal_impl;
extern RTE_Param_Service_T RTE_Param_Service;
namespace slrealtime
{
  /* Description of SEGMENTS */
  SegmentVector segmentInfo {
    { (void*)&RTE_Param_Service, (void**)&RTE_Param_Service_ptr, sizeof
      (RTE_Param_Service_T), 2 },

    { (void*)&Driver_test_cal_impl, (void**)&Driver_test_cal, sizeof
      (Driver_test_cal_type), 2 }
  };

  SegmentVector &getSegmentVector(void)
  {
    return segmentInfo;
  }
}                                      // slrealtime
