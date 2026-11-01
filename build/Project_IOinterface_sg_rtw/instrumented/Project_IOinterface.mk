###########################################################################
## Makefile generated for component 'Project_IOinterface'. 
## 
## Makefile     : Project_IOinterface.mk
## Generated on : Wed Oct 21 15:50:04 2026
## Final product: $(START_DIR)/Project_IOinterface_sg_rtw/Project_IOinterface
## Product type : executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile

PRODUCT_NAME              = Project_IOinterface
MAKEFILE                  = Project_IOinterface.mk
MATLAB_ROOT               = /usr/local/MATLAB/R2025b
MATLAB_BIN                = /usr/local/MATLAB/R2025b/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/glnxa64
START_DIR                 = /home/havard/Desktop/MAS508
SOLVER                    = 
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
TGT_FCN_LIB               = ISO_C++
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 0
RELATIVE_PATH_TO_ANCHOR   = ../..
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Simulink Real-Time Toolchain
# Supported Version(s):    
# ToolchainInfo Version:   2025b
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# SLREALTIME_QNX_SP_ROOT
# SLREALTIME_QNX_VERSION

#-----------
# MACROS
#-----------

QCC_TARGET             = gcc_ntox86_64

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = -L$(MATLAB_ROOT)/toolbox/slrealtime/target/glnxa64/target/lib -ltraceparser -lpps -lslrealtime_kernel -lslrealtime_platform -lslrealtime_rtps -lsocket -lboost_system -lboost_log -lpci -lopenblas -lpcap

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: QNX C Compiler
CC = qcc

# Linker: QCC Linker
LD = q++

# C++ Compiler: QNX C++ Compiler
CPP = q++

# C++ Linker: QCC C++ Linker
CPP_LD = q++

# Archiver: QNX Archiver
AR = ntox86_64-gcc-ar

# Builder: GMAKE Utility
MAKE = bash $SLREALTIME_CODER_TOOLS/slrtmake.sh


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g -O0 -finstrument-functions
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g -O0 -finstrument-functions
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
RM                  = @rm -f
ECHO                = @echo
MV                  = @mv
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c -V$(QCC_TARGET) -g \
                       -O2 -fwrapv
CPPFLAGS             = -c -V$(QCC_TARGET) -g -std=gnu++14 -stdlib=libstdc++ \
                       -O2 -fwrapv
CPP_LDFLAGS          = -V$(QCC_TARGET) -g -std=gnu++14 -stdlib=libstdc++
CPP_SHAREDLIB_LDFLAGS  = -V$(QCC_TARGET) -shared -Wl,--no-undefined -g
LDFLAGS              = -V$(QCC_TARGET) -g -std=gnu++14 -stdlib=libstdc++
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -V$(QCC_TARGET) -shared -Wl,--no-undefined -g



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(START_DIR)/Project_IOinterface_sg_rtw/Project_IOinterface
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Top-Level Standalone Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -I$(START_DIR)/Project_IOinterface_sg_rtw -I$(MATLAB_ROOT)/toolbox/slrealtime/simulink/blocks/dist/include -I$(MATLAB_ROOT)/toolbox/slrealtime/target/kernel/dist/include -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I/home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/common/libsg -I/home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0 -I/home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/analog/include -I$(START_DIR)/Project_IOinterface_sg_rtw/instrumented

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -DSIMULINK_REAL_TIME -D_QNX_SOURCE -DFMU_CG_TARGET=30
DEFINES_BUILD_ARGS = -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DEXT_MODE=1 -DMAT_FILE=0 -DONESTEPFCN=1 -DTERMFCN=1 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0
DEFINES_CUSTOM = 
DEFINES_OPTS = -DTID01EQ=0
DEFINES_STANDARD = -DMODEL=Project_IOinterface -DNUMST=1 -DNCSTATES=0 -DHAVESTDIO -DRT -DUSE_RTMODEL

DEFINES = $(DEFINES_) $(DEFINES_BUILD_ARGS) $(DEFINES_CUSTOM) $(DEFINES_OPTS) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(MATLAB_ROOT)/rtw/c/src/rt_matrx.c $(MATLAB_ROOT)/rtw/c/src/rt_printf.c $(START_DIR)/Project_IOinterface_sg_rtw/Project_IOinterface.cpp $(START_DIR)/Project_IOinterface_sg_rtw/Project_IOinterface_cal.cpp $(START_DIR)/Project_IOinterface_sg_rtw/rtGetInf.cpp $(START_DIR)/Project_IOinterface_sg_rtw/rtGetNaN.cpp $(START_DIR)/Project_IOinterface_sg_rtw/rt_nonfinite.cpp $(START_DIR)/Project_IOinterface_sg_rtw/slrealtime_datatype_ground.cpp $(START_DIR)/Project_IOinterface_sg_rtw/rte_Project_IOinterface_parameters.cpp $(START_DIR)/Project_IOinterface_sg_rtw/main.cpp /home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/analog/sg_IO183_ad_s.c /home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/analog/sg_IO183_da_s.c /home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/analog/sg_IO183_setup_s.c host_timer_x86.c slrealtime_code_profiling_utility_functions.cpp

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = rt_matrx.o rt_printf.o Project_IOinterface.o Project_IOinterface_cal.o rtGetInf.o rtGetNaN.o rt_nonfinite.o slrealtime_datatype_ground.o rte_Project_IOinterface_parameters.o main.o sg_IO183_ad_s.o sg_IO183_da_s.o sg_IO183_setup_s.o host_timer_x86.o slrealtime_code_profiling_utility_functions.o

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_ = -lsg_qnx710_x86_64 -L/home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/common/libsg

CPP_LDFLAGS += $(CPP_LDFLAGS_)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_ = -lsg_qnx710_x86_64 -L/home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/common/libsg

CPP_SHAREDLIB_LDFLAGS += $(CPP_SHAREDLIB_LDFLAGS_)

#-----------
# Linker
#-----------

LDFLAGS_ = -lsg_qnx710_x86_64 -L/home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/common/libsg

LDFLAGS += $(LDFLAGS_)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_ = -lsg_qnx710_x86_64 -L/home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/common/libsg

SHAREDLIB_LDFLAGS += $(SHAREDLIB_LDFLAGS_)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS)
	@echo "### Successfully generated all binary outputs."


prebuild : 


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(CPP_LD) $(CPP_LDFLAGS) -o $(PRODUCT) $(OBJS) -Wl,--start-group $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS) -Wl,--end-group
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


%.o : /home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : /home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/%.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


%.o : /home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/analog/src/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : /home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/analog/src/%.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


%.o : /home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/analog/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : /home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/analog/%.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


%.o : $(START_DIR)/Project_IOinterface_sg_rtw/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : $(START_DIR)/Project_IOinterface_sg_rtw/%.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


%.o : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


%.o : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : $(MATLAB_ROOT)/simulink/src/%.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


%.o : $(MATLAB_ROOT)/toolbox/simulink/blocks/src/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : $(MATLAB_ROOT)/toolbox/simulink/blocks/src/%.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


%.o : ../%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : ../%.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


%.o : $(MATLAB_ROOT)/toolbox/coder/profile/src/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : $(MATLAB_ROOT)/toolbox/coder/profile/src/%.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


%.o : $(START_DIR)/Project_IOinterface_sg_rtw/instrumented/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : $(START_DIR)/Project_IOinterface_sg_rtw/instrumented/%.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


rt_matrx.o : $(MATLAB_ROOT)/rtw/c/src/rt_matrx.c
	$(CC) $(CFLAGS) -o $@ $<


rt_printf.o : $(MATLAB_ROOT)/rtw/c/src/rt_printf.c
	$(CC) $(CFLAGS) -o $@ $<


Project_IOinterface.o : $(START_DIR)/Project_IOinterface_sg_rtw/Project_IOinterface.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


Project_IOinterface_cal.o : $(START_DIR)/Project_IOinterface_sg_rtw/Project_IOinterface_cal.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


rtGetInf.o : $(START_DIR)/Project_IOinterface_sg_rtw/rtGetInf.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


rtGetNaN.o : $(START_DIR)/Project_IOinterface_sg_rtw/rtGetNaN.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


rt_nonfinite.o : $(START_DIR)/Project_IOinterface_sg_rtw/rt_nonfinite.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


slrealtime_datatype_ground.o : $(START_DIR)/Project_IOinterface_sg_rtw/slrealtime_datatype_ground.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


rte_Project_IOinterface_parameters.o : $(START_DIR)/Project_IOinterface_sg_rtw/rte_Project_IOinterface_parameters.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


main.o : $(START_DIR)/Project_IOinterface_sg_rtw/main.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<


sg_IO183_ad_s.o : /home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/analog/sg_IO183_ad_s.c
	$(CC) $(CFLAGS) -o $@ $<


sg_IO183_da_s.o : /home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/analog/sg_IO183_da_s.c
	$(CC) $(CFLAGS) -o $@ $<


sg_IO183_setup_s.o : /home/havard/.speedgoat/speedgoatlib/R2025b/9.11.0/sg_blocks/analog/sg_IO183_setup_s.c
	$(CC) $(CFLAGS) -o $@ $<


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files ..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


