/* MODULE NAME:  foundry_sn_arp_group.h
 *
 * PURPOSE: For SNMP to access Brocade's FOUNDRY-SN-ARP-GROUP-MIB:
 *
 * foundry(1991).products(1).switch(1).snSwitch(3).snArpInfo(22)
 *
 * NOTES:
 *
 * HISTORY (mm/dd/yyyy)
 *    05/28/2011 - Qiyao Zhong, Created
 *
 * Copyright(C)      Accton Corporation, 2011
 */

/* Note: this file originally auto-generated by mib2c using
 *        : mib2c.old-api.conf,v 1.4 2004/07/28 08:04:58 dts12 Exp $
 */
#ifndef FOUNDRY_SN_ARP_GROUP_H
#define FOUNDRY_SN_ARP_GROUP_H

/* function declarations
 */

/* ------------------------------------------------------------------------
 * SCALAR NODES - 1.1.3.22.1 snArpStats.*
 * ------------------------------------------------------------------------
 */
void init_snArpStatsTotalReceived(void);
Netsnmp_Node_Handler get_snArpStatsTotalReceived;

void init_snArpStatsRequestReceived(void);
Netsnmp_Node_Handler get_snArpStatsRequestReceived;

void init_snArpStatsRequestSent(void);
Netsnmp_Node_Handler get_snArpStatsRequestSent;

void init_snArpStatsRepliesSent(void);
Netsnmp_Node_Handler get_snArpStatsRepliesSent;

/* ------------------------------------------------------------------------
 * FUNCTION NAME - init_snArpInfo
 * ------------------------------------------------------------------------
 * PURPOSE  :   This is the entry point into this file for initialisation.
 *
 * INPUT    :   None.
 *
 * OUTPUT   :   None.
 *
 * RETURN   :   None.
 *
 * NOTES    :   None.
 * ------------------------------------------------------------------------
 */
void init_snArpInfo(void);

#endif  /* FOUNDRY_SN_ARP_GROUP */
