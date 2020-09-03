#ifndef _COS_TYPE_H
#define _COS_TYPE_H

#include "sys_type.h"
#include "sys_adpt.h"


#define COS_TYPE_DEFAULT_COS   0
#define COS_TYPE_COS_MIN_RAGNE 0
#define COS_TYPE_COS_MAX_RAGNE 7

#define VAL_cosEntryStatus_notExist           0
#define VAL_cosEntryStatus_active             1
#define VAL_cosEntryStatus_notInService       2
#define VAL_cosEntryStatus_notReady           3
#define VAL_cosEntryStatus_createAndGo        4
#define VAL_cosEntryStatus_createAndWait      5
#define VAL_cosEntryStatus_destroy            6

#define COS_TYPE_PRIORITY_USER                1
#define COS_TYPE_PRIORITY_ETS                 2
#define COS_TYPE_PRIORITY_CN                  3

typedef struct
{

    char acl_name[SYS_ADPT_ACL_MAX_NAME_LEN + 1];

    /* acl_type can be
       ACL_IP_ACL
       ACL_MAC_ACL
     */

    /*  only used in WWW and CLI
     */
    UI32_T acl_type;

    UI32_T cos;
    UI32_T row_status;

}COS_TYPE_AclCosEntry_T;


/*
absolate part
*/
typedef struct
{
    UI8_T ip_acl[SYS_ADPT_ACL_MAX_NAME_LEN+1];
    UI8_T mac_acl[SYS_ADPT_ACL_MAX_NAME_LEN+1];
    UI32_T ip_acl_cos;
    UI32_T mac_acl_cos;

}COS_AclCosMapping_T;



#define COS_TYPE_AF11 10
#define COS_TYPE_AF12 12
#define COS_TYPE_AF13 14
#define COS_TYPE_AF21 18
#define COS_TYPE_AF22 20
#define COS_TYPE_AF23 22
#define COS_TYPE_AF31 26
#define COS_TYPE_AF32 28
#define COS_TYPE_AF33 30
#define COS_TYPE_AF41 34
#define COS_TYPE_AF42 36
#define COS_TYPE_AF43 38
#define COS_TYPE_EF   46
#define CS_TYPE_CS0   0
#define CS_TYPE_CS1   8
#define CS_TYPE_CS2   16
#define CS_TYPE_CS3   24
#define CS_TYPE_CS4   32
#define CS_TYPE_CS5   40
#define CS_TYPE_CS6   48
#define CS_TYPE_CS7   56

#define COS_TYPE_UNKNOWN_COS         0xFF
#define COS_TYPE_UNKNOWN_CFI         0xFF
#define COS_TYPE_UNKONWN_PRI         0XFF
#define COS_TYPE_UNKNOWN_PRE         0xFF
#define COS_TYPE_UNKNOWN_PHB         0xFF
#define COS_TYPE_UNKNOWN_COLOR       0xFF
#define COS_TYPE_UNKNOWN_DSCP        0xFF
#define COS_TYPE_UNKNOWN_QUEUE       0xFF

typedef enum
{
    COS_TYPE_E_NONE = 1,
    COS_TYPE_E_UNKNOWN,
    COS_TYPE_E_PARAMETER,
    COS_TYPE_E_CONFIG_NOT_FOUND,
    COS_TYPE_E_CONFIG_FILE_FULL,
    COS_TYPE_E_PRIORITY_NOT_ENABLED,
    COS_TYPE_E_PRIORITY_NOT_MODIFIED,
    COS_TYPE_E_SET_TO_SWCTRL,
    COS_TYPE_E_WRONG_TRUST_MODE,
    COS_TYPE_E_SCHEDULING_METHOD,
    COS_TYPE_E_TRUNCK_PORT, /* now didn't support trunk */
    COS_TYPE_E_NO_CHANGE,
    COS_TYPE_E_PARAMETER_STRICT_QUEUE_PRIORITY,
    COS_TYPE_E_STRICT_QUEUE_CONFIG,
    COS_TYPE_E_COUNT
}COS_TYPE_ERROR_CODE_E;

/* cos_to_dscp_map[INGRESS_COS_TO_DSCP_MAPPING_ENTRY_NMB][INGRESS_COS_TO_DSCP_MAPPING_CFI]
 */
#define COS_TYPE_DEFAULT_COS_TO_DSCP_MAP_ARRAY \
{                                                                                                                                                 \
    {{SYS_DFLT_INGRESS_COS_0_TO_PHB_0, SYS_DFLT_INGRESS_COS_0_TO_COLOR_0}, {SYS_DFLT_INGRESS_COS_0_TO_PHB_1, SYS_DFLT_INGRESS_COS_0_TO_COLOR_1}}, \
    {{SYS_DFLT_INGRESS_COS_1_TO_PHB_0, SYS_DFLT_INGRESS_COS_1_TO_COLOR_0}, {SYS_DFLT_INGRESS_COS_1_TO_PHB_1, SYS_DFLT_INGRESS_COS_1_TO_COLOR_1}}, \
    {{SYS_DFLT_INGRESS_COS_2_TO_PHB_0, SYS_DFLT_INGRESS_COS_2_TO_COLOR_0}, {SYS_DFLT_INGRESS_COS_2_TO_PHB_1, SYS_DFLT_INGRESS_COS_2_TO_COLOR_1}}, \
    {{SYS_DFLT_INGRESS_COS_3_TO_PHB_0, SYS_DFLT_INGRESS_COS_3_TO_COLOR_0}, {SYS_DFLT_INGRESS_COS_3_TO_PHB_1, SYS_DFLT_INGRESS_COS_1_TO_COLOR_1}}, \
    {{SYS_DFLT_INGRESS_COS_4_TO_PHB_0, SYS_DFLT_INGRESS_COS_4_TO_COLOR_0}, {SYS_DFLT_INGRESS_COS_4_TO_PHB_1, SYS_DFLT_INGRESS_COS_4_TO_COLOR_1}}, \
    {{SYS_DFLT_INGRESS_COS_5_TO_PHB_0, SYS_DFLT_INGRESS_COS_5_TO_COLOR_0}, {SYS_DFLT_INGRESS_COS_5_TO_PHB_1, SYS_DFLT_INGRESS_COS_5_TO_COLOR_1}}, \
    {{SYS_DFLT_INGRESS_COS_6_TO_PHB_0, SYS_DFLT_INGRESS_COS_6_TO_COLOR_0}, {SYS_DFLT_INGRESS_COS_6_TO_PHB_1, SYS_DFLT_INGRESS_COS_6_TO_COLOR_1}}, \
    {{SYS_DFLT_INGRESS_COS_7_TO_PHB_0, SYS_DFLT_INGRESS_COS_7_TO_COLOR_0}, {SYS_DFLT_INGRESS_COS_7_TO_PHB_1, SYS_DFLT_INGRESS_COS_7_TO_COLOR_1}}  \
}

/* pre_to_dscp_map[INGRESS_PRE_TO_DSCP_MAPPING_ENTRY_NMB]
 */
#define COS_TYPE_DEFAULT_PRE_TO_DSCP_MAP_ARRAY \
{                                                                     \
    {SYS_DFLT_INGRESS_PRE_0_TO_PHB, SYS_DFLT_INGRESS_PRE_0_TO_COLOR}, \
    {SYS_DFLT_INGRESS_PRE_1_TO_PHB, SYS_DFLT_INGRESS_PRE_1_TO_COLOR}, \
    {SYS_DFLT_INGRESS_PRE_2_TO_PHB, SYS_DFLT_INGRESS_PRE_2_TO_COLOR}, \
    {SYS_DFLT_INGRESS_PRE_3_TO_PHB, SYS_DFLT_INGRESS_PRE_3_TO_COLOR}, \
    {SYS_DFLT_INGRESS_PRE_4_TO_PHB, SYS_DFLT_INGRESS_PRE_4_TO_COLOR}, \
    {SYS_DFLT_INGRESS_PRE_5_TO_PHB, SYS_DFLT_INGRESS_PRE_5_TO_COLOR}, \
    {SYS_DFLT_INGRESS_PRE_6_TO_PHB, SYS_DFLT_INGRESS_PRE_6_TO_COLOR}, \
    {SYS_DFLT_INGRESS_PRE_7_TO_PHB, SYS_DFLT_INGRESS_PRE_7_TO_COLOR}  \
}

/* dscp_to_dscp_map[INGRESS_DSCP_TO_DSCP_MAPPING_ENTRY_NMB]
 */
#define COS_TYPE_DEFAULT_DSCP_TO_DSCP_MAP_ARRAY \
{                                                                         \
    {SYS_DFLT_INGRESS_DSCP_0_TO_PHB,  SYS_DFLT_INGRESS_DSCP_0_TO_COLOR},  \
    {SYS_DFLT_INGRESS_DSCP_1_TO_PHB,  SYS_DFLT_INGRESS_DSCP_1_TO_COLOR},  \
    {SYS_DFLT_INGRESS_DSCP_2_TO_PHB,  SYS_DFLT_INGRESS_DSCP_2_TO_COLOR},  \
    {SYS_DFLT_INGRESS_DSCP_3_TO_PHB,  SYS_DFLT_INGRESS_DSCP_3_TO_COLOR},  \
    {SYS_DFLT_INGRESS_DSCP_4_TO_PHB,  SYS_DFLT_INGRESS_DSCP_4_TO_COLOR},  \
    {SYS_DFLT_INGRESS_DSCP_5_TO_PHB,  SYS_DFLT_INGRESS_DSCP_5_TO_COLOR},  \
    {SYS_DFLT_INGRESS_DSCP_6_TO_PHB,  SYS_DFLT_INGRESS_DSCP_6_TO_COLOR},  \
    {SYS_DFLT_INGRESS_DSCP_7_TO_PHB,  SYS_DFLT_INGRESS_DSCP_7_TO_COLOR},  \
    {SYS_DFLT_INGRESS_DSCP_8_TO_PHB,  SYS_DFLT_INGRESS_DSCP_8_TO_COLOR},  \
    {SYS_DFLT_INGRESS_DSCP_9_TO_PHB,  SYS_DFLT_INGRESS_DSCP_9_TO_COLOR},  \
    {SYS_DFLT_INGRESS_DSCP_10_TO_PHB, SYS_DFLT_INGRESS_DSCP_10_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_11_TO_PHB, SYS_DFLT_INGRESS_DSCP_11_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_12_TO_PHB, SYS_DFLT_INGRESS_DSCP_12_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_13_TO_PHB, SYS_DFLT_INGRESS_DSCP_13_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_14_TO_PHB, SYS_DFLT_INGRESS_DSCP_14_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_15_TO_PHB, SYS_DFLT_INGRESS_DSCP_15_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_16_TO_PHB, SYS_DFLT_INGRESS_DSCP_16_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_17_TO_PHB, SYS_DFLT_INGRESS_DSCP_17_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_18_TO_PHB, SYS_DFLT_INGRESS_DSCP_18_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_19_TO_PHB, SYS_DFLT_INGRESS_DSCP_19_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_20_TO_PHB, SYS_DFLT_INGRESS_DSCP_20_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_21_TO_PHB, SYS_DFLT_INGRESS_DSCP_21_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_22_TO_PHB, SYS_DFLT_INGRESS_DSCP_22_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_23_TO_PHB, SYS_DFLT_INGRESS_DSCP_23_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_24_TO_PHB, SYS_DFLT_INGRESS_DSCP_24_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_25_TO_PHB, SYS_DFLT_INGRESS_DSCP_25_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_26_TO_PHB, SYS_DFLT_INGRESS_DSCP_26_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_27_TO_PHB, SYS_DFLT_INGRESS_DSCP_27_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_28_TO_PHB, SYS_DFLT_INGRESS_DSCP_28_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_29_TO_PHB, SYS_DFLT_INGRESS_DSCP_29_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_30_TO_PHB, SYS_DFLT_INGRESS_DSCP_30_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_31_TO_PHB, SYS_DFLT_INGRESS_DSCP_31_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_32_TO_PHB, SYS_DFLT_INGRESS_DSCP_32_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_33_TO_PHB, SYS_DFLT_INGRESS_DSCP_33_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_34_TO_PHB, SYS_DFLT_INGRESS_DSCP_34_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_35_TO_PHB, SYS_DFLT_INGRESS_DSCP_35_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_36_TO_PHB, SYS_DFLT_INGRESS_DSCP_36_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_37_TO_PHB, SYS_DFLT_INGRESS_DSCP_37_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_38_TO_PHB, SYS_DFLT_INGRESS_DSCP_38_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_39_TO_PHB, SYS_DFLT_INGRESS_DSCP_39_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_40_TO_PHB, SYS_DFLT_INGRESS_DSCP_40_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_41_TO_PHB, SYS_DFLT_INGRESS_DSCP_41_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_42_TO_PHB, SYS_DFLT_INGRESS_DSCP_42_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_43_TO_PHB, SYS_DFLT_INGRESS_DSCP_43_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_44_TO_PHB, SYS_DFLT_INGRESS_DSCP_44_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_45_TO_PHB, SYS_DFLT_INGRESS_DSCP_45_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_46_TO_PHB, SYS_DFLT_INGRESS_DSCP_46_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_47_TO_PHB, SYS_DFLT_INGRESS_DSCP_47_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_48_TO_PHB, SYS_DFLT_INGRESS_DSCP_48_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_49_TO_PHB, SYS_DFLT_INGRESS_DSCP_49_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_50_TO_PHB, SYS_DFLT_INGRESS_DSCP_50_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_51_TO_PHB, SYS_DFLT_INGRESS_DSCP_51_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_52_TO_PHB, SYS_DFLT_INGRESS_DSCP_52_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_53_TO_PHB, SYS_DFLT_INGRESS_DSCP_53_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_54_TO_PHB, SYS_DFLT_INGRESS_DSCP_54_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_55_TO_PHB, SYS_DFLT_INGRESS_DSCP_55_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_56_TO_PHB, SYS_DFLT_INGRESS_DSCP_56_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_57_TO_PHB, SYS_DFLT_INGRESS_DSCP_57_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_58_TO_PHB, SYS_DFLT_INGRESS_DSCP_58_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_59_TO_PHB, SYS_DFLT_INGRESS_DSCP_59_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_60_TO_PHB, SYS_DFLT_INGRESS_DSCP_60_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_61_TO_PHB, SYS_DFLT_INGRESS_DSCP_61_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_62_TO_PHB, SYS_DFLT_INGRESS_DSCP_62_TO_COLOR}, \
    {SYS_DFLT_INGRESS_DSCP_63_TO_PHB, SYS_DFLT_INGRESS_DSCP_63_TO_COLOR}  \
}

/* phb_to_queue_map[MAX_PHB_VAL + 1]
 */
#define COS_TYPE_DEFAULT_PHB_TO_QUEUE_MAP_ARRAY \
{                            \
    SYS_DFLT_PRI_0_TO_QUEUE, \
    SYS_DFLT_PRI_1_TO_QUEUE, \
    SYS_DFLT_PRI_2_TO_QUEUE, \
    SYS_DFLT_PRI_3_TO_QUEUE, \
    SYS_DFLT_PRI_4_TO_QUEUE, \
    SYS_DFLT_PRI_5_TO_QUEUE, \
    SYS_DFLT_PRI_6_TO_QUEUE, \
    SYS_DFLT_PRI_7_TO_QUEUE  \
}

#endif
