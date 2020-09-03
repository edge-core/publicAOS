/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.old-api.conf,v 1.3 2002/10/17 09:40:46 dts12 Exp $
 */
#ifndef DIFFSERVDATAPATHTABLE_H
#define DIFFSERVDATAPATHTABLE_H

/*
 * function declarations 
 */
void            init_diffServDataPathTable(void);
FindVarMethod   var_diffServDataPathTable;
WriteMethod     write_diffServDataPathStart;
WriteMethod     write_diffServDataPathStorage;
WriteMethod     write_diffServDataPathStatus;

void            init_diffServClfrTable(void);
FindVarMethod   var_diffServClfrTable;
WriteMethod     write_diffServClfrStorage;
WriteMethod     write_diffServClfrStatus;

void            init_diffServClfrElementTable(void);
FindVarMethod   var_diffServClfrElementTable;
WriteMethod     write_diffServClfrElementPrecedence;
WriteMethod     write_diffServClfrElementNext;
WriteMethod     write_diffServClfrElementSpecific;
WriteMethod     write_diffServClfrElementStorage;
WriteMethod     write_diffServClfrElementStatus;

void            init_diffServMultiFieldClfrTable(void);
FindVarMethod   var_diffServMultiFieldClfrTable;
WriteMethod     write_diffServMultiFieldClfrAddrType;
WriteMethod     write_diffServMultiFieldClfrDstAddr;
WriteMethod     write_diffServMultiFieldClfrDstPrefixLength;
WriteMethod     write_diffServMultiFieldClfrSrcAddr;
WriteMethod     write_diffServMultiFieldClfrSrcPrefixLength;
WriteMethod     write_diffServMultiFieldClfrDscp;
WriteMethod     write_diffServMultiFieldClfrFlowId;
WriteMethod     write_diffServMultiFieldClfrProtocol;
WriteMethod     write_diffServMultiFieldClfrDstL4PortMin;
WriteMethod     write_diffServMultiFieldClfrDstL4PortMax;
WriteMethod     write_diffServMultiFieldClfrSrcL4PortMin;
WriteMethod     write_diffServMultiFieldClfrSrcL4PortMax;
WriteMethod     write_diffServMultiFieldClfrStorage;
WriteMethod     write_diffServMultiFieldClfrStatus;

void            init_diffServActionTable(void);
FindVarMethod   var_diffServActionTable;
WriteMethod     write_diffServActionInterface;
WriteMethod     write_diffServActionNext;
WriteMethod     write_diffServActionSpecific;
WriteMethod     write_diffServActionStorage;
WriteMethod     write_diffServActionStatus;

void            init_diffServMeterTable(void);
FindVarMethod   var_diffServMeterTable;
WriteMethod     write_diffServMeterSucceedNext;
WriteMethod     write_diffServMeterFailNext;
WriteMethod     write_diffServMeterSpecific;
WriteMethod     write_diffServMeterStorage;
WriteMethod     write_diffServMeterStatus;

void            init_diffServTBParamTable(void);
FindVarMethod   var_diffServTBParamTable;
WriteMethod     write_diffServTBParamType;
WriteMethod     write_diffServTBParamRate;
WriteMethod     write_diffServTBParamBurstSize;
WriteMethod     write_diffServTBParamInterval;
WriteMethod     write_diffServTBParamStorage;
WriteMethod     write_diffServTBParamStatus;

void            init_diffServDscpMarkActTable(void);
FindVarMethod   var_diffServDscpMarkActTable;

void            init_diffServAlgDropTable(void);
FindVarMethod   var_diffServAlgDropTable;
WriteMethod     write_diffServAlgDropType;
WriteMethod     write_diffServAlgDropNext;
WriteMethod     write_diffServAlgDropQMeasure;
WriteMethod     write_diffServAlgDropQThreshold;
WriteMethod     write_diffServAlgDropSpecific;
WriteMethod     write_diffServAlgDropStorage;
WriteMethod     write_diffServAlgDropStatus;

void            init_diffServClassifier(void);
Netsnmp_Node_Handler get_diffServClfrElementNextFree;
Netsnmp_Node_Handler get_diffServClfrNextFree;
Netsnmp_Node_Handler get_diffServMultiFieldClfrNextFree;

void            init_diffServAction(void);
Netsnmp_Node_Handler get_diffServActionNextFree;
Netsnmp_Node_Handler get_diffServCountActNextFree;

void            init_diffServMeter(void);
Netsnmp_Node_Handler get_diffServMeterNextFree;

void            init_diffServTBParam(void);
Netsnmp_Node_Handler get_diffServTBParamNextFree;

void            init_diffServAlgDrop(void);
Netsnmp_Node_Handler get_diffServRandomDropNextFree;
Netsnmp_Node_Handler get_diffServAlgDropNextFree;

#endif                          /* DIFFSERVDATAPATHTABLE_H */