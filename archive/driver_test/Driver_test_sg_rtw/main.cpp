/* Main generated for Simulink Real-Time model Driver_test */
#include <ModelInfo.hpp>
#include <utilities.hpp>
#include "Driver_test.h"
#include "rte_Driver_test_parameters.h"

/* Task wrapper function definitions */
void Driver_test_Task1(void)
{ 
    Driver_test_step();
} 
/* Task descriptors */
slrealtime::TaskInfo task_1( 0u, std::bind(Driver_test_Task1), slrealtime::TaskInfo::PERIODIC, 0.0001, 0, 40);

/* Executable base address for XCP */
#ifdef __linux__
extern char __executable_start;
static uintptr_t const base_address = reinterpret_cast<uintptr_t>(&__executable_start);
#else
/* Set 0 as placeholder, to be parsed later from /proc filesystem */
static uintptr_t const base_address = 0;
#endif

/* Model descriptor */
slrealtime::ModelInfo Driver_test_Info =
{
    "Driver_test",
    Driver_test_initialize,
    Driver_test_terminate,
    []()->char const*& { return Driver_test_M->errorStatus; },
    []()->unsigned char& { return Driver_test_M->Timing.stopRequestedFlag; },
    { task_1 },
    slrealtime::getSegmentVector()
};

int main(int argc, char *argv[]) {
    slrealtime::BaseAddress::set(base_address);
    return slrealtime::runModel(argc, argv, Driver_test_Info);
}
