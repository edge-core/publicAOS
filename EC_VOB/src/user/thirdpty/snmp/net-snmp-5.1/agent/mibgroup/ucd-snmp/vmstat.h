/*
 *  vmstat mib groups
 *
 */
#ifndef _MIBGROUP_VMSTAT_H
#define _MIBGROUP_VMSTAT_H

#include "mibdefs.h"

FindVarMethod   var_extensible_vmstat;
void            init_vmstat(void);

#define SWAPIN 3
#define SWAPOUT 4
#define IOSENT 5
#define IORECEIVE 6
#define SYSINTERRUPTS 7
#define SYSCONTEXT 8
#define CPUUSER 9
#define CPUSYSTEM 10
#define CPUIDLE 11
#define CPUERROR 16
#define CPURAWUSER 50
#define CPURAWNICE 51
#define CPURAWSYSTEM 52
#define CPURAWIDLE 53
#define CPURAWWAIT 54
#define CPURAWKERNEL 55
#define CPURAWINTR 56
#define IORAWSENT 57
#define IORAWRECEIVE 58
#define SYSRAWINTERRUPTS 59
#define SYSRAWCONTEXT 60

#endif                          /* _MIBGROUP_VMSTAT_H */
