#include "rte_Project_Controller_parameters.h"
#include "Project_Controller.h"
#include "Project_Controller_cal.h"

RTE_Param_Service_T RTE_Param_Service = {
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

  { 0.11958431418232265, 2.7388448209125713E-10, 8.1698394857585748E-6,
    1.0021591746327627E-16, 4.3514162153532976E-12, 1.7704744915798965E-19,
    -97.014085323933173, 0.54594015317761269, 2.1517075089995878,
    0.094553344956826033, 10.025727544481333, 0.033797564811430231 },

  { 0.64927283209661546, 3500.0520919684532, 65.486337041810117,
    -1537.496750264834, 254.04569775122593, 52.998100875366816 },
  5000.0000000005994,
  0.015,
  0.005,
  5.0,

  { -5.0, 5.0 },
  0.6,
  0.0006449771016251983,

  { 3.5167970380470019, 3.5167970380470019 },

  { 0.0, 0.0016, 0.0, 0.0016, 0.0, 0.0016 }
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

real_T* get_rHigh(void)
{
  return &RTE_Param_Service_ptr->rHigh;
}

real_T* get_rLow(void)
{
  return &RTE_Param_Service_ptr->rLow;
}

real_T* get_tExc(void)
{
  return &RTE_Param_Service_ptr->tExc;
}

real_T* get_uLim(void)
{
  return RTE_Param_Service_ptr->uLim;
}

real_T* get_vBias(void)
{
  return &RTE_Param_Service_ptr->vBias;
}

real_T* get_xN0(void)
{
  return &RTE_Param_Service_ptr->xN0;
}

real_T* get_xPre0(void)
{
  return RTE_Param_Service_ptr->xPre0;
}

real_T* get_xhat0(void)
{
  return RTE_Param_Service_ptr->xhat0;
}

extern Project_Controller_cal_type Project_Controller_cal_impl;
extern RTE_Param_Service_T RTE_Param_Service;
namespace slrealtime
{
  /* Description of SEGMENTS */
  SegmentVector segmentInfo {
    { (void*)&RTE_Param_Service, (void**)&RTE_Param_Service_ptr, sizeof
      (RTE_Param_Service_T), 2 },

    { (void*)&Project_Controller_cal_impl, (void**)&Project_Controller_cal,
      sizeof(Project_Controller_cal_type), 2 }
  };

  SegmentVector &getSegmentVector(void)
  {
    return segmentInfo;
  }
}                                      // slrealtime
