/*system*/
#define RUNCFG_DEVELOP 0
/*syb-systems*/
#include <arpa/inet.h>
#include "sys_type.h"
#include "sys_cpnt.h"
#include "sys_hwcfg.h"
#include "sys_module.h"
#include "l_mm.h"
#include "cli_type.h"
#include "l_inet.h"
#include "l_cvrt.h"
#if 0 //rich
#include "sock_port.h"
#include "netif_om.h"
#if (SYS_CPNT_COS == TRUE)
#include "l4_cos_mgr.h"
#include "cos_vm.h"
#endif
#include "L_MD5.h"
#if (SYS_CPNT_SMTP == TRUE)
#include "smtp_mgr.h"
#endif
#endif
#if (SYS_CPNT_SMTP == TRUE)
    #include "smtp_pmgr.h"
#endif

#if (SYS_CPNT_SNTP == TRUE)
    #include "sntp_pmgr.h"
#endif

#if (SYS_CPNT_NTP == TRUE)
#include "ntp_pmgr.h"
#include "ntp_type.h"
#endif

#include "swctrl.h"
#include "leaf_sys.h"
#include "stktplg_task.h"
#include "vlan_mgr.h"
#include "sys_time.h"
#include "leaf_2674p.h"
#include "leaf_2674q.h"
#include "trk_mgr.h"
#include "fs.h"
#include "cli_api.h"
#include "userauth.h"
#include "syslog_type.h"
#include "sys_mgr.h"
#include "sys_dflt.h"
#if (SYS_CPNT_RIP == TRUE)
#include "netcfg_pmgr_rip.h"
#endif
#if (SYS_CPNT_OSPF == TRUE)
#include "ospf_type.h"
#include "ospf_pmgr.h"
#endif
#include "l_md5.h"
#include "dhcp_pmgr.h"
#include "dhcp_mgr.h"
#include "tacacs_pom.h"
#include "netcfg_type.h"
#include "netcfg_pom_nd.h"
#include "netcfg_pmgr_nd.h"
#include "netcfg_pom_route.h"
#include "netcfg_mgr_route.h"
#include "netcfg_pmgr_route.h"
#include "ip_lib.h"
#include "vlan_lib.h"

#if (SYS_CPNT_COS == TRUE)
    #if (SYS_CPNT_QOS_V2 != TRUE)
        #include "l4_cos_mgr.h"
    #endif

    #include "cos_vm.h"
#endif
#if (SYS_CPNT_IP_FOR_ETHERNET0 == TRUE)
#include <net/if.h>/*fuzhimin,20090212*/
#endif
#include "sys_adpt.h"
#include "l_inet.h"
#include <string.h>
#include "stktplg_mgr.h"
#include "mib2_mgr.h"
//#include <stdio.h>
#include "syslog_mgr.h"
#include "amtr_mgr.h"
#include "leaf_2863.h"
//#include "netcfg.h"
#include "iml.h"
#include "pri_mgr.h"
#include "lacp_mgr.h"
#include "extbrg_mgr.h"
#include "smtp_om.h"
#if (SYS_CPNT_NSM == TRUE)
#include "nsm_pmgr.h"
#endif

#include "trap_mgr.h"

#include "userauth_pmgr.h"
/*cli internal*/
#include "cli_def.h"
#include "cli_lib.h"
#include "cli_runcfg.h"
//#include "cli_api.h"
#include "cli_msg.h"
#if (SYS_CPNT_STP == SYS_CPNT_STP_TYPE_RSTP || SYS_CPNT_STP == SYS_CPNT_STP_TYPE_MSTP)
#include "xstp_pmgr.h"
#include "xstp_pom.h"
#include "xstp_type.h"
#endif
#include "cli_api_vlan.h"

#if (CLI_SUPPORT_L2_DHCP_RELAY == 1)
#include "brg_mgr.h"
#endif

#include "if_mgr.h"

#if (SYS_CPNT_VDSL == TRUE)
#include "vdsl_drv.h"
#endif

#if (SYS_CPNT_PORT_SECURITY == TRUE)
#include "psec_mgr.h"
#include "psec_pmgr.h"
#endif

#if (SYS_CPNT_PFU == TRUE)
#include "pfu_type.h"
#include "pfu_mgr.h"
#endif

#if (SYS_CPNT_TACACS == TRUE )
#include "tacacs_mgr.h"
#endif

#if (SYS_CPNT_SSHD == TRUE || SYS_CPNT_SSH2 == TRUE)
#include "sshd_type.h"
#include "sshd_mgr.h"
#endif

#if (SYS_CPNT_HTTP == TRUE || SYS_CPNT_HTTPS == TRUE)
#include "http_pmgr.h"
#include "http_type.h"
#endif  /* #if (SYS_CPNT_HTTP == TRUE || SYS_CPNT_HTTPS == TRUE) */

#if ((CLI_SUPPORT_DHCP_CLIENTID == 1) || (CLI_SUPPORT_L3_FEATURE == 1))
#include "dhcp_mgr.h"
#endif

#include "dhcp_mgr.h"
#include "dhcp_pmgr.h"
#include "dhcp_pom.h"
#include "dhcp_om.h"
#if (SYS_CPNT_DHCP_CLIENT_CLASSID == TRUE)
#include "dhcp_type.h"
#endif

#if (SYS_CPNT_AAA == TRUE)
#include "aaa_mgr.h"
#include "aaa_pom.h"
#endif

#if (SYS_CPNT_DOT1X == TRUE)
#include "1x_mgr.h"
#include "1x_pom.h"
#include "leaf_ieee8021x.h"
#endif

#if (SYS_CPNT_RADIUS == TRUE)
#include "radius_pmgr.h"
#include "radius_pom.h"
#endif

#if (SYS_CPNT_TACACS == TRUE )
#include "tacacs_pmgr.h"
#include "tacacs_pom.h"
#endif

#if 0 //rich
#if (CLI_SUPPORT_L3_FEATURE == 1)
#include "netcfg_type.h"
#include "netcfg_mgr.h"
#else
#include "netcfg.h"
#endif
#endif

#include "netcfg_type.h"
#if (SYS_CPNT_ACL == TRUE)
#if (SYS_CPNT_QOS_V2 == TRUE)
    #include "l4_pmgr.h"
    #include "cli_api_acl.h"
#else
    #include "acl_type.h"
    #include "l4_acl_mgr.h"
#endif /* #if (SYS_CPNT_QOS_V2 == TRUE) */

    #include "cli_api_acl.h"
#endif /* #if (SYS_CPNT_ACL == TRUE) */

#if ((SYS_CPNT_QOS == SYS_CPNT_QOS_MARKER) && (SYS_CPNT_QOS_V2 != TRUE))
#include "l4_marker_mgr.h"
#endif

#if (SYS_CPNT_DNS == TRUE)
#include "dns_mgr.h"
#include "dns_pmgr.h"
#include "dns_type.h"
#endif

#if 0//rich

#if (SYS_CPNT_QOS == SYS_CPNT_QOS_DIFFSERV)
#include "l4_ds_mgr.h"
#include "l4_ds_type.h"
#endif

#endif
#include "l_base64.h"

#if (SYS_CPNT_MGMT_IP_FLT == TRUE)
#include "mgmt_ip_flt.h"
#endif

#if (SYS_CPNT_SNMP_VERSION == 3)
#include "snmp_mgr.h"
#include "leaf_3411.h"
#endif

#if (SYS_CPNT_HSRP == TRUE)
#include "hsrp_mgr.h"
#include "hsrp_sys_adpt.h"
#endif


#if (SYS_CPNT_VRRP == TRUE)
#include "vrrp_mgr.h"
#include "vrrp_pmgr.h"
#include "vrrp_type.h"
#include "vlan_lib.h"
#endif

#include "telnet_mgr.h"

#if (SYS_CPNT_POE == TRUE)
#include "poe_pom.h"
#endif

#if (SYS_CPNT_MOTD == TRUE)
#include "sys_bnr_mgr.h"
#endif

#if (SYS_CPNT_LACP == TRUE)
#include "lacp_pom.h"
#endif
#if (SYS_CPNT_LLDP == TRUE)
#include "lldp_mgr.h"
#include "lldp_pom.h"
#include "lldp_type.h"
#include "lldp_pmgr.h"
#endif

#if(SYS_CPNT_CLUSTER==TRUE)
#include "cluster_mgr.h"
#include "cluster_type.h"
#include "cluster_pom.h"
#endif

#if (SYS_CPNT_CLI_BANNER == TRUE)
#include "cli_banner.h"
#endif

#if (SYS_CPNT_L2MCAST == TRUE)
#include "igv3snp_pmgr.h"
#endif

#include "swctrl_pom.h"
#include "temp.h"

/* for OAM */
#if (SYS_CPNT_EFM_OAM == TRUE)
#include "oam_mgr.h"
#include "oam_pom.h"
#include "oam_type.h"
#include "leaf_4878.h"
#endif

/*for DHCPSNP*/
#if (SYS_CPNT_DHCPSNP == TRUE)
#include "dhcpsnp_mgr.h"
#include "dhcpsnp_pmgr.h"
#include "dhcpsnp_type.h"
#endif

/*for DHCP relay information option 82 */
#if (SYS_CPNT_DHCP_RELAY_OPTION82 == TRUE)
#include "dhcp_pom.h"
#endif

/*for DHCPv6 */
#if (SYS_CPNT_DHCPV6 == TRUE)
#include "dhcpv6_pmgr.h"
#include "cfg.h"
#endif

/*for DHCPv6 Relay*/
#if (SYS_CPNT_DHCPV6_RELAY == TRUE)
#include "dhcpv6_pom.h"
#endif

/*for MLDSNP*/
#if(SYS_CPNT_MLDSNP==TRUE)
#include "mldsnp_pom.h"
#include "mldsnp_type.h"
#endif

/*Net Access */
#if(SYS_CPNT_NETACCESS == TRUE)
#include "netaccess_pmgr.h"
#include "netaccess_type.h"
#endif  /* #if(SYS_CPNT_NETACCESS == TRUE) */

/*for cwmp*/
#if (SYS_CPNT_CWMP == TRUE)
#include "cwmp_type.h"
#include "cwmp_pom.h"
#endif

#if (SYS_CPNT_QOS == SYS_CPNT_QOS_DIFFSERV)
#include "rule_type.h"
#endif

#if(SYS_CPNT_OSPF == TRUE)
#include "netcfg_mgr_ospf.h"
#include "netcfg_pmgr_ospf.h"
#endif
/* cfm */
#if(SYS_CPNT_CFM == TRUE)
#include "cfm_pmgr.h"
#endif

#if (SYS_CPNT_PPPOE_IA == TRUE)
#include "pppoe_ia_pmgr.h"
#endif /* #if (SYS_CPNT_PPPOE_IA == TRUE) */

#if (SYS_CPNT_ADD == TRUE)
#include "add_pmgr.h"
#endif
#if (SYS_CPNT_UDP_HELPER == TRUE)
#include "udphelper_type.h"
#include "udphelper_pmgr.h"
#endif

#include "netcfg_pom_ip.h"
#include "netcfg_pmgr_ip.h"

#if (SYS_CPNT_DAI == TRUE)
#include "dai_pmgr.h"
#endif/*#if (SYS_CPNT_DAI == TRUE)*/

#if(SYS_CPNT_MAC_VLAN == TRUE)
#include "cli_api_mac_vlan.h"
#endif
#if (SYS_CPNT_SYSMGMT == TRUE)
#include "sys_pmgr.h"
#endif

#if (SYS_CPNT_OSPF6 == TRUE)
#include "ospf6_type.h"
#include "ospf6_pmgr.h"
#endif

#if (SYS_CPNT_RSPAN == TRUE)
#include "leaf_es3626a.h"
#include "rspan_om.h"
#include "rspan_pmgr.h"
#include "cli_api_rspan.h"
#endif

#if (SYS_CPNT_WEBAUTH == TRUE)
#include "webauth_pmgr.h"
#include "webauth_type.h"
#endif /* #if(SYS_CPNT_WEBAUTH == TRUE) */

#if (SYS_CPNT_XFER_AUTO_UPGRADE == TRUE)
#include "xfer_pmgr.h"
#endif

#if (SYS_CPNT_DOS == TRUE)
#include "dos_pmgr.h"
#endif

#if (SYS_CPNT_DHCPV6SNP == TRUE)
#include "dhcpv6snp_pom.h"
#include "dhcpv6snp_pmgr.h"
#endif

#if (SYS_CPNT_BGP == TRUE)
#include "bgp_type.h"
#include "bgp_pmgr.h"
#include "bgp_pom.h"
#endif

#if (SYS_CPNT_NSM_POLICY == TRUE)
#include "nsm_policy_type.h"
#include "nsm_policy_pmgr.h"
#endif

#include "leaf_3019.h"

#if (SYS_CPNT_NDSNP == TRUE)
#include "ndsnp_pom.h"
#endif

#if (SYS_CPNT_IPV6_SOURCE_GUARD == TRUE)
#include "ip6sg_pom.h"
#endif

#if (SYS_CPNT_SYNCE==TRUE)
#include "sync_e_pmgr.h"
#include "syncedrv_type.h"
#include "l_pbmp.h"
#endif

#if (SYS_CPNT_PFC == TRUE)
#include "pfc_pmgr.h"
#endif
#if (SYS_CPNT_ETS==TRUE)
#include "ets_pmgr.h"
#endif
#if (SYS_CPNT_DCBX == TRUE)
#include "dcbx_pmgr.h"
#endif

#if (SYS_CPNT_CN == TRUE)
#include "cn_pom.h"
#include "cn_type.h"
#endif

#if (SYS_CPNT_APP_FILTER == TRUE)
#include "af_type.h"
#include "af_pmgr.h"
#endif /* #if (SYS_CPNT_APP_FILTER == TRUE) */

#if (SYS_CPNT_MLAG == TRUE)
#include "mlag_pom.h"
#include "mlag_type.h"
#endif

#if (SYS_CPNT_VXLAN == TRUE)
#include "vxlan_pom.h"
#include "vxlan_type.h"
#include "amtrl3_mgr.h"
#include "amtrl3_om.h"
#include "amtrl3_pom.h"
#endif

#if (SYS_CPNT_PBR == TRUE)
#include "netcfg_pom_pbr.h"
#endif

#ifndef ASSERT
#define ASSERT(e)
#endif

#ifndef _countof
#define _countof(_Ary)  (sizeof(_Ary) / sizeof(*_Ary))
#endif /* _countof */

typedef struct
{
    UI32_T value;   /*the value of this variable*/
    UI32_T type;    /*which type of variable  maxage = 1 , hello = 2 , forward = 3*/
    BOOL_T valid;   /*is valid to use*/
}CLI_RUNCFG_Sequence_T;


typedef struct
{
    UI32_T starting_port_ifindex;
    UI32_T number_of_port;
}CLI_RUNCFG_ModuleInfo_T;


typedef UI32_T (* Func_T)    (UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count);


/*macros*/
#define APPEND_RUNNING_CFG(FORMAT, ARGS...) do{                                 \
        memset(temp_buffer, 0, CLI_DEF_MAX_BUFSIZE);                            \
        SYSFUN_Snprintf((char *)temp_buffer, CLI_DEF_MAX_BUFSIZE, FORMAT, ##ARGS);  \
        if(buffer_count + strlen((char *)temp_buffer) >= buffer_size)           \
        {                                                                       \
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;                          \
        }                                                                       \
        else                                                                    \
            buffer_count += strlen((char *)temp_buffer);                        \
        memcpy(&(buffer[buffer_count-strlen((char *)temp_buffer)]), temp_buffer , strlen((char *)temp_buffer)+1);   \
    }while(0)

#define APPEND_RUNNING_CFG_0(FORMAT) {                                          \
        memset(temp_buffer, 0, CLI_DEF_MAX_BUFSIZE);                            \
        SYSFUN_Snprintf((char *)temp_buffer, CLI_DEF_MAX_BUFSIZE, FORMAT);      \
        if(buffer_count + strlen((char *)temp_buffer) >= buffer_size)           \
        {                                                                       \
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;                          \
        }                                                                       \
        else                                                                    \
            buffer_count += strlen((char *)temp_buffer);                        \
        memcpy(&(buffer[buffer_count-strlen((char *)temp_buffer)]), temp_buffer , strlen((char *)temp_buffer)+1);   \
    }

#define APPEND_RUNNING_CFG_1(FORMAT, ARG1) {                                    \
        memset(temp_buffer, 0, CLI_DEF_MAX_BUFSIZE);                            \
        SYSFUN_Snprintf((char *)temp_buffer, CLI_DEF_MAX_BUFSIZE, FORMAT, ARG1);\
        if(buffer_count + strlen((char *)temp_buffer) >= buffer_size)           \
        {                                                                       \
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;                          \
        }                                                                       \
        else                                                                    \
            buffer_count += strlen((char *)temp_buffer);                        \
        memcpy(&(buffer[buffer_count-strlen((char *)temp_buffer)]), temp_buffer , strlen((char *)temp_buffer)+1);   \
    }

#define APPEND_RUNNING_CFG_2(FORMAT, ARG1, ARG2) {                              \
        memset(temp_buffer, 0, CLI_DEF_MAX_BUFSIZE);                            \
        SYSFUN_Snprintf((char *)temp_buffer, CLI_DEF_MAX_BUFSIZE, FORMAT, ARG1, ARG2);  \
        if(buffer_count + strlen((char *)temp_buffer) >= buffer_size)           \
        {                                                                       \
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;                          \
        }                                                                       \
        else                                                                    \
            buffer_count += strlen((char *)temp_buffer);                        \
        memcpy(&(buffer[buffer_count-strlen((char *)temp_buffer)]), temp_buffer , strlen((char *)temp_buffer)+1);   \
    }

#define APPEND_RUNNING_CFG_3(FORMAT, ARG1, ARG2, ARG3) {                        \
        memset(temp_buffer, 0, CLI_DEF_MAX_BUFSIZE);                            \
        SYSFUN_Snprintf((char *)temp_buffer, CLI_DEF_MAX_BUFSIZE, FORMAT, ARG1, ARG2, ARG3);       \
        if(buffer_count + strlen((char *)temp_buffer) >= buffer_size)           \
        {                                                                       \
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;                          \
        }                                                                       \
        else                                                                    \
            buffer_count += strlen((char *)temp_buffer);                        \
        memcpy(&(buffer[buffer_count-strlen((char *)temp_buffer)]), temp_buffer , strlen((char *)temp_buffer)+1);   \
    }

#define APPEND_RUNNING_CFG_4(FORMAT, ARG1, ARG2, ARG3, ARG4) {                  \
        memset(temp_buffer, 0, CLI_DEF_MAX_BUFSIZE);                            \
        SYSFUN_Snprintf((char *)temp_buffer, CLI_DEF_MAX_BUFSIZE, FORMAT, ARG1, ARG2, ARG3, ARG4);     \
        if(buffer_count + strlen((char *)temp_buffer) >= buffer_size)           \
        {                                                                       \
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;                          \
        }                                                                       \
        else                                                                    \
            buffer_count += strlen((char *)temp_buffer);                        \
        memcpy(&(buffer[buffer_count-strlen((char *)temp_buffer)]), temp_buffer , strlen((char *)temp_buffer)+1);   \
    }

#define APPEND_RUNNING_CFG_5(FORMAT, ARG1, ARG2, ARG3, ARG4, ARG5) {            \
        memset(temp_buffer, 0, CLI_DEF_MAX_BUFSIZE);                            \
        SYSFUN_Snprintf((char *)temp_buffer, CLI_DEF_MAX_BUFSIZE, FORMAT, ARG1, ARG2, ARG3, ARG4, ARG5);     \
        if(buffer_count + strlen((char *)temp_buffer) >= buffer_size)           \
        {                                                                       \
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;                          \
        }                                                                       \
        else                                                                    \
            buffer_count += strlen((char *)temp_buffer);                        \
        memcpy(&(buffer[buffer_count-strlen((char *)temp_buffer)]), temp_buffer , strlen((char *)temp_buffer)+1);   \
    }

#define APPEND_RUNNING_CFG_6(FORMAT, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) {      \
        memset(temp_buffer, 0, CLI_DEF_MAX_BUFSIZE);                            \
        SYSFUN_Snprintf((char *)temp_buffer, CLI_DEF_MAX_BUFSIZE, FORMAT, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6);     \
        if(buffer_count + strlen((char *)temp_buffer) >= buffer_size)           \
        {                                                                       \
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;                          \
        }                                                                       \
        else                                                                    \
            buffer_count += strlen((char *)temp_buffer);                        \
        memcpy(&(buffer[buffer_count-strlen((char *)temp_buffer)]), temp_buffer , strlen((char *)temp_buffer)+1);   \
    }



#define APPEND_RUNNING_CFG_7(FORMAT, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) { \
        memset(temp_buffer, 0, CLI_DEF_MAX_BUFSIZE);                            \
        SYSFUN_Snprintf((char *)temp_buffer, CLI_DEF_MAX_BUFSIZE, FORMAT, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7);     \
        if(buffer_count + strlen((char *)temp_buffer) >= buffer_size)           \
        {                                                                       \
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;                          \
        }                                                                       \
        else                                                                    \
            buffer_count += strlen((char *)temp_buffer);                        \
        memcpy(&(buffer[buffer_count-strlen((char *)temp_buffer)]), temp_buffer , strlen((char *)temp_buffer)+1);   \
    }

#define APPEND_RUNNING_CFG_8(FORMAT, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8) { \
        memset(temp_buffer, 0, CLI_DEF_MAX_BUFSIZE);                            \
        SYSFUN_Snprintf((char *)temp_buffer, CLI_DEF_MAX_BUFSIZE, FORMAT, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8);     \
        if(buffer_count + strlen((char *)temp_buffer) >= buffer_size)           \
        {                                                                       \
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;                          \
        }                                                                       \
        else                                                                    \
            buffer_count += strlen((char *)temp_buffer);                        \
        memcpy(&(buffer[buffer_count-strlen((char *)temp_buffer)]), temp_buffer , strlen((char *)temp_buffer)+1);   \
    }
#define APPEND_RUNNING_CFG_9(FORMAT, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9) { \
        memset(temp_buffer, 0, CLI_DEF_MAX_BUFSIZE);                            \
        SYSFUN_Snprintf((char *)temp_buffer, CLI_DEF_MAX_BUFSIZE, FORMAT, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9);     \
        if(buffer_count + strlen((char *)temp_buffer) >= buffer_size)           \
        {                                                                       \
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;                          \
        }                                                                       \
        else                                                                    \
            buffer_count += strlen((char *)temp_buffer);                        \
        memcpy(&(buffer[buffer_count-strlen((char *)temp_buffer)]), temp_buffer , strlen((char *)temp_buffer)+1);   \
    }

#define COLLECT_ENCRTPT_TEXT_TO_PRINT(ENCRY, PLAIN)                             \
    SYSFUN_Sprintf(ENCRY, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",   \
    PLAIN[0], PLAIN[1], PLAIN[2],  PLAIN[3],  PLAIN[4],  PLAIN[5],  PLAIN[6],  PLAIN[7],        \
    PLAIN[8], PLAIN[9], PLAIN[10], PLAIN[11], PLAIN[12], PLAIN[13], PLAIN[14], PLAIN[15]);

#define COLLECT_ENCRTPT_TEXT_TO_PRINT_LENGTH(ENCRY, PLAIN, BYTE_LEN)          { \
        UI32_T i;                                                               \
        char buff[10] = {0};                                                    \
        for(i=0;i<BYTE_LEN;i++)                                                 \
        {                                                                       \
            SYSFUN_Sprintf(buff, "%02x", PLAIN[i]);                             \
            strcat(ENCRY,buff);                                                 \
        }                                                                       \
    }

#define CHECK_BUFF_RETURN_VALUE(buffer_count)                                   \
    if (buffer_count == CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY)                     \
        return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;                              \


extern UI32_T DHCP_PMGR_C_GetRunningClientId(UI32_T vid_ifIndex, DHCP_MGR_ClientId_T *cid_p);
extern UI32_T  TACACS_POM_GetRunningServerSecret(UI8_T serversecret[]);
extern UI32_T TACACS_POM_GetRunningServerPort(UI32_T *serverport);
extern UI32_T TACACS_POM_GetNextRunning_Server_Host(UI32_T *index,TACACS_Server_Host_T *server_host);
extern UI32_T NETCFG_POM_IP_GetIpAddressMode(UI32_T ifindex, UI32_T *mode_p);
extern UI32_T NETCFG_POM_IP_GetL3Interface(NETCFG_TYPE_L3_Interface_T *intf_p);
extern UI32_T NETCFG_PMGR_ARP_GetNextStaticIpNetToMediaEntry(NETCFG_TYPE_StaticIpNetToMediaEntry_T *entry);
extern SYS_TYPE_Get_Running_Cfg_T NETCFG_PMGR_ARP_GetRunningIpNetToMediaTimeout(UI32_T *age_time);
extern UI32_T IGMPSNP_PMGR_GetRunningProxyQueryRespIntervalPerVlan(UI32_T vid,UI32_T* interval);
extern UI32_T NETCFG_PMGR_RIP_GetInterfaceEntry(NETCFG_TYPE_RIP_If_T *entry);
extern UI32_T NETCFG_PMGR_RIP_GetInstanceEntry(NETCFG_TYPE_RIP_Instance_T *entry);
extern UI32_T NETCFG_PMGR_RIP_GetNextDistanceTable(NETCFG_TYPE_RIP_Distance_T *entry);
extern UI32_T NETCFG_PMGR_RIP_GetNextNeighborTable(NETCFG_TYPE_RIP_Network_T *entry);
extern UI32_T NETCFG_PMGR_RIP_GetNextInterfaceEntry(NETCFG_TYPE_RIP_If_T *entry);
extern UI32_T NETCFG_PMGR_RIP_GetNextNetworkTable(NETCFG_TYPE_RIP_Network_T *entry);
extern UI32_T NETCFG_PMGR_RIP_GetNextRedistributeTable(NETCFG_TYPE_RIP_Redistribute_Table_T *entry);
void IP_LIB_CidrToMask(UI32_T prefix_length, UI8_T mask[SYS_ADPT_IPV4_ADDR_LEN]);
UI32_T IP_LIB_MaskToCidr(UI8_T mask[SYS_ADPT_IPV4_ADDR_LEN]);

/* FUNCTION : CLI_RUNCFG_Check_Sequence
 * PURPOSE  : This function is used to specify the sequence of "hello" "maxage" and "forward" time.
 *            Also can check sequence of "join" "leave" and "leaveall" timer of garp.
 * INPUT    : A = input variable , B = default value  type = 1 is for STA , type = 2 is for GARP
 *            count = number of variable , point = the stack pointer
 * OUTPUT   : C = the output sequence variable
 * RETUEN   : TRUE/FALSE
 * NOTES    :
 *
 */
static BOOL_T CLI_RUNCFG_Check_Sequence(CLI_RUNCFG_Sequence_T *A, CLI_RUNCFG_Sequence_T *B, CLI_RUNCFG_Sequence_T *C, UI32_T *point, UI32_T count ,UI8_T type);
static BOOL_T CLI_RUNCFG_Check_STA_Inequality(UI32_T maxage, UI32_T hello ,UI32_T forward);

static void CLI_Runcfg_ListStrToOneLine(I32_T *process_length, UI32_T dec_number, char *str_list, char *print_str);


#if (SYS_CPNT_STACKING == TRUE)
static UI32_T CLI_RUNCFG_Get_Stacking_UnitMAC(UI32_T unit_id, char *buffer, char *temp_buffer,
                                              UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_INIT_PHASE_PROVISION == TRUE)
static UI32_T CLI_RUNCFG_Get_Init_Phase_Config(UI32_T unit_id, char *buffer, char *temp_buffer,
                                              UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_SYNCE==TRUE)
static UI32_T CLI_RUNCFG_Get_SyncE_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                             UI32_T buffer_size, UI32_T b_count);
#endif

static UI32_T CLI_RUNCFG_Get_System_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#if defined(SYS_CPNT_SNMP) && (SYS_CPNT_SNMP == TRUE)
static UI32_T CLI_RUNCFG_Get_Snmp_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif
static UI32_T CLI_RUNCFG_Get_Rmon_Config_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
static UI32_T CLI_RUNCFG_Get_Auth_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
static UI32_T CLI_RUNCFG_Get_Syslog_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#if (SYS_CPNT_SMTP == TRUE)
static UI32_T CLI_RUNCFG_Get_Smtp_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif
static UI32_T CLI_RUNCFG_Get_VlanDatabase_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);

/* 2006/06/28
 * ES4649-38-00189: free memory before return
 */
static UI32_T cli_runcfg_get_vlanDatabase_parameter_macro(UI32_T unit_id, char *buffer, char *temp_buffer,
                                UI32_T buffer_size, UI32_T b_count, char *str_list);
static UI32_T CLI_RUNCFG_Get_Create_Trunk(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);

static UI32_T CLI_RUNCFG_Get_Ethernet_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);

static UI32_T CLI_RUNCFG_Get_Ethernet_Parameter_One_Port(UI32_T unit_id, UI32_T port_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
static UI32_T CLI_RUNCFG_Get_Loopback_Parameter(UI32_T unit_id, char * buffer, char * temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);

static UI32_T CLI_RUNCFG_Get_Trunk_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
static UI32_T CLI_RUNCFG_Get_Trunk_Parameter_Per_Trunk(UI32_T trunk_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
static UI32_T  CLI_RUNCFG_Get_Control_Plane_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
static UI32_T CLI_RUNCFG_Get_VLAN_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
static UI32_T CLI_RUNCFG_Get_VLAN_Parameter_Per_VLAN(UI32_T vid, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#if (SYS_CPNT_IP_TUNNEL == TRUE)
static UI32_T CLI_RUNCFG_Get_IpTunnel_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif /*SYS_CPNT_IP_TUNNEL*/
/*fuzhimin,20090106*/
#if (SYS_CPNT_IP_FOR_ETHERNET0 == TRUE)
static UI32_T CLI_RUNCFG_Get_Ethernet0_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif
/*fuzhimin,20090106,end*/
static UI32_T CLI_RUNCFG_Get_PFU_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
static UI32_T CLI_RUNCFG_Get_MSTP_Mode_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);

static UI32_T CLI_RUNCFG_Get_Line_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);

static UI32_T CLI_RUNCFG_Get_VDSL_Global_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);

static UI32_T CLI_RUNCFG_Get_HTTP_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);

static UI32_T CLI_RUNCFG_Get_Spanningtree_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);

static UI32_T CLI_RUNCFG_Get_Remote_Auth_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);

static UI32_T CLI_RUNCFG_Get_COS_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);

static UI32_T CLI_RUNCFG_Get_SSH_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);

static UI32_T CLI_RUNCFG_Get_TFTP_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);

static UI32_T CLI_RUNCFG_Get_PVLAN_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);

/* 2006/06/28
 * ES4649-38-00189: free memory before return
 */
#if (SYS_CPNT_PORT_TRAFFIC_SEGMENTATION == TRUE)
#if (SYS_CPNT_PORT_TRAFFIC_SEGMENTATION_MODE == SYS_CPNT_PORT_TRAFFIC_SEGMENTATION_MODE_MULTIPLE_SESSION)
static UI32_T cli_runcfg_get_pvlan_ms_parameter_macro(UI32_T unit_id, char *buffer, char *temp_buffer,
                 UI32_T buffer_size, UI32_T b_count, char *tmp_buff, char *uplink_str_eth, char *uplink_str_pch,
                 char *downlink_str_eth, char *downlink_str_pch, char *uplink_str, char *downlink_str,
                 char *uplink_port_list, char *downlink_port_list);
#else
static UI32_T cli_runcfg_get_pvlan_parameter_macro(UI32_T unit_id, char *buffer, char *temp_buffer,
                 UI32_T buffer_size, UI32_T b_count, char *tmp_buff, char *uplink_str_eth, char *uplink_str_pch,
                 char *downlink_str_eth, char *downlink_str_pch, char *uplink_str, char *downlink_str,
                 char *uplink_port_list, char *downlink_port_list);
#endif
#endif
#if (SYS_CPNT_DOT1X == TRUE)
static UI32_T CLI_RUNCFG_Get_Dot1x_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif /* #if (SYS_CPNT_DOT1X == TRUE) */
#if (SYS_CPNT_DOT1X_EAPOL_PASS_THROUGH == TRUE)
static UI32_T CLI_RUNCFG_Get_Dot1xEapolPassThrough_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif /* #if (SYS_CPNT_DOT1X_EAPOL_PASS_THROUGH == TRUE) */
static UI32_T CLI_RUNCFG_Get_FileHeader(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#if (SYS_CPNT_MGMT_IP_FLT == TRUE)
static UI32_T CLI_RUNCFG_Get_MGMT_IP_FLT_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif
#if (CLI_SUPPORT_L3_FEATURE == 1)
static UI32_T CLI_RUNCFG_Get_L3_Per_Vlan_Parameter(UI32_T vid, UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count);
static UI32_T CLI_RUNCFG_Get_L3_Global_To_Router_Mode_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count);
static UI32_T CLI_RUNCFG_Get_L3_Global_Command_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_ECMP_BALANCE_MODE == TRUE)
static UI32_T CLI_RUNCFG_Get_ECMP_Global_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count);
#endif

#if(SYS_CPNT_CFM==TRUE)
static UI32_T CLI_RUNCFG_Get_Cfm_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,UI32_T buffer_size, UI32_T b_count);
static UI32_T cli_runcfg_get_cfm_parameter_macro(UI32_T unit_id, char *buffer,
                                UI32_T buffer_size, UI32_T b_count, char *str_list, char *print_str);
#endif  /* #if(SYS_CPNT_CFM==TRUE) */
#if (SYS_CPNT_ACL_UI == TRUE)
static UI32_T CLI_RUNCFG_Get_ACL_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#if (SYS_CPNT_QOS_V2_ALL_PORTS == TRUE)
static UI32_T CLI_RUNCFG_Get_Access_Group_Global_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                                           UI32_T buffer_size, UI32_T b_count);
#endif /* SYS_CPNT_QOS_V2_ALL_PORTS */
static UI32_T CLI_RUNCFG_Get_Access_Group_Parameter_By_Ifindex(UI32_T ifindex, char *buffer, char *temp_buffer,
                                                               UI32_T buffer_size, UI32_T b_count);
#if (SYS_CPNT_TIME_BASED_ACL == TRUE)
static UI32_T CLI_RUNCFG_Get_ACL_TIME_RANGE_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                                      UI32_T buffer_size, UI32_T b_count);
#endif /* end of #if (SYS_CPNT_TIME_BASED_ACL == TRUE) */
#endif /* #if (SYS_CPNT_ACL_UI == TRUE) */

#if (SYS_CPNT_DNS == TRUE)
static UI32_T CLI_RUNCFG_Get_DNS_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif
#if (SYS_CPNT_QOS_UI == TRUE)
#if (SYS_CPNT_QOS == SYS_CPNT_QOS_DIFFSERV)
static UI32_T CLI_RUNCFG_Get_Class_Map_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
static UI32_T CLI_RUNCFG_Get_Policy_Map_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif
#endif /* #if (SYS_CPNT_QOS_UI == TRUE) */

#if (SYS_CPNT_COS_INTER_DSCP == TRUE)
static UI32_T CLI_RUNCFG_Get_Global_Qos_Map_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif/* #if (SYS_CPNT_COS_INTER_DSCP == TRUE) */

static UI32_T CLI_RUNCFG_Get_Ethernet_Parameter_For_Module(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count, CLI_RUNCFG_ModuleInfo_T module);

static UI32_T CLI_RUNCFG_Get_GlobalModule_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count, BOOL_T is_module_only, CLI_RUNCFG_ModuleInfo_T module);
static UI32_T CLI_RUNCFG_Get_InterfaceModule_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count, BOOL_T is_module_only, CLI_RUNCFG_ModuleInfo_T module);

#if ( SYS_CPNT_UNIT_HOT_SWAP == TRUE )
#if (SYS_CPNT_MSTP_SUPPORT_PVST==TRUE)
static UI32_T CLI_RUNCFG_Get_VlanDatabaseModule_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                    UI32_T buffer_size, UI32_T b_count, BOOL_T is_module_only, CLI_RUNCFG_ModuleInfo_T module);

/* 2006/06/28
 * ES4649-38-00189: free memory before return
 */
static UI32_T cli_runcfg_get_vlanDatabaseModule_parameter_macro(UI32_T unit_id, char *buffer, char *temp_buffer,
      UI32_T buffer_size, UI32_T b_count, BOOL_T is_module_only, CLI_RUNCFG_ModuleInfo_T module, char *str_list);
#endif
#endif

#if (SYS_CPNT_POE == TRUE)
static UI32_T CLI_RUNCFG_Get_POE_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif

#if defined(UNICORN)
static UI32_T CLI_RUNCFG_Get_UNICORN_Parameter(UI32_T runcfg_my_unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif

static UI32_T CLI_RUNCFG_Get_IPAddress_Parameter(UI32_T runcfg_my_unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);


#if (SYS_CPNT_IPV6 == TRUE)
static UI32_T CLI_RUNCFG_Get_IPV6_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_NSM_POLICY == TRUE)
static UI32_T CLI_RUNCFG_Get_NSM_Policy_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_LLDP == TRUE)
static UI32_T CLI_RUNCFG_Get_Lldp_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_DHCPSNP == TRUE)
static UI32_T CLI_RUNCFG_Get_Dhcpsnp_Global_Parameter ( UI32_T unit_id, char *buffer, char *temp_buffer,
                                                        UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_DHCPV6 == TRUE)
static UI32_T CLI_RUNCFG_Get_Dhcpv6_Parameter ( UI32_T unit_id, char *buffer, char *temp_buffer,
                                                UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_DAI == TRUE)
static UI32_T CLI_RUNCFG_Get_DAI_Parameter ( UI32_T unit_id, char *buffer, char *temp_buffer,
                                           UI32_T buffer_size, UI32_T b_count);
#endif/*#if (SYS_CPNT_DAI == TRUE)*/

#if(SYS_CPNT_MLDSNP==TRUE)
static UI32_T CLI_RUNCFG_Get_MLDSNP_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_CLI_MULTI_PRIVILEGE_LEVEL == TRUE)
static UI32_T CLI_RUNCFG_Get_Privilege_Level_Cmd_Parameter (UI32_T unit_id,
    char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count);
#endif    /* #if (SYS_CPNT_CLI_MULTI_PRIVILEGE_LEVEL == TRUE) */

#if (SYS_CPNT_NETACCESS == TRUE)
static UI32_T CLI_RUNCFG_GET_Net_Access_Parameter (UI32_T unit_id,
    char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count);
#endif    /* #if (SYS_CPNT_NETACCESS == TRUE) */

#if(SYS_CPNT_CWMP == TRUE)
static UI32_T CLI_RUNCFG_Get_Cwmp_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_ADD == TRUE)
static UI32_T CLI_RUNCFG_Get_Voice_Vlan_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_SYSMGMT_DEFERRED_RELOAD == TRUE)
static UI32_T CLI_RUNCFG_Get_Reload_Parameter(
    UI32_T unit_id,
    char *buffer,
    char *temp_buffer,
    UI32_T buffer_size,
    UI32_T b_count
    );
#endif

/* auto traffic control */
#if (SYS_CPNT_ATC_STORM == TRUE)
static UI32_T CLI_RUNCFG_Get_ATC_Global_Parameter ( UI32_T unit_id, char *buffer, char *temp_buffer,
                                                        UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_WEBAUTH == TRUE)
static UI32_T CLI_RUNCFG_Get_Webauth_Parameter (UI32_T unit_id, char *buffer, char *temp_buffer,
                                                            UI32_T buffer_size, UI32_T b_count);
#endif /* #if(SYS_CPNT_WEBAUTH == TRUE) */

#if (SYS_CPNT_MAC_VLAN == TRUE)
static UI32_T CLI_RUNCFG_Get_MAC_VLAN_Parameter (UI32_T unit_id, char *buffer, char *temp_buffer,
                                                            UI32_T buffer_size, UI32_T b_count);
#endif
#if (SYS_CPNT_RSPAN == TRUE)
static void cli_runcfg_rspan_construct_rx_tx_list(
    UI8_T src_rx_ar[], UI8_T src_tx_ar[], UI32_T max_port_number,
    UI8_T src_both_rx_tx_ar[], BOOL_T *empty_rx_list_p, BOOL_T *empty_tx_list_p,
    BOOL_T *empty_rx_tx_list_p);

static char cli_runcfg_rspan_print_conditional(
    UI8_T src_ar[], UI8_T src_both_rx_tx_ar[], int k, char mode);
static void cli_runcfg_rspan_print_source_config_mode(char mode, char cmd_buff_ar[]);
static void cli_runcfg_rspan_print_port_id_list(
    int k, int *last_port_p, BOOL_T *hyphen_printed_p, char cmd_buff_ar[]);
static void cli_runcfg_rspan_print_source_meta_config(
    char session_id, UI8_T src_ar[], UI8_T src_both_rx_tx_ar[], UI32_T unit_id,
    UI32_T max_port_number, char mode, char cmd_buff_ar[]);
static void cli_runcfg_rspan_print_source_config(char session_id, UI8_T src_rx_ar[],
    UI8_T src_tx_ar[], UI8_T src_both_rx_tx_ar[], BOOL_T empty_rx_list,
    BOOL_T empty_tx_list, BOOL_T empty_rx_tx_list, UI32_T unit_id,
    UI32_T max_port_number, char cmd_buff_ar[]);
static void cli_runcfg_rspan_print_remote_vlan_config_mode(char switch_role, char cmd_buff_ar[]);
static void cli_runcfg_rspan_print_uplink(
    UI8_T uplink_ar[], UI32_T unit_id, UI32_T max_port_number, char cmd_buff_ar[]);
static void cli_runcfg_rspan_print_remote_vlan_config(
    char session_id, UI32_T unit_id, UI32_T remote_vid, char switch_role,
    UI8_T uplink_ar[], UI32_T max_port_number, char cmd_buff_ar[]);
static void cli_runcfg_rspan_print_destination_config(
    char session_id, UI32_T unit_id, char destination_port, char is_tagged, char cmd_buff_ar[]);
static UI32_T CLI_RUNCFG_Get_Rspan_Parameter(
    UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_CRAFT_PORT == TRUE)
static UI32_T CLI_RUNCFG_Get_CraftPort_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_PPPOE_IA == TRUE)
static UI32_T CLI_RUNCFG_Get_PPPoE_IA_Parameter(
    UI32_T unit_id, char *buffer, char *temp_buffer,
    UI32_T buffer_size, UI32_T b_count);

static UI32_T CLI_RUNCFG_Get_PPPoE_IA_Ethernet_Parameter(
    UI32_T unit_id, UI32_T port_id, char *buffer, char *temp_buffer,
    UI32_T buffer_size, UI32_T b_count, UI32_T ifindex);
#endif /* #if (SYS_CPNT_PPPOE_IA == TRUE) */

#if (SYS_CPNT_IPV6_RA_GUARD == TRUE)
static UI32_T CLI_RUNCFG_Get_IPV6_RAGUARD_Ethernet_Parameter(
    UI32_T unit_id, UI32_T port_id, char *buffer, char *temp_buffer,
    UI32_T buffer_size, UI32_T b_count, UI32_T ifindex);
#endif /* #if (SYS_CPNT_IPV6_RA_GUARD == TRUE) */

#if (SYS_CPNT_DHCPV6SNP == TRUE)
static UI32_T CLI_RUNCFG_Get_Dhcpv6snp_Parameter ( UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_NDSNP == TRUE)
static UI32_T CLI_RUNCFG_Get_Ndsnp_Parameter ( UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_IPV6_SOURCE_GUARD == TRUE)
static UI32_T CLI_RUNCFG_Get_Ip6sg_Parameter ( UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_PFC == TRUE)
static UI32_T CLI_RUNCFG_Get_PFC_Ethernet_Parameter(
    UI32_T unit_id, UI32_T port_id, char *buffer, char *temp_buffer,
    UI32_T buffer_size, UI32_T b_count, UI32_T ifindex);
#endif /* #if (SYS_CPNT_PPPOE_IA == TRUE) */

#if (SYS_CPNT_CN == TRUE)
static UI32_T CLI_RUNCFG_Get_CN_Parameter(UI32_T unit_id, char *buffer,
    char *temp_buffer, UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_SWCTRL_GLOBAL_STORM_SAMPLE_TYPE == TRUE)
static UI32_T CLI_RUNCFG_Get_GlobalStormSampleType_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_XSTP_TC_PROP_GROUP == TRUE)
static UI32_T CLI_RUNCFG_Get_XSTP_Tc_Prop_Group_Parameter(UI32_T unit_id, char *buffer,
    char *temp_buffer, UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_MLAG == TRUE)
static UI32_T CLI_RUNCFG_Get_MLAG_Parameter(UI32_T unit_id, char *buffer,
                char *temp_buffer, UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_VXLAN == TRUE)
static UI32_T CLI_RUNCFG_Get_VXLAN_Parameter(UI32_T unit_id, char *buffer,
                char *temp_buffer, UI32_T buffer_size, UI32_T b_count);
#endif

#if (SYS_CPNT_HASH_SELECTION == TRUE)
static UI32_T CLI_RUNCFG_Get_HashSelection_Parameter(UI32_T unit_id, char *buffer,
                char *temp_buffer, UI32_T buffer_size, UI32_T b_count);
#endif

Func_T cli_runcfg_table [] = {
    &CLI_RUNCFG_Get_FileHeader,
#if (SYS_CPNT_STACKING == TRUE)
    &CLI_RUNCFG_Get_Stacking_UnitMAC,
#endif
#if (SYS_CPNT_INIT_PHASE_PROVISION == TRUE)
    &CLI_RUNCFG_Get_Init_Phase_Config,
#endif
#if (SYS_CPNT_SYNCE==TRUE)
    &CLI_RUNCFG_Get_SyncE_Parameter,
#endif
    &CLI_RUNCFG_Get_System_Parameter,
#if (SYS_CPNT_POE == TRUE)
    &CLI_RUNCFG_Get_POE_Parameter,
#endif
#if defined(SYS_CPNT_SNMP) && (SYS_CPNT_SNMP == TRUE)
    &CLI_RUNCFG_Get_Snmp_Parameter,
#endif
    &CLI_RUNCFG_Get_Rmon_Config_Parameter,
    &CLI_RUNCFG_Get_Auth_Parameter,
    &CLI_RUNCFG_Get_Syslog_Parameter,
#if (SYS_CPNT_SMTP == TRUE)
    &CLI_RUNCFG_Get_Smtp_Parameter,
#endif
#if defined(UNICORN)
    &CLI_RUNCFG_Get_UNICORN_Parameter,
#endif
    &CLI_RUNCFG_Get_VlanDatabase_Parameter,
    &CLI_RUNCFG_Get_MSTP_Mode_Parameter,
#if(SYS_CPNT_XSTP_TC_PROP_GROUP == TRUE)
    &CLI_RUNCFG_Get_XSTP_Tc_Prop_Group_Parameter,
#endif

#if (SYS_CPNT_HASH_SELECTION == TRUE)
    &CLI_RUNCFG_Get_HashSelection_Parameter,
#endif

    &CLI_RUNCFG_Get_Create_Trunk,
    &CLI_RUNCFG_Get_PVLAN_Parameter,
#if (SYS_CPNT_MAC_VLAN == TRUE)
    &CLI_RUNCFG_Get_MAC_VLAN_Parameter,
#endif
#if (SYS_CPNT_DOT1X == TRUE)
    &CLI_RUNCFG_Get_Dot1x_Parameter,
#endif /* #if (SYS_CPNT_DOT1X == TRUE) */
#if (SYS_CPNT_DOT1X_EAPOL_PASS_THROUGH == TRUE)
    &CLI_RUNCFG_Get_Dot1xEapolPassThrough_Parameter,
#endif /* #if (SYS_CPNT_DOT1X_EAPOL_PASS_THROUGH == TRUE) */
#if (SYS_CPNT_LLDP == TRUE)
    &CLI_RUNCFG_Get_Lldp_Parameter,
#endif
#if(SYS_CPNT_CFM==TRUE)
    &CLI_RUNCFG_Get_Cfm_Parameter,
#endif
#if (SYS_CPNT_ACL_UI == TRUE)
#if (SYS_CPNT_TIME_BASED_ACL == TRUE)
    &CLI_RUNCFG_Get_ACL_TIME_RANGE_Parameter,
#endif /* end of #if (SYS_CPNT_TIME_BASED_ACL == TRUE) */
    &CLI_RUNCFG_Get_ACL_Parameter,
#endif /* #if (SYS_CPNT_ACL_UI == TRUE) */

#if (SYS_CPNT_QOS_UI == TRUE)
#if (SYS_CPNT_QOS == SYS_CPNT_QOS_DIFFSERV)
    &CLI_RUNCFG_Get_Class_Map_Parameter,
    &CLI_RUNCFG_Get_Policy_Map_Parameter,
#endif
#endif /* #if (SYS_CPNT_QOS_UI == TRUE) */

#if (SYS_CPNT_ACL_UI == TRUE && SYS_CPNT_QOS_V2_ALL_PORTS == TRUE)
    &CLI_RUNCFG_Get_Access_Group_Global_Parameter,
#endif
#if (SYS_CPNT_COS_INTER_DSCP == TRUE)
    &CLI_RUNCFG_Get_Global_Qos_Map_Parameter,
#endif/* #if (SYS_CPNT_COS_INTER_DSCP == TRUE) */
#if(SYS_CPNT_PPPOE_IA == TRUE)
    &CLI_RUNCFG_Get_PPPoE_IA_Parameter,
#endif
#if (SYS_CPNT_DAI == TRUE)
    &CLI_RUNCFG_Get_DAI_Parameter,
#endif/*#if (SYS_CPNT_DAI == TRUE)*/
#if (SYS_CPNT_CN == TRUE)
    &CLI_RUNCFG_Get_CN_Parameter,
#endif
#if (SYS_CPNT_SWCTRL_GLOBAL_STORM_SAMPLE_TYPE == TRUE)
    &CLI_RUNCFG_Get_GlobalStormSampleType_Parameter,
#endif
    &CLI_RUNCFG_Get_Ethernet_Parameter,
    &CLI_RUNCFG_Get_Trunk_Parameter,
    &CLI_RUNCFG_Get_Control_Plane_Parameter,
    &CLI_RUNCFG_Get_Loopback_Parameter,
    &CLI_RUNCFG_Get_VLAN_Parameter,
#if (SYS_CPNT_IP_FOR_ETHERNET0 == TRUE)
    &CLI_RUNCFG_Get_Ethernet0_Parameter,/*fuzhimin,20090106*/
#endif
#if (SYS_CPNT_CRAFT_PORT == TRUE)
    &CLI_RUNCFG_Get_CraftPort_Parameter,
#endif
#if (SYS_CPNT_MGMT_IP_FLT == TRUE)
    &CLI_RUNCFG_Get_MGMT_IP_FLT_Parameter,
#endif
/* auto traffic control */
#if (SYS_CPNT_ATC_STORM == TRUE)
    &CLI_RUNCFG_Get_ATC_Global_Parameter,
#endif
#if (SYS_CPNT_DNS == TRUE)
    &CLI_RUNCFG_Get_DNS_Parameter,
#endif
    &CLI_RUNCFG_Get_VDSL_Global_Parameter,
    &CLI_RUNCFG_Get_HTTP_Parameter,
    &CLI_RUNCFG_Get_IPAddress_Parameter,
#if (CLI_SUPPORT_L3_FEATURE == 1)
    &CLI_RUNCFG_Get_L3_Global_Command_Parameter,
#endif
#if (SYS_CPNT_ECMP_BALANCE_MODE == TRUE)
    &CLI_RUNCFG_Get_ECMP_Global_Parameter,
#endif
#if (SYS_CPNT_VXLAN == TRUE)
    &CLI_RUNCFG_Get_VXLAN_Parameter,
#endif
    &CLI_RUNCFG_Get_Spanningtree_Parameter, /*include mac-address-table*/
#if (SYS_CPNT_ADD == TRUE)
    &CLI_RUNCFG_Get_Voice_Vlan_Parameter,
#endif
    &CLI_RUNCFG_Get_Remote_Auth_Parameter,
    &CLI_RUNCFG_Get_COS_Parameter,
    &CLI_RUNCFG_Get_SSH_Parameter,
    &CLI_RUNCFG_Get_TFTP_Parameter,
    &CLI_RUNCFG_Get_PFU_Parameter,
#if (SYS_CPNT_DHCPSNP == TRUE)
    &CLI_RUNCFG_Get_Dhcpsnp_Global_Parameter,
#endif
#if (SYS_CPNT_DHCPV6 == TRUE)
    &CLI_RUNCFG_Get_Dhcpv6_Parameter,
#endif
#if(SYS_CPNT_DHCPV6SNP == TRUE)
    &CLI_RUNCFG_Get_Dhcpv6snp_Parameter,
#endif
#if(SYS_CPNT_NDSNP == TRUE)
    &CLI_RUNCFG_Get_Ndsnp_Parameter,
#endif

#if(SYS_CPNT_IPV6_SOURCE_GUARD == TRUE)
    &CLI_RUNCFG_Get_Ip6sg_Parameter,
#endif
#if(SYS_CPNT_MLDSNP==TRUE)
    &CLI_RUNCFG_Get_MLDSNP_Parameter,
#endif
#if (SYS_CPNT_CLI_MULTI_PRIVILEGE_LEVEL == TRUE)
    &CLI_RUNCFG_Get_Privilege_Level_Cmd_Parameter,
#endif    /* #if (SYS_CPNT_CLI_MULTI_PRIVILEGE_LEVEL == TRUE) */
#if (SYS_CPNT_NETACCESS == TRUE)
    &CLI_RUNCFG_GET_Net_Access_Parameter,
#endif    /*#if (SYS_CPNT_NETACCESS == TRUE)*/
#if(SYS_CPNT_WEBAUTH == TRUE)
    &CLI_RUNCFG_Get_Webauth_Parameter,
#endif /* #if(SYS_CPNT_WEBAUTH == TRUE) */
#if(SYS_CPNT_CWMP == TRUE)
    &CLI_RUNCFG_Get_Cwmp_Parameter,
#endif
#if (SYS_CPNT_IP_TUNNEL == TRUE)
    &CLI_RUNCFG_Get_IpTunnel_Parameter,
#endif /*SYS_CPNT_IP_TUNNEL*/
#if (SYS_CPNT_IPV6 == TRUE)
    &CLI_RUNCFG_Get_IPV6_Parameter,
#endif
#if (SYS_CPNT_NSM_POLICY == TRUE)
    &CLI_RUNCFG_Get_NSM_Policy_Parameter,
#endif

#if (SYS_CPNT_SYSMGMT_DEFERRED_RELOAD == TRUE)
    &CLI_RUNCFG_Get_Reload_Parameter,
#endif
#if (SYS_CPNT_RSPAN == TRUE)
    &CLI_RUNCFG_Get_Rspan_Parameter,
#endif
#if (SYS_CPNT_MLAG == TRUE)
    &CLI_RUNCFG_Get_MLAG_Parameter,
#endif
    &CLI_RUNCFG_Get_Line_Parameter
};

#if(SYS_CPNT_OSPF == TRUE)
/* Interface Type String. */
static char *cli_runcfg_ospf_if_type_str[] =
{
    "unknown",               /* should never be used. */
    "point-to-point",
    "broadcast",
    "non-broadcast",
    "point-to-multipoint",
    "ponit-to-multipoint non-broadcast",
    "virtual-link",          /* should never be used. */
    "loopback"
};
#endif
#define TOTAL_CLI_RUNCFG_COMPONENT_NUM  sizeof(cli_runcfg_table)/sizeof(Func_T)

/*-----------------------------------------------------------
 * ROUTINE NAME - CLI_RUNCFG_Get_RunningCfg
 *-----------------------------------------------------------
 * FUNCTION: This is a running config generator. Use the function
 *           call to collect the configuration of the system, and
 *           store in the style of CLI command.
 * INPUT   : buffer      - The pointer to the starting address to
 *                         store the configuration.
 *         : buffer_size - The size of the buffer to store the
 *                         configuration.
 * OUTPUT  : None.
 * RETURN  : CLI_RUNCFG_RETURN_OK - Collect configuration successfully.
 *           CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY - Buffer size is too
 *                                  to collect all configuration.
 * NOTE    : None.
 *----------------------------------------------------------*/
UI32_T CLI_RUNCFG_Get_RunningCfg(char *buffer, UI32_T buffer_size)
{
    char  temp_buffer[CLI_DEF_MAX_BUFSIZE];
    UI32_T runcfg_my_unit_id   = 0;
    UI32_T buffer_count        = 0;
    UI32_T i = 0;

    STKTPLG_POM_GetMyUnitID(&runcfg_my_unit_id);

    while (i < TOTAL_CLI_RUNCFG_COMPONENT_NUM)
    {
        buffer_count = (* cli_runcfg_table[i]) (runcfg_my_unit_id, buffer, temp_buffer, buffer_size, buffer_count);
        CHECK_BUFF_RETURN_VALUE(buffer_count);
        APPEND_RUNNING_CFG_0("!\n");
        i++;
        /*For this issue ES4649-ZZ-00902 : Continuity PING will timeout if issue running configure
          Becase show running configure occupied much time and it's priority is higher, so we let it sleep.
        */
        if (i%3 == 0)
        {
            SYSFUN_Sleep(1);
        }

#if (SYS_CPNT_SW_WATCHDOG_TIMER == TRUE)
        {
            CLI_TASK_WorkingArea_T *ctrl_P = (CLI_TASK_WorkingArea_T *)CLI_TASK_GetMyWorkingArea();
            if (NULL != ctrl_P)
            {
                CLI_LIB_SwWatchDogRoutine(ctrl_P);
            }
        }
#endif /* SYS_CPNT_SW_WATCHDOG_TIMER */
    }

    return CLI_RUNCFG_RETURN_OK;
}

/*-----------------------------------------------------------
 * ROUTINE NAME - CLI_RUNCFG_Get_Interface_RunningCfg
 *-----------------------------------------------------------
 * FUNCTION: This is a running config generator. Use the function
 *           call to collect the configuration of specific interface,
 *           and store in the style of CLI command.
 * INPUT   : buffer      - The pointer to the starting address to
 *                         store the configuration.
 *         : buffer_size - The size of the buffer to store the
 *                         configuration.
 * OUTPUT  : None.
 * RETURN  : CLI_RUNCFG_RETURN_OK - Collect configuration successfully.
 *           CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY - Buffer size is too
 *                                  to collect all configuration.
 * NOTE    : None.
 *----------------------------------------------------------*/
UI32_T CLI_RUNCFG_Get_Interface_RunningCfg(char *buffer, UI32_T buffer_size, char *arg[])
{
    char temp_buffer[CLI_DEF_MAX_BUFSIZE];
    UI32_T buffer_count = 0;

    if (arg[0] != NULL)
    {
        switch (arg[0][0])
        {
            /* interface ethernet <value> */
            case 'e':
            case 'E':
            {
                UI32_T unit = (UI32_T)atoi((char*)arg[1]);
                UI32_T port = (UI32_T)atoi(strchr((char*)arg[1], '/')+1);
                if (STKTPLG_POM_UnitExist(unit) != TRUE)
                {
                    return CLI_RUNCFG_RETURN_OK;
                }
                if (port > SWCTRL_POM_UIGetUnitPortNumber(unit))
                {
                    return CLI_RUNCFG_RETURN_OK;
                }
                buffer_count =
                    CLI_RUNCFG_Get_Ethernet_Parameter_One_Port(unit, port, buffer, temp_buffer, buffer_size, buffer_count);
                break;
            }

            /* interface port-channel <value> */
            case 'p':
            case 'P':
            {
                UI32_T trunk_id = (UI32_T)atoi((char*)arg[1]);
                buffer_count =
                    CLI_RUNCFG_Get_Trunk_Parameter_Per_Trunk(trunk_id, buffer, temp_buffer, buffer_size, buffer_count);
                break;
            }

            /* interface vlan {id | name} <value> */
            case 'v':
            case 'V':
            {
                UI32_T vid;
                /* by id */
                if (arg[1][0] == 'i' || arg[1][0] == 'I')
                {
                    vid = atoi(arg[2]);
                    if (VLAN_POM_IsVlanExisted(vid))
                    {
                        buffer_count =
                            CLI_RUNCFG_Get_VLAN_Parameter_Per_VLAN(vid, buffer, temp_buffer, buffer_size, buffer_count);
                    }
                }
                /* by name */
                else
                {
                    VLAN_OM_Dot1qVlanCurrentEntry_T vlan_info;
                    UI32_T time_mark = 0, time_mark2 = 0;
                    vid = 0;

                    while (VLAN_POM_GetNextVlanId(time_mark, &vid))
                    {
                        memset(&vlan_info, 0, sizeof(vlan_info));
#if (SYS_CPNT_VLAN_PROVIDING_DUAL_MODE == TRUE)
                        VLAN_POM_GetDot1qVlanCurrentEntryAgent(time_mark2, vid, &vlan_info);
#else
                        VLAN_POM_GetDot1qVlanCurrentEntry(time_mark2, vid, &vlan_info);
#endif
                        if (strcmp(arg[2], vlan_info.dot1q_vlan_static_name) == 0)
                        {
                            buffer_count =
                                CLI_RUNCFG_Get_VLAN_Parameter_Per_VLAN(vid, buffer, temp_buffer, buffer_size, buffer_count);
                            break;  /* break while */
                        }
                    }
                }
                break;
            }

            default:
                APPEND_RUNNING_CFG_0("=== This command is not implemented yet! ===\n");
                break;
        }
        CHECK_BUFF_RETURN_VALUE(buffer_count);
        APPEND_RUNNING_CFG_0("!\n");
    }

    return CLI_RUNCFG_RETURN_OK;
}



static BOOL_T CLI_RUNCFG_Check_STA_Inequality(UI32_T maxage, UI32_T hello ,UI32_T forward)
{
    if (maxage < 600 || maxage < 2*(hello+100) || maxage > 4000 || maxage > 2*(forward-100))
        return FALSE;
    return TRUE;
}

static BOOL_T CLI_RUNCFG_Check_Sequence(CLI_RUNCFG_Sequence_T *A, CLI_RUNCFG_Sequence_T *B, CLI_RUNCFG_Sequence_T *C, UI32_T *point, UI32_T count ,UI8_T type)
{
    BOOL_T is_not_end = FALSE;
    BOOL_T is_push    = FALSE;
    UI32_T i      = 0;
    UI32_T value1 = B[0].value;
    UI32_T value2 = B[1].value;
    UI32_T value3 = B[2].value;
    for (i = 0 ; i <= *point ; i++)
    {
        switch(C[i].type)
        {
            case 1:
                value1 = C[i].value;
                break;

            case 2:
                value2 = C[i].value;
                break;

            case 3:
                value3 = C[i].value;
                break;

            default:
                break;
        }
    }

    for (i = 0 ; i< count ; i++)
    {
        if (A[i].valid)
        {
            is_not_end = TRUE;
            break;
        }
    }

    if (is_not_end)
    {
        for (i = 0; i < count ; i++)
        {
            if (A[i].valid)
            {
                switch(A[i].type)
                {
                    case 1:
                        value1 = A[i].value;
                        break;

                    case 2:

                        value2 = A[i].value;
                        break;

                    case 3:
                        value3 = A[i].value;
                        break;

                    default:
                        return FALSE;
                }

                switch(type)
                {
                    case 1:
                        if (CLI_RUNCFG_Check_STA_Inequality(value1, value2, value3))
                        is_push = TRUE;
                        break;

                    default:
                        return FALSE;
                }

                if (is_push)
                {
                    A[i].valid = FALSE;
                    C[*point] = A[i];
                    (*point)++;
                    if(CLI_RUNCFG_Check_Sequence(A, B, C , point,count,type))
                        return TRUE;
                    (*point)--;
                    A[i].valid = TRUE;
                }
                else
                {
                    switch(A[i].type)
                    {
                        case 1:
                            value1 = B[0].value;
                            break;

                        case 2:
                            value2 = B[1].value;
                            break;

                        case 3:
                            value3 = B[2].value;
                            break;

                        default:
                            return FALSE;
                    }
                }
            }
        }
        return FALSE;
    }
    else
        return TRUE;
}


/*------------------------------------------------------------------------------
 * FUNCTION NAME - CLI_Runcfg_ListStrToOneLine
 *------------------------------------------------------------------------------
 * PURPOSE  : This is caculate string list to one command line length, use for vlan id list.
 * INPUT    : process_length:now process string list position
              dec_number:except vlan list, other command char length,
              *str_list:the all vlan id string
              *print_str:one line vlan id string
 * OUTPUT   : *process_length
              *print_str
 * RETURN   : None
 * NOTES    :
 *------------------------------------------------------------------------------*/
static void CLI_Runcfg_ListStrToOneLine(I32_T *process_length, UI32_T dec_number, char *str_list, char *print_str)
{
    /*because must show per line, so spilt the str_list to show */
    I32_T str_len = strlen(str_list);
    UI8_T j = 0;

    memset(print_str, 0, sizeof(char)*CLI_DEF_MAX_BUFSIZE-dec_number);
    if (str_len - *process_length < CLI_DEF_MAX_BUFSIZE-dec_number-1)
        memcpy(print_str, str_list+*process_length, sizeof(char)*(str_len - *process_length));
    else
        memcpy(print_str, str_list+*process_length, sizeof(char)*(CLI_DEF_MAX_BUFSIZE-dec_number-1));

    for (j = 0;j<=10;j++)/*xxxx-xxxx*/
    {
        if (str_len - *process_length < CLI_DEF_MAX_BUFSIZE-dec_number-1)
        {
            *process_length = str_len;
            break;
        }
        else
        {
            if (*(print_str+CLI_DEF_MAX_BUFSIZE-dec_number-1 - j) == ',')
            {
                *process_length = *process_length + CLI_DEF_MAX_BUFSIZE-dec_number-1 - j + 1;/*add 1, because ',' need to count, and point to next char*/
                *(print_str+CLI_DEF_MAX_BUFSIZE-dec_number-1 - j) = 0;/*set ',' to null*/
                break;
            }
        }
    }
    return;
}

#if (SYS_CPNT_SYNCE==TRUE)
/* synchronous ethernet */
static UI32_T CLI_RUNCFG_Get_SyncE_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                             UI32_T buffer_size, UI32_T b_count)
{
    SWCTRL_Lport_Type_T lport_type;
    UI32_T buffer_count = b_count;
    UI32_T unit, port, trunk, clock_src_lst_len, i, ifindex;
    SYNCEDRV_TYPE_ClockSource_T clock_src_lst[SYS_HWCFG_SYNCE_MAX_NBR_OF_CLOCK_SRC];
    UI8_T ifindex_pbmp[SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST]={0};
    BOOL_T clk_src_ssm_status, clk_src_select_is_auto, is_revertive;

    /* Get running synce enabled ports
     */
    if(SYNC_E_PMGR_GetRunningEnabledSyncEPbmp(ifindex_pbmp)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        #if (SYS_DFLT_SYNCE_STATUS == TRUE)
        for(i = SYS_ADPT_SYNC_E_MIN_SUPPORT_IFINDEX;
            i <=SYS_ADPT_SYNC_E_MAX_SUPPORT_IFINDEX;
            i++)
        {
            if((STKTPLG_BOARD_IsSyncEPort((UI8_T)i)==TRUE) &&
                (L_PBMP_GET_PORT_IN_PBMP_ARRAY(ifindex_pbmp, i)==0)
            {

                lport_type = SWCTRL_POM_LogicalPortToUserPort(i, &unit, &port, &trunk);

                if(lport_type == SWCTRL_LPORT_UNKNOWN_PORT
                    || lport_type == SWCTRL_LPORT_TRUNK_PORT)
                    continue;

                APPEND_RUNNING_CFG_2("no synce ethernet %lu/%lu\n", unit, port);
            }
        }

        #else /* #if (SYS_DFLT_SYNCE_STATUS == TRUE) */
        L_PBMP_FOR_EACH_PORT_IN_PBMP_ARRAY(ifindex_pbmp, SYS_ADPT_TOTAL_NBR_OF_LPORT, i)
        {
            lport_type = SWCTRL_POM_LogicalPortToUserPort(i, &unit, &port, &trunk);

            if(lport_type == SWCTRL_LPORT_UNKNOWN_PORT
                || lport_type == SWCTRL_LPORT_TRUNK_PORT)
                continue;

            APPEND_RUNNING_CFG_2("synce ethernet %lu/%lu\n", unit, port);
        }
        #endif /* #if (SYS_DFLT_SYNCE_STATUS == TRUE) */
    }

    /* Get running synce clock source port list
     */
    if(SYNC_E_PMGR_GetRunningClockSourcePortList(clock_src_lst, &clock_src_lst_len)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        for(i=0; i<clock_src_lst_len; i++)
        {
            APPEND_RUNNING_CFG_2("synce ethernet 1/%lu clock-source priority %lu\n", clock_src_lst[i].port, clock_src_lst[i].priority);
        }
    }

    /* Get running clock-source selection mode
     */
    if(SYNC_E_PMGR_GetRunningClockSourceSelectMode(&clk_src_select_is_auto, &is_revertive, &ifindex)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if(clk_src_select_is_auto==TRUE)
        {
            APPEND_RUNNING_CFG_0("synce auto-clock-source-selecting");
            if(is_revertive==TRUE)
            {
                APPEND_RUNNING_CFG_0(" revertive-switching");
            }

            APPEND_RUNNING_CFG_0("\n");
        }
        else
        {
            if(ifindex==0)
            {
                APPEND_RUNNING_CFG_0("synce force-clock-source-selecting\n");
            }
            else
            {
                lport_type = SWCTRL_POM_LogicalPortToUserPort(ifindex, &unit, &port, &trunk);

                if(lport_type != SWCTRL_LPORT_UNKNOWN_PORT
                    && lport_type != SWCTRL_LPORT_TRUNK_PORT)
                {
                    APPEND_RUNNING_CFG_2("synce force-clock-source-selecting ethernet %lu/%lu\n", unit, port);
                }
            }
        }
    }


    /* clock source selection mode - ssm mode
     */
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SYNC_E_PMGR_GetRunningClkSrcSsm(&clk_src_ssm_status))
    {
        if(clk_src_ssm_status)
        {
            APPEND_RUNNING_CFG("synce clk-src-ssm\n");
        }
        else
        {
            APPEND_RUNNING_CFG("no synce clk-src-ssm\n");
        }
    }

    /* ssm status
     */
    {
        UI16_T i;
        UI8_T  pri;
        BOOL_T port_ssm_status;

        for(i = SYS_ADPT_SYNC_E_MIN_SUPPORT_IFINDEX;
            i <=SYS_ADPT_SYNC_E_MAX_SUPPORT_IFINDEX;
            i++)
        {
            lport_type = SWCTRL_POM_LogicalPortToUserPort(i, &unit, &port, &trunk);

            if(lport_type == SWCTRL_LPORT_UNKNOWN_PORT
                || lport_type == SWCTRL_LPORT_TRUNK_PORT)
                continue;

            if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SYNC_E_PMGR_GetRunningPortSsmStatus(i, &port_ssm_status, &pri))
            {
                if(port_ssm_status)
                {
                    if(pri)
                    {
                        APPEND_RUNNING_CFG_3("synce ssm ethernet %lu/%lu priority %d\n", unit, port, pri);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_2("synce ssm ethernet %lu/%lu\n", unit, port);
                    }
                }
                else
                {
                    APPEND_RUNNING_CFG_2("no synce ssm ethernet %lu/%lu\n", unit, port);
                }
            }
        }
    }
    return buffer_count;
}
#endif /* end of #if (SYS_CPNT_SYNCE==TRUE) */

/* system management */
static UI32_T CLI_RUNCFG_Get_System_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    char   Contact[MAXSIZE_sysContact + 1];
    char   Name[MAXSIZE_sysName + 1];
    char   Location[MAXSIZE_sysLocation + 1];
    char   prompt[SYS_ADPT_MAX_PROMPT_STRING_LEN] = {0};
    /*
#if (SYS_CPNT_SNMP_VERSION == 3)
    SNMP_MGR_TrapDestEntry_T trap_receiver;
#else
    TRAP_MGR_TrapDestEntry_T trap_receiver;
#endif*/

#if ((SYS_HWCFG_SUPPORT_PD==TRUE) && (SYS_CPNT_SWDRV_ONLY_ALLOW_PD_PORT_LINKUP_WITH_PSE_PORT==TRUE))
    {
        BOOL_T pse_check_status;

        if(SWCTRL_PMGR_GetPSECheckStatus(&pse_check_status)==TRUE)
        {
            if(pse_check_status!=SYS_DFLT_PSE_CHECK_STATUS)
            {
                if(pse_check_status==TRUE)
                {
                    APPEND_RUNNING_CFG_0("power-source-check\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0("no power-source-check\n");
                }
            }
        }
    }
#endif /* end of #if ((SYS_HWCFG_SUPPORT_PD==TRUE) && (SYS_CPNT_SWDRV_ONLY_ALLOW_PD_PORT_LINKUP_WITH_PSE_PORT==TRUE)) */

#if (SYS_CPNT_DHCP_RELAY_OPTION82 == TRUE)
   {
       UI32_T optionstatus;
       UI32_T policystatus;
       UI32_T rid_mode;
       UI32_T relay_server[SYS_ADPT_MAX_NBR_OF_DHCP_RELAY_SERVER]={0};
       UI32_T i=0;
       BOOL_T subtype_format = FALSE;

       if(DHCP_PMGR_GetRunningDhcpRelayOption82Status(&optionstatus) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
       {
            if(optionstatus == DHCP_OPTION82_ENABLE)
            {
               APPEND_RUNNING_CFG_0("ip dhcp relay information option\n");
            }
            else if(optionstatus == DHCP_OPTION82_DISABLE)
            {
               APPEND_RUNNING_CFG_0("no ip dhcp relay information option\n");
            }
       }

       if(DHCP_PMGR_GetRunningDhcpRelayOption82Format(&subtype_format) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
       {
            if(subtype_format)
            {
               APPEND_RUNNING_CFG_0("no ip dhcp relay information option encode no-subtype\n");
            }
            else
            {
               APPEND_RUNNING_CFG_0("ip dhcp relay information option encode no-subtype\n");
            }
       }

       if(DHCP_PMGR_GetRunningDhcpRelayOption82RidMode(&rid_mode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
       {
            if(rid_mode == DHCP_OPTION82_RID_IP_HEX)
            {
                APPEND_RUNNING_CFG_0("ip dhcp relay information option remote-id ip-address encode hex\n");
            }
            else if (rid_mode == DHCP_OPTION82_RID_IP_ASCII)
            {
                APPEND_RUNNING_CFG_0("ip dhcp relay information option remote-id ip-address encode ascii\n");
            }
            else if(rid_mode == DHCP_OPTION82_RID_MAC_HEX)
            {
                APPEND_RUNNING_CFG_0("ip dhcp relay information option remote-id mac-address encode hex\n");
            }
            else if(rid_mode == DHCP_OPTION82_RID_MAC_ASCII)
            {
                APPEND_RUNNING_CFG_0("ip dhcp relay information option remote-id mac-address encode ascii\n");
            }
            else if(rid_mode == DHCP_OPTION82_RID_CONFIGURED_STRING)
            {
                UI8_T    rid_value[SYS_ADPT_MAX_LENGTH_OF_RID + 1]={0};
                if(DHCP_OM_OK == DHCP_POM_GetDhcpRelayOption82RidValue(rid_value))
                {
                    APPEND_RUNNING_CFG_1("ip dhcp relay information option remote-id string %s\n",rid_value);
                }
            }
       }

       if(DHCP_PMGR_GetRunningDhcpRelayOption82Policy(&policystatus) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
       {
            if(policystatus == DHCP_OPTION82_POLICY_DROP)
            {
               APPEND_RUNNING_CFG_0("ip dhcp relay information policy drop\n");
            }
            else if(policystatus == DHCP_OPTION82_POLICY_REPLACE)
            {
               APPEND_RUNNING_CFG_0("ip dhcp relay information policy replace\n");
            }
            else if(policystatus == DHCP_OPTION82_POLICY_KEEP)
            {
               APPEND_RUNNING_CFG_0("ip dhcp relay information policy keep\n");
            }
       }

       if(DHCP_PMGR_GetRunningRelayServerAddress(relay_server)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
       {
           APPEND_RUNNING_CFG_0("ip dhcp relay server");
           for(i=0;i<SYS_ADPT_MAX_NBR_OF_DHCP_RELAY_SERVER;i++)
           {
               if(relay_server[i]!=0)
               {
                   APPEND_RUNNING_CFG_4(" %u.%u.%u.%u",
                    ((UI8_T *)(&relay_server[i]))[0],((UI8_T *)(&relay_server[i]))[1],
                    ((UI8_T *)(&relay_server[i]))[2],((UI8_T *)(&relay_server[i]))[3]);
               }
           }
            APPEND_RUNNING_CFG_0("\n");
       }



    }

#endif

#if (SYS_CPNT_SNTP == TRUE)
    /*sntp server */
    {
        UI8_T  server_count = 0;
        char   ip_str1[L_INET_MAX_IPADDR_STR_LEN+1] = {0};
        char   ip_str2[L_INET_MAX_IPADDR_STR_LEN+1] = {0};
        char   ip_str3[L_INET_MAX_IPADDR_STR_LEN+1] = {0};
        L_INET_AddrIp_T ip_address;
        UI32_T i = 0;
        /*get ip*/

        for (i = 1; i<=MAX_sntpServerIndex; i ++)
        {
            memset(&ip_address, 0, sizeof(L_INET_AddrIp_T));

            if ((SNTP_PMGR_GetServerIp(i,&ip_address)) &&
                (ip_address.addrlen != 0))
            {
                server_count++;
                switch(server_count)
                {
                    case 1:
                        L_INET_InaddrToString((L_INET_Addr_T*)&ip_address, ip_str1, sizeof(ip_str1));
                        break;

                    case 2:
                        L_INET_InaddrToString((L_INET_Addr_T*)&ip_address, ip_str2, sizeof(ip_str2));
                        break;

                    case 3:
                        L_INET_InaddrToString((L_INET_Addr_T*)&ip_address, ip_str3, sizeof(ip_str3));
                        break;

                    default:
                        break;
                }
            }
        }

        /*trans late*/
        switch(server_count)
        {
            case 1:
                APPEND_RUNNING_CFG_1("sntp server %s\n", ip_str1);
                break;

            case 2:
                APPEND_RUNNING_CFG_2("sntp server %s %s\n", ip_str1, ip_str2);
                break;

            case 3:
                APPEND_RUNNING_CFG_3("sntp server %s %s %s\n", ip_str1, ip_str2, ip_str3);
                break;

            default:
                break;
        }
        APPEND_RUNNING_CFG_0("!\n");
    }

    {
        UI32_T status=0,polltime=0,servicemode=0;

        if(SNTP_PMGR_GetRunningStatus(&status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(status==VAL_sntpStatus_enabled)
            {
                APPEND_RUNNING_CFG_0("sntp client\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no sntp client\n");
            }
        }

        if(SNTP_PMGR_GetRunningServiceMode(&servicemode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(servicemode==VAL_sntpServiceMode_unicast)
            {
                APPEND_RUNNING_CFG_0("no sntp broadcast client\n");
            }
            else if(servicemode==VAL_sntpServiceMode_broadcast)
            {
                APPEND_RUNNING_CFG_0("sntp broadcast client\n");
            }
        }

        if(SNTP_PMGR_GetRunningPollTime(&polltime) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("sntp poll %lu\n",(unsigned long)polltime);
        }
    }
#endif /* #if (SYS_CPNT_SNTP == TRUE) */

    /* systime */
    {
        SYS_TIME_Timezone_T timezone;

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SYS_TIME_GetRunningTimeZone(&timezone))
        {
            if (SYS_TIME_TIMEZONE_TYPE_TIMEZONE == timezone.type)
            {
                char  buf[CLI_DEF_MAX_BUFSIZE+1];
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                CLI_LIB_Str_Add_Quote(timezone.timezone.custom.name, buf);

                APPEND_RUNNING_CFG_4("clock timezone %s hours %s%lu minute %lu\n", buf,
                                     (SYS_TIME_TIMEZONE_MINUS == timezone.timezone.custom.sign) ? "-" : "",
                                     (unsigned long)timezone.timezone.custom.hour,
                                     (unsigned long)timezone.timezone.custom.minute);
#else
                APPEND_RUNNING_CFG_4("clock timezone %s hours %s%lu minute %lu\n",
                                     timezone.timezone.custom.name,
                                     (SYS_TIME_TIMEZONE_MINUS == timezone.timezone.custom.sign) ? "-" : "",
                                     (unsigned long)timezone.timezone.custom.hour,
                                     (unsigned long)timezone.timezone.custom.minute);
#endif /* #if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE) */
            }
            else
            {
                APPEND_RUNNING_CFG_1("clock timezone-predefined %s\n", timezone.timezone.predefined.name);
            }
        }
    }

#if (SYS_CPNT_NTP == TRUE)
    {
        NTP_MGR_AUTHKEY_T *sk;
        UI32_T  ntpStatus = 0;
        UI32_T  ntpauthStatus = 0;
        UI32_T  ip = 0;
        UI32_T  version = 0;
        UI32_T  keyid = 0;
        UI8_T   ip_str[16] = {0};

        APPEND_RUNNING_CFG_0("!\n");

        if (NTP_PMGR_GetRunningStatus(&ntpStatus) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (ntpStatus == VAL_ntpStatus_enabled)
            {
                APPEND_RUNNING_CFG_0("ntp client\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no ntp client\n");
            }
        }

        if (NTP_PMGR_GetRunningAuthStatus(&ntpauthStatus) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (ntpauthStatus == VAL_ntpAuthenticateStatus_enabled)
            {
                APPEND_RUNNING_CFG_0("ntp authenticate\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no ntp authenticate\n");
            }
        }

        /* show server */
        while (NTP_PMGR_GetNextServer(&ip, &version, &keyid) == TRUE)
        {
            L_INET_Ntoa(ip, ip_str);

            if (keyid != 0)
            {
                APPEND_RUNNING_CFG_2("ntp server %s key %lu\n", ip_str, (unsigned long)keyid);
            }
            else
            {
                APPEND_RUNNING_CFG_1("ntp server %s\n",ip_str);
            }
        }

        /* show hash key */
        sk = (NTP_MGR_AUTHKEY_T *)malloc(sizeof(NTP_MGR_AUTHKEY_T));

        if (sk != NULL)
        {
            memset(sk,0,sizeof(NTP_MGR_AUTHKEY_T));

            while (NTP_PMGR_GetNextKey(sk) == TRUE)
            {
                APPEND_RUNNING_CFG_2("ntp authentication-key %lu md5 %s\n", (unsigned long)sk->keyid, sk->password);
            }

            free(sk);
        }

        APPEND_RUNNING_CFG_0("!\n");
   }
#endif /* #if (SYS_CPNT_NTP == TRUE) */

#if (SYS_CPNT_MOTD == TRUE)
{
   char   running_sys_bnr_msg[CLI_DEF_MAX_BUFSIZE + 1] = {0};
   char   running_banner_msg_delimiting_character;
   UI32_T section_id = 0;
   UI32_T total_length = 0;

   while(SYS_BNR_PMGR_GetNextSysBnrMsgByID(SYS_BNR_MGR_MOTD_TYPE, (UI8_T *)running_sys_bnr_msg, &section_id, CLI_DEF_MAX_BUFSIZE) == TRUE)
   {
      if(section_id == 1) /*first enter*/
      {
         SYS_BNR_PMGR_GetSysBnrMsgDelimitingChar(SYS_BNR_MGR_MOTD_TYPE, (UI8_T *)&running_banner_msg_delimiting_character);
         APPEND_RUNNING_CFG_1("banner motd %c\n", running_banner_msg_delimiting_character);
      }
      total_length = total_length + strlen(running_sys_bnr_msg);
      APPEND_RUNNING_CFG_1("%s", running_sys_bnr_msg);
   }

   if(section_id > 0) /*if banner msg existed, then need end character*/
   {
      if(total_length == SYS_ADPT_MAX_MOTD_LENGTH)
      {
        APPEND_RUNNING_CFG_1("%c\n", running_banner_msg_delimiting_character);
      }
      else
      {
        APPEND_RUNNING_CFG_1("%c\n", running_banner_msg_delimiting_character);
      }
   }
}
#endif /*#if (SYS_CPNT_MOTD == TRUE)*/

    if(SYS_PMGR_GetRunningPromptString((UI8_T *)prompt) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
        char      buf[CLI_DEF_MAX_BUFSIZE+1];
        CLI_LIB_Str_Add_Quote(prompt,buf);
        APPEND_RUNNING_CFG_1("prompt %s\n", buf/*prompt*/);
#else
        APPEND_RUNNING_CFG_1("prompt %s\n", prompt);
#endif
    }
    if(MIB2_PMGR_GetRunningSysName((UI8_T *)Name) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
        char      buf[CLI_DEF_MAX_BUFSIZE+1];
        CLI_LIB_Str_Add_Quote(Name,buf);
        APPEND_RUNNING_CFG_1("hostname %s\n", buf/*Name*/);
#else
        APPEND_RUNNING_CFG_1("hostname %s\n", Name);
#endif
    }
    if(MIB2_PMGR_GetRunningSysLocation((UI8_T *)Location) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
        char      buf[CLI_DEF_MAX_BUFSIZE+1];
        CLI_LIB_Str_Add_Quote(Location,buf);
        APPEND_RUNNING_CFG_1("snmp-server location %s\n", buf/*Location*/);
#else
        APPEND_RUNNING_CFG_1("snmp-server location %s\n", Location);
#endif
    }

    if(MIB2_PMGR_GetRunningSysContact((UI8_T *)Contact) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
        char      buf[CLI_DEF_MAX_BUFSIZE+1];
        CLI_LIB_Str_Add_Quote(Contact,buf);
        APPEND_RUNNING_CFG_1("snmp-server contact %s\n", buf/*Contact*/);
#else
        APPEND_RUNNING_CFG_1("snmp-server contact %s\n", Contact);
#endif
    }
    APPEND_RUNNING_CFG_0("!\n");
    /*default-vlan-id*/
    {
        UI32_T vid;
        if(VLAN_POM_GetRunningGlobalDefaultVlan(&vid) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("default-vlan-id %ld\n", (long)vid);
            APPEND_RUNNING_CFG_0("!\n");
        }
    }

#if (SYS_CPNT_JUMBO_FRAMES == TRUE)
    {
        UI32_T jumbo_frame_status = 0;

        if (SWCTRL_POM_GetRunningJumboFrameStatus (&jumbo_frame_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (jumbo_frame_status == SWCTRL_JUMBO_FRAME_ENABLE)
            {
                APPEND_RUNNING_CFG_0("jumbo frame\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no jumbo frame\n");
            }
        }
        APPEND_RUNNING_CFG_0("!\n");
    }

#endif
#if (SYS_CPNT_SWCTRL_MTU_CONFIG_MODE == SYS_CPNT_SWCTRL_MTU_PER_SYSTEM )
    UI32_T jumbo,mtu;
    if(SWCTRL_PMGR_GetSystemMTU(&jumbo, &mtu))
    {
                APPEND_RUNNING_CFG_1("system mtu jumbo %lu\n",(unsigned long)jumbo);
    }
#endif
       APPEND_RUNNING_CFG_0("!\n");

#if(SYS_CPNT_CLUSTER==TRUE)
    /*CLUSTER*/
    {
        UI32_T status;
        CLUSTER_TYPE_MemberEntry_T member;
        UI8_T id=0;
        char  buff[CLI_DEF_MAX_BUFSIZE] = {0};
        UI8_T ipAddress[4]={0};

        if(CLUSTER_POM_GetRunningClusterStatus(&status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(status==VAL_clusterEnable_enabled)
            {
                APPEND_RUNNING_CFG_0("cluster\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no cluster\n");
            }
        }

        if(CLUSTER_POM_GetRunningClusterIpPool(ipAddress)== SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_4("cluster ip-pool %d.%d.%d.%d\n",ipAddress[0],
                          ipAddress[1],ipAddress[2],ipAddress[3]);
        }

        if(CLUSTER_POM_GetRunningClusterCommander(&status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(status==VAL_clusterCommanderEnable_enabled)
            {
                APPEND_RUNNING_CFG_0("cluster commander\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no cluster commander\n");
            }
        }

        while(CLUSTER_POM_GetNextMember(&id,&member))
        {
            sprintf(buff, "mac %02x-%02x-%02x-%02x-%02x-%02x id %d",
                member.mac[0],member.mac[1], member.mac[2],member.mac[3],
                member.mac[4],member.mac[5],member.id);

            APPEND_RUNNING_CFG_1("cluster member %s\n",buff);
        }

        APPEND_RUNNING_CFG_0("!\n");
    }
#endif

#if (SYS_CPNT_SYS_TIME_SUMMERTIME == TRUE)
    /* summer time */
    {
        SYS_TIME_DST_MODE_T daylight_mode = SYS_TIME_DEFAULT_DAYLIGHT_SAVING_TIME;
        char zone_name[SYS_TIME_MAX_DST_TIMEZONE_NAME_LEN + 1] = {0};

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SYS_TIME_DST_GetRunningMode(&daylight_mode)
#if (SYS_CPNT_SYS_TIME_SUMMERTIME_ZONENAME == TRUE)
            || SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SYS_TIME_DST_GetRunningZoneName(zone_name)
#endif
           )
        {
#if (SYS_CPNT_SYS_TIME_SUMMERTIME_ZONENAME == TRUE)
            /* ZoneName might be set or not, but should be show in summer-time running.
             */
            SYS_TIME_DST_GetZoneName(zone_name);
#endif
            SYS_TIME_DST_GetMode(&daylight_mode);

            switch (daylight_mode)
            {
                case DAYLIGHT_SAVING_TIME_ENABLE_AMERICA:
                    APPEND_RUNNING_CFG_1("clock summer-time %s predefined usa\n", zone_name);
                    break;

                case DAYLIGHT_SAVING_TIME_ENABLE_EUROPE_PARTS_OF_ASIA:
                    APPEND_RUNNING_CFG_1("clock summer-time %s predefined europe\n", zone_name);
                    break;

                case DAYLIGHT_SAVING_TIME_ENABLE_AUSTRALIA:
                    APPEND_RUNNING_CFG_1("clock summer-time %s predefined australia\n", zone_name);
                    break;

                case DAYLIGHT_SAVING_TIME_ENABLE_NEW_ZEALAND:
                    APPEND_RUNNING_CFG_1("clock summer-time %s predefined new-zealand\n", zone_name);
                    break;

                case DAYLIGHT_SAVING_TIME_ENABLE_USER_CONFIGURED:
                    {
                        SYS_TIME_DST begin_dst;
                        SYS_TIME_DST end_dst;
                        memset(&begin_dst, 0, sizeof(SYS_TIME_DST));
                        memset(&end_dst, 0, sizeof(SYS_TIME_DST));

                        if (TRUE == SYS_TIME_DST_GetUserConfigTime(DAYLIGHT_SAVING_TIME_ENABLE_USER_CONFIGURED, &begin_dst, &end_dst))
                        {
                            UI32_T offset = 0;
                            char month_str[10] = {0};

                            CLI_LIB_ConvertToMonthString(begin_dst.month, month_str, sizeof(month_str));

                            APPEND_RUNNING_CFG_5("clock summer-time %s date %lu %s %lu %lu", zone_name, (unsigned long)begin_dst.day, month_str, (unsigned long)begin_dst.year, (unsigned long)begin_dst.hour);

                            memset(month_str, 0, sizeof(month_str));
                            CLI_LIB_ConvertToMonthString(end_dst.month, month_str, sizeof(month_str));

                            APPEND_RUNNING_CFG_4(" %lu %lu %s %lu", (unsigned long)begin_dst.minute, (unsigned long)end_dst.day, month_str, (unsigned long)end_dst.year);
                            if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SYS_TIME_DST_GetRunningTimeOffset(&offset))
                            {
                                APPEND_RUNNING_CFG_3(" %lu %lu %lu\n", (unsigned long)end_dst.hour, (unsigned long)end_dst.minute, (unsigned long)offset);
                            }
                            else
                            {
                                APPEND_RUNNING_CFG_2(" %lu %lu\n", (unsigned long)end_dst.hour, (unsigned long)end_dst.minute);
                            }
                        }
                    }
                    break;

                case DAYLIGHT_SAVING_TIME_ENABLE_USER_CONFIGURED_RECURRING:
                    {
                        SYS_TIME_RECURRING_DST begin_dst;
                        SYS_TIME_RECURRING_DST end_dst;
                        memset(&begin_dst, 0, sizeof(SYS_TIME_RECURRING_DST));
                        memset(&end_dst, 0, sizeof(SYS_TIME_RECURRING_DST));

                        if (TRUE == SYS_TIME_DST_GetRecurringTime(DAYLIGHT_SAVING_TIME_ENABLE_USER_CONFIGURED_RECURRING, &begin_dst, &end_dst))
                        {
                            UI32_T  offset = 0;
                            char date_str[10] = {0};
                            char month_str[10] = {0};

                            CLI_LIB_ConvertToDateString(begin_dst.wday, date_str, sizeof(date_str));
                            CLI_LIB_ConvertToMonthString(begin_dst.month, month_str, sizeof(month_str));

                            APPEND_RUNNING_CFG_5("clock summer-time %s recurring %lu %s %s %lu", zone_name, (unsigned long)begin_dst.week, date_str, month_str, (unsigned long)begin_dst.hour);

                            memset(date_str, 0, sizeof(date_str));
                            memset(month_str, 0, sizeof(month_str));
                            CLI_LIB_ConvertToDateString(end_dst.wday, date_str, sizeof(date_str));
                            CLI_LIB_ConvertToMonthString(end_dst.month, month_str, sizeof(month_str));

                            APPEND_RUNNING_CFG_4(" %lu %lu %s %s", (unsigned long)begin_dst.minute, (unsigned long)end_dst.week, date_str, month_str);

                            if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SYS_TIME_DST_GetRunningTimeOffset(&offset))
                            {
                                APPEND_RUNNING_CFG_3(" %lu %lu %lu\n", (unsigned long)end_dst.hour, (unsigned long)end_dst.minute, (unsigned long)offset);
                            }
                            else
                            {
                                APPEND_RUNNING_CFG_2(" %lu %lu\n", (unsigned long)end_dst.hour, (unsigned long)end_dst.minute);
                            }
                        }
                    }
                    break;

                default:
                    break;
            } /* end of switch (daylight_mode) */
        } /* end of if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SYS_TIME_GetRunningDaylightSavingTimeMode(&daylight_mode) ... */
    } /* end of summer time */
#endif /* #if (SYS_CPNT_SYS_TIME_SUMMERTIME == TRUE) */

/*banner*/
#if (SYS_CPNT_CLI_BANNER == TRUE)
    {
        char string_ar[BANNER_MAX_NOTE_DATA_LENGTH+1] = {0};
        BannerDCPowerInfo_T dc_power_info_p;
        BannerEquipmentInfo_T equipment_info_p;
        BannerManagerInfo_T manager_info_p;
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
        char buf[CLI_DEF_MAX_BUFSIZE+1]={0};
#endif

        memset(&dc_power_info_p, 0, sizeof(BannerDCPowerInfo_T));
        memset(&equipment_info_p, 0, sizeof(BannerEquipmentInfo_T));
        memset(&manager_info_p, 0, sizeof(BannerManagerInfo_T));

        if(CLI_BANNER_GetRunningCompany(string_ar)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
            CLI_LIB_Str_Add_Quote(string_ar, buf);
            APPEND_RUNNING_CFG_1("banner configure company %s\n",buf);
#else
            APPEND_RUNNING_CFG_1("banner configure company %s\n",string_ar);
#endif
        }

        if(CLI_BANNER_GetRunningDepartment(string_ar)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
            CLI_LIB_Str_Add_Quote(string_ar,buf);
            APPEND_RUNNING_CFG_1("banner configure department %s\n",buf);
#else
            APPEND_RUNNING_CFG_1("banner configure department %s\n",string_ar);
#endif
        }

        {
            UI32_T index=1;
            UI32_T ret_val=FALSE;

            while(index<4)
            {
                if(CLI_BANNER_GetRunningManagerInfoIsTrue(index)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    ret_val = TRUE;
                }
                index++;
            }
            index=1;

            if(ret_val == TRUE)
            {
                APPEND_RUNNING_CFG_0("banner configure manager-info");

                while(index<4)
                {
                    if(CLI_BANNER_GetRunningManagerInfo(index, &manager_info_p)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                    {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                        CLI_LIB_Str_Add_Quote(manager_info_p.name_ar,buf);
                        APPEND_RUNNING_CFG_2(" name%lu %s",(unsigned long)index,buf);
                        CLI_LIB_Str_Add_Quote(manager_info_p.phone_number_ar,buf);
                        APPEND_RUNNING_CFG_1(" phone-number %s",buf);
#else
                        APPEND_RUNNING_CFG_3(" name%lu %s phone-number %s",
                            (unsigned long)index,manager_info_p.name_ar,manager_info_p.phone_number_ar);
#endif
                    }
                    index++;
                }  /* end of while(index<4) */
                APPEND_RUNNING_CFG_0("\n");
            }  /* end of if(ret_val == TRUE) */
        }

        if(CLI_BANNER_GetRunningEquipmentLocation(string_ar)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
            CLI_LIB_Str_Add_Quote(string_ar,buf);
            APPEND_RUNNING_CFG_1("banner configure equipment-location %s\n",buf);
#else
            APPEND_RUNNING_CFG_1("banner configure equipment-location %s\n",string_ar);
#endif
        }

        if(CLI_BANNER_GetRunningEquipmentInfo(&equipment_info_p)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
            CLI_LIB_Str_Add_Quote(equipment_info_p.manufacturer_id_ar,buf);
            APPEND_RUNNING_CFG_1("banner configure equipment-info manufacturer-id %s",buf);
            CLI_LIB_Str_Add_Quote(equipment_info_p.floor_ar,buf);
            APPEND_RUNNING_CFG_1(" floor %s",buf);
            CLI_LIB_Str_Add_Quote(equipment_info_p.row_ar,buf);
            APPEND_RUNNING_CFG_1(" row %s",buf);
            CLI_LIB_Str_Add_Quote(equipment_info_p.rack_ar,buf);
            APPEND_RUNNING_CFG_1(" rack %s",buf);
            CLI_LIB_Str_Add_Quote(equipment_info_p.self_rack_ar,buf);
            APPEND_RUNNING_CFG_1(" shelf-rack %s",buf);
            CLI_LIB_Str_Add_Quote(equipment_info_p.manufacturer_ar,buf);
            APPEND_RUNNING_CFG_1(" manufacturer %s\n",buf);
#else
            APPEND_RUNNING_CFG_3("banner configure equipment-info manufacturer-id %s floor %s row %s",
                    equipment_info_p.manufacturer_id_ar,equipment_info_p.floor_ar,equipment_info_p.row_ar);
            APPEND_RUNNING_CFG_3(" rack %s shelf-rack %s manufacturer %s\n",
                    equipment_info_p.rack_ar,equipment_info_p.self_rack_ar,equipment_info_p.manufacturer_ar);
#endif
        }

        if(CLI_BANNER_GetRunningDCPowerInfo(&dc_power_info_p)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
            CLI_LIB_Str_Add_Quote(dc_power_info_p.floor_ar,buf);
            APPEND_RUNNING_CFG_1("banner configure dc-power-info floor %s",buf);
            CLI_LIB_Str_Add_Quote(dc_power_info_p.row_ar,buf);
            APPEND_RUNNING_CFG_1(" row %s",buf);
            CLI_LIB_Str_Add_Quote(dc_power_info_p.rack_ar,buf);
            APPEND_RUNNING_CFG_1(" rack %s",buf);
            CLI_LIB_Str_Add_Quote(dc_power_info_p.electrical_circuit_ar,buf);
            APPEND_RUNNING_CFG_1(" electrical-circuit %s\n",buf);
#else
            APPEND_RUNNING_CFG_4("banner configure dc-power-info floor %s row %s rack %s electrical_circuit %s\n",
                    dc_power_info_p.floor_ar,dc_power_info_p.row_ar,
                    dc_power_info_p.rack_ar,dc_power_info_p.electrical_circuit_ar);
#endif
        }

        if(CLI_BANNER_GetRunningLPNumber(string_ar)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
            CLI_LIB_Str_Add_Quote(string_ar,buf);
            APPEND_RUNNING_CFG_1("banner configure lp-number %s\n",buf);
#else
            APPEND_RUNNING_CFG_1("banner configure lp-number %s\n",string_ar);
#endif
        }

        if(CLI_BANNER_GetRunningMUX(string_ar)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
            CLI_LIB_Str_Add_Quote(string_ar,buf);
            APPEND_RUNNING_CFG_1("banner configure mux %s\n",buf);
#else
            APPEND_RUNNING_CFG_1("banner configure mux %s\n",string_ar);
#endif
        }

        if(CLI_BANNER_GetRunningIpLan(string_ar)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
            CLI_LIB_Str_Add_Quote(string_ar,buf);
            APPEND_RUNNING_CFG_1("banner configure ip-lan %s\n",buf);
#else
            APPEND_RUNNING_CFG_1("banner configure ip-lan %s\n",string_ar);
#endif
        }

        if(CLI_BANNER_GetRunningNote(string_ar)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
            CLI_LIB_Str_Add_Quote(string_ar,buf);
            APPEND_RUNNING_CFG_1("banner configure note %s\n",buf);
#else
            APPEND_RUNNING_CFG_1("banner configure note %s\n",string_ar);
#endif
        }

    }
#endif  /* #if (SYS_CPNT_CLI_BANNER == TRUE) */

#if (SYS_CPNT_SYSMGMT_MONITORING_PROCESS_CPU == TRUE)
    /* process cpu */
    {
        UI32_T rising_threshold, falling_threshold;

        if (SYS_PMGR_GetRunningCpuUtilRisingThreshold(&rising_threshold) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("process cpu rising %lu\n", (unsigned long)rising_threshold);
        }
        if (SYS_PMGR_GetRunningCpuUtilFallingThreshold(&falling_threshold) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("process cpu falling %lu\n", (unsigned long)falling_threshold);
        }
    }
#endif

#if (SYS_CPNT_SYSMGMT_CPU_GUARD == TRUE)
    /* process cpu guard */
    {
        UI32_T value;
        BOOL_T status;

        if (SYS_PMGR_GetRunningCpuGuardStatus(&status) ==
                SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (status == TRUE)
            {
                APPEND_RUNNING_CFG("process cpu guard\n");
            }
            else
            {
                APPEND_RUNNING_CFG("no process cpu guard\n");
            }
        }
        if (SYS_PMGR_GetRunningCpuGuardHighWatermark(&value) ==
                SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(
                    "process cpu guard high-watermark %lu\n", (unsigned long)value);
        }
        if (SYS_PMGR_GetRunningCpuGuardLowWatermark(&value) ==
                SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(
                    "process cpu guard low-watermark %lu\n", (unsigned long)value);
        }
        if (SYS_PMGR_GetRunningCpuGuardMaxThreshold(&value) ==
                SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(
                    "process cpu guard max-threshold %lu\n", (unsigned long)value);
        }
        if (SYS_PMGR_GetRunningCpuGuardMinThreshold(&value) ==
                SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(
                    "process cpu guard min-threshold %lu\n", (unsigned long)value);
        }
        if (SYS_PMGR_GetRunningCpuGuardTrapStatus(&status) ==
                SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (status == TRUE)
            {
                APPEND_RUNNING_CFG("process cpu guard trap\n");
            }
            else
            {
                APPEND_RUNNING_CFG("no process cpu guard trap\n");
            }
        }
    }
#endif

#if (SYS_CPNT_SYSMGMT_MONITORING_MEMORY_UTILIZATION == TRUE)
    /* memory */
    {
        UI32_T rising_threshold, falling_threshold;

        if (SYS_PMGR_GetRunningMemoryUtilRisingThreshold(&rising_threshold) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("memory rising %lu\n", (unsigned long)rising_threshold);
        }
        if (SYS_PMGR_GetRunningMemoryUtilFallingThreshold(&falling_threshold) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("memory falling %lu\n", (unsigned long)falling_threshold);
        }
    }
#endif

#if (SYS_CPNT_NETACCESS_AGING_MODE == SYS_CPNT_NETACCESS_AGING_MODE_CONFIGURABLE)
    /* network-access aging */
    {
        UI32_T aging_mode;

        if (NETACCESS_PMGR_GetRunningMacAddressAgingMode(&aging_mode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (aging_mode == VAL_networkAccessAging_enabled)
            {
                APPEND_RUNNING_CFG_0("network-access aging\n");
            }
            else if (aging_mode == VAL_networkAccessAging_disabled)
            {
                APPEND_RUNNING_CFG_0("no network-access aging\n");
            }
        }
    }
#endif

#if (SYS_CPNT_XFER_AUTO_UPGRADE == TRUE)
    {
        UI32_T status, reload_status;
        char path[MAXSIZE_fileAutoUpgradeOpCodePath+1] = {0};

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == XFER_PMGR_GetRunningAutoOpCodeUpgradeStatus(&status))
        {
            if (VAL_fileAutoUpgradeOpCodeStatus_enabled == status)
            {
                APPEND_RUNNING_CFG_0("upgrade opcode auto\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no upgrade opcode auto\n");
            }
        }

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == XFER_PMGR_GetRunningAutoOpCodeUpgradeReloadStatus(&reload_status))
        {
            if (VAL_fileAutoUpgradeOpCodeReloadStatus_enabled == reload_status)
            {
                APPEND_RUNNING_CFG_0("upgrade opcode reload\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no upgrade opcode reload\n");
            }
        }

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == XFER_PMGR_GetRunningAutoOpCodeUpgradePath(path))
        {
            APPEND_RUNNING_CFG_1("upgrade opcode path %s\n", path);
        }

        APPEND_RUNNING_CFG_0("!\n");
    }
#endif /* #if (SYS_CPNT_XFER_AUTO_UPGRADE == TRUE) */

#if (SYS_CPNT_SYSMGMT_FAN_SPEED_FORCE_FULL == TRUE)
    {
        BOOL_T mode = FALSE;

        if (SYS_PMGR_GetRunningFanSpeedForceFull(&mode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (mode == TRUE)
            {
                APPEND_RUNNING_CFG_0("fan-speed force-full\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no fan-speed force-full\n");
            }
        }
        APPEND_RUNNING_CFG_0("!\n");
    }
#endif

#if (SYS_CPNT_DOS == TRUE)
    /* dos protection */
    {
        enum {
            STATUS,
            RATE_LIMIT,
        };

        static struct {
            UI32_T method;
            char *cmd;
        }
        field_info[] =
        {
            [DOS_TYPE_FLD_SYSTEM_ECHO_CHARGEN_STATUS]       = { STATUS,     "echo-chargen" },
            [DOS_TYPE_FLD_SYSTEM_ECHO_CHARGEN_RATELIMIT]    = { RATE_LIMIT, "echo-chargen" },
            [DOS_TYPE_FLD_SYSTEM_LAND_STATUS]               = { STATUS,     "land" },
            [DOS_TYPE_FLD_SYSTEM_SMURF_STATUS]              = { STATUS,     "smurf" },
            [DOS_TYPE_FLD_SYSTEM_TCP_FLOODING_STATUS]       = { STATUS,     "tcp-flooding" },
            [DOS_TYPE_FLD_SYSTEM_TCP_FLOODING_RATELIMIT]    = { RATE_LIMIT, "tcp-flooding" },
            [DOS_TYPE_FLD_SYSTEM_TCP_NULL_SCAN_STATUS]      = { STATUS,     "tcp-null-scan" },
            [DOS_TYPE_FLD_SYSTEM_TCP_SCAN_STATUS]           = { STATUS,     "tcp-scan" },
            [DOS_TYPE_FLD_SYSTEM_TCP_SYN_FIN_SCAN_STATUS]   = { STATUS,     "tcp-syn-fin-scan" },
            [DOS_TYPE_FLD_SYSTEM_TCP_UDP_PORT_ZERO_STATUS]  = { STATUS,     "tcp-udp-port-zero" },
            [DOS_TYPE_FLD_SYSTEM_TCP_XMAS_SCAN_STATUS]      = { STATUS,     "tcp-xmas-scan" },
            [DOS_TYPE_FLD_SYSTEM_UDP_FLOODING_STATUS]       = { STATUS,     "udp-flooding" },
            [DOS_TYPE_FLD_SYSTEM_UDP_FLOODING_RATELIMIT]    = { RATE_LIMIT, "udp-flooding" },
            [DOS_TYPE_FLD_SYSTEM_WIN_NUKE_STATUS]           = { STATUS,     "win-nuke" },
            [DOS_TYPE_FLD_SYSTEM_WIN_NUKE_RATELIMIT]        = { RATE_LIMIT, "win-nuke" },
        };

        DOS_TYPE_FieldId_T field_id;
        DOS_TYPE_FieldDataBuf_T data;

        for (field_id = 0; field_id < DOS_TYPE_FLD_NUM; field_id++)
        {
            if (DOS_PMGR_GetRunningDataByField(field_id, &data) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                switch (field_info[field_id].method)
                {
                    case STATUS:
                        if (data.u32 == DOS_TYPE_STATUS_ENABLED)
                        {
                            APPEND_RUNNING_CFG_1("dos-protection %s\n", field_info[field_id].cmd);
                        }
                        else
                        {
                            APPEND_RUNNING_CFG_1("no dos-protection %s\n", field_info[field_id].cmd);
                        }
                        break;

                    case RATE_LIMIT:
                        APPEND_RUNNING_CFG_2("dos-protection %s bit-rate-in-kilo %lu\n", field_info[field_id].cmd, (unsigned long)data.u32);
                        break;

                    default:
                        continue;
                }
            }
        } /* end of for (field_id) */
    }
#endif

#if ((SYS_CPNT_ALARM_INPUT_DETECT == TRUE) && (SYS_CPNT_CLI_SHOW_ALARM_INPUT == TRUE))
    {
        UI32_T unit, index;
        SYS_MGR_SwAlarmEntry_T alarm;

        for (unit=0; STKTPLG_OM_GetNextUnit(&unit); )
        {
            for(index=1; index <= SYS_ADPT_MAX_NBR_OF_ALARM_INPUT_PER_UNIT; index++)
            {
                memset(&alarm, 0, sizeof(SYS_MGR_SwAlarmEntry_T));
                alarm.sw_alarm_unit_index = unit;
                alarm.sw_alarm_input_index = index;
                if (SYS_PMGR_GetRunningAlarmInputName(&alarm) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    APPEND_RUNNING_CFG_3("alarm input name %lu %lu %s\n", (unsigned long)unit, (unsigned long)index, alarm.sw_alarm_input_name);
                }
            }
        }

        APPEND_RUNNING_CFG_0("!\n");
    }
#endif

#if (SYS_CPNT_VRRP_PING == TRUE)
    {
        UI32_T ping_status=0;

        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == VRRP_PMGR_GetRunningPingStatus(&ping_status))
        {
            if(ping_status == VRRP_TYPE_PING_STATUS_ENABLE)
            {
                APPEND_RUNNING_CFG_0("vrrp ping-enable\n");
            }

            if(ping_status == VRRP_TYPE_PING_STATUS_DISABLE)
            {
                APPEND_RUNNING_CFG_0("no vrrp ping-enable\n");
            }

            APPEND_RUNNING_CFG_0("!\n");
        }
    }
#endif /*SYS_CPNT_VRRP_PING*/
#if RUNCFG_DEVELOP
    CLI_LIB_PrintStr("system management complete\r\n");
#endif
    return buffer_count;
}

#if defined(SYS_CPNT_SNMP) && (SYS_CPNT_SNMP == TRUE)
static UI32_T CLI_RUNCFG_Get_Snmp_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
   UI32_T buffer_count = b_count;
   /*snmp-server community*/
   {
#if (SYS_CPNT_SNMP_VERSION == 3)
      SNMP_MGR_SnmpCommunity_T comm;
      memset(&comm , 0, sizeof(SNMP_MGR_SnmpCommunity_T));

      while (SNMP_PMGR_GetNextRunningSnmpCommunity(&comm) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if ( comm.access_right != SNMP_MGR_ACCESS_RIGHT_GROUP_SPECIFIC)
         {
            APPEND_RUNNING_CFG_2("snmp-server community %s %s\n", comm.comm_string_name,(comm.access_right == SNMP_MGR_ACCESS_RIGHT_READ_WRITE/*USERAUTH_ACCESS_RIGHT_READ_WRITE*/)?("rw"):("ro"));
         }
      }
      APPEND_RUNNING_CFG_0("!\n");
#else
      USERAUTH_SnmpCommunity_T comm;
      memset(&comm , 0, sizeof(USERAUTH_SnmpCommunity_T));

      while (USERAUTH_GetNextRunningSnmpCommunity(&comm) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
         char      buf[CLI_DEF_MAX_BUFSIZE+1];
         //memset(buf,0,sizeof(buf));
         //buf[CLI_DEF_MAX_BUFSIZE+1] = '\0';
         CLI_LIB_Str_Add_Quote(comm.comm_string_name,buf);
         APPEND_RUNNING_CFG_2("snmp-server community %s %s\n", buf/*comm.comm_string_name*/,(comm.access_right == USERAUTH_ACCESS_RIGHT_READ_WRITE)?("rw"):("ro"));
#else
         APPEND_RUNNING_CFG_2("snmp-server community %s %s\n", comm.comm_string_name,(comm.access_right == USERAUTH_ACCESS_RIGHT_READ_WRITE)?("rw"):("ro"));
#endif
      }
      APPEND_RUNNING_CFG_0("!\n");
#endif
   }

   /*snmp-server enable traps authentication*/
   {
      UI8_T snmp_enable_authen_traps;
      UI32_T link_up_down_trap;
#if defined(FTTH_TRAP)
      UI32_T trap_status,port_num;
      int i;
      BOOL_T is_inherit        =TRUE;
#endif

      if(SNMP_PMGR_GetSnmpEnableAuthenTraps(&snmp_enable_authen_traps))
      {
         if (snmp_enable_authen_traps == VAL_snmpEnableAuthenTraps_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps authentication\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps authentication\n");
         }
      }

#if (SYS_CPNT_IF_LINK_TRAP_PORT_BASE == FALSE)
      {
         UI32_T l_port=0;

         if( SWCTRL_LPORT_UNKNOWN_PORT != SWCTRL_POM_GetNextLogicalPort(&l_port))
         {
             if(IF_PMGR_GetRunningIfLinkUpDownTrapEnable(l_port, &link_up_down_trap)== SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
             {
                if (link_up_down_trap == VAL_ifLinkUpDownTrapEnable_enabled)
                {
                   APPEND_RUNNING_CFG_0("snmp-server enable traps link-up-down\n");
                }
                else
                {
                   APPEND_RUNNING_CFG_0("no snmp-server enable traps link-up-down\n");
                }
             }
          }
      }
#endif /* #if (SYS_CPNT_IF_LINK_TRAP_PORT_BASE == FALSE) */

#if (SYS_CPNT_AMTR_MAC_NOTIFY == TRUE)
    {
        UI32_T  interval;
        BOOL_T  is_enabled;

        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS  == AMTR_PMGR_GetRunningMacNotifyGlobalStatus(&is_enabled))
        {
            if(TRUE == is_enabled)
            {
                APPEND_RUNNING_CFG_0("snmp-server enable traps mac-notification\n");
            }
            else
            {
               APPEND_RUNNING_CFG_0("no snmp-server enable traps mac-notification\n");
            }
        }

        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS  == AMTR_PMGR_GetRunningMacNotifyInterval(&interval))
        {
            APPEND_RUNNING_CFG_1("snmp-server enable traps mac-notification interval %lu\n", (unsigned long)interval);
        }
    }
#endif /* #if(SYS_CPNT_AMTR_MAC_NOTIFY == TRUE) */
#if defined(FTTH_TRAP)
      if (TRAP_PMGR_GetRunningEnableAllTraps(&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_trapEnableAll_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps\n");
         }
      }
      if (TRAP_PMGR_GetRunningEnableBladeTraps(&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_trapBladeEnableStatus_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps blade\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps blade\n");
         }
      }
      if (TRAP_PMGR_GetRunningEnableAllAlarmTraps(&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_trapEnableAllAlarm_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps all-alarm\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps all-alarm\n");
         }
      }
      if (TRAP_PMGR_GetRunningEnableAlarmSensitivityTraps(&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         /*if (trap_status == VAL_trapEnableAlarmSensitivity_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps alarm-sensitivity\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps alarm-sensitivity\n");
         }*/
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_COLD_START,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableColdStart_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps coldstart\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps coldstart\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_FAN_EVENT,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableFanEvent_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps fan-event\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps fan-event\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_FAN_FAILURE,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableFanFailure_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps fan-failure\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps fan-failure\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_FAN_RECOVER,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableFanRecover_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps fan-recover\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps fan-recover\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_HARDWARE_FAULT_EVENT,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableHardwareFaultEvent_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps hardware-fault-event\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps hardware-fault-event\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_HARDWARE_FAULT_RECOVER,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableHardwareFaultRecover_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps hardware-fault-recover\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps hardware-fault-recover\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_HARDWARE_FAULT,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableHardwareFault_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps hardware-fault\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps hardware-fault\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_INTERFACE_CARD_COLD_START,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableInterfaceCardColdStart_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps interface-card-cold-start\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps interface-card-cold-start\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_LINK_CHANGE_EVENT,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableLinkChangeEvent_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps link-change-event\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps link-change-event\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_PORT_LINK_DOWN,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableLinkDown_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps link-down\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps link-down\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_PORT_LINK_UP,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableLinkUp_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps link-up\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps link-up\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_LOOPBACK_BUSY,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableLoopBackBusy_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps loopback-busy\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps loopback-busy\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_DIAGNOSIS_RESULT,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableDiagonsisResult_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps loopback-diagnosis-result\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps loopback-diagnosis-result\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_DIAGNOSIS_START,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableDiagnosisStart_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps loopback-diagnosis-start\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps loopback-diagnosis-start\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_LOOPBACK_LBERROR_TIMEOUT,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableLoopBackLBErrorTimeout_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps loopback-lb-error-timeout\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps loopback-lb-error-timeout\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_LOOPBACK_NORMAL_END,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableLoopBackNormalEnd_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps loopback-normal-end\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps loopback-normal-end\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_LOOPBACK_NOT_TEST,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableLoopBackNotTest_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps loopback-not-test\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps loopback-not-test\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_LOOPBACK_STOP,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableLoopBackStop_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps loopback-stop\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps loopback-stop\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_LOOPBACK_TEST_START,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableLoopBackTestStart_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps loopback-test-start\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps loopback-test-start\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_LOOPBACK_OAM_RELEASE_TIMEOUT,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableLoopBackOAMReleaseTimeout_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps loopback-oam-release-timeout\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps loopback-oam-release-timeout\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_LOOPBACK_OAM_SETTING_TIMEOUT,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableLoopBackOAMSettingTimeout_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps loopback-oam-setting-timeout\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps loopback-oam-setting-timeout\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_LOOPBACK_UMC_TIMEOUT,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableLoopBackUMCTimeout_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps loopback-umc-timeout\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps loopback-umc-timeout\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_UMC_LINKDOWN,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableUmcLinkDown_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps umc-link-down\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps umc-link-down\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_UMC_LINKUP,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableUmcLinkUp_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps umc-link-up\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps umc-link-up\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_UMC_LIP_EVENT,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableUmcLipEvent_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps umc-lip-event\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps umc-lip-event\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_UMC_LIP_RECOVER,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableUmcLipRecover_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps umc-lip-recover\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps umc-lip-recover\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_UMC_LIP,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableUmcLip_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps umc-lip\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps umc-lip\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_UMC_MC_FAULT_EVENT,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableUmcMCFaultEvent_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps umc-mc-fault-event\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps umc-mc-fault-event\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_UMC_MC_FAULT_RECOVER,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableUmcMCFaultRecover_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps umc-mc-fault-recover\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps umc-mc-fault-recover\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_UMC_MC_FAULT,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableUmcMCFault_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps umc-mc-fault\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps umc-mc-fault\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_UMC_POWER_DOWN,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableUmcPowerDown_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps umc-power-down\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps umc-power-down\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_UMC_POWER_UP,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableUmcPowerUp_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps umc-power-up\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps umc-power-up\n");
         }
      }
      if (TRAP_PMGR_GetRunningIndividualTraps(TRAP_EVENT_UMC_UTP_LINK_EVENT,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (trap_status == VAL_ftthTrapEnableUmcUtpLinkEvent_enabled)
         {
            APPEND_RUNNING_CFG_0("snmp-server enable traps umc-utp-link-event\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no snmp-server enable traps umc-utp-link-event\n");
         }
      }
      for (i = 1; i <= SYS_ADPT_TOTAL_NBR_OF_LPORT; i++)
      {
         if( SWCTRL_LPORT_UNKNOWN_PORT == SWCTRL_POM_UIUserPortToIfindex(1, i , &port_num, &is_inherit))
            continue;
         if (TRAP_PMGR_GetRunningEnablePortTraps(port_num,&trap_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            if (trap_status == VAL_trapEnablePortStatus_enabled)
            {
               APPEND_RUNNING_CFG_1("snmp-server enable traps interface ethernet 1/%d\n",i);
            }
            else
            {
               APPEND_RUNNING_CFG_1("no snmp-server enable traps interface ethernet 1/%d\n",i);
            }
         }
      }
#endif
   }

#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("snmp community auth complete\r\n");
#endif

#if (SYS_CPNT_SNMP_VERSION == 3)
    /*snmp-server engine-id*/
    {
        /*snmp-server engine-id local*/
        {
            UI8_T engineID[MAXSIZE_snmpEngineID] = {0};
            UI32_T engineIDLen;  /* Jenny */
            char   str[MAXSIZE_snmpEngineID*2+1] = {0};
            char   temp[CLI_DEF_MAX_BUFSIZE] = {0};

            memset(str, 0, sizeof(str));
            memset(temp, 0, sizeof(temp));

            if (SNMP_PMGR_GetRunningEngineID(engineID, &engineIDLen) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                UI32_T i;

                for (i = 0; i < engineIDLen; i++)
                {
                    char temp[10] = {0};

                    SYSFUN_Sprintf(temp, "%02x",engineID[i]);
                    strcat(str, temp);
                }

                APPEND_RUNNING_CFG_1("snmp-server engine-id local %s\n", str);
            }
        }

        /*snmp-server engine-id remote*/
        {
            char   str2[MAXSIZE_snmpEngineID*2+1] = {0};
            UI32_T i;
            char   temp2[CLI_DEF_MAX_BUFSIZE] = {0};

            SNMP_MGR_SnmpRemoteEngineID_T entry;
            memset(&entry,0,sizeof(SNMP_MGR_SnmpRemoteEngineID_T));

            while(SNMP_PMGR_GetNextRunningSnmpRemoteEngineIDEntry(&entry)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                memset(str2, 0, sizeof(str2));
                memset(temp2, 0, sizeof(temp2));
                for(i=0;i<entry.snmp_remote_engineIDLen;i++)
                {
                    SYSFUN_Sprintf(temp2,"%02x",entry.snmp_remote_engineID[i]);
                    strcat(str2,temp2);
                }
                APPEND_RUNNING_CFG_5("snmp-server engine-id remote %d.%d.%d.%d %s\n", ((UI8_T *)(&(entry.snmp_remote_engineID_host)))[0],((UI8_T *)(&(entry.snmp_remote_engineID_host)))[1],
                                                                                      ((UI8_T *)(&(entry.snmp_remote_engineID_host)))[2],((UI8_T *)(&(entry.snmp_remote_engineID_host)))[3],str2);
            }
        }

    }

    /*snmp-server group*/
    {
        SNMP_MGR_SnmpV3GroupEntry_T entry;
        char  temp[CLI_DEF_MAX_BUFSIZE]       = {0};

        memset(&entry,0,sizeof(entry));

        while(SNMP_PMGR_GetNextRunningSnmpV3Group(&entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(strcmp(entry.snmpv3_group_readview,"\0") != 0)
            {
                if(strcmp(entry.snmpv3_group_writeview,"\0") != 0)
                {
                    if(strcmp(entry.snmpv3_group_notifyview,"\0") !=0)
                    {
                        SYSFUN_Sprintf(temp,"read %s write %s notify %s",entry.snmpv3_group_readview,
                                                                  entry.snmpv3_group_writeview,entry.snmpv3_group_notifyview);
                    }
                    else
                    {
                        SYSFUN_Sprintf(temp,"read %s write %s",entry.snmpv3_group_readview,
                                                                    entry.snmpv3_group_writeview);
                    }
                }
                else if(strcmp(entry.snmpv3_group_notifyview,"\0") !=0)
                {
                    SYSFUN_Sprintf(temp,"read %s notify %s",entry.snmpv3_group_readview,
                                                                     entry.snmpv3_group_notifyview);
                }
                else
                {
                    SYSFUN_Sprintf(temp,"read %s",entry.snmpv3_group_readview);
                }
            }
            else if(strcmp(entry.snmpv3_group_writeview,"\0") != 0)
            {
                if(strcmp(entry.snmpv3_group_notifyview,"\0") !=0)
                {
                    SYSFUN_Sprintf(temp,"write %s notify %s",entry.snmpv3_group_writeview
                                                     ,entry.snmpv3_group_notifyview);
                }
                else
                {
                    SYSFUN_Sprintf(temp,"write %s",entry.snmpv3_group_writeview);
                }
            }
            else if(strcmp(entry.snmpv3_group_notifyview,"\0") != 0)
            {
                SYSFUN_Sprintf(temp,"notify %s",entry.snmpv3_group_notifyview);
            }
            else
            {
                *temp='\0';
            }

            if(entry.snmpv3_group_model == SNMP_MGR_SNMPV3_MODEL_V1)
            {
                APPEND_RUNNING_CFG_2("snmp-server group %s v1 %s\n", entry.snmpv3_group_name,
                                                               temp);
            }
            else if(entry.snmpv3_group_model == SNMP_MGR_SNMPV3_MODEL_V2C)
            {
                APPEND_RUNNING_CFG_2("snmp-server group %s v2c %s\n", entry.snmpv3_group_name,
                                                               temp);
            }
            else if(entry.snmpv3_group_model == SNMP_MGR_SNMPV3_MODEL_V3)
            {
                if(entry.snmpv3_group_security_level == VAL_vacmAccessSecurityLevel_noAuthNoPriv)
                {
                    APPEND_RUNNING_CFG_2("snmp-server group %s v3 noauth %s\n", entry.snmpv3_group_name,
                                                               temp);
                }
                else if(entry.snmpv3_group_security_level == VAL_vacmAccessSecurityLevel_authNoPriv)
                {
                    APPEND_RUNNING_CFG_2("snmp-server group %s v3 auth %s\n", entry.snmpv3_group_name,
                                                               temp);
                }
                else if(entry.snmpv3_group_security_level == VAL_vacmAccessSecurityLevel_authPriv)
                {
                    APPEND_RUNNING_CFG_2("snmp-server group %s v3 priv %s\n", entry.snmpv3_group_name,
                                                               temp);
                }
            }
        }
    }

    /* snmp-server user
     */
    {
        SNMP_MGR_SnmpV3UserEntry_T  entry;
        char   temp[CLI_DEF_MAX_BUFSIZE]       = {0};
        char   auth_key[SNMP_MGR_SNMPV3_SHA_KEY_LEN*2+1];/* SNMP_MGR_SNMPV3_SHA_KEY_LEN *2 > MAX_SNMPV3_PASSWORD_LEN, so use SNMP_MGR_SNMPV3_SHA_KEY_LEN *2 */
        char   priv_key[SNMP_MGR_SNMPV3_MAX_PRIV_KEY_LEN*2+1];
        char   auth_type[10] = {0};
        char   priv_type[10] = {0};
        UI32_T max_len = 0;
        UI32_T max_priv_len = 0;

        memset(&entry,0,sizeof(SNMP_MGR_SnmpV3UserEntry_T));

        /* snmp-server user local
         */
        {
            while(SNMP_PMGR_GetNextRunningSnmpV3User(&entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                auth_key[0]=0;
                priv_key[0]=0;

                if(entry.snmpv3_user_security_model == SNMP_MGR_SNMPV3_MODEL_V1)
                {
                    APPEND_RUNNING_CFG_2("snmp-server user %s %s v1\n", entry.snmpv3_user_name,
                                                                entry.snmpv3_user_group_name);
                }
                else if(entry.snmpv3_user_security_model == SNMP_MGR_SNMPV3_MODEL_V2C)
                {
                    APPEND_RUNNING_CFG_2("snmp-server user %s %s v2c\n", entry.snmpv3_user_name,
                                                                 entry.snmpv3_user_group_name);
                }
                else if(entry.snmpv3_user_security_model == SNMP_MGR_SNMPV3_MODEL_V3)
                {
                    if(entry.snmpv3_user_security_level == VAL_vacmAccessSecurityLevel_noAuthNoPriv)
                    {
                        *temp='\0';
                    }
                    else if(entry.snmpv3_user_security_level == VAL_vacmAccessSecurityLevel_authNoPriv)
                    {
                        if(entry.snmpv3_user_auth_type == SNMP_MGR_SNMPV3_AUTHTYPE_MD5)
                        {
                            SYSFUN_Sprintf(auth_type,"md5");
                            max_len = SNMP_MGR_SNMPV3_MD5_KEY_LEN;
                        }
                        else if(entry.snmpv3_user_auth_type == SNMP_MGR_SNMPV3_AUTHTYPE_SHA)
                        {
                            SYSFUN_Sprintf(auth_type,"sha");
                            max_len = SNMP_MGR_SNMPV3_SHA_KEY_LEN;
                        }

                        COLLECT_ENCRTPT_TEXT_TO_PRINT_LENGTH(auth_key, entry.snmpv3_user_auth_key, max_len);
                        SYSFUN_Sprintf(temp,"encrypted auth %s %s",auth_type,auth_key);

                    }
                    else if(entry.snmpv3_user_security_level == VAL_vacmAccessSecurityLevel_authPriv)
                    {
                        if(entry.snmpv3_user_auth_type == SNMP_MGR_SNMPV3_AUTHTYPE_MD5)
                        {
                            SYSFUN_Sprintf(auth_type,"md5");
                            max_len = SNMP_MGR_SNMPV3_MD5_KEY_LEN;
                        }
                        else if(entry.snmpv3_user_auth_type == SNMP_MGR_SNMPV3_AUTHTYPE_SHA)
                        {
                            SYSFUN_Sprintf(auth_type,"sha");
                            max_len = SNMP_MGR_SNMPV3_SHA_KEY_LEN;
                        }

                        switch(entry.snmpv3_user_priv_type)
                        {
                            case SNMP_MGR_SNMPV3_PRIVTYPE_DES:
                                max_priv_len = max_len;
                            SYSFUN_Sprintf(priv_type,"des56");
                                break;

                            case SNMP_MGR_SNMPV3_PRIVTYPE_3DES:
                                max_priv_len = SNMP_MGR_SNMPV3_MAX_PRIV_KEY_LEN;
                                SYSFUN_Sprintf(priv_type,"3des");
                                break;

                            case SNMP_MGR_SNMPV3_PRIVTYPE_AES128:
                                max_priv_len = max_len;
                                SYSFUN_Sprintf(priv_type,"aes128");
                                break;

                            case SNMP_MGR_SNMPV3_PRIVTYPE_AES192:
                                max_priv_len = SNMP_MGR_SNMPV3_AES192_KEY_LEN;
                                SYSFUN_Sprintf(priv_type,"aes192");
                                break;

                            case SNMP_MGR_SNMPV3_PRIVTYPE_AES256:
                                max_priv_len = SNMP_MGR_SNMPV3_AES256_KEY_LEN;
                                SYSFUN_Sprintf(priv_type,"aes256");
                                break;

                            case SNMP_MGR_SNMPV3_PRIVTYPE_NONE:
                            default:
                                break;

                        }

                        COLLECT_ENCRTPT_TEXT_TO_PRINT_LENGTH(auth_key, entry.snmpv3_user_auth_key, max_len);
                        COLLECT_ENCRTPT_TEXT_TO_PRINT_LENGTH(priv_key, entry.snmpv3_user_priv_key, max_priv_len);

                        SYSFUN_Sprintf(temp,"encrypted auth %s %s priv %s %s",auth_type,auth_key,priv_type,priv_key);
                    }

                    APPEND_RUNNING_CFG_3("snmp-server user %s %s v3 %s\n", entry.snmpv3_user_name,entry.snmpv3_user_group_name,temp);
                }
            }
        } // end snmp-server user local

        /*snmp-server user remote*/
        {
            char  ip_address[16];
            SNMP_MGR_SnmpRemoteEngineID_T engineid_entry;

            memset(&entry,0,sizeof(SNMP_MGR_SnmpV3UserEntry_T));

            while(SNMP_PMGR_GetNextRunningSnmpRemoteUserEntry(&entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                memset(&engineid_entry,0,sizeof(SNMP_MGR_SnmpRemoteEngineID_T));

                while(SNMP_PMGR_GetNextRunningSnmpRemoteEngineIDEntry(&engineid_entry)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    if (( entry.snmpv3_user_engineIDLen != engineid_entry.snmp_remote_engineIDLen) ||
                       ( memcmp(entry.snmpv3_user_engine_id, engineid_entry.snmp_remote_engineID, entry.snmpv3_user_engineIDLen)!=0))
                    {
                        continue;
                    }

                    auth_key[0]=0;
                    priv_key[0]=0;

                    if(entry.snmpv3_user_security_model == SNMP_MGR_SNMPV3_MODEL_V1)
                    {
                        SYSFUN_Sprintf(ip_address,"%d.%d.%d.%d",((UI8_T *)(&(engineid_entry.snmp_remote_engineID_host)))[0],((UI8_T *)(&(engineid_entry.snmp_remote_engineID_host)))[1],
                                                         ((UI8_T *)(&(engineid_entry.snmp_remote_engineID_host)))[2],((UI8_T *)(&(engineid_entry.snmp_remote_engineID_host)))[3]);
                        APPEND_RUNNING_CFG_3("snmp-server user %s %s remote %s v1\n", entry.snmpv3_user_name,entry.snmpv3_user_group_name,ip_address);
                    }
                    else if(entry.snmpv3_user_security_model == SNMP_MGR_SNMPV3_MODEL_V2C)
                    {
                        SYSFUN_Sprintf(ip_address,"%d.%d.%d.%d",((UI8_T *)(&(engineid_entry.snmp_remote_engineID_host)))[0],((UI8_T *)(&(engineid_entry.snmp_remote_engineID_host)))[1],
                                                         ((UI8_T *)(&(engineid_entry.snmp_remote_engineID_host)))[2],((UI8_T *)(&(engineid_entry.snmp_remote_engineID_host)))[3]);
                        APPEND_RUNNING_CFG_3("snmp-server user %s %s remote %s v2c\n", entry.snmpv3_user_name,entry.snmpv3_user_group_name,ip_address);
                    }
                    else if(entry.snmpv3_user_security_model == SNMP_MGR_SNMPV3_MODEL_V3)
                    {
                        if(entry.snmpv3_user_security_level == VAL_vacmAccessSecurityLevel_noAuthNoPriv)
                        {
                            *temp='\0';
                        }
                        else if(entry.snmpv3_user_security_level == VAL_vacmAccessSecurityLevel_authNoPriv)
                        {
                            if(entry.snmpv3_user_auth_type == SNMP_MGR_SNMPV3_AUTHTYPE_MD5)
                            {
                                SYSFUN_Sprintf(auth_type,"md5");
                                max_len = SNMP_MGR_SNMPV3_MD5_KEY_LEN;
                            }
                            else if(entry.snmpv3_user_auth_type == SNMP_MGR_SNMPV3_AUTHTYPE_SHA)
                            {
                                SYSFUN_Sprintf(auth_type,"sha");
                                max_len = SNMP_MGR_SNMPV3_SHA_KEY_LEN;
                            }

                            COLLECT_ENCRTPT_TEXT_TO_PRINT_LENGTH(auth_key, entry.snmpv3_user_auth_key, max_len);
                            SYSFUN_Sprintf(temp,"encrypted auth %s %s",auth_type,auth_key);

                        }
                        else if(entry.snmpv3_user_security_level == VAL_vacmAccessSecurityLevel_authPriv)
                        {
                            if(entry.snmpv3_user_auth_type == SNMP_MGR_SNMPV3_AUTHTYPE_MD5)
                            {
                                SYSFUN_Sprintf(auth_type,"md5");
                                max_len = SNMP_MGR_SNMPV3_MD5_KEY_LEN;
                            }
                            else if(entry.snmpv3_user_auth_type == SNMP_MGR_SNMPV3_AUTHTYPE_SHA)
                            {
                                SYSFUN_Sprintf(auth_type,"sha");
                                max_len = SNMP_MGR_SNMPV3_SHA_KEY_LEN;
                            }

                            switch(entry.snmpv3_user_priv_type)
                            {
                                case SNMP_MGR_SNMPV3_PRIVTYPE_DES:
                                    max_priv_len = max_len;
                                SYSFUN_Sprintf(priv_type,"des56");
                                break;

                                case SNMP_MGR_SNMPV3_PRIVTYPE_3DES:
                                    max_priv_len = SNMP_MGR_SNMPV3_MAX_PRIV_KEY_LEN;
                                    SYSFUN_Sprintf(priv_type,"3des");
                                    break;

                                case SNMP_MGR_SNMPV3_PRIVTYPE_AES128:
                                    max_priv_len = max_len;
                                    SYSFUN_Sprintf(priv_type,"aes128");
                                break;

                                case SNMP_MGR_SNMPV3_PRIVTYPE_AES192:
                                    max_priv_len = SNMP_MGR_SNMPV3_AES192_KEY_LEN;
                                    SYSFUN_Sprintf(priv_type,"aes192");
                                break;

                                case SNMP_MGR_SNMPV3_PRIVTYPE_AES256:
                                    max_priv_len = SNMP_MGR_SNMPV3_AES256_KEY_LEN;
                                    SYSFUN_Sprintf(priv_type,"aes256");
                                break;

                                case SNMP_MGR_SNMPV3_PRIVTYPE_NONE:
                                default:
                                break;

                            }

                            COLLECT_ENCRTPT_TEXT_TO_PRINT_LENGTH(auth_key, entry.snmpv3_user_auth_key, max_len);
                            COLLECT_ENCRTPT_TEXT_TO_PRINT_LENGTH(priv_key, entry.snmpv3_user_priv_key, max_priv_len);

                            SYSFUN_Sprintf(temp,"encrypted auth %s %s priv %s %s",auth_type,auth_key,priv_type,priv_key);
                        }

                        SYSFUN_Sprintf(ip_address,"%d.%d.%d.%d",((UI8_T *)(&(engineid_entry.snmp_remote_engineID_host)))[0],((UI8_T *)(&(engineid_entry.snmp_remote_engineID_host)))[1],
                                                     ((UI8_T *)(&(engineid_entry.snmp_remote_engineID_host)))[2],((UI8_T *)(&(engineid_entry.snmp_remote_engineID_host)))[3]);
                        APPEND_RUNNING_CFG_4("snmp-server user %s %s remote %s v3 %s\n", entry.snmpv3_user_name,entry.snmpv3_user_group_name,ip_address,temp);
                    }
                }
            }
        } // end snmp-server user remote
    }

    /*snmp-server view*/
    {
        SNMP_MGR_SnmpV3ViewEntry_T  entry;
        char   temp[CLI_DEF_MAX_BUFSIZE]       = {0};
        char   temp1[CLI_DEF_MAX_BUFSIZE]       = {0};

        memset(&entry,0,sizeof(entry));
        while(SNMP_PMGR_GetNextRunningSnmpV3View(&entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(entry.snmpv3_view_type == VAL_vacmViewTreeFamilyType_excluded)
            {
                SYSFUN_Sprintf(temp,"excluded");
            }
            else if(entry.snmpv3_view_type == VAL_vacmViewTreeFamilyType_included)
            {
                SYSFUN_Sprintf(temp,"included");
            }
            else
            {
                *temp='\0';
            }
#if 0
            if(strcmp(entry.snmpv3_view_mask,"\0") != 0)
            {
                SYSFUN_Sprintf((char *)temp1,"mask %s",entry.snmpv3_view_mask);
            }
            else
#endif
            {
               *temp1='\0';
            }
            APPEND_RUNNING_CFG_4("snmp-server view %s %s %s %s\n", entry.snmpv3_view_name,
                                                        entry.snmpv3_wildcard_subtree/*snmpv3_view_subtree*/,
                                                        temp,
                                                        temp1);
        }

    }


   /*snmp-server agent status*/
    {
        BOOL_T status;

        if(SNMP_PMGR_GetRunningSnmpAgentStatus(&status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(status == TRUE)
            {
                APPEND_RUNNING_CFG_0("snmp-server\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no snmp-server\n");
            }
        }
    }
#endif
    /*snmp-server host*/
    {
#if (SYS_CPNT_SNMP_VERSION == 3)
        SNMP_MGR_TrapDestEntry_T trap_receiver;
        char ip_str[L_INET_MAX_IPADDR_STR_LEN + 1] = {0};
        memset(&trap_receiver, 0, sizeof(SNMP_MGR_TrapDestEntry_T));
#else
        TRAP_MGR_TrapDestEntry_T trap_receiver;
        memset(&trap_receiver, 0, sizeof(TRAP_MGR_TrapDestEntry_T)); /*initialize*/
#endif

#if (SYS_CPNT_SNMP_VERSION == 3)
        while (SNMP_PMGR_GetNextRunningTrapReceiver(&trap_receiver) ==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
#else
        while(TRAP_PMGR_GetNextRunningTrapReceiver(&trap_receiver) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
#endif
        {
#if (CLI_SUPPORT_SNMP_V2C == 1)
            char temp_string[3] = {0};

            switch(trap_receiver.trap_dest_version)
            {
                case SNMP_MGR_SNMPV3_MODEL_V1:
                    strcpy(temp_string,"1");
                break;

                case SNMP_MGR_SNMPV3_MODEL_V2C:
                    strcpy(temp_string,"2c");
                break;

                case SNMP_MGR_SNMPV3_MODEL_V3:
                    strcpy(temp_string,"3");
                break;

                default:
                break;
           }

            if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&trap_receiver.trap_dest_address,
                                                               ip_str,
                                                               sizeof(ip_str)))
            {
                APPEND_RUNNING_CFG_1("snmp-server host %s ", ip_str);
            }

//#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
//      CLI_LIB_Str_Add_Quote(trap_receiver.trap_dest_community,buf);
//    APPEND_RUNNING_CFG_2("%s version %s ", buf/*trap_receiver.trap_dest_community*/,temp_string);
//#else
//      APPEND_RUNNING_CFG_2("%s version %s ", trap_receiver.trap_dest_community,temp_string);
//#endif

#if (SYS_CPNT_SNMP_VERSION == 3)

           if(trap_receiver.trap_dest_version!=SNMP_MGR_SNMPV3_MODEL_V3)
           {
               if(trap_receiver.trap_dest_type == VAL_snmpNotifyType_inform)
               {
                   APPEND_RUNNING_CFG_2("inform timeout %ld retry %ld ", (long)trap_receiver.trap_inform_request_timeout,(long)trap_receiver.trap_inform_request_retry_cnt);
               }
               APPEND_RUNNING_CFG_3("%s version %s udp-port %ld\n", trap_receiver.trap_dest_community,temp_string,(long)trap_receiver.trap_dest_port);
           }
           else
           {
               if(trap_receiver.trap_dest_type==VAL_snmpNotifyType_inform)
               {
                   APPEND_RUNNING_CFG_2("inform timeout %ld retry %ld ", (long)trap_receiver.trap_inform_request_timeout,(long)trap_receiver.trap_inform_request_retry_cnt);
               }

               if(trap_receiver.trap_dest_security_level == VAL_snmpTargetParamsSecurityLevel_noAuthNoPriv)
               {
                   APPEND_RUNNING_CFG_3("%s version %s noauth udp-port %ld\n", trap_receiver.trap_dest_community,temp_string,(long)trap_receiver.trap_dest_port);
               }
               else if(trap_receiver.trap_dest_security_level == VAL_snmpTargetParamsSecurityLevel_authNoPriv)
               {
                   APPEND_RUNNING_CFG_3("%s version %s auth udp-port %ld\n", trap_receiver.trap_dest_community,temp_string,(long)trap_receiver.trap_dest_port);
               }
               else if(trap_receiver.trap_dest_security_level == VAL_snmpTargetParamsSecurityLevel_authPriv)
               {
                   APPEND_RUNNING_CFG_3("%s version %s priv udp-port %ld\n", trap_receiver.trap_dest_community,temp_string,(long)trap_receiver.trap_dest_port);
               }
          }
#else
           APPEND_RUNNING_CFG_2("%s version %s\n", trap_receiver.trap_dest_community,temp_string);
#endif

#else
           APPEND_RUNNING_CFG_4("snmp-server host %d.%d.%d.%d ", ((UI8_T *)(&trap_receiver.trap_dest_address))[0],
                                                                 ((UI8_T *)(&trap_receiver.trap_dest_address))[1],
                                                                 ((UI8_T *)(&trap_receiver.trap_dest_address))[2],
                                                                 ((UI8_T *)(&trap_receiver.trap_dest_address))[3]);
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
           CLI_LIB_Str_Add_Quote(trap_receiver.trap_dest_community,buf);
       APPEND_RUNNING_CFG_1("%s\n", buf/*trap_receiver.trap_dest_community*/);
#else
           APPEND_RUNNING_CFG_1("%s\n", trap_receiver.trap_dest_community);
#endif

#endif
       }
    }
#if (SYS_CPNT_NOTIFICATIONLOG_MIB == TRUE)
    /*snmp notify filter*/
    {
        SNMP_MGR_SnmpNotifyFilterProfileEntry_T entry;
        char ip_str[L_INET_MAX_IPADDR_STR_LEN + 1] = {0};

        memset(&entry, 0, sizeof(SNMP_MGR_SnmpNotifyFilterProfileEntry_T));
        while (SNMP_PMGR_GetNextSnmpNotifyFilterProfileTable(&entry) == SNMP_MGR_ERROR_OK)
        {
            if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&entry.snmp_notify_filter_profile_ip,
                                                               ip_str,
                                                               sizeof(ip_str)))
            {
                APPEND_RUNNING_CFG_2("snmp-server notify-filter %s remote %s\n",
                    entry.snmp_notify_filter_profile_name, ip_str);
            }
        }
    }

    /*notification log*/
    {
        SNMP_MGR_NlmConfigLog_T entry;

        memset(&entry, 0, sizeof(SNMP_MGR_NlmConfigLog_T));
        if (TRUE == NLM_PMGR_GetConfigLogEntry(&entry))
        {
            if (entry.filter_name[0] != '\0')
            {
                if (entry.admin_status == 1)
                {
                    APPEND_RUNNING_CFG_1("nlm %s\n", entry.filter_name);
                }
                else
                {
                    APPEND_RUNNING_CFG_0("no nlm\n");
                }
            }
        }
    }
#endif

   return buffer_count;
}
#endif

static UI32_T CLI_RUNCFG_Get_Rmon_Config_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;

    {
        SNMP_MGR_RmonAlarmEntry_T entry;

        memset(&entry, 0, sizeof(entry));

        while (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SNMP_PMGR_GetNextRunningRmonAlarmDeletedDefaultEntry(&entry))
        {
            APPEND_RUNNING_CFG_1("no rmon alarm %lu\n", (unsigned long)entry.id);
        }

        memset(&entry, 0, sizeof(entry));

        while (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SNMP_PMGR_GetNextRunningRmonAlarmTable(&entry))
        {
            APPEND_RUNNING_CFG_8("rmon alarm %lu %s %lu %s rising-threshold %lu %lu falling-threshold %lu %lu",
                            (unsigned long)entry.id,
                            entry.variable,
                            (unsigned long)entry.interval,
                            (VAL_alarmSampleType_absoluteValue == entry.sample_type) ? "absolute" : "delta",
                            (unsigned long)entry.rising_threshold,
                            (unsigned long)entry.rising_event_index,
                            (unsigned long)entry.falling_threshold,
                            (unsigned long)entry.falling_event_index);

            if ('\0' != entry.owner[0])
            {
                APPEND_RUNNING_CFG_1(" owner %s", entry.owner);
            }

            APPEND_RUNNING_CFG_0("\n");
        }
    }

    {
        SNMP_MGR_RmonEventEntry_T entry;

        memset(&entry, 0, sizeof(entry));

        while (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SNMP_PMGR_GetNextRunningRmonEventTable(&entry))
        {
            APPEND_RUNNING_CFG_1("rmon event %lu", (unsigned long)entry.id);

            if (   (VAL_eventType_log == entry.type)
                || (VAL_eventType_logandtrap == entry.type))
            {
                APPEND_RUNNING_CFG_0(" log");
            }

            if (   ('\0' != entry.community[0])
                && (   (VAL_eventType_snmptrap == entry.type)
                    || (VAL_eventType_logandtrap == entry.type)))
            {
                APPEND_RUNNING_CFG_1(" trap %s", entry.community);
            }

            if ('\0' != entry.description[0])
            {
                APPEND_RUNNING_CFG_1(" description %s", entry.description);
            }

            if ('\0' != entry.owner[0])
            {
                APPEND_RUNNING_CFG_1(" owner %s", entry.owner);
            }

            APPEND_RUNNING_CFG_0("\n");
        }
    }

    return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_Auth_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
   UI32_T buffer_count = b_count;
  /*username*/
    {
        /* UI32_T USERAUTH_GetNextRunningLoginUser(USERAUTH_LoginLocal_T *login_user);    */
        USERAUTH_LoginLocal_T login_user[SYS_ADPT_MAX_NBR_OF_LOGIN_USER + 2];
        UI32_T user_index;
        UI32_T get_user_count = 0;

        memset(login_user, 0, sizeof(login_user));

        if (USERAUTH_PMGR_GetRunningAllLoginLocalUser(login_user, _countof(login_user), &get_user_count) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {

            for (user_index = 0; user_index < get_user_count; user_index++)
            {
                if (login_user[user_index].status == USERAUTH_ENTRY_VALID)
                {
                    char  plain_empty_password[1 + 1];
                    char  encrypted_empty_password[SYS_ADPT_MAX_ENCRYPTED_PASSWORD_LEN + 1];
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                    char      buf[CLI_DEF_MAX_BUFSIZE + 1];
                    CLI_LIB_Str_Add_Quote((char *)login_user[user_index].username, buf);
#endif

#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                    APPEND_RUNNING_CFG_2("username %s access-level %lu\n", buf/*login_user.username*/, (unsigned long)login_user[user_index].privilege);
#else
                    APPEND_RUNNING_CFG_2("username %s access-level %lu\n", login_user.username, (unsigned long)login_user.privilege);
#endif

                    memset(plain_empty_password, 0, sizeof(plain_empty_password));
                    memset(encrypted_empty_password, 0, sizeof(encrypted_empty_password));
                    L_MD5_MDString((UI8_T *)encrypted_empty_password, (UI8_T *)plain_empty_password, strlen(plain_empty_password));

                    if (memcmp(encrypted_empty_password, login_user[user_index].password, SYS_ADPT_MAX_ENCRYPTED_PASSWORD_LEN) == 0)
                    {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                        APPEND_RUNNING_CFG_1("username %s nopassword\n", buf/*login_user.username*/);
#else
                        APPEND_RUNNING_CFG_1("username %s nopassword\n", login_user.username);
#endif
                    }
                    else
                    {
                        char  encrypt_buff[33] = { 0 };
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                        //UI8_T     buf[CLI_DEF_MAX_BUFSIZE+1];
                        char      buf1[CLI_DEF_MAX_BUFSIZE + 1];
#endif
                        COLLECT_ENCRTPT_TEXT_TO_PRINT(encrypt_buff, login_user[user_index].password);
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                        CLI_LIB_Str_Add_Quote(encrypt_buff, buf1);
                        APPEND_RUNNING_CFG_2("username %s password 7 %s\n", buf/*login_user.username*/, buf1/*encrypt_buff*/);
#else
                        APPEND_RUNNING_CFG_2("username %s password 7 %s\n", login_user.username, encrypt_buff);
#endif
                    }
                }
                else
                {
                    APPEND_RUNNING_CFG_1("no username %s \n", login_user[user_index].username);
                }
            }
        }
    }/*end of username*/

   /*enable password*/
   {
      SYS_TYPE_Get_Running_Cfg_T ret_;
      USERAUTH_Privilege_Password_T privilege_password;
      memset(&privilege_password, 0, sizeof(USERAUTH_Privilege_Password_T));

      ret_ = USERAUTH_PMGR_GetFirstRunningPrivilegePassword(&privilege_password);
      while (ret_ == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         char  encrypt_buff[33] = {0};
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
         char  buf[CLI_DEF_MAX_BUFSIZE+1];
#endif

         if (privilege_password.privilege == SYS_ADPT_MAX_LOGIN_PRIVILEGE)
         {
            COLLECT_ENCRTPT_TEXT_TO_PRINT(encrypt_buff, privilege_password.password);
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
            CLI_LIB_Str_Add_Quote(encrypt_buff,buf);

            APPEND_RUNNING_CFG_1("enable password 7 %s\n", buf/*encrypt_buff*/);
#else
            APPEND_RUNNING_CFG_1("enable password 7 %s\n", encrypt_buff);
#endif
         }
         else
         {
             COLLECT_ENCRTPT_TEXT_TO_PRINT(encrypt_buff, privilege_password.password);
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
             CLI_LIB_Str_Add_Quote(encrypt_buff,buf);
             APPEND_RUNNING_CFG_2("enable password level %lu 7 %s\n", (unsigned long)privilege_password.privilege, buf/*encrypt_buff*/);
#else
             APPEND_RUNNING_CFG_2("enable password level %lu 7 %s\n", (unsigned long)privilege_password.privilege, encrypt_buff);
#endif
         }

         ret_ = USERAUTH_PMGR_GetNextRunningPrivilegePassword(&privilege_password);
      }
   }/*end of enable password*/
#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("user auth complete\r\n");
#endif

#if (SYS_CPNT_DOT1X == TRUE)
   /* starting to set 802.1x global configuration */
   {
#if 0
      UI32_T max_req,mode,quiet_seconds,reauth_seconds,tx_seconds;
#endif
      /*if(DOT1X_MGR_GetRunning_Authen_Dot1x(&authen_do1x)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if(authen_do1x==0)
         {
            APPEND_RUNNING_CFG_0("no authentication dot1x\n");
         }
         else if(authen_do1x==1)
         {
            APPEND_RUNNING_CFG_0("authentication dot1x default radius\n");
         }
      }*/

#if 0
      if(DOT1X_MGR_GetRunning_MaxReq(&max_req)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1("dot1x max-req %lu\n",max_req);
      }

      if(DOT1X_POM_GetRunning_ReAuthenticationMode(&mode)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_0("dot1x re-authentication\n");
      }

      if(DOT1X_POM_GetRunning_QuietPeriod(&quiet_seconds)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1("dot1x timeout quiet-period %lu\n",quiet_seconds);
      }

      if(DOT1X_POM_GetRunning_ReAuthPeriod(&reauth_seconds)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1("dot1x timeout re-authperiod %lu\n",reauth_seconds);
      }

      if(DOT1X_POM_GetRunning_TxPeriod(&tx_seconds)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1("dot1x timeout tx-period %lu\n",tx_seconds);
      }
#endif
      APPEND_RUNNING_CFG_0("!\n");
   }
#endif

#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("dot1x global setup complete\r\n");
#endif
   return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_Syslog_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
   UI32_T buffer_count = b_count;
   /* syslog */
   {
      UI32_T syslog_status;
      UI32_T uc_log_level;
      UI32_T flash_log_level;
#if (SYS_CPNT_REMOTELOG == TRUE)
      UI32_T level, facility, remotelog_status;
#endif


      if(SYSLOG_PMGR_GetRunningSyslogStatus(&syslog_status)== SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if(syslog_status==SYSLOG_STATUS_ENABLE)
         {
            APPEND_RUNNING_CFG_0("logging on\n");
         }
         else if(syslog_status==SYSLOG_STATUS_DISABLE)
         {
            APPEND_RUNNING_CFG_0("no logging on\n");
         }
      }

      if(SYSLOG_PMGR_GetRunningUcLogLevel(&uc_log_level) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1("logging history ram %lu\n",(unsigned long)uc_log_level);
      }

      if(SYSLOG_PMGR_GetRunningFlashLogLevel(&flash_log_level) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1("logging history flash %lu\n",(unsigned long)flash_log_level);
      }
#if (SYS_CPNT_REMOTELOG == TRUE)
#if (SYS_CPNT_REMOTELOG_FACILITY_LEVEL_FOR_EVERY_SERVER == TRUE)
      {
         UI32_T udp_port;
         UI8_T ip_str[L_INET_MAX_IPADDR_STR_LEN+1];
         int i;
         SYSLOG_OM_Remote_Server_Config_T server_config;

         for(i=0;i<=4;i++)
         {
            memset(&server_config,0,sizeof(SYSLOG_OM_Remote_Server_Config_T));
            if(SYSLOG_PMGR_GetRunningRemoteLogServer(&server_config, i) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&(server_config.ipaddr),
                                                                   ip_str,
                                                                   sizeof(ip_str)))
                {
                    facility = server_config.facility;
                    level = server_config.level;
                    udp_port = server_config.udp_port;

                    if((facility == SYS_DFLT_REMOTELOG_FACILITY_TYPE) &&
                       (level == SYS_DFLT_REMOTELOG_LEVEL))
                    {
                        APPEND_RUNNING_CFG_2("logging host %s port %lu\r\n",ip_str, (unsigned long)udp_port);
                    }
                    else if(facility == SYS_DFLT_REMOTELOG_FACILITY_TYPE)
                    {
                        APPEND_RUNNING_CFG_3("logging host %s port %lu level %lu\r\n",ip_str, (unsigned long)udp_port,(unsigned long)level);
                    }
                    else if(level == SYS_DFLT_REMOTELOG_LEVEL)
                    {
                        APPEND_RUNNING_CFG_3("logging host %s port %lu facility %lu\r\n",ip_str, (unsigned long)udp_port,(unsigned long)facility);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_4("logging host %s port %lu facility %lu level %lu\r\n",ip_str, (unsigned long)udp_port,(unsigned long)facility,(unsigned long)level);
                    }
                }
            }
         }
      }
#else
      UI32_T udp_port;
      char ip_str[L_INET_MAX_IPADDR_STR_LEN+1];
      int i;
      SYSLOG_OM_Remote_Server_Config_T server_config;

      if(SYSLOG_PMGR_GetRunningFacilityType(&facility) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1("logging facility %lu\n",(unsigned long)facility);
      }

      if(SYSLOG_PMGR_GetRunningRemotelogLevel(&level) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1("logging trap level %lu\n",(unsigned long)level);
      }

      for(i = 0; i <= 4; i ++)
      {
          memset(&server_config,0,sizeof(SYSLOG_OM_Remote_Server_Config_T));

          if(SYSLOG_PMGR_GetRunningRemoteLogServer(&server_config, i) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
          {
              if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&(server_config.ipaddr),
                                                               ip_str,
                                                               sizeof(ip_str)))
              {
                  udp_port = server_config.udp_port;
                  APPEND_RUNNING_CFG_2("logging host %s port %lu\r\n", ip_str, (unsigned long)udp_port);
              }
          }
      }
#endif /* #if (SYS_CPNT_REMOTELOG_FACILITY_LEVEL_FOR_EVERY_SERVER == TRUE) */

      if(SYSLOG_PMGR_GetRunningRemoteLogStatus(&remotelog_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if(remotelog_status==SYSLOG_STATUS_ENABLE)
         {
            APPEND_RUNNING_CFG_0("logging trap\n");
         }
         else if(remotelog_status==SYSLOG_STATUS_DISABLE)
         {
            APPEND_RUNNING_CFG_0("no logging trap\n");
         }
      }
#endif
      APPEND_RUNNING_CFG_0("!\n");
   }/*end of syslog*/
#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("syslog complete\r\n");
#endif
   return buffer_count;
}


#if (SYS_CPNT_SMTP == TRUE)
static UI32_T CLI_RUNCFG_Get_Smtp_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    UI32_T ip_addr = 0;
    UI32_T status = 0;
    UI32_T level = 0;
    char   email_addr[SYS_ADPT_MAX_LENGTH_OF_SMTP_EMAIL_ADDRESS+1] = {0};
    UI8_T  temp_addr[30]   = {0};

    while(SMTP_PMGR_GetNextRunningSmtpServerIPAddr(&ip_addr) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        L_INET_Ntoa(ip_addr, temp_addr);
        APPEND_RUNNING_CFG_1("logging sendmail host %s\n", temp_addr);
    }

    if(SMTP_PMGR_GetRunningEmailSeverityLevel(&level)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        APPEND_RUNNING_CFG_1("logging sendmail level %lu\n", (unsigned long)level);
    }

    while(SMTP_PMGR_GetNextRunningSmtpDestinationEmailAddr((UI8_T *)email_addr)== SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
        char     buf[CLI_DEF_MAX_BUFSIZE+1];

        CLI_LIB_Str_Add_Quote(email_addr,buf);
        APPEND_RUNNING_CFG_1("logging sendmail destination-email %s\n", buf/*email_addr*/);
#else
        APPEND_RUNNING_CFG_1("logging sendmail destination-email %s\n", email_addr);
#endif
    }
    memset(email_addr, 0, sizeof(email_addr));

    if(SMTP_PMGR_GetRunningSmtpSourceEmailAddr((UI8_T *)email_addr)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
        char      buf[CLI_DEF_MAX_BUFSIZE+1];

        CLI_LIB_Str_Add_Quote(email_addr,buf);
        APPEND_RUNNING_CFG_1("logging sendmail source-email %s\n", buf/*email_addr*/);
#else
        APPEND_RUNNING_CFG_1("logging sendmail source-email %s\n", email_addr);
#endif
    }

    if(SMTP_PMGR_GetRunningSmtpAdminStatus(&status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if(status == SMTP_STATUS_ENABLE)
        {
            APPEND_RUNNING_CFG_0("logging sendmail\n");
        }
        else if(status == SMTP_STATUS_DISABLE)
        {
            APPEND_RUNNING_CFG_0("no logging sendmail\n");
        }
    }
    APPEND_RUNNING_CFG_0("!\n");
    APPEND_RUNNING_CFG_0("!\n");
    return buffer_count;
}
#endif

/* 2006/06/28
 * ES4649-38-00189: free memory before return
 */
static UI32_T cli_runcfg_get_vlanDatabase_parameter_macro(UI32_T unit_id, char *buffer, char *temp_buffer,
                                UI32_T buffer_size, UI32_T b_count, char *str_list)
{
    UI32_T buffer_count = b_count;

    /*VLAN database command*/ /*create vlan first*/
    {
        UI32_T time_mark = 0;
        UI32_T vid       = 0;

#if (SYS_CPNT_MSTP_SUPPORT_PVST==TRUE)
        UI32_T vlan_type = 0;
        UI8_T vlan_name[16];
#endif

        VLAN_TYPE_Vlan_RunningCfg_T vlan_cfg;

#if (SYS_CPNT_MSTP_SUPPORT_PVST==TRUE)
        UI32_T unit,port,ifindex;
        UI32_T current_max_unit,max_port_num;
        BOOL_T is_untagged = FALSE;
        BOOL_T is_tagged   = FALSE;
        UI32_T pvid      = 0;
        VLAN_TYPE_Vlan_Port_RunningCfg_T vlan_port_cfg;
        char  untagged_ports_list[SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST]={0};
        char  tagged_ports_list[SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST]={0};
        UI32_T i;
#endif

        char *vlan_list_str = NULL, *print_str = NULL;
        char active_vlan_list[(SYS_DFLT_DOT1QMAXVLANID+7)/8] = {0};
        char suspend_vlan_list[(SYS_DFLT_DOT1QMAXVLANID+7)/8] = {0};

#define MAX_VLAN_LIST_STRING_LEN 10000
        vlan_list_str = calloc(MAX_VLAN_LIST_STRING_LEN, sizeof(char));
        if (vlan_list_str == NULL )
        {
            return CLII_ERR_MEMORY_NOT_ENOUGH;
        }

        print_str = calloc(CLI_DEF_MAX_BUFSIZE-34, sizeof(char));
        if (print_str == NULL )
        {
            free(vlan_list_str);
            return CLII_ERR_MEMORY_NOT_ENOUGH;
        }

        memset(&vlan_cfg, 0, sizeof(VLAN_TYPE_Vlan_RunningCfg_T));
#if (SYS_CPNT_MSTP_SUPPORT_PVST==FALSE)
        APPEND_RUNNING_CFG_0("vlan database\n");      /*change to vlan database mode*/
#else
        CLI_API_GET_VLAN_DATABASE_VLAN_TYPE(&vlan_type,vlan_name);
#endif

        while (VLAN_POM_GetNextVlanId(time_mark, &vid))/*just for get vlan id*/
        {
            if (VLAN_POM_GetRunningVlanParameters(vid, &vlan_cfg) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {   /* private vlan */
                {
#if (SYS_CPNT_MSTP_SUPPORT_PVST==TRUE)
#if (SYS_CPNT_STACKING == TRUE)
                    current_max_unit = SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK;
#else
                    current_max_unit = 1;
#endif
                    memset(untagged_ports_list, 0, sizeof(untagged_ports_list));
                    memset(tagged_ports_list, 0, sizeof(untagged_ports_list));

                    for (i = 0; STKTPLG_POM_GetNextUnit(&i);)
                    {
                        unit = i;
                        max_port_num = SWCTRL_POM_UIGetUnitPortNumber(unit);

                        for (port = 1; port <= max_port_num; port++)
                        {
                            SWCTRL_UIUserPortToLogicalPort(unit,port,&ifindex);
                            VLAN_POM_GetRunningVlanPortParameters(ifindex, &vlan_port_cfg);
                            VLAN_IFINDEX_CONVERTTO_VID(vlan_port_cfg.pvid_index,pvid);

                            /*switchport allowed*/
                            if (vlan_cfg.egress_ports_changed == TRUE)
                            {
                                if (vlan_cfg.vlan_egress_ports[(UI32_T)((ifindex-1)/8)] & (1 << ( 7 - (( ifindex - 1) % 8) ) ))
                                {
                                    if (vlan_cfg.untag_ports_changed == TRUE)
                                    {
                                        if (vlan_cfg.vlan_untagged_ports[(UI32_T)((ifindex-1)/8)] & (1 << ( 7 - (( ifindex - 1) % 8) ) )) /*untagged*/
                                        {
                                            is_untagged = TRUE;
                                            untagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                        }
                                        else                                                                                             /*tagged*/
                                        {
                                            if (pvid != 1 && vid == 1)/*if user have set vlan1 to tag, when provision other command will not take effect, so */
                                                                      /*move this commadn to the end of those setting*/
                                            {
                                                is_untagged = TRUE;
                                                untagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                                is_tagged = TRUE;
                                                tagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                            }
                                            else
                                            {                /*2002.07.04 pttch prevent that if pvid is tag member, other command will not */
                                                if (pvid == vid)/*take effect in provision, like switchport native vlan x, then produce conflict problem*/
                                                {
#if (SYS_CPNT_VLAN_PROVIDING_DUAL_MODE==FALSE)
                                                    is_untagged = TRUE;
                                                    untagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
#endif
                                                    is_tagged = TRUE;
                                                    tagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                                }
                                                else
                                                {
                                                    is_tagged = TRUE;
                                                    tagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                                }
                                            }
                                        }
                                    }
                                    else /*because egress port change ,whatever untagged port changed or not*/
                                    {    /* we must show the command*/
                                        if (vlan_cfg.vlan_untagged_ports[(UI32_T)((ifindex-1)/8)] & (1 << ( 7 - (( ifindex - 1) % 8) ) )) /*untagged*/
                                        {
                                            is_untagged = TRUE;
                                            untagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                        }
                                        else                                                                                                             /*tagged*/
                                        {
                                            if (pvid != 1 && vid == 1)/*if user have set vlan1 to tag, when provision other command will not take effect, so */
                                                                      /*move this commadn to the end of those setting*/
                                            {
                                                is_untagged = TRUE;
                                                untagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                                is_tagged = TRUE;
                                                tagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                            }
                                            else
                                            {                /*2002.07.04 pttch prevent that if pvid is tag member, other command will not */
                                                if (pvid == vid)/*take effect in provision, like switchport native vlan x, then produce conflict problem*/
                                                {
                                                    is_untagged = TRUE;
                                                    untagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                                    is_tagged = TRUE;
                                                    tagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                                }
                                                else
                                                {
                                                    is_tagged = TRUE;
                                                    tagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }  //end for port loop
                    }  //end for unit loop

                    if (!vlan_cfg.name_changed && vlan_cfg.row_status_changed)
                    {
                        APPEND_RUNNING_CFG_1("vlan %lu by port\n",vid);

                        /*untagged member add first, tag member must add after untagged command done*/
                        {
                            memset (str_list,0,(512*4));

                            if (is_untagged)
                            {
                                CLI_LIB_Portlist_To_Userport(untagged_ports_list,str_list,0);
                                APPEND_RUNNING_CFG_1("%s",str_list);
                            }
                        }

                        /*tag member must add after untagged command done*/
                        {
                            memset (str_list,0,(512*4));

                            if (is_tagged)
                            {
                                CLI_LIB_Portlist_To_Userport(tagged_ports_list,str_list,1);
                                APPEND_RUNNING_CFG_1("%s",str_list);
                            }
                        }

                        /*spanning tree in vlan database mode*/
                        {
                            BOOL_T spanning_tree_status;
                            if (XSTP_PMGR_GetRunningVlanSpanningTreeStatus(vid,&spanning_tree_status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                            {
                                switch (spanning_tree_status)
                                {
                                    case TRUE:
                                        APPEND_RUNNING_CFG_0(" spanning-tree\r\n");
                                    break;

                                    case FALSE:
                                        APPEND_RUNNING_CFG_0(" no spanning-tree\r\n");
                                    break;

                                    default:
                                    break;
                                }
                            }
                        }

                        APPEND_RUNNING_CFG_0("!\n");
                    }

                    if (vlan_cfg.name_changed && vlan_cfg.row_status_changed)
                    {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                        char     buf[CLI_DEF_MAX_BUFSIZE+1];
                        CLI_LIB_Str_Add_Quote(vlan_cfg.vlan_name,buf);
                        APPEND_RUNNING_CFG_2("vlan %lu name %s\r\n",vid,buf);
#else
                        APPEND_RUNNING_CFG_2("vlan %lu name %s\r\n",vid,vlan_cfg.vlan_name);
#endif
                        /*untagged member add first, tag member must add after untagged command done*/
                        {
                            memset (str_list,0,(512*4);

                            if (is_untagged)
                            {
                                CLI_LIB_Portlist_To_Userport(untagged_ports_list,str_list,0);
                                APPEND_RUNNING_CFG_1("%s",str_list);
                            }
                        }

                        /*tag member must add after untagged command done*/
                        {
                            memset (str_list,0,(512*4));

                            if (is_tagged)
                            {
                                CLI_LIB_Portlist_To_Userport(tagged_ports_list,str_list,1);
                                APPEND_RUNNING_CFG_1("%s",str_list);
                            }
                        }

                        /*spanning tree in vlan database mode*/
                        {
                            BOOL_T spanning_tree_status;
                            if (XSTP_PMGR_GetRunningVlanSpanningTreeStatus(vid,&spanning_tree_status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                            {
                                switch (spanning_tree_status)
                                {
                                    case TRUE:
                                        APPEND_RUNNING_CFG_0(" spanning-tree\r\n");
                                    break;

                                    case FALSE:
                                        APPEND_RUNNING_CFG_0(" no spanning-tree\r\n");
                                    break;

                                    default:
                                    break;
                                }
                            }
                        }

                        APPEND_RUNNING_CFG_0("!\n");
                    }
#endif /* #if (SYS_CPNT_MSTP_SUPPORT_PVST==TRUE) */

#if (SYS_CPNT_MSTP_SUPPORT_PVST==FALSE)
#if (SYS_CPNT_RSPAN != TRUE)
                    if (vlan_cfg.name_changed && vlan_cfg.row_status_changed)
                    {
                        if (vlan_cfg.vlan_name[0])
                        {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                            char      buf[CLI_DEF_MAX_BUFSIZE+1];
                            CLI_LIB_Str_Add_Quote(vlan_cfg.vlan_name,buf);
                            APPEND_RUNNING_CFG_3(" vlan %lu name %s media ethernet state %s\n", vid, buf/*vlan_cfg.vlan_name*/,
                                (vlan_cfg.vlan_row_status == VAL_dot1qVlanStaticRowStatus_active ? "active"  : "suspend"));
#else
                            APPEND_RUNNING_CFG_3(" vlan %lu name %s media ethernet state %s\n", vid, vlan_cfg.vlan_name,
                                (vlan_cfg.vlan_row_status == VAL_dot1qVlanStaticRowStatus_active ? "active"  : "suspend");
#endif
                        }
                        else
                        {
                            APPEND_RUNNING_CFG_2(" vlan %lu media ethernet state %s\n", vid, (vlan_cfg.vlan_row_status == VAL_dot1qVlanStaticRowStatus_active ? "active"  : "suspend"));
                        }
                    }
                    else if (vlan_cfg.name_changed && !vlan_cfg.row_status_changed)
                    {
                        if (vlan_cfg.vlan_name[0])
                        {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                            char     buf[CLI_DEF_MAX_BUFSIZE+1];
                            CLI_LIB_Str_Add_Quote(vlan_cfg.vlan_name,buf);
                            APPEND_RUNNING_CFG_2(" vlan %lu name %s media ethernet\n", vid, buf/*vlan_cfg.vlan_name*/);
#else
                            APPEND_RUNNING_CFG_2(" vlan %lu name %s media ethernet\n", vid, vlan_cfg.vlan_name);
#endif
                        }
                        else
                        {
                            L_CVRT_ADD_MEMBER_TO_PORTLIST(active_vlan_list, vid);
                        }
                    }
                    else if (!vlan_cfg.name_changed && vlan_cfg.row_status_changed)
                    {
                        L_CVRT_ADD_MEMBER_TO_PORTLIST(suspend_vlan_list, vid);
                    }
                    else if (!vlan_cfg.name_changed && !vlan_cfg.row_status_changed)
                    {
                        L_CVRT_ADD_MEMBER_TO_PORTLIST(active_vlan_list, vid);
                    }
#else /* else #if (SYS_CPNT_RSPAN != TRUE) */
/* #if (SYS_CPNT_RSPAN == TRUE)
 */
                    if (vlan_cfg.rspan_status  == 3) /* VAL_vlanStaticExtRspanStatus_rspanVlan */
                    {
                        if (vlan_cfg.name_changed && vlan_cfg.row_status_changed && vlan_cfg.rspan_status_changed)
                        {
                            if (vlan_cfg.vlan_name[0])
                            {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                                char     buf[CLI_DEF_MAX_BUFSIZE+1];
                                CLI_LIB_Str_Add_Quote(vlan_cfg.vlan_name,buf);
                                APPEND_RUNNING_CFG_3(" VLAN %lu name %s media ethernet state %s rspan\n", (unsigned long)vid, buf/*vlan_cfg.vlan_name*/,
                                    (vlan_cfg.vlan_row_status == VAL_dot1qVlanStaticRowStatus_active ? "active"  : "suspend"));
#else
                                APPEND_RUNNING_CFG_3(" VLAN %lu name %s media ethernet state %s rspan\n", (unsigned long)vid, vlan_cfg.vlan_name,
                                    (vlan_cfg.vlan_row_status == VAL_dot1qVlanStaticRowStatus_active ? "active"  : "suspend"));
#endif
                            }
                            else
                            {
                                APPEND_RUNNING_CFG_1(" VLAN %lu media ethernet rspan\n", (unsigned long)vid);
                            }
                        }
                        else if (vlan_cfg.name_changed && vlan_cfg.row_status_changed && !vlan_cfg.rspan_status_changed)
                        {
                            if (vlan_cfg.vlan_name[0])
                            {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                                char     buf[CLI_DEF_MAX_BUFSIZE+1];
                                CLI_LIB_Str_Add_Quote(vlan_cfg.vlan_name,buf);
                                APPEND_RUNNING_CFG_3(" VLAN %lu name %s media ethernet state %s\n", (unsigned long)vid, buf/*vlan_cfg.vlan_name*/,
                                    (vlan_cfg.vlan_row_status == VAL_dot1qVlanStaticRowStatus_active ? "active"  : "suspend"));
#else
                                APPEND_RUNNING_CFG_3(" VLAN %lu name %s media ethernet state %s\n", (unsigned long)vid, vlan_cfg.vlan_name,
                                    (vlan_cfg.vlan_row_status == VAL_dot1qVlanStaticRowStatus_active ? "active"  : "suspend"));
#endif
                            }
                            else
                            {
                                L_CVRT_ADD_MEMBER_TO_PORTLIST(suspend_vlan_list, vid);
                            }
                        }
                        else if (vlan_cfg.name_changed && !vlan_cfg.row_status_changed && vlan_cfg.rspan_status_changed)
                        {
                            if (vlan_cfg.vlan_name[0])
                            {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                                char     buf[CLI_DEF_MAX_BUFSIZE+1];
                                CLI_LIB_Str_Add_Quote(vlan_cfg.vlan_name,buf);
                                APPEND_RUNNING_CFG_2(" VLAN %lu name %s media ethernet rspan\n", (unsigned long)vid, buf/*vlan_cfg.vlan_name*/);
#else
                                APPEND_RUNNING_CFG_2(" VLAN %lu name %s media ethernet rspan\n", (unsigned long)vid, vlan_cfg.vlan_name);
#endif
                            }
                            else
                            {
                                APPEND_RUNNING_CFG_1(" VLAN %lu media ethernet rspan\n", (unsigned long)vid);
                            }
                        }
                        else if (vlan_cfg.name_changed && !vlan_cfg.row_status_changed && !vlan_cfg.rspan_status_changed)
                        {
                            if (vlan_cfg.vlan_name[0])
                            {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                                char     buf[CLI_DEF_MAX_BUFSIZE+1];
                                CLI_LIB_Str_Add_Quote(vlan_cfg.vlan_name,buf);
                                APPEND_RUNNING_CFG_2(" VLAN %lu name %s media ethernet\n", (unsigned long)vid, buf/*vlan_cfg.vlan_name*/);
#else
                                APPEND_RUNNING_CFG_2(" VLAN %lu name %s media ethernet\n", (unsigned long)vid, vlan_cfg.vlan_name);
#endif
                            }
                            else
                            {
                                L_CVRT_ADD_MEMBER_TO_PORTLIST(active_vlan_list, vid);
                            }
                        }
                        else if (!vlan_cfg.name_changed && vlan_cfg.row_status_changed && vlan_cfg.rspan_status_changed)
                        {
                            APPEND_RUNNING_CFG_2(" VLAN %lu media ethernet state %s rspan\n", (unsigned long)vid,
                                (vlan_cfg.vlan_row_status == VAL_dot1qVlanStaticRowStatus_active ? "active"  : "suspend"));
                        }
                        else if (!vlan_cfg.name_changed && vlan_cfg.row_status_changed && !vlan_cfg.rspan_status_changed)
                        {
                            L_CVRT_ADD_MEMBER_TO_PORTLIST(suspend_vlan_list, vid);
                        }
                        else if (!vlan_cfg.name_changed && !vlan_cfg.row_status_changed && vlan_cfg.rspan_status_changed)
                        {
                            APPEND_RUNNING_CFG_1(" VLAN %lu media ethernet rspan\n", (unsigned long)vid);
                        }
                        else if (!vlan_cfg.name_changed && !vlan_cfg.row_status_changed && !vlan_cfg.rspan_status_changed)
                        {
                            L_CVRT_ADD_MEMBER_TO_PORTLIST(active_vlan_list, vid);
                        }
                    }
                    else
                    {
                        if (vlan_cfg.name_changed && vlan_cfg.row_status_changed)
                        {
                            if (vlan_cfg.vlan_name[0])
                            {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                                char     buf[CLI_DEF_MAX_BUFSIZE+1];
                                CLI_LIB_Str_Add_Quote(vlan_cfg.vlan_name,buf);
                                APPEND_RUNNING_CFG_3(" VLAN %lu name %s media ethernet state %s\n", (unsigned long)vid, buf/*vlan_cfg.vlan_name*/,
                                    (vlan_cfg.vlan_row_status == VAL_dot1qVlanStaticRowStatus_active ? "active"  : "suspend"));
#else
                                APPEND_RUNNING_CFG_3(" VLAN %lu name %s media ethernet state %s\n", (unsigned long)vid, vlan_cfg.vlan_name,
                                    (vlan_cfg.vlan_row_status == VAL_dot1qVlanStaticRowStatus_active ? "active"  : "suspend"));
#endif
                            }
                            else
                            {
                                L_CVRT_ADD_MEMBER_TO_PORTLIST(suspend_vlan_list, vid);
                            }
                        }
                        else if (vlan_cfg.name_changed && !vlan_cfg.row_status_changed)
                        {
                            if (vlan_cfg.vlan_name[0])
                            {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                                char     buf[CLI_DEF_MAX_BUFSIZE+1];
                                CLI_LIB_Str_Add_Quote(vlan_cfg.vlan_name,buf);
                                APPEND_RUNNING_CFG_2(" VLAN %lu name %s media ethernet\n", (unsigned long)vid, buf/*vlan_cfg.vlan_name*/);
#else
                                APPEND_RUNNING_CFG_2(" VLAN %lu name %s media ethernet\n", (unsigned long)vid, vlan_cfg.vlan_name);
#endif
                            }
                            else
                            {
                                L_CVRT_ADD_MEMBER_TO_PORTLIST(active_vlan_list, vid);
                            }
                        }
                        else if (!vlan_cfg.name_changed && vlan_cfg.row_status_changed)
                        {
                            L_CVRT_ADD_MEMBER_TO_PORTLIST(suspend_vlan_list, vid);
                        }
                        else if (!vlan_cfg.name_changed && !vlan_cfg.row_status_changed)
                        {
                            L_CVRT_ADD_MEMBER_TO_PORTLIST(active_vlan_list, vid);
                        }
                    } /* end-of-if ( vlan_cfg.rspan_status  == 3 ) */
/* end-of-#if (SYS_CPNT_RSPAN == TRUE)
 */
#endif /* end of #if (SYS_CPNT_RSPAN != TRUE) */
#endif /* #if (SYS_CPNT_MSTP_SUPPORT_PVST==FALSE) */
                }
            }  //end VLAN_POM_GetRunningVlanParameters

            else if (vid == 1) /*dynamic vlan => no this entry*/
            {
#if (SYS_CPNT_MSTP_SUPPORT_PVST==TRUE)
                APPEND_RUNNING_CFG_1("vlan %lu\n",(unsigned long)vid);
#else
                APPEND_RUNNING_CFG_1(" vlan %lu media ethernet state active\n", (unsigned long)vid);
#endif
            }
        }  //end while loop

        if (CLI_LIB_Bitmap_To_List(active_vlan_list, vlan_list_str, MAX_VLAN_LIST_STRING_LEN, SYS_ADPT_MAX_VLAN_ID, TRUE))
        {
            I32_T str_len = strlen((char *)vlan_list_str);
            I32_T printed_len = 0;

            memset(print_str, 0, (CLI_DEF_MAX_BUFSIZE-34));
            while (printed_len < str_len)
            {
                CLI_Runcfg_ListStrToOneLine(&printed_len, 34, vlan_list_str, print_str);
                APPEND_RUNNING_CFG_1(" vlan %s media ethernet\n", print_str);
            }
        }
        if (CLI_LIB_Bitmap_To_List(suspend_vlan_list, vlan_list_str, MAX_VLAN_LIST_STRING_LEN, SYS_ADPT_MAX_VLAN_ID, TRUE))
        {
            I32_T str_len = strlen((char *)vlan_list_str);
            I32_T printed_len = 0;

            memset(print_str, 0, (CLI_DEF_MAX_BUFSIZE-34));
            while (printed_len < str_len)
            {
                CLI_Runcfg_ListStrToOneLine(&printed_len, 34, vlan_list_str, print_str);
                APPEND_RUNNING_CFG_1(" vlan %s media ethernet state suspend\n", print_str);
            }
        }

        free(vlan_list_str);
        free(print_str);

        APPEND_RUNNING_CFG_0("!\n");
        APPEND_RUNNING_CFG_0("!\n");
    }/*end of vlan database*/

#if RUNCFG_DEVELOP
    CLI_LIB_PrintStr("create vlan complete\r\n");
#endif

    /*management vlan*/
#if (SYS_CPNT_ISOLATED_MGMT_VLAN == TRUE)
    {
        UI32_T vid_ifidx, vid;
        switch (NETCFG_PMGR_GetRunningManagementVid(&vid_ifidx))
        {
            case SYS_TYPE_GET_RUNNING_CFG_SUCCESS:
                if (FALSE == VLAN_OM_ConvertFromIfindex(vid_ifidx, &vid))
                {
                    vid = 0; /* Set management vlan disable*/
                }

                if (SYS_DFLT_SWITCH_MANAGEMENT_VLAN == 0) /* default management vlan disable*/
                {
                    APPEND_RUNNING_CFG_1(" management vlan %lu\n", (unsigned long)vid);
                }
                else
                {
                    if (vid == 0) /* if management vlan disable*/
                    {
                        APPEND_RUNNING_CFG_0(" no management vlan\n");
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_1(" management vlan %lu\n", (unsigned long)vid);
                    }
                }
                break;

            case SYS_TYPE_GET_RUNNING_CFG_FAIL:
                break;

            case SYS_TYPE_GET_RUNNING_CFG_NO_CHANGE:
                break;

            default:
                break;
        }
    }

    /* management vlan default-gateway */
    {
        UI8_T default_gateway[4]={0};

        switch (NETCFG_PMGR_GetRunningManagementVlanDefaultGateway((UI32_T*) default_gateway))
        {
            case SYS_TYPE_GET_RUNNING_CFG_SUCCESS:
                APPEND_RUNNING_CFG_4(" management vlan default-gateway %d.%d.%d.%d\r\n",
                    default_gateway[0], default_gateway[1], default_gateway[2], default_gateway[3]);
                break;

            case SYS_TYPE_GET_RUNNING_CFG_FAIL:
                break;

            case SYS_TYPE_GET_RUNNING_CFG_NO_CHANGE:
                break;

            default:
                break;
        }
    }
#endif /*#if (SYS_CPNT_ISOLATED_MGMT_VLAN == TRUE)   */

    APPEND_RUNNING_CFG_0("!\n");
    APPEND_RUNNING_CFG_0("!\n");

    return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_VlanDatabase_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    char     *str_list;
    UI32_T   return_value;

    if( (str_list = calloc(512*4, sizeof(char))) == NULL )
    {               /*why allocate this number, because vlan list string may be too large*/
                    /*so allocate such big memory to store this string*/
        return CLII_ERR_MEMORY_NOT_ENOUGH;
    }

    /* 2006/06/28
     * ES4649-38-00189: free memory before return
     */
    return_value = cli_runcfg_get_vlanDatabase_parameter_macro(unit_id, buffer, temp_buffer, buffer_size,
                      b_count, str_list);

    free( str_list );

    return return_value;
}

static UI32_T CLI_RUNCFG_Get_Create_Trunk(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;

#if (SYS_CPNT_TRUNK_BALANCE_MODE == TRUE)
    /*load balance*/
    {
        char *balance_mode_str = NULL;
        UI32_T balance_mode;

        if (SWCTRL_POM_GetRunningTrunkBalanceMode(&balance_mode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            switch (balance_mode)
            {
                case SWCTRL_TRUNK_BALANCE_MODE_MAC_SA:
                    balance_mode_str = "src-mac";
                    break;

                case SWCTRL_TRUNK_BALANCE_MODE_MAC_DA:
                    balance_mode_str = "dst-mac";
                    break;

                case SWCTRL_TRUNK_BALANCE_MODE_MAC_SA_DA:
                    balance_mode_str = "src-dst-mac";
                    break;

                case SWCTRL_TRUNK_BALANCE_MODE_IP_SA:
                    balance_mode_str = "src-ip";
                    break;

                case SWCTRL_TRUNK_BALANCE_MODE_IP_DA:
                    balance_mode_str = "dst-ip";
                    break;

                case SWCTRL_TRUNK_BALANCE_MODE_IP_SA_DA:
                    balance_mode_str = "src-dst-ip";
                    break;
            }

            if (balance_mode_str)
            {
                APPEND_RUNNING_CFG_1("port-channel load-balance %s\n", balance_mode_str);
            }
        }
    }
#endif /* (SYS_CPNT_TRUNK_BALANCE_MODE == TRUE) */

   /*interface-pchannel command*/   /*create trunk*/
   {
      TRK_MGR_TrunkEntry_T trunk_entry;
      UI32_T trunk_ifindex;
      memset (&trunk_entry, 0 , sizeof(TRK_MGR_TrunkEntry_T));
      trunk_entry.trunk_index = 0;

      while (TRK_PMGR_GetNextRunningTrunkEntry(&trunk_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         SWCTRL_POM_TrunkIDToLogicalPort(trunk_entry.trunk_index, &trunk_ifindex);
         if(TRK_PMGR_IsDynamicTrunkId(trunk_entry.trunk_index))
           continue;
         APPEND_RUNNING_CFG_1("interface port-channel %lu\n", (unsigned long)trunk_entry.trunk_index);
         APPEND_RUNNING_CFG_0("!\n");
         APPEND_RUNNING_CFG_0("!\n");
      }
   }
#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("create trunk complete\r\n");
#endif
   return buffer_count;
}

/* 2006/06/28
 * ES4649-38-00189: free memory before return
 */
static UI32_T cli_runcfg_get_ethernet_parameter_one_port_macor(UI32_T unit_id, UI32_T port_id, char *buffer,
                char *temp_buffer, UI32_T buffer_size, UI32_T b_count, char *str_list, char *print_str)
{
    UI32_T buffer_count = b_count;
    UI32_T which_trunk = 0;//* change to getrunning */
    UI32_T ifindex, trunk_ifindex;
    UI32_T lacp_state = 0;
    BOOL_T is_inherit      = TRUE;
    #if 0
    UI32_T cos,cfi,dscp;
    UI32_T queue,ret1;  /*remove warring,because never used.*/
    #endif
    SWCTRL_Lport_Type_T port_type;
    Port_Info_T port_info;

    port_type = SWCTRL_POM_UIUserPortToIfindex(unit_id, port_id, &ifindex, &is_inherit);

    if( SWCTRL_LPORT_UNKNOWN_PORT == port_type)
    {
        return buffer_count;
    }

#if (CLI_SUPPORT_PORT_NAME == 1)
    {
        char name[MAXSIZE_ifName+1] = {0};
        CLI_LIB_Ifindex_To_Name(ifindex,name);
        APPEND_RUNNING_CFG_1("interface ethernet %s\n", name);/*enter interface ethernet mode*/
    }
#else
    APPEND_RUNNING_CFG_2("interface ethernet %lu/%lu\n", (unsigned long)unit_id, (unsigned long)port_id);/*enter interface ethernet mode*/
#endif
    /*join trunk*/
    if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
    {
        if( SWCTRL_LPORT_UNKNOWN_PORT == SWCTRL_POM_UIUserPortToTrunkPort(unit_id, port_id, &which_trunk))
        {
            return buffer_count;
        }
        if( FALSE == SWCTRL_POM_TrunkIDToLogicalPort(which_trunk,&trunk_ifindex))
        {
            return buffer_count;
        }

#if 0
#if (SYS_CPNT_COS == TRUE && SYS_CPNT_ACL_UI == TRUE)
        {
            COS_TYPE_AclCosEntry_T cos_entry;
            memset(&cos_entry, 0, sizeof(cos_entry));

            while(L4_COS_PMGR_GetNextRunningCosEntry(ifindex, &cos_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
#if (SYS_CPNT_QOS_V2 == TRUE)
                if (cos_entry.acl_type == RULE_TYPE_IP_ACL)
#else
                if (cos_entry.acl_type == ACL_IP_ACL)
#endif
                {
                    APPEND_RUNNING_CFG_2(" map access-list ip %s cos %lu\n",cos_entry.acl_name ,cos_entry.cos);
                }
                else
                {
                    APPEND_RUNNING_CFG_2(" map access-list mac %s cos %lu\n",cos_entry.acl_name ,cos_entry.cos);
                }
            }
        }
#endif
#if (SYS_CPNT_ACL_UI == TRUE)
#if (SYS_CPNT_QOS_V2 == TRUE)
         {
            L4_MGR_AclEntry_T acl_entry;
            UI32_T            acl_index;
            UI16_T            time_range_index;
            enum{extra_time_range_string_size = sizeof("time-range ") + 1};
            char              time_range_string[SYS_ADPT_MAX_LENGTH_OF_TIME_ACL_TABLE_NAME + extra_time_range_string_size] = {0};
            if ( L4_PMGR_ACL_GetNextRunningAclByPort ( ifindex, &acl_index, &acl_entry, &time_range_index ) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS )
            {
#if (SYS_CPNT_TIME_BASED_ACL == TRUE)
                /* get time range name */
                if ( RULE_TYPE_UNDEF_TIME_RANGE != cur.time_range_index )
                {
                    char time_range_name[SYS_ADPT_MAX_LENGTH_OF_TIME_ACL_TABLE_NAME + 1] = {0};

                    L4_PMGR_GetTimeRangeNameByID(time_range_index, time_range_name);
                    sprintf (time_range_string,"time-range %s", time_range_name);
                }
#endif /* end of #if (SYS_CPNT_TIME_BASED_ACL == TRUE) */
               if ( acl_entry.acl_type == RULE_TYPE_IP_ACL )
               {
                    APPEND_RUNNING_CFG_2(" ip access-group %s in %s\n", acl_entry.acl_name, time_range_string);
               }

               if ( acl_entry.acl_type == RULE_TYPE_MAC_ACL )
               {
                    APPEND_RUNNING_CFG_2(" mac access-group %s in %s\n", acl_entry.acl_name, time_range_string);
               }

#if (SYS_CPNT_IPV6 == TRUE)
               if ( ( acl_entry.acl_type == RULE_TYPE_IPV6_STD_ACL ) ||
                   ( acl_entry.acl_type == RULE_TYPE_IPV6_EXT_ACL ) )
               {
                  APPEND_RUNNING_CFG_1(" ipv6 access-group %s in\n", acl_entry.acl_name);
               }
#endif

            }
         }
#else
        {
            ACL_AclGroup_Entry_T access_group;
            memset(&access_group, 0, sizeof(access_group));
            if (L4_ACL_PMGR_GetRunningAclGroup(ifindex , &access_group) == TRUE)
            {
                if (access_group.in_ip_acl[0] != 0)
                {
                    APPEND_RUNNING_CFG_1(" ip access-group %s in\n",access_group.in_ip_acl);
                }
                if (access_group.out_ip_acl[0] != 0)
                {
                    APPEND_RUNNING_CFG_1(" ip access-group %s out\n",access_group.out_ip_acl);
                }
                if (access_group.in_mac_acl[0] != 0)
                {
                    APPEND_RUNNING_CFG_1(" mac access-group %s in\n",access_group.in_mac_acl);
                }
                if (access_group.out_mac_acl[0] != 0)
                {
                    APPEND_RUNNING_CFG_1(" mac access-group %s out\n",access_group.out_mac_acl);
                }
            }
        }
#endif /* #if (SYS_CPNT_QOS_V2 == TRUE) */
#endif /* #if (SYS_CPNT_ACL_UI == TRUE) */

#if (SYS_CPNT_QOS == SYS_CPNT_QOS_MARKER)
        {
            UI8_T  acl_type[4] = {0};
            UI8_T  cos_type1[12] = {0};
            UI8_T  cos_type2[12] = {0};
            MARKER_TYPE_MarkerEntry_T marker_entry;
            memset(&marker_entry, 0, sizeof(marker_entry));
            while(L4_MARKER_PMGR_GetNextRunningMarkerEntry(ifindex, &marker_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                switch(marker_entry.acl_type)
                {
#if (SYS_CPNT_QOS_V2 == TRUE)
                    case RULE_TYPE_IP_ACL:
#else
                    case ACL_IP_ACL:
#endif
                       strcpy(acl_type, "ip");
                        break;

#if (SYS_CPNT_QOS_V2 == TRUE)
                    case RULE_TYPE_MAC_ACL:
#else
                    case ACL_MAC_ACL:
#endif
                        strcpy(acl_type, "mac");
                        break;

                    default:
                        break;
                }

                if ((marker_entry.action & MARKER_TYPE_REMARK_DOT1P_PRIORITY) == MARKER_TYPE_REMARK_DOT1P_PRIORITY)
                {
                    SYSFUN_Sprintf((char *)cos_type1, "priority %lu", marker_entry.dot1p);
                }

                if ((marker_entry.action & MARKER_TYPE_REMARK_DSCP) == MARKER_TYPE_REMARK_DSCP)
                {
                    SYSFUN_Sprintf((char *)cos_type2, "dscp %lu", marker_entry.dscp);
                }
                if ((marker_entry.action & MARKER_TYPE_REMARK_TOS_PRECEDENCE) == MARKER_TYPE_REMARK_TOS_PRECEDENCE)
                {
                    SYSFUN_Sprintf((char *)cos_type2, "precedence %lu", marker_entry.precedence);
                }

                if (cos_type1[0] == 0)
                {
                    APPEND_RUNNING_CFG_3(" match access-list %s %s set %s\n", acl_type, marker_entry.acl_name, cos_type2);
                }
                else
                {
                    if (cos_type2[0] == 0)
                    {
                        APPEND_RUNNING_CFG_3(" match access-list %s %s set %s\n", acl_type, marker_entry.acl_name, cos_type1);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_4(" match access-list %s %s set %s %s\n", acl_type, marker_entry.acl_name, cos_type1, cos_type2);
                    }
                }
                memset(&acl_type, 0, sizeof(acl_type));
                memset(&cos_type1, 0, sizeof(cos_type1));
                memset(&cos_type2, 0, sizeof(cos_type2));
            }
        }
#endif
#endif /*#if 0*/
    } //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

#if (SYS_CPNT_ETS==TRUE)
        /*For normal ports and member ports*/
        SWCTRL_POM_UserPortToIfindex(unit_id, port_id, &ifindex);
        UI32_T i;
        ETS_TYPE_MODE_T mode;
        UI32_T tc_tmp, tc_weight[SYS_ADPT_ETS_MAX_NBR_OF_TRAFFIC_CLASS];
        ETS_TYPE_TSA_T tsa;

        for(i=0; i<MAX_COS_VAL+1; i++){
            if(ETS_PMGR_GetRunningPrioAssign(ifindex, i, &tc_tmp)
                ==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_2(" traffic-class map %lu %lu\n", (unsigned long)i, (unsigned long)tc_tmp);
            }
        }

        for(i=0; i<SYS_ADPT_ETS_MAX_NBR_OF_TRAFFIC_CLASS; i++){
            if(ETS_PMGR_GetRunningTCTSA(ifindex, i, &tsa)
                ==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_2(" traffic-class algo %lu %s\n", (unsigned long)i, (tsa==ETS_TYPE_TSA_ETS)?"ets":"strict");
            }
        }

        if(ETS_PMGR_GetRunningWeight(ifindex, tc_weight)
            ==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG(" traffic-class weight");
            for(i=0; i<SYS_ADPT_ETS_MAX_NBR_OF_TRAFFIC_CLASS; i++){
                APPEND_RUNNING_CFG_1(" %lu", (unsigned long)tc_weight[i]);
            }
            APPEND_RUNNING_CFG("\n");
        }


        if(ETS_PMGR_GetRunningPortMode(ifindex, &mode)
                ==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            switch (mode)
            {
            case ETS_TYPE_MODE_USER:
                APPEND_RUNNING_CFG(" ets mode on\n");
                break;
            case ETS_TYPE_MODE_OFF:
                APPEND_RUNNING_CFG(" not ets mode\n");
                break;
            case ETS_TYPE_MODE_AUTO:
                APPEND_RUNNING_CFG(" ets mode auto\n");
                break;
            }
        }
#endif


    {
        SNMP_MGR_RmonStatisticsEntry_T entry;

        memset(&entry, 0, sizeof(entry));

        while (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SNMP_PMGR_GetNextRunningRmonStatisticsDeletedDefaultEntry(ifindex, &entry))
        {
            APPEND_RUNNING_CFG_1(" no rmon collection rmon1 controlEntry %lu\n", (unsigned long)entry.id);
        }

        memset(&entry, 0, sizeof(entry));

        while (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SNMP_PMGR_GetNextRunningRmonStatisticsTableByLport(ifindex, &entry))
        {
            APPEND_RUNNING_CFG_1(" rmon collection rmon1 controlEntry %lu", (unsigned long)entry.id);

            if ('\0' != entry.owner[0])
            {
                APPEND_RUNNING_CFG_1(" owner %s", entry.owner);
            }

            APPEND_RUNNING_CFG_0("\n");
        }
    }

    {
        SNMP_MGR_RmonHistoryControlEntry_T entry;

        memset(&entry, 0, sizeof(entry));

        while (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SNMP_PMGR_GetNextRunningRmonHistoryControlDeletedDefaultEntryByLport(ifindex, &entry))
        {
            APPEND_RUNNING_CFG_1(" no rmon collection history controlEntry %lu\n", (unsigned long)entry.id);
        }

        memset(&entry, 0, sizeof(entry));

        while (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == SNMP_PMGR_GetNextRunningRmonHistoryControlTableByLport(ifindex, &entry))
        {
            APPEND_RUNNING_CFG_1(" rmon collection history controlEntry %lu", (unsigned long)entry.id);

            if ('\0' != entry.owner[0])
            {
                APPEND_RUNNING_CFG_1(" owner %s", entry.owner);
            }

            APPEND_RUNNING_CFG_2(" buckets %lu interval %lu\n", (unsigned long)entry.buckets_requested, (unsigned long)entry.interval);
        }
    }

#if (SYS_CPNT_SFP_DDM_ALARMWARN_TRAP == TRUE)
    {
        SWCTRL_OM_SfpDdmThresholdEntry_T sfp_ddm_threshold_entry;

        if (SWCTRL_POM_GetRunningPortSfpDdmThresholdEntry(ifindex, &sfp_ddm_threshold_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(sfp_ddm_threshold_entry.trap_enable != SYS_DFLT_SFP_DDM_ALARMWARN_TRAP_STATUS)
            {
                APPEND_RUNNING_CFG_1(" %stransceiver-monitor \n", (sfp_ddm_threshold_entry.trap_enable == TRUE)?"":"no ");
            }
            if(sfp_ddm_threshold_entry.auto_mode != SYS_DFLT_SFP_DDM_ALARMWARN_AUTO_MODE)
            {
                APPEND_RUNNING_CFG_1(" %stransceiver-threshold-auto \n", (sfp_ddm_threshold_entry.auto_mode == TRUE)?"":"no ");
            }
            /* save config when auto_mode is false */
            if(sfp_ddm_threshold_entry.auto_mode == FALSE)
            {
                /* rx power */
                if(sfp_ddm_threshold_entry.threshold.rx_power_low_alarm != (float)SYS_DFLT_SFP_THRESHOLD_RX_POWER_LOW_ALARM)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold rx-power low-alarm %d\n", sfp_ddm_threshold_entry.threshold_int.rx_power_low_alarm);
                }
                if(sfp_ddm_threshold_entry.threshold.rx_power_low_warning != (float)SYS_DFLT_SFP_THRESHOLD_RX_POWER_LOW_WARNING)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold rx-power low-warning %d\n", sfp_ddm_threshold_entry.threshold_int.rx_power_low_warning);
                }
                if(sfp_ddm_threshold_entry.threshold.rx_power_high_warning != (float)SYS_DFLT_SFP_THRESHOLD_RX_POWER_HIGH_WARNING)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold rx-power high-warning %d\n", sfp_ddm_threshold_entry.threshold_int.rx_power_high_warning);
                }
                if(sfp_ddm_threshold_entry.threshold.rx_power_high_alarm != (float)SYS_DFLT_SFP_THRESHOLD_RX_POWER_HIGH_ALARM)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold rx-power high-alarm %d\n", sfp_ddm_threshold_entry.threshold_int.rx_power_high_alarm);
                }
                /* tx power */
                if(sfp_ddm_threshold_entry.threshold.tx_power_low_alarm != (float)SYS_DFLT_SFP_THRESHOLD_TX_POWER_LOW_ALARM)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold tx-power low-alarm %d\n", sfp_ddm_threshold_entry.threshold_int.tx_power_low_alarm);
                }
                if(sfp_ddm_threshold_entry.threshold.tx_power_low_warning != (float)SYS_DFLT_SFP_THRESHOLD_TX_POWER_LOW_WARNING)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold tx-power low-warning %d\n", sfp_ddm_threshold_entry.threshold_int.tx_power_low_warning);
                }
                if(sfp_ddm_threshold_entry.threshold.tx_power_high_warning != (float)SYS_DFLT_SFP_THRESHOLD_TX_POWER_HIGH_WARNING)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold tx-power high-warning %d\n", sfp_ddm_threshold_entry.threshold_int.tx_power_high_warning);
                }
                if(sfp_ddm_threshold_entry.threshold.tx_power_high_alarm != (float)SYS_DFLT_SFP_THRESHOLD_TX_POWER_HIGH_ALARM)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold tx-power high-alarm %d\n", sfp_ddm_threshold_entry.threshold_int.tx_power_high_alarm);
                }
                /* temperature */
                if(sfp_ddm_threshold_entry.threshold.temp_low_alarm != (float)SYS_DFLT_SFP_THRESHOLD_TEMP_LOW_ALARM)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold temperature low-alarm %d\n", sfp_ddm_threshold_entry.threshold_int.temp_low_alarm);
                }
                if(sfp_ddm_threshold_entry.threshold.temp_low_warning != (float)SYS_DFLT_SFP_THRESHOLD_TEMP_LOW_WARNING)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold temperature low-warning %d\n", sfp_ddm_threshold_entry.threshold_int.temp_low_warning);
                }
                if(sfp_ddm_threshold_entry.threshold.temp_high_warning != (float)SYS_DFLT_SFP_THRESHOLD_TEMP_HIGH_WARNING)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold temperature high-warning %d\n", sfp_ddm_threshold_entry.threshold_int.temp_high_warning);
                }
                if(sfp_ddm_threshold_entry.threshold.temp_high_alarm != (float)SYS_DFLT_SFP_THRESHOLD_TEMP_HIGH_ALARM)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold temperature high-alarm %d\n", sfp_ddm_threshold_entry.threshold_int.temp_high_alarm);
                }
                /* voltage */
                if(sfp_ddm_threshold_entry.threshold.voltage_low_alarm != (float)SYS_DFLT_SFP_THRESHOLD_VOLTAGE_LOW_ALARM)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold voltage low-alarm %u\n", sfp_ddm_threshold_entry.threshold_int.voltage_low_alarm);
                }
                if(sfp_ddm_threshold_entry.threshold.voltage_low_warning != (float)SYS_DFLT_SFP_THRESHOLD_VOLTAGE_LOW_WARNING)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold voltage low-warning %u\n", sfp_ddm_threshold_entry.threshold_int.voltage_low_warning);
                }
                if(sfp_ddm_threshold_entry.threshold.voltage_high_warning != (float)SYS_DFLT_SFP_THRESHOLD_VOLTAGE_HIGH_WARNING)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold voltage high-warning %u\n", sfp_ddm_threshold_entry.threshold_int.voltage_high_warning);
                }
                if(sfp_ddm_threshold_entry.threshold.voltage_high_alarm != (float)SYS_DFLT_SFP_THRESHOLD_VOLTAGE_HIGH_ALARM)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold voltage high-alarm %u\n", sfp_ddm_threshold_entry.threshold_int.voltage_high_alarm);
                }
                /* current */
                if(sfp_ddm_threshold_entry.threshold.bias_low_alarm != (float)SYS_DFLT_SFP_THRESHOLD_BIAS_LOW_ALARM)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold current low-alarm %u\n", sfp_ddm_threshold_entry.threshold_int.bias_low_alarm);
                }
                if(sfp_ddm_threshold_entry.threshold.bias_low_warning != (float)SYS_DFLT_SFP_THRESHOLD_BIAS_LOW_WARNING)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold current low-warning %u\n", sfp_ddm_threshold_entry.threshold_int.bias_low_warning);
                }
                if(sfp_ddm_threshold_entry.threshold.bias_high_warning != (float)SYS_DFLT_SFP_THRESHOLD_BIAS_HIGH_WARNING)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold current high-warning %u\n", sfp_ddm_threshold_entry.threshold_int.bias_high_warning);
                }
                if(sfp_ddm_threshold_entry.threshold.bias_high_alarm != (float)SYS_DFLT_SFP_THRESHOLD_BIAS_HIGH_ALARM)
                {
                    APPEND_RUNNING_CFG_1(" transceiver-threshold current high-alarm %u\n", sfp_ddm_threshold_entry.threshold_int.bias_high_alarm);
                }
            }
        }
    }
#endif


#if (SYS_CPNT_COMBO_PORT_FORCE_MODE == TRUE)
    /*combo-forced-mode*/
    {
        UI32_T forcedmode;
#if (SYS_CPNT_COMBO_PORT_FORCED_MODE_SFP_SPEED == TRUE)
        UI32_T fiber_operator_mode;
#endif
        if (SWCTRL_POM_GetRunningPortComboForcedMode(ifindex, &forcedmode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            switch(forcedmode)
            {
                case VAL_portComboForcedMode_none:
                    break;

                case VAL_portComboForcedMode_copperForced:
                    APPEND_RUNNING_CFG_0(" media-type copper-forced\n");
                    break;

/*pttch 2004/8/5 04:20 do not support this mode*/
#if 0
                case VAL_portComboForcedMode_copperPreferredAuto:
                    APPEND_RUNNING_CFG_0(" media-type copper-preferred-auto\n");
                    break;
#endif
                case VAL_portComboForcedMode_sfpForced:
                    APPEND_RUNNING_CFG_0(" media-type sfp-forced");
                    /*add 100fx&1000sfp*/
#if (SYS_CPNT_COMBO_PORT_FORCED_MODE_SFP_SPEED == TRUE)
                    if (SWCTRL_POM_GetRunningPortComboForcedModeSpeed(ifindex, &fiber_operator_mode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                    {
                        if(fiber_operator_mode==VAL_portType_hundredBaseFX)
                        {
                            APPEND_RUNNING_CFG_0(" 100fx");
                        }
                        else if(fiber_operator_mode==VAL_portType_thousandBaseSfp)
                        {
                            APPEND_RUNNING_CFG_0(" 1000sfp");
                        }
                        else if(fiber_operator_mode==VAL_portType_tenGBaseSFP)
                        {
                            APPEND_RUNNING_CFG_0(" 10gsfp");
                        }
                        else if(fiber_operator_mode==VAL_portType_fortyGBaseQSFP)
                        {
                            APPEND_RUNNING_CFG_0(" 40gqsfp");
                        }
                        else if(fiber_operator_mode==VAL_portType_hundredGBaseQSFP)
                        {
                            APPEND_RUNNING_CFG_0(" 100gqsfp");
                        }
                        else if(fiber_operator_mode==VAL_portType_twentyFiveGBaseSFP)
                        {
                            APPEND_RUNNING_CFG_0(" 25gsfp");
                        }
                    }
#endif
                    APPEND_RUNNING_CFG_0("\n");
                    break;

                case VAL_portComboForcedMode_sfpPreferredAuto:
                    APPEND_RUNNING_CFG_0(" media-type sfp-preferred-auto\n");
                    break;

                default:
                    break;
            }
        }
    }
#endif

#if 0/*for 60 temp*/
    /*spanning-tree per port*/
    {
        UI32_T spanning_status;

        if(XSTP_POM_GetRunningPortSpanningTreeStatus(ifindex,&spanning_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(spanning_status == VAL_staPortSystemStatus_enabled)
            {
                APPEND_RUNNING_CFG_0(" no spanning-tree spanning-disabled\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" spanning-tree spanning-disabled\n");
            }
        }
    }
#endif

#if (SYS_CPNT_POE == TRUE)
    if (STKTPLG_OM_IsPoeDevice(unit_id))
    {
        UI32_T value = 0;

#if (SYS_CPNT_POE_TIME_RANGE == TRUE)
        UI8_T time_range[SYS_ADPT_TIME_RANGE_MAX_NAME_LENGTH + 1] = {0};
#endif

        /* power inline */
        if(POE_POM_GetRunningPsePortAdmin(unit_id,port_id,&value)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(value==VAL_pethPsePortAdminEnable_true)
            {
                APPEND_RUNNING_CFG_0(" power inline\n");
                    }
                    else
                    {
                APPEND_RUNNING_CFG_0(" no power inline\n");
                    }
                }
#ifdef SYS_CPNT_POE_PSE_DOT3AT
#if (SYS_CPNT_POE_ASIC == SYS_CPNT_POE_ASIC_BROADCOM)
        /* power inline high-power */
        if(POE_POM_GetRunningPortManualHighPowerMode(unit_id,port_id,&value)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (value == 1)
            {
                APPEND_RUNNING_CFG_0(" power inline high-power\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no power inline high-power\n");
            }
        }
#endif
#endif
        #if (SYS_CPNT_POE_PRIORITY_SUPPORT == TRUE)
        /* power inline priority */
        if(POE_POM_GetRunningPsePortPowerPriority(unit_id,port_id,&value)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" power inline priority %lu\n",(unsigned long)value);
        }
        #endif
        #if (SYS_CPNT_POE_INLINE_MAX_ALLOC_FIXED != TRUE)
        /* power inline maximum allocation: milliwatts */
        if(POE_POM_GetRunningPortPowerMaximumAllocation(unit_id, port_id, &value)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" power inline maximum allocation %lu\n", (unsigned long)value);
        }
        #endif

#if (SYS_CPNT_POE_TIME_RANGE == TRUE)
        /* power inline time-range */
        if (POE_POM_GetRunningPsePortTimeRangeName(unit_id, port_id, time_range) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" power inline time-range %s\n", (char *) time_range);
        }
#endif

    }
#endif /* #if (SYS_CPNT_POE == TRUE) */
    /*switch control*/
    {

        UI32_T temp_ifindex = 0;

        memset (&port_info , 0 , sizeof(Port_Info_T));

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

        if (SWCTRL_POM_GetRunningPortInfo(ifindex, &port_info) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            /* description */
            if (port_info.port_name_changed == TRUE)
            {
                if (port_info.port_name[0])
                {
                    APPEND_RUNNING_CFG_1(" description %s\n",port_info.port_name);
                }
            }

#if (SYS_CPNT_SWCTRL_CONTAIN_CLI_ALIAS == TRUE)
          /*EPR:ES4827G-FLF-ZZ-00232
           *Problem: CLI:size of vlan name different in console and mib
           *Solution: add CLI command "alias" for interface set,the
           *          alias is different from name and port descrition,so
           *          need add new command.
           *modify file: cli_cmd.c,cli_cmd.h,cli_arg.c,cli_arg.h,cli_msg.c,
           *             cli_msg.h,cli_api_vlan.c,cli_api_vlan.h,cli_api_ehternet.c
           *             cli_api_ethernet.h,cli_api_port_channel.c,cli_api_port_channel.h,
           *             cli_running.c,rfc_2863.c,swctrl.h,trk_mgr.h,trk_pmgr.h,swctrl.c
           *             swctrl_pmgr.c,trk_mgr.c,trk_pmgr.c,vlan_mgr.h,vlan_pmgr.h,
           *             vlan_type.h,vlan_mgr.c,vlan_pmgr.c,if_mgr.c
           *Approved by:Hardsun
           *Fixed by:Dan Xie
           */
        /*for Port alias command*/
            if(port_info.port_alias_changed == TRUE)
            {
               /* switchport mtu */
                if(port_info.port_alias[0])
                {
                    APPEND_RUNNING_CFG_1(" alias %s\n",port_info.port_alias);
                }
            }
#endif /* (SYS_CPNT_SWCTRL_CONTAIN_CLI_ALIAS == TRUE) */

            /*shutdown eth*/
            if(port_info.admin_state_changed == TRUE)
            {
                if (port_info.admin_state == VAL_ifAdminStatus_down)
                {
                    APPEND_RUNNING_CFG_0(" shutdown\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no shutdown\n");
                }
            }

#if (SYS_CPNT_AMTR_UI == TRUE)
#if(SYS_CPNT_AMTR_PORT_MAC_LEARNING == TRUE)/*Tony.Lei*/
            /*mac-learning*/
            if(port_info.port_macaddr_learning_changed == TRUE)
            {
                if (port_info.port_macaddr_learning == VAL_staPortMacAddrLearning_true)
                {
                    APPEND_RUNNING_CFG_0(" mac-learning\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no mac-learning\n");
                }
            }
#endif
#endif /* #if (SYS_CPNT_AMTR_UI == TRUE) */

#if (SYS_CPNT_SWCTRL_MTU_CONFIG_MODE == SYS_CPNT_SWCTRL_MTU_PER_PORT)
           {
              /* switchport mtu */
                if(port_info.port_mtu_changed == TRUE)
                {
                    APPEND_RUNNING_CFG_1(" switchport mtu %lu\n",(unsigned long)port_info.mtu);
                }
           }
#endif

#if (SYS_CPNT_SWCTRL_SWITCH_MODE_CONFIGURABLE == TRUE)
            if ((port_type != SWCTRL_LPORT_TRUNK_PORT_MEMBER) && port_info.switch_mode_changed)
            {
                if (port_info.switch_mode == VAL_swctrlSwitchModeCT)
                {
                    APPEND_RUNNING_CFG_0(" switching-mode cut-through\n");
                }
                else if (port_info.switch_mode == VAL_swctrlSwitchModeSF)
                {
                    APPEND_RUNNING_CFG_0(" switching-mode store-and-forward\n");
                }
            }
#endif /*#if (SYS_CPNT_SWCTRL_SWITCH_MODE_CONFIGURABLE == TRUE)*/

        } // end SWCTRL_POM_GetRunningPortInfo(ifindex, &port_info)

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }

        /*The configurations that follow user physical port setting*/
        {
            Port_Info_T tmp_port_info;

            if (SWCTRL_POM_GetRunningPortInfo(ifindex, &tmp_port_info) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {

#if (SYS_CPNT_NEGOTIATION == TRUE)
                /* capabilities */
                if (tmp_port_info.autoneg_capability_changed)
                {  /*((value & default) & capability) = capability*/
                    if (((tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap10half) == SYS_VAL_portCapabilities_portCap10half)
                    {
                        APPEND_RUNNING_CFG_0(" capabilities 10half\n");
                    }

                    else if (((~tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap10half) == SYS_VAL_portCapabilities_portCap10half)
                    {
                        APPEND_RUNNING_CFG_0(" no capabilities 10half\n");
                    }

                    if (((tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap10full) == SYS_VAL_portCapabilities_portCap10full)
                    {
                        APPEND_RUNNING_CFG_0(" capabilities 10full\n");
                    }

                    else if (((~tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap10full) == SYS_VAL_portCapabilities_portCap10full)
                    {
                        APPEND_RUNNING_CFG_0(" no capabilities 10full\n");
                    }

                    if (((tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap100half) == SYS_VAL_portCapabilities_portCap100half)
                    {
                        APPEND_RUNNING_CFG_0(" capabilities 100half\n");
                    }

                    else if (((~tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap100half) == SYS_VAL_portCapabilities_portCap100half)
                    {
                        APPEND_RUNNING_CFG_0(" no capabilities 100half\n");
                    }

                    if (((tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap100full) == SYS_VAL_portCapabilities_portCap100full)
                    {
                        APPEND_RUNNING_CFG_0(" capabilities 100full\n");
                    }

                    else if (((~tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap100full) == SYS_VAL_portCapabilities_portCap100full)
                    {
                        APPEND_RUNNING_CFG_0(" no capabilities 100full\n");
                    }

                    if (((tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap1000half) == SYS_VAL_portCapabilities_portCap1000half)
                    {
                        APPEND_RUNNING_CFG_0(" capabilities 1000half\n");
                    }

                    else if (((~tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap1000half) == SYS_VAL_portCapabilities_portCap1000half)
                    {
                        APPEND_RUNNING_CFG_0(" no capabilities 1000half\n");
                    }

                    if (((tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap1000full) == SYS_VAL_portCapabilities_portCap1000full)
                    {
                        APPEND_RUNNING_CFG_0(" capabilities 1000full\n");
                    }
                    else if (((~tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap1000full) == SYS_VAL_portCapabilities_portCap1000full)
                    {
                        APPEND_RUNNING_CFG_0(" no capabilities 1000full\n");
                    }

                    if (((tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap10gHalf) == SYS_VAL_portCapabilities_portCap10gHalf)
                    {
                        APPEND_RUNNING_CFG_0(" capabilities 10ghalf\n");
                    }
                    else if (((~tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap10gHalf) == SYS_VAL_portCapabilities_portCap10gHalf)
                    {
                        APPEND_RUNNING_CFG_0(" no capabilities 10ghalf\n");
                    }

                    if (((tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap10gFull) == SYS_VAL_portCapabilities_portCap10gFull)
                    {
                        APPEND_RUNNING_CFG_0(" capabilities 10gfull\n");
                    }
                    else if (((~tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap10gFull) == SYS_VAL_portCapabilities_portCap10gFull)
                    {
                        APPEND_RUNNING_CFG_0(" no capabilities 10gfull\n");
                    }

                    if (((tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap40gHalf) == SYS_VAL_portCapabilities_portCap40gHalf)
                    {
                        APPEND_RUNNING_CFG_0(" capabilities 40ghalf\n");
                    }
                    else if (((~tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap40gHalf) == SYS_VAL_portCapabilities_portCap40gHalf)
                    {
                        APPEND_RUNNING_CFG_0(" no capabilities 40ghalf\n");
                    }

                    if (((tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap40gFull) == SYS_VAL_portCapabilities_portCap40gFull)
                    {
                        APPEND_RUNNING_CFG_0(" capabilities 40gfull\n");
                    }
                    else if (((~tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap40gFull) == SYS_VAL_portCapabilities_portCap40gFull)
                    {
                        APPEND_RUNNING_CFG_0(" no capabilities 40gfull\n");
                    }

                    if (((tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap100gFull) == SYS_VAL_portCapabilities_portCap100gFull)
                    {
                        APPEND_RUNNING_CFG_0(" capabilities 100gfull\n");
                    }
                    else if (((~tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCap100gFull) == SYS_VAL_portCapabilities_portCap100gFull)
                    {
                        APPEND_RUNNING_CFG_0(" no capabilities 100gfull\n");
                    }

                    if (((tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCapSym) == SYS_VAL_portCapabilities_portCapSym)
                    {
                        APPEND_RUNNING_CFG_0(" capabilities symmetric\n");
                    }

                    else if (((~tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCapSym) == SYS_VAL_portCapabilities_portCapSym)
                    {
                        APPEND_RUNNING_CFG_0(" no capabilities symmetric\n");
                    }
                    if (((tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCapFlowCtrl) == SYS_VAL_portCapabilities_portCapFlowCtrl)
                    {
                        APPEND_RUNNING_CFG_0(" capabilities flowcontrol\n");
                    }

                    else if (((~tmp_port_info.autoneg_capability & tmp_port_info.autoneg_capability_changed) & SYS_VAL_portCapabilities_portCapFlowCtrl) == SYS_VAL_portCapabilities_portCapFlowCtrl)
                    {
                        APPEND_RUNNING_CFG_0(" no capabilities flowcontrol\n");
                    }
                }
#endif /* (SYS_CPNT_NEGOTIATION == TRUE) */

#if (SYS_CPNT_NEGOTIATION == TRUE)
                /* negotiation */
                if(tmp_port_info.autoneg_state_changed == TRUE)
                {
                    if (tmp_port_info.autoneg_state == VAL_portAutonegotiation_enabled)
                    {
                        APPEND_RUNNING_CFG_0(" negotiation\n");
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_0(" no negotiation\n");
                    }
                }
#endif

#if (SYS_CPNT_SPEED_DUPLEX == TRUE)
                /* speed-duplex */
                if (tmp_port_info.speed_duplex_cfg_changed == TRUE)
                {
                    switch(tmp_port_info.speed_duplex_cfg)
                    {
                        case VAL_portSpeedDpxStatus_halfDuplex10:
                            APPEND_RUNNING_CFG_0(" speed-duplex 10half\n");
                            break;

                        case VAL_portSpeedDpxStatus_fullDuplex10:
                            APPEND_RUNNING_CFG_0(" speed-duplex 10full\n");
                            break;

                        case VAL_portSpeedDpxStatus_halfDuplex100:
                            APPEND_RUNNING_CFG_0(" speed-duplex 100half\n");
                            break;

                        case VAL_portSpeedDpxStatus_fullDuplex100:
                            APPEND_RUNNING_CFG_0(" speed-duplex 100full\n");
                            break;

                        case VAL_portSpeedDpxCfg_halfDuplex1000:
                            APPEND_RUNNING_CFG_0(" speed-duplex 1000half\n");
                            break;

                        case VAL_portSpeedDpxCfg_fullDuplex1000:
                            APPEND_RUNNING_CFG_0(" speed-duplex 1000full\n");
                            break;

                        case VAL_portSpeedDpxCfg_fullDuplex10g:
                            APPEND_RUNNING_CFG_0(" speed-duplex 10gfull\n");
                            break;

                        case VAL_portSpeedDpxCfg_fullDuplex25g:
                            APPEND_RUNNING_CFG_0(" speed-duplex 25gfull\n");
                            break;

                        case VAL_portSpeedDpxCfg_fullDuplex40g:
                            APPEND_RUNNING_CFG_0(" speed-duplex 40gfull\n");
                            break;

                        case VAL_portSpeedDpxCfg_fullDuplex100g:
                            APPEND_RUNNING_CFG_0(" speed-duplex 100gfull\n");
                            break;

                        default :
                            break;
                    }
                }
#endif /* (SYS_CPNT_SPEED_DUPLEX == TRUE) */

                /* START: MDIX mode */
#if (SYS_CPNT_SWCTRL_MDIX_CONFIG == TRUE)
                if ( TRUE == tmp_port_info.port_MDIX_mode_changed )
                {
                    if ( tmp_port_info.port_MDIX_mode != SYS_DFLT_MDIX_MODE )
                    {
                        if ( tmp_port_info.port_MDIX_mode == VAL_portMdixMode_auto )
                        {
                            APPEND_RUNNING_CFG_0(" mdix auto\n");
                        }
                        else if ( tmp_port_info.port_MDIX_mode == VAL_portMdixMode_straight )
                        {
                            APPEND_RUNNING_CFG_0(" mdix straight\n");
                        }
                        else if ( tmp_port_info.port_MDIX_mode == VAL_portMdixMode_crossover )
                        {
                            APPEND_RUNNING_CFG_0(" mdix crossover\n");
                        }
                    }
                }
#endif
                /* END: MDIX mode */

#if (SYS_CPNT_SUPPORT_FORCED_1000BASE_T_MODE==TRUE)
                /*giga phy mode*/
                if(tmp_port_info.forced_1000t_mode_changed==TRUE)
                {
                    switch(tmp_port_info.forced_1000t_mode)
                    {
                        case VAL_portMasterSlaveModeCfg_master:
                            APPEND_RUNNING_CFG_0(" giga-phy-mode master\n");
                            break;

                        case VAL_portMasterSlaveModeCfg_slave:
                            APPEND_RUNNING_CFG_0(" giga-phy-mode slave\n");
                            break;

                        default:
                            break;
                    }
                 }
#endif

                /* flowcontrol */
                if(tmp_port_info.flow_control_cfg_changed == TRUE)
                {
                    if (tmp_port_info.flow_control_cfg == VAL_portFlowCtrlCfg_enabled)
                    {
                        APPEND_RUNNING_CFG_0(" flowcontrol\n");
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_0(" no flowcontrol\n");
                    }
                }

#if (SYS_CPNT_SWCTRL_FEC == TRUE)
                if(tmp_port_info.port_fec_mode_changed == TRUE)
                {
                    switch (tmp_port_info.port_fec_mode)
                    {
                        case VAL_portFecMode_disabled:
                            APPEND_RUNNING_CFG_0(" no fec\n");
                            break;

                        case VAL_portFecMode_baseR:
                            APPEND_RUNNING_CFG_0(" fec base-r\n");
                            break;

                        case VAL_portFecMode_rs:
                            APPEND_RUNNING_CFG_0(" fec rs\n");
                            break;
                    }
                }
#endif

            } /*if (SWCTRL_POM_GetRunningPortInfo(ifindex, &tmp_port_info) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)*/
        }
        /* end of "The configurations that follow user physical port setting" */

        /* port monitor */
        {
#if (SYS_CPNT_VLAN_MIRROR == TRUE)
            SWCTRL_VlanMirrorEntry_T vlan_mirror_entry;
#endif /* End of #if (SYS_CPNT_VLAN_MIRROR == TRUE) */
#if (SYS_CPNT_MAC_BASED_MIRROR == TRUE)
            SWCTRL_MacAddrMirrorEntry_T mac_addr_entry;
            UI32_T                      mac_dest_port;
#endif /* End of #if (SYS_CPNT_MAC_BASED_MIRROR == TRUE) */
            SWCTRL_MirrorEntry_T mirroring_entry;


#if (SYS_CPNT_ACL_MIRROR == TRUE)
            {
                UI32_T  acl_dest_port;
                UI32_T  acl_index;
                RULE_TYPE_UI_AclEntry_T acl_entry;
                UI32_T  mirror_type;

                acl_dest_port = ifindex;
                acl_index = 0;
                while (RULE_TYPE_OK == L4_PMGR_ACL_GetNextRunningAclMirrorEntry(&acl_dest_port, &acl_index, &mirror_type, &acl_entry) )
                {
                    if (acl_dest_port == ifindex)
                    {
                        switch(mirror_type)
                        {
                            case VAL_aclMirrorType_rx:
                                APPEND_RUNNING_CFG_1(" port monitor access-list %s rx\n", acl_entry.acl_name);
                                break;
                            case VAL_aclMirrorType_tx:
                                APPEND_RUNNING_CFG_1(" port monitor access-list %s tx\n", acl_entry.acl_name);
                                break;
                            case VAL_aclMirrorType_both:
                                APPEND_RUNNING_CFG_1(" port monitor access-list %s both\n", acl_entry.acl_name);
                                break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
           }
#endif /* #if (SYS_CPNT_ACL_MIRROR == TRUE) */


            memset(&mirroring_entry , 0 , sizeof(SWCTRL_MirrorEntry_T));

            //pttch //* change to getrunning */
            while (SWCTRL_POM_GetNextMirrorEntry(&mirroring_entry))
            {
                UI32_T unit     = 0;
                UI32_T port     = 0;
                UI32_T trunk_id = 0;

#if (CLI_SUPPORT_PORT_NAME == 1)
                {
                    UI8_T name[MAXSIZE_ifName+1] = {0};
                    if (mirroring_entry.mirror_destination_port == ifindex)
                    {
                        CLI_LIB_Ifindex_To_Name(mirroring_entry.mirror_source_port,name);
                        switch(mirroring_entry.mirror_type)
                        {
                            case VAL_mirrorType_rx:
                                APPEND_RUNNING_CFG_1(" port monitor ethernet %s rx\n",name);
                                break;

                            case VAL_mirrorType_tx:
                                APPEND_RUNNING_CFG_1(" port monitor ethernet %s tx\n",name);
                                break;

                            case VAL_mirrorType_both:
                                APPEND_RUNNING_CFG_1(" port monitor ethernet %s both\n",name);
                                break;

                            default:
                                break;
                        }
                    }
                }
#else
                if (mirroring_entry.mirror_destination_port == ifindex)
                {
                    SWCTRL_POM_LogicalPortToUserPort(mirroring_entry.mirror_source_port,&unit,&port,&trunk_id);
                    switch(mirroring_entry.mirror_type)
                    {
                        case VAL_mirrorType_rx:
                            APPEND_RUNNING_CFG_2(" port monitor ethernet %lu/%lu rx\n",(unsigned long)unit,(unsigned long)port);
                            break;

                        case VAL_mirrorType_tx:
                            APPEND_RUNNING_CFG_2(" port monitor ethernet %lu/%lu tx\n",(unsigned long)unit,(unsigned long)port);
                            break;

                        case VAL_mirrorType_both:
                            APPEND_RUNNING_CFG_2(" port monitor ethernet %lu/%lu both\n",(unsigned long)unit,(unsigned long)port);
                            break;

                        default:
                            break;
                    }
                }
#endif
            }
#if (SYS_CPNT_VLAN_MIRROR == TRUE)

            memset(&vlan_mirror_entry , 0 , sizeof(SWCTRL_VlanMirrorEntry_T));
            /* get next entry by ifindex port */
            vlan_mirror_entry.mirror_dest_port = ifindex;
            vlan_mirror_entry.mirror_source_vlan = 0;

            /* get next vlan mirror entry */
            while (SWCTRL_PMGR_GetNextVlanMirrorEntry(&vlan_mirror_entry))
            {
                APPEND_RUNNING_CFG_1(" port monitor vlan %lu\n", (unsigned long)vlan_mirror_entry.mirror_source_vlan);
            }
#endif /* End of #if (SYS_CPNT_VLAN_MIRROR == TRUE) */
#if (SYS_CPNT_MAC_BASED_MIRROR == TRUE)

            /* get mac-address dest_port */
            SWCTRL_POM_GetVlanAndMacMirrorDestPort(&mac_dest_port);

            if ((ifindex == mac_dest_port) && (mac_dest_port !=0))
            {
                memset(&mac_addr_entry , 0 , sizeof(SWCTRL_MacAddrMirrorEntry_T));
                /* first mac-address index entry shall be 0 */
                mac_addr_entry.addr_entry_index = 0;

                /* get next mac-addressmirror entry */
                while (SWCTRL_POM_GetNextMacAddrMirrorEntry(&mac_addr_entry))
                {
                    APPEND_RUNNING_CFG_4(" port monitor mac-address %02x-%02x-%02x-%02x",
                                           mac_addr_entry.mac_addr[0],
                                           mac_addr_entry.mac_addr[1],
                                           mac_addr_entry.mac_addr[2],
                                           mac_addr_entry.mac_addr[3]);
                    APPEND_RUNNING_CFG_2("-%02x-%02x\n",
                                           mac_addr_entry.mac_addr[4],
                                           mac_addr_entry.mac_addr[5]);
                }
             }
#endif /* End of #if (SYS_CPNT_MAC_BASED_MIRROR == TRUE) */


        }/*end of port monitor*/

#if (SYS_CPNT_PORT_SECURITY == TRUE)
#if (CLI_SUPPORT_PSEC_MAC_COUNT == 1)
        /*port sercrity*/
        {
            UI32_T port_security_status = 0;
            UI32_T mac_count = 0;

            if (PSEC_PMGR_GetRunningPortSecurityMacCount(ifindex, &mac_count) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_1(" port security max-mac-count %lu\n",(unsigned long)mac_count);
            }

            if (PSEC_PMGR_GetRunningPortSecurityStatus(ifindex, &port_security_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if (port_security_status == VAL_portSecPortStatus_enabled)
                {
                    APPEND_RUNNING_CFG_0(" port security\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no port security\n");
                }
            }
        }
#if (SYS_CPNT_INTRUSION_MSG_TRAP == TRUE)
        /*port security action*/
        {
            UI32_T  action_status;

            if (PSEC_PMGR_GetRunningPortSecurityActionStatus(ifindex, &action_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                switch(action_status)
                {
                    case VAL_portSecAction_none:
                        APPEND_RUNNING_CFG_0(" no port security action\n");
                        break;

                    case VAL_portSecAction_trap:
                        APPEND_RUNNING_CFG_0(" port security action trap\n");
                        break;

                    case VAL_portSecAction_shutdown:
                        APPEND_RUNNING_CFG_0(" port security action shutdown\n");
                        break;

                    case VAL_portSecAction_trapAndShutdown:
                        APPEND_RUNNING_CFG_0(" port security action trap-and-shutdown\n");
                        break;

                    default:
                        break;
                }
            }
        } /*end - port security action*/

#endif
#else /*#if (CLI_SUPPORT_PSEC_MAC_COUNT != 1)*/
        /*port security*/
        {
            UI32_T port_security_status = 0;

            if (PSEC_PMGR_GetRunningPortSecurityStatus( ifindex, &port_security_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if (port_security_status == VAL_portSecPortStatus_enabled)
                {
                    APPEND_RUNNING_CFG_0(" port security\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no port security\n");
                }
            }
        }

#if (SYS_CPNT_INTRUSION_MSG_TRAP == TRUE)
        /*port security action*/
        {
            UI32_T  action_status;

            if (PSEC_PMGR_GetRunningPortSecurityActionStatus(ifindex, &action_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                switch(action_status)
                {
                    case VAL_portSecAction_none:
                        APPEND_RUNNING_CFG_0(" no port security action\n");
                        break;

                    case VAL_portSecAction_trap:
                        APPEND_RUNNING_CFG_0(" port security action trap\n");
                        break;

                    case VAL_portSecAction_shutdown:
                        APPEND_RUNNING_CFG_0(" port security action shutdown\n");
                        break;

                    case VAL_portSecAction_trapAndShutdown:
                        APPEND_RUNNING_CFG_0(" port security action trap-and-shutdown\n");
                        break;

                    default:
                        break;
                }
            }
        }
#endif /*#if (SYS_CPNT_INTRUSION_MSG_TRAP == TRUE)*/
#endif /*#if (CLI_SUPPORT_PSEC_MAC_COUNT == 1)*/
#endif /*#if (SYS_CPNT_PORT_SECURITY == TRUE)*/


        /*switchport broadcast*/
        {
            if ((port_info.bsctrl_state_changed == TRUE) || (port_info.bcast_rate_limit_changed == TRUE))
            {
                if (port_info.bsctrl_state == VAL_bcastStormStatus_disabled)
                {
                    APPEND_RUNNING_CFG_0(" no switchport broadcast\n");
                }
                else
                {
                    switch(port_info.bcast_rate_mode)
                    {
                        case VAL_bcastStormSampleType_pkt_rate:
                            if (port_info.bcast_rate_limit_changed == TRUE)
                            {

#if defined(STRAWMAN)
                                APPEND_RUNNING_CFG_1(" switchport broadcast threshold level %lu\n", (unsigned long)port_info.bcast_rate_limit);
#else
                                APPEND_RUNNING_CFG_1(" switchport broadcast packet-rate %lu\n", (unsigned long)port_info.bcast_rate_limit);
#endif

                            }
                            break;

                        case VAL_bcastStormSampleType_octet_rate:
                            if (port_info.bcast_rate_limit_changed == TRUE)
                            {
                                APPEND_RUNNING_CFG_1(" switchport broadcast packet-rate %lu\n", (unsigned long)port_info.bcast_rate_limit);
                            }
                            break;

                        case VAL_bcastStormSampleType_percent:
                            if (port_info.bcast_rate_limit_changed == TRUE)
                            {
                                APPEND_RUNNING_CFG_1(" switchport broadcast packet-rate %lu\n", (unsigned long)port_info.bcast_rate_limit);
                            }
                            break;

                        default:
                            break;
                    }
                }
            }
        }

#if (SYS_CPNT_STORM_MODE & SYS_CPNT_STORM_MSTORM)
        /*switchport multicast*/
        if (SYS_DFLT_MCAST_STORM_STATUS == VAL_mcastStormStatus_enabled)
        {
            if ((port_info.msctrl_state_changed == TRUE) || (port_info.mcast_rate_limit_changed == TRUE))
            {
                if (port_info.msctrl_state == VAL_mcastStormStatus_enabled)
                {
                    switch(port_info.mcast_rate_mode)
                    {
                        case VAL_mcastStormSampleType_pkt_rate:
                            if (port_info.mcast_rate_limit_changed == TRUE)
                            {
#if defined(STRAWMAN)
                                APPEND_RUNNING_CFG_1(" switchport multicast threshold level %lu\n", (unsigned long)port_info.mcast_rate_limit);
#else
                                APPEND_RUNNING_CFG_1(" switchport multicast packet-rate %lu\n", (unsigned long)port_info.mcast_rate_limit);
#endif
                            }
                            break;

                        case VAL_mcastStormSampleType_octet_rate:
                            if (port_info.mcast_rate_limit_changed == TRUE)
                            {
                                APPEND_RUNNING_CFG_1(" switchport multicast packet-rate %lu\n", (unsigned long)port_info.mcast_rate_limit);
                            }
                            break;

                        case VAL_mcastStormSampleType_percent:
                            if (port_info.mcast_rate_limit_changed == TRUE)
                            {
                                APPEND_RUNNING_CFG_1(" switchport multicast packet-rate %lu\n", (unsigned long)port_info.mcast_rate_limit);
                            }
                            break;

                        default:
                            break;
                     }
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no switchport multicast\n");
                }
            }
        }
        else
        {
            if(port_info.msctrl_state == VAL_mcastStormStatus_enabled)
            {
#if defined(STRAWMAN)
                APPEND_RUNNING_CFG_1(" switchport multicast threshold level %lu\n", (unsigned long)port_info.mcast_rate_limit);
#else
                APPEND_RUNNING_CFG_1(" switchport multicast packet-rate %lu\n", (unsigned long)port_info.mcast_rate_limit);
#endif
            }
        }
#endif /*#if (SYS_CPNT_STORM_MODE & SYS_CPNT_STORM_MSTORM)*/

#if (SYS_CPNT_STORM_MODE & SYS_CPNT_STORM_UNKNOWN_USTORM)
        /*switchport unknown-unicast*/
        if (SYS_DFLT_UNKUCAST_STORM_STATUS == VAL_unknownUcastStormStatus_enabled)
        {
            if ((port_info.unknown_usctrl_state_changed == TRUE) || (port_info.unknown_ucast_rate_limit_changed == TRUE))
            {
                if (port_info.unknown_usctrl_state == VAL_unknownUcastStormStatus_enabled)
                {
                    switch(port_info.unknown_ucast_rate_mode)
                    {
                        case VAL_unknownUcastStormSampleType_packet_rate:
                            if (port_info.unknown_ucast_rate_limit_changed == TRUE)
                            {
#if defined(STRAWMAN)
                                APPEND_RUNNING_CFG_1(" switchport unknown-unicast threshold level %lu\n", (unsigned long)port_info.unknown_ucast_rate_limit);
#else
                                APPEND_RUNNING_CFG_1(" switchport unknown-unicast packet-rate %lu\n", (unsigned long)port_info.unknown_ucast_rate_limit);
#endif
                            }
                            break;

                        case VAL_unknownUcastStormSampleType_octet_rate:
                            if (port_info.unknown_ucast_rate_limit_changed == TRUE)
                            {
                                APPEND_RUNNING_CFG_1(" switchport unknown-unicast packet-rate %lu\n", (unsigned long)port_info.unknown_ucast_rate_limit);
                            }
                            break;

                        case VAL_unknownUcastStormSampleType_percent:
                            if (port_info.unknown_ucast_rate_limit_changed == TRUE)
                            {
                                APPEND_RUNNING_CFG_1(" switchport unknown-unicast packet-rate %lu\n", (unsigned long)port_info.unknown_ucast_rate_limit);
                            }
                            break;

                        default:
                            break;
                    }
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no switchport unknown-unicast\n");
                }
            }
        }
        else
        {
            if(port_info.unknown_usctrl_state == VAL_unknownUcastStormStatus_enabled)
            {
#if defined(STRAWMAN)
                APPEND_RUNNING_CFG_1(" switchport unknown-unicast threshold level %lu\n", (unsigned long)port_info.unknown_ucast_rate_limit);
#else
                APPEND_RUNNING_CFG_1(" switchport unknown-unicast packet-rate %lu\n", (unsigned long)port_info.unknown_ucast_rate_limit);
#endif
            }
        }
#endif /*#if (SYS_CPNT_STORM_MODE & SYS_CPNT_STORM_UNKNOWN_USTORM)*/

#if (SYS_CPNT_RATE_BASED_STORM_CONTROL == TRUE) /*LinkSys ASF4506B rate base storm control*/
{
    UI32_T s_rate;
    UI32_T storm_type;

    if(SWCTRL_POM_GetRunningRateBasedStormControlRate(ifindex, &s_rate)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        APPEND_RUNNING_CFG_1(" switchport storm-rate bit-rate-in-kilo %lu\n", (unsigned long)s_rate);
    }

    if(SWCTRL_POM_GetRunningRateBasedStormControlMode(ifindex, &storm_type)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if(storm_type & 4) /*binary 4=100*/
        {
            APPEND_RUNNING_CFG_0(" switchport unknown-unicast\n");
        }
        else
        {
            APPEND_RUNNING_CFG_0(" no switchport unknown-unicast\n");
        }

       if(storm_type & 2) /*binary 2=010*/
       {
            APPEND_RUNNING_CFG_0(" switchport multicast\n");
        }
        else
        {
            APPEND_RUNNING_CFG_0(" no switchport multicast\n");
        }

       if(storm_type & 1) /*binary 1=001*/
       {
            APPEND_RUNNING_CFG_0(" switchport broadcast\n");
        }
        else
        {
            APPEND_RUNNING_CFG_0(" no switchport broadcast\n");
        }
    }
}
#endif

#if (SYS_CPNT_INGRESS_RATE_LIMIT == TRUE)
        if (port_info.ingress_rate_limit_changed)
        {
#ifdef SYS_ADPT_UI_RATE_LIMIT_FACTOR
            APPEND_RUNNING_CFG_1(" rate-limit input %lu\n", (unsigned long)port_info.ingress_rate_limit/SYS_ADPT_UI_RATE_LIMIT_FACTOR);
#else
            APPEND_RUNNING_CFG_1(" rate-limit input %lu\n", (unsigned long)port_info.ingress_rate_limit/1000);
#endif

            if (port_info.ingress_rate_limit_status == VAL_rlPortInputStatus_disabled)
            {
                APPEND_RUNNING_CFG_0(" no rate-limit input\n");
            }
        }
        else if (port_info.ingress_rate_limit_status != SYS_DFLT_INGRESS_RATE_LIMIT_STATUS)
        {
            if (port_info.ingress_rate_limit_status == VAL_rlPortInputStatus_disabled)
            {
                APPEND_RUNNING_CFG_0(" no rate-limit input\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" rate-limit input\n");
            }
        }
#endif

#if (SYS_CPNT_EGRESS_RATE_LIMIT == TRUE)
        if (port_info.egress_rate_limit_changed)
        {
#ifdef SYS_ADPT_UI_RATE_LIMIT_FACTOR
            APPEND_RUNNING_CFG_1(" rate-limit output %lu\n", (unsigned long)port_info.egress_rate_limit/SYS_ADPT_UI_RATE_LIMIT_FACTOR);
#else
            APPEND_RUNNING_CFG_1(" rate-limit output %lu\n", (unsigned long)port_info.egress_rate_limit/1000);
#endif

            if (port_info.egress_rate_limit_status == VAL_rlPortOutputStatus_disabled)
            {
                APPEND_RUNNING_CFG_0(" no rate-limit output\n");
            }
        }
        else if (port_info.egress_rate_limit_status != SYS_DFLT_EGRESS_RATE_LIMIT_STATUS)
        {
            if (port_info.egress_rate_limit_status == VAL_rlPortOutputStatus_disabled)
            {
                APPEND_RUNNING_CFG_0(" no rate-limit output\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" rate-limit output\n");
            }
        }
#endif

    } /*end end of switch control*/

    /*switchport priority*/
    {
        UI32_T temp_ifindex = 0;
        PRI_MGR_PortPriority_RunningCfg_T port_cfg;
        memset(&port_cfg , 0 , sizeof(PRI_MGR_PortPriority_RunningCfg_T));

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

        if (PRI_PMGR_GetRunningPortPriorityParameters(ifindex,&port_cfg) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (port_cfg.user_priority_changed == TRUE)
            {
                APPEND_RUNNING_CFG_1(" switchport priority default %lu\n",(unsigned long)port_cfg.default_user_priority );
            }
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }
    }
#if (SYS_CPNT_DAI == TRUE)
    {
        UI8_T status;
        UI32_T rate_limit;
        UI32_T lport_ifindex = ifindex;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            lport_ifindex = trunk_ifindex;
        }

        if (DAI_PMGR_GetPortTrustStatus(lport_ifindex, &status) == DAI_TYPE_OK)
        {
            if (status == DAI_TYPE_PORT_TRUSTED)
            {
                APPEND_RUNNING_CFG_0( " ip arp inspection trust\n");
            }
        }

        if (DAI_PMGR_GetPortRateLimit(lport_ifindex, &rate_limit) == DAI_TYPE_OK
            && DAI_TYPE_PORT_RATE_LIMIT_DEFAULT != rate_limit)
        {
            if (rate_limit == DAI_TYPE_PORT_RATE_LIMIT_UNLIMITED)
            {
                APPEND_RUNNING_CFG_0( " ip arp inspection limit none\n");
            }
            else
            {
                APPEND_RUNNING_CFG_1(" ip arp inspection limit rate %lu\n",(unsigned long)rate_limit);
            }
        }

    }
#endif/*#if (SYS_CPNT_DAI == TRUE)*/

    /* lldp notification */
#if (SYS_CPNT_LLDP == TRUE)
{
    UI32_T temp_ifindex = 0;

    if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
    {
        temp_ifindex = ifindex;
        ifindex = trunk_ifindex;
    }

    /* lldp notification */
    {
        BOOL_T  notify_enable;

        if (LLDP_POM_GetRunningPortNotificationEnable(ifindex, &notify_enable) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (notify_enable == VAL_lldpPortConfigNotificationEnable_true)
            {
                APPEND_RUNNING_CFG_0(" lldp notification\n");
            }
            else if (notify_enable == VAL_lldpPortConfigNotificationEnable_false)
            {
                APPEND_RUNNING_CFG_0(" no lldp notification\n");
            }
        }
    }

    /* lldp admin-status */
    {
        UI8_T admin_status;

        if (LLDP_POM_GetRunningPortAdminStatus(ifindex, &admin_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (admin_status == VAL_lldpPortConfigAdminStatus_disabled)
            {
                APPEND_RUNNING_CFG_0(" no lldp admin-status\n");
            }
            else if (admin_status == VAL_lldpPortConfigAdminStatus_txOnly)
            {
                APPEND_RUNNING_CFG_0(" lldp admin-status tx-only\n");
            }
            else if (admin_status == VAL_lldpPortConfigAdminStatus_rxOnly)
            {
                APPEND_RUNNING_CFG_0(" lldp admin-status rx-only\n");
            }
            else if (admin_status == VAL_lldpPortConfigAdminStatus_txAndRx)
            {
                APPEND_RUNNING_CFG_0(" lldp admin-status tx-rx\n");
            }
        }
    }


    /* lldp basic-tlv */
    {
        UI8_T   basic_tlvs_tx_flag = 0;
        UI8_T   basic_tlvs_change_flag = 0;
        UI8_T   enabled = 0;

        if (LLDP_POM_GetRunningPortBasicTlvTransfer(ifindex, &basic_tlvs_tx_flag, &basic_tlvs_change_flag) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (basic_tlvs_change_flag & LLDP_TYPE_TX_PORT_DESC_TLV)
            {
                if (basic_tlvs_tx_flag & LLDP_TYPE_TX_PORT_DESC_TLV)
                {
                    APPEND_RUNNING_CFG_0(" lldp basic-tlv port-description\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp basic-tlv port-description\n");
                }
            }

            if (basic_tlvs_change_flag & LLDP_TYPE_TX_SYS_NAME_TLV)
            {
                if (basic_tlvs_tx_flag & LLDP_TYPE_TX_SYS_NAME_TLV)
                {
                    APPEND_RUNNING_CFG_0(" lldp basic-tlv system-name\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp basic-tlv system-name\n");
                }
            }

            if (basic_tlvs_change_flag & LLDP_TYPE_TX_SYS_DESC_TLV)
            {
                if (basic_tlvs_tx_flag & LLDP_TYPE_TX_SYS_DESC_TLV)
                {
                    APPEND_RUNNING_CFG_0(" lldp basic-tlv system-description\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp basic-tlv system-description\n");
                }
            }

            if (basic_tlvs_change_flag & LLDP_TYPE_TX_SYS_CAP_TLV)
            {
                if (basic_tlvs_tx_flag & LLDP_TYPE_TX_SYS_CAP_TLV)
                {
                    APPEND_RUNNING_CFG_0(" lldp basic-tlv system-capabilities\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp basic-tlv system-capabilities\n");
                }
            }
        }
        if (LLDP_POM_GetRunningPortManAddrTlvTransfer(ifindex, &enabled) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (enabled)
            {
                APPEND_RUNNING_CFG_0(" lldp basic-tlv management-ip-address\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no lldp basic-tlv management-ip-address\n");
            }
        }
    }

    #if (SYS_CPNT_LLDP_EXT == TRUE)
    {
        LLDP_MGR_Xdot1ConfigEntry_T     xdot1_config_entry;
        LLDP_MGR_Xdot3PortConfigEntry_T xdot3_port_config_entry;

        memset(&xdot1_config_entry, 0, sizeof(LLDP_MGR_Xdot1ConfigEntry_T));
        memset(&xdot3_port_config_entry, 0, sizeof(LLDP_MGR_Xdot3PortConfigEntry_T));
        xdot1_config_entry.lport = ifindex;
        xdot3_port_config_entry.lport = ifindex;

        if (LLDP_POM_GetRunningXdot1ConfigEntry(&xdot1_config_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (xdot1_config_entry.port_vlan_tx_changed == TRUE)
            {
                if (xdot1_config_entry.port_vlan_tx_enable == VAL_lldpXdot1ConfigPortVlanTxEnable_true)
                {
                    APPEND_RUNNING_CFG_0(" lldp dot1-tlv pvid\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp dot1-tlv pvid\n");
                }
            }

            if (xdot1_config_entry.vlan_name_tx_changed == TRUE)
            {
                if (xdot1_config_entry.vlan_name_tx_enable == VAL_lldpXdot1ConfigVlanNameTxEnable_true)
                {
                    APPEND_RUNNING_CFG_0(" lldp dot1-tlv vlan-name\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp dot1-tlv vlan-name\n");
                }
            }

            if (xdot1_config_entry.proto_vlan_tx_changed == TRUE)
            {
                if (xdot1_config_entry.proto_vlan_tx_enable == VAL_lldpXdot1ConfigProtoVlanTxEnable_true)
                {
                    APPEND_RUNNING_CFG_0(" lldp dot1-tlv proto-vid\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp dot1-tlv proto-vid\n");
                }
            }

            if (xdot1_config_entry.protocol_tx_changed == TRUE)
            {
                if (xdot1_config_entry.protocol_tx_enable == VAL_lldpXdot1ConfigProtocolTxEnable_true)
                {
                    APPEND_RUNNING_CFG_0(" lldp dot1-tlv proto-ident\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp dot1-tlv proto-ident\n");
                }
            }

            if (xdot1_config_entry.cn_tx_changed == TRUE)
            {
                if (xdot1_config_entry.cn_tx_enable == TRUE)
                {
                    APPEND_RUNNING_CFG_0(" lldp dot1-tlv cn\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp dot1-tlv cn\n");
                }
            }
        }

        if (LLDP_POM_GetRunningXdot3PortConfigEntry(&xdot3_port_config_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (xdot3_port_config_entry.tlvs_tx_changed & LLDP_TYPE_XDOT3_MAC_PHY_TLV_TX)
            {
                if (xdot3_port_config_entry.tlvs_tx_enable & LLDP_TYPE_XDOT3_MAC_PHY_TLV_TX)
                {
                    APPEND_RUNNING_CFG_0(" lldp dot3-tlv mac-phy\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp dot3-tlv mac-phy\n");
                }
            }

            if (xdot3_port_config_entry.tlvs_tx_changed & LLDP_TYPE_XDOT3_POWER_VIA_MDI_TX)
            {
                if (xdot3_port_config_entry.tlvs_tx_enable & LLDP_TYPE_XDOT3_POWER_VIA_MDI_TX)
                {
                    APPEND_RUNNING_CFG_0(" lldp dot3-tlv poe\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp dot3-tlv poe\n");
                }
            }

            if (xdot3_port_config_entry.tlvs_tx_changed & LLDP_TYPE_XDOT3_LINK_AGG_TX)
            {
                if (xdot3_port_config_entry.tlvs_tx_enable & LLDP_TYPE_XDOT3_LINK_AGG_TX)
                {
                    APPEND_RUNNING_CFG_0(" lldp dot3-tlv link-agg\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp dot3-tlv link-agg\n");
                }
            }

            if (xdot3_port_config_entry.tlvs_tx_changed & LLDP_TYPE_XDOT3_MAX_FRAME_SIZE_TLV)
            {
                if (xdot3_port_config_entry.tlvs_tx_enable & LLDP_TYPE_XDOT3_MAX_FRAME_SIZE_TLV)
                {
                    APPEND_RUNNING_CFG_0(" lldp dot3-tlv max-frame\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp dot3-tlv max-frame\n");
                }
            }
        }
    }
    #endif  /* #if (SYS_CPNT_LLDP_EXT == TRUE) */

    #if(SYS_CPNT_LLDP_MED == TRUE)
    /* lldp medTlv */
    {
        UI16_T  tlvs_tx_enabled;
        UI16_T  tlvs_tx_changed;

        if (LLDP_PMGR_GetRunningXMedPortConfigTlvsTx(ifindex, &tlvs_tx_enabled) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            tlvs_tx_changed = tlvs_tx_enabled ^ LLDP_TYPE_DEFAULT_MED_TX;

            if (tlvs_tx_changed & LLDP_TYPE_MED_CAP_TX)
            {
                if (tlvs_tx_enabled & LLDP_TYPE_MED_CAP_TX)
                {
                    APPEND_RUNNING_CFG_0(" lldp med-tlv med-cap\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp med-tlv med-cap\n");
                }
            }

            if (tlvs_tx_changed & LLDP_TYPE_MED_NETWORK_POLICY_TX)
            {
                if (tlvs_tx_enabled & LLDP_TYPE_MED_NETWORK_POLICY_TX)
                {
                    APPEND_RUNNING_CFG_0(" lldp med-tlv network-policy\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp med-tlv network-policy\n");
                }
            }

            if (tlvs_tx_changed & LLDP_TYPE_MED_LOCATION_IDENT_TX)
            {
                if (tlvs_tx_enabled & LLDP_TYPE_MED_LOCATION_IDENT_TX)
                {
                    APPEND_RUNNING_CFG_0(" lldp med-tlv location\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp med-tlv location\n");
                }
            }

            if ((tlvs_tx_changed & LLDP_TYPE_MED_EXT_PSE_TX) || (tlvs_tx_changed & LLDP_TYPE_MED_EXT_PD_TX))
            {
                if ((tlvs_tx_enabled & LLDP_TYPE_MED_EXT_PSE_TX) || (tlvs_tx_enabled & LLDP_TYPE_MED_EXT_PD_TX))
                {
                    APPEND_RUNNING_CFG_0(" lldp med-tlv ext-poe\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp med-tlv ext-poe\n");
                }
            }

            if (tlvs_tx_changed & LLDP_TYPE_MED_INVENTORY_TX)
            {
                if (tlvs_tx_enabled & LLDP_TYPE_MED_INVENTORY_TX)
                {
                    APPEND_RUNNING_CFG_0(" lldp med-tlv inventory\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp med-tlv inventory\n");
                }
            }
        }
    }

    /* lldp medNotification */
    {
        UI8_T  enabled;

        if (LLDP_PMGR_GetRunningXMedPortNotification(ifindex, &enabled) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (enabled == VAL_lldpXMedPortConfigNotifEnable_true)
            {
                APPEND_RUNNING_CFG_0(" lldp med-notification\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no lldp med-notification\n");
            }
        }
    }

    /*lldp medLocation*/
    {
        BOOL_T status;

        /*civic address*/
        LLDP_MGR_XMedLocationCivicAddrCaEntry_T ca_entry;
        UI8_T country_code[2], what;

        memset(&ca_entry, 0, sizeof(LLDP_MGR_XMedLocationCivicAddrCaEntry_T));
        if(LLDP_PMGR_GetXMedLocLocationStatus(ifindex, VAL_lldpXMedLocLocationSubtype_civicAddress,&status))
        {
            if(status==TRUE)
            {
                /*Country*/
                if (LLDP_PMGR_GetRunningXMedLocLocationCivicAddrCoutryCode(ifindex, country_code) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    APPEND_RUNNING_CFG_2(" lldp med-location civic-addr country %.*s\n", 2, country_code);
                }

                /*What*/
                if (LLDP_PMGR_GetRunningXMedLocLocationCivicAddrWhat(ifindex, &what)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    APPEND_RUNNING_CFG_1(" lldp med-location civic-addr what %u\n", what);
                }

                /*CA-TYPE 0*/
                if(LLDP_PMGR_Get1stXMedLocLocationCivicAddrCaEntry(ifindex,&ca_entry ))
                {
                    APPEND_RUNNING_CFG_3(" lldp med-location civic-addr %u %.*s\n", ca_entry.ca_type, ca_entry.ca_length, ca_entry.ca_value);
                }

                /*CA-TYPE 1~255*/
                while(LLDP_PMGR_GetNextXMedLocLocationCivicAddrCaEntry(ifindex, &ca_entry))
                {
                    APPEND_RUNNING_CFG_3(" lldp med-location civic-addr %u %.*s\n", ca_entry.ca_type, ca_entry.ca_length, ca_entry.ca_value);
                }
            }
        }
    }
    #endif  /* #if(SYS_CPNT_LLDP_MED == TRUE) */

#if(SYS_CPNT_DCBX == TRUE)
    /* lldp dcbxTlv */
    {
        LLDP_TYPE_XdcbxPortConfigEntry_T  xdcbx_port_config_entry;

        memset(&xdcbx_port_config_entry, 0, sizeof(LLDP_TYPE_XdcbxPortConfigEntry_T));
        xdcbx_port_config_entry.lport = ifindex;
        if (LLDP_PMGR_GetRunningXdcbxPortConfig(&xdcbx_port_config_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (xdcbx_port_config_entry.tlvs_tx_changed & LLDP_TYPE_XDCBX_ETS_CON_TLV_TX)
            {
                if (xdcbx_port_config_entry.tlvs_tx_enable & LLDP_TYPE_XDCBX_ETS_CON_TLV_TX)
                {
                    APPEND_RUNNING_CFG_0(" lldp dcbx-tlv ets-config\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp dcbx-tlv ets-config\n");
                }
            }

            if (xdcbx_port_config_entry.tlvs_tx_changed & LLDP_TYPE_XDCBX_ETS_RECOM_TLV_TX)
            {
                if (xdcbx_port_config_entry.tlvs_tx_enable & LLDP_TYPE_XDCBX_ETS_RECOM_TLV_TX)
                {
                    APPEND_RUNNING_CFG_0(" lldp dcbx-tlv ets-recommend\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp dcbx-tlv ets-recommend\n");
                }
            }

            if (xdcbx_port_config_entry.tlvs_tx_changed & LLDP_TYPE_XDCBX_PFC_CON_TLV_TX)
            {
                if (xdcbx_port_config_entry.tlvs_tx_enable & LLDP_TYPE_XDCBX_PFC_CON_TLV_TX)
                {
                    APPEND_RUNNING_CFG_0(" lldp dcbx-tlv pfc-config\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lldp dcbx-tlv pfc-config\n");
                }
            }

        }
    }
#endif  /* #if(SYS_CPNT_DCBX == TRUE) */

    if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
    {
        ifindex = temp_ifindex;
    }
}
#endif /* #if (SYS_CPNT_LLDP == TRUE) */

#if(SYS_CPNT_DCBX == TRUE)
    {
        UI32_T temp_ifindex = 0;
        BOOL_T pstatus = FALSE;
        UI32_T pmode = 0;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }

        /* dcbx */
        if (DCBX_PMGR_GetRunningPortStatus(ifindex, &pstatus) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (pstatus == TRUE)
            {
                APPEND_RUNNING_CFG_0(" dcbx\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no dcbx\n");
            }
        }

        /* dcbx mode */
        if (DCBX_PMGR_GetRunningPortMode(ifindex, &pmode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (pmode == DCBX_TYPE_PORT_MODE_MANUAL)
            {
                APPEND_RUNNING_CFG_0(" dcbx mode manual\n");
            }
            else if (pmode == DCBX_TYPE_PORT_MODE_CFGSRC)
            {
                APPEND_RUNNING_CFG_0(" dcbx mode config-source\n");
            }
            else if (pmode == DCBX_TYPE_PORT_MODE_AUTOUP)
            {
                APPEND_RUNNING_CFG_0(" dcbx mode auto-up\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" dcbx mode auto-down\n");
            }
        }


        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }
    }
#endif  /* #if(SYS_CPNT_DCBX == TRUE) */
    /* vlan manage*/
    {
        VLAN_TYPE_Vlan_RunningCfg_T vlan_cfg;
        VLAN_TYPE_Vlan_Port_RunningCfg_T vlan_port_cfg;
        UI32_T time_mark = 0;
        UI32_T vid       = 0;
        UI32_T vid_ifindex;
        UI32_T pvid      = 0;
        UI32_T pvid_ifindex;
        VLAN_MGR_Dot1qVlanStaticEntry_T vlan_static_entry;

        char  remove_vlan_1[CLI_DEF_MAX_BUFSIZE] = {0};

        char  vlan_untag_list[(SYS_DFLT_DOT1QMAXVLANID/8)+1] = {0};
        char  vlan_tag_list[(SYS_DFLT_DOT1QMAXVLANID/8)+1] = {0};
        BOOL_T is_untagged = FALSE;
        BOOL_T is_tagged   = FALSE;
        UI32_T temp_ifindex = 0;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

        VLAN_POM_GetVlanPortPvid(ifindex, &pvid_ifindex);
        VLAN_IFINDEX_CONVERTTO_VID(pvid_ifindex, pvid);

        /*switchport allowed*/
        while(VLAN_POM_GetNextVlanId(time_mark, &vid))
        {
            VLAN_VID_CONVERTTO_IFINDEX(vid, vid_ifindex);

            if (VLAN_POM_GetDot1qVlanStaticEntry(vid, &vlan_static_entry) == FALSE)
            {
                continue;
            }

            if (L_CVRT_IS_MEMBER_OF_PORTLIST(vlan_static_entry.dot1q_vlan_static_egress_ports, ifindex))
            {
                if (L_CVRT_IS_MEMBER_OF_PORTLIST(vlan_static_entry.dot1q_vlan_static_untagged_ports, ifindex))
                {
                    if (vid != SYS_DFLT_1Q_PORT_VLAN_PVID)
                    {
                        is_untagged = TRUE;
                        vlan_untag_list[(UI32_T)((vid-1)/8)] |= (1 << (7 - ((vid-1)%8)));
                    }
                }
                else
                {
                    is_tagged = TRUE;
                    vlan_tag_list[(UI32_T)((vid-1)/8)] |= (1 << (7 - ((vid-1)%8)));
                }
            }
            else if (vid == SYS_DFLT_1Q_PORT_VLAN_PVID)
            {
#if (SYS_CPNT_MSTP_SUPPORT_PVST == FALSE)
                SYSFUN_Sprintf(remove_vlan_1, " switchport allowed vlan remove %lu\n", (unsigned long)vid);
#endif
            }
        }/*end of while get next vlan id*/

        /*untagged member add first, tag member must add after untagged command done*/
        {
            if (is_untagged)
            {
                CLI_LIB_Bitmap_To_List(vlan_untag_list,str_list,512*4,SYS_DFLT_DOT1QMAXVLANID,TRUE);
                {
                    /*because must show per line, so spilt the str_list to show */
                    I32_T str_len = strlen((char *)str_list);
                    I32_T process_length = 0;

                    while ((str_len-process_length) > 0)
                    {
                        CLI_Runcfg_ListStrToOneLine(&process_length, 38, str_list, print_str);
#if (SYS_CPNT_MSTP_SUPPORT_PVST ==FALSE)
                        APPEND_RUNNING_CFG_1(" switchport allowed vlan add %s untagged\n",print_str);
#endif
                    }
                }
            }
        }

        memset(&vlan_port_cfg, 0 , sizeof(VLAN_TYPE_Vlan_Port_RunningCfg_T));
        memset(&vlan_cfg, 0 , sizeof(VLAN_TYPE_Vlan_RunningCfg_T));

        if (VLAN_POM_GetRunningVlanPortParameters(ifindex, &vlan_port_cfg) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            /*switchport ingress-filtering */
            if (vlan_port_cfg.ingress_filtering_changed == TRUE)
            {
                if (vlan_port_cfg.port_ingress_filtering == VAL_dot1qPortIngressFiltering_true)
                {
                    APPEND_RUNNING_CFG_0(" switchport ingress-filtering\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no switchport ingress-filtering\n");
                }
            }

            /*switchport native */
            {
                if (vlan_port_cfg.pvid_changed == TRUE)
                {
                    UI32_T native_vid;

                    VLAN_IFINDEX_CONVERTTO_VID(vlan_port_cfg.pvid_index,native_vid);
#if (SYS_CPNT_MSTP_SUPPORT_PVST ==FALSE)
                    APPEND_RUNNING_CFG_1(" switchport native vlan %lu\n", (unsigned long)native_vid);
#endif
                }
            }

#if(SYS_CPNT_VLAN_PROVIDING_DUAL_MODE != TRUE)
            /*switchport acceptable-frame-types*/
            if (vlan_port_cfg.acceptable_frame_types_changed == TRUE)
            {
                if (vlan_port_cfg.port_acceptable_frame_types == VAL_dot1qPortAcceptableFrameTypes_admitAll)
                {
                    APPEND_RUNNING_CFG_0(" switchport acceptable-frame-types all\n");
                }
                else if(vlan_port_cfg.port_acceptable_frame_types == VAL_dot1qPortAcceptableFrameTypes_admitOnlyVlanUnTagged)
                {
                    APPEND_RUNNING_CFG_0(" switchport acceptable-frame-types untagged\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" switchport acceptable-frame-types tagged\n");
                }
            }
#endif

            /*switchport mode */
            if (vlan_port_cfg.vlan_port_mode_changed == TRUE)
            {
                switch(vlan_port_cfg.vlan_port_mode)
                {
                    case VAL_vlanPortMode_hybrid:
                        APPEND_RUNNING_CFG_0(" switchport mode hybrid\n");
                        break;

                    case VAL_vlanPortMode_dot1qTrunk:
                        APPEND_RUNNING_CFG_0(" switchport mode trunk\n");
                        break;

                    case VAL_vlanPortMode_access:
                        APPEND_RUNNING_CFG_0(" switchport mode access\n");
                        break;

                    default:
                        break;
                }
            }

        }

        /*tag member must add after untagged command done*/
        {
            if (is_tagged)
            {
                memset(str_list,0,(512*4));

                CLI_LIB_Bitmap_To_List(vlan_tag_list,str_list,512*4,SYS_DFLT_DOT1QMAXVLANID,TRUE);
                {
                    /*because must show per line, so spilt the str_list to show */
                    I32_T str_len = strlen((char *)str_list);
                    I32_T process_length = 0;

                    memset(print_str,0,(CLI_DEF_MAX_BUFSIZE-38));

                    while ((str_len-process_length) > 0)
                    {
                        CLI_Runcfg_ListStrToOneLine(&process_length, 37, str_list, print_str);
#if (SYS_CPNT_MSTP_SUPPORT_PVST == FALSE)
                        APPEND_RUNNING_CFG_1(" switchport allowed vlan add %s tagged\n",print_str);
#endif
                    }
                }
            }
        }

        /*remove default vlan after specifying another pvid*/
        if (remove_vlan_1[0] != 0)
        {
            APPEND_RUNNING_CFG_0((char *)remove_vlan_1);
        }

        /*switchport forbidden*/
        {
            char  vlan_forbidden_list[(SYS_DFLT_DOT1QMAXVLANID/8)+1] = {0};
            BOOL_T is_forbidden = FALSE;/*to check user have set forbidden list*/
            vid = 0;
            while(VLAN_POM_GetNextVlanId(time_mark, &vid))
            {
                if (VLAN_POM_GetRunningVlanParameters(vid,&vlan_cfg) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    if(vlan_cfg.forbidden_ports_changed == TRUE)
                    {
                        if (vlan_cfg.vlan_forbidden_egress_ports[(UI32_T)((ifindex - 1)/8)] & (1 << ( 7 - (( ifindex - 1) % 8) ) ))
                        {
                            is_forbidden = TRUE;
                            vlan_forbidden_list[(UI32_T)((vid-1)/8)] |= (1 << (7 - ((vid-1)%8)));
                        }
                    }
                }/*end of get vlan parameters*/
            }/*end of while get next vlan id*/

            /*user have set forbidden list*/
            if (is_forbidden)
            {
                memset(str_list,0,(512*4));

                CLI_LIB_Bitmap_To_List(vlan_forbidden_list,str_list,512*4,SYS_DFLT_DOT1QMAXVLANID,TRUE);
                {
                    /*because must show per line, so spilt the str_list to show */
                    I32_T str_len = strlen((char *)str_list);
                    I32_T process_length = 0;

                    memset(print_str,0,(CLI_DEF_MAX_BUFSIZE-38));

                    while ((str_len-process_length) > 0)
                    {
                        CLI_Runcfg_ListStrToOneLine(&process_length, 32, str_list, print_str);
                        APPEND_RUNNING_CFG_1(" switchport forbidden vlan add %s\n",print_str);
                    }
                }
            }
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }

    }/*end of vlan manage*/

#if (SYS_CPNT_VLAN_PROVIDING_DUAL_MODE==TRUE)
    /*Dual-mode*/
    {
        UI32_T vlan_id = 0;
        BOOL_T dual_mode_status;
        UI32_T temp_ifindex = 0;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }

        if(VLAN_PMGR_GetRunningPortDualMode(ifindex,&dual_mode_status,&vlan_id)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(dual_mode_status==TRUE)
            {
                APPEND_RUNNING_CFG_1(" dual-mode %lu\n",vlan_id);
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no dual-mode\n");
            }
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }

    }
#endif

#if (SYS_CPNT_STP == SYS_CPNT_STP_TYPE_RSTP || SYS_CPNT_STP == SYS_CPNT_STP_TYPE_MSTP)
    /*spanning-tree cost*/
    {
        UI32_T cost = 0;
#if (SYS_CPNT_STP == SYS_CPNT_STP_TYPE_RSTP)
        UI32_T mstid = 0;/*for global get or set, use 0 to get information*/
#endif
        UI32_T temp_ifindex = 0;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

#if (SYS_CPNT_STP == SYS_CPNT_STP_TYPE_RSTP)
        if (XSTP_PMGR_GetRunningMstPortPathCost(ifindex, mstid, &cost) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" spanning-tree cost %lu\n",(unsigned long)cost);
        }
#endif
#if (SYS_CPNT_STP == SYS_CPNT_STP_TYPE_MSTP)
        if (XSTP_PMGR_GetRunningPortPathCost(ifindex, &cost) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" spanning-tree cost %lu\n",(unsigned long)cost);
        }
#endif

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }

    }

    /*spanning-tree priority*/
    {
        UI32_T mode = XSTP_TYPE_DEFAULT_STP_VERSION;
        UI32_T priority = 0;
        UI32_T mstid = 0;/*for global get or set, use 0 to get information*/
        UI32_T temp_ifindex = 0;

        XSTP_POM_GetRunningSystemSpanningTreeVersion(&mode);
        if (mode != XSTP_TYPE_MSTP_PROTOCOL_VERSION_ID)
        {
            if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
            {
                temp_ifindex = ifindex;
                ifindex = trunk_ifindex;
            }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

            if (XSTP_POM_GetRunningMstPortPriority(ifindex, mstid, &priority) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_1(" spanning-tree port-priority %lu\n",(unsigned long)priority);
            }

            if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
            {
                ifindex = temp_ifindex;
            }
        }
    }

    /*spanning-tree edge-port*/
    {
        UI32_T mode = 0;
        UI32_T mstid = 0;/*for global get or set, use 0 to get information*/
        UI32_T temp_ifindex = 0;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

        if (XSTP_POM_GetRunningPortAdminEdgePort(ifindex, mstid, &mode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (mode == VAL_staPortAdminEdgePortWithAuto_true)
            {
                APPEND_RUNNING_CFG_0(" spanning-tree edge-port\n");
            }
#if (SYS_CPNT_STP_AUTO_EDGE_PORT == TRUE)
            else if (mode == VAL_staPortAdminEdgePortWithAuto_auto)
            {
                APPEND_RUNNING_CFG_0(" spanning-tree edge-port auto\n");
            }
#endif /* #if (SYS_CPNT_STP_AUTO_EDGE_PORT == TRUE) */
            else
            {
                APPEND_RUNNING_CFG_0(" no spanning-tree edge-port\n");
            }
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }

    }

    /*spanning-tree link-type*/
    {
        UI32_T mode = 0;
        UI32_T mstid = 0;/*for global get or set, use 0 to get information*/
        UI32_T temp_ifindex = 0;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

        if (XSTP_POM_GetRunningPortLinkTypeMode(ifindex, mstid, &mode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            switch(mode)
            {
                case VAL_staPortAdminPointToPoint_forceTrue:
                    APPEND_RUNNING_CFG_0(" spanning-tree link-type point-to-point\n");
                    break;

                case VAL_staPortAdminPointToPoint_forceFalse:
                    APPEND_RUNNING_CFG_0(" spanning-tree link-type shared\n");
                    break;

                case VAL_staPortAdminPointToPoint_auto:
                    APPEND_RUNNING_CFG_0(" spanning-tree link-type auto\n");
                    break;

                default:
                    break;
            }
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }

    }

    /*spanning-tree spanning-disabled*/
    {
        UI32_T spanning_status;
        UI32_T temp_ifindex = 0;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

        if(XSTP_POM_GetRunningPortSpanningTreeStatus(ifindex,&spanning_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(spanning_status == VAL_staPortSystemStatus_enabled)
            {
                APPEND_RUNNING_CFG_0(" no spanning-tree spanning-disabled\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" spanning-tree spanning-disabled\n");
            }
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }
    }

#if (SYS_CPNT_STP_ROOT_GUARD == TRUE)
    /*rootguard*/
    {
        UI32_T root_guard_status = 0;
        UI32_T temp_ifindex = 0;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

        if (XSTP_POM_GetRunningPortRootGuardStatus(ifindex, &root_guard_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (root_guard_status == XSTP_TYPE_PORT_ROOT_GUARD_ENABLED)
            {
                APPEND_RUNNING_CFG_0(" spanning-tree root-guard\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no spanning-tree root-guard\n");
            }
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }
    }
#endif /* #if (SYS_CPNT_STP_ROOT_GUARD == TRUE) */

#if (SYS_CPNT_STP_BPDU_GUARD == TRUE)
    /* spanning-tree bpdu-guard */
    {
        UI32_T temp_ifindex = 0;
        UI32_T status = 0;
        UI32_T interval = 0;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }

        if (XSTP_POM_GetRunningPortBpduGuardStatus(ifindex, &status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (status == XSTP_TYPE_PORT_BPDU_GUARD_ENABLED)
            {
                APPEND_RUNNING_CFG_0(" spanning-tree bpdu-guard\n");
            }
            else if (status == XSTP_TYPE_PORT_BPDU_GUARD_DISABLED)
            {
                APPEND_RUNNING_CFG_0(" no spanning-tree bpdu-guard\n");
            }
        }

        if (XSTP_POM_GetRunningPortBPDUGuardAutoRecovery(ifindex, &status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (status == XSTP_TYPE_PORT_BPDU_GUARD_AUTO_RECOVERY_ENABLED)
            {
                APPEND_RUNNING_CFG_0(" spanning-tree bpdu-guard auto-recovery\n");
            }
            else if (status == XSTP_TYPE_PORT_BPDU_GUARD_AUTO_RECOVERY_DISABLED)
            {
                APPEND_RUNNING_CFG_0(" no spanning-tree bpdu-guard auto-recovery\n");
            }
        }

        if (XSTP_POM_GetRunningPortBPDUGuardAutoRecoveryInterval(ifindex, &interval) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" spanning-tree bpdu-guard auto-recovery interval %lu\n", (unsigned long)interval);
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }
    }
#endif /* SYS_CPNT_STP_BPDU_GUARD == TRUE */

#if (SYS_CPNT_STP_BPDU_FILTER == TRUE)
    /* spanning-tree bpdu-filter */
    {
        UI32_T temp_ifindex = 0;
        UI32_T status = 0;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }

        if (XSTP_POM_GetRunningPortBpduFilterStatus(ifindex, &status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (status == XSTP_TYPE_PORT_BPDU_FILTER_ENABLED)
            {
                APPEND_RUNNING_CFG_0(" spanning-tree bpdu-filter\n");
            }
            else if (status == XSTP_TYPE_PORT_BPDU_FILTER_DISABLED)
            {
                APPEND_RUNNING_CFG_0(" no spanning-tree bpdu-filter\n");
            }
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }
    }
#endif /* #if (SYS_CPNT_STP_BPDU_FILTER == TRUE) */

#if (SYS_CPNT_XSTP_TC_PROP_STOP == TRUE)
    {
        UI32_T temp_ifindex = 0;
        BOOL_T status;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == XSTP_POM_GetRunningPortTcPropStop(ifindex, &status))
        {
            if (status)
            {
                APPEND_RUNNING_CFG(" spanning-tree tc-prop-stop\n");
            }
            else
            {
                APPEND_RUNNING_CFG(" no spanning-tree tc-prop-stop\n");
            }
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }
    }
#endif /* #if (SYS_CPNT_XSTP_TC_PROP_STOP == TRUE) */

#if (SYS_CPNT_STP == SYS_CPNT_STP_TYPE_MSTP)
    /*spanning-tree mst instant_id cost priority*/
    {
        UI32_T mode     = XSTP_TYPE_DEFAULT_STP_VERSION;
        UI32_T mstid    = 0;
        UI32_T cost     = 0;
        UI32_T priority = 0;
        UI32_T temp_ifindex = 0;

        XSTP_POM_GetRunningSystemSpanningTreeVersion(&mode);
        if (mode == XSTP_TYPE_MSTP_PROTOCOL_VERSION_ID)
        {
            if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
            {
                temp_ifindex = ifindex;
                ifindex = trunk_ifindex;
            }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

            do
            {
#if (SYS_CPNT_MSTP_SUPPORT_PVST==TRUE)
                if (mstid == 0)
                    continue;
#endif
                if (XSTP_PMGR_GetRunningMstPortPathCost(ifindex, mstid, &cost) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    APPEND_RUNNING_CFG_2(" spanning-tree mst %lu cost %lu\n",(unsigned long)mstid,(unsigned long)cost);
                }
                if (XSTP_POM_GetRunningMstPortPriority(ifindex, mstid, &priority) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    APPEND_RUNNING_CFG_2(" spanning-tree mst %lu port-priority %lu\n",(unsigned long)mstid,(unsigned long)priority);
                }
            }while(XSTP_POM_GetNextExistedInstance(&mstid));

            if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
            {
                ifindex = temp_ifindex;
            }
        }
    }
#endif

#else
    //pttch need to change getrunning by record ???
    /*bridge-group family eth*/
    /*path-cost*/
    {
        UI32_T path_cost = 0;
        UI32_T temp_ifindex = 0;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

        if (STA_PMGR_GetRunningDot1dStpPortPathCost(ifindex,&path_cost) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" bridge-group 1 path-cost %lu\n", (unsigned long)path_cost);
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }

    }
    /*priority*/
    {
        UI32_T priority = 0;
        UI32_T temp_ifindex = 0;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

        if (STA_PMGR_GetRunningDot1dStpPortPriority(ifindex,&priority) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" bridge-group 1 priority %lu\n",(unsigned long)priority);
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }
    }

    /*portfast*/
    {
        UI32_T portfast = 0;
        UI32_T temp_ifindex = 0;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

        if (STA_PMGR_GetRunningStaPortMgtFastForward(ifindex, &portfast) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(portfast == VAL_staPortFastForward_enabled)
            {
                APPEND_RUNNING_CFG_0(" bridge-group 1 portfast\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no bridge-group 1 portfast\n");
            }
        }
        /*spanning-disabled*/
        {
        /* this command will be removed
        * commented by Charles
        */
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }

    }

#endif

    /*map ip port*/
#if (SYS_CPNT_COS_ING_IP_PORT_TO_COS == TRUE)
    {
        UI32_T cos_ifindex;
        I32_T  port        = 65535;/*for guarntee can get the match ifindex information*/
        UI32_T cos         = 0;
        UI32_T return_type = 0;
        UI32_T temp_ifindex= ifindex;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
            cos_ifindex = ifindex - 1;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        else
        {
            cos_ifindex = ifindex - 1;
        }

        while(1)
        {

#if(SYS_CPNT_QOS_V2 == TRUE)
            return_type = L4_PMGR_COS_GetNextRunningPortToCos(&cos_ifindex, (UI16_T *)&port ,&cos);
#else
            return_type = L4_COS_MGR_GetNextRunningPortToCos(&cos_ifindex, (UI16_T *)&port ,&cos);
#endif
            if (cos_ifindex > ifindex || return_type == SYS_TYPE_GET_RUNNING_CFG_FAIL)
                break;
            else if (cos_ifindex < ifindex || return_type == SYS_TYPE_GET_RUNNING_CFG_NO_CHANGE)
                continue;
            else
            {
                APPEND_RUNNING_CFG_2(" map ip port %lu cos %lu\n",(unsigned long)port, (unsigned long)cos);
            }
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }

    }
#endif /* #if (SYS_CPNT_COS_ING_IP_PORT_TO_COS == TRUE) */

    /*map ip dscp*/
#if (SYS_CPNT_COS_CONTAIN_CLI_MAP_IP_DSCP == TRUE)
    {
        UI32_T cos_ifindex;
        UI8_T  dscp         = 255;/*for guarntee can get the match ifindex information*/
        UI32_T cos          = 0;
        UI32_T return_type  = 0;
        UI32_T temp_ifindex= ifindex;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
            cos_ifindex = ifindex - 1;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        else
            cos_ifindex = ifindex - 1;

        while(1)
        {

#if(SYS_CPNT_QOS_V2 == TRUE)
            return_type = L4_PMGR_COS_GetNextRunningDSCPToCos(&cos_ifindex, &dscp ,&cos);
#else
            return_type = L4_COS_PMGR_GetNextRunningDSCPToCos(&cos_ifindex, &dscp ,&cos);
#endif

            if (cos_ifindex > ifindex || return_type == SYS_TYPE_GET_RUNNING_CFG_FAIL)
                break;
            else if (cos_ifindex < ifindex || return_type == SYS_TYPE_GET_RUNNING_CFG_NO_CHANGE)
                continue;
            else
            {
                APPEND_RUNNING_CFG_2(" map ip dscp %d cos %lu\n",dscp,(unsigned long)cos);
            }
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }
    }
#endif /* #if (SYS_CPNT_COS_CONTAIN_CLI_MAP_IP_DSCP == TRUE) */

    /*map ip precedence*/
#if (SYS_CPNT_COS_ING_IP_PRECEDENCE_TO_COS == TRUE)
    {
        UI32_T cos_ifindex;
        UI8_T  ipprecedence = 255;/*for guarntee can get the match ifindex information*/
        UI32_T cos          = 0;
        UI32_T return_type  = 0;
        UI32_T temp_ifindex= ifindex;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
            cos_ifindex  = ifindex - 1;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        else
            cos_ifindex  = ifindex - 1;

        while(1)
        {

#if(SYS_CPNT_QOS_V2 == TRUE)
            return_type = L4_PMGR_COS_GetNextRunningIpPrecedenceToCos(&cos_ifindex, &ipprecedence ,&cos);
#else
            return_type = L4_COS_PMGR_GetNextRunningIpPrecedenceToCos(&cos_ifindex, &ipprecedence ,&cos);
#endif
            if (cos_ifindex > ifindex || return_type == SYS_TYPE_GET_RUNNING_CFG_FAIL)
                break;
            else if (cos_ifindex < ifindex || return_type == SYS_TYPE_GET_RUNNING_CFG_NO_CHANGE)
                continue;
            else
            {
                APPEND_RUNNING_CFG_2(" map ip precedence %d cos %lu\n",ipprecedence,(unsigned long)cos);
            }
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }

    }
#endif /* #if (SYS_CPNT_COS_ING_IP_PRECEDENCE_TO_COS == TRUE) */

    /*queue cos-map*/
#if (SYS_CPNT_COS_ING_COS_TO_QUEUE == TRUE)
    {
        UI8_T queue[SYS_ADPT_MAX_NBR_OF_PRIORITY_QUEUE] = {0};/*bitmap of queue map priority queue[0] is first queue*/
        UI8_T priority[20] = {0};/*store priority string*/
        BOOL_T change[SYS_ADPT_MAX_NBR_OF_PRIORITY_QUEUE] = {0};
        PRI_MGR_TrafficClass_RunningCfg_T traffic_class_cfg;
        UI32_T return_type  = 0;
        UI32_T i = 0;
        UI32_T j = 0;
        UI32_T temp_ifindex= ifindex;
        memset(&traffic_class_cfg, 0, sizeof(PRI_MGR_TrafficClass_RunningCfg_T));
        traffic_class_cfg.lport_ifindex = ifindex - 1;/*brcause have two key , need -1 to get first entry*/
        traffic_class_cfg.dot1d_traffic_class_priority = MAX_dot1dTrafficClassPriority;/*to get first priority of ifindex*/

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        }  //end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)

        while(1)
        {
            return_type = PRI_PMGR_GetNextRunningTrafficClassParameters(&traffic_class_cfg);
            if (traffic_class_cfg.lport_ifindex > ifindex || return_type == SYS_TYPE_GET_RUNNING_CFG_FAIL)
                break;
            else if (traffic_class_cfg.lport_ifindex < ifindex || return_type == SYS_TYPE_GET_RUNNING_CFG_NO_CHANGE)
                continue;
            else
            {
                switch(traffic_class_cfg.dot1d_traffic_class)
                {
                    case 0:
                        change[0] = TRUE;
                        break;

                    case 1:
                        change[1] = TRUE;
                        break;

                    case 2:
                        change[2] = TRUE;
                        break;

                    case 3:
                        change[3] = TRUE;
                        break;

                    case 4:
                        change[4] = TRUE;
                        break;

                    case 5:
                        change[5] = TRUE;
                        break;

                    case 6:
                        change[6] = TRUE;
                        break;

                    case 7:
                        change[7] = TRUE;
                        break;

                    default:
                        break;
                }
            }
        }

        {
            UI32_T lport_ifindex = ifindex - 1;
            UI32_T priority = MAX_dot1dTrafficClassPriority;
            PRI_MGR_Dot1dTrafficClassEntry_T traffic_class_entry;
            memset(&traffic_class_entry,0 , sizeof(PRI_MGR_Dot1dTrafficClassEntry_T));
            while(1)
            {
                if (!PRI_PMGR_GetNextDot1dTrafficClassEntry(&lport_ifindex, &priority, &traffic_class_entry) || lport_ifindex > ifindex)
                    break;
                else if (lport_ifindex < ifindex)
                    continue;
                else
                {
                    switch(traffic_class_entry.dot1d_traffic_class)
                    {
                        case 0:
                            queue[0] |= (1 << traffic_class_entry.dot1d_traffic_class_priority);
                            break;

                        case 1:
                            queue[1] |= (1 << traffic_class_entry.dot1d_traffic_class_priority);
                            break;

                        case 2:
                            queue[2] |= (1 << traffic_class_entry.dot1d_traffic_class_priority);
                            break;

                        case 3:
                            queue[3] |= (1 << traffic_class_entry.dot1d_traffic_class_priority);
                            break;

                        case 4:
                            queue[4] |= (1 << traffic_class_entry.dot1d_traffic_class_priority);
                            break;

                        case 5:
                            queue[5] |= (1 << traffic_class_entry.dot1d_traffic_class_priority);
                            break;

                        case 6:
                            queue[6] |= (1 << traffic_class_entry.dot1d_traffic_class_priority);
                            break;

                        case 7:
                            queue[7] |= (1 << traffic_class_entry.dot1d_traffic_class_priority);
                            break;

                        default:
                            break;
                    }
                }
            }
        }

        for (i = 0;i < SYS_ADPT_MAX_NBR_OF_PRIORITY_QUEUE;i++)
        {
            UI8_T buf[4] = {0};
            memset(priority,0,sizeof(priority));
            if (change[i] == TRUE)
            {
                for (j = 0;j < MAX_dot1dTrafficClassPriority + 1;j++)
                {
                    if (queue[i] & (1 << j))
                    {
                        SYSFUN_Sprintf((char *)buf,"%lu ",j);
                        strcat((char *)priority,(char *)buf);
                        memset(buf,0,sizeof(buf));
                    }
                }
                APPEND_RUNNING_CFG_2(" queue cos-map %lu %s\n",(unsigned long)i,priority);
            }
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }

    }
#endif /* #if (SYS_CPNT_COS_ING_COS_TO_QUEUE == TRUE) */


#if (SYS_CPNT_WRR_Q_MODE_PER_PORT_CTRL == TRUE)
    /*queue mode*/
    {
        UI32_T              mode, l_port, nTrunk;
        BOOL_T              is_inherit =TRUE;
        UI16_T              priority = COS_VM_PRIORITY_USER;
        SWCTRL_Lport_Type_T LportType;

        LportType = SWCTRL_POM_UIUserPortToIfindex(unit_id, port_id, &l_port, &is_inherit);

        /* when this port is unknown port, do nothing,
           when the port is trunk member, we use trunk_id ifindex as key to get value */

        if ( LportType == SWCTRL_LPORT_TRUNK_PORT_MEMBER ) /* trunk member */
        {
            LportType = SWCTRL_POM_UIUserPortToTrunkPort(unit_id,port_id, &nTrunk);

            if ( LportType != SWCTRL_LPORT_UNKNOWN_PORT )
            {
                if ( FALSE == SWCTRL_POM_TrunkIDToLogicalPort (nTrunk, &l_port) )
                {
                    LportType = SWCTRL_LPORT_UNKNOWN_PORT;
                }
            }
        }

        if (TRUE == L4_PMGR_QOS_GetPortPriorityEgressQueueMode(l_port, priority, &mode))
        {
            UI32_T default_mode = COS_VM_SCHEDULING_WEIGHT_ROUND_ROBIN;

            if (mode != default_mode)
            {
                switch (mode)
                {
                    case COS_VM_SCHEDULING_WEIGHT_ROUND_ROBIN:
                        APPEND_RUNNING_CFG_0("queue mode wrr\n");
                        break;
                    case COS_VM_SCHEDULING_STRICT_PRIORITY:
                        APPEND_RUNNING_CFG_0("queue mode strict\n");
                        break;
                    case COS_VM_SCHEDULING_METHOD_DRR:
                        APPEND_RUNNING_CFG_0("queue mode drr\n");
                        break;
                    case COS_VM_SCHEDULING_METHOD_SP_WRR:
                    case COS_VM_SCHEDULING_METHOD_SP_DRR:
                        {
                            UI32_T queue;
                            COS_VM_QUEUE_STRICT_STATUS_T strict_status;

                            if(COS_VM_SCHEDULING_METHOD_SP_WRR == mode)
                            {
                                APPEND_RUNNING_CFG_0("queue mode strict-wrr ");
                            }
                            else if(COS_VM_SCHEDULING_METHOD_SP_WRR == mode)
                            {
                                APPEND_RUNNING_CFG_0("queue mode strict-drr ");
                            }

                            for (queue = 0; queue < SYS_ADPT_MAX_NBR_OF_PRIORITY_QUEUE; ++queue)
                            {
                                if (TRUE == L4_PMGR_QOS_GetPortPriorityEgressQueueStrictStatus(
                                                l_port, priority, queue, &strict_status)
                                    && (strict_status == COS_VM_QUEUE_STRICT_STATUS_ENABLED))
                                {
                                    APPEND_RUNNING_CFG_0("1 ");
                                }
                                else
                                {
                                    APPEND_RUNNING_CFG_0("0 ");
                                }
                            }
                            APPEND_RUNNING_CFG_0("\n");
                        }
                        break;
                }
            }
        }
    }
#endif

#if (SYS_CPNT_WRR_Q_WEIGHT_PER_PORT_CTRL == TRUE)
    {
        UI32_T lport_ifindex;
        UI32_T queue;
        UI32_T weights[SYS_ADPT_MAX_NBR_OF_PRIORITY_QUEUE];
        BOOL_T change = FALSE;

        lport_ifindex = (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
                        ? trunk_ifindex : ifindex;

        for (queue = 0; queue < SYS_ADPT_MAX_NBR_OF_PRIORITY_QUEUE; ++queue)
        {
            SYS_TYPE_Get_Running_Cfg_T result;

            result = L4_PMGR_QOS_GetRunningPortEgressQueueWeight(
                         lport_ifindex, queue, &(weights[queue]));

            if (result == SYS_TYPE_GET_RUNNING_CFG_FAIL)
            {
                change = FALSE;
                break;
            }

            if (result == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                change = TRUE;
            }
        }

        if (change == TRUE)
        {
            APPEND_RUNNING_CFG_0("queue weight ");
            for (queue = 0; queue < SYS_ADPT_MAX_NBR_OF_PRIORITY_QUEUE; queue++)
            {
                APPEND_RUNNING_CFG_1("%lu ", (unsigned long)weights[queue]);
            }
            APPEND_RUNNING_CFG_0("\n");
        }
    }
#endif /* #if (SYS_CPNT_WRR_Q_WEIGHT_PER_PORT_CTRL == TRUE) */

/* starting to set eth 802.1x configuration */

#if (SYS_CPNT_DOT1X == TRUE)
    {
        UI32_T type;
        UI32_T max_req;
        UI32_T mode;
        UI32_T quiet_seconds;
        UI32_T reauth_seconds;
        UI32_T tx_seconds;
        UI32_T temp_ifindex = 0;
#if ((SYS_CPNT_NETACCESS == TRUE) && (SYS_CPNT_NETACCESS_GUEST_VLAN == TRUE))
        UI32_T action_status;
#endif
        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            temp_ifindex = ifindex;
            ifindex = trunk_ifindex;
        } /*end if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)*/

#if ((SYS_CPNT_NETACCESS == TRUE) && (SYS_CPNT_NETACCESS_GUEST_VLAN == TRUE))
        if(NETACCESS_PMGR_GetRunningDot1xPortIntrusionAction(ifindex,&action_status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(action_status == VAL_dot1xAuthConfigExtPortIntrusionAction_block_traffic)
            {
                APPEND_RUNNING_CFG_0(" dot1x intrusion-action block-traffic\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" dot1x intrusion-action guest-vlan\n");
            }
        }
#endif

        if (DOT1X_POM_GetRunning_PortReAuthMax(ifindex, &max_req)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" dot1x max-reauth-req %lu\n", (unsigned long)max_req);
        }

        if(DOT1X_POM_GetRunning_PortMaxReq(ifindex,&max_req)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" dot1x max-req %lu\n",(unsigned long)max_req);
        }

        if(DOT1X_POM_GetRunning_PortReAuthEnabled(ifindex,&mode)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_0(" dot1x re-authentication\n");
        }

        if(DOT1X_POM_GetRunning_PortOperationMode(ifindex,&mode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(mode == DOT1X_PORT_OPERATION_MODE_ONEPASS)
            {
                APPEND_RUNNING_CFG_0(" dot1x operation-mode single-host\n");
            }
            else if(mode == DOT1X_PORT_OPERATION_MODE_MULTIPASS)
            {
                UI32_T count;

                if(DOT1X_POM_GetRunning_PortMultiHostMacCount(ifindex,&count) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    APPEND_RUNNING_CFG_1(" dot1x operation-mode multi-host max-count %ld\n",(long)count);
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" dot1x operation-mode multi-host\n");
                }
            }
#if (SYS_CPNT_DOT1X_MACBASED_AUTH == TRUE)
            else if(mode == DOT1X_PORT_OPERATION_MODE_MACBASED)
            {
                APPEND_RUNNING_CFG_0(" dot1x operation-mode mac-based-auth\n");
            }
#endif /* end of #if (SYS_CPNT_DOT1X_MACBASED_AUTH == TRUE) */
        }

        if(DOT1X_POM_GetRunning_PortControlMode(ifindex,&type)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(type==VAL_dot1xAuthAuthControlledPortControl_forceUnauthorized)
            {
                APPEND_RUNNING_CFG_0(" dot1x port-control force-unauthorized\n");
            }
            else if(type==VAL_dot1xAuthAuthControlledPortControl_forceAuthorized)
            {
                APPEND_RUNNING_CFG_0(" dot1x port-control force-authorized\n");
            }
            else if(type==VAL_dot1xAuthAuthControlledPortControl_auto)
            {
                APPEND_RUNNING_CFG_0(" dot1x port-control auto\n");
            }
        }
#if 1
        if(DOT1X_POM_GetRunning_PortQuietPeriod(ifindex,&quiet_seconds)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" dot1x timeout quiet-period %lu\n",(unsigned long)quiet_seconds);
        }

        if(DOT1X_POM_GetRunning_PortReAuthPeriod(ifindex,&reauth_seconds)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" dot1x timeout re-authperiod %lu\n",(unsigned long)reauth_seconds);
        }

        if(DOT1X_POM_GetRunning_PortTxPeriod(ifindex,&tx_seconds)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" dot1x timeout tx-period %lu\n",(unsigned long)tx_seconds);
        }

        if(DOT1X_POM_GetRunning_AuthSuppTimeout(ifindex,&tx_seconds)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" dot1x timeout supp-timeout %lu\n",(unsigned long)tx_seconds);
        }
#endif

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            ifindex = temp_ifindex;
        }

    }
#endif

#if (SYS_CPNT_ACCOUNTING == TRUE)
        {
            AAA_AccDot1xEntry_T aaa_acc_dot1x_entry;
            memset(&aaa_acc_dot1x_entry ,0 , sizeof(AAA_AccDot1xEntry_T));
            aaa_acc_dot1x_entry.ifindex = ifindex;
            if(AAA_POM_GetRunningAccDot1xEntry(&aaa_acc_dot1x_entry)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_1(" accounting dot1x %s\n",aaa_acc_dot1x_entry.list_name);
            }
        }
#endif /*#if (SYS_CPNT_ACCOUNTING == TRUE)*/

#if (SYS_CPNT_ADD == TRUE)
    {
        {
            UI32_T mode;

            if (ADD_PMGR_GetRunningVoiceVlanPortMode(ifindex, &mode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                switch(mode)
                {
                    case VAL_voiceVlanPortMode_manual:
                         APPEND_RUNNING_CFG_0(" switchport voice vlan manual\n");
                         break;

                    case VAL_voiceVlanPortMode_auto:
                         APPEND_RUNNING_CFG_0(" switchport voice vlan auto\n");
                         break;

                    case VAL_voiceVlanPortMode_none:
                         APPEND_RUNNING_CFG_0(" no switchport voice vlan\n");
                         break;

                    default:
                         break;
                }
            }/*end of ADD_MGR_GetRunningVoiceVlanPortMode*/
        }

    #if (SYS_CPNT_ADD_SUPPORT_LLDP == TRUE)
        {
            UI32_T lldp_state;
            UI32_T oui_state;

            if (ADD_PMGR_GetRunningVoiceVlanPortLldpRuleState(ifindex, &lldp_state) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if (lldp_state == VAL_voiceVlanPortRuleLldp_enabled)
                {
                    APPEND_RUNNING_CFG_0(" switchport voice vlan rule lldp\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no switchport voice vlan rule lldp\n");
                }
            }

            if (ADD_PMGR_GetRunningVoiceVlanPortOuiRuleState(ifindex, &oui_state) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if (oui_state == VAL_voiceVlanPortRuleOui_enabled)
                {
                    APPEND_RUNNING_CFG_0(" switchport voice vlan rule oui\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no switchport voice vlan rule oui\n");
                }
            }
        }
    #endif /*#if (SYS_CPNT_ADD_SUPPORT_LLDP == TRUE)*/

    #if (SYS_CPNT_ADD_CONFIGURABLE_PRIORTIY == TRUE)
        {
            UI8_T priority;

            if (ADD_PMGR_GetRunningVoiceVlanPortPriority(ifindex, &priority) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_1(" switchport voice vlan priority %u \n", priority);
            }
        }
    #endif /*#if (SYS_CPNT_ADD_CONFIGURABLE_PRIORTIY == TRUE)*/

        {
            UI32_T security_state;

            if (ADD_PMGR_GetRunningVoiceVlanPortSecurityState(ifindex, &security_state)== SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if (security_state == VAL_voiceVlanPortSecurity_enabled)
                {
                   APPEND_RUNNING_CFG_0(" switchport voice vlan security\n");
                }
                else
                {
                     APPEND_RUNNING_CFG_0(" no switchport voice vlan security\n");
                }
            }
        }
    }
#endif /* #if (SYS_CPNT_ADD == TRUE) */

#if (SYS_CPNT_VDSL == TRUE)/*---------------------------------------------------------------------------*/
    /* lre */
    {
        VDSLDRV_PORT_CONFIG_T vdsl_default_config;
        VDSLDRV_PORT_CONFIG_T vdsl_current_config;
        UI8_T sz_name[VDSLDRV_MAX_SPEED_PROFILE_NAME_LEN];
        UI32_T broadcom_egress_rate;

        VDSLDRV_get_default_port_config(&vdsl_default_config);

        if (1 == VDSLDRV_get_port_config(i -1, &vdsl_current_config))
        {
            if (vdsl_default_config.m_b_enable_port != vdsl_current_config.m_b_enable_port)
            {
                if (vdsl_current_config.m_b_enable_port == FALSE)
                {
                    APPEND_RUNNING_CFG_0(" lre shutdown\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lre shutdown\n");
                }
            }

            if (vdsl_default_config.m_b_enable_flow_control != vdsl_current_config.m_b_enable_flow_control)
            {
                if (vdsl_current_config.m_b_enable_flow_control == TRUE)
                {
                    /*where to get flow control*/ /*APPEND_RUNNING_CFG_1(" lre flow-control %lu\n",);*///pttch
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lre flow-control\n");
                }
            }

            if (vdsl_default_config.m_n_speed_profile_id != vdsl_current_config.m_n_speed_profile_id)
            {
                if (VDSLDRV_get_speed_profile_name(vdsl_current_config.m_n_speed_profile_id, sz_name))
                {
                    APPEND_RUNNING_CFG_1(" lre profile %s\n", sz_name);
                }
            }

            if (vdsl_default_config.m_b_enable_RDL != vdsl_current_config.m_b_enable_RDL)
            {
                if (vdsl_current_config.m_b_enable_RDL == TRUE)
                {
                    APPEND_RUNNING_CFG_0(" lre rdl\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lre rdl\n");
                }
            }
            if (1 == VDSLDRV_get_broadcom_egress_rate(i -1, &broadcom_egress_rate))
            {
                if (broadcom_egress_rate != 100)
                {
                    APPEND_RUNNING_CFG_1(" lre flow-control %lu\n",(unsigned long)broadcom_egress_rate);
                }
            }
        }
    }
#endif/*-----------------------------------------------------------------------------------*/

/*ACL here*/
#if (SYS_CPNT_COS == TRUE && SYS_CPNT_ACL_UI == TRUE)
    {
        COS_TYPE_AclCosEntry_T cos_entry;
        UI32_T lport = ifindex;
        memset(&cos_entry, 0, sizeof(cos_entry));

#if(SYS_CPNT_QOS_V2 == TRUE)
        while(L4_PMGR_COS_GetNextRunningCosEntry(lport, &cos_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
#else
        while(L4_COS_PMGR_GetNextRunningCosEntry(lport, &cos_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
#endif
        {
#if (SYS_CPNT_QOS_V2 == TRUE)
            if (cos_entry.acl_type == RULE_TYPE_IP_ACL)
#else
            if (cos_entry.acl_type == ACL_IP_ACL)
#endif
            {
                APPEND_RUNNING_CFG_2(" map access-list ip %s cos %lu\n",cos_entry.acl_name ,(unsigned long)cos_entry.cos);
            }
            else
            {
                APPEND_RUNNING_CFG_2(" map access-list mac %s cos %lu\n",cos_entry.acl_name ,(unsigned long)cos_entry.cos);
            }
        }
    }
#endif /* #if (SYS_CPNT_COS == TRUE && SYS_CPNT_ACL_UI == TRUE) */

#if (SYS_CPNT_ACL_UI == TRUE)
#if (SYS_CPNT_QOS_V2 == TRUE)
    buffer_count = CLI_RUNCFG_Get_Access_Group_Parameter_By_Ifindex(ifindex,
                                                                    buffer,
                                                                    temp_buffer,
                                                                    buffer_size,
                                                                    buffer_count);
#else /* #if (SYS_CPNT_QOS_V2 == TRUE) */

    {
        ACL_AclGroup_Entry_T access_group;
        memset(&access_group, 0, sizeof(access_group));
        if (L4_ACL_PMGR_GetRunningAclGroup(ifindex , &access_group) == TRUE)
        {
            if (access_group.in_ip_acl[0] != 0)
            {
                APPEND_RUNNING_CFG_1(" ip access-group %s in\n",access_group.in_ip_acl);
            }
            if (access_group.out_ip_acl[0] != 0)
            {
                APPEND_RUNNING_CFG_1(" ip access-group %s out\n",access_group.out_ip_acl);
            }
            if (access_group.in_mac_acl[0] != 0)
            {
                APPEND_RUNNING_CFG_1(" mac access-group %s in\n",access_group.in_mac_acl);
            }
            if (access_group.out_mac_acl[0] != 0)
            {
                APPEND_RUNNING_CFG_1(" mac access-group %s out\n",access_group.out_mac_acl);
            }
        }
    }
#endif /* #if (SYS_CPNT_QOS_V2 == TRUE) */
#endif /* #if (SYS_CPNT_ACL_UI == TRUE) */
#if (SYS_CPNT_QOS == SYS_CPNT_QOS_MARKER)
    {
        UI8_T  acl_type[4] = {0};
        UI8_T  cos_type1[12] = {0};
        UI8_T  cos_type2[12] = {0};
        MARKER_TYPE_MarkerEntry_T marker_entry;
        memset(&marker_entry, 0, sizeof(marker_entry));


        while(L4_MARKER_PMGR_GetNextRunningMarkerEntry(ifindex, &marker_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            switch(marker_entry.acl_type)
            {
#if (SYS_CPNT_QOS_V2 == TRUE)
                case RULE_TYPE_IP_ACL:
#else
                case ACL_IP_ACL:
#endif
                    strcpy(acl_type, "ip");
                    break;
#if (SYS_CPNT_QOS_V2 == TRUE)
                case RULE_TYPE_MAC_ACL:
#else
                case ACL_MAC_ACL:
#endif
                    strcpy(acl_type, "mac");
                    break;

                default:
                    break;
            }

            if ((marker_entry.action & MARKER_TYPE_REMARK_DOT1P_PRIORITY) == MARKER_TYPE_REMARK_DOT1P_PRIORITY)
            {
                SYSFUN_Sprintf((char *)cos_type1, "priority %lu", (unsigned long)marker_entry.dot1p);
            }

            if ((marker_entry.action & MARKER_TYPE_REMARK_DSCP) == MARKER_TYPE_REMARK_DSCP)
            {
                SYSFUN_Sprintf((char *)cos_type2, "dscp %lu", (unsigned long)marker_entry.dscp);
            }
            if ((marker_entry.action & MARKER_TYPE_REMARK_TOS_PRECEDENCE) == MARKER_TYPE_REMARK_TOS_PRECEDENCE)
            {
                SYSFUN_Sprintf((char *)cos_type2, "precedence %lu", (unsigned long)marker_entry.precedence);
            }

            if (cos_type1[0] == 0)
            {
                APPEND_RUNNING_CFG_3(" match access-list %s %s set %s\n", acl_type, marker_entry.acl_name, cos_type2);
            }
            else
            {
                if (cos_type2[0] == 0)
                {
                    APPEND_RUNNING_CFG_3(" match access-list %s %s set %s\n", acl_type, marker_entry.acl_name, cos_type1);
                }
                else
                {
                    APPEND_RUNNING_CFG_4(" match access-list %s %s set %s %s\n", acl_type, marker_entry.acl_name, cos_type1, cos_type2);
                }
            }
            memset(&acl_type, 0, sizeof(acl_type));
            memset(&cos_type1, 0, sizeof(cos_type1));
            memset(&cos_type2, 0, sizeof(cos_type2));
        }

    }
#endif /* #if (SYS_CPNT_QOS == SYS_CPNT_QOS_MARKER) */

#if (SYS_CPNT_PPPOE_IA == TRUE)
    buffer_count = CLI_RUNCFG_Get_PPPoE_IA_Ethernet_Parameter(
        unit_id, port_id, buffer, temp_buffer, buffer_size, buffer_count, ifindex);
#endif

#if (SYS_CPNT_IPV6_RA_GUARD == TRUE)
    buffer_count = CLI_RUNCFG_Get_IPV6_RAGUARD_Ethernet_Parameter(
        unit_id, port_id, buffer, temp_buffer, buffer_size, buffer_count, ifindex);
#endif

#if (SYS_CPNT_PFC == TRUE)
    buffer_count = CLI_RUNCFG_Get_PFC_Ethernet_Parameter(
        unit_id, port_id, buffer, temp_buffer, buffer_size, buffer_count, ifindex);
#endif

#if (SYS_CPNT_NMTR_HISTORY == TRUE)
    {
        NMTR_TYPE_HistCtrlInfo_T ctrl_info;

        memset(&ctrl_info, 0, sizeof(ctrl_info));
        ctrl_info.data_source = ifindex;

        while (NMTR_PMGR_GetNextRemovedDefaultHistoryCtrlEntryByDataSrc(&ctrl_info))
        {
            APPEND_RUNNING_CFG_1(" no history %s\n",
                ctrl_info.name);
        }

        memset(&ctrl_info, 0, sizeof(ctrl_info));
        ctrl_info.data_source = ifindex;

        while (NMTR_PMGR_GetNextUserCfgHistoryCtrlEntryByDataSrc(&ctrl_info))
        {
            APPEND_RUNNING_CFG_3(" history %s %lu %lu\n",
                ctrl_info.name,
                (unsigned long)ctrl_info.interval,
                (unsigned long)ctrl_info.buckets_requested);
        }
    }
#endif /* (SYS_CPNT_NMTR_HISTORY == TRUE) */

#if (SYS_CPNT_QOS_UI == TRUE)
#if (SYS_CPNT_QOS == SYS_CPNT_QOS_DIFFSERV)
#if (SYS_CPNT_QOS_V2 == TRUE)
    {
        char   pmap [SYS_ADPT_DIFFSERV_MAX_NAME_LENGTH+1];

        if ( L4_PMGR_QoS_GetRunningPolicyMapNameByPort ( ifindex, RULE_TYPE_INBOUND, pmap ) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS )
        {
            APPEND_RUNNING_CFG_1(" service-policy input %s\n", pmap );
        }

        if ( L4_PMGR_QoS_GetRunningPolicyMapNameByPort ( ifindex, RULE_TYPE_OUTBOUND, pmap ) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS )
        {
            APPEND_RUNNING_CFG_1(" service-policy output %s\n", pmap );
        }
    }
#else
    {
        L4_TYPE_ServicePolicyEntry_T    entry_p;
        L4_TYPE_diffServClfrEntry_T rec_p;
        L4_TYPE_Direction_T direction;
        UI32_T temp_index = 0;

        while(L4_DS_PMGR_GetNextRunningServicePolicy(&temp_index, &direction, &entry_p) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(temp_index == ifindex)
            {
                L4_DS_PMGR_GetPolicyMap(entry_p.start.index, &rec_p);

                if(direction == L4_DS_TYPE_INGRESS)
                {
                    APPEND_RUNNING_CFG_1(" service-policy input %s\n", rec_p.name);
                }
                if(direction == L4_DS_TYPE_EGRESS)
                {
                    APPEND_RUNNING_CFG_1(" service-policy output %s\n", rec_p.name);
                }
            }
        }
    }
#endif /* #if (SYS_CPNT_QOS_V2 == TRUE) */
#endif /* #if (SYS_CPNT_QOS == SYS_CPNT_QOS_DIFFSERV) */
#endif /* #if (SYS_CPNT_QOS_UI == TRUE) */


    /* Net Access */
#if(SYS_CPNT_NETACCESS == TRUE)
#if(SYS_CPNT_NETACCESS_GUEST_VLAN == TRUE)
    {
        UI32_T vid;

        if (NETACCESS_PMGR_GetRunningSecureGuestVlanId(ifindex, &vid) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" network-access guest-vlan %lu\n", (unsigned long)vid);
        }
    }
#endif

#if(SYS_CPNT_NETACCESS_DYNAMIC_VLAN == TRUE)
    {
        UI32_T dynamic_vlan_status;

        if (NETACCESS_PMGR_GetRunningSecureDynamicVlanStatus(ifindex, &dynamic_vlan_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(dynamic_vlan_status == VAL_networkAccessPortDynamicVlan_enabled)
            {
                APPEND_RUNNING_CFG_0(" network-access dynamic-vlan\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no network-access dynamic-vlan\n");
            }
        }
    }
#endif

#if (SYS_CPNT_NETACCESS_DYNAMIC_QOS == TRUE)
    /* network-access dynamic-qos */
    {
        UI32_T status;

        if (NETACCESS_PMGR_GetRunningDynamicQosStatus(ifindex, &status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (status == VAL_networkAccessPortLinkDynamicQos_enabled)
            {
                APPEND_RUNNING_CFG_0(" network-access dynamic-qos\n");
             }
            else if (status == VAL_networkAccessPortLinkDynamicQos_disabled )
            {
                APPEND_RUNNING_CFG_0(" no network-access dynamic-qos\n");
            }
        }
    }
#endif /* #if (SYS_CPNT_NETACCESS_DYNAMIC_QOS == TRUE) */

#if (SYS_CPNT_NETACCESS_MACAUTH == TRUE)
    /* MAC authentication status */
    {
        UI32_T mac_auth_status;

        if (NETACCESS_PMGR_GetRunningMacAuthPortStatus(ifindex, &mac_auth_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (mac_auth_status == NETACCESS_TYPE_MACAUTH_ENABLED)
            {
                APPEND_RUNNING_CFG_0(" network-access mode mac-authentication\n");
             }
            else if (mac_auth_status == NETACCESS_TYPE_MACAUTH_DISABLED)
            {
                APPEND_RUNNING_CFG_0(" no network-access mode mac-authentication\n");
            }
        }
    }

    /* Secure Number Addresses  */
    {
        UI32_T number;

       if (NETACCESS_PMGR_GetRunningSecureNumberAddresses(ifindex, &number) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" network-access max-mac-count %lu\n", (unsigned long)number);
        }
    }

    /* Intrusion Action */
    {
        UI32_T action;

        if (NETACCESS_PMGR_GetRunningMacAuthPortIntrusionAction(ifindex, &action) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (action == VAL_macAuthPortIntrusionAction_block_traffic)
            {
                APPEND_RUNNING_CFG_0(" mac-authentication intrusion-action block-traffic\n");
            }
         else if (action == VAL_macAuthPortIntrusionAction_pass_traffic)
         {
             APPEND_RUNNING_CFG_0(" mac-authentication intrusion-action pass-traffic\n");
         }
        }
    }

    /*MAC Authentication Max Mac Count*/
    {
        UI32_T count;

        if (NETACCESS_PMGR_GetRunningMacAuthPortMaxMacCount(ifindex, &count) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" mac-authentication max-mac-count %lu\n", (unsigned long)count);
        }
    }
#endif /* #if (SYS_CPNT_NETACCESS_MACAUTH == TRUE) */

#if (SYS_CPNT_NETACCESS_MAC_FILTER_TABLE == TRUE)
    {
        UI32_T filter_id;
        if (NETACCESS_PMGR_GetRunningFilterIdOnPort(ifindex, &filter_id) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" network-access port-mac-filter %lu\n", (unsigned long)filter_id);
        }
    }
#endif /*#if (SYS_CPNT_NETACCESS_MAC_FILTER_TABLE == TRUE)*/

#if (SYS_CPNT_NETACCESS_LINK_DETECTION == TRUE)
    /* network-access link-detection mode&action  */
    {
        UI32_T mode;
        UI32_T action;
        SYS_TYPE_Get_Running_Cfg_T  ret_m,ret_a;

        /*c language is a short cut,we should force the two functions to get their value. */
        ret_m= NETACCESS_PMGR_GetRunningLinkDetectionMode(ifindex, &mode);
        ret_a= NETACCESS_PMGR_GetRunningLinkDetectionAction(ifindex, &action);

        if( (ret_m==SYS_TYPE_GET_RUNNING_CFG_SUCCESS) || (ret_a==SYS_TYPE_GET_RUNNING_CFG_SUCCESS) )
        {

            APPEND_RUNNING_CFG_0(" network-access link-detection");

            if (mode == VAL_networkAccessPortLinkDetectionMode_linkUp)
            {
                APPEND_RUNNING_CFG_0(" link-up");
            }
            else if (mode == VAL_networkAccessPortLinkDetectionMode_linkDown)
            {
                APPEND_RUNNING_CFG_0(" link-down");
            }
            else if (mode == VAL_networkAccessPortLinkDetectionMode_linkUpDown)
            {
                APPEND_RUNNING_CFG_0(" link-up-down");
            }

            if (action == VAL_networkAccessPortLinkDetectionAciton_trap)
            {
                APPEND_RUNNING_CFG_0(" action trap\n");
            }
            else if (action == VAL_networkAccessPortLinkDetectionAciton_shutdown)
            {
                APPEND_RUNNING_CFG_0(" action shutdown\n");
            }
            else if (action == VAL_networkAccessPortLinkDetectionAciton_trapAndShutdown)
            {
                APPEND_RUNNING_CFG_0(" action trap-and-shutdown\n");
            }

        }
    }

    /* network-access link-detection */
    {
        UI32_T status;

        if (NETACCESS_PMGR_GetRunningLinkDetectionStatus(ifindex, &status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (status == VAL_networkAccessPortLinkDetectionStatus_enabled)
            {
                APPEND_RUNNING_CFG_0(" network-access link-detection\n");
             }
            else if (status == VAL_networkAccessPortLinkDetectionStatus_disabled )
            {
                APPEND_RUNNING_CFG_0(" no network-access link-detection\n");
            }
        }
    }
#endif /* #if (SYS_CPNT_NETACCESS_LINK_DETECTION == TRUE) */

#endif  /* #if(SYS_CPNT_NETACCESS == TRUE) */

#if (SYS_CPNT_WEBAUTH == TRUE)
    {
        UI8_T status;

        if (WEBAUTH_PMGR_GetRunningStatusByLPort(ifindex, &status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (status == VAL_webAuthPortConfigStatus_enabled)
            {
                APPEND_RUNNING_CFG_0(" web-auth\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no web-auth\n");
            }
        }
    }
#endif /* #if(SYS_CPNT_WEBAUTH == TRUE) */

/*switchport protected*/
#if (SYS_DFLT_TRAFFIC_SEG_METHOD == SYS_DFLT_TRAFFIC_SEG_METHOD_PORT_PRIVATE_MODE)
{
    UI32_T port_private_mode=0 ;
    if(SWCTRL_POM_GetRunningPortPrivateMode(ifindex, &port_private_mode)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if(port_private_mode==VAL_pvePortStatus_enabled)
        {
            APPEND_RUNNING_CFG_0(" switchport protected\n");
        }
        else
        {
            APPEND_RUNNING_CFG_0(" no switchport protected\n");
        }
    }
}
#endif

/*OAM*/
#if(SYS_CPNT_EFM_OAM == TRUE)
{
    UI32_T lport = 0;
    EFM_OAM_ENTITY_INFO oam_entity;
    EFM_OAM_EVENT_CONF_T event_config;

    memset(&oam_entity, 0, sizeof(EFM_OAM_ENTITY_INFO));
    memset(&event_config, 0, sizeof(EFM_OAM_EVENT_CONF_T));

    SWCTRL_POM_UserPortToIfindex(unit_id, port_id, &lport);

    if(EFM_OAM_POM_GetOAMEntry(lport, &oam_entity) == TRUE)
    {
        if(oam_entity.local_oam_enable != EFM_OAM_DEFAULT_STATUS)
        {
            if(oam_entity.local_oam_enable == EFM_OAM_ENABLED)
            {
                APPEND_RUNNING_CFG_0(" efm oam\n");
            }
            else if(oam_entity.local_oam_enable == EFM_OAM_DISABLED)
            {
                APPEND_RUNNING_CFG_0(" no efm oam\n");
            }
        }
        if(oam_entity.local_mode != EFM_OAM_DEFAULT_MODE)
        {
            if(oam_entity.local_mode == EFM_OAM_ACTIVE)
            {
                APPEND_RUNNING_CFG_0(" efm oam mode active\n");
            }
            else if(oam_entity.local_mode == EFM_OAM_PASSIVE)
            {
                APPEND_RUNNING_CFG_0(" efm oam mode passive\n");
            }
        }
    }

    if(EFM_OAM_POM_GetEventConfig(lport, &event_config) == TRUE)
    {
        if(event_config.dying_gasp_enable != EFM_OAM_DYING_GASP_DEFAULT_STATUS)
        {
            if(event_config.dying_gasp_enable == EFM_OAM_DYING_GASP_ENABLED)
            {
                APPEND_RUNNING_CFG_0(" efm oam critical-link-event dying-gasp\n");
            }
            else if(event_config.dying_gasp_enable == EFM_OAM_DYING_GASP_DISABLED)
            {
                APPEND_RUNNING_CFG_0(" no efm oam critical-link-event dying-gasp\n");
            }
        }
        if(event_config.critical_event_enable != EFM_OAM_CRITICAL_EVENT_DEFAULT_STATUS)
        {
            if(event_config.critical_event_enable == EFM_OAM_CRITICAL_EVENT_ENABLED)
            {
                APPEND_RUNNING_CFG_0(" efm oam critical-link-event critical-event\n");
            }
            else if(event_config.critical_event_enable == EFM_OAM_CRITICAL_EVENT_DISABLED)
            {
                APPEND_RUNNING_CFG_0(" no efm oam critical-link-event critical-event\n");
            }
        }
        if(event_config.err_frame_enable != EFM_OAM_ERRORED_FRAME_DEFAULT_STATUS)
        {
            if(event_config.err_frame_enable == EFM_OAM_ERRORED_FRAME_ENABLED)
            {
                APPEND_RUNNING_CFG_0(" efm oam link-monitor frame\n");
            }
            else if(event_config.err_frame_enable == EFM_OAM_ERRORED_FRAME_DISABLED)
            {
                APPEND_RUNNING_CFG_0(" no efm oam link-monitor frame\n");
            }
        }
        if(event_config.err_frame_window != SYS_DFLT_EFM_OAM_ERROR_FRAME_WINDOW)
        {
            APPEND_RUNNING_CFG_1(" efm oam link-monitor frame window %lu\n", event_config.err_frame_window);
        }
        if(event_config.err_frame_threshold != SYS_DFLT_EFM_OAM_ERROR_FRAME_THRESHOLD)
        {
            APPEND_RUNNING_CFG_1(" efm oam link-monitor frame threshold %lu\n", event_config.err_frame_threshold);
        }
    }

}
#endif

#if (SYS_CPNT_DHCPSNP == TRUE)
    /* for dhcp snooping trust mode */
    {
        UI8_T status_trust;
        UI32_T lport_ifindex = ifindex;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            lport_ifindex = trunk_ifindex;
        }

        if (DHCPSNP_PMGR_GetRunningPortTrustStatus(lport_ifindex, &status_trust) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (status_trust == DHCPSNP_TYPE_PORT_TRUSTED)
            {
                APPEND_RUNNING_CFG_0( " ip dhcp snooping trust\n");
            }
            else if (status_trust == DHCPSNP_TYPE_PORT_UNTRUSTED)
            {
                APPEND_RUNNING_CFG_0( " no ip dhcp snooping trust\n");
            }
        }
    }

#if (SYS_CPNT_DHCPSNP_INFORMATION_OPTION == TRUE)
    {
        UI8_T cid_mode;
        UI8_T cid_value[SYS_ADPT_MAX_LENGTH_OF_CID+1]={0};
        UI32_T lport_ifindex = ifindex;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            lport_ifindex = trunk_ifindex;
        }

        if(DHCPSNP_PMGR_GetRunningPortCidMode(lport_ifindex, &cid_mode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            switch(cid_mode)
            {
                case DHCPSNP_TYPE_OPTION82_CID_VLAN_UNIT_PORT:
                    APPEND_RUNNING_CFG_0(" no ip dhcp snooping information option circuit-id\n");
                    break;
                case DHCPSNP_TYPE_OPTION82_CID_CONFIGURED_STRING:
                    if(DHCPSNP_TYPE_OK == DHCPSNP_PMGR_GetInformationPortCidValue(lport_ifindex, cid_value))
                    {
                        APPEND_RUNNING_CFG_1(" ip dhcp snooping information option circuit-id string %s\n",cid_value);
                    }
                    break;
#if (SYS_CPNT_DHCPSNP_INFORMATION_OPTION_TR101_FORMAT == TRUE)
                case DHCPSNP_TYPE_OPTION82_CID_TR101_IP:
                    APPEND_RUNNING_CFG_0(" ip dhcp snooping information option circuit-id tr101 node-identifier ip\n");
                    break;
                case DHCPSNP_TYPE_OPTION82_CID_TR101_SYSNAME:
                    APPEND_RUNNING_CFG_0(" ip dhcp snooping information option circuit-id tr101 node-identifier sysname\n");
                    break;
#endif
            }
        }
    }
#endif
#endif

/* for dhcpv6snp */
#if (SYS_CPNT_DHCPV6SNP == TRUE)
{
    UI8_T port_trust=0;
    UI8_T max_binding=0;
    UI32_T lport_ifindex = ifindex;

    if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
    {
        lport_ifindex = trunk_ifindex;
    }

    /* get port trust status */
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == DHCPV6SNP_POM_GetRunningPortTrustStatus(lport_ifindex, &port_trust))
    {
        if(DHCPV6SNP_TYPE_PORT_TRUST == port_trust)
        {
            APPEND_RUNNING_CFG_0(" ipv6 dhcp snooping trust\n");
        }

        if(DHCPV6SNP_TYPE_PORT_UNTRUST == port_trust)
        {
            APPEND_RUNNING_CFG_0(" no ipv6 dhcp snooping trust\n");
        }
    }

    /* get port max binding */
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == DHCPV6SNP_POM_GetRunningPortMaxBinding(lport_ifindex, &max_binding))
    {
        APPEND_RUNNING_CFG_1(" ipv6 dhcp snooping max-binding %u\n", max_binding);
    }
}
#endif

/* for ndsnp */
#if (SYS_CPNT_NDSNP == TRUE)
{
    UI8_T  port_trust=0;
    UI8_T  max_binding=0;
    UI32_T lport_ifindex = ifindex;

    if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
    {
        lport_ifindex = trunk_ifindex;
    }

    /* get port trust status */
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NDSNP_POM_GetRunningPortTrustStatus(lport_ifindex, &port_trust))
    {
        if(NDSNP_TYPE_PORT_TRUST == port_trust)
        {
            APPEND_RUNNING_CFG_0(" ipv6 nd snooping trust\n");
        }

        if(NDSNP_TYPE_PORT_UNTRUST == port_trust)
        {
            APPEND_RUNNING_CFG_0(" no ipv6 nd snooping trust\n");
        }
    }

    /* get port max binding */
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NDSNP_POM_GetRunningPortMaxBinding(lport_ifindex, &max_binding))
    {
        APPEND_RUNNING_CFG_1(" ipv6 nd snooping max-binding %u\n", max_binding);
    }
}
#endif

/* for ip6sg */
#if (SYS_CPNT_IPV6_SOURCE_GUARD == TRUE)
{
    UI8_T  mode=0;
    UI8_T  max_binding=0;
    UI32_T lport_ifindex = ifindex;

    if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
    {
        lport_ifindex = trunk_ifindex;
    }

    /* get port filter mode*/
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == IP6SG_POM_GetRunningPortFilterMode(lport_ifindex, &mode))
    {
        APPEND_RUNNING_CFG_0(" ipv6 source-guard sip\n");
    }

    /* get port max binding */
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == IP6SG_POM_GetRunningPortMaxBinding(lport_ifindex, &max_binding))
    {
        APPEND_RUNNING_CFG_1(" ipv6 source-guard max-binding %u\n",max_binding);
    }
}
#endif

#if (SYS_CPNT_COS_TRUST_MODE_SUPPORT_COS || SYS_CPNT_COS_TRUST_MODE_SUPPORT_DSCP \
    || SYS_CPNT_COS_TRUST_MODE_SUPPORT_PRECEDENCE)
    {
        UI32_T status_trust;
        if (L4_PMGR_QOS_GetRunningTrustStatus(ifindex, &status_trust) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (status_trust == DSCP_IF_MAPPING_MODE)
            {
                APPEND_RUNNING_CFG_0( " qos map trust-mode dscp\n");
            }
            else if (status_trust == PRECEDENCE_MAPPING_MODE)
            {
                APPEND_RUNNING_CFG_0( " qos map trust-mode ip-precedence\n");
            }
        }
    }
#endif /* #if (SYS_CPNT_COS_TRUST_MODE_SUPPORT_COS || SYS_CPNT_COS_TRUST_MODE_SUPPORT_DSCP \
            || SYS_CPNT_COS_TRUST_MODE_SUPPORT_PRECEDENCE) */

#if (SYS_CPNT_COS_ING_COS_TO_INTER_DSCP == TRUE)
#if (SYS_CPNT_COS_ING_COS_TO_INTER_DSCP_PER_PORT == TRUE)
    {
        const int max_cos_entry_num = 8;

        UI32_T cos, cfi, phb, color;
        int entry_number = 0;
        BOOL_T is_first_entry;

        APPEND_RUNNING_CFG_0(" \r\n");

        for (phb = MIN_PHB_VAL; phb <= MAX_PHB_VAL; ++phb)
        {
            for (color = MIN_COLOR_VAL; color <= MAX_COLOR_VAL; ++color)
            {
                is_first_entry = TRUE;
                cos = COS_TYPE_UNKNOWN_COS;

                while (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                       L4_PMGR_QOS_GetNextRunningPortCos2InternalDscp(ifindex, phb, color, &cos, &cfi))
                {
                    if (is_first_entry == TRUE)
                    {
                        is_first_entry = FALSE;
                        APPEND_RUNNING_CFG_2(" qos map cos-dscp %lu %lu from", (unsigned long)phb, (unsigned long)color);
                    }

                    APPEND_RUNNING_CFG_2(" %lu %lu", (unsigned long)cos, (unsigned long)cfi);

                    entry_number++;
                    if (entry_number == max_cos_entry_num)
                    {
                        APPEND_RUNNING_CFG_0("\r\n");
                        entry_number = 0;
                        is_first_entry = TRUE;
                    }
                }

                if (is_first_entry != TRUE)
                {
                    APPEND_RUNNING_CFG_0("\r\n");
                }
            }
        }
    }
#endif /* SYS_CPNT_COS_ING_COS_TO_INTER_DSCP_PER_PORT */
#endif /* SYS_CPNT_COS_ING_COS_TO_INTER_DSCP */

#if (SYS_CPNT_COS_ING_IP_PRECEDENCE_TO_INTER_DSCP == TRUE)
#if (SYS_CPNT_COS_ING_IP_PRECEDENCE_TO_INTER_DSCP_PER_PORT == TRUE)
    {
        UI32_T pre_phb[MAX_PRE_VAL + 1] = {0}, pre_color[MAX_PRE_VAL + 1] = {0};
        UI32_T pre;

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
            L4_PMGR_QOS_GetRunningPortPre2InternalDscp(ifindex, pre_phb, pre_color))
        {
            APPEND_RUNNING_CFG_0(" qos map ip-prec-dscp");
            for(pre = 0; pre <= MAX_PRE_VAL; pre++)
            {
                APPEND_RUNNING_CFG_2(" %lu %lu", (unsigned long)pre_phb[pre], (unsigned long)pre_color[pre]);
            }

            APPEND_RUNNING_CFG_0(" \n");
        }
    }
#endif /* #if (SYS_CPNT_COS_ING_IP_PRECEDENCE_TO_INTER_DSCP_PER_PORT == TRUE) */
#endif /* SYS_CPNT_COS_ING_IP_PRECEDENCE_TO_INTER_DSCP */

#if (SYS_CPNT_COS_ING_DSCP_TO_INTER_DSCP == TRUE)
#if (SYS_CPNT_COS_ING_DSCP_TO_INTER_DSCP_PER_PORT == TRUE)
    {
        const int max_cos_entry_num = 8;

        UI32_T dscp, phb, color;
        int entry_number = 0;
        BOOL_T is_first_entry;

        for (phb = MIN_PHB_VAL; phb <= MAX_PHB_VAL; ++phb)
        {
            for (color = MIN_COLOR_VAL; color <= MAX_COLOR_VAL; ++color)
            {
                is_first_entry = TRUE;
                dscp = COS_TYPE_UNKNOWN_DSCP;

                while (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                       L4_PMGR_QOS_GetNextRunningPortDscp2InternalDscp(ifindex, phb, color, &dscp))
                {
                    if (is_first_entry == TRUE)
                    {
                        is_first_entry = FALSE;
                        APPEND_RUNNING_CFG_2(" qos map dscp-mutation %lu %lu from", (unsigned long)phb, (unsigned long)color);
                    }

                    APPEND_RUNNING_CFG_1(" %lu", (unsigned long)dscp);

                    entry_number++;
                    if (entry_number == max_cos_entry_num)
                    {
                        APPEND_RUNNING_CFG_0("\r\n");
                        entry_number = 0;
                        is_first_entry = TRUE;
                    }
                }

                if (is_first_entry != TRUE)
                {
                    APPEND_RUNNING_CFG_0("\r\n");
                }
            }
        }
    }
#endif /* #if (SYS_CPNT_COS_ING_DSCP_TO_INTER_DSCP_PER_PORT == TRUE) */
#endif /* SYS_CPNT_COS_ING_DSCP_TO_INTER_DSCP */

    /*ip-port-dscp*/
#if (SYS_CPNT_COS_ING_IP_PORT_TO_INTER_DSCP == TRUE)
#if (SYS_CPNT_COS_ING_IP_PORT_TO_INTER_DSCP_PER_PORT == TRUE)
    {
        UI32_T temp_ifindex = ifindex;
        UI32_T phb,color = 0,protocol,dport,ret;

        ret = L4_PMGR_QOS_GetRunningTCPUDP2Dscp(temp_ifindex, &protocol, &dport ,&phb, &color);
        while((TRUE == ret) && (temp_ifindex == ifindex))
        {
            APPEND_RUNNING_CFG_0(" qos map ip-port-dscp");
            if(protocol == tcp_protocol)
            {
                APPEND_RUNNING_CFG_3(" tcp %lu to %lu %lu\n", (unsigned long)dport, (unsigned long)phb, (unsigned long)color);
            }
            else if(protocol == udp_protocol)
            {
                APPEND_RUNNING_CFG_3(" udp %lu to %lu %lu\n", (unsigned long)dport, (unsigned long)phb, (unsigned long)color);
            }
            ret = L4_PMGR_QOS_GetNextTCPUDP2Dscp(&temp_ifindex, &protocol, &dport ,&phb, &color);
        }
    }
#endif /* #if (SYS_CPNT_COS_ING_IP_PORT_TO_INTER_DSCP_PER_PORT == TRUE) */
#endif /* SYS_CPNT_COS_ING_IP_PORT_TO_INTER_DSCP */

#if (SYS_CPNT_COS_ING_INTER_DSCP_TO_COLOR == TRUE)
    {
        UI8_T  pre_color[MAX_PRE_VAL + 1]={0};
        UI32_T ret,k,i,j,first = TRUE;

        first = TRUE;
        for (i = 0;i <=MAX_COLOR_VAL;i++)
        {
            if (i == 2)
                    continue;
            ret = L4_PMGR_QOS_GetRunningIngressDscp2Color(ifindex,pre_color);
            k=0;
            for(j = 0;j<=MAX_PRE_VAL;j++)
            {
                if((pre_color[j] != 4)&&(pre_color[j] == i))
                {
                    if (k % 8 == 0 && first == FALSE)
                    {
                        APPEND_RUNNING_CFG_0(" \n");
                        k=0;
                    }
                    if (k % 8 == 0 && k == 0)
                    {
                        APPEND_RUNNING_CFG_1(" qos map default-drop-precedence %d from",pre_color[j]);
                        APPEND_RUNNING_CFG_1(" %lu",(unsigned long)j);
                        first = FALSE;
                    }
                    else
                    {
                        if (k % 8 != 0)
                        {
                            APPEND_RUNNING_CFG_1(" %lu",(unsigned long)j);
                        }
                    }
                    k++;
                }
            }
            if(k > 0)
            {
                APPEND_RUNNING_CFG_0(" \n");
            }
        }
    }
#endif /* #if (SYS_CPNT_COS_ING_INTER_DSCP_TO_COLOR == TRUE) */

#if (SYS_CPNT_COS_ING_INTER_DSCP_TO_QUEUE == TRUE)
#if (SYS_CPNT_COS_ING_INTER_DSCP_TO_QUEUE_PER_PORT == TRUE)
    {
        const int max_cos_entry_num = 8;

        UI32_T queue, phb;
        int entry_number = 0;
        BOOL_T is_first_entry;

        for (queue = MIN_QUEUE_VAL; phb <= MAX_QUEUE_VAL; ++queue)
        {
            is_first_entry = TRUE;
            phb = COS_TYPE_UNKNOWN_PHB;

            while (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                   L4_PMGR_QOS_GetNextRunningPortIngressPhb2Queue(ifindex, queue, &phb))
            {
                if (is_first_entry == TRUE)
                {
                    is_first_entry = FALSE;
                    APPEND_RUNNING_CFG_1(" qos map phb-queue %lu from", (unsigned long)queue);
                }

                APPEND_RUNNING_CFG_1(" %lu", (unsigned long)phb);

                entry_number++;
                if (entry_number == max_cos_entry_num)
                {
                    APPEND_RUNNING_CFG_0("\r\n");
                    entry_number = 0;
                    is_first_entry = TRUE;
                }
            }

            if (is_first_entry != TRUE)
            {
                APPEND_RUNNING_CFG_0("\r\n");
            }
        }
    }
#endif /* #if (SYS_CPNT_COS_ING_INTER_DSCP_TO_QUEUE_PER_PORT == TRUE) */
#endif /* SYS_CPNT_COS_ING_INTER_DSCP_TO_QUEUE */

#if (SYS_CPNT_COS_ING_INTER_DSCP_TO_COS == TRUE)
    {
        UI8_T  cos_phb[8]={8},cos_color[8]={4};
        UI8_T  l_phb = 0, l_color = 0;
        UI32_T k=0,i,j;

        for (i = 0;i <=MAX_COS_VAL;i++)
        {
            for (j = 0;j <= MAX_CFI_VAL;j++)
            {
                l_phb = 0;
                l_color = 0;
                while (l_phb != 8 && l_color != 4)
                {
                    if(TRUE == L4_PMGR_QOS_GetRunningIngressDscp2Cos(ifindex, i, j,&l_phb,&l_color, cos_phb, cos_color))
                    {
                        APPEND_RUNNING_CFG_0(" \n");
                        APPEND_RUNNING_CFG_2(" qos map dscp-cos %lu %lu from",(unsigned long)i,(unsigned long)j);

                        k=0;
                        while( k<8 && cos_phb[k] != 8 && cos_color[k] != 4)
                        {
                            APPEND_RUNNING_CFG_2(" %d %d",cos_phb[k],cos_color[k]);
                            k++;
                        }
                    }
                }

            }
        }
        if(k > 0)
        {
            APPEND_RUNNING_CFG_0(" \n");
        }
    }
#endif /* #if (SYS_CPNT_COS_ING_INTER_DSCP_TO_COS == TRUE) */

#if(SYS_CPNT_CFM==TRUE)

    /* Commands:
     * ethernet cfm mep mpid mpid ma ma-name [up]
     * no ethernet cfm mep mpid mpid ma ma-name
     */
    {
#define CLI_API_IS_BIT_ON(pbmp, lport)  (((pbmp[((lport) - 1) >> 3]) & (1 << (7 - (((lport) - 1) & 7)))) != 0)

        CFM_OM_MepInfo_T    mep_p;
        UI32_T              md_index_p      = 0;
        UI32_T              ma_index_p      = 0;
        UI32_T              tmp_ifidx       = 0;
        BOOL_T              is_fst_trk_mbr  = FALSE;

        /* record the MEP on the trunk's member port with lowest ifindex
         */
        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            TRK_MGR_TrunkEntry_T    trk_info;

            trk_info.trunk_index = which_trunk;
            if (TRUE == TRK_PMGR_GetTrunkEntry(&trk_info))
            {
                for (tmp_ifidx =1; tmp_ifidx < ifindex; tmp_ifidx++)
                {
                    if (CLI_API_IS_BIT_ON(trk_info.trunk_ports, tmp_ifidx))
                    {
                        break;

                    }
                }

                if (tmp_ifidx == ifindex)
                {
                    is_fst_trk_mbr = TRUE;
                    ifindex = trunk_ifindex;
                }
            }
        }

        while (CFM_OM_GetNextRunnningMep(&md_index_p, &ma_index_p, ifindex, &mep_p)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
#if (SYS_CPNT_CFM_MA_NAME_UNIQUE_PER_DOMAIN == TRUE)
            if(mep_p.direction==CFM_TYPE_MP_DIRECTION_DOWN)
            {
                APPEND_RUNNING_CFG_3(" ethernet cfm mep mpid %lu md %s ma %s\n",
                                        (unsigned long)mep_p.identifier, mep_p.md_name_a, mep_p.ma_name_a);
            }
            else
            {
                APPEND_RUNNING_CFG_3(" ethernet cfm mep mpid %lu md %s ma %s up\n",
                                        (unsigned long)mep_p.identifier, mep_p.md_name_a, mep_p.ma_name_a);
            }
#else
            if(mep_p.direction==CFM_TYPE_MP_DIRECTION_DOWN)
            {
                APPEND_RUNNING_CFG_2(" ethernet cfm mep mpid %lu ma %s\n",
                                        (unsigned long)mep_p.identifier, mep_p.ma_name_a);
            }
            else
            {
                APPEND_RUNNING_CFG_2(" ethernet cfm mep mpid %lu ma %s up\n",
                                        (unsigned long)mep_p.identifier, mep_p.ma_name_a);
            }
#endif /* #if (SYS_CPNT_CFM_MA_NAME_UNIQUE_PER_DOMAIN == TRUE) */
        }

        /* restore the ifindex
         */
        if (TRUE == is_fst_trk_mbr)
        {
            ifindex = tmp_ifidx;
        }
    }

    /* Commands:
     * ethernet cfm port-enable
     * no ethernet cfm port-enable
     */
    {
        CFM_TYPE_CfmStatus_T  cfm_port_Status;

        if(CFM_OM_GetRunningCfmPortStatus( ifindex, &cfm_port_Status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(cfm_port_Status==CFM_TYPE_CFM_STATUS_ENABLE)
            {
                APPEND_RUNNING_CFG_0(" ethernet cfm port-enable\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no ethernet cfm port-enable\n");
            }
        }
    }
#endif


/* auto traffic control */
#if (SYS_CPNT_ATC_STORM == TRUE)
    {
        SWCTRL_ATCBroadcastStormEntry_T bcast_entry;
        SWCTRL_ATCMulticastStormEntry_T mcast_entry;

#if (SYS_CPNT_ATC_BSTORM == TRUE)
        /* ----------------------------------- broadcast ------------------------------------*/
        bcast_entry.atc_broadcast_storm_ifindex = ifindex;
        if ( SWCTRL_PMGR_GetRunningATCBroadcastStormEntry(&bcast_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS )
        {
            /* ATC broadcast */
            if (bcast_entry.atc_broadcast_storm_status != SYS_DFLT_ATC_BSTORM_STATUS)
            {
                if (bcast_entry.atc_broadcast_storm_status == VAL_atcBcastStormEnable_enabled)
                {
                    APPEND_RUNNING_CFG_0(" auto-traffic-control broadcast\n");
                }
                else if ( bcast_entry.atc_broadcast_storm_action == VAL_atcBcastStormTcAction_shutdown )
                {
                    APPEND_RUNNING_CFG_0(" no auto-traffic-control broadcast\n");
                }
            }

            /* ATC broadcast action */
            if ( bcast_entry.atc_broadcast_storm_action != SYS_DFLT_ATC_BSTORM_STORM_ACTION )
            {
                if ( bcast_entry.atc_broadcast_storm_action == VAL_atcBcastStormTcAction_rate_control )
                {
                    APPEND_RUNNING_CFG_0(" auto-traffic-control broadcast action rate-control\n");
                }
                else if ( bcast_entry.atc_broadcast_storm_action == VAL_atcBcastStormTcAction_shutdown )
                {
                    APPEND_RUNNING_CFG_0(" auto-traffic-control broadcast action shutdown\n");
                }
            }

            /* ATC broadcast auto-control-release */
            if ( bcast_entry.atc_broadcast_storm_auto_traffic_control_release != SYS_DFLT_ATC_BSTORM_STORM_TC_RELEASE )
            {
                if ( bcast_entry.atc_broadcast_storm_auto_traffic_control_release == VAL_atcBcastStormAutoRelease_enabled )
                {
                    APPEND_RUNNING_CFG_0(" auto-traffic-control broadcast auto-control-release\n");
                }
                else if ( bcast_entry.atc_broadcast_storm_auto_traffic_control_release == VAL_atcBcastStormAutoRelease_disabled )
                {
                    APPEND_RUNNING_CFG_0(" no auto-traffic-control broadcast auto-control-release\n");
                }
            }

            if (bcast_entry.atc_broadcast_storm_storm_alarm_threshold < (SYS_DFLT_ATC_BSTORM_STORM_CLEAR_THRESHOLD / SYS_ADPT_ATC_STORM_CONTROL_UNIT))
            {
                /* ATC broadcast alarm clear threshold */
                if ( bcast_entry.atc_broadcast_storm_storm_clear_threshold * SYS_ADPT_ATC_STORM_CONTROL_UNIT != SYS_DFLT_ATC_BSTORM_STORM_CLEAR_THRESHOLD )
                {
                    APPEND_RUNNING_CFG_1(" auto-traffic-control broadcast alarm-clear-threshold %lu\n", (unsigned long)bcast_entry.atc_broadcast_storm_storm_clear_threshold);
                }

                /* ATC broadcast alarm fire threshold */
                if ( bcast_entry.atc_broadcast_storm_storm_alarm_threshold * SYS_ADPT_ATC_STORM_CONTROL_UNIT != SYS_DFLT_ATC_BSTORM_STORM_ALARM_THRESHOLD )
                {
                    APPEND_RUNNING_CFG_1(" auto-traffic-control broadcast alarm-fire-threshold %lu\n", (unsigned long)bcast_entry.atc_broadcast_storm_storm_alarm_threshold);
                }
            }
            else
            {
                /* ATC broadcast alarm fire threshold */
                if ( bcast_entry.atc_broadcast_storm_storm_alarm_threshold * SYS_ADPT_ATC_STORM_CONTROL_UNIT != SYS_DFLT_ATC_BSTORM_STORM_ALARM_THRESHOLD )
                {
                    APPEND_RUNNING_CFG_1(" auto-traffic-control broadcast alarm-fire-threshold %lu\n", (unsigned long)bcast_entry.atc_broadcast_storm_storm_alarm_threshold);
                }

                /* ATC broadcast alarm clear threshold */
                if ( bcast_entry.atc_broadcast_storm_storm_clear_threshold * SYS_ADPT_ATC_STORM_CONTROL_UNIT != SYS_DFLT_ATC_BSTORM_STORM_CLEAR_THRESHOLD )
                {
                    APPEND_RUNNING_CFG_1(" auto-traffic-control broadcast alarm-clear-threshold %lu\n", (unsigned long)bcast_entry.atc_broadcast_storm_storm_clear_threshold);
                }
            }


            /* ATC broadcast alarm fire */
            if ( bcast_entry.atc_broadcast_storm_trap_storm_alarm != SYS_DFLT_ATC_BSTORM_STORM_TRAP_STORM_ALARM )
            {
                if ( bcast_entry.atc_broadcast_storm_trap_storm_alarm == VAL_atcBcastStormAlarmFireTrapStatus_enabled )
                {
                    APPEND_RUNNING_CFG_0(" snmp-server enable port-traps atc broadcast-alarm-fire\n");
                }
                else if ( bcast_entry.atc_broadcast_storm_trap_storm_alarm == VAL_atcBcastStormAlarmFireTrapStatus_disabled )
                {
                    APPEND_RUNNING_CFG_0(" no snmp-server enable port-traps atc broadcast-alarm-fire\n");
                }
            }

            /* ATC broadcast alarm clear */
            if ( bcast_entry.atc_broadcast_storm_trap_storm_clear != SYS_DFLT_ATC_BSTORM_STORM_TRAP_STORM_CLEAR )
            {
                if ( bcast_entry.atc_broadcast_storm_trap_storm_clear == VAL_atcBcastStormAlarmClearTrapStatus_enabled )
                {
                    APPEND_RUNNING_CFG_0(" snmp-server enable port-traps atc broadcast-alarm-clear\n");
                }
                else if ( bcast_entry.atc_broadcast_storm_trap_storm_clear == VAL_atcBcastStormAlarmClearTrapStatus_disabled )
                {
                    APPEND_RUNNING_CFG_0(" no snmp-server enable port-traps atc broadcast-alarm-clear\n");
                }
            }

            /* ATC broadcast control apply */
            if ( bcast_entry.atc_broadcast_storm_trap_traffic_control_on != SYS_DFLT_ATC_BSTORM_STORM_TRAP_TC_ON )
            {
                if ( bcast_entry.atc_broadcast_storm_trap_traffic_control_on == VAL_atcBcastStormTcApplyTrapStatus_enabled )
                {
                    APPEND_RUNNING_CFG_0(" snmp-server enable port-traps atc broadcast-control-apply\n");
                }
                else if ( bcast_entry.atc_broadcast_storm_trap_traffic_control_on == VAL_atcBcastStormTcApplyTrapStatus_disabled )
                {
                    APPEND_RUNNING_CFG_0(" no snmp-server enable port-traps atc broadcast-control-apply\n");
                }
            }

            /* ATC broadcast control release */
            if ( bcast_entry.atc_broadcast_storm_trap_traffic_control_release != SYS_DFLT_ATC_BSTORM_STORM_TRAP_TC_RELEASE )
            {
                if ( bcast_entry.atc_broadcast_storm_trap_traffic_control_release == VAL_atcBcastStormTcReleaseTrapStatus_enabled )
                {
                    APPEND_RUNNING_CFG_0(" snmp-server enable port-traps atc broadcast-control-release\n");
                }
                else if ( bcast_entry.atc_broadcast_storm_trap_traffic_control_release == VAL_atcBcastStormTcReleaseTrapStatus_disabled )
                {
                    APPEND_RUNNING_CFG_0(" no snmp-server enable port-traps atc broadcast-control-release\n");
                }
            }
        }
#endif

#if (SYS_CPNT_ATC_MSTORM == TRUE)
        /* -------------------------------------- multicast ------------------------------------------*/
        mcast_entry.atc_multicast_storm_ifindex = ifindex;

        if ( SWCTRL_PMGR_GetRunningATCMulticastStormEntry(&mcast_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS )
        {
            /* ATC multicast */
            if (mcast_entry.atc_multicast_storm_status != SYS_DFLT_ATC_MSTORM_STATUS)
            {
                if (mcast_entry.atc_multicast_storm_status == VAL_atcMcastStormEnable_enabled)
                {
                    APPEND_RUNNING_CFG_0(" auto-traffic-control multicast\n");
                }
                else if ( mcast_entry.atc_multicast_storm_action == VAL_atcMcastStormTcAction_shutdown )
                {
                    APPEND_RUNNING_CFG_0(" no auto-traffic-control multicast\n");
                }
            }

            /* ATC multicast action */
            if ( mcast_entry.atc_multicast_storm_action != SYS_DFLT_ATC_MSTORM_STORM_ACTION )
            {
                if ( mcast_entry.atc_multicast_storm_action == VAL_atcMcastStormTcAction_rate_control )
                {
                    APPEND_RUNNING_CFG_0(" auto-traffic-control multicast action rate-control\n");
                }
                else if ( mcast_entry.atc_multicast_storm_action == VAL_atcMcastStormTcAction_shutdown )
                {
                    APPEND_RUNNING_CFG_0(" auto-traffic-control multicast action shutdown\n");
                }
            }

            /* ATC multicast control-release */
            if ( mcast_entry.atc_multicast_storm_auto_traffic_control_release != SYS_DFLT_ATC_MSTORM_STORM_TC_RELEASE )
            {
                if ( mcast_entry.atc_multicast_storm_auto_traffic_control_release == VAL_atcMcastStormAutoRelease_enabled )
                {
                    APPEND_RUNNING_CFG_0(" auto-traffic-control multicast auto-control-release\n");
                }
                else if ( mcast_entry.atc_multicast_storm_auto_traffic_control_release == VAL_atcMcastStormAutoRelease_disabled )
                {
                    APPEND_RUNNING_CFG_0(" no auto-traffic-control multicast auto-control-release\n");
                }
            }

            if ( mcast_entry.atc_multicast_storm_storm_alarm_threshold < (SYS_DFLT_ATC_MSTORM_STORM_CLEAR_THRESHOLD / SYS_ADPT_ATC_STORM_CONTROL_UNIT))
            {
                /* ATC multicast alarm clear threshold */
                if ( mcast_entry.atc_multicast_storm_storm_clear_threshold * SYS_ADPT_ATC_STORM_CONTROL_UNIT != SYS_DFLT_ATC_MSTORM_STORM_CLEAR_THRESHOLD )
                {
                    APPEND_RUNNING_CFG_1(" auto-traffic-control multicast alarm-clear-threshold %lu\n", mcast_entry.atc_multicast_storm_storm_clear_threshold);
                }

                /* ATC multicast alarm fire threshold */
                if ( mcast_entry.atc_multicast_storm_storm_alarm_threshold * SYS_ADPT_ATC_STORM_CONTROL_UNIT != SYS_DFLT_ATC_MSTORM_STORM_ALARM_THRESHOLD )
                {
                    APPEND_RUNNING_CFG_1(" auto-traffic-control multicast alarm-fire-threshold %lu\n", mcast_entry.atc_multicast_storm_storm_alarm_threshold);
                }
            }
            else
            {
                /* ATC multicast alarm fire threshold */
                if ( mcast_entry.atc_multicast_storm_storm_alarm_threshold * SYS_ADPT_ATC_STORM_CONTROL_UNIT != SYS_DFLT_ATC_MSTORM_STORM_ALARM_THRESHOLD )
                {
                    APPEND_RUNNING_CFG_1(" auto-traffic-control multicast alarm-fire-threshold %lu\n", mcast_entry.atc_multicast_storm_storm_alarm_threshold);
                }

                /* ATC multicast alarm clear threshold */
                if ( mcast_entry.atc_multicast_storm_storm_clear_threshold * SYS_ADPT_ATC_STORM_CONTROL_UNIT != SYS_DFLT_ATC_MSTORM_STORM_CLEAR_THRESHOLD )
                {
                    APPEND_RUNNING_CFG_1(" auto-traffic-control multicast alarm-clear-threshold %lu\n", mcast_entry.atc_multicast_storm_storm_clear_threshold);
                }
            }

            /* ATC multicast alarm fire */
            if ( mcast_entry.atc_multicast_storm_trap_storm_alarm != SYS_DFLT_ATC_MSTORM_STORM_TRAP_STORM_ALARM )
            {
                if ( mcast_entry.atc_multicast_storm_trap_storm_alarm == VAL_atcMcastStormAlarmFireTrapStatus_enabled )
                {
                    APPEND_RUNNING_CFG_0(" snmp-server enable port-traps atc multicast-alarm-fire\n");
                }
                else if ( mcast_entry.atc_multicast_storm_trap_storm_alarm == VAL_atcMcastStormAlarmFireTrapStatus_disabled )
                {
                    APPEND_RUNNING_CFG_0(" no snmp-server enable port-traps atc multicast-alarm-fire\n");
                }
            }

            /* ATC multicast alarm clear */
            if ( mcast_entry.atc_multicast_storm_trap_storm_clear != SYS_DFLT_ATC_MSTORM_STORM_TRAP_STORM_CLEAR )
            {
                if ( mcast_entry.atc_multicast_storm_trap_storm_clear == VAL_atcMcastStormAlarmClearTrapStatus_enabled )
                {
                    APPEND_RUNNING_CFG_0(" snmp-server enable port-traps atc multicast-alarm-clear\n");
                }
                else if ( mcast_entry.atc_multicast_storm_trap_storm_clear == VAL_atcMcastStormAlarmClearTrapStatus_disabled )
                {
                    APPEND_RUNNING_CFG_0(" no snmp-server enable port-traps atc multicast-alarm-clear\n");
                }
}

            /* ATC multicast control apply */
            if ( mcast_entry.atc_multicast_storm_trap_traffic_control_on != SYS_DFLT_ATC_MSTORM_STORM_TRAP_TC_ON )
            {
                if ( mcast_entry.atc_multicast_storm_trap_traffic_control_on == VAL_atcMcastStormTcApplyTrapStatus_enabled )
                {
                    APPEND_RUNNING_CFG_0(" snmp-server enable port-traps atc multicast-control-apply\n");
                }
                else if ( mcast_entry.atc_multicast_storm_trap_traffic_control_on == VAL_atcMcastStormTcApplyTrapStatus_disabled )
                {
                    APPEND_RUNNING_CFG_0(" no snmp-server enable port-traps atc multicast-control-apply\n");
                }
            }

            /* ATC multicast control release */
            if ( mcast_entry.atc_multicast_storm_trap_traffic_control_release != SYS_DFLT_ATC_MSTORM_STORM_TRAP_TC_RELEASE )
            {
                if ( mcast_entry.atc_multicast_storm_trap_traffic_control_release == VAL_atcMcastStormTcReleaseTrapStatus_enabled )
                {
                    APPEND_RUNNING_CFG_0(" snmp-server enable port-traps atc multicast-control-release\n");
                }
                else if ( mcast_entry.atc_multicast_storm_trap_traffic_control_release == VAL_atcMcastStormTcReleaseTrapStatus_disabled )
                {
                    APPEND_RUNNING_CFG_0(" no snmp-server enable port-traps atc multicast-control-release\n");
                }
            }
        }
#endif
    }
#endif

#if (SYS_CPNT_IF_LINK_TRAP_PORT_BASE == TRUE)
    {
        UI32_T  link_up_down_trap;

        if (IF_PMGR_GetRunningIfLinkUpDownTrapEnable(ifindex, &link_up_down_trap) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (link_up_down_trap == VAL_ifLinkUpDownTrapEnable_enabled)
            {
                APPEND_RUNNING_CFG_0(" snmp-server enable port-traps link-up-down\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no snmp-server enable port-traps link-up-down\n");
            }
        }
    }
#endif /* #if (SYS_CPNT_IF_LINK_TRAP_PORT_BASE == TRUE) */

#if (SYS_CPNT_AMTR_MAC_NOTIFY == TRUE)
    {
        UI32_T  lport=ifindex;
        BOOL_T  is_enabled;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
            lport = trunk_ifindex;

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS  == AMTR_PMGR_GetRunningMacNotifyPortStatus(lport, &is_enabled))
        {
            if (TRUE == is_enabled)
            {
                APPEND_RUNNING_CFG_0(" snmp-server enable port-traps mac-notification\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no snmp-server enable port-traps mac-notification\n");
            }
        }
    }
#endif /* #if (SYS_CPNT_AMTR_MAC_NOTIFY == TRUE) */

#if (SYS_CPNT_POWER_SAVE == TRUE)
    {
        BOOL_T status;

        if(SWCTRL_PMGR_GetRunningPortPowerSaveStatus(ifindex, &status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" %spower-save\n", (status == VAL_portPowerSave_enabled)? "":"no ");
        }
    }
#endif /* #if (SYS_CPNT_POWER_SAVE == TRUE) */

#if (SYS_CPNT_IGMPAUTH== TRUE)
    {
        UI32_T status;

        if(IGMPSNP_PMGR_GetRunningIgmpAuthenticationStatus(ifindex, &status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(status == VAL_igmpSnoopAuthentication_enable)
            {
                APPEND_RUNNING_CFG_0(" ip igmp authentication\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no ip igmp authentication\n");
            }
        }
    }
#endif


#if (SYS_CPNT_MLDSNP_QUERY_DROP == TRUE)
    {
        UI32_T status;

        if(MLDSNP_POM_GetRunningQuaryGuardStatus(port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER?trunk_ifindex:ifindex, &status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(status == VAL_igmpSnoopQueryDrop_enable)
            {
                APPEND_RUNNING_CFG_0(" ipv6 mld query-drop\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no ipv6 mld query-drop\n");
            }
        }
    }
#endif

#if (SYS_CPNT_IPV6_MULTICAST_DATA_DROP== TRUE)
    {
        UI32_T status;

        if(MLDSNP_POM_GetRunningMulticastDataDropStatus(port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER?trunk_ifindex:ifindex, &status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(status == VAL_igmpSnoopMulticastDataDrop_enable)
            {
                APPEND_RUNNING_CFG_0(" ipv6 multicast-data-drop\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no ipv6 multicast-data-drop\n");
            }
        }
    }
#endif
#if (SYS_CPNT_ITRI_MIM == TRUE)
    {
        BOOL_T status;

        if (SWCTRL_POM_ITRI_MIM_GetRunningStatus(port_id, &status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (status)
            {
                APPEND_RUNNING_CFG_0(" mac-translate\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no mac-translate\n");
            }
        }
    }
#endif

#if (SYS_CPNT_CN == TRUE)
    {
        UI32_T lport = ifindex;
        UI32_T cnpv, mode, alt_priority;

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            lport = trunk_ifindex;
        }

        cnpv = CN_TYPE_START_PRIORITY_FOR_SEARCHING;
        while (CN_POM_GetNextCnpv(&cnpv) == CN_TYPE_RETURN_OK)
        {
            if (CN_POM_GetRunningPortCnpvDefenseMode(cnpv, lport, &mode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                switch (mode)
                {
                case CN_TYPE_DEFENSE_MODE_AUTO:
                    APPEND_RUNNING_CFG_1(" cn cnpv %lu defense-mode auto\n", (unsigned long)cnpv);
                    break;
                case CN_TYPE_DEFENSE_MODE_DISABLED:
                    APPEND_RUNNING_CFG_1(" cn cnpv %lu defense-mode disabled\n", (unsigned long)cnpv);
                    break;
                case CN_TYPE_DEFENSE_MODE_EDGE:
                    APPEND_RUNNING_CFG_1(" cn cnpv %lu defense-mode edge\n", (unsigned long)cnpv);
                    break;
                case CN_TYPE_DEFENSE_MODE_INTERIOR:
                    APPEND_RUNNING_CFG_1(" cn cnpv %lu defense-mode interior\n", (unsigned long)cnpv);
                    break;
                case CN_TYPE_DEFENSE_MODE_INTERIOR_READY:
                    APPEND_RUNNING_CFG_1(" cn cnpv %lu defense-mode interior-ready\n", (unsigned long)cnpv);
                    break;
                }
            }

            if (CN_POM_GetRunningPortCnpvAlternatePriority(cnpv, lport, &alt_priority) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_2(" cn cnpv %lu alternate-priority %lu\n", (unsigned long)cnpv, (unsigned long)alt_priority);
            }
        } /* end of while */
    }
#endif /* #if (SYS_CPNT_CN == TRUE) */

    if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
    {
        /*it must be trunk member; it's not necessary to check the return value*/
        if(!TRK_PMGR_IsDynamicTrunkId(which_trunk) )
        {
#if (SYS_CPNT_LACP == TRUE)
            if (LACP_POM_GetRunningDot3adLacpPortEnabled(ifindex,&lacp_state) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if (lacp_state == VAL_lacpPortStatus_enabled)
                {
                    APPEND_RUNNING_CFG_0(" lacp\n");/*if go to this line, must be bug*/
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lacp\n");
                }
            }
#endif  /* #if (SYS_CPNT_LACP == TRUE) */
            APPEND_RUNNING_CFG_1(" channel-group %lu\n", (unsigned long)which_trunk);
        }
        else
        {
#if (SYS_CPNT_LACP == TRUE)
            if (LACP_POM_GetRunningDot3adLacpPortEnabled(ifindex,&lacp_state) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if (lacp_state == VAL_lacpPortStatus_enabled)
                {
                    APPEND_RUNNING_CFG_0(" lacp\n");/*if go to this line, must be bug*/
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no lacp\n");
                }
            }
#endif  /* #if (SYS_CPNT_LACP == TRUE) */
        }
    }
    else
    {
#if (SYS_CPNT_LACP == TRUE)
        if (LACP_POM_GetRunningDot3adLacpPortEnabled(ifindex,&lacp_state) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (lacp_state == VAL_lacpPortStatus_enabled)
            {
                APPEND_RUNNING_CFG_0(" lacp\n");/*if go to this line, must be bug*/
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no lacp\n");
            }
        }
#endif  /* #if (SYS_CPNT_LACP == TRUE) */
    }

#if (SYS_CPNT_LACP == TRUE)
    /*lacp*/
    {
#if 0
        UI32_T state = 0;
        UI8_T actor_admin_state = 0;
        UI8_T partner_admin_state = 0;
        UI8_T partner_system_id[6] = {0};
        UI16_T partner_admin_port = 0;
        UI8_T  buff[CLI_DEF_MAX_BUFSIZE]       = {0};
        UI32_T temp_ifindex;
#endif
        UI16_T actor_system_priority = 0;
        UI16_T actor_admin_key = 0;
        UI16_T actor_port_priority = 0;
        UI16_T partner_system_priority = 0;
        UI16_T partner_admin_key = 0;
        UI16_T partner_port_priority = 0;
#if 0
        /* Actually, it's not necessary to get the state for the dynamic trunk member,
        * but for code consistence, get it not matter what it is.
        */
        if (LACP_PMGR_GetRunningDot3adLacpPortEnabled(ifindex,&state) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (state == VAL_lacpPortStatus_enabled)
            {
                APPEND_RUNNING_CFG_0(" lacp\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no lacp\n");
            }
        }
#endif
        /*lacp actor system-priority*/
        if(LACP_PMGR_GetRunningDot3adAggPortActorSystemPriority(ifindex,&actor_system_priority) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" lacp actor system-priority %d\n",actor_system_priority);
        }

        /*lacp actor admin-key*/
        if(LACP_PMGR_GetRunningDot3adAggPortActorAdminKey(ifindex,&actor_admin_key) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" lacp actor admin-key %d\n",actor_admin_key);
        }

        /*lacp actor port-priority*/
        if(LACP_PMGR_GetRunningDot3adAggPortActorPortPriority(ifindex,&actor_port_priority) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" lacp actor port-priority %d\n",actor_port_priority);
        }
#if 0
        /*lacp actor admin-state*/
        if(LACP_PMGR_GetRunningDot3adAggPortActorAdminState(ifindex,&actor_admin_state) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if((actor_admin_state >> 7) & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp actor admin-state lacp-activity\n");
            }
            if((actor_admin_state >> 6) & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp actor admin-state lacp-timeout\n");
            }
            if((actor_admin_state >> 5) & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp actor admin-state aggregation\n");
            }
            if((actor_admin_state >> 4) & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp actor admin-state synchronization\n");
            }
            if((actor_admin_state >> 3) & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp actor admin-state collecting\n");
            }
            if((actor_admin_state >> 2) & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp actor admin-state distributing\n");
            }
            if((actor_admin_state >> 1) & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp actor admin-state defaulted\n");
            }
            if(actor_admin_state & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp actor admin-state expired\n");
            }
        }
#endif
        /*lacp partner system-priority*/
        if(LACP_PMGR_GetRunningDot3adAggPortPartnerAdminSystemPriority(ifindex,&partner_system_priority) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" lacp partner system-priority %d\n",partner_system_priority);
        }

        /*lacp partner admin-key*/
        if(LACP_PMGR_GetRunningDot3adAggPortPartnerAdminKey(ifindex,&partner_admin_key) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" lacp partner admin-key %d\n",partner_admin_key);
        }

        /*lacp partner port-priority*/
        if(LACP_PMGR_GetRunningDot3adAggPortPartnerAdminPortPriority(ifindex,&partner_port_priority) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" lacp partner port-priority %d\n",partner_port_priority);
        }
#if 0
        /*lacp partner admin-state*/
        if(LACP_PMGR_GetRunningDot3adAggPortPartnerAdminState(ifindex,&partner_admin_state) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if((partner_admin_state >> 7) & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp partner admin-state lacp-activity\n");
            }
            if((partner_admin_state >> 6) & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp partner admin-state lacp-timeout\n");
            }
            if((partner_admin_state >> 5) & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp partner admin-state aggregation\n");
            }
            if((partner_admin_state >> 4) & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp partner admin-state synchronization\n");
            }
            if((partner_admin_state >> 3) & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp partner admin-state collecting\n");
            }
            if((partner_admin_state >> 2) & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp partner admin-state distributing\n");
            }
            if((partner_admin_state >> 1) & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp partner admin-state defaulted\n");
            }
            if(partner_admin_state & 1)
            {
                APPEND_RUNNING_CFG_0(" lacp partner admin-state expired\n");
            }
        }

        /*lacp partner admin-system-id*/
        if(LACP_POM_GetRunningDot3adAggPortPartnerAdminSystemId(ifindex,&partner_system_id) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            SYSFUN_Sprintf((char *)buff, " %02X-%02X-%02X-%02X-%02X-%02X", partner_system_id[0],
                                         partner_system_id[1],
                                         partner_system_id[2],
                                         partner_system_id[3],
                                         partner_system_id[4],
                                         partner_system_id[5]);
            APPEND_RUNNING_CFG_1(" lacp partner admin-system-id %s\n",buff);
        }

        /*lacp partner admin-port*/
        if(LACP_POM_GetRunningDot3adAggPortPartnerAdminPort(ifindex,&partner_admin_port) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" lacp partner admin-port %d\n",partner_admin_port);
        }
#endif
    }
#endif /* #if (SYS_CPNT_LACP == TRUE) */

#if (SYS_CPNT_SWCTRL_SHUTDOWN_FOR_TRUNK_MEMBER == TRUE)
    /*switch control (overwrite trunk member config after channel-group)*/
    {
        Port_Info_T uport_info;
        Port_Info_T trunk_port_info;
        Port_Info_T *logical_port_info_p = &uport_info;

        memset (&uport_info, 0, sizeof(uport_info));
        if (SWCTRL_POM_GetRunningPortInfo(ifindex, &uport_info) == SYS_TYPE_GET_RUNNING_CFG_FAIL)
        {
            return buffer_count;
        }

        if (port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
        {
            memset (&trunk_port_info, 0, sizeof(trunk_port_info));

            if (SWCTRL_POM_GetRunningPortInfo(trunk_ifindex, &trunk_port_info) == SYS_TYPE_GET_RUNNING_CFG_FAIL)
            {
                return buffer_count;
            }

            logical_port_info_p = &trunk_port_info;
        }

        /*shutdown eth*/
        if (uport_info.admin_state != logical_port_info_p->admin_state)
        {
            if (uport_info.admin_state == VAL_ifAdminStatus_down)
            {
                APPEND_RUNNING_CFG_0(" shutdown\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no shutdown\n");
            }
        }
    }
#endif /* (SYS_CPNT_SWCTRL_SHUTDOWN_FOR_TRUNK_MEMBER == TRUE) */

#if (SYS_CPNT_APP_FILTER == TRUE)
    {
        AF_TYPE_STATUS_T status;

        if (AF_TYPE_SUCCESS == AF_PMGR_GetPortCdpStatus(ifindex, &status))
        {
            if (AF_TYPE_DISCARD == status)
            {
                APPEND_RUNNING_CFG_0(" discard cdp\n");
            }
        }

        if (AF_TYPE_SUCCESS == AF_PMGR_GetPortPvstStatus(ifindex, &status))
        {
            if (AF_TYPE_DISCARD == status)
            {
                APPEND_RUNNING_CFG_0(" discard pvst\n");
            }
        }

    }
#endif /* #if (SYS_CPNT_APP_FILTER == TRUE) */

    return buffer_count;
}


static UI32_T CLI_RUNCFG_Get_Ethernet_Parameter_One_Port(UI32_T unit_id, UI32_T port_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T  return_value;
    char    *str_list;
    char    *print_str;


    if( (str_list = calloc(512*4, sizeof(char))) == NULL )
    {   /*why allocate this number, because vlan list string may be too large*/
        /*so allocate such big memory to store this string*/
        return CLII_ERR_MEMORY_NOT_ENOUGH;
    }

    if( (print_str = calloc(CLI_DEF_MAX_BUFSIZE-38, sizeof(char))) == NULL )
    {
        free(str_list);
        return CLII_ERR_MEMORY_NOT_ENOUGH;
    }

    /* 2006/06/28
     * ES4649-38-00189: free memory before return
     */
    return_value = cli_runcfg_get_ethernet_parameter_one_port_macor(unit_id, port_id, buffer,
                    temp_buffer, buffer_size, b_count, str_list, print_str);

    free(print_str);
    free(str_list);
    return return_value;
}




static UI32_T CLI_RUNCFG_Get_Ethernet_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    /*interface ethernet config*/
    UI32_T buffer_count = b_count;
    UI32_T current_max_unit = 0;
    UI32_T port_id = 0;
    UI32_T max_port_num = 0;

#if (SYS_CPNT_STACKING == TRUE)
    current_max_unit = SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK;
#else
    current_max_unit = 1;
#endif

    for (unit_id = 1; unit_id <= current_max_unit; unit_id++)
    {
        if (STKTPLG_POM_UnitExist(unit_id) != TRUE)
        {
            continue;
        }

        max_port_num = SWCTRL_POM_UIGetUnitPortNumber(unit_id);

        for (port_id = 1 ; port_id <= max_port_num ; port_id++)/*the global loop of interface ethernet*/
        {
            /*Action*/
            buffer_count = CLI_RUNCFG_Get_Ethernet_Parameter_One_Port(unit_id, port_id, buffer, temp_buffer,
                                                buffer_size, buffer_count);
            /*For this issue ES4649-ZZ-00902 : Continuity PING will timeout if issue running configure
              Becase show running configure occupied much time and it's priority is higher, so we let it sleep.*/
            if (port_id == max_port_num/2)
            {
                // SYSFUN_Sleep(5);
            }

            APPEND_RUNNING_CFG_0("!\n");
        }/*the global loop of interface ethernet*/

        /*For this issue ES4649-ZZ-00902 : Continuity PING will timeout if issue running configure
        Becase show running configure occupied much time and it's priority is higher, so we let it sleep.
        */
        SYSFUN_Sleep(5);

    }/*end of the global loop of unit*/
#if RUNCFG_DEVELOP
    CLI_LIB_PrintStr("eth config complete\r\n");
#endif

    return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_Trunk_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                             UI32_T buffer_size, UI32_T b_count)
{
    UI32_T  buffer_count = b_count;
    UI32_T  trunk_id =0;

    for(trunk_id= 1;
        trunk_id<= SYS_ADPT_MAX_NBR_OF_TRUNK_PER_SYSTEM; trunk_id++)
    {
        buffer_count = CLI_RUNCFG_Get_Trunk_Parameter_Per_Trunk(trunk_id, buffer, temp_buffer,
                                                                buffer_size, buffer_count);
    }

#if RUNCFG_DEVELOP
    CLI_LIB_PrintStr("trunk config complete\r\n");
#endif
    return buffer_count;
}

static UI32_T
CLI_RUNCFG_Get_Control_Plane_Parameter(
    UI32_T unit_id,
    char *buffer,
    char *temp_buffer,
    UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
#if (SYS_CPNT_QOS_V2 == TRUE && SYS_CPNT_QOS_V2_CPU_PORT == TRUE)
    UI32_T ifindex;

    ifindex = SYS_ADPT_CPU_1_IF_INDEX_NUMBER;

    APPEND_RUNNING_CFG_0("!\n");
    APPEND_RUNNING_CFG_0("control-plane\n");

    {
        char   pmap [SYS_ADPT_DIFFSERV_MAX_NAME_LENGTH+1];

        /** The control plane means (phy) CPU port at egress direction
         */
        if ( L4_PMGR_QoS_GetRunningPolicyMapNameByPort ( ifindex, RULE_TYPE_OUTBOUND, pmap ) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS )
        {
            APPEND_RUNNING_CFG_1(" service-policy input %s\n", pmap );
        }
    }
#endif /* SYS_CPNT_QOS_V2 && SYS_CPNT_QOS_V2_CPU_PORT */

    return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_Trunk_Parameter_Per_Trunk(UI32_T trunk_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
#define APPEND_RUNNING_CFG_INTERFACE_PORT_CHANNEL_START() \
    do {                                            \
        if (!title_is_displayed)                    \
        {                                           \
            APPEND_RUNNING_CFG_1("interface port-channel %lu\n", (unsigned long)trunk_id); \
            title_is_displayed = TRUE;              \
        }                                           \
    } while (0)

#define APPEND_RUNNING_CFG_INTERFACE_PORT_CHANNEL_END() \
    do {                                            \
        if (title_is_displayed)                     \
        {                                           \
        }                                           \
    } while (0)

    UI32_T buffer_count = b_count;
    UI32_T trunk_ifindex  = 0;
    #if 0
    UI32_T queue,ret1, color = 0,dscp,cos,cfi,phb;  /*remove warring,because never used.*/
    #endif
    BOOL_T is_static;
    BOOL_T title_is_displayed = FALSE;

    /*interface-pchannel command*/
    SWCTRL_POM_TrunkIDToLogicalPort(trunk_id, &trunk_ifindex);

    /*-----------------------------------------------------
     * Configurations for all trunks
     *
     *   trunk might be not existed before provision
     *-----------------------------------------------------
     */

#if (SYS_CPNT_LACP == TRUE)
    /*lacp*/
    {
        UI16_T admin_key = 0;

        if (LACP_PMGR_GetRunningDot3adAggActorAdminKey(trunk_ifindex, &admin_key) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_INTERFACE_PORT_CHANNEL_START();
            APPEND_RUNNING_CFG_1(" lacp admin-key %d\n", admin_key);
        }
    }
    {
        UI32_T timeout;

        if (LACP_PMGR_GetRunningDot3adAggActorLACP_Timeout(trunk_ifindex,&timeout) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(timeout == LACP_LONG_TIMEOUT)
            {
                APPEND_RUNNING_CFG_INTERFACE_PORT_CHANNEL_START();
                APPEND_RUNNING_CFG_0(" lacp timeout long\n");
            }
            else if (timeout == LACP_SHORT_TIMEOUT)
            {
                APPEND_RUNNING_CFG_INTERFACE_PORT_CHANNEL_START();
                APPEND_RUNNING_CFG_0(" lacp timeout short\n");
            }
        }
    }
#endif

#if (SYS_CPNT_TRUNK_MAX_ACTIVE_PORTS_CONFIGURABLE == TRUE)
    {
        UI32_T max_num_of_active_ports;

        if (SWCTRL_POM_GetRunningTrunkMaxNumOfActivePorts(trunk_id, &max_num_of_active_ports) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_INTERFACE_PORT_CHANNEL_START();
            APPEND_RUNNING_CFG_1( " max-active-ports %lu\n", max_num_of_active_ports);
        }
    }
#endif /* (SYS_CPNT_TRUNK_MAX_ACTIVE_PORTS_CONFIGURABLE == TRUE) */

    /*-----------------------------------------------------
     * end of Configurations for all trunks
     *-----------------------------------------------------
     */



    /*-----------------------------------------------------
     * Configurations for static trunks
     *
     *   trunk must be existed before provision
     *-----------------------------------------------------
     */
    if (!TRK_PMGR_IsTrunkExist(trunk_id, &is_static))
    {
        APPEND_RUNNING_CFG_INTERFACE_PORT_CHANNEL_END();
        return buffer_count;
    }

    if (!is_static)
    {
        APPEND_RUNNING_CFG_INTERFACE_PORT_CHANNEL_END();
        return buffer_count;
    }

    APPEND_RUNNING_CFG_INTERFACE_PORT_CHANNEL_START();

/* Port Security */
#if (SYS_CPNT_PORT_SECURITY_TRUNK== TRUE)
#if (SYS_CPNT_PORT_SECURITY == TRUE)
#if (CLI_SUPPORT_PSEC_MAC_COUNT == 1)
        /*port sercrity*/
        {
            UI32_T port_security_status = 0;
            UI32_T mac_count = 0;

            if (PSEC_PMGR_GetRunningPortSecurityMacCount(trunk_ifindex, &mac_count) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_1(" port security max-mac-count %lu\n",mac_count);
            }

            if (PSEC_PMGR_GetRunningPortSecurityStatus(trunk_ifindex, &port_security_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if (port_security_status == VAL_portSecPortStatus_enabled)
                {
                    APPEND_RUNNING_CFG_0(" port security\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no port security\n");
                }
            }
        }

        /*port security action*/
        {
            UI32_T  action_status;

            if (PSEC_PMGR_GetRunningPortSecurityActionStatus(trunk_ifindex, &action_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                switch(action_status)
                {
                    case VAL_portSecAction_none:
                        APPEND_RUNNING_CFG_0(" no port security action\n");
                        break;

                    case VAL_portSecAction_trap:
                        APPEND_RUNNING_CFG_0(" port security action trap\n");
                        break;

                    case VAL_portSecAction_shutdown:
                        APPEND_RUNNING_CFG_0(" port security action shutdown\n");
                        break;

                    case VAL_portSecAction_trapAndShutdown:
                        APPEND_RUNNING_CFG_0(" port security action trap-and-shutdown\n");
                        break;

                    default:
                        break;
                }
            }
        } /*end - port security action*/
#else /*#if (CLI_SUPPORT_PSEC_MAC_COUNT != 1)*/
        /*port security*/
        {
            UI32_T port_security_status = 0;

            if (PSEC_PMGR_GetRunningPortSecurityStatus( trunk_ifindex, &port_security_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if (port_security_status == VAL_portSecPortStatus_enabled)
                {
                    APPEND_RUNNING_CFG_0(" port security\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0(" no port security\n");
                }
            }
        }
#endif /*#if (CLI_SUPPORT_PSEC_MAC_COUNT == 1)*/
#endif /*#if (SYS_CPNT_PORT_SECURITY == TRUE)*/
#endif



#if(SYS_CPNT_LLDP_MED == TRUE)
    /* lldp medTlv */
    {
        UI16_T  tlvs_tx_enabled;

        if (LLDP_PMGR_GetRunningXMedPortConfigTlvsTx(trunk_ifindex, &tlvs_tx_enabled) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(tlvs_tx_enabled & LLDP_TYPE_MED_CAP_TX)
            {
                if( !(LLDP_TYPE_DEFAULT_MED_TX & LLDP_TYPE_MED_CAP_TX) )
                {
                    APPEND_RUNNING_CFG_0(" lldp med-tlv med-cap\n");
                }
            }
            else
            {
                if( LLDP_TYPE_DEFAULT_MED_TX & LLDP_TYPE_MED_CAP_TX )
                {
                    APPEND_RUNNING_CFG_0(" no lldp med-tlv med-cap\n");
                }
            }

            if(tlvs_tx_enabled & LLDP_TYPE_MED_NETWORK_POLICY_TX)
            {
                if( !(LLDP_TYPE_DEFAULT_MED_TX & LLDP_TYPE_MED_NETWORK_POLICY_TX) )
                {
                    APPEND_RUNNING_CFG_0(" lldp med-tlv network-policy\n");
                }
            }
            else
            {
                if( LLDP_TYPE_DEFAULT_MED_TX & LLDP_TYPE_MED_NETWORK_POLICY_TX )
                {
                    APPEND_RUNNING_CFG_0(" no lldp med-tlv network-policy\n");
                }
            }

            if(tlvs_tx_enabled & LLDP_TYPE_MED_LOCATION_IDENT_TX)
            {
                if( !(LLDP_TYPE_DEFAULT_MED_TX & LLDP_TYPE_MED_LOCATION_IDENT_TX) )
                {
                    APPEND_RUNNING_CFG_0(" lldp med-tlv location\n");
                }
            }
            else
            {
                if( LLDP_TYPE_DEFAULT_MED_TX & LLDP_TYPE_MED_LOCATION_IDENT_TX )
                {
                    APPEND_RUNNING_CFG_0(" no lldp med-tlv location\n");
                }
            }

            if((tlvs_tx_enabled & LLDP_TYPE_MED_EXT_PD_TX)&&(tlvs_tx_enabled & LLDP_TYPE_MED_EXT_PSE_TX))
            {
                if( !((LLDP_TYPE_DEFAULT_MED_TX & LLDP_TYPE_MED_EXT_PD_TX)&&(LLDP_TYPE_DEFAULT_MED_TX & LLDP_TYPE_MED_EXT_PSE_TX))  )
                {
                    APPEND_RUNNING_CFG_0(" lldp med-tlv extPoe\n");
                }
            }
            else
            {
                if( (LLDP_TYPE_DEFAULT_MED_TX & LLDP_TYPE_MED_EXT_PD_TX)&&(LLDP_TYPE_DEFAULT_MED_TX & LLDP_TYPE_MED_EXT_PSE_TX) )
                {
                    APPEND_RUNNING_CFG_0(" no lldp med-tlv extPoe\n");
                }
            }

            if(tlvs_tx_enabled & LLDP_TYPE_MED_INVENTORY_TX)
            {
                if( !(LLDP_TYPE_DEFAULT_MED_TX & LLDP_TYPE_MED_INVENTORY_TX) )
                {
                    APPEND_RUNNING_CFG_0(" lldp med-tlv inventory\n");
                }
            }
            else
            {
                if( LLDP_TYPE_DEFAULT_MED_TX & LLDP_TYPE_MED_INVENTORY_TX )
                {
                    APPEND_RUNNING_CFG_0(" no lldp med-tlv inventory\n");
                }
            }
        }
    }
    /* lldp medNotification */
    {
        UI8_T  enabled;

        if (LLDP_PMGR_GetRunningXMedPortNotification(trunk_ifindex, &enabled) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (enabled == VAL_lldpXMedPortConfigNotifEnable_true)
            {
                APPEND_RUNNING_CFG_0(" lldp med-notification\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no lldp med-notification\n");
            }
        }
    }


    /*lldp medLocation*/
    {
        BOOL_T status;

        /*civic address*/
        LLDP_MGR_XMedLocationCivicAddrCaEntry_T ca_entry;
        UI8_T country_code[2], what;

        memset(&ca_entry, 0, sizeof(LLDP_MGR_XMedLocationCivicAddrCaEntry_T));
        if(LLDP_PMGR_GetXMedLocLocationStatus(trunk_ifindex, VAL_lldpXMedLocLocationSubtype_civicAddress,&status))
        {
            if(status==TRUE)
            {
                /*Country*/
                if (LLDP_PMGR_GetRunningXMedLocLocationCivicAddrCoutryCode(trunk_ifindex, country_code) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                    {
                        APPEND_RUNNING_CFG_2(" lldp med-location civic-addr country %.*s\n", 2, country_code);
                    }

                /*What*/
                if (LLDP_PMGR_GetRunningXMedLocLocationCivicAddrWhat(trunk_ifindex, &what)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                    {
                        APPEND_RUNNING_CFG_1(" lldp med-location civic-addr what %u\n", what);
                    }

                /*CA-TYPE 0*/
                if(LLDP_PMGR_Get1stXMedLocLocationCivicAddrCaEntry(trunk_ifindex,&ca_entry ))
                {
                    APPEND_RUNNING_CFG_3(" lldp med-location civic-addr %u %.*s\n", ca_entry.ca_type, ca_entry.ca_length, ca_entry.ca_value);
                }

                /*CA-TYPE 1~255*/
                while(LLDP_PMGR_GetNextXMedLocLocationCivicAddrCaEntry(trunk_ifindex, &ca_entry))
                {
                    APPEND_RUNNING_CFG_3(" lldp med-location civic-addr %u %.*s\n", ca_entry.ca_type, ca_entry.ca_length, ca_entry.ca_value);
                }
            }
        }
    }


#endif /*#if(SYS_CPNT_LLDP_MED == TRUE)*/

/* sync from ASE4512BBS-FLF-P5-01125
 */
#if 0
/*cfm*/
#if(SYS_CPNT_CFM==TRUE)
            /* Commands:
             * ethernet cfm mep mpid mpid ma ma-name [up]
             * no ethernet cfm mep mpid mpid ma ma-name
             */
             {
                CFM_OM_MepInfo_T  mep_p;
                UI32_T  md_index_p = 0;
                UI32_T  ma_index_p = 0;

                while(CFM_OM_GetNextRunnningMep(&md_index_p, &ma_index_p, trunk_ifindex, &mep_p)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
#if (SYS_CPNT_CFM_MA_NAME_UNIQUE_PER_DOMAIN == TRUE)
                    if(mep_p.direction==CFM_TYPE_MP_DIRECTION_DOWN)
                    {
                        APPEND_RUNNING_CFG_3("ethernet cfm mep mpid %lu md %s ma %s\n",
                                                mep_p.identifier, mep_p.md_name_a, mep_p.ma_name_a);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_3("ethernet cfm mep mpid %lu md %s ma %s up\n",
                                                mep_p.identifier, mep_p.ma_name_a, mep_p.ma_name_a);
                    }
#else
                    if(mep_p.direction==CFM_TYPE_MP_DIRECTION_DOWN)
                    {
                        APPEND_RUNNING_CFG_2("ethernet cfm mep mpid %lu ma %s\n",
                                                mep_p.identifier, mep_p.ma_name_a);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_2("ethernet cfm mep mpid %lu ma %s up\n",
                                                mep_p.identifier, mep_p.ma_name_a);
                    }
#endif /* #if (SYS_CPNT_CFM_MA_NAME_UNIQUE_PER_DOMAIN == TRUE) */
                }
            }

            /* Commands:
             * ethernet cfm port-enable
             * no ethernet cfm port-enable
             */
             {
                CFM_TYPE_CfmStatus_T  cfm_port_Status;

                if(CFM_OM_GetRunningCfmPortStatus( trunk_ifindex, &cfm_port_Status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    if(cfm_port_Status==CFM_TYPE_CFM_STATUS_ENABLE)
                    {
                        APPEND_RUNNING_CFG_0("ethernet cfm port-enable\n");
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_0("no ethernet cfm port-enable\n");
                    }
                }
            }
#endif /* #if(SYS_CPNT_CFM==TRUE) */
#endif /* #if 0 sync from ASE4512BBS-FLF-P5-01125 */

#if (SYS_CPNT_IF_LINK_TRAP_PORT_BASE == TRUE)
            {
                UI32_T  link_up_down_trap;

                if (IF_PMGR_GetRunningIfLinkUpDownTrapEnable(trunk_ifindex, &link_up_down_trap) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    if (link_up_down_trap == VAL_ifLinkUpDownTrapEnable_enabled)
                    {
                        APPEND_RUNNING_CFG_0(" snmp-server enable port-traps link-up-down\n");
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_0(" no snmp-server enable port-traps link-up-down\n");
                    }
                }
            }
#endif /* #if (SYS_CPNT_IF_LINK_TRAP_PORT_BASE == TRUE) */

#if (SYS_CPNT_IGMPAUTH== TRUE)
    {
        UI32_T status;

        if(IGMPSNP_PMGR_GetRunningIgmpAuthenticationStatus(trunk_ifindex, &status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(status == VAL_igmpSnoopAuthentication_enable)
            {
                APPEND_RUNNING_CFG_0(" ip igmp authentication\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no ip igmp authentication\n");
            }
        }
    }
#endif

#if (SYS_CPNT_ACL_UI == TRUE && SYS_CPNT_QOS_V2_TRUNK_PORT == TRUE)
    buffer_count = CLI_RUNCFG_Get_Access_Group_Parameter_By_Ifindex(trunk_ifindex,
                                                                    buffer,
                                                                    temp_buffer,
                                                                    buffer_size,
                                                                    buffer_count);
#endif /* SYS_CPNT_ACL_UI && SYS_CPNT_QOS_V2_TRUNK_PORT  */

#if (SYS_CPNT_QOS_V2 == TRUE && SYS_CPNT_QOS_V2_TRUNK_PORT == TRUE)
    {
        char policy_map_name[SYS_ADPT_DIFFSERV_MAX_NAME_LENGTH+1];

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == L4_PMGR_QoS_GetRunningPolicyMapNameByPort(trunk_ifindex, RULE_TYPE_INBOUND, policy_map_name))
        {
            APPEND_RUNNING_CFG_1(" service-policy input %s\n", policy_map_name);
        }
    }
#endif /* SYS_CPNT_QOS_V2 && SYS_CPNT_QOS_V2_TRUNK_PORT */

#if ((SYS_CPNT_INGRESS_RATE_LIMIT == TRUE) || (SYS_CPNT_EGRESS_RATE_LIMIT == TRUE))
    {
        Port_Info_T port_info;

        memset (&port_info , 0 , sizeof(Port_Info_T));
        if (SWCTRL_POM_GetRunningPortInfo(trunk_ifindex, &port_info) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
#if (SYS_CPNT_INGRESS_RATE_LIMIT == TRUE)
            if (port_info.ingress_rate_limit_status != SYS_DFLT_INGRESS_RATE_LIMIT_STATUS)
            {
                if (port_info.ingress_rate_limit_status == VAL_rlPortInputStatus_disabled)
                {
                    APPEND_RUNNING_CFG_0(" no rate-limit input\n");
                }
                else
                {
#ifdef SYS_ADPT_UI_RATE_LIMIT_FACTOR
                    APPEND_RUNNING_CFG_1(" rate-limit input %lu\n", (unsigned long)port_info.ingress_rate_limit/SYS_ADPT_UI_RATE_LIMIT_FACTOR);
#else
                    APPEND_RUNNING_CFG_1(" rate-limit input %lu\n", (unsigned long)port_info.ingress_rate_limit/1000);
#endif
                }
            }
#endif

#if (SYS_CPNT_EGRESS_RATE_LIMIT == TRUE)
            if (port_info.egress_rate_limit_status != SYS_DFLT_EGRESS_RATE_LIMIT_STATUS)
            {
                if (port_info.egress_rate_limit_status == VAL_rlPortOutputStatus_disabled)
                {
                    APPEND_RUNNING_CFG_0(" no rate-limit output\n");
                }
                else
                {
#ifdef SYS_ADPT_UI_RATE_LIMIT_FACTOR
                    APPEND_RUNNING_CFG_1(" rate-limit output %lu\n", (unsigned long)port_info.egress_rate_limit/SYS_ADPT_UI_RATE_LIMIT_FACTOR);
#else
                    APPEND_RUNNING_CFG_1(" rate-limit output %lu\n", (unsigned long)port_info.egress_rate_limit/1000);
#endif
                 }
             }
#endif
        }
    }
#endif /*#if ((SYS_CPNT_INGRESS_RATE_LIMIT == TRUE) || (SYS_CPNT_EGRESS_RATE_LIMIT == TRUE))*/

    APPEND_RUNNING_CFG_INTERFACE_PORT_CHANNEL_END();

#if RUNCFG_DEVELOP
    CLI_LIB_PrintStr("trunk config complete\r\n");
#endif
    return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_Loopback_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    UI32_T lo_id = 0;
    NETCFG_TYPE_InetRifConfig_T rif_config;
    NETCFG_TYPE_L3_Interface_T lo_intf;
    UI8_T mask[SYS_ADPT_IPV4_ADDR_LEN];

    memset(&rif_config, 0, sizeof(rif_config));
    memset(&lo_intf, 0, sizeof(lo_intf));

    while (NETCFG_TYPE_OK == NETCFG_POM_IP_GetNextL3Interface(&lo_intf))
    {
        if (lo_intf.ifindex < SYS_ADPT_LOOPBACK_IF_INDEX_NUMBER)
            continue;

        if (FALSE == IP_LIB_ConvertLoopbackIfindexToId(lo_intf.ifindex, &lo_id))
            continue;

        rif_config.ifindex = lo_intf.ifindex;

        APPEND_RUNNING_CFG_1("interface loopback %lu\n", (unsigned long)lo_id);

        while(NETCFG_TYPE_OK == NETCFG_POM_IP_GetNextInetRifOfInterface(&rif_config))
        {
            if (rif_config.ipv4_role == NETCFG_TYPE_MODE_PRIMARY)
            {
                IP_LIB_CidrToMask(rif_config.addr.preflen , mask);
                APPEND_RUNNING_CFG_4(" ip address %d.%d.%d.%d", rif_config.addr.addr[0], rif_config.addr.addr[1], rif_config.addr.addr[2], rif_config.addr.addr[3]);
                APPEND_RUNNING_CFG_4(" %d.%d.%d.%d\n", mask[0], mask[1], mask[2], mask[3]);
            }
            else if(rif_config.ipv4_role == NETCFG_TYPE_MODE_SECONDARY)
            {
                IP_LIB_CidrToMask(rif_config.addr.preflen , mask);
                APPEND_RUNNING_CFG_4(" ip address %d.%d.%d.%d", rif_config.addr.addr[0], rif_config.addr.addr[1], rif_config.addr.addr[2], rif_config.addr.addr[3]);
                APPEND_RUNNING_CFG_4(" %d.%d.%d.%d secondary\n", mask[0], mask[1], mask[2], mask[3]);
            }
        }

    }

    return buffer_count;
}


static UI32_T CLI_RUNCFG_Get_VLAN_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count, time_mark = 0, vid = 0;
#if (CLI_SUPPORT_L3_FEATURE == 1)
    UI32_T runcfg_my_unit_id = 0;
#endif

    while (VLAN_POM_GetNextVlanId(time_mark, &vid))
    {
        buffer_count =
            CLI_RUNCFG_Get_VLAN_Parameter_Per_VLAN(vid, buffer, temp_buffer, buffer_size, buffer_count);
    } /* while (VLAN_MGR_GetNextVlanId(time_mark, &vid)) */
    APPEND_RUNNING_CFG_0("!\n");
#if RUNCFG_DEVELOP
    CLI_LIB_PrintStr("VLAN config complete\r\n");
#endif

#if (CLI_SUPPORT_L3_FEATURE == 1)
    STKTPLG_OM_GetMyUnitID(&runcfg_my_unit_id);
    buffer_count = CLI_RUNCFG_Get_L3_Global_To_Router_Mode_Parameter(runcfg_my_unit_id, buffer, temp_buffer, buffer_size, buffer_count);
    CHECK_BUFF_RETURN_VALUE(buffer_count);
    APPEND_RUNNING_CFG_0("!\n");
#if RUNCFG_DEVELOP
    CLI_LIB_PrintStr("global configuration setting--ARP, RIP, OSPF, DVMRP, IGMP, enter router xxx mode\r\n");
#endif
#endif  /* #if (CLI_SUPPORT_L3_FEATURE == 1) */

    return buffer_count;
}




static UI32_T CLI_RUNCFG_Get_VLAN_Parameter_Per_VLAN(UI32_T vid, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
   UI32_T buffer_count = b_count;
#if (CLI_SUPPORT_L3_FEATURE == 1)
   UI32_T runcfg_my_unit_id   = 0;
#endif
   VLAN_TYPE_Vlan_RunningCfg_T vlan_cfg;
   UI32_T ifindex     = 0;
   NETCFG_TYPE_L3_Interface_T intf;

#if (CLI_SUPPORT_L3_FEATURE != 1)
//         UI32_T manage_vlan_ifindex = 0;
//         UI32_T manage_vid  = 0;

//         VLAN_POM_GetManagementVlan (&manage_vid);   /*shall be static VLAN*/

//         if (manage_vid != vid)
//            continue;  /*pttch,only one manage vlan, so only set one ip address,others bypass*/
#endif
         VLAN_VID_CONVERTTO_IFINDEX(vid, ifindex);
         memset(&intf, 0, sizeof(intf));
         intf.ifindex = ifindex;
         if (NETCFG_POM_IP_GetL3Interface(&intf) != NETCFG_TYPE_OK)
         {
            return buffer_count;
         }
         APPEND_RUNNING_CFG_1("interface vlan %lu\n", (unsigned long)vid);

#if (CLI_SUPPORT_L3_FEATURE == 1)
         STKTPLG_POM_GetMyUnitID(&runcfg_my_unit_id);
         buffer_count = CLI_RUNCFG_Get_L3_Per_Vlan_Parameter(vid, runcfg_my_unit_id, buffer, temp_buffer, buffer_size, buffer_count);
         CHECK_BUFF_RETURN_VALUE(buffer_count);
         /* EPR_ID:ES3628BT-FLF-ZZ-00391
                  * Problem: SNMP: SNMP: DUT can't save the ifalias value.
                  * Root Cause: call function "APPEND_RUNNING_CFG_0("!\n")" before alias's configuration.
                  * Solution: delete the APPEND_RUNNING_CFG_0("!\n").
                  * Modified files:
                  *     src\user\apps\cli\cli_runcfg.c
                  * Approved by: Tiger Liu, Hard Sun
                  * Modified by: Shumin Wang
                  */
         //APPEND_RUNNING_CFG_0("!\n");
#else
        /*ip address mode*/
        {
            NETCFG_TYPE_InetRifConfig_T rif_config;
            UI32_T  access_mode;
            UI32_T  ifindex;
            UI8_T  mask[SYS_ADPT_IPV4_ADDR_LEN];

            VLAN_VID_CONVERTTO_IFINDEX(vid, ifindex);
            memset(&rif_config, 0, sizeof(rif_config));
            rif_config.ifindex = ifindex;

            if (NETCFG_POM_IP_GetIpAddressMode(ifindex, &access_mode) == NETCFG_TYPE_OK)
            {
        switch(access_mode)
            {
                case NETCFG_TYPE_IP_ADDRESS_MODE_USER_DEFINE:

                /* get primary rif first */
                if(NETCFG_TYPE_OK == NETCFG_POM_IP_GetPrimaryRifFromInterface(&rif_config))
                {
                    if((rif_config.addr.type != L_INET_ADDR_TYPE_IPV4)
                        && (rif_config.addr.type != L_INET_ADDR_TYPE_IPV4Z))
                        break;

/*if support cfgdb ip address will not store in config file in l2 products*/
#if ((SYS_CPNT_CFGDB == FALSE)||(SYS_CPNT_NETCFG_IP_ADDRESS_IN_CFGDB == FALSE))
                        APPEND_RUNNING_CFG_4(" ip address %d.%d.%d.%d", rif_config.addr.addr[0], rif_config.addr.addr[1], rif_config.addr.addr[2], rif_config.addr.addr[3]);
                        IP_LIB_CidrToMask(rif_config.addr.preflen , mask);
                    APPEND_RUNNING_CFG_4(" %d.%d.%d.%d\n", mask[0], mask[1], mask[2], mask[3]);
#endif
                }

                    /* get secondary rif */
                    memset(&rif_config, 0, sizeof(rif_config));
                    rif_config.ifindex = ifindex;
                    while(NETCFG_TYPE_OK == NETCFG_POM_IP_GetNextSecondaryRifFromInterface(&rif_config))
                    {
                        if((rif_config.addr.type != L_INET_ADDR_TYPE_IPV4)
                            && (rif_config.addr.type != L_INET_ADDR_TYPE_IPV4Z))
                            break;

                        /*if support cfgdb ip address will not store in config file in l2 products*/
#if ((SYS_CPNT_CFGDB == FALSE)||(SYS_CPNT_NETCFG_IP_ADDRESS_IN_CFGDB == FALSE))
                        APPEND_RUNNING_CFG_4(" ip address %d.%d.%d.%d", rif_config.addr.addr[0], rif_config.addr.addr[1], rif_config.addr.addr[2], rif_config.addr.addr[3]);
                        IP_LIB_CidrToMask(rif_config.addr.preflen , mask);
                        APPEND_RUNNING_CFG_4(" %d.%d.%d.%d secondary\n", mask[0], mask[1], mask[2], mask[3]);
#endif
                    }

                        break;
#if (SYS_CPNT_DHCP_CLIENT == TRUE)
                    case NETCFG_TYPE_IP_ADDRESS_MODE_DHCP:
/*if support cfgdb ip address will not store in config file in l2 products*/
#if ((SYS_CPNT_CFGDB == FALSE)||(SYS_CPNT_NETCFG_IP_ADDRESS_IN_CFGDB == FALSE))
                        APPEND_RUNNING_CFG_0(" ip address dhcp\n");
#endif
                        break;
#endif

#if (SYS_CPNT_BOOTP == TRUE)
                    case NETCFG_TYPE_IP_ADDRESS_MODE_BOOTP:
/*if support cfgdb ip address will not store in config file in l2 products*/
#if ((SYS_CPNT_CFGDB == FALSE)||(SYS_CPNT_NETCFG_IP_ADDRESS_IN_CFGDB == FALSE))
                        APPEND_RUNNING_CFG_0(" ip address bootp\n");
#endif
                        break;
#endif

                    default:
                    break;
                }/*end of switch of type*/
                /*no matter which mode generate ip address first*/
            }
        }/*end of ip address*/
#endif

#if (CLI_SUPPORT_L2_DHCP_RELAY == 1)
#if 0//rich
   /*ip dhcp relay*/
   {
      BRG_MGR_DHCP_SETTING_FLAG_T status;
      if (BRG_PMGR_GetBridgeDHCPRelayVlanId(vid, &status) == TRUE)
      {
         if (status == BRG_MGR_DHCP_ENABLED)//temp
         {
            APPEND_RUNNING_CFG_0(" ip dhcp relay\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0(" no ip dhcp relay\n");
         }
      }
   }
#endif //rich
#endif
#if 0
#if (CLI_SUPPORT_DHCP_CLIENTID == 1)
/*ip dhcp clientid*/
      {
         UI32_T vid_ifIndex;
         UI8_T  temp_str[MAXSIZE_dhcpcIfClientId*2 + 1] = {0};

         DHCP_MGR_ClientId_T cid_p;
         VLAN_VID_CONVERTTO_IFINDEX(vid, vid_ifIndex);


         if (DHCP_PMGR_C_GetRunningClientId(vid_ifIndex, &cid_p) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            switch(cid_p.id_mode)
            {
            case DHCP_MGR_CID_HEX:
               {
                  UI32_T i;
                  UI8_T  buff[3] = {0};
                  for(i = 0; i < cid_p.id_len ; i++)
                  {
                     SYSFUN_Sprintf((char *)buff,"%02x",cid_p.id_buf[i]);
                     strcat((char *)temp_str,(char *)buff);
                  }
                  APPEND_RUNNING_CFG_1(" ip dhcp client-identifier hex %s\n",temp_str);
               }
               break;

            case DHCP_MGR_CID_TEXT:
               {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
               char     buf[CLI_DEF_MAX_BUFSIZE+1];

               CLI_LIB_Str_Add_Quote((char *)cid_p.id_buf,buf);
               APPEND_RUNNING_CFG_1(" ip dhcp client-identifier text %s\n",buf/*cid_p.id_buf*/);
#else
               APPEND_RUNNING_CFG_1(" ip dhcp client-identifier text %s\n",cid_p.id_buf);
#endif
               }
               break;

            default:
               break;
            }
         }
      }
#endif
#endif

#if (SYS_CPNT_DHCP_CLIENT_CLASSID == TRUE) /*option60 vendor class-id*/
{
    UI32_T vid_ifIndex;
    char   temp_str[DHCP_MGR_CLASSID_BUF_MAX_SIZE*2 + 1] = {0};
    DHCP_MGR_Vendor_T class_id;

    memset(&class_id, 0, sizeof(DHCP_MGR_Vendor_T));
    VLAN_VID_CONVERTTO_IFINDEX(vid, vid_ifIndex);

    if (DHCP_PMGR_C_GetRunningVendorClassId(vid_ifIndex, &class_id) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        /* if vendor class id is 0 , we should store 'no ip dhcp client class-id '*/
        if(class_id.vendor_len == 0)
        {
            APPEND_RUNNING_CFG_0(" no ip dhcp client class-id\n");
        }
        else
        {
            switch(class_id.vendor_mode)
            {
                case DHCP_MGR_CLASSID_HEX:
                {
                    UI32_T i;
                    char   buff[3] = {0};

                    for(i = 0; i < class_id.vendor_len ; i++)
                    {
                        SYSFUN_Sprintf(buff,"%02x",class_id.vendor_buf[i]);
                        strcat(temp_str,buff);
                    }

                    APPEND_RUNNING_CFG_1(" ip dhcp client class-id hex %s\n",temp_str);
                }
                break;

                case DHCP_MGR_CLASSID_TEXT:
                {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)

                    char  buf[CLI_DEF_MAX_BUFSIZE+1];

                    CLI_LIB_Str_Add_Quote((char *)class_id.vendor_buf,buf);
                    APPEND_RUNNING_CFG_1(" ip dhcp client class-id text %s\n",buf/*class_id.vendor_buf*/);
#else
                    APPEND_RUNNING_CFG_1(" ip dhcp client class-id text %s\n",class_id.vendor_buf);
#endif

                }
                break;
                default:
                break;
            }
        }

    }
}
#endif

/*EPR:ES4827G-FLF-ZZ-00232
 *Problem: CLI:size of vlan name different in console and mib
 *Solution: add CLI command "alias" for interface set,the
 *          alias is different from name and port descrition,so
 *          need add new command.
 *modify file: cli_cmd.c,cli_cmd.h,cli_arg.c,cli_arg.h,cli_msg.c,
 *             cli_msg.h,cli_api_vlan.c,cli_api_vlan.h,cli_api_ehternet.c
 *             cli_api_ethernet.h,cli_api_port_channel.c,cli_api_port_channel.h,
 *             cli_running.c,rfc_2863.c,swctrl.h,trk_mgr.h,trk_pmgr.h,swctrl.c
 *             swctrl_pmgr.c,trk_mgr.c,trk_pmgr.c,vlan_mgr.h,vlan_pmgr.h,
 *             vlan_type.h,vlan_mgr.c,vlan_pmgr.c,if_mgr.c
 *Approved by:Hardsun
 *Fixed by:Dan Xie
 */

/*for VLAN alias command*/
    {
        memset (&vlan_cfg,0,sizeof(VLAN_TYPE_Vlan_RunningCfg_T));
        if (VLAN_POM_GetRunningVlanParameters(vid, &vlan_cfg) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(vlan_cfg.alias_changed == TRUE)
            {
                APPEND_RUNNING_CFG_1(" alias %s\n",vlan_cfg.vlan_alias);
            }
        }
    }
         APPEND_RUNNING_CFG_0("!\n");

#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("vlan config complete\r\n");
#endif
   return buffer_count;
}

#if (SYS_CPNT_IP_TUNNEL == TRUE)
static UI32_T CLI_RUNCFG_Get_IpTunnel_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    NETCFG_TYPE_L3_Interface_T intf;
    UI32_T ifindex, u32_v,tid,vid;
    L_INET_AddrIp_T addr;
    char  str_ipv6_prefix[L_INET_MAX_IP6ADDR_STR_LEN+1] = {0};
    char  tmp_buf[L_INET_MAX_IP6ADDR_STR_LEN+1] = {0};
    NETCFG_TYPE_InetRifConfig_T rif,rif_tmp;

    memset(&intf, 0, sizeof(intf));
    while(NETCFG_TYPE_OK ==NETCFG_POM_IP_GetNextL3Interface(&intf))
    {
        if(!IS_TUNNEL_IFINDEX(intf.ifindex))
            continue;
         ifindex = intf.ifindex;
         IP_LIB_ConvertTunnelIdFromIfindex(ifindex,&tid);
        APPEND_RUNNING_CFG_1("interface tunnel %lu\n", tid);

         /* ipv6 address */
        memset(&rif, 0, sizeof(rif));
        rif.ifindex = ifindex;
        while(NETCFG_TYPE_OK == NETCFG_POM_IP_GetNextInetRifOfInterface(&rif))
        {
            if (L_INET_RETURN_SUCCESS != L_INET_InaddrToString((L_INET_Addr_T *)&rif.addr,
                                                               tmp_buf,
                                                               sizeof(tmp_buf)))
            {
                continue;
            }

            if((rif.addr.type == L_INET_ADDR_TYPE_IPV6Z)
                &&(NETCFG_TYPE_IPV6_ADDRESS_CONFIG_TYPE_MANUAL == rif.ipv6_addr_config_type))
            {

                APPEND_RUNNING_CFG_1(" ipv6 address %s link-local\n", tmp_buf);
            }
            else if((rif.addr.type == L_INET_ADDR_TYPE_IPV6)
                && (rif.ipv6_addr_type == NETCFG_TYPE_IPV6_ADDRESS_TYPE_EUI64)
                && (NETCFG_TYPE_IPV6_ADDRESS_CONFIG_TYPE_MANUAL == rif.ipv6_addr_config_type))
            {
                memcpy(&rif_tmp, &rif, sizeof(rif_tmp));
                if (TRUE == IP_LIB_GetPrefixAddr(rif.addr.addr, rif.addr.addrlen, rif.addr.preflen, rif_tmp.addr.addr))
                {
                    /* ipv6 perfix address*/
                    L_INET_InaddrToString((L_INET_Addr_T *)&rif_tmp.addr, str_ipv6_prefix, sizeof(str_ipv6_prefix));
                }
                APPEND_RUNNING_CFG_1(" ipv6 address %s eui-64\n", str_ipv6_prefix);
            }
            else if((rif.addr.type == L_INET_ADDR_TYPE_IPV6)
                &&(NETCFG_TYPE_IPV6_ADDRESS_CONFIG_TYPE_MANUAL == rif.ipv6_addr_config_type))
            {
                APPEND_RUNNING_CFG_1(" ipv6 address %s\n", tmp_buf);
            }
        }

        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_PMGR_IP_GetRunningTunnelSourceVlan(ifindex,&u32_v))
        {
            VLAN_OM_ConvertFromIfindex(u32_v, &vid);
            APPEND_RUNNING_CFG_1(" tunnel source vlan %ld\n", vid);
        }
        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_PMGR_IP_GetRunningTunnelDestination(ifindex,&addr))
        {
            if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&addr,
                                                               str_ipv6_prefix,
                                                               sizeof(str_ipv6_prefix)))
            {
                APPEND_RUNNING_CFG_1(" tunnel destination %s\n", str_ipv6_prefix);
            }
        }
        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_PMGR_IP_GetRunningTunnelMode(ifindex,&u32_v))
        {
            switch(u32_v)
            {
                case NETCFG_TYPE_TUNNEL_MODE_CONFIGURED:
                    APPEND_RUNNING_CFG_0(" tunnel mode ipv6ip configured\n");
                    break;
                case NETCFG_TYPE_TUNNEL_MODE_6TO4:
                    APPEND_RUNNING_CFG_0(" tunnel mode ipv6ip 6to4\n");
                    break;
                case NETCFG_TYPE_TUNNEL_MODE_ISATAP:
                    APPEND_RUNNING_CFG_0(" tunnel mode ipv6ip isatap\n");
                    break;
                default:
                    break;
            }
        }
        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_PMGR_IP_GetRunningTunnelTtl(ifindex,&u32_v))
        {
            APPEND_RUNNING_CFG_1(" tunnel ttl %ld\n", u32_v);
        }
         CHECK_BUFF_RETURN_VALUE(buffer_count);
        APPEND_RUNNING_CFG_0("!\n");
    }

   return buffer_count;
}
#endif /*SYS_CPNT_IP_TUNNEL*/
#if (SYS_CPNT_IPV6 == TRUE)
static UI32_T CLI_RUNCFG_Get_Global_To_Router_Mode_ParameterForIPv6(
    UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    UI32_T  buffer_count = b_count;

#if (SYS_CPNT_IPV6_ROUTING == TRUE)
    /* ipv6 unicast-routing */
    {
        BOOL_T ipv6_unicast_routing;
        UI32_T vr_id = 0;

        /* IPv6 unicast-routing */
        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_PMGR_ROUTE_GetRunningIpForwarding(vr_id, L_INET_ADDR_TYPE_IPV6, &ipv6_unicast_routing))
        {
            APPEND_RUNNING_CFG_1("%sipv6 unicast-routing\n", (ipv6_unicast_routing ? "": "no "));
        }
    }

    {
        UI32_T u32v;

        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==NETCFG_PMGR_ND_GetRunningNdHoplimit(&u32v))
            APPEND_RUNNING_CFG("ipv6 hop-limit %lu\n", (unsigned long)u32v);
    }

    {
        UI32_T                                      vid;
        NETCFG_TYPE_StaticIpNetToPhysicalEntry_T    entry;
        char                                        buf[L_INET_MAX_IPADDR_STR_LEN + 1];

        memset(&entry, 0, sizeof(entry));
        while(NETCFG_PMGR_ND_GetNextStaticIpv6NetToPhysicalEntry(&entry) == NETCFG_TYPE_OK)
        {
            if(!VLAN_OM_ConvertFromIfindex(entry.ip_net_to_physical_entry.ip_net_to_physical_if_index,&vid))
                continue;

            if (L_INET_RETURN_SUCCESS != L_INET_InaddrToString((L_INET_Addr_T*)&entry.ip_net_to_physical_entry.ip_net_to_physical_net_address,
                                                               buf,
                                                               sizeof(buf)))
            {
                continue;
            }

            APPEND_RUNNING_CFG("ipv6 neighbor %s vlan %ld %02x-%02x-%02x-%02x-%02x-%02x\n",buf,(long)vid,L_INET_EXPAND_MAC(entry.ip_net_to_physical_entry.ip_net_to_physical_phys_address.phy_address_cctet_string));
        }
    }
#endif

    return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_Per_Vlan_Parameter_ForIPv6(
    UI32_T vid_ifidx, UI32_T unit_id, char *buffer, char *temp_buffer,
    UI32_T buffer_size, UI32_T b_count)
{
    UI32_T              buffer_count = b_count;
    UI32_T              u32v;
#if (SYS_CPNT_IPV6_ROUTING == TRUE)
    UI32_T              u32v_2;
#endif

    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_POM_ND_GetRunningDADAttempts(vid_ifidx, &u32v))
    {
        APPEND_RUNNING_CFG(" ipv6 nd dad attempts %ld\n",(long)u32v);
    }

    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_POM_ND_GetRunningNdNsInterval(vid_ifidx, &u32v))
    {
        APPEND_RUNNING_CFG(" ipv6 nd ns-interval %ld\n",(long)u32v);
    }

    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_POM_ND_GetRunningNdReachableTime(vid_ifidx, &u32v))
    {
        if(u32v == 0)
            APPEND_RUNNING_CFG(" no ipv6 nd reachable-time\n");
        else
            APPEND_RUNNING_CFG(" ipv6 nd reachable-time %ld\n",(long)u32v);
    }

#if (SYS_CPNT_IPV6_ROUTING == TRUE)
    {
        L_INET_AddrIp_T     inetaddr;
        UI32_T              u32v_1, valid_lifetime, preferred_lifetime;
        BOOL_T              enable_onlink, enable_autoconf;
        BOOL_T              boolv, boolv_1 ;
        char                ipv6_addr_str[L_INET_MAX_IPADDR_STR_LEN+1];

        NETCFG_POM_ND_GetNdDefaultPrefixConfig(&valid_lifetime,&preferred_lifetime,&enable_onlink,&enable_autoconf);
        memset(&inetaddr,0,sizeof(inetaddr));
        while(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_PMGR_ND_GetNextRunningNdPrefix(vid_ifidx,&inetaddr,&u32v,&u32v_1,&boolv,&boolv_1))
        {
            if (L_INET_RETURN_SUCCESS != L_INET_InaddrToString((L_INET_Addr_T*)&inetaddr,
                                                               ipv6_addr_str,
                                                               sizeof(ipv6_addr_str)))
            {
                continue;
            }

            if(valid_lifetime ==u32v && preferred_lifetime == u32v_1 &&
                            enable_onlink == boolv && enable_autoconf == boolv)
            {
                APPEND_RUNNING_CFG(" ipv6 nd prefix %s default\n",ipv6_addr_str);
            }
            else
            {
                if (enable_onlink != boolv && boolv == FALSE)
                {
                    APPEND_RUNNING_CFG(" ipv6 nd prefix %s %ld %ld off-link\n",
                                                ipv6_addr_str, (long)u32v, (long)u32v_1);
                }
                else if (enable_autoconf != boolv_1 && boolv_1 == FALSE)
                {
                    APPEND_RUNNING_CFG(" ipv6 nd prefix %s %ld %ld no-autoconfig\n",
                                                ipv6_addr_str, (long)u32v, (long)u32v_1);
                }
                else
                {
                    APPEND_RUNNING_CFG(" ipv6 nd prefix %s %ld %ld\n",
                                                ipv6_addr_str, (long)u32v, (long)u32v_1);
                }
            }
        }

        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_PMGR_ND_GetRunningNdManagedConfigFlag(vid_ifidx, &boolv))
        {
            if(boolv)
                APPEND_RUNNING_CFG(" ipv6 nd managed-config-flag\n");
            else
                APPEND_RUNNING_CFG(" no ipv6 nd managed-config-flag\n");
        }
        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_PMGR_ND_GetRunningNdOtherConfigFlag(vid_ifidx, &boolv))
        {
            if(boolv)
                APPEND_RUNNING_CFG(" ipv6 nd other-config-flag\n");
            else
                APPEND_RUNNING_CFG(" no ipv6 nd other-config-flag\n");
        }
        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_PMGR_ND_GetRunningNdRaSuppress(vid_ifidx, &boolv))
        {
            if(boolv)
                APPEND_RUNNING_CFG(" ipv6 nd ra suppress\n");
            else
                APPEND_RUNNING_CFG(" no ipv6 nd ra suppress\n");
        }
        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_PMGR_ND_GetRunningNdRaLifetime(vid_ifidx, &u32v))
        {
            if(u32v != SYS_DFLT_ND_ROUTER_ADVERTISEMENTS_ROUTER_LIFETIME)
                APPEND_RUNNING_CFG(" ipv6 nd ra lifetime %lu\n",(unsigned long)u32v);
            else
                APPEND_RUNNING_CFG(" no ipv6 nd ra lifetime\n");
        }
        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_PMGR_ND_GetRunningNdRaInterval(vid_ifidx, &u32v, &u32v_2))
        {
            if(u32v   != SYS_DFLT_ND_ROUTER_ADVERTISEMENTS_MAX_TRANSMISSIONS_INTERVAL ||
               u32v_2 != SYS_DFLT_ND_ROUTER_ADVERTISEMENTS_MIN_TRANSMISSIONS_INTERVAL)
                APPEND_RUNNING_CFG(" ipv6 nd ra interval %lu %lu\n", (unsigned long)u32v, (unsigned long)u32v_2);
            else
                APPEND_RUNNING_CFG(" no ipv6 nd ra interval\n");
        }
        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_PMGR_ND_GetRunningNdRouterPreference(vid_ifidx, &u32v))
        {   //NETCFG_TYPE_ND_ROUTER_PERFERENCE_HIGH
            UI8_T preference_str[3][10]= {"medium","high","low"};

            if(u32v!=SYS_DFLT_ND_ROUTER_ADVERTISEMENTS_DEFAULT_ROUTER_PREFERENCE)
                APPEND_RUNNING_CFG(" ipv6 nd router-preference %s\n",preference_str[u32v]);
            else
                APPEND_RUNNING_CFG(" no ipv6 nd ra interval\n");
        }
    }
#endif /* #if (SYS_CPNT_IPV6_ROUTING == TRUE) */

    return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_IPV6_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    UI32_T time_mark   = 0;
    UI32_T vid         = 0;
    UI32_T ifindex     = 0;
    NETCFG_TYPE_L3_Interface_T intf;

    BOOL_T ipv6_enable, ipv6_addr_autoconfig;
    UI32_T ipv6_forwarding_status;
    NETCFG_TYPE_InetRifConfig_T inet_rif, rif_tmp;
    char   tmp_buf[L_INET_MAX_IP6ADDR_STR_LEN+1] = {0};
    char   str_ipv6_prefix[L_INET_MAX_IP6ADDR_STR_LEN+1] = {0};
    UI32_T intf_mtu;
#if (SYS_CPNT_IPV6_ROUTING == FALSE)
    L_INET_AddrIp_T ipv6_default_gateway;
#endif

    while(VLAN_POM_GetNextVlanId(time_mark, &vid))
    {
        VLAN_OM_ConvertToIfindex(vid, &ifindex);
        memset(&intf, 0, sizeof(intf));
        intf.ifindex = ifindex;
        if (NETCFG_POM_IP_GetL3Interface(&intf) != NETCFG_TYPE_OK)
        {
            continue;
        }
        APPEND_RUNNING_CFG_1("interface vlan %lu\n", (unsigned long)vid);


        /* ipv6 enable */
        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_POM_IP_GetRunningIPv6EnableStatus(ifindex,&ipv6_enable))
        {
            APPEND_RUNNING_CFG_1(" %sipv6 enable\n", (ipv6_enable ? "": "no "));
        }

        /* ipv6 address */
        memset(&inet_rif, 0, sizeof(inet_rif));
        inet_rif.ifindex = ifindex;
        while(NETCFG_TYPE_OK == NETCFG_POM_IP_GetNextInetRifOfInterface(&inet_rif))
        {
            if((inet_rif.addr.type == L_INET_ADDR_TYPE_IPV6Z)
                &&(NETCFG_TYPE_IPV6_ADDRESS_CONFIG_TYPE_MANUAL == inet_rif.ipv6_addr_config_type))
            {
                L_INET_Ntop(L_INET_AF_INET6, inet_rif.addr.addr, (char*)tmp_buf, sizeof(tmp_buf));
                APPEND_RUNNING_CFG_1(" ipv6 address %s link-local\n", tmp_buf);
            }
            else if((inet_rif.addr.type == L_INET_ADDR_TYPE_IPV6)
                && (inet_rif.ipv6_addr_type == NETCFG_TYPE_IPV6_ADDRESS_TYPE_EUI64)
                && (NETCFG_TYPE_IPV6_ADDRESS_CONFIG_TYPE_MANUAL == inet_rif.ipv6_addr_config_type))
            {
                memcpy(&rif_tmp, &inet_rif, sizeof(rif_tmp));
                if (TRUE == IP_LIB_GetPrefixAddr(inet_rif.addr.addr, inet_rif.addr.addrlen, inet_rif.addr.preflen, rif_tmp.addr.addr))
                {
                    /* ipv6 perfix address*/
                    L_INET_InaddrToString((L_INET_Addr_T *)&rif_tmp.addr, str_ipv6_prefix, sizeof(str_ipv6_prefix));
                }
                APPEND_RUNNING_CFG_1(" ipv6 address %s eui-64\n", str_ipv6_prefix);
            }
            else if((inet_rif.addr.type == L_INET_ADDR_TYPE_IPV6)
                &&(NETCFG_TYPE_IPV6_ADDRESS_CONFIG_TYPE_MANUAL == inet_rif.ipv6_addr_config_type))
            {
                if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&inet_rif.addr,
                                                                   tmp_buf,
                                                                   sizeof(tmp_buf)))
                {
                    APPEND_RUNNING_CFG_1(" ipv6 address %s\n", tmp_buf);
                }
            }
        } /* while */
        /* IPv6 interface MTU */
        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_POM_IP_GetRunningIPv6InterfaceMTU(ifindex, &intf_mtu))
        {
            APPEND_RUNNING_CFG_1(" ipv6 mtu %ld\n", (long)intf_mtu);
        }

        /* ipv6 autoconfig config is only for L2 device */
        {
            NETCFG_OM_ROUTE_IpForwardingStatus_T ifs;
            ifs.vr_id = SYS_DFLT_VR_ID;
            if((NETCFG_POM_ROUTE_GetIpForwardingStatus(&ifs) == NETCFG_TYPE_OK)
                && (ifs.status_bitmap & NETCFG_MGR_ROUTE_FLAGS_IPV6) == 0)
            {
                /* ipv6 address autoconfig */
                if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_POM_IP_GetRunningIPv6AddrAutoconfigEnableStatus(ifindex,&ipv6_addr_autoconfig))
                {
                    APPEND_RUNNING_CFG_1(" %sipv6 address autoconfig\n", (ipv6_addr_autoconfig ? "": "no "));
                }
            }
        }

        buffer_count = CLI_RUNCFG_Get_Per_Vlan_Parameter_ForIPv6(
                            ifindex, unit_id, buffer, temp_buffer, buffer_size, buffer_count);

#if (SYS_CPNT_OSPF6 == TRUE)
        {
            UI32_T find_ospf6;
            OSPF6_TYPE_Interface_T if_entry;
            OSPF6_MGR_OSPF_ENTRY_T ospf6;
            OSPF6_TYPE_IfParam_T entry;
            char buf[50] = {0};
            char buf_instance[20] = {};

            find_ospf6 = FALSE;
            memset(&ospf6, 0, sizeof(OSPF6_MGR_OSPF_ENTRY_T));
            ospf6.is_first = TRUE;  /* to get the first process */
            while(OSPF6_PMGR_Process_GetNext(&ospf6) == OSPF6_TYPE_RESULT_SUCCESS)
            {
                memset(&if_entry, 0, sizeof(OSPF6_TYPE_Interface_T));
                if_entry.ifindex = ifindex;
                strncpy(if_entry.tag, ospf6.tag, strlen(ospf6.tag));
                if ( OSPF6_PMGR_Interface_Get(&if_entry) == OSPF6_TYPE_RESULT_SUCCESS)
                {
                    memset(&entry, 0, sizeof(OSPF6_TYPE_IfParam_T));
                    entry.ifindex = ifindex;
                    entry.instance_id = if_entry.instance_id;
                    strncpy(entry.tag, ospf6.tag, strlen(ospf6.tag));
                    if(OSPF6_PMGR_IfParam_Get(&entry) == OSPF6_TYPE_RESULT_SUCCESS)
                    {
                        find_ospf6 = TRUE;
                        break;
                    }
                }
            }
            if ( find_ospf6 )
            {
                if (entry.instance_id)
                    sprintf(buf_instance, " instance %lu", (unsigned long)entry.instance_id);

                /* Area */
                if (entry.tag[0] != '\0')
                    sprintf(buf, " ipv6 ospf %s", entry.tag);
                else
                    sprintf(buf, " ipv6 ospf");

                sprintf(buf + strlen(buf), "%s", buf_instance);
                APPEND_RUNNING_CFG_1("%s\r\n", buf);

                snprintf (buf, 50, " ipv6 ospf");
            }
       }

#endif /* #if (SYS_CPNT_OSPF6 == TRUE) */

        APPEND_RUNNING_CFG_0("!\n");
    } /* while */

#if (SYS_CPNT_IPV6_ROUTING == TRUE)
    { /* ipv6 route */
        NETCFG_TYPE_IpCidrRouteEntry_T  route_entry;

        memset(&route_entry, 0, sizeof(NETCFG_TYPE_IpCidrRouteEntry_T));
        route_entry.route_dest.type = L_INET_ADDR_TYPE_IPV6;
        while(NETCFG_POM_ROUTE_GetNextRunningStaticIpCidrRouteEntry(&route_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (route_entry.ip_cidr_route_status != NETCFG_TYPE_StaticIpCidrEntryRowStatus_active)
                continue;

            L_INET_InprefixToString((L_INET_Addr_T *)&route_entry.route_dest, sizeof(tmp_buf), tmp_buf);
            APPEND_RUNNING_CFG_1("ipv6 route %s ", tmp_buf);
            if(route_entry.ip_cidr_route_type == VAL_ipCidrRouteType_local &&
                route_entry.ip_cidr_route_if_index!=0)
            {
                UI32_T vtid;
#if (SYS_CPNT_IP_TUNNEL == TRUE)

                if(IS_TUNNEL_IFINDEX(route_entry.ip_cidr_route_if_index))
                {
                    IP_LIB_ConvertTunnelIdFromIfindex(route_entry.ip_cidr_route_if_index, &vtid);
                    APPEND_RUNNING_CFG_1("tunnel %ld ", (long)vtid);
                }
                else
#endif /*SYS_CPNT_IP_TUNNEL*/
                {
                    VLAN_OM_ConvertFromIfindex(route_entry.ip_cidr_route_if_index, &vtid);
                    APPEND_RUNNING_CFG_1("vlan %ld ", (long)vtid);
                }
            }
            else
            {
                if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&route_entry.route_next_hop,
                                                                   tmp_buf,
                                                                   sizeof(tmp_buf)))
                {
                    APPEND_RUNNING_CFG_1("%s ", tmp_buf);
                }
            }
            if (route_entry.ip_cidr_route_distance > SYS_ADPT_MIN_ROUTE_DISTANCE)
            {
                APPEND_RUNNING_CFG_1("%ld", (long)route_entry.ip_cidr_route_distance);
            }
            APPEND_RUNNING_CFG_0("\n");

        }
    }
#endif /* #if (SYS_CPNT_IPV6_ROUTING == TRUE) */

#if (SYS_CPNT_IPV6_ROUTING == FALSE) /* ipv6 default-gateway for L2 */
    /* IPv6 default-gateway */
    memset(&ipv6_default_gateway, 0, sizeof(ipv6_default_gateway));
    ipv6_default_gateway.type = L_INET_ADDR_TYPE_IPV6;
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_POM_ROUTE_GetRunningDefaultGateway(&ipv6_default_gateway))
    {
        if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&ipv6_default_gateway,
                                                           tmp_buf,
                                                           sizeof(tmp_buf)))
        {
            APPEND_RUNNING_CFG_1(" ipv6 default-gateway %s\n", tmp_buf);
        }
    }
#endif

    buffer_count = CLI_RUNCFG_Get_Global_To_Router_Mode_ParameterForIPv6
                    (unit_id, buffer, temp_buffer, buffer_size, buffer_count);

    return buffer_count;
}
#endif/* SYS_CPNT_IPV6 == TRUE */

extern int getEth0IpAddr
(
    char *      devName,                /* device name e.g. "eth" */
    int         unit,
    int *  ipAddr,
    int *  netmask,
    int*   flag
);

/*fuzhimin,20090212*/
#if (SYS_CPNT_IP_FOR_ETHERNET0 == TRUE)
static UI32_T CLI_RUNCFG_Get_Ethernet0_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    int ipAddr = 0;
    int netMask = 0;
    int flag = 0;

    getEth0IpAddr("eth",0,&ipAddr,&netMask,&flag);

    if(flag & IFF_UP)
    {
        APPEND_RUNNING_CFG_0("interface ethernet0\n");

        APPEND_RUNNING_CFG_4(" ip address %d.%d.%d.%d",
        (ipAddr&0xff000000)>>24, (ipAddr&0xff0000)>>16, (ipAddr&0xff00)>>8, (ipAddr&0xff));
        APPEND_RUNNING_CFG_4(" %d.%d.%d.%d\n", (netMask&0xff000000)>>24, (netMask&0xff0000)>>16, (netMask&0xff00)>>8, (netMask&0xff));

    }

    APPEND_RUNNING_CFG_0("!\n");
    return buffer_count;

}
#endif
/*fuzhimin,20090212,end*/

#if (SYS_CPNT_NSM_POLICY == TRUE)
static UI32_T CLI_RUNCFG_Get_NSM_Policy_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;

#if 0 //TODO
    BGP_TYPE_CommunityList_T clist;
    BGP_TYPE_CommunityEntry_T centry;
    memset(&clist, 0, sizeof(clist));
    while(BGP_PMGR_GetNextIpCommunityList(&clist) == BGP_TYPE_RESULT_OK)
    {

        memset(&centry, 0, sizeof(centry));
        strncpy(centry.list_name, clist.name, sizeof(centry.list_name));
        while (BGP_PMGR_GetNextIpCommunityListEntry(&centry) == BGP_TYPE_RESULT_OK)
        {
            if (clist.sort == BGP_TYPE_COMMUNITY_LIST_NUMBER)
                APPEND_RUNNING_CFG("ip community-list %s", clist.name);
            else
            {
                if(centry.style == BGP_TYPE_COMMUNITY_LIST_STANDARD)
                    APPEND_RUNNING_CFG("ip community standard %s",clist.name);
                else
                    APPEND_RUNNING_CFG("ip community expanded %s",clist.name);
            }

            if (centry.any)
                APPEND_RUNNING_CFG(" %s\n", centry.direct ? "permit": "deny");
            else
            {
                char buf[BGP_TYPE_COMMUNITY_STR_LEN +1] = {};
                APPEND_RUNNING_CFG(" %s", centry.direct ? "permit": "deny");
                if(centry.style == BGP_TYPE_COMMUNITY_LIST_STANDARD)
                {
                    /* convert local-AS to local-as */
                    CLI_API_Conver_Lower_Case(centry.u.com.str, buf);

                    APPEND_RUNNING_CFG(" %s\n", buf);
                }
                else
                    APPEND_RUNNING_CFG(" %s\n", centry.config);
            }
        } /* while */
    } /* while */

    memset(&clist, 0, sizeof(clist));
    while(BGP_PMGR_GetNextIpExtCommunityList(&clist) == BGP_TYPE_RESULT_OK)
    {

        memset(&centry, 0, sizeof(centry));
        strncpy(centry.list_name, clist.name, sizeof(centry.list_name));
        while (BGP_PMGR_GetNextIpExtCommunityListEntry(&centry) == BGP_TYPE_RESULT_OK)
        {
            if (clist.sort == BGP_TYPE_COMMUNITY_LIST_NUMBER)
                APPEND_RUNNING_CFG("ip extcommunity-list %s", clist.name);
            else
            {
                if(centry.style == BGP_TYPE_EXTCOMMUNITY_LIST_STANDARD)
                    APPEND_RUNNING_CFG("ip extcommunity-list standard %s",clist.name);
                else
                    APPEND_RUNNING_CFG("ip extcommunity-list expanded %s",clist.name);
            }

            if (centry.any)
                APPEND_RUNNING_CFG(" %s\n", centry.direct ? "permit": "deny");
            else
            {
                APPEND_RUNNING_CFG(" %s", centry.direct ? "permit": "deny");
                APPEND_RUNNING_CFG(" %s\n", centry.config);
            }
        } /* while */
    }
    /* as-path access-list */
    {
        BGP_TYPE_AsList_T as_list;
        BGP_TYPE_AsFilter_T as_filter;

        memset(&as_list, 0, sizeof(as_list));

        while(BGP_PMGR_GetNextIpAsPathList(&as_list) == BGP_TYPE_RESULT_OK)
        {

            memset(&as_filter, 0, sizeof(as_filter));
            strncpy(as_filter.as_list_name, as_list.name, sizeof(as_filter.as_list_name));

            while(BGP_PMGR_GetNextIpAsPathListEntry(&as_filter) == BGP_TYPE_RESULT_OK)
            {
                APPEND_RUNNING_CFG("ip as-path access-list %s %s %s\n",
                        as_filter.as_list_name,
                        (as_filter.filter_type == BGP_TYPE_AS_FILTER_PERMIT)? "permit": "deny",
                        as_filter.reg_str);
            }
        }
    }
    /* ip prefix-list */
    {
        NSM_POLICY_TYPE_PrefixList_T plist;
        NSM_POLICY_TYPE_PrefixListEntry_T pentry;
        //char buf[L_INET_MAX_IPADDR_STR_LEN] = {};
        UI8_T arr_mask[SYS_ADPT_IPV4_ADDR_LEN] = {};

        memset(&plist, 0, sizeof(plist));

        while(BGP_PMGR_GetNextIpPrefixList(&plist) == BGP_TYPE_RESULT_OK)
        {
            memset(&pentry, 0, sizeof(pentry));
            strncpy(pentry.plist_name, plist.name, sizeof(pentry.plist_name));

            while(BGP_PMGR_GetNextIpPrefixListEntry(&pentry) == BGP_TYPE_RESULT_OK)
            {
                APPEND_RUNNING_CFG("ip prefix-list %s seq %lu %s",
                        pentry.plist_name,
                        (unsigned long)pentry.seq,
                        (pentry.type == NSM_POLICY_TYPE_PREFIX_PERMIT)? "permit": "deny");

                if(pentry.any)
                {
                    APPEND_RUNNING_CFG(" any");
                }
                else
                {
                    APPEND_RUNNING_CFG(" %d.%d.%d.%d",
                            pentry.prefix.addr[0], pentry.prefix.addr[1], pentry.prefix.addr[2], pentry.prefix.addr[3]);
                    IP_LIB_CidrToMask(pentry.prefix.preflen, arr_mask);

                    APPEND_RUNNING_CFG(" %d.%d.%d.%d",
                            arr_mask[0], arr_mask[1], arr_mask[2], arr_mask[3]);
                    if(pentry.ge)
                        APPEND_RUNNING_CFG(" ge %lu", (unsigned long)pentry.ge);
                    if(pentry.le)
                        APPEND_RUNNING_CFG(" le %lu", (unsigned long)pentry.le);
                }
                APPEND_RUNNING_CFG("\n");

            }
        }
    }
    /* route-map */
    {
        NSM_POLICY_TYPE_RouteMap_T rmap;
        NSM_POLICY_TYPE_RouteMapIndex_T rmap_index;
        NSM_POLICY_TYPE_RouteMapRule_T rmap_rule; /* match or set */
        memset(&rmap, 0, sizeof(rmap));

        while(BGP_PMGR_GetNextRouteMap(&rmap) == BGP_TYPE_RESULT_OK)
        {
            memset(&rmap_index, 0, sizeof(rmap_index));
            strncpy(rmap_index.map_name, rmap.name, sizeof(rmap_index.map_name));

            while(BGP_PMGR_GetNextRouteMapIndex(&rmap_index) == BGP_TYPE_RESULT_OK)
            {

                APPEND_RUNNING_CFG("route-map %s %s %d\n",
                   rmap.name,
                   (rmap_index.type == NSM_POLICY_TYPE_RMAP_PERMIT) ? "permit":"deny",
                   rmap_index.pref);

                /* Description */
                if(rmap_index.description[0] != '\0')
                    APPEND_RUNNING_CFG(" description %s\n", rmap_index.description);

                /* Match clauses */

                memset(&rmap_rule, 0, sizeof(rmap_rule));
                strncpy(rmap_rule.map_name, rmap.name, sizeof(rmap_rule.map_name));
                rmap_rule.index_type = rmap_index.type;
                rmap_rule.index_pref = rmap_index.pref;

                while(BGP_PMGR_GetNextRouteMapMatch(&rmap_rule) == BGP_TYPE_RESULT_OK)
                {
                    APPEND_RUNNING_CFG(" match %s %s\n",
                        rmap_rule.cmd_str, rmap_rule.rule_str);

                }
                memset(&rmap_rule, 0, sizeof(rmap_rule));
                strncpy(rmap_rule.map_name, rmap.name, sizeof(rmap_rule.map_name));
                rmap_rule.index_type = rmap_index.type;
                rmap_rule.index_pref = rmap_index.pref;

                while(BGP_PMGR_GetNextRouteMapSet(&rmap_rule) == BGP_TYPE_RESULT_OK)
                {
                    char str_additive[] = "additive";
                    char *pch;

                    if(!strncmp(rmap_rule.cmd_str, "community", 9))
                    {
                        /* move "additive" from end to begin position */
                        pch = strstr(rmap_rule.rule_str, str_additive);
                        if(pch)
                        {
                            *pch= '\0';
                            APPEND_RUNNING_CFG(" set %s additive %s\n", rmap_rule.cmd_str, rmap_rule.rule_str);
                        }
                        else
                            APPEND_RUNNING_CFG(" set %s %s\n", rmap_rule.cmd_str, rmap_rule.rule_str);
                    }
                    else
                        APPEND_RUNNING_CFG(" set %s %s\n", rmap_rule.cmd_str, rmap_rule.rule_str);


                }

                /* Call clause */
                if (rmap_index.nextrm[0] != '\0')
                    APPEND_RUNNING_CFG(" call %s\n", rmap_index.nextrm);

                /* Exit Policy */
                if (rmap_index.exitpolicy == NSM_POLICY_TYPE_RMAP_GOTO)
                    APPEND_RUNNING_CFG(" on-match goto %d\n", rmap_index.nextpref);
                else if (rmap_index.exitpolicy == NSM_POLICY_TYPE_RMAP_NEXT)
                    APPEND_RUNNING_CFG(" on-match next\n");

                APPEND_RUNNING_CFG_0("!\n");
            } /* while */
        } /* while */
    }
#endif

    return buffer_count;
}
#endif /* SYS_CPNT_NSM_POLICY */

#if (SYS_CPNT_CRAFT_PORT == TRUE)
static UI32_T CLI_RUNCFG_Get_CraftPort_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    BOOL_T ipv6_enable;
    NETCFG_TYPE_CraftInetAddress_T craft_addr;
    char   tmp_buf[L_INET_MAX_IPADDR_STR_LEN+1] = {0};

    APPEND_RUNNING_CFG_0("interface craft\n");

    memset(&craft_addr, 0, sizeof(craft_addr));
    craft_addr.addr.type = L_INET_ADDR_TYPE_IPV4;
    if(NETCFG_TYPE_OK == NETCFG_POM_IP_GetCraftInterfaceInetAddress(&craft_addr)
        && craft_addr.ifindex !=0)
    {
        UI8_T mask[SYS_ADPT_IPV4_ADDR_LEN] = {};
        IP_LIB_CidrToMask(craft_addr.addr.preflen , mask);

        APPEND_RUNNING_CFG_4(" ip address %d.%d.%d.%d",
            craft_addr.addr.addr[0],
            craft_addr.addr.addr[1],
            craft_addr.addr.addr[2],
            craft_addr.addr.addr[3]);
        APPEND_RUNNING_CFG_4(" %d.%d.%d.%d\n",
            mask[0],
            mask[1],
            mask[2],
            mask[3]);
    }

    if(NETCFG_TYPE_OK == NETCFG_POM_IP_GetIPv6EnableStatus_Craft(SYS_ADPT_CRAFT_INTERFACE_IFINDEX, &ipv6_enable)
        && ipv6_enable)
    {
        APPEND_RUNNING_CFG(" ipv6 enable\n");
    }

    memset(&craft_addr, 0, sizeof(craft_addr));
    craft_addr.addr.type = L_INET_ADDR_TYPE_IPV6Z;
    if(NETCFG_TYPE_OK == NETCFG_POM_IP_GetCraftInterfaceInetAddress(&craft_addr)
        && craft_addr.ifindex !=0
        && craft_addr.addr.type == L_INET_ADDR_TYPE_IPV6Z
        && craft_addr.ipv6_addr_config_type == NETCFG_TYPE_IPV6_ADDRESS_CONFIG_TYPE_MANUAL)

    {
        if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&craft_addr.addr,
                                                           tmp_buf,
                                                           sizeof(tmp_buf)))
        {
            APPEND_RUNNING_CFG_1(" ipv6 address %s link-local\n", tmp_buf);
        }
    }

    memset(&craft_addr, 0, sizeof(craft_addr));
    craft_addr.addr.type = L_INET_ADDR_TYPE_IPV6;
    if(NETCFG_TYPE_OK == NETCFG_POM_IP_GetCraftInterfaceInetAddress(&craft_addr)
        && craft_addr.ifindex !=0
        && craft_addr.addr.type == L_INET_ADDR_TYPE_IPV6
        && craft_addr.ipv6_addr_config_type == NETCFG_TYPE_IPV6_ADDRESS_CONFIG_TYPE_MANUAL)

    {
        if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&craft_addr.addr,
                                                           tmp_buf,
                                                           sizeof(tmp_buf)))
        {
            APPEND_RUNNING_CFG_1(" ipv6 address %s\n", tmp_buf);
        }
    }

    APPEND_RUNNING_CFG_0("!\n");
    return buffer_count;

}
#endif //SYS_CPNT_CRAFT_PORT

static UI32_T CLI_RUNCFG_Get_PFU_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
   UI32_T buffer_count = b_count;
#if (SYS_CPNT_PFU == TRUE)
   /*for ip filter command*/
   {
      UI8_T *str[] =
      {
         "fin",
         "syn",
         "rst",
         "psh",
         "ack",
         "urg"};
      UI32_T temp  = 0;
      UI32_T unused_rules = 0;
      UI32_T index = 0;
      UI8_T  temp_string[16] = {0};
      UI8_T  buff[CLI_DEF_MAX_BUFSIZE] = {0};
      PFU_TYPE_RuleEntry_T rule;

      memset(&rule, 0, sizeof(rule));
      while(PFU_PMGR_GetNextRunningRuleEntry(&index,&rule) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         memset(temp_string, 0, sizeof(temp_string));
         memset(buff, 0, sizeof(buff));

         if (rule.pfu_row_status != VAL_pfuRuleRowStatus_active)
         {/*for checking rule is creating by snmp*/
            unused_rules++;
            continue;
         }
         strcat((char *)buff, "ip filter");
         SYSFUN_Sprintf((char *)temp_string, " %lu",rule.pfu_rule_precedence - unused_rules);
         strcat((char *)buff, (char *)temp_string);

         switch(rule.pfu_rule_action)
         {
         case VAL_pfuRuleAction_permit:
            SYSFUN_Sprintf((char *)temp_string, " %s","permit");
            strcat((char *)buff, (char *)temp_string);
            break;

         case VAL_pfuRuleAction_deny:
            SYSFUN_Sprintf((char *)temp_string, " %s","deny");
            strcat((char *)buff, (char *)temp_string);
            break;

         default:
            break;
         }

         switch(rule.pfu_protocol)
         {
         case PFU_TYPE_TCP_PROTOCOL:
            SYSFUN_Sprintf((char *)temp_string, " %s","tcp");
            strcat((char *)buff, (char *)temp_string);
            break;

         case PFU_TYPE_UDP_PROTOCOL:
            SYSFUN_Sprintf((char *)temp_string, " %s","udp");
            strcat((char *)buff, (char *)temp_string);
            break;

         case PFU_TYPE_IP_PROTOCOL_ANY:
            SYSFUN_Sprintf((char *)temp_string, " %s","any");
            strcat((char *)buff, (char *)temp_string);
            break;

         default:
            SYSFUN_Sprintf((char *)temp_string, " %lu",rule.pfu_protocol);
            strcat((char *)buff, (char *)temp_string);
            break;
         }

         /*save source ip address*/
         strcat((char *)buff," ");
         temp=htonl(rule.pfu_srcip_addr);
         L_INET_Ntoa(temp, temp_string);
         strcat((char *)buff,(char *)temp_string);
         strcat((char *)buff," ");
         memset(temp_string, 0, sizeof(temp_string));
         temp=htonl(rule.pfu_srcip_bitmask);
         L_INET_Ntoa(temp, temp_string);
         strcat((char *)buff,(char *)temp_string);

         /*check source port number or no specify port*/
         if (!(rule.pfu_sport_range1 == PFU_TYPE_SPORT_ANY && rule.pfu_sport_range2 == PFU_TYPE_SPORT_ANY))
         {
            if (rule.pfu_sport_range1 == PFU_TYPE_SPORT_ANY)
            {/*range1 = any , range2 = value*/
               SYSFUN_Sprintf((char *)temp_string," %lu",rule.pfu_sport_range2);
               strcat((char *)buff,(char *)temp_string);
            }
            else if (rule.pfu_sport_range2 == PFU_TYPE_SPORT_ANY)
            {/*range1 = value , range2 = any*/
               SYSFUN_Sprintf((char *)temp_string," %lu",rule.pfu_sport_range1);
               strcat((char *)buff,(char *)temp_string);
            }
            else
            {/*range1 = value , range2 = value*/
               if (rule.pfu_sport_range1 == rule.pfu_sport_range2)
               {
                  SYSFUN_Sprintf((char *)temp_string," %lu",rule.pfu_sport_range1);
                  strcat((char *)buff,(char *)temp_string);
               }
               else
               {
                  SYSFUN_Sprintf((char *)temp_string," %lu-%lu",rule.pfu_sport_range1, rule.pfu_sport_range2);
                  strcat((char *)buff,(char *)temp_string);
               }
            }
         }

         /*save destination ip address*/
         strcat((char *)buff," ");
         temp=htonl(rule.pfu_dstip_addr);
         L_INET_Ntoa(temp, temp_string);
         strcat((char *)buff,(char *)temp_string);
         strcat((char *)buff," ");
         memset(temp_string, 0, sizeof(temp_string));
         temp=htonl(rule.pfu_dstip_bitmask);
         L_INET_Ntoa(temp, temp_string);
         strcat((char *)buff,(char *)temp_string);

         /*check source port number or no specify port*/
         if (!(rule.pfu_dport_range1 == PFU_TYPE_DPORT_ANY && rule.pfu_dport_range2 == PFU_TYPE_DPORT_ANY))
         {
            if (rule.pfu_dport_range1 == PFU_TYPE_DPORT_ANY)
            {/*range1 = any , range2 = value*/
               SYSFUN_Sprintf((char *)temp_string," %lu",rule.pfu_dport_range2);
               strcat((char *)buff,(char *)temp_string);
            }
            else if (rule.pfu_dport_range2 == PFU_TYPE_DPORT_ANY)
            {/*range1 = value , range2 = any*/
               SYSFUN_Sprintf((char *)temp_string," %lu",rule.pfu_dport_range1);
               strcat((char *)buff,(char *)temp_string);
            }
            else
            {/*range1 = value , range2 = value*/
               if (rule.pfu_dport_range1 == rule.pfu_dport_range2)
               {
                  SYSFUN_Sprintf((char *)temp_string," %lu",rule.pfu_dport_range1);
                  strcat((char *)buff,(char *)temp_string);
               }
               else
               {
                  SYSFUN_Sprintf((char *)temp_string," %lu-%lu",rule.pfu_dport_range1, rule.pfu_dport_range2);
                  strcat((char *)buff,(char *)temp_string);
               }
            }
         }
         /*if protocol == tcp check tcp code*/
         if (rule.pfu_protocol == PFU_TYPE_TCP_PROTOCOL)
         {
            UI8_T  i = 0;
            //UI32_T translate_control_code = 0;

            if (rule.pfu_tcp_code == rule.pfu_tcp_code_bitmask)/*use symbol to generate running config*/
            {
               if (rule.pfu_tcp_code != 0)
               {
                  //translate_control_code = rule.pfu_tcp_code & rule.pfu_tcp_code_bitmask;
                  strcat(buff, " code");
                  for (i = 0; i < 6 ; i++)
                  {
                     if (rule.pfu_tcp_code & (1 << i))
                     {
                        SYSFUN_Sprintf((char *)temp_string," %s",str[i]);
                        strcat((char *)buff, (char *)temp_string);
                     }
                  }
               }
            }
            else /*use value and mask to generate running config*/
            {
               strcat((char *)buff, " code");
               SYSFUN_Sprintf((char *)temp_string, " %lu %lu",rule.pfu_tcp_code,rule.pfu_tcp_code_bitmask);
               strcat((char *)buff, (char *)temp_string);
            }
         }

         /*check fragment and log*/
         if (rule.pfu_rule_fragments == VAL_pfuRuleFragments_enabled)
            strcat((char *)buff, " fragment");

         if (rule.pfu_rule_log == VAL_pfuRuleLog_enabled)
            strcat((char *)buff, " log");

         APPEND_RUNNING_CFG_1("%s\n", buff);
      }
      APPEND_RUNNING_CFG_0("!\n");
   }
#endif
#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("pfu complete\r\n");
#endif
   return buffer_count;
}

/* 2006/06/28
 * ES4649-38-00189: free memory before return
 */
static UI32_T cli_runcfg_get_mstp_mode_parameter_macro(UI32_T unit_id, char *buffer, char *temp_buffer,
                                       UI32_T buffer_size, UI32_T b_count, char *str_list, char *print_str)
{
   UI32_T buffer_count = b_count;

#if (SYS_CPNT_MSTP_SUPPORT_PVST==FALSE)
    /*spanning-tree mode*/
    {
        UI32_T mode = 0;

        if (XSTP_POM_GetRunningSystemSpanningTreeVersion(&mode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            switch(mode)
            {
                case XSTP_TYPE_STP_PROTOCOL_VERSION_ID:
                    APPEND_RUNNING_CFG_0("spanning-tree mode stp\n");
                break;

                case XSTP_TYPE_RSTP_PROTOCOL_VERSION_ID:
                    APPEND_RUNNING_CFG_0("spanning-tree mode rstp\n");
                break;

                case XSTP_TYPE_MSTP_PROTOCOL_VERSION_ID:
                    APPEND_RUNNING_CFG_0("spanning-tree mode mstp\n");
                break;

                default:
                break;
            }
        }
    }
#endif

/*mst configuration*/
#if (SYS_CPNT_STP == SYS_CPNT_STP_TYPE_MSTP)

   APPEND_RUNNING_CFG_0("!\n");
   APPEND_RUNNING_CFG_0("spanning-tree mst configuration\n");

   /*mst instant_id vlan*/
   {
      UI32_T mstid = 0;
      XSTP_MGR_MstpInstanceEntry_T mstp_instance_entry;
      char  vlan_list[512] = {0};

      do
      {
         memset(&mstp_instance_entry, 0, sizeof(mstp_instance_entry));

         if (XSTP_POM_GetRunningMstpInstanceVlanConfiguration(mstid,&mstp_instance_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            memcpy(vlan_list,mstp_instance_entry.mstp_instance_vlans_mapped,sizeof(char)*128);
            memcpy(vlan_list+128,mstp_instance_entry.mstp_instance_vlans_mapped2k,sizeof(char)*128);
            memcpy(vlan_list+256,mstp_instance_entry.mstp_instance_vlans_mapped3k,sizeof(char)*128);
            memcpy(vlan_list+384,mstp_instance_entry.mstp_instance_vlans_mapped4k,sizeof(char)*128);
            CLI_LIB_MSB_To_LSB(vlan_list,512);
            CLI_LIB_Bitmap_To_List(vlan_list,str_list,512*4,SYS_DFLT_DOT1QMAXVLANID,FALSE);
            if (strlen((char *)str_list) > 0)
            {
               if (mstid != 0)
               {
                  /*because must show per line, so spilt the str_list to show */
                  I32_T str_len = strlen((char *)str_list);
                  I32_T process_length = 0;

                  while ((str_len-process_length) > 0)
                  {
                     CLI_Runcfg_ListStrToOneLine(&process_length, 15, str_list, print_str);
                     APPEND_RUNNING_CFG_2(" mst %lu vlan %s\n",(unsigned long)mstid,print_str);
                  }
               }
            }
         }
      }while(XSTP_POM_GetNextExistedInstanceForMstConfigTable(&mstid));
   }
   /*mst instant_id priority */
   {
      UI32_T mstid = 0;
      UI32_T priority = 0;

      do
      {
         if (XSTP_POM_GetRunningMstPriority(mstid, &priority) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_2(" mst %lu priority %lu\n",(unsigned long)mstid,(unsigned long)priority);
         }
      }while(XSTP_POM_GetNextExistedInstance(&mstid));
   }
   /*name*/
   {
      char  name[XSTP_TYPE_REGION_NAME_MAX_LENGTH + 1] = {0};

      if (XSTP_PMGR_GetRunningMstpConfigurationName((UI8_T *)name) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
         char      buf[CLI_DEF_MAX_BUFSIZE+1];
         CLI_LIB_Str_Add_Quote(name,buf);
         APPEND_RUNNING_CFG_1(" name %s\n",buf/*name*/);
#else
         APPEND_RUNNING_CFG_1(" name %s\n",name);
#endif
      }
   }
   /*revision*/
   {
      UI32_T revision = 0;

      if (XSTP_POM_GetRunningMstpRevisionLevel(&revision) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1(" revision %lu\n",(unsigned long)revision);
      }
   }
   /*max-hops*/
   {
      UI32_T maxhpos = 0;

      if (XSTP_POM_GetRunningMstpMaxHop(&maxhpos) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1(" max-hops %lu\n",(unsigned long)maxhpos);
      }
   }
   APPEND_RUNNING_CFG_0("!\n");

#endif
#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("MSTP mode complete\r\n");
#endif
   return buffer_count;
}


static UI32_T CLI_RUNCFG_Get_MSTP_Mode_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    char  *str_list;
    char  *print_str;
    UI32_T return_value;

    if( (str_list = calloc(512*4, sizeof(char))) == NULL )
    {
        return CLII_ERR_MEMORY_NOT_ENOUGH;
    }
    if( (print_str = calloc(CLI_DEF_MAX_BUFSIZE-15, sizeof(char))) == NULL )
    {
        free(str_list);
        return CLII_ERR_MEMORY_NOT_ENOUGH;
    }

    /* 2006/06/28
     * ES4649-38-00189: free memory before return
     */
    return_value = cli_runcfg_get_mstp_mode_parameter_macro(unit_id, buffer, temp_buffer,
                                            buffer_size, b_count, str_list, print_str);

    free(print_str);
    free(str_list);

    return return_value;
}

static UI32_T CLI_RUNCFG_Get_Line_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
   UI32_T buffer_count = b_count;
   /* line commands */
   {
      UI32_T time_out_value;
      UI32_T passwordThreshold;
      //UI32_T silent_time;
      SYS_MGR_Uart_RunningCfg_T uart_cfg;
      USERAUTH_Login_Method_T login_method;
      memset(&uart_cfg,0,sizeof(SYS_MGR_Uart_RunningCfg_T));
      /*console parameter*/
      APPEND_RUNNING_CFG_0("line console\n");

      if (USERAUTH_PMGR_GetRunningConsoleLoginMethod(&login_method) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         switch(login_method)
         {
         case USERAUTH_LOGIN_NO_LOGIN:
            APPEND_RUNNING_CFG_0(" no login\n");
            break;

         case USERAUTH_LOGIN_LOGIN:
            APPEND_RUNNING_CFG_0(" login\n");
            break;

         case USERAUTH_LOGIN_LOGIN_LOCAL:
            APPEND_RUNNING_CFG_0(" login local\n");
            break;

         default:
            break;
         }
      }

      if (SYS_PMGR_GetRunningUartParameters(&uart_cfg) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         /*speed baud*/
         if (uart_cfg.baurdrate_changed == TRUE)
         {
            switch(uart_cfg.baudrate)
            {
            case SYS_MGR_UART_BAUDRATE_9600:
               APPEND_RUNNING_CFG_0(" speed 9600\n");
               break;

            case SYS_MGR_UART_BAUDRATE_19200:
               APPEND_RUNNING_CFG_0(" speed 19200\n");
               break;

            case SYS_MGR_UART_BAUDRATE_38400:
               APPEND_RUNNING_CFG_0(" speed 38400\n");
               break;

            case SYS_MGR_UART_BAUDRATE_57600:
               APPEND_RUNNING_CFG_0(" speed 57600\n");
               break;

            case SYS_MGR_UART_BAUDRATE_115200:
               APPEND_RUNNING_CFG_0(" speed 115200\n");
               break;

#if (SYS_CPNT_AUTOBAUDRATE == TRUE)
            case SYS_MGR_UART_BAUDRATE_AUTO:
               APPEND_RUNNING_CFG_0(" speed auto\n");
               break;
#endif

            default:
               ;
            }
         }/*end of speed baud*/
         /*parity*/
         if (uart_cfg.parity_changed == TRUE)
         {
            switch(uart_cfg.parity)
            {
            case SYS_MGR_UART_PARITY_NONE:
               APPEND_RUNNING_CFG_0(" parity none\n");
               break;

            case SYS_MGR_UART_PARITY_EVEN:
               APPEND_RUNNING_CFG_0(" parity even\n");
               break;

            case SYS_MGR_UART_PARITY_ODD:
               APPEND_RUNNING_CFG_0(" parity odd\n");
               break;

            case SYS_MGR_UART_PARITY_MARK:
               APPEND_RUNNING_CFG_0(" parity mark\n");
               break;

            case SYS_MGR_UART_PARITY_SPACE:
               APPEND_RUNNING_CFG_0(" parity space\n");

            default:
               ;
            }
         }/*end of parity*/
         /*databit*/
         if (uart_cfg.data_length_changed == TRUE)
         {
            switch(uart_cfg.data_length)
            {
            case SYS_MGR_UART_DATA_LENGTH_5_BITS:
               APPEND_RUNNING_CFG_0(" databits 5\n");
               break;

            case SYS_MGR_UART_DATA_LENGTH_6_BITS:
               APPEND_RUNNING_CFG_0(" databits 6\n");
               break;

            case SYS_MGR_UART_DATA_LENGTH_7_BITS:
               APPEND_RUNNING_CFG_0(" databits 7\n");
               break;

            case SYS_MGR_UART_DATA_LENGTH_8_BITS:
               APPEND_RUNNING_CFG_0(" databits 8\n");
               break;

            default:
               ;
            }
         }/*end of databit*/
         /*stopbit*/
         if (uart_cfg.stop_bits_changed == TRUE)
         {
            switch(uart_cfg.stop_bits)
            {
            case SYS_MGR_UART_STOP_BITS_1_BITS:
               APPEND_RUNNING_CFG_0(" stopbits 1\n");
               break;

//            case SYS_MGR_UART_STOP_BITS_1_AND_HALF_BITS:
//               APPEND_RUNNING_CFG_0(" stopbits 1.5\n");
//               break;

            case SYS_MGR_UART_STOP_BITS_2_BITS:
               APPEND_RUNNING_CFG_0(" stopbits 2\n");
               break;

            default:
               ;
            }
         }/*end of stopbit*/
      }/*end of console para*/
      /*exec-timeout*/
      {
         UI32_T time_out_value = 0;
         if (SYS_PMGR_GetRunningConsoleExecTimeOut(&time_out_value) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_1(" exec-timeout %lu\n", (unsigned long)time_out_value);
         }
      }
      /*password-threshold*/
      {
         UI32_T passwordThreshold = 0;
         if(SYS_PMGR_GetRunningPasswordThreshold(&passwordThreshold) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_1(" password-thresh %lu\n", (unsigned long)passwordThreshold);
         }
      }
      /*silent-time*/
      {
         UI32_T silent_time = 0;
         if(SYS_PMGR_GetRunningConsoleSilentTime(&silent_time) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_1(" silent-time %lu\n", (unsigned long)silent_time);
         }
      }
      /*password*/
      {
         char  password[SYS_ADPT_MAX_ENCRYPTED_PASSWORD_LEN+1] = {0};

         if (USERAUTH_PMGR_GetRunningConsoleLoginPassword((UI8_T *)password) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            char  encrypt_buff[33] = {0};
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
            char      buf[CLI_DEF_MAX_BUFSIZE+1];
#endif
            COLLECT_ENCRTPT_TEXT_TO_PRINT(encrypt_buff, password);
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
            CLI_LIB_Str_Add_Quote(encrypt_buff,buf);

            APPEND_RUNNING_CFG_1(" password 7 %s\n", buf/*encrypt_buff*/);
#else
            APPEND_RUNNING_CFG_1(" password 7 %s\n", encrypt_buff);
#endif
         }
      }

    /* timeout */
    {
        UI32_T time_out_value;

        if (SYS_PMGR_GetRunningConsoleLoginTimeOut(&time_out_value) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" timeout login response %lu\n", (unsigned long)time_out_value);
        }
    }

#if (SYS_CPNT_AUTHORIZATION == TRUE)
    /*authorization*/
    {
        AAA_AuthorExecEntry_T aaa_author_exec_entry;
        memset(&aaa_author_exec_entry, 0, sizeof(AAA_AuthorExecEntry_T));
        aaa_author_exec_entry.exec_type = AAA_EXEC_TYPE_CONSOLE;
        if(AAA_POM_GetRunningAuthorExecEntry(&aaa_author_exec_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" authorization exec %s\n",aaa_author_exec_entry.list_name);
        }
    }
#endif /*#if (SYS_CPNT_AUTHORIZATION == TRUE)*/

#if (SYS_CPNT_AUTHORIZATION_COMMAND == TRUE)
        {
            AAA_AuthorCommandEntry_T aaa_author_command_entry;
            UI32_T priv_lvl;

            for (priv_lvl = 0; priv_lvl < SYS_ADPT_NBR_OF_LOGIN_PRIVILEGE; priv_lvl++)
            {
                if (AAA_POM_GetRunningAuthorCommandEntry(priv_lvl, AAA_EXEC_TYPE_CONSOLE,
                                                         &aaa_author_command_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    APPEND_RUNNING_CFG_2(" authorization command %lu %s\n", (unsigned long)priv_lvl, aaa_author_command_entry.list_name);
                }
            }
        }
#endif /*#if (SYS_CPNT_AUTHORIZATION_COMMAND == TRUE)*/


#if (SYS_CPNT_ACCOUNTING == TRUE)
    /*accounting*/
    {
        AAA_AccExecEntry_T acc_exec_entry;
        memset(&acc_exec_entry ,0 , sizeof(AAA_AccExecEntry_T));
        acc_exec_entry.exec_type = AAA_EXEC_TYPE_CONSOLE;
        if(AAA_POM_GetRunningAccExecEntry(&acc_exec_entry)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" accounting exec %s\n",acc_exec_entry.list_name);
        }
    }

#if (SYS_CPNT_ACCOUNTING_COMMAND == TRUE)
    {
        UI32_T                 priv_lvl;
        AAA_AccCommandEntry_T  acc_cmd_entry;
        memset(&acc_cmd_entry ,0 , sizeof(acc_cmd_entry));

        acc_cmd_entry.exec_type = AAA_EXEC_TYPE_CONSOLE;

        for (priv_lvl = 0; SYS_ADPT_NBR_OF_LOGIN_PRIVILEGE > priv_lvl; ++priv_lvl)
        {
            acc_cmd_entry.priv_lvl = priv_lvl;
            if(AAA_POM_GetRunningAccCommandEntry(&acc_cmd_entry)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_2(" accounting commands %ld %s\n",(long)acc_cmd_entry.priv_lvl, acc_cmd_entry.list_name);
            }
        }
    }
#endif /*#if (SYS_CPNT_ACCOUNTING_COMMAND == TRUE)*/

#endif /*#if (SYS_CPNT_ACCOUNTING == TRUE)*/

      APPEND_RUNNING_CFG_0("!\n");
      APPEND_RUNNING_CFG_0("!\n");
#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("line console complete\r\n");
#endif

      /*vty*/
      {
         APPEND_RUNNING_CFG_0("line vty\n");

         if (USERAUTH_PMGR_GetRunningTelnetLoginMethod(&login_method) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            switch(login_method)
            {
            case USERAUTH_LOGIN_NO_LOGIN:
               APPEND_RUNNING_CFG_0(" no login\n");
               break;

            case USERAUTH_LOGIN_LOGIN:
               APPEND_RUNNING_CFG_0(" login\n");
               break;

            case USERAUTH_LOGIN_LOGIN_LOCAL:
               APPEND_RUNNING_CFG_0(" login local\n");
               break;

            default:
               break;
            }
         }

         if (SYS_PMGR_GetRunningTelnetExecTimeOut(&time_out_value) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_1(" exec-timeout %lu\n", (unsigned long)time_out_value);
         }

         if (SYS_PMGR_GetRunningTelnetPasswordThreshold(&passwordThreshold) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_1(" password-thresh %lu\n", (unsigned long)passwordThreshold);
         }

         /*silent-time*/
         {
             UI32_T silent_time = 0;
             if (SYS_PMGR_GetRunningTelnetSilentTime(&silent_time) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
             {
                APPEND_RUNNING_CFG_1(" silent-time %lu\n", (unsigned long)silent_time);
             }
         }

         /*password*/
         {
           char  password[SYS_ADPT_MAX_PASSWORD_LEN+1] = {0};

           if (USERAUTH_PMGR_GetRunningTelnetLoginPassword((UI8_T *)password) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
           {
              char  encrypt_buff[33] = {0};
              COLLECT_ENCRTPT_TEXT_TO_PRINT(encrypt_buff, password);

              APPEND_RUNNING_CFG_1(" password 7 %s\n", encrypt_buff);
           }
         }

        /* timeout */
        {
            UI32_T time_out_value;

            if (SYS_PMGR_GetRunningTelnetLoginTimeOut(&time_out_value) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_1(" timeout login response %lu\n", (unsigned long)time_out_value);
            }
        }

#if (SYS_CPNT_AUTHORIZATION == TRUE)
        {
            AAA_AuthorExecEntry_T aaa_author_exec_entry;
            memset(&aaa_author_exec_entry, 0, sizeof(AAA_AuthorExecEntry_T));
            aaa_author_exec_entry.exec_type = AAA_EXEC_TYPE_VTY;
            if(AAA_POM_GetRunningAuthorExecEntry(&aaa_author_exec_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_1(" authorization exec %s\n",aaa_author_exec_entry.list_name);
            }
        }
#endif /*#if (SYS_CPNT_AUTHORIZATION == TRUE)*/

#if (SYS_CPNT_AUTHORIZATION_COMMAND == TRUE)
        {
            AAA_AuthorCommandEntry_T aaa_author_command_entry;
            UI32_T priv_lvl;

            for (priv_lvl = 0; priv_lvl < SYS_ADPT_NBR_OF_LOGIN_PRIVILEGE; priv_lvl++)
            {
                if (AAA_POM_GetRunningAuthorCommandEntry(priv_lvl, AAA_EXEC_TYPE_VTY, &aaa_author_command_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    APPEND_RUNNING_CFG_2(" authorization command %lu %s\n", (unsigned long)priv_lvl, aaa_author_command_entry.list_name);
                }
            }
        }
#endif /*#if (SYS_CPNT_AUTHORIZATION_COMMAND == TRUE)*/


#if (SYS_CPNT_ACCOUNTING == TRUE)
        /*accounting*/
        {
            AAA_AccExecEntry_T acc_exec_entry;
            memset(&acc_exec_entry ,0 , sizeof(AAA_AccExecEntry_T));
            acc_exec_entry.exec_type = AAA_EXEC_TYPE_VTY;
            if(AAA_POM_GetRunningAccExecEntry(&acc_exec_entry)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_1(" accounting exec %s\n",acc_exec_entry.list_name);
            }
        }

#if (SYS_CPNT_ACCOUNTING_COMMAND == TRUE)
    {
        UI32_T                 priv_lvl;
        AAA_AccCommandEntry_T  acc_cmd_entry;
        memset(&acc_cmd_entry ,0 , sizeof(acc_cmd_entry));

        acc_cmd_entry.exec_type = AAA_EXEC_TYPE_VTY;

        for (priv_lvl = 0; SYS_ADPT_NBR_OF_LOGIN_PRIVILEGE > priv_lvl; ++priv_lvl)
        {
            acc_cmd_entry.priv_lvl = priv_lvl;
            if(AAA_POM_GetRunningAccCommandEntry(&acc_cmd_entry)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_2(" accounting commands %ld %s\n",(long)acc_cmd_entry.priv_lvl, acc_cmd_entry.list_name);
            }
        }
    }
#endif /*#if (SYS_CPNT_ACCOUNTING_COMMAND == TRUE)*/

#endif /*#if (SYS_CPNT_ACCOUNTING == TRUE)*/

         APPEND_RUNNING_CFG_0("!\n");
         APPEND_RUNNING_CFG_0("!\n");
      }
   }/*end of line*/
   /*end this provision session*/
   APPEND_RUNNING_CFG_0("!\n");
   APPEND_RUNNING_CFG_0("end\n");
#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("line VTY complete\r\n");
#endif
   return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_VDSL_Global_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
   UI32_T buffer_count = b_count;
#if (SYS_CPNT_VDSL == TRUE)/*---------------------------------------------------------------------------*/
   {
      UI32_T port_id = VDSLDRV_INVALID_PORT_ID;/*invalid id for get first port*/
      VDSLDRV_PORT_CONFIG_T port_config;
      UI32_T previous_profile_id = 0;
      BOOL_T is_the_same_profile = TRUE;
      memset(&port_config , 0 , sizeof(VDSLDRV_PORT_CONFIG_T));
      while (VDSLDRV_get_next_port_config(&port_id, &port_config))
      {
         if (port_id == 0)/*to set first profile_id*/
            previous_profile_id = port_config.m_n_speed_profile_id;

         if (previous_profile_id != port_config.m_n_speed_profile_id)
         {
            is_the_same_profile = FALSE;
            break;
         }

         previous_profile_id = port_config.m_n_speed_profile_id;
      }

      if (is_the_same_profile)
      {
         VDSLDRV_PORT_CONFIG_T vdsl_default_config;
         UI8_T sz_name[VDSLDRV_MAX_SPEED_PROFILE_NAME_LEN];
         VDSLDRV_get_default_port_config(&vdsl_default_config);
         if (vdsl_default_config.m_n_speed_profile_id != previous_profile_id)
         {
            if (VDSLDRV_get_speed_profile_name(previous_profile_id, sz_name))
            {
               APPEND_RUNNING_CFG_1("lre profile global %s\n", sz_name);
            }
         }
      }
   }

   /*lre define user-profile id up down interleave*/
   {
      VDSLDRV_SPEED_PROFILE_T default_vdsl_profile_config;
      VDSLDRV_SPEED_PROFILE_T current_vdsl_profile_config;
      UI32_T  i = 0;

      memset(&default_vdsl_profile_config,0,sizeof(default_vdsl_profile_config));
      memset(&current_vdsl_profile_config,0,sizeof(current_vdsl_profile_config));
      VDSLDRV_get_default_profile_config(&default_vdsl_profile_config);

      for (i = 0; i<2 ; i++)
      {
         VDSLDRV_get_profile_config(i,&current_vdsl_profile_config);
         if (default_vdsl_profile_config.m_n_downstream_rate != current_vdsl_profile_config.m_n_downstream_rate
             || default_vdsl_profile_config.m_n_upstream_rate != current_vdsl_profile_config.m_n_upstream_rate
             || default_vdsl_profile_config.m_n_interleave_depth != current_vdsl_profile_config.m_n_interleave_depth)
         {
            APPEND_RUNNING_CFG_4("lre define user-profile %lu %lu %lu %lu\n",(unsigned long)i+1,(unsigned long)current_vdsl_profile_config.m_n_upstream_rate
            ,(unsigned long)current_vdsl_profile_config.m_n_downstream_rate,(unsigned long)current_vdsl_profile_config.m_n_interleave_depth);
         }
      }
   }
#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("VDSL Global complete\r\n");
#endif
#endif/*---------------------------------------------------------------------------*/
   return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_HTTP_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
#if (SYS_CPNT_HTTP_UI == TRUE)
    /*ip http */
    {
        HTTP_MGR_RunningCfg_T http_cfg;

        memset(&http_cfg,0,sizeof(HTTP_MGR_RunningCfg_T));

        if (HTTP_PMGR_GetRunningHttpParameters(&http_cfg) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            /*ip http server*/
            if (http_cfg.state_changed == TRUE)
            {
                if (http_cfg.state == HTTP_STATE_ENABLED)
            {
               APPEND_RUNNING_CFG_0("ip http server\n");
            }
            else
            {
               APPEND_RUNNING_CFG_0("no ip http server\n");
            }
         }
            /*ip http port*/
            if (http_cfg.port_changed == TRUE)
            {
                APPEND_RUNNING_CFG_1("ip http port %lu\n",(unsigned long)http_cfg.port);
            }
            APPEND_RUNNING_CFG_0("!\n");
        }
    }/*end of ip http*/
#endif  /*#if (SYS_CPNT_HTTP_UI == TRUE)*/

#if (SYS_CPNT_HTTP_UI == TRUE)
#if (SYS_CPNT_HTTPS == TRUE)
    /*ip http secure-server*/
    {
        UI32_T status;

        if (HTTP_PMGR_Get_Running_Secure_Http_Status(&status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (status == SECURE_HTTP_STATE_ENABLED)
            {
                APPEND_RUNNING_CFG_0("ip http secure-server\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no ip http secure-server\n");
            }
        }

    }
    /*ip http secure-port*/
    {
        UI32_T port;

        if (HTTP_PMGR_Get_Running_Http_Secure_Port(&port) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("ip http secure-port %lu\n",(unsigned long)port);
        }
    }
    APPEND_RUNNING_CFG_0("!\n");

#endif  /* #if (SYS_CPNT_HTTPS == TRUE) */
#endif  /* #if (SYS_CPNT_HTTP_UI == TRUE) */

#if (CLI_SUPPORT_L2_DHCP_RELAY == 1)
   /*ip dhcp relay*/
   {
      BOOL_T status = FALSE;
      if (IML_GetRunningBridgeDHCPReleyStatus(&status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (status == TRUE)//temp
         {
            APPEND_RUNNING_CFG_0("ip dhcp relay\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no ip dhcp relay\n");
         }
      }
      APPEND_RUNNING_CFG_0("!\n");
   }
#endif


#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr((UI8_T *)"HTTP or HTTPS complete\r\n");
#endif
    return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_Spanningtree_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
   UI32_T buffer_count = b_count;
#if (SYS_CPNT_STP == SYS_CPNT_STP_TYPE_RSTP || SYS_CPNT_STP == SYS_CPNT_STP_TYPE_MSTP)

   /*spanning-tree*/
   {
      UI32_T status = 0;
      if (XSTP_POM_GetRunningSystemSpanningTreeStatus(&status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         switch(status)
         {
         case VAL_staSystemStatus_enabled:
            APPEND_RUNNING_CFG_0("spanning-tree\n");
            break;

         case VAL_staSystemStatus_disabled:
            APPEND_RUNNING_CFG_0("no spanning-tree\n");
            break;

         default:
            break;
         }
      }
   }

   /*forward_time hello_time max_age*/
   {
      UI32_T count = 0;
      UI32_T point = 0;
      UI32_T i     = 0;
      UI8_T  type  = 1;
      CLI_RUNCFG_Sequence_T A[3],B[3],C[3];

      memset(A,0,sizeof(A));
      memset(B,0,sizeof(B));
      memset(C,0,sizeof(C));
      /*forward_time */
      {
         UI32_T forward_time = 0;
         if (XSTP_POM_GetRunningForwardDelay(&forward_time) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            A[count].type = 3;
            A[count].value = forward_time;
            A[count].valid = TRUE;
            count++;
         }
      }
      /*hello-time*/
      {
         UI32_T hello_time = 0;
         if (XSTP_POM_GetRunningHelloTime(&hello_time) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            A[count].type = 2;
            A[count].value = hello_time;
            A[count].valid = TRUE;
            count++;
         }
      }
      /*max-age*/
      {
         UI32_T max_age = 0;
         if (XSTP_POM_GetRunningMaxAge(&max_age) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            A[count].type = 1;
            A[count].value = max_age;
            A[count].valid = TRUE;
            count++;
         }
      }

      B[0].type  = 1;
      B[0].value = SYS_DFLT_STP_BRIDGE_MAX_AGE*100;
      B[1].type  = 2;
      B[1].value = SYS_DFLT_XSTP_BRIDGE_HELLO_TIME*100;
      B[2].type  = 3;
      B[2].value = SYS_DFLT_STP_BRIDGE_FORWARD_DELAY*100;

      if (CLI_RUNCFG_Check_Sequence(A,B,C,&point,count,type))
      {
         for (i = 0 ; i < count ; i++)
         {
            switch(C[i].type)
            {
               {
               case 1:
                  APPEND_RUNNING_CFG_1("spanning-tree max-age %lu\n", (unsigned long)C[i].value/100);
                  break;

               case 2:
                  APPEND_RUNNING_CFG_1("spanning-tree hello-time %lu\n", (unsigned long)C[i].value/100);
                  break;

               case 3:
                  APPEND_RUNNING_CFG_1("spanning-tree forward-time %lu\n", (unsigned long)C[i].value/100);
                  break;

               default:
                  break;
               }
            }
         }
      }
   }

   /*spanning-tree pathcost method*/
   {
      UI32_T method = 0;

      if (XSTP_POM_GetRunningPathCostMethod(&method) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         switch(method)
         {
         case VAL_staPathCostMethod_short:
            APPEND_RUNNING_CFG_0("spanning-tree pathcost method short\n");
            break;

         case VAL_staPathCostMethod_long:
            APPEND_RUNNING_CFG_0("spanning-tree pathcost method long\n");
            break;

         default:
            break;
         }
      }
   }

   /*spanning-tree transmission-limit*/
   {
      UI32_T count = 0;

      if (XSTP_POM_GetRunningTransmissionLimit(&count) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1("spanning-tree transmission-limit %lu\n",(unsigned long)count);
      }
   }

   /*spanning-tree priority*/
   {
      UI32_T priority = 0;

      if (XSTP_POM_GetRunningMstPriority(0,&priority) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1("spanning-tree priority %lu\n",(unsigned long)priority);
      }
   }
#if (SYS_CPNT_STP_COMPATIBLE_WITH_CISCO_PRESTANDARD == TRUE)
    /*spanning-tree cisco-prestandard-compatibility*/
    {
        UI32_T cisco_prestandard_status;
        if (XSTP_POM_GetRunningCiscoPrestandardCompatibility(&cisco_prestandard_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_0("spanning-tree cisco-prestandard\n");
        }
    }
#endif


/* ahten */
/* mac-address-table static*/
      {
          AMTR_TYPE_AddrEntry_T addr_entry;
          UI32_T unit  = 0;
          UI32_T port  = 0;
          UI32_T trunk = 0;
          memset(&addr_entry,0,sizeof(AMTR_TYPE_AddrEntry_T));
          while (AMTR_PMGR_GetNextRunningStaticAddrEntry(&addr_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
          {
             switch(SWCTRL_POM_LogicalPortToUserPort((UI32_T)addr_entry.ifindex,&unit,&port,&trunk))
             {
             case SWCTRL_LPORT_NORMAL_PORT:
                APPEND_RUNNING_CFG_4("mac-address-table static %02x-%02x-%02x-%02x",addr_entry.mac[0],addr_entry.mac[1],addr_entry.mac[2],addr_entry.mac[3]);
                APPEND_RUNNING_CFG_2("-%02x-%02x interface",addr_entry.mac[4],addr_entry.mac[5]);
#if (CLI_SUPPORT_PORT_NAME == 1)
                {
                   UI8_T name[MAXSIZE_ifName+1] = {0};
                   CLI_LIB_Ifindex_To_Name((UI32_T)addr_entry.ifindex,name);
                   APPEND_RUNNING_CFG_1(" ethernet %s",name);
                }
#else
                APPEND_RUNNING_CFG_2(" ethernet %lu/%lu ",(unsigned long)unit,(unsigned long)port);
#endif
                APPEND_RUNNING_CFG_1(" vlan %u ",addr_entry.vid);
                APPEND_RUNNING_CFG_1(" %s\n",(addr_entry.life_time== VAL_dot1dStaticStatus_other)?("other"):
                     ((addr_entry.life_time == VAL_dot1dStaticStatus_invalid)?("invalid"):
                     ((addr_entry.life_time == VAL_dot1dStaticStatus_permanent)?("permanent"):
                      (addr_entry.life_time == VAL_dot1dStaticStatus_deleteOnReset)?("delete-on-reset"):("delete-on-timeout"))));
                break;

             case SWCTRL_LPORT_TRUNK_PORT:
                APPEND_RUNNING_CFG_4("mac-address-table static %02x-%02x-%02x-%02x",addr_entry.mac[0],addr_entry.mac[1],addr_entry.mac[2],addr_entry.mac[3]);
                APPEND_RUNNING_CFG_2("-%02x-%02x interface",addr_entry.mac[4],addr_entry.mac[5]);
                APPEND_RUNNING_CFG_1(" port-channel %lu",(unsigned long)trunk);
                APPEND_RUNNING_CFG_1(" vlan %u ",addr_entry.vid);
                APPEND_RUNNING_CFG_1(" %s\n",(addr_entry.life_time== VAL_dot1dStaticStatus_other)?("other"):
                     ((addr_entry.life_time == VAL_dot1dStaticStatus_invalid)?("invalid"):
                     ((addr_entry.life_time == VAL_dot1dStaticStatus_permanent)?("permanent"):
                      (addr_entry.life_time == VAL_dot1dStaticStatus_deleteOnReset)?("delete-on-reset"):("delete-on-timeout"))));
                break;
#if (SYS_CPNT_VXLAN == TRUE)
             case SWCTRL_LPORT_VXLAN_PORT:
                {
                    UI32_T r_vxlan_port = 0;
                    UI16_T vid = 0;
                    UI32_T vni = 0;
                    AMTRL3_OM_VxlanTunnelEntry_T vxlan_tunnel;
                    UI8_T  ip_str[L_INET_MAX_IPADDR_STR_LEN] = {0};
                    BOOL_T is_network_port = 0;
                    char port_ar[20];

                    if (addr_entry.r_vtep_ip[0])
                    {
                        vni = VXLAN_POM_GetVniByVfi(addr_entry.vid);
                        is_network_port = 1;
                    }
                    else
                    {
                        if (VXLAN_TYPE_IS_L_PORT(addr_entry.ifindex))
                        {
                            UI32_T lport;
                            VXLAN_TYPE_L_PORT_CONVERTTO_R_PORT(addr_entry.ifindex, r_vxlan_port);

                            if (VXLAN_POM_GetVlanNlportOfAccessPort(r_vxlan_port, &vid, &lport))
                            {
                                SWCTRL_Lport_Type_T     lport_type;

                                VXLAN_POM_GetPortVlanVniMapEntry(lport, vid, &vni);

                                lport_type = SWCTRL_POM_LogicalPortToUserPort(lport, &unit, &port, &trunk);
                                if(lport_type == SWCTRL_LPORT_NORMAL_PORT)
                                {
                                    snprintf(port_ar, sizeof(port_ar), "ethernet %lu/%lu", (unsigned long)unit, (unsigned long)port);
                                }
                                else if (lport_type == SWCTRL_LPORT_TRUNK_PORT)
                                {
                                    snprintf(port_ar, sizeof(port_ar), "port-channel %lu", (unsigned long)trunk);
                                }
                                else
                                {
                                    continue;
                                }
                            }
                        }
                    }

                    APPEND_RUNNING_CFG_4("mac-address-table static %02x-%02x-%02x-%02x",addr_entry.mac[0],addr_entry.mac[1],addr_entry.mac[2],addr_entry.mac[3]);
                    APPEND_RUNNING_CFG_2("-%02x-%02x",addr_entry.mac[4],addr_entry.mac[5]);

                    APPEND_RUNNING_CFG_1(" vni %lu", (unsigned long)vni);

                    if (is_network_port)
                    {
                        APPEND_RUNNING_CFG_4(" r-vtep %d.%d.%d.%d", addr_entry.r_vtep_ip[0], addr_entry.r_vtep_ip[1], addr_entry.r_vtep_ip[2], addr_entry.r_vtep_ip[3]);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_2(" interface %s vlan %u", port_ar, vid);
                    }

                    APPEND_RUNNING_CFG_1(" %s\n",(addr_entry.life_time== VAL_dot1dStaticStatus_other)?("other"):
                         ((addr_entry.life_time == VAL_dot1dStaticStatus_invalid)?("invalid"):
                         ((addr_entry.life_time == VAL_dot1dStaticStatus_permanent)?("permanent"):
                          (addr_entry.life_time == VAL_dot1dStaticStatus_deleteOnReset)?("delete-on-reset"):("delete-on-timeout"))));

                }
                break;
#endif

             default:
                break;
             }
          }
      }
/* ahten */
#if 0 /*add for remove mac-address-table secure command*/
/* mac-address-table secure*/
      {
          PSEC_MGR_PortSecAddrEntry_T portsec_entry;
          UI32_T unit  = 0;
          UI32_T port  = 0;
          UI32_T trunk = 0;
          memset(&portsec_entry,0,sizeof(PSEC_MGR_PortSecAddrEntry_T));
          while (PSEC_PMGR_GetNextPortSecAddrEntry(&portsec_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
          {
             switch(SWCTRL_POM_LogicalPortToUserPort(portsec_entry.port_sec_addr_port,&unit,&port,&trunk))
             {
             case SWCTRL_LPORT_NORMAL_PORT:
                APPEND_RUNNING_CFG_4("mac-address-table secure %02x-%02x-%02x-%02x",portsec_entry.port_sec_addr_address[0],portsec_entry.port_sec_addr_address[1],portsec_entry.port_sec_addr_address[2],portsec_entry.port_sec_addr_address[3]);
                APPEND_RUNNING_CFG_2("-%02x-%02x",portsec_entry.port_sec_addr_address[4],portsec_entry.port_sec_addr_address[5]);
#if (CLI_SUPPORT_PORT_NAME == 1)
                {
                   UI8_T name[MAXSIZE_ifName+1] = {0};
                   CLI_LIB_Ifindex_To_Name(portsec_entry.port_sec_addr_port,name);
                   APPEND_RUNNING_CFG_1(" ethernet %s",name);
                }
#else
                APPEND_RUNNING_CFG_2(" ethernet %lu/%lu ",unit,port);
#endif
                APPEND_RUNNING_CFG_1(" vlan %lu\n",portsec_entry.port_sec_addr_fdb_id);
                break;

             case SWCTRL_LPORT_TRUNK_PORT:
                APPEND_RUNNING_CFG_4("mac-address-table secure %02x-%02x-%02x-%02x",portsec_entry.port_sec_addr_address[0],portsec_entry.port_sec_addr_address[1],portsec_entry.port_sec_addr_address[2],portsec_entry.port_sec_addr_address[3]);
                APPEND_RUNNING_CFG_2("-%02x-%02x",portsec_entry.port_sec_addr_address[4],portsec_entry.port_sec_addr_address[5]);
                APPEND_RUNNING_CFG_1(" port-channel %lu",trunk);
                APPEND_RUNNING_CFG_1(" vlan %lu\n",portsec_entry.port_sec_addr_fdb_id);
                break;

             default:
                break;
             }
          }
      }
#endif /*add for remove mac-address-table secure command*/
#else
   /*bridge family */
   {
      /*bridge bridge-group address ip-address forward ethernet ?/? VLAN vlan_id [x|x|x]*/
      {
          AMTR_MGR_AddrEntry_T addr_entry;
          UI32_T unit  = 0;
          UI32_T port  = 0;
          UI32_T trunk = 0;
          memset(&addr_entry,0,sizeof(AMTR_MGR_AddrEntry_T));
          while (AMTR_PMGR_GetNextRunningStaticAddrEntry(&addr_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
          {
             switch(SWCTRL_POM_LogicalPortToUserPort(addr_entry.l_port,&unit,&port,&trunk))
             {
             case SWCTRL_LPORT_NORMAL_PORT:
                APPEND_RUNNING_CFG_4("bridge 1 address %02x-%02x-%02x-%02x",addr_entry.mac[0],addr_entry.mac[1],addr_entry.mac[2],addr_entry.mac[3]);
                APPEND_RUNNING_CFG_3("-%02x-%02x vlan %lu forward",addr_entry.mac[4],addr_entry.mac[5],(unsigned long)addr_entry.vid);
#if (CLI_SUPPORT_PORT_NAME == 1)
                {
                   char name[MAXSIZE_ifName+1] = {0};
                   CLI_LIB_Ifindex_To_Name(addr_entry.l_port,name);
                   APPEND_RUNNING_CFG_2(" ethernet %s %s\n",name,(addr_entry.attribute == VAL_dot1dStaticStatus_permanent)?("permanent"):
                                     ((addr_entry.attribute == VAL_dot1dStaticStatus_deleteOnReset)?("delete-on-reset"):("delete-on-timeout")));
                }
#else
                APPEND_RUNNING_CFG_3(" ethernet %lu/%lu %s\n",(unsigned long)unit,(unsigned long)port,(addr_entry.attribute == VAL_dot1dStaticStatus_permanent)?("permanent"):
                                  ((addr_entry.attribute == VAL_dot1dStaticStatus_deleteOnReset)?("delete-on-reset"):("delete-on-timeout")));
#endif
                break;

             case SWCTRL_LPORT_TRUNK_PORT:
                APPEND_RUNNING_CFG_4("bridge 1 address %02x-%02x-%02x-%02x",addr_entry.mac[0],addr_entry.mac[1],addr_entry.mac[2],addr_entry.mac[3]);
                APPEND_RUNNING_CFG_3("-%02x-%02x vlan %lu forward",addr_entry.mac[4],addr_entry.mac[5],(unsigned long)addr_entry.vid);
                APPEND_RUNNING_CFG_2(" port-channel %lu %s\n",(unsigned long)trunk,(addr_entry.attribute == VAL_dot1dStaticStatus_permanent)?("permanent"):
                                  ((addr_entry.attribute == VAL_dot1dStaticStatus_deleteOnReset)?("delete-on-reset"):("delete-on-timeout")));
                break;

             default:
                break;
             }
          }
      }

      /*forward_time hello_time max_age*/
      {
         UI32_T count = 0;
         UI32_T point = 0;
         UI32_T i     = 0;
         UI8_T  type  = 1;
         CLI_RUNCFG_Sequence_T A[3],B[3],C[3];

         memset(A,0,sizeof(A));
         memset(B,0,sizeof(B));
         memset(C,0,sizeof(C));
         /*forward_time */
         {
            UI32_T forward_time = 0;
            if (STA_PMGR_GetRunningDot1dStpBridgeForwardDelay(&forward_time) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
               A[count].type = 3;
               A[count].value = forward_time;
               A[count].valid = TRUE;
               count++;
            }
         }
         /*hello-time*/
         {
            UI32_T hello_time = 0;
            if (STA_PMGR_GetRunningDot1dStpBridgeHelloTime(&hello_time) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
               A[count].type = 2;
               A[count].value = hello_time;
               A[count].valid = TRUE;
               count++;
            }
         }
         /*max-age*/
         {
            UI32_T max_age = 0;
            if (STA_PMGR_GetRunningDot1dStpBridgeMaxAge(&max_age) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
               A[count].type = 1;
               A[count].value = max_age;
               A[count].valid = TRUE;
               count++;
            }
         }

         B[0].type  = 1;
         B[0].value = STA_DEFAULT_MAX_AGE;
         B[1].type  = 2;
         B[1].value = STA_DEFAULT_HELLO_TIME;
         B[2].type  = 3;
         B[2].value = STA_DEFAULT_FORWARD_DELAY;

         if (CLI_RUNCFG_Check_Sequence(A,B,C,&point,count,type))
         {
            for (i = 0 ; i < count ; i++)
            {
               switch(C[i].type)
               {
                  {
                  case 1:
                     APPEND_RUNNING_CFG_1("bridge 1 max-age %lu\n", (unsigned long)C[i].value/100);
                     break;

                  case 2:
                     APPEND_RUNNING_CFG_1("bridge 1 hello-time %lu\n", (unsigned long)C[i].value/100);
                     break;

                  case 3:
                     APPEND_RUNNING_CFG_1("bridge 1 forward-time %lu\n", (unsigned long)C[i].value/100);
                     break;

                  default:
                     break;
                  }
               }
            }
         }
      }
      /*priority*/
      {
         UI32_T priority = 0;
         if (STA_PMGR_GetRunningDot1dStpPriority(&priority) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_1("bridge 1 priority %lu\n", (unsigned long)priority);
         }
      }
      /*spanning-tree*/
      {
         UI32_T status = 0;
         if (STA_PMGR_GetRunningStaSystemStatus(&status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            if(status == VAL_staSystemStatus_enabled)
            {
               APPEND_RUNNING_CFG_0("bridge 1 spanning-tree\n");
            }
            else
            {
               APPEND_RUNNING_CFG_0("no bridge 1 spanning-tree\n");
            }
         }
      }
   }
#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("bridge complete\r\n");
#endif
#endif

#if (SYS_CPNT_STP == SYS_CPNT_STP_TYPE_RSTP || SYS_CPNT_STP == SYS_CPNT_STP_TYPE_MSTP)
/* ahten */
   {
      BOOL_T status_changed, aging_changed;
      UI32_T aging_time = 0;
      UI32_T status = VAL_amtrMacAddrAgingStatus_disabled;

      status_changed =
         AMTR_PMGR_GetRunningAgingStatus(&status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS;
      aging_changed =
         AMTR_PMGR_GetRunningAgingTime(&aging_time) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS;

      if (status == VAL_amtrMacAddrAgingStatus_disabled)
      {
         if (status_changed)
         {
            APPEND_RUNNING_CFG_0("mac-address-table aging-time 0\n");
         }
      }
      else
      {
         if (status_changed || aging_changed)
         {
            APPEND_RUNNING_CFG_1("mac-address-table aging-time %lu\n", (unsigned long)aging_time);
         }
      }

      APPEND_RUNNING_CFG_0("!\n");
   }

#else
   /* bridge-group global*/
   {
      UI32_T ageing_time = 0;

      if (AMTR_PMGR_GetRunningAgingTime(&ageing_time) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1("bridge-group 1 aging-time %lu\n", (unsigned long)ageing_time);
      }
      APPEND_RUNNING_CFG_0("!\n");
   }
#endif

#if (SYS_CPNT_HASH_LOOKUP_DEPTH_CONFIGURABLE == TRUE)
    {
        UI32_T lookup_len;

        if (AMTR_PMGR_GetHashLookupDepthFromConfig(&lookup_len) &&
            lookup_len != SYS_DFLT_L2_MAC_TABLE_HASH_LOOKUP_DEPTH)
        {
            APPEND_RUNNING_CFG_1("mac-address-table hash-lookup-depth %lu\n",(unsigned long)lookup_len);
        }
    }
#endif

#if (SYS_CPNT_AMTR_VLAN_MAC_LEARNING == TRUE)
   {
      UI32_T vid=0;
      BOOL_T learning=TRUE;

      for(vid = 1; vid <= SYS_DFLT_DOT1QMAXVLANID; vid++)
      {
          if (AMTR_PMGR_GetRunningVlanLearningStatus(vid, &learning) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
          {
              if(learning == FALSE)
              {
                  APPEND_RUNNING_CFG_1("no mac-address-table mac-learning vlan %lu\n", (unsigned long)vid);
              }
              else
              {
                  APPEND_RUNNING_CFG_1("mac-address-table mac-learning vlan %lu\n", (unsigned long)vid);
              }
          }
      }
      APPEND_RUNNING_CFG_0("!\n");
   }
#endif

#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("bridge-group bridge-ext complete\r\n");
#endif
   return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_Remote_Auth_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
   UI32_T buffer_count = b_count;
#if (SYS_CPNT_RADIUS==TRUE)
   /*radius family*/
   {
      /*radius-server server-index*/
      {
         UI32_T server_index = 0;
         RADIUS_Server_Host_T server_host;
         UI8_T *out_ptr;
         UI32_T out_len;
         UI8_T string[CLI_DEF_MAX_BUFSIZE+1];
         UI8_T serversecret[MAXSIZE_radiusServerGlobalKey + 1] = {0};

         memset(&server_host, 0, sizeof(RADIUS_Server_Host_T));

         while (RADIUS_POM_GetNextRunning_Server_Host(&server_index,&server_host) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            if (server_host.secret[0] != '\0')
            {
                strcpy((char *)serversecret, (char *)server_host.secret);
                /* encrypt for radius key */
                if(L_Base64(serversecret, strlen((char *)serversecret), &out_ptr, &out_len, L_BASE64_ENCODE))
                {
                    memcpy(string,out_ptr,out_len);
                    string[out_len] = '\0';
                    L_MM_Free(out_ptr);
                }
                else
                {
                    continue;
                }

            }

            APPEND_RUNNING_CFG_1("radius-server %lu", (unsigned long)server_host.server_index);
            APPEND_RUNNING_CFG_4(" host %d.%d.%d.%d",((UI8_T *)(&(server_host.server_ip)))[0],
                                                                    ((UI8_T *)(&(server_host.server_ip)))[1],
                                                                    ((UI8_T *)(&(server_host.server_ip)))[2],
                                                                    ((UI8_T *)(&(server_host.server_ip)))[3]);

#if(SYS_CPNT_RADIUS_ACCOUNTING == TRUE)
            APPEND_RUNNING_CFG_4(" auth-port %lu acct-port %lu timeout %lu retransmit %lu",
                    (unsigned long)server_host.server_port, (unsigned long)server_host.acct_port, (unsigned long)server_host.timeout, (unsigned long)server_host.retransmit);
#else
            APPEND_RUNNING_CFG_3(" auth-port %lu timeout %lu retransmit %lu",
                    (unsigned long)server_host.server_port, (unsigned long)server_host.timeout, (unsigned long)server_host.retransmit);
#endif /*#if(SYS_CPNT_RADIUS_ACCOUNTING == TRUE)*/
            if (server_host.secret[0] != '\0')
            {
                APPEND_RUNNING_CFG_1(" key %s", string);
            }
            APPEND_RUNNING_CFG_0("\n");
         }

      }

      /*radius-server host*/
      {
         UI32_T serverip = 0;
         if (RADIUS_POM_GetRunningServerIP(&serverip) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_4("radius-server host %d.%d.%d.%d\n",((UI8_T *)(&serverip))[0],
                                                                     ((UI8_T *)(&serverip))[1],
                                                                     ((UI8_T *)(&serverip))[2],
                                                                     ((UI8_T *)(&serverip))[3]);

         }
      }

      /*radius-server key*/
      {
         char serversecret[MAXSIZE_radiusServerGlobalKey + 1] = {0};
         if (RADIUS_POM_GetRunningServerSecret((UI8_T *)serversecret) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            char *out_ptr;
            UI32_T out_len;
            char  string[CLI_DEF_MAX_BUFSIZE+1];
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
        CLI_LIB_Str_Add_Quote(serversecret,string);
#else
                strcpy(string,serversecret);
#endif
            /* encrypt for radius key */
            if(L_Base64((UI8_T *)string, strlen(string), (UI8_T **)&out_ptr, &out_len, L_BASE64_ENCODE))
            {
                memcpy(string,out_ptr,out_len);
                string[out_len] = '\0';
                L_MM_Free(out_ptr);
                APPEND_RUNNING_CFG_1("radius-server key %s\n", string);
            }
         }
      }

      /*radius-server port
       */
      {
         UI32_T auth_port = 0;
#if (SYS_CPNT_RADIUS_ACCOUNTING == TRUE)
         UI32_T acct_port = 0;
#endif /* #if (SYS_CPNT_RADIUS_ACCOUNTING == TRUE) */

         if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == RADIUS_POM_GetRunningServerPort(&auth_port))
         {
             APPEND_RUNNING_CFG_1("radius-server auth-port %lu\n", (unsigned long)auth_port);
         }

#if (SYS_CPNT_RADIUS_ACCOUNTING == TRUE)
         if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == RADIUS_POM_GetRunningServerAcctPort(&acct_port))
         {
             APPEND_RUNNING_CFG_1("radius-server acct-port %lu\n", (unsigned long)acct_port);
         }
#endif /* #if (SYS_CPNT_RADIUS_ACCOUNTING == TRUE) */
      }

      /*radius-server retransmit*/
      {
         UI32_T retimes = 0;
         if (RADIUS_POM_GetRunningRetransmitTimes(&retimes) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_1("radius-server retransmit %lu\n", (unsigned long)retimes);
         }
      }

      APPEND_RUNNING_CFG_0("!\n");
   }
#endif  /* #if (SYS_CPNT_RADIUS==TRUE) */
/*#if (SYS_CPNT_TACACS == TRUE )*/
#if ((SYS_CPNT_RADIUS == TRUE ||SYS_CPNT_RADIUS_AUTHENTICATION == TRUE) && (SYS_CPNT_TACACS == TRUE ))
   /*authentication login*/
   {
      USERAUTH_Auth_Method_T auth_method[5]  = {0};
      char  temp_string[25] = {0};
      UI8_T i               = 0;
      if (USERAUTH_PMGR_GetRunningAuthMethod(auth_method) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         for (i = 0; i < 3; i++)
         {
            if (auth_method[i] == 0) break;
            switch(auth_method[i])
            {
            case USERAUTH_AUTH_LOCAL:
               strcat(temp_string," local");
               break;

            case USERAUTH_AUTH_RADIUS:
               strcat(temp_string," radius");
               break;

            case USERAUTH_AUTH_TACACS:
               strcat(temp_string," tacacs");
               break;

            default:
               break;
            }
         }
         APPEND_RUNNING_CFG_1("authentication login%s\n", temp_string);
      }
   }
   /*authentication enable*/
   {
      USERAUTH_Auth_Method_T auth_method[5]  = {0};
      char  temp_string[25] = {0};
      UI8_T i               = 0;
      if (USERAUTH_PMGR_GetRunningEnableAuthMethod(auth_method) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         for (i = 0; i < 3 && auth_method[i] != 0; i++)
         {
            switch(auth_method[i])
            {
            case USERAUTH_AUTH_LOCAL:
               strcat(temp_string," local");
               break;

            case USERAUTH_AUTH_RADIUS:
               strcat(temp_string," radius");
               break;

            case USERAUTH_AUTH_TACACS:
               strcat(temp_string," tacacs");
               break;

            default:
               break;
            }
         }
         APPEND_RUNNING_CFG_1("authentication enable%s\n", temp_string);
      }
   }
#endif

#if (SYS_CPNT_TACACS == TRUE )
#if (SYS_CPNT_TACACS_PLUS_MULTIPLE_SERVER == TRUE)
   /*tacacs series*/
   {
      /*tacacs-server server-index*/
      {
         UI32_T server_index = 0;
         TACACS_Server_Host_T server_host;
         UI8_T *out_ptr;
         UI32_T out_len;
         char  crypo_key[CLI_DEF_MAX_BUFSIZE+1] = {0};

         memset(&server_host, 0, sizeof(TACACS_Server_Host_T));

         while (TACACS_POM_GetNextRunning_Server_Host(&server_index,&server_host) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_1("tacacs-server %lu", (unsigned long)server_host.server_index);
            APPEND_RUNNING_CFG_4(" host %d.%d.%d.%d",((UI8_T *)(&(server_host.server_ip)))[0],
                                                                    ((UI8_T *)(&(server_host.server_ip)))[1],
                                                                    ((UI8_T *)(&(server_host.server_ip)))[2],
                                                                    ((UI8_T *)(&(server_host.server_ip)))[3]);

            APPEND_RUNNING_CFG_1(" port %lu", (unsigned long)server_host.server_port);

#if (SYS_CPNT_TACACS_PLUS_RETRY_TIMEOUT == TRUE )
            APPEND_RUNNING_CFG_2(" timeout %lu retransmit %lu", (unsigned long)server_host.timeout, (unsigned long)server_host.retransmit);
#endif /* #if (SYS_CPNT_TACACS_PLUS_RETRY_TIMEOUT == TRUE ) */
            if (server_host.secret[0] != '\0')
            {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                CLI_LIB_Str_Add_Quote((char *)server_host.secret,crypo_key);
#else
                strcpy(crypo_key,server_host.secret);
#endif

            /* encrypt for tacacs key */
                if(L_Base64((UI8_T *)crypo_key, strlen(crypo_key), &out_ptr, &out_len, L_BASE64_ENCODE))
                {
                     memcpy(crypo_key,out_ptr,out_len);
                     crypo_key[out_len] = '\0';
                     L_MM_Free(out_ptr); /* L_Base64() use L_MM_Malloc() */
                     APPEND_RUNNING_CFG_1(" key %s", crypo_key);
                 }
                 else
                 {
                     CLI_LIB_PrintStr("\r\nFailed to encrypt tacacs key.\r\n");
                 }
            }

            APPEND_RUNNING_CFG_0("\n");
         }
      }

      /*tacacs-server key*/
      {
         char  serversecret[MAXSIZE_tacacsServerKey + 1] = {0};
         char  crypo_key[CLI_DEF_MAX_BUFSIZE+1] = {0};
         UI8_T *out_ptr;
         UI32_T out_len;

         if (TACACS_POM_GetRunningServerSecret((UI8_T *)serversecret) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                CLI_LIB_Str_Add_Quote(serversecret,crypo_key);
#else
                strcpy(crypo_key,serversecret);
#endif

        /* encrypt for tacacs key */
             if(L_Base64((UI8_T *)crypo_key, strlen(crypo_key), &out_ptr, &out_len, L_BASE64_ENCODE))
             {
                 memcpy(crypo_key,out_ptr,out_len);
                 crypo_key[out_len] = '\0';
                 L_MM_Free(out_ptr);  /* L_Base64() use L_MM_Malloc() */
                 APPEND_RUNNING_CFG_1("tacacs-server key %s\n", crypo_key);
             }
             else
             {
                 CLI_LIB_PrintStr("\r\nFailed to encrypt tacacs key.\r\n");
             }
         }
      }
      /*tacacs-server port*/
      {
         UI32_T serverport = 0;
         if (TACACS_POM_GetRunningServerPort(&serverport) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_1("tacacs-server port %lu\n", (unsigned long)serverport);
         }
      }

#if (SYS_CPNT_TACACS_PLUS_RETRY_TIMEOUT == TRUE )
      /*tacacs-server retransmit*/
      {
         UI32_T retransmit = 0;
         if (TACACS_POM_GetRunningServerRetransmit(&retransmit) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_1("tacacs-server retransmit %lu\n", (unsigned long)retransmit);
         }
      }
      /*tacacs-server timeout*/
      {
         UI32_T timeout = 0;
         if (TACACS_POM_GetRunningServerTimeout(&timeout) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_1("tacacs-server timeout %lu\n", (unsigned long)timeout);
         }
      }
#endif /* #if (SYS_CPNT_TACACS_PLUS_RETRY_TIMEOUT == TRUE ) */

      APPEND_RUNNING_CFG_0("!\n");
   }

#else  /* Single tacacs server */

   /*tacacs series*/
   {
      /*tacacs server ip*/
      {
         UI32_T serverip;

         if (TACACS_POM_GetRunningServerIP(&serverip) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_4("tacacs-server host %d.%d.%d.%d\n",((UI8_T *)(&serverip))[0],
                                                                  ((UI8_T *)(&serverip))[1],
                                                                  ((UI8_T *)(&serverip))[2],
                                                                  ((UI8_T *)(&serverip))[3]);
         }
      }
      /*tacacs server key*/
      {
         char  serversecret[MAXSIZE_radiusServerGlobalKey + 1] = {0};

         if (TACACS_POM_GetRunningServerSecret((UI8_T *)serversecret) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            UI8_T *out_ptr;
            UI32_T out_len;
            char  string[CLI_DEF_MAX_BUFSIZE+1];

#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
            CLI_LIB_Str_Add_Quote(serversecret,string);
            //APPEND_RUNNING_CFG_1("tacacs-server key %s\n", buf/*serversecret*/);
#else
            strcpy(string,serversecret);
            //APPEND_RUNNING_CFG_1("tacacs-server key %s\n", serversecret);
#endif
            /* encrypt for radius key */
            if(L_Base64((UI8_T *)string, strlen(string), &out_ptr, &out_len, L_BASE64_ENCODE))
            {
                memcpy(string,out_ptr,out_len);
                string[out_len] = '\0';
                L_MM_Free(out_ptr);
                APPEND_RUNNING_CFG_1("tacacs-server key %s\n", string);
            }
            else
            {
                CLI_LIB_PrintStr("\r\nFailed to encrypt TACACS key.\r\n");
            }

         }
      }

      /*tacacs server port*/
      {
         UI32_T serverport;

         if (TACACS_POM_GetRunningServerPort(&serverport) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_1("tacacs-server port %lu\n", (unsigned long)serverport);
         }
      }
      /* tacacs server retransmit */
      {
         UI32_T retransmit = 0;
         if (TACACS_POM_GetRunningRetransmit(&retransmit) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_1("tacacs-server retransmit %d\n", retransmit);
         }
      }
      /* tacacs server timeout */
      {
         UI32_T timeout = 0;
         if (TACACS_POM_GetRunningTimeout(&timeout) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            APPEND_RUNNING_CFG_1("tacacs-server timeout %d\n", timeout);
         }
      }
   }
#endif
#endif

/*#else*/
#if 0
   /*authentication login*/
   {
      USERAUTH_Auth_Method_T login_method = 0;
      if (USERAUTH_POM_GetRunningAuthMethod(&login_method) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         switch(login_method)
         {
         case USERAUTH_AUTH_LOCAL_ONLY:
            APPEND_RUNNING_CFG_0("authentication login local\n");
            break;

         case USERAUTH_AUTH_REMOTE_ONLY:
            APPEND_RUNNING_CFG_0("authentication login radius\n");
            break;

         case USERAUTH_AUTH_REMOTE_THEN_LOCAL:
            APPEND_RUNNING_CFG_0("authentication login radius local\n");
            break;

         case USERAUTH_AUTH_LOCAL_THEN_REMOTE:
            APPEND_RUNNING_CFG_0("authentication login local radius\n");
            break;

         default:
            break;
         }
         APPEND_RUNNING_CFG_0("!\n");
      }
   }
#endif
#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("Remote auth (TACACS RADIUS) complete\r\n");
#endif


#if (SYS_CPNT_AUTHORIZATION == TRUE)
    {
        AAA_AuthorListEntryInterface_T aaa_author_list_entry;
        memset(&aaa_author_list_entry, 0, sizeof(AAA_AuthorListEntryInterface_T));
        /*command: aaa authorization exec {default | list-name} group {tacacs+ | groupname}*/

        while(AAA_POM_GetNextRunningAuthorListEntry(&aaa_author_list_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (aaa_author_list_entry.list_type.client_type == AAA_CLIENT_TYPE_EXEC)
            {
                APPEND_RUNNING_CFG_2("aaa authorization exec %s group %s\n", aaa_author_list_entry.list_name, aaa_author_list_entry.group_name);
            }
        }
        APPEND_RUNNING_CFG_0("!\n");
    }
#endif /*#if (SYS_CPNT_AUTHORIZATION == TRUE)*/

#if (SYS_CPNT_AUTHORIZATION_COMMAND == TRUE)
    {
        AAA_AuthorListEntryInterface_T aaa_author_list_entry;
        memset(&aaa_author_list_entry, 0, sizeof(AAA_AuthorListEntryInterface_T));
        /*command: aaa authorization command priv-lvl {default | list-name} group {tacacs+ | groupname} */

        while (AAA_POM_GetNextRunningAuthorListEntry(&aaa_author_list_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (aaa_author_list_entry.list_type.client_type == AAA_CLIENT_TYPE_COMMANDS)
            {
                APPEND_RUNNING_CFG_3("aaa authorization command %lu %s group %s\n",
                    (unsigned long)aaa_author_list_entry.list_type.priv_lvl,
                    aaa_author_list_entry.list_name,
                    aaa_author_list_entry.group_name);
            }
        }
        APPEND_RUNNING_CFG_0("!\n");
    }
#endif /*#if (SYS_CPNT_AUTHORIZATION_COMMAND == TRUE)*/

#if (SYS_CPNT_ACCOUNTING == TRUE)
    /*Accounting family*/
    {
        AAA_AccListEntryInterface_T aaa_acc_list_entry;
        UI32_T update_interval;
        memset(&aaa_acc_list_entry, 0, sizeof(AAA_AccListEntryInterface_T));
        /*command: aaa accounting dot1x {default | list-name} {start-stop} group {radius | tacacs+ | groupname}*/
        while(AAA_POM_GetNextRunningAccListEntry(&aaa_acc_list_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(aaa_acc_list_entry.client_type == AAA_CLIENT_TYPE_DOT1X) /*dot1x*/
            {
                APPEND_RUNNING_CFG_2("aaa accounting dot1x %s start-stop group %s\n", aaa_acc_list_entry.list_name, aaa_acc_list_entry.group_name);
            }
            else if(aaa_acc_list_entry.client_type == AAA_CLIENT_TYPE_EXEC) /*exec*/
            {
                APPEND_RUNNING_CFG_2("aaa accounting exec %s start-stop group %s\n", aaa_acc_list_entry.list_name, aaa_acc_list_entry.group_name);
            }
#if (SYS_CPNT_ACCOUNTING_COMMAND == TRUE)
            else if(aaa_acc_list_entry.client_type == AAA_CLIENT_TYPE_COMMANDS) /*commands*/
            {
                APPEND_RUNNING_CFG_3("aaa accounting commands %lu %s start-stop group %s\n", (unsigned long)aaa_acc_list_entry.priv_lvl, aaa_acc_list_entry.list_name, aaa_acc_list_entry.group_name);
            }
#endif /*#if (SYS_CPNT_ACCOUNTING_COMMAND == TRUE)*/
        }
        APPEND_RUNNING_CFG_0("!\n");

        /*command: aaa accounting update [periodic number]*/
        if(AAA_POM_GetRunningAccUpdateInterval(&update_interval) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(update_interval != 0)
            {
                APPEND_RUNNING_CFG_1("aaa accounting update periodic %lu\n", (unsigned long)update_interval);
            }
            else
            {
                APPEND_RUNNING_CFG_0("no aaa accounting update\n");
            }
        }

    }
#endif /*#if (SYS_CPNT_ACCOUNTING == TRUE)*/
#if (SYS_CPNT_AAA == TRUE)
    /*Aaa Group Server*/
    {
        AAA_RadiusGroupEntryInterface_T aaa_radius_group_entry;
        AAA_RadiusEntryInterface_T aaa_radius_entry;
        AAA_TacacsPlusGroupEntryInterface_T aaa_tacacs_plus_group_entry;
        AAA_TacacsPlusEntryInterface_T aaa_tacacs_plus_entry;

        memset(&aaa_radius_group_entry, 0, sizeof(AAA_RadiusGroupEntryInterface_T));
        memset(&aaa_tacacs_plus_group_entry, 0, sizeof(AAA_TacacsPlusGroupEntryInterface_T));
        memset(&aaa_radius_entry, 0, sizeof(AAA_RadiusEntryInterface_T));
        memset(&aaa_tacacs_plus_group_entry, 0, sizeof(AAA_TacacsPlusGroupEntryInterface_T));

        /*command: aaa group server {radius | tacacs+} group-name*/
        while(AAA_POM_GetNextRunningRadiusGroupEntry(&aaa_radius_group_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("aaa group server radius %s\n", aaa_radius_group_entry.group_name);
            /*command: server {server-index | ip-address}*/
            aaa_radius_entry.radius_index = 0;
            while(AAA_POM_GetNextRunningRadiusEntry(aaa_radius_group_entry.group_index, &aaa_radius_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_1("server %lu\n", aaa_radius_entry.radius_server_index);
            }
            APPEND_RUNNING_CFG_0("!\n");

        }


        /*command: aaa group server {tacacs+} group-name*/
        while(AAA_POM_GetNextRunningTacacsPlusGroupEntry(&aaa_tacacs_plus_group_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("aaa group server tacacs+ %s\n", aaa_tacacs_plus_group_entry.group_name);
            /*command: server {server-index | ip-address}*/
            memset(&aaa_tacacs_plus_entry, 0, sizeof(AAA_TacacsPlusEntryInterface_T));
            while(AAA_POM_GetNextRunningTacacsPlusEntry(aaa_tacacs_plus_group_entry.group_index, &aaa_tacacs_plus_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                APPEND_RUNNING_CFG_1("server %lu\n", (unsigned long)aaa_tacacs_plus_entry.tacacs_server_index);
            }

            APPEND_RUNNING_CFG_0("!\n");
        }

    }
#endif /*#if (SYS_CPNT_AAA == TRUE)*/
   return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_COS_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                           UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;

    /*map ip precedence*/
#if (SYS_CPNT_COS_ING_IP_PRECEDENCE_TO_COS == TRUE)
    {
        COS_VM_MAPPING_FLAG_T flag;

#if(SYS_CPNT_QOS_V2 == TRUE)
        if (L4_PMGR_COS_GetRunningIpPrecedenceDscpMappingStatus(&flag) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
#else
        if (L4_COS_PMGR_GetRunningIpPrecedenceDscpMappingStatus(&flag) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
#endif
        {
            switch(flag)
            {
            case COS_VM_IPPRECEDENCE_MAPPING_ENABLED:
                APPEND_RUNNING_CFG_0("map ip precedence\n");
                break;

            case COS_VM_DSCP_MAPPING_ENABLED:
                APPEND_RUNNING_CFG_0("no map ip precedence\n");
                break;

            case COS_VM_DISABLE_BOTH:
                APPEND_RUNNING_CFG_0("no map ip precedence\n");
                break;

            default:
                ;
            }
        }
    }
#endif /* #if (SYS_CPNT_COS_ING_IP_PRECEDENCE_TO_COS == TRUE) */

    /*map ip dscp*/
#if (SYS_CPNT_COS_CONTAIN_CLI_MAP_IP_DSCP == TRUE)
    {
        COS_VM_MAPPING_FLAG_T flag;

#if(SYS_CPNT_QOS_V2 == TRUE)
        if (L4_PMGR_COS_GetRunningIpPrecedenceDscpMappingStatus(&flag) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
#else
        if (L4_COS_PMGR_GetRunningIpPrecedenceDscpMappingStatus(&flag) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
#endif
        {
            switch(flag)
            {
            case COS_VM_DSCP_MAPPING_ENABLED:
                APPEND_RUNNING_CFG_0("map ip dscp\n");
                break;

            case COS_VM_IPPRECEDENCE_MAPPING_ENABLED:
                APPEND_RUNNING_CFG_0("no map ip dscp\n");
                break;

            case COS_VM_DISABLE_BOTH:
                APPEND_RUNNING_CFG_0("no map ip dscp\n");
                break;

            default:
                ;
            }
        }
    }
#endif /* #if (SYS_CPNT_COS_CONTAIN_CLI_MAP_IP_DSCP == TRUE) */

#if (SYS_CPNT_WRR_Q_MODE_PER_PORT_CTRL == FALSE)
    /* queue scheduling mod */
    {
        UI32_T mode;
        UI16_T priority = COS_TYPE_PRIORITY_USER;
        UI32_T default_mode = COS_VM_SCHEDULING_WEIGHT_ROUND_ROBIN;

        if (TRUE == L4_PMGR_QOS_GetPriorityEgressQueueMode(priority, &mode))
        {
            if (mode != default_mode)
            {
                switch (mode)
                {
                    case COS_VM_SCHEDULING_WEIGHT_ROUND_ROBIN:
                        APPEND_RUNNING_CFG_0("queue mode wrr\n");
                        break;
                    case COS_VM_SCHEDULING_STRICT_PRIORITY:
                        APPEND_RUNNING_CFG_0("queue mode strict\n");
                        break;
                    case COS_VM_SCHEDULING_METHOD_DRR:
                        APPEND_RUNNING_CFG_0("queue mode drr\n");
                        break;
                    case COS_VM_SCHEDULING_METHOD_SP_WRR:
                    case COS_VM_SCHEDULING_METHOD_SP_DRR:
                        {
                            UI32_T queue;
                            COS_VM_QUEUE_STRICT_STATUS_T strict_status;

                            if(COS_VM_SCHEDULING_METHOD_SP_WRR == mode)
                            {
                                APPEND_RUNNING_CFG_0("queue mode strict-wrr ");
                            }
                            else if(COS_VM_SCHEDULING_METHOD_SP_WRR == mode)
                            {
                                APPEND_RUNNING_CFG_0("queue mode strict-drr ");
                            }

                            for (queue = 0; queue < SYS_ADPT_MAX_NBR_OF_PRIORITY_QUEUE; ++queue)
                            {
                                if (TRUE == L4_PMGR_QOS_GetPriorityEgressQueueStrictStatus(priority, queue, &strict_status)
                                    && (strict_status == COS_VM_QUEUE_STRICT_STATUS_ENABLED))
                                {
                                    APPEND_RUNNING_CFG_0("1 ");
                                }
                                else
                                {
                                    APPEND_RUNNING_CFG_0("0 ");
                                }
                            }
                            APPEND_RUNNING_CFG_0("\n");
                        }
                        break;
                }
            }
        }
    }
#endif /* #if (SYS_CPNT_WRR_Q_MODE_PER_PORT_CTRL == FALSE) */

#if (SYS_CPNT_WRR_Q_WEIGHT_PER_PORT_CTRL == FALSE)
    {
        UI32_T queue;
        UI32_T weights[SYS_ADPT_MAX_NBR_OF_PRIORITY_QUEUE];
        BOOL_T change = FALSE;

        for (queue = 0; queue < SYS_ADPT_MAX_NBR_OF_PRIORITY_QUEUE; ++queue)
        {
            SYS_TYPE_Get_Running_Cfg_T result;

            result = L4_PMGR_QOS_GetRunningEgressQueueWeight(
                         queue, &(weights[queue]));

            if (result == SYS_TYPE_GET_RUNNING_CFG_FAIL)
            {
                change = FALSE;
                break;
            }

            if (result == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                change = TRUE;
            }
        }

        if (change == TRUE)
        {
            APPEND_RUNNING_CFG_0("queue weight ");
            for (queue = 0; queue < SYS_ADPT_MAX_NBR_OF_PRIORITY_QUEUE; queue++)
            {
                APPEND_RUNNING_CFG_1("%lu ", weights[queue]);
            }
            APPEND_RUNNING_CFG_0("\n");
        }
    }
#endif /* #if (SYS_CPNT_WRR_Q_WEIGHT_PER_PORT_CTRL == FALSE) */

    /*map ip port*/
#if (SYS_CPNT_COS_ING_IP_PORT_TO_COS == TRUE)
    {
        COS_VM_TCPPORT_MAPPING_FLAG_T flag;

#if (SYS_CPNT_QOS_V2 == TRUE)
        if (L4_PMGR_COS_GetRunningTcpPortMappingStatus(&flag) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
#else
        if (L4_COS_PMGR_GetRunningTcpPortMappingStatus(&flag) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
#endif
        {
            switch(flag)
            {
             case COS_VM_MAPPING_ENABLED:
                APPEND_RUNNING_CFG_0("map ip port\n");
             break;

             case COS_VM_MAPPING_DISABLED:
                APPEND_RUNNING_CFG_0("no map ip port\n");
             break;

             default:
              ;
            }
        }
    }
#endif /* #if (SYS_CPNT_COS_ING_IP_PORT_TO_COS == TRUE) */


#if RUNCFG_DEVELOP
    CLI_LIB_PrintStr("cos complete\r\n");
#endif

    return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_SSH_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
   UI32_T buffer_count = b_count;
#if(SYS_CPNT_SSHD == TRUE || SYS_CPNT_SSH2 == TRUE)
/*pttch need to call get running function*/
   /*ip ssh authentication-retries*/
   {
      UI32_T retries;
      if ( (retries = SSHD_MGR_GetAuthenticationRetries()) != SSHD_DEFAULT_AUTHENTICATION_RETRIES)
      {
         APPEND_RUNNING_CFG_1("ip ssh authentication-retries %lu\n",(unsigned long)retries);
      }
   }
   /*ip ssh timeout*/
   {
      UI32_T timeout;
      if ((timeout = SSHD_MGR_GetNegotiationTimeout()) != SSHD_DEFAULT_NEGOTIATION_TIMEOUT)
      {
         APPEND_RUNNING_CFG_1("ip ssh timeout %lu\n",(unsigned long)timeout);
      }
   }
   /*ip ssh server*/
   {
      UI32_T status;
      if ((status = SSHD_MGR_GetSshdStatus()) != SSHD_DEFAULT_STATE)
      {
         switch(status)
         {
         case SSHD_STATE_ENABLED:
            APPEND_RUNNING_CFG_0("ip ssh server\n");
            break;

         case SSHD_STATE_DISABLED:
            APPEND_RUNNING_CFG_0("no ip ssh server\n");
            break;

         default:
            break;
         }
      }
   }
   /*ip ssh server-key size*/
   {
      UI32_T key_size = 0;
      if(SSHD_MGR_GetRunningServerKeySize(&key_size)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1("ip ssh server-key size %lu\n", (unsigned long)key_size);
      }
      APPEND_RUNNING_CFG_0("!\n");
   }

#endif

   {
      UI32_T status;
      UI32_T port;
      UI32_T maxSession;

      if (TELNET_MGR_GetRunningTnpdStatus(&status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         switch(status)
         {
         case TELNET_STATE_ENABLED:
            APPEND_RUNNING_CFG_0("ip telnet server\n");
            break;

         case TELNET_STATE_DISABLED:
            APPEND_RUNNING_CFG_0("no ip telnet server\n");
            break;

         default:
            break;
         }
      }

      if(TELNET_MGR_GetRunningTnpdPort(&port) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1("ip telnet port %lu\n", (unsigned long)port);
      }

      if(TELNET_MGR_GetRunningTnpdMaxSession(&maxSession) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         APPEND_RUNNING_CFG_1("ip telnet max-sessions %lu\n", (unsigned long)maxSession);
      }
      APPEND_RUNNING_CFG_0("!\n");
   }

#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("SSH complete\r\n");
#endif

   return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_TFTP_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    UI32_T retry_times;
    UI32_T timeout;

    if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == XFER_PMGR_GetRunningTftpRetryTimes(&retry_times))
    {
        APPEND_RUNNING_CFG_1("ip tftp retry %ld\n", (long)retry_times);
    }

    if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == XFER_PMGR_GetRunningTftpTimeout(&timeout))
    {
        APPEND_RUNNING_CFG_1("ip tftp timeout %ld\n", (long)timeout);
    }

    APPEND_RUNNING_CFG_0("!\n");

    return buffer_count;
}

#if (SYS_CPNT_PORT_TRAFFIC_SEGMENTATION == TRUE)
/* 2006/06/28
 * ES4649-38-00189: free memory before return
 */
#if (SYS_CPNT_PORT_TRAFFIC_SEGMENTATION_MODE == SYS_CPNT_PORT_TRAFFIC_SEGMENTATION_MODE_MULTIPLE_SESSION)
static UI32_T cli_runcfg_get_pvlan_ms_parameter_macro(UI32_T unit_id, char *buffer, char *temp_buffer,
                 UI32_T buffer_size, UI32_T b_count, char *tmp_buff, char *uplink_str_eth, char *uplink_str_pch,
                 char *downlink_str_eth, char *downlink_str_pch, char *uplink_str, char *downlink_str,
                 char *uplink_port_list, char *downlink_port_list)
{
    UI32_T buffer_count = b_count;
    int runcfg_line_count = 0;

    /* pvlan: ENABLE/DISABLE*/
    {
        UI32_T vlan_status;

        if( SWCTRL_POM_GetRunningPrivateVlanStatus(&vlan_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            switch(vlan_status)
            {
            case VAL_privateVlanStatus_enabled:
                APPEND_RUNNING_CFG_0("traffic-segmentation\n");
                break;

            case VAL_privateVlanStatus_disabled:
                APPEND_RUNNING_CFG_0("no traffic-segmentation\n");
                break;

            default:
                break;
            }
            runcfg_line_count++;
        }
    }

    /* get private VLAN mode */
    {
        UI32_T status;

        if (SWCTRL_POM_GetRunningPrivateVlanUplinkToUplinkStatus(&status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            switch(status)
            {
            case SYS_DFLT_TRAFFIC_SEG_UPLINK_TO_UPLINK_MODE_BLOCKING:
                APPEND_RUNNING_CFG_0("traffic-segmentation uplink-to-uplink blocking\n");
                break;
            case SYS_DFLT_TRAFFIC_SEG_UPLINK_TO_UPLINK_MODE_FORWARDING:
                APPEND_RUNNING_CFG_0("traffic-segmentation uplink-to-uplink forwarding\n");
                break;
            default:
                return CLI_ERR_INTERNAL;
            }
            runcfg_line_count++;
        }
    }

    /* pvlan: uplink/downlink*/
    {
        char  bitmap[(SYS_ADPT_MAX_NBR_OF_TRUNK_PER_SYSTEM/8)+1+1] = {0};/*second +1 is for NULL*/
        UI32_T i;
        UI32_T j;
        UI32_T session_id;

        for(session_id = 1; session_id <= SYS_ADPT_PORT_TRAFFIC_SEGMENTATION_MAX_NBR_OF_SESSIONS; session_id++)
        {
            if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                SWCTRL_POM_GetRunningPrivateVlanPortListBySessionId(session_id, (UI8_T *)uplink_port_list, (UI8_T *)downlink_port_list))
            {
                /*up-link: eth*/
                CLI_LIB_Stack_Bitmap_To_List(uplink_port_list, &unit_id, uplink_str_eth, 128, SYS_ADPT_TOTAL_NBR_OF_LPORT,TRUE);  //talor 2004-08-26

                /*up-link: pch*/
                memset(bitmap, 0, sizeof(bitmap));
                for(i=SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER, j=0; i<=SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER + SYS_ADPT_MAX_NBR_OF_TRUNK_PER_SYSTEM - 1; i++, j++)
                {
                    if(uplink_port_list[(UI32_T)((i-1)/8)] & (1 << ( 7 - ((i-1)%8)))  )
                        bitmap[(i-SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER)/8] |= 1<< (7-(j%8));
                }
                CLI_LIB_Bitmap_To_List(bitmap, uplink_str_pch, 128, SYS_ADPT_MAX_NBR_OF_TRUNK_PER_SYSTEM,TRUE);

                uplink_str[0] = 0;

                if(uplink_str_eth[0] != 0)
                {
                    SYSFUN_Sprintf((char *)tmp_buff, "ethernet %lu/%s", (unsigned long)unit_id, uplink_str_eth);  //talor 2004-08-26
                    strcat((char *)uplink_str, (char *)tmp_buff);
                }

                if(uplink_str_pch[0] != 0)
                {
                    SYSFUN_Sprintf((char *)tmp_buff, "port-channel %s", uplink_str_pch);
                    if(uplink_str[0]!= 0)
                        strcat((char *)uplink_str, " ");
                    strcat((char *)uplink_str, (char *)tmp_buff);
                }

                /*down-link: eth*/
                CLI_LIB_Stack_Bitmap_To_List(downlink_port_list, &unit_id, downlink_str_eth, 128, SYS_ADPT_TOTAL_NBR_OF_LPORT,TRUE); //talor 2004-08-26

                /*down-link: pch*/
                memset(bitmap, 0 , sizeof(bitmap));
                for(i=SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER, j=0; i<=SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER + SYS_ADPT_MAX_NBR_OF_TRUNK_PER_SYSTEM - 1; i++, j++)
                {
                    if(uplink_port_list[(UI32_T)((i-1)/8)] & (1 << ( 7 - ((i-1)%8)))  )
                        bitmap[(i-SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER)/8] |= 1<< (7-(j%8));
                }
                CLI_LIB_Bitmap_To_List(bitmap, downlink_str_pch, 128, SYS_ADPT_MAX_NBR_OF_TRUNK_PER_SYSTEM,TRUE);

                downlink_str[0] = 0;

                if(downlink_str_eth[0] != 0)
                {
                    SYSFUN_Sprintf((char *)tmp_buff, "ethernet %lu/%s", (unsigned long)unit_id, downlink_str_eth);
                    strcat((char *)downlink_str, (char *)tmp_buff);
                }

                if(downlink_str_pch[0] != 0)
                {
                    SYSFUN_Sprintf((char *)tmp_buff, "port-channel %s", downlink_str_pch);
                    if(downlink_str[0]!=0)
                        strcat((char *)downlink_str, " ");
                    strcat((char *)downlink_str, (char *)tmp_buff);
                }

                /*generate*/
                if (uplink_str[0] != 0 && downlink_str[0] != 0)
                {
                    APPEND_RUNNING_CFG_3("traffic-segmentation session %lu uplink %s downlink %s\n", (unsigned long)session_id, uplink_str, downlink_str);
                }
                else if (uplink_str[0] != 0)
                {
                    APPEND_RUNNING_CFG_2("traffic-segmentation session %lu uplink %s\n", (unsigned long)session_id, uplink_str);
                }
                else if (downlink_str[0] != 0)
                {
                    APPEND_RUNNING_CFG_2("traffic-segmentation session %lu downlink %s\n", (unsigned long)session_id, downlink_str);
                }
                else
                {
                    APPEND_RUNNING_CFG_1("traffic-segmentation session %lu\n", (unsigned long)session_id);
                }
                runcfg_line_count++;
            }
        }
    }

    if (runcfg_line_count > 0)
    {
        APPEND_RUNNING_CFG_0("!\n");
    }
#if RUNCFG_DEVELOP
    CLI_LIB_PrintStr("PVLAN_MS complete\r\n");
#endif
    return buffer_count;
}
#else
static UI32_T cli_runcfg_get_pvlan_parameter_macro(UI32_T unit_id, char *buffer, char *temp_buffer,
                 UI32_T buffer_size, UI32_T b_count, char *tmp_buff, char *uplink_str_eth, char *uplink_str_pch,
                 char *downlink_str_eth, char *downlink_str_pch, char *uplink_str, char *downlink_str,
                 char *uplink_port_list, char *downlink_port_list)
{
   UI32_T buffer_count = b_count;

   {
      /* pvlan: ENABLE/DISABLE*/
      UI32_T vlan_status;

      if( SWCTRL_POM_GetRunningPrivateVlanStatus(&vlan_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         switch(vlan_status)
         {
         case VAL_privateVlanStatus_enabled:
            APPEND_RUNNING_CFG_0("traffic-segmentation\n");
            break;

         case VAL_privateVlanStatus_disabled:
            APPEND_RUNNING_CFG_0("no traffic-segmentation\n");
            break;

         default:
            break;
         }
      }

      /* pvlan: uplink/downlink*/
      {
         char  bitmap[(SYS_ADPT_MAX_NBR_OF_TRUNK_PER_SYSTEM/8)+1+1] = {0};/*second +1 is for NULL*/
         UI32_T i;
         UI32_T j;

         if(SWCTRL_POM_GetRunningPrivateVlanUplinkPortList((UI8_T *)uplink_port_list)     ==  SYS_TYPE_GET_RUNNING_CFG_SUCCESS &&
            SWCTRL_POM_GetRunningPrivateVlanDownlinkPortList((UI8_T *)downlink_port_list) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
            /*up-link: eth*/
            //memcpy(&bitmap, uplink_port_list, sizeof(UI32_T));
             CLI_LIB_Stack_Bitmap_To_List(uplink_port_list, &unit_id, uplink_str_eth, 128, SYS_ADPT_TOTAL_NBR_OF_LPORT,TRUE);  //talor 2004-08-26

            /*up-link: pch*/

            for(i=SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER, j=0; i<=SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER + SYS_ADPT_MAX_NBR_OF_TRUNK_PER_SYSTEM - 1; i++, j++)
            {
               if(uplink_port_list[(UI32_T)((i-1)/8)] & (1 << ( 7 - ((i-1)%8)))  )
                  bitmap[(i-SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER)/8] |= 1<< (7-(j%8));
            }
            CLI_LIB_Bitmap_To_List(bitmap, uplink_str_pch, 128, SYS_ADPT_MAX_NBR_OF_TRUNK_PER_SYSTEM,TRUE);

            if(uplink_str_eth[0] != 0)
            {
               SYSFUN_Sprintf((char *)tmp_buff, "ethernet %lu/%s", (unsigned long)unit_id, uplink_str_eth);  //talor 2004-08-26
               strcat((char *)uplink_str, (char *)tmp_buff);
            }

            if(uplink_str_pch[0] != 0)
            {
               SYSFUN_Sprintf((char *)tmp_buff, "port-channel %s", uplink_str_pch);
               if(uplink_str[0]!= 0)
                  strcat((char *)uplink_str, " ");
               strcat((char *)uplink_str, (char *)tmp_buff);
            }

            /*down-link: eth*/
            //memcpy(&bitmap, downlink_port_list, sizeof(UI32_T));
            CLI_LIB_Stack_Bitmap_To_List(downlink_port_list, &unit_id, downlink_str_eth, 128, SYS_ADPT_TOTAL_NBR_OF_LPORT,TRUE); //talor 2004-08-26

            /*down-link: pch*/
            memset(bitmap, 0 , sizeof(bitmap));
            for(i=SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER, j=0; i<=SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER + SYS_ADPT_MAX_NBR_OF_TRUNK_PER_SYSTEM - 1; i++, j++)
            {
               if(uplink_port_list[(UI32_T)((i-1)/8)] & (1 << ( 7 - ((i-1)%8)))  )
                  bitmap[(i-SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER)/8] |= 1<< (7-(j%8));
            }
            CLI_LIB_Bitmap_To_List(bitmap, downlink_str_pch, 128, SYS_ADPT_MAX_NBR_OF_TRUNK_PER_SYSTEM,TRUE);

            if(downlink_str_eth[0] != 0)
            {
               SYSFUN_Sprintf((char *)tmp_buff, "ethernet %lu/%s", (unsigned long)unit_id, downlink_str_eth);
               strcat((char *)downlink_str, (char *)tmp_buff);
            }

            if(downlink_str_pch[0] != 0)
            {
               SYSFUN_Sprintf((char *)tmp_buff, "port-channel %s", downlink_str_pch);
               if(downlink_str[0]!=0)
                  strcat((char *)downlink_str, " ");
               strcat((char *)downlink_str, (char *)tmp_buff);
            }


            /*generate*/
            if(uplink_str[0]!= 0 && downlink_str[0]!= 0)
            {
               APPEND_RUNNING_CFG_2("traffic-segmentation uplink %s downlink %s\n", uplink_str, downlink_str);
            }
         }
      }
      APPEND_RUNNING_CFG_0("!\n");

   }
#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("PVLAN complete\r\n");
#endif
   return buffer_count;
}
#endif /* #if (SYS_CPNT_PORT_TRAFFIC_SEGMENTATION_MODE == SYS_CPNT_PORT_TRAFFIC_SEGMENTATION_MODE_MULTIPLE_SESSION) */
#endif

static UI32_T CLI_RUNCFG_Get_PVLAN_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{

    UI32_T return_value = b_count;

#if (SYS_CPNT_PORT_TRAFFIC_SEGMENTATION == TRUE)

    /*pvlan uplink   xxxxx  downlink xxxxx */
    char   *tmp_buff; //[128] = {0};

    char   *uplink_str_eth; //[128]   = {0};
    char   *uplink_str_pch; //[128]   = {0};

    char   *downlink_str_eth; //[128] = {0};
    char   *downlink_str_pch; //[128] = {0};

    char   *uplink_str;   //[256] = {0};
    char   *downlink_str; //[256] = {0};

    char  *uplink_port_list;   //[SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST] = {0};
    char  *downlink_port_list; //[SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST] = {0};

    if((tmp_buff = calloc(128, sizeof(char))) == 0)
        return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;

    if((uplink_str_eth = calloc(128, sizeof(char))) == 0)
    {
        free(tmp_buff);
        return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
    }

    if((uplink_str_pch = calloc(128, sizeof(char))) == 0)
    {
        free(tmp_buff);
        free(uplink_str_eth);
        return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
    }

    if((downlink_str_eth = calloc(128, sizeof(char))) == 0)
    {
        free(tmp_buff);
        free(uplink_str_eth);
        free(uplink_str_pch);
        return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
    }

    if((downlink_str_pch = calloc(128, sizeof(char))) == 0)
    {
        free(tmp_buff);
        free(uplink_str_eth);
        free(uplink_str_pch);
        free(downlink_str_eth);
        return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
    }

    if((uplink_str = calloc(256, sizeof(char))) == 0)
    {
        free(tmp_buff);
        free(uplink_str_eth);
        free(uplink_str_pch);
        free(downlink_str_eth);
        free(downlink_str_pch);
        return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
    }

    if((downlink_str = calloc(256, sizeof(char))) == 0)
    {
        free(tmp_buff);
        free(uplink_str_eth);
        free(uplink_str_pch);
        free(downlink_str_eth);
        free(downlink_str_pch);
        free(uplink_str);
        return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
    }

    if((uplink_port_list = calloc(SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST, sizeof(char))) == 0)
    {
        free(tmp_buff);
        free(uplink_str_eth);
        free(uplink_str_pch);
        free(downlink_str_eth);
        free(downlink_str_pch);
        free(uplink_str);
        free(downlink_str);
        return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
    }

    if((downlink_port_list = calloc(SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST, sizeof(char))) == 0)
    {
        free(tmp_buff);
        free(uplink_str_eth);
        free(uplink_str_pch);
        free(downlink_str_eth);
        free(downlink_str_pch);
        free(uplink_str);
        free(downlink_str);
        free(uplink_port_list);
        return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
    }

    /* 2006/06/28
     * ES4649-38-00189: free memory before return
     */
#if (SYS_CPNT_PORT_TRAFFIC_SEGMENTATION_MODE == SYS_CPNT_PORT_TRAFFIC_SEGMENTATION_MODE_MULTIPLE_SESSION)
    return_value = cli_runcfg_get_pvlan_ms_parameter_macro(unit_id, buffer, temp_buffer, buffer_size, b_count, tmp_buff,
                         uplink_str_eth, uplink_str_pch, downlink_str_eth, downlink_str_pch, uplink_str,
                         downlink_str, uplink_port_list, downlink_port_list);
#else
    return_value = cli_runcfg_get_pvlan_parameter_macro(unit_id, buffer, temp_buffer, buffer_size, b_count, tmp_buff,
                         uplink_str_eth, uplink_str_pch, downlink_str_eth, downlink_str_pch, uplink_str,
                         downlink_str, uplink_port_list, downlink_port_list);
#endif

    free(tmp_buff);
    free(uplink_str_eth);
    free(uplink_str_pch);
    free(downlink_str_eth);
    free(downlink_str_pch);
    free(uplink_str);
    free(downlink_str);
    free(uplink_port_list);
    free(downlink_port_list);
#endif
    return return_value;
}

#if (SYS_CPNT_ECMP_BALANCE_MODE == TRUE)
static UI32_T CLI_RUNCFG_Get_ECMP_Global_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    UI32_T mode, idx;

    if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_POM_ROUTE_GetRunningEcmpBalanceMode(&mode, &idx))
    {
        switch (mode)
        {
        case NETCFG_TYPE_ECMP_DIP_L4_PORT:
            APPEND_RUNNING_CFG_0("ecmp load-balance dst-ip-l4-port\n");
            break;
#if 0
        case NETCFG_TYPE_ECMP_L4_PORT:
            APPEND_RUNNING_CFG_0("ecmp load-balance l4-port\n");
            break;
#endif
        case NETCFG_TYPE_ECMP_HASH_SELECTION:
            APPEND_RUNNING_CFG_1("ecmp load-balance hash-selection-list %ld\n", (long)idx);

        default:
            break;
        }
    }

   return buffer_count;
}
#endif /* #if (SYS_CPNT_ECMP_BALANCE_MODE == TRUE) */

#if (CLI_SUPPORT_L3_FEATURE == 1)
static UI32_T CLI_RUNCFG_Get_L3_Per_Vlan_Parameter(UI32_T vid, UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
   UI32_T buffer_count = b_count;
   NETCFG_TYPE_InetRifConfig_T rif_config;
   UI32_T ifindex = 0;
   UI32_T  address_mode;
   UI8_T mask[SYS_ADPT_IPV4_ADDR_LEN];

   memset(&rif_config, 0, sizeof(rif_config));
   VLAN_VID_CONVERTTO_IFINDEX(vid, ifindex);
   rif_config.ifindex = ifindex;
   /*   Get Running configuration of subnet(ip,mask)    */

   if(NETCFG_POM_IP_GetIpAddressMode(ifindex, &address_mode)==NETCFG_TYPE_OK)
   {
      if(address_mode==NETCFG_TYPE_IP_ADDRESS_MODE_DHCP)
      {
         APPEND_RUNNING_CFG_0(" ip address dhcp\n");
      }
#if (SYS_CPNT_BOOTP == TRUE)
      else if(address_mode==NETCFG_TYPE_IP_ADDRESS_MODE_BOOTP)
      {
         APPEND_RUNNING_CFG_0(" ip address bootp\n");
      }
#endif
      else
      {

         /* get primary rif first */
         if(NETCFG_TYPE_OK == NETCFG_POM_IP_GetPrimaryRifFromInterface(&rif_config))
         {
             if((rif_config.addr.type == L_INET_ADDR_TYPE_IPV4)
                || (rif_config.addr.type == L_INET_ADDR_TYPE_IPV4Z))
             {

                  APPEND_RUNNING_CFG_4(" ip address %d.%d.%d.%d", rif_config.addr.addr[0], rif_config.addr.addr[1], rif_config.addr.addr[2], rif_config.addr.addr[3]);
                  IP_LIB_CidrToMask(rif_config.addr.preflen , mask);
                  APPEND_RUNNING_CFG_4(" %d.%d.%d.%d\n", mask[0], mask[1], mask[2], mask[3]);
             }
         }

         /* get secondary rif */
         memset(&rif_config, 0, sizeof(rif_config));
         rif_config.ifindex = ifindex;
         while(NETCFG_TYPE_OK == NETCFG_POM_IP_GetNextSecondaryRifFromInterface(&rif_config))
         {
             if((rif_config.addr.type != L_INET_ADDR_TYPE_IPV4)
                && (rif_config.addr.type != L_INET_ADDR_TYPE_IPV4Z))
                break;

                  APPEND_RUNNING_CFG_4(" ip address %d.%d.%d.%d", rif_config.addr.addr[0], rif_config.addr.addr[1], rif_config.addr.addr[2], rif_config.addr.addr[3]);
                  IP_LIB_CidrToMask(rif_config.addr.preflen , mask);
                  APPEND_RUNNING_CFG_4(" %d.%d.%d.%d secondary\n", mask[0], mask[1], mask[2], mask[3]);
               }
#if (SYS_CPNT_VIRTUAL_IP == TRUE)
        /* get virtual rif */
        memset(&rif_config, 0, sizeof(rif_config));
        rif_config.ifindex = ifindex;

        while(NETCFG_TYPE_OK == NETCFG_POM_IP_GetNextVirtualRifByIfindex(&rif_config))
        {
            APPEND_RUNNING_CFG_4(" ip address %d.%d.%d.%d", rif_config.addr.addr[0], rif_config.addr.addr[1], rif_config.addr.addr[2], rif_config.addr.addr[3]);
            IP_LIB_CidrToMask(rif_config.addr.preflen , mask);
            APPEND_RUNNING_CFG_4(" %d.%d.%d.%d virtual\n", mask[0], mask[1], mask[2], mask[3]);
        }
#endif


      }
   }

#if (SYS_CPNT_PROXY_ARP == TRUE)
   {
      NETCFG_TYPE_L3_Interface_T intf;

      memset(&intf, 0, sizeof(intf));
      intf.ifindex = ifindex;
      if (NETCFG_POM_IP_GetL3Interface(&intf) == NETCFG_TYPE_OK)
      {
         if(intf.u.physical_intf.proxy_arp_enable == TRUE)
         {
            APPEND_RUNNING_CFG_0(" ip proxy-arp\n");
         }
      }
   }
#endif

#if (SYS_CPNT_DHCP_INFORM == TRUE)
    {
        BOOL_T dhcp_inform = FALSE;
        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_POM_IP_GetRunningDhcpInform(ifindex, &dhcp_inform))
        {
            if(dhcp_inform)
            {
                APPEND_RUNNING_CFG_0(" ip dhcp inform\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no ip dhcp inform\n");
            }
        }
    }
#endif /* SYS_CPNT_DHCP_INFORM */

#if (SYS_CPNT_RIP == TRUE)
    {
        NETCFG_TYPE_RIP_If_T  rip_interface_entry;
        memset(&rip_interface_entry, 0, sizeof(NETCFG_TYPE_RIP_If_T));
        rip_interface_entry.ifindex = ifindex;

        if (NETCFG_PMGR_RIP_GetInterfaceEntry(&rip_interface_entry) == NETCFG_TYPE_OK)
        {
            if(rip_interface_entry.send_packet != TRUE)
            {
                APPEND_RUNNING_CFG_0(" no ip rip send-packet\n");
            }
            if(rip_interface_entry.recv_packet != TRUE)
            {
                APPEND_RUNNING_CFG_0(" no ip rip receive-packet\n");
            }

            if(rip_interface_entry.auth_mode != SYS_DFLT_RIP_AUTH_MODE)
            {
                if(rip_interface_entry.auth_mode == NETCFG_TYPE_RIP_AUTH_MD5)
                {
                    APPEND_RUNNING_CFG_0(" ip rip authentication mode md5\n");
                }
                else if(rip_interface_entry.auth_mode == NETCFG_TYPE_RIP_AUTH_SIMPLE_PASSWORD)
                {
                    APPEND_RUNNING_CFG_0(" ip rip authentication mode text\n");
                }
            }

            if(strcmp(rip_interface_entry.auth_str, ""))
            {
                APPEND_RUNNING_CFG_1(" ip rip authentication string %s\n", rip_interface_entry.auth_str);
            }

            if (RIP_IF_PARAM_CHECK (&rip_interface_entry, SEND_VERSION))
            {
                if(rip_interface_entry.send_version_type == NETCFG_TYPE_RIP_VERSION_VERSION_1)
                {
                    APPEND_RUNNING_CFG_0(" ip rip send version 1\n");
                }
                else if(rip_interface_entry.send_version_type == NETCFG_TYPE_RIP_VERSION_VERSION_2)
                {
                    APPEND_RUNNING_CFG_0(" ip rip send version 2\n");
                }
                else if(rip_interface_entry.send_version_type == NETCFG_TYPE_RIP_VERSION_VERSION_1_COMPATIBLE)
                {
                    APPEND_RUNNING_CFG_0(" ip rip send version 1-compatible\n");
                }
            }
            if (RIP_IF_PARAM_CHECK (&rip_interface_entry, RECV_VERSION))
            {
                if(rip_interface_entry.recv_version_type == NETCFG_TYPE_RIP_VERSION_VERSION_1)
                {
                    APPEND_RUNNING_CFG_0(" ip rip receive version 1\n");
                }
                else if(rip_interface_entry.recv_version_type == NETCFG_TYPE_RIP_VERSION_VERSION_2)
                {
                    APPEND_RUNNING_CFG_0(" ip rip receive version 2\n");
                }
                else if(rip_interface_entry.recv_version_type == NETCFG_TYPE_RIP_VERSION_VERSION_1_AND_2)
                {
                    APPEND_RUNNING_CFG_0(" ip rip receive version 1 2\n");
                }
            }

            if(rip_interface_entry.split_horizon != SYS_DFLT_RIP_SPLIT_HORIZON_TYPE)
            {
                if(rip_interface_entry.split_horizon == NETCFG_TYPE_RIP_SPLIT_HORIZON_NONE)
                {
                    APPEND_RUNNING_CFG_0(" no ip rip split-horizon\n");
                }
                else if(rip_interface_entry.split_horizon == NETCFG_TYPE_RIP_SPLIT_HORIZON)
                {
                    APPEND_RUNNING_CFG_0(" ip rip split-horizon\n");
                }
            }
        } /*  end of ip address for one vlan/interface    */
    }
#endif

#if (SYS_CPNT_DHCP_RELAY == TRUE)
    {
        UI32_T i;
        UI32_T ip_array[SYS_ADPT_MAX_NBR_OF_DHCP_RELAY_SERVER] = {0};

        if(DHCP_OM_OK == DHCP_POM_GetIfRelayServerAddress(ifindex, ip_array))
        {
            if(ip_array[0]!=0)
            {
                APPEND_RUNNING_CFG_0(" ip dhcp relay server");

                for(i=0;i<SYS_ADPT_MAX_NBR_OF_DHCP_RELAY_SERVER;i++)
                {
                    if(ip_array[i]!=0)
                    {
                        APPEND_RUNNING_CFG_4(" %d.%d.%d.%d",((UI8_T *)(&(ip_array[i])))[0], ((UI8_T *)(&(ip_array[i])))[1], ((UI8_T *)(&(ip_array[i])))[2], ((UI8_T *)(&(ip_array[i])))[3] );
                    }
                }
                APPEND_RUNNING_CFG_0("\n");
            }
        }
    }
#endif

#if (SYS_CPNT_DHCPV6_RELAY == TRUE)
    {
        char tmp_buf[L_INET_MAX_IPADDR_STR_LEN+1] = {0};
        UI32_T mcast_ifindex = 0;
        UI32_T vid = 0;
        DHCPv6_MGR_Ipv6_Addr_T uni_addr;
        L_INET_AddrIp_T  ipv6_addr;
        UI8_T flag;

        memset(&uni_addr, 0, sizeof(DHCPv6_MGR_Ipv6_Addr_T));
        memset(&ipv6_addr, 0, sizeof(L_INET_AddrIp_T));
        ipv6_addr.type = L_INET_ADDR_TYPE_IPV6;
        ipv6_addr.addrlen = SYS_ADPT_IPV6_ADDR_LEN;

        while(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == DHCPv6_POM_GetNextRunningRelayAddress(ifindex, &uni_addr))
        {
            memcpy(ipv6_addr.addr, uni_addr.s6_addr,SYS_ADPT_IPV6_ADDR_LEN);

            if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&ipv6_addr,
                                                               tmp_buf,
                                                               sizeof(tmp_buf)))
            {
                APPEND_RUNNING_CFG_1(" ipv6 dhcp relay destination %s\n",tmp_buf);
            }
        }

        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == DHCPv6_POM_GetRunningRelayAllVlan(ifindex, &flag))
        {
             APPEND_RUNNING_CFG(" ipv6 dhcp relay destination multicast all\n");
        }
        else
        {
            while(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == DHCPv6_POM_GetNextRunningRelayVlan(ifindex,&mcast_ifindex))
            {
                VLAN_OM_ConvertFromIfindex(mcast_ifindex, &vid);
                APPEND_RUNNING_CFG_1(" ipv6 dhcp relay destination multicast vlan %lu\n",(unsigned long)vid)
            }
        }

    }
#endif

#if (SYS_CPNT_OSPF == TRUE)
    {
        OSPF_TYPE_IfParam_T entry;
        UI32_T vr_id = SYS_DFLT_VR_ID;
        UI32_T vrf_id = SYS_DFLT_VRF_ID;
        UI8_T addr[SYS_ADPT_IPV4_ADDR_LEN];
        UI32_T indexlen = 0;
        memset(&entry, 0, sizeof(OSPF_TYPE_IfParam_T));
        entry.config_type = OSPF_CONFIGURATION_TYPE_CLI_WEB ;
        entry.ifindex = ifindex;
        while(OSPF_PMGR_GetNextIfParamEntry(vr_id, vrf_id, indexlen, &entry) == OSPF_TYPE_RESULT_SUCCESS)
        {
            char buf[25] = {0};
            indexlen = 1;
            memset(addr, 0, sizeof(addr));
            memcpy(addr, &entry.ip_address, sizeof(UI32_T));

            if (entry.mask_len != 0)
                snprintf (buf, 25, " ip ospf %d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);
            else
                snprintf (buf, 25, " ip ospf");

            /* Interface disable all.  */
            if (entry.config & OSPF_IF_PARAMS_DISABLE_ALL)
            {
                APPEND_RUNNING_CFG_1("%s disable all\n", buf);
            }

            /* Interface Network .  */
            if (entry.config & OSPF_IF_PARAMS_NETWORK_TYPE)
            {
            }

            /* OSPF interface authentication . */
            if (entry.config & OSPF_IF_PARAMS_AUTH_TYPE)
            {
                if(entry.auth_type == NETCFG_TYPE_OSPF_AUTH_SIMPLE)
                {
                    APPEND_RUNNING_CFG_1("%s authentication\n", buf);
                }
                else if(entry.auth_type == NETCFG_TYPE_OSPF_AUTH_NULL)
                {
                    APPEND_RUNNING_CFG_1("%s authentication null\n", buf);
                }
                else if(entry.auth_type == NETCFG_TYPE_OSPF_AUTH_CRYPTOGRAPHIC)
                {
                    APPEND_RUNNING_CFG_1("%s authentication message-digest\n", buf);
                }
            }

            /* Simple Authentication Password . */
            if (entry.config & OSPF_IF_PARAMS_AUTH_SIMPLE)
            {
                APPEND_RUNNING_CFG_2("%s authentication-key %s\n", buf, entry.auth_simple);
            }

            /* Cryptographic Authentication Key . */
            if (entry.config & OSPF_IF_PARAMS_AUTH_CRYPT)
            {
                int i;
                for(i = 0; i < 256; i++)
                {
                    if(entry.auth_crypt[i][0] != '\0')
                    {
                        APPEND_RUNNING_CFG_3("%s message-digest-key %d md5 %s\n", buf, i, entry.auth_crypt[i]);
                    }
                }
            }

            /* Interface Output Cost . */
            if (entry.config & OSPF_IF_PARAMS_OUTPUT_COST)
            {
                APPEND_RUNNING_CFG_2("%s cost %lu\n", buf, (unsigned long)entry.output_cost);
            }

            /* Hello Interval . */
            if (entry.config & OSPF_IF_PARAMS_HELLO_INTERVAL)
            {
                APPEND_RUNNING_CFG_2("%s hello-interval %lu\n", buf, (unsigned long)entry.hello_interval);
            }

            /* Router Dead Interval . */
            if (entry.config & OSPF_IF_PARAMS_DEAD_INTERVAL)
            {
                APPEND_RUNNING_CFG_2("%s dead-interval %lu\n", buf, (unsigned long)entry.dead_interval);
            }

            /* Router Priority . */
            if (entry.config & OSPF_IF_PARAMS_PRIORITY)
            {
                APPEND_RUNNING_CFG_2("%s priority %u\n", buf, entry.priority);
            }

#ifdef HAVE_RESTART
            /* Resync timeout. */
            if (entry.config & OSPF_IF_PARAMS_RESYNC_TIMEOUT)
            {
                APPEND_RUNNING_CFG_2("%s resync-timeout %lu\n", buf, (unsigned long)entry.resync_timeout);
            }
#endif /* HAVE_RESTART */

            /* MTU . */
            if (entry.config & OSPF_IF_PARAMS_MTU)
            {
                APPEND_RUNNING_CFG_2("%s mtu %u\n", buf, entry.mtu);
            }

            /* MTU ignore . */
            if (entry.config & OSPF_IF_PARAMS_MTU_IGNORE)
            {
                APPEND_RUNNING_CFG_1("%s mtu-ignore\n", buf);
            }

            /* Retransmit Interval . */
            if (entry.config & OSPF_IF_PARAMS_RETRANSMIT_INTERVAL)
            {
                APPEND_RUNNING_CFG_2("%s retransmit-interval %lu\n", buf, (unsigned long)entry.retransmit_interval);
            }

            /* Transmit Delay . */
            if (entry.config & OSPF_IF_PARAMS_TRANSMIT_DELAY)
            {
                APPEND_RUNNING_CFG_2("%s transmit-delay %lu\n", buf, (unsigned long)entry.transmit_delay);
            }

            /* Database Filter . */
            if (entry.config & OSPF_IF_PARAMS_DATABASE_FILTER)
            {
                APPEND_RUNNING_CFG_1("%s database-filter all out\n", buf);
            }

        }
   }

#endif

#if (SYS_CPNT_HSRP == TRUE)
    {
        UI32_T ifindex;
        UI8_T hsrp_id;
        UI32_T priority;
        UI32_T temp_vid;
        UI8_T auth_string[8];
        UI32_T hello_time;
        UI32_T hold_time;
        UI32_T preempt_mode;
        UI32_T preempt_delay;
        SYS_TYPE_Get_Running_Cfg_T ret;
        UI32_T iftracked;
        UI32_T virtual_ip;
        UI32_T sec_virtual_ip;
        BOOL_T is_config;

        /*need to add "standby group-id ip ip-address second" command*/
        ifindex = 0;
        hsrp_id = 0;
        hello_time = 0;
        while((ret = HSRP_PMGR_GetNextRunningHsrpGrpVirtaulIp(&ifindex,&hsrp_id,&virtual_ip,&is_config)) != SYS_TYPE_GET_RUNNING_CFG_FAIL)
        {
            VLAN_OM_ConvertFromIfindex(ifindex, &temp_vid);

            if (temp_vid == vid)
            {
                if(is_config == TRUE)
                {
                    APPEND_RUNNING_CFG_5(" standby %d ip %d.%d.%d.%d\n",hsrp_id,
                                              ((UI8_T *)(&virtual_ip))[0],
                                              ((UI8_T *)(&virtual_ip))[1],
                                              ((UI8_T *)(&virtual_ip))[2],
                                              ((UI8_T *)(&virtual_ip))[3]);
                }
            /*Willy mark off this part to prevent error provision
                else
                {
                    APPEND_RUNNING_CFG_1(" standby %d ip\n",hsrp_id);
                }
            */
                if(ret == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    sec_virtual_ip = 0;
                    while(HSRP_PMGR_GetNextRunningHsrpGrpSecVirtaulIp(&ifindex,&hsrp_id,&sec_virtual_ip) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                    {
                        APPEND_RUNNING_CFG_5(" standby %d ip %d.%d.%d.%d second\n",hsrp_id,
                                              ((UI8_T *)(&sec_virtual_ip))[0],
                                              ((UI8_T *)(&sec_virtual_ip))[1],
                                              ((UI8_T *)(&sec_virtual_ip))[2],
                                              ((UI8_T *)(&sec_virtual_ip))[3]);
                    }
                }
            }
        }

        ifindex = 0;
        hsrp_id = 0;
        memset(auth_string,0,sizeof(auth_string));
        while((ret = HSRP_PMGR_GetNextRunningHsrpGrpAuthString(&ifindex,&hsrp_id,auth_string)) != SYS_TYPE_GET_RUNNING_CFG_FAIL)
        {
            VLAN_OM_ConvertFromIfindex(ifindex, &temp_vid);

            if ((ret == SYS_TYPE_GET_RUNNING_CFG_SUCCESS) && (temp_vid == vid))
            {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                char     buf[CLI_DEF_MAX_BUFSIZE+1];

                CLI_LIB_Str_Add_Quote(auth_string,buf);
                APPEND_RUNNING_CFG_2(" standby %d authentication %s\n",hsrp_id,buf/*auth_string*/);
#else
                APPEND_RUNNING_CFG_2(" standby %d authentication %s\n",hsrp_id,auth_string);
#endif
            }
        }

        ifindex = 0;
        hsrp_id = 0;
        priority = 0;
        while((ret = HSRP_PMGR_GetNextRunningHsrpGrpPriority(&ifindex,&hsrp_id,&priority)) != SYS_TYPE_GET_RUNNING_CFG_FAIL)
        {
            VLAN_OM_ConvertFromIfindex(ifindex, &temp_vid);

            if ((ret == SYS_TYPE_GET_RUNNING_CFG_SUCCESS) && (temp_vid == vid))
            {
                APPEND_RUNNING_CFG_2(" standby %d priority %ld\n",hsrp_id,(long)priority);
            }
        }

        ifindex = 0;
        hsrp_id = 0;
        hello_time = 0;
        while(((ret = HSRP_PMGR_GetNextRunningHsrpGrpHelloTime(&ifindex,&hsrp_id,&hello_time)) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS) ||
              (ret == SYS_TYPE_GET_RUNNING_CFG_NO_CHANGE))
        {
            VLAN_OM_ConvertFromIfindex(ifindex, &temp_vid);

            if(temp_vid == vid)
            {
                if(ret == SYS_TYPE_GET_RUNNING_CFG_NO_CHANGE)
                {
                    if(HSRP_PMGR_GetRunningHsrpGrpHoldTime(ifindex,hsrp_id,&hold_time) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                    {
                        APPEND_RUNNING_CFG_3(" standby %d timers %ld %ld\n",hsrp_id,(long)hello_time,(long)hold_time);
                    }
                }
                else
                {
                    if(HSRP_PMGR_GetRunningHsrpGrpHoldTime(ifindex,hsrp_id,&hold_time) != SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                    {
                        HSRP_SYS_ADPT_GetDefaultHoldTime(&hold_time);
                    }
                    APPEND_RUNNING_CFG_3(" standby %d timers %ld %ld\n",hsrp_id,(long)hello_time,(long)hold_time);
                }
            }
        }

        ifindex = 0;
        hsrp_id = 0;
        preempt_mode = 0;
        while((ret = HSRP_PMGR_GetNextRunningHsrpGrpPreemptMode(&ifindex,&hsrp_id,&preempt_mode)) != SYS_TYPE_GET_RUNNING_CFG_FAIL)
        {
            VLAN_OM_ConvertFromIfindex(ifindex, &temp_vid);

            if ((ret == SYS_TYPE_GET_RUNNING_CFG_SUCCESS) && (temp_vid == vid))
            {
                char buff[10] = {0};
                if(HSRP_PMGR_GetRunningHsrpGrpPreemptDelay(ifindex,hsrp_id,&preempt_delay) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    SYSFUN_Sprintf(buff," delay %ld",(long)preempt_delay);
                }

                APPEND_RUNNING_CFG_3(" standby %d preempt %ld%s\n",hsrp_id,(long)preempt_mode,buff);
            }
        }

        ifindex = 0;
        hsrp_id = 0;
        iftracked = 0;
        priority = 0;
        while((ret = HSRP_PMGR_GetNextRunningHsrpIfTracked(&ifindex,&hsrp_id,&iftracked)) != SYS_TYPE_GET_RUNNING_CFG_FAIL)
        {
            VLAN_OM_ConvertFromIfindex(ifindex, &temp_vid);

            if((ret == SYS_TYPE_GET_RUNNING_CFG_SUCCESS) && (temp_vid == vid))
            {
                UI32_T track_vid;

                VLAN_OM_ConvertFromIfindex(iftracked, &track_vid);

                if((HSRP_PMGR_GetRunningHsrpIfTrackedPriority(ifindex,hsrp_id,&iftracked,&priority)) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    APPEND_RUNNING_CFG_3(" standby %d track vlan %ld %ld\n",hsrp_id,(long)track_vid,(long)priority);
                }
                else
                {
                    APPEND_RUNNING_CFG_2(" standby %d track vlan %ld\n",hsrp_id,(long)track_vid);
                }
            }
        }
    }
#endif
#if (SYS_CPNT_VRRP == TRUE)
/* vrrp */
   {
      UI32_T vid_ifIndex,ifindex;
      UI8_T  ip_addr[4] = {0};
      UI8_T  vrid;
      UI32_T auth_type = 0;
      char   authen_string[16+1] = {0};
      UI32_T priority = 0;
      UI32_T interval = 0;
      UI32_T preempt_mode = 0;
      UI32_T preempt_delay = 0;
      SYS_TYPE_Get_Running_Cfg_T ret;
      VRRP_OPER_ENTRY_T vrrp_oper_entry;

      memset(&vrrp_oper_entry, 0, sizeof(VRRP_OPER_ENTRY_T));
      VLAN_VID_CONVERTTO_IFINDEX(vid, vid_ifIndex);

      /*createAndWait*/
      while(VRRP_PMGR_GetNextVrrpOperEntry(&vrrp_oper_entry) == TRUE)
      {
         if(vrrp_oper_entry.ifindex == vid_ifIndex)
         {
            APPEND_RUNNING_CFG_1(" vrrp %d\n", vrrp_oper_entry.vrid);
         }
      }

      /* ip address */
      ifindex = vid_ifIndex;
      vrid = 0;

      while(VRRP_PMGR_GetNextRunningVrrpAssocIp(&ifindex,&vrid,ip_addr) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if(ifindex != vid_ifIndex)
             break;
         APPEND_RUNNING_CFG_5(" vrrp %d ip %d.%d.%d.%d\n",vrid,ip_addr[0],ip_addr[1],ip_addr[2],ip_addr[3]);
      }

      /* authentication */
      ifindex = vid_ifIndex;
      vrid = 0;

      while((ret = VRRP_PMGR_GetNextRunningVrrpAuthType(&ifindex,&vrid,&auth_type,(UI8_T*)authen_string)) != SYS_TYPE_GET_RUNNING_CFG_FAIL)
      {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
         char     buf[CLI_DEF_MAX_BUFSIZE+1];
#endif
         if(ifindex != vid_ifIndex)
             break;
         if (ret == SYS_TYPE_GET_RUNNING_CFG_NO_CHANGE)
            continue;
         /*if(VRRP_MGR_GetRunningVrrpAuthKey(ifindex,vrid,authen_string) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {*/
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
         CLI_LIB_Str_Add_Quote(authen_string,buf);
         APPEND_RUNNING_CFG_2(" vrrp %d authentication %s\n",vrid,buf/*authen_string*/);
#else
         APPEND_RUNNING_CFG_2(" vrrp %d authentication %s\n",vrid,authen_string);
#endif
         /*}*/
      }

      /* priority */
      ifindex = vid_ifIndex;
      vrid = 0;
      while((ret = VRRP_PMGR_GetNextRunningVrrpPriority(&ifindex,&vrid,&priority)) != SYS_TYPE_GET_RUNNING_CFG_FAIL)
      {
         if(ifindex != vid_ifIndex)
             break;
         if (ret == SYS_TYPE_GET_RUNNING_CFG_NO_CHANGE)
            continue;
         APPEND_RUNNING_CFG_2(" vrrp %d priority %lu\n",vrid,(unsigned long)priority);
      }

      /* timers advertisement */
      ifindex = vid_ifIndex;
      vrid = 0;

      while((ret = VRRP_PMGR_GetNextRunningVrrpAdverInt(&ifindex,&vrid,&interval)) != SYS_TYPE_GET_RUNNING_CFG_FAIL)
      {
         if(ifindex != vid_ifIndex)
             break;
         if (ret == SYS_TYPE_GET_RUNNING_CFG_NO_CHANGE)
            continue;
         APPEND_RUNNING_CFG_2(" vrrp %d timers advertise %lu\n",vrid,(unsigned long)interval);
      }

      /* preempt */
      ifindex = vid_ifIndex;
      vrid = 0;

      while((ret = VRRP_PMGR_GetNextRunningVrrpPreemptMode(&ifindex,&vrid,&preempt_mode)) != SYS_TYPE_GET_RUNNING_CFG_FAIL)
      {
         if(ifindex != vid_ifIndex)
             break;
         if (ret == SYS_TYPE_GET_RUNNING_CFG_NO_CHANGE)
            continue;
         if(preempt_mode == VAL_vrrpOperPreemptMode_true)
         {
            if(VRRP_PMGR_GetRunningVrrpPreemptDelay(ifindex,vrid,&preempt_delay) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
               APPEND_RUNNING_CFG_2(" vrrp %d preempt delay %lu\n",vrid,(unsigned long)preempt_delay);
            }
            else
            {
               APPEND_RUNNING_CFG_1(" vrrp %d preempt\n",vrid);
            }
        }
        else
        {
            APPEND_RUNNING_CFG_1(" no vrrp %d preempt\n",vrid);
        }
      }
   }
#endif
#if (SYS_CPNT_UDP_HELPER == TRUE)
      {
          L_INET_AddrIp_T helper;

         memset(&helper, 0, sizeof(helper));
         while(UDPHELPER_PMGR_GetNextHelper(ifindex, &helper) == UDPHELPER_TYPE_RESULT_SUCCESS )
         {
             APPEND_RUNNING_CFG_4(" ip helper-address %d.%d.%d.%d\n",
                                  helper.addr[0],helper.addr[1],
                                  helper.addr[2],helper.addr[3]);
         }
      }
#endif

#if (SYS_CPNT_PBR == TRUE)
    {
        char rmap_name[SYS_ADPT_MAX_ROUTE_MAP_NAME_LENGTH+1];

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NETCFG_POM_PBR_GetRunningBindingRouteMap(vid, rmap_name))
        {
            APPEND_RUNNING_CFG_1(" ip policy route-map %s\n", rmap_name);
        }
    }
#endif

   return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_L3_Global_To_Router_Mode_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;

    /*  static arp
     */
    {
        NETCFG_TYPE_StaticIpNetToPhysicalEntry_T   entry;
        char buf[L_INET_MAX_IPADDR_STR_LEN + 1] = {0};

        memset(&entry.ip_net_to_physical_entry,0,sizeof(entry.ip_net_to_physical_entry));
        while (NETCFG_POM_ND_GetNextStaticEntry(L_INET_ADDR_TYPE_IPV4, &entry))
        {
            if (L_INET_RETURN_SUCCESS != L_INET_InaddrToString((L_INET_Addr_T*)&entry.ip_net_to_physical_entry.ip_net_to_physical_net_address, buf, sizeof(buf)))
                continue;

            APPEND_RUNNING_CFG("%s %s %02x-%02x-%02x-%02x-%02x-%02x\n","arp", buf, L_INET_EXPAND_MAC(entry.ip_net_to_physical_entry.ip_net_to_physical_phys_address.phy_address_cctet_string));
        }
    }

#if (SYS_CPNT_RIP == TRUE)
    {
        #define PFXLEN2MASK(len) ~((1<<(32-len)) - 1)

        UI32_T vid;
        UI32_T mask;
        UI8_T addr[SYS_ADPT_IPV4_ADDR_LEN];
        UI8_T mask_addr[SYS_ADPT_IPV4_ADDR_LEN];
        NETCFG_TYPE_RIP_Instance_T              rip_entry;
        NETCFG_TYPE_RIP_Distance_T              distance_table;
        NETCFG_TYPE_RIP_Network_T               network_table;
        NETCFG_TYPE_RIP_If_T                    rip_interface_entry;
        NETCFG_TYPE_RIP_Redistribute_Table_T    redis_table;
        char  buff[CLI_DEF_MAX_BUFSIZE] = {};
        UI32_T buff_len = 0;

        memset(&redis_table, 0, sizeof(NETCFG_TYPE_RIP_Redistribute_Table_T));
        memset(&rip_interface_entry, 0, sizeof(NETCFG_TYPE_RIP_If_T));
        memset(&rip_entry, 0, sizeof(NETCFG_TYPE_RIP_Instance_T));
        memset(&distance_table, 0, sizeof(NETCFG_TYPE_RIP_Distance_T));
        memset(&network_table, 0, sizeof(NETCFG_TYPE_RIP_Network_T));

        if(NETCFG_PMGR_RIP_GetInstanceEntry(&rip_entry) == NETCFG_TYPE_OK)
        {
            APPEND_RUNNING_CFG_0("router rip\n");

            if(rip_entry.default_information == TRUE)
            {
                APPEND_RUNNING_CFG_0(" default-information originate\n");
            }

            if(rip_entry.default_metric != SYS_DFLT_RIP_DEFAULT_METRIC)
            {
                APPEND_RUNNING_CFG_1(" default-metric %ld\n",(long)rip_entry.default_metric);
            }

            if(rip_entry.distance != SYS_DFLT_RIP_DISTANCE)
            {
                APPEND_RUNNING_CFG_1(" distance %ld\n",(long)rip_entry.distance);
            }

            while(NETCFG_PMGR_RIP_GetNextDistanceTable(&distance_table) == NETCFG_TYPE_OK)
            {
                memset(addr, 0, sizeof(addr));
                memcpy(addr, &distance_table.ip_addr, sizeof(UI32_T));
                mask = L_STDLIB_Hton32(PFXLEN2MASK(distance_table.pfxlen));
                memset(mask_addr, 0, sizeof(mask_addr));
                memcpy(mask_addr, &mask, sizeof(UI32_T));
                if(distance_table.alist_name[0] != '\0')
                {
                    APPEND_RUNNING_CFG_5(" distance %ld %d.%d.%d.%d",(long)distance_table.distance,addr[0],addr[1], addr[2],addr[3]);
                    APPEND_RUNNING_CFG_5(" %d.%d.%d.%d %s\n",mask_addr[0],mask_addr[1], mask_addr[2],mask_addr[3],distance_table.alist_name);
                }
                else
                {
                    APPEND_RUNNING_CFG_5(" distance %ld %d.%d.%d.%d",(long)distance_table.distance,addr[0],addr[1], addr[2],addr[3]);
                    APPEND_RUNNING_CFG_4(" %d.%d.%d.%d\n",mask_addr[0],mask_addr[1], mask_addr[2],mask_addr[3]);
                }
            }

            if(rip_entry.pmax != SYS_ADPT_MAX_NBR_OF_RIP_ROUTE_ENTRY)
            {
                APPEND_RUNNING_CFG_1(" maximum-prefix %ld\n",(long)rip_entry.pmax);
            }

            while(NETCFG_PMGR_RIP_GetNextNeighborTable(&network_table) == NETCFG_TYPE_OK)
            {
                memset(addr, 0, sizeof(addr));
                memcpy(addr, &network_table.ip_addr, sizeof(UI32_T));
                APPEND_RUNNING_CFG_4(" neighbor %d.%d.%d.%d\n", addr[0],addr[1], addr[2],addr[3]);
            }

            while(NETCFG_PMGR_RIP_GetNextInterfaceEntry(&rip_interface_entry) == NETCFG_TYPE_OK)
            {
                if(rip_interface_entry.network_if == TRUE)
                {
                    VLAN_OM_ConvertFromIfindex(rip_interface_entry.ifindex, &vid);
                    APPEND_RUNNING_CFG_1(" network vlan %ld\n", (long)vid);
                }

                if(rip_interface_entry.pass_if == TRUE)
                {
                    VLAN_OM_ConvertFromIfindex(rip_interface_entry.ifindex, &vid);
                    APPEND_RUNNING_CFG_1(" passive-interface vlan %ld\n", (long)vid);
                }
            }

            memset(&network_table, 0, sizeof(NETCFG_TYPE_RIP_Network_T));
            while(NETCFG_PMGR_RIP_GetNextNetworkTable(&network_table) == NETCFG_TYPE_OK)
            {
                memset(addr, 0, sizeof(addr));
                memcpy(addr, &network_table.ip_addr, sizeof(UI32_T));
                mask = L_STDLIB_Hton32(PFXLEN2MASK(network_table.pfxlen));
                memset(mask_addr, 0, sizeof(mask_addr));
                memcpy(mask_addr, &mask, sizeof(UI32_T));
                APPEND_RUNNING_CFG_4(" network %d.%d.%d.%d", addr[0],addr[1], addr[2],addr[3]);
                APPEND_RUNNING_CFG_4(" %d.%d.%d.%d\n", mask_addr[0],mask_addr[1], mask_addr[2],mask_addr[3]);
            }

            redis_table.protocol = NETCFG_TYPE_RIP_Redistribute_Max;
            while(NETCFG_PMGR_RIP_GetNextRedistributeTable(&redis_table) == NETCFG_TYPE_OK)
            {
                memset(buff, 0, sizeof(buff));
                buff_len = snprintf(buff, CLI_DEF_MAX_BUFSIZE, " redistribute");

                switch(redis_table.protocol)
                {
                    case NETCFG_TYPE_RIP_Redistribute_Connected:
                        buff_len += snprintf(buff + buff_len, CLI_DEF_MAX_BUFSIZE, " connected");
                        break;
                    case NETCFG_TYPE_RIP_Redistribute_Static:
                        buff_len += snprintf(buff + buff_len, CLI_DEF_MAX_BUFSIZE, " static");
                        break;
                    case NETCFG_TYPE_RIP_Redistribute_Ospf:
                        buff_len += snprintf(buff + buff_len, CLI_DEF_MAX_BUFSIZE, " ospf");
                        break;
                    case NETCFG_TYPE_RIP_Redistribute_Bgp:
                        buff_len += snprintf(buff + buff_len, CLI_DEF_MAX_BUFSIZE, " bgp");
                        break;
                    default:
                        break;
                }
                if(redis_table.table.metric != 0)
                    buff_len += snprintf(buff + buff_len, CLI_DEF_MAX_BUFSIZE, " metric %ld", (long)redis_table.table.metric);
                if(redis_table.table.rmap_name[0] != '\0')
                    buff_len += snprintf(buff + buff_len, CLI_DEF_MAX_BUFSIZE, " route-map %s",redis_table.table.rmap_name);

                buff_len += snprintf(buff + buff_len, CLI_DEF_MAX_BUFSIZE, "\n");
                APPEND_RUNNING_CFG_0(buff);
                buff[0] = 0;
            } /* while */

            if(rip_entry.timer.update != SYS_DFLT_RIP_UPDATE_TIME ||
               rip_entry.timer.timeout!= SYS_DFLT_RIP_TIMEOUT_TIME||
               rip_entry.timer.garbage!= SYS_DFLT_RIP_GARBAGE_TIME)
            {
                APPEND_RUNNING_CFG_3(" timers basic %ld %ld %ld\n",(long)rip_entry.timer.update,
                                                                (long)rip_entry.timer.timeout,
                                                                (long)rip_entry.timer.garbage);
            }

            if(rip_entry.version != SYS_DFLT_RIP_GLOBAL_VERSION)
            {
                if(rip_entry.version == NETCFG_TYPE_RIP_GLOBAL_VERSION_1)
                {
                    APPEND_RUNNING_CFG_0(" version 1\n");
                }
                else if(rip_entry.version == NETCFG_TYPE_RIP_GLOBAL_VERSION_2)
                {
                    APPEND_RUNNING_CFG_0(" version 2\n");
                }
            }
        }
        APPEND_RUNNING_CFG_0("!\n");
    }
#endif

#if (SYS_CPNT_DHCP_SERVER == TRUE)
      {
         DHCP_TYPE_PoolConfigEntry_T pool_config;
         UI32_T i,count=0;

         UI32_T y;
         char buff[3]={0};
         char tmp_str[DHCP_MGR_CID_BUF_MAX_SIZE*2+1]={0};
         char pool_name[SYS_ADPT_DHCP_MAX_POOL_NAME_LEN+1] = {0};

         memset(&pool_config, 0, sizeof(DHCP_TYPE_PoolConfigEntry_T));

         while(DHCP_PMGR_GetNextDhcpPoolTable(pool_name, &pool_config)==DHCP_MGR_OK)
         {
            if(pool_config.pool_name[0] != 0)
            {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
               char      buf[CLI_DEF_MAX_BUFSIZE+1];

               CLI_LIB_Str_Add_Quote(pool_config.pool_name,buf);
               APPEND_RUNNING_CFG_1("ip dhcp pool %s\n",buf/*pool_config.pool_name*/);
#else
               APPEND_RUNNING_CFG_1("ip dhcp pool %s\n",pool_config.pool_name);
#endif
               if(pool_config.network_address !=0)
               {
                  APPEND_RUNNING_CFG_4(" network %d.%d.%d.%d ",((UI8_T *)(&(pool_config.network_address)))[0], ((UI8_T *)(&(pool_config.network_address)))[1], ((UI8_T *)(&(pool_config.network_address)))[2], ((UI8_T *)(&(pool_config.network_address)))[3] );
                  APPEND_RUNNING_CFG_4("%d.%d.%d.%d\n",((UI8_T *)(&(pool_config.sub_netmask)))[0], ((UI8_T *)(&(pool_config.sub_netmask)))[1], ((UI8_T *)(&(pool_config.sub_netmask)))[2], ((UI8_T *)(&(pool_config.sub_netmask)))[3] );
               }

               if(pool_config.host_address !=0)
               {
                  APPEND_RUNNING_CFG_4(" host %d.%d.%d.%d ",((UI8_T *)(&(pool_config.host_address)))[0], ((UI8_T *)(&(pool_config.host_address)))[1], ((UI8_T *)(&(pool_config.host_address)))[2], ((UI8_T *)(&(pool_config.host_address)))[3] );
                  APPEND_RUNNING_CFG_4("%d.%d.%d.%d\n",((UI8_T *)(&(pool_config.sub_netmask)))[0], ((UI8_T *)(&(pool_config.sub_netmask)))[1], ((UI8_T *)(&(pool_config.sub_netmask)))[2], ((UI8_T *)(&(pool_config.sub_netmask)))[3] );
               }

               if (strlen((char *)pool_config.options.cid.id_buf)!= 0)
               {
                  if (pool_config.options.cid.id_mode == DHCP_MGR_CID_HEX)
                  {
                     APPEND_RUNNING_CFG_0(" client-identifier hex ");

                     for (y=0; y<pool_config.options.cid.id_len;y++)
                     {
                            SYSFUN_Sprintf(buff, "%02x",pool_config.options.cid.id_buf[y]);
                            strcat(tmp_str,buff);
                     }
                     APPEND_RUNNING_CFG_1("%s\n",tmp_str);
                  }
                  else
                  {
                     APPEND_RUNNING_CFG_0(" client-identifier text ");
                     APPEND_RUNNING_CFG_1("%s\n",pool_config.options.cid.id_buf);
                  }

               }

               /* default-router */
               if(pool_config.options.default_router[0]!=0)
               {
                  APPEND_RUNNING_CFG_4(" default-router %d.%d.%d.%d",((UI8_T *)(&(pool_config.options.default_router[0])))[0], ((UI8_T *)(&(pool_config.options.default_router[0])))[1], ((UI8_T *)(&(pool_config.options.default_router[0])))[2], ((UI8_T *)(&(pool_config.options.default_router[0])))[3] );
                  for(i=1;i<SYS_ADPT_MAX_NBR_OF_DHCP_DEFAULT_ROUTER;i++)
                  {
                     if(pool_config.options.default_router[i]!=0)
                     {
                        APPEND_RUNNING_CFG_4(" %d.%d.%d.%d",((UI8_T *)(&(pool_config.options.default_router[i])))[0], ((UI8_T *)(&(pool_config.options.default_router[i])))[1], ((UI8_T *)(&(pool_config.options.default_router[i])))[2], ((UI8_T *)(&(pool_config.options.default_router[i])))[3] );
                     }
                  }
                  APPEND_RUNNING_CFG_0("\n");
               }

               if(pool_config.options.dns_server[0]!=0)
               {
                  APPEND_RUNNING_CFG_4(" dns-server %d.%d.%d.%d",((UI8_T *)(&(pool_config.options.dns_server[0])))[0], ((UI8_T *)(&(pool_config.options.dns_server[0])))[1], ((UI8_T *)(&(pool_config.options.dns_server[0])))[2], ((UI8_T *)(&(pool_config.options.dns_server[0])))[3] );
                  for(i=1;i<SYS_ADPT_MAX_NBR_OF_DHCP_DNS_SERVER;i++)
                  {
                     if(pool_config.options.dns_server[i]!=0)
                     {
                        APPEND_RUNNING_CFG_4(" %d.%d.%d.%d",((UI8_T *)(&(pool_config.options.dns_server[i])))[0], ((UI8_T *)(&(pool_config.options.dns_server[i])))[1], ((UI8_T *)(&(pool_config.options.dns_server[i])))[2], ((UI8_T *)(&(pool_config.options.dns_server[i])))[3] );
                     }
                  }
                  APPEND_RUNNING_CFG_0("\n");
               }

               if(pool_config.options.next_server!=0)
               {
                  APPEND_RUNNING_CFG_4(" next-server %d.%d.%d.%d\n",((UI8_T *)(&(pool_config.options.next_server)))[0], ((UI8_T *)(&(pool_config.options.next_server)))[1], ((UI8_T *)(&(pool_config.options.next_server)))[2], ((UI8_T *)(&(pool_config.options.next_server)))[3] );
               }

               if(pool_config.options.netbios_name_server[0]!=0)
               {
                  APPEND_RUNNING_CFG_4(" netbios-name-server %d.%d.%d.%d",((UI8_T *)(&(pool_config.options.netbios_name_server[0])))[0], ((UI8_T *)(&(pool_config.options.netbios_name_server[0])))[1], ((UI8_T *)(&(pool_config.options.netbios_name_server[0])))[2], ((UI8_T *)(&(pool_config.options.netbios_name_server[0])))[3] );
                  for(i=1;i<SYS_ADPT_MAX_NBR_OF_DHCP_NETBIOS_NAME_SERVER;i++)
                  {
                     if(pool_config.options.netbios_name_server[i]!=0)
                     {
                        APPEND_RUNNING_CFG_4(" %d.%d.%d.%d",((UI8_T *)(&(pool_config.options.netbios_name_server[i])))[0], ((UI8_T *)(&(pool_config.options.netbios_name_server[i])))[1], ((UI8_T *)(&(pool_config.options.netbios_name_server[i])))[2], ((UI8_T *)(&(pool_config.options.netbios_name_server[i])))[3] );
                     }
                  }
                  APPEND_RUNNING_CFG_0("\n");
               }

               if(pool_config.options.netbios_node_type!=0)
               {
                  if(pool_config.options.netbios_node_type==DHCP_MGR_NETBIOS_NODE_TYPE_B_NODE)
                  {
                     APPEND_RUNNING_CFG_0(" netbios-node-type broadcast\n");
                  }
                  else if(pool_config.options.netbios_node_type==DHCP_MGR_NETBIOS_NODE_TYPE_H_NODE)
                  {
                     APPEND_RUNNING_CFG_0(" netbios-node-type hybrid\n");
                  }
                  else if(pool_config.options.netbios_node_type==DHCP_MGR_NETBIOS_NODE_TYPE_M_NODE)
                  {
                     APPEND_RUNNING_CFG_0(" netbios-node-type mixed\n");
                  }
                  else if(pool_config.options.netbios_node_type==DHCP_MGR_NETBIOS_NODE_TYPE_P_NODE)
                  {
                     APPEND_RUNNING_CFG_0(" netbios-node-type peer-to-peer\n");
                  }
               }

               if(pool_config.options.domain_name[0] != 0)
               {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                  char     buf[CLI_DEF_MAX_BUFSIZE+1];

                  CLI_LIB_Str_Add_Quote(pool_config.options.domain_name,buf);
                  APPEND_RUNNING_CFG_1(" domain-name %s\n",buf/*pool_config.options.domain_name*/);
#else
                  APPEND_RUNNING_CFG_1(" domain-name %s\n",pool_config.options.domain_name);
#endif
               }

               if(pool_config.options.bootfile[0] != 0)
               {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                  char     buf[CLI_DEF_MAX_BUFSIZE+1];

                  CLI_LIB_Str_Add_Quote(pool_config.options.bootfile,buf);
                  APPEND_RUNNING_CFG_1(" bootfile %s\n",buf/*pool_config.options.bootfile*/);
#else
                  APPEND_RUNNING_CFG_1(" bootfile %s\n",pool_config.options.bootfile);
#endif
               }

               if(pool_config.options.lease_time != 0)
               {
                  if(pool_config.options.lease_time == DHCP_MGR_INFINITE_LEASE_TIME)
                  {
                     APPEND_RUNNING_CFG_0(" lease infinite\n");
                  }
                  else
                  {
                        UI32_T day=0;
                        UI32_T hour=0;
                        UI32_T min=0;

                        day = pool_config.options.lease_time/DHCP_TYPE_ONE_DAY_SEC;
                        hour = (pool_config.options.lease_time%DHCP_TYPE_ONE_DAY_SEC)/DHCP_TYPE_ONE_HOUR_SEC;
                        min = ((pool_config.options.lease_time%DHCP_TYPE_ONE_DAY_SEC)%DHCP_TYPE_ONE_HOUR_SEC)/DHCP_TYPE_ONE_MIN_SEC;
                        APPEND_RUNNING_CFG_3(" lease %lu %lu %lu\n",(unsigned long)day,(unsigned long)hour,(unsigned long)min);

                  }
               }

               count=0;
               for(i=0;i<6;i++)
               {
                  if(pool_config.hardware_address.haddr[i]==0)
                  {
                     count++;
                  }
               }

               if(count !=6)
               {
                  APPEND_RUNNING_CFG_4(" hardware-address %02x-%02x-%02x-%02x",
              pool_config.hardware_address.haddr[0],
              pool_config.hardware_address.haddr[1],
              pool_config.hardware_address.haddr[2],
              pool_config.hardware_address.haddr[3]);

              APPEND_RUNNING_CFG_2("-%02x-%02x",
              pool_config.hardware_address.haddr[4],
              pool_config.hardware_address.haddr[5]);

                  if(pool_config.hardware_address.htype !=0)
                  {
                     if(pool_config.hardware_address.htype==DHCP_MGR_HTYPE_ETHER)
                     {
                        APPEND_RUNNING_CFG_0(" ethernet");
                     }
                     else if(pool_config.hardware_address.htype==DHCP_MGR_HTYPE_IEEE802)
                     {
                        APPEND_RUNNING_CFG_0(" ieee802");
                     }
                     else if(pool_config.hardware_address.htype==DHCP_MGR_HTYPE_FDDI)
                     {
                        APPEND_RUNNING_CFG_0(" fddi");
                     }
                  }
                  APPEND_RUNNING_CFG_0("\n");
               }
            }
            APPEND_RUNNING_CFG_0("!\n");
         }


         {
            UI32_T low_address=0, high_address=0;
            while(DHCP_PMGR_GetNextExcludedIp(&low_address, &high_address)==DHCP_MGR_OK)
            {
               if(low_address==high_address)
               {
                  APPEND_RUNNING_CFG_4(" ip dhcp excluded-address %d.%d.%d.%d\n",((UI8_T *)(&(low_address)))[0], ((UI8_T *)(&(low_address)))[1], ((UI8_T *)(&(low_address)))[2], ((UI8_T *)(&(low_address)))[3] );
               }
               else
               {
                  APPEND_RUNNING_CFG_4(" ip dhcp excluded-address %d.%d.%d.%d",((UI8_T *)(&(low_address)))[0], ((UI8_T *)(&(low_address)))[1], ((UI8_T *)(&(low_address)))[2], ((UI8_T *)(&(low_address)))[3] );
                  APPEND_RUNNING_CFG_4(" %d.%d.%d.%d\n",((UI8_T *)(&(high_address)))[0], ((UI8_T *)(&(high_address)))[1], ((UI8_T *)(&(high_address)))[2], ((UI8_T *)(&(high_address)))[3] );
               }
            }
         }

         if(DHCP_PMGR_GetDhcpServerServiceStatus()== TRUE)
         {
            APPEND_RUNNING_CFG_0(" service dhcp\n");
         }

         //APPEND_RUNNING_CFG_0("!\n");
      }
#endif

#if (SYS_CPNT_OSPF6 == TRUE)
{
    #define PFXLEN2MASK(len) ~((1<<(32-len)) - 1)
    #define CHECK_FLAG(V,F)      ((V) & (F))
    UI32_T vr_id = SYS_DFLT_VR_ID;
    UI32_T ifindex = 0, vid = 0;
    OSPF6_MGR_OSPF_ENTRY_T   instance_entry;
    OSPF6_TYPE_Vlink_T               vlink_entry;
    UI8_T addr[SYS_ADPT_IPV4_ADDR_LEN];
    UI8_T addr2[SYS_ADPT_IPV4_ADDR_LEN];
    char  temp_buff[CLI_DEF_MAX_BUFSIZE] = {0};
    UI32_T buff_len = 0;
    OSPF6_TYPE_Area_Range_T range;
    char  ip6_address[L_INET_MAX_IP6ADDR_STR_LEN+1];
    OSPF6_TYPE_Area_T area;
    OSPF6_TYPE_Multi_Proc_Redist_T redist_entry;

    memset(&instance_entry, 0, sizeof(instance_entry));
    instance_entry.is_first = TRUE;
    while(OSPF6_PMGR_Process_GetNext(&instance_entry) == OSPF6_TYPE_RESULT_SUCCESS)
    {
        if(instance_entry.tag[0] == 0)
        {
            APPEND_RUNNING_CFG_0("router ipv6 ospf\n");
        }
        else
        {
            APPEND_RUNNING_CFG_1("router ipv6 ospf %s\n",instance_entry.tag);
        }
        /* Router ID print. */
        {
            memset(addr, 0, sizeof(addr));
            memset(temp_buff, 0, sizeof(temp_buff));
            memcpy(addr, &instance_entry.router_id.s_addr, sizeof(UI32_T));
            sprintf(temp_buff,"%d.%d.%d.%d", addr[0],addr[1], addr[2], addr[3]);
            APPEND_RUNNING_CFG_1(" router-id %s\n",temp_buff);
        }

        /* SPF timers print. */
        if (instance_entry.spf_delay != SYS_DFLT_OSPF_SPF_DELAY_DEFAULT ||
            instance_entry.spf_holdtime != SYS_DFLT_OSPF_SPF_HOLDTIME_DEFAULT)
        {
            APPEND_RUNNING_CFG_2(" timers spf %ld %ld\n",(long)instance_entry.spf_delay,(long)instance_entry.spf_holdtime);
        }

        /* Passive-interface print. */
        while(OSPF6_PMGR_PassiveIfGetNext(vr_id, instance_entry.tag, &ifindex) == OSPF6_TYPE_RESULT_SUCCESS)
        {
            VLAN_OM_ConvertFromIfindex(ifindex, &vid);
            APPEND_RUNNING_CFG_1(" passive-interface vlan %ld\n", (long)vid);
        }
        /* To-do: passive-interface vlan <1-4096> X:X:X:X::X */

        /* Virtual-Link. */
        memset(&vlink_entry, 0 ,sizeof(OSPF6_TYPE_Vlink_T));
        vlink_entry.vr_id = vr_id;
        strncpy(vlink_entry.tag, instance_entry.tag, strlen(instance_entry.tag));
        while(OSPF6_PMGR_VirtualLink_GetNext(&vlink_entry) == OSPF6_TYPE_RESULT_SUCCESS)
        {
            memset(temp_buff, 0, sizeof(temp_buff));
            buff_len = 0;
            memset(addr, 0, sizeof(addr));
            memset(addr2, 0, sizeof(addr));
            memcpy(addr, &(vlink_entry.peer_id.s_addr), sizeof(UI32_T));
            memcpy(addr2, &(vlink_entry.area_id.s_addr), sizeof(UI32_T));
            buff_len += sprintf(temp_buff," area %d.%d.%d.%d virtual-link %d.%d.%d.%d ",
                                           addr2[0],addr2[1],addr2[2],addr2[3],
                                           addr[0],addr[1],addr[2],addr[3]);

            APPEND_RUNNING_CFG_1("%s\n", temp_buff);
        }

        /*default-metric*/
        if (instance_entry.default_metric != 20 )//OSPF6_DEFAULT_DEFAULT_EXTERNAL_METRIC)
        {
            APPEND_RUNNING_CFG_1(" default-metric %ld\n", (long)instance_entry.default_metric);
        }
        /*max concurrent dd */
        if (instance_entry.max_dd != 5)//OSPF6_MAX_CONCURRENT_DD_DEFAULT)
        {
            APPEND_RUNNING_CFG_1(" max-concurrent-dd %d\n", instance_entry.max_dd);
        }
        /* area range */
        memset(&range, 0, sizeof(OSPF6_TYPE_Area_Range_T));
        strncpy(range.tag, instance_entry.tag, strlen(instance_entry.tag));
        range.is_first = TRUE;
        /* display all area */
        memset(&area, 0, sizeof(OSPF6_TYPE_Area_T));
        strncpy(area.tag, instance_entry.tag, strlen(instance_entry.tag));
        area.first_flag = TRUE;
        memset(temp_buff, 0, sizeof(temp_buff));
        buff_len = 0;
        memset(&redist_entry, 0, sizeof(redist_entry));
        strncpy(redist_entry.tag, instance_entry.tag, strlen(instance_entry.tag));
        while( OSPF6_PMGR_RedistributeEntry_GetNext(&redist_entry) == OSPF6_TYPE_RESULT_SUCCESS )
        {
            memset(temp_buff, 0, sizeof(temp_buff));
            buff_len = 0;
            switch ( redist_entry.proto )
            {
                case OSPF6_TYPE_REDISTRIBUTE_CONNECTED:
                    buff_len += sprintf(temp_buff," redistribute connected");
                    break;
                case OSPF6_TYPE_REDISTRIBUTE_STATIC:
                    buff_len += sprintf(temp_buff," redistribute static");
                    break;
                case OSPF6_TYPE_REDISTRIBUTE_RIPNG:
                    buff_len += sprintf(temp_buff," redistribute ripng");
                    break;
            }
            APPEND_RUNNING_CFG_0(temp_buff);
            if(redist_entry.metric_type)
            {
                APPEND_RUNNING_CFG_1(" metric-type %lu", (unsigned long)redist_entry.metric_type);
            }
            if(redist_entry.metric)
            {
                APPEND_RUNNING_CFG_1(" metric %lu", (unsigned long)redist_entry.metric);
            }

            APPEND_RUNNING_CFG_0("\r\n");
            redist_entry.metric = 0;
            redist_entry.metric_type = 0;
        }
        APPEND_RUNNING_CFG_0("!\n");
    }
}
#endif

#if (SYS_CPNT_OSPF == TRUE)
{
      #define PFXLEN2MASK(len) ~((1<<(32-len)) - 1)
      #define CHECK_FLAG(V,F)      ((V) & (F))
      UI32_T proc_id = 0xffffffff;
      UI32_T vr_id = SYS_DFLT_VR_ID;
      UI32_T vrf_id = SYS_DFLT_VRF_ID;
      OSPF_TYPE_MultiProcessSystem_T   instance_entry;
      OSPF_TYPE_Passive_If_T           pass_if_entry;
      OSPF_TYPE_Network_Area_T         network_entry;
      OSPF_TYPE_Area_Para_T            area_entry;
      OSPF_TYPE_Area_Range_T           range_entry;
      OSPF_TYPE_Vlink_T                vlink_entry;
      UI8_T addr[SYS_ADPT_IPV4_ADDR_LEN];
      char  temp_buff[CLI_DEF_MAX_BUFSIZE] = {0};
      UI32_T buff_len = 0;
      UI32_T mask;
      int ret;
      OSPF_TYPE_Multi_Proc_Summary_Addr_T summary_addr_entry;
      UI32_T refbw;
      UI32_T vid = 0;
      struct pal_in4_addr netmask;
      OSPF_TYPE_Multi_Proc_Redist_T config;
      char  buff[CLI_DEF_MAX_BUFSIZE] = {0};
      char  tmpBuf[50] = {0};
      char *ospf_auth_type_str[] =
      {
        " null",
        "",
        " message-digest",
      };

    while(OSPF_PMGR_GetNextProcessStatus(vr_id, &proc_id) == OSPF_TYPE_RESULT_SUCCESS)
    {
        if(proc_id == 0)
        {
            APPEND_RUNNING_CFG_0("router ospf\n");
        }
        else
        {
            APPEND_RUNNING_CFG_1("router ospf %ld\n",(long)proc_id);
        }
        memset(&instance_entry, 0, sizeof(OSPF_TYPE_MultiProcessSystem_T));
        instance_entry.proc_id = proc_id;
        if(OSPF_PMGR_GetMultiProcessSystemEntry(vr_id, vrf_id, &instance_entry)!= OSPF_TYPE_RESULT_SUCCESS)
        {
            /*printf("&&&&&&can not get instance parameters in ospf!\n");*/
        }
        /* Router ID print. */
        if (instance_entry.routerId_type == OSPF_ROUTER_ID_TYPE_MANUAL)
        {
            memset(addr, 0, sizeof(addr));
            memset(temp_buff, 0, sizeof(temp_buff));
            memcpy(addr, &instance_entry.routerId.s_addr, sizeof(UI32_T));
            sprintf(temp_buff,"%d.%d.%d.%d", addr[0],addr[1], addr[2], addr[3]);
            APPEND_RUNNING_CFG_1(" router-id %s\n",temp_buff);
        }

        /* RFC1583 compatibility flag print. */
        if (instance_entry.rfc1583CompatibleState == OSPF_RFC1583_COMPATIBLE_STATE_ENABLED)
        {
            APPEND_RUNNING_CFG_0(" compatible rfc1583\n");
        }


        /* SPF timers print. */
        if (instance_entry.spfDelayTime != SYS_DFLT_OSPF_SPF_DELAY_DEFAULT ||
            instance_entry.spfHoldTime != SYS_DFLT_OSPF_SPF_HOLDTIME_DEFAULT)
        {
            APPEND_RUNNING_CFG_2(" timers spf %ld %ld\n",(long)instance_entry.spfDelayTime,(long)instance_entry.spfHoldTime);
        }

        /* Passive-interface print. */
        memset(&pass_if_entry, 0, sizeof(OSPF_TYPE_Passive_If_T));
        pass_if_entry.vr_id = vr_id;
        pass_if_entry.proc_id = proc_id;
        while(OSPF_PMGR_GetNextPassIfTable(&pass_if_entry) == OSPF_TYPE_RESULT_SUCCESS)
        {
            VLAN_OM_ConvertFromIfindex(pass_if_entry.ifindex, &vid);
            if(pass_if_entry.addr == 0)
            {
                APPEND_RUNNING_CFG_1(" passive-interface vlan %ld\n", (long)vid);
            }
            else
            {
                memset(addr, 0, sizeof(addr));
                memset(temp_buff, 0, sizeof(temp_buff));
                memcpy(addr, &pass_if_entry.addr, sizeof(UI32_T));
                sprintf(temp_buff,"%d.%d.%d.%d", addr[0],addr[1], addr[2], addr[3]);
                APPEND_RUNNING_CFG_2(" passive-interface vlan %ld %s\n", (long)vid, temp_buff);
            }
        }

        /* Area config. */
        memset(&area_entry, 0, sizeof(OSPF_TYPE_Area_Para_T));
        area_entry.vr_id = vr_id;
        area_entry.proc_id = proc_id;
        area_entry.first_flag = TRUE;
        while(OSPF_PMGR_GetNextAreaPara(&area_entry) == OSPF_TYPE_RESULT_SUCCESS)
        {
            /*stub*/
            if (area_entry.area_type == OSPF_TYPE_AREA_STUB)
            {
                if(area_entry.stub_no_summary_flag)
                {
                    APPEND_RUNNING_CFG_1(" area %s stub no-summary\n",area_entry.area_id_str);
                }
                else
                {
                    APPEND_RUNNING_CFG_1(" area %s stub\n",area_entry.area_id_str);
                }
            }

            /*nssa*/
            if (area_entry.area_type == OSPF_TYPE_AREA_NSSA)
            {
                APPEND_RUNNING_CFG_1(" area %s nssa ",area_entry.area_id_str);
                if (CHECK_FLAG (area_entry.nssa.config, OSPF_TYPE_AREA_NSSA_CONF_TRANSLATOR_ROLE))
                {
                    if(area_entry.nssa.translator_role == OSPF_TYPE_TRANSLATOR_ALAWAYS)
                    {
                        APPEND_RUNNING_CFG_0("translator-role always");
                    }
                    else if(area_entry.nssa.translator_role == OSPF_TYPE_TRANSLATOR_NEVER)
                    {
                        APPEND_RUNNING_CFG_0("translator-role never");
                    }
                }

                if (CHECK_FLAG (area_entry.nssa.config, OSPF_TYPE_AREA_NSSA_CONF_NO_REDISTRIBUTION))
                {
                    APPEND_RUNNING_CFG_0(" no-redistribution");
                }

                if (area_entry.stub_no_summary_flag)
                {
                    APPEND_RUNNING_CFG_0(" no-summary");
                }

                if (CHECK_FLAG (area_entry.nssa.config, OSPF_TYPE_AREA_NSSA_CONF_DFLT_INFORMATION))
                {
                    APPEND_RUNNING_CFG_0(" default-information-originate");
                    if (CHECK_FLAG (area_entry.nssa.config, OSPF_TYPE_AREA_NSSA_CONF_DFLT_INFORMATION_METRIC))
                    {
                        APPEND_RUNNING_CFG_1(" metric %ld",(long)area_entry.nssa.metric);
                    }
                    if (CHECK_FLAG (area_entry.nssa.config, OSPF_TYPE_AREA_NSSA_CONF_DFLT_INFORMATION_METRIC_TYPE))
                    {
                        APPEND_RUNNING_CFG_1(" metric-type %d",area_entry.nssa.metric_type);
                    }
                }
                APPEND_RUNNING_CFG_0("\n");
            }

            /*authentication*/
            if(area_entry.auth_type)
            {
                switch(area_entry.auth_type)
                {
                    case OSPF_TYPE_AUTH_SIMPLE:
                        APPEND_RUNNING_CFG_1(" area %s authentication\n",area_entry.area_id_str);
                        break;
                    case OSPF_TYPE_AUTH_CRYPTOGRAPHIC:
                        APPEND_RUNNING_CFG_1(" area %s authentication message-digest\n",area_entry.area_id_str);
                        break;
                    default:
                        break;
                }
            }

            /*default-cost*/
            if(area_entry.default_cost_flag)
            {
                APPEND_RUNNING_CFG_2(" area %s default-cost %ld\n",area_entry.area_id_str,(long)area_entry.default_cost);
            }

            /*range*/
            memset(&range_entry, 0, sizeof(OSPF_TYPE_Area_Range_T));
            range_entry.indexlen = 13;
            range_entry.vr_id = vr_id;
            range_entry.proc_id = proc_id;
            range_entry.area_id = area_entry.area_id;
            while(OSPF_PMGR_GetNextAreaRangeTable(&range_entry) == OSPF_TYPE_RESULT_SUCCESS)
            {
                if((range_entry.vr_id == vr_id)&&(range_entry.proc_id == proc_id) &&(range_entry.area_id == area_entry.area_id))
                {
                    memset(temp_buff, 0, sizeof(temp_buff));
                    buff_len = 0;
                    buff_len += sprintf(temp_buff," area %s range ",area_entry.area_id_str);

                    memset(addr, 0, sizeof(addr));
                    memcpy(addr, &(range_entry.range_addr), sizeof(UI32_T));
                    buff_len += sprintf(temp_buff + buff_len,"%d.%d.%d.%d ", addr[0],addr[1], addr[2], addr[3]);

                    memset(addr, 0, sizeof(addr));
                    memcpy(addr, &(range_entry.range_mask), sizeof(UI32_T));
                    buff_len += sprintf(temp_buff + buff_len,"%d.%d.%d.%d ", addr[0],addr[1], addr[2], addr[3]);

                    if (!CHECK_FLAG (range_entry.flags, OSPF_AREA_RANGE_ADVERTISE))
                    {
                        buff_len += sprintf(temp_buff + buff_len,"not-advertise");
                    }
                    APPEND_RUNNING_CFG_1("%s\n",temp_buff);
                }
                else
                {
                    break;
                }
            }
        }

        /* Virtual-Link. */
        memset(&vlink_entry, 0 ,sizeof(OSPF_TYPE_Vlink_T));
        vlink_entry.vr_id = vr_id;
        vlink_entry.proc_id = proc_id;
        while(OSPF_PMGR_GetNextVirtualLinkEntry(&vlink_entry) == OSPF_TYPE_RESULT_SUCCESS)
        {
            memset(temp_buff, 0, sizeof(temp_buff));
            buff_len = 0;
            memset(addr, 0, sizeof(addr));
            memcpy(addr, &(vlink_entry.peer_id.s_addr), sizeof(UI32_T));
            buff_len += sprintf(temp_buff," area %s virtual-link %d.%d.%d.%d ",vlink_entry.area_id_str,addr[0],addr[1],addr[2],addr[3]);

            if (CHECK_FLAG(vlink_entry.config, OSPF_IF_PARAM_HELLO_INTERVAL))
            {
                buff_len += sprintf(temp_buff + buff_len," hello-interval %ld", (long)vlink_entry.hello_interval);
            }

            if (CHECK_FLAG(vlink_entry.config, OSPF_IF_PARAM_DEAD_INTERVAL))
            {
                buff_len += sprintf(temp_buff + buff_len," dead-interval %ld", (long)vlink_entry.dead_interval);
            }

            if (CHECK_FLAG(vlink_entry.config, OSPF_IF_PARAM_RETRANSMIT_INTERVAL))
            {
                buff_len += sprintf(temp_buff + buff_len," retransmit-interval %ld", (long)vlink_entry.retransmit_interval);
            }

            if (CHECK_FLAG(vlink_entry.config, OSPF_IF_PARAM_TRANSMIT_DELAY))
            {
                buff_len += sprintf(temp_buff + buff_len," transmit-delay %ld", (long)vlink_entry.transmit_delay);
            }

            if (CHECK_FLAG(vlink_entry.config, OSPF_IF_PARAM_AUTH_TYPE))
            {
                buff_len += sprintf(temp_buff + buff_len," authentication %s", ospf_auth_type_str[vlink_entry.auth_type]);
            }

            if (CHECK_FLAG(vlink_entry.config, OSPF_IF_PARAM_AUTH_SIMPLE))
            {
                buff_len += sprintf(temp_buff + buff_len," authentication-key %s", vlink_entry.auth_simple);
            }
            buff_len += sprintf(temp_buff + buff_len,"\n");
            APPEND_RUNNING_CFG_1("%s",temp_buff);

            if (CHECK_FLAG(vlink_entry.config, OSPF_IF_PARAM_AUTH_CRYPT))
            {
                int i;
                for(i = 1; i < 256; i++)
                {
                    if(vlink_entry.auth_crypt[i][0] != '\0')
                    {
                        memset(temp_buff, 0, sizeof(temp_buff));
                        buff_len = 0;
                        memset(addr, 0, sizeof(addr));
                        memcpy(addr, &(vlink_entry.peer_id.s_addr), sizeof(UI32_T));
                        buff_len += sprintf(temp_buff," area %s virtual-link %d.%d.%d.%d ",vlink_entry.area_id_str,addr[0],addr[1],addr[2],addr[3]);
                        buff_len += sprintf(temp_buff + buff_len,"message-digest-key %d md5 %s\n", i,vlink_entry.auth_crypt[i]);
                        APPEND_RUNNING_CFG_1("%s",temp_buff);
                    }
                }
            }
        }

        /*default-metric*/
        if (instance_entry.defaultMetric != -1)
        {
            APPEND_RUNNING_CFG_1(" default-metric %ld\n", (long)instance_entry.defaultMetric);
        }
        memset(&summary_addr_entry, 0, sizeof(OSPF_TYPE_Multi_Proc_Summary_Addr_T));
        summary_addr_entry.proc_id = proc_id;
        summary_addr_entry.config_type = OSPF_TYPE_SUMMARY_CONFIG_TYPE_CLI;
        summary_addr_entry.indexlen = 0;
        while(OSPF_PMGR_GetNextMultiProcSummaryAddrEntry(vr_id, SYS_DFLT_VRF_ID, &summary_addr_entry) == OSPF_TYPE_RESULT_SUCCESS)
        {
            if(summary_addr_entry.proc_id == proc_id)
            {
                memset(buff, 0, sizeof(buff));
                memset(tmpBuf, 0, sizeof(tmpBuf));
                L_PREFIX_MaskLen2IPv4(summary_addr_entry.summary_pfxlen, &netmask);
                HexAddrToStr(summary_addr_entry.summary_address, tmpBuf, FALSE);
                sprintf(buff, " summary-address %s ", tmpBuf);
                HexAddrToStr(netmask.s_addr, tmpBuf, FALSE);
                strcat(buff, tmpBuf);
                strcat(buff, "\r\n");
                APPEND_RUNNING_CFG_0(buff);
                summary_addr_entry.indexlen = 8;
            }
            else
            {
                break;
            }
        }
        memset(buff, 0, sizeof(buff));
        memset(tmpBuf, 0, sizeof(tmpBuf));
        ret = OSPF_PMGR_GetAutoCost(0, proc_id, &refbw);
        if ( ret == NETCFG_TYPE_OK && refbw != 100 )
        {
            APPEND_RUNNING_CFG_1(" auto-cost reference-bandwidth %ld\r\n", (long)refbw);
        }
        config.vr_id = 0;
        config.proc_id = proc_id;
        config.proto = OSPF_TYPE_REDISTRIBUTE_CONNECTED;
        ret = OSPF_PMGR_GetMultiProcRedistEntry(SYS_DFLT_VR_ID, SYS_DFLT_VRF_ID, &config);
        if ( ret == NETCFG_TYPE_OK )
        {
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_ENABLE))
                 sprintf(buff, " redistribute connected");
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_METRIC))
             {
                 sprintf(tmpBuf, " metric %ld", (long)config.metric);
                 strcat(buff, tmpBuf);
             }
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_METRIC_TYPE))
                 strcat(buff, " metric-type 1");
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_TAG))
             {
                 sprintf(tmpBuf, " tag %lu", (unsigned long)config.tag);
                 strcat(buff, tmpBuf);
             }
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_ROUTE_MAP))
             {
                 sprintf(tmpBuf, " route-map %s", config.route_map);
                 strcat(buff, tmpBuf);
             }
             strcat(buff, "\r\n");
             APPEND_RUNNING_CFG_0(buff);
             buff[0] = 0;
        }
        config.proto = OSPF_TYPE_REDISTRIBUTE_RIP;
        ret = OSPF_PMGR_GetMultiProcRedistEntry(SYS_DFLT_VR_ID, SYS_DFLT_VRF_ID, &config);
        if ( ret == NETCFG_TYPE_OK )
        {
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_ENABLE))
                 sprintf(buff, " redistribute rip");
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_METRIC))
             {
                 sprintf(tmpBuf, " metric %ld", (long)config.metric);
                 strcat(buff, tmpBuf);
             }
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_METRIC_TYPE))
                 strcat(buff, " metric-type 1");
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_TAG))
             {
                 sprintf(tmpBuf, " tag %lu", (unsigned long)config.tag);
                 strcat(buff, tmpBuf);
             }
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_ROUTE_MAP))
             {
                 sprintf(tmpBuf, " route-map %s", config.route_map);
                 strcat(buff, tmpBuf);
             }
             strcat(buff, "\r\n");
             APPEND_RUNNING_CFG_0(buff);
             buff[0] = 0;
        }
        config.proto = OSPF_TYPE_REDISTRIBUTE_STATIC;
        ret = OSPF_PMGR_GetMultiProcRedistEntry(SYS_DFLT_VR_ID, SYS_DFLT_VRF_ID, &config);
        if ( ret == NETCFG_TYPE_OK )
        {
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_ENABLE))
                 sprintf(buff, " redistribute static");
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_METRIC))
             {
                 sprintf(tmpBuf, " metric %ld", (long)config.metric);
                 strcat(buff, tmpBuf);
             }
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_METRIC_TYPE))
                 strcat(buff, " metric-type 1");
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_TAG))
             {
                 sprintf(tmpBuf, " tag %lu", (unsigned long)config.tag);
                 strcat(buff, tmpBuf);
             }
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_ROUTE_MAP))
             {
                 sprintf(tmpBuf, " route-map %s", config.route_map);
                 strcat(buff, tmpBuf);
             }
             strcat(buff, "\r\n");
             APPEND_RUNNING_CFG_0(buff);
             buff[0] = 0;
        }

        config.proto = OSPF_TYPE_REDISTRIBUTE_BGP;
        ret = OSPF_PMGR_GetMultiProcRedistEntry(SYS_DFLT_VR_ID, SYS_DFLT_VRF_ID, &config);
        if ( ret == NETCFG_TYPE_OK )
        {
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_ENABLE))
                 sprintf(buff, " redistribute bgp");
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_METRIC))
             {
                 sprintf(tmpBuf, " metric %ld", (long)config.metric);
                 strcat(buff, tmpBuf);
             }
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_METRIC_TYPE))
                 strcat(buff, " metric-type 1");
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_TAG))
             {
                 sprintf(tmpBuf, " tag %lu", (unsigned long)config.tag);
                 strcat(buff, tmpBuf);
             }
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_ROUTE_MAP))
             {
                 sprintf(tmpBuf, " route-map %s", config.route_map);
                 strcat(buff, tmpBuf);
             }
             strcat(buff, "\r\n");
             APPEND_RUNNING_CFG_0(buff);
             buff[0] = 0;
        }

        config.proto = OSPF_TYPE_REDISTRIBUTE_DEFAULT;
        ret = OSPF_PMGR_GetMultiProcRedistEntry(SYS_DFLT_VR_ID, SYS_DFLT_VRF_ID, &config);
        if ( ret == NETCFG_TYPE_OK )
        {
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_ENABLE))
                 sprintf(buff, " default-information originate");
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_METRIC))
             {
                 sprintf(tmpBuf, " metric %ld", (long)config.metric);
                 strcat(buff, tmpBuf);
             }
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_METRIC_TYPE))
                 strcat(buff, " metric-type 1");
             if (CHECK_FLAG(config.flags, NETCFG_TYPE_OSPF_REDIST_ROUTE_MAP))
             {
                 sprintf(tmpBuf, " route-map %s", config.route_map);
                 strcat(buff, tmpBuf);
             }
             if (NETCFG_TYPE_OSPF_DEFAULT_ORIGINATE_ALWAYS == config.origin_type)
                 strcat(buff, " always");
             strcat(buff, "\r\n");
             APPEND_RUNNING_CFG_0(buff);
             buff[0] = 0;
        }

        APPEND_RUNNING_CFG_0("!\n");
    }
}
#endif

#if 0 //TODO(SYS_CPNT_BGP == TRUE)
{
    char  buff[CLI_DEF_MAX_BUFSIZE] = {0};
    BGP_OM_RunCfgInstance_T  bgp_instance;
    BGP_OM_AggregateAddr_T   aggregate_addr;
    BGP_OM_Distance_T        distance;
    BGP_OM_AfiSafiNeighbor_T neighbor, config, *config_p = NULL, *group_p = NULL;
    BGP_OM_Network_T         network;
    char                     group_name[BGP_TYPE_PEER_GROUP_NAME_LEN+1];
    char                     ipv4_str[L_INET_MAX_IP4ADDR_STR_LEN+1];
    char                     peer_str[BGP_TYPE_PEER_STR_LEN+1];
    UI32_T                   confederation_peer;
    struct                   pal_in4_addr netmask;
    UI32_T                   afi = BGP_TYPE_AFI_IP;
    UI32_T                   safi = BGP_TYPE_SAFI_UNICAST;
    UI32_T                   rtype; /*route type */
    UI32_T                   peer_sort;
    BOOL_T                   is_gen_peer_group;
    BOOL_T                   is_group_member;
    BOOL_T                   is_af_group;
    BOOL_T                   is_continue;
    UI8_T                    routerId[SYS_ADPT_IPV4_ADDR_LEN] = {0};

    bgp_instance.as_number = 0;
    while (BGP_POM_GetNextRunCfgInstance(&bgp_instance))
    {
        /* Note: The configuraton CLI commands sequence below follows
         *       bgp_config_write() in bgpd.c of quagga
         *       (except 'distance' and 'distance bgp' command)
         */

        /* router bgp */
        APPEND_RUNNING_CFG_1("router bgp %lu\r\n", (unsigned long)bgp_instance.as_number);

        /* bgp fast-external-failover */
        if (bgp_instance.flag & BGP_TYPE_BGP_FLAG_NO_FAST_EXTERNAL_FAILOVER)
        {
            APPEND_RUNNING_CFG_0(" no bgp fast-external-failover\r\n");
        }

        /* bgp router-id */
        if (bgp_instance.config & BIT_VALUE(BGP_OM_CONFIG_ROUTER_ID))
        {
            IP_LIB_UI32toArray(bgp_instance.router_id, routerId);
            APPEND_RUNNING_CFG_4(" bgp router-id %u.%u.%u.%u\r\n", routerId[0], routerId[1], routerId[2], routerId[3]);
        }

        /* bgp log-neighbor-changes */
        if (bgp_instance.flag & BGP_TYPE_BGP_FLAG_LOG_NEIGHBOR_CHANGES)
        {
            APPEND_RUNNING_CFG_0(" bgp log-neighbor-changes\r\n");
        }

        /* bgp always-compare-med */
        if (bgp_instance.flag & BGP_TYPE_BGP_FLAG_ALWAYS_COMPARE_MED)
        {
            APPEND_RUNNING_CFG_0(" bgp always-compare-med\r\n");
        }

        /* bgp default local-preference */
        if (bgp_instance.config & BIT_VALUE(BGP_OM_CONFIG_LOCAL_PREFERENCE))
        {
            APPEND_RUNNING_CFG_1(" bgp default local-preference %lu\r\n", (unsigned long)bgp_instance.local_preference);
        }

        /* bgp client-to-client reflection */
        if (bgp_instance.flag & BGP_TYPE_BGP_FLAG_NO_CLIENT_TO_CLIENT_REFLECTION)
        {
            APPEND_RUNNING_CFG_0(" no bgp client-to-client reflection\r\n");
        }

        /* bgp cluster-id */
        if (bgp_instance.config & BIT_VALUE(BGP_OM_CONFIG_CLUSTER_ID))
        {
            if (bgp_instance.cluster_id_format == BGP_TYPE_CLUSTER_ID_FORMAT_IP_ADDRESS)
            {
                APPEND_RUNNING_CFG_4(" bgp cluster-id %u.%u.%u.%u\r\n",
                    (bgp_instance.cluster_id&0xff000000)>>24, (bgp_instance.cluster_id&0xff0000)>>16,
                    (bgp_instance.cluster_id&0xff00)>>8, (bgp_instance.cluster_id&0xff));
            }
            else if (bgp_instance.cluster_id_format == BGP_TYPE_CLUSTER_ID_FORMAT_DECIMAL)
            {
                APPEND_RUNNING_CFG_1(" bgp cluster-id %lu\r\n", (unsigned long)bgp_instance.cluster_id);
            }
        }

        /* bgp confederation identifier */
        if (bgp_instance.config & BIT_VALUE(BGP_OM_CONFIG_CONFEDERATION_ID))
        {
            APPEND_RUNNING_CFG_1(" bgp confederation identifier %lu\r\n", (unsigned long)bgp_instance.confederation_id);
        }

        /* bgp confederation peer */
        confederation_peer = 0;
        while (BGP_POM_GetNextRunCfgConfederationPeer(bgp_instance.as_number, &confederation_peer))
        {
            APPEND_RUNNING_CFG_1(" bgp confederation peer %lu\r\n", (unsigned long)confederation_peer);
        }

        /* bgp enforce-first-as */
        if (bgp_instance.flag & BGP_TYPE_BGP_FLAG_ENFORCE_FIRST_AS)
        {
            APPEND_RUNNING_CFG_0(" bgp enforce-first-as\r\n");
        }

        /* bgp deterministic-med */
        if (bgp_instance.flag & BGP_TYPE_BGP_FLAG_DETERMINISTIC_MED)
        {
            APPEND_RUNNING_CFG_0(" bgp deterministic-med\r\n");
        }

        /* bgp bestpath as-path ignore */
        if (bgp_instance.flag & BGP_TYPE_BGP_FLAG_BESTPATH_AS_PATH_IGNORE)
        {
            APPEND_RUNNING_CFG_0(" bgp bestpath as-path ignore\r\n");
        }

        /* bgp bestpath compare-confed-aspath */
        if (bgp_instance.flag & BGP_TYPE_BGP_FLAG_BESTPATH_AS_PATH_CONFED)
        {
            APPEND_RUNNING_CFG_0(" bgp bestpath compare-confed-aspath\r\n");
        }

        /* bgp bestpath compare-routerid */
        if (bgp_instance.flag & BGP_TYPE_BGP_FLAG_BESTPATH_COMPARE_ROUTERID)
        {
            APPEND_RUNNING_CFG_0(" bgp bestpath compare-routerid\r\n");
        }

        /* bgp bestpath med confed missing-as-worst */
        if (bgp_instance.flag & BGP_TYPE_BGP_FLAG_MED_CONFED ||
            bgp_instance.flag & BGP_TYPE_BGP_FLAG_MED_MISSING_AS_WORST)
        {
            APPEND_RUNNING_CFG_0(" bgp bestpath med");
            if (bgp_instance.flag & BGP_TYPE_BGP_FLAG_MED_CONFED)
            {
                APPEND_RUNNING_CFG_0(" confed");
            }
            if (bgp_instance.flag & BGP_TYPE_BGP_FLAG_MED_MISSING_AS_WORST)
            {
                APPEND_RUNNING_CFG_0(" missing-as-worst");
            }
            APPEND_RUNNING_CFG_0("\r\n");
        }

        /* bgp network import-check */
        if (bgp_instance.flag & BGP_TYPE_BGP_FLAG_NETWORK_IMPORT_CHECK)
        {
            APPEND_RUNNING_CFG_0(" bgp network import-check\r\n");
        }

        /* bgp scan-time */
        if (bgp_instance.config & BIT_VALUE(BGP_OM_CONFIG_SCAN_TIME))
        {
            APPEND_RUNNING_CFG_1(" bgp scan-time %lu\r\n", (unsigned long)bgp_instance.scan_time);
        }

        /* bgp dampening */
        if(bgp_instance.dampening_info[afi][safi].is_enable == TRUE)
        {
            if (bgp_instance.config_afi_safi[afi][safi] & BIT_VALUE(BGP_OM_CONFIG_AFI_SAFI_DAMPENING_HALF_LIFE))
            {
                if (bgp_instance.config_afi_safi[afi][safi] & BIT_VALUE(BGP_OM_CONFIG_AFI_SAFI_DAMPENING_REUSE_LIMIT))
                {
                    if (bgp_instance.config_afi_safi[afi][safi] & BIT_VALUE(BGP_OM_CONFIG_AFI_SAFI_DAMPENING_SUPPRESS_LIMIT))
                    {
                        if (bgp_instance.config_afi_safi[afi][safi] & BIT_VALUE(BGP_OM_CONFIG_AFI_SAFI_DAMPENING_MAX_SUPPRESS_TIME))
                        {
                            APPEND_RUNNING_CFG_4(" bgp dampening %lu %lu %lu %lu\r\n", (unsigned long)bgp_instance.dampening_info[afi][safi].half_life,
                                    (unsigned long)bgp_instance.dampening_info[afi][safi].reuse_limit,
                                    (unsigned long)bgp_instance.dampening_info[afi][safi].suppress_limit,
                                    (unsigned long)bgp_instance.dampening_info[afi][safi].max_suppress_time);
                        }
                        else
                        {
                            APPEND_RUNNING_CFG_3(" bgp dampening %lu %lu %lu\r\n", (unsigned long)bgp_instance.dampening_info[afi][safi].half_life,
                                    (unsigned long)bgp_instance.dampening_info[afi][safi].reuse_limit,
                                    (unsigned long)bgp_instance.dampening_info[afi][safi].suppress_limit);
                        }
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_2(" bgp dampening %lu %lu\r\n", (unsigned long)bgp_instance.dampening_info[afi][safi].half_life,
                                (unsigned long)bgp_instance.dampening_info[afi][safi].reuse_limit);
                    }
                }
                else
                {
                    APPEND_RUNNING_CFG_1(" bgp dampening %lu\r\n", (unsigned long)bgp_instance.dampening_info[afi][safi].half_life);
                }
            }
            else
            {
                APPEND_RUNNING_CFG_0(" bgp dampening\r\n");
            }
        }

        /* network */
        memset(&network, 0, sizeof(network));
        while (BGP_POM_GetNextRuncfgNetwork(bgp_instance.as_number, afi, safi, &network))
        {
            APPEND_RUNNING_CFG_4(" network %d.%d.%d.%d ", network.prefix.addr[0],
                network.prefix.addr[1], network.prefix.addr[2], network.prefix.addr[3]);
            L_PREFIX_MaskLen2IPv4(network.prefix.preflen, &netmask);
            APPEND_RUNNING_CFG_1("%s", inet_ntoa(netmask));
            if (network.route_map[0] != '\0')
            {
                APPEND_RUNNING_CFG_1(" route-map %s\r\n", network.route_map);
            }
            else
            {
                if (network.backdoor != 0)
                {
                    APPEND_RUNNING_CFG_0(" backdoor");
                }

                if (network.ttl != 0)
                {
                    APPEND_RUNNING_CFG_1(" pathlimit %u\r\n", network.ttl);
                }
                else
                {
                    APPEND_RUNNING_CFG_0("\r\n");
                }
            }
        }

        /* aggregate-address */
        memset(&aggregate_addr, 0, sizeof(aggregate_addr));
        while (BGP_POM_GetNextRunCfgAggregateAddress(bgp_instance.as_number, afi, safi, &aggregate_addr))
        {
            APPEND_RUNNING_CFG_4(" aggregate-address %d.%d.%d.%d ", aggregate_addr.prefix.addr[0],
                aggregate_addr.prefix.addr[1], aggregate_addr.prefix.addr[2], aggregate_addr.prefix.addr[3]);
            L_PREFIX_MaskLen2IPv4(aggregate_addr.prefix.preflen, &netmask);
            APPEND_RUNNING_CFG_1("%s", inet_ntoa(netmask));
            if (aggregate_addr.is_as_set)
            {
                APPEND_RUNNING_CFG_0(" as-set");
            }
            if (aggregate_addr.is_summary_only)
            {
                APPEND_RUNNING_CFG_0(" summary-only");
            }
            APPEND_RUNNING_CFG_0("\r\n");
        }

        /* redistribute */
        for (rtype = BGP_TYPE_ROUTE_SYSTEM; rtype < BGP_TYPE_ROUTE_MAX; rtype++)
        {
            if (bgp_instance.config_afi_rtype[afi][rtype] & BIT_VALUE(BGP_OM_CONFIG_AFI_RTYPE_REDISTRIBUTE_STATUS))
            {
                if (bgp_instance.redistribute_status[afi][rtype])
                {
                    switch (rtype)
                    {
                        case BGP_TYPE_ROUTE_CONNECT:
                            APPEND_RUNNING_CFG_0(" redistribute connected");
                            break;
                        case BGP_TYPE_ROUTE_OSPF:
                            APPEND_RUNNING_CFG_0(" redistribute ospf");
                            break;
                        case BGP_TYPE_ROUTE_RIP:
                            APPEND_RUNNING_CFG_0(" redistribute rip");
                            break;
                        case BGP_TYPE_ROUTE_STATIC:
                            APPEND_RUNNING_CFG_0(" redistribute static");
                            break;
                        default:
                            continue;
                    }
                    if (bgp_instance.config_afi_rtype[afi][rtype] & BIT_VALUE(BGP_OM_CONFIG_AFI_RTYPE_REDISTRIBUTE_METRIC))
                    {
                        APPEND_RUNNING_CFG_1(" metric %lu", (unsigned long)bgp_instance.redistribute_metric[afi][rtype]);
                    }
                    if (bgp_instance.config_afi_rtype[afi][rtype] & BIT_VALUE(BGP_OM_CONFIG_AFI_RTYPE_REDISTRIBUTE_RMAP))
                    {
                        APPEND_RUNNING_CFG_1(" route-map %s\r\n", bgp_instance.redistribute_rmap[afi][rtype]);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_0("\r\n");
                    }
                }
            }
        }

        /* timers bgp */
        if (bgp_instance.config & BIT_VALUE(BGP_OM_CONFIG_TIMERS_BGP))
        {
            APPEND_RUNNING_CFG_2(" timers bgp %lu %lu\r\n", (unsigned long)bgp_instance.keep_alive_interval, (unsigned long)bgp_instance.hold_time);
        }

        /* distance bgp */
        if (bgp_instance.config & BIT_VALUE(BGP_OM_CONFIG_DISTANCE_BGP))
        {
            APPEND_RUNNING_CFG_3(" distance bgp %lu %lu %lu\r\n", (unsigned long)bgp_instance.distance_ebgp, (unsigned long)bgp_instance.distance_ibgp, (unsigned long)bgp_instance.distance_local);
        }

        /* distance */
        memset(&distance, 0, sizeof(distance));
        while (BGP_POM_GetNextRunCfgDistance(bgp_instance.as_number, &distance))
        {
            APPEND_RUNNING_CFG_5(" distance %lu %d.%d.%d.%d ", (unsigned long)distance.distance,
                distance.prefix.addr[0], distance.prefix.addr[1], distance.prefix.addr[2], distance.prefix.addr[3]);
            L_PREFIX_MaskLen2IPv4(distance.prefix.preflen, &netmask);
            APPEND_RUNNING_CFG_1("%s", inet_ntoa(netmask));
            if (distance.access_list[0] != 0)
            {
                APPEND_RUNNING_CFG_1(" %s\r\n",distance.access_list);
            }
            else
            {
                APPEND_RUNNING_CFG_0("\r\n");
            }
        }

        /* below is neighbor configuration
         */
        memset(&neighbor, 0, sizeof(neighbor));
        neighbor.afi  = afi;
        neighbor.safi = safi;
        memset(group_name, 0, sizeof(group_name));
        memset(&config, 0, sizeof(config));
        config.afi  = afi;
        config.safi = safi;

        is_gen_peer_group = TRUE; /* gen peer group config first, then peer config */
        is_continue = TRUE;

        while (is_continue)
        {
            if (!is_gen_peer_group)
            {
                if (TRUE == (is_continue = BGP_POM_GetNextRuncfgNeighbor(bgp_instance.as_number, &neighbor)))
                {
                    memset(ipv4_str, 0, sizeof(ipv4_str));
                    snprintf(ipv4_str, L_INET_MAX_IP4ADDR_STR_LEN, "%u.%u.%u.%u", neighbor.neighbor_addr.addr[0], neighbor.neighbor_addr.addr[1],
                              neighbor.neighbor_addr.addr[2],neighbor.neighbor_addr.addr[3]);

                    /* if it is a peer group member, need to get it's peer-group config when gen
                     */
                    if (neighbor.cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_GROUP_MEMBER))
                    {
                        if (!BGP_POM_GetRuncfgPeerGroup(bgp_instance.as_number, neighbor.cmn_cfg.group_name, &config))
                            continue;
                        group_p = &config;
                    }

                    strncpy(peer_str, ipv4_str, sizeof(peer_str));
                    config_p = &neighbor;
                    is_group_member = config_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_GROUP_MEMBER);
                    is_af_group     = config_p->afi_safi_cfg.af_group;
                }
                else
                {
                    break; /* end of gen neighbor config */
                }
            }
            else
            {
                if (TRUE == (is_continue = BGP_POM_GetNextRuncfgPeerGroup(bgp_instance.as_number, group_name, &config)))
                {
                    strncpy(peer_str, group_name, sizeof(peer_str));
                    config_p = &config;
                    is_group_member = FALSE;
                    is_af_group     = FALSE;
                }
                else
                {
                    is_gen_peer_group = FALSE; /* continue to peer config */
                    is_continue = TRUE;
                    continue;
                }
            }

            /* peer group and remote as */
            if (is_gen_peer_group)
            {
                APPEND_RUNNING_CFG_1(" neighbor %s peer-group\r\n", group_name);
                if (config_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_AS_NUMBER))
                {
                    APPEND_RUNNING_CFG_2(" neighbor %s remote-as %lu\r\n", group_name, (unsigned long)config_p->cmn_cfg.as_number);
                }
            }
            else
            {
                if (is_group_member)
                {
                    if (!(group_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_AS_NUMBER)) &&
                        (config_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_AS_NUMBER)))
                    {
                        APPEND_RUNNING_CFG_2(" neighbor %s remote-as %lu\r\n", ipv4_str, (unsigned long)config_p->cmn_cfg.as_number);
                    }

                    APPEND_RUNNING_CFG_2(" neighbor %s peer-group %s\r\n", ipv4_str, config_p->cmn_cfg.group_name);
                }
                else
                {
                    if (config_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_AS_NUMBER))
                    {
                        APPEND_RUNNING_CFG_2(" neighbor %s remote-as %lu\r\n", ipv4_str, (unsigned long)config_p->cmn_cfg.as_number);
                    }
                }
            }

            /* neighbor description */
            if (config_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_DESCRIPTION))
            {
                if (config_p->cmn_cfg.description[0] != 0)
                {
                    APPEND_RUNNING_CFG_2(" neighbor %s description %s\r\n", peer_str, config_p->cmn_cfg.description);
                }
            }

            /* neighbor shutdown */
            if (config_p->cmn_cfg.flag & BGP_TYPE_NEIGHBOR_FLAG_SHUTDOWN)
            {
                if (!is_group_member ||
                    !(group_p->cmn_cfg.flag & BGP_TYPE_NEIGHBOR_FLAG_SHUTDOWN))
                {
                    APPEND_RUNNING_CFG_1(" neighbor %s shutdown\r\n", peer_str);
                }
            }

            /* neighbor port */
            if (config_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_PORT))
            {
                APPEND_RUNNING_CFG_2(" neighbor %s port %lu\r\n", peer_str, (unsigned long)config_p->cmn_cfg.port);
            }

            /* neighbor interface */
            if (config_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_INTERFACE))
            {
                UI32_T vlan_id;

                if (IS_VLAN_IFINDEX_VAILD(config_p->cmn_cfg.ifindex))
                {
                    VLAN_IFINDEX_CONVERTTO_VID(config_p->cmn_cfg.ifindex, vlan_id);
                    APPEND_RUNNING_CFG_2(" neighbor %s interface vlan %lu\r\n", peer_str, (unsigned long)vlan_id);
                }
            }

            /* neighbor passive */
            if (config_p->cmn_cfg.flag & BGP_TYPE_NEIGHBOR_FLAG_PASSIVE)
            {
                if (!is_group_member ||
                    !(group_p->cmn_cfg.flag & BGP_TYPE_NEIGHBOR_FLAG_PASSIVE))
                {
                    APPEND_RUNNING_CFG_1(" neighbor %s passive\r\n", peer_str);
                }
            }

            /* neighbor password */
            if (config_p->cmn_cfg.password[0] !=0)
            {
                if (!is_group_member ||
                    !(group_p->cmn_cfg.password[0] !=0))
                {
                    APPEND_RUNNING_CFG_2(" neighbor %s password %s\r\n", peer_str,config_p->cmn_cfg.password);
                }
            }

            /* neighbor ebgp-multihop */
            if (config_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_EBGP_MULTIHOP))
            {
                if (BGP_TYPE_RESULT_OK == BGP_PMGR_GetNeighborPeerSort(bgp_instance.as_number, peer_str, &peer_sort))
                {
                    if (peer_sort != BGP_TYPE_NEIGHBOR_IBGP)
                    {
                        if (!is_group_member ||
                            !(group_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_EBGP_MULTIHOP)) ||
                             (config_p->cmn_cfg.ebgp_multihop != group_p->cmn_cfg.ebgp_multihop))
                        {
                            if (config_p->cmn_cfg.ebgp_multihop != BGP_TYPE_DEFAULT_EBGP_MULTIHOP)
                            {
                                APPEND_RUNNING_CFG_2(" neighbor %s ebgp-multihop %lu\r\n", peer_str, (unsigned long)config_p->cmn_cfg.ebgp_multihop);
                            }
                            else
                            {
                                APPEND_RUNNING_CFG_1(" neighbor %s ebgp-multihop\r\n", peer_str);
                            }
                        }
                    }
                }
            }

            /* neighbor enforce-multihop */
            if (config_p->cmn_cfg.flag & BGP_TYPE_NEIGHBOR_FLAG_DISABLE_CONNECTED_CHECK)
            {
                if (!is_group_member ||
                    !(group_p->cmn_cfg.flag & BGP_TYPE_NEIGHBOR_FLAG_DISABLE_CONNECTED_CHECK))
                {
                    APPEND_RUNNING_CFG_1(" neighbor %s enforce-multihop\r\n", peer_str);
                }
            }

            /* neighbor update-source */
            if (config_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_UPDATE_SOURCE))
            {
                if (!is_group_member ||
                    !(group_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_UPDATE_SOURCE)) ||
                    config_p->cmn_cfg.update_source != group_p->cmn_cfg.update_source)
                {
                    UI32_T vlan_id;

                    if (IS_VLAN_IFINDEX_VAILD(config_p->cmn_cfg.update_source))
                    {
                        VLAN_IFINDEX_CONVERTTO_VID(config_p->cmn_cfg.update_source, vlan_id);
                        APPEND_RUNNING_CFG_2(" neighbor %s update-source interface vlan %lu\r\n", peer_str, (unsigned long)vlan_id);
                    }
                }
            }

            /* neighbor advertisement-interval */
            if (config_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_ADVERTISEMENT_INTERVAL))
            {
                APPEND_RUNNING_CFG_2(" neighbor %s advertisement-interval %lu\r\n", peer_str, (unsigned long)config_p->cmn_cfg.advertise_interval);
            }

            /* neighbor timers */
            if (!is_group_member &&
                config_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_TIMERS))
            {
                APPEND_RUNNING_CFG_3(" neighbor %s timers %lu %lu\r\n", peer_str, (unsigned long)config_p->cmn_cfg.keep_alive_interval, (unsigned long)config_p->cmn_cfg.hold_time);
            }

            /* neighbor timers connect */
            if (config_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_CONNECT_RETRY_INTERVAL))
            {
                APPEND_RUNNING_CFG_2(" neighbor %s timers connect %lu\r\n", peer_str, (unsigned long)config_p->cmn_cfg.connect_retry_interval);
            }

            /* neighbor weight */
            if (config_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_WEIGHT))
            {
                if (!is_group_member ||
                    !(group_p->cmn_cfg.config & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_WEIGHT)) ||
                    config_p->cmn_cfg.weight != group_p->cmn_cfg.weight)
                {
                    APPEND_RUNNING_CFG_2(" neighbor %s weight %lu\r\n", peer_str, (unsigned long)config_p->cmn_cfg.weight);
                }
            }

            /* neighbor capability dynamic */
            if (config_p->cmn_cfg.flag & BGP_TYPE_NEIGHBOR_FLAG_DYNAMIC_CAPABILITY)
            {
                if (!is_group_member ||
                    !(group_p->cmn_cfg.flag & BGP_TYPE_NEIGHBOR_FLAG_DYNAMIC_CAPABILITY))
                {
                    APPEND_RUNNING_CFG_1(" neighbor %s capability dynamic\r\n", peer_str);
                }
            }

            /* neighbor dont-capability-negotiate */
            if (config_p->cmn_cfg.flag & BGP_TYPE_NEIGHBOR_FLAG_DONT_CAPABILITY)
            {
                if (!is_group_member ||
                    !(group_p->cmn_cfg.flag & BGP_TYPE_NEIGHBOR_FLAG_DONT_CAPABILITY))
                {
                    APPEND_RUNNING_CFG_1(" neighbor %s dont-capability-negotiate\r\n", peer_str);
                }
            }

            /* neighbor override-capability */
            if (config_p->cmn_cfg.flag & BGP_TYPE_NEIGHBOR_FLAG_OVERRIDE_CAPABILITY)
            {
                if (!is_group_member ||
                    !(group_p->cmn_cfg.flag & BGP_TYPE_NEIGHBOR_FLAG_OVERRIDE_CAPABILITY))
                {
                    APPEND_RUNNING_CFG_1(" neighbor %s override-capability\r\n", peer_str);
                }
            }

            /* neighbor strict-capability-match */
            if (config_p->cmn_cfg.flag & BGP_TYPE_NEIGHBOR_FLAG_STRICT_CAP_MATCH)
            {
                if (!is_group_member ||
                    !(group_p->cmn_cfg.flag & BGP_TYPE_NEIGHBOR_FLAG_STRICT_CAP_MATCH))
                {
                    APPEND_RUNNING_CFG_1(" neighbor %s strict-capability-match\r\n", peer_str);
                }
            }

            /* neigbor activate */
            if (config_p->afi_safi_cfg.config_afi_safi & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_AFI_SAFI_ACTIVATE_STATUS) &&
                !is_group_member)
            {
                if (bgp_instance.flag & BGP_TYPE_BGP_FLAG_NO_DEFAULT_ACTIVATE_IPV4_UNICAST)
                {
                    if (config_p->afi_safi_cfg.activate_status)
                    {
                        APPEND_RUNNING_CFG_1(" neighbor %s activate\r\n", peer_str);
                    }
                }
                else
                {
                    if (!config_p->afi_safi_cfg.activate_status)
                    {
                        APPEND_RUNNING_CFG_1(" no neighbor %s activate\r\n", peer_str);
                    }
                }
            }

            /* neighbor capability orf prefix-list */
            if (config_p->afi_safi_cfg.af_flag & (BGP_TYPE_NEIGHBOR_AF_FLAG_ORF_PREFIX_SM |
                                                  BGP_TYPE_NEIGHBOR_AF_FLAG_ORF_PREFIX_RM))
            {
                if (!is_af_group)
                {
                    if (config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_ORF_PREFIX_SM)
                    {
                        if (config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_ORF_PREFIX_RM)
                        {
                            APPEND_RUNNING_CFG_1(" neighbor %s capability orf prefix-list both\r\n", peer_str);
                        }
                        else
                        {
                            APPEND_RUNNING_CFG_1(" neighbor %s capability orf prefix-list send\r\n", peer_str);
                        }
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_1(" neighbor %s capability orf prefix-list receive\r\n", peer_str);
                    }
                }
            }

            /* neighbor route-reflector-client */
            if (config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_REFLECTOR_CLIENT &&
                !is_af_group)
            {
                APPEND_RUNNING_CFG_1(" neighbor %s route-reflector-client\r\n", peer_str);
            }

            /* neighbor next-hop-self */
            if (config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_NEXTHOP_SELF &&
                !is_af_group)
            {
                APPEND_RUNNING_CFG_1(" neighbor %s next-hop-self\r\n", peer_str);
            }

            /* neighbor remove-private-as */
            if (config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_REMOVE_PRIVATE_AS &&
                !is_af_group)
            {
                APPEND_RUNNING_CFG_1(" neighbor %s remove-private-as\r\n", peer_str);
            }

            /* neighbor send-community */
            if ((config_p->afi_safi_cfg.af_flag & (BGP_TYPE_NEIGHBOR_AF_FLAG_SEND_COMMUNITY |
                                                   BGP_TYPE_NEIGHBOR_AF_FLAG_SEND_EXT_COMMUNITY)) &&
                (!is_af_group))
            {
                if (config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_SEND_COMMUNITY)
                {
                    if (config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_SEND_EXT_COMMUNITY)
                    {
                        APPEND_RUNNING_CFG_1(" neighbor %s send-community both\r\n", peer_str);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_1(" neighbor %s send-community standard\r\n", peer_str);
                    }
                }
                else
                {
                    APPEND_RUNNING_CFG_1(" neighbor %s send-community extended\r\n", peer_str);
                }
            }

            /* neighbor default-originate */
            if (config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_DEFAULT_ORIGINATE &&
                !is_af_group)
            {
                if (config_p->afi_safi_cfg.default_originate[0] != 0)
                {
                    APPEND_RUNNING_CFG_2(" neighbor %s default-originate route-map %s\r\n", peer_str, config_p->afi_safi_cfg.default_originate);
                }
                else
                {
                    APPEND_RUNNING_CFG_1(" neighbor %s default-originate\r\n", peer_str);
                }
            }

            /* neighbor soft-reconfiguration inbound */
            if (config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_SOFT_RECONFIG)
            {
                if (!is_af_group ||
                    !(group_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_SOFT_RECONFIG))
                {
                    APPEND_RUNNING_CFG_1(" neighbor %s soft-reconfiguration inbound\r\n", peer_str);
                }
            }

            /* neighbor maximum-prefix */
            if (config_p->afi_safi_cfg.config_afi_safi & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_AFI_SAFI_MAXIMUM_PREFIX))
            {
                if (!is_af_group ||
                    config_p->afi_safi_cfg.max_prefix_info.max_prefix != group_p->afi_safi_cfg.max_prefix_info.max_prefix ||
                    config_p->afi_safi_cfg.max_prefix_info.threshold != group_p->afi_safi_cfg.max_prefix_info.threshold ||
                    config_p->afi_safi_cfg.max_prefix_info.warn_only != group_p->afi_safi_cfg.max_prefix_info.warn_only)
                {
                    APPEND_RUNNING_CFG_2(" neighbor %s maximum-prefix %lu", peer_str, (unsigned long)config_p->afi_safi_cfg.max_prefix_info.max_prefix);
                    if (config_p->afi_safi_cfg.max_prefix_info.threshold > 0)
                    {
                        APPEND_RUNNING_CFG_1(" %u", config_p->afi_safi_cfg.max_prefix_info.threshold);
                        if (config_p->afi_safi_cfg.max_prefix_info.warn_only)
                        {
                            APPEND_RUNNING_CFG_0(" warning-only\r\n");
                        }
                        else if (config_p->afi_safi_cfg.max_prefix_info.restart_interval)
                        {
                            APPEND_RUNNING_CFG_1(" restart %u\r\n", config_p->afi_safi_cfg.max_prefix_info.restart_interval);
                        }
                        else
                        {
                            APPEND_RUNNING_CFG_0("\r\n");
                        }
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_0("\r\n");
                    }
                }
            }

            /* neighbor route-server-client */
            if (config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_RSERVER_CLIENT &&
                !is_af_group)
            {
                APPEND_RUNNING_CFG_1(" neighbor %s route-server-client\r\n", peer_str);
            }

            /* neighbor allowas-in */
            if (config_p->afi_safi_cfg.config_afi_safi & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_AFI_SAFI_ALLOW_AS_IN))
            {
                if (!is_af_group ||
                    !(group_p->afi_safi_cfg.config_afi_safi & BIT_VALUE(BGP_OM_CONFIG_NEIGHBOR_AFI_SAFI_ALLOW_AS_IN)) ||
                    config_p->afi_safi_cfg.allow_as_in != group_p->afi_safi_cfg.allow_as_in)
                {
                    if (config_p->afi_safi_cfg.allow_as_in == BGP_TYPE_DEFAULT_ALLOW_AS_IN)
                    {
                        APPEND_RUNNING_CFG_1(" neighbor %s allowas-in\r\n", peer_str);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_2(" neighbor %s allowas-in %lu\r\n", peer_str, (unsigned long)config_p->afi_safi_cfg.allow_as_in);
                    }
                }
            }

            /* neighbor distribute-list */
            if (config_p->afi_safi_cfg.distribute_list[BGP_TYPE_FILTER_DIRECTION_IN][0] != 0)
            {
                if (!is_af_group ||
                    group_p->afi_safi_cfg.distribute_list[BGP_TYPE_FILTER_DIRECTION_IN][0] == 0 ||
                    0 != strncmp(config_p->afi_safi_cfg.distribute_list[BGP_TYPE_FILTER_DIRECTION_IN],
                            group_p->afi_safi_cfg.distribute_list[BGP_TYPE_FILTER_DIRECTION_IN],
                            sizeof(config_p->afi_safi_cfg.distribute_list[BGP_TYPE_FILTER_DIRECTION_IN])))
                {
                    APPEND_RUNNING_CFG_2(" neighbor %s distribute-list %s in\r\n",peer_str, config_p->afi_safi_cfg.distribute_list[BGP_TYPE_FILTER_DIRECTION_IN]);
                }
            }
            if (config_p->afi_safi_cfg.distribute_list[BGP_TYPE_FILTER_DIRECTION_OUT][0] != 0 &&
                !is_af_group)
            {
                APPEND_RUNNING_CFG_2(" neighbor %s distribute-list %s out\r\n",peer_str, config_p->afi_safi_cfg.distribute_list[BGP_TYPE_FILTER_DIRECTION_OUT]);
            }

            /* neighbor prefix-list */
            if (config_p->afi_safi_cfg.prefix_list[BGP_TYPE_FILTER_DIRECTION_IN][0] != 0)
            {
                if (!is_af_group ||
                    group_p->afi_safi_cfg.prefix_list[BGP_TYPE_FILTER_DIRECTION_IN][0] == 0 ||
                    0 != strncmp(config_p->afi_safi_cfg.prefix_list[BGP_TYPE_FILTER_DIRECTION_IN],
                            group_p->afi_safi_cfg.prefix_list[BGP_TYPE_FILTER_DIRECTION_IN],
                            sizeof(config_p->afi_safi_cfg.prefix_list[BGP_TYPE_FILTER_DIRECTION_IN])))
                {
                    APPEND_RUNNING_CFG_2(" neighbor %s prefix-list %s in\r\n",peer_str, config_p->afi_safi_cfg.prefix_list[BGP_TYPE_FILTER_DIRECTION_IN]);
                }
            }
            if (config_p->afi_safi_cfg.prefix_list[BGP_TYPE_FILTER_DIRECTION_OUT][0] != 0 &&
                !is_af_group)
            {
                APPEND_RUNNING_CFG_2(" neighbor %s prefix-list %s out\r\n",peer_str, config_p->afi_safi_cfg.prefix_list[BGP_TYPE_FILTER_DIRECTION_OUT]);
            }

            /* neighbor route-map */
            if (config_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_IN][0] != 0)
            {
                if (!is_af_group ||
                    group_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_IN][0] == 0 ||
                    0 != strncmp(config_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_IN],
                            group_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_IN],
                            sizeof(config_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_IN])))
                {
                    APPEND_RUNNING_CFG_2(" neighbor %s route-map %s in\r\n",peer_str, config_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_IN]);
                }
            }
            if (config_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_OUT][0] != 0 &&
                !is_af_group)
            {
                APPEND_RUNNING_CFG_2(" neighbor %s route-map %s out\r\n",peer_str, config_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_OUT]);
            }
            if (config_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_IMPORT][0] != 0 &&
                !is_af_group)
            {
                APPEND_RUNNING_CFG_2(" neighbor %s route-map %s import\r\n",peer_str, config_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_IMPORT]);
            }
            if (config_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_EXPORT][0] != 0)
            {
                if (!is_af_group ||
                    group_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_EXPORT][0] == 0 ||
                    0 != strncmp(config_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_EXPORT],
                            group_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_EXPORT],
                            sizeof(config_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_EXPORT])))
                {
                    APPEND_RUNNING_CFG_2(" neighbor %s route-map %s export\r\n",peer_str, config_p->afi_safi_cfg.route_map[BGP_TYPE_RMAP_EXPORT]);
                }
            }

            /* neighbor unsuppress-map */
            if (config_p->afi_safi_cfg.unsuppress_map[0] != 0 &&
                !is_af_group)
            {
                APPEND_RUNNING_CFG_2(" neighbor %s unsuppress-map %s\r\n", peer_str, config_p->afi_safi_cfg.unsuppress_map);
            }

            /* neighbor filter-list */
            if (config_p->afi_safi_cfg.filter_list[BGP_TYPE_FILTER_DIRECTION_IN][0] != 0)
            {
                if (!is_af_group ||
                    group_p->afi_safi_cfg.filter_list[BGP_TYPE_FILTER_DIRECTION_IN][0] == 0 ||
                    0 != strncmp(config_p->afi_safi_cfg.filter_list[BGP_TYPE_FILTER_DIRECTION_IN],
                            group_p->afi_safi_cfg.filter_list[BGP_TYPE_FILTER_DIRECTION_IN],
                            sizeof(config_p->afi_safi_cfg.filter_list[BGP_TYPE_FILTER_DIRECTION_IN])))
                {
                    APPEND_RUNNING_CFG_2(" neighbor %s filter-list %s in\r\n",peer_str, config_p->afi_safi_cfg.filter_list[BGP_TYPE_FILTER_DIRECTION_IN]);
                }
            }
            if (config_p->afi_safi_cfg.filter_list[BGP_TYPE_FILTER_DIRECTION_OUT][0] != 0 &&
                !is_af_group)
            {
                APPEND_RUNNING_CFG_2(" neighbor %s filter-list %s out\r\n",peer_str, config_p->afi_safi_cfg.filter_list[BGP_TYPE_FILTER_DIRECTION_OUT]);
            }

            /* neighbor attribute-unchanged */
            if ((config_p->afi_safi_cfg.af_flag & (BGP_TYPE_NEIGHBOR_AF_FLAG_AS_PATH_UNCHANGED |
                                                  BGP_TYPE_NEIGHBOR_AF_FLAG_NEXTHOP_UNCHANGED |
                                                  BGP_TYPE_NEIGHBOR_AF_FLAG_MED_UNCHANGED)) &&
                !is_af_group)
            {
                if (config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_AS_PATH_UNCHANGED &&
                    config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_MED_UNCHANGED &&
                    config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_NEXTHOP_UNCHANGED)
                {
                    APPEND_RUNNING_CFG_1(" neighbor %s attribute-unchanged\r\n", peer_str);
                }
                else
                {
                    buff[0] = '\0';
                    if (config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_AS_PATH_UNCHANGED)
                    {
                        strncat(buff, " as-path", CLI_DEF_MAX_BUFSIZE);
                    }
                    if (config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_MED_UNCHANGED)
                    {
                        strncat(buff, " med", CLI_DEF_MAX_BUFSIZE);
                    }
                    if (config_p->afi_safi_cfg.af_flag & BGP_TYPE_NEIGHBOR_AF_FLAG_NEXTHOP_UNCHANGED)
                    {
                        strncat(buff, " next-hop", CLI_DEF_MAX_BUFSIZE);
                    }

                    APPEND_RUNNING_CFG_2(" neighbor %s attribute-unchanged%s\r\n", peer_str, buff);
                }
            }
        }
        /* End of neighbor configuration
         */
    }
}
#endif /* #if (SYS_CPNT_BGP == TRUE) */


   return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_L3_Global_Command_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{

   UI32_T buffer_count = b_count;
   //int ip_forwarding = VAL_ipForwarding_forwarding;
//   BOOL_T ip_forwarding;

#if 0
   if(NETCFG_PMGR_ROUTE_GetRunningIpForwarding(vr_id, L_INET_ADDR_TYPE_IPV4, &ip_forwarding) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
   {
      //if(ip_forwarding==VAL_ipForwarding_forwarding)
      if(ip_forwarding == TRUE)
      {
         APPEND_RUNNING_CFG_0("ip routing\n");
      }
      else
      {
         APPEND_RUNNING_CFG_0("no ip routing\n");
      }
   }
#endif

#if (SYS_CPNT_NSM == TRUE)
   {
      UI8_T multipaths = 0;

      NSM_PMGR_GetMultipathNumber(&multipaths);
      if (SYS_DFLT_ALLOWED_ECMP_NBR_PER_ROUTE != multipaths)
      {
          APPEND_RUNNING_CFG_1("maximum-paths %d\n", multipaths);
      }
   }
#endif

   {
      {
         UI32_T time_out_value;
         SYS_TYPE_Get_Running_Cfg_T rc;
         /* arp timeout */
         rc=NETCFG_POM_ND_GetRunningIpNetToMediaTimeout(&time_out_value);
         if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == rc )
         {
            APPEND_RUNNING_CFG_1("arp timeout %lu\n", (unsigned long)time_out_value);
         }
      }

   }

#if (SYS_CPNT_UDP_HELPER == TRUE)
   {
      UI32_T ret;
      UI32_T status;
      UI32_T forward_port;

      ret = UDPHELPER_PMGR_GetStatus(&status);
      if ( ret == UDPHELPER_TYPE_RESULT_SUCCESS && status )
      {
          APPEND_RUNNING_CFG_0("ip helper\n");
      }
      forward_port = 0;
      while(UDPHELPER_PMGR_GetNextForwardPort(&forward_port) == UDPHELPER_TYPE_RESULT_SUCCESS )
      {
          APPEND_RUNNING_CFG_1("ip forward-protocol udp %lu\n", forward_port);
      }
   }
#endif
#if (SYS_CPNT_STATIC_ROUTE_AND_METER_WORKAROUND == TRUE)
    {
        UI32_T status;
        NETCFG_PMGR_ROUTE_GetSWRoute(&status);
        if (status != SYS_DFLT_SW_ROUTE_STATUS)
        {
            if (status)
            {
                APPEND_RUNNING_CFG_0("ip sw-route\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no ip sw-route\n");
            }
        }
    }
#endif /*#if (SYS_CPNT_STATIC_ROUTE_AND_METER_WORKAROUND == TRUE)*/

   return buffer_count;
}
#endif

#if (SYS_CPNT_ACL_UI == TRUE)
#if (SYS_CPNT_QOS_V2 == TRUE)
#if (SYS_CPNT_TIME_BASED_ACL == TRUE)
static UI32_T CLI_RUNCFG_Get_ACL_TIME_RANGE_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    /*show running*/
    UI32_T buffer_count = b_count;
    UI32_T periodic_index;

    UI16_T time_range_index = RULE_TYPE_UNDEF_TIME_RANGE;
    RULE_TYPE_TIME_ACL_TIME_RANGE_T time_range_entry;

    char month[13][15] = {"", "january", "february", "march", "april", "may", "june",
                               "july", "aguest", "september", "october", "november", "december"};

    char day[10][10]   = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday",
                           "daily", "weekdays", "weekend"};

    char  buff[CLI_DEF_MAX_BUFSIZE] = {0};
    BOOL_T is_show_absolute;

    while ( L4_PMGR_ACL_GetNextRunningTimeRange(&time_range_index, &time_range_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        is_show_absolute = FALSE;

        APPEND_RUNNING_CFG_1 ("time-range %s\n", time_range_entry.name);

        /* show absolute */
        if (TRUE == time_range_entry.check_start_absolute)
        {
            is_show_absolute = TRUE;
            sprintf(buff, "   absolute start %02u %02u %02u %s %04u",
                time_range_entry.start_time.hour, time_range_entry.start_time.minute,
                time_range_entry.start_time.day, month[time_range_entry.start_time.month],
                time_range_entry.start_time.year);

        }
        if (TRUE == time_range_entry.check_end_absolute)
        {
            if (FALSE == is_show_absolute)
            {
                sprintf (buff, "   absolute");
                is_show_absolute = TRUE;
            }

            sprintf(buff, "%s end %02u %02u %02u %s %04u ", buff,
                time_range_entry.end_time.hour, time_range_entry.end_time.minute,
                time_range_entry.end_time.day, month[time_range_entry.end_time.month],
                time_range_entry.end_time.year);
        }

        if (TRUE == is_show_absolute)
        {
            strcat(buff, "\n");
            APPEND_RUNNING_CFG_0 (buff);
        }

        /* show periodic */
        for (periodic_index = 0; periodic_index < SYS_ADPT_MAX_NBRS_OF_TIME_ACL_PERIODIC; periodic_index++)
        {
            if (TRUE == time_range_entry.check_periodic[periodic_index])
            {
                sprintf(buff, "   periodic %s %02u %02u to %s %02u %02u \n",
                day[time_range_entry.periodic_daily_time[periodic_index].start_type_of_wk],
                    time_range_entry.periodic_daily_time[periodic_index].start_hour,
                    time_range_entry.periodic_daily_time[periodic_index].start_minute,
                day[time_range_entry.periodic_daily_time[periodic_index].end_type_of_wk],
                    time_range_entry.periodic_daily_time[periodic_index].end_hour,
                    time_range_entry.periodic_daily_time[periodic_index].end_minute);
                APPEND_RUNNING_CFG_0 (buff);
            }

        }/*get next of periodic*/

        APPEND_RUNNING_CFG_0("!\n");
    }/*get next of time range */

    return buffer_count;
}
#endif /* end of #if (SYS_CPNT_TIME_BASED_ACL == TRUE) */

static UI32_T
CLI_RUNCFG_Get_ACL_Parameter(
    UI32_T unit_id,
    char *buffer,
    char *temp_buffer,
    UI32_T buffer_size,
    UI32_T b_count)
{
    /*show running*/
    UI32_T buffer_count = b_count;

    UI32_T  i;
    UI32_T  acl_index;
    UI32_T  ace_index;

    RULE_TYPE_AclType_T acl_type_ary[] =
    {
        RULE_TYPE_IP_STD_ACL,
        RULE_TYPE_IP_EXT_ACL,
#if (SYS_CPNT_ACL_IPV6 == TRUE)
        RULE_TYPE_IPV6_STD_ACL,
        RULE_TYPE_IPV6_EXT_ACL,
#endif /* #if (SYS_CPNT_ACL_IPV6 == TRUE) */
        RULE_TYPE_MAC_ACL,
#if (SYS_CPNT_DAI == TRUE)
        RULE_TYPE_ARP_ACL
#endif /* #if (SYS_CPNT_DAI == TRUE) */
    };

    RULE_TYPE_UI_AclEntry_T     acl_entry;
    RULE_TYPE_UI_Ace_Entry_T    ui_ace;

#define CLI_RUNCFG_ACL_PRIV_STRCAT(dest, source) \
    strncat(dest, source, sizeof(dest) - strlen(dest) - 1)

    for (i = 0; i < (sizeof(acl_type_ary)/sizeof(acl_type_ary[0])); i++)
    {
        memset(&acl_entry, 0, sizeof(acl_entry));
        acl_index = 0;
        acl_entry.acl_type = acl_type_ary [i];

        while (L4_PMGR_ACL_GetNextRunningAcl( &acl_index, &acl_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            /* ACL name
             */
            {
                char acl_name[SYS_ADPT_ACL_MAX_NAME_LEN + 1];
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                CLI_LIB_Str_Add_Quote ( (char *)acl_entry.acl_name, acl_name);
#else
                SYSFUN_Snprintf(acl_name, sizeof(acl_name), "%s", acl_entry.acl_name);
#endif

                switch ( acl_entry.acl_type )
                {
                    case RULE_TYPE_IP_STD_ACL:
                        APPEND_RUNNING_CFG_0("access-list IP standard");
                        break;

                    case RULE_TYPE_IP_EXT_ACL:
                        APPEND_RUNNING_CFG_0("access-list IP extended");
                        break;

                    case RULE_TYPE_MAC_ACL:
                        APPEND_RUNNING_CFG_0("access-list MAC");
                        break;

#if (SYS_CPNT_ACL_IPV6 == TRUE)
                    case RULE_TYPE_IPV6_EXT_ACL:
                        APPEND_RUNNING_CFG_0("access-list ipv6 extended");
                        break;

                    case RULE_TYPE_IPV6_STD_ACL:
                        APPEND_RUNNING_CFG_0("access-list ipv6 standard");
                        break;
#endif /* #if (SYS_CPNT_ACL_IPV6 == TRUE) */

#if (SYS_CPNT_DAI == TRUE)
                    case RULE_TYPE_ARP_ACL:
                        APPEND_RUNNING_CFG_0("access-list arp");
                        break;
#endif/*#if (SYS_CPNT_DAI == TRUE)*/

                    default:
                        continue;
                        break;
                }

                APPEND_RUNNING_CFG_1(" %s\n", acl_name);
            }

            ace_index = 0;

            while(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == L4_PMGR_ACL_GetNextRunningUIAceByAcl(acl_index,
                                                                                           &ace_index,
                                                                                           &ui_ace))
            {
                char  local_format_str[L_INET_MAX_IPADDR_STR_LEN+1] = {0}; /* cache for sprintf */
                char  local_buf[CLI_DEF_MAX_BUFSIZE] = {0}; /* cache per ace string */
                UI32_T ace_action;

                ace_action = ui_ace.access;
                switch (ace_action)
                {
                    case RULE_TYPE_ACE_PERMIT:
                        CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, " permit");
                        break;

                    case RULE_TYPE_ACE_DENY:
                        CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, " deny");
                        break;

                    default:
                        break;
                }

                switch ( acl_entry.acl_type )
                {
                    case RULE_TYPE_IP_STD_ACL:
                        CLI_ACL_ConvertIpv4Addr2UIString(ui_ace.ipv4.sip.addr,
                                                         ui_ace.ipv4.sip.mask,
                                                         local_format_str);
                        CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                        break;

                    case RULE_TYPE_IP_EXT_ACL:
#if (SYS_CPNT_ACL_IP_PLUS_VID == TRUE)
                        if (ui_ace.ipv4.vid.op == VAL_diffServMacAceVidOp_equal)
                        {
                            SYSFUN_Sprintf(local_format_str, " MAC VID %lu",
                                           (unsigned long)ui_ace.ipv4.vid.u.s.data);
                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                            if (ui_ace.ipv4.vid.u.s.mask != MAX_diffServMacAceVidBitmask)
                            {
                                SYSFUN_Sprintf(local_format_str, " %lu",
                                               (unsigned long)ui_ace.ipv4.vid.u.s.mask);
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                            }
                        }
#endif /* #if (SYS_CPNT_ACL_IP_PLUS_VID == TRUE) */
                        if (ui_ace.ipv4.protocol.op == RULE_TYPE_IPV4_PROTOCOL_OP_EQUAL)
                        {
                            switch (ui_ace.ipv4.protocol.u.s.data)
                            {
                                case RULE_TYPE_ACL_TCP_PROTOCOL:
                                    CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, " TCP");
                                    break;
                                case RULE_TYPE_ACL_UDP_PROTOCOL:
                                    CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, " UDP");
                                    break;
#if (SYS_CPNT_ACL_IP_EXT_ICMP == TRUE)
                                case RULE_TYPE_ACL_ICMP_PROTOCOL:
                                    CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, " ICMP");
                                    break;
#endif
                                default:
                                    CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, " protocol");
                                    SYSFUN_Sprintf(local_format_str," %u",
                                                   ui_ace.ipv4.protocol.u.s.data);
                                    CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                                    break;
                            }
                        }

                        CLI_ACL_ConvertIpv4Addr2UIString(ui_ace.ipv4.sip.addr,
                                                         ui_ace.ipv4.sip.mask,
                                                         local_format_str);
                        CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                        CLI_ACL_ConvertIpv4Addr2UIString(ui_ace.ipv4.dip.addr,
                                                         ui_ace.ipv4.dip.mask,
                                                         local_format_str);
                        CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                        switch (ui_ace.ipv4.dscp.op)
                        {
                            case RULE_TYPE_IPV4_DSCP_OP_DSCP:
                                SYSFUN_Sprintf(local_format_str, " DSCP %u",
                                               ui_ace.ipv4.dscp.u.ds);
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                                break;

                            case RULE_TYPE_IPV4_DSCP_OP_PRECEDENCE:
                                SYSFUN_Sprintf(local_format_str," precedence %u",
                                               ui_ace.ipv4.dscp.u.tos.precedence);
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                                break;

                            case RULE_TYPE_IPV4_DSCP_OP_TOS:
                                SYSFUN_Sprintf(local_format_str," tos %u",
                                               ui_ace.ipv4.dscp.u.tos.tos);
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                                break;

                            case RULE_TYPE_IPV4_DSCP_OP_PRECEDENCE_AND_TOS:
                                SYSFUN_Sprintf(local_format_str," precedence %u tos %u",
                                               ui_ace.ipv4.dscp.u.tos.precedence, ui_ace.ipv4.dscp.u.tos.tos);
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                                break;

                            case RULE_TYPE_IPV4_DSCP_OP_NO_OPERATION:
                                break;

                            default:
                                ASSERT(0);
                                break;
                        }

                        if (ui_ace.l4_common.sport.op == VAL_diffServIpAceSourcePortOp_equal)
                        {
                            SYSFUN_Sprintf(local_format_str, " source-port %lu",
                                           (unsigned long)ui_ace.l4_common.sport.u.s.data);
                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                            if (ui_ace.l4_common.sport.u.s.mask != MAX_diffServIpAceSourcePortBitmask)
                            {
                                SYSFUN_Sprintf(local_format_str, " %lu",
                                               (unsigned long)ui_ace.l4_common.sport.u.s.mask);
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                            }
                        }

                        if (ui_ace.l4_common.dport.op == VAL_diffServIpAceDestPortOp_equal)
                        {
                            SYSFUN_Sprintf(local_format_str, " destination-port %lu",
                                           (unsigned long)ui_ace.l4_common.dport.u.s.data);
                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                            if (ui_ace.l4_common.dport.u.s.mask != MAX_diffServIpAceDestPortBitmask)
                            {
                                SYSFUN_Sprintf(local_format_str, " %lu",
                                               (unsigned long)ui_ace.l4_common.dport.u.s.mask);
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                            }
                        }

#if (SYS_CPNT_ACL_IP_EXT_ICMP == TRUE)
                        if (ui_ace.icmp.icmp_type.op == RULE_TYPE_ICMP_ICMPTYPE_OP_EQUAL)
                        {
                            SYSFUN_Sprintf(local_format_str, " icmp-type %u",
                                           ui_ace.icmp.icmp_type.u.s.data);
                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                        }
#endif

                        if (ui_ace.tcp.flags.mask.u.code != MIN_diffServIpAceControlCodeBitmask)
                        {
                            SYSFUN_Sprintf(local_format_str, " control-flag %u",
                                           ui_ace.tcp.flags.data.u.code);
                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                            if (ui_ace.tcp.flags.mask.u.code != MAX_diffServIpAceControlCodeBitmask)
                            {
                                SYSFUN_Sprintf(local_format_str," %u",
                                               ui_ace.tcp.flags.mask.u.code);
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                            }
                        }
                        break;

                    case RULE_TYPE_MAC_ACL:
                        switch (ui_ace.pkt_format)
                        {
                            case VAL_diffServMacAcePktformat_untagged_Eth2:
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf," untagged-eth2");
                                break;
                            case VAL_diffServMacAcePktformat_untagged802Dot3:
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf," untagged-802.3");
                                break;
                            case VAL_diffServMacAcePktformat_tagggedEth2:
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf," tagged-eth2");
                                break;
                            case VAL_diffServMacAcePktformat_tagged802Dot3:
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf," tagged-802.3");
                                break;

                            case VAL_diffServMacAcePktformat_any:
                                break;

                            default:
                                ASSERT(0);
                                break;
                        }

                        memset(local_format_str, 0, sizeof(local_format_str));
                        CLI_ACL_Check_AnyMAC(ui_ace.ether.sa.addr,
                                             ui_ace.ether.sa.mask,
                                             local_format_str);
                        CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                        memset(local_format_str, 0, sizeof(local_format_str));
                        CLI_ACL_Check_AnyMAC(ui_ace.ether.da.addr,
                                             ui_ace.ether.da.mask,
                                             local_format_str);
                        CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                        if (ui_ace.ether.vid.op == VAL_diffServMacAceVidOp_equal)
                        {
                            SYSFUN_Sprintf(local_format_str, " VID %lu",
                                           (unsigned long)ui_ace.ether.vid.u.s.data);
                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                            if (ui_ace.ether.vid.u.s.mask != MAX_diffServMacAceVidBitmask)
                            {
                                SYSFUN_Sprintf(local_format_str, " %lu",
                                               (unsigned long)ui_ace.ether.vid.u.s.mask);
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                            }
                        }

                        /* ethertype | ip | ipv6
                         */
                        if (ui_ace.ether.ethertype.op == VAL_diffServMacAceEtherTypeOp_equal)
                        {
                            if (ui_ace.ether.ethertype.u.s.mask == MAX_diffServMacAceEtherTypeBitmask)
                            {
#if (SYS_CPNT_ACL_MAC_IP_MIX == TRUE)
                                RULE_TYPE_UI_Ace_Entry_T default_ui_ace;

                                L4_PMGR_ACL_InitUIAce(&default_ui_ace);

                                if(0 != memcmp(&ui_ace.ipv4, &default_ui_ace.ipv4, sizeof(ui_ace.ipv4)) ||
                                   0 != memcmp(&ui_ace.ipv6, &default_ui_ace.ipv6, sizeof(ui_ace.ipv6)) ||
                                   0 != memcmp(&ui_ace.l4_common, &default_ui_ace.l4_common, sizeof(ui_ace.l4_common)))
                                {
                                    switch (ui_ace.ether.ethertype.u.s.data)
                                    {
                                        case RULE_TYPE_ETHERTYPE_IP:
                                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, " ip");

                                            CLI_ACL_ConvertIpv4Addr2UIString(ui_ace.ipv4.sip.addr,
                                                                             ui_ace.ipv4.sip.mask,
                                                                             local_format_str);
                                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                                            CLI_ACL_ConvertIpv4Addr2UIString(ui_ace.ipv4.dip.addr,
                                                                             ui_ace.ipv4.dip.mask,
                                                                             local_format_str);
                                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                                            if (ui_ace.ipv4.protocol.op == RULE_TYPE_IPV4_PROTOCOL_OP_EQUAL)
                                            {
                                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, " protocol");
                                                SYSFUN_Sprintf(local_format_str," %u", ui_ace.ipv4.protocol.u.s.data);
                                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                                            }
                                            break;

                                        case RULE_TYPE_ETHERTYPE_IPV6:
                                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, " ipv6");

                                            CLI_ACL_Check_AnyIPV6(local_format_str,
                                                                  ui_ace.ipv6.sip.addr,
                                                                  ui_ace.ipv6.sip.prefix_len);
                                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                                            CLI_ACL_Check_AnyIPV6(local_format_str,
                                                                  ui_ace.ipv6.dip.addr,
                                                                  ui_ace.ipv6.dip.prefix_len);
                                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                                            memset(local_format_str, 0, sizeof(local_format_str));
                                            if (ui_ace.ipv6.next_header.op == RULE_TYPE_IPV6_NEXT_HEADER_OP_EQUAL)
                                            {
                                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, " protocol");
                                                SYSFUN_Sprintf(local_format_str," %u",
                                                               ui_ace.ipv6.next_header.u.s.data);
                                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                                            }
                                            break;

                                        default:
                                            ASSERT(0);
                                            break;
                                    }

                                    if (ui_ace.l4_common.sport.op == VAL_diffServIpAceSourcePortOp_equal)
                                    {
                                        SYSFUN_Sprintf(local_format_str, " l4-source-port %lu",
                                                       ui_ace.l4_common.sport.u.s.data);
                                        CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                                        if (ui_ace.l4_common.sport.u.s.mask != MAX_diffServIpAceSourcePortBitmask )
                                        {
                                            sprintf(local_format_str," %lu",
                                                    ui_ace.l4_common.sport.u.s.mask);
                                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                                        }
                                    }

                                    if (ui_ace.l4_common.dport.op == VAL_diffServIpAceDestPortOp_equal)
                                    {
                                        SYSFUN_Sprintf(local_format_str, " l4-destination-port %lu",
                                                       ui_ace.l4_common.dport.u.s.data);
                                        CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                                        if (ui_ace.l4_common.dport.u.s.mask != MAX_diffServIpAceDestPortBitmask )
                                        {
                                            sprintf(local_format_str," %lu",
                                                    ui_ace.l4_common.dport.u.s.mask);
                                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                                        }
                                    }
                                }
                                else
#endif /* SYS_CPNT_ACL_MAC_IP_MIX */
                                {
                                    SYSFUN_Sprintf(local_format_str," ethertype %04lx",
                                                   (long)ui_ace.ether.ethertype.u.s.data);
                                    CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                                }
                            }
                            else
                            {
                                SYSFUN_Sprintf(local_format_str," ethertype %04lx %04lx",
                                               (long)ui_ace.ether.ethertype.u.s.data,
                                               (long)ui_ace.ether.ethertype.u.s.mask);
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                            }
                        }
                        break;

#if (SYS_CPNT_ACL_IPV6 == TRUE)
                    case RULE_TYPE_IPV6_STD_ACL:
                        memset(local_format_str, 0, sizeof(local_format_str));
                        CLI_ACL_Check_AnyIPV6(local_format_str,
                                              ui_ace.ipv6.sip.addr,
                                              ui_ace.ipv6.sip.prefix_len);
                        CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                        break;

                    case RULE_TYPE_IPV6_EXT_ACL:
                        /*next-header*/
#if (SYS_CPNT_ACL_IPV6_EXT_NEXT_HEADER_NEW_FORMAT == TRUE)
                        if (ui_ace.ipv6.next_header.op == RULE_TYPE_IPV6_NEXT_HEADER_OP_EQUAL)
                        {
                            switch (ui_ace.ipv6.next_header.u.s.data)
                            {
                                case RULE_TYPE_ACL_IPV6_TCP_NEXT_HEADER:
                                    CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, " TCP");
                                    break;
                                case RULE_TYPE_ACL_IPV6_UDP_NEXT_HEADER:
                                    CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, " UDP");
                                    break;
#if (SYS_CPNT_ACL_IPV6_EXT_ICMP == TRUE)
                                case RULE_TYPE_ACL_IPV6_ICMP_NEXT_HEADER:
                                    CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, " ICMP");
                                    break;
#endif
                                default:
                                    SYSFUN_Sprintf(local_format_str," %u",
                                                   ui_ace.ipv6.next_header.u.s.data);
                                    CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                                    break;
                            }
                        }
#endif /*#if (SYS_CPNT_ACL_IPV6_EXT_NEXT_HEADER_NEW_FORMAT == TRUE)*/

#if (SYS_CPNT_ACL_IPV6_EXT_SRC_IP_ADDR == TRUE)
                        memset(local_format_str, 0, sizeof(local_format_str));
                        CLI_ACL_Check_AnyIPV6(local_format_str,
                                              ui_ace.ipv6.sip.addr,
                                              ui_ace.ipv6.sip.prefix_len);
                        CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
#endif /* SYS_CPNT_ACL_IPV6_EXT_SRC_IP_ADDR */

#if (SYS_CPNT_ACL_IPV6_EXT_DST_IP_ADDR == TRUE)
                        memset(local_format_str, 0, sizeof(local_format_str));
                        CLI_ACL_Check_AnyIPV6(local_format_str,
                                              ui_ace.ipv6.dip.addr,
                                              ui_ace.ipv6.dip.prefix_len);
                        CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
#endif /* SYS_CPNT_ACL_IPV6_EXT_DST_IP_ADDR */

#if (SYS_CPNT_ACL_IPV6_EXT_NEXT_HEADER == TRUE)
                        if (ui_ace.ipv6.next_header.op == RULE_TYPE_IPV6_NEXT_HEADER_OP_EQUAL)
                        {
                            SYSFUN_Sprintf(local_format_str," next-header %u",
                                            ui_ace.ipv6.next_header.u.s.data);
                            CLI_RUNCFG_ACL_PRIV_STRCAT (local_buf, local_format_str);
                        }
#endif

                        if (ui_ace.ipv6.traffic_class.op == RULE_TYPE_IPV6_TRAFFIC_CLASS_OP_EQUAL)
                        {
                            /* traffic class is DS(6 bits) + ignore(2 bits)
                             */
                            SYSFUN_Sprintf(local_format_str," DSCP %u",
                                            ui_ace.ipv6.traffic_class.u.s.data >> 2);
                            CLI_RUNCFG_ACL_PRIV_STRCAT (local_buf, local_format_str);
                        }

                        if (ui_ace.ipv6.flow_label.op == RULE_TYPE_IPV6_FLOW_LABEL_OP_EQUAL)
                        {
                            SYSFUN_Sprintf(local_format_str," flow-label %lu",
                                           (unsigned long)ui_ace.ipv6.flow_label.u.s.data);
                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                        }

#if (SYS_CPNT_ACL_IPV6_EXT_TCP_UDP_PORT == TRUE)
                        if (ui_ace.l4_common.sport.op == VAL_diffServIpAceSourcePortOp_equal)
                        {
                            SYSFUN_Sprintf(local_format_str, " source-port %lu",
                                           (unsigned long)ui_ace.l4_common.sport.u.s.data);
                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                            if (ui_ace.l4_common.sport.u.s.mask != MAX_diffServIpAceSourcePortBitmask)
                            {
                                SYSFUN_Sprintf(local_format_str, " %lu",
                                               (unsigned long)ui_ace.l4_common.sport.u.s.mask);
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                            }
                        }

                        if (ui_ace.l4_common.dport.op == VAL_diffServIpAceDestPortOp_equal)
                        {
                            SYSFUN_Sprintf(local_format_str, " destination-port %lu",
                                           (unsigned long)ui_ace.l4_common.dport.u.s.data);
                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                            if (ui_ace.l4_common.dport.u.s.mask != MAX_diffServIpAceDestPortBitmask)
                            {
                                SYSFUN_Sprintf(local_format_str, " %lu",
                                               (unsigned long)ui_ace.l4_common.dport.u.s.mask);
                                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                            }
                        }
#endif

#if (SYS_CPNT_ACL_IPV6_EXT_ICMP == TRUE)
                        if (ui_ace.icmp.icmp_type.op == RULE_TYPE_ICMP_ICMPTYPE_OP_EQUAL)
                        {
                            SYSFUN_Sprintf(local_format_str, " icmp-type %u",
                                           ui_ace.icmp.icmp_type.u.s.data);
                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                        }
#endif
                        break;
#endif /* #if (SYS_CPNT_ACL_IPV6 == TRUE) */

#if (SYS_CPNT_DAI == TRUE)
                    case RULE_TYPE_ARP_ACL:
                        switch (ui_ace.arp.arp_type)
                        {
                            case RULE_TYPE_ARP_REQUEST:
                                CLI_RUNCFG_ACL_PRIV_STRCAT (local_buf," request");
                                break;
                            case RULE_TYPE_ARP_REPLY:
                                CLI_RUNCFG_ACL_PRIV_STRCAT (local_buf," response");
                                break;
                            default:
                                break;
                        }

                        CLI_RUNCFG_ACL_PRIV_STRCAT (local_buf," ip");

                        CLI_ACL_ConvertIpv4Addr2UIString(ui_ace.arp.sender.ip.addr,
                                                         ui_ace.arp.sender.ip.mask,
                                                         local_format_str);
                        CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);

                        if (ui_ace.arp.arp_type == RULE_TYPE_ARP_REPLY)
                        {
                            CLI_ACL_ConvertIpv4Addr2UIString(ui_ace.arp.target.ip.addr,
                                                             ui_ace.arp.target.ip.mask,
                                                             local_format_str);
                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                        }

                        CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf," mac");

                        memset (local_format_str, 0, sizeof(local_format_str));
                        CLI_ACL_Check_AnyMAC (ui_ace.arp.sender.mac.addr,
                                              ui_ace.arp.sender.mac.mask,
                                              local_format_str);
                        CLI_RUNCFG_ACL_PRIV_STRCAT (local_buf, local_format_str);

                        if (ui_ace.arp.arp_type == RULE_TYPE_ARP_REPLY)
                        {
                            memset (local_format_str, 0, sizeof(local_format_str));
                            CLI_ACL_Check_AnyMAC(ui_ace.arp.target.mac.addr,
                                                 ui_ace.arp.target.mac.mask,
                                                 local_format_str);
                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, local_format_str);
                        }

                        if (ui_ace.arp.is_log == TRUE)
                        {
                            CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf," log");
                        }

                        break;
#endif/*#if (SYS_CPNT_DAI == TRUE)*/
                    default:
                        break;
                }

#if (SYS_CPNT_TIME_BASED_ACL == TRUE)
                if (RULE_TYPE_UNDEF_TIME_RANGE != ui_ace.time_range_index)
                {
                    enum
                    {
                        extra_time_range_string_size = sizeof("time-range ") + 1
                    };

                    char time_range_string[SYS_ADPT_MAX_LENGTH_OF_TIME_ACL_TABLE_NAME+extra_time_range_string_size] = {0};
                    char time_range_name[SYS_ADPT_MAX_LENGTH_OF_TIME_ACL_TABLE_NAME+1] = {0};

                    L4_PMGR_GetTimeRangeNameByID(ui_ace.time_range_index,
                                                 time_range_name);
                    SYSFUN_Sprintf(time_range_string, " time-range %s", time_range_name);
                    CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, time_range_string);
                }
#endif /* #if (SYS_CPNT_TIME_BASED_ACL == TRUE) */
                CLI_RUNCFG_ACL_PRIV_STRCAT(local_buf, "\n");
                APPEND_RUNNING_CFG_0(local_buf);
            }/* ace */
            APPEND_RUNNING_CFG_0("!\n");
        }/* acl */
    }/* for loop of acl type */

#undef CLI_RUNCFG_ACL_PRIV_STRCAT
    return buffer_count;
}

#if (SYS_CPNT_ACL_UI == TRUE && SYS_CPNT_QOS_V2_ALL_PORTS == TRUE)
static UI32_T CLI_RUNCFG_Get_Access_Group_Global_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                                           UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;

    UI32_T ifindex = RULE_TYPE_ALL_PORTS_1_IF_INDEX_NUMBER;

    buffer_count = CLI_RUNCFG_Get_Access_Group_Parameter_By_Ifindex(ifindex,
                                                                    buffer,
                                                                    temp_buffer,
                                                                    buffer_size,
                                                                    buffer_count);
    return buffer_count;
}
#endif /* SYS_CPNT_QOS_V2_ALL_PORTS  */

static UI32_T CLI_RUNCFG_Get_Access_Group_Parameter_By_Ifindex(UI32_T ifindex, char *buffer, char *temp_buffer,
                                                               UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;

#if (SYS_CPNT_ACL_UI == TRUE && SYS_CPNT_QOS_V2 == TRUE)
    RULE_TYPE_UI_AclEntry_T acl_entry;
    UI32_T                  acl_index =0;
    UI32_T                  precedence = 0;
    RULE_TYPE_InOutDirection_T inout_profile;
    RULE_TYPE_COUNTER_ENABLE_T counter_enable;
    UI16_T                  time_range_index;

    for (inout_profile = RULE_TYPE_INBOUND;
         inout_profile <= RULE_TYPE_OUTBOUND;
         inout_profile++)
    {
        memset (&acl_entry, 0, sizeof (RULE_TYPE_UI_AclEntry_T));

        acl_index = 0;
        precedence = 0;

        while ( L4_PMGR_ACL_GetNextRunningAclByPort(ifindex, inout_profile,
                                                    &acl_index,
                                                    &acl_entry,
                                                    &precedence,
                                                    &time_range_index,
                                                    &counter_enable) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS )
        {
            if ( ( acl_entry.acl_type == RULE_TYPE_IP_STD_ACL ) ||
                 ( acl_entry.acl_type == RULE_TYPE_IP_EXT_ACL ) )
            {
                APPEND_RUNNING_CFG_1(" ip access-group %s", acl_entry.acl_name);
            }

            if ( acl_entry.acl_type == RULE_TYPE_MAC_ACL )
            {
                APPEND_RUNNING_CFG_1(" mac access-group %s", acl_entry.acl_name);
            }

#if (SYS_CPNT_ACL_IPV6 == TRUE)
            if ( ( acl_entry.acl_type == RULE_TYPE_IPV6_STD_ACL ) ||
                 ( acl_entry.acl_type == RULE_TYPE_IPV6_EXT_ACL ) )
            {
                APPEND_RUNNING_CFG_1(" ipv6 access-group %s", acl_entry.acl_name);
            }
#endif

            if (RULE_TYPE_INBOUND == inout_profile)
            {
                APPEND_RUNNING_CFG_0(" in");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" out");
            }

#if (SYS_CPNT_TIME_BASED_ACL == TRUE)

            /* get time range name */
            if ( RULE_TYPE_UNDEF_TIME_RANGE != time_range_index )
            {
                char time_range_name[SYS_ADPT_MAX_LENGTH_OF_TIME_ACL_TABLE_NAME + 1] = {0};

                L4_PMGR_GetTimeRangeNameByID(time_range_index, time_range_name);

                APPEND_RUNNING_CFG_1(" time-range %s", time_range_name);
            }
#endif /*#if (SYS_CPNT_TIME_BASED_ACL == TRUE)*/

#if (SYS_CPNT_ACL_COUNTER == TRUE)
            if (RULE_TYPE_COUNTER_ENABLE == counter_enable)
            {
                APPEND_RUNNING_CFG_0(" counter");
            }
#endif /* #if (SYS_CPNT_ACL_COUNTER == TRUE) */

            APPEND_RUNNING_CFG_0("\n");

        }
    } /* for each direction */
#endif /* SYS_CPNT_ACL_UI && SYS_CPNT_QOS_V2 */

    return buffer_count;
}
#endif /* #if (SYS_CPNT_QOS_V2 == TRUE) */
#endif /* #if (SYS_CPNT_ACL_UI == TRUE)  */

#if (SYS_CPNT_STACKING == TRUE)
static UI32_T CLI_RUNCFG_Get_Stacking_UnitMAC(UI32_T unit_id, char *buffer, char *temp_buffer,
                                              UI32_T buffer_size, UI32_T b_count)
{
   UI32_T buffer_count = b_count;
   UI32_T next_unit_id;
   UI8_T  unit_mac[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK][6] = {{0}};

#if 1
  /*
   UI8_T  per_unit_id;
   if (STKTPLG_MGR_GetMasterUnitId(&per_unit_id) != TRUE)
   {
      return buffer_count;
   }
   next_unit_id = per_unit_id;

   do
   {
      UI8_T mac_unit_id = next_unit_id;
      STKTPLG_MGR_GetUnitBaseMac(mac_unit_id, unit_mac[mac_unit_id-1]);
   }while( STKTPLG_MGR_GetNextUnit(&next_unit_id) == TRUE); */
   next_unit_id = 0;
   while( STKTPLG_POM_GetNextUnit(&next_unit_id) == TRUE)
   {
        UI8_T mac_unit_id = next_unit_id;
        STKTPLG_POM_GetUnitBaseMac(mac_unit_id, unit_mac[mac_unit_id-1]);
   }
#endif

#if 0
   for (i = 0; i<SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK; i++)
   {
      STKTPLG_PMGR_GetUnitBaseMac(i+1, unit_mac[i]);
   }
#endif

#if 0 /*phymap*/
   APPEND_RUNNING_CFG_0("phymap ");
   for (i = 0; i<SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK; i++)
   {
      APPEND_RUNNING_CFG_3("%02x-%02x-%02x-", unit_mac[i][0], unit_mac[i][1], unit_mac[i][2]);
      APPEND_RUNNING_CFG_3("%02x-%02x-%02x ", unit_mac[i][3], unit_mac[i][4], unit_mac[i][5]);
   }
#endif
   APPEND_RUNNING_CFG_0("\n");

   return buffer_count;
}
#endif

#if (SYS_CPNT_INIT_PHASE_PROVISION == TRUE)
static UI32_T CLI_RUNCFG_Get_Init_Phase_Config(UI32_T unit_id, char *buffer, char *temp_buffer,
                                               UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    UI32_T lookup_len;

    APPEND_RUNNING_CFG_0("!---<InitPhaseConfig>\n");

#if (SYS_CPNT_HASH_LOOKUP_DEPTH_CONFIGURABLE == TRUE)
    if (AMTR_PMGR_GetHashLookupDepthFromConfig(&lookup_len) &&
        lookup_len != SYS_DFLT_L2_MAC_TABLE_HASH_LOOKUP_DEPTH)
    {
        APPEND_RUNNING_CFG_1("!---HASH_LOOKUP_DEPTH=%lu\n",lookup_len);
    }
#endif

    APPEND_RUNNING_CFG_0("!---</InitPhaseConfig>\n");

    return buffer_count;
}
#endif

#if (SYS_CPNT_DNS == TRUE)
static UI32_T CLI_RUNCFG_Get_DNS_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
   UI32_T buffer_count = b_count;
   L_INET_AddrIp_T ip;
   char   buff[CLI_DEF_MAX_BUFSIZE+1] = {0};
    char   ip_add_str[L_INET_MAX_IPADDR_STR_LEN+1] = {0};

   {/*ip name-server*/
      memset(&ip, 0, sizeof(ip));

      while (DNS_PMGR_GetNextRunningNameServerList(&ip) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
            if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&ip,
                                                               ip_add_str,
                                                               sizeof(ip_add_str)))
            {
                strcat(buff, "ip name-server ");
                strcat(buff, (char *)ip_add_str);
                APPEND_RUNNING_CFG_0(buff);
                APPEND_RUNNING_CFG_0("\n");
                memset(buff, 0, sizeof(buff));
            }
      }
   }

   {/*ip domain-lookup*/
      UI32_T state;
      if (DNS_PMGR_GetRunningDnsStatus(&state) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         if (state == DNS_ENABLE)
         {
            APPEND_RUNNING_CFG_0("ip domain-lookup\n");
         }
         else
         {
            APPEND_RUNNING_CFG_0("no ip domain-lookup\n");
         }
         APPEND_RUNNING_CFG_0("!\n");
      }
   }

   {/*ip domain-name*/

      char  domain_name[DNS_MAX_NAME_LENGTH + 1] = {0};
      if (DNS_PMGR_GetRunningDnsIpDomain((UI8_T *)domain_name) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {/*need check if string length excreed limit*/
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
         char      buf[CLI_DEF_MAX_BUFSIZE+1];

         CLI_LIB_Str_Add_Quote(domain_name,buf);
         APPEND_RUNNING_CFG_1("ip domain-name %s\n",buf/*domain_name*/);
#else
         APPEND_RUNNING_CFG_1("ip domain-name %s\n",domain_name);
#endif
      }
      APPEND_RUNNING_CFG_0("!\n");
   }


   {/*ip domain-list*/

      char  domain_name[DNS_MAX_NAME_LENGTH + 1] = {0};
      while(DNS_PMGR_GetNextRunningDomainNameList((I8_T *)domain_name) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {/*need check if string length excreed limit*/
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
         char      buf[CLI_DEF_MAX_BUFSIZE+1];

         CLI_LIB_Str_Add_Quote(domain_name,buf);
         APPEND_RUNNING_CFG_1("ip domain-list %s\n",buf/*domain_name*/);
#else
         APPEND_RUNNING_CFG_1("ip domain-list %s\n",domain_name);
#endif
      }
      APPEND_RUNNING_CFG_0("!\n");
   }

   {/*ip host*/
      int host_index;
      int i;
      char  hostname[MAXHOSTNAMELEN + 1 + 1] = {0}; /*maggie liu, another plus 1 is for a space after %s in SYSFUN_Sprintf(hostname, "%s ", buf);*/

    /* 2006/06/28
     * ES4649-38-00189: free memory before return
     */
      HostEntry_T hostentry;

      memset(ip_add_str, 0, sizeof(ip_add_str));
      host_index = -1;

      while( DNS_PMGR_GetNextRunningDnsHostEntry(&host_index, &hostentry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
         char      buf[CLI_DEF_MAX_BUFSIZE+1];

        /*V4 address*/
        {
            BOOL_T v4_addr = FALSE;

#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
         CLI_LIB_Str_Add_Quote((char *)hostentry.hostName[0].name,buf);
         strcat(buff, "ip host ");
         SYSFUN_Sprintf(hostname, "%s ", buf);
#else
         strcat(buff, "ip host ");
         SYSFUN_Sprintf(hostname, "%s ", hostentry.hostName[0].name);
#endif
         strcat(buff, hostname);
         for(i = 0; i < MAXHOSTIPNUM; i++)
         {
                if(hostentry.netAddr[i].addrlen != 0)
            {
                   if(hostentry.netAddr[i].type !=L_INET_ADDR_TYPE_IPV4 )
                   {
                        continue;
                   }

                   v4_addr = TRUE;

               if ((strlen(buff)+16) > CLI_DEF_MAX_BUFSIZE)
               {
                  strcat(buff,"\n");
                  APPEND_RUNNING_CFG_0(buff);
                  memset(buff, 0,sizeof(buff));
                  strcat(buff, "ip host ");
                  strcat(buff, hostname);
               }

               if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&hostentry.netAddr[i],
                                                                   ip_add_str,
                                                                   sizeof(ip_add_str)))
               {
                   strcat(buff, ip_add_str);
                   memset(ip_add_str, 0, sizeof(ip_add_str));
                   strcat(buff," ");
               }
            }
         }
         strcat(buff,"\n");

         if(v4_addr == TRUE)
         {
            APPEND_RUNNING_CFG_0(buff);
         }

         memset(buff, 0,sizeof(buff));
    }

        /*V6 address*/
        {
            BOOL_T v6_addr = FALSE;

#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
             CLI_LIB_Str_Add_Quote(hostentry.hostName[0].name,buf);
             strcat(buff, "ipv6 host ");
             SYSFUN_Sprintf(hostname, "%s ", buf);
#else
             strcat(buff, "ipv6 host ");
             SYSFUN_Sprintf(hostname, "%s ", hostentry.hostName[0].name);
#endif
             strcat(buff, hostname);
             for(i = 0; i < MAXHOSTIPNUM; i++)
             {
                if(hostentry.netAddr[i].addrlen != 0 &&
                  (hostentry.netAddr[i].type == L_INET_ADDR_TYPE_IPV6 ||
                   hostentry.netAddr[i].type == L_INET_ADDR_TYPE_IPV6Z))
                {
                   v6_addr = TRUE;

                   if ((strlen(buff)+16) > CLI_DEF_MAX_BUFSIZE)
                   {
                      strcat(buff,"\n");
                      APPEND_RUNNING_CFG_0(buff);
                      memset(buff, 0,sizeof(buff));
                      strcat(buff, "ipv6 host ");
                      strcat(buff, hostname);
                   }

                   if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&hostentry.netAddr[i],
                                                                       ip_add_str,
                                                                       sizeof(ip_add_str)))
                   {
                       strcat(buff, ip_add_str);
                       memset(ip_add_str, 0, sizeof(ip_add_str));
                       strcat(buff," ");
                   }
                }
             }
             strcat(buff,"\n");

             if(v6_addr == TRUE)
             {
               APPEND_RUNNING_CFG_0(buff);
             }

         memset(buff, 0,sizeof(buff));
        }



#if 0/*not support Alias at present*/
         for(j = 1 ; j < MAXHOSTNAMENUM; j++)
         {
            memset(ip_add_str, 0, sizeof(ip_add_str));
            if(hostentry.hostName[j].name[0]!='\0')
            {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
               char     buf[CLI_DEF_MAX_BUFSIZE+1];
               CLI_LIB_Str_Add_Quote((char *)hostentry.hostName[j].name,buf);
               strcat(buff, "ip host ");
               SYSFUN_Sprintf(hostname, "%s ", buf/*hostentry.hostName[j].name*/);
#else
               strcat(buff, "ip host ");
               SYSFUN_Sprintf(hostname, "%s ", hostentry.hostName[j].name);
#endif
               strcat(buff, hostname);

               if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&hostentry.netAddr[0],
                                                                   ip_add_str,
                                                                   sizeof(ip_add_str)))
               {
                   strcat(buff, ip_add_str);
               }

               strcat(buff,"\n");
               APPEND_RUNNING_CFG_0(buff);
               memset(buff, 0,sizeof(buff));
            }
         }
#endif
      }
   }
   return buffer_count;

}
#endif

#if (SYS_CPNT_MGMT_IP_FLT == TRUE)
static UI32_T CLI_RUNCFG_Get_MGMT_IP_FLT_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
   UI32_T buffer_count = b_count;
   UI32_T mode = 0;
   MGMT_IP_FLT_IpFilter_T ip_filter_entry;
   char  buff[CLI_DEF_MAX_BUFSIZE+1] = {0};
   char  ipadd_start_str[L_INET_MAX_IPADDR_STR_LEN+1] = {0};
   char  ipadd_end_str[L_INET_MAX_IPADDR_STR_LEN+1] = {0};

   memset(&ip_filter_entry, 0, sizeof(ip_filter_entry));
   for (mode = MGMT_IP_FLT_WEB; mode <= MGMT_IP_FLT_TELNET; mode++)
   //for (mode = MGMT_IP_FLT_SNMP; mode <= MGMT_IP_FLT_TELNET; mode++)
   {
      while(MGMT_IP_FLT_GetNextRunningIpFilter(mode, &ip_filter_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
      {
            if (L_INET_RETURN_SUCCESS != L_INET_InaddrToString((L_INET_Addr_T *)&(ip_filter_entry.start_ipaddress),
                                                               ipadd_start_str,
                                                               sizeof(ipadd_start_str)))
            {
                continue;
            }

            if (L_INET_RETURN_SUCCESS != L_INET_InaddrToString((L_INET_Addr_T *)&(ip_filter_entry.end_ipaddress),
                                                               ipadd_end_str,
                                                               sizeof(ipadd_end_str)))
            {
                continue;
            }

         switch(mode)
         {
         case MGMT_IP_FLT_WEB:
            SYSFUN_Sprintf(buff, "management http-client %s %s\n",ipadd_start_str, ipadd_end_str);
            break;

         case MGMT_IP_FLT_SNMP:
            SYSFUN_Sprintf(buff, "management snmp-client %s %s\n",ipadd_start_str, ipadd_end_str);
            break;

         case MGMT_IP_FLT_TELNET:
            SYSFUN_Sprintf(buff, "management telnet-client %s %s\n",ipadd_start_str, ipadd_end_str);
            break;

         default:
            break;
         }
         APPEND_RUNNING_CFG_0(buff);
      }
      memset(&ip_filter_entry, 0, sizeof(ip_filter_entry));
   }
   APPEND_RUNNING_CFG_0("!\n");

   return buffer_count;
}
#endif

#if (SYS_CPNT_DOT1X == TRUE)
static UI32_T CLI_RUNCFG_Get_Dot1x_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T SystemAuthControl_status;
    UI32_T buffer_count = b_count;

    if( DOT1X_POM_GetRunning_SystemAuthControl(&SystemAuthControl_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        switch(SystemAuthControl_status)
        {
            case VAL_dot1xPaeSystemAuthControl_enabled:
                APPEND_RUNNING_CFG_0("dot1x system-auth-control\n");
                break;

            case VAL_dot1xPaeSystemAuthControl_disabled:
                APPEND_RUNNING_CFG_0("no dot1x system-auth-control\n");
                break;

            default:
                break;
        }
  }

  return buffer_count;
}
#endif /* #if (SYS_CPNT_DOT1X == TRUE) */

#if (SYS_CPNT_DOT1X_EAPOL_PASS_THROUGH == TRUE)
static UI32_T CLI_RUNCFG_Get_Dot1xEapolPassThrough_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    UI32_T status;

    if (NETACCESS_PMGR_GetRunningDot1xEapolPassThrough(&status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if (VAL_dot1xEapolPassThrough_enabled == status)
        {
            APPEND_RUNNING_CFG_0("dot1x eapol-pass-through\n");
        }
        else
        {
            APPEND_RUNNING_CFG_0("no dot1x eapol-pass-through\n");
        }
    }

    return buffer_count;
}
#endif /* #if (SYS_CPNT_DOT1X_EAPOL_PASS_THROUGH == TRUE) */

static UI32_T CLI_RUNCFG_Get_FileHeader(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T      buffer_count = b_count;
    UI32_T      i = 0;
    UI8_T       module_type = 0;
    char        stackingDB_str[40] = {0};
    char        module_type_str[4] = {0};
    STKTPLG_MGR_switchModuleInfoEntry_T module_info;

    /*module type*/
    {
        for(i = 1; i<= SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK ; i++)
        {
            module_info.unit_index  = i;
            module_info.module_index  = 1;
            module_type = 0;
            if(STKTPLG_PMGR_GetSwitchModuleInfoEntry(&module_info))
            {
                module_type = module_info.module_type;
                SYSFUN_Sprintf((char *)module_type_str,"%02d",module_type);
                strcat((char *)stackingDB_str,(char *)module_type_str);
            }
            else
            {
                SYSFUN_Sprintf((char *)module_type_str,"%02d",module_type);
                strcat((char *)stackingDB_str,(char *)module_type_str);
            }
        }

        APPEND_RUNNING_CFG_1("!<stackingDB>%s</stackingDB>\n",stackingDB_str);
    }

    /*unit mac*/
    {
        STKTPLG_MGR_StackingDB_T stacking_db[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK];
        UI32_T      i = 0;
        UI32_T      unit_id = 0;
        UI8_T       mac_addr[SYS_ADPT_MAC_ADDR_LEN] = {0};
        UI32_T      device_type = 0;
        char        mac_str[20] = {0};
        char        sub_str[40] = {0};

        memset(stacking_db,0,sizeof(stacking_db));

        STKTPLG_POM_GetCurrentStackingDB(stacking_db);

        for(i=0;i<SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK;i++)
        {
            memset(mac_addr,0,sizeof(mac_addr));
            unit_id = stacking_db[i].unit_id;
            memcpy(mac_addr,stacking_db[i].mac_addr,sizeof(mac_addr));
            device_type = stacking_db[i].device_type;

            CLI_LIB_EAtoStr(mac_addr, mac_str);
            SYSFUN_Sprintf(sub_str,"%02lu_%s_%02lu",(unsigned long)unit_id,mac_str,(unsigned long)device_type);
            APPEND_RUNNING_CFG_1("!<stackingMac>%s</stackingMac>\n",sub_str);
        }
    }

    APPEND_RUNNING_CFG_0("!\n");
    APPEND_RUNNING_CFG_0("\n");

    return buffer_count;
}


/*-----------------------------------------------------------
 * ROUTINE NAME - CLI_RUNCFG_Get_Ethernet_Parameter_For_Module
 *-----------------------------------------------------------
 * FUNCTION: To get global command of ethernet command for module
 * INPUT   : UI32_T unit_id, UI8_T *buffer, char *temp_buffer,
             UI32_T buffer_size, UI32_T b_count, CLI_RUNCFG_ModuleInfo_T module
 * OUTPUT  : None.
 * RETURN  : buffer size
 * NOTE    :
 *----------------------------------------------------------*/

static UI32_T CLI_RUNCFG_Get_Ethernet_Parameter_For_Module(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count, CLI_RUNCFG_ModuleInfo_T module)
{
    /*interface ethernet config for module*/
    UI32_T buffer_count = b_count;
    UI32_T port_id = 0, trunk_id = 0;
    UI32_T max_port_num = 0;

    if (SWCTRL_POM_LogicalPortToUserPort(module.starting_port_ifindex, &unit_id, &port_id, &trunk_id) == SWCTRL_LPORT_UNKNOWN_PORT)
    {
        return buffer_count;
    }

    /*get the max port num for this module*/
    max_port_num = port_id + module.number_of_port - 1;

    for (; port_id <= max_port_num ; port_id++) /*the global loop of interface ethernet for module*/
    {
        /*Action*/
        buffer_count = CLI_RUNCFG_Get_Ethernet_Parameter_One_Port(unit_id, port_id, buffer, temp_buffer,
                                            buffer_size, buffer_count);

        APPEND_RUNNING_CFG_0("!\n");
    }/*end of the global loop of interface ethernet for module*/

#if RUNCFG_DEVELOP
    CLI_LIB_PrintStr("eth config for module complete\r\n");
#endif

    return buffer_count;
}

#if ( SYS_CPNT_UNIT_HOT_SWAP == TRUE )
#if (SYS_CPNT_MSTP_SUPPORT_PVST==TRUE)
/*-----------------------------------------------------------
 * ROUTINE NAME - cli_runcfg_get_vlanDatabaseModule_parameter_macro
 *-----------------------------------------------------------
 * FUNCTION: To get command of vlan database mode for module
 * INPUT   : UI32_T unit_id, UI8_T *buffer, char *temp_buffer,
             UI32_T buffer_size, UI32_T b_count, BOOL_T is_module_only,
             CLI_RUNCFG_ModuleInfo_T module
 * OUTPUT  : None.
 * RETURN  : buffer size
 * NOTE    :
 *----------------------------------------------------------*/
/* 2006/06/28
 * ES4649-38-00189: free memory before return
 */
static UI32_T cli_runcfg_get_vlanDatabaseModule_parameter_macro(UI32_T unit_id, char *buffer, char *temp_buffer,
      UI32_T buffer_size, UI32_T b_count, BOOL_T is_module_only, CLI_RUNCFG_ModuleInfo_T module, char *str_list)
{
   UI32_T buffer_count = b_count;
   /*VLAN database command*/ /*create vlan first*/
   {
      UI32_T time_mark = 0;
      UI32_T vid       = 0;
      UI32_T vlan_type = 0;
      UI8_T vlan_name[16];
      VLAN_TYPE_Vlan_RunningCfg_T vlan_cfg;
      UI32_T unit,port,ifindex;
      UI32_T current_max_unit,max_port_num;
      BOOL_T is_untagged = FALSE;
      BOOL_T is_tagged   = FALSE;
      UI32_T pvid      = 0;
      VLAN_TYPE_Vlan_Port_RunningCfg_T vlan_port_cfg;
      UI8_T untagged_ports_list[SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST]={0};
      UI8_T tagged_ports_list[SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST]={0};
      UI32_T port_id = 0, trunk_id = 0;
      UI32_T i=0;

printf( "CLI:Starting get module vlan config.\r\n" );

      memset (&vlan_cfg,0,sizeof(VLAN_TYPE_Vlan_RunningCfg_T));
      CLI_API_GET_VLAN_DATABASE_VLAN_TYPE(&vlan_type,vlan_name);

      while(VLAN_POM_GetNextVlanId(time_mark, &vid))/*just for get vlan id*/
      {
printf( "CLI:Starting get next vlan ID.\r\n" );
         if (VLAN_POM_GetRunningVlanParameters(vid, &vlan_cfg) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
         {
printf( "CLI:Starting get vlan ID params.\r\n" );

#if (SYS_CPNT_STACKING == TRUE)
            current_max_unit = SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK;
#else
            current_max_unit = 1;
#endif
            memset(untagged_ports_list,0,sizeof(untagged_ports_list));
            memset(tagged_ports_list,0,sizeof(untagged_ports_list));

/*
            if (SWCTRL_POM_LogicalPortToUserPort(module.starting_port_ifindex, &unit_id, &port_id, &trunk_id) == SWCTRL_LPORT_UNKNOWN_PORT)
            {
                return buffer_count;
            }

            unit = unit_id;
            get the max port num for this module
            max_port_num = port_id + module.number_of_port-1;
 */
            max_port_num = SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT;

            for(i=1;i<=current_max_unit;i++)
            {
                unit = i;
            for(port = 1;port <= max_port_num; port++)
            {
                SWCTRL_UIUserPortToLogicalPort(unit,port,&ifindex);
                VLAN_POM_GetRunningVlanPortParameters(ifindex, &vlan_port_cfg);
                VLAN_IFINDEX_CONVERTTO_VID(vlan_port_cfg.pvid_index,pvid);

                /*switchport allowed*/
                if (vlan_cfg.egress_ports_changed == TRUE)
                {
                    if (vlan_cfg.vlan_egress_ports[(UI32_T)((ifindex-1)/8)] & (1 << ( 7 - (( ifindex - 1) % 8) ) ))
                    {
                        if (vlan_cfg.untag_ports_changed == TRUE)
                        {
                            if (vlan_cfg.vlan_untagged_ports[(UI32_T)((ifindex-1)/8)] & (1 << ( 7 - (( ifindex - 1) % 8) ) )) /*untagged*/
                            {
                                is_untagged = TRUE;
                                untagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));

                            }
                            else                                                                                             /*tagged*/
                            {
                                if (pvid != 1 && vid == 1)/*if user have set vlan1 to tag, when provision other command will not take effect, so */
                                                          /*move this commadn to the end of those setting*/
                                {
                                    is_untagged = TRUE;
                                    untagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                    is_tagged = TRUE;
                                    tagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                }
                                else
                                {                /*2002.07.04 pttch prevent that if pvid is tag member, other command will not */
                                    if (pvid == vid)/*take effect in provision, like switchport native vlan x, then produce conflict problem*/
                                    {
#if (SYS_CPNT_VLAN_PROVIDING_DUAL_MODE==FALSE)
                                        is_untagged = TRUE;
                                        untagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
#endif
                                        is_tagged = TRUE;
                                        tagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                     }
                                     else
                                     {
                                         is_tagged = TRUE;
                                         tagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                     }
                                }
                            }
                        }
                        else /*because egress port change ,whatever untagged port changed or not*/
                        {    /* we must show the command*/
                            if (vlan_cfg.vlan_untagged_ports[(UI32_T)((ifindex-1)/8)] & (1 << ( 7 - (( ifindex - 1) % 8) ) )) /*untagged*/
                            {
                                is_untagged = TRUE;
                                untagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                            }
                            else                                                                                                             /*tagged*/
                            {
                                if (pvid != 1 && vid == 1)/*if user have set vlan1 to tag, when provision other command will not take effect, so */
                                                          /*move this commadn to the end of those setting*/
                                {
                                    is_untagged = TRUE;
                                    untagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                    is_tagged = TRUE;
                                    tagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                }
                                else
                                {                /*2002.07.04 pttch prevent that if pvid is tag member, other command will not */
                                    if (pvid == vid)/*take effect in provision, like switchport native vlan x, then produce conflict problem*/
                                    {
                                        is_untagged = TRUE;
                                        untagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                        is_tagged = TRUE;
                                        tagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                    }
                                    else
                                    {
                                        is_tagged = TRUE;
                                        tagged_ports_list[(UI32_T)((ifindex-1)/8)] |= (1 << (7 - ((ifindex-1)%8)));
                                    }
                                }
                            }
                        }
                    }
                }


            }  //end for port loop
        } //end for unit loop

            if (!vlan_cfg.name_changed && vlan_cfg.row_status_changed)
            {
                APPEND_RUNNING_CFG_1("vlan %lu by port\n",(unsigned long)vid);

                /*untagged member add first, tag member must add after untagged command done*/
                {
                    memset( str_list, 0, ( 512*4 ) );

                    if (is_untagged)
                    {
                        CLI_LIB_Portlist_To_Userport(untagged_ports_list,str_list,0);
                        APPEND_RUNNING_CFG_1("%s",str_list);
                    }
                }

                 /*tag member must add after untagged command done*/
                 {
                     memset( str_list, 0, ( 512*4 ) );

                     if (is_tagged)
                     {
                         CLI_LIB_Portlist_To_Userport(tagged_ports_list,str_list,1);
                         APPEND_RUNNING_CFG_1("%s",str_list);
                     }
                 }
                APPEND_RUNNING_CFG_0("!\n");
            }

            if (vlan_cfg.name_changed && vlan_cfg.row_status_changed)
            {
#if (CLI_SUPPORT_QUOTE_STRING_FEATURE == TRUE)
                char      buf[CLI_DEF_MAX_BUFSIZE+1];
                CLI_LIB_Str_Add_Quote(vlan_cfg.vlan_name,buf);
                APPEND_RUNNING_CFG_2("vlan %lu name %s\r\n",(unsigned long)vid,buf);
#else
                APPEND_RUNNING_CFG_2("vlan %lu name %s\r\n",(unsigned long)vid,vlan_cfg.vlan_name);
#endif

                /*untagged member add first, tag member must add after untagged command done*/
                {
                    memset( str_list, 0, ( 512*4 ) );

                    if (is_untagged)
                    {
                        CLI_LIB_Portlist_To_Userport(untagged_ports_list,str_list,0);
                        APPEND_RUNNING_CFG_1("%s",str_list);
                    }
                }

                 /*tag member must add after untagged command done*/
                 {
                     memset( str_list, 0, ( 512*4 ) );

                     if (is_tagged)
                     {
                         CLI_LIB_Portlist_To_Userport(tagged_ports_list,str_list,1);
                         APPEND_RUNNING_CFG_1("%s",str_list);
                     }
                 }
                APPEND_RUNNING_CFG_0("!\n");
            }
        }  //end VLAN_POM_GetRunningVlanParameters

      }  //end while loop

      APPEND_RUNNING_CFG_0("!\n");
      APPEND_RUNNING_CFG_0("!\n");
   }/*end of vlan database*/
#if RUNCFG_DEVELOP
   CLI_LIB_PrintStr("create VLAN complete\r\n");
#endif

   APPEND_RUNNING_CFG_0("!\n");
   APPEND_RUNNING_CFG_0("!\n");

   return buffer_count;

}

static UI32_T CLI_RUNCFG_Get_VlanDatabaseModule_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count, BOOL_T is_module_only, CLI_RUNCFG_ModuleInfo_T module)
{
    char    *str_list;
    UI32_T   return_value;

    if( (str_list = calloc(512*4, sizeof(char))) == NULL )
    {               /*why allocate this number, because vlan list string may be too large*/
                    /*so allocate such big memory to store this string*/
        return CLII_ERR_MEMORY_NOT_ENOUGH;
    }

    /* 2006/06/28
     * ES4649-38-00189: free memory before return
     */
    return_value = cli_runcfg_get_vlanDatabaseModule_parameter_macro(unit_id, buffer, temp_buffer, buffer_size,
                      b_count, str_list);

    free( str_list );

    return return_value;
}
#endif

#endif

/*-----------------------------------------------------------
 * ROUTINE NAME - CLI_RUNCFG_Get_GlobalModule_Parameter
 *-----------------------------------------------------------
 * FUNCTION: To get global command of interface command for module
 * INPUT   : UI32_T unit_id, char *buffer, char *temp_buffer,
             UI32_T buffer_size, UI32_T b_count, BOOL_T is_module_only, CLI_RUNCFG_ModuleInfo_T module
 * OUTPUT  : None.
 * RETURN  : buffer size
 * NOTE    : mac-address-table, ip igmp snooping vlan ...
 *----------------------------------------------------------*/
static UI32_T CLI_RUNCFG_Get_GlobalModule_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count, BOOL_T is_module_only, CLI_RUNCFG_ModuleInfo_T module)
{
   UI32_T buffer_count = b_count;

/*mac-address-table*/
#if (SYS_CPNT_AMTR == TRUE)
   {
       AMTR_TYPE_AddrEntry_T addr_entry;
       UI32_T unit  = 0;
       UI32_T port  = 0;
       UI32_T trunk = 0;
       memset(&addr_entry,0,sizeof(AMTR_TYPE_AddrEntry_T));
       while (AMTR_PMGR_GetNextRunningStaticAddrEntry(&addr_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
       {
          /*if not the module ports, continue get next*/
          if (addr_entry.ifindex < module.starting_port_ifindex || addr_entry.ifindex > (module.starting_port_ifindex+module.number_of_port))
              continue;

          switch(SWCTRL_POM_LogicalPortToUserPort((UI32_T)addr_entry.ifindex,&unit,&port,&trunk))
          {
          case SWCTRL_LPORT_NORMAL_PORT:
             APPEND_RUNNING_CFG_4("mac-address-table static %02x-%02x-%02x-%02x",addr_entry.mac[0],addr_entry.mac[1],addr_entry.mac[2],addr_entry.mac[3]);
             APPEND_RUNNING_CFG_2("-%02x-%02x interface",addr_entry.mac[4],addr_entry.mac[5]);
#if (CLI_SUPPORT_PORT_NAME == 1)
             {
                char name[MAXSIZE_ifName+1] = {0};
                CLI_LIB_Ifindex_To_Name((UI32_T)addr_entry.ifindex,name);
                APPEND_RUNNING_CFG_1(" ethernet %s",name);
             }
#else
             APPEND_RUNNING_CFG_2(" ethernet %lu/%lu ",(unsigned long)unit,(unsigned long)port);
#endif
             APPEND_RUNNING_CFG_1(" vlan %u ",addr_entry.vid);
             APPEND_RUNNING_CFG_1(" %s\n",(addr_entry.life_time== VAL_dot1dStaticStatus_other)?("other"):
                     ((addr_entry.life_time == VAL_dot1dStaticStatus_invalid)?("invalid"):
                     ((addr_entry.life_time == VAL_dot1dStaticStatus_permanent)?("permanent"):
                     (addr_entry.life_time == VAL_dot1dStaticStatus_deleteOnReset)?("delete-on-reset"):("delete-on-timeout"))));
             break;

          case SWCTRL_LPORT_TRUNK_PORT:
          default:
             break;
          }
       }
   }
#endif
/*ipv6 mld snooping vlan*/
#if(SYS_CPNT_MLDSNP==TRUE)
    /*mrouter*/
    {
        UI32_T i ;
        UI32_T vid=0;
        UI32_T time_mark = 0;
        UI8_T  static_router_portlist[SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST] = {0};

        while(VLAN_POM_GetNextVlanId(time_mark, &vid))
        {
            if(MLDSNP_POM_GetRunningRouterPortList(vid, static_router_portlist)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                for(i=module.starting_port_ifindex; i<(module.starting_port_ifindex+module.number_of_port); i++)
                {
                    char  UserPort[20] = {0};
                    UI32_T unit;
                    UI32_T port;
                    UI32_T trunk_id;
                    SWCTRL_Lport_Type_T ret;

                    ret = SWCTRL_POM_LogicalPortToUserPort(i, &unit, &port, &trunk_id);

#if (CLI_SUPPORT_PORT_NAME == 1)
                    {
                        char name[MAXSIZE_ifName+1] = {0};
                        CLI_LIB_Ifindex_To_Name(i,name);
                        switch(ret)
                        {
                            case SWCTRL_LPORT_NORMAL_PORT:
                                SYSFUN_Sprintf(UserPort, "ethernet %s",name);
                                break;

                            case SWCTRL_LPORT_TRUNK_PORT:
                                SYSFUN_Sprintf(UserPort, "port-channel %lu", (unsigned long)trunk_id);
                                break;

                            default:
                                continue;
                        }
                    }
#else
                    switch(ret)
                    {
                        case SWCTRL_LPORT_NORMAL_PORT:
                            SYSFUN_Sprintf(UserPort, "ethernet %lu/%lu", (unsigned long)unit, (unsigned long)port);
                            break;

                        case SWCTRL_LPORT_TRUNK_PORT:
                            SYSFUN_Sprintf(UserPort, "port-channel %lu", (unsigned long)trunk_id);
                            break;

                        default:
                            continue;
                    }
#endif
                    if(static_router_portlist[(UI32_T)((i-1)/8)]  & (1 << (7 - ((i-1) % 8))) )
                    {
                        APPEND_RUNNING_CFG_2(" ipv6 mld snooping vlan %lu mrouter %s\n", (unsigned long)vid, UserPort);
                    }
                }
            }
        }
    }

    /*static*/
    {
        MLDSNP_TYPE_RecordType_T rec_type;
        UI16_T vid = 0, nxt_id=0, join_port=0;
        char   ipv6_group_addr_str[L_INET_MAX_IP6ADDR_STR_LEN+1], ipv6_src_addr_str[L_INET_MAX_IP6ADDR_STR_LEN+1];
        UI8_T group_addr[MLDSNP_TYPE_IPV6_DST_IP_LEN] = {0};
        UI8_T source_addr[MLDSNP_TYPE_IPV6_SRC_IP_LEN]={0};
        UI8_T null_source_addr[MLDSNP_TYPE_IPV6_SRC_IP_LEN]={0};

        while(MLDSNP_POM_GetNextRunningPortStaticGroup(&nxt_id, &vid, group_addr, source_addr, &join_port, &rec_type)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            L_INET_Ntop(L_INET_AF_INET6, (void *)group_addr, ipv6_group_addr_str, sizeof(ipv6_group_addr_str));
            L_INET_Ntop(L_INET_AF_INET6, (void *)source_addr, ipv6_src_addr_str, sizeof(ipv6_src_addr_str));
            {
                char  UserPort[20] = {0};
                UI32_T unit;
                UI32_T port;
                UI32_T trunk_id;
                SWCTRL_Lport_Type_T ret;

                ret = SWCTRL_POM_LogicalPortToUserPort(join_port, &unit, &port, &trunk_id);

#if (CLI_SUPPORT_PORT_NAME == 1)
                {
                    char  name[MAXSIZE_ifName+1] = {0};
                    CLI_LIB_Ifindex_To_Name(i,name);
                    switch(ret)
                    {
                        case SWCTRL_LPORT_NORMAL_PORT:
                            SYSFUN_Sprintf(UserPort, "ethernet %s",name);
                            break;

                        case SWCTRL_LPORT_TRUNK_PORT:
                            SYSFUN_Sprintf(UserPort, "port-channel %lu", (unsigned long)trunk_id);
                            break;

                        default:
                            continue;
                    }
                }
#else
                switch(ret)
                {
                    case SWCTRL_LPORT_NORMAL_PORT:
                        SYSFUN_Sprintf(UserPort, "ethernet %lu/%lu", (unsigned long)unit, (unsigned long)port);
                        break;

                    case SWCTRL_LPORT_TRUNK_PORT:
                        SYSFUN_Sprintf(UserPort, "port-channel %lu", (unsigned long)trunk_id);
                        break;

                    default:
                        continue;
                }
#endif
                if(MLDSNP_TYPE_IS_INCLUDE_MODE==rec_type)
                {
                    APPEND_RUNNING_CFG_4(" ipv6 mld snooping vlan %u static %s %s include-list %s\n", vid, ipv6_group_addr_str, UserPort, ipv6_src_addr_str);
                }
                else if(memcmp(source_addr, null_source_addr, MLDSNP_TYPE_IPV6_SRC_IP_LEN))
                {
                    APPEND_RUNNING_CFG_4(" ipv6 mld snooping vlan %u static %s %s exclude-list %s\n", vid, ipv6_group_addr_str, UserPort, ipv6_src_addr_str);
                }
                else
                {
                    APPEND_RUNNING_CFG_3(" ipv6 mld snooping vlan %u static %s %s\n", vid, ipv6_group_addr_str, UserPort);
                }
            }

        }
    }

/*
    {
        MLDSNP_TYPE_ImmediateStatus_T mld_immediate_leave_status;
        MLDSNP_TYPE_ImmediateByHostStatus_T mld_immediate_leave_byhost_status;
        UI32_T vid=0;

        while(TRUE == VLAN_POM_GetNextVlanId(0, &vid))
        {
            if(MLDSNP_POM_GetRunningImmediateLeaveStatus(vid, &mld_immediate_leave_status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if(mld_immediate_leave_status==MLDSNP_TYPE_IMMEDIATE_ENABLED)
                {
                    APPEND_RUNNING_CFG_1(" ipv6 mld snooping vlan %lu immediate-leave\n", vid);
                }
                else
                {
                    APPEND_RUNNING_CFG_1(" no ipv6 mld snooping vlan %lu immediate-leave\n", vid);
                }
            }
            if(MLDSNP_POM_GetRunningImmediateLeaveByHostStatus(vid, &mld_immediate_leave_byhost_status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if(mld_immediate_leave_byhost_status==MLDSNP_TYPE_IMMEDIATE_BYHOST_ENABLED)
                {
                    APPEND_RUNNING_CFG_1(" ipv6 mld snooping vlan %lu immediate-leave by-host-ip\n", vid);
                }
                else
                {
                    APPEND_RUNNING_CFG_1(" no ipv6 mld snooping vlan %lu immediate-leave by-host-ip\n", vid);
                }
            }
        }
    }
*/

#endif /*End #if(SYS_CPNT_MLDSNP==TRUE)*/

   return buffer_count;
}

/*-----------------------------------------------------------
 * ROUTINE NAME - CLI_RUNCFG_Get_InterfaceModule_Parameter
 *-----------------------------------------------------------
 * FUNCTION: To get inteface related command of module
 * INPUT   : UI32_T unit_id, UI8_T *buffer, char *temp_buffer,
             UI32_T buffer_size, UI32_T b_count, BOOL_T is_module_only, CLI_RUNCFG_ModuleInfo_T module
 * OUTPUT  : None.
 * RETURN  : buffer size
 * NOTE    : port monitor....
 *----------------------------------------------------------*/
static UI32_T CLI_RUNCFG_Get_InterfaceModule_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count, BOOL_T is_module_only, CLI_RUNCFG_ModuleInfo_T module)
{
   UI32_T buffer_count = b_count;
   /* port monitor */
   {
      SWCTRL_MirrorEntry_T mirroring_entry;

      memset(&mirroring_entry , 0 , sizeof(SWCTRL_MirrorEntry_T));

      //pttch //* change to getrunning */
      while (SWCTRL_POM_GetNextMirrorEntry(&mirroring_entry))
      {
         UI32_T unit     = 0;
         UI32_T port     = 0;
         UI32_T trunk_id = 0;
         UI32_T main_unit = 0;
         UI32_T main_port = 0;

         if (mirroring_entry.mirror_source_port < module.starting_port_ifindex || mirroring_entry.mirror_source_port > (module.starting_port_ifindex+module.number_of_port))
             continue;

         SWCTRL_POM_LogicalPortToUserPort(mirroring_entry.mirror_source_port,&unit,&port,&trunk_id);
         SWCTRL_POM_LogicalPortToUserPort(mirroring_entry.mirror_destination_port,&main_unit,&main_port,&trunk_id);
         switch(mirroring_entry.mirror_type)
         {
         case VAL_mirrorType_rx:
            APPEND_RUNNING_CFG_2("!\ninterface ethernet %lu/%lu\n",(unsigned long)main_unit,(unsigned long)main_port);
            APPEND_RUNNING_CFG_2(" port monitor ethernet %lu/%lu rx\n!\n",(unsigned long)unit,(unsigned long)port);
            break;

         case VAL_mirrorType_tx:
            APPEND_RUNNING_CFG_2("!\ninterface ethernet %lu/%lu\n",(unsigned long)main_unit,(unsigned long)main_port);
            APPEND_RUNNING_CFG_2(" port monitor ethernet %lu/%lu tx\n!\n",(unsigned long)unit,(unsigned long)port);
            break;

         case VAL_mirrorType_both:
            APPEND_RUNNING_CFG_2("!\ninterface ethernet %lu/%lu\n",(unsigned long)main_unit,(unsigned long)main_port);
            APPEND_RUNNING_CFG_2(" port monitor ethernet %lu/%lu both\n!\n",(unsigned long)unit,(unsigned long)port);
            break;

         default:
            break;
         }
      }
   }/*end of port monitor*/

   return buffer_count;
}

#if ( SYS_CPNT_UNIT_HOT_SWAP == TRUE )
UI32_T CLI_RUNCFG_Get_DeviceRunningCfg(UI32_T starting_port_ifindex, UI32_T number_of_port, char *buffer, UI32_T buffer_size)
{
    char temp_buffer[CLI_DEF_MAX_BUFSIZE];
    UI32_T runcfg_my_unit_id   = (starting_port_ifindex - 1)/SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT + 1;
    UI32_T buffer_count        = 0;
    CLI_RUNCFG_ModuleInfo_T module;


printf( "CLI:Starting get module config.\r\n" );
    module.starting_port_ifindex = starting_port_ifindex;
    module.number_of_port = number_of_port;

#if (SYS_CPNT_MSTP_SUPPORT_PVST==TRUE)
    buffer_count = CLI_RUNCFG_Get_VlanDatabaseModule_Parameter(runcfg_my_unit_id, buffer, temp_buffer, buffer_size, buffer_count, TRUE, module);
    CHECK_BUFF_RETURN_VALUE(buffer_count);
    APPEND_RUNNING_CFG_0("!\n");
#endif

    buffer_count = CLI_RUNCFG_Get_Ethernet_Parameter_For_Module(runcfg_my_unit_id, buffer, temp_buffer, buffer_size, buffer_count, module);
    CHECK_BUFF_RETURN_VALUE(buffer_count);
    APPEND_RUNNING_CFG_0("!\n");

    buffer_count = CLI_RUNCFG_Get_GlobalModule_Parameter(runcfg_my_unit_id, buffer, temp_buffer, buffer_size, buffer_count, TRUE, module);
    CHECK_BUFF_RETURN_VALUE(buffer_count);
    APPEND_RUNNING_CFG_0("!\n");

    buffer_count = CLI_RUNCFG_Get_InterfaceModule_Parameter(runcfg_my_unit_id, buffer, temp_buffer, buffer_size, buffer_count, TRUE, module);
    CHECK_BUFF_RETURN_VALUE(buffer_count);
    APPEND_RUNNING_CFG_0("!\n");

    return buffer_count;
}
#else
UI32_T CLI_RUNCFG_Get_ModuleRunningCfg(UI32_T starting_port_ifindex, UI32_T number_of_port, char *buffer, UI32_T buffer_size)
{
    I8_T temp_buffer[CLI_DEF_MAX_BUFSIZE];
    UI32_T runcfg_my_unit_id   = (starting_port_ifindex - 1)/SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT + 1;
    UI32_T buffer_count        = 0;
    CLI_RUNCFG_ModuleInfo_T module;

    module.starting_port_ifindex = starting_port_ifindex;
    module.number_of_port = number_of_port;

    buffer_count = CLI_RUNCFG_Get_Ethernet_Parameter_For_Module(runcfg_my_unit_id, buffer, temp_buffer, buffer_size, buffer_count, module);
    CHECK_BUFF_RETURN_VALUE(buffer_count);
    APPEND_RUNNING_CFG_0("!\n");

    buffer_count = CLI_RUNCFG_Get_GlobalModule_Parameter(runcfg_my_unit_id, buffer, temp_buffer, buffer_size, buffer_count, TRUE, module);
    CHECK_BUFF_RETURN_VALUE(buffer_count);
    APPEND_RUNNING_CFG_0("!\n");

    buffer_count = CLI_RUNCFG_Get_InterfaceModule_Parameter(runcfg_my_unit_id, buffer, temp_buffer, buffer_size, buffer_count, TRUE, module);
    CHECK_BUFF_RETURN_VALUE(buffer_count);
    APPEND_RUNNING_CFG_0("!\n");


    return buffer_count;
}
#endif

#if (SYS_CPNT_QOS_UI == TRUE)
#if (SYS_CPNT_QOS == SYS_CPNT_QOS_DIFFSERV)
#if (SYS_CPNT_QOS_V2 == TRUE)
static UI32_T CLI_RUNCFG_Get_Class_Map_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    UI32_T cmap_id = 0;
    UI32_T cmap_eid;

    UI8_T  temp_string1[12] = {0};

    RULE_TYPE_UI_ClassMap_T         cmap;
    RULE_TYPE_UI_ClassMapElement_T  cmap_element;

    while ( L4_PMGR_QoS_GetNextRunningClassMap ( &cmap_id, &cmap ) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS )
    {
        if(cmap.row_status != VAL_diffServClassMapStatus_active)
            continue;

        if( cmap.class_map_match_type == RULE_TYPE_CLASS_MAP_MATCH_ALL)
        {
            SYSFUN_Sprintf((char *)temp_string1, "%s","match-all");
        }
        else
        {
            SYSFUN_Sprintf((char *)temp_string1, "%s","match-any");
        }


        APPEND_RUNNING_CFG_0("!\n");
        APPEND_RUNNING_CFG_2("class-map %s %s\n",cmap.class_map_name, temp_string1);
        if (cmap.desc[0] != 0)
        {
            APPEND_RUNNING_CFG_1(" description \"%s\"\n", cmap.desc);
        }

        cmap_eid = 0;
        while ( L4_PMGR_QoS_GetNextRunningElementFromClassMap ( cmap_id, &cmap_eid, &cmap_element ) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS )
        {
            if (cmap_element.class_type == RULE_TYPE_CLASS_ACL)
            {
                /* acl */
                APPEND_RUNNING_CFG_1(" match access-list %s\n", cmap_element.element.acl_name );
            }
            else
            if(cmap_element.class_type == RULE_TYPE_CLASS_MF)
            {

                switch ( cmap_element.element.mf_entry.mf_type )
                {
                case RULE_TYPE_MF_PRECEDENCE:
                    /* ip precedence */
                    APPEND_RUNNING_CFG_1(" match ip precedence %lu\n", (unsigned long)cmap_element.element.mf_entry.mf_value );
                    break;

                case RULE_TYPE_MF_DSCP:
                    /* ip dscp */
                    APPEND_RUNNING_CFG_1(" match ip dscp %lu\n", (unsigned long)cmap_element.element.mf_entry.mf_value );
                    break;

                case RULE_TYPE_MF_VLAN:
                    /* vlan */
                    APPEND_RUNNING_CFG_1(" match vlan %lu\n", (unsigned long)cmap_element.element.mf_entry.mf_value );
                    break;

                case RULE_TYPE_MF_DSCP_IPV6:
                    /* ipv6 dscp */
                    APPEND_RUNNING_CFG_1(" match ipv6 dscp %lu\n", (unsigned long)cmap_element.element.mf_entry.mf_value );
                    break;

                case RULE_TYPE_MF_COS:
                    APPEND_RUNNING_CFG_1(" match cos %lu\n", (unsigned long)cmap_element.element.mf_entry.mf_value );
                    break;

                case RULE_TYPE_MF_SOURCE_PORT:
                    {
                        UI32_T unit, port, trunk_id;

                        SWCTRL_POM_LogicalPortToUserPort(cmap_element.element.mf_entry.mf_value,
                                                         &unit, &port, &trunk_id);

                        APPEND_RUNNING_CFG_2(" match source-port ethernet %lu/%lu\n", (unsigned long)unit, (unsigned long)port );
                    }
                    break;

                }
            }
        }
    }

    return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_Policy_Map_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;

    UI32_T pmap_id = 0;

    RULE_TYPE_UI_PolicyMap_T        pmap;
    RULE_TYPE_UI_PolicyElement_T    pmap_element;

    while ( L4_PMGR_QoS_GetNextRunningPolicyMap (&pmap_id, &pmap) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS )
    {
        if (pmap.row_status != VAL_diffServPolicyMapStatus_active)
            continue;

        APPEND_RUNNING_CFG_0("!\n");
        APPEND_RUNNING_CFG_1("policy-map %s\n", pmap.name);

        if (pmap.desc[0] != 0)
            APPEND_RUNNING_CFG_1(" description \"%s\"\n", pmap.desc);

        memset ( &pmap_element, 0, sizeof(RULE_TYPE_UI_PolicyElement_T) );
        while ( L4_PMGR_QoS_GetNextRunningElementFromPolicyMap ( pmap_id, &pmap_element ) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS )
        {
            if (pmap_element.row_status != VAL_diffServPolicyMapElementStatus_active)
                continue;

            APPEND_RUNNING_CFG_1(" class %s\n", pmap_element.class_map_name);

            /* get in-profile action */
            switch  ( pmap_element.action_entry.in_action_type )
            {
            case IN_ACTION_NEW_COS:
                APPEND_RUNNING_CFG_1("  set cos %lu\n", (unsigned long)pmap_element.action_entry.in_action_value );
                break;
            case IN_ACTION_NEW_PHB:
                APPEND_RUNNING_CFG_1("  set phb %lu\n", (unsigned long)pmap_element.action_entry.in_action_value );
                break;

            case IN_ACTION_NEW_IP_DSCP:
                APPEND_RUNNING_CFG_1("  set ip dscp %lu\n", (unsigned long)pmap_element.action_entry.in_action_value );
                break;

            case IN_ACTION_NEW_IP_PRECEDENCE:
                APPEND_RUNNING_CFG_1("  set ip precedence %lu\n", (unsigned long)pmap_element.action_entry.in_action_value );
                break;

            default:
                break;
            }

            if (VAL_diffServMeterStatus_active == pmap_element.meter_entry.row_status)
            {
                if(RULE_TYPE_METER_MODE_FLOW == pmap_element.meter_entry.meter_model)
                {
                    APPEND_RUNNING_CFG_2("  police flow %lu %lu",
                                            (unsigned long)pmap_element.meter_entry.rate,
                                            (unsigned long)pmap_element.meter_entry.burst_size);
                }
                else if(RULE_TYPE_METER_MODE_TRTCM_COLOR_BLIND == pmap_element.meter_entry.meter_model)
                {
                    APPEND_RUNNING_CFG_4("  police trtcm-color-blind %lu %lu %lu %lu",
                                            (unsigned long)pmap_element.meter_entry.rate,
                                            (unsigned long)pmap_element.meter_entry.burst_size,
                                            (unsigned long)pmap_element.meter_entry.peak_rate,
                                           (unsigned long) pmap_element.meter_entry.peak_burst_size);
                }
                else if(RULE_TYPE_METER_MODE_TRTCM_COLOR_AWARE== pmap_element.meter_entry.meter_model)
                {
                    APPEND_RUNNING_CFG_4("  police trtcm-color-aware %lu %lu %lu %lu",
                                            (unsigned long)pmap_element.meter_entry.rate,
                                            (unsigned long)pmap_element.meter_entry.burst_size,
                                            (unsigned long)pmap_element.meter_entry.peak_rate,
                                            (unsigned long)pmap_element.meter_entry.peak_burst_size);
                }
                else if(RULE_TYPE_METER_MODE_SRTCM_COLOR_BLIND == pmap_element.meter_entry.meter_model)
                {
                    APPEND_RUNNING_CFG_3("  police srtcm-color-blind %lu %lu %lu",
                                            (unsigned long)pmap_element.meter_entry.rate,
                                            (unsigned long)pmap_element.meter_entry.burst_size,
                                            (unsigned long)pmap_element.meter_entry.peak_burst_size);
                }
                else if(RULE_TYPE_METER_MODE_SRTCM_COLOR_AWARE == pmap_element.meter_entry.meter_model)
                {
                    APPEND_RUNNING_CFG_3("  police srtcm-color-aware %lu %lu %lu",
                                            (unsigned long)pmap_element.meter_entry.rate,
                                            (unsigned long)pmap_element.meter_entry.burst_size,
                                            (unsigned long)pmap_element.meter_entry.peak_burst_size);
                }

                switch( pmap_element.action_entry.confirm_action_type)
                {
                    case CONFIRM_ACTION_TRANSMIT:
                        APPEND_RUNNING_CFG_0(" conform-action transmit");
                        break;

                    case CONFIRM_ACTION_REMARK_DSCP_TRANSMIT:
                        APPEND_RUNNING_CFG_1(" conform-action %lu",
                                               (unsigned long)pmap_element.action_entry.confirm_action_value);
                        break;

                    default:
                        break;
                }

                switch(pmap_element.action_entry.exceed_action_type)
                {
                    case EXCEED_ACTION_DROP:
                        APPEND_RUNNING_CFG_0(" exceed-action drop");
                        break;

                    case EXCEED_ACTION_REMARK_DSCP_TRANSMIT:
                        APPEND_RUNNING_CFG_1(" exceed-action %lu",(unsigned long)pmap_element.action_entry.exceed_action_value);
                        break;

                    default:
                        break;
                }

                switch(pmap_element.action_entry.violate_action_type)
                {
                    case VIOLATE_ACTION_DROP:
                        APPEND_RUNNING_CFG_0(" violate-action drop\n");
                        break;

                    case VIOLATE_ACTION_REMARK_DSCP_TRANSMIT:
                        APPEND_RUNNING_CFG_1(" violate-action %lu\n",(unsigned long)pmap_element.action_entry.violate_action_value);
                        break;

                    default:
                        break;
                }

#if (SYS_CPNT_QOS_V2_SOFTWARE_BUNDLE_RATE_CONTROL == TRUE)
                switch ( pmap_element.action_entry.class_action_type )
                {
                    case CLASS_ACTION_SET_PRIORITY:
                        APPEND_RUNNING_CFG_1("  priority %lu\n", (unsigned long)pmap_element.action_entry.class_action_value);
                        break;

                    case CLASS_ACTION_INVALID:
                    default:
                        break;
                }
#endif /* SYS_CPNT_QOS_V2_SOFTWARE_BUNDLE_RATE_CONTROL */

            } /* end meter config */
            APPEND_RUNNING_CFG_0("  exit\n");
        }

#if (SYS_CPNT_QOS_V2_SOFTWARE_BUNDLE_RATE_CONTROL == TRUE)
        {
            UI32_T  bundle_group_index;
            UI32_T  cnt;

            for (bundle_group_index = 0; bundle_group_index < SYS_ADPT_DIFFSERV_MAX_BUNDLE_GROUP_OF_POLICY_MAP; ++bundle_group_index)
            {
                if (TRUE != pmap.bundle_group[bundle_group_index].valid_status)
                {
                    continue;
                }

                APPEND_RUNNING_CFG_2(" bundle %lu %lu",
                                (unsigned long)pmap.bundle_group[bundle_group_index].index,
                                (unsigned long)pmap.bundle_group[bundle_group_index].bundle_rate_kbps);

                for (cnt = 0; cnt < pmap.bundle_group[bundle_group_index].class_map_count; ++cnt)
                {
                    APPEND_RUNNING_CFG_2("%s%s",
                                    (0 == cnt) ? " " : " ",
                                    pmap.bundle_group[bundle_group_index].class_map_name_list[cnt]);
                }

                APPEND_RUNNING_CFG_0("\n");
            }
        }
#endif /* #if (SYS_CPNT_QOS_V2_SOFTWARE_BUNDLE_RATE_CONTROL == TRUE) */

        APPEND_RUNNING_CFG_0("!\n");
    }

    return buffer_count;
}

#else

static UI32_T CLI_RUNCFG_Get_Class_Map_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
#if 1
    UI32_T map_id = 0;
    L4_TYPE_ClassMapEntry_T rec_p;
    UI8_T  temp_string1[10] = {0};
    UI32_T cme_id_p = 0;
    L4_TYPE_ClassMapElementEntry_T rec;
    L4_TYPE_diffServMultiFieldClfrEntry_T Mentry_p;
    L4_TYPE_diffServAclClfrEntry_T Aentry_p;

    memset(&rec_p, 0, sizeof(L4_TYPE_ClassMapEntry_T));
    memset(&rec, 0, sizeof(L4_TYPE_ClassMapElementEntry_T));
    memset(&Mentry_p, 0, sizeof(L4_TYPE_diffServMultiFieldClfrEntry_T));
    memset(&Aentry_p, 0, sizeof(L4_TYPE_diffServAclClfrEntry_T));

    while(L4_DS_PMGR_GetNextRunningClassMap(&map_id, &rec_p) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if(rec_p.type == L4_TYPE_CLASS_MAP_MATCH_ALL)
        {
            SYSFUN_Sprintf((char *)temp_string1, "%s","match-all");
        }
        else
        {
            SYSFUN_Sprintf((char *)temp_string1, "%s","match-any");
        }


        APPEND_RUNNING_CFG_0("!\n");
        APPEND_RUNNING_CFG_2("class-map %s %s\n",rec_p.name, temp_string1);
        if (rec_p.desc[0] != 0)
        {
            APPEND_RUNNING_CFG_1(" description %s\n",rec_p.desc);
        }
        if(L4_DS_PMGR_GetFirstRunningClassMapElement(map_id, &cme_id_p, &rec) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(rec.specific.table == DS_OM_ACL_CLFR_TABLE)
            {
                /* acl */
                if(L4_DS_PMGR_GetAclClfr(rec.specific.index, &Aentry_p) == TRUE)
                {
                    APPEND_RUNNING_CFG_1(" match access-list %s\n", Aentry_p.name);
                }

                memset(&Aentry_p, 0, sizeof(L4_TYPE_diffServAclClfrEntry_T));
            }
            else if(rec.specific.table == DS_OM_MULTI_FIELD_CLFR_TABLE)
            {
                if(L4_DS_PMGR_GetMultiFieldClfr(rec.specific.index, &Mentry_p) == TRUE)
                {
                    if(Mentry_p.valid_zero & 1)
                    {
                        /* ip dscp */
                        APPEND_RUNNING_CFG_1(" match ip dscp %d\n", Mentry_p.dscp);
                    }
                    else if(Mentry_p.valid_zero & 2)
                    {
                        /* ip precedence */
                        APPEND_RUNNING_CFG_1(" match ip precedence %d\n", Mentry_p.ip_precedence);
                    }
                    else if(Mentry_p.valid_zero & 4)
                    {
                        /* vlan */
                        APPEND_RUNNING_CFG_1(" match vlan %u\n", Mentry_p.vlan_id);
                    }
                }
                memset(&Mentry_p, 0, sizeof(L4_TYPE_diffServMultiFieldClfrEntry_T));
            }

            memset(&rec, 0, sizeof(L4_TYPE_ClassMapElementEntry_T));
            while(L4_DS_PMGR_GetNextClassMapElement(map_id, &cme_id_p, &rec) == TRUE)
            {
                if(rec.specific.table == DS_OM_ACL_CLFR_TABLE)
                {
                    /* acl */
                    if(L4_DS_PMGR_GetAclClfr(rec.specific.index, &Aentry_p) == TRUE)
                    {
                        APPEND_RUNNING_CFG_1(" match access-list %s\n", Aentry_p.name);
                    }

                    memset(&Aentry_p, 0, sizeof(L4_TYPE_diffServAclClfrEntry_T));
                }
                else if(rec.specific.table == DS_OM_MULTI_FIELD_CLFR_TABLE)
                {
                    if(L4_DS_PMGR_GetMultiFieldClfr(rec.specific.index, &Mentry_p) == TRUE)
                    {
                        if(Mentry_p.valid_zero & 1)
                        {
                            /* ip dscp */
                            APPEND_RUNNING_CFG_1(" match ip dscp %d\n", Mentry_p.dscp);
                        }
                        else if(Mentry_p.valid_zero & 2)
                        {
                            /* ip precedence */
                            APPEND_RUNNING_CFG_1(" match ip precedence %d\n", Mentry_p.ip_precedence);
                        }
                    }
                    memset(&Mentry_p, 0, sizeof(L4_TYPE_diffServMultiFieldClfrEntry_T));
                }
                memset(&rec, 0, sizeof(L4_TYPE_ClassMapElementEntry_T));
            }

        }
        /*for active this class map*/
        APPEND_RUNNING_CFG_0(" exit\n");
    }
#endif
return buffer_count;

}

static UI32_T CLI_RUNCFG_Get_Policy_Map_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    UI32_T pmap_id = 0;
    L4_TYPE_diffServClfrEntry_T rec_p;
    UI32_T cmap_id = 0;
    L4_TYPE_diffServClfrElementEntry_T e_rec_p;
    L4_TYPE_ClassMapEntry_T cm_rec_p;
    L4_TYPE_diffServActionEntry_T entry_p;
    L4_TYPE_diffServTBParamEntry_T tb_entry_p;
    L4_TYPE_diffServMeterEntry_T meter_entry_p;

    memset(&meter_entry_p, 0, sizeof(L4_TYPE_diffServMeterEntry_T));
    memset(&rec_p, 0, sizeof(L4_TYPE_diffServClfrEntry_T));
    memset(&e_rec_p, 0, sizeof(L4_TYPE_diffServClfrElementEntry_T));
    memset(&cm_rec_p, 0, sizeof(L4_TYPE_ClassMapEntry_T));
    memset(&entry_p, 0, sizeof(L4_TYPE_diffServActionEntry_T));
    memset(&tb_entry_p, 0, sizeof(L4_TYPE_diffServTBParamEntry_T));

    while(L4_DS_PMGR_GetNextRunningPolicyMap(&pmap_id, &rec_p) == TRUE)
    {
        APPEND_RUNNING_CFG_0("!\n");
        APPEND_RUNNING_CFG_1("policy-map %s\n", rec_p.name);
        if (rec_p.desc[0] != 0)
        {
            APPEND_RUNNING_CFG_1(" description %s\n", rec_p.desc);
        }

        if(L4_DS_PMGR_GetFirstClass(pmap_id, &cmap_id, &e_rec_p) == TRUE)
        {
            if(e_rec_p.next.table == DS_OM_METER_TABLE)
            {
                memset(&meter_entry_p, 0, sizeof(L4_TYPE_diffServMeterEntry_T));
                L4_DS_PMGR_GetMeter(e_rec_p.next.index, &meter_entry_p);
            }
            if(L4_DS_PMGR_GetClassMap(cmap_id, &cm_rec_p) == TRUE)
            {
                /*
                  2004/6/29 10:23 pttch add for init variable or the first entry can not get
                */
                memset(&entry_p, 0, sizeof(L4_TYPE_diffServActionEntry_T));
                APPEND_RUNNING_CFG_1(" class %s\n", cm_rec_p.name);
                while(L4_DS_PMGR_GetNextInProfileAction(pmap_id, cmap_id, &entry_p) == TRUE)
                {
                    if(entry_p.specific.table == DS_OM_DOT1P_MARK_ACT_TABLE)
                    {
                        APPEND_RUNNING_CFG_1("  set cos %d\n", entry_p.specific.index);
                    }
                    else if(entry_p.specific.table == DS_OM_DSCP_MARK_ACT_TABLE)
                    {
                        APPEND_RUNNING_CFG_1("  set ip dscp %d\n", entry_p.specific.index);
                    }
                    else if(entry_p.specific.table == DS_OM_TOS_MARK_ACT_TABLE)
                    {
                        APPEND_RUNNING_CFG_1("  set ip precedence %d\n", entry_p.specific.index);
                    }
                }
                memset(&entry_p, 0, sizeof(L4_TYPE_diffServActionEntry_T));
                while(L4_DS_PMGR_GetNextOutProfileAction(pmap_id, cmap_id, &entry_p) == TRUE)
                {
                    if(L4_DS_PMGR_GetTBParam(meter_entry_p.specific.index, &tb_entry_p) == TRUE)
                    {
                        if(entry_p.specific.table == DS_OM_DOT1P_MARK_ACT_TABLE)
                        {
                            APPEND_RUNNING_CFG_3("  police %ld %ld exceed-action set cos %d\n", (long)tb_entry_p.rate, (long)tb_entry_p.burst_size, entry_p.specific.index);
                        }
                        else if(entry_p.specific.table == DS_OM_DSCP_MARK_ACT_TABLE)
                        {
                            APPEND_RUNNING_CFG_3("  police %ld %ld exceed-action set ip dscp %d\n", (long)tb_entry_p.rate, (long)tb_entry_p.burst_size, entry_p.specific.index);
                        }
                        else if(entry_p.specific.table == DS_OM_TOS_MARK_ACT_TABLE)
                        {
                            APPEND_RUNNING_CFG_3("  police %ld %ld exceed-action set ip precedence %d\n", (long)tb_entry_p.rate, (long)tb_entry_p.burst_size, entry_p.specific.index);
                        }
                        else
                        {
                            APPEND_RUNNING_CFG_2("  police %ld %ld exceed-action drop\n", (long)tb_entry_p.rate, (long)tb_entry_p.burst_size);
                        }
                    }
                }
                APPEND_RUNNING_CFG_0("  exit\n");
            }

            while(L4_DS_PMGR_GetNextClass(pmap_id, &cmap_id, &e_rec_p) == TRUE)
            {
                if(e_rec_p.next.table == DS_OM_METER_TABLE)
                {
                    memset(&meter_entry_p, 0, sizeof(L4_TYPE_diffServMeterEntry_T));
                    L4_DS_PMGR_GetMeter(e_rec_p.next.index, &meter_entry_p);
                }

                if(L4_DS_PMGR_GetClassMap(cmap_id, &cm_rec_p) == TRUE)
                {
                    /*
                      2004/6/29 10:23 pttch add for init variable or the first entry can not get
                    */
                    memset(&entry_p, 0, sizeof(L4_TYPE_diffServActionEntry_T));
                    APPEND_RUNNING_CFG_1(" class %s\n", cm_rec_p.name);
                    while(L4_DS_PMGR_GetNextInProfileAction(pmap_id, cmap_id, &entry_p) == TRUE)
                    {
                        if(entry_p.specific.table == DS_OM_DOT1P_MARK_ACT_TABLE)
                        {
                            APPEND_RUNNING_CFG_1("  set cos %d\n", entry_p.specific.index);
                        }
                        else if(entry_p.specific.table == DS_OM_DSCP_MARK_ACT_TABLE)
                        {
                            APPEND_RUNNING_CFG_1("  set ip dscp %d\n", entry_p.specific.index);
                        }
                        else if(entry_p.specific.table == DS_OM_TOS_MARK_ACT_TABLE)
                        {
                            APPEND_RUNNING_CFG_1("  set ip precedence %d\n", entry_p.specific.index);
                        }
                    }
                    memset(&entry_p, 0, sizeof(L4_TYPE_diffServActionEntry_T));
                    while(L4_DS_PMGR_GetNextOutProfileAction(pmap_id, cmap_id, &entry_p) == TRUE)
                    {
                        if(L4_DS_PMGR_GetTBParam(meter_entry_p.specific.index, &tb_entry_p) == TRUE)
                        {
                            if(entry_p.specific.table == DS_OM_DOT1P_MARK_ACT_TABLE)
                            {
                                APPEND_RUNNING_CFG_3("  police %ld %ld exceed-action set cos %d\n", (long)tb_entry_p.rate, (long)tb_entry_p.burst_size, entry_p.specific.index);
                            }
                            else if(entry_p.specific.table == DS_OM_DSCP_MARK_ACT_TABLE)
                            {
                                APPEND_RUNNING_CFG_3("  police %ld %ld exceed-action set ip dscp %d\n", (long)tb_entry_p.rate, (long)tb_entry_p.burst_size, entry_p.specific.index);
                            }
                            else if(entry_p.specific.table == DS_OM_TOS_MARK_ACT_TABLE)
                            {
                                APPEND_RUNNING_CFG_3("  police %ld %ld exceed-action set ip precedence %d\n", (long)tb_entry_p.rate, (long)tb_entry_p.burst_size, entry_p.specific.index);
                            }
                            else
                            {
                                APPEND_RUNNING_CFG_2("  police %ld %ld exceed-action drop\n", (long)tb_entry_p.rate, (long)tb_entry_p.burst_size);
                            }
                        }
                    }
                    APPEND_RUNNING_CFG_0("  exit\n");
                }
            }
        }
        /*for active this policy map*/
        APPEND_RUNNING_CFG_0(" exit\n");
    }
return buffer_count;
}
#endif /* #if (SYS_CPNT_QOS_V2 == TRUE) */
#endif /* #if (SYS_CPNT_QOS == SYS_CPNT_QOS_DIFFSERV) */
#endif /* #if (SYS_CPNT_QOS_UI == TRUE) */

#if (SYS_CPNT_COS_INTER_DSCP == TRUE)
static UI32_T
CLI_RUNCFG_Get_Global_Qos_Map_Parameter(
    UI32_T unit_id,
    char *buffer,
    char *temp_buffer,
    UI32_T buffer_size,
    UI32_T b_count)
{
    UI32_T buffer_count = b_count;

#if (SYS_CPNT_COS_ING_COS_TO_INTER_DSCP == TRUE)
#if (SYS_CPNT_COS_ING_COS_TO_INTER_DSCP_PER_PORT == FALSE)
    {
        const int max_cos_entry_num = 8;

        UI32_T cos, cfi, phb, color;
        int entry_number = 0;
        BOOL_T is_first_entry = TRUE;

        for (phb = MIN_PHB_VAL; phb <= MAX_PHB_VAL; ++phb)
        {
            for (color = MIN_COLOR_VAL; color <= MAX_COLOR_VAL; ++color)
            {
                is_first_entry = TRUE;
                cos = COS_TYPE_UNKNOWN_COS;

                while (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                       L4_PMGR_QOS_GetNextRunningCos2InternalDscp(phb, color, &cos, &cfi))
                {
                    if (is_first_entry == TRUE)
                    {
                        is_first_entry = FALSE;
                        APPEND_RUNNING_CFG_2(" qos map cos-dscp %lu %lu from", (unsigned long)phb, (unsigned long)color);
                    }

                    APPEND_RUNNING_CFG_2(" %lu %lu", (unsigned long)cos, (unsigned long)cfi);

                    entry_number++;
                    if (entry_number == max_cos_entry_num)
                    {
                        APPEND_RUNNING_CFG_0("\r\n");
                        entry_number = 0;
                        is_first_entry = TRUE;
                    }
                }

                if (is_first_entry != TRUE)
                {
                    APPEND_RUNNING_CFG_0("\r\n");
                }
            }
        }
    }
#endif /* (SYS_CPNT_COS_ING_COS_TO_INTER_DSCP_PER_PORT == FALSE) */
#endif /* SYS_CPNT_COS_ING_COS_TO_INTER_DSCP */

#if (SYS_CPNT_COS_ING_DSCP_TO_INTER_DSCP == TRUE)
#if (SYS_CPNT_COS_ING_DSCP_TO_INTER_DSCP_PER_PORT == FALSE)
    {
        const int max_cos_entry_num = 8;

        UI32_T dscp, phb, color;
        int entry_number = 0;
        BOOL_T is_first_entry;

        for (phb = MIN_PHB_VAL; phb <= MAX_PHB_VAL; ++phb)
        {
            for (color = MIN_COLOR_VAL; color <= MAX_COLOR_VAL; ++color)
            {
                is_first_entry = TRUE;
                dscp = COS_TYPE_UNKNOWN_DSCP;

                while (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                       L4_PMGR_QOS_GetNextRunningDscp2InternalDscp(phb, color, &dscp))
                {
                    if (is_first_entry == TRUE)
                    {
                        is_first_entry = FALSE;
                        APPEND_RUNNING_CFG_2(" qos map dscp-mutation %lu %lu from", (unsigned long)phb, (unsigned long)color);
                    }

                    APPEND_RUNNING_CFG_1(" %lu", (unsigned long)dscp);

                    entry_number++;
                    if (entry_number == max_cos_entry_num)
                    {
                        APPEND_RUNNING_CFG_0("\r\n");
                        entry_number = 0;
                        is_first_entry = TRUE;
                    }
                }

                if (is_first_entry != TRUE)
                {
                    APPEND_RUNNING_CFG_0("\r\n");
                }
            }
        }
    }
#endif /* (SYS_CPNT_COS_ING_DSCP_TO_INTER_DSCP_PER_PORT == FALSE) */
#endif /* SYS_CPNT_COS_ING_DSCP_TO_INTER_DSCP */

#if (SYS_CPNT_COS_ING_INTER_DSCP_TO_QUEUE == TRUE)
#if (SYS_CPNT_COS_ING_INTER_DSCP_TO_QUEUE_PER_PORT == FALSE)
    {
        const int max_cos_entry_num = 8;

        UI32_T queue, phb;
        int entry_number = 0;
        BOOL_T is_first_entry;

        for (queue = MIN_QUEUE_VAL; queue <= MAX_QUEUE_VAL; ++queue)
        {
            is_first_entry = TRUE;
            phb = COS_TYPE_UNKNOWN_PHB;

            while (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                   L4_PMGR_QOS_GetNextRunningIngressPhb2Queue(queue, &phb))
            {
                if (is_first_entry == TRUE)
                {
                    is_first_entry = FALSE;
                    APPEND_RUNNING_CFG_1(" qos map phb-queue %lu from", (unsigned long)queue);
                }

                APPEND_RUNNING_CFG_1(" %lu", (unsigned long)phb);

                entry_number++;
                if (entry_number == max_cos_entry_num)
                {
                    APPEND_RUNNING_CFG_0("\r\n");
                    entry_number = 0;
                    is_first_entry = TRUE;
                }
            }

            if (is_first_entry != TRUE)
            {
                APPEND_RUNNING_CFG_0("\r\n");
            }
        }
    }
#endif /* (SYS_CPNT_COS_ING_INTER_DSCP_TO_QUEUE_PER_PORT == FALSE) */
#endif /* SYS_CPNT_COS_ING_INTER_DSCP_TO_QUEUE */

    return buffer_count;
}
#endif/* #if (SYS_CPNT_COS_INTER_DSCP == TRUE) */

#if (SYS_CPNT_POE == TRUE)
static UI32_T CLI_RUNCFG_Get_POE_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;

    UI32_T milliwatts = 36;
    UI32_T runcfg_my_unit_id = 0;
    UI32_T power_inline_compatible_status;

#if (SYS_CPNT_POE_MAX_ALLOC_FIXED != TRUE)
    runcfg_my_unit_id = 0;
    while(STKTPLG_OM_GetNextUnit(&runcfg_my_unit_id))
    {
        if (STKTPLG_OM_IsPoeDevice(runcfg_my_unit_id) == FALSE)
        {
            continue;
        }
        if(POE_POM_GetRunningMainPowerMaximumAllocation(runcfg_my_unit_id, &milliwatts)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_2("power mainpower maximum allocation %lu unit %lu\r\n", (unsigned long)milliwatts, (unsigned long)runcfg_my_unit_id);
        }
    }
#endif/* End of #if (SYS_CPNT_POE_MAX_ALLOC_FIXED != TRUE) */

#if (SYS_CPNT_POE_COMPATIBLE_SUPPORT == TRUE)
    runcfg_my_unit_id = 0;
    while(STKTPLG_OM_GetNextUnit(&runcfg_my_unit_id))
    {
        if (STKTPLG_OM_IsPoeDevice(runcfg_my_unit_id) == FALSE)
        {
            continue;
        }
        if(POE_POM_GetRunningLegacyDetection(runcfg_my_unit_id, &power_inline_compatible_status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            switch(power_inline_compatible_status)
            {
                case 0:
                    APPEND_RUNNING_CFG_1("no power inline compatible %lu\r\n", (unsigned long)runcfg_my_unit_id);
                    break;

                case 1:
                    APPEND_RUNNING_CFG_1("power inline compatible %lu\r\n", (unsigned long)runcfg_my_unit_id);
                    break;

                default:
                    break;
            }
        }
    }
#endif/* End of #if (SYS_CPNT_POE_COMPATIBLE_SUPPORT == TRUE) */
    return buffer_count;
}
#endif



#if defined(UNICORN) /*switchport broadcast global setting*/
static UI32_T CLI_RUNCFG_Get_UNICORN_Parameter(UI32_T runcfg_my_unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    UI32_T i;
    UI32_T ifindex;
    Port_Info_T port_info;
    BOOL_T is_inherit        =TRUE;

    memset (&port_info , 0 , sizeof(Port_Info_T));
    for (i = 1 ; i <= runcfg_max_port_num ; i++)/*the global loop of interface ethernet*/
    {
        SWCTRL_Lport_Type_T port_type = SWCTRL_POM_UIUserPortToIfindex(runcfg_my_unit_id, i, &ifindex, &is_inherit);
        /*prevent from generate code of not present module*/
        if(!SWCTRL_UIUserPortExisting(runcfg_my_unit_id, i) || port_type == SWCTRL_LPORT_TRUNK_PORT_MEMBER)
            continue;
        else
        {
            if (SWCTRL_POM_GetRunningPortInfo(ifindex, &port_info) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if ((port_info.bsctrl_state_changed == TRUE) || (port_info.rate_limit_changed == TRUE))
                {
                    if (port_info.bsctrl_state == VAL_bcastStormStatus_disabled)
                    {
                        APPEND_RUNNING_CFG_0("no broadcast\n");
                    }
                    else
                    {
                        switch(port_info.rate_mode)
                        {
                            case VAL_bcastStormSampleType_pkt_rate:
                                if (port_info.rate_limit_changed == TRUE)
                                {
                                    APPEND_RUNNING_CFG_1("broadcast frame-count %lu\n", (unsigned long)port_info.rate_limit);
                                }
                            break;

                            case VAL_bcastStormSampleType_octet_rate:
                                if (port_info.rate_limit_changed == TRUE)
                                {
                                }
                            break;

                            case VAL_bcastStormSampleType_percent:
                                if (port_info.rate_limit_changed == TRUE)
                                {
                                }
                            break;

                            default:
                            break;
                        }
                    }
                }
            }
        break; /*setting get one as global*/
        }
    }
    APPEND_RUNNING_CFG_0("!\n");

    return buffer_count;
}
#endif /*#if defined(UNICORN)*/


static UI32_T CLI_RUNCFG_Get_IPAddress_Parameter(UI32_T runcfg_my_unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;

#if (CLI_SUPPORT_L3_FEATURE != 1)
    {
        L_INET_AddrIp_T default_gateway_ip;

        default_gateway_ip.type = L_INET_ADDR_TYPE_IPV4;
        if(NETCFG_PMGR_ROUTE_GetRunningDefaultGateway(&default_gateway_ip) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_4("ip default-gateway %d.%d.%d.%d\n", default_gateway_ip.addr[0], default_gateway_ip.addr[1], default_gateway_ip.addr[2], default_gateway_ip.addr[3]);
        }
    }
    /* arp timeout for L2 */
    {
         UI32_T time_out_value;
         SYS_TYPE_Get_Running_Cfg_T rc;
         /* arp timeout */
         rc = NETCFG_PMGR_ND_GetRunningIpNetToMediaTimeout(&time_out_value);
         if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS == rc)
         {
            APPEND_RUNNING_CFG_1("arp timeout %lu\n", (unsigned long)time_out_value);
         }
    }

#else
    /* default gateway */
    {
        NETCFG_TYPE_IpCidrRouteEntry_T  route_entry;

        memset(&route_entry, 0, sizeof(NETCFG_TYPE_IpCidrRouteEntry_T));
        route_entry.route_dest.type = L_INET_ADDR_TYPE_IPV4;

        while(NETCFG_POM_ROUTE_GetNextRunningStaticIpCidrRouteEntry(&route_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            /* steven.gao */
            struct pal_in4_addr netmask_t;

            if (route_entry.ip_cidr_route_status != NETCFG_TYPE_StaticIpCidrEntryRowStatus_active)
                continue;

            if (route_entry.ip_cidr_route_distance > SYS_ADPT_MIN_ROUTE_DISTANCE)
            {
                /* steven.gao */
#if 0
                APPEND_RUNNING_CFG_4("ip route %d.%d.%d.%d ",   ((UI8_T *)(&(route_entry.ip_cidr_route_dest)))[0], ((UI8_T *)(&(route_entry.ip_cidr_route_dest)))[1], ((UI8_T *)(&(route_entry.ip_cidr_route_dest)))[2], ((UI8_T *)(&(route_entry.ip_cidr_route_dest)))[3] );
                APPEND_RUNNING_CFG_4("%d.%d.%d.%d ",   ((UI8_T *)(&(route_entry.ip_cidr_route_mask)))[0], ((UI8_T *)(&(route_entry.ip_cidr_route_mask)))[1], ((UI8_T *)(&(route_entry.ip_cidr_route_mask)))[2], ((UI8_T *)(&(route_entry.ip_cidr_route_mask)))[3] );
                APPEND_RUNNING_CFG_4("%d.%d.%d.%d ",   ((UI8_T *)(&(route_entry.ip_cidr_route_next_hop)))[0], ((UI8_T *)(&(route_entry.ip_cidr_route_next_hop)))[1], ((UI8_T *)(&(route_entry.ip_cidr_route_next_hop)))[2], ((UI8_T *)(&(route_entry.ip_cidr_route_next_hop)))[3] );
                APPEND_RUNNING_CFG_1("%lu\n", route_entry.ip_cidr_route_distance);
#else
                APPEND_RUNNING_CFG_4("ip route %d.%d.%d.%d ",   ((UI8_T *)(&(route_entry.route_dest.addr)))[0], ((UI8_T *)(&(route_entry.route_dest.addr)))[1], ((UI8_T *)(&(route_entry.route_dest.addr)))[2], ((UI8_T *)(&(route_entry.route_dest.addr)))[3] );
                L_PREFIX_MaskLen2IPv4(route_entry.route_dest.preflen, &netmask_t);
                APPEND_RUNNING_CFG_1("%s ", inet_ntoa(netmask_t));
                APPEND_RUNNING_CFG_4("%d.%d.%d.%d ",   ((UI8_T *)(&(route_entry.route_next_hop.addr)))[0], ((UI8_T *)(&(route_entry.route_next_hop.addr)))[1], ((UI8_T *)(&(route_entry.route_next_hop.addr)))[2], ((UI8_T *)(&(route_entry.route_next_hop.addr)))[3] );
                APPEND_RUNNING_CFG_1("%lu\n", (unsigned long)route_entry.ip_cidr_route_distance);

#endif
            }
            else
            {
                APPEND_RUNNING_CFG_4("ip route %d.%d.%d.%d ",   ((UI8_T *)(&(route_entry.route_dest.addr)))[0], ((UI8_T *)(&(route_entry.route_dest.addr)))[1], ((UI8_T *)(&(route_entry.route_dest.addr)))[2], ((UI8_T *)(&(route_entry.route_dest.addr)))[3] );
                L_PREFIX_MaskLen2IPv4(route_entry.route_dest.preflen, &netmask_t);
                APPEND_RUNNING_CFG_1("%s ", inet_ntoa(netmask_t));
                APPEND_RUNNING_CFG_4("%d.%d.%d.%d\n",   ((UI8_T *)(&(route_entry.route_next_hop.addr)))[0], ((UI8_T *)(&(route_entry.route_next_hop.addr)))[1], ((UI8_T *)(&(route_entry.route_next_hop.addr)))[2], ((UI8_T *)(&(route_entry.route_next_hop.addr)))[3] );
            }
        }
    }
#endif
    APPEND_RUNNING_CFG_0("!\n");

#if RUNCFG_DEVELOP
    CLI_LIB_PrintStr("default gateway complete\r\n");
#endif

    return buffer_count;
}

#if (SYS_CPNT_LLDP == TRUE)
static UI32_T CLI_RUNCFG_Get_Lldp_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;

    /* LLDP */
    {
        UI32_T  admin_status;

        if (LLDP_POM_GetRunningSysAdminStatus(&admin_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (admin_status == LLDP_TYPE_SYS_ADMIN_ENABLE)
            {
                APPEND_RUNNING_CFG_0("lldp\n");
            }
            else if (admin_status == LLDP_TYPE_SYS_ADMIN_DISABLE)
            {
                APPEND_RUNNING_CFG_0("no lldp\n");
            }
        }
    }

    /* lldp refresh-interval */
    {
        UI32_T  msg_tx_interval,tx_delay_time_pre;
        if (LLDP_POM_GetRunningMsgTxInterval(&msg_tx_interval) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (LLDP_POM_GetRunningTxDelay(&tx_delay_time_pre) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if (tx_delay_time_pre*4 <= msg_tx_interval)
                {
                    APPEND_RUNNING_CFG_1("lldp tx-delay %lu\n", (unsigned long)tx_delay_time_pre);
                }
        else
        {
                    APPEND_RUNNING_CFG_1("lldp refresh-interval %lu\n", (unsigned long)msg_tx_interval);
        }
            }
        else
        {
                APPEND_RUNNING_CFG_1("lldp refresh-interval %lu\n", (unsigned long)msg_tx_interval);
        }
        }
    }

    /* lldp holdtime-multiplier */
    {
        UI32_T  msg_tx_hold;

        if (LLDP_POM_GetRunningMsgTxHoldMul(&msg_tx_hold) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("lldp holdtime-multiplier %lu\n", (unsigned long)msg_tx_hold);
        }
    }

    /* lldp tx-delay */
    {
        UI32_T  tx_delay_time,msg_tx_interval_pre;

        if (LLDP_POM_GetRunningTxDelay(&tx_delay_time) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (LLDP_POM_GetRunningMsgTxInterval(&msg_tx_interval_pre) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
                if (tx_delay_time*4 <= msg_tx_interval_pre)
                {
                    APPEND_RUNNING_CFG_1("lldp refresh-interval %lu\n", (unsigned long)msg_tx_interval_pre);
                }
        else
        {
                    APPEND_RUNNING_CFG_1("lldp tx-delay %lu\n", (unsigned long)tx_delay_time);
        }
            }
        else
        {
                APPEND_RUNNING_CFG_1("lldp tx-delay %lu\n", (unsigned long)tx_delay_time);
        }
        }
    }

    /* lldp reinit-delay */
    {
        UI32_T  reinit_delay;

        if (LLDP_POM_GetRunningReinitDelay(&reinit_delay) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("lldp reinit-delay %lu\n", (unsigned long)reinit_delay);
        }
    }

    /* lldp notification-interval */
    {
        UI32_T  notify_interval;

        if (LLDP_POM_GetRunningNotifyInterval(&notify_interval) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("lldp notification-interval %lu\n", (unsigned long)notify_interval);
        }
    }

#if (SYS_CPNT_LLDP_MED == TRUE)
    /* lldp medFastStartCount  */
    {
        UI32_T  repeat_count;

        if (LLDP_POM_GetRunningXMedFastStartRepeatCount( &repeat_count) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" lldp med-fast-start-count %lu\n",(unsigned long)repeat_count);
        }
    }
#endif /*#if (SYS_CPNT_LLDP_MED == TRUE)*/

    APPEND_RUNNING_CFG_0("!\n");
    return buffer_count;
}

#endif

#if (SYS_CPNT_DHCPSNP == TRUE)
static UI32_T CLI_RUNCFG_Get_Dhcpsnp_Global_Parameter ( UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    UI8_T status;
    UI32_T vid = 0;
    UI32_T  buffer_count = b_count;


    /* IP DHCP Snooping */
    if (DHCPSNP_PMGR_GetRunningGlobalDhcpSnoopingStatus(&status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if (status == DHCPSNP_TYPE_SNOOPING_GLOBAL_ENABLED)
        {
            // printf("test tets\r\n");
            APPEND_RUNNING_CFG_0("ip dhcp snooping\n");
        }
        else if (status == DHCPSNP_TYPE_SNOOPING_GLOBAL_DISABLED)
        {
            APPEND_RUNNING_CFG_0("no ip dhcp snooping\n");
        }
    }


    /* for dhcpsnp verify mac-address */
    if (DHCPSNP_PMGR_GetRunningVerifyMacAddressStatus(&status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if (status == DHCPSNP_TYPE_VERIFY_MAC_ADDRESS_ENABLED)
        {
            APPEND_RUNNING_CFG_0("ip dhcp snooping verify mac-address\n");
        }
        else if (status == DHCPSNP_TYPE_VERIFY_MAC_ADDRESS_DISABLED)
        {
            APPEND_RUNNING_CFG_0("no ip dhcp snooping verify mac-address\n");
        }
    }

    /* for dhcpsnp verify vlan */
    {
        UI8_T vlan_list[(SYS_DFLT_DOT1QMAXVLANID/8)+1];
        UI8_T *vlan_buff;
        BOOL_T flag=FALSE;

        memset(vlan_list, 0, sizeof(vlan_list));

        /*why allocate this number, because vlan list string may be too large*/
        /*so allocate such big memory to store this string*/
        if((vlan_buff = calloc(512*4, sizeof(UI8_T))) == NULL)
        {
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
        }

        while(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == DHCPSNP_PMGR_GetNextRunningDhcpSnoopingStatusByVlan(&vid, &status))
        {

            vlan_list[(UI32_T)((vid-1)/8)]  |= (1 << ( 7 - ((vid-1)%8)));
            flag=TRUE;
        }

        if(flag)
        {
            CLI_LIB_Bitmap_To_List((char *)vlan_list, (char *)vlan_buff, 512*4, SYS_DFLT_DOT1QMAXVLANID,TRUE);

            if( status == DHCPSNP_TYPE_SNOOPING_VLAN_ENABLED)
            {
                APPEND_RUNNING_CFG_1("ip dhcp snooping vlan %s\n", vlan_buff);
            }

            if( status == DHCPSNP_TYPE_SNOOPING_VLAN_DISABLED)
            {
                APPEND_RUNNING_CFG_1("no ip dhcp snooping vlan %s\n", vlan_buff);
            }
        }
        free(vlan_buff);
    }

#if (SYS_CPNT_DHCPSNP_SYSTEM_RATELIMIT == TRUE)
    {
        UI32_T limit=0;
        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                DHCPSNP_PMGR_GetRunningGlobalRateLimit(&limit))
        {
            if(limit!=DHCPSNP_TYPE_SYSTEM_NO_RATELIMIT)
            {
                APPEND_RUNNING_CFG_1("ip dhcp snooping limit rate %lu\n",(unsigned long)limit);
            }
            else
            {
                APPEND_RUNNING_CFG_0("no ip dhcp snooping limit rate\n");
            }
        }
    }
#endif /* End of #if (SYS_CPNT_DHCPSNP_SYSTEM_RATELIMIT == TRUE) */

#if (SYS_CPNT_IPSG_BINDING_FILTER_SOURCE == TRUE)
    {
        UI32_T filter_source=0;

        if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == IPSG_POM_GetRunningBindingFilterSource(&filter_source))
        {
            if(filter_source == IPSG_TYPE_IPSG_BINDING_FILTER_SOURCE_STATIC)
            {
                APPEND_RUNNING_CFG_0("ip source-guard binding filter-source static\n");
            }
            else if(filter_source == IPSG_TYPE_IPSG_BINDING_FILTER_SOURCE_ALL)
            {
                APPEND_RUNNING_CFG_0("ip source-guard binding filter-source all\n");
            }
        }
    }
#endif /* SYS_CPNT_IPSG_BINDING_FILTER_SOURCE */

/*dhcp snooping option 82*/
#if (SYS_CPNT_DHCPSNP_INFORMATION_OPTION == TRUE)
    {

    UI8_T option_status, policy,rid_mode;
    BOOL_T subtype_format=FALSE;
    if (DHCPSNP_PMGR_GetRunningInformationOptionStatus(&option_status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if (option_status == DHCPSNP_TYPE_OPTION82_ENABLED)
        {
            // printf("test tets\r\n");
            APPEND_RUNNING_CFG_0("ip dhcp snooping information option\n");
        }
        else if (option_status == DHCPSNP_TYPE_OPTION82_DISABLED)
        {
            APPEND_RUNNING_CFG_0("no ip dhcp snooping information option\n");
        }
    }

    if (DHCPSNP_PMGR_GetRunningInformationFormat(&subtype_format) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if(subtype_format)
        {
            APPEND_RUNNING_CFG_0("no ip dhcp snooping information option encode no-subtype\n");
        }
        else
        {
            APPEND_RUNNING_CFG_0("ip dhcp snooping information option encode no-subtype\n");
        }
    }

    if(DHCPSNP_PMGR_GetRunningInformationRidMode(&rid_mode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        switch(rid_mode)
        {
            case DHCPSNP_TYPE_OPTION82_RID_MAC_HEX:
                APPEND_RUNNING_CFG_0("ip dhcp snooping information option remote-id mac-address encode hex\n");
                break;
            case DHCPSNP_TYPE_OPTION82_RID_MAC_ASCII:
                APPEND_RUNNING_CFG_0("ip dhcp snooping information option remote-id mac-address encode ascii\n");
                break;
            case DHCPSNP_TYPE_OPTION82_RID_IP_HEX:
                APPEND_RUNNING_CFG_0("ip dhcp snooping information option remote-id ip-address encode hex\n");
                break;
            case DHCPSNP_TYPE_OPTION82_RID_IP_ASCII:
                APPEND_RUNNING_CFG_0("ip dhcp snooping information option remote-id ip-address encode ascii\n");
                break;
            case DHCPSNP_TYPE_OPTION82_RID_CONFIGURED_STRING:
                {
                    UI8_T    rid_value[SYS_ADPT_MAX_LENGTH_OF_RID+ 1]={0};
                    if(DHCPSNP_TYPE_OK == DHCPSNP_PMGR_GetInformationRidValue(rid_value))
                    {
                        APPEND_RUNNING_CFG_1("ip dhcp snooping information option remote-id string %s\n",rid_value);
                    }
                }
                break;
#if (SYS_CPNT_DHCPSNP_INFORMATION_OPTION_TR101_FORMAT == TRUE)
            case DHCPSNP_TYPE_OPTION82_RID_TR101_IP:
                APPEND_RUNNING_CFG_0("ip dhcp snooping information option remote-id tr101 node-identifier ip\n");
                break;
            case DHCPSNP_TYPE_OPTION82_RID_TR101_SYSNAME:
                APPEND_RUNNING_CFG_0("ip dhcp snooping information option remote-id tr101 node-identifier sysname\n");
                break;
#endif
#if (SYS_CPNT_DHCPSNP_INFORMATION_OPTION_RID_SUB_OPTION == TRUE)
            case DHCPSNP_TYPE_OPTION82_RID_CONFIGURED_STRING_PLUS_PORT_DESCRIPTION:
                {
                    char   buff[255]={0};
                    UI8_T   rid_value[SYS_ADPT_MAX_LENGTH_OF_RID+1]={0};
                    UI8_T   delimiter=0;

                    if(DHCPSNP_TYPE_OK == DHCPSNP_PMGR_GetInformationRidValue(rid_value))
                    {
                        sprintf(buff,
                                "ip dhcp snooping information option remote-id string %s "
                                "sub-option plus-port-description ",
                                rid_value);
                    }

                    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                        DHCPSNP_PMGR_GetRunningOptionDelimiter(&delimiter))
                    {
                        sprintf(buff+strlen(buff),"delimiter %u\n",delimiter);
                    }
                    else
                    {
                        sprintf(buff+strlen(buff),"\n");
                    }

                    APPEND_RUNNING_CFG_1("%s",buff);
                }
                break;
#endif
        }
    }


    if(DHCPSNP_PMGR_GetRunningInformationPolicy(&policy) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        switch(policy)
        {
            case DHCPSNP_TYPE_OPTION82_POLICY_DROP:
            {
                APPEND_RUNNING_CFG_0("ip dhcp snooping information policy drop\n");
                break;
            }

            case DHCPSNP_TYPE_OPTION82_POLICY_REPLACE:
            {
                APPEND_RUNNING_CFG_0("ip dhcp snooping information policy replace\n");
                break;
            }

            case DHCPSNP_TYPE_OPTION82_POLICY_KEEP:
            {
                APPEND_RUNNING_CFG_0("ip dhcp snooping information policy keep\n");
                break;
            }
        }
    }

#if (SYS_CPNT_DHCPSNP_INFORMATION_OPTION_TR101_FORMAT == TRUE)
    {
        UI8_T board_id=0;
        if(DHCPSNP_PMGR_GetRunningBoardId(&board_id) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("ip dhcp snooping information option tr101 board-id %u\n",board_id);
        }
    }
#endif


    }
#endif

    return buffer_count;
}
#endif

#if (SYS_CPNT_DHCPV6 == TRUE)
static UI32_T CLI_RUNCFG_Get_Dhcpv6_Parameter ( UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    UI32_T  buffer_count = b_count;
    UI32_T  vid = 0;
    BOOL_T  rapid_commit = DHCPv6_TYPE_DEFAULT_RAPID_COMMIT;

    while (DHCPv6_PMGR_GetNextRunningRapidCommit(&vid, &rapid_commit) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if (rapid_commit == TRUE)
        {
            APPEND_RUNNING_CFG_1(" ipv6 dhcp client rapid-commit vlan %lu\n", (unsigned long)vid);
        }
        else if (rapid_commit == FALSE)
        {
            APPEND_RUNNING_CFG_1(" no ipv6 dhcp client rapid-commit vlan %lu\n", (unsigned long)vid);
        }
    }

    APPEND_RUNNING_CFG_0("!\n");

    return buffer_count;
}
#endif

#if (SYS_CPNT_DHCPV6SNP == TRUE)
static UI32_T CLI_RUNCFG_Get_Dhcpv6snp_Parameter ( UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    UI32_T  buffer_count = b_count;
    UI8_T    global_status=0;
    UI32_T  vid=0;
    UI8_T    vlan_status=0;

    /* get global snooping status */
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == DHCPV6SNP_POM_GetRunningGlobalSnoopingStatus(&global_status))
    {
        if(DHCPV6SNP_TYPE_GLOBAL_SNOOPING_ENABLE == global_status)
        {
            APPEND_RUNNING_CFG_0("ipv6 dhcp snooping\n");
        }

        if(DHCPV6SNP_TYPE_GLOBAL_SNOOPING_DISABLE == global_status)
        {

            APPEND_RUNNING_CFG_0("no ipv6 dhcp snooping\n");
        }
    }

#if (SYS_CPNT_DHCPV6SNP_REMOTE_ID_OPTION == TRUE)
{
    UI8_T remote_id_status=0;
    UI8_T remote_id_policy=0;

    /* get remote-id option status */
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == DHCPV6SNP_POM_GetRunningRemoteIdStatus(&remote_id_status))
    {
        if(DHCPV6SNP_TYPE_REMOTE_ID_ENABLE == remote_id_status)
        {
            APPEND_RUNNING_CFG_0("ipv6 dhcp snooping option remote-id\n");
        }

        if(DHCPV6SNP_TYPE_REMOTE_ID_DISABLE == remote_id_policy)
        {
            APPEND_RUNNING_CFG_0("no ipv6 dhcp snooping option remote-id\n");
        }
    }

    /* get remote-id forwarding policy */
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == DHCPV6SNP_POM_GetRunningRemoteIdPolicy(&remote_id_policy))
    {
        switch(remote_id_policy)
        {
            case DHCPV6SNP_TYPE_REMOTE_ID_POLICY_DROP:
                APPEND_RUNNING_CFG_0("ipv6 dhcp snooping option remote-id policy drop\n");
                break;
            case DHCPV6SNP_TYPE_REMOTE_ID_POLICY_KEEP:
                APPEND_RUNNING_CFG_0("ipv6 dhcp snooping option remote-id policy keep\n");
                break;
            case DHCPV6SNP_TYPE_REMOTE_ID_POLICY_REPLACE:
                APPEND_RUNNING_CFG_0("ipv6 dhcp snooping option remote-id policy replace\n");
                break;
        }
    }
}
#endif

    /* get vlan snooping status */
    {
        UI8_T vlan_list[(SYS_DFLT_DOT1QMAXVLANID/8)+1];
        UI8_T *vlan_buff;
        BOOL_T flag=FALSE;

        memset(vlan_list, 0, sizeof(vlan_list));

        /*why allocate this number, because vlan list string may be too large*/
        /*so allocate such big memory to store this string*/
        if((vlan_buff = calloc(512*4, sizeof(UI8_T))) == NULL)
        {
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
        }

        while(DHCPV6SNP_TYPE_OK == DHCPV6SNP_PMGR_GetNextConfiguredVlanSnoopingStatus(&vid, &vlan_status))
        {

            vlan_list[(UI32_T)((vid-1)/8)]  |= (1 << ( 7 - ((vid-1)%8)));
            flag=TRUE;
        }

        if(flag)
        {
            CLI_LIB_Bitmap_To_List((char *)vlan_list, (char *)vlan_buff, 512*4, SYS_DFLT_DOT1QMAXVLANID,TRUE);
            if(vlan_status == DHCPV6SNP_TYPE_VLAN_SNOOPING_ENABLE)
            {
                APPEND_RUNNING_CFG_1("ipv6 dhcp snooping vlan %s\n", vlan_buff);
            }

            if(vlan_status == DHCPV6SNP_TYPE_VLAN_SNOOPING_DISABLE)
            {
                APPEND_RUNNING_CFG_1("no ipv6 dhcp snooping vlan %s\n", vlan_buff);
            }
        }
        free(vlan_buff);
    }

    APPEND_RUNNING_CFG_0("!\n");

    return buffer_count;
}
#endif

#if (SYS_CPNT_NDSNP == TRUE)
static UI32_T CLI_RUNCFG_Get_Ndsnp_Parameter ( UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    UI32_T  buffer_count = b_count;
    UI8_T   global_status=0;
    UI32_T  vid=0;
    UI8_T   vlan_status=0;
    UI32_T  timeout=0;
    UI8_T   auto_detect=0;
    UI8_T   retransmit_count=0;
    UI32_T  retransmit_interval=0;
    /* get global snooping status */
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NDSNP_POM_GetRunningGlobalSnoopingStatus(&global_status))
    {
        if(NDSNP_TYPE_GLOBAL_SNOOPING_ENABLE == global_status)
        {
            APPEND_RUNNING_CFG_0("ipv6 nd snooping\n");
        }

        if(NDSNP_TYPE_GLOBAL_SNOOPING_DISABLE == global_status)
        {
            APPEND_RUNNING_CFG_0("no ipv6 nd snooping\n");
        }
    }

    /* get vlan snooping status */
    {
        UI8_T vlan_list[(SYS_DFLT_DOT1QMAXVLANID/8)+1];
        UI8_T *vlan_buff;
        BOOL_T flag=FALSE;

        memset(vlan_list, 0, sizeof(vlan_list));

        /*why allocate this number, because vlan list string may be too large*/
        /*so allocate such big memory to store this string*/
        if((vlan_buff = calloc(512*4, sizeof(UI8_T))) == NULL)
        {
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
        }

        while(NDSNP_TYPE_OK == NDSNP_POM_GetNextConfiguredVlanSnoopingStatus(&vid, &vlan_status))
        {
             vlan_list[(UI32_T)((vid-1)/8)]  |= (1 << ( 7 - ((vid-1)%8)));
             flag=TRUE;
        }

        if(flag)
        {
            CLI_LIB_Bitmap_To_List((char *)vlan_list, (char *)vlan_buff, 512*4, SYS_DFLT_DOT1QMAXVLANID,TRUE);
            if(SYS_DFLT_NDSNP_VLAN_SNOOPING_STATUS == NDSNP_TYPE_VLAN_SNOOPING_DISABLE)
            {
                APPEND_RUNNING_CFG_1("ipv6 nd snooping vlan %s\n", vlan_buff);
            }

            if(SYS_DFLT_NDSNP_VLAN_SNOOPING_STATUS == NDSNP_TYPE_VLAN_SNOOPING_ENABLE)
            {
                APPEND_RUNNING_CFG_1("no ipv6 nd snooping vlan %s\n", vlan_buff);
            }
        }
        free(vlan_buff);
    }

    /* get prefix timeout */
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NDSNP_POM_GetRunningPrefixTimeout(&timeout))
    {
        APPEND_RUNNING_CFG_1("ipv6 nd snooping prefix timeout %lu\n",(unsigned long)timeout);
    }

    /* get user binding auto-detection */
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NDSNP_POM_GetRunningAutoDetect(&auto_detect))
    {
        if(NDSNP_TYPE_AUTODETECT_ENABLE == auto_detect)
        {
            APPEND_RUNNING_CFG_0("ipv6 nd snooping auto-detect\n");
        }

        if(NDSNP_TYPE_AUTODETECT_DISABLE == auto_detect)
        {
            APPEND_RUNNING_CFG_0("no ipv6 nd snooping auto-detect\n");
        }
    }

    /* get user binding auto-detection retransmit count */
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NDSNP_POM_GetRunningRetransmitCount(&retransmit_count))
    {
        APPEND_RUNNING_CFG_1("ipv6 nd snooping auto-detect retransmit count %u\n",retransmit_count);
    }

    /* get user binding auto-detection retransmit interval */
    if(SYS_TYPE_GET_RUNNING_CFG_SUCCESS == NDSNP_POM_GetRunningRetransmitInterval(&retransmit_interval))
    {
        APPEND_RUNNING_CFG_1("ipv6 nd snooping auto-detect retransmit interval %lu\n",(unsigned long)retransmit_interval);
    }

    return buffer_count;
}
#endif

#if (SYS_CPNT_IPV6_SOURCE_GUARD == TRUE)
static UI32_T CLI_RUNCFG_Get_Ip6sg_Parameter ( UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    UI32_T  buffer_count = b_count;
    IP6SG_TYPE_Binding_T binding;
    UI32_T  unit=0;
    UI32_T  port=0;
    UI32_T  trunk_id=0;
    UI32_T  lport_type=0;
    char    addr_buf[L_INET_MAX_IPADDR_STR_LEN + 1] = {0};

    memset(&binding, 0, sizeof(binding));
    while(IP6SG_TYPE_OK == IP6SG_POM_GetNextStaticBindingEntry(&binding))
    {
        APPEND_RUNNING_CFG("ipv6 source-guard binding ");
        APPEND_RUNNING_CFG_6("%02x-%02x-%02x-%02x-%02x-%02x ",
            binding.link_layer_addr[0],binding.link_layer_addr[1],
            binding.link_layer_addr[2],binding.link_layer_addr[3],
            binding.link_layer_addr[4],binding.link_layer_addr[5]);
        APPEND_RUNNING_CFG_1("vlan %lu ",(unsigned long)binding.vid);

        if (L_INET_RETURN_SUCCESS == L_INET_InaddrToString((L_INET_Addr_T *)&binding.ipv6_addr,
                                                           addr_buf,
                                                           sizeof(addr_buf)))
        {
            APPEND_RUNNING_CFG_1("%s ",addr_buf);
        }

        lport_type = SWCTRL_PMGR_LogicalPortToUserPort(binding.lport, &unit, &port, &trunk_id);
        if(SWCTRL_LPORT_NORMAL_PORT == lport_type)
        {
            APPEND_RUNNING_CFG_2("interface ethernet %lu/%lu\n", (unsigned long)unit, (unsigned long)port);
        }
    }
    return buffer_count;
}
#endif


#if (SYS_CPNT_WEBAUTH == TRUE)
static UI32_T CLI_RUNCFG_Get_Webauth_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;

    {
        UI8_T  status;

        if (WEBAUTH_PMGR_GetRunningSystemStatus(&status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if (status == VAL_webauthEnable_enabled)
            {
                APPEND_RUNNING_CFG_0("web-auth system-auth-control\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no web-auth system-auth-control\n");
            }
        }
    }

#if 0 /* 2007/11/09, chengrui_yeh, The following web-auth login url feature aren't supported yet. */
    /* web-auth login-page-url */
    {
        char login_url[WEBAUTH_TYPE_MAX_URL_LENGTH+1];

        if (WEBAUTH_PMGR_GetRunningLoginURL(login_url) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("web-auth login-page-url %s\n", login_url);
        }
    }

    /* web-auth login-fail-page-url */
    {
        char login_fail_url[WEBAUTH_TYPE_MAX_URL_LENGTH+1];

        if (WEBAUTH_PMGR_GetRunningLoginFailURL(login_fail_url) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("web-auth login-fail-page-url %s\n", login_fail_url);
        }
    }

    /* web-auth login-success-page-url */
    {
        char login_success_url[WEBAUTH_TYPE_MAX_URL_LENGTH+1];

        if (WEBAUTH_PMGR_GetRunningLoginSuccessURL(login_success_url) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("web-auth login-success-page-url %s\n", login_success_url);
        }
    }
#endif /* endif */

    /* web-auth session-timeout timeout */
    {
        UI16_T session_timeout;

        if (WEBAUTH_PMGR_GetRunningSessionTimeout(&session_timeout) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("web-auth session-timeout %d\n", session_timeout);
        }
    }

    /* web-auth quiet-period seconds */
    {
        UI16_T quiet_period;

        if (WEBAUTH_PMGR_GetRunningQuietPeriod(&quiet_period) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("web-auth quiet-period %d\n", quiet_period);
        }
    }

    /* web-auth login-attempts count */
    {
        UI8_T login_attempt;

        if (WEBAUTH_PMGR_GetRunningMaxLoginAttempt(&login_attempt) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("web-auth login-attempts %d\n", login_attempt);
        }
    }

    APPEND_RUNNING_CFG_0("!\n");
    return buffer_count;
}
#endif /* #if(SYS_CPNT_WEBAUTH == TRUE) */

#if (SYS_CPNT_DAI == TRUE)
static UI32_T CLI_RUNCFG_Get_DAI_Parameter ( UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    UI32_T  buffer_count = b_count;
    char buf[32];

    memset(buf,0,32);


    /* ip arp inspection */
    {
        UI8_T  status;

        if (DAI_PMGR_GetGlobalDaiStatus(&status) == DAI_TYPE_OK)
        {
            if ( status != DAI_TYPE_GLOBAL_DEFAULT )
            {
                if (status == DAI_TYPE_GLOBAL_ENABLED)
                {
                    APPEND_RUNNING_CFG_0("ip arp inspection\n");
                }
                else
                {
                    APPEND_RUNNING_CFG_0("no ip arp inspection\n");
                }
            }
        }
    }
    /*ip arp inspection vlan*/
    {
        UI8_T vlan_list[(SYS_DFLT_DOT1QMAXVLANID/8)+1];
        UI8_T *vlan_buff;
        UI8_T status=0;
        BOOL_T flag=FALSE;
        UI32_T vid=0;
        DAI_TYPE_VlanInfo_T vlan_info;

        memset(vlan_list, 0, sizeof(vlan_list));

        /*why allocate this number, because vlan list string may be too large*/
        /*so allocate such big memory to store this string*/
        if((vlan_buff = calloc(512*4, sizeof(UI8_T))) == NULL)
        {
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
        }

        memset(&vlan_info, 0, sizeof(vlan_info));
        while(DAI_TYPE_OK == DAI_PMGR_GetNextVlanConfig(&vid,&vlan_info, &status))
        {
            if(DAI_TYPE_VLAN_ENABLED == status)
            {
                vlan_list[(UI32_T)((vid-1)/8)]  |= (1 << ( 7 - ((vid-1)%8)));
                flag=TRUE;
            }
        }

        if(flag)
        {
            CLI_LIB_Bitmap_To_List((char *)vlan_list, (char *)vlan_buff, 512*4, SYS_DFLT_DOT1QMAXVLANID,TRUE);
            APPEND_RUNNING_CFG_1("ip arp inspection vlan %s\n", vlan_buff);
        }
        free(vlan_buff);
    }

    /*ip arp inspection filter*/
    {
        DAI_TYPE_VlanInfo_T vlan_info;
        RULE_TYPE_UI_AclEntry_T acl_entry;
        UI32_T  acl_index =0;
        UI8_T status;
        UI32_T vid=0;

        /*need to get acl_name first*/
        acl_entry.acl_type = RULE_TYPE_ARP_ACL;
        while( L4_PMGR_ACL_GetNextAcl(&acl_index, &acl_entry) == RULE_TYPE_OK)
        {
            if ( acl_entry.acl_type == RULE_TYPE_ARP_ACL )
            {
                /* initialize vid
                 */
                vid=0;
                while(DAI_PMGR_GetNextVlanInfo(&vid,&vlan_info,&status) == DAI_TYPE_OK)
                {
                    if (0 == strcmp((char*)acl_entry.acl_name, (char*)vlan_info.arp_acl_name))
                    {
                        if (vlan_info.acl_static == FALSE)
                        {
                            APPEND_RUNNING_CFG_2("ip arp inspection filter %s vlan %lu\n", acl_entry.acl_name, (unsigned long)vid);
                        }
                        else
                        {
                            APPEND_RUNNING_CFG_2("ip arp inspection filter %s vlan %lu static\n", acl_entry.acl_name, (unsigned long)vid);
                        }
                    }
                }/*end-of-while*/
            }
        }/*end-of-while*/
    }
    /*ip arp inspection log-buffer logs*/
    {
        UI32_T log_message_interval,log_message_number;
        UI32_T ret1,ret2;

        ret1 = DAI_PMGR_GetLoggingMessageInterval(&log_message_interval);
        ret2 = DAI_PMGR_GetLoggingMessageNumber(&log_message_number);

        if( ret1 == DAI_TYPE_OK
            && ret2 == DAI_TYPE_OK
            && (log_message_number != DAI_TYPE_LOG_MSG_NBR_PER_INTERVAL_DEFAULT
               || log_message_interval != DAI_TYPE_LOG_MSG_INTERVAL_DEFAULT ))
        {
            APPEND_RUNNING_CFG_2("ip arp inspection log-buffer logs %lu interval %lu\n", (unsigned long)log_message_number, (unsigned long)log_message_interval);
        }
    }

    /*ip arp inspection validate*/
    {
        UI8_T status=0;

        if (DAI_PMGR_GetAdditionalCheckStatus(&status) == DAI_TYPE_OK)
        {

            if(status == DAI_TYPE_ADDITIONAL_CHECK_ENABLED)
            {
                UI32_T validate_type=0;

                if (DAI_PMGR_GetAdditionalCheckType(&validate_type) == DAI_TYPE_OK)
                {
                    if (validate_type & DAI_TYPE_ADDITIONAL_VALIDATE_DSTMAC)
                    {
                        APPEND_RUNNING_CFG_0("ip arp inspection validate dst-mac\n");
                    }

                    if (validate_type & DAI_TYPE_ADDITIONAL_VALIDATE_IP)
                    {
                        APPEND_RUNNING_CFG_0("ip arp inspection validate ip");
                        if(validate_type & DAI_TYPE_ADDITIONAL_VALIDATE_IP_ALLOW_ZEROS)
                            APPEND_RUNNING_CFG_0(" allow-zeros");
                        APPEND_RUNNING_CFG_0("\n");
                    }

                    if (validate_type & DAI_TYPE_ADDITIONAL_VALIDATE_SRCMAC)
                    {
                        APPEND_RUNNING_CFG_0("ip arp inspection validate src-mac\n");
                    }

                }
            }
        }
    }

    APPEND_RUNNING_CFG_0("!\n");
    return buffer_count;

}
#endif/*#if (SYS_CPNT_DAI == TRUE)*/

#if (SYS_CPNT_ADD == TRUE)
/*added for voice vlan by Eric_Hsu */
static UI32_T CLI_RUNCFG_Get_Voice_Vlan_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    UI32_T voice_vlan_timeout;
    I32_T vid;
    ADD_MGR_VoiceVlanOui_T entry;

    if (ADD_PMGR_GetRunningVoiceVlanId(&vid) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if (vid != VAL_voiceVlanEnabledId_disabled)
        {
            APPEND_RUNNING_CFG_1("voice vlan %ld\n", (long)vid);
        }
        else
        {
            APPEND_RUNNING_CFG_0(" no voice vlan\n");
        }
    }

    if (ADD_PMGR_GetRunningVoiceVlanAgingTime(&voice_vlan_timeout) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        APPEND_RUNNING_CFG_1("voice vlan aging %lu\n", (unsigned long)voice_vlan_timeout);
    }

    memset(entry.oui, 0xff, SYS_ADPT_MAC_ADDR_LEN);
    while(ADD_PMGR_GetNextRunningOuiEntry(&entry)== SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        APPEND_RUNNING_CFG_5("voice vlan mac-address %02X-%02X-%02X-%02X-%02X",
                      entry.oui[0],entry.oui[1],entry.oui[2],entry.oui[3],entry.oui[4]);
        APPEND_RUNNING_CFG_1("-%02X",entry.oui[5]);
        APPEND_RUNNING_CFG_5(" mask %02X-%02X-%02X-%02X-%02X",
                      entry.mask[0],entry.mask[1],entry.mask[2],entry.mask[3],entry.mask[4]);
        APPEND_RUNNING_CFG_1("-%02X",entry.mask[5]);

        if (entry.description[0]!='\0')
        {
            APPEND_RUNNING_CFG_0(" description");
            APPEND_RUNNING_CFG_1(" %s",entry.description);
        }

        APPEND_RUNNING_CFG_0("\r\n");
    }

    return buffer_count;
}
#endif /* #if (SYS_CPNT_ADD == TRUE) */

#if (SYS_CPNT_CLI_MULTI_PRIVILEGE_LEVEL == TRUE)
static UI32_T CLI_RUNCFG_Get_Privilege_Level_Cmd_Parameter(
    UI32_T unit_id, char *buffer, char *temp_buffer,
    UI32_T buffer_size, UI32_T b_count)
{
    UI32_T                  buffer_count = b_count;
    UI32_T                  iter_idx = 0;
    char                    mode_str [20];
    UI32_T                  len = sizeof(mode_str);
    CLI_PrivLvlCmdEntry_T   plce;

    APPEND_RUNNING_CFG_0("!\n");

    while ( CLI_MGR_GetNextRunningPrivilegeCmd (&iter_idx, &plce) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS )
    {
        if (FALSE == CLI_LIB_GetCommandModeString (plce.cmd_mode, mode_str, &len))
            continue;

        APPEND_RUNNING_CFG_4("privilege %s%s level %d %s\n", mode_str,
           ((plce.is_all == TRUE)? " all":""), plce.pri_level, plce.cmd_str);
    }

    return buffer_count;
}
#endif    /* #if (SYS_CPNT_CLI_MULTI_PRIVILEGE_LEVEL == TRUE) */

/*ipv6 MLD snooping*/
#if(SYS_CPNT_MLDSNP==TRUE)
static UI32_T CLI_RUNCFG_Get_MLDSNP_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    MLDSNP_OM_RunningCfg_T mld_confg;
#if(SYS_CPNT_MLDSNP_UNKNOWN_BY_VLAN == TRUE)
    UI8_T vlan_list_unknown_behavior[(SYS_DFLT_DOT1QMAXVLANID/8)+1];
#endif
    UI8_T vlan_list_mld_immediate_leave[(SYS_DFLT_DOT1QMAXVLANID/8)+1];
    UI8_T vlan_list_mld_immediate_leave_host[(SYS_DFLT_DOT1QMAXVLANID/8)+1];
    UI8_T vlan_list_mld_immediate_leave_disable[(SYS_DFLT_DOT1QMAXVLANID/8)+1];
    UI8_T *vlan_buff;
#if(SYS_CPNT_MLDSNP_UNKNOWN_BY_VLAN == TRUE)
    memset(vlan_list_unknown_behavior, 0, sizeof(vlan_list_unknown_behavior));
#endif
    memset(vlan_list_mld_immediate_leave, 0, sizeof(vlan_list_mld_immediate_leave));
    memset(vlan_list_mld_immediate_leave_host, 0, sizeof(vlan_list_mld_immediate_leave_host));
    memset(vlan_list_mld_immediate_leave_disable, 0, sizeof(vlan_list_mld_immediate_leave_disable));

    memset(&mld_confg, 0, sizeof(MLDSNP_OM_RunningCfg_T));
    if(MLDSNP_POM_GetRunningGlobalConf(&mld_confg)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        /*MLD snooping status*/
        if(mld_confg.mldsnp_status_changed==TRUE)
        {
            if(mld_confg.mldsnp_status==MLDSNP_TYPE_MLDSNP_ENABLED)
            {
                APPEND_RUNNING_CFG_0(" ipv6 mld snooping\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" no ipv6 mld snooping\n");
            }
        }
        #if(SYS_CPNT_MLDSNP_PROXY == TRUE)
        if(mld_confg.proxy_reporting != SYS_DFLT_MLDSNP_PROXY_REPORTING)
        {
          if(mld_confg.proxy_reporting == VAL_mldSnoopProxyReporting_enabled)
          {
              APPEND_RUNNING_CFG_0(" ipv6 mld snooping proxy-reporting\n");
          }
          else
          {
              APPEND_RUNNING_CFG_0(" no ipv6 mld snooping proxy-reporting\n");
          }
        }
        if(mld_confg.unsolicit_report_interval != SYS_DFLT_MLDSNP_UNSOLICIT_REPORT_INTERVAL)
        {
            APPEND_RUNNING_CFG_1(" ipv6 mld snooping unsolicited-report-interval %lu\n", (unsigned long)mld_confg.unsolicit_report_interval);
        }
        #endif

        /*querier status*/
        if(mld_confg.querier_status_changed==TRUE)
        {
             if(mld_confg.querier_status==MLDSNP_TYPE_QUERIER_ENABLED)
             {
                APPEND_RUNNING_CFG_0(" ipv6 mld snooping querier\n");
             }
             else
             {
                APPEND_RUNNING_CFG_0(" no ipv6 mld snooping querier\n");
             }

        }

        /*query-interval*/
        if(mld_confg.query_interval_changed==TRUE)
        {
            APPEND_RUNNING_CFG_1(" ipv6 mld snooping query-interval %u\n", mld_confg.query_interval);
        }

        /*query-max-response-time*/
        if(mld_confg.query_response_interval_changed==TRUE)
        {
            APPEND_RUNNING_CFG_1(" ipv6 mld snooping query-max-response-time %u\n", mld_confg.query_response_interval);
        }

        /*robustness*/
        if(mld_confg.robust_value_changed==TRUE)
        {
            APPEND_RUNNING_CFG_1(" ipv6 mld snooping robustness %u\n", mld_confg.robust_value);
        }

        /*router-port-expire-time*/
        if(mld_confg.router_exp_time_changed==TRUE)
        {
            APPEND_RUNNING_CFG_1(" ipv6 mld snooping router-port-expire-time %u\n", mld_confg.router_exp_time);
        }
        #if(SYS_CPNT_MLDSNP_UNKNOWN_BY_VLAN == FALSE)
        /*unknown-multicast*/
        if(mld_confg.unknown_flood_behaviro_changed==TRUE)
        {
            if(mld_confg.unknown_flood_behavior==MLDSNP_TYPE_UNKNOWN_BEHAVIOR_FLOOD)
            {
                APPEND_RUNNING_CFG_0(" ipv6 mld snooping unknown-multicast mode flood\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0(" ipv6 mld snooping unknown-multicast mode to-router-port\n");
            }
        }
        #endif
        /*version*/
        if(mld_confg.version_changed==TRUE)
        {
            APPEND_RUNNING_CFG_1(" ipv6 mld snooping version %u\n", mld_confg.version);
        }
    }

    /*vlan config*/
    {
        MLDSNP_OM_VlanRunningCfg_T vlan_cfg;
        UI8_T  UserPort[20] = {0};
        UI32_T nxt_vid=0;
        UI32_T i, j;
        UI32_T unit = 0;
        UI32_T port= 0;
        UI32_T trunk_id = 0;

        while(TRUE == MLDSNP_POM_GetNextRunningVlanConfig(&nxt_vid, &vlan_cfg))
        {
            /*router port*/
            for(i=1; i<=SYS_ADPT_TOTAL_NBR_OF_LPORT; i++)
            {
                if(vlan_cfg.router_port_bitmap[(UI32_T)((i-1)/8)]  & (1 << (7 - ((i-1) % 8))) )
                {
                    if (i < SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER)
                    {
                        unit = ( ((UI32_T)(((i)-1)/(SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT)))+1 );
                        port = ( (i) - (unit-1)*(SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT) );
                        SYSFUN_Sprintf((char *)UserPort, "ethernet %lu/%lu", (unsigned long)unit, (unsigned long)port);
                    }
                    else
                    {
                        TRK_MGR_TrunkEntry_T trunk_entry;
                        trunk_id = i - SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER + 1;
                        memset(&trunk_entry, 0, sizeof(TRK_MGR_TrunkEntry_T));
                        trunk_entry.trunk_index = trunk_id;
                        if (TRK_PMGR_GetTrunkEntry(&trunk_entry))
                        {
                            /*  add the member ports into port-L_list if the trunk port is dynamic created.*/
                            if (trunk_entry.trunk_creation == VAL_trunkCreation_lacp)
                            {
                                for(j=1; j<=SYS_ADPT_TOTAL_NBR_OF_LPORT; j++)
                                {
                                    if(trunk_entry.trunk_ports[(UI32_T)((j-1)/8)]  & (1 << (7 - ((j-1) % 8))) )
                                    {
                                        unit = ( ((UI32_T)(((j)-1)/(SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT)))+1 );
                                        port = ( (j) - (unit-1)*(SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT) );
                                        SYSFUN_Sprintf((char *)UserPort, "ethernet %lu/%lu", (unsigned long)unit, (unsigned long)port);
                                    }
                                }
                            }
                            else
                            {
                                SYSFUN_Sprintf((char *)UserPort, "port-channel %lu", (unsigned long)trunk_id);
                            }
                        }
                    }
                    APPEND_RUNNING_CFG_2("ipv6 mld snooping vlan %lu mrouter %s\n", (unsigned long)nxt_vid, UserPort);
                }
            }

            /* unknown behavior */
            #if(SYS_CPNT_MLDSNP_UNKNOWN_BY_VLAN == TRUE)
            if(vlan_cfg.flood_behavior != SYS_DFLT_MLDSNP_UNKNOWN_MULTICAST_MOD)
            {
                vlan_list_unknown_behavior[(UI32_T)((nxt_vid-1)/8)]  |= (1 << ( 7 - ((nxt_vid-1)%8)));
            }
            #endif

            /* immediate leave */
            if ((SYS_DFLT_MLDSNP_IMMEIDATE_STATUS != vlan_cfg.immediate_leave_status)
               || (SYS_DFLT_MLDSNP_IMMEIDATE_BYHOST_STATUS != vlan_cfg.immediate_leave_byhost_status))
            {
                if(vlan_cfg.immediate_leave_byhost_status==MLDSNP_TYPE_IMMEDIATE_BYHOST_ENABLED)
                {
                    vlan_list_mld_immediate_leave_host[(UI32_T)((nxt_vid-1)/8)]  |= (1 << ( 7 - ((nxt_vid-1)%8)));
                }
                else if(vlan_cfg.immediate_leave_status==MLDSNP_TYPE_IMMEDIATE_ENABLED)
                {
                    vlan_list_mld_immediate_leave[(UI32_T)((nxt_vid-1)/8)]  |= (1 << ( 7 - ((nxt_vid-1)%8)));
                }
                else
                {
                    vlan_list_mld_immediate_leave_disable[(UI32_T)((nxt_vid-1)/8)]  |= (1 << ( 7 - ((nxt_vid-1)%8)));
                }
            }

            #if(SYS_CPNT_MLDSNP_MLD_REPORT_LIMIT_PER_SECOND_PER_VLAN == TRUE)
            if(vlan_cfg.pkt_ratelimit != SYS_DFLT_MLDSNP_MLD_REPORT_LIMIT_PER_SECOND_PER_VLAN)
            {
                APPEND_RUNNING_CFG_2(" ipv6 mld report-limit rate %d interface vlan %lu\n", vlan_cfg.pkt_ratelimit, (unsigned long)nxt_vid);
            }
            #endif

       }
    }
    #if(SYS_CPNT_MLDSNP_MLD_REPORT_LIMIT_PER_SECOND_PER_PORT == TRUE)
    {/*how about lacp case? need to take care ?*/
        UI32_T ifindex =0;
        UI16_T limit_per_sec;
        SWCTRL_Lport_Type_T type;
        UI32_T unit, port, trunk_id;

        while( (type = SWCTRL_POM_GetNextLogicalPort(&ifindex))!= SWCTRL_LPORT_UNKNOWN_PORT)
        {
          if(FALSE == SWCTRL_POM_LogicalPortToUserPort(ifindex, &unit, &port, &trunk_id))
              continue;

          if(MLDSNP_POM_GetRunnningMldReportLimitPerSec(ifindex, &limit_per_sec) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
          {
            if(type == SWCTRL_LPORT_NORMAL_PORT)
            {
              APPEND_RUNNING_CFG_3(" ipv6 mld report-limit rate %d interface ethernet %lu/%lu\n", limit_per_sec, (unsigned long)unit, (unsigned long)port);
            }
            else
            {
              APPEND_RUNNING_CFG_2(" ipv6 mld report-limit rate %d interface port-channel %lu\n", limit_per_sec, (unsigned long)trunk_id);
            }
          }
        }
    }
    #endif

    /*vlan static*/
    {
        MLDSNP_TYPE_RecordType_T rec_type;
        UI16_T vid = 0, nxt_id=0, joined_port=0;
        char   ipv6_group_addr_str[L_INET_MAX_IP6ADDR_STR_LEN+1] = {0}, ipv6_src_addr_str[L_INET_MAX_IP6ADDR_STR_LEN+1] = {0};
        UI8_T  group_addr[MLDSNP_TYPE_IPV6_DST_IP_LEN] = {0};
        UI8_T source_addr[MLDSNP_TYPE_IPV6_SRC_IP_LEN]={0};
        UI8_T null_source_addr[MLDSNP_TYPE_IPV6_SRC_IP_LEN]={0};

        while(MLDSNP_POM_GetNextRunningPortStaticGroup(&nxt_id, &vid, group_addr, source_addr, &joined_port, &rec_type)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            L_INET_Ntop(L_INET_AF_INET6, (void *)group_addr, ipv6_group_addr_str, sizeof(ipv6_group_addr_str));
            L_INET_Ntop(L_INET_AF_INET6, (void *)source_addr, ipv6_src_addr_str, sizeof(ipv6_src_addr_str));
            {
                char   UserPort[20] = {0};
                UI32_T unit = 0;
                UI32_T port = 0;
                UI32_T trunk_id = 0;

                if (joined_port < SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER)
                {
                    unit = ( ((UI32_T)(((joined_port)-1)/(SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT)))+1 );
                    port = ( (joined_port) - (unit-1)*(SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT) );
                    SYSFUN_Sprintf((char *)UserPort, "ethernet %lu/%lu", (unsigned long)unit, (unsigned long)port);
                }
                else
                {
                    TRK_MGR_TrunkEntry_T trunk_entry;
                    trunk_id = joined_port - SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER + 1;
                    memset(&trunk_entry, 0, sizeof(TRK_MGR_TrunkEntry_T));
                    trunk_entry.trunk_index = trunk_id;
                    if (TRK_PMGR_GetTrunkEntry(&trunk_entry))
                    {
                        /*  add the member ports into port-L_list if the trunk port is dynamic created.*/
                        if (trunk_entry.trunk_creation == VAL_trunkCreation_lacp)
                        {
                            UI32_T j;
                            for(j=1; j<=SYS_ADPT_TOTAL_NBR_OF_LPORT; j++)
                            {
                                if(trunk_entry.trunk_ports[(UI32_T)((j-1)/8)]  & (1 << (7 - ((j-1) % 8))) )
                                {
                                    unit = ( ((UI32_T)(((j)-1)/(SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT)))+1 );
                                    port = ( (j) - (unit-1)*(SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT) );
                                    SYSFUN_Sprintf((char *)UserPort, "ethernet %lu/%lu", (unsigned long)unit, (unsigned long)port);
                                }
                            }
                        }
                        else
                        {
                            SYSFUN_Sprintf((char *)UserPort, "port-channel %lu", (unsigned long)trunk_id);
                        }
                    }
                }

                if(MLDSNP_TYPE_IS_INCLUDE_MODE==rec_type)
                {
                    APPEND_RUNNING_CFG_4(" ipv6 mld snooping vlan %u static %s %s include-list %s\n", vid, ipv6_group_addr_str, UserPort, ipv6_src_addr_str);
                }
                else if(memcmp(source_addr, null_source_addr, MLDSNP_TYPE_IPV6_SRC_IP_LEN))
                {
                    APPEND_RUNNING_CFG_4(" ipv6 mld snooping vlan %u static %s %s exclude-list %s\n", vid, ipv6_group_addr_str, UserPort, ipv6_src_addr_str);
                }
                else
                {
                    APPEND_RUNNING_CFG_3(" ipv6 mld snooping vlan %u static %s %s\n", vid, ipv6_group_addr_str, UserPort);
                }
            }

        }
    }

    /* configure per vlan setting */
    {
        if((vlan_buff = calloc(512*4, sizeof(UI8_T))) == NULL)
        {
            return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
        }

#if(SYS_CPNT_MLDSNP_UNKNOWN_BY_VLAN == TRUE)
        /* unknown behavior */
        CLI_LIB_Bitmap_To_List((char *)vlan_list_unknown_behavior , (char *)vlan_buff, 512*4, SYS_DFLT_DOT1QMAXVLANID,TRUE);
        if (strlen((char *)vlan_buff) > 0)
        {
             if (SYS_DFLT_MLDSNP_UNKNOWN_MULTICAST_MOD == VAL_mldSnoopUnknownMcastMode_toRouterPort)
             {
                 APPEND_RUNNING_CFG_1(" ipv6 mld snooping unknown-multicast vlan %s mode flood\n", vlan_buff);
             }
             else
             {
                 APPEND_RUNNING_CFG_1(" ipv6 mld snooping unknown-multicast vlan %s mode to-router-port\n", vlan_buff);
             }
        }
#endif

        /* immediate leave */
        CLI_LIB_Bitmap_To_List((char *)vlan_list_mld_immediate_leave_host, (char *)vlan_buff, 512*4, SYS_DFLT_DOT1QMAXVLANID,TRUE);
        if (strlen((char *)vlan_buff) > 0)
        {
            APPEND_RUNNING_CFG_1("ipv6 mld snooping vlan %s immediate-leave by-host-ip\n", vlan_buff);
        }

        CLI_LIB_Bitmap_To_List((char *)vlan_list_mld_immediate_leave, (char *)vlan_buff, 512*4, SYS_DFLT_DOT1QMAXVLANID,TRUE);
        if (strlen((char *)vlan_buff) > 0)
        {
            APPEND_RUNNING_CFG_1("ipv6 mld snooping vlan %s immediate-leave\n", vlan_buff);
        }

        CLI_LIB_Bitmap_To_List((char *)vlan_list_mld_immediate_leave_disable, (char *)vlan_buff, 512*4, SYS_DFLT_DOT1QMAXVLANID,TRUE);
        if (strlen((char *)vlan_buff) > 0)
        {
            APPEND_RUNNING_CFG_1("no ipv6 mld snooping vlan %s immediate-leave\n", vlan_buff);
        }

        free(vlan_buff);
    }

    APPEND_RUNNING_CFG_0("!\n");

#if RUNCFG_DEVELOP
    CLI_LIB_PrintStr("ipv6 mld snooping complete\r\n");
#endif

    return buffer_count;

}
#endif

/*Net Access*/
#if (SYS_CPNT_NETACCESS == TRUE)
static UI32_T CLI_RUNCFG_GET_Net_Access_Parameter (UI32_T unit_id, char *buffer,
                                                                char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    UI32_T reauth_time;
#if (SYS_CPNT_NETACCESS_MAC_FILTER_TABLE == TRUE)
    UI32_T filter_id;
    UI8_T  filter_mac[SYS_ADPT_MAC_ADDR_LEN] = {0};
    UI8_T  filter_mask[SYS_ADPT_MAC_ADDR_LEN] = {0};
    char  buff[CLI_DEF_MAX_BUFSIZE] = {0};
    UI8_T  default_mask[SYS_ADPT_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
#endif /* #if (SYS_CPNT_NETACCESS_MAC_FILTER_TABLE == TRUE) */

    if (NETACCESS_PMGR_GetRunningSecureReauthTime(&reauth_time) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        APPEND_RUNNING_CFG_1("mac-authentication reauth-time %lu\n", (unsigned long)reauth_time);
    }

#if (SYS_CPNT_NETACCESS_MAC_FILTER_TABLE == TRUE)
    filter_id = 0;
    while (TRUE == NETACCESS_PMGR_GetRunningFilterMac(&filter_id, filter_mac, filter_mask))
    {
        if (0 != memcmp(filter_mask, default_mask, SYS_ADPT_MAC_ADDR_LEN))
        {
            SYSFUN_Sprintf(buff, "network-access mac-filter %lu mac-address %02X-%02X-%02X-%02X-%02X-%02X mask %02X-%02X-%02X-%02X-%02X-%02X\n",
                (unsigned long)filter_id, filter_mac[0], filter_mac[1], filter_mac[2], filter_mac[3], filter_mac[4], filter_mac[5],
                filter_mask[0], filter_mask[1], filter_mask[2], filter_mask[3], filter_mask[4], filter_mask[5]);
        }
        else
        {
            SYSFUN_Sprintf(buff, "network-access mac-filter %lu mac-address %02X-%02X-%02X-%02X-%02X-%02X\n",
                (unsigned long)filter_id, filter_mac[0], filter_mac[1], filter_mac[2], filter_mac[3], filter_mac[4], filter_mac[5]);
        }

        APPEND_RUNNING_CFG_0(buff);
    }
#endif /* #if (SYS_CPNT_NETACCESS_MAC_FILTER_TABLE == TRUE) */

    APPEND_RUNNING_CFG_0("!\n");

    return buffer_count;
}
#endif    /*#if (SYS_CPNT_NETACCESS == TRUE)*/

/*CWMP*/
#if(SYS_CPNT_CWMP==TRUE)
static UI32_T CLI_RUNCFG_Get_Cwmp_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;

    /*url*/
    {
        char url[CWMP_TYPE_STR_LEN_256];
        if(CWMP_POM_GetRunningUrl(url)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" cwmp url %s\n", url);
        }
    }

    /*user name*/
    {
        char user_name[SYS_ADPT_MAX_USER_NAME_LEN];
        if(CWMP_POM_GetRunningUsername(user_name)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" cwmp username %s\n", user_name);
        }
    }

    /*password*/
    {
        char password[SYS_ADPT_MAX_PASSWORD_LEN];
        if(CWMP_POM_GetRunningUsername(user_name)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" cwmp username %s\n", password);
         }
    }

    /*periodic inform*/
    {
        BOOL_T periodic_Inform_status;
        if(CWMP_POM_GetRunningPeriodicInformEnable(&periodic_Inform_status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(periodic_Inform_status==TRUE)
                APPEND_RUNNING_CFG_0(" cwmp periodic-inform\n");
            else
                APPEND_RUNNING_CFG_0(" no cwmp periodic-inform\n");
        }
    }

    /*periodic inform interval*/
    {
        UI32_T interval;
        if(CWMP_POM_GetRunningPeriodicInformInterval(&interval)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" cwmp periodic-inform interval %lu\n", (unsigned long)interval);
         }
    }

    /*connection-request username*/
    {
        char req_suername[SYS_ADPT_MAX_USER_NAME_LEN];
        if(CWMP_POM_GetRunningConnectionRequestUsername(req_suername)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" cwmp connection-request username %s\n", req_suername);
         }
    }

    /*connection-request password*/
    {
        char req_password[SYS_ADPT_MAX_PASSWORD_LEN];
        if(CWMP_POM_GetRunningConnectionRequestPassword(req_password)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1(" cwmp connection-request password %s\n", req_password);
         }
    }

    APPEND_RUNNING_CFG_0("!\n");

    return buffer_count;

}
#endif
/*cfm*/
#if(SYS_CPNT_CFM==TRUE)
static UI32_T cli_runcfg_get_cfm_parameter_macro(UI32_T unit_id, char *buffer,
                                UI32_T buffer_size, UI32_T b_count, char *str_list, char *print_str)
{
    UI32_T  buffer_count = b_count;
    UI8_T  temp_buffer[CLI_DEF_MAX_BUFSIZE]={0};

    /* Commands:
     * ethernet cfm domain index index name domain-name level level-id [mip-creation {default|explicit|none}]
     * no ethernet cfm domain index index
     */
    {
        CFM_OM_MdInfo_T     md_entry;
        UI32_T              md_index=0;

        while(CFM_OM_GetNextRunningMd(&md_index, &md_entry)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(md_entry.mhf_creation == CFM_TYPE_MHF_CREATION_NONE)
            {
                APPEND_RUNNING_CFG_3("ethernet cfm domain index %lu name %s level %u mip-creation none\n",(unsigned long)md_entry.index, md_entry.name_a, md_entry.level);
            }
            else if(md_entry.mhf_creation == CFM_TYPE_MHF_CREATION_EXPLICIT)
            {
                APPEND_RUNNING_CFG_3("ethernet cfm domain index %lu name %s level %u mip-creation explicit\n",
                                          (unsigned long)md_entry.index, md_entry.name_a, md_entry.level);
            }
            else
            {
                APPEND_RUNNING_CFG_3("ethernet cfm domain index %lu name %s level %u\n",
                                          (unsigned long)md_entry.index, md_entry.name_a, md_entry.level);
            }

            /* Commands:
             * mep archive-hold-time minutes
             * no mep archive-hold-time
             */
            if(md_entry.mep_archive_hold_time!=SYS_DFLT_CFM_ARCHIVE_HOLD_TIME)
            {
                APPEND_RUNNING_CFG_1(" mep archive-hold-time %lu\n", (unsigned long)md_entry.mep_archive_hold_time);
            }

            /* Commands:
             * mep fault-notify lowest-priority priority
             * no mep fault-notify lowest-priority
             */
            if(md_entry.lowest_alarm_pri!=SYS_DFLT_CFM_FNG_LOWEST_ALARM_PRI)
            {
                APPEND_RUNNING_CFG_1(" mep fault-notify lowest-priority %d\n", md_entry.lowest_alarm_pri);
            }

            /* Commands:
             * mep fault-notify alarm-time time
             * no mep fault-notify alarm-time
             */
            if(md_entry.fng_alarm_time!=SYS_DFLT_CFM_FNG_LOWEST_ALARM_TIME)
            {
                APPEND_RUNNING_CFG_1(" mep fault-notify alarm-time %lu\n", (unsigned long)md_entry.fng_alarm_time);
            }

            /* Commands:
             * mep fault-notify reset-time time
             * no mep fault-notify reset-time
             */
            if(md_entry.fng_reset_time!=SYS_DFLT_CFM_FNG_LOWEST_RESET_TIME)
            {
                APPEND_RUNNING_CFG_1(" mep fault-notify reset-time %lu\n", (unsigned long)md_entry.fng_reset_time);
            }

            /* Commands:
             * ma index index name name [vlan vid-list [mip-creation {default|explicit|none}] ]
             * no ma index index [vlan vid-list]
             */
            {
                CFM_OM_MaInfo_T     ma_entry;
                UI32_T              ma_index=0;

                while(CFM_OM_GetNextRunningMa( md_entry.index, &ma_index, &ma_entry)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    if(ma_entry.primary_vid == 0)
                    {
                        APPEND_RUNNING_CFG_2(" ma index %lu name %s\n", (unsigned long)ma_entry.ma_index, ma_entry.ma_name_a);
                    }
                    else
                    {
                        memset(str_list,0,(512*4));
                        APPEND_RUNNING_CFG_3(" ma index %lu name %s vlan %u",
                                                     (unsigned long)ma_entry.ma_index, ma_entry.ma_name_a, ma_entry.primary_vid);
                        ma_entry.vlan_list_a[(UI32_T)((ma_entry.primary_vid-1)/8)]&=~(0x01 << (7 - ((ma_entry.primary_vid-1)%8)));
                        CLI_LIB_Bitmap_To_List((char *)ma_entry.vlan_list_a, str_list, 512*4, SYS_DFLT_DOT1QMAXVLANID,TRUE);
                        {
                            I32_T str_len = strlen(str_list);
                            I32_T process_length = 0;

                            while ((str_len-process_length) > 0)
                            {
                                CLI_Runcfg_ListStrToOneLine(&process_length, 38, str_list, print_str);
                                      APPEND_RUNNING_CFG_1(",%s",print_str);

                            }
                        }
                        if(ma_entry.mhf_creation == CFM_TYPE_MHF_CREATION_NONE)
                        {
                            APPEND_RUNNING_CFG_0(" mip-creation none\n");
                        }
                        else if(ma_entry.mhf_creation == CFM_TYPE_MHF_CREATION_EXPLICIT)
                        {
                            APPEND_RUNNING_CFG_0(" mip-creation explicit\n");
                        }
                        else
                        {
                            APPEND_RUNNING_CFG_0("\n");
                        }
                    }

                    if(CFM_TYPE_DFT_MA_NAME_FORMAT != ma_entry.name_format)
                    {
                        if(ma_entry.name_format == CFM_TYPE_MA_NAME_CHAR_STRING)
                        {
                            APPEND_RUNNING_CFG_1(" ma index %lu name-format character-string\n",
                                             (unsigned long)ma_entry.ma_index);
                        }
                        else if(ma_entry.name_format == CFM_TYPE_MA_NAME_ICC_BASED)
                        {
                            APPEND_RUNNING_CFG_1(" ma index %lu name-format icc-based\n",
                                             (unsigned long)ma_entry.ma_index);
                        }
                    }
                }    /* end of while(CFM_OM_GetNextRunningMa) */
            }

            /* Commands:
             * mep crosscheck mpid id ma ma-name
             * no mep crosscheck mpid id ma ma-name
             */
            {
                UI32_T  ma_index=0;
                UI32_T  remote_mep_id=0;
                UI32_T  current_time=SYS_TIME_GetSystemTicksBy10ms();
                UI8_T   ma_name_a[CFM_TYPE_MA_MAX_NAME_LENGTH+1]={0};

                while(CFM_OM_GetNextRunningCrossCheckMpIdInfo
                        ( md_entry.index, &ma_index, &remote_mep_id, current_time, ma_name_a)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
                {
                    APPEND_RUNNING_CFG_2(" mep crosscheck mpid %lu ma %s\n", (unsigned long)remote_mep_id, ma_name_a);
                }
            }

            APPEND_RUNNING_CFG_0("!\n");
        }    /* end of while(CFM_OM_GetNextRunningMd) */
    }

    /* exit from domain mode, return to global mode */
    APPEND_RUNNING_CFG_0("!\n");

    /* Commands:
     * ethernet cfm enable
     * no ethernet cfm enable
     */
    {
        CFM_TYPE_CfmStatus_T  cfm_status;

        if(CFM_OM_GetRunningCfmGlobalStatus(&cfm_status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(cfm_status == CFM_TYPE_CFM_STATUS_ENABLE)
            {
                APPEND_RUNNING_CFG_0("ethernet cfm enable\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no ethernet cfm enable\n");
            }
        }
    }

    /* Commands:
     * ethernet cfm mep crosscheck start-delay delay
     * no ethernet cfm mep crosscheck start-delay
     */
    {
        UI32_T  delay;

        if(CFM_OM_GetRunningCrossCheckStartDelay(&delay)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("ethernet cfm mep crosscheck start-delay %lu\n", (unsigned long)delay);
        }
    }

    /* Commands:
     * ethernet cfm linktrace cache
     * no ethernet cfm linktrace cache
     */
    {
        CFM_TYPE_LinktraceStatus_T  cache_status;

        if(CFM_OM_GetRunningLinktraceCacheStatus(&cache_status)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(cache_status == CFM_TYPE_LINKTRACE_STATUS_ENABLE)
            {
                APPEND_RUNNING_CFG_0("ethernet cfm linktrace cache\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no ethernet cfm linktrace cache\n");
            }
        }
    }

    /* Commands:
     * ethernet cfm linktrace cache hold-time minutes
     * no ethernet cfm linktrace cache hold-time
     */
    {
        UI32_T  hold_time;

        if(CFM_OM_GetRunningLinktraceHoldTime(&hold_time)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("ethernet cfm linktrace cache hold-time %lu\n", (unsigned long)hold_time);
        }
    }

    /* Commands:
     * ethernet cfm linktrace cache size entries
     * no ethernet cfm linktrace cache size
     */
    {
        UI32_T  size;

        if(CFM_OM_GetRunningLinktraceCacheSize(&size)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_1("ethernet cfm linktrace cache size %lu\n", (unsigned long)size);
        }
    }

    /* Commands:
     * |76543210| bit 7 : ALL, bit 6: MEP_UP, bit 5:MEP_DOWN,bit 4:CONFIG,bit 3:LOOP
     * snmp-server enable traps ethernet cfm cc [mep-up | mep-down | config | loop]
     * no snmp-server enable traps ethernet cfm cc [mep-up | mep-down | config | loop]
     */
    {
        UI8_T  changed_traps;

        if(CFM_OM_GetRunningSnmpCcTrap(&changed_traps)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if( ((changed_traps&0x80)==0x80)&&(FALSE == SYS_DFLT_CFM_SNMP_TRAP_CC_ALL))
            {
                APPEND_RUNNING_CFG_0("snmp-server enable traps ethernet cfm cc\n");
            }
            else
            {
                if(((changed_traps&0x10)==0x10)&&(FALSE == SYS_DFLT_CFM_SNMP_TRAP_CC_CONFIG))
                {
                    APPEND_RUNNING_CFG_0("snmp-server enable traps ethernet cfm cc config\n");
                }
                else if (((changed_traps&0x10)==0x10)&&(TRUE == SYS_DFLT_CFM_SNMP_TRAP_CC_CONFIG))
                {
                    APPEND_RUNNING_CFG_0("no snmp-server enable traps ethernet cfm cc config\n");
                }

                if(((changed_traps&0x20)==0x20)&&(FALSE == SYS_DFLT_CFM_SNMP_TRAP_CC_MEP_DOWN))
                {
                    APPEND_RUNNING_CFG_0("snmp-server enable traps ethernet cfm cc mep-down\n");
                }
                else if (((changed_traps&0x20)==0x20)&&(TRUE == SYS_DFLT_CFM_SNMP_TRAP_CC_MEP_DOWN))
                {
                    APPEND_RUNNING_CFG_0("no snmp-server enable traps ethernet cfm cc mep-down\n");
                }

                if(((changed_traps&0x40)==0x40)&&(FALSE == SYS_DFLT_CFM_SNMP_TRAP_CC_MEP_UP))
                {
                    APPEND_RUNNING_CFG_0("snmp-server enable traps ethernet cfm cc mep-up\n");
                }
                else if (((changed_traps&0x40)==0x40)&&(TRUE == SYS_DFLT_CFM_SNMP_TRAP_CC_MEP_UP))
                {
                    APPEND_RUNNING_CFG_0("no snmp-server enable traps ethernet cfm cc mep-up\n");
                }
                if(((changed_traps&0x08))==0x08&&(FALSE == SYS_DFLT_CFM_SNMP_TRAP_CC_LOOP))
                {
                    APPEND_RUNNING_CFG_0("snmp-server enable traps ethernet cfm cc loop\n");
                }
                else if(((changed_traps&0x08))==0x08&&(TRUE == SYS_DFLT_CFM_SNMP_TRAP_CC_LOOP))
                {
                    APPEND_RUNNING_CFG_0("no snmp-server enable traps ethernet cfm cc loop\n");
                }

            }
        }
    }

    /* Commands:
     * |76543210| bit 7 : ALL, bit 6: MA_UP, bit 5:MEP_MISSING,bit 4:MEP_UNKNOWN,bit
     * snmp-server enable traps ethernet cfm crosscheck [mep-unknown | mep-missing | ma-up]
     * no snmp-server enable traps ethernet cfm crosscheck [mep-unknown | mep-missing |ma-up]
     */
    {
        UI8_T  changed_traps;

        if(CFM_OM_GetRunningSnmpCrossCheckTrap(&changed_traps)==SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            if(((changed_traps&0x80)==0x80)&&(FALSE == SYS_DFLT_CFM_SNMP_TRAP_CROSS_CHECK_ALL))
            {
                APPEND_RUNNING_CFG_0("snmp-server enable traps ethernet cfm crosscheck\n");
            }
            else
            {
                if(((changed_traps&0x10)==0x10)&&(FALSE == SYS_DFLT_CFM_SNMP_TRAP_CROSS_CHECK_UNKNOWN))
                {
                    APPEND_RUNNING_CFG_0("snmp-server enable traps ethernet cfm crosscheck mep-unknown\n");
                }
                else if(((changed_traps&0x10)==0x10)&&(TRUE == SYS_DFLT_CFM_SNMP_TRAP_CROSS_CHECK_UNKNOWN))
                {
                    APPEND_RUNNING_CFG_0("no snmp-server enable traps ethernet cfm crosscheck mep-unknown\n");
                }

                if(((changed_traps&0x20)==0x20)&&(FALSE == SYS_DFLT_CFM_SNMP_TRAP_CROSS_CHECK_MEP_MISSING))
                {
                    APPEND_RUNNING_CFG_0("snmp-server enable traps ethernet cfm crosscheck mep-missing\n");
                }
                else if(((changed_traps&0x20)==0x20)&&(TRUE == SYS_DFLT_CFM_SNMP_TRAP_CROSS_CHECK_MEP_MISSING))
                {
                    APPEND_RUNNING_CFG_0("no snmp-server enable traps ethernet cfm crosscheck mep-missing\n");
                }

                if(((changed_traps&0x40)==0x40)&&(FALSE == SYS_DFLT_CFM_SNMP_TRAP_CROSS_CHECK_MA_UP))
                {
                    APPEND_RUNNING_CFG_0("snmp-server enable traps ethernet cfm crosscheck ma-up\n");
                }
                else if(((changed_traps&0x40)==0x40)&&(TRUE == SYS_DFLT_CFM_SNMP_TRAP_CROSS_CHECK_MA_UP))
                {
                    APPEND_RUNNING_CFG_0("no snmp-server enable traps ethernet cfm crosscheck ma-up\n");
                }
            }
        }
    }

    /* need md_index to get information */
    {
        UI32_T          md_index=0, ma_index=0;
        CFM_OM_MdInfo_T md_entry;
        CFM_OM_MaInfo_T ma;

        memset(&md_entry , 0, sizeof(CFM_OM_MdInfo_T));

        while(CFM_OM_GetNextRunningMd(&md_index, &md_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            ma_index = 0;
            while(CFM_OM_GetNextRunningMa(md_index, &ma_index, &ma) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
            {
#if (SYS_CPNT_CFM_MA_NAME_UNIQUE_PER_DOMAIN == TRUE)
                /* Commands:
                 * ethernet cfm cc enable md md_name ma ma_name
                 * no ethernet cfm cc enable md md_name ma ma_name
                */
                if(ma.ccm_status != SYS_DFLT_CFM_CCM_STATUS)
                {
                    if(ma.ccm_status == CFM_TYPE_CCM_STATUS_ENABLE)
                    {
                        APPEND_RUNNING_CFG_2("ethernet cfm cc enable md %s ma %s\n",
                                md_entry.name_a, ma.ma_name_a);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_2("no ethernet cfm cc enable md %s ma %s\n",
                                md_entry.name_a, ma.ma_name_a);
                    }
                }
                /* Commands:
                 * ethernet cfm cc md md_name ma ma_name interval interval-level
                 * no ethernet cfm cc md md_name ma ma_name interval
                 */
                if(ma.interval!= SYS_DFLT_CFM_CCM_INTERVAL)
                {
                    APPEND_RUNNING_CFG_3("ethernet cfm cc md %s ma %s interval %d\n",
                                md_entry.name_a, ma.ma_name_a, ma.interval);
                }
                /* Commands:
                 * ethernet cfm ais level level_id md md_name ma ma_name
                 * no ethernet cfm ais level md md_name ma ma_name
                 */
                if(ma.ais_level!= SYS_DFLT_CFM_AIS_LEVEL)
                {
                    APPEND_RUNNING_CFG_3("ethernet cfm ais level %d md %s ma %s\n",
                                ma.ais_level, md_entry.name_a, ma.ma_name_a);
                }
                /* Commands:
                 * ethernet cfm ais period period md md_name ma ma_name
                 * no ethernet cfm ais period md md_name ma ma_name
                 */
                if(ma.ais_period!= SYS_DFLT_CFM_AIS_PERIOD)
                {
                    APPEND_RUNNING_CFG_3("ethernet cfm ais period %d md %s ma %s\n",
                                ma.ais_period, md_entry.name_a, ma.ma_name_a);
                }

                /* Commands:
                 * ethernet cfm ais md md_name ma ma_name
                 * no ethernet cfm ais md md_name ma ma_name
                 */
                if(ma.ais_status!= SYS_DFLT_CFM_AIS_STATUS)
                {
                    if(ma.ais_status == CFM_TYPE_AIS_STATUS_ENABLE)
                    {
                        APPEND_RUNNING_CFG_2("ethernet cfm ais md %s ma %s\n",
                                md_entry.name_a, ma.ma_name_a);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_2("no ethernet cfm ais md %s ma %s\n",
                                md_entry.name_a, ma.ma_name_a);
                    }
                }

                /* Commands:
                 * ethernet cfm ais suppress alarm md md_name ma ma_name
                 * no ethernet cfm ais suppress alarm md md_name ma ma_name
                 */
                if(ma.ais_suppress_status!= SYS_DFLT_CFM_AIS_SUPRESS_STATUS)
                {
                    if(ma.ais_suppress_status == CFM_TYPE_AIS_STATUS_ENABLE)
                    {
                        APPEND_RUNNING_CFG_2("ethernet cfm ais suppress alarm md %s ma %s\n",
                                md_entry.name_a, ma.ma_name_a);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_2("no ethernet cfm ais suppress alarm md %s ma %s\n",
                                md_entry.name_a, ma.ma_name_a);
                    }
                }
#else
                /* Commands:
                 * ethernet cfm cc enable ma ma-name
                 * no ethernet cfm cc enable ma ma-name
                */
                if(ma.ccm_status != SYS_DFLT_CFM_CCM_STATUS)
                {
                    if(ma.ccm_status == CFM_TYPE_CCM_STATUS_ENABLE)
                    {
                        APPEND_RUNNING_CFG_1("ethernet cfm cc enable ma %s\n", ma.ma_name_a);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_1("no ethernet cfm cc enable ma %s\n", ma.ma_name_a);
                    }
                }
                /* Commands:
                 * ethernet cfm cc ma ma-name interval interval-level
                 * no ethernet cfm cc ma ma-name interval
                 */
                if(ma.interval!= SYS_DFLT_CFM_CCM_INTERVAL)
                {
                    APPEND_RUNNING_CFG_2("ethernet cfm cc ma %s interval %d\n", ma.ma_name_a, ma.interval);
                }
                /* Commands:
                 * ethernet cfm ais level level_id ma ma-name
                 * no ethernet cfm ais level ma ma-name
                 */
                if(ma.ais_level!= SYS_DFLT_CFM_AIS_LEVEL)
                {
                    APPEND_RUNNING_CFG_2("ethernet cfm ais level %d ma %s\n",ma.ais_level, ma.ma_name_a);
                }
                /* Commands:
                 * ethernet cfm ais period period ma ma-name
                 * no ethernet cfm ais period ma ma-name
                 */
                if(ma.ais_period!= SYS_DFLT_CFM_AIS_PERIOD)
                {
                    APPEND_RUNNING_CFG_2("ethernet cfm ais period %d ma %s\n",ma.ais_period, ma.ma_name_a);
                }

                /* Commands:
                 * ethernet cfm ais ma ma-name
                 * no ethernet cfm ais ma ma-name
                 */
                if(ma.ais_status!= SYS_DFLT_CFM_AIS_STATUS)
                {
                    if(ma.ais_status == CFM_TYPE_AIS_STATUS_ENABLE)
                    {
                        APPEND_RUNNING_CFG_1("ethernet cfm ais ma %s\n", ma.ma_name_a);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_1("no ethernet cfm ais ma %s\n", ma.ma_name_a);
                    }
                }

                /* Commands:
                 * ethernet cfm ais suppress alarm ma ma-name
                 * no ethernet cfm ais suppress alarm ma ma-name
                 */
                if(ma.ais_suppress_status!= SYS_DFLT_CFM_AIS_SUPRESS_STATUS)
                {
                    if(ma.ais_suppress_status == CFM_TYPE_AIS_STATUS_ENABLE)
                    {
                        APPEND_RUNNING_CFG_1("ethernet cfm ais suppress alarm ma %s\n", ma.ma_name_a);
                    }
                    else
                    {
                        APPEND_RUNNING_CFG_1("no ethernet cfm ais suppress alarm ma %s\n", ma.ma_name_a);
                    }
                }
#endif /* #if (SYS_CPNT_CFM_MA_NAME_UNIQUE_PER_DOMAIN == TRUE) */
            } /* while(CFM_OM_GetNextRunningMa(...) */
        }
    }
    APPEND_RUNNING_CFG_0("!\n");

    return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_Cfm_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T  return_value;
    char   *str_list;
    char   *print_str;

    if( (str_list = calloc(512*4,sizeof(UI8_T))) == NULL )
    {   /*why allocate this number, because vlan list string may be too large*/
        /*so allocate such big memory to store this string*/
        return CLII_ERR_MEMORY_NOT_ENOUGH;
    }

    if( (print_str = calloc((CLI_DEF_MAX_BUFSIZE-38), sizeof(UI8_T))) == NULL )
    {
        free(str_list);
        return CLII_ERR_MEMORY_NOT_ENOUGH;
    }

    return_value = cli_runcfg_get_cfm_parameter_macro(unit_id, buffer,
                                               buffer_size, b_count, str_list, print_str);

    free(print_str);
    free(str_list);

    return return_value;
}
#endif

#if (SYS_CPNT_SYSMGMT_DEFERRED_RELOAD == TRUE)
static UI32_T CLI_RUNCFG_Get_Reload_Parameter(
    UI32_T unit_id,
    char *buffer,
    char *temp_buffer,
    UI32_T buffer_size,
    UI32_T b_count
    )
{
    UI32_T buffer_count = b_count;
    SYS_RELOAD_OM_RELOADAT_DST reload_at;
    SYS_RELOAD_OM_RELOADREGULARITY_DST reload_regularity;

    if (SYS_PMGR_GetRunningReloadAtInfo(&reload_at) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        char *month_ar[12] = {
            "January", "February", "March", "April", "May", "June",
            "July",  "August", "September", "October", "November", "December"
        };

        /* reload at hour minute month day year */
        APPEND_RUNNING_CFG_2("reload at %ld %ld ", (long)reload_at.hour, (long)reload_at.minute);
        APPEND_RUNNING_CFG_3("%s %ld %ld\n", month_ar[reload_at.month-1], (long)reload_at.day, (long)reload_at.year);
    }

    if (SYS_PMGR_GetRunningReloadRegularityInfo(&reload_regularity) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        char *day_ar[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

        /* reload regularity hour minute period {daily | weekly day_of_week | monthly day} */
        APPEND_RUNNING_CFG_2("reload regularity %ld %ld period ", (long)reload_regularity.hour, (long)reload_regularity.minute);
        if (reload_regularity.period == SYS_RELOAD_TYPE_REGULARITY_PERIOD_DAILY)
        {
            APPEND_RUNNING_CFG_0("daily\n");
        }
        else if (reload_regularity.period == SYS_RELOAD_TYPE_REGULARITY_PERIOD_WEEKLY)
        {
            APPEND_RUNNING_CFG_1("weekly %s\n", day_ar[reload_regularity.day_of_week]);
        }
        else
        {
            APPEND_RUNNING_CFG_1("monthly %ld\n", (long)reload_regularity.day_of_month);
        }
    }

    APPEND_RUNNING_CFG_0("!\n");
    return buffer_count;
}
#endif /* #if (SYS_CPNT_SYSMGMT_DEFERRED_RELOAD == TRUE) */


/* auto traffic control */
#if (SYS_CPNT_ATC_STORM == TRUE)
static UI32_T CLI_RUNCFG_Get_ATC_Global_Parameter ( UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    SWCTRL_ATCBroadcastStormTimer_T bcast_timer_entry;
    SWCTRL_ATCMulticastStormTimer_T mcast_timer_entry;
    UI32_T  buffer_count = b_count;

#if (SYS_CPNT_ATC_BSTORM == TRUE)
    if (SWCTRL_PMGR_GetRunningATCBroadcastStormTimer(&bcast_timer_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS )
    {
        /* apply timer */
        if (bcast_timer_entry.atc_broadcast_storm_traffic_control_on_timer != SYS_DFLT_ATC_BSTORM_TC_ON_TIMER)
        {
            APPEND_RUNNING_CFG_1("auto-traffic-control broadcast apply-timer %lu\n", (unsigned long)bcast_timer_entry.atc_broadcast_storm_traffic_control_on_timer);
        }

        /* release timer */
        if (bcast_timer_entry.atc_broadcast_storm_traffic_control_release_timer != SYS_DFLT_ATC_BSTORM_TC_RELEASE_TIMER)
        {
            APPEND_RUNNING_CFG_1("auto-traffic-control broadcast release-timer %lu\n", (unsigned long)bcast_timer_entry.atc_broadcast_storm_traffic_control_release_timer);
        }

        APPEND_RUNNING_CFG_0("!\n");
    }
#endif

#if (SYS_CPNT_ATC_MSTORM == TRUE)
    if (SWCTRL_PMGR_GetRunningATCMulticastStormTimer(&mcast_timer_entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS )
    {
        /* apply timer */
        if (mcast_timer_entry.atc_multicast_storm_traffic_control_on_timer != SYS_DFLT_ATC_MSTORM_TC_ON_TIMER)
        {
            APPEND_RUNNING_CFG_1("auto-traffic-control multicast apply-timer %lu\n", (unsigned long)mcast_timer_entry.atc_multicast_storm_traffic_control_on_timer);
        }

        /* release timer */
        if (mcast_timer_entry.atc_multicast_storm_traffic_control_release_timer != SYS_DFLT_ATC_MSTORM_TC_RELEASE_TIMER)
        {
            APPEND_RUNNING_CFG_1("auto-traffic-control multicast release-timer %lu\n", (unsigned long)mcast_timer_entry.atc_multicast_storm_traffic_control_release_timer);
        }

        APPEND_RUNNING_CFG_0("!\n");
    }
#endif

    return buffer_count;
}
#endif

/* for mac-based VLAN */
#if (SYS_CPNT_MAC_VLAN == TRUE)
static UI32_T CLI_RUNCFG_Get_MAC_VLAN_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer,
                                            UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    VLAN_TYPE_MacVlanEntry_T entry;
    char mac_str[18] = {0};
    #if(SYS_CPNT_MAC_VLAN_WITH_MASK == TRUE)
    char mask_str[18] = {0};
    #endif
    APPEND_RUNNING_CFG_0("!\n");

    memset(&entry, 0, sizeof(entry));

    while (VLAN_OM_GetNextRunningMacVlanEntry(&entry) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        CLI_LIB_EAtoStr(entry.mac_address, mac_str);
      #if(SYS_CPNT_MAC_VLAN_WITH_MASK == TRUE)
        CLI_LIB_EAtoStr(entry.mask, mask_str);
        #if (SYS_CPNT_MAC_VLAN_WITH_PRIORITY == TRUE)
        APPEND_RUNNING_CFG_4("mac-vlan mac-address %s mask %s vlan %u priority %u\n", mac_str, mask_str, entry.vid, entry.priority);
        #else
        APPEND_RUNNING_CFG_3("mac-vlan mac-address %s mask %s vlan %u\n", mac_str, mask_str, entry.vid);
        #endif
      #else
        #if (SYS_CPNT_MAC_VLAN_WITH_PRIORITY == TRUE)
        APPEND_RUNNING_CFG_3("mac-vlan mac-address %s vlan %u priority %u\n", mac_str, entry.vid, entry.priority);
        #else
        APPEND_RUNNING_CFG_2("mac-vlan mac-address %s vlan %u\n", mac_str, entry.vid);
        #endif
      #endif
    }

    APPEND_RUNNING_CFG_0("!\n");

    return buffer_count;
}
#endif
#if (SYS_CPNT_RSPAN == TRUE)
/*-----------------------------------------------------------
 * ROUTINE NAME - cli_runcfg_rspan_construct_rx_tx_list
 *-----------------------------------------------------------
 * PURPOSE : This function contructs the rx_tx_list from src_rx and src_tx.
 *           If both the rx and tx attributes are selected for a port,
 *           the both_rx_tx attribute will be set.
 * INPUT   : src_rx_ar[] - The array of rx attribute of the source ports.
 *         : src_tx_ar[] - The array of tx attribute of the source ports.
 *         : max_port_number - The maximum number of ports allowed in the RSPAN session.
 * OUTPUT  : src_both_rx_tx_ar[] - The array of both rx and tx attribute of the source ports.
 *         : empty_rx_list_p - a pointer to a boolean value indicating whether the rx_list is empty.
 *         : empty_tx_list_p - a pointer to a boolean value indicating whether the tx_list is empty.
 *         : empty_rx_tx_list_p - a pointer to a boolean value indicating whether both the rx_list
 *                                and the tx_list are empty.
 * RETURN  : None.
 * NOTE    : This function is called by CLI_RUNCFG_Get_Rspan_Parameter().
 *           3-31-2008, Kwok-yam TAM.
 *----------------------------------------------------------
 */
static void cli_runcfg_rspan_construct_rx_tx_list(UI8_T src_rx_ar[], UI8_T src_tx_ar[], UI32_T max_port_number, UI8_T src_both_rx_tx_ar[], BOOL_T *empty_rx_list_p, BOOL_T *empty_tx_list_p, BOOL_T *empty_rx_tx_list_p)
{
    UI32_T rx_on;
    UI32_T tx_on;
    int k;
    UI8_T both_value[SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST]={0};

    *empty_rx_list_p=TRUE;
    *empty_tx_list_p=TRUE;
    *empty_rx_tx_list_p=TRUE;
    memset(src_both_rx_tx_ar, 0, sizeof(UI8_T)*((max_port_number+7)/8));

    for (k=1; k<=max_port_number; k++)
    {
        rx_on=src_rx_ar[(UI32_T)((k-1)/8)] & (1 << (7 - ((k-1)%8)));
        tx_on=src_tx_ar[(UI32_T)((k-1)/8)] & (1 << (7 - ((k-1)%8)));
        if(rx_on && tx_on)
        {
            both_value[(UI32_T)((k-1)/8)]=both_value[(UI32_T)((k-1)/8)]|rx_on;
            *empty_rx_tx_list_p=FALSE;
            src_both_rx_tx_ar[(UI32_T)((k-1)/8)]=both_value[(UI32_T)((k-1)/8)];
        }
        else if(rx_on)
        {
            *empty_rx_list_p=FALSE;
        }
        else if(tx_on)
        {
            *empty_tx_list_p=FALSE;
        }
    }
}

/*-----------------------------------------------------------
 * ROUTINE NAME - cli_runcfg_rspan_print_conditional
 *-----------------------------------------------------------
 * PURPOSE : This function is the conditional to decide whether to print the attribute of a port.
 *           If the port is selected, print its RSPAN attribute.  The input array src_ar[]
 *           is one of the following --- src_rx_ar[], src_tx_ar[], src_both_rx_tx_ar[].
 * INPUT   : src_ar[] - This is one of the following --- src_rx_ar[], src_tx_ar[], src_both_rx_tx_ar[].
 *         : src_both_rx_tx_ar[] - The array of both rx and tx attribute of the source ports.
 *         : k - port index.
 *         : mode - RSPAN source port mirror mode, which is one of the following ---
 *           VAL_mirrorType_rx,
 *           VAL_mirrorType_tx,
 *           VAL_mirrorType_both.
 * OUTPUT  : None.
 * RETURN  : 0 for ports which are not selected.
 *           1 (non-zero) for selected ports.
 * NOTE    : This function is called by cli_runcfg_rspan_print_source_meta_config().
 *           3-31-2008, Kwok-yam TAM.
 *----------------------------------------------------------
 */
static char cli_runcfg_rspan_print_conditional(UI8_T src_ar[], UI8_T src_both_rx_tx_ar[], int k, char mode)
{
    if(mode==VAL_mirrorType_both)
    {
        return (src_ar[(UI32_T)((k-1)/8)] & (1 << (7-((k-1)%8))) );
    }
    else
    {
        return (src_ar[(UI32_T)((k-1)/8)] & (1 << (7-((k-1)%8))) )
            &&!(src_both_rx_tx_ar[(UI32_T)((k-1)/8)] & (1 << (7-((k-1)%8))) );
    }
}

/*-----------------------------------------------------------
 * ROUTINE NAME - cli_runcfg_rspan_print_source_config_mode
 *-----------------------------------------------------------
 * PURPOSE : This function prints the source port configuration mode.
 *           If the port is selected, print its RSPAN attribute.  The input array src_ar[]
 *           is one of the following --- src_rx_ar[], src_tx_ar[], src_both_rx_tx_ar[].
 * INPUT   : mode - RSPAN source port mirror mode, which is one of the following ---
 *           VAL_mirrorType_rx,
 *           VAL_mirrorType_tx,
 *           VAL_mirrorType_both.
 *         : cmd_buff_ar - Common output text buffer.
 * OUTPUT  : No direct output (implicit output:
 *           rx - this is an rx source port.
 *           tx - this is a tx source port.
 *           both - this is an rx_tx source port.
 *           default - this is an rx_tx source port.)
 * RETURN  : None.
 * NOTE    : This function is called by cli_runcfg_rspan_print_source_config().
 *           3-31-2008, Kwok-yam TAM.
 *----------------------------------------------------------
 */
static void cli_runcfg_rspan_print_source_config_mode(char mode, char cmd_buff_ar[])
{
    char temp_buff_ar[SYS_ADPT_CLI_MAX_BUFSIZE];

    switch(mode)
    {
        case VAL_mirrorType_rx:
            strcpy(temp_buff_ar, " rx");
            break;
        case VAL_mirrorType_tx:
            strcpy(temp_buff_ar, " tx");
            break;
        case VAL_mirrorType_both:
            strcpy(temp_buff_ar, " both");
            break;
        default:
            strcpy(temp_buff_ar, " both");
            break;
    }
    strcat(temp_buff_ar, "\r\n");
    strcat(cmd_buff_ar, temp_buff_ar);
}

/*-----------------------------------------------------------
 * ROUTINE NAME - cli_runcfg_rspan_print_port_id_list
 *-----------------------------------------------------------
 * PURPOSE : This function prints the source port configuration mode.
 *           If the port is selected, print its RSPAN attribute.  The input array src_ar[]
 *           is one of the following --- src_rx_ar[], src_tx_ar[], src_both_rx_tx_ar[].
 * INPUT   : k - port index.
 *         : last_port_p - a pointer to the port previously printed.
 *         : hyphen_printed_p - a pointer to a boolean value indicated whether a hyphen
 *           is printed to indicate a range of ports selected.
 *         : cmd_buff_ar - Common output text buffer.
 * OUTPUT  : No direct output (implicit output: port ID list).
 * RETURN  : None.
 * NOTE    : This function is called by cli_runcfg_rspan_print_source_meta_config() and
 *           cli_runcfg_rspan_print_uplink()
 *           3-31-2008, Kwok-yam TAM.
 *----------------------------------------------------------
 */
static void cli_runcfg_rspan_print_port_id_list(int k, int *last_port_p, BOOL_T *hyphen_printed_p, char cmd_buff_ar[])
{
    char temp_buff_ar[SYS_ADPT_CLI_MAX_BUFSIZE];

    if(k==*last_port_p+1)
    {
        if(!*hyphen_printed_p)
        {
            strcpy(temp_buff_ar, "-");
            strcat(cmd_buff_ar, temp_buff_ar);
            *hyphen_printed_p=TRUE;
        }
        *last_port_p=k;
    }
    else
    {
        if(*hyphen_printed_p)
        {
            sprintf(temp_buff_ar, "%d,%d", *last_port_p, k);
            strcat(cmd_buff_ar, temp_buff_ar);
        }
        else
        {
            sprintf(temp_buff_ar, ",%d", k);
            strcat(cmd_buff_ar, temp_buff_ar);
        }
        *last_port_p=k;
        *hyphen_printed_p=FALSE;
    }
}

/*-----------------------------------------------------------
 * ROUTINE NAME - cli_runcfg_rspan_print_source_meta_config
 *-----------------------------------------------------------
 * PURPOSE : This is a meta function to print the source port configuration of
 *           rx, tx and both_rx_and_tx.
 * INPUT   : session_id - The RSPAN session ID, currently 1 or 2.
 *         : src_ar[] - The source port array.  It can be src_rx_ar[], src_tx_ar[], or src_both_rx_tx_ar[].
 *         : src_both_rx_tx_ar[] - The array of both rx and tx attribute of the source ports.  This argument is NULL
 *           if the input array src_ar[] is src_both_rx_tx_ar[].
 *         : unit_id - The unit ID of the switch.
 *         : max_port_number - The maximum number of ports allowed in the RSPAN session.
 *         : mode - RSPAN source port mirror mode, which is one of the following ---
 *           VAL_mirrorType_rx, VAL_mirrorType_tx, VAL_mirrorType_both.
 *         : cmd_buff_ar - Common output text buffer.
 * OUTPUT  : No direct output (implicit output: RSPAN session source port configuration.)
 * RETURN  : None.
 * NOTE    : This function is called by cli_runcfg_rspan_print_source_config().
 *           3-31-2008, Kwok-yam TAM.
 *----------------------------------------------------------
 */
static void cli_runcfg_rspan_print_source_meta_config(char session_id, UI8_T src_ar[], UI8_T src_both_rx_tx_ar[], UI32_T unit_id, UI32_T max_port_number, char mode, char cmd_buff_ar[])
{
    char temp_buff_ar[SYS_ADPT_CLI_MAX_BUFSIZE];
    BOOL_T first_entry=TRUE;
    BOOL_T hyphen_printed=FALSE;
    int k;
    int last_port;

    sprintf(temp_buff_ar, "rspan session %u source interface ethernet %lu/", session_id, (unsigned long)unit_id);
    strcat(cmd_buff_ar, temp_buff_ar);
    for (k=1; k<=max_port_number; k++)
    {
        if (cli_runcfg_rspan_print_conditional(src_ar, src_both_rx_tx_ar, k, mode))
        {
            if(first_entry)
            {
                sprintf(temp_buff_ar, "%u", k);
                strcat(cmd_buff_ar, temp_buff_ar);
                first_entry=FALSE;
                last_port=k;
            }
            else
            {
                cli_runcfg_rspan_print_port_id_list(k, &last_port, &hyphen_printed, cmd_buff_ar);
            }
        }
    }
    if(hyphen_printed)
    {
        sprintf(temp_buff_ar, "%d", last_port);
        strcat(cmd_buff_ar, temp_buff_ar);
    }
    cli_runcfg_rspan_print_source_config_mode(mode, cmd_buff_ar);
}

/*-----------------------------------------------------------
 * ROUTINE NAME - cli_runcfg_rspan_print_source_config
 *-----------------------------------------------------------
 * PURPOSE : This function prints the source port configuration of rx, tx and both_rx_and_tx.
 * INPUT   : session_id - The RSPAN session ID, currently 1 or 2.
 *         : src_rx_ar[] - The array of rx attribute of the source ports.
 *         : src_tx_ar[] - The array of tx attribute of the source ports.
 *         : src_both_rx_tx_ar[] - The array of both rx and tx attribute of the source ports.
 *         : empty_rx_list - a boolean value indicating whether the rx_list is empty.
 *         : empty_tx_list - a boolean value indicating whether the tx_list is empty.
 *         : empty_rx_tx_list - a boolean value indicating whether both the rx_list
 *           and the tx_list are empty.
 *         : unit_id - The unit ID of the switch.
 *         : max_port_number - The maximum number of ports allowed in the RSPAN session.
 *         : cmd_buff_ar - Common output text buffer.
 * OUTPUT  : No direct output (implicit output: RSPAN session source port configuration.)
 * RETURN  : None.
 * NOTE    : This function is called by CLI_RUNCFG_Get_Rspan_Parameter().
 *           3-31-2008, Kwok-yam TAM.
 *----------------------------------------------------------
 */
static void cli_runcfg_rspan_print_source_config(char session_id, UI8_T src_rx_ar[],
    UI8_T src_tx_ar[], UI8_T src_both_rx_tx_ar[], BOOL_T empty_rx_list,
    BOOL_T empty_tx_list, BOOL_T empty_rx_tx_list, UI32_T unit_id,
    UI32_T max_port_number, char cmd_buff_ar[])
{
    cmd_buff_ar[0] = '\0';
    if(!empty_rx_list)
    {
        /* Print RSPAN source_rx configuration.
         */
        cli_runcfg_rspan_print_source_meta_config(session_id, src_rx_ar, src_both_rx_tx_ar, unit_id, max_port_number, VAL_mirrorType_rx, cmd_buff_ar);
    }
    if(!empty_tx_list)
    {
        /* Print RPSAN source_tx configuration.
         */
        cli_runcfg_rspan_print_source_meta_config(session_id, src_tx_ar, src_both_rx_tx_ar, unit_id, max_port_number, VAL_mirrorType_tx, cmd_buff_ar);
    }
    if(!empty_rx_tx_list)
    {
        /* Print RSPAN source_both configuration.
         */
        cli_runcfg_rspan_print_source_meta_config(session_id, src_both_rx_tx_ar, NULL, unit_id, max_port_number, VAL_mirrorType_both, cmd_buff_ar);
    }
}

/*-----------------------------------------------------------
 * ROUTINE NAME - cli_runcfg_rspan_print_remote_vlan_config_mode
 *-----------------------------------------------------------
 * PURPOSE : This function prints the mode of the remote VLAN uplink port configuration.
 * INPUT   : switch_role - role of remote VLAN uplink port.  It can be one of the following ---
 *           VAL_rspanSwitchRole_source, VAL_rspanSwitchRole_intermediate, VAL_rspanSwitchRole_destination.
 *           The default is none of the above.
 *         : cmd_buff_ar - Common output text buffer.
 * OUTPUT  : No direct output (implicit output:
 *           source - the uplink port is a source,
 *           intermediate - the uplink port is an intermediate between source and destination.
 *           destination - the uplink port is a destination
 *           none - no role specified.)
 * RETURN  : None.
 * NOTE    : This function is called by cli_runcfg_rspan_print_source_config().
 *           3-31-2008, Kwok-yam TAM.
 *----------------------------------------------------------
 */
static void cli_runcfg_rspan_print_remote_vlan_config_mode(char switch_role, char cmd_buff_ar[])
{
    char temp_buff_ar[SYS_ADPT_CLI_MAX_BUFSIZE];

    switch(switch_role)
    {
        case VAL_rspanSwitchRole_source:
            strcpy(temp_buff_ar, "source");
            break;
        case VAL_rspanSwitchRole_intermediate:
            strcpy(temp_buff_ar, "intermediate");
            break;
        case VAL_rspanSwitchRole_destination:
            strcpy(temp_buff_ar, "destination");
            break;
        default:
            /* Default value won't be source, but "none". 2008.1.14. by Tien.
             */
            strcpy(temp_buff_ar, "none");
            break;
    }
    strcat(cmd_buff_ar, temp_buff_ar);
}

/*-----------------------------------------------------------
 * ROUTINE NAME - cli_runcfg_rspan_print_uplink
 *-----------------------------------------------------------
 * PURPOSE : This function prints the remote VLAN uplink port configuration.
 * INPUT   : uplink_ar - An array of remote VLAN uplink ports.
 *         : unit_id - The unit ID of the switch.
 *         : max_port_number - The maximum number of ports allowed in the RSPAN session.
 *         : cmd_buff_ar - Common output text buffer.
 * OUTPUT  : No direct output (implicit output: port ID list of the uplink ports.)
 * RETURN  : None.
 * NOTE    : This function is called by cli_runcfg_rspan_print_remote_vlan_config().
 *           3-31-2008, Kwok-yam TAM.
 *----------------------------------------------------------
 */
static void cli_runcfg_rspan_print_uplink(UI8_T uplink_ar[], UI32_T unit_id, UI32_T max_port_number, char cmd_buff_ar[])
{
    char temp_buff_ar[SYS_ADPT_CLI_MAX_BUFSIZE];
    BOOL_T first_entry=TRUE;
    BOOL_T hyphen_printed=FALSE;
    int k;
    int last_port;

    sprintf(temp_buff_ar, "%lu/", (unsigned long)unit_id);
    strcat(cmd_buff_ar, temp_buff_ar);
    for (k=1; k<=max_port_number; k++)
    {
        if (uplink_ar[(UI32_T)((k-1)/8)] & (1 << (7-((k-1)%8))) )
        {
            if(first_entry)
            {
                sprintf(temp_buff_ar, "%d", k);
                strcat(cmd_buff_ar, temp_buff_ar);
                first_entry=FALSE;
                last_port=k;
            }
            else
            {
                cli_runcfg_rspan_print_port_id_list(k, &last_port, &hyphen_printed, cmd_buff_ar);
            }
        }
    }
    if(hyphen_printed)
    {
        sprintf(temp_buff_ar, "%d", last_port);
        strcat(cmd_buff_ar, temp_buff_ar);
    }
}

/*-----------------------------------------------------------
 * ROUTINE NAME - cli_runcfg_rspan_print_remote_vlan_config
 *-----------------------------------------------------------
 * PURPOSE : This function prints the remote VLAN configuration.
 * INPUT   : session_id - The RSPAN session ID, currently 1 or 2.
 *         : unit_id - The unit ID of the switch.
 *         : remote_vid - Remote VLAN ID.
 *         : switch_role - role of remote VLAN uplink port.  It can be one of the following ---
 *           VAL_rspanSwitchRole_source,
 *           VAL_rspanSwitchRole_intermediate,
 *           VAL_rspanSwitchRole_destination.
 *           The default is none of the above.
 *         : uplink_ar - An array of the remote VLAN uplink ports.
 *         : max_port_number - The maximum number of ports allowed in the RSPAN session.
 *         : cmd_buff_ar - Common output text buffer.
 * OUTPUT  : No direct output (implicit output: remote RSPAN VLAN configuration -
 *           session ID, VLAN ID, uplink port, switch role)
 * RETURN  : None.
 * NOTE    : This function is called by CLI_RUNCFG_Get_Rspan_Parameter().
 *           3-31-2008, Kwok-yam TAM.
 *----------------------------------------------------------
 */
static void cli_runcfg_rspan_print_remote_vlan_config(char session_id, UI32_T unit_id, UI32_T remote_vid, char switch_role, UI8_T uplink_ar[], UI32_T max_port_number, char cmd_buff_ar[])
{
    char temp_buff_ar[SYS_ADPT_CLI_MAX_BUFSIZE];
    UI8_T i ;
    BOOL_T isConfigured = FALSE ;

    cmd_buff_ar[0] = '\0';

    /* Need to check every field if being set before writing into running file. 2008.1.14. by Tien.
     */
    if(remote_vid && switch_role )
    {
        for (i=0; i<SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST && isConfigured == FALSE; i++)
        {
            if ( uplink_ar [i] )
                isConfigured = TRUE ;
        }

        if ( isConfigured == TRUE )
        {
            sprintf(cmd_buff_ar, "rspan session %u remote vlan %lu ", session_id, (unsigned long)remote_vid);
            cli_runcfg_rspan_print_remote_vlan_config_mode(switch_role, cmd_buff_ar);
            strcpy(temp_buff_ar, " uplink ethernet ");
            strcat(cmd_buff_ar, temp_buff_ar);
            cli_runcfg_rspan_print_uplink(uplink_ar, unit_id, max_port_number, cmd_buff_ar);
            strcpy(temp_buff_ar, "\r\n");
            strcat(cmd_buff_ar, temp_buff_ar);
        }
    }
}

/*-----------------------------------------------------------
 * ROUTINE NAME - cli_runcfg_rspan_print_destination_config
 *-----------------------------------------------------------
 * PURPOSE : This function prints the destination configuration.
 * INPUT   : session_id - The RSPAN session ID, currently 1 or 2.
 *         : unit_id - The unit ID of the switch.
 *         : destination_port - The RSPAN destination port.
 *         : is_tagged - A boolean value indicating if the destination port is tagged.
 *         : cmd_buff_ar - Common output text buffer.
 * OUTPUT  : No direct output (implicit output: RSPAN destination configuration -
 *           session ID, destination port, port tag status.)
 * RETURN  : None.
 * NOTE    : This function is called by CLI_RUNCFG_Get_Rspan_Parameter().
 *           3-31-2008, Kwok-yam TAM.
 *----------------------------------------------------------
 */
static void cli_runcfg_rspan_print_destination_config(char session_id, UI32_T unit_id, char destination_port, char is_tagged, char cmd_buff_ar[])
{
    char temp_buff_ar[SYS_ADPT_CLI_MAX_BUFSIZE];

    cmd_buff_ar[0] = '\0';

    /* Need to check if every field being set before writing into running file. 2008.1.14. by Tien.
     */
    if(destination_port && is_tagged>0 )
    {
        sprintf(cmd_buff_ar, "rspan session %u destination interface ethernet %lu/%u ", session_id, (unsigned long)unit_id, destination_port);
        if(is_tagged==VAL_rspanDstPortTag_tagged)
        {
            strcpy(temp_buff_ar, "tagged\n");
        }
        else if (is_tagged == VAL_rspanDstPortTag_untagged)
        {
            strcpy(temp_buff_ar, "untagged\n");
        }
        else
        {
            strcpy(temp_buff_ar, "none\n");
        }
        strcat(cmd_buff_ar, temp_buff_ar);
    }
}

/*-----------------------------------------------------------
 * ROUTINE NAME - CLI_RUNCFG_Get_Rspan_Parameter
 *-----------------------------------------------------------
 * PURPOSE : This is the public handle to obtain the RSPAN session parameters.
 * INPUT   : unit_id - The unit ID of the switch.
 *         : buffer - common CLI_RUNCFG text buffer used by the APPEND_RUNNING_CFG_0 macro.
 *         : temp_buffer - common CLI_RUNCFG temporary text buffer used by the APPEND_RUNNING_CFG_0 macro.
 *         : buffer_size - size of buffers used by the APPEND_RUNNING_CFG_0 macro.
 *         : b_count - buffer count used by the APPEND_RUNNING_CFG_0 macro.
 * OUTPUT  : No direct output (implicit output: RSPAN session configuration -
 *           session ID, source, destination, remote RSPAN VLAN.)
 * RETURN  : buffer count.
 * NOTE    : 3-31-2008, Kwok-yam TAM.
 *----------------------------------------------------------
 */
UI32_T CLI_RUNCFG_Get_Rspan_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    RSPAN_OM_SessionEntry_T rspan_session_entry;
    UI32_T buffer_count = b_count;
    UI32_T max_port_number;
    char cmd_buff_ar[CLI_DEF_MAX_BUFSIZE]={0};
    UI8_T src_both_rx_tx_ar[SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST]={0};
    UI8_T session_id;
    BOOL_T empty_rx_list=TRUE;
    BOOL_T empty_tx_list=TRUE;
    BOOL_T empty_rx_tx_list=TRUE;

    memset(&rspan_session_entry, 0, sizeof(RSPAN_OM_SessionEntry_T));
    session_id=0;
    while(RSPAN_PMGR_GetNextRspanSessionEntry(&session_id, &rspan_session_entry))
    {
        max_port_number=SWCTRL_POM_UIGetUnitPortNumber(unit_id);
        cli_runcfg_rspan_construct_rx_tx_list(rspan_session_entry.src_rx, rspan_session_entry.src_tx, max_port_number, src_both_rx_tx_ar, &empty_rx_list, &empty_tx_list, &empty_rx_tx_list);
        cli_runcfg_rspan_print_source_config(session_id, rspan_session_entry.src_rx, rspan_session_entry.src_tx, src_both_rx_tx_ar, empty_rx_list, empty_tx_list, empty_rx_tx_list, unit_id, max_port_number, cmd_buff_ar);
        APPEND_RUNNING_CFG_0(cmd_buff_ar);
        cli_runcfg_rspan_print_remote_vlan_config(session_id, unit_id, rspan_session_entry.remote_vid, rspan_session_entry.switch_role, rspan_session_entry.uplink, max_port_number, cmd_buff_ar);
        APPEND_RUNNING_CFG_0(cmd_buff_ar);
        cli_runcfg_rspan_print_destination_config(session_id, unit_id, rspan_session_entry.dst, rspan_session_entry.is_tagged, cmd_buff_ar);
        APPEND_RUNNING_CFG_0(cmd_buff_ar);
    }
    APPEND_RUNNING_CFG_0("!\n");
    return buffer_count;
}
#endif /* #if (SYS_CPNT_RSPAN == TRUE) */

#if (SYS_CPNT_PPPOE_IA == TRUE)
static UI32_T CLI_RUNCFG_Get_PPPoE_IA_Parameter(
    UI32_T unit_id, char *buffer, char *temp_buffer,
    UI32_T buffer_size, UI32_T b_count)
{
    UI32_T  buffer_count = b_count;

    /* Commands:
     * [no] pppoe intermediate-agent
     */
    {
        BOOL_T  bool_flag;

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
            PPPOE_IA_PMGR_GetRunningBoolDataByField(
                0, PPPOE_IA_TYPE_FLDID_GLOBAL_ENABLE, &bool_flag))
        {
            if (TRUE == bool_flag)
            {
                APPEND_RUNNING_CFG_0("pppoe intermediate-agent\n");
            }
            else
            {
                APPEND_RUNNING_CFG_0("no pppoe intermediate-agent\n");
            }
        }
    }

    /* Commands:
     * [no] pppoe intermediate-agent format-type
     *      {access-node-identifier | generic-error-message}
     */
     {
        char    *str_tag_ar[] = {"access-node-identifier", "generic-error-message"};
        char    fld_id_ar[]   = {PPPOE_IA_TYPE_FLDID_GLOBAL_ACC_NODE_ID,
                                 PPPOE_IA_TYPE_FLDID_GLOBAL_GEN_ERMSG};
        char    str_buf[CLI_DEF_MAX_BUFSIZE];
        UI8_T   i;

        /* access-node-identifier, generic-error-message
         */
        for (i=0; i<=1; i++)
        {
            if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                PPPOE_IA_PMGR_GetRunningStrDataByField(
                    0, fld_id_ar[i], sizeof(str_buf), (UI8_T *) str_buf))
            {
                APPEND_RUNNING_CFG_2("pppoe intermediate-agent format-type %s %s\n",
                    str_tag_ar[i], str_buf);
            }
        }
    }

    return buffer_count;
}

static UI32_T CLI_RUNCFG_Get_PPPoE_IA_Ethernet_Parameter(
    UI32_T unit_id, UI32_T port_id, char *buffer, char *temp_buffer,
    UI32_T buffer_size, UI32_T b_count, UI32_T ifindex)
{
    UI32_T  buffer_count = b_count;

    /* Commands:
     * [no] pppoe intermediate-agent {port-enable | trust | vendor-tag strip}
     */
    {
        char    *no_tag_p;
        char    *str_tag_ar[] = {" port-enable", " trust", " vendor-tag strip"};
        char    *no_tag_ar[]  = {"", " no"};
        UI8_T   fld_id_ar[]   = {PPPOE_IA_TYPE_FLDID_PORT_ENABLE,
                                 PPPOE_IA_TYPE_FLDID_PORT_TRUST,
                                 PPPOE_IA_TYPE_FLDID_PORT_STRIP_VENDOR};
        UI8_T   i;
        BOOL_T  bool_flag;

        /* enable, trust, strip
         */
        for (i=0; i<=2; i++)
        {
            if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                PPPOE_IA_PMGR_GetRunningBoolDataByField(
                    ifindex, fld_id_ar[i], &bool_flag))
            {
                no_tag_p = (TRUE == bool_flag) ? no_tag_ar[0] : no_tag_ar[1];

                APPEND_RUNNING_CFG_2("%s pppoe intermediate-agent%s\n",
                    no_tag_p, str_tag_ar[i]);
            }
        }
    }

    /* Commands:
     * [no] pppoe intermediate-agent port-format-type
     *      {circuit-id | remote-id}
     */
    {
        char    *str_tag_ar[] = {"circuit-id", "remote-id"};
        UI8_T   fld_id_ar[]   = {PPPOE_IA_TYPE_FLDID_PORT_CIRCUIT_ID,
                                 PPPOE_IA_TYPE_FLDID_PORT_REMOTE_ID};
        char    str_buf[CLI_DEF_MAX_BUFSIZE];
        UI8_T   i;

        /* circuit-id, remote-id
         */
        for (i=0; i<=1; i++)
        {
            if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                PPPOE_IA_PMGR_GetRunningStrDataByField(
                    ifindex, fld_id_ar[i], sizeof(str_buf), (UI8_T *) str_buf))
            {
                APPEND_RUNNING_CFG_2(" pppoe intermediate-agent port-format-type %s %s\n",
                    str_tag_ar[i], str_buf);
            }
        }
    }

#if (SYS_CPNT_PPPOE_IA_REMOTE_ID_ENHANCE == TRUE)
    /* Commands:
     * [no] pppoe intermediate-agent port-format-type
     *      {remote-id-delimiter {enable | ascii}}
     */
    {
        char    *no_tag_p;
        char    *no_tag_ar[]  = {"", " no"};
        UI32_T  tmp_data;
        BOOL_T  bool_flag;

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
            PPPOE_IA_PMGR_GetRunningBoolDataByField(
                ifindex, PPPOE_IA_TYPE_FLDID_PORT_RID_DELIM, &bool_flag))
        {
            no_tag_p = (TRUE == bool_flag) ? no_tag_ar[0] : no_tag_ar[1];

            APPEND_RUNNING_CFG_1("%s pppoe intermediate-agent port-format-type remote-id-delimiter enable\n",
                no_tag_p);
        }

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
            PPPOE_IA_PMGR_GetRunningUi32DataByField(
                ifindex, PPPOE_IA_TYPE_FLDID_PORT_RID_DASCII, &tmp_data))
        {
            APPEND_RUNNING_CFG_1(" pppoe intermediate-agent port-format-type remote-id-delimiter %ld\n",
                (long)tmp_data);
        }
    }
#endif /* #if (SYS_CPNT_PPPOE_IA_REMOTE_ID_ENHANCE == TRUE) */

    return buffer_count;
}
#endif /* #if (SYS_CPNT_PPPOE_IA == TRUE) */

#if (SYS_CPNT_IPV6_RA_GUARD == TRUE)
static UI32_T CLI_RUNCFG_Get_IPV6_RAGUARD_Ethernet_Parameter(
    UI32_T unit_id, UI32_T port_id, char *buffer, char *temp_buffer,
    UI32_T buffer_size, UI32_T b_count, UI32_T ifindex)
{
    UI32_T  buffer_count = b_count;

    /* Commands:
     * [no] ipv6 nd raguard
     */
    {
        char    *no_tag_p;
        char    *no_tag_ar[]  = {"", " no"};
        BOOL_T  bool_flag;

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                    NETCFG_PMGR_ND_RAGUARD_GetRunningPortStatus(
                        ifindex, &bool_flag))
        {
            no_tag_p = (TRUE == bool_flag) ? no_tag_ar[0] : no_tag_ar[1];

            APPEND_RUNNING_CFG_1("%s ipv6 nd raguard\n", no_tag_p);
        }
    }

    return buffer_count;
}
#endif /* #if (SYS_CPNT_IPV6_RA_GUARD == TRUE) */

#if (SYS_CPNT_PFC == TRUE)
static UI32_T CLI_RUNCFG_Get_PFC_Ethernet_Parameter(
    UI32_T unit_id, UI32_T port_id, char *buffer, char *temp_buffer,
    UI32_T buffer_size, UI32_T b_count, UI32_T ifindex)
{
    UI32_T  buffer_count = b_count;

    /* Commands:
     * [no] pfc mode {auto | on}
     */
    {
        char    *no_tag_ar[]   = {"", " no"};
        char    *str_tag_ar[]  = {"", " auto", " on",};
        UI32_T  pfc_mode;
        UI32_T  no_tag_id =1, str_tag_id =0;

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                        PFC_PMGR_GetRunningDataByField(
                            ifindex, PFC_TYPE_FLDE_PORT_MODE_ADM, &pfc_mode))
        {
            switch (pfc_mode)

            {
            case PFC_TYPE_PMODE_OFF:
                break;
            case PFC_TYPE_PMODE_ON:
                no_tag_id  =0;
                str_tag_id =2;
                break;
            case PFC_TYPE_PMODE_AUTO:
                no_tag_id  =0;
                str_tag_id =1;
                break;

            }

            APPEND_RUNNING_CFG("%s pfc mode%s\n",
                no_tag_ar[no_tag_id], str_tag_ar[str_tag_id]);
        }
    }

#define _PFC_REVERSE_BMP_BYTE(a)            \
            ({                              \
                UI8_T   v = a;              \
                UI8_T   r = v;              \
                int     s = 7;              \
                                            \
                for (v >>= 1; v; v >>= 1)   \
                {                           \
                  r <<= 1;                  \
                  r |= v & 1;               \
                  s--;                      \
                }                           \
                r <<= s;                    \
                r;                          \
            })

    /* Commands:
     * [no] pfc priority enable pri_lst
     */
    {
        UI32_T  pfc_pri_bmp;
        char    adm_pri_buf[16] = {0};

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                        PFC_PMGR_GetRunningDataByField(
                            ifindex, PFC_TYPE_FLDE_PORT_PRI_EN_ADM, &pfc_pri_bmp))
        {
            if (0 != pfc_pri_bmp)
            {
                /* need to reverse the order of bits for CLI_LIB_Bitmap_To_List
                 */
                char    tmp_bmp;

                tmp_bmp = _PFC_REVERSE_BMP_BYTE(pfc_pri_bmp & 0xff);

                CLI_LIB_Bitmap_To_List_Ex(&tmp_bmp,
                    adm_pri_buf, sizeof(adm_pri_buf), 8, 0, TRUE);

                APPEND_RUNNING_CFG(" pfc priority enable %s\n", adm_pri_buf);
            }
            else
            {
                APPEND_RUNNING_CFG(" no pfc priority enable 0-7\n");
            }
        }
    }

#if 0 /* not supported yet */
    /* Commands:
     * [no] pfc link-delay-allowance lda_bits
     */
    {
        UI32_T  pfc_lda;

        if (SYS_TYPE_GET_RUNNING_CFG_SUCCESS ==
                        PFC_PMGR_GetRunningDataByField(
                            ifindex, PFC_TYPE_FLDE_PORT_LDA, &pfc_lda))
        {
            APPEND_RUNNING_CFG_1(" pfc link-delay-allowance %ld\n", pfc_lda);
        }
    }
#endif

    return buffer_count;
}
#endif /* #if (SYS_CPNT_PFC == TRUE) */

#if (SYS_CPNT_CN == TRUE)
static UI32_T CLI_RUNCFG_Get_CN_Parameter(UI32_T unit_id, char *buffer,
    char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    UI32_T status, priority, mode, alt_priority;

    if (CN_POM_GetRunningGlobalAdminStatus(&status) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if (status == CN_TYPE_GLOBAL_STATUS_ENABLE)
        {
            APPEND_RUNNING_CFG_0("cn\n");
        }
        else
        {
            APPEND_RUNNING_CFG_0("no cn\n");
        }
    }

    if (CN_POM_GetRunningCnmTxPriority(&priority) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        APPEND_RUNNING_CFG_1("cn cnm-transmit-priority %lu\n", (unsigned long)priority);
    }

    priority = CN_TYPE_START_PRIORITY_FOR_SEARCHING;
    while (CN_POM_GetNextCnpv(&priority) == CN_TYPE_RETURN_OK)
    {
        APPEND_RUNNING_CFG_1("cn cnpv %lu\n", (unsigned long)priority);

        if (CN_POM_GetRunningCnpvDefenseMode(priority, &mode) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            switch (mode)
            {
            case CN_TYPE_DEFENSE_MODE_AUTO:
                APPEND_RUNNING_CFG_1("cn cnpv %lu defense-mode auto\n", (unsigned long)priority);
                break;
            case CN_TYPE_DEFENSE_MODE_DISABLED:
                APPEND_RUNNING_CFG_1("cn cnpv %lu defense-mode disabled\n", (unsigned long)priority);
                break;
            case CN_TYPE_DEFENSE_MODE_EDGE:
                APPEND_RUNNING_CFG_1("cn cnpv %lu defense-mode edge\n", (unsigned long)priority);
                break;
            case CN_TYPE_DEFENSE_MODE_INTERIOR:
                APPEND_RUNNING_CFG_1("cn cnpv %lu defense-mode interior\n", (unsigned long)priority);
                break;
            case CN_TYPE_DEFENSE_MODE_INTERIOR_READY:
                APPEND_RUNNING_CFG_1("cn cnpv %lu defense-mode interior-ready\n", (unsigned long)priority);
                break;
            }
        }

        if (CN_POM_GetRunningCnpvAlternatePriority(priority, &alt_priority) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
        {
            APPEND_RUNNING_CFG_2("cn cnpv %lu alternate-priority %lu\n", (unsigned long)priority, (unsigned long)alt_priority);
        }
    } /* end of while */

    return buffer_count;
} /* end of CLI_RUNCFG_Get_CN_Parameter */
#endif /* #if (SYS_CPNT_CN == TRUE) */

#if (SYS_CPNT_SWCTRL_GLOBAL_STORM_SAMPLE_TYPE == TRUE)
static UI32_T CLI_RUNCFG_Get_GlobalStormSampleType_Parameter(UI32_T unit_id, char *buffer, char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    UI32_T buffer_count = b_count;
    UI32_T global_storm_sample_type;

    if (SWCTRL_POM_GetRunningGlobalStormSampleType(&global_storm_sample_type) == SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        switch (global_storm_sample_type)
        {
            case VAL_stormSampleType_pkt_rate:
                APPEND_RUNNING_CFG_0("storm-sample-type packet\n");
                break;

            case VAL_stormSampleType_octet_rate:
                APPEND_RUNNING_CFG_0("storm-sample-type octet\n");
                break;

            case VAL_stormSampleType_percent:
                APPEND_RUNNING_CFG_0("storm-sample-type percent\n");
                break;
        }
    }

    return buffer_count;
}
#endif /* (SYS_CPNT_SWCTRL_GLOBAL_STORM_SAMPLE_TYPE == TRUE) */

#if(SYS_CPNT_XSTP_TC_PROP_GROUP == TRUE)
static UI32_T CLI_RUNCFG_Get_XSTP_Tc_Prop_Group_Parameter(UI32_T unit_id, char *buffer,
    char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    TRK_MGR_TrunkEntry_T trunk_entry;
    UI32_T buffer_count = b_count;
    UI32_T group_id = 0;
    UI32_T i,j;
    UI32_T index;
    UI32_T unit;
    BOOL_T have_port = FALSE;
    UI8_T  bitmap[SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST+1] = {0};
    char   *eth_str;
    char   *pch_str;
    char   *temp_buff;


    /*spanning-tree tc-prop*/
    if((temp_buff = calloc(128, sizeof(char))) == 0)
    {
        return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
    }

    if((eth_str = calloc(128, sizeof(char))) == 0)
    {
        free(temp_buff);
        return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
    }

    if((pch_str = calloc(128, sizeof(char))) == 0)
    {
        free(temp_buff);
        free(eth_str);
        return CLI_RUNCFG_RETURN_NO_ENOUGH_MEMORY;
    }

    while (XSTP_POM_GetTcPropNextGroupPortbitmap(&group_id, bitmap, &have_port))
    {
        if (have_port)
        {
            for(i=SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER, j=0; i<=SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER + SYS_ADPT_MAX_NBR_OF_TRUNK_PER_SYSTEM - 1; i++, j++)
            {
                /* If trunk port is member of TC Prop Group, set trunk memmber bit on.
                 */
                if(bitmap[(UI32_T)((i-1)/8)] & (1 << ( 7 - ((i-1)%8))))
                {
                    trunk_entry.trunk_index = (i-SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER)+1;

                    if(TRK_PMGR_GetTrunkEntry(&trunk_entry))
                    {
                        for (index = 0; (index < (SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK*SYS_ADPT_NBR_OF_BYTE_FOR_1BIT_UPORT_LIST)); index++)
                        {
                            bitmap[index] |= trunk_entry.trunk_ports[index];
                        }
                    }
                    bitmap[(UI32_T)((i-1)/8)] &=(~(1 << ( 7 - ((i-1)%8))));
                }
            }


            /* eth */
            CLI_LIB_Stack_Bitmap_To_List((char *)bitmap, &unit, eth_str, 128, (SYS_ADPT_TRUNK_1_IF_INDEX_NUMBER-1),TRUE);
            if(eth_str[0] != 0)
            {
                SYSFUN_Sprintf((char *)temp_buff, "ethernet %lu/%s", (unsigned long)unit, eth_str);
                APPEND_RUNNING_CFG_2("spanning-tree tc-prop group %lu %s\n", (unsigned long)group_id, temp_buff);
            }

            memset(bitmap, 0, sizeof(bitmap));
        }
    }

    free(eth_str);
    free(pch_str);
    free(temp_buff);

    return buffer_count;
} /* end of CLI_RUNCFG_Get_CN_Parameter */
#endif /*#if(SYS_CPNT_XSTP_TC_PROP_GROUP == TRUE)*/

#if (SYS_CPNT_MLAG == TRUE)
static UI32_T CLI_RUNCFG_Get_MLAG_Parameter(UI32_T unit_id, char *buffer,
                char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    MLAG_TYPE_MlagEntry_T   mlag_entry;
    MLAG_TYPE_DomainEntry_T domain_entry;
    UI32_T                  status;
    SWCTRL_Lport_Type_T     lport_type;
    UI32_T                  unit, port, trunk_id;
    UI32_T                  buffer_count = b_count;

    if (MLAG_POM_GetRunningGlobalStatus(&status) ==
            SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if (status == MLAG_TYPE_GLOBAL_STATUS_ENABLED)
        {
            APPEND_RUNNING_CFG_0("mlag\n");
        }
        else
        {
            APPEND_RUNNING_CFG_0("no mlag\n");
        }
    }

    memset(&domain_entry, 0, sizeof(MLAG_TYPE_DomainEntry_T));
    while (MLAG_POM_GetNextDomainEntry(&domain_entry) == MLAG_TYPE_RETURN_OK)
    {
        lport_type = SWCTRL_POM_LogicalPortToUserPort(domain_entry.peer_link,
                        &unit, &port, &trunk_id);

        switch (lport_type)
        {
        case SWCTRL_LPORT_NORMAL_PORT:
            APPEND_RUNNING_CFG_3("mlag domain %s peer-link ethernet %lu/%lu\n",
                domain_entry.domain_id, (unsigned long)unit, (unsigned long)port);
            break;

        case SWCTRL_LPORT_TRUNK_PORT:
            APPEND_RUNNING_CFG_2("mlag domain %s peer-link port-channel %lu\n",
                domain_entry.domain_id, (unsigned long)trunk_id);
            break;

        default:
            break;
        }
    } /* end while get next domain entry is ok */

    memset(&mlag_entry, 0, sizeof(MLAG_TYPE_MlagEntry_T));
    while (MLAG_POM_GetNextMlagEntry(&mlag_entry) == MLAG_TYPE_RETURN_OK)
    {
        lport_type = SWCTRL_POM_LogicalPortToUserPort(mlag_entry.local_member,
                        &unit, &port, &trunk_id);

        switch (lport_type)
        {
        case SWCTRL_LPORT_NORMAL_PORT:
            APPEND_RUNNING_CFG_4("mlag group %lu domain %s member ethernet %lu/"
                "%lu\n", (unsigned long)mlag_entry.mlag_id, mlag_entry.domain_id, (unsigned long)unit, (unsigned long)port);
            break;

        case SWCTRL_LPORT_TRUNK_PORT:
            APPEND_RUNNING_CFG_3("mlag group %lu domain %s member port-channel "
                "%lu\n", (unsigned long)mlag_entry.mlag_id, mlag_entry.domain_id, (unsigned long)trunk_id);
            break;

        default:
            break;
        }
    } /* end while get next mlag entry is ok */

    return buffer_count;
} /* End of CLI_RUNCFG_Get_MLAG_Parameter */
#endif /* #if (SYS_CPNT_MLAG == TRUE) */

#if (SYS_CPNT_VXLAN == TRUE)
static UI32_T CLI_RUNCFG_Get_VXLAN_Parameter(UI32_T unit_id, char *buffer,
                char *temp_buffer, UI32_T buffer_size, UI32_T b_count)
{
    VXLAN_OM_RVtep_T rvtep_entry;
    VXLAN_OM_VNI_T vni_entry;
    SWCTRL_Lport_Type_T     lport_type;
    UI32_T unit, port, trunk_id;
    //UI32_T vni = 0;
    UI32_T buffer_count = b_count;
    UI32_T ifindex, lport;
    UI16_T dst_port;
    UI16_T vid = 0;
    char port_ar[20];

    if (VXLAN_POM_GetRunningUdpDstPort(&dst_port) ==
            SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        APPEND_RUNNING_CFG_1("vxlan udp-dst-port %u\n", dst_port);
    }

    if (VXLAN_POM_GetRunningSrcIf(&ifindex) ==
            SYS_TYPE_GET_RUNNING_CFG_SUCCESS)
    {
        if (IS_VLAN_IFINDEX_VAILD(ifindex))
        {
            UI32_T vid;
            VLAN_OM_ConvertFromIfindex(ifindex, &vid);
            APPEND_RUNNING_CFG_1("vxlan source-interface vlan %lu\n", (unsigned long)vid);
        }
#if (SYS_CPNT_LOOPBACK_IF_VISIBLE == TRUE)
        else if (ifindex >= SYS_ADPT_LOOPBACK_IF_INDEX_NUMBER &&
                 ifindex < SYS_ADPT_LOOPBACK_IF_INDEX_NUMBER + SYS_ADPT_MAX_NBR_OF_LOOPBACK_IF)
        {
            UI32_T lo_id;
            IP_LIB_ConvertLoopbackIfindexToId(ifindex, &lo_id);
            APPEND_RUNNING_CFG_1("vxlan source-interface loopback %lu\n", (unsigned long)lo_id);
        }
#endif
    }
#if 0
    while (VXLAN_POM_GetNextVlanVniMapEntry(&vid, &vni) == VXLAN_TYPE_RETURN_OK)
    {
        APPEND_RUNNING_CFG_2("vxlan vlan %u vni %lu\n", vid, (unsigned long)vni);
    }
#endif
    memset(&vni_entry, 0, sizeof(vni_entry));
    while (VXLAN_TYPE_RETURN_OK == VXLAN_POM_GetNextVniEntry(&vni_entry))
    {
        APPEND_RUNNING_CFG_1("vxlan vni %lu\n", (unsigned long)vni_entry.vni);
        lport = 0;
        vid = 0;
        while (VXLAN_TYPE_RETURN_OK == VXLAN_POM_GetNextPortVlanVniMapByVni(vni_entry.vni, &lport, &vid))
        {
            lport_type = SWCTRL_POM_LogicalPortToUserPort(lport, &unit, &port, &trunk_id);
            if(lport_type == SWCTRL_LPORT_NORMAL_PORT)
            {
                snprintf(port_ar, sizeof(port_ar), "ethernet %lu/%lu", (unsigned long)unit, (unsigned long)port);
            }
            else if (lport_type == SWCTRL_LPORT_TRUNK_PORT)
            {
                snprintf(port_ar, sizeof(port_ar), "port-channel %lu", (unsigned long)trunk_id);
            }
            else
            {
                continue;
            }

            if (vid == 0)
            {
                APPEND_RUNNING_CFG_2("vxlan vni %lu access-port interface %s\n",
                    (unsigned long)vni_entry.vni, port_ar);
            }
            else
            {
                APPEND_RUNNING_CFG_3("vxlan vni %lu access-port interface %s vlan %u\n",
                    (unsigned long)vni_entry.vni, port_ar, vid);
            }
        } //VXLAN_POM_GetNextPortVlanVniMapByVni

        memset(&rvtep_entry, 0, sizeof(rvtep_entry));
        rvtep_entry.vni = vni_entry.vni;

        while (VXLAN_POM_GetNextFloodRVtepByVni(&rvtep_entry) == VXLAN_TYPE_RETURN_OK)
        {
            APPEND_RUNNING_CFG_5("vxlan vni %lu flood r-vtep %d.%d.%d.%d\n",
                                (unsigned long)rvtep_entry.vni, rvtep_entry.ip.addr[0], rvtep_entry.ip.addr[1],
                                rvtep_entry.ip.addr[2], rvtep_entry.ip.addr[3]);
        } //VXLAN_POM_GetNextFloodRVtepByVni

        memset(&rvtep_entry, 0, sizeof(rvtep_entry));
        rvtep_entry.vni = vni_entry.vni;

        if (VXLAN_POM_GetFloodMulticastByVni(&rvtep_entry) == VXLAN_TYPE_RETURN_OK)
        {
            lport_type = SWCTRL_POM_LogicalPortToUserPort(rvtep_entry.lport,
                            &unit, &port, &trunk_id);

            switch (lport_type)
            {
                case SWCTRL_LPORT_NORMAL_PORT:
                    APPEND_RUNNING_CFG_8("vxlan vni %lu flood multicast %d.%d.%d.%d vlan %u ethernet %lu/%lu\n",
                        (unsigned long)rvtep_entry.vni, rvtep_entry.ip.addr[0], rvtep_entry.ip.addr[1],
                        rvtep_entry.ip.addr[2], rvtep_entry.ip.addr[3], rvtep_entry.vid,
                        (unsigned long)unit, (unsigned long)port);
                    break;

                case SWCTRL_LPORT_TRUNK_PORT:
                    break;

                default:
                    break;
            }
        } //VXLAN_POM_GetFloodMulticastByVni
    }

    return buffer_count;
} /* End of CLI_RUNCFG_Get_VXLAN_Parameter */
#endif /* #if (SYS_CPNT_VXLAN == TRUE) */
#if (SYS_CPNT_HASH_SELECTION == TRUE)
static UI32_T
CLI_RUNCFG_Get_HashSelection_Parameter(
    UI32_T unit_id,
    char *buffer,
    char *temp_buffer,
    UI32_T buffer_size,
    UI32_T b_count)
{
    UI32_T  buffer_count = b_count;
    UI8_T i=0;
    SWCTRL_OM_HashSelBlockInfo_T  block_info;

    for (i=1; i<=SYS_ADPT_MAX_HASH_SELECTION_BLOCK_SIZE; i++)
    {
        if (TRUE == SWCTRL_POM_GetHashBlockInfo(i, &block_info))
        {
            if (block_info.pkt_l2.arg.value > 0)
            {
                APPEND_RUNNING_CFG_1("hash-selection list %d mac\n", i);
                if (block_info.pkt_l2.arg.item.dst_mac)
                {
                    APPEND_RUNNING_CFG(" dst-mac\n");
                }
                if (block_info.pkt_l2.arg.item.src_mac)
                {
                    APPEND_RUNNING_CFG(" src-mac\n");
                }
                if (block_info.pkt_l2.arg.item.ether_type)
                {
                    APPEND_RUNNING_CFG(" ethertype\n");
                }
                if (block_info.pkt_l2.arg.item.vlan)
                {
                    APPEND_RUNNING_CFG(" vlan\n");
                }
                APPEND_RUNNING_CFG("!\n");
            }

            if (block_info.pkt_ipv4.arg.value > 0)
            {
                APPEND_RUNNING_CFG_1("hash-selection list %d ipv4\n", i);
                if (block_info.pkt_ipv4.arg.item.dst_ip)
                {
                    APPEND_RUNNING_CFG(" dst-ip\n");
                }
                if (block_info.pkt_ipv4.arg.item.src_ip)
                {
                    APPEND_RUNNING_CFG(" src-ip\n");
                }
                if (block_info.pkt_ipv4.arg.item.dst_l4_port)
                {
                    APPEND_RUNNING_CFG(" dst-l4-port\n");
                }
                if (block_info.pkt_ipv4.arg.item.src_l4_port)
                {
                    APPEND_RUNNING_CFG(" src-l4-port\n");
                }
                if (block_info.pkt_ipv4.arg.item.protocol_id)
                {
                    APPEND_RUNNING_CFG(" protocol-id\n");
                }
                if (block_info.pkt_ipv4.arg.item.vlan)
                {
                    APPEND_RUNNING_CFG(" vlan\n");
                }
                APPEND_RUNNING_CFG("!\n");
            }

            if (block_info.pkt_ipv6.arg.value > 0)
            {
                APPEND_RUNNING_CFG_1("hash-selection list %d ipv6\n", i);
                if (block_info.pkt_ipv6.arg.item.dst_ip)
                {
                    APPEND_RUNNING_CFG(" collapsed-dst-ip\n");
                }
                if (block_info.pkt_ipv6.arg.item.src_ip)
                {
                    APPEND_RUNNING_CFG(" collapsed-src-ip\n");
                }
                if (block_info.pkt_ipv6.arg.item.dst_l4_port)
                {
                    APPEND_RUNNING_CFG(" dst-l4-port\n");
                }
                if (block_info.pkt_ipv6.arg.item.src_l4_port)
                {
                    APPEND_RUNNING_CFG(" src-l4-port\n");
                }
                if (block_info.pkt_ipv6.arg.item.next_header)
                {
                    APPEND_RUNNING_CFG(" next-header\n");
                }
                if (block_info.pkt_ipv6.arg.item.vlan)
                {
                    APPEND_RUNNING_CFG(" vlan\n");
                }
                APPEND_RUNNING_CFG("!\n");
            }
        }
    }

    return buffer_count;
}
#endif /*#if (SYS_CPNT_HASH_SELECTION == TRUE)*/
