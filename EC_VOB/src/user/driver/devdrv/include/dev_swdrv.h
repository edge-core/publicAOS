/* Module Name: DEV_SWDRV.H
 * Purpose:
 *      This package is a low level driver routine which provides the low level service routines
 *      to manage/drive the switch device.
 *      This package provides a generic interface to the upper layer SWDRV to manage the switch
 *      device for all layer 2 switch product lines.
 * Notes:
 *      1. This packet provides the services to configure/report the Port speed/duplex/flow-control,
 *         Port trunking, Port mirroring, VLAN, Spanning tree, IGMP snooping, and Broadcast/Multicasr
 *         storm control behavior of L2 switch device.
 *      2. The service routines provided by this package may block (lock up) the calling task due to
 *         resources (critical section) manage algorithm or H/W limitation.
 *      3. This package WILL NOT BE REUSABLE to other L2 switch device since the implementation
 *         of this package is ASIC dependent.
 *      4. The following L2 switch services will be provided by other packages:
 *          DEV_AMTRDRV.H - L2 address table related management function
 *          DEV_NMTRDRV.H - Port/interface and RMON statistics function
 *      5. Layer 3 switch related services is defined by DEV_SWDRVL3.H
 *
 *
 *
 *
 *
 * History:
 *       Date        Modifier    Reason
 *       2002/8/27   Anderson    Init
 *       2002/9/18   Anderson    Put more comments on each function spec
 *       2002/10/4   Jason Hsue  1. Add MAU MIB relative APIs
 *                               2. Add Jumbo frame APIs(Enable/Disable)
 *                               3. Modify comments for DEV_SWDRV_SetPortAutoNegCapability()
 *                               4. Add one more argument mstid for DEV_SWDRV_SetPortSTAState()
 *                               5. Add one more argument unit_id for DEV_SWDRV_SetPortToVlanMemberSet()
 *                               6. Add one more argument unit_id for DEV_SWDRV_SetPortToVlanUntaggedSet()
 *
 *
 * Copyright(C)      Accton Corporation, 1999, 2000, 2001, 2002
 */


#ifndef DEV_SWDRV_H
#define DEV_SWDRV_H


/* INCLUDE FILE DECLARATIONS
 */
#include "sys_type.h"
#include "sys_adpt.h"
#include "sysfun.h"

#if (SYS_CPNT_POE == TRUE)

#if (SYS_CPNT_POE_INTERFACE == SYS_CPNT_POE_INTERFACE_DRAGONITE)
#include <cpss/generic/dragonite/cpssGenDragonite.h>
#endif

#endif

#if (SYS_CPNT_VXLAN == TRUE)
    #include "l_inet.h"
#endif

/*ADD FOR 3652C/3628C*/
#define DEV_SWDRV_PORT_NBR_PER_MOD		32
#define DEV_SWDRV_MOD_NBR_OF_5650		1
#define DEV_SWDRV_MOD_NBR_OF_5655		2

#define LEDDRV_UP_ENABLE                0x01
#define LEDDRV_UP_DISABLE               0x00

#define LED_PROGRAM_SIZE                300
/* NAMING CONSTANT DECLARATIONS
 */

/* Define the port operation link status.
 * Note: 1. For normal port link-up, using the (DEV_SWDRV_PORT_LINK_UP | DEV_SWDRV_NORMAL_PORT_TYPE)
 *       2. For combo port link-up in copper mode, using the (DEV_SWDRV_PORT_LINK_UP | DEV_SWDRV_COMBO_COPPER_TYPE)
 *       3. For combo port link-up in serdes mode, using the (DEV_SWDRV_PORT_LINK_UP | DEV_SWDRV_COMBO_SERDES_TYPE)
 *
 */
#define DEV_SWDRV_PORT_LINK_DOWN            0
#define DEV_SWDRV_PORT_LINK_UP              1
#define DEV_SWDRV_NORMAL_PORT_TYPE          1
#define DEV_SWDRV_COMBO_COPPER_TYPE         2
#define DEV_SWDRV_COMBO_SERDES_TYPE         4


/* Define the operation mode of Storm Control.
 * Note: 1. The traffic storm in the netwrok can be evaluated by the following way:
 *          a) Packet rate : number of packet per second
 *          b) Byte rate   : number of bytes per second
 *          c) Percentage  : the utilization of a given ethernet segment
 *       2. The Storm Control shall be per port based unless the ASIC limited.
 *       3. The Storm Control threshold value will be set to one of three mode:
 *          - packet rate, byte rate or percentage
 *       4. In most of ASIC, the Storm Control is based on the threshold vaule of received data,
 *          and it is ASIC dependent
 *       5. We may need to define the Private MIB to allow the user to select the operation mode of
 *          Strom Control. The naming constants defined here shall be obsoleted by the Leaf
 *          Constants defined in the Private MIB when MIB object for Storm Control mode is defined.
 */
#define DEV_SWDRV_STORM_CTRL_MODE_PACKET_RATE   1
#define DEV_SWDRV_STORM_CTRL_MODE_BYTE_RATE     2
#define DEV_SWDRV_STORM_CTRL_MODE_PERCENTAGE    4


/* Define the number of Traffic Class (Queues) shall be used in different application
 * Note: 1. In some application, the ASIC may need to change the number of traffic classes
 *          to suppot it.
 *          For example, the number of Traffic Classes (Queues) may need to be changed if Jumbo Frame
 *          is supported.
 *      2. The queue number can be changed/configured by the service routine provided
 *          in this package.
 *       3. We may need to define the Private MIB to allow the user to enable/configure the total number
 *          traffic classes (output queue) for a give port. The naming constants defined here shall be
 *          obsoleted by the Leaf Constants defined in the Private MIB when MIB object for the total number
 *          traffic classes (output queue) is defined.
 */
#define DEV_SWDRV_TRAFFIC_CLASS_NUM_1           1
#define DEV_SWDRV_TRAFFIC_CLASS_NUM_2           2
#define DEV_SWDRV_TRAFFIC_CLASS_NUM_4           4
#define DEV_SWDRV_TRAFFIC_CLASS_NUM_8           8


/* Arden, 10, 10, 2003, Forwarding attributes */
#define DEV_SWDRV_PORT_FORWARD_BROADCAST           0x0001
#define DEV_SWDRV_PORT_FORWARD_UNKNOWN_MULTICAST   0x0002
#define DEV_SWDRV_PORT_FORWARD_UNKNOWN_UNICAST     0x0004

/* Define the invalid physical port id for initialization.
 */
#define DEV_SWDRV_INVALID_PHY_PORT_ID   0xff

/* TYPE DECLARATIONS
 */
#if(SYS_CPNT_VXLAN == TRUE)
enum
{
    DEV_SWDRV_VXLAN_PORT_ACCESS,
    DEV_SWDRV_VXLAN_PORT_NETWORK
};

enum
{
    DEV_SWDRV_VXLAN_MATCH_PORT,
    DEV_SWDRV_VXLAN_MATCH_PORT_VLAN
};
#endif

/* Define data type for Port Mirror function
 * Note:  We may need to define the Private MIB to allow the user to select the operation
 *        mode of Port Mirror function. The naming constants defined here shall be obsoleted
 *        by the Leaf Constants defined in the Private MIB when the MIB object for mirror mode
 *        configuration is defined.
 */
enum DEV_SWDRV_Mirror_Mode_E
{
    DEV_SWDRV_MIRROR_MODE_INGRESS = 1,
    DEV_SWDRV_MIRROR_MODE_EGRESS,
    DEV_SWDRV_MIRROR_MODE_BOTH
};


/* Define data type for the Load/Traffic Balance Algorithm of Port Trunking function
 * Note:  1. We may need to define the Private MIB to allow the user to select
 *           the Load Balance Algorithm of Port Trunking function.
 *        2. The naming constants defined here shall be obsoleted by the Leaf
 *           Constants defined in the Private MIB when the MIB object for trunk mode
 *           configuration is defined.
 *        2. The default Load/Traffic Balance Algorithm will be ASIC dependant.
 */
enum DEV_SWDRV_Trunk_Mode_E
{
    DEV_SWDRV_TRUNK_MAC_SA = 1,
    DEV_SWDRV_TRUNK_MAC_DA,
    DEV_SWDRV_TRUNK_MAC_SA_DA,
    DEV_SWDRV_TRUNK_IP_SA,
    DEV_SWDRV_TRUNK_IP_DA,
    DEV_SWDRV_TRUNK_IP_SA_DA
};
#define DEV_SWDRV_TRUNK_DEFAULT_MODE    DEV_SWDRV_TRUNK_MAC_SA_DA


/* Define Port Type for Physical Device/Port Mapping table
 * Note: 1. The Port Type will indicate if a port is installed/avaialble in the system
 *       2. The Port Type will also indicate if it is operated as a normal port of stacking port
 *          for those ASICs which can reconfigure the port to function as a stcking port
 */
enum
{
    DEV_SWDRV_DEVICE_PORT_TYPE_NOT_EXIST = 1,
    DEV_SWDRV_DEVICE_PORT_TYPE_NORMAL,
    DEV_SWDRV_DEVICE_PORT_TYPE_STACKING_SIMPLEX,
    DEV_SWDRV_DEVICE_PORT_TYPE_STACKING_DUPLEX
};

/* Define Spanning Tree Mode
 * Note: 1. The Mode for Single/Multiple Tree, 802.1D never call this function
 *
 */
enum
{
    DEV_SWDRV_STAMODE_SSTP = 1,
    DEV_SWDRV_STAMODE_MSTP

};

enum DEV_SWDRV_FLOW_CONTROL_MODE_E
{
   DEV_SWDRV_FLOW_CONTROL_DISABLED = 1,
   DEV_SWDRV_FLOW_CONTROL_DISABLED_AUTO,
   DEV_SWDRV_HALF_DUPLEX_BACK_PRESSURE,
   DEV_SWDRV_FULL_DUPLEX_802_3X,
   DEV_SWDRV_FULL_DUPLEX_802_3X_AUTO,
   DEV_SWDRV_FLOW_CONTROL_ENABLED,
   DEV_SWDRV_FLOW_CONTROL_ENABLED_AUTO
};

#if (SYS_CPNT_SWCTRL_CABLE_DIAG == TRUE)
#if (SYS_CPNT_SWCTRL_CABLE_DIAG_CHIP == SYS_CPNT_SWCTRL_CABLE_DIAG_BROADCOM)
enum {
    DEV_SWDRV_PORT_CABLE_STATE_OK,
    DEV_SWDRV_PORT_CABLE_STATE_OPEN,
    DEV_SWDRV_PORT_CABLE_STATE_SHORT,
    DEV_SWDRV_PORT_CABLE_STATE_OPENSHORT,
    DEV_SWDRV_PORT_CABLE_STATE_CROSSTALK,
    DEV_SWDRV_PORT_CABLE_STATE_UNKNOWN,
    DEV_SWDRV_PORT_CABLE_STATE_COUNT
};

typedef struct
{
    UI32_T state;	/* state of all pairs */
    UI32_T npairs;	/* pair_* elements valid */
    UI32_T pair_state[4];  /* pair state */
    UI32_T pair_len[4];    /* pair length in metres */
    UI32_T fuzz_len;	/* len values +/- this */
}DEV_SWDRV_CableDiagResult_T;

#elif (SYS_CPNT_SWCTRL_CABLE_DIAG_CHIP == SYS_CPNT_SWCTRL_CABLE_DIAG_MARVELL)
enum DEV_SWDRV_Cable_Status_E
{
    CABLE_TEST_FAIL = 0,
    CABLE_NORMAL_CABLE,
    CABLE_OPEN_CABLE,
    CABLE_SHORT_CABLE,
    CABLE_IMPEDANCE_MISMATCH,
    CABLE_NO_CABLE,
    CABLE_NOT_TEST_BEFORE,
    CABLE_DIAG_NOT_SUPPORTED
} DEV_SWDRV_Cable_Status_T;

typedef struct DEV_SWDRV_CableDiagResult_S
{
    UI32_T    testStatus[4];
    UI8_T     errCableLen[4];
    UI32_T    normalCableLen;
    UI32_T    phyType;
}DEV_SWDRV_CableDiagResult_T;

typedef struct DEV_SWDRV_ExtCableDiagResult_S
{
    BOOL_T    isValid;
    UI32_T    pairSwap[2];
    UI32_T    pairPolarity[4];
    BOOL_T    pairSkewisValid;
    UI32_T    pairSkew[4];
    UI32_T    cableLenisValid[4];     /* result is not valid if: FE or length more than 135 meters */
    UI16_T    cableLen[4];    /* in meters */
    UI32_T    twoPairDownShift;
} DEV_SWDRV_ExtCableDiagResult_T;

typedef struct DEV_SWDRV_CableDiagResultGeneral_S
{
    UI32_T    last_test_time;
    UI32_T    ori_link_status; /* the link status before cable test */
    UI16_T    pair1Status;
    UI16_T    pair2Status;
    UI16_T    pair3Status;
    UI16_T    pair4Status;
    UI8_T     pair1FaultLen;
    UI8_T     pair2FaultLen;
    UI8_T     pair3FaultLen;
    UI8_T     pair4FaultLen;
    BOOL_T    under_testing;
    BOOL_T    is_dsp_mode;
}DEV_SWDRV_CableDiagResultGeneral_T; /* need sync with SWCTRL_Cable_Info_T and SWDRV_CableDiagInfo_T */

#else
#error "Chip not defined!"
#endif
#endif


/* Define data type for Physical Device/Port Mapping table
 * Note: 1. For each switch product, the physical mapping of each device/port
 *          will be layout/project/customer dependent.
 *       2. The Topology Discovery subsystem will dicover the physical mapping of
 *          (Device ID, phyport ID) of each unit based on the Product ID/Model number
 *          and number of units/expansion modules installed in the system.
 *          -- Device ID is used to identify a unique device/chip in a unit.
 *          -- Device ID is numbered from (1 .. total number of devices in a unit)
 *          -- phyport ID is used to identify a unique port of a given device/chip in a unit.
 *       3. The Topology Discovery subsystem will dicover the total number of devices/chips
 *          in the system (standalone/stackable/chassis system). A unique Module ID is assigned
 *          to each device/chip in the system during topology discovery.
 *          -- Module ID is used to identify a unique device/chip in the system.
 *          -- Module ID is numbered from (1 .. total number of devices in the system).
 *          -- Module ID is a sequentail (liner) number
 */
typedef struct
{
    UI8_T   module_id;              /* The module ID                            */
    UI8_T   device_id;              /* The device ID                            */
    UI8_T   device_port_id;         /* The physical port ID of a give device    */
    UI8_T   phy_id;                 /* The PHY ID of a given physical port      */
    UI8_T   port_type;              /* The type/function of given port          */
} DEV_SWDRV_Device_Port_Mapping_T;

/* EPR ES4649-ZZ-01303 modified on 09/05/05 by mike
 * Define a data type to store unit & port for Physical to logical  port Mapping table
 */
typedef struct DEV_SWDRV_PortTableStats_S
{
    UI32_T   portLinkStatus[SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT];
    UI32_T   portSpeedDuplex[SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT];
    UI32_T   portFlowCtrl[SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT];
}DEV_SWDRV_PortTableStats_T;
typedef struct
{
    UI8_T   unit_id;
    UI8_T   port_id;
}DEV_SWDRV_Logical_Port_Mapping_T;

/* This data structure is used for topology to feed topology information to dev_swdrv
 * dev_swdrv shall configure the ASIC based on below rules
 * Line topology:
 * the top unit refer to the unit that UPLINK port is not connected
 * in line topology the uint_id[0] is the top unit's  Unit-ID, the traffic destinate to
 * the units between unit_id[0] and my self ID shall be forward through UPLINK and the Units
 * and the reset through DOWNLINK
 * example:   unit_id[0]  unit_id[1]   ....unit_id[3] ...
 *            module0,1   module2,3          module 6, 7 ...
 * traffic destinate to module 0,1,2,3 shall be forward via UPLINK port
 * Ring topology:
 * unit_id[0] is the UNIT-ID of master unit
 * break the ring on master unit's UPLINK port,  ie,the traffic destinate to
 * the units between unit_id[0] and my self ID shall be forward through UPLINK and the Units
 * and the reset through DOWNLINK
 * example:   unit_id[0]  unit_id[1]   ....unit_id[3] ...
 *            module0,1   module2,3          module 6, 7 ...
 */
typedef struct Stacking_Info_S
{
    UI8_T   my_unit_id;
    /* ring topology:
     * unit_id[0] is master UNIT ID
     * unit_id[1] is downlink unitID
     *   ...
     * Line Topology:
     * unit_id[0] is the most top uit ID
     * unit_id[1] is downlink unitID
     *   ...
     */
    UI8_T   unit_id[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK];

    /* ring topology:
     * start_module_id[0] is start module id of master UNIT
     * start_module_id[1] is start module id of master's downlink unitID
     * ...
     * Line Topology:
     * start_module_id[0] is start module id of the most top uitt
     * start_module_id[1] is start module id of unit_id[0]'s downlink unit
     */
    UI8_T   start_module_id[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK];

    /* num_module_id[i] is number of modules in unit_id[i]
     */
    UI8_T   num_module_id[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK];

    /* unit_id array valid through 0.. (total_units_in_stack-1)
     */
    UI8_T   total_units_in_stack;

    /* cpu_enabled_device_id[0] is the device id that unit_id[0]'s CPU connected.
     */
    UI8_T   cpu_enabled_device_id[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK];

    /* for line topology use
     */
    UI8_T   master_unit_id;
    BOOL_T  Is_Ring;
    BOOL_T  Cutoff_flag;    /* not used */
    UI8_T   expansion_module_id[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK];  /* potencial issue */
#if (SYS_CPNT_UNIT_HOT_SWAP == TRUE)
    UI8_T   second_module_id[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK];
    UI8_T   third_module_id[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK];
    UI8_T   fourth_module_id[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK];
#endif
#if (SYS_CPNT_STACKING_BUTTON == TRUE)
  /*stacking button is pressed or not*/
    BOOL_T   stacking_is_enable;
#endif
}Stacking_Info_T;

typedef struct Stacking_Info_Old_S
{
    UI8_T   my_unit_id;
    UI8_T   unit_id[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK];
    UI8_T   start_module_id[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK];
    UI8_T   num_module_id[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK];
    UI8_T   total_units_in_stack;
    UI8_T   master_unit_id;
    BOOL_T  Is_Ring;
    BOOL_T  Cutoff_flag;
    UI8_T   expansion_module_id[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK];
}Stacking_Info_Old_T;

typedef struct DEV_SWDRV_PHY_Reg_Operation_S
{
    UI16_T reg_addr;
    UI16_T reg_val;  /* only the corresponding bit in reg_val_mask set as 1 will be set */
    UI16_T reg_val_mask;
} DEV_SWDRV_PHY_Reg_Operation_T;

#if defined(SYS_ADPT_DEV_SWDRV_XGSIII_50PORT_BOARD_INTER_HG_PORT1_BY_DEV_ID)
#define DEV_SWDRV_XGSIII_50PORT_BOARD_INTER_HG_PORT1(device_id)     SYS_ADPT_DEV_SWDRV_XGSIII_50PORT_BOARD_INTER_HG_PORT1_BY_DEV_ID(device_id)
#define DEV_SWDRV_XGSIII_50PORT_BOARD_INTER_HG_PORT2(device_id)     SYS_ADPT_DEV_SWDRV_XGSIII_50PORT_BOARD_INTER_HG_PORT2_BY_DEV_ID(device_id)
#else
#define DEV_SWDRV_XGSIII_50PORT_BOARD_INTER_HG_PORT1(device_id)     SYS_ADPT_DEV_SWDRV_XGSIII_50PORT_BOARD_INTER_HG_PORT1
#define DEV_SWDRV_XGSIII_50PORT_BOARD_INTER_HG_PORT2(device_id)     SYS_ADPT_DEV_SWDRV_XGSIII_50PORT_BOARD_INTER_HG_PORT2
#endif

#if (SYS_CPNT_STACKING == TRUE)
#define BOTH_STACKINGPORT                                                          SYS_ADPT_BOTH_STACKINGPORT
#define MAINBRD_To_EXPSION_STACKINGPORT                               SYS_ADPT_MAINBRD_To_EXPSION_STACKINGPORT
#define EXPSION_To_MAINBRD_STACKINGPORT                               SYS_ADPT_EXPSION_To_MAINBRD_STACKINGPORT
#endif

/* port media type
 */
enum {
    DEV_SWDRV_PORT_MEDIA_COPPER,
    DEV_SWDRV_PORT_MEDIA_FIBER,
    DEV_SWDRV_PORT_MEDIA_UNKNOWN,
};

#if (SYS_CPNT_MAC_IN_MAC == TRUE)
/* for MAC-in-MAC
 *
 * NOTE: should sync to swdrv_type.h
 */
typedef struct
{
    UI32_T isid;

   /* output param for creation; input param for deletion
    *
    * for delection,
    * 1) fill all field except hw_idx or
    * 2) specify hw_idx and zero other field
    */
    UI32_T hw_idx;
} DEV_SWDRV_MimServiceInfo_T;

typedef enum
{
    DEV_SWDRV_MIM_PORT_TYPE_HWIDX,
    DEV_SWDRV_MIM_PORT_TYPE_ACCESS,
    DEV_SWDRV_MIM_PORT_TYPE_BACKBONE,
} DEV_SWDRV_MimPortType_T;

typedef struct
{
    UI32_T isid;
    UI32_T unit;
    UI32_T port;
    DEV_SWDRV_MimPortType_T port_type;
    union {
        struct {
            UI32_T svid;
            UI32_T cvid;
        } access;
        struct {
            UI32_T egr_vid;
            UI8_T egr_src_addr[SYS_ADPT_MAC_ADDR_LEN];
            UI8_T egr_dst_addr[SYS_ADPT_MAC_ADDR_LEN];
        } backbone;
    } ext;

   /* output param for creation; input param for deletion
    *
    * to delete port by hw_idx,
    * specify port_type = HWIDX and hw_idx of port to delete.
    */
    UI32_T hw_idx;
} DEV_SWDRV_MimPortInfo_T;
#endif /* (SYS_CPNT_MAC_IN_MAC == TRUE) */

#if (SYS_CPNT_VXLAN == TRUE)
typedef struct
{
    UI32_T vfi;
    UI32_T vnid;
    UI32_T bc_group;
} DEV_SWDRV_VxlanVpnInfo_T;
#endif /* (SYS_CPNT_VXLAN == TRUE) */

typedef struct {
    int medium_copper:1;
    int medium_fiber_100m:1;
    int medium_fiber_1000m:1;
    int medium_fiber_10g:1;
    int medium_fiber_25g:1;
    int medium_fiber_40g:1;
    int medium_fiber_100g:1;

    int spd_10m_hd:1;
    int spd_10m_fd:1;
    int spd_100m_hd:1;
    int spd_100m_fd:1;
    int spd_1000m_hd:1;
    int spd_1000m_fd:1;
    int spd_10g_hd:1;
    int spd_10g_fd:1;
    int spd_25g_fd:1;
    int spd_40g_hd:1;
    int spd_40g_fd:1;
    int spd_100g_fd:1;

    int pause:1;
    int pause_asymm:1;

    int autoneg:1;

    int fec_baser:1;
    int fec_rs:1;
} DEV_SWDRV_PortAbility_T;

typedef enum
{
    DEV_SWDRV_VLAN_FLOODING_UKN_UC = 0,
    DEV_SWDRV_VLAN_FLOODING_UKN_MC,
    DEV_SWDRV_VLAN_FLOODING_BC
} DEV_SWDRV_VlanFloodingType_T;

#if (SYS_CPNT_HASH_SELECTION == TRUE)
typedef struct
{
    union {
        struct {
            unsigned char    src_mac    :1;
            unsigned char    dst_mac    :1;
            unsigned char    vlan       :1;
            unsigned char    ether_type :1;
        } item;
        UI8_T value;
    } arg;
} DEV_SWDRV_HashSelection_L2_T;

typedef struct
{
    union {
        struct {
            unsigned char    src_ip       :1;
            unsigned char    dst_ip       :1;
            unsigned char    vlan         :1;
            unsigned char    src_l4_port  :1;
            unsigned char    dst_l4_port  :1;
            unsigned char    protocol_id  :1;
        } item;
        UI8_T value;
    } arg;
} DEV_SWDRV_HashSelection_IPv4_T;

typedef struct
{
    union {
        struct {
            unsigned char    src_ip       :1;
            unsigned char    dst_ip       :1;
            unsigned char    vlan         :1;
            unsigned char    src_l4_port  :1;
            unsigned char    dst_l4_port  :1;
            unsigned char    next_header  :1;
        } item;
        UI8_T value;
    } arg;
} DEV_SWDRV_HashSelection_IPv6_T;

typedef struct
{
    UI8_T  hw_block_index;

    DEV_SWDRV_HashSelection_L2_T      pkt_l2;
    DEV_SWDRV_HashSelection_IPv4_T    pkt_ipv4;
    DEV_SWDRV_HashSelection_IPv6_T    pkt_ipv6;
} DEV_SWDRV_HashSelBlockInfo_T;
#endif /*#if (SYS_CPNT_HASH_SELECTION == TRUE)*/

#if (SYS_CPNT_WRED == TRUE)
typedef struct
{
    I8_T queue_id;
    UI32_T min;
    UI32_T max;
    UI32_T drop;
    UI32_T ecn;
    UI32_T flag;
}DEV_SWDRV_RandomDetect_T;
#endif
/* EXPORTED SUBPROGRAM SPECIFICATIONS
 */

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_ChipInit
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function initiate chip resources
 * INPUT   : None
 * OUTPUT  : None
 * RETURN  : None
 * NOTE    : This function must be called before common library initiate
 * -------------------------------------------------------------------------------------------
 */
void DEV_SWDRV_ChipInit(void) ;

/* Switch Device Driver Initialization
 */
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_Init
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function allocates the system resource for low level switch
 *           driver initiation.
 * INPUT   : unit_port_to_device_port_mapping_table
 * OUTPUT  : None
 * RETURN  : None
 * NOTE    : 1. For a Centralized (Tightly Coupling) system, the NULL Topology
 *              Table WILL be passed to the low level switch driver during the system init.
 *              This is because the system topology won't be available until Topology
 *              Discovery procedure is complete.
 *           2. The System Control/Topology Discovery subsystem shall provide the
 *              system topology to the low level switch drive.
 *           3. The unit_port_to_device_port_mapping_table provides the port mapping
 *              from user view (unit, port) to physical view (device id, physical port id).
 *              Please refer to DEV_SWDRV_SetDevicePortMapping() for detailed definition
 *              of mapping table .
 * -------------------------------------------------------------------------------------------
 */
/* void DEV_SWDRV_Init(DEV_SWDRV_Device_Port_Mapping_T *unit_port_to_device_port_mapping_table[SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK]);*/
void DEV_SWDRV_Init(void);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_ResetOnDemand
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function reset the system resource for low level switch
 *           driver initiation.
 * INPUT   : None
 * OUTPUT  : None
 * RETURN  : None
 * NOTE    : 1. Reset Chip & Disable chip port status or clear database
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_ResetOnDemand(BOOL_T include_cross_bar);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetDevicePortMapping
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function provides the system topology to the low level switch driver.
 *           This function also configures the Stacking Port for Stackable design.
 *
 * INPUT   : unit_port_to_device_port_mapping_table
 * OUTPUT  : None
 * RETURN  : None
 * NOTE    : 1. This function shall be invoked during system start-up or when
 *              Hot-Swap/Topology change occured.
 *           2. For a Distributed (Loosely Coupling) system, this function WILL BE
 *              invoked by DEV_SWDRV_Init() during the system init
 *           3. Each time when topology is changed, this functon will be
 *              invoked by STK_CTRL subsystem to provide the new system topology
 *              to the low level switch driver.
 *              However, for a Distributed (Loosely Coupling) System, this function
 *              SHALL NOT be invoked by STK_CTRL subsystem on the 1st topology change.
 *           4. When this function is invoked, ASIC should be reset before
 *              device/port are remapped.
 *
 *           5. The following is the definition of device/port mapping table:
 *
 *              a) For a Centralized (Tightly Coupling) System, the size of table will be
 *                 (SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK *
 *                  SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT) bytes
 *
 *              b) For a Distributed (Loosely Couling) system, the size of table will be
 *                 (SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT) *
 *                  sizeof (DEV_SWDRV_Device_Port_Mapping_T) bytes
 *
 *              c) There device/port mapping table provides the following informantion:
 *
 *                  (unit, port)    <-->    (device ID, physical port ID)
 *                  (unit, port)    <-->    (module ID, physical port ID)
 *                  (unit, port)    <-->    (PHY ID)
 *
 *                  where
 *                      unit            : 1 .. SYS_ADPT_MAX_NBR_OF_UNIT_PER_STACK
 *                      port            : 1 .. SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT
 *                      device ID       : 1 .. total number of devices (chips) in a unit
 *                      module ID       : 1 .. total number of devices (chips) in a stacking/chassis system
 **                     physical port ID: 1 .. total number of ports in a device (chip)
 *
 *              d) For those non-existed port (e.g. expansion module/slot not installed),
 *                 the given port type will be DEV_SWDRV_DEVICE_PORT_TYPE_NOT_EXIST.
 *                 The respective physical device/port/PHY id will be set to 255, and
 *                 shall be ignored by the low level switch driver.
 *
 *              e) For those ports which do not require the PHY, the PHY ID will be set to 255,
 *                 and shall be ignored by the low level switch driver.
 *
 *              f) The meaning/definition of the Device ID is ASIC/system dependent.
 *                 For example, For some ASIC, Device ID is equvalent to Moudle ID
 *                 range from 0 .. MAX value, and the value is global assigned.
 *
 *                 In some ASIC, Device ID is equvalent Chip ID range from 0 .. max,
 *                 but the value is local assigned, e.g. the same Device ID can be
 *                 assigned to Chip located in different unit.
 *
 *              << (unit, port) to (device id, physical port id) mapping table >>
 *              =====================================================================
 *              | unit-port      |             physical-port           | PHY Address
 *              =================|===========|=========================|=============
 *              |(unit,port)     | Module Id | Device Id | PhyPort Id  |   PHYId
 *              |================|===========|===========|=============|=============
 *              |    (1, 1)      |     0     |     0     |      0      |     1
 *              |    (1, 2)      |     0     |     0     |      1      |     2
 *              |    (1, 3)      |     0     |     0     |      2      |     3
 *              |    (1, 4)      |     0     |     0     |      3      |     4
 *              |    (1, 5)      |     0     |     0     |      4      |     5
 *              |    (1, 6)      |     0     |     0     |      5      |     6
 *              |    (1, 7)      |     0     |     0     |      6      |     7
 *              |    (1, 8)      |     0     |     0     |      7      |     8
 *              |    (1, 9)      |     1     |     1     |      0      |     1
 *              |    (1, 10)     |     1     |     1     |      1      |     2
 *              |    (1, 11)     |     1     |     1     |      2      |     3
 *              |    (1, 12)     |     1     |     1     |      3      |     4
 *              |      ...       |    ...    |    ...    |     ...     |    ...
 *              |    (1, 23)     |     2     |     2     |      6      |     7
 *              | (1, max_port)  |     2     |     2     |      7      |     8
 *              ---------------------------------------------------------  ------------
 *              |    (2, 1)      |     3     |     0     |      0      |     1
 *              |    (2, 2)      |     3     |     0     |      1      |     2
 *              |    (2, 3)      |     3     |     0     |      2      |     3
 *              |    (2, 4)      |     3     |     0     |      3      |     4
 *              |    (2, 5)      |     3     |     0     |      4      |     5
 *              |    (1, 6)      |     3     |     0     |      5      |     6
 *              |    (1, 7)      |     3     |     0     |      6      |     7
 *              |    (1, 8)      |     3     |     0     |      7      |     8
 *              |    (1, 9)      |     4     |     1     |      0      |     1
 *              |    (1, 10)     |     4     |     1     |      1      |     2
 *              |      ...       |    ...    |    ...    |     ...     |    ...
 *              |      ...       |    ...    |    ...    |     ...     |    ...
 * ----------------------------------------------------------------------------------------------------
 */
void DEV_SWDRV_SetDevicePortMapping(DEV_SWDRV_Device_Port_Mapping_T unit_port_to_device_port_mapping_table[][SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT]);

/*--------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetLocalDeviceIDFromModuleID
 *---------------------------------------------------------------------------
 * PURPOSE:  mapping physical port/phy to user port
 * INPUT:    device_id
 * OUTPUT:   module_id
 * RETURN:   TRUE/FALSE
 * NOTE:
 *---------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_GetLocalDeviceIDFromModuleID(UI32_T unit, UI32_T module_id, UI32_T *device_id);

BOOL_T DEV_SWDRV_GetModuleIdFromLocalDeviceId(UI32_T unit, UI32_T device_id, UI32_T *module_id);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_Register_PortLinkUp_CallBack
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function registers the call-back function for port link up event.
 *           When when link state is changed from down to up, all the reigistered
 *           functions will be invoked/notified.
 * INPUT   : *fun(UI32_T unit_id, UI32_T port)   -- call back function pointer
 * OUTPUT  : none
 * RETURN  : none
 * NOTE    : The low level switch driver can use either polling or interrupt mechanism
 *           to detect the link state change.
 * -------------------------------------------------------------------------------------------
 */
void DEV_SWDRV_Register_PortLinkUp_CallBack(void (*fun)(UI32_T unit_id, UI32_T port));


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_Register_PortLinkDown_CallBack
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function registers the call-back function for port link down event.
 *           When when link state is changed from up to down, all the reigistered
 *           functions will be invoked/notified.
 * INPUT   : *fun(UI32_T unit_id,UI32_T port)   -- call back function pointer
 * OUTPUT  : none
 * RETURN  : none
 * NOTE    : The low level switch driver may use either polling or interrupt mechanism
 *           to detect the link state change.
 * -------------------------------------------------------------------------------------------
 */
void DEV_SWDRV_Register_PortLinkDown_CallBack(void (*fun)(UI32_T unit_id, UI32_T port));


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_Register_PortSpeedDuplex_CallBack
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function registers the call-back function for port speed/duplex
 *           change event.
 *           When the speed/duplex is changed on any port, all the reigistered
 *           functions will be invoked/notified.
 * INPUT   : *fun(UI32_T unit_id, UI32_T port, UI32_T speed_duplex)   -- call back function pointer
 * OUTPUT  : none
 * RETURN  : none
 * NOTE    : 1. The low level switch driver may use either polling or interrupt mechanism
 *              to detect the speed/duplex change.
 *              The speed/duplex change is the result of Auto-Negotiation between link partner.
 *           2. Whenever speed/duplex is changed, DEV_SWDRV needs to notify SWDRV/SWCTRL,
 *              and SWCTRL needs to further notify
 *              - LED_MGMT
 *              - STA
 *              - IML
 *              - and more ...
 *           3. The enumerated value for speed/duplex mode is defined in file, "leaf_es3626a.h".
 *                  #define VAL_portSpeedDpxStatus_error
 *                  #define VAL_portSpeedDpxStatus_halfDuplex10
 *                  #define VAL_portSpeedDpxStatus_fullDuplex10
 *                  #define VAL_portSpeedDpxStatus_halfDuplex100
 *                  #define VAL_portSpeedDpxStatus_fullDuplex100
 *                  #define VAL_portSpeedDpxStatus_halfDuplex1000
 *                  #define VAL_portSpeedDpxStatus_fullDuplex1000
 *
 * -------------------------------------------------------------------------------------------
 */
void DEV_SWDRV_Register_PortSpeedDuplex_CallBack(void (*fun)(UI32_T unit_id,
                                                             UI32_T port,
                                                             UI32_T speed_duplex));


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_Register_PortFlowCtrl_CallBack
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function registers the call-back function for port flow control change.
 *           When the flow control status (mode) is changed on any port,
 *           all the reigistered functions will be invoked/notified.
 * INPUT   : *fun(UI32_T unit_id, UI32_T port, UI32_T flow_control)   -- call back function pointer
 * OUTPUT  : none
 * RETURN  : none
 * NOTE    : 1. The low level switch driver may use either polling or interrupt mechanism
 *              to detect if the flow control status (mode) is changed.
 *              The flow control status(mode) change is the result of Auto-Negotiation
 *              between link partner.
 *           2. Whenever flow control changes, DEV_SWDRV needs to notify SWDRV/SWCTRL,
 *              and SWCTRL needs to further notify
 *              - LED_MGMT
 *              - STA
 *              - IML
 *              - and more ...
 *           3. The enumerated value for flow control status (mode) is defined in file, "leaf_es3626a.h".
 *                  #define VAL_portFlowCtrlStatus_error
 *                  #define VAL_portFlowCtrlStatus_backPressure
 *                  #define VAL_portFlowCtrlStatus_dot3xFlowControl
 *                  #define VAL_portFlowCtrlStatus_none
 *
 * -------------------------------------------------------------------------------------------
 */
void DEV_SWDRV_Register_PortFlowCtrl_CallBack(void (*fun)(UI32_T unit_id,
                                                          UI32_T port,
                                                          UI32_T flow_control));

/* Port Configuration
 */
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_UpdatePortSfpTxEnable
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function will configure the sfp tx enable setting kept in the
 *           shadow database to the hardware device.
 * INPUT   : unit  -  which unit
 *           port  -  which port
 * OUTPUT  : none
 * RETURN  : TRUE  -  Successfully. FALSE - Failed.
 * NOTE    : 1. This function needs to be called when the insertion of a QSFP
 *              transceiver is detected. However, it is no harm to called when
 *              other types of a transceiver is inserted.
 *
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_UpdatePortSfpTxEnable(UI32_T unit, UI32_T port);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnablePortAdmin
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function enables a specified port
 * INPUT   : unit_id            -- in which unit
 *           port               -- which port wants to be enabled
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given (unit, port) is not available
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnablePortAdmin(UI32_T unit_id, UI32_T port);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnableHGPortAdmin
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function enables a specified port
 * INPUT   :
 *
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              --
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnableHGPortAdmin(void);



/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisablePortAdmin
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function disables a specified port
 * INPUT   : unit_id            -- in which unit
 *           port               -- which port wants to be disabled
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
             FALSE              -- If a given (unit, port) is not available
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisablePortAdmin(UI32_T unit_id, UI32_T port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortCfgSpeedDuplex
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets the specified speed/duplex mode for a given port.
 *           This function forces a given port to operate on the specified speed/duplex mode
 * INPUT   : unit_id            -- in which unit
 *           port               -- which port to set
 *           speed_duplex       -- speed/duplex mode for a given port
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given (unit, port) is not available, or it can not support
 *                                 the specified speed/duplex mode
 * NOTE    : 1. This function is applied for "Forced" speed/duplex mode only.
 *           2. The enumerated value for speed/duplex mode is defined in file, "leaf_es3626a.h".
 *                  #define VAL_portSpeedDpxCfg_halfDuplex10
 *                  #define VAL_portSpeedDpxCfg_fullDuplex10
 *                  #define VAL_portSpeedDpxCfg_halfDuplex100
 *                  #define VAL_portSpeedDpxCfg_fullDuplex100
 *                  #define VAL_portSpeedDpxCfg_halfDuplex1000
 *                  #define VAL_portSpeedDpxCfg_fullDuplex1000
 *           3. The low level switch driver may need to do the sementic check
 *              to verify if the input speeed/duple mode can be supported
 *              by a given port type.
 *
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortCfgSpeedDuplex(UI32_T unit_id, UI32_T port, UI32_T speed_duplex);

#if (SYS_CPNT_SUPPORT_FORCED_1000BASE_T_MODE == TRUE)
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPort1000BaseTForceMode
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets the specified speed/duplex mode for a given port.
 *           This function forces a given port to operate on the specified speed/duplex mode
 * INPUT   : unit_id            -- in which unit
 *           port               -- which port to set
 *           force_mode         -- master/slave mode for a given force 1000T port
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given (unit, port) is not available, or it can not support
 *                                 the specified speed/duplex mode
 * NOTE    : 1. This function is applied for 1000T "Forced" master/slave mode only.
 *           2. The enumerated value for speed/duplex mode is defined in file, "leaf_es3626a.h".
 *                  #define VAL_portSpeedDpxCfg_halfDuplex10
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPort1000BaseTForceMode(UI32_T unit_id, UI32_T port, UI32_T force_mode);
#endif


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetCopperEnergyDetect
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function get the copper energy detect status.
 * INPUT   : unit_id                -- in which unit
 *           port                   -- which port to set
 *           copper_energy_detect   -- on/off mode for a given force 1000T port
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given (unit, port) is not available, or it can not support
 *                                 the specified speed/duplex mode
 * NOTE    : 1. This function is applied for 1000T "Forced" master/slave mode only.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_GetCopperEnergyDetect(UI32_T unit_id, UI32_T port, UI32_T *copper_energy_detect);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnablePortAutoNeg
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function enables the auto-negotiation mode of a given port
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given (unit, port) is not available, or can not support
 *                                 auto-negotiation mode
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnablePortAutoNeg(UI32_T unit_id, UI32_T port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisablePortAutoNeg
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function disables the auto-negotiation mode of a given port
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given (unit, port) is not available, or it can not support
 *                                 auto-negotiation mode
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisablePortAutoNeg(UI32_T unit_id, UI32_T port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnablePortCfgFlowCtrl
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function enables the 802.3x/backpressure flow control function
 *           of a given port
 * INPUT   : unit_id            -- in which unit
 *           port               -- which port to enable
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given (unit, port) is not available, or it can not support
 *                                 flow control function.
 * NOTE    : 1. The Flow Control mode will be auto determined by the duplex mode of a given port.
 *           2. The low level switch driver may need to enable both 802.3x flow control and/or
 *              backpressure flow control for a given port.
 *           3. For those ASICS which CAN ONLY support global based flow control configuration,
 *              the input parameter (unit_id, port) SHALL BE ignored.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnablePortCfgFlowCtrl(UI32_T unit_id, UI32_T port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisablePortCfgFlowCtrl
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function disables the 802.3x/backpressure flow control function
 *           of a given port
 * INPUT   : unit_id            -- in which unit
 *           port               -- which port to disable
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given (unit, port) is not available, or it can not support
 *                                 flow control function.
 * NOTE    : 1. The low level switch driver may need to disable/reset both 802.3x flow control
 *              and/or backpressure flow control for a given port.
 *           2. For those ASICS which CAN ONLY support global based flow control configuration,
 *              the input parameter (unit_id, port) SHALL BE ignored.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisablePortCfgFlowCtrl(UI32_T unit_id, UI32_T port);

/* -------------------------------------------------------------------------------------
 * ROUTINE NAME - BCMDRV_SetPortCfgFlowCtrl
 * -------------------------------------------------------------------------------------
 * PURPOSE : This function set the mode of the 802.3x/backpressure flow control function
 *           of a given port
 * INPUT   : unit_id -- in which unit
 *           port  -- which port to config
 *           mode  -- VAL_portFlowCtrlCfg_enabled: Turn on both TX and RX pause function
 *                    VAL_portFlowCtrlCfg_disabled: Turn off both TX and RX pause function
 *                    VAL_portFlowCtrlCfg_tx: Turn on TX and turn off RX pause function.
 *                    VAL_portFlowCtrlCfg_rx: Turn on RX and turn off TX pause function.
 * OUTPUT  : None
 * RETURN  : TRUE     -- Success
 *           FALSE    -- If a given (unit, port) is not available, or it can not support
 *                       flow control function that caller specify.
 * NOTE    : 1. The operation Flow Control mode will be auto determined by the duplex
 *              mode of a given port.
 *           2. The low level switch driver may need to enable both 802.3x flow control
 *              and/or backpressure flow control for a given port.
 *           3. For those ASICS which CAN ONLY support global based flow control
 *              configuration, the input parameter (unit_id, port) SHALL BE ignored.
 * -------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortCfgFlowCtrl(UI32_T unit_id, UI32_T port, UI32_T mode);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortAutoNegCapability
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets/configures the auto-negotiation capability of a given port
 * INPUT   : unit_id            -- in which unit
 *           port               -- which port to set
 *           capability         -- port auto-negotiation capability
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given (unit, port) is not available.
 * NOTE    : 1. The Flow Control capability bit will not depend on the flow control mode.
 *           ie. If flow control is enabled, the Flow Control capability bit could be either
 *               set (to '1') or nonset (to '0').
 *           2. The enumerated value for auto-negotiation capability is defined in file, "leaf_es3626a.h".
 *              #define SYS_VAL_portCapabilities_portCap10half
 *              #define SYS_VAL_portCapabilities_portCap10full
 *              #define SYS_VAL_portCapabilities_portCap100half
 *              #define SYS_VAL_portCapabilities_portCap100full
 *              #define SYS_VAL_portCapabilities_portCap1000half
 *              #define SYS_VAL_portCapabilities_portCap1000full
 *              #define SYS_VAL_portCapabilities_portCapSym
 *              #define SYS_VAL_portCapabilities_portCapFlowCtrl
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortAutoNegCapability(UI32_T unit_id,
                                          UI32_T port,
                                          UI32_T capability);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortType
 * -------------------------------------------------------------------------
 * PURPOSE : This function will get port type info of a specified port
 * INPUT   : unit_id            -- in which unit
 *           port               -- which port to set
 *           port_type          -- port type
 * OUTPUT  : None
 * RETURN  : True: Successfully, False: If not available
 * NOTE    : Please refere the definition in MIB header:
 *             #define VAL_portType_other	                    1L
 *             #define VAL_portType_hundredBaseTX	            2L
 *             #define VAL_portType_hundredBaseFX	            3L
 *             #define VAL_portType_thousandBaseSX	            4L
 *             #define VAL_portType_thousandBaseLX	            5L
 *             #define VAL_portType_thousandBaseT	            6L
 *             #define VAL_portType_thousandBaseGBIC	        7L
 *             #define VAL_portType_thousandBaseSfp	            8L
 *             #define VAL_portType_hundredBaseFxScSingleMode	9L
 *             #define VAL_portType_hundredBaseFxScMultiMode	10L
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetPortType(UI32_T unit_id,
                             UI32_T port,
                             UI32_T *port_type);


/* MAU MIB Configuration and status getting
 */
/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortRestartAutoNego
 * -------------------------------------------------------------------------
 * FUNCTION: To triger PHY to re-start auto-nego.
 * INPUT   : unit -- Which unit.
 *           port -- Which port.
 * OUTPUT  : None.
 * RETURN  : TRUE/FALSE
 * NOTE    : None.
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetPortRestartAutoNego(UI32_T unit, UI32_T port);

#if (SYS_CPNT_MAU_MIB == TRUE)
/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortAutoNegoRemoteFaultAdvertisement
 * -------------------------------------------------------------------------
 * FUNCTION: Set auto-nego remote fault advertisement bits.
 * INPUT   : unit         -- Which unit.
 *           port         -- Which port.
 *           remote_fault -- VAL_ifMauAutoNegRemoteFaultAdvertised_noError
 *                           VAL_ifMauAutoNegRemoteFaultAdvertised_offline
 *                           VAL_ifMauAutoNegRemoteFaultAdvertised_linkFailure
 *                           VAL_ifMauAutoNegRemoteFaultAdvertised_autoNegError
 * OUTPUT  : None.
 * RETURN  : TRUE/FALSE
 * NOTE    : None.
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetPortAutoNegoRemoteFaultAdvertisement (UI32_T unit, UI32_T port, UI32_T remote_fault);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortAutoNegoRemoteFaultAdvertisement
 * -------------------------------------------------------------------------
 * FUNCTION: Set auto-nego remote fault advertisement bits.
 * INPUT   : unit         -- Which unit.
 *           port         -- Which port.
 * OUTPUT  : remote_fault -- VAL_ifMauAutoNegRemoteFaultAdvertised_noError
 *                           VAL_ifMauAutoNegRemoteFaultAdvertised_offline
 *                           VAL_ifMauAutoNegRemoteFaultAdvertised_linkFailure
 *                           VAL_ifMauAutoNegRemoteFaultAdvertised_autoNegError
 * RETURN  : TRUE/FALSE
 * NOTE    : None.
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetPortAutoNegoRemoteFaultAdvertisement (UI32_T unit, UI32_T port, UI32_T *remote_fault);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortLinkPartnerAutoNegoSignalingState
 * -------------------------------------------------------------------------
 * FUNCTION: Get the status if link partner in auto-nego signaling state.
 * INPUT   : unit  -- Which unit.
 *           port  -- Which port.
 * OUTPUT  : state -- VAL_ifMauAutoNegRemoteSignaling_detected
 *                    VAL_ifMauAutoNegRemoteSignaling_notdetected
 * RETURN  : TRUE/FALSE
 * NOTE    : If the link state is link-down, VAL_ifMauAutoNegRemoteSignaling_notdetected
 *           shall be outputed.
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetPortLinkPartnerAutoNegoSignalingState (UI32_T unit, UI32_T port, UI32_T *state);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortAutoNegoProcessState
 * -------------------------------------------------------------------------
 * FUNCTION: Get the status of auto-nego process.
 * INPUT   : unit  -- Which unit.
 *           port  -- Which port.
 * OUTPUT  : state -- VAL_ifMauAutoNegConfig_other
 *                    VAL_ifMauAutoNegConfig_configuring
 *                    VAL_ifMauAutoNegConfig_complete
 *                    VAL_ifMauAutoNegConfig_disabled
 *                    VAL_ifMauAutoNegConfig_parallelDetectFail
 * RETURN  : TRUE/FALSE
 * NOTE    : In this API, check "auto-nego" enable/disable first, if disabled
 *           return, then check "parallel detect fail", if true, return.
 *           Finally check status is "configuring" or "complete".
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetPortAutoNegoProcessState (UI32_T unit, UI32_T port, UI32_T *state);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortLinkPartnerAutoNegoCapa
 * -------------------------------------------------------------------------
 * FUNCTION: Get the auto-nego capability bits of link partner.
 * INPUT   : unit -- Which unit.
 *           port -- Which port.
 * OUTPUT  : capabilities -- bitmap:
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_bOther      )
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_b10baseT    )
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_b10baseTFD  )
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_b100baseT4  )
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_b100baseTX  )
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_b100baseTXFD)
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_b100baseT2  )
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_b100baseT2FD)
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_bFdxPause   )
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_bFdxAPause  )
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_bFdxSPause  )
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_bFdxBPause  )
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_b1000baseX  )
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_b1000baseXFD)
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_b1000baseT  )
 *                           (1 << VAL_ifMauAutoNegCapReceivedBits_b1000baseTFD)
 * RETURN  : TRUE/FALSE
 * NOTE    : If the link state is link-down, only (1 << VAL_ifMauAutoNegCapReceivedBits_bOther)
 *           shall be outputed.
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetPortLinkPartnerAutoNegoCapa (UI32_T unit, UI32_T port, UI32_T *capabilities);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortLinkPartnerAutoNegoRemoteFault
 * -------------------------------------------------------------------------
 * FUNCTION: Get the auto-nego remote fault of link partner.
 * INPUT   : unit -- Which unit.
 *           port -- Which port.
 * OUTPUT  : remote fault -- VAL_ifMauAutoNegRemoteFaultReceived_noError
 *                           VAL_ifMauAutoNegRemoteFaultReceived_offline
 *                           VAL_ifMauAutoNegRemoteFaultReceived_linkFailure
 *                           VAL_ifMauAutoNegRemoteFaultReceived_autoNegError
 *
 * RETURN  : TREU/FALSE
 * NOTE    : If the link state is link-down, VAL_ifMauAutoNegRemoteFaultReceived_noError
 *           shall be outputed.
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetPortLinkPartnerAutoNegoRemoteFault (UI32_T unit, UI32_T port, UI32_T *remote_fault);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortJabberState
 * -------------------------------------------------------------------------
 * FUNCTION: Get the status if the port in jabbering state.
 * INPUT   : unit  -- Which unit.
 *           port  -- Which port.
 * OUTPUT  : state -- VAL_ifMauJabberState_other
 *                    VAL_ifMauJabberState_unknown
 *                    VAL_ifMauJabberState_noJabber
 *                    VAL_ifMauJabberState_jabbering
 * RETURN  : TRUE/FALSE
 * NOTE    : None.
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetPortJabberState (UI32_T unit, UI32_T port, UI32_T *state);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortFalseCarrierSenseCounter
 * -------------------------------------------------------------------------
 * FUNCTION: Get the counter of the false carrier sense.
 * INPUT   : unit -- Which unit.
 *           port -- Which port.
 * OUTPUT  : counter: Just cunter.
 * RETURN  : TRUE/FALSE
 * NOTE    : None.
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetPortFalseCarrierSenseCounter (UI32_T unit, UI32_T port, UI32_T *counte);

#endif

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetMiniGbicPortLEDStatus
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function set mini gbic port active led
 * INPUT   : unit_id            -- in which unit
 *           port               -- which port to set
 *           status             -- ebanle /disable
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given (unit, port) is not available.
 * NOTE    :
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetMiniGbicPortLEDStatus(UI32_T unit_id, UI32_T port, BOOL_T status);

/* 802.1s (Multiple Spanning Tree) Configuration
 */
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetSTAMode
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets/configures the global spanning tree mode for the whole system
 * INPUT   : mode               -- spanning tree mode, use MIB define value
 *                                  #define DEV_SWDRV_STAMODE_SSTP(?)
 *                                  #define DEV_SWDRV_STAMODE_MSTP(?)
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the system can not support the specified spanning tree mode.
 * NOTE    : 1. This function shall be invoked during the system initiatation phase
 *              if the ASIC Chip needs to setup the global mode at system initialization.
 *           2. This function can also be used to toggle the global spanning tree mode.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetSTAMode(UI32_T mode);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortSTAState
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets the Port Spanning Tree State of the specified port.
 * INPUT   : mstid              -- Multi-Spanning Tree ID
 *           vlan_count         -- total vlan count
 *           vlan_list          -- the vlan list
 *           unit_id            -- which unit
 *           port               -- which port to set
 *           state              -- the port spanning tree state
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given port is not available
 * NOTE    : 1. In multiple spanning tree (MSTP) mode,
 *              a) In multiple spanning tree environment, each port will have a specific
 *                 state on a given spanning tree.
 *              b) Most of ASIC uses the per VLAN port state to implement the Port Spanning Tree State.
 *              c) Since a spanning tree is running over a certain VLANs, we need to configure the
 *                 all "per VLAN port states" to the same port state.
 *              d) The vlan_count and vlan_list shows the vlan groups that a given spanning tree
 *                 is running.
 *           2. In single spanning tree (SSTP) mode, the vlan_count and vlan_list shall be ignored.
 *              The calling route shall set vlan_count = 0, and vlan_list = NULL.
 *           3. The enumerated value for port spanning tree state is defined in file, "leaf_1493.h".
 *                  #define VAL_dot1dStpPortState_disabled
 *                  #define VAL_dot1dStpPortState_blocking
 *                  #define VAL_dot1dStpPortState_listening
 *                  #define VAL_dot1dStpPortState_learning
 *                  #define VAL_dot1dStpPortState_forwarding
 *           4. This function SHALL ONLY be supported/invoked for those ASICs which DO NOT have
 *              "Multiple Spanning Instance" concept in their design.
 *              This function is exclusive with the following service routines.
 *                  DEV_SWDRV_SetPortSTAStateWithMstidx();
 *                  DEV_SWDRV_AddVlanToSTAWithMstidx();
 *                  DEV_SWDRV_DeleteVlanFromSTAWithMstidx();
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortSTAState(UI32_T mstid,
                                 UI32_T vlan_count,
                                 UI16_T *vlan_list,
                                 UI32_T unit_id,
                                 UI32_T port,
                                 UI32_T state);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortSTAStateWithMstidx
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets the Port Spanning Tree State of the specified port with
 *           "Multiple Spanning Tree ID" associated.
 * INPUT   : mstidx             -- mstidx (multiple spanning tree index) to identify a unique spanning tree
 *           unit_id            -- which unit
 *           port               -- which port to set
 *           state              -- the port spanning tree state
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given port is not available
 * NOTE    : 1. This function SHALL ONLY be supported/invoked for those ASICs which have
 *              "Multiple Spanning Instance" concept in their design. "mstidx" will be used
 *              to identify a unique "Spanning Instance" in the system.
 *              This function is exclusive with the DEV_SWDRV_SetPortSTAStateWithMstidx()routine.
 *           2. For those ASICs which have "Multiple Spanning Instance" concept, this following
 *              set of service routines shall be invoked for Multiple Spanning Tree configuration:
 *                  DEV_SWDRV_SetPortSTAStateWithMstidx();
 *                  DEV_SWDRV_AddVlanToSTAWithMstidx();
 *                  DEV_SWDRV_DeleteVlanFromSTAWithMstidx();
 *           2. In multiple spanning tree (MSTP) mode, each port will have a specific
 *              state on a given spanning tree.
 *           3. In single spanning tree (SSTP) mode, the "mstidx" SHALL be ignored.
 *           4. The enumerated value for port spanning tree state is defined in file, "leaf_1493.h".
 *                  #define VAL_dot1dStpPortState_disabled
 *                  #define VAL_dot1dStpPortState_blocking
 *                  #define VAL_dot1dStpPortState_listening
 *                  #define VAL_dot1dStpPortState_learning
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortSTAStateWithMstidx(UI32_T mstidx, UI32_T unit_id, UI32_T port, UI32_T state);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_AddVlanToSTAWithMstidx
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function adds a VLAN to a given Spanning Tree instance.
 *           In Multiple Spanning environment, a Spanning Tree is running over a set of VLANs.
 * INPUT   : vid                -- the VLAN will be added to a given Spanning Tree
 *           mstidx             -- mstidx (multiple spanning tree index) to identify a unique spanning tree
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given VLAN is not available
 * NOTE    : 1. This function SHALL ONLY be supported/invoked for those ASICs which have
 *              "Multiple Spanning Instance" concept in their design. "mstidx" will be used
 *              to identify a unique "Spanning Instance" in the system.
 *           2. For those ASICs which have "Multiple Spanning Instance" concept, this following
 *              set of service routines shall be invoked for Multiple Spanning Tree configuration:
 *                  DEV_SWDRV_SetPortSTAStateWithMstidx();
 *                  DEV_SWDRV_AddVlanToSTAWithMstidx();
 *                  DEV_SWDRV_DeleteVlanFromSTAWithMstidx();
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_AddVlanToSTAWithMstidx(UI32_T vid, UI32_T mstidx);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DeleteVlanFromSTAWithMstidx
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function deletes a VLAN from a given Spanning Tree instance.
 *           In Multiple Spanning environment, a Spanning Tree is running over a set of VLANs.
 * INPUT   : vid                -- the VLAN will be deleted from a given Spanning Tree
 *           mstidx             -- mstid (multiple spanning tree index) to identify a unique spanning tree
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given VLAN is not available
 * NOTE    : 1. This function SHALL ONLY be supported/invoked for those ASICs which have
 *              "Multiple Spanning Instance" concept in their design. "mstidx" will be used
 *              to identify a unique "Spanning Instance" in the system.
 *           2. For those ASICs which have "Multiple Spanning Instance" concept, this following
 *              set of service routines shall be invoked for Multiple Spanning Tree configuration:
 *                  DEV_SWDRV_SetPortSTAStateWithMstidx();
 *                  DEV_SWDRV_AddVlanToSTAWithMstidx();
 *                  DEV_SWDRV_DeleteVlanFromSTAWithMstidx();
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DeleteVlanFromSTAWithMstidx(UI32_T vid, UI32_T mstidx);



/* VLAN Configuration
 */
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortPVID
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets the default "Port VLAN ID" for a given port
 * INPUT   : port               -- which port to set
 *           pvid               -- Port VID to set
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given port is not available
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortPVID(UI32_T unit_id, UI32_T port, UI32_T pvid);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortPVID
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function gets the default "Port VLAN ID" for a given port
 * INPUT   : unit               -- which unit
             port               -- which port
 *           pvid               -- Port VID
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If a given port is not available
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_GetPortPVID(UI32_T unit_id, UI32_T port, UI32_T *pvid) ;


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_CreateVlan
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function creates a specified VLAN
 * INPUT   : vid                -- the vid of the new created VLAN
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If total number of vlan created is over the max number of VLANs
 *           supported by ASIC.
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_CreateVlan(UI32_T vid);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DestroyVlan
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function deletes a specified VLAN
 * INPUT   : vid                -- which VLAN to delete
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified VLAN is not available.
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DestroyVlan(UI32_T vid);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetGlobalDefaultVlan
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function changes the global default VLAN
 * INPUT   : vid                -- the vid of the new default VLAN
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified VLAN is not available.
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetGlobalDefaultVlan(UI32_T vid);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DeletePortUntaggedVlanSet
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function delete the untagged port of the specified VLAN
 * INPUT   : unit_id            -- which unit to set
 *           port               -- spedified one port
 *           vid                -- specified a VLAN
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified VLAN is not available.
 * NOTE    : 1. delete untagged specific untag vlan port
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DeletePortUntaggedVlanSet(UI32_T unit_id, UI32_T port, UI32_T vid);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_AddPortUntaggedVlanSet
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function add the untagged port of the specified VLAN
 * INPUT   : unit_id            -- which unit to set
 *           port               -- spedified one port
 *           vid                -- specified a VLAN
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified VLAN is not available.
 * NOTE    : 1. add untagged specific untag vlan port
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_AddPortUntaggedVlanSet(UI32_T unit_id, UI32_T port, UI32_T vid);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DeletePortVlanSet
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function delete the port of the specified VLAN
 * INPUT   : unit_id            -- which unit to set
 *           port               -- spedified one port
 *           vid                -- specified a VLAN
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified VLAN is not available.
 * NOTE    : 1. delete specific vlan port
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DeletePortVlanSet(UI32_T unit_id, UI32_T port, UI32_T vid);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_AddPortVlanSet
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function add the port of the specified VLAN
 * INPUT   : unit_id            -- which unit to set
 *           port               -- spedified one port
 *           vid                -- specified a VLAN
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified VLAN is not available.
 * NOTE    : 1. add specific vlan port
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_AddPortVlanSet(UI32_T unit_id, UI32_T port, UI32_T vid);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortToVlanMemberSet
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets/updates the port member (egress port list)
 *           of the specified VLAN
 * INPUT   : unit_id            -- which unit to set
 *           vid                -- specified a VLAN
 *           *port_list         -- the updated port member list (egress port list)
 *                                 of a given VLAN
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified VLAN is not available.
 * NOTE    : 1. The port_list is a bitmap(same format as defined in RFC2674 Q-MIB)
 *           2. The length (byte count) of port list is defined by
 *              "SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST" for standalone system
 *           3. For a stacking system, port_list will be uport array which will be by 4 bytes
 *              resolution for each unit.  If the stacking is mixed port count, it will be
 *              passed by the SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT as the port count always.
 *              For example, for 24 port stacking system, the 2nd unit port 1 needs to be
 *              counted from byte 5.
 *           4. For a Distributed (Loosely Coupling) system, the all port list of every unit
 *              will be passed, unit_id need to be taken to count which byte is the start
 *              byte for this unit.
 *           5. For a Centralized (Tightly Coupling) System, the port_list represents
 *              all units/ports in the system in a linear port list format.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortToVlanMemberSet(UI32_T unit_id,
                                        UI32_T vid,
                                        UI8_T  *port_list);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortToVlanUntaggedSet
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets/updates the untagged port member (untagged port list)
 *           of the specified VLAN
 * INPUT   : vid                -- specified a VLAN
 *           *port_list         -- the updated untagged port member list (untagged port list)
 *                                 of a given VLAN
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified VLAN is not available.
 * NOTE    : 1. The port_list is a bitmap(same format as defined in RFC2674 Q-MIB)
 *           2. The length (byte count) of port list is defined by
 *              "SYS_ADPT_TOTAL_NBR_OF_BYTE_FOR_1BIT_PORT_LIST" for standalone system
 *           3. For a stacking system, port_list will be uport array which will be by 4 bytes
 *              resolution for each unit.  If the stacking is mixed port count, it will be
 *              passed by the SYS_ADPT_MAX_NBR_OF_PORT_PER_UNIT as the port count always.
 *              For example, for 24 port stacking system, the 2nd unit port 1 needs to be
 *              counted from byte 5.
 *           4. For a Distributed (Loosely Coupling) system, the all port list of every unit
 *              will be passed, unit_id need to be taken to count which byte is the start
 *              byte for this unit.
 *           5. For a Centralized (Tightly Coupling) System, the port_list represents
 *              all units/ports in the system in a linear port list format.
  * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortToVlanUntaggedSet(UI32_T unit_id,
                                          UI32_T vid,
                                          UI8_T  *port_list);


BOOL_T DEV_SWDRV_SetSystemMTU(UI32_T status,UI32_T mtu);

BOOL_T DEV_SWDRV_SetPortMTU(UI32_T unit,UI32_T port,UI32_T MTU);

/* -------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_GetPortMaxFrameSize
 * -------------------------------------------------------------------------
 * PURPOSE : to get max frame size of port
 * INPUT   : unit
 *           port
 * OUTPUT  : untagged_max_frame_sz_p - max frame size for untagged frames
 *           tagged_max_frame_sz_p   - max frame size for tagged frames
 * RETURN  : TRUE / FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_GetPortMaxFrameSize(UI32_T unit, UI32_T port, UI32_T *untagged_max_frame_sz_p, UI32_T *tagged_max_frame_sz_p);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnableIngressFilter
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function enables the ingress filter of the specified port
 * INPUT   : unit_id            -- which unit to enable
 *           port               -- which port to enable
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified (unit, port) is not available, or
 *                                 the ASIC does not support ingress filter.
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnableIngressFilter(UI32_T unit_id, UI32_T port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisableIngressFilter
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function disables the ingress filter of the specified port
 * INPUT   : unit_id            -- which unit to enable
 *           port               -- which port to enable
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified (unit, port) is not available, or
 *                                 the ASIC does not support ingress filter.
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisableIngressFilter(UI32_T unit_id, UI32_T port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_AdmitOnlyVlanTaggedFrames
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function admins a given port to receive/handle tagged frames only.
 *           Only tagged frame will be handled by this port.
 *           Any untagged data frame enters this port will be dropped silently.
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified (unit, port) is not available, or
 *                                 the ASIC does not support "Tagged Frame Only" mode.
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_AdmitOnlyVlanTaggedFrames(UI32_T unit_id, UI32_T port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_AdmitOnlyVlanUntaggedFrames
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function admins a given port to receive/handle untagged frames only.
 *           Only untagged frame will be handled by this port.
 *           Any tagged data frame enters this port will be dropped silently.
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_AdmitOnlyVlanUntaggedFrames(UI32_T unit_id, UI32_T port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_AdmitAllFrames
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function admins a given port to receive/handle both tagged
 *           and untagged frames.
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified (unit, port) is not available, or
 *                                 the ASIC does not support "All Frame" mode.
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_AdmitAllFrames(UI32_T unit_id, UI32_T port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnableTrapUnspecifiedTagFrame

 * -------------------------------------------------------------------------------------------
 * PURPOSE : Enable trapping to CPU if unspecified tag frame incomming.
 * INPUT   : None
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified VLAN is not available
 * NOTE    :
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnableTrapUnspecifiedTagFrame(void);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisableTrapUnspecifiedTagFrame

 * -------------------------------------------------------------------------------------------
 * PURPOSE : Disable trapping to CPU if unspecified tag frame incomming.
 * INPUT   : None
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified VLAN is not available
 * NOTE    :
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisableTrapUnspecifiedTagFrame(void);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_AddCpuToVlan

 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function adds/joins CPU to a specified VLAN.
 *           Any broadcast, unknow multicast, and unknown DA packets on
 *           this VLAN will be trapped/forwarded to the CPU.
 * INPUT   : vid                -- which VLAN that CPU wants to join
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified VLAN is not available
 * NOTE    : This function shall ONLY be used for L2 switch.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_AddCpuToVlan(UI32_T vid);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DeleteCpuFromVlan
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function deletes/leaves CPU from a specified VLAN.
 *           Any broadcast, unknow multicast, and unknown DA packets on
 *           this VLAN will NOT be trapped/forwarded to the CPU.
 * INPUT   : vid                -- which VLAN that CPU wants to leave
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified VLAN is not available
 * NOTE    : This function shall ONLY be used for L2 switch.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DeleteCpuFromVlan(UI32_T vid);




/* Port Mirroring Configuration
 */
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortMirroring
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets/configures the source port and sniffer port
 *           for the a port mirroring session.
 * INPUT   : source_port        -- (Key) which port to be monitored(mirror to sniffer port)
 *           rx_to_sniffer_port -- sniffer port which will moniter any packet rx by source_port
 *           tx_to_sniffer_port -- sniffer port which will moniter aney packet tx by source_port
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified source or sniffer port is not available, or
 *                                 the ASIC can not support port mirroring function
 * NOTE    : 1. ONLY one Mirror session can be coonfigured based on current design.
 *           2. For those ASICs which can support multiple Mirror sessions, ONLY ONE mirror
 *              session shall be used/created. This function will ALWAYS OVERRIDE the last
 *              seting of mirroring seesion.
 *           3. For those ASIC which can not support two sniffer ports, the calling routine
 *              shall assign/give the same port number for both rx_to_sniffer_port and tx_to_sniffer_port.
 *           4. For those ASIC can support two sniffer ports (one for rx packet sniffer, and
 *              the other for tx packet sniffer),
 *              - packet rx by source_port will NOT be mirrored if rx_to_sniffer_port is 0
 *              - packet tx by source_port will NOT be mirrored if tx_to_sniffer_port is 0
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortMirroring(SYS_TYPE_Uport_T source_port,
                                  SYS_TYPE_Uport_T rx_to_sniffer_port,
                                  SYS_TYPE_Uport_T tx_to_sniffer_port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DeletePortMirroring
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function deletes a port mirroring session
 * INPUT   : source_port        -- (key) to identify a unique port mirror session
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified source-port is not available, or
 *                                 the ASIC can not support port mirroring function
 * NOTE    : For those ASICs which DO NOT need "source port" to identify a port mirror session,
 *           the input parameter, source_port will be ignored.
 *
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DeletePortMirroring(SYS_TYPE_Uport_T source_port , SYS_TYPE_Uport_T dest_port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnablePortMirroring
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function enables a port mirroring session
 * INPUT   : source_port        -- (key) to identify a unique port mirror session
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified source-port/port mirror session is not available,
 *                                 or the ASIC can not support port mirroring function
 * NOTE    : For those ASICs which DO NOT need "source port" to identify a port mirror session,
 *           the input parameter, source_port will be ignored.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnablePortMirroring(SYS_TYPE_Uport_T source_port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisablePortMirroring
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function disables a port mirroring session
 * INPUT   : source_port        -- (key) to identify a unique port mirror session
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified source-port/port mirror session is not available,
 *                                 or the ASIC can not support port mirroring function
 * NOTE    : For those ASICs which DO NOT need "source port" to identify a port mirror session,
 *           the input parameter, source_port will be ignored.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisablePortMirroring(SYS_TYPE_Uport_T source_port);

#if (SYS_CPNT_VLAN_MIRROR == TRUE)
/*------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_AddVlanMirror
 *------------------------------------------------------------------------
 * FUNCTION: This function will add the vlan mirror and destination port
 * INPUT   : unit -- which unit to set
 *           port -- which destination port to set
 *           vid  -- which vlan-id add to source mirrored table
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 *------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_AddVlanMirror(UI32_T unit, UI32_T port, UI32_T vid);

/*------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DeleteVlanMirror
 *------------------------------------------------------------------------
 * FUNCTION: This function will delete the vlan mirror and destination port
 * INPUT   : unit -- which unit to set
 *           port -- which destination port to set
 *           vid  -- which vlan-id add to source mirrored table
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : A destination port shall be removed when source vlan mirror has empty
 *------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_DeleteVlanMirror(UI32_T unit, UI32_T port, UI32_T vid);
#endif /* end of #if (SYS_CPNT_VLAN_MIRROR == TRUE) */

#if (SYS_CPNT_MAC_BASED_MIRROR == TRUE)
/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetDestPortForMacMirror
 * -------------------------------------------------------------------------
 * PURPOSE : This function sets destination port for MAC based MIRROR
 * INPUT   : unit -- in which unit
 *           port -- which port to monitor
 *           mode -- TRUE: set, FALSE: remove
 * OUTPUT  : none
 * RETURN  : TRUE               -- Success
 *           FALSE              -- Failed
 * NOTE    : none
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetDestPortForMacMirror(UI32_T unit, UI32_T port, BOOL_T mode);
#endif

#if (SYS_CPNT_ACL_MIRROR == TRUE)
/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetDestPortForAclMirror
 * -------------------------------------------------------------------------
 * PURPOSE : This function sets destination port for ACL based MIRROR
 * INPUT   : unit -- in which unit
 *           port -- which port to monitor
 *           mode -- TRUE: set, FALSE: remove
 * OUTPUT  : none
 * RETURN  : TRUE               -- Success
 *           FALSE              -- Failed
 * NOTE    : none
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetDestPortForAclMirror(UI32_T unit, UI32_T port, BOOL_T mode);
#endif

/* Trunk Port (Link Aggregation) Configuration
 */
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_CreateTrunk
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function creates a trunk (Link Aggregation) port
 * INPUT   : trunk_id           -- a unique trunk id for the new turnk port to be created
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified trunk id is not available, or the ASIC can not
 *                                 support trunk port.
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_CreateTrunk(UI32_T trunk_id);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_CreateTrunkwithMode
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function creates a trunk (Link Aggregation) port
 * INPUT   : trunk_id           -- a unique trunk id for the new turnk port to be created
 * INPUT   : mode               -- trunk load balance mode
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified trunk id is not available, or the ASIC can not
 *                                 support trunk port.
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_CreateTrunkwithMode(UI32_T trunk_id, UI8_T mode);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DestroyTrunk
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function destroies a trunk port
 * INPUT   : trunk_id           -- the trunk to be destroied
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified trunk id is not available, or the ASIC can not
 *                                 support trunk port.
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DestroyTrunk(UI32_T trunk_id);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetTrunkPortMembers
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets/updates the port members to the specified trunk port.
 * INPUT   : trunk_id           -- the trunk port to be updated
 *           port_member_count  -- total number of port members of the specified trunk port
 *           port_member_list   -- the port members list of specified trunk port
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the specified trunk id is not available, or the ASIC can not
 *                                 support trunk port.
 * NOTE    : 1. The most of ASIC needs to assign/use one of port member of trunk port
 *              to forward the Boardcast or Unknown DA packet.
 *           2. The most ASIC assigns/uses the first port member (lowest Port ID)for
 *              Boardcast or Unknown DA packet forwarding.
 *           3. This function will also configure the port member of a given trunk port
 *              for Boardcast or Unknown DA packet forwarding for those ASICs which need
 *              S/W to do the configuration.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetTrunkPortMembers(UI32_T           trunk_id,
                                     UI32_T           port_member_count,
                                     SYS_TYPE_Uport_T *port_member_list);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetTrunkLoadBalanceMode
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets/configures the load/traffic balance mode for all trunk ports.
 * INPUT   : load_balance_mode  -- the load/traffic balance mode
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the ASIC can not support the specified load/traffic balance
 *                                 mode, or the ASIC does not allow S/W to configure the load/traffic
 *                                 balance mode.
 * NOTE    : 1. The most of ASICs supports the load/traffic balance mode on the egress port.
 *              The load/traffic balance of a trunk port is dertermined based on the specified
 *              mode during the packet forwarding.
 *           2. For those ASICs DOES NOT support the specified load/traffic balance, or
 *              DOES NOT allow S/W to configure the the load/traffic balance mode over the
 *              trunk port, this function shall be ignored or return FALSE.
 *           3. The type of load/traffic balance mode for the trunk port is defined by
 *              the enumeration type, DEV_SWDRV_Trunk_Mode_E.
 *                      DEV_SWDRV_TRUNK_MAC_SA,
 *                      DEV_SWDRV_TRUNK_MAC_DA,
 *                      DEV_SWDRV_TRUNK_MAC_SA_DA,
 *                      DEV_SWDRV_TRUNK_IP_SA,
 *                      DEV_SWDRV_TRUNK_IP_DA,
 *                      DEV_SWDRV_TRUNK_IP_SA_DA
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetTrunkLoadBalanceMode(UI32_T load_balance_mode);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_AddMulticastAddrToTrunkMember
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function adds/assigns a mulitcast address to the specified port member of
 *           a given trunk port. The multicast traffic will be forward by the spcified port
 *           member of the given trunk.
 *           This function provides S/W load/traffic balance configuration for the multicast
 *           traffic over the trunk port.
 * INPUT   : mac                -- the multicast address
 *           vid                -- the specified VLAN
 *           trunk_id           -- the specified trunk
 *           trunk_member       -- the specified trunk member (unit, port) to forward the specific
 *                                multicast traffic to add
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the ASIC does not allow S/W to configure the load/traffic
 *                                 balance mode for multicast traffic over the trunk port
 * NOTE    : 1. This function shall ONLY be invoked for those ASICs which need S/W configuration
 *              to support multicast load/traffic balance over trunk port.
 *           2. For those ASICs support H/W based multicast load/traffic balance over trunk port,
 *              this function shall be ignored.
 *           2. For those ASICs CAN NOT support multicast load/traffic balance over trunk port,
 *              this function shall be ignored. For those ASICs CAN only support "fixed port" for
 *              multicast traffic, S/W can not do workaround for it.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_AddMulticastAddrToTrunkMember(UI8_T            *mac,
                                               UI32_T           vid,
                                               UI32_T           trunk_id,
                                               SYS_TYPE_Uport_T trunk_member);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DeleteMulticastAddrFromTrunkMember
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function deletes a mulitcast address from the specified port member of
 *           a given trunk port.
 *           This function provides S/W load/traffic balance configuration for the multicast
 *           traffic over the trunk port.
 * INPUT   : mac                -- the multicast address to be deleted from the specified trunk member
 *           vid                -- the specified VLAN
 *           trunk_id           -- the specified trunk
 *           trunk_member       -- the specified trunk member (unit, port)
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the ASIC does not allow S/W to configure the load/traffic
 *                                 balance mode for multicast traffic over the trunk port
 * NOTE    : 1. This function shall ONLY be invoked for those ASICs which need S/W configuration
 *              to support multicast load/traffic balance over trunk port.
 *           2. For those ASICs support H/W based multicast load/traffic balance over trunk port,
 *              this function shall be ignored.
 *           2. For those ASICs CAN NOT support multicast load/traffic balance over trunk port,
 *              this function shall be ignored. For those ASICs CAN only support "fixed port" for
 *              multicast traffic, S/W can not do workaround for it.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DeleteMulticastAddrTFromTrunkMember(UI8_T            *mac,
                                                     UI32_T           vid,
                                                     UI32_T           trunk_id,
                                                     SYS_TYPE_Uport_T trunk_member);



/* IGMP Snooping Configuration
 */
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnableIgmpTrap
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function enables the IGMP Snooping functiion.
 *           All the IGMP Control packets to be trapped/forwarded to CPU.
 * INPUT   : None
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the ASIC does not support IGMP Snooping function
 * NOTE    : When IGMP Snooping function is enabled, all the IGMP Control packets shall
 *           ONLY be trapped/forwarded to CPU.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnableIgmpTrap(void);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisableIgmpTrap
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function disables the IGMP Snooping function.
 *           All the IGMP control packets will NOT be trapped/forwarded to CPU.
 * INPUT   : igmp_mode          -- forward or discard igmp control packet.
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the ASIC does not support IGMP Snooping function
 * NOTE    : When IGMP Snooping function is disabled, all the IGMP Control packets shall
 *           be FLOODED out to all port memmers on the same VLAN, and SHALL NOT be
 *           trapped/forwarded to CPU.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisableIgmpTrap(void);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_TrapIGMPToCPU
 * -------------------------------------------------------------------------
 * FUNCTION: This function will trap/mirror IGMP packet to CPU
 * INPUT   : to_cpu -- TRUE for trap to cpu
 *           drop   -- TRUE for drop
 * OUTPUT  : None
 * RETURN  : True: Successfully, False: If not available
 * NOTE    : to_cpu  drop
 *           TRUE    TRUE  : trap
 *           TRUE    FALSE : copy
 *           FALSE   TRUE  : drop, currently, not supported
 *           FALSE   FALSE : forward
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_TrapIGMPToCPU(BOOL_T to_cpu, BOOL_T drop);


/* Broadcast Storm Control/Rate Limiting Configuration
 * Multicast Storm Control/Rate Limiting Configuration
 */
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetBroadcastStormControlThreshold
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets/configures the threshold (rate limiting) value of
 *           broadcast storm traffic of a given port
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 *           threshold          -- the threshold (rate limiting) value
 *           mode               -- the type of threshold (rate limiting) mode
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the ASIC does not support the specified threshold (rate limiting)
 *                                 value/mode, or the ASIC does not support broadcast storm control
 *                                 capability.
 * NOTE    : 1. The type of threshold (rate limiting) mode is defined as following:
 *                  DEV_SWDRV_STORM_CTRL_MODE_PACKET_RATE
 *                  DEV_SWDRV_STORM_CTRL_MODE_BYTE_RATE
 *                  DEV_SWDRV_STORM_CTRL_MODE_PERCENTAGE
 *           2. The range of threshold (rate limiting) value shall be ASIC dependent.
 *           3. For those ASICs which CAN NOT support different threshold (rate limiting) mode,
 *              the parameter "mode" shall be ignored.
 *           4. For those ASICs which use the same threshold (rate limiting) value/mode
 *              for both Broadcast/Multicast traffic storm control, this function shall be invoked
 *              to configure the threshold (rate limiting) value/mode for both storm control function.
 *           5. For those ASICs which use the separate set of threshold (rate limiting) value/mode
 *              for multicast traffic storm control, the DEV_SWDRV_SetMulticastStormControlThreshold()
 *              shall be invoked separately.
 *           6. For those ASICs which CAN ONLY support global based broadcast storm control,
 *              the input parameter (unit_id, port) WILL BE ignored.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetBroadcastStormControlThreshold(UI32_T unit_id,
                                                   UI32_T port,
                                                   UI32_T threshold,
                                                   UI32_T mode);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetMulticastStormControlThreshold
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets/configures the threshold (rate limiting) value of
 *           multicast storm traffic of a given port
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 *           threshold          -- the threshold (rate limiting) value
 *           mode               -- the type of threshold (rate limiting) mode
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the ASIC does not support the specified threshold (rate limiting)
 *                                 value/mode, or the ASIC does not support multicast storm control
 *                                 capability.
 * NOTE    : 1. The type of threshold (rate limiting) mode is defined as following:
 *                  DEV_SWDRV_STORM_CTRL_MODE_PACKET_RATE
 *                  DEV_SWDRV_STORM_CTRL_MODE_BYTE_RATE
 *                  DEV_SWDRV_STORM_CTRL_MODE_PERCENTAGE
 *           2. The range of threshold (rate limiting) value shall be ASIC dependent.
 *           3. For those ASICs which CAN NOT support different threshold (rate limiting) mode,
 *              the parameter "mode" shall be ignored.
 *           4. This function SHALL ONLY be invoked for those ASICs which use the separate
 *              set of threshold (rate limiting) value/mode for multicast traffic storm control.
 *              shall be invoked separately.
 *           5. This function SHALL BE IGNORED for those ASICs which use the same threshold
 *              (rate limiting) value/mode for both Broadcast/Multicast traffic storm control.
 *           6. For those ASICs which CAN ONLY support global based multicast storm control,
 *              the input parameter (unit_id, port) WILL BE ignored.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetMulticastStormControlThreshold(UI32_T unit_id,
                                                   UI32_T port,
                                                   UI32_T threshold,
                                                   UI32_T mode);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnableBroadcastStormControl
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function enables the broadcast storm control function of
 *           given a port.
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the ASIC does not support the broadcast storm control function.
 * NOTE    : 1. For those ASICs which use the "global enable" command for for both
 *              Broadcast/Multicast traffic storm control, this function shall be invoked
 *              to enable both storm control function.
 *           2. For those ASICs which use the separate "enable" command for multicast
 *              traffic storm control, the DEV_SWDRV_EnableMulticastStormControl()
 *              shall be invoked separately.
 *           3. For those ASICs which CAN ONLY support global based broadcast storm control,
 *              the input parameter (unit_id, port) WILL BE ignored.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnableBroadcastStormControl(UI32_T unit_id, UI32_T port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisableBroadcastStormControl
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function disables the broadcast storm control function of
 *           a given port
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the ASIC does not support the broadcast storm control function.
 * NOTE    : 1. For those ASICs which use the "global disable" command for for both
 *              Broadcast/Multicast traffic storm control, this function shall be invoked
 *              to disable both storm control function.
 *           2. For those ASICs which use the separate "disable" command for multicast
 *              traffic storm control, the DEV_SWDRV_DisableMulticastStormControl()
 *              shall be invoked separately.
 *           3. For those ASICs which CAN ONLY support global based broadcast storm control,
 *              the input parameter (unit_id, port) WILL BE ignored.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisableBroadcastStormControl(UI32_T unit_id, UI32_T port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnableMulticastStormControl
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function enables the multicast storm control function of
 *           given a port.
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the ASIC does not support the multicast storm control function.
 * NOTE    : 1. This function SHALL ONLY be iinvoked for those ASICs which use the separate
 *              "enable" command for multicast traffic storm control.
 *           2. For those ASICs which use the "global enable" command for for both
 *              Broadcast/Multicast traffic storm control, this function SHALL BE ignored.
 *           3. For those ASICs which CAN ONLY support global based multicast storm control,
 *              the input parameter (unit_id, port) WILL BE ignored.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnableMulticastStormControl(UI32_T unit_id, UI32_T port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisableMulticastStormControl
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function disables the multicast storm control function of
 *           given a port.
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the ASIC does not support the multicast storm control function.
 * NOTE    : 1. This function SHALL ONLY be iinvoked for those ASICs which use the separate
 *              "disable" command for multicast traffic storm control.
 *           2. For those ASICs which use the "global disable" command for for both
 *              Broadcast/Multicast traffic storm control, this function SHALL BE ignored.
 *           3. For those ASICs which CAN ONLY support global based multicast storm control,
 *              the input parameter (unit_id, port) WILL BE ignored.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisableMulticastStormControl(UI32_T unit_id, UI32_T port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetUnknownUnicastStormControlThreshold
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets/configures the threshold (rate limiting) value of
 *           unknown unicast storm traffic of a given port
 * INPUT   : unit               -- which unit to set
 *           port               -- which port to set
 *           threshold          -- the threshold (rate limiting) value
 *           mode               -- the type of threshold (rate limiting) mode
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the ASIC does not support the specified threshold (rate limiting)
 *                                 value/mode, or the ASIC does not support unknown unicast storm control
 *                                 capability.
 * NOTE    : 1. The type of threshold (rate limiting) mode is defined as following:
 *                  DEV_SWDRV_STORM_CTRL_MODE_PACKET_RATE
 *                  DEV_SWDRV_STORM_CTRL_MODE_BYTE_RATE
 *                  DEV_SWDRV_STORM_CTRL_MODE_PERCENTAGE
 *           2. The range of threshold (rate limiting) value shall be ASIC dependent.
 *           3. For those ASICs which CAN NOT support different threshold (rate limiting) mode,
 *              the parameter "mode" shall be ignored.
 *           4. This function SHALL ONLY be invoked for those ASICs which use the separate
 *              set of threshold (rate limiting) value/mode for unknown unicast traffic storm control.
 *              shall be invoked separately.
 *           5. This function SHALL BE IGNORED for those ASICs which use the same threshold
 *              (rate limiting) value/mode for both Broadcast/Multicast/UnknownUnicast traffic storm control.
 *           6. For those ASICs which CAN ONLY support global based unknown unicast storm control,
 *              the input parameter (unit_id, port) WILL BE ignored.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetUnknownUnicastStormControlThreshold(UI32_T unit_id, UI32_T port, UI32_T threshold, UI32_T mode);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnableBroadcastStormControl
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function enables the broadcast storm control function of
 *           given a port.
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the ASIC does not support the broadcast storm control function.
 * NOTE    : 1. For those ASICs which use the "global enable" command for for both
 *              Broadcast/Multicast traffic storm control, this function shall be invoked
 *              to enable both storm control function.
 *           2. For those ASICs which use the separate "enable" command for multicast
 *              traffic storm control, the DEV_SWDRV_EnableMulticastStormControl()
 *              shall be invoked separately.
 *           3. For those ASICs which CAN ONLY support global based broadcast storm control,
 *              the input parameter (unit_id, port) WILL BE ignored.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnableBroadcastStormControl(UI32_T unit_id, UI32_T port);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisableBroadcastStormControl
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function disables the broadcast storm control function of
 *           a given port
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If the ASIC does not support the broadcast storm control function.
 * NOTE    : 1. For those ASICs which use the "global disable" command for for both
 *              Broadcast/Multicast traffic storm control, this function shall be invoked
 *              to disable both storm control function.
 *           2. For those ASICs which use the separate "disable" command for multicast
 *              traffic storm control, the DEV_SWDRV_DisableMulticastStormControl()
 *              shall be invoked separately.
 *           3. For those ASICs which CAN ONLY support global based broadcast storm control,
 *              the input parameter (unit_id, port) WILL BE ignored.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisableBroadcastStormControl(UI32_T unit_id, UI32_T port);



/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetForwardingStackingPortBitMap
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function return forwarding stacking port
 * INPUT   : None
 * OUTPUT  : UI32_T stacking_port_bmap;
 * RETURN  : None
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
void DEV_SWDRV_GetForwardingStackingPortBitMap(UI32_T *stacking_port_bmap) ;

/* Class of Service - CoS Configuration
 */
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortUserDefaultPriority
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets/configures the Port User Default Priority of
 *           a given port.
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 *           priority           -- the User Default Priority of the given port
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If ASIC does not support 802.1p MIB requirements.
 * NOTE    : 1. This function shall comply with the 802.1p MIB requirements.
 *           2. For those ASICs which CAN ONLY support global based Port User Default Priority
 *              setting/configuration, the input parameter (unit, port) SHALL BE ignored.
 *           3. For some ASICs which use the traffic class (queue#) to represent the
 *              1P priority, the low level device driver shall do the translation internally.
 *              Whenever the priority mapping change (via the following API), the low level
 *              device driver also needs to auto change/update the Port User Default Priority.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortUserDefaultPriority(UI32_T unit_id,
                                            UI32_T port,
                                            UI32_T priority);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPriorityMapping
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets/configures the 802.1p Priority to Output Queue (CoS) mapping
 *           of a given port.
 * INPUT   : unit_id                -- which unit to set
 *           port                   -- which port to set
 *           dot1p_to_cos_mapping   -- 802.1p priority to output queue (CoS) mapping for a given port
 * OUTPUT  : None
 * RETURN  : TRUE                   -- Success
 *           FALSE                  -- If ASIC does not support 802.1p MIB requirements.
 * NOTE    : 1. This function shall comply with the 802.1p MIB requirements.
 *           2. For those ASICs which CAN ONLY support global based Port User Default Priority
 *              setting/configuration, the input parameter (unit, port) SHALL BE ignored.
 *           3. The input parameter "dot1p_to_cos_mapping[]" is an 8-element array.
 *              The index of dot1p_to_cos_mapping[] array is range from 0 ~ 7 as defined in 802.1p MIB.
 *              The content of the "mapping[]" is the mapped/associated Traffic Class (output queue#).
 *           4. Some ASICS may need to change the total number of Traffic Classes (output queue#)
 *              to support a specific function, such as Jumbo Frame. In some ODM cases, customer may
 *              require to change the total number of Traffic Classes (output queue#) for some applications.
 *              The DEV_SWDRV_SetNumberofTrafficClassByPort() is defined for this purpose.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPriorityMapping(UI32_T unit_id,
                                    UI32_T port,
                                    UI8_T  *dot1p_to_cos_mapping);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPriorityMappingPerSystem
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets/configures the 802.1p Priority to Output Queue (CoS) mapping
 *           of a driver unit.
 * INPUT   : dot1p_to_cos_mapping   -- 802.1p priority to output queue (CoS) mapping for a given port
 * OUTPUT  : None
 * RETURN  : TRUE                   -- Success
 *           FALSE                  -- If ASIC does not support 802.1p MIB requirements.
 * NOTE    : 1. This function shall comply with the 802.1p MIB requirements.
 *           2. For those ASICs which CAN ONLY support global based Port User Default Priority
 *              setting/configuration, the input parameter (unit, port) SHALL BE ignored.
 *           3. The input parameter "dot1p_to_cos_mapping[]" is an 8-element array.
 *              The index of dot1p_to_cos_mapping[] array is range from 0 ~ 7 as defined in 802.1p MIB.
 *              The content of the "mapping[]" is the mapped/associated Traffic Class (output queue#).
 *           4. Some ASICS may need to change the total number of Traffic Classes (output queue#)
 *              to support a specific function, such as Jumbo Frame. In some ODM cases, customer may
 *              require to change the total number of Traffic Classes (output queue#) for some applications.
 *              The DEV_SWDRV_SetNumberofTrafficClassByPort() is defined for this purpose.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPriorityMappingPerSystem(UI8_T *dot1p_to_cos_mapping);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetNumberOfTrafficClassByPort
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function enables/configures the total number of traffic classes
 *           (output queues) of a given port.
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 *           number_of_queue    - total number number of traffic classes (output queues) enabled
 *                                      DEV_SWDRV_TRAFFIC_CLASS_NUM_1
 *                                      DEV_SWDRV_TRAFFIC_CLASS_NUM_2
 *                                      DEV_SWDRV_TRAFFIC_CLASS_NUM_4
 *                                      DEV_SWDRV_TRAFFIC_CLASS_NUM_8
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- If ASIC does not have this flexibility to enable/configure the
 *                                 total number of traffic classes (output queues) to be used.
 * NOTE    : 1. For those ASICs which CAN NOT support this cpability, this function shall be ignored.
 *           2. For those ASICs which CAN ONLY support global based Port traffic classes (output queues)
 *              enable/configuration, the input parameter (unit, port) SHALL BE ignored.
 *           3. The total number of traffic classes (output queues) can be support will be ASIC dependent.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetNumberOfTrafficClassByPort(UI32_T unit_id,
                                               UI32_T port,
                                               UI32_T number_of_queue);


/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetStackingPortPriorityMapping
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets/configures the 802.1p Priority to Output Queue (CoS) mapping
 *           to the specified stacking port
 * INPUT   : unit_id                -- which unit to set
 *           port                   -- which stacking port to set
 *           dot1p_to_cos_mapping   -- 802.1p priority to output queue (CoS) mapping for the
 *                                     stacking port
 * OUTPUT  : None
 * RETURN  : TRUE                   -- Success
 *           FALSE                  -- If ASIC does not support 802.1p MIB requirements.
 * NOTE    : 1. This function shall comply with the 802.1p MIB requirements.
 *           2. For those ASICs which CAN ONLY support global based Port User Default Priority
 *              setting/configuration, the input parameter (unit, port) SHALL BE ignored.
 *           3. The input parameter "dot1p_to_cos_mapping[]" is an 8-element array.
 *              The index of dot1p_to_cos_mapping[] array is range from 0 ~ 7 as defined in 802.1p MIB.
 *              The content of the "mapping[]" is the mapped/associated Traffic Class (output queue#).
 *           4. Some ASICS may need to change the total number of Traffic Classes (output queue#)
 *              to support a specific function, such as Jumbo Frame. In some ODM cases, customer may
 *              require to change the total number of Traffic Classes (output queue#) for some applications.
 *              The DEV_SWDRV_SetNumberofTrafficClassByPort() is defined for this purpose.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetStackingPortPriorityMapping(UI32_T unit_id,
                                                UI32_T port,
                                                UI8_T  *dot1p_to_cos_mapping);


/* Jumbo frame setting
 */
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnableJumboFrame
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function enables jumbo frame for whole system
 * INPUT   : None
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- Failure
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnableJumboFrame(void);



/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisableJumboFrame
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function disables jumbo frame for whole system
 * INPUT   : None
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- Failure
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisableJumboFrame(void);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortType
 * -------------------------------------------------------------------------
 * FUNCTION: This function will get port type info of a specified port
 * INPUT   : unit_id    -- in which unit
 *           port       -- which port to set
 *           port_type  -- port type
 * OUTPUT  : None
 * RETURN  : True: Successfully, False: If not available
 * NOTE    : Please refere the definition in MIB header file "leaf_es3626a.h":
 *             #define VAL_portType_other	                    1L
 *             #define VAL_portType_hundredBaseTX	            2L
 *             #define VAL_portType_hundredBaseFX	            3L
 *             #define VAL_portType_thousandBaseSX	            4L
 *             #define VAL_portType_thousandBaseLX	            5L
 *             #define VAL_portType_thousandBaseT	            6L
 *             #define VAL_portType_thousandBaseGBIC	        7L
 *             #define VAL_portType_thousandBaseSfp	            8L
 *             #define VAL_portType_hundredBaseFxScSingleMode	9L
 *             #define VAL_portType_hundredBaseFxScMultiMode	10L
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetPortType(UI32_T unit_id,
                             UI32_T port,
                             UI32_T *port_type);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortOperSpeedDuplex
 * -------------------------------------------------------------------------
 * FUNCTION: This function will get Port Operation Speed Duplex
 * INPUT   : unit_id    -- in which unit
 *           port       -- which port to set
 * OUTPUT  : speed duplex
 * RETURN  : True: Successfully, False: If not available
 * NOTE    :
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetPortOperSpeedDuplex(UI32_T unit_id, UI32_T port, UI32_T *speed_duplex);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortLinkStatus
 * -------------------------------------------------------------------------
 * FUNCTION: This function will get Port link status
 * INPUT   : unit_id    -- in which unit
 *           port       -- which port to set
 * OUTPUT  : link_status
 * RETURN  : True: Successfully, False: If not available
 * NOTE    :
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetPortLinkStatus(UI32_T unit_id, UI32_T port, UI32_T *link_status);

BOOL_T DEV_SWDRV_GetAllPortLinkStatus(UI32_T unit_id, UI32_T start_port,UI32_T end_port, DEV_SWDRV_PortTableStats_T *PortStats);
/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortFlowCtrl
 * -------------------------------------------------------------------------
 * FUNCTION: This function will get Port Flow control
 * INPUT   : unit_id    -- in which unit
 *           port       -- which port to set
 * OUTPUT  : flow_ctrl
 * RETURN  : True: Successfully, False: If not available
 * NOTE    :
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetPortFlowCtrl(UI32_T unit_id, UI32_T port, UI32_T *flow_ctrl);

/*--------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_Physical2LogicalPort
 *---------------------------------------------------------------------------
 * PURPOSE:  mapping physical port/phy to user port
 * INPUT:    module_id, device_id, phy_port
 * OUTPUT:   unit, port
 * RETURN:   TRUE/FALSE
 * NOTE:
 *---------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_Physical2LogicalPort(UI32_T module_id, UI32_T device_id, UI32_T phy_port,
    UI32_T *unit, UI32_T *port);

/*--------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetUnitAndDeviceIDFromModuleID
 *---------------------------------------------------------------------------
 * PURPOSE:  Get the mapping physical unit/device_id to the module_id.
 * INPUT:    module_id
 * OUTPUT:   unit, device_id
 * RETURN:   TRUE/FALSE
 * NOTE:
 *---------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_GetUnitAndDeviceIDFromModuleID(UI32_T module_id, UI32_T *unit, UI32_T *device_id);

/*--------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_Logical2PhyDeviceID
 *---------------------------------------------------------------------------
 * PURPOSE:  mapping logical user port to phy id
 * INPUT:    unit_id, port
 * OUTPUT:   module_id, device_id, phy_id
 * RETURN:   TRUE/FALSE
 * NOTE:
 *---------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_Logical2PhyDeviceID(UI32_T unit_id, UI32_T port, UI32_T *module_id,
    UI32_T *device_id, UI32_T *phy_id);

/*--------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_Logical2PhyDevicePortID
 *---------------------------------------------------------------------------
 * PURPOSE:  mapping logical user port to phy port
 * INPUT:    unit_id, port,
 * OUTPUT:   module_id, device_id, phy_port
 * RETURN:   TRUE/FALSE
 * NOTE:
 *---------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_Logical2PhyDevicePortID(UI32_T unit_id, UI32_T port, UI32_T *module_id,
    UI32_T *device_id, UI32_T *phy_port);

/*--------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetUnitChipsetNumber
 *---------------------------------------------------------------------------
 * PURPOSE:  get the unit chip number
 * INPUT:    None
 * OUTPUT:   None
 * RETURN:   chip number
 * NOTE:
 *---------------------------------------------------------------------------
 */
UI32_T DEV_SWDRV_GetLocalUnitChipsetNumber(void);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_LinkScan_Update
 * -------------------------------------------------------------------------
 * FUNCTION: This function will update broadcom chip link status
 * INPUT   : None.
 * OUTPUT  : None.
 * RETURN  : None.
 * NOTE    :
 * -------------------------------------------------------------------------*/
void DEV_SWDRV_LinkScan_Update(void);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnableIPMC
 * -------------------------------------------------------------------------
 * FUNCTION: This function will enable IPMC
 * INPUT   : unit_id    -- in which unit
 * OUTPUT  : None.
 * RETURN  : TRUE / FALSE.
 * NOTE    :
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_EnableIPMC(I32_T unit_id);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisableIPMC
 * -------------------------------------------------------------------------
 * FUNCTION: This function will disable IPMC
 * INPUT   : unit_id    -- in which unit
 * OUTPUT  : None.
 * RETURN  : TRUE / FALSE.
 * NOTE    :
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_DisableIPMC(I32_T unit_id);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_IPMC_EnableSourcePortCheck
 * -------------------------------------------------------------------------
 * FUNCTION: This function will enable IPMC source port check
 * INPUT   : unit_id    -- in which unit
 * OUTPUT  : None.
 * RETURN  : TRUE / FALSE.
 * NOTE    :
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_IPMC_EnableSourcePortCheck(I32_T unit_id);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_IPMC_DisableSourcePortCheck
 * -------------------------------------------------------------------------
 * FUNCTION: This function will disable IPMC source port check
 * INPUT   : unit_id    -- in which unit
 * OUTPUT  : None.
 * RETURN  : TRUE / FALSE.
 * NOTE    :
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_IPMC_DisableSourcePortCheck(I32_T unit_id);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_IPMC_EnableSourceIPSearch
 * -------------------------------------------------------------------------
 * FUNCTION: This function will enable IPMC source ip search
 * INPUT   : unit_id    -- in which unit
 * OUTPUT  : None.
 * RETURN  : TRUE / FALSE.
 * NOTE    :
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_IPMC_EnableSourceIPSearch(I32_T unit_id);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_IPMC_DisableSourceIPSearch
 * -------------------------------------------------------------------------
 * FUNCTION: This function will disable IPMC source ip search
 * INPUT   : unit_id    -- in which unit
 * OUTPUT  : None.
 * RETURN  : TRUE / FALSE.
 * NOTE    :
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_IPMC_DisableSourceIPSearch(I32_T unit_id);


/*-------------------------------------------------------------------------
 *                      Protocol Base VLAN API
 *------------------------------------------------------------------------*/

#define DEV_SWDRV_MAX_NBR_PRTABLE_ENTRY             SYS_ADPT_1V_MAX_NBR_OF_PROTOCOL_GROUP
#define DEV_SWDRV_FRAMETYPE_ETHER_II                1
#define DEV_SWDRV_FRAMETYPE_802_3_LLC_SNAP          2
#define DEV_SWDRV_FRAMETYPE_802_3_LLC_NONSNAP       4
#define DEV_SWDRV_MAX_1V_PROTOCOL_VALUE_LENGTH      SYS_ADPT_1V_MAX_PROTOCOL_VALUE_BUFFER_LENGTH

typedef struct
{
    UI8_T   frame_type;
    UI32_T  ether_type;
    UI32_T  vid;
    BOOL_T  isvalid;

} DEV_SWDRV_PRVLAN_ENTRY_T;

typedef struct
{
    DEV_SWDRV_PRVLAN_ENTRY_T  entry[SYS_ADPT_1V_MAX_NBR_OF_PROTOCOL_GROUP];
    UI8_T           count;
} DEV_SWDRV_PRVLAN_PER_PORT_T;

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_Create_InterCSC_Relation
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function initializes all function pointer registration operations.
 * INPUT   : None
 * OUTPUT  : None
 * RETURN  : None
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
void DEV_SWDRV_Create_InterCSC_Relation(void) ;

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_AddDot1vProtocolPortEntry
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion returns TRUE if the specified protocol port
 *              entry can be successfully set. Otherwise, FALSE is returned.
 * INPUT    :   unit            --  unit number
 *              port            --  user port number
 *                              --  the range of the value is [1..maxnum_of_lport] of UI32_T
 *              group_index     --  group index
 *                              --  the range of the value is [1..maxnum_of_group] of UI32_T,
 *              vlan_id         --  vlan identifier
 *                              --  the range of the value is [1..4094] of UI32_T
 *              nbr_of_type_protocol
 *                              --  number of the type-protocol entry indicated
 *                                  by the key {lport,group_index}
 *              frame_type      --  frame type
 *                              --  value of the array with the combination key {lport,group_index}
 *                              --  the range of the value stored in the array is [1..5] of UI32_T,
 *                                  following the definition of MIB value:
 *                                  VAL_dot1vProtocolTemplateFrameType_ethernet     (1),
 *                                  VAL_dot1vProtocolTemplateFrameType_rfc1042      (2),
 *                                  VAL_dot1vProtocolTemplateFrameType_snap8021H    (3),
 *                                  VAL_dot1vProtocolTemplateFrameType_snapOther    (4),
 *                                  VAL_dot1vProtocolTemplateFrameType_llcOther     (5)
 *              protocol_value  --  buffer of the array containing the protocol value
 *                              --  buffer of the array with the combination key {lport,group_index}
 *                              --  size of the buffer is:
 *                                  2 bytes, for frame_type = {1,2,3,5}, or
 *                                  5 bytes, for frame_type = {4}
 * OUTPUT   :   None
 * RETURN   :   TRUE/FALSE
 * NOTES    :   The following constant used in this function is defined in sys_adpt.h
 *              #define SYS_ADPT_1V_MAX_NBR_OF_FRAME_TYPE        3
 *                  -- The number of frame supported in 802.1v is 5.
 *                  -- This constant has to take the chip limitation into consideration.
 *              #define SYS_ADPT_1V_MAX_NBR_OF_PROTOCOL_GROUP    7
 *                  -- This constant has to take the chip limitation into consideration.
 * ------------------------------------------------------------------------
 */
BOOL_T  DEV_SWDRV_AddDot1vProtocolPortEntry(   UI32_T  unit_id,
                                               UI32_T  port,
                                               UI32_T  group_index,
                                               UI32_T  vlan_id,
                                               UI32_T  nbr_of_type_protocol,
                                               UI8_T   *frame_type,
                                               #if (SYS_CPNT_PROTOCOL_VLAN_PORT_SUPPORT_PRIORITY == TRUE)
                                               UI8_T   priority,
                                               #endif
                                               UI8_T   (*protocol_value)[DEV_SWDRV_MAX_1V_PROTOCOL_VALUE_LENGTH]
                                            );

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_DelDot1vProtocolPortEntry
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion returns TRUE if the specified protocol port
 *              entry can be successfully set. Otherwise, FALSE is returned.
 * INPUT    :   unit            --  unit number
 *              port            --  user port number
 *                              --  the range of the value is [1..maxnum_of_lport] of UI32_T
 *              group_index     --  group index
 *                              --  the range of the value is [1..maxnum_of_group] of UI32_T,
 *              vlan_id         --  vlan identifier
 *                              --  the range of the value is [1..4094] of UI32_T
 *              nbr_of_type_protocol
 *                              --  number of the type-protocol entry indicated
 *                                  by the key {lport,group_index}
 *              frame_type      --  frame type
 *                              --  value of the array with the combination key {lport,group_index}
 *                              --  the range of the value stored in the array is [1..5] of UI32_T,
 *                                  following the definition of MIB value:
 *                                  VAL_dot1vProtocolTemplateFrameType_ethernet     (1),
 *                                  VAL_dot1vProtocolTemplateFrameType_rfc1042      (2),
 *                                  VAL_dot1vProtocolTemplateFrameType_snap8021H    (3),
 *                                  VAL_dot1vProtocolTemplateFrameType_snapOther    (4),
 *                                  VAL_dot1vProtocolTemplateFrameType_llcOther     (5)
 *              protocol_value  --  buffer of the array containing the protocol value
 *                              --  buffer of the array with the combination key {lport,group_index}
 *                              --  size of the buffer is:
 *                                  2 bytes, for frame_type = {1,2,3,5}, or
 *                                  5 bytes, for frame_type = {4}
 * OUTPUT   :   None
 * RETURN   :   TRUE/FALSE
 * NOTES    :   The following constant used in this function is defined in sys_adpt.h
 *              #define SYS_ADPT_1V_MAX_NBR_OF_FRAME_TYPE        3
 *                  -- The number of frame supported in 802.1v is 5.
 *                  -- This constant has to take the chip limitation into consideration.
 *              #define SYS_ADPT_1V_MAX_NBR_OF_PROTOCOL_GROUP    7
 *                  -- This constant has to take the chip limitation into consideration.
 * ------------------------------------------------------------------------
 */
BOOL_T  DEV_SWDRV_DelDot1vProtocolPortEntry(   UI32_T  unit_id,
                                               UI32_T  port,
                                               UI32_T  group_index,
                                               UI32_T  vlan_id,
                                               UI32_T  nbr_of_type_protocol,
                                               UI8_T   *frame_type,
                                               UI8_T   (*protocol_value)[DEV_SWDRV_MAX_1V_PROTOCOL_VALUE_LENGTH]
                                           );

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_SetDot1vProtocolGroupEntry
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion returns TRUE if the specified protocol group
 *              entry can be successfully set. Otherwise, FALSE is returned.
 * INPUT    :   frame_type      --  frame type
 *                              --  the range of the value is [1..5] of UI32_T,
 *                                  following the definition of MIB value:
 *                                  VAL_dot1vProtocolTemplateFrameType_ethernet     (1),
 *                                  VAL_dot1vProtocolTemplateFrameType_rfc1042      (2),
 *                                  VAL_dot1vProtocolTemplateFrameType_snap8021H    (3),
 *                                  VAL_dot1vProtocolTemplateFrameType_snapOther    (4),
 *                                  VAL_dot1vProtocolTemplateFrameType_llcOther     (5)
 *              protocol_value  --  pointer of the protocol value
 *                              --  2 bytes, for frame_type = {1,2,3,5}, or
 *                                  5 bytes, for frame_type = {4}
 *              group_index     --  group index
 *                              --  [1..maxnum_of_group]
 * OUTPUT   :   None
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T  DEV_SWDRV_SetDot1vProtocolGroupEntry(  UI32_T  frame_type,
                                               UI8_T   *protocol_value,
                                               UI32_T  group_index
                                            );

#if (SYS_CPNT_COMBO_PORT_FORCE_MODE == TRUE)
/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_SetPortComboForcedMode
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will set combo port medium mode
 * INPUT    :   unit            --  unit number
 *              port            --  user port number
 *              forcedmode      --  active medium
 *              mau_type        --  SYS_VAL_dot3MauType
 *              speed           --  which type of medium to activate
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortComboForcedMode(UI32_T unit, UI32_T port, UI32_T forcedmode, UI32_T mau_type, UI32_T speed);
#endif

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_ShutdownSwitch
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will shutdown the switch before warm start
 * INPUT    :   None
 * OUTPUT   :   None
 * RETURN   :   None
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
void DEV_SWDRV_ShutdownSwitch(void);

 /* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_ConfigTopologyInfo
 * -------------------------------------------------------------------------------------------
 * PURPOSE : when the toplogy already fixed  ,
 *           the stkpolog will call dev_sw to setting the Module_id
 *
 * INPUT   :
 * OUTPUT  : None
 * RETURN  : None
 * NOTE    :
 * -------------------------------------------------------------------------------------------
 */
BOOL_T  DEV_SWDRV_ConfigTopologyInfo(Stacking_Info_T *stack_info);

 /*--------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_Physical2LogicalPortByUnitID_DeviceID
 *---------------------------------------------------------------------------
 * PURPOSE:  mapping physical port/phy to user port
 * INPUT:    module_id, device_id, phy_port
 * OUTPUT:   unit, port
 * RETURN:   TRUE/FALSE
 * NOTE:
 *---------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_Physical2LogicalPortByUnitID_DeviceID(UI32_T unit_id, UI32_T device_id, UI32_T phy_port, UI32_T *unit, UI32_T *port);


 /*--------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_ GetStackChipDeviceID
 *---------------------------------------------------------------------------
 * PURPOSE:  get  Stack Chip DeviceID
 * INPUT:    None
 * OUTPUT:   StackChipDeviceID
 * RETURN:   TRUE/FALSE
 * NOTE:     This is HardCode
 *---------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_GetStackChipDeviceID(UI32_T  *StackChipDeviceID);



/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_GetDstUnitInfo
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will get the  destination unit  info
 * INPUT:    src_unit
 *           dst_unt
 * OUTPUT   :   port(5670 stacking port (uplink, or downlink port )
 *              dst_mod(destination unit module id)
 * RETURN   :   None
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
void  DEV_SWDRV_GetDstUnitInfo(UI32_T src_unit,UI32_T dst_unt,UI32_T *port,UI32_T *dst_mod);

void DEV_SWDRV_HiGigRemoteLoopbackSet(UI32_T unit, UI32_T port, UI32_T mode);

BOOL_T DEV_SWDRV_Get5670linkport(UI32_T module_id, UI32_T *phy_port);

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_EnableUMCASTIpTrap
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will enable trap unknown multicast ip
 * INPUT    :   None
 * OUTPUT   :   None
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnableUMCASTIpTrap(void);

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_DisableUMCASTIpTrap
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will disable trap unknown multicast ip
 * INPUT    :   None
 * OUTPUT   :   None
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisableUMCASTIpTrap(void);

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_EnableUMCASTMacTrap
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will enable trap unknown multicast mac
 * INPUT    :   None
 * OUTPUT   :   None
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnableUMCASTMacTrap(void);

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_DisableUMCASTMacTrap
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will disable trap unknown multicast mac
 * INPUT    :   None
 * OUTPUT   :   None
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisableUMCASTMacTrap(void);

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_SetFiberPortAutoNeg
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will set fiber port auto neg on/off mode
 * INPUT    :   unit            --  unit number
 *              port            --  user port number
 *              auto_neg        --  fiber mode auto-ngr on(1)/off(0)
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetFiberPortAutoNeg(UI32_T unit, UI32_T port, UI32_T auto_neg);

#if 0/*Tony Lei mark it. Should be delelte the function later */
BOOL_T DEV_SWDRV_SetPortForwardingAttribute(UI32_T port, UI32_T attribute);
#endif

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_EnablePortLearning
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will enable port learning
 * INPUT    :   None
 * OUTPUT   :   None
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnablePortLearning(UI32_T unit, UI32_T port);

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_DisablePortLearning
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will disable port learning
 * INPUT    :   None
 * OUTPUT   :   None
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisablePortLearning(UI32_T unit, UI32_T port);

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_SetPortLearningStatus
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will set port learning status and NA handling
 *              behavior
 * INPUT    :   unit
 *              port
 *              learning
 *              to_cpu
 *              drop
 * OUTPUT   :   None
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortLearningStatus(UI32_T unit, UI32_T port, BOOL_T learning, BOOL_T to_cpu, BOOL_T drop);

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_GetFabricPortToDstUnit
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will get the stacking port to destination unit
 * INPUT    :   unit
 * OUTPUT   :   frabicStkport
 *              5670 stacking port (uplink, or downlink port )
 * RETURN   :   None
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
void  DEV_SWDRV_GetFabricPortToDstUnit(UI32_T unit,UI32_T *frabicStkport);

/*-------------------------------------------------------------------------
 * FUNCTION NAME - GetMasterModuleID
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will get the Master  module_id
 * INPUT    :   None
 * OUTPUT   :   mastermoduleid
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T  DEV_SWDRV_GetMasterModuleID(UI32_T  *mastermoduleid);

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_GetModuleInfoByUnit
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will get the module_id  of a specific unit
 *              (mainboard or option module)
 * INPUT    :   unit_id
 *          :   mainbrd_option
 *              0: mainbord
 *              1: optionmodule
 * OUTPUT   :   moduleid
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T  DEV_SWDRV_GetModuleInfoByUnit(UI32_T unit_id,BOOL_T mainbrd_option,UI32_T *moduleid);

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_GetCpuEnabledDevIdByUnit
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will get the device_id that CPU enabled
 *              of a specific unit
 * INPUT    :   unit_id
 * OUTPUT   :   device_id
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T  DEV_SWDRV_GetCpuEnabledDevIdByUnit(UI32_T unit_id, UI32_T *device_id);

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_GetLocalCrossBarDeviceId
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will get the module_id  of a specific unit
 *              (mainboard or option module)
 * INPUT    :   unit_id
 *          :   mainbrd_option
 *              0: mainbord
 *              1: optionmodule
 * OUTPUT   :   moduleid
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T  DEV_SWDRV_GetLocalCrossBarDeviceId(UI32_T *cross_bar_id);

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_GetFabricportByUnitPosition
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will get the stacking port to destination unit
 * INPUT    :   unit
 * OUTPUT   :   frabicStkport
 *              5670 stacking port (uplink, or downlink port )
 * RETURN   :   None
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
void  DEV_SWDRV_GetFabricportByUnitPosition(UI32_T unitid,UI32_T  *frabicStkport);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisableAllPortAdmin
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function disables a specified port
 * INPUT   : unit_id            -- in which unit
 *           port               -- which port wants to be disabled
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
             FALSE              -- If a given (unit, port) is not available
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisableAllPortAdmin(void);
#if 0
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnableStackingChipAllPort
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function disables a specified port
 * INPUT   : None
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
             FALSE              -- If a given (unit, port) is not available
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnableStackingChipAllPort(void);
#endif
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetNextSwitchChipId
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function diable the egress ports of  the vid table when master detect its ring
 *           cut first ,can avoid the looping
 * INPUT   : *device_id
 * OUTPUT  : *device_id
 * RETURN  : TRUE  --  get next succuess
             FALSE --  don't exist the next chip id
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_GetNextSwitchChipId(UI32_T *device_id);

void DEV_SWDRV_VID_BREAK(void);

void DEV_SWDRV_Receive_All(int flag);

#if (SYS_CPNT_CPU_INTERFACE_CPU_JOIN_VLAN == TRUE)
/* ---------------------------------------------------------------------
 * ROUTINE NAME  -DEV_SWDRV_SetBlockCPUForwardingAttr
 * ---------------------------------------------------------------------
 * PURPOSE: For CPU join VLAN, but we should not forward BC, unknown MC,
 *          DLF packet to cpu.
 * INPUT : None
 * OUTPUT: None
 * RETURN: TRUE/FALSE
 * NOTES : Both front port and hih port should set those register
 *         UNKNOWN_UCAST_BLOCK_MASKr,IUNKNOWN_UCAST_BLOCK_MASKr,
 *         UNKNOWN_MCAST_BLOCK_MASKr,IUNKNOWN_MCAST_BLOCK_MASKr,
 *         BCAST_BLOCK_MASKr,IBCAST_BLOCK_MASKr,
 * ---------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetBlockCPUForwardingAttr();
#endif

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPort1000BaseTForceMode
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function sets the specified giga-phy mode for a given port.
 *           This function forces a given port to operate on the specified giga-phy mode
 * INPUT   : unit_id          -- in which unit
 *           port             -- which port to set
 *           force_mode       -- available modes for a given port are listed below
 *                               VAL_portMasterSlaveModeCfg_master
 *                               VAL_portMasterSlaveModeCfg_slave
 *                               VAL_portMasterSlaveModeCfg_auto
 * OUTPUT  : None
 * RETURN  : TRUE             -- Success
 *           FALSE            -- If a given (unit, port) is not available, or it can not support
 *                               the specified giga-phy mode
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPort1000BaseTForceMode(UI32_T unit_id, UI32_T port, UI32_T mode);

#if (SYS_CPNT_UNIT_HOT_SWAP == TRUE)
/*--------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SavePreHotSwapPortMapping()
 *---------------------------------------------------------------------------
 * PURPOSE: To save a copy of the stabilized portmapping for AMTR use
 * INPUT:   None
 * OUTPUT:  None
 * RETURN:  None
 * NOTE:    Should be called at Provision Complete stage
 *---------------------------------------------------------------------------
 */
void DEV_SWDRV_SavePreHotSwapPortMapping(void);

/*--------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_PreHotSwapLogical2PhyDevicePortID
 *---------------------------------------------------------------------------
 * PURPOSE:  mapping logical user port to phy port.
 *           This portmapping is the one before topology change.
 * INPUT:    unit_id, port,
 * OUTPUT:   module_id, device_id, phy_port
 * RETURN:   TRUE/FALSE
 * NOTE:     This API is currently used by AMTR in HandleHotRemoval
 *---------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_PreHotSwapLogical2PhyDevicePortID(UI32_T unit_id, UI32_T port, UI32_T *module_id, UI32_T *device_id, UI32_T *phy_port);

#endif

#if (SYS_CPNT_POWER_SAVE == TRUE)
/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortPowerSave
 * -------------------------------------------------------------------------
 * FUNCTION: This function will set the port power-save status
 * INPUT   : unit --which unit
 *           port -- which port to enable/disable power save
 *           status--TRUE:enable
 *                   FALSE:disable
 *           link_status-- link status of the port
 * OUTPUT  :
 * RETURN  : True: Successfully, False: If not available
 * NOTE    :None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetPortPowerSave(UI32_T unit, UI32_T port, BOOL_T status, UI8_T link_status);
#endif

#if (SYS_CPNT_SWCTRL_CABLE_DIAG == TRUE)
/*------------------------------------------------------------------------|
 * ROUTINE NAME - DEV_SWDRV_GetCableDiag
 *------------------------------------------------------------------------|
 * FUNCTION: Execute and return the cable diagnositc informaiton
 * INPUT   : unit
 *           port
 * OUTPUT  : diag_status - DEV_SWDRV_PORT_CABLE_STATE_OK,
 *                         DEV_SWDRV_PORT_CABLE_STATE_OPEN,
 *                         DEV_SWDRV_PORT_CABLE_STATE_SHORT,
 *                         DEV_SWDRV_PORT_CABLE_STATE_OPENSHORT,
 *                         DEV_SWDRV_PORT_CABLE_STATE_CROSSTALK,
 *                         DEV_SWDRV_PORT_CABLE_STATE_UNKNOWN,
 *                         DEV_SWDRV_PORT_CABLE_STATE_COUNT
 *           diag_fault_len
 * RETURN  : None
 * NOTE    :
 *------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetCableDiag(UI32_T unit, UI32_T port, DEV_SWDRV_CableDiagResult_T *diag_result);

#if (SYS_CPNT_SWCTRL_CABLE_DIAG_CHIP == SYS_CPNT_SWCTRL_CABLE_DIAG_MARVELL)
/*------------------------------------------------------------------------|
 * ROUTINE NAME - DEV_SWDRV_GetCableDiag
 *------------------------------------------------------------------------|
 * FUNCTION: Execute and return the cable diagnositc informaiton
 * INPUT   : unit
 *           port
 * OUTPUT  : diag_status - DEV_SWDRV_PORT_CABLE_STATE_OK,
 *                         DEV_SWDRV_PORT_CABLE_STATE_OPEN,
 *                         DEV_SWDRV_PORT_CABLE_STATE_SHORT,
 *                         DEV_SWDRV_PORT_CABLE_STATE_OPENSHORT,
 *                         DEV_SWDRV_PORT_CABLE_STATE_CROSSTALK,
 *                         DEV_SWDRV_PORT_CABLE_STATE_UNKNOWN,
 *                         DEV_SWDRV_PORT_CABLE_STATE_COUNT
 *           diag_fault_len
 * RETURN  : None
 * NOTE    :
 *------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetCableDiagResult(UI32_T unit, UI32_T port, DEV_SWDRV_CableDiagResultGeneral_T *diag_result);
#endif
#endif

/*------------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_EnableInternalLoopback
 *------------------------------------------------------------------------------
 * PURPOSE  : Enable Internal Loopback
 * INPUT    : port - port.
 *
 * OUTPUT   : None.
 * RETURN   : TRUE : SUCCESS, FALSE: FAIL.
 * NOTES    : None.
 *------------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_EnableInternalLoopback(UI32_T port);

/*------------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_DisableInternalLoopback
 *------------------------------------------------------------------------------
 * PURPOSE  : Disable Internal Loopback
 * INPUT    : port - port.
 *
 * OUTPUT   : None.
 * RETURN   : TRUE : SUCCESS, FALSE: FAIL.
 * NOTES    : None.
 *------------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_DisableInternalLoopback(UI32_T port);

#if (SYS_CPNT_INTERNAL_LOOPBACK_TEST == TRUE)
/*------------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_IsPortLoopbacking
 *------------------------------------------------------------------------------
 * PURPOSE  : Disable Internal Loopback
 * INPUT    : port - port.
 *
 * OUTPUT   : None.
 * RETURN   : TRUE : SUCCESS, FALSE: FAIL.
 * NOTES    : None.
 *------------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_IsPortLoopbacking(UI32_T port);
#endif
BOOL_T DEV_SWDRV_EnableAllPortAdmin(void);
BOOL_T DEV_SWDRV_EnableAllPortLearning(void);
BOOL_T DEV_SWDRV_EnableAllPortAutoNeg(void);

BOOL_T  DEV_SWDRV_UpdatePortMapping(BOOL_T is_init);
#ifdef BCM_ROBO_SUPPORT
/*------------------------------------------------------------------------|
 * ROUTINE NAME - DEV_SWDRV_WriteRegister
 *------------------------------------------------------------------------|
 * FUNCTION: Set chip's register value
 * INPUT   : device_id   -- chip unit number
 *           reg_addr    -- register address
 *           reg_val     -- register value
 *           reg_len     -- register len (in byte)
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 *------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_WriteRegister(UI32_T device_id, UI32_T reg_addr, UI32_T reg_val, UI32_T reg_len);
#endif
BOOL_T DEV_SWDRV_SetStackingPort(UI8_T is_stacking_port);

BOOL_T DEV_SWDRV_linkscan_register(void);
BOOL_T DEV_SWDRV_GetNextPortFromPortList (UI32_T *port, UI8_T *port_list);

BOOL_T DEV_SWDRV_GetPortLinkStatusByDeviceId(UI32_T device_id, UI32_T phy_port, UI32_T *link_status);
/*Add for 802.1x -- xiongyu 20090109*/
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortAuthMode
 * -------------------------------------------------------------------------------------------
 * PURPOSE : Set the 802.1X control mode
 * INPUT   : unit_id            -- which unit to set
 *           port               -- which port to set
 *           mode           -- control mode
 * OUTPUT  : None
 * RETURN  : TRUE               -- Success
 *           FALSE              -- Set error.
 * NOTE    :
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortAuthMode(UI32_T unit_id, UI32_T port, UI32_T mode);


#if(SYS_CPNT_SWCTRL_MDIX_CONFIG == TRUE)
BOOL_T DEV_SWDRV_SetMDIXMode(UI32_T unit_id, UI32_T port, UI32_T medium);
#endif

#if (SYS_CPNT_MAC_VLAN == TRUE)
/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetMacVlanEntry
 * -------------------------------------------------------------------------
 * FUNCTION:
 * INPUT   :
 * OUTPUT  : None
 * RETURN  : True: Successfully, False: If not available
 * NOTE    :
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetMacVlanEntry(UI8_T *mac_address, UI16_T vid, UI8_T priority);
/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DeleteMacVlanEntry
 * -------------------------------------------------------------------------
 * FUNCTION:
 * INPUT   :
 * OUTPUT  : None
 * RETURN  : True: Successfully, False: If not available
 * NOTE    :
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_DeleteMacVlanEntry(UI8_T *mac_address);
#endif

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetEapolFramePassThrough
 * -------------------------------------------------------------------------------------------
 * PURPOSE : To set EAPOL frames pass through (pass through means not trapped to CPU)
 * INPUT   : state (TRUE/FALSE)
 * OUTPUT  : None
 * RETURN  : TRUE
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetEapolFramePassThrough(BOOL_T state);

#if (SYS_CPNT_RSPAN == TRUE)
/* -----------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetRspanVlanTag
 * -----------------------------------------------------------------------------
 * PURPOSE : Set VLAN for egressing mirrored packets on a port.
 * INPUT   : target_port -- mirror-to port to set (-1 for all ports)
 *           tpid        -- tag protocol id (tpid and vid are equal 0, meaning
 *                          to disable RSPAN)
 *           vlan        -- virtual lan number (tpid and vid are equal 0,
 *                          meaning to disable RSPAN)
 * OUTPUT  : None
 * RETURN  : TRUE        -- Success
 *           FALSE       -- Possible failure reasons:
 *                          1. the specified specific-port is not available
 *                          2. the ASIC can not support port mirroring function
 *                          3. the input argument target_port is invalid
 * NOTE    :
 *     1. For now RSPAN doesn't support stacking.
 *     2. This API shall be able to accept invalid "unit" and "port" in the
 *        input argument "target_port" and shall return FALSE when the argument
 *        is invalid.
 * -----------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetRspanVlanTag (SYS_TYPE_Uport_T target_port, UI16_T tpid, UI16_T vlan);

/* -----------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisableRspanPortLearning
 * -----------------------------------------------------------------------------
 * FUNCTION: This function will disable port mac learning.
 * INPUT   : unit -- in which unit
 *           port -- in which port
 * OUTPUT  : None
 * RETURN  : True: Successfully, FALSE: Failed
 * NOTE    : For now RSPAN doesn't support stacking. The reason not to use
 *           SWDRV_DisablePortLearning is because there will be different ways
 *           to handle remote parts.
 * -----------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisableRspanPortLearning (UI32_T unit_id, UI32_T port);

/* -----------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnableRspanPortLearning
 * -----------------------------------------------------------------------------
 * FUNCTION: This function will enable port mac learning.
 * INPUT   : unit -- in which unit
 *           port -- in which port
 * OUTPUT  : None
 * RETURN  : True: Successfully, FALSE: Failed
 * NOTE    : For now RSPAN doesn't support stacking. The reason not to use
 *           SWDRV_DisablePortLearning is because there will be different ways
 *           to handle remote parts.
 * -----------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnableRspanPortLearning (UI32_T unit_id, UI32_T port);

/* -----------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_ModifyMaxFrameSize
 * -----------------------------------------------------------------------------
 * FUNCTION: This function will modify maximum fram size of RSPAN
 * INPUT   : port -- in which port
 *           is_increase -- TRUE:add RSPAN tag size (4 bytes)
 *                       -- FALSE:delete RSPAN tag size (4 bytes)
 * OUTPUT  : None
 * RETURN  : True: Successfully, FALSE: Failed
 * NOTE    : For now RSPAN doesn't support stacking. The reason not to use
 *           SWDRV_DisablePortLearning is because there will be different ways
 *           to handle remote parts.
 * -----------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_ModifyMaxFrameSize (UI8_T port,BOOL_T is_increase);
#endif /* end of #if (SYS_CPNT_RSPAN == TRUE) */

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortMediaActive
 * -------------------------------------------------------------------------
 * FUNCTION: This function check which media is active.
 * INPUT   : device_id
 *           phy_port
 * OUTPUT  : port_media_p -- DEV_SWDRV_PORT_MEDIA_COPPER
 *                           DEV_SWDRV_PORT_MEDIA_FIBER
 *                           DEV_SWDRV_PORT_MEDIA_UNKNOWN
 * RETURN  : TRUE/FALSE
 * NOTE    : None.
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetPortMediaActive(UI32_T unit, UI32_T port, UI32_T *port_media_p);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_TrapUnknownIpMcastToCPU
 * -------------------------------------------------------------------------
 * FUNCTION: This function will trap unknown ip multicast packet to CPU
 * INPUT   : to_cpu -- trap to cpu or not.
 *           flood  -- TRUE to flood to other ports; FLASE to discard the traffic.
 *           vid = 0 -- global setting, vid = else -- which VLAN ID to set
 * OUTPUT  : None
 * RETURN  : True: Successfully, False: If not available
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_TrapUnknownIpMcastToCPU(BOOL_T to_cpu, BOOL_T flood, UI32_T vid);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_TrapUnknownIpv6McastToCPU
 * -------------------------------------------------------------------------
 * FUNCTION: This function will trap unknown ipv6 multicast packet to CPU
 * INPUT   : to_cpu -- trap to cpu or not.
 *           flood  -- TRUE to flood to other ports; FLASE to discard the traffic.
 *           vid = 0 -- global setting, vid = else -- which VLAN ID to set
 * OUTPUT  : None
 * RETURN  : True: Successfully, False: If not available
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_TrapUnknownIpv6McastToCPU(BOOL_T to_cpu, BOOL_T flood, UI32_T vid);

#if (SYS_CPNT_EFM_OAM == TRUE)
#if (SYS_CPNT_EFM_OAM_REMOTE_LB_PASSIVELY_BY_RULE != TRUE)
/* -------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_SetOamPduToCpu
 * -------------------------------------------------------------------------
 * PURPOSE : This function will trap EFM OAM PDU to CPU
 * INPUT   : unit  -- which unit.
 *           port  -- which port.
 * OUTPUT  : None
 * RETURN  : True: Successfully, FALSE: Failed
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetOamPduToCpu(UI32_T unit, UI32_T port, BOOL_T enable);

/* -------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_SetOamLoopback
 * -------------------------------------------------------------------------
 * PURPOSE : This function will enable EFM OAM Loopback
 * INPUT   : unit  -- which unit.
 *           port  -- which port.
 * OUTPUT  : None
 * RETURN  : True: Successfully, FALSE: Failed
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetOamLoopback(UI32_T unit, UI32_T port, BOOL_T enable);
#endif /* (SYS_CPNT_EFM_OAM_REMOTE_LB_PASSIVELY_BY_RULE != TRUE) */
#endif /* (SYS_CPNT_EFM_OAM == TRUE) */

/* -------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_SetCpuRateLimit
 * -------------------------------------------------------------------------
 * PURPOSE : To configure CPU rate limit
 * INPUT   : pkt_type  -- SWDRV_PKTTYPE_XXX
 *           rate      -- in pkt/s. 0 to disable.
 * OUTPUT  : None
 * RETURN  : TRUE / FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetCpuRateLimit(UI32_T pkt_type, UI32_T rate);

/* -------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_GetPortAbility
 * -------------------------------------------------------------------------
 * PURPOSE : To get port abilities
 * INPUT   : unit
 *           port
 * OUTPUT  : ability_p
 * RETURN  : TRUE / FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_GetPortAbility(UI32_T unit, UI32_T port, DEV_SWDRV_PortAbility_T *ability_p);

#if 0 /* not used */
BOOL_T DEV_SWDRV_PhyRegisterWrite(UI32_T unit, UI32_T port, UI8_T reg, UI16_T data);
BOOL_T DEV_SWDRV_PhyRegisterRead(UI32_T unit, UI32_T port, UI8_T reg, UI16_T* data);
#endif /* #if 0 */
BOOL_T DEV_SWDRV_PhyLightPortLedNormal(void);

BOOL_T DEV_SWDRV_TwsiInit(void);
BOOL_T DEV_SWDRV_TwsiRegisterWrite(UI32_T dev_slv_id, UI32_T reg_addr, UI32_T value);
BOOL_T DEV_SWDRV_TwsiRegisterRead(UI32_T dev_slv_id, UI32_T reg_addr, UI32_T* value);
BOOL_T DEV_SWDRV_TwsiDataWrite(UI8_T dev_slv_id, UI8_T type, UI8_T validOffset, UI32_T offset, UI8_T moreThen256, const UI8_T* data, UI8_T data_len);
BOOL_T DEV_SWDRV_TwsiDataRead(UI8_T dev_slv_id, UI8_T type, UI8_T validOffset, UI32_T offset, UI8_T moreThen256, UI8_T data_len, UI8_T* data);
BOOL_T DEV_SWDRV_TwsiDataWriteWithBusIdx(UI8_T i2c_bus_idx, UI8_T dev_slv_id, UI8_T type, UI8_T validOffset, UI32_T offset, UI8_T moreThen256, const UI8_T* data, UI8_T data_len);
BOOL_T DEV_SWDRV_TwsiDataReadWithBusIdx(UI8_T i2c_bus_idx, UI8_T dev_slv_id, UI8_T type, UI8_T validOffset, UI32_T offset, UI8_T moreThen256, UI8_T data_len, UI8_T* data);

#if (SYS_CPNT_POE == TRUE)

#if (SYS_CPNT_POE_INTERFACE == SYS_CPNT_POE_INTERFACE_DRAGONITE)
BOOL_T DEV_SWDRV_ProcessDragoniteData(UI32_T event, UI32_T unit, UI32_T port, UI32_T data, CPSS_GEN_DRAGONITE_DATA_STC *dragonitep);
#endif

BOOL_T DEV_SWDRV_TwsiWrite(UI8_T I2C_Address, UI16_T Flags, const UI8_T* Txdata, UI16_T num_write_length, void* UserParam);
BOOL_T DEV_SWDRV_TwsiRead(UI8_T I2C_Address, UI16_T Flags, UI8_T* Rxdata, UI16_T number_of_bytes_to_read, void* UserParam);
BOOL_T DEV_SWDRV_MSCC_POE_Init(void);
BOOL_T DEV_SWDRV_MSCC_POE_Write(UI8_T* pTxdata, UI16_T num_write_length, I32_T* pDevice_error);
BOOL_T DEV_SWDRV_MSCC_POE_Read(UI8_T* pRxdata, UI16_T num_read_length, I32_T* pDevice_error);
BOOL_T DEV_SWDRV_MSCC_POE_Exit(void);
#endif

#if (SYS_CPNT_10G_MODULE_SUPPORT == TRUE)
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_Reconfig_Module
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function reconfig HW PHY singal when plug in module.
 * INPUT   : module_slot_index  -- module slot index
 *           module_id;         -- module ID
 * OUTPUT  : None
 * RETURN  : TRUE / FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_Reconfig_Module(UI32_T module_slot_index, UI8_T module_id);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_Reconfig_Module_ByPprt
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function reconfig HW PHY singal for a specified port.
 * INPUT   : port
 * OUTPUT  : None
 * RETURN  : TRUE / FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_Reconfig_Module_ByPprt(UI32_T port);
#endif /*end of SYS_CPNT_10G_MODULE_SUPPORT */

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetXMIIPhyReg
 * -------------------------------------------------------------------------------------------
 * PURPOSE : Get the register value of the specified XG Phy through
 *           XMII (10-Gigabit Media Independent Interface).
 * INPUT   : device_id      -  The device id of the XG Phy port
 *           phy_addr       -  PHY address
 *           dev_addr       -  Device address
 *           phy_reg_addr   -  PHY register address
 * OUTPUT  : reg_value_p    -  The register value got from XMII
 * RETURN  : TRUE - Success, FALSE - Failed
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_GetXMIIPhyReg(UI32_T device_id, UI32_T phy_addr, UI32_T dev_addr, UI32_T phy_reg_addr, UI16_T *reg_value_p);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetXMIIPhyReg
 * -------------------------------------------------------------------------------------------
 * PURPOSE : Set the register value of the specified XG Phy through
 *           XMII (10-Gigabit Media Independent Interface).
 * INPUT   : device_id      -  The device id of the XG Phy port
 *           phy_addr       -  PHY address
 *           dev_addr       -  Device address
 *           phy_reg_addr   -  PHY register address
 *           reg_value      -  The register value to be set through XMII
 * OUTPUT  : None
 * RETURN  : TRUE - Success, FALSE - Failed
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetXMIIPhyReg(UI32_T device_id, UI32_T phy_addr, UI32_T dev_addr, UI32_T phy_reg_addr, UI16_T reg_value);


#if (SYS_CPNT_HW_LINKSCAN == TRUE)
/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_LinkStatusChanged_Callback
 * ------------------------------------------------------------------------
 * PURPOSE  :   This function is to register HW link status changed event
 * INPUT    :   func - callback func to handle link status changed
 * OUTPUT   :   None
 * RETURN   :   None
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
void DEV_SWDRV_Register_LinkStatusChanged(void (*func)(UI32_T unit, UI32_T port, UI32_T link_status));
#endif /* (SYS_CPNT_HW_LINKSCAN == TRUE) */

#if (SYS_CPNT_MLDSNP == TRUE)
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_EnableMLDTrap2CPU
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function enable trap MLD packet to CPU
 * INPUT   : None
 * OUTPUT  : None
 * RETURN  : TRUE  --  get next succuess
             FALSE --  don't exist the next chip id
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnableMLDTrap2CPU(void);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DisableMLDTrap2CPU
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function enable or disbale trap MLD packet to CPU
 * INPUT   : None
 * OUTPUT  : None
 * RETURN  : TRUE  --  get next succuess
             FALSE --  don't exist the next chip id
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DisableMLDTrap2CPU(void);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_TrapMLDToCPU
 * -------------------------------------------------------------------------
 * FUNCTION: This function will trap/mirror MLD packet to CPU
 * INPUT   : to_cpu -- TRUE for trap to cpu
 *           drop   -- TRUE for drop
 * OUTPUT  : None
 * RETURN  : True: Successfully, False: If not available
 * NOTE    : to_cpu  drop
 *           TRUE    TRUE  : trap
 *           TRUE    FALSE : copy
 *           FALSE   TRUE  : not supported
 *           FALSE   FALSE : forward
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_TrapMLDToCPU(BOOL_T to_cpu, BOOL_T drop);
#endif


#if (SYS_CPNT_IPV6_RA_GUARD_TRAP_BY_REG == TRUE)
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetRaAndRrTrap2CPU
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function eanble/disable RA/RR packet to CPU
 * INPUT   : is_enabled - TRUE to enable
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetRaAndRrTrap2CPU(
    BOOL_T  is_enabled);

#endif /* #if (SYS_CPNT_IPV6_RA_GUARD_TRAP_BY_REG == TRUE) */

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_DoPHYRegsTransactions
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function will do phy register write operations by the given arguments
 *           atomically
 * INPUT   : unit_id     -- which unit to set
 *           port        -- which port to set
 *           phy_reg_ops -- an array which contains the phy reg operations to be performed
 *                          as a transaction
 *           num_of_ops  -- number of element in phy_reg_ops[]
 * OUTPUT  : None
 * RETURN  : TRUE        -- successfully
 *           FALSE       -- errors occur when doing phy register write operations
 * NOTE    : Always switch page register back to page 0
 *           if phy_reg_ops[] changes the page register.
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DoPHYRegsTransactions(UI32_T unit_id, UI32_T port, DEV_SWDRV_PHY_Reg_Operation_T phy_reg_ops[], UI32_T num_of_ops);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetMIIPhyRegByPage
 * -------------------------------------------------------------------------
 * FUNCTION: This function will Read Phy Register by specified Page
 * INPUT   : device_id - device id
 *           phy_port  - PHY port id
 *           phy_addr  - PHY address
 *           phy_reg   - PHY register to read
 *           page_reg  - page register of the PHY
 *           page_val  - page value to be written to the page register of the PHY
 *           page_mask - the mask used together with page_val when writing page
 *                       register of the PHY, only the bit with value 1 will be
 *                       written to the page register.
 * OUTPUT  : data_p    - Register value read from PHY
 * RETURN  : TRUE/FALSE
 * NOTE    : Must not call this function if PHY do not have a page register
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetMIIPhyRegByPage(UI32_T device_id, UI32_T phy_addr,
    UI32_T phy_port, UI32_T phy_reg, UI32_T page_reg, UI32_T page_val, UI32_T page_mask, UI16_T *data_p);

#if (SYS_CPNT_NDSNP == TRUE)
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_TrapND2CPU
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function trap ND packet to CPU
 * INPUT   : to_cpu    -- send packet to cpu or not
 *           drop      -- drop packet or not
 * OUTPUT  : None
 * RETURN  : TRUE  --  get next succuess
             FALSE --  don't exist the next chip id
 * NOTE    :
 *                 to_cpu         !to_cpu
 *      drop    redirect to cpu     drop
 *     !drop     copy to cpu       flood
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_TrapND2CPU(BOOL_T to_cpu, BOOL_T drop);

#endif

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortMacAddr
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function configure source MAC address of chip port.
 * INPUT   : unit
 *           port
 *           mac_addr
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortMacAddr(UI32_T unit, UI32_T port, UI8_T *mac_addr);

#if (SYS_CPNT_PFC == TRUE)
/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortPfcStatus
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function configure PFC status.
 * INPUT   : unit
 *           port
 *           rx_en      -- enable/disable PFC response
 *           tx_en      -- enable/disable PFC triggering
 *           pri_en_vec -- bitmap of enable status per priority
 *                         set bit to enable PFC; clear to disable.
 * OUTPUT  : None
 * RETURN  : TRUE  --  get next succuess
             FALSE --  don't exist the next chip id
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetPortPfcStatus(UI32_T unit, UI32_T port, BOOL_T rx_en, BOOL_T tx_en, UI16_T pri_en_vec);

/* -------------------------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_UpdatePfcPriMap
 * -------------------------------------------------------------------------------------------
 * PURPOSE : This function update PFC priority to queue mapping.
 * INPUT   : None
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_UpdatePfcPriMap(void);
#endif /* (SYS_CPNT_PFC == TRUE) */

#if (SYS_CPNT_MAC_IN_MAC == TRUE)
/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetMimService
 * -------------------------------------------------------------------------
 * FUNCTION: This function will create/destroy a MiM service instance.
 * INPUT   : mim_p            -- MiM service instance info.
 *           is_valid         -- TRUE to create/update; FALSE to destroy.
 * OUTPUT  : None
 * RETURN  : TRUE: Successfully, FALSE: If not available
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetMimService(DEV_SWDRV_MimServiceInfo_T *mim_p, BOOL_T is_valid);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetMimServicePort
 * -------------------------------------------------------------------------
 * FUNCTION: This function will add/delete member port to a MiM service instance.
 * INPUT   : mim_port_p       -- MiM port info.
 *           is_valid         -- TRUE to add; FALSE to delete.
 * OUTPUT  : None
 * RETURN  : TRUE: Successfully, FALSE: If not available
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetMimServicePort(DEV_SWDRV_MimPortInfo_T *mim_port_p, BOOL_T is_valid);

/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_SetMimServicePortLearningStatus
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will set MiM port learning status
 * INPUT    :   learning
 *              to_cpu
 *              drop
 * OUTPUT   :   None
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetMimServicePortLearningStatus(BOOL_T learning, BOOL_T to_cpu, BOOL_T drop);

#if (SYS_CPNT_IAAS == TRUE)
/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_SetMimServicePortLearningStatusForStationMove
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will set MiM port learning status
 *              for station move handling only
 * INPUT    :   learning
 *              to_cpu
 *              drop
 * OUTPUT   :   None
 * RETURN   :   TRUE/FALSE
 * NOTES    :   None
 * ------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetMimServicePortLearningStatusForStationMove(BOOL_T learning, BOOL_T to_cpu, BOOL_T drop);
#endif /* (SYS_CPNT_IAAS == TRUE) */
#endif /* (SYS_CPNT_MAC_IN_MAC == TRUE) */

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetAllPortAverageTemperature
 * -------------------------------------------------------------------------
 * FUNCTION: This function will get average temperature from PHY chipsets.
 * INPUT   : None.
 * OUTPUT  : temperature -- The average temperature from PHY chipsets.
 * RETURN  : True: Successfully.
 *           False: If not available / Failed.
 * NOTE    : The feature will be supported by following PHY chipset.
 *           1. 88E1540 family:
 *              - 88E1543
 *              - 88E1545
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetAllPortAverageTemperature(UI32_T *temperature);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetCpuPortRate
 * -------------------------------------------------------------------------
 * FUNCTION:
 * INPUT   : packet per second       -- cpu port rx rate limit
 * OUTPUT  : None
 * RETURN  : TRUE:
 *           FALSE:
 * NOTE    :
 * -------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetCpuPortRate(UI32_T packet_per_second);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortEgressBlock
 * -------------------------------------------------------------------------
 * FUNCTION: To set egress block ports.
 * INPUT   : unit
 *           port
 *           egr_blk_uport_list - uport list to block.
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None.
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetPortEgressBlock(
    UI32_T unit,
    UI32_T port,
    UI8_T egr_blk_uport_list[SYS_ADPT_NBR_OF_BYTE_FOR_1BIT_UPORT_LIST]);

/* -------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_DisableVlanFlooding
 * -------------------------------------------------------------------------
 * PURPOSE : This function will drop and disable unknown UC/MC/BC flooding.
 *           1. Drop unicast packets in the VLAN that miss the L2 lookup and
 *              do not copy to CPU. Multicast packets must not be dropped.
 *           2. Block flooding of unknown unicast, unknown multicast and
 *              broadcast by default.
 * INPUT   : vid   -- which VLAN
 *           type  -- Uknown UC, Uknown MC or BC
 *           flood -- TRUE = flooding, FALSE = not flooding
 * OUTPUT  : None
 * RETURN  : TRUE / FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_SetVlanFlooding(UI32_T vid, DEV_SWDRV_VlanFloodingType_T type, BOOL_T flood);

/* -------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_EnablePortOpenFlowMode
 * -------------------------------------------------------------------------
 * PURPOSE : This function will configure the following settings for
 *           specified port to meet OpenFlow requirements.
 *           1. Turn off flow control on each port.
 *           2. Disable MAC learning on new addresses and copy SLF packet
 *              to CPU.
 *           3. Disable MAC learning on station moves and copy SLF packet
 *              to CPU.
 *           4. Disable IPv4 Multicast
 *           5. Disable IPv6 Multicast
 *           6. Discard untagged traffic
 *           7. Filter traffic for a VLAN which is not a member of a port.
 * INPUT   : unit -- which unit
 *           port -- which port to enable OpenFlow mode
 * OUTPUT  : None
 * RETURN  : TRUE / FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_EnablePortOpenFlowMode(UI32_T unit, UI32_T port);

/* -------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_DeleteAllPortFromVlan
 * -------------------------------------------------------------------------
 * PURPOSE : Remove all ports from specified VLAN
 * INPUT   : vid -- which VLAN to remove all members
 * OUTPUT  : None
 * RETURN  : TRUE / FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_DeleteAllPortFromVlan(UI32_T vid);

/* -------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_StaticMacMovePktToCpu
 * -------------------------------------------------------------------------
 * PURPOSE : The operation for static MAC address port move event.
 * INPUT   : is_enable -- TRUE will trap packet to CPU. FASLE will not.
 * OUTPUT  : None
 * RETURN  : TRUE / FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_StaticMacMovePktToCpu(UI32_T is_enable);

#if (SYS_CPNT_VXLAN == TRUE)
/*------------------------------------------------------------------------------
 * Function : DEV_SWDRV_GetVxlanPortFromUPortMap
 *------------------------------------------------------------------------------
 * Purpose  : This function get the vxlan port id by the specified port or trunk
 *            id and vfi.
 * INPUT    : port       - logical port, should be zero when get info of trunk
 *            trunk_id   - trunk id, should be zero when get info of port
 *            vfi        - virtual forwarding instance
 *            type       - Access port or Network port
 * OUTPUT   : None
 * RETURN   : vxlan_port id, 0 when failed
 * NOTES    : The input argument port and trunk_id cannot be non-zero at the
 *            same time.
 *-----------------------------------------------------------------------------*/
UI32_T DEV_SWDRV_GetVxlanPortFromUPortMap(UI32_T port, UI32_T trunk_id, UI16_T vfi, UI8_T type);

/*------------------------------------------------------------------------------
 * Function : DEV_SWDRV_GetVxlanPortIteratorFromUportMap
 *------------------------------------------------------------------------------
 * Purpose  : This function get the vxlan info iterator of the specified port or
 *            trunk id.
 * INPUT    : port       - logical port, should be zero when get the iterator of
 *                         the trunk
 *            trunk_id   - trunk id, should be zero when get the iterator of the
 *                         port
 * OUTPUT   : None
 * RETURN   : NULL if no vxlan info for the specified port or trunk id
 *            Non-NULL for the iterator of the specified port or trunk id
 * NOTES    : The input argument port and trunk_id cannot be non-zero at the
 *            same time.
 *-----------------------------------------------------------------------------*/
void* DEV_SWDRV_GetVxlanPortIteratorFromUportMap(UI32_T port, UI32_T trunk_id);

/*------------------------------------------------------------------------------
 * Function : DEV_SWDRV_GetNextVxlanPortFromUportMap
 *------------------------------------------------------------------------------
 * Purpose  : This function get the next vxlan info by the given iterator.
 * INPUT    : None
 * OUTPUT   : iterator_p   - The iterator is got from the function
 *                           DEV_SWDRV_GetVxlanPortIteratorFromUportMap().
 *            vxlan_port_p - the vxlan port
 *            vfi_p        - virtual forwarding instance
 * RETURN   : TRUE if the info is got successfully.
 *            FALSE if there is no more info to get.
 * NOTES    : None.
 *-----------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetNextVxlanPortFromUportMap(void** iterator_p, UI32_T *vxlan_port_p, UI16_T *vfi_p);
/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetVxlanStatus
 * -------------------------------------------------------------------------
 * FUNCTION: To enable/disable vxlan globally.
 * INPUT   : is_enable          - TRUE to enable
 *           is_random_src_port - TRUE to configure random src port also
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetVxlanStatus(
    BOOL_T  is_enable,
    BOOL_T  is_random_src_port);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetVxlanStatusPort
 * -------------------------------------------------------------------------
 * FUNCTION: To enable/disable vxlan status for a port.
 * INPUT   : unit        - unit to set
 *           port        - port to set
 *           is_acc_port - TRUE if it's access port
 *           is_enable   - TRUE if enable
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : not support trunk !!!
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetVxlanStatusPort(
    UI32_T  unit,
    UI32_T  port,
    BOOL_T  is_acc_port,
    BOOL_T  is_enable);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetVxlanUdpPort
 * -------------------------------------------------------------------------
 * FUNCTION: To set udp dst port for vxlan globally.
 * INPUT   : udp_port - dst port to conifgure
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetVxlanUdpPort(UI32_T udp_port);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetVxlanVpn
 * -------------------------------------------------------------------------
 * FUNCTION: To add/del VPN for VXLAN
 * INPUT   : vpn_info_p - key for add is vnid
 *                        key for del is vfi/bc_group
 *           is_add     - TRUE to add
 * OUTPUT  : vpn_info_p - vfi/bc_group for add
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetVxlanVpn(
    DEV_SWDRV_VxlanVpnInfo_T    *vpn_info_p,
    BOOL_T                      is_add);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_AddVtepIntoMcastGroup
 * -------------------------------------------------------------------------
 * FUNCTION: To add/del a vxlan port to mcast group.
 * INPUT   : bcast_group - bcast group to set
 *           vxlan_port  - vxlan port to set
 *           unit        - unit to set
 *           port        - port to set (trunk id if unit is 0)
 *           is_add      - TRUE to add
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_AddVtepIntoMcastGroup(
    UI32_T  bcast_group,
    UI32_T  vxlan_port,
    BOOL_T  is_add);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetVxlanPortLearning
 * -------------------------------------------------------------------------
 * FUNCTION: To enable/disable MAC learning for VXLAN port.
 * INPUT   : vxlan_port_id - Which VXLAN logical port.
 *           is_learning -- TRUE to enable MAC learning.
 *                          FALSE to disable MAC learning.
 * OUTPUT  : None
 * RETURN  : TRUE: Successfully, FALSE: If not available
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetVxlanPortLearning(
    UI32_T vxlan_port_id,
    BOOL_T is_learning);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_CreateVTEP
 * -------------------------------------------------------------------------
 * FUNCTION: To create vtep for vxlan.
 * INPUT   : vfi_id       - vfi to create vtep
 *           l3_inf_id    - l3 intf id used in sdk
 *           unit         - physical unit of vtep
 *           e_port       - physical port of vtep
 *           udp_port     - udp dst port for vxlan
 *           r_mac        - remote mac, not used if it's access vtep
 *           is_mc        - TRUE if it's mc vtep
 *           is_acc_port  - TRUE if it's access vtep
 *           l_vtep_p     - local ip of vtep, not used if it's access vtep
 *           r_vtep_p     - remote ip of vtep, not used if it's access vtep
 * OUTPUT  : vxlan_port_p - output vxlan port created
 * RETURN  : TRUE/FALSE
 * NOTE    : 1. for trunk, caller should call DEV_SWDRV_SetVxlanStatusPort
 *              to enable for all trunk member port.
 *           2. not cover the case when apply settings on a trunk on the board
 *              that has more than 1 ASIC.
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_CreateVxlanAccessPort(
    UI32_T              vfi_id,
    UI32_T              l3_inf_id,
    UI32_T              unit,
    UI32_T              port,
    UI8_T               mac[SYS_ADPT_MAC_ADDR_LEN],
    UI32_T              match_type,
    UI32_T              *vxlan_port_p);

BOOL_T DEV_SWDRV_CreateVxlanNetworkPort(
    UI32_T                      vfi_id,
    UI32_T              udp_port,
    BOOL_T              is_mc,
    L_INET_AddrIp_T     *l_vtep_p,
    L_INET_AddrIp_T     *r_vtep_p,
    BOOL_T                      is_ecmp,
    void                        *nh_hw_info,
    UI32_T              *vxlan_port_p);

BOOL_T DEV_SWDRV_DestroyVxlanPort(
    UI32_T  vfi_id,
    UI32_T  vxlan_port_id,
    BOOL_T  is_ecmp);

BOOL_T DEV_SWDRV_CreateVxlanNexthop(
    UI32_T              l3_inf_id,
    UI32_T  unit,
    UI32_T              port,
    UI8_T               mac[SYS_ADPT_MAC_ADDR_LEN],
    BOOL_T              is_mc,
    void                **nh_hw_info_pp);

BOOL_T DEV_SWDRV_DestroyVxlanNexthop(void *nh_hw_info);

BOOL_T DEV_SWDRV_AddVxlanEcmpNexthop(
    UI32_T                      vfi_id,
    UI32_T vxlan_port_id,
    void                        *nh_hw_info);

BOOL_T DEV_SWDRV_RemoveVxlanEcmpNexthop(
    UI32_T                      vfi_id,
    UI32_T                      vxlan_port_id,
    void                        *nh_hw_info);

#endif /*#if(SYS_CPNT_VXLAN == TRUE)*/

#if (SYS_CPNT_HASH_SELECTION == TRUE)
/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetHashSelBlock
 * -------------------------------------------------------------------------
 * FUNCTION: To set hash-selection block
 * INPUT   : block_info_p - block info
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetHashSelBlock(DEV_SWDRV_HashSelBlockInfo_T *block_info_p);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_UnBindHashSelForECMP
 * -------------------------------------------------------------------------
 * FUNCTION: Unbind hash-selection for ECMP
 * INPUT   : None
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_UnBindHashSelForECMP(void);

#if (SYS_CPNT_ECMP_BALANCE_MODE == TRUE)
/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetHashSelectionForECMP
 * -------------------------------------------------------------------------
 * FUNCTION: To set hash-selection block index for ECMP
 * INPUT   : hw_block_index - the index of hash-selection block for ECMP
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetHashSelectionForECMP(UI8_T hw_block_index);
#endif
#endif /*#if (SYS_CPNT_HASH_SELECTION == TRUE)*/

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortStatusForLicense
 * -------------------------------------------------------------------------
 * FUNCTION: To set set port administration status
 * INPUT   : unit
 *           port
 *           status  - TRUE/FALSE
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetPortStatusForLicense(UI32_T unit, UI32_T port, BOOL_T status);

#if (SYS_CPNT_SWCTRL_SWITCH_MODE_CONFIGURABLE == TRUE)
/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetSwitchingMode
 * -------------------------------------------------------------------------
 * FUNCTION: To set switching mode
 * INPUT   : unit
 *           port
 *           mode - VAL_swctrlSwitchModeSF
 *                  VAL_swctrlSwitchModeCT
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetSwitchingMode(UI32_T unit, UI32_T port, UI32_T mode);
#endif /*#if (SYS_CPNT_SWCTRL_SWITCH_MODE_CONFIGURABLE == TRUE)*/

#if (SYS_CPNT_SWCTRL_FEC == TRUE)
/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_SetPortFec
 * -------------------------------------------------------------------------
 * FUNCTION: To enable/disable FEC
 * INPUT   : unit
 *           port
 *           fec_mode - VAL_portFecMode_XXX
 * OUTPUT  : None
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_SetPortFec(UI32_T unit, UI32_T port, UI32_T fec_mode);

/* -------------------------------------------------------------------------
 * ROUTINE NAME - DEV_SWDRV_GetPortFecStatus
 * -------------------------------------------------------------------------
 * FUNCTION: To get FEC status
 * INPUT   : unit
 *           port
 * OUTPUT  : fec_mode_p - VAL_portFecMode_XXX
 * RETURN  : TRUE/FALSE
 * NOTE    : None
 * -------------------------------------------------------------------------*/
BOOL_T DEV_SWDRV_GetPortFecStatus(UI32_T unit, UI32_T port, UI32_T *fec_mode_p);
#endif

/* -------------------------------------------------------------------------------------------
* ROUTINE NAME - DEV_SWDRV_GetUnknownIpMcastAction
* -------------------------------------------------------------------------------------------
* PURPOSE : Get the forwarding action for IPv4 unknownm mulitcast.
* INPUT   : dev_id  - device id
* OUTPUT  : to_cpu  - packet will send one copy to CPU
*           flood   - packet will flood to all ports in VLAN
* RETURN  : None
* NOTE    : None
* -------------------------------------------------------------------------------------------
*/
void DEV_SWDRV_GetUnknownIpMcastAction(UI32_T dev_id, BOOL_T *to_cpu, BOOL_T *flood);

/* -------------------------------------------------------------------------------------------
* ROUTINE NAME - DEV_SWDRV_GetUnknownIp6McastAction
* -------------------------------------------------------------------------------------------
* PURPOSE : Get the forwarding action for IPv6 unknownm mulitcast.
* INPUT   : dev_id  - device id
* OUTPUT  : to_cpu  - packet will send one copy to CPU
*           flood   - packet will flood to all ports in VLAN
* RETURN  : None
* NOTE    : None
* -------------------------------------------------------------------------------------------
*/
void DEV_SWDRV_GetUnknownIp6McastAction(UI32_T dev_id, BOOL_T *to_cpu, BOOL_T *flood);

#if(SYS_CPNT_WRED == TRUE)
/*-------------------------------------------------------------------------
 * FUNCTION NAME - DEV_SWDRV_MGR_WredEcnMarking
 * ------------------------------------------------------------------------
 * PURPOSE  :   This funtion will set port ecn marking percentage
 * INPUT    :   unit       - which unit
 *              port       - which port
 *              percentage - what percantage
 * OUTPUT   :   None
 * RETURN   :   TRUE/FALSE
 * NOTES    :   
 * ------------------------------------------------------------------------
 */
BOOL_T DEV_SWDRV_RandomDetect(UI32_T unit, UI32_T port, DEV_SWDRV_RandomDetect_T *value_p);
#endif

#endif /* DEV_SWDRV_H */

