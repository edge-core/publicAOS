/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.old-api.conf,v 1.3 2002/10/17 09:40:46 dts12 Exp $
 */
#ifndef DOT3ADAGGTABLE_H
#define DOT3ADAGGTABLE_H

/*
 * function declarations 
 */
void            init_dot3adAggTable(void);
FindVarMethod   var_dot3adAggTable;
WriteMethod     write_dot3adAggActorSystemPriority;
WriteMethod     write_dot3adAggActorAdminKey;
WriteMethod     write_dot3adAggCollectorMaxDelay;

void            init_dot3adAggPortListTable(void);
FindVarMethod   var_dot3adAggPortListTable;

void            init_dot3adAggPortTable(void);
FindVarMethod   var_dot3adAggPortTable;
WriteMethod     write_dot3adAggPortActorSystemPriority;
WriteMethod     write_dot3adAggPortActorAdminKey;
WriteMethod     write_dot3adAggPortActorOperKey;
WriteMethod     write_dot3adAggPortPartnerAdminSystemPriority;
WriteMethod     write_dot3adAggPortPartnerAdminSystemID;
WriteMethod     write_dot3adAggPortPartnerAdminKey;
WriteMethod     write_dot3adAggPortActorPortPriority;
WriteMethod     write_dot3adAggPortPartnerAdminPort;
WriteMethod     write_dot3adAggPortPartnerAdminPortPriority;
WriteMethod     write_dot3adAggPortActorAdminState;
WriteMethod     write_dot3adAggPortPartnerAdminState;

void            init_dot3adAggPortStatsTable(void);
FindVarMethod   var_dot3adAggPortStatsTable;

void            init_dot3adAggPortDebugTable(void);
FindVarMethod   var_dot3adAggPortDebugTable;

void            init_lagMIBObjects(void);
Netsnmp_Node_Handler get_dot3adTablesLastChanged;
#endif                          /* DOT3ADAGGTABLE_H */
