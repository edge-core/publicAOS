/* MODULE NAME:  sysrsc_mgr_private.c
 * PURPOSE:
 *    This csc is designed to manage all system-wised resource such as shared
 *    memory and system-wised semaphores.
 *
 * NOTES:
 *    The creation of system-wised resource will be done through SYSINIT program.
 *    SYSRSC_MGR_CreateAndInitiateSystemResources() can be called by SYSINIT only.
 *    SYSRSC_MGR_AttachSystemResources() is needed to call in the initialization
 *    stage of each process to attach the system resource to the calling process
 *    context.
 *
 *    Functions in this file will only be linked to sysinit_proc.
 *
 * HISTORY
 *    31/5/2007 - Charlie Chen, Created
 *
 * Copyright(C)      Accton Corporation, 2007
 */

/* INCLUDE FILE DECLARATIONS
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sysrsc_mgr.h"
#include "sys_bld.h"
#include "sys_cpnt.h"
#include "sysfun.h"
#include "backdoor_mgr.h"
#include "uc_mgr.h"
#include "fs.h"

#if (SYS_CPNT_BUFFERMGMT == TRUE)
#include "buffermgmt_init.h"
#endif

#include "sys_callback_init.h"

#if (SYS_CPNT_SWDRV == TRUE)
#include "swdrv.h"
#include "swdrv_init.h"
#endif

#if (SYS_CPNT_AMTRDRV == TRUE)
#include "amtrdrv_mgr.h"
#endif

#if (SYS_CPNT_NMTRDRV == TRUE)
#include "nmtrdrv.h"
#endif

#if (SYS_CPNT_NICDRV == TRUE)
#include "dev_nicdrv_om.h"
#include "lan.h"
#endif

#if (SYS_CPNT_ISCDRV == TRUE)
#include "isc_init.h"
#endif

#if (SYS_CPNT_FLASHDRV == TRUE)
#include "fs_init.h"
#endif

#if (SYS_CPNT_COS == TRUE)
#include "cos_om.h"
#endif
#if (SYS_CPNT_QOS_V2 == TRUE)
#include "rule_ctrl.h"
#include "rule_om.h"
#endif

#if (SYS_CPNT_LEDDRV == TRUE)
#include "leddrv_init.h"
#endif

#if (SYS_CPNT_SYSDRV == TRUE)
#include "sysdrv_init.h"
#endif

/* shumin.wang added for ipfilter 2008 */
#if (SYS_CPNT_MGMT_IP_FLT == TRUE)
#include "mgmt_ip_flt.h"
#endif

#if (SYS_CPNT_SYS_TIME == TRUE)
#include "sys_time_init.h"
#include "sys_time.h"
#endif

#if (SYS_CPNT_SWDRVL3 == TRUE)
#include "swdrvl3_init.h"
#endif

#if (SYS_CPNT_SWDRVL4 == TRUE)
#include "swdrvl4.h"
#endif

#if (SYS_CPNT_CFGDB == TRUE)
#include "cfgdb_init.h"
#endif

#if (SYS_CPNT_STACKING == TRUE)
#include "stktplg_shom.h"
#endif
#include "xstp_pom.h"
#if (SYS_CPNT_VLAN == TRUE)
#include "vlan_om.h"
#endif
#if (SYS_CPNT_CFM == TRUE)
#include "cfm_om.h"
#endif
#include "netcfg_om_ip.h"

#if (SYS_CPNT_RSPAN == TRUE)
#include "rspan_om.h"
#endif /* #if (SYS_CPNT_RSPAN == TRUE) */

#if (SYS_CPNT_POE == TRUE)
#include "poedrv_init.h"
#endif

#if (SYS_CPNT_AMTR == TRUE)
#include "amtr_om.h"
#endif

#if (SYS_CPNT_PFC == TRUE)
#include "pfc_om.h"
#endif

#if (SYS_CPNT_SW_WATCHDOG_TIMER == TRUE)
#include "sw_watchdog_mgr.h"
#endif

#if (SYS_CPNT_DOS == TRUE)
#include "dos_om.h"
#endif

#if (SYS_CPNT_SWCTRL == TRUE)
#include "swctrl_om.h"
#endif

#if (SYS_CPNT_DEBUG == TRUE)
#include "debug_mgr.h"
#endif /* SYS_CPNT_DEBUG */

#if (SYS_CPNT_SYNCE == TRUE)
#include "syncedrv_om.h"
#endif

#if (SYS_CPNT_CN == TRUE)
#include "cn_om.h"
#endif

#if (SYS_CPNT_SFLOW == TRUE)
#include "sflow_om.h"
#endif

#if (SYS_CPNT_APP_FILTER == TRUE)
#include "af_om.h"
#endif /* #if (SYS_CPNT_APP_FILTER == TRUE) */

#include "ssl_crypto_lock.h"

#if (SYS_CPNT_EH == TRUE)
#include "eh_om.h"
#endif

#include "http_om_exp.h" /* for prototype of HTTP_OM_InitateProcessResource() */

#if (SYS_CPNT_CLI == TRUE)
#include "cli_om_exp.h"
#endif /* SYS_CPNT_CLI */

#if (SYS_CPNT_VXLAN == TRUE)
#include "vxlan_om.h"
#endif

#if (SYS_CPNT_UCMGMT == TRUE)
#include "uc_mgr.h"
#endif

#if (SYS_CPNT_WEBAUTH == TRUE)
#include "webauth_om.h"
#endif

#if (SYS_CPNT_OVSVTEP == TRUE)
#include "ovsvtep_om.h"
#endif

/*
#define SYSRSC_MGR_DEBUG
*/
/* NAMING CONSTANT DECLARATIONS
 */

/* MACRO FUNCTION DECLARATIONS
 */


#ifdef SYSRSC_MGR_DEBUG
#define SYSRSC_DBG(...) printf(__VA_ARGS__)
#else
#define SYSRSC_DBG(...)
#endif

/* DATA TYPE DECLARATIONS
 */

typedef void (*SYSRSC_MGR_GetShMemInfoFunc_T)(SYSRSC_MGR_SEGID_T *segid_p, UI32_T *seglen_p);

/* LOCAL SUBPROGRAM DECLARATIONS
 */
static BOOL_T SYSRSC_MGR_CreateAllSysSemaphores(void);
static BOOL_T SYSRSC_MGR_CreateSharedMemory(void);
static void   SYSRSC_MGR_InitiateAllCSCSystemResources(void);
static void   SYSRSC_MGR_InitUCSysinfo(void);

/* STATIC VARIABLE DECLARATIONS
 */

extern void SYSRSC_MGR_SetShMemHeaderPtr(SYSRSC_MGR_ShMemHeader_T* ptr);

/* EXPORTED SUBPROGRAM BODIES
 */
extern void SNMP_PMGR_GetShMemInfo(SYSRSC_MGR_SEGID_T *segid, UI32_T *seglen);
extern void SNMP_PMGR_InitiateSystemResources(void);

/*------------------------------------------------------------------------------
 * ROUTINE NAME : SYSRSC_MGR_CreateAndInitiateSystemResources
 *------------------------------------------------------------------------------
 * PURPOSE:
 *    Create system-wised resource and initiate them.
 *
 * INPUT:
 *    None.
 *
 * OUTPUT:
 *    None.
 *
 * RETURN:
 *    TRUE  --  Success
 *    FALSE --  Error
 *
 * NOTES:
 *    1.This api shall only be called in SYSINT program
 *    2.This api will call functions related to create and initiate system
 *      resource provided by CSCs. Presently, the functions listed below will be
 *      called in this api:
 *         XXX_GetShMemInfo()
 *         XXX_InitiateSystemResources()
 *------------------------------------------------------------------------------
 */
BOOL_T SYSRSC_MGR_CreateAndInitiateSystemResources(void)
{
    SYSRSC_DBG("Invoke SYSRSC_MGR_CreateAllSysSemaphores\r\n");
    if(FALSE==SYSRSC_MGR_CreateAllSysSemaphores())
        return FALSE;

    SYSRSC_DBG("Invoke SYSRSC_MGR_CreateSharedMemory\r\n");
    if(FALSE==SYSRSC_MGR_CreateSharedMemory())
        return FALSE;

    SYSRSC_DBG("Invoke SYSRSC_MGR_InitiateAllCSCSystemResources\r\n");
    SYSRSC_MGR_InitiateAllCSCSystemResources();
    return TRUE;
}

struct sem_init_table
{
    UI32_T      sem_key;
    UI32_T      sem_count;
    UI32_T      sem_flag;
};

struct sem_init_table sysrsc_init_sem_table[] ={
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_AMTRDRV,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_AMTRDRV_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_AMTR_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_STKTPLG_SHOM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_STKTPLG_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_VLAN_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_SWDRV_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_SWDRVL3_OM,1,SYSFUN_SEM_FIFO},
      /*{(UI32_T)SYS_BLD_SYS_SEMAPHORE_BUFFERMGR,1,SYSFUN_SEM_FIFO},        */
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_ISC_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_CFGDB_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_DEV_NICDRV_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_LAN_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_NMTRDRV_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_FS_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_COS_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_RULE_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_RULE_CTRL,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_I2CDRV,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_MLDSNP,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_SWDRVL4,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_NETCFG_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_BUFFER_MGR,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_SYSCTRL_XOR_MGR,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_NETACCESS_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_DHCPSNP_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_HTTP_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_UC_MGR,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_SYS_CALLBACK_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_CLI_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_DNS_CACHE,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_DNS_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_DNS_RESOLVER,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_KEYGEN_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_IPFILTER,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_MIB2_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_PING_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_SMTP_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_SNTP_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_SSHD_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_SYSLOG_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_TACACS_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_TELNET_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_TRACEROUTE_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_XSTP_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_AMTR_NA_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_SYSTIME_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_VRRP,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_NAQUEUE_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_SNMP_TRAP,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_AAA_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_CMGR,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_CLUSTER_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_RSPAN_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_POEDRV_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_GPIO,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_TWSI,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_SYSDRV,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_BACKDOOR,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_NTP_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_PRIVATE_VLAN_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_BGP_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_I2CDRV_MUX,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_UDLD_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_DEBUG_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_SYNCEDRV_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_ELPS_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_PFC_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_ETS_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_CN_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_LBD_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_SFLOW_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_APP_FILTER_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_OPENSSL,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_EH_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_EH,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_VXLAN_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_AMTRDRV_SYNC_OP,0,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_IPSG_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_WEBAUTH_OM,1,SYSFUN_SEM_FIFO},
        {(UI32_T)SYS_BLD_SYS_SEMAPHORE_KEY_OVSVTEP_OM,1,SYSFUN_SEM_FIFO},
};
/* LOCAL SUBPROGRAM BODIES
 */
/*------------------------------------------------------------------------------
 * ROUTINE NAME : SYSRSC_MGR_CreateAllSysSemaphores
 *------------------------------------------------------------------------------
 * PURPOSE:
 *    This function will create all system-wised semaphores.
 *
 * INPUT:
 *    None.
 *
 * OUTPUT:
 *    None.
 *
 * RETURN:
 *    TRUE  --  Sucess
 *    FALSE --  Error
 *
 * NOTES:
 *    None.
 *------------------------------------------------------------------------------
 */
static BOOL_T SYSRSC_MGR_CreateAllSysSemaphores(void)
{
    UI32_T sem_id;
    UI32_T i;
    /*add by Tony.Lei, redesign */
    for(i = 0;i < sizeof(sysrsc_init_sem_table)/sizeof(struct sem_init_table); i++) {
        if(SYSFUN_OK != SYSFUN_CreateSem(sysrsc_init_sem_table[i].sem_key,
                                         sysrsc_init_sem_table[i].sem_count,
                                         sysrsc_init_sem_table[i].sem_flag,
                                         &sem_id)){
            printf("%s: SYSFUN_CreateSem [id:%ld]fail.\n", __FUNCTION__,(long)i);
            return FALSE;
        }
    }
    return TRUE;
}

/*------------------------------------------------------------------------------
 * ROUTINE NAME : SYSRSC_MGR_CreateSharedMemory
 *------------------------------------------------------------------------------
 * PURPOSE:
 *    This function will create shared memory.
 *
 * INPUT:
 *    None.
 *
 * OUTPUT:
 *    None.
 *
 * RETURN:
 *    TRUE  --  Sucess
 *    FALSE --  Error
 *
 * NOTES:
 *    None.
 *------------------------------------------------------------------------------
 */
static BOOL_T SYSRSC_MGR_CreateSharedMemory(void)
{
    UI32_T shmid;
    UI32_T total_shmem_seg_num, total_shmem_seg_len, i, shmem_header_len;
    SYSRSC_MGR_ShMemHeader_T *tmp_shmem_header_p, *shmem_header_p;

    /* put all XXX_GetShMemInfo() in csc_getshmem_funcs
     */
    SYSRSC_MGR_GetShMemInfoFunc_T csc_getshmem_funcs[] =
    {
#if (SYS_CPNT_BUFFERMGMT == TRUE)
        BUFFERMGMT_INIT_GetShMemInfo,
#endif
        SYS_CALLBACK_INIT_GetShMemInfo,
#if (SYS_CPNT_SWDRV == TRUE)
        SWDRV_INIT_GetShMemInfo,
#endif
#if (SYS_CPNT_AMTRDRV == TRUE)
        AMTRDRV_MGR_GetShMemInfo,
#endif
#if (SYS_CPNT_NMTRDRV == TRUE)
        NMTRDRV_GetShMemInfo,
#endif
#if (SYS_CPNT_NICDRV == TRUE)
        DEV_NICDRV_OM_GetShMemInfo,
        LAN_GetShMemInfo,
#endif
#if (SYS_CPNT_ISCDRV == TRUE)
        ISC_INIT_GetShMemInfo,
#endif
#if (SYS_CPNT_FLASHDRV == TRUE)
        FLASHDRV_INIT_GetShMemInfo,
#endif
#if (SYS_CPNT_COS == TRUE)
        COS_OM_GetShMemInfo,
#endif
#if (SYS_CPNT_MGMT_IP_FLT == TRUE)
        MGMT_IP_FLT_GetShMemInfo,
#endif
#if (SYS_CPNT_QOS_V2 == TRUE)
        RULE_OM_GetShMemInfo,
        RULE_CTRL_GetShMemInfo,
#endif
#if (SYS_CPNT_LEDDRV == TRUE)
        LEDDRV_INIT_GetShMemInfo,
#endif
#if (SYS_CPNT_SYSDRV == TRUE)
        SYSDRV_INIT_GetShMemInfo,
#endif
#if (SYS_CPNT_SYS_TIME == TRUE)
        SYS_TIME_INIT_GetShMemInfo,
#endif
#if (SYS_CPNT_SWDRVL3 == TRUE)
        SWDRVL3_INIT_GetShMemInfo,
#endif
#if (SYS_CPNT_SWDRVL4 == TRUE)
        SWDRVL4_GetShMemInfo,
#endif
#if (SYS_CPNT_CFGDB == TRUE)
        CFGDB_INIT_GetShMemInfo,
#endif
#if (SYS_CPNT_STACKING == TRUE)
        STKTPLG_SHOM_GetShMemInfo,
#endif
#if (SYS_CPNT_CFM == TRUE)
        CFM_OM_GetShMemInfo,
#endif
#if (SYS_CPNT_BRIDGE == TRUE)
        XSTP_SHARE_OM_GetShMemInfo,
#endif
#if (SYS_CPNT_VLAN == TRUE)
        VLAN_OM_GetShMemInfo,
#endif
        NETCFG_OM_IP_GetShMemInfo,

#if (SYS_CPNT_POE == TRUE)
        POEDRV_INIT_GetShMemInfo,
#endif

#if (SYS_CPNT_SNMP == TRUE) /* 2009-01-05, steven.jiang */
        SNMP_PMGR_GetShMemInfo,
#endif
#if (SYS_CPNT_RSPAN == TRUE)
        RSPAN_OM_GetShMemInfo,
#endif
#if (SYS_CPNT_AMTR == TRUE)
        AMTR_OM_GetShMemInfo,
#endif

#if (SYS_CPNT_PFC == TRUE)
        PFC_OM_GetShMemInfo,
#endif

#if (SYS_CPNT_DOS == TRUE)
        DOS_OM_GetShMemInfo,
#endif

#if (SYS_CPNT_APP_FILTER == TRUE)
        AF_OM_GetShMemInfo,
#endif /* #if (SYS_CPNT_APP_FILTER == TRUE) */

        BACKDOOR_MGR_GetShMemInfo,

#if (SYS_CPNT_DEBUG == TRUE)
        DEBUG_MGR_GetShMemInfo,
#endif /* SYS_CPNT_DEBUG */

#if (SYS_CPNT_SW_WATCHDOG_TIMER == TRUE)
        SW_WATCHDOG_MGR_GetShMemInfo,
#endif

#if (SYS_CPNT_SWCTRL == TRUE)
        SWCTRL_OM_GetShMemInfo,
#endif

#if (SYS_CPNT_SYNCE == TRUE)
        SYNCEDRV_OM_GetShMemInfo,
#endif

#if (SYS_CPNT_CN == TRUE)
        CN_OM_GetShMemInfo,
#endif

#if (SYS_CPNT_SFLOW == TRUE)
        SFLOW_OM_GetShMemInfo,
#endif

#if (SYS_CPNT_CLI == TRUE)
        CLI_OM_EXP_GetShMemInfo,
#endif /* SYS_CPNT_CLI */
#if (SYS_CPNT_VXLAN == TRUE)
        VXLAN_OM_GetShMemInfo,
#endif
#if (SYS_CPNT_OVSVTEP == TRUE)
        OVSVTEP_OM_GetShMemInfo,
#endif

#if (SYS_CPNT_EH == TRUE)
        EH_OM_GetShMemInfo,
#endif
#if (SYS_CPNT_UCMGMT == TRUE)
        UC_MGR_GetShMemInfo,
#endif

#if (SYS_CPNT_WEBAUTH == TRUE)
        WEBAUTH_OM_GetShMemInfo,
#endif
    };

    total_shmem_seg_num = sizeof(csc_getshmem_funcs)/sizeof(SYSRSC_MGR_GetShMemInfoFunc_T);
    shmem_header_len = SYSRSC_MGR_SHMEM_HEADER_SIZE(total_shmem_seg_num);

    /* initiate shared memory header
     */
    tmp_shmem_header_p = (SYSRSC_MGR_ShMemHeader_T*)malloc(shmem_header_len);
    if(tmp_shmem_header_p==NULL)
    {
        printf("%s: malloc to tmp_shmem_header_p fail.\n", __FUNCTION__);
        return FALSE;
    }

    tmp_shmem_header_p->num_of_seg = total_shmem_seg_num;

    /* collect all shared memory segment info
     */
    total_shmem_seg_len=0;
    for(i=0; i<total_shmem_seg_num; i++)
    {
        UI32_T seglen;
        SYSRSC_MGR_SEGID_T seg_id;

        SYSRSC_DBG("Invoke GetShMemInfo(i=%d)\r\n", (int)i);
        (csc_getshmem_funcs[i])(&seg_id, &seglen);

        (tmp_shmem_header_p->seg_descs[i]).offset = shmem_header_len + total_shmem_seg_len;
        (tmp_shmem_header_p->seg_descs[i]).seg_id = seg_id;
        total_shmem_seg_len                      += seglen;
    }

    tmp_shmem_header_p->total_seg_len = total_shmem_seg_len;
    /* create shared memory
     */
    SYSRSC_DBG("Invoke SYSFUN_CreateShMem\r\n");
    if (SYSFUN_OK!=SYSFUN_CreateShMem(SYS_BLD_SHMEM_KEY_SYSRSC,
        shmem_header_len+total_shmem_seg_len,
        &shmid))
    {
        printf("%s: SYSFUN_CreateShMem fail. (seg size: %08lx)\n", __FUNCTION__,
            (unsigned long)shmem_header_len+total_shmem_seg_len);
        free(tmp_shmem_header_p);
        return FALSE;
    }

    /* attach shared memory
     */
    SYSRSC_DBG("Invoke SYSFUN_AttachShMem\r\n");
    shmem_header_p = (SYSRSC_MGR_ShMemHeader_T*)SYSFUN_AttachShMem(shmid);

    if(shmem_header_p==NULL)
    {
        printf("%s: SYSFUN_AttachShMem fail.\n", __FUNCTION__);
        free(tmp_shmem_header_p);
        return FALSE;
    }

    /* init shared memory header
     */
    memcpy(shmem_header_p, tmp_shmem_header_p, shmem_header_len);
    free(tmp_shmem_header_p);

    SYSRSC_MGR_SetShMemHeaderPtr(shmem_header_p);

    return TRUE;
}

/*------------------------------------------------------------------------------
 * ROUTINE NAME : SYSRSC_MGR_InitiateAllCSCSystemResources
 *------------------------------------------------------------------------------
 * PURPOSE:
 *    This function will call XXX_InitiateSystemResources() provided by CSCs
 *    that need to initiate system resource.
 *
 * INPUT:
 *    None.
 *
 * OUTPUT:
 *    None.
 *
 * RETURN:
 *    None.
 *
 * NOTES:
 *    None.
 *------------------------------------------------------------------------------
 */
static void SYSRSC_MGR_InitiateAllCSCSystemResources(void)
{
    /* move FLASHDRV init here because it needs to call FS API
     * in SYSRSC_MGR_InitUCSysinfo()
     */
#if (SYS_CPNT_FLASHDRV == TRUE)
    SYSRSC_DBG("%s: Invoke FLASHDRV_INIT_InitiateSystemResources()\r\n", __FUNCTION__);
    FLASHDRV_INIT_InitiateSystemResources();
    #if (SYS_CPNT_FS_SUPPORT_DATA_STORAGE==TRUE)
    /* Refer to the comment for calling SYS_TIME_InitAccumulatedSysUpTimeContrlBlock()
     * within this function
     */
    FS_InitDataStorageControl();
    #endif

#endif

    /* some CSCs need to access UC for initiating system resources
     * for example, SYSDRV_InitiateSystemResources(which will call into UART_TO_I2C_ChipInit())
     */
#if (SYS_CPNT_UCMGMT_SHMEM == TRUE)
    if(UC_MGR_InitiateSystemResources()==FALSE)
    {
        printf("%s(%d):UC_MGR_InitiateProcessResources failed\r\n", __FUNCTION__, __LINE__);
    }
    else
    {
        SYSRSC_MGR_InitUCSysinfo();
    }
#else
    if(UC_MGR_InitiateProcessResources()==FALSE)
    {
        printf("%s(%d):UC_MGR_InitiateProcessResources failed\r\n", __FUNCTION__, __LINE__);
    }
    else
    {
        SYSRSC_MGR_InitUCSysinfo();
    }
#endif

    /* invoke InitiateSystemResources
     */
#if (SYS_CPNT_BUFFERMGMT ==TRUE)
    SYSRSC_DBG("%s: Invoke BUFFERMGMT_INIT_InitiateSystemResources()\r\n", __FUNCTION__);
    BUFFERMGMT_INIT_InitiateSystemResources();
#endif

    SYSRSC_DBG("%s: Invoke SYS_CALLBACK_INIT_InitiateSystemResources()\r\n", __FUNCTION__);
    SYS_CALLBACK_INIT_InitiateSystemResources();


#if (SYS_CPNT_SWDRV == TRUE)
    SYSRSC_DBG("%s: Invoke SWDRV_INIT_InitiateSystemResources()\r\n", __FUNCTION__);
    SWDRV_INIT_InitiateSystemResources();
#endif

#if (SYS_CPNT_AMTRDRV == TRUE)
    SYSRSC_DBG("%s: Invoke AMTRDRV_MGR_InitiateSystemResources()\r\n", __FUNCTION__);
    AMTRDRV_MGR_InitiateSystemResources();
#endif

#if (SYS_CPNT_NMTRDRV == TRUE)
    SYSRSC_DBG("%s: Invoke NMTRDRV_InitiateSystemResources()\r\n", __FUNCTION__);
    NMTRDRV_InitiateSystemResources();
#endif

#if (SYS_CPNT_NICDRV == TRUE)
    SYSRSC_DBG("%s: Invoke LAN_InitiateSystemResources()\r\n", __FUNCTION__);
    DEV_NICDRV_OM_InitSystemResources();
    LAN_InitiateSystemResources();
#endif

#if (SYS_CPNT_ISCDRV == TRUE)
    SYSRSC_DBG("%s: Invoke ISC_INIT_InitiateSystemResources()\r\n", __FUNCTION__);
    ISC_INIT_InitiateSystemResources();
#endif

#if (SYS_CPNT_COS == TRUE)
    SYSRSC_DBG("%s: Invoke COS_OM_InitiateSystemResources()\r\n", __FUNCTION__);
    COS_OM_InitiateSystemResources();
#endif
#if (SYS_CPNT_QOS_V2 == TRUE)
    SYSRSC_DBG("%s: Invoke RULE_OM_InitiateSystemResources()\r\n", __FUNCTION__);
    RULE_OM_InitiateSystemResources();
    SYSRSC_DBG("%s: Invoke RULE_CTRL_InitiateSystemResources()\r\n", __FUNCTION__);
    RULE_CTRL_InitiateSystemResources();
#endif

#if (SYS_CPNT_STACKING == TRUE)
    SYSRSC_DBG("%s: Invoke STKTPLG_SHOM_InitiateSystemResources()\r\n", __FUNCTION__);
    STKTPLG_SHOM_InitiateSystemResources();
#endif

#if (SYS_CPNT_LEDDRV == TRUE)
    SYSRSC_DBG("%s: Invoke LEDDRV_INIT_InitiateSystemResources()\r\n", __FUNCTION__);
    LEDDRV_INIT_InitiateSystemResources();
#endif

#if (SYS_CPNT_SYSDRV == TRUE)
    SYSRSC_DBG("%s: Invoke SYSDRV_INIT_InitiateSystemResources()\r\n", __FUNCTION__);
    SYSDRV_INIT_InitiateSystemResources();
#endif

#if (SYS_CPNT_SYS_TIME == TRUE)
    SYSRSC_DBG("%s: Invoke SYS_TIME_INIT_InitiateSystemResources()\r\n", __FUNCTION__);
    SYS_TIME_INIT_InitiateSystemResources();
#if (SYS_CPNT_SYS_TIME_ACCUMULATED_SYSTEM_UP_TIME == TRUE)
    /* In usual, SYS_TIME_InitAccumulatedSysUpTimeContrlBlock() should be called
     * within the function SYS_TIME_INIT_InitiateSystemResources(). However,
     * SYS_TIME_InitAccumulatedSysUpTimeContrlBlock() is a security-sensitive
     * function which would not be allowed to be put in a shared object library.
     * So it is defined in sys_time_static_lib.c and its compiled object
     * file will be put in libsystime_static.a.
     * The function SYS_TIME_INIT_InitiateSystemResources() will be put in
     * libsystime.so which is a shared object. If SYS_TIME_InitAccumulatedSysUpTimeContrlBlock()
     * is called in the function SYS_TIME_INIT_InitiateSystemResources(), it means
     * that all executable binary file that links to libsystime.so also need to
     * link to libsystime_static.a when writing the Makefile. To avoid the cumbersome
     * and meaningless link to libsystem_static.a, SYS_TIME_InitAccumulatedSysUpTimeContrlBlock
     * is called here.
     */
    SYS_TIME_InitAccumulatedSysUpTimeContrlBlock();
#endif
#endif

#if (SYS_CPNT_SWDRVL3 == TRUE)
    SYSRSC_DBG("%s: Invoke SWDRVL3_INIT_InitiateSystemResources()\r\n", __FUNCTION__);
    SWDRVL3_INIT_InitiateSystemResources();
#endif

#if (SYS_CPNT_SWDRVL4 == TRUE)
    SYSRSC_DBG("%s: Invoke SWDRVL4_Init()\r\n", __FUNCTION__);
    SWDRVL4_Init();
#endif

    SSL_CRYPTO_LOCK_InitateSystemResource();

    SYSRSC_DBG("%s: Invoke HTTP_OM_InitateProcessResource()\r\n", __FUNCTION__);
    HTTP_OM_InitateProcessResource();

/* shumin.wang added for ipfilter 2008 */
#if (SYS_CPNT_MGMT_IP_FLT == TURE)
	SYSRSC_DBG("%s: Invoke MGMT_IP_FLT_INIT_Initiate_System_Resources()\r\n", __FUNCTION__);
	MGMT_IP_FLT_INIT_Initiate_System_Resources();
#endif

#if (SYS_CPNT_POE == TRUE)
    SYSRSC_DBG("%s: Invoke POEDRV_INIT_InitiateSystemResources()\r\n", __FUNCTION__);
    POEDRV_INIT_InitiateSystemResources();
#endif

#if (SYS_CPNT_CFGDB == TRUE)
    SYSRSC_DBG("%s: Invoke CFGDB_INIT_InitiateSystemResources()\r\n", __FUNCTION__);
    CFGDB_INIT_InitiateSystemResources();
#endif
#if (TRUE == TRUE)
    SYSRSC_DBG("%s: Invoke XSTP_SHARE_OM_InitiateSystemResources()\r\n", __FUNCTION__);
    XSTP_SHARE_OM_InitiateSystemResources();
#endif
#if (SYS_CPNT_VLAN == TRUE)
    SYSRSC_DBG("%s: Invoke VLAN_OM_InitiateSystemResources()\r\n", __FUNCTION__);
    VLAN_OM_InitiateSystemResources();
#endif

#if (SYS_CPNT_SNMP == TRUE)
    SNMP_PMGR_InitiateSystemResources();
#endif

    NETCFG_OM_IP_InitateSystemResources();

#if (SYS_CPNT_RSPAN == TRUE)
    RSPAN_OM_InitDataBase();
#endif /* #if (SYS_CPNT_RSPAN == TRUE) */

#if (SYS_CPNT_AMTR == TRUE)
    AMTR_OM_InitiateSystemResources();
#endif

#if (SYS_CPNT_DOS == TRUE)
    DOS_OM_InitiateSystemResources();
#endif

#if (SYS_CPNT_APP_FILTER == TRUE)
    AF_OM_InitiateSystemResources();
#endif /* #if (SYS_CPNT_APP_FILTER == TRUE) */

    SYSRSC_DBG("%s: Invoke BACKDOOR_MGR_InitiateSystemResources()\r\n", __FUNCTION__);
    BACKDOOR_MGR_InitiateSystemResources();

#if (SYS_CPNT_SW_WATCHDOG_TIMER == TRUE)
    SYSRSC_DBG("%s: Invoke SW_WATCHDOG_MGR_InitiateSystemResources()\r\n", __FUNCTION__);
    SW_WATCHDOG_MGR_InitiateSystemResources();
#endif

#if (SYS_CPNT_SWCTRL == TRUE)
    SYSRSC_DBG("%s: Invoke SWCTRL_OM_InitiateSystemResources()\r\n", __FUNCTION__);
    SWCTRL_OM_InitiateSystemResources();
#endif

#if (SYS_CPNT_SYNCE == TRUE)
    SYSRSC_DBG("%s: Invoke SYNCEDRV_OM_InitiateSystemResources()\r\n", __FUNCTION__);
    SYNCEDRV_OM_InitiateSystemResources();
#endif

#if (SYS_CPNT_SFLOW == TRUE)
    SYSRSC_DBG("%s: Invoke SFLOW_OM_InitiateSystemResources()\r\n", __FUNCTION__);
    SFLOW_OM_InitiateSystemResources();
#endif

#if (SYS_CPNT_EH == TRUE)
    SYSRSC_DBG("%s: Invoke EH_OM_InitiateSystemResources()\r\n", __FUNCTION__);
    EH_OM_InitiateSystemResources();
#endif

#if (SYS_CPNT_CLI == TRUE)
    SYSRSC_DBG("%s: Invoke CLI_OM_InitiateSystemResources()\r\n", __FUNCTION__);
    CLI_OM_EXP_InitiateSystemResources();
#endif /* SYS_CPNT_CLI */
#if(SYS_CPNT_VXLAN == TRUE)
    SYSRSC_DBG("%s: Invoke VXLAN_OM_InitiateSystemResource()\r\n", __FUNCTION__);
    VXLAN_OM_InitiateSystemResources();
#endif  /* #if(SYS_CPNT_VXLAN == TRUE) */
}

/*------------------------------------------------------------------------------
 * ROUTINE NAME : SYSRSC_MGR_InitUCSysinfo
 *------------------------------------------------------------------------------
 * PURPOSE:
 *    This function will init the UC sysinfo according to hwinfo
 *    on the flash.
 *
 * INPUT:
 *    None.
 *
 * OUTPUT:
 *    None.
 *
 * RETURN:
 *    None.
 *
 * NOTES:
 *    None.
 *------------------------------------------------------------------------------
 */
static void SYSRSC_MGR_InitUCSysinfo(void)
{
    FS_HW_Info_T hw_info;
    UC_MGR_Sys_Info_T sys_info;

    /* get current system information from UC */
    UC_MGR_Allocate(UC_MGR_SYS_INFO_INDEX, sizeof(UC_MGR_Sys_Info_T), 4);

    UC_MGR_GetSysInfo(&sys_info);
    FS_ReadHardwareInfo(DUMMY_DRIVE, &hw_info);

    /* transfer h/w information to UC's system information area */
    /* MAC address is one of the data */
    memcpy(sys_info.mac_addr, hw_info.mac_addr, SYS_ADPT_MAC_ADDR_LEN);
    memcpy(sys_info.serial_no, hw_info.serial_no, SYS_ADPT_SERIAL_NO_STR_LEN+1);
    memcpy(sys_info.sw_service_tag, hw_info.service_tag, SYS_ADPT_SERIAL_NO_STR_LEN+1);
    memcpy(sys_info.mainboard_hw_ver, hw_info.agent_hw_ver, SYS_ADPT_HW_VER_STR_LEN+1);
    memcpy(sys_info.manufacture_date, hw_info.manufacture_date, SYS_ADPT_MANUFACTURE_DATE_LEN);
    sys_info.manufacture_date[SYS_ADPT_MANUFACTURE_DATE_LEN]='\0';
    memcpy(sys_info.model_number,     hw_info.model_num_by_string, SYS_ADPT_MODEL_NUMBER_LEN + 1);
    sys_info.board_id   = hw_info.board_id;
    sys_info.project_id = hw_info.project_id;

    UC_MGR_SetSysInfo(sys_info);

    return;
}

