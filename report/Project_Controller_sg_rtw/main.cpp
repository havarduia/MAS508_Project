/* Main generated for Simulink Real-Time model Project_Controller */
#include <ModelInfo.hpp>
#include <utilities.hpp>
#include "Project_Controller.h"
#include "rte_Project_Controller_parameters.h"

/* Task wrapper function definitions */
void Project_Controller_Task1(void)
{ 
    Project_Controller_step();
} 
/* Task descriptors */
slrealtime::TaskInfo task_1( 0u, std::bind(Project_Controller_Task1), slrealtime::TaskInfo::PERIODIC, 0.0001, 0, 40);

/* Executable base address for XCP */
#ifdef __linux__
extern char __executable_start;
static uintptr_t const base_address = reinterpret_cast<uintptr_t>(&__executable_start);
#else
/* Set 0 as placeholder, to be parsed later from /proc filesystem */
static uintptr_t const base_address = 0;
#endif

/* Model descriptor */
slrealtime::ModelInfo Project_Controller_Info =
{
    "Project_Controller",
    Project_Controller_initialize,
    Project_Controller_terminate,
    []()->char const*& { return Project_Controller_M->errorStatus; },
    []()->unsigned char& { return Project_Controller_M->Timing.stopRequestedFlag; },
    { task_1 },
    slrealtime::getSegmentVector()
};

int main(int argc, char *argv[]) {
    slrealtime::BaseAddress::set(base_address);
    return slrealtime::runModel(argc, argv, Project_Controller_Info);
}
