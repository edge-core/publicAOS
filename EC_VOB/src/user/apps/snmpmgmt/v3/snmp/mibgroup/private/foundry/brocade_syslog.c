/* MODULE NAME:  brocade_syslog.c
 *
 * PURPOSE: For SNMP to access Brocade's BROCADE-SYSLOG-MIB:
 *
 * foundry(1991).products(1).switch(1).brcdSysLog(17).brocadeSysLogMIB(1)
 *
 * NOTES:
 *
 * HISTORY (mm/dd/yyyy)
 *    12/12/2011 - Qiyao Zhong, Created
 *
 * Copyright(C)      Accton Corporation, 2011
 */

/* Note: this file originally auto-generated by mib2c using
 *        : mib2c.old-api.conf,v 1.4 2004/07/28 08:04:58 dts12 Exp $
 */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include "sys_type.h"
#include "sys_adpt.h"
#include "sys_cpnt.h"
#include "leaf_brocade_syslog.h"

#include "snmp_mgr.h"
#include "sysORTable.h"
#include "foundry_lib.h"
#include "brocade_syslog.h"

#if (SYS_CPNT_SYSLOG == TRUE)
#if (SYS_CPNT_REMOTELOG == TRUE)
#include "syslog_pmgr.h"
#endif  /* #if (SYS_CPNT_REMOTELOG == TRUE) */
#endif  /* #if (SYS_CPNT_SYSLOG == TRUE) */

/* STATIC VARIABLE DEFINITIONS
 */

#if (SYS_CPNT_SYSLOG == TRUE)  /* from near-beginning to end of file */
#if (SYS_CPNT_REMOTELOG == TRUE)  /* from near-beginning to end of file */
/* ------------------------------------------------------------------------
 * TABLE NAME - brcdSysLogServerTable
 * ------------------------------------------------------------------------
 */
oid brcdSysLogServerTable_variables_oid[] = { 1,3,6,1,4,1,1991,1,1,11,1,1 };

/* variable3 brcdSysLogServerTable_variables:
 *   this variable defines function callbacks and type return information
 *   for the  mib section
 */
struct variable3 brcdSysLogServerTable_variables[] =
{
    /* magic number, variable type, ro/rw, callback fn, L, oidsuffix
     *     (L = length of the oidsuffix)
     */
#if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1)
    { LEAF_brcdSysLogServerAddrType, ASN_INTEGER, RONLY, var_brcdSysLogServerTable, 3, { 1, 1, 1 }},
#endif  /* #if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1) */

#if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1)
    { LEAF_brcdSysLogServerAddr, ASN_OCTET_STR, RONLY, var_brcdSysLogServerTable, 3, { 1, 1, 2 }},
#endif  /* #if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1) */

#if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1)
    { LEAF_brcdSysLogServerUDPPort, ASN_UNSIGNED, RONLY, var_brcdSysLogServerTable, 3, { 1, 1, 3 }},
#endif  /* #if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1) */

#if 0  /* not supported */
    { LEAF_brcdSysLogServerOutPkts, ASN_COUNTER, RONLY, var_brcdSysLogServerTable, 3, { 1, 1, 4 }},
#endif

    { LEAF_brcdSysLogServerRowStatus, ASN_INTEGER, RWRITE, var_brcdSysLogServerTable, 3, { 1, 1, 5 }},
};

void init_brcdSysLogServerTable(void)
{
    oid brocadeSysLogMIB_oid[] = { 1,3,6,1,4,1,1991,1,1,11,1 };

    /* register ourselves in the sysORTable
     */
    REGISTER_SYSOR_ENTRY(brocadeSysLogMIB_oid,
        "This MIB module contains the managed object definitions for syslog.");

    /* Register ourselves with the agent to handle our MIB tree
     */
    REGISTER_MIB("brcdSysLogServerTable", brcdSysLogServerTable_variables, variable3,
                 brcdSysLogServerTable_variables_oid);
}

#define BRCDSYSLOGSERVERENTRY_INSTANCE_LEN  23  /* manually coded for IPv6z */

BOOL_T brcdSysLogServerTable_OidIndexToData(UI32_T exact, UI32_T compc,
    oid *compl, UI32_T *brcdSysLogServerAddrType, UI8_T *brcdSysLogServerAddr, UI32_T *brcdSysLogServerAddr_length, UI32_T *brcdSysLogServerUDPPort)
{
    UI32_T i;

    /* get or set
     */
    if (exact)
    {
        /* check the index length: variable-length index
         *
         * compc < 1, means the "address content (with length-prefix)" is empty
         */
        if ((compc < 1)
            || (compc > BRCDSYSLOGSERVERENTRY_INSTANCE_LEN))  /* the dynamic size index */
        {
            return FALSE;
        }
    }

    /* get-next without index
     */
    if (compc == 0)
    {
        return TRUE;
    }

    /* get-next without address
     */
    if (compc == 1)
    {
        return TRUE;
    }

    /* copy type and length
     */
    *brcdSysLogServerAddrType = compl[0];
    *brcdSysLogServerAddr_length = compl[1]; 

    if ((compl[1] < MINSIZE_brcdSysLogServerAddr)
        || (compl[1] > MAXSIZE_brcdSysLogServerAddr))
    {
        return FALSE;
    }

    /* copy each byte of the address
     */
    for (i = 0; i < compl[1]; i++)
    {
        brcdSysLogServerAddr[i] = compl[2 + i];
    }

    /* get-next without port
     */
    if (compc <= 2 + compl[1])
    {
        return TRUE;
    }

    /* copy port
     */
    *brcdSysLogServerUDPPort = compl[2 + compl[1]];
    
    return TRUE;
}

/*
 * var_brcdSysLogServerTable():
 *   Handle this table separately from the scalar value case.
 *   The workings of this are basically the same as for var_ above.
 */
unsigned char *var_brcdSysLogServerTable(struct variable *vp,
    oid *name,
    size_t *length,
    int exact,
    size_t *var_len,
    WriteMethod **write_method)
{
    UI32_T compc = 0;
    UI32_T i;
    oid compl[BRCDSYSLOGSERVERENTRY_INSTANCE_LEN] = {0};
    oid best_inst[BRCDSYSLOGSERVERENTRY_INSTANCE_LEN] = {0};

    /* table-specific variables
     */
    L_INET_AddrIp_T entry;
    UI32_T udp_port = 0;

    /* extracted from user index sub-OID
     */
    UI32_T type = 0, addr_len = 0, preflen = 0;
    UI8_T addr_ar[SYS_TYPE_IPV6Z_ADDR_LEN] = {0};  /* longest case: IPv6z, with zone ID */

    /* dispatch node to set write method
     */
    switch (vp->magic)
    {
        case LEAF_brcdSysLogServerRowStatus:
            *write_method = write_brcdSysLogServerRowStatus;
            break;

        default:
            *write_method = 0;
            break;
    }

    /* check compc, retrive compl
     */
    SNMP_MGR_RetrieveCompl(vp->name, vp->namelen, name, *length, &compc, compl,
        BRCDSYSLOGSERVERENTRY_INSTANCE_LEN);

    memset(&entry, 0, sizeof(entry));

    /* dispatch get-exact versus get-next
     */
    if (exact)  /* get or set */
    {
        /* extract index
         */
        if (! brcdSysLogServerTable_OidIndexToData(exact, compc, compl,
            &type, addr_ar, &addr_len, &udp_port))
        {
            return NULL;
        }

        /* only fixed value for UDP port, hard-coded
         *
         * The core layer does not have a configurable port.
         * If "udp_port" is not equal to this fixed value, fail.
         */
        if (udp_port != 514)
        {
            return NULL;
        }

        /* convert to L_INET_AddrIp_T
         */
        if (! SNMP_MGR_ConvertInetAddrAndTypeToLInetAddr(type,
            addr_len, addr_ar, 0, (L_INET_Addr_T *) &entry))
        {
            return NULL;
        }

        /* get-exact from core layer
         */
        if (SYSLOG_PMGR_IsExistServerIPAddr(&entry) != SYSLOG_REMOTE_SUCCESS)
        {
            return NULL;
        }
    }
    else  /* get-next */
    {
        /* extract index
         */
        brcdSysLogServerTable_OidIndexToData(exact, compc, compl,
            &type, addr_ar, &addr_len, &udp_port);

        /* convert to L_INET_AddrIp_T
         */
        if (! SNMP_MGR_ConvertInetAddrAndTypeToLInetAddr(type,
            addr_len, addr_ar, 0, (L_INET_Addr_T *) &entry))
        {
            return NULL;
        }

        /* Check the length of inputing index.  If compc is less than the
         * instance length, we should try get {A.B.C.0.0...}, where A.B.C was
         * obtained from the "..._OidIndexToData" function call, and
         * 0.0... was initialized in the beginning of this function.
         * This instance may exist in the core layer.
         */
        /* NOTE:
         * This is a variable-length index:
         * IfIndex.AddressType.length-prefixed-InetAddress.PrefixLength
         * We check length of address based on type.
         */
        if (
            /* incomplete address length
             */
            ( (type == 0)
                || ((type == VAL_brcdSysLogServerAddrType_ipv4)
                    && (addr_len < SYS_TYPE_IPV4_ADDR_LEN))
                || ((type == VAL_brcdSysLogServerAddrType_ipv6)
                    && (addr_len < SYS_TYPE_IPV6_ADDR_LEN))
                || ((type == VAL_brcdSysLogServerAddrType_ipv4z)
                    && (addr_len < SYS_TYPE_IPV4Z_ADDR_LEN))
                || ((type == VAL_brcdSysLogServerAddrType_ipv6z)
                    && (addr_len < SYS_TYPE_IPV6Z_ADDR_LEN)) )

            /* or, port less than fixed value
             *
             * The core layer does not have a configurable port.
             *
             * If "upd_port < PORT", then
             * SNMP.GetNext(address, port) = OM.Get(address) if Get exists, or
             * SNMP.GetNext(address, port) = OM.GetNext(address) if Get does not exist
             *
             * If "udp_port >= PORT", then
             * SNMP.GetNext(address, port) = OM.GetNext(address)
             */
            || (udp_port < 514) )
        {
            /* get-exact, in case this instance exists
             */
            if (SYSLOG_PMGR_IsExistServerIPAddr(&entry) != SYSLOG_REMOTE_SUCCESS)
            {
                /* get-next according to lexicographic order; if none, fail
                 */
                if (SYSLOG_PMGR_GetNextServerIPAddr(&entry) != SYSLOG_REMOTE_SUCCESS)
                {
                    return NULL;
                }
            }
        }
        else   /* complete index */
        {
            /* get-next according to lexicographic order; if none, fail
             */
            if (SYSLOG_PMGR_GetNextServerIPAddr(&entry) != SYSLOG_REMOTE_SUCCESS)
            {
                return NULL;
            }
        }
    }

    /* copy base OID (without index) to output
     */
    memcpy(name, vp->name, vp->namelen * sizeof(oid));

    /* convert L_INET_AddrIp_T back to SNMP values
     */
    if (! SNMP_MGR_ConvertLInetAddrToInetAddrAndType(
        (L_INET_Addr_T *) &entry,
        &type, &addr_len, addr_ar, &preflen))
    {
        /* conversion failed
         */
        return NULL;
    }

    udp_port = 514;  /* hard-coded value, and does not participate in get-next */

    /* assign data to the OID index
     */
    best_inst[0] = type;
    best_inst[1] = addr_len;

    for (i = 0; i < best_inst[1]; i++)
    {
        best_inst[2 + i] = addr_ar[i];
    }

    best_inst[2 + best_inst[1]] = udp_port;
    memcpy(name + vp->namelen, best_inst, (3 + best_inst[1]) * sizeof(oid));
    *length = vp->namelen + 3 + best_inst[1];

    /* dispatch node to read value
     */
    switch (vp->magic)
    {
#if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1)
        case LEAF_brcdSysLogServerAddrType:
            *var_len = 4;
            long_return = type;
            return (u_char *) &long_return;
#endif  /* #if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1) */

#if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1)
        case LEAF_brcdSysLogServerAddr:
            *var_len = addr_len;
            memcpy(return_buf, addr_ar, *var_len);
            return (u_char *) return_buf;
#endif  /* #if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1) */

#if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1)
        case LEAF_brcdSysLogServerUDPPort:
            *var_len = 4;
            long_return = udp_port;
            return (u_char *) &long_return;
#endif  /* #if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1) */

#if 0  /* not supported */
        case LEAF_brcdSysLogServerOutPkts:
            *var_len = 4;
            long_return = 0;  /* not supported */
            return (u_char *) &long_return;
#endif

        case LEAF_brcdSysLogServerRowStatus:
            *var_len = 4;
            long_return = VAL_brcdSysLogServerRowStatus_active;  /* fixed value */
            return (u_char *) &long_return;

        default:
            ERROR_MSG("");
            break;
    }

    /* return failure
     */
    return NULL;
}

int write_brcdSysLogServerRowStatus(int action,
    u_char *var_val,
    u_char var_val_type,
    size_t var_val_len,
    u_char *statP,
    oid *name,
    size_t name_len)
{
    /* extracted from user index sub-OID
     */
    UI32_T type = 0, addr_len = 0;
    UI8_T addr_ar[SYS_TYPE_IPV6Z_ADDR_LEN] = {0};  /* longest case: IPv6z, with zone ID */

    /* dispatch action
     */
    switch (action)
    {
        case RESERVE1:
            /* check type and length
             */
            if (var_val_type != ASN_INTEGER)
            {
                return SNMP_ERR_WRONGTYPE;
            }
            break;

        case RESERVE2:
            /* check valid values
             */
            switch (*(long *) var_val)
            {
                case VAL_brcdSysLogServerRowStatus_active:
                    break;

                case VAL_brcdSysLogServerRowStatus_notInService:
                case VAL_brcdSysLogServerRowStatus_notReady:
                    return SNMP_ERR_WRONGVALUE;
                    break;

                case VAL_brcdSysLogServerRowStatus_createAndGo:
                case VAL_brcdSysLogServerRowStatus_createAndWait:
                case VAL_brcdSysLogServerRowStatus_destroy:
                    break;

                default:
                    return SNMP_ERR_WRONGVALUE;
            }
            break;

        case FREE:
            break;

        case ACTION:
        {
            UI32_T oid_name_length = 15;
            I32_T value = 0;

            /* table-specific variables
             */
            L_INET_AddrIp_T entry;
            UI32_T brcdSysLogServerUDPPort = 0;

            /* extract index
             */
            if (! brcdSysLogServerTable_OidIndexToData(TRUE,
                name_len - oid_name_length,
                &(name[oid_name_length]),
                &type, addr_ar, &addr_len, &brcdSysLogServerUDPPort))
            {
                return SNMP_ERR_COMMITFAILED;
            }

            /* only support IPv4(z) and IPv6(z)
             */
            if ( (type < VAL_dnsHostAddrInetAddressType_ipv4)
                || (type > VAL_dnsHostAddrInetAddressType_ipv6z) )
            {
                return SNMP_ERR_COMMITFAILED;
            }

            /* convert to L_INET_AddrIp_T
             */
            if (! SNMP_MGR_ConvertInetAddrAndTypeToLInetAddr(type,
                addr_len, addr_ar, 0, (L_INET_Addr_T *) &entry))
            {
                return SNMP_ERR_COMMITFAILED;
            }

            /* get user value
             */
            memcpy(&value, var_val, sizeof(I32_T));

            /* set to core layer
             */
            switch (value)
            {
                /* active: allowed only if it already exists
                 */
                case VAL_brcdSysLogServerRowStatus_active:
                    if (SYSLOG_PMGR_IsExistServerIPAddr(&entry) != SYSLOG_REMOTE_SUCCESS)
                    {
                        return SNMP_ERR_COMMITFAILED;
                    }
                    break;

                /* not supported: should not come here; already filtered in RESERVE2
                 */
                case VAL_brcdSysLogServerRowStatus_notInService:
                case VAL_brcdSysLogServerRowStatus_notReady:
                    return SNMP_ERR_WRONGVALUE;

                /* create: always results in a valid (active) entry
                 *
                 * REFERENCE: PRIVATE-MIB.remoteLogServerStatus
                 */
                case VAL_brcdSysLogServerRowStatus_createAndGo:
                case VAL_brcdSysLogServerRowStatus_createAndWait:
                {
                    /* it does not allow overwriting valid existing entry
                     */
                    if (SYSLOG_PMGR_IsExistServerIPAddr(&entry) == SYSLOG_REMOTE_SUCCESS)
                    {
                        return SNMP_ERR_COMMITFAILED;
                    }

                    /* use the index specified by the user to add a server address
                     */
                    if (SYSLOG_PMGR_AddServerIPAddr(&entry) != SYSLOG_REMOTE_SUCCESS)
                    {
                        return SNMP_ERR_COMMITFAILED;
                    }
                    break;
                }

                /* destroy: even if non-existent, the core layer should return success
                 * (RFC 2579 SNMPv2-TC)
                 */
                case VAL_brcdSysLogServerRowStatus_destroy:
                    if (SYSLOG_PMGR_DeleteServerIPAddr(&entry) != SYSLOG_REMOTE_SUCCESS)
                    {
                        return SNMP_ERR_COMMITFAILED;
                    }
                    break;

                default:
                    return SNMP_ERR_WRONGVALUE;
            }

            break;
        }

        case UNDO:
            break;

        case COMMIT:
            break;
    }

    /* return success
     */
    return SNMP_ERR_NOERROR;
}
#endif  /* (SYS_CPNT_REMOTELOG == TRUE); from near-beginning to end of file */
#endif  /* (SYS_CPNT_SYSLOG == TRUE); from near-beginning to end of file */
