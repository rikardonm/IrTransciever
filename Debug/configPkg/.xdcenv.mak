#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/grace_3_00_03_66/packages;C:/ti/msp430/driverlib_1_97_00_19/packages;C:/ti/msp430/driverlib_1_97_00_19;C:/ti/ccsv6/ccs_base
override XDCROOT = c:/ti/xdctools_3_30_06_67_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/grace_3_00_03_66/packages;C:/ti/msp430/driverlib_1_97_00_19/packages;C:/ti/msp430/driverlib_1_97_00_19;C:/ti/ccsv6/ccs_base;c:/ti/xdctools_3_30_06_67_core/packages;..
HOSTOS = Windows
endif
