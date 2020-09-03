/* MODULE NAME:  fdry_trap.h
 *
 * PURPOSE: For SNMP to access Brocade's FDRY-TRAP-MIB:
 *
 * foundry(1991).products(1).switch(1).fdryTrap(10).fdryTrapMIB(1)
 *
 * NOTES:
 *
 * HISTORY (mm/dd/yyyy)
 *    07/19/2011 - Qiyao Zhong, Created
 *
 * Copyright(C)      Accton Corporation, 2011
 */

/* Note: this file originally auto-generated by mib2c using
 *        : mib2c.scalar.conf,v 1.5 2002/07/18 14:18:52 dts12 Exp $
 */
#ifndef FDRY_TRAP_H
#define FDRY_TRAP_H

/* function declarations
 */

#if (SYS_CPNT_SNMP == TRUE)  /* from near-beginning to end of file */
/* ------------------------------------------------------------------------
 * TABLE NAME - fdryTrapReceiverTable
 * ------------------------------------------------------------------------
 */
void init_fdryTrapReceiverTable(void);
FindVarMethod var_fdryTrapReceiverTable;
WriteMethod write_fdryTrapReceiverAddrType;
WriteMethod write_fdryTrapReceiverAddr;
WriteMethod write_fdryTrapReceiverCommunityOrSecurityName;
WriteMethod write_fdryTrapReceiverUDPPort;
WriteMethod write_fdryTrapReceiverSecurityModel;
WriteMethod write_fdryTrapReceiverSecurityLevel;
WriteMethod write_fdryTrapReceiverRowStatus;

#endif  /* (SYS_CPNT_SNMP == TRUE); from near-beginning to end of file */
#endif  /* FDRY_TRAP_H */
