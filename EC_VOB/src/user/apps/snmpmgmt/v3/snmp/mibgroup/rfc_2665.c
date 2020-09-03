/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.old-api.conf,v 1.2 2002/07/18 15:37:37 dts12 Exp $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "rfc_2665.h"
#include "sysORTable.h"
#include "nmtr_mgr.h"
#include "nmtr_pmgr.h"
#include "swdrv_type.h"
#include "sys_type.h"
#include "snmp_mgr.h"

/*
 * dot3StatsTable_variables_oid:
 *   this is the top level oid that we want to register under.  This
 *   is essentially a prefix, with the suffix appearing in the
 *   variable below.
 */

oid etherLike_module_oid[] = { SNMP_OID_MIB2, 10, 7 };
oid dot3StatsTable_variables_oid[] = { 1,3,6,1,2,1,10,7};

/*
 * variable4 dot3StatsTable_variables:
 *   this variable defines function callbacks and type return information
 *   for the  mib section
 */

struct variable3  dot3StatsTable_variables[] = {
/*  magic number        , variable type , ro/rw , callback fn  , L, oidsuffix */

#define DOT3STATSINDEX		1
{DOT3STATSINDEX,  ASN_INTEGER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 1 }},
#define DOT3STATSALIGNMENTERRORS		2
{DOT3STATSALIGNMENTERRORS,  ASN_COUNTER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 2 }},
#define DOT3STATSFCSERRORS		3
{DOT3STATSFCSERRORS,  ASN_COUNTER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 3 }},
#define DOT3STATSSINGLECOLLISIONFRAMES		4
{DOT3STATSSINGLECOLLISIONFRAMES,  ASN_COUNTER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 4 }},
#define DOT3STATSMULTIPLECOLLISIONFRAMES		5
{DOT3STATSMULTIPLECOLLISIONFRAMES,  ASN_COUNTER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 5 }},
#define DOT3STATSSQETESTERRORS		6
{DOT3STATSSQETESTERRORS,  ASN_COUNTER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 6 }},
#define DOT3STATSDEFERREDTRANSMISSIONS		7
{DOT3STATSDEFERREDTRANSMISSIONS,  ASN_COUNTER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 7 }},
#define DOT3STATSLATECOLLISIONS		8
{DOT3STATSLATECOLLISIONS,  ASN_COUNTER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 8 }},
#define DOT3STATSEXCESSIVECOLLISIONS		9
{DOT3STATSEXCESSIVECOLLISIONS,  ASN_COUNTER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 9 }},
#define DOT3STATSINTERNALMACTRANSMITERRORS		10
{DOT3STATSINTERNALMACTRANSMITERRORS,  ASN_COUNTER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 10 }},
#define DOT3STATSCARRIERSENSEERRORS		11
{DOT3STATSCARRIERSENSEERRORS,  ASN_COUNTER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 11 }},
#define DOT3STATSFRAMETOOLONGS		12
{DOT3STATSFRAMETOOLONGS,  ASN_COUNTER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 13 }},
#define DOT3STATSINTERNALMACRECEIVEERRORS		13
{DOT3STATSINTERNALMACRECEIVEERRORS,  ASN_COUNTER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 16 }},
#define DOT3STATSETHERCHIPSET		14
{DOT3STATSETHERCHIPSET,  ASN_OBJECT_ID,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 17 }},
#define DOT3STATSSYMBOLERRORS		15
{DOT3STATSSYMBOLERRORS,  ASN_COUNTER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 18 }},
#define DOT3STATSDUPLEXSTATUS		16
{DOT3STATSDUPLEXSTATUS,  ASN_INTEGER,  RONLY,   var_dot3StatsTable, 3,  { 2, 1, 19 }},
};
/*    (L = length of the oidsuffix) */


/** Initializes the dot3StatsTable module */
void
init_dot3StatsTable(void)
{

    DEBUGMSGTL(("dot3StatsTable", "Initializing\n"));

    /* register ourselves with the agent to handle our mib tree */
    REGISTER_MIB("dot3StatsTable", dot3StatsTable_variables, variable3,
               dot3StatsTable_variables_oid);

    REGISTER_SYSOR_ENTRY(etherLike_module_oid,
                         "The EthernetLike MIB.");

    /* place any other initialization junk you need here */
}

#define dot3StatsEntry_INSTANCE_LEN 1
static int
header_dot3StatsTable(struct variable *vp,
               oid * name,
               size_t * length,
               int exact, size_t * var_len, WriteMethod ** write_method,UI32_T *ifindex)
{
    UI32_T      compc=0,ifindex1;
    oid         compl[dot3StatsEntry_INSTANCE_LEN];
    SWDRV_EtherlikeStats_T  entry;
    int         i;

    memset( &entry, 0, sizeof(entry));
    /*check compc, retrive compl*/
    SNMP_MGR_RetrieveCompl(vp->name, vp->namelen, name, *length, &compc,compl, dot3StatsEntry_INSTANCE_LEN);

    if (exact)/*get,set*/
    {
        if(compl[0]>0 && compl[0]<=SYS_ADPT_TOTAL_NBR_OF_LPORT)
        {
            *ifindex = compl[0];
            return 0;
        }
        return -1;
    }
    else/*getnext*/
    {
        if(compc == 0)
        {
            ifindex1 = 1;
        }
        else if(compl[0]>0 && compl[0]<SYS_ADPT_TOTAL_NBR_OF_LPORT)
        {
            ifindex1 = compl[0]+1;
        }
        else
            return -1;

        for (i = ifindex1;i <= SYS_ADPT_TOTAL_NBR_OF_LPORT; i++)
        {
            if (TRUE == NMTR_PMGR_GetEtherLikeStats(i,&entry))
            {
                *ifindex = i;
                return 0;
            }
        }
        return -1;
    }
}

/*
 * var_dot3StatsTable():
 *   Handle this table separately from the scalar value case.
 *   The workings of this are basically the same as for var_ above.
 */
unsigned char *
var_dot3StatsTable(struct variable *vp,
    	    oid     *name,
    	    size_t  *length,
    	    int     exact,
    	    size_t  *var_len,
    	    WriteMethod **write_method)
{
   SWDRV_EtherlikeStats_T  entry;
   oid best_inst[dot3StatsEntry_INSTANCE_LEN];
   UI32_T             interface = 0;

   memset( &entry, 0, sizeof(entry));

   if(MATCH_FAILED == header_dot3StatsTable(vp, name, length, exact, var_len, write_method,&interface))
   {
       return NULL;
   }

   if (NMTR_PMGR_GetEtherLikeStats( interface, &entry)!= TRUE)
   {
        return NULL;
   }

    memcpy(name, vp->name, vp->namelen*sizeof(oid));
    best_inst[0] = interface;
    memcpy(name + vp->namelen, best_inst, dot3StatsEntry_INSTANCE_LEN*sizeof(oid));
    *length = vp->namelen + dot3StatsEntry_INSTANCE_LEN;
    *var_len = sizeof(long);    /* default to 'long' results */
    /*
   * this is where we do the value assignments for the mib results.
   */
    switch(vp->magic) {
    case DOT3STATSINDEX:
          long_return = interface;
          return (u_char*) &long_return;
    case DOT3STATSALIGNMENTERRORS:
         long_return = entry.dot3StatsAlignmentErrors;
          return (u_char*) &long_return;
    case DOT3STATSFCSERRORS:
        long_return = entry.dot3StatsFCSErrors;
          return (u_char*) &long_return;
    case DOT3STATSSINGLECOLLISIONFRAMES:
         long_return = entry.dot3StatsSingleCollisionFrames;
          return (u_char*) &long_return;
    case DOT3STATSMULTIPLECOLLISIONFRAMES:
         long_return = entry.dot3StatsMultipleCollisionFrames;
          return (u_char*) &long_return;
    case DOT3STATSSQETESTERRORS:
        long_return = entry.dot3StatsSQETestErrors;
          return (u_char*) &long_return;
    case DOT3STATSDEFERREDTRANSMISSIONS:
         long_return = entry.dot3StatsDeferredTransmissions;
          return (u_char*) &long_return;
    case DOT3STATSLATECOLLISIONS:
         long_return = entry.dot3StatsLateCollisions;
          return (u_char*) &long_return;
    case DOT3STATSEXCESSIVECOLLISIONS:
         long_return = entry.dot3StatsExcessiveCollisions;
          return (u_char*) &long_return;
    case DOT3STATSINTERNALMACTRANSMITERRORS:
         long_return = entry.dot3StatsInternalMacTransmitErrors;
          return (u_char*) &long_return;
    case DOT3STATSCARRIERSENSEERRORS:
         long_return = entry.dot3StatsCarrierSenseErrors;
          return (u_char*) &long_return;
    case DOT3STATSFRAMETOOLONGS:
        long_return = entry.dot3StatsFrameTooLongs;
          return (u_char*) &long_return;
   case  DOT3STATSINTERNALMACRECEIVEERRORS:
         long_return = entry.dot3StatsInternalMacReceiveErrors;
          return (u_char*) &long_return;
    case DOT3STATSETHERCHIPSET:
         *var_len = 2* sizeof( oid);
          return (u_char*) &nullOid;
    case DOT3STATSSYMBOLERRORS:
         long_return = entry.dot3StatsSymbolErrors;
          return (u_char*) &long_return;
    case DOT3STATSDUPLEXSTATUS:
         long_return = entry.dot3StatsDuplexStatus;
          return (u_char*) &long_return;
    default:
      ERROR_MSG("");
    }
    return NULL;
}
