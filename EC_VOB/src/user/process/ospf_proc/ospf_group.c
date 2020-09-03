/* MODULE NAME:  ospf_group.c
 * PURPOSE:
 *     This file handles the related work for OSPF csc group.
 *
 * NOTES:
 *
 * HISTORY
 *    11/27/2008 - Lin.Li     , Created
 *
 * Copyright(C)      Accton Corporation, 2008
 */

/* INCLUDE FILE DECLARATIONS
 */
#include <stdio.h>
#include "sysfun.h"
#include "sys_cpnt.h"
#include "sys_bld.h"
#include "sys_module.h"
#include "l_threadgrp.h"

#include "ospf_group.h"
#include "ospf_proc_comm.h"

#include "ospf_init.h"
#include "ospf_mgr.h"
#include "backdoor_mgr.h"

#if (SYS_CPNT_UNIT_HOT_SWAP == TRUE)
static void   OSPF_GROUP_HandleHotInertion(SYSFUN_Msg_T* msgbuf_p);
static void   OSPF_GROUP_HandleHotRemoval(SYSFUN_Msg_T* msgbuf_p);
#endif

/* NAMING CONSTANT DECLARATIONS
 */
#define OSPF_PMGR_MSGBUF_MAX_REQUIRED_SIZE sizeof(OSPF_GROUP_MgrMsg_T)


/* MACRO FUNCTION DECLARATIONS
 */

/* DATA TYPE DECLARATIONS
 */
/* union all data type used for MGR IPC message to get the maximum required
 * ipc message buffer
 */

typedef union OSPF_GROUP_MgrMsg_U
{
    OSPF_MGR_IPCMsg_T ospf_mgr_ipcmsg;

} OSPF_GROUP_MgrMsg_T;

/* STATIC VARIABLE DECLARATIONS
 */
/* LOCAL SUBPROGRAM DECLARATIONS
 */
static void OSPF_GROUP_EnterTransitionMode(void);
static void OSPF_GROUP_SetTransitionMode(void);
static void OSPF_GROUP_EnterMasterMode(void);
static void OSPF_GROUP_EnterSlaveMode(void);
static void OSPF_GROUP_BackdoorCallback(void);
/* EXPORTED SUBPROGRAM BODIES
 */

/*-----------------------------------------------------------------------------
 * FUNCTION NAME - OSPF_GROUP_InitiateProcessResources
 *-----------------------------------------------------------------------------
 * PURPOSE : Initiate process resource for OSPF group.
 *
 * INPUT   : None.
 *
 * OUTPUT  : None.
 *
 * RETURN  : None.
 *
 * NOTES   : None.
 *-----------------------------------------------------------------------------
 */
void OSPF_GROUP_InitiateProcessResources(void)
{
    /* Initial PMGR used in OSPF Group */


    /* Initial OSPF Group */
    /*Lin.Li, OSPF init in function ospf_start()*/
}
/*-----------------------------------------------------------------------------
 * FUNCTION NAME - OSPF_GROUP_BackdoorCallback
 *-----------------------------------------------------------------------------
 * PURPOSE : inter-CSC relationships' callback for OSPF group.
 *
 * INPUT   : None.
 *
 * OUTPUT  : None.
 *
 * RETURN  : None.
 *
 * NOTES   : None.
 *-----------------------------------------------------------------------------
 */
static void OSPF_GROUP_BackdoorCallback(void)
{
    L_THREADGRP_Handle_T tg_handle = OSPF_PROC_COMM_GetOspfTGHandle();
    UI32_T  member_id;

    /* Join thread group
     */
    if (L_THREADGRP_Join(tg_handle, SYS_BLD_BACKDOOR_THREAD_PRIORITY,
            &member_id) == FALSE)
    {
        printf("\n%s: L_THREADGRP_Join fail.\n", __FUNCTION__);
        return;
    }

    BACKDOOR_MGR_Printf("OSPF Backdoor!!\n");
    OSPF_MGR_BackDoor_Main(tg_handle, member_id);

    /* Leave thread group
     */
    L_THREADGRP_Leave(tg_handle, member_id);
    return;
}

/*-----------------------------------------------------------------------------
 * FUNCTION NAME - OSPF_GROUP_Create_InterCSC_Relation
 *-----------------------------------------------------------------------------
 * PURPOSE : Create inter-CSC relationships for OSPF group.
 *
 * INPUT   : None.
 *
 * OUTPUT  : None.
 *
 * RETURN  : None.
 *
 * NOTES   : None.
 *-----------------------------------------------------------------------------
 */
void OSPF_GROUP_Create_InterCSC_Relation(void)
{
    BACKDOOR_MGR_Register_SubsysBackdoorFunc_CallBack("OSPF",
        SYS_BLD_OSPF_GROUP_IPCMSGQ_KEY, OSPF_GROUP_BackdoorCallback);

}

/* FUNCTION NAME:  OSPF_GROUP_EnterTransitionMode
 * PURPOSE:
 *    This function will invoke all enter transition mode function in OSPF GROUP.
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
 *
 */
static void OSPF_GROUP_EnterTransitionMode(void)
{
    OSPF_INIT_EnterTransitionMode();
}

/* FUNCTION NAME:  OSPF_GROUP_SetTransitionMode
 * PURPOSE:
 *    This function will invoke all set transition mode function in OSPF GROUP.
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
 *
 */
static void OSPF_GROUP_SetTransitionMode(void)
{
    OSPF_INIT_SetTransitionMode();
}

/* FUNCTION NAME:  OSPF_GROUP_EnterMasterMode
 * PURPOSE:
 *    This function will invoke all enter master mode function in OSPF GROUP.
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
 *
 */
static void OSPF_GROUP_EnterMasterMode(void)
{
    OSPF_INIT_EnterMasterMode();
}

/* FUNCTION NAME:  OSPF_GROUP_EnterSlaveMode
 * PURPOSE:
 *    This function will invoke all enter slave mode function in OSPF Group.
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
 *
 */
static void OSPF_GROUP_EnterSlaveMode(void)
{
    OSPF_INIT_EnterSlaveMode();
}

/* FUNCTION NAME:  OSPF_GROUP_Mgr_Thread_Function_Entry
 * PURPOSE:
 *    This is the entry function for the MGR thread of OSPF GROUP.
 *
 * INPUT:
 *    arg   --  not used.
 *
 * OUTPUT:
 *    None.
 *
 * RETURN:
 *    None.
 *
 * NOTES:
 *    None.
 *
 */
static void OSPF_GROUP_Mgr_Thread_Function_Entry(void* arg)
{
    SYSFUN_MsgQ_T        ipcmsgq_handle;
    L_THREADGRP_Handle_T tg_handle = OSPF_PROC_COMM_GetOspfTGHandle();
    UI32_T               member_id,received_events,local_events=SYSFUN_SYSTEM_EVENT_IPCMSG;
    UI8_T                msgbuf[SYSFUN_SIZE_OF_MSG(sizeof(OSPF_MGR_IPCMsg_T))];
    BOOL_T               need_resp;
    SYSFUN_Msg_T         *msgbuf_p;

    msgbuf_p = (SYSFUN_Msg_T*)msgbuf;

    /* join the thread group of CSCGroup1
     */
    if(L_THREADGRP_Join(tg_handle, SYS_BLD_OSPF_GROUP_MGR_THREAD_PRIORITY, &member_id)==FALSE)
    {
        printf("%s: L_THREADGRP_Join fail.\n", __FUNCTION__);
        return;
    }

    /* create mgr ipc message queue handle
     */
    if(SYSFUN_CreateMsgQ(SYS_BLD_OSPF_GROUP_IPCMSGQ_KEY, SYSFUN_MSGQ_BIDIRECTIONAL, &ipcmsgq_handle)!=SYSFUN_OK)
    {
        printf("%s: SYSFUN_CreateMsgQ fail.\n", __FUNCTION__);
        return;
    }

    /* main loop:
     *    while(1)
     *    {
     *
     *        Wait event
     *            Handle SYSFUN_SYSTEM_EVENT_SET_TRANSITION_MODE event if any
     *            Handle SYSFUN_SYSTEM_EVENT_IPCMSG if any
     *            Handle SYSFUN_SYSTEM_EVENT_IPCFAIL if any
     *    }
     */
    while(1)
    {
        SYSFUN_ReceiveEvent (SYSFUN_SYSTEM_EVENT_IPCFAIL|
                             SYSFUN_SYSTEM_EVENT_IPCMSG |
                             SYSFUN_SYSTEM_EVENT_SET_TRANSITION_MODE,
                             SYSFUN_EVENT_WAIT_ANY,
                             (local_events==0)?SYSFUN_TIMEOUT_WAIT_FOREVER:SYSFUN_TIMEOUT_NOWAIT,
                             &received_events);
        local_events |= received_events;

        if(local_events & SYSFUN_SYSTEM_EVENT_SET_TRANSITION_MODE)
        {
            OSPF_GROUP_SetTransitionMode();
            local_events ^= SYSFUN_SYSTEM_EVENT_SET_TRANSITION_MODE;
            /* need not to do IPCFAIL recovery in transition mode
             */
            if(local_events & SYSFUN_SYSTEM_EVENT_IPCFAIL)
            {
                /* clear fail info in IPCFAIL
                 */
                local_events ^= SYSFUN_SYSTEM_EVENT_IPCFAIL;
            }

        }

        /* handle IPCMSG
         */
        if(local_events & SYSFUN_SYSTEM_EVENT_IPCMSG)
        {
            if(SYSFUN_ReceiveMsg(ipcmsgq_handle, 0, SYSFUN_TIMEOUT_NOWAIT,
                OSPF_PMGR_MSGBUF_MAX_REQUIRED_SIZE, msgbuf_p)==SYSFUN_OK)
            {
                /* request thread group execution permission
                 */
                if(L_THREADGRP_Execution_Request(tg_handle, member_id)!=TRUE)
                {
                    SYSFUN_Debug_Printf("%s: L_THREADGRP_Execution_Request fail.\n", __FUNCTION__);
                }

                /* handle request message based on cmd
                 */
                switch(msgbuf_p->cmd)
                {
                    /* module id cmd
                     */
                    case SYS_MODULE_OSPF:
                        need_resp=OSPF_MGR_HandleIPCReqMsg(msgbuf_p);
                        break;
                    case SYS_MODULE_BACKDOOR:
                        need_resp = BACKDOOR_MGR_HandleIPCMsg(msgbuf_p);
                        break;
                    /* global cmd
                     */
                    case SYS_TYPE_CMD_ENTER_MASTER_MODE:
                        OSPF_GROUP_EnterMasterMode();

                        /* SYS_TYPE_CMD_ENTER_MASTER_MODE
                         * need a response which contains nothing
                         */
                        msgbuf_p->msg_size=0;
                        need_resp=TRUE;

                        /* IPCFAIL might happen when a upper layer cscgroup has
                         * entered transition mode but lower layer cscgroups still
                         * in master mode so async callback msg will keep sending
                         * from lower layer cscgroups. In this case, the IPCFAIL
                         * event can be ignored.
                         */
                        if(local_events & SYSFUN_SYSTEM_EVENT_IPCFAIL)
                        {
                            /* clear fail info in IPCFAIL
                             */
                            local_events ^= SYSFUN_SYSTEM_EVENT_IPCFAIL;
                        }

                        break;

                    case SYS_TYPE_CMD_ENTER_SLAVE_MODE:
                        OSPF_GROUP_EnterSlaveMode();

                        /* SYS_TYPE_CMD_ENTER_SLAVE_MODE
                         * need a response which contains nothing
                         */
                        msgbuf_p->msg_size=0;
                        need_resp=TRUE;

                        /* IPCFAIL might happen when a upper layer cscgroup has
                         * entered transition mode but lower layer cscgroups still
                         * in master mode so async callback msg will keep sending
                         * from lower layer cscgroups. In this case, the IPCFAIL
                         * event can be ignored.
                         */
                        if(local_events & SYSFUN_SYSTEM_EVENT_IPCFAIL)
                        {
                            /* clear fail info in IPCFAIL
                             */
                            local_events ^= SYSFUN_SYSTEM_EVENT_IPCFAIL;
                        }

                        break;

                    case SYS_TYPE_CMD_ENTER_TRANSITION_MODE:
                        OSPF_GROUP_EnterTransitionMode();

                        /* SYS_TYPE_CMD_ENTER_TRANSITION_MODE
                         * need a response which contains nothing
                         */
                        msgbuf_p->msg_size=0;
                        need_resp=TRUE;
                        break;


                    case SYS_TYPE_CMD_PROVISION_COMPLETE:

                        /* SYS_TYPE_CMD_PROVISION_COMPLETE
                         * need a response which contains nothing
                         */
                        msgbuf_p->msg_size=0;
                        need_resp=TRUE;
                        break;
                        
                    case SYS_TYPE_CMD_MODULE_PROVISION_COMPLETE:
                    
                        /* SYS_TYPE_CMD_PROVISION_COMPLETE
                         * need a response which contains nothing
                         */
                        msgbuf_p->msg_size=0;
                        need_resp=TRUE;
                        break;

#if (SYS_CPNT_UNIT_HOT_SWAP == TRUE)
                    case     SYS_TYPE_CMD_HANDLE_HOT_INSERTION:
                      OSPF_GROUP_HandleHotInertion(msgbuf_p);
                      
                       msgbuf_p->msg_size=0;
                       need_resp=TRUE;
                       break;
                       
                    case SYS_TYPE_CMD_HANDLE_HOT_REMOVAL:
                      OSPF_GROUP_HandleHotRemoval(msgbuf_p);
                      
                       msgbuf_p->msg_size=0;
                       need_resp=TRUE;
                        break;
#endif
                    case  SYS_TYPE_CMD_RELOAD_SYSTEM:
                    
                        msgbuf_p->msg_size=0;
                        need_resp=TRUE;
                        break;

                        
                    default:
                        /* Unknow command. There is no way to idntify whether this
                         * ipc message need or not need a response. If we response to
                         * a asynchronous msg, then all following synchronous msg will
                         * get wrong responses and that might not easy to debug.
                         * If we do not response to a synchronous msg, the requester
                         * will be blocked forever. It should be easy to debug that
                         * error.
                         */
                        need_resp=FALSE;
                        printf("%s: Invalid IPC req cmd.\n", __FUNCTION__);
                }

                /* release thread group execution permission
                 */
                if(L_THREADGRP_Execution_Release(tg_handle, member_id)!=TRUE)
                {
                    SYSFUN_Debug_Printf("%s: L_THREADGRP_Execution_Release fail.\n", __FUNCTION__);
                }

                if((need_resp==TRUE) && (SYSFUN_SendResponseMsg(ipcmsgq_handle, msgbuf_p)!=SYSFUN_OK))
                    printf("%s: SYSFUN_SendResponseMsg fail.\n", __FUNCTION__);

            } /* end of if(SYSFUN_ReceiveMsg... */
            else
                local_events ^= SYSFUN_SYSTEM_EVENT_IPCMSG;
        } /* end of if(local_events & SYSFUN_SYSTEM_EVENT_IPCMSG) */

        /* handle IPC Async Callback fail when IPC Msgq is empty
         */
        if((local_events & SYSFUN_SYSTEM_EVENT_IPCFAIL) &&
            !(local_events & SYSFUN_SYSTEM_EVENT_IPCMSG))
        {
            /* read fail info from IPCFAIL
             */

            /* do recovery action
             */
            local_events ^= SYSFUN_SYSTEM_EVENT_IPCFAIL;
        }

    } /* end of while(1) */
}

/* FUNCTION NAME:  OSPF_GROUP_Create_All_Threads
 * PURPOSE:
 *    This function will spawn all threads in CSCGroup.
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
 *    All threads in the same CSC group will join the same thread group.
 *
 */
void OSPF_GROUP_Create_All_Threads(void)
{
    UI32_T thread_id;

    L_THREADGRP_Handle_T tg_handle = OSPF_PROC_COMM_GetOspfTGHandle();

    /* orginal OSPF task */
  
    OSPF_INIT_Create_Tasks(tg_handle);

    /* Create Thread to handle the MGR message */
    if(SYSFUN_SpawnThread(SYS_BLD_OSPF_GROUP_MGR_THREAD_PRIORITY,
                          SYS_BLD_OSPF_GROUP_MGR_SCHED_POLICY,
                          SYS_BLD_OSPF_GROUP_MGR_THREAD_NAME,
                          SYS_BLD_TASK_COMMON_STACK_SIZE,
                          SYSFUN_TASK_FP,
                          OSPF_GROUP_Mgr_Thread_Function_Entry,
                          NULL, &thread_id)!=SYSFUN_OK)
    {
        printf("%s:Spawn CSCGroup2 MGR thread fail.\n", __FUNCTION__);
    }

}

#if (SYS_CPNT_UNIT_HOT_SWAP == TRUE)
/*------------------------------------------------------------------------------
 * ROUTINE NAME : OSPF_GROUP_HandleHotInertion
 *------------------------------------------------------------------------------
 * PURPOSE:
 *    This function will invoke a new dut insertion in CSCGroup1.
 *
 * INPUT:
 *    starting_port_ifindex.
      number_of_port
      use_default
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
static void OSPF_GROUP_HandleHotInertion(SYSFUN_Msg_T* msgbuf_p)
{
 SYS_TYPE_HandleHotSwapArg_T *msg_p;

 if (msgbuf_p == NULL)
    return;

    msg_p = (SYS_TYPE_HandleHotSwapArg_T*)msgbuf_p->msg_buf;

  
}

/*------------------------------------------------------------------------------
 * ROUTINE NAME : OSPF_GROUP_HandleHotRemoval
 *------------------------------------------------------------------------------
 * PURPOSE:
 *    This function will invoke a  dut removal in CSCGroup1.
 *
 * INPUT:
 *    starting_port_ifindex.
      number_of_port
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
static void OSPF_GROUP_HandleHotRemoval(SYSFUN_Msg_T* msgbuf_p)
{
 SYS_TYPE_HandleHotSwapArg_T *msg_p;

 if (msgbuf_p == NULL)
    return;

    msg_p = (SYS_TYPE_HandleHotSwapArg_T*)msgbuf_p->msg_buf; 
}
#endif


