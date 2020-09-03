/* MODULE NAME:  fdry_tacacs.h
 *
 * PURPOSE: For SNMP to access Brocade's FDRY-TACACS-MIB:
 *
 * foundry(1991).products(1).switch(1).fdryTacacs(9).fdryTacacsMIB(1)
 *
 * NOTES:
 *
 * HISTORY (mm/dd/yyyy)
 *    04/25/2011 - Qiyao Zhong, Created
 *
 * Copyright(C)      Accton Corporation, 2011
 */

/* Note: this file originally auto-generated by mib2c using
 *        : mib2c.scalar.conf,v 1.5 2002/07/18 14:18:52 dts12 Exp $
 */
#ifndef FDRY_TACACS_H
#define FDRY_TACACS_H

/* FDRY-TACACS-MIB.fdryTacacsServerTable
 */

/* function declarations
 */

#if (SYS_CPNT_TACACS == TRUE)  /* from near-beginning to end of file */
/* ------------------------------------------------------------------------
 * TABLE NAME - fdryTacacsServerTable
 * ------------------------------------------------------------------------
 */
void init_fdryTacacsServerTable(void);
FindVarMethod var_fdryTacacsServerTable;
WriteMethod write_fdryTacacsServerAddrType;
WriteMethod write_fdryTacacsServerAddr;
WriteMethod write_fdryTacacsServerAuthPort;
WriteMethod write_fdryTacacsServerRowKey;
WriteMethod write_fdryTacacsServerUsage;
WriteMethod write_fdryTacacsServerRowStatus;

#endif  /* (SYS_CPNT_TACACS == TRUE); from near-beginning to end of file */
#endif  /* FDRY_TACACS_H */