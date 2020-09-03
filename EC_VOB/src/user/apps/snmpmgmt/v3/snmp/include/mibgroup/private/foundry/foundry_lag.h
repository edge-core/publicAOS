/* MODULE NAME:  foundry_lag.h
 *
 * PURPOSE: For SNMP to access Brocade's FOUNDRY-LAG-MIB:
 *
 * foundry(1991).products(1).switch(1).snSwitch(3).fdryLinkAggregationGroupMIB(33)
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
#ifndef FOUNDRY_LAG_H
#define FOUNDRY_LAG_H

/* function declarations
 */

/* ------------------------------------------------------------------------
 * TABLE NAME - 1.1.3.33.1.1 fdryLinkAggregationGroupTable
 * ------------------------------------------------------------------------
 */
void init_fdryLinkAggregationGroupTable(void);
FindVarMethod var_fdryLinkAggregationGroupTable;
WriteMethod write_fdryLinkAggregationGroupType;
WriteMethod write_fdryLinkAggregationGroupAdminStatus;
WriteMethod write_fdryLinkAggregationGroupIfList;
WriteMethod write_fdryLinkAggregationGroupPrimaryPort;
WriteMethod write_fdryLinkAggregationGroupTrunkType;
WriteMethod write_fdryLinkAggregationGroupTrunkThreshold;
WriteMethod write_fdryLinkAggregationGroupLacpTimeout;
WriteMethod write_fdryLinkAggregationGroupRowStatus;

/* ------------------------------------------------------------------------
 * FUNCTION NAME - init_fdryLinkAggregationGroupMIB
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
void init_fdryLinkAggregationGroupMIB(void);

#endif  /* FOUNDRY_LAG_H */