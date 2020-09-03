/******************************************************************************
 ******************************************************************************
 **** This file was automatically generated by Epilogue Technology's
 **** Emissary SNMP MIB Compiler, version 6.3.
 **** This file was generated using the -leaf switch.
 **** 
 **** This file #defines C preprocessor macros providing a variety of
 **** information for the leaf objects in the MIB.
 **** 
 **** The file includes a LEAF_xxx macro for each leaf object in the
 **** MIB (xxx is replaced by the object's name).  The value of the
 **** LEAF_xxx macro is the final component of the object's object
 **** identifier.
 **** 
 **** If the object's SYNTAX clause included named INTEGER values,
 **** then there is a VAL_xxx_yyy macro for each named value (xxx is
 **** replaced by the object's name and yyy by the value's name).  The
 **** value of the VAL_xxx_yyy macro is the value associated with the
 **** named value.
 **** 
 **** If the object's SYNTAX clause specified a set of range limitations
 **** for the value of the object, then there are one or more sets of
 **** MIN_xxx and MAX_xxx macros specifying the lower and upper bound of
 **** each range limitation.
 **** 
 **** If the object's SYNTAX clause specified a set of size constraints
 **** for the value of the object, then there are one or more sets of
 **** MINSIZE_xxx and MAXSIZE_xxx macros specifying the lower and upper
 **** bound of each size constraint.  (If the size constraint is a single
 **** value rather than a range then the MINSIZE_xxx and MAXSIZE_xxx
 **** macros are replaced by a single SIZE_xxx macro.)
 **** 
 **** DO NOT MODIFY THIS FILE BY HAND.
 **** 
 **** Last build date: Thu Jun 19 12:18:01 2003
 **** from files:
 ****  ..\MibFiles\SnmpFramework_Rfc3411.mib, ctl\SnmpFramework_Rfc3411.ctl,
 ****  ..\MibFiles\SnmpViewBaseAcm_Rfc3415.mib
 ******************************************************************************
 ******************************************************************************
 */
#ifndef  LEAF_3415_H
#define  LEAF_3415_H

#define LEAF_vacmContextName	1
#define MINSIZE_vacmContextName	0L
#define MAXSIZE_vacmContextName	32L
#define LEAF_vacmSecurityModel	1
#define MIN_vacmSecurityModel	1L
#define MAX_vacmSecurityModel	2147483647L
#define LEAF_vacmSecurityName	2
#define MINSIZE_vacmSecurityName	1L
#define MAXSIZE_vacmSecurityName	32L
#define LEAF_vacmGroupName	3
#define MINSIZE_vacmGroupName	1L
#define MAXSIZE_vacmGroupName	32L
#define LEAF_vacmSecurityToGroupStorageType	4
#define VAL_vacmSecurityToGroupStorageType_other	1L
#define VAL_vacmSecurityToGroupStorageType_volatile	2L
#define VAL_vacmSecurityToGroupStorageType_nonVolatile	3L
#define VAL_vacmSecurityToGroupStorageType_permanent	4L
#define VAL_vacmSecurityToGroupStorageType_readOnly	5L
#define LEAF_vacmSecurityToGroupStatus	5
#define VAL_vacmSecurityToGroupStatus_active	1L
#define VAL_vacmSecurityToGroupStatus_notInService	2L
#define VAL_vacmSecurityToGroupStatus_notReady	3L
#define VAL_vacmSecurityToGroupStatus_createAndGo	4L
#define VAL_vacmSecurityToGroupStatus_createAndWait	5L
#define VAL_vacmSecurityToGroupStatus_destroy	6L
#define LEAF_vacmAccessContextPrefix	1
#define MINSIZE_vacmAccessContextPrefix	0L
#define MAXSIZE_vacmAccessContextPrefix	32L
#define LEAF_vacmAccessSecurityModel	2
#define MIN_vacmAccessSecurityModel	0L
#define MAX_vacmAccessSecurityModel	2147483647L
#define LEAF_vacmAccessSecurityLevel	3
#define VAL_vacmAccessSecurityLevel_noAuthNoPriv	1L
#define VAL_vacmAccessSecurityLevel_authNoPriv	2L
#define VAL_vacmAccessSecurityLevel_authPriv	3L
#define LEAF_vacmAccessContextMatch	4
#define VAL_vacmAccessContextMatch_exact	1L
#define VAL_vacmAccessContextMatch_prefix	2L
#define LEAF_vacmAccessReadViewName	5
#define MINSIZE_vacmAccessReadViewName	0L
#define MAXSIZE_vacmAccessReadViewName	32L
#define LEAF_vacmAccessWriteViewName	6
#define MINSIZE_vacmAccessWriteViewName	0L
#define MAXSIZE_vacmAccessWriteViewName	32L
#define LEAF_vacmAccessNotifyViewName	7
#define MINSIZE_vacmAccessNotifyViewName	0L
#define MAXSIZE_vacmAccessNotifyViewName	32L
#define LEAF_vacmAccessStorageType	8
#define VAL_vacmAccessStorageType_other	1L
#define VAL_vacmAccessStorageType_volatile	2L
#define VAL_vacmAccessStorageType_nonVolatile	3L
#define VAL_vacmAccessStorageType_permanent	4L
#define VAL_vacmAccessStorageType_readOnly	5L
#define LEAF_vacmAccessStatus	9
#define VAL_vacmAccessStatus_active	1L
#define VAL_vacmAccessStatus_notInService	2L
#define VAL_vacmAccessStatus_notReady	3L
#define VAL_vacmAccessStatus_createAndGo	4L
#define VAL_vacmAccessStatus_createAndWait	5L
#define VAL_vacmAccessStatus_destroy	6L
#define LEAF_vacmViewSpinLock	1
#define MIN_vacmViewSpinLock	0L
#define MAX_vacmViewSpinLock	2147483647L
#define LEAF_vacmViewTreeFamilyViewName	1
#define MINSIZE_vacmViewTreeFamilyViewName	1L
#define MAXSIZE_vacmViewTreeFamilyViewName	32L
#define LEAF_vacmViewTreeFamilySubtree	2
#define LEAF_vacmViewTreeFamilyMask	3
#define MINSIZE_vacmViewTreeFamilyMask	0L
#define MAXSIZE_vacmViewTreeFamilyMask	16L
#define LEAF_vacmViewTreeFamilyType	4
#define VAL_vacmViewTreeFamilyType_included	1L
#define VAL_vacmViewTreeFamilyType_excluded	2L
#define LEAF_vacmViewTreeFamilyStorageType	5
#define VAL_vacmViewTreeFamilyStorageType_other	1L
#define VAL_vacmViewTreeFamilyStorageType_volatile	2L
#define VAL_vacmViewTreeFamilyStorageType_nonVolatile	3L
#define VAL_vacmViewTreeFamilyStorageType_permanent	4L
#define VAL_vacmViewTreeFamilyStorageType_readOnly	5L
#define LEAF_vacmViewTreeFamilyStatus	6
#define VAL_vacmViewTreeFamilyStatus_active	1L
#define VAL_vacmViewTreeFamilyStatus_notInService	2L
#define VAL_vacmViewTreeFamilyStatus_notReady	3L
#define VAL_vacmViewTreeFamilyStatus_createAndGo	4L
#define VAL_vacmViewTreeFamilyStatus_createAndWait	5L
#define VAL_vacmViewTreeFamilyStatus_destroy	6L

#endif /* end of #ifndef  LEAF_3415_H */
