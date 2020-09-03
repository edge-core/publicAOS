/* MODULE NAME:  fdry_dai.c
 *
 * PURPOSE: For SNMP to access Brocade's FDRY-DAI-MIB:
 * 
 * foundry(1991).products(1).switch(1).snSwitch(3).fdryDaiMIB(35)
 *
 * NOTES:
 *
 * HISTORY (mm/dd/yyyy)
 *    04/27/2011 - Qiyao Zhong, Created
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
#include "leaf_fdry_dai.h"
#include "l_stdlib.h"

#include "snmp_mgr.h"
#include "sysORTable.h"
#include "foundry_lib.h"
#include "fdry_dai.h"

#if (SYS_CPNT_DAI == TRUE)
#include "dai_pmgr.h"
#endif /* #if (SYS_CPNT_DAI == TRUE) */

#if (SYS_CPNT_DAI == TRUE)  /* from near-beginning to end of file */
/* ------------------------------------------------------------------------
 * TABLE NAME - fdryDaiVlanConfigTable
 * ------------------------------------------------------------------------
 */
oid fdryDaiVlanConfigTable_variables_oid[] = { 1,3,6,1,4,1,1991,1,1,3,35,1 };

/* variable3 fdryDaiVlanConfigTable_variables:
 *   this variable defines function callbacks and type return information
 *   for the  mib section
 */
struct variable3 fdryDaiVlanConfigTable_variables[] =
{
    /* magic number, variable type, ro/rw, callback fn, L, oidsuffix
     *     (L = length of the oidsuffix)
     */
#if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1)
    { LEAF_fdryDaiVlanVLanId, ASN_UNSIGNED, RONLY, var_fdryDaiVlanConfigTable, 3, { 1, 1, 1 }},
#endif /* #if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1) */

    { LEAF_fdryDaiVlanDynArpInspEnable, ASN_INTEGER, RWRITE, var_fdryDaiVlanConfigTable, 3, { 1, 1, 2 }},
};

void init_fdryDaiVlanConfigTable(void)
{
    /* Register ourselves with the agent to handle our MIB tree
     */
    REGISTER_MIB("fdryDaiVlanConfigTable", fdryDaiVlanConfigTable_variables, variable3,
                 fdryDaiVlanConfigTable_variables_oid);
}

#define FDRYDAIVLANCONFIGENTRY_INSTANCE_LEN  1

BOOL_T fdryDaiVlanConfigTable_OidIndexToData(UI32_T exact, UI32_T compc,
    oid *compl, UI32_T *fdryDaiVlanVLanId)
{
    /* get or set
     */
    if (exact)
    {
        /* check the index length
         */
        if (compc != FDRYDAIVLANCONFIGENTRY_INSTANCE_LEN) /* the constant size index */
        {
            return FALSE;
        }
    }

    *fdryDaiVlanVLanId = compl[0];

    return TRUE;
}

/*
 * var_fdryDaiVlanConfigTable():
 *   Handle this table separately from the scalar value case.
 *   The workings of this are basically the same as for var_ above.
 */
unsigned char *var_fdryDaiVlanConfigTable(struct variable *vp,
    oid *name,
    size_t *length,
    int exact,
    size_t *var_len,
    WriteMethod **write_method)
{
    UI32_T compc = 0;
    oid compl[FDRYDAIVLANCONFIGENTRY_INSTANCE_LEN] = {0};
    oid best_inst[FDRYDAIVLANCONFIGENTRY_INSTANCE_LEN] = {0};

    /* table-specific variables
     */
    DAI_TYPE_VlanInfo_T entry;
    UI32_T  vid = 0;
    UI8_T   dai_status;

    /* dispatch node to set write method
     */
    switch (vp->magic)
    {
        case LEAF_fdryDaiVlanDynArpInspEnable:
            *write_method = write_fdryDaiVlanDynArpInspEnable;
            break;

        default:
            *write_method = 0;
            break;
    }

    /* check compc, retrive compl
     */
    SNMP_MGR_RetrieveCompl(vp->name, vp->namelen, name, *length, &compc, compl,
        FDRYDAIVLANCONFIGENTRY_INSTANCE_LEN);

    memset(&entry, 0, sizeof(entry));

    /* dispatch get-exact versus get-next
     */
    if (exact) /* get or set */
    {
        /* extract index
         */
        if (! fdryDaiVlanConfigTable_OidIndexToData(exact, compc, compl,
            &vid))
        {
            return NULL;
        }

        /* get-exact from core layer
         */
        if (DAI_PMGR_GetVlanInfo(vid, &entry, &dai_status) != DAI_TYPE_OK)
        {
            return NULL;
        }
    }
    else /* get-next */
    {
        /* extract index
         */
        fdryDaiVlanConfigTable_OidIndexToData(exact, compc, compl,
            &vid);

        /* Check the length of inputing index. If compc is less than instance
         * length, we should try get {A.B.C.0.0...}, where A.B.C was
         * obtained from the "..._OidIndexToData" function call, and
         * 0.0... was initialized in the beginning of this function.
         * This instance may exist in the core layer.
         */
        if (compc < FDRYDAIVLANCONFIGENTRY_INSTANCE_LEN)  /* incomplete index */
        {
            /* get-exact, in case this instance exists
             */
            if (DAI_PMGR_GetVlanInfo(vid, &entry, &dai_status) != DAI_TYPE_OK)
            {
                /* get-next according to lexicographic order; if none, fail
                 */
                if (DAI_PMGR_GetNextVlanInfo(&vid, &entry, &dai_status) != DAI_TYPE_OK)
                {
                    return NULL;
                }
            }
        }
        else  /* complete index */
        {
            /* get-next according to lexicographic order; if none, fail
             */
            if (DAI_PMGR_GetNextVlanInfo(&vid, &entry, &dai_status) != DAI_TYPE_OK)
            {
                return NULL;
            }
        }
    }

    /* copy base OID (without index) to output
     */
    memcpy(name, vp->name, vp->namelen * sizeof(oid));

    /* assign data to the OID index
     */
    best_inst[0] = vid;
    memcpy(name + vp->namelen, best_inst, FDRYDAIVLANCONFIGENTRY_INSTANCE_LEN * sizeof(oid));
    *length = vp->namelen + FDRYDAIVLANCONFIGENTRY_INSTANCE_LEN;

    /* dispatch node to read value
     */
    switch (vp->magic)
    {
#if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1)
        case LEAF_fdryDaiVlanVLanId:
            *var_len = 4;
            long_return = vid;
            return (u_char *) &long_return;
#endif /* #if (SYS_ADPT_PRIVATEMIB_INDEX_ACCESSIBLE == 1) */

        case LEAF_fdryDaiVlanDynArpInspEnable:
            *var_len = 4;
            long_return = (UI32_T) dai_status;  /* TruthValue = EnabledStatus */
            return (u_char *) &long_return;

        default:
            ERROR_MSG("");
            break;
    }

    /* return failure
     */
    return NULL;
}

int write_fdryDaiVlanDynArpInspEnable(int action,
    u_char *var_val,
    u_char var_val_type,
    size_t var_val_len,
    u_char *statP,
    oid *name,
    size_t name_len)
{
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
                case VAL_fdryDaiVlanDynArpInspEnable_true:
                    break;

                case VAL_fdryDaiVlanDynArpInspEnable_false:
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
            UI32_T fdryDaiVlanVLanId = 0;

            /* extract index
             */
            if (! fdryDaiVlanConfigTable_OidIndexToData(TRUE,
                name_len - oid_name_length,
                &(name[oid_name_length]),
                &fdryDaiVlanVLanId))
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
                /* enable
                 */
                case VAL_fdryDaiVlanDynArpInspEnable_true:
                    if (DAI_PMGR_EnableDaiByVlan(fdryDaiVlanVLanId) != DAI_TYPE_OK)
                    {
                        return SNMP_ERR_COMMITFAILED;
                    }
                    break;

                /* disable
                 */
                case VAL_fdryDaiVlanDynArpInspEnable_false:
                    if (DAI_PMGR_DisableDaiByVlan(fdryDaiVlanVLanId) != DAI_TYPE_OK)
                    {
                        return SNMP_ERR_COMMITFAILED;
                    }
                    break;

                /* should not happen
                 */
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

/* ------------------------------------------------------------------------
 * TABLE NAME - fdryDaiIfConfigTable
 * ------------------------------------------------------------------------
 */
oid fdryDaiIfConfigTable_variables_oid[] = { 1,3,6,1,4,1,1991,1,1,3,35,2 };

/* variable3 fdryDaiIfConfigTable_variables:
 *   this variable defines function callbacks and type return information
 *   for the  mib section
 */
struct variable3 fdryDaiIfConfigTable_variables[] =
{
    /* magic number, variable type, ro/rw, callback fn, L, oidsuffix
     *     (L = length of the oidsuffix)
     */
    { LEAF_fdryDaiIfTrustValue, ASN_INTEGER, RWRITE, var_fdryDaiIfConfigTable, 3, { 1, 1, 1 }},
};

void init_fdryDaiIfConfigTable(void)
{
    /* Register ourselves with the agent to handle our MIB tree
     */
    REGISTER_MIB("fdryDaiIfConfigTable", fdryDaiIfConfigTable_variables, variable3,
                 fdryDaiIfConfigTable_variables_oid);
}

#define FDRYDAIIFCONFIGENTRY_INSTANCE_LEN  1

BOOL_T fdryDaiIfConfigTable_OidIndexToData(UI32_T exact, UI32_T compc,
    oid *compl, UI32_T *ifIndex)
{
    /* get or set
     */
    if (exact)
    {
        /* check the index length
         */
        if (compc != FDRYDAIIFCONFIGENTRY_INSTANCE_LEN) /* the constant size index */
        {
            return FALSE;
        }
    }

    *ifIndex = compl[0];

    return TRUE;
}

/*
 * var_fdryDaiIfConfigTable():
 *   Handle this table separately from the scalar value case.
 *   The workings of this are basically the same as for var_ above.
 */
unsigned char *var_fdryDaiIfConfigTable(struct variable *vp,
    oid *name,
    size_t *length,
    int exact,
    size_t *var_len,
    WriteMethod **write_method)
{
    UI32_T compc = 0;
    oid compl[FDRYDAIIFCONFIGENTRY_INSTANCE_LEN] = {0};
    oid best_inst[FDRYDAIIFCONFIGENTRY_INSTANCE_LEN] = {0};

    /* table-specific variables
     */
    DAI_TYPE_PortInfo_T entry;
    UI32_T ifIndex = 0;

    /* dispatch node to set write method
     */
    switch (vp->magic)
    {
        case LEAF_fdryDaiIfTrustValue:
            *write_method = write_fdryDaiIfTrustValue;
            break;

        default:
            *write_method = 0;
            break;
    }

    /* check compc, retrive compl
     */
    SNMP_MGR_RetrieveCompl(vp->name, vp->namelen, name, *length, &compc, compl,
        FDRYDAIIFCONFIGENTRY_INSTANCE_LEN);

    memset(&entry, 0, sizeof(entry));

    /* dispatch get-exact versus get-next
     */
    if (exact) /* get or set */
    {
        /* extract index
         */
        if (! fdryDaiIfConfigTable_OidIndexToData(exact, compc, compl,
            &ifIndex))
        {
            return NULL;
        }

        /* get-exact from core layer
         */
        if (DAI_PMGR_GetPortInfo(ifIndex, &entry) != DAI_TYPE_OK)
        {
            return NULL;
        }
    }
    else /* get-next */
    {
        /* extract index
         */
        fdryDaiIfConfigTable_OidIndexToData(exact, compc, compl,
            &ifIndex);

        /* Check the length of inputing index. If compc is less than instance
         * length, we should try get {A.B.C.0.0...}, where A.B.C was
         * obtained from the "..._OidIndexToData" function call, and
         * 0.0... was initialized in the beginning of this function.
         * This instance may exist in the core layer.
         */
        if (compc < FDRYDAIIFCONFIGENTRY_INSTANCE_LEN)  /* incomplete index */
        {
            /* get-exact, in case this instance exists
             */
            if (DAI_PMGR_GetPortInfo(ifIndex, &entry) != DAI_TYPE_OK)
            {
                /* get-next according to lexicographic order; if none, fail
                 */
                if (DAI_PMGR_GetNextPortInfo(&ifIndex, &entry) != DAI_TYPE_OK)
                {
                    return NULL;
                }
            }
        }
        else  /* complete index */
        {
            /* get-next according to lexicographic order; if none, fail
             */
            if (DAI_PMGR_GetNextPortInfo(&ifIndex, &entry) != DAI_TYPE_OK)
            {
                return NULL;
            }
        }
    }

    /* copy base OID (without index) to output
     */
    memcpy(name, vp->name, vp->namelen * sizeof(oid));

    /* assign data to the OID index
     */
    best_inst[0] = ifIndex;
    memcpy(name + vp->namelen, best_inst, FDRYDAIIFCONFIGENTRY_INSTANCE_LEN * sizeof(oid));
    *length = vp->namelen + FDRYDAIIFCONFIGENTRY_INSTANCE_LEN;

    /* dispatch node to read value
     */
    switch (vp->magic)
    {
        case LEAF_fdryDaiIfTrustValue:
            *var_len = 4;
            long_return = (UI32_T) entry.trust_status;  /* TruthValue = EnabledStatus */
            return (u_char *) &long_return;

        default:
            ERROR_MSG("");
            break;
    }

    /* return failure
     */
    return NULL;
}

int write_fdryDaiIfTrustValue(int action,
    u_char *var_val,
    u_char var_val_type,
    size_t var_val_len,
    u_char *statP,
    oid *name,
    size_t name_len)
{
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
                case VAL_fdryDaiIfTrustValue_true:
                    break;

                case VAL_fdryDaiIfTrustValue_false:
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
            UI32_T ifIndex = 0;
            UI8_T  status;

            /* extract index
             */
            if (! fdryDaiIfConfigTable_OidIndexToData(TRUE,
                name_len - oid_name_length,
                &(name[oid_name_length]),
                &ifIndex))
            {
                return SNMP_ERR_COMMITFAILED;
            }

            /* get user value
             */
            memcpy(&value, var_val, sizeof(I32_T));

            /* convert to value for core layer
             */
            if (value == VAL_fdryDaiIfTrustValue_true)
            {
                status = DAI_TYPE_PORT_TRUSTED;
            }
            else
            {
                status = DAI_TYPE_PORT_UNTRUSTED;
            }

            /* set to core layer
             */
            if (DAI_PMGR_SetPortTrustStatus(ifIndex, status) != DAI_TYPE_OK)
            {
                return SNMP_ERR_COMMITFAILED;
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

/* ------------------------------------------------------------------------
 * FUNCTION NAME - init_fdryDaiMIB
 * ------------------------------------------------------------------------
 * PURPOSE  :   The is the entry point into this file for initialisation.
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
void init_fdryDaiMIB(void)
{
    oid fdryDaiMIB_oid[] = { 1,3,6,1,4,1,1991,1,1,3,35 };

    /* register individual tables
     */
    init_fdryDaiVlanConfigTable();
    init_fdryDaiIfConfigTable();

    /* register ourselves in the sysORTable
     */
    REGISTER_SYSOR_ENTRY(fdryDaiMIB_oid,
        "Management Information for configuration of Dynamic ARP Inspection feature.");
}
#endif  /* (SYS_CPNT_DAI == TRUE); from near-beginning to end of file */
