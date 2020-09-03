/*
 *  snmp_bgp.h
 *
 */
#ifndef _MIBGROUP_SNMP_BGP_H
#define _MIBGROUP_SNMP_BGP_H

config_require(smux/smux)

     extern FindVarMethod var_bgp;
     extern void     init_snmp_bgp(void);


#define BGPVERSION			0
#define BGPLOCALAS			1
#define BGPIDENTIFIER			2
#define BGPPEERIDENTIFIER		3
#define BGPPEERSTATE			4
#define BGPPEERADMINSTATUS		5
#define BGPPEERNEGOTIATEDVERSION	6
#define BGPPEERLOCALADDR		7
#define BGPPEERLOCALPORT		8
#define BGPPEERREMOTEADDR		9
#define BGPPEERREMOTEPORT		10
#define BGPPEERREMOTEAS			11
#define BGPPEERINUPDATES		12
#define BGPPEEROUTUPDATES		13
#define BGPPEERINTOTALMESSAGES		14
#define BGPPEEROUTTOTALMESSAGES		15
#define BGPPEERLASTERROR		16
#define BGPPATHATTRPEER			17
#define BGPPATHATTRDESTNETWORK		18
#define BGPPATHATTRORIGIN		19
#define BGPPATHATTRASPATH		20
#define BGPPATHATTRNEXTHOP		21
#define BGPPATHATTRINTERASMETRIC	22

#endif                          /* _MIBGROUP_SNMP_BGP_H */
