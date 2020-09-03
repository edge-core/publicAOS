/*--------------------------------------------------------------------------
 * Module Name: eh_type.h
 *--------------------------------------------------------------------------
 * PURPOSE: Type declartion and definitions for EH(Error Handler).
 *--------------------------------------------------------------------------
 * NOTES:
 * Terminology:
 *     UI Message Number   -   A number that is able to be displayed with a
 *                             specific error message when an UI operation
 *                             failed. End users may look up the user manual by
 *                             the UI Message Number to get detailed
 *                             description for the error.
 *
 *     UI Message ID       -   In context of C source code, UI Message ID is
 *                             a constant name, which can be passed to
 *                             EH_MGR_Handle_Exception() to set error message.
 *                             In UI Message Data file(eh_msg.xml) in XML format
 *                             , UI Message ID represents an entity name
 *                             embraced by tag "UI_Msg_No". The real value of
 *                             the entity will be defined in eh_ui_msg_no.dtd
 *                             ,which will be referenced by eh_msg.xml.
 *                             The final eh_msg.xml to be copied to rootfs needs
 *                             to be processed by XML utility to replace these
 *                             entity name with real value. The command shown
 *                             below can have this done.
 *                             xmllint --loaddtd --noent eh_msg_rootfs.xml
 *
 *
 * In order to keep the integrity between the UI Message ID used in C source
 * code and the UI message defined in UI Message data file, the constant
 * name of UI Message ID and its represented value after interpreted by C
 * pre-processor in eh_ui_msg_no.h must be exactly the same with the definition
 * in eh_ui_msg_no.dtd.
 *--------------------------------------------------------------------------
 * HISTORY:
 *      Date        -- Modifier,        Reason
 *      2003.03.11  -- Unknown          Generated by the UIMSG Converter.
 *      2013.02.04  -- Charlie Chen     Porting from Vxworks to Linux. Refine
 *                                      the design and add support for display
 *                                      of multiple language and encoding.
 *                                      Change the design for allocation of UI
 *                                      Message ID(number) for each CSC.
 *--------------------------------------------------------------------------
 * Copyright(C)                               Accton Corporation, 2002
 * Copyright(C)                               EdgeCore Newtorks,  2013
 *--------------------------------------------------------------------------
 */
#ifndef EH_TYPE_H
#define EH_TYPE_H

/* INCLUDE FILE DECLARATIONS
 */
#include <wchar.h>
#include "sys_module.h"
#include "sys_type.h"
#include "eh_ui_msg_no.h"

/* NAMING CONSTANT DECLARATIONS
 */

#define EH_TYPE_LANG_ID(id, name)       id,
#define EH_TYPE_LANG_TAG_NAME(id, name) name,

/* enumeration of supported language in EH
 * Column 1 data: enum name of a specific language
 * Column 2 data: tag name for a specific language in error message XML file 
 */
#define EH_TYPE_LANG_LIST(_) \
    _(EH_TYPE_LANGUAGE_EN_EN,    "en-EN")  /* English */                       \
    _(EH_TYPE_LANGUAGE_ZH_CN,    "zh-CN")  /* Simplified Chinese */            \
    _(EH_TYPE_LANGUAGE_ZH_TW,    "zh-TW")  /* Traditional Chinese */           \
    _(EH_TYPE_LANGUAGE_MAX_NUM,  "Invalid")/* Must be placed in the last enum */

typedef enum
{
    EH_TYPE_LANG_LIST(EH_TYPE_LANG_ID)
} EH_TYPE_LANGUAGE_T;

#define EH_TYPE_ENCODING_ID(id, name)     id,
#define EH_TYPE_ENCODING_NAME(id, name)   name,

/* enumeration of supported character encoding in EH
 * Column 1 data: enum name of a specific encoding
 * Column 2 data: encoding name defined in iconv
 * NOTE!!! Please keep unicode type encoding in continuous sequence in the same
 *         section, and keep multi byte type encoding in continuous sequence in
 *         the other section.
 */
#define EH_TYPE_ENCODING_LIST(_) \
    _(EH_TYPE_ENCODING_UTF_8,     "UTF8")      /* Unicode encoding with UTF-8 */                                \
    _(EH_TYPE_ENCODING_UTF_16_BE, "UTF16BE")   /* Unicode encoding with UTF-16 Big Endian */                    \
    _(EH_TYPE_ENCODING_UTF_16_LE, "UTF16LE")   /* Unicode encoding with UTF-16 Little Endian */                 \
    _(EH_TYPE_ENCODING_UTF_32_BE, "UTF32BE")   /* Unicode encoding with UTF-32 Big Endian */                    \
    _(EH_TYPE_ENCODING_UTF_32_LE, "UTF32LE")   /* Unicode encoding with UTF-32 Little Endian */                 \
    _(EH_TYPE_ENCODING_WCHAR_T,   "WCHAR_T")   /* System dependent encoding for handling unicode charset */     \
    _(EH_TYPE_ENCODING_ISO_8859_1,"ISO8859-1") /* Multi byte encoding with ISO-8859-1(Latin alphabet part 1) */ \
    _(EH_TYPE_ENCODING_BIG5,      "BIG5")      /* Multi byte encoding with BIG5 for traditional Chinese */      \
    _(EH_TYPE_ENCODING_GB_2312,   "GB2312")    /* Multi byte encoding with GB-2312 for simplified Chinesee */   \
    _(EH_TYPE_ENCODING_MAX_NUM,   "Invalid")   /* Must be placed in the last enum */

typedef enum
{
  EH_TYPE_ENCODING_LIST(EH_TYPE_ENCODING_ID)
} EH_TYPE_ENCODING_T;

/* enumeration of return value in EH
 */
typedef enum
{
    EH_TYPE_RET_OK,                  /* operation is performed successfully */
    EH_TYPE_RET_NO_ERR_MSG,          /* No error message exists in the EH Message Buffer */
    EH_TYPE_RET_NO_BOUND_EH_MSG_BUF, /* Cannot find the bounded EH Message Buffer */
    EH_TYPE_RET_INVALID_INPUT_ARG,   /* Invalid input argument */
    EH_TYPE_RET_NOT_SUPPORT,         /* Not support the requested operation */
    EH_TYPE_RET_SET_OM_FAILED,       /* failed to set OM */
    EH_TYPE_RET_INVALID_UI_MSG_NO,   /* Invalid UI Message Number */
    EH_TYPE_RET_GENERATE_MSG_ERROR,  /* error occurs when generates the error message */
    EH_TYPE_RET_OUT_OF_MEMORY,       /* error caused by out of memory */
    EH_TYPE_RET_INTERNAL_DATA_ERROR, /* error due to internal data error, e.g. error message xml file */
    EH_TYPE_RET_CHAR_ENCODING_CONVERT_ERROR, /* error due to char encoding convert */
} EH_TYPE_RET_T;

/* for trace_id of user_id when allocate buffer with l_mm
 */
enum
{
    EH_TYPE_TRACE_ID_EH_MGR_GENERATE_MSG1 = 0,
    EH_TYPE_TRACE_ID_EH_MGR_GENERATE_MSG2,
    EH_TYPE_TRACE_ID_EH_MGR_GENERATE_MSG3,
};

/* Maximum number of allocated UI Message ID for a CSC
 */
#define EH_TYPE_MAX_NUMBER_OF_UI_MSG_ID_FOR_ONE_CSC 1000

/* The maximum number of argument allowed for a UI Error Message is 3. The
 * requirement for passing over 3 arguments needs to be reviewed by SA.
 * NOTE!!! Remember to update the arguments in function call to swprintf()
 *         in function EH_MGR_GenerateMsg() when
 *         EH_TYPE_MAX_NUMBER_OF_ARG_FOR_UI_MSG is changed.
 */
#define EH_TYPE_MAX_NUMBER_OF_ARG_FOR_UI_MSG 3

/* Invalid value of UI message number
 */
#define EH_TYPE_INVALID_UI_MSG_NO 0xFFFFFFFFUL

/* Invalid value for EH_OM_ErrorMsgEntry_T.xml_msg_buf_p
 */
#define EH_TYPE_INVALID_XML_BUFFER_PTR 0xFFFFFFFFUL

/* MACRO FUNCTION DECLARATIONS
 */
/* Get the minimum UI Message ID for the specified sys_module_id
 * The UI Message ID allocation range for a CSC is shown below:
 * Minimum ID:(sys_module_id*EH_TYPE_MAX_NUMBER_OF_UI_MSG_ID_FOR_ONE_CSC)
 * Maximum ID:(((sys_module_id+1)*EH_TYPE_MAX_NUMBER_OF_UI_MSG_ID_FOR_ONE_CSC)-1)  
 */
#define EH_TYPE_GET_CSC_UI_MSG_ID_MIN(sys_module_id) (sys_module_id*EH_TYPE_MAX_NUMBER_OF_UI_MSG_ID_FOR_ONE_CSC)

/* Get the maximum UI Message Number for the specified sys_module_id
 */
#define EH_TYPE_GET_CSC_UI_MSG_ID_MAX(sys_module_id) (((sys_module_id+1)*EH_TYPE_MAX_NUMBER_OF_UI_MSG_ID_FOR_ONE_CSC)-1)

/* DATA TYPE DECLARATIONS
 */
typedef UI32_T EH_TYPE_UIMsgNumber_T;

typedef struct EH_TYPE_OutputMessage_S
{
    char* msg_p; /* output message in spcified encoding */
    EH_TYPE_ENCODING_T encoding;
} EH_TYPE_OutputMessage_T;

/* This function pointer type is referenced by EH_MGR_Process_Error_Info().
 * INPUT arguments:
 *     cookie      -- The argument passed to EH_MGR_Process_Error_Info().
 *     output_msg_p--
 *                    msg.multi_byte_msg_p: Pointer to the output error message
 *                                          of multi byte string.
 *                    msg.unicode_msg_p   : Pointer to the output error message
 *                                          of unicode_msg_p.
 *                    encoding            : Encoding of the msg.
 */
typedef void (*EH_TYPE_OutputMessageFunction_T)(void* cookie, EH_TYPE_OutputMessage_T *output_msg_p);

/* EXPORTED SUBPROGRAM SPECIFICATIONS
 */

#endif/* #ifndef EH_TYPE_H */
