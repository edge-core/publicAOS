/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.scalar.conf,v 1.5 2002/07/18 14:18:52 dts12 Exp $
 */
#ifndef IPFORWARD_H
#define IPFORWARD_H

/*
 * function declarations
 */
void            init_ipForwardNumber(void);
Netsnmp_Node_Handler get_ipForwardNumber;

/*
 * function declarations
 */
void            init_ipCidrRouteNumber(void);
Netsnmp_Node_Handler get_ipCidrRouteNumber;

/*
 * function declarations
 */
void            init_ipCidrRouteTable(void);
FindVarMethod   var_ipCidrRouteTable;
FindVarMethod   var_ipCidrRouteTable;
WriteMethod     write_ipCidrRouteIfIndex;
WriteMethod     write_ipCidrRouteType;
WriteMethod     write_ipCidrRouteInfo;
WriteMethod     write_ipCidrRouteNextHopAS;
WriteMethod     write_ipCidrRouteMetric1;
WriteMethod     write_ipCidrRouteMetric2;
WriteMethod     write_ipCidrRouteMetric3;
WriteMethod     write_ipCidrRouteMetric4;
WriteMethod     write_ipCidrRouteMetric5;
WriteMethod     write_ipCidrRouteStatus;

#endif                          /* IPFORWARD_H */