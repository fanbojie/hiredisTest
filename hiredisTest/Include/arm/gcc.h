/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  GCC.H                                                                   */
/*                                                                          */
/*  Version 1.0(01/10/2002 based on IMTC GCC API specificaiton 0.13)        */
/*                                                                          */
/*  History                                                                 */
/*      01/10/2002     created by Jack Feng                                 */
/*      05/21/2002     modified by Jack Feng                                */
/*                     . expose parameter support API out                   */
/*                     . modify flowcontrol API to support priority         */
/*                     . add cache optimization API                         */
/*                                                                          */
/*  Copyright (C) 2002 by WebEx Communications Inc.                         */
/*  All rights reserved                                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#if !defined(__GCC_H__)
#define __GCC_H__

#include "platform.h"
#include "wbxconfid.h"
class GCC_Conference_Pdu2;
//////////////////////////////////////////////////////////////////////////////
// MCS define
//
#if !defined(__MCS_H__)
typedef uint32       MCS_User_ID;
typedef uint32       MCS_Channel_ID;
typedef uint16       MCS_Token_ID;
typedef uint32       MCS_Node_ID;

typedef uint8        MCS_Node_Type;
#define MCS_TERMINAL 0
#define MCS_MCU      1

typedef uint16       MCS_Priority;
#define MAX_NUM_PRIORITY     4
#define MCS_TOP_PRIORITY     0
#define MCS_HIGH_PRIORITY    1
#define MCS_MEDIUM_PRIORITY  2
#define MCS_LOW_PRIORITY     3

//cache_ex enhancement,kelvin 2007-12-27
#ifndef MCS_UNSPECIFIED_PRIORITY
#define MCS_UNSPECIFIED_PRIORITY 0xff
#endif

typedef uint8        MCS_Flow_Control_Alarm_Status;
#define MCS_FLOW_CONTROL_ALARM_GREEN    0
#define MCS_FLOW_CONTROL_ALARM_YELLOW   1
#define MCS_FLOW_CONTROL_ALARM_RED      2

#if !defined(uint64)
typedef  unsigned long long uint64;
#endif

typedef struct
{
    uint32  length;
    uint8*  data;
} MCS_User_Data;

#endif //__MCS_H__


typedef enum
{
	H264_DATA_TYPE_UNKNOWN = 0,
	H264_DATA_TYPE_KEY_FRAME = 1,
	H264_DATA_TYPE_NORMAL_FRAME,	
}H264_DATA_TYPE;

typedef enum
{
	H264_COMMAND_UNKNOWN = 0,
	H264_COMMAND_KEY_FRAME_REQUEST,
	H264_COMMAND_CHANGE_ENCODE_FPS,
	H264_COMMAND_CTMS_BANDWIDTH,      // CTMS represent Cisco old telepresence
	H264_COMMAND_TBG_BANDWIDTH,		  // TBG represent TANDBERG
	H264_COMMAND_TBG_MAXFS,
}H264_COMMAND_TYPE;


//////////////////////////////////////////////////////////////////////////////
// Transport_Address
// Format: protocol_type://host_ip:port
// protocol_type can be "tcp", "http", "https" ...
typedef char* Transport_Address;

//////////////////////////////////////////////////////////////////////////////
// GCC defines
//
#define GCC_MAX_PDU_DATA_SIZE 65535
#define GCC_MAX_SVR_NAME_LENGTH 256
#define GCC_MAX_SVR_TYPE_LENGTH 256
#define GCC_MAX_SVR_IPADDRPORT_LENGTH 256
#define GCC_MAX_PROXY_LENGTH 256

#define GCC_MAX_TRANSPORT_ADDR_LENGTH 64
#define GCC_MAX_CONF_NAME_LENGTH 512
#define GCC_MAX_CONF_KEY_LENGTH 32

#define GCC_MAX_CONF_PASSWORD_LENGTH 256
#define GCC_MAX_CONF_USER_PASSWORD_LENGTH 128
#define GCC_MAX_CONF_USER_NAME_LENGTH 256
#define GCC_MAX_RSC_ID_LENGTH 64
#define GCC_MAX_P2P_ID_LENGTH 16
#define GCC_MAX_NODE_INFO_LENGTH 512  //256,change for unicode support,kelvin 2008-3-6
#define GCC_MAX_APE_INFO_LENGTH  4096 //256
#define GCC_MAX_RESOURCE_NUM     256
#define GCC_MAX_USER_DATA_LENGTH 1024
#define GCC_MAX_CONF_USER_DATA_LENGTH 4096
#define GCC_MAX_SESSION_USER_DATA_LENGTH 16384	//4096
#define GCC_MAX_CONF_MSG_LENGTH 4096
#define GCC_MAX_ROSTER_UPDATE_RECORD_NUM 512

#define GCC_MAX_DOMAIN_NAME_LENGTH	256
#define GCC_MAX_ZONE_NAME_LENGTH	256
#define GCC_MAX_MACC_ADDR_LENGTH	256
#define GCC_MAX_CB_ADDR_LENGTH	256

typedef MCS_User_ID   GCC_Node_ID;
typedef MCS_User_ID   GCC_APE_ID;
typedef uint16        GCC_App_Protocol_Type;

//////////////////////////////////////////////////////////////////////////////
// GCC_Node_Type
//      ------------------------------------
//      | MCS_Node_Type    | GCC_NODE_TYPE |
//      ------------------------------------
//      | OS_Type          | Browser_Type  |
//      ------------------------------------
//      |                  |               |
//      ------------------------------------
//      |                  |               |
//      ------------------------------------
//
typedef uint32        GCC_Node_Type;

#define MASK_MCS_NODE_TYPE     0x000f

#define MASK_GCC_NODE_TYPE     0x00f0
#define GCC_NODE_CLIENT        0x00
#define GCC_NODE_APPSVR        0x10
#define GCC_NODE_TOP_MCU       0x20
#define GCC_NODE_SUB_MCU       0x30

#define MASK_OS_TYPE           0x0f00
#define GCC_OS_WIN32           0x000
#define GCC_OS_MAC             0x100
#define GCC_OS_SOLARIS         0x200
#define GCC_OS_JAVA            0x300
#define GCC_OS_LINUX           0x400
#define GCC_OS_FLASH           0x500
#define GCC_OS_JAVASCRIPT      0x600
#define GCC_OS_IPHONE          0x700 //7.  platform=iphone
#define GCC_OS_MOBILE          0x800 //8.  platform=mobile web solution via MBGW
#define GCC_OS_IP_PHONE        0x900 //9.  platform=IP Phone
#define GCC_OS_CISCOTP         0xa00 //10. platform=Telepresence device
#define GCC_OS_BB              0xb00 //11. platform=blackberry
#define GCC_OS_WM              0xc00 //12. platform=winmobile
#define GCC_OS_ANDROID         0xd00 //13. Platform=Android,browser=null
#define GCC_OS_SYMBIAN         0xe00 //14. Platform=Nokia/Symbian,browser=null
#define GCC_OS_RESERVE         0xf00 //15. Reserve for expand more platform types in future


#define MASK_BROWSER_TYPE		0xf000
#define GCC_CONSOLE				0x0000
#define GCC_BROWSER_NETSCAPE	0x1000
#define GCC_BROWSER_IE			0x2000
#define GCC_BROWSER_MOZILLA		0x3000
#define GCC_BROWSER_FIREFOX		0x4000
#define GCC_BROWSER_SAFARI		0x5000
#define GCC_BROWSER_CHROME		0x6000

#define MASK_PRIVILEGE			0xf0000
#define GCC_CAN_NOT_BE_HOST		0x10000
#define GCC_CAN_NOT_BE_PRESENTER  0x20000

#define GCC_INTERNAL_CLIENT		0x40000	// for EMX

#define GCC_LOCK_DOWN_NODE		0x80000

#define GCC_SDK_JAVA			0x100000
#define GCC_SDK_NATIVE			0x0

#define GCC_DOWNLOAD_JAVA		0x200000
#define GCC_DOWNLOAD_ACTIVEX	0x0

#define GCC_RUN_STANDALONE		0x400000
#define GCC_RUN_PLUGIN			0x0

#define MASK_GCC_SUB_NODE_TYPE 0x0f000000
#define GCC_NODE_CLIENT_GW_V 0x01000000
#define GCC_NODE_CLIENT_GW_R 0x02000000
#define GCC_NODE_CLIENT_TP_PLUS 0x3000000
#define GCC_NODE_CLIENT_TP_VMR 0x04000000

//////////////////////////////////////////////////////////////////////////////
// GCC Error Code
//
typedef int32 GCC_Error;
const GCC_Error GCC_ERROR_NOERR                       = 0;
const GCC_Error GCC_ERROR_NOT_PROVIDED                = 27;
const GCC_Error GCC_ERROR_ALREADY_REGISTERED          = 28;
const GCC_Error GCC_ERROR_CALLBACK_NOT_PROCESSED      = 29;
const GCC_Error GCC_ERROR_CONFERENCE_ALREADY_EXISTS   = 30;
const GCC_Error GCC_ERROR_FUNCTION_NOT_SUPPORTED      = 31;
const GCC_Error GCC_ERROR_INVALID_PARAMETERS          = 32;
const GCC_Error GCC_ERROR_INVALID_CONFERENCE          = 33;
const GCC_Error GCC_ERROR_MESSAGE_BUFFER_SIZE_EXCEEDED = 34;
const GCC_Error GCC_ERROR_NOT_AUTHORISED              = 35;
const GCC_Error GCC_ERROR_NOT_REGISTERED              = 36;
const GCC_Error GCC_ERROR_RESOURCE_ERROR              = 37;
const GCC_Error GCC_ERROR_TRANSMIT_BUFFER_FULL        = 38;
const GCC_Error GCC_ERROR_UNKNOWN_ERROR               = 39;
const GCC_Error GCC_ERROR_USER_DATA_BUFFER_SIZE_EXCEEDED = 40;
const GCC_Error GCC_ERROR_VERSION_NOT_SUPPORTED       = 41;

const GCC_Error GCC_ERROR_NOT_INITIALIZED             = 42;
const GCC_Error GCC_ERROR_CONFERENCE_NOT_EXISTS       = 43;
const GCC_Error GCC_ERROR_CONFERENCE_DELETING         = 44;
const GCC_Error GCC_ERROR_INVALID_PDU                 = 46;
const GCC_Error GCC_ERROR_INVALID_RESPONSE_TAG        = 47;
const GCC_Error GCC_ERROR_INVALID_CONNECTION          = 48;
const GCC_Error GCC_ERROR_NO_MESSAGE_AVAILABLE        = 49;
const GCC_Error GCC_ERROR_CONFERENCE_NOT_ACTIVE       = 50;
const GCC_Error GCC_ERROR_SAP_NOT_ENROLLED            = 51;
const GCC_Error GCC_ERROR_CONFERENCE_NOT_LOCKED       = 52;
const GCC_Error GCC_ERROR_CONFERENCE_ALREADY_LOCKED   = 53;
const GCC_Error GCC_ERROR_USERIDTAG_ALREADY_IN_MAP    = 54;
const GCC_Error GCC_ERROR_USERIDTAG_NOT_IN_MAP        = 55;
const GCC_Error GCC_ERROR_USER_NOT_IN_MIB             = 56;
const GCC_Error GCC_ERROR_USER_ALREADY_IN_MIB         = 57;
const GCC_Error GCC_ERROR_INVALID_SESSION             = 58;
const GCC_Error GCC_ERROR_NO_CALLBACK                 = 59;
const GCC_Error GCC_ERROR_INVALID_REQUEST_CONFIRM_TAG = 60;
const GCC_Error GCC_ERROR_INVALID_SAP                 = 61;
const GCC_Error GCC_ERROR_INVALID_STATE               = 62;
const GCC_Error GCC_ERROR_INVALID_PARAMETER           = 63;

//Andrew, 2007-12-15, added for Cascading task
const GCC_Error GCC_ERROR_CREATE_CAS_CNTL_FAILED      = 80;

const GCC_Error GCC_ERROR_CREATE_CAS_CNTL_ERROR_BASE  = 200; 


#define ARM_Error GCC_Error

//////////////////////////////////////////////////////////////////////////////
// GCC Reason Codes
//
typedef uint16 GCC_Reason;
#define GCC_REASON_FLAG                     0x80
#define GCC_REASON_USER_INITIATED           0x80
#define GCC_REASON_NOT_PROVIDED             0x81
#define GCC_REASON_EJECTED_NODE             0x82
#define GCC_REASON_ERROR_TERMINATION        0x83
#define GCC_REASON_HIGHER_NODE_DISCONNECT   0x84
#define GCC_REASON_HIGHER_NODE_EJECTED      0x85
#define GCC_REASON_NO_MORE_PARTICIPANTS     0x86
#define GCC_REASON_NORMAL_TERMINATION       0x87
#define GCC_REASON_TIMED_CONF_TERMINATION   0x88
#define GCC_REASON_CONF_LICENSE_EXPIRE      0x89
#define GCC_REASON_CONF_LICENSE_TOO_MANY    0x8a
#define GCC_REASON_APP_SVR_DISCONN          0x8b
#define GCC_REASON_UNKNOWN                  0x8c
#define GCC_REASON_SPLIT_CONF_TERMINATION	0x8d
#define GCC_REASON_APP_SVR_CAPACITY_FULL	0x8e
#define GCC_REASON_APP_SVR_NOT_AVAILABLE	0x8f
#define GCC_REASON_APP_SVR_REDIRECT			0x90
#define GCC_REASON_HOST_LICENSE_EXCCEED		0x91
#define GCC_REASON_TP_MEETING_CLOSE		    0x92
#define GCC_REASON_CMR_MEETING_WBX_HOST_LEAVE   0x93


//<= Andrew+, 09/19/2005 15:45:37
// for LIC & PKI
#define GCC_RESULT_LIC_PKI_START							(0x8d+1)
#define GCC_RESULT_LIC_EXTEND_MAX							GCC_RESULT_LIC_PKI_START+1
#define GCC_RESULT_CERT_EXPIRED								GCC_RESULT_LIC_PKI_START+2
#define GCC_RESULT_CERT_NOT_TRASTY							GCC_RESULT_LIC_PKI_START+3
#define GCC_RESULT_HOST_CERT_EXPIRED						GCC_RESULT_LIC_PKI_START+4
#define GCC_RESULT_HOST_CERT_NOT_TRASTY						GCC_RESULT_LIC_PKI_START+5
#define GCC_RESULT_ATTENDEE_CERT_EXPIRED					GCC_RESULT_LIC_PKI_START+6
#define GCC_RESULT_ATTENDEE_CERT_NOT_TRASTY					GCC_RESULT_LIC_PKI_START+7
#define GCC_RESULT_CANNT_DESCRYPT							GCC_RESULT_LIC_PKI_START+8
#define GCC_RESULT_HOST_DENY_ATTENDEE						GCC_RESULT_LIC_PKI_START+9
#define GCC_RESULT_CB_DENY_ATTENDEE							GCC_RESULT_LIC_PKI_START+10

//{ 09/21/2005, added by Folki for PKI
#define GCC_RESULT_CANT_INIT_CRYPTO_LIB						GCC_RESULT_LIC_PKI_START+11
#define GCC_RESULT_CANT_ENCRYPT_CONF_KEY					GCC_RESULT_LIC_PKI_START+12
#define GCC_RESULT_CANT_DECRYPT_CONF_KEY					GCC_RESULT_LIC_PKI_START+13
#define GCC_RESULT_CANT_ENCRYPT_DATA						GCC_RESULT_LIC_PKI_START+14
#define GCC_RESULT_CANT_DECRYPT_DATA						GCC_RESULT_LIC_PKI_START+15
//}

//<= Andrew+, 09/22/2005 11:10:33
#define GCC_RESULT_PKI_HOST_TIMEOUT							GCC_RESULT_LIC_PKI_START+16
#define GCC_RESULT_LIC_CHECK_TIMEOUT						GCC_RESULT_LIC_PKI_START+17

#define GCC_RESULT_LIC_PKI_QUERY_FAIL						GCC_RESULT_LIC_PKI_START+18

//{ 09/23/2005, added by Folki for PKI
#define GCC_RESULT_NO_PKI_RESOURCE							GCC_RESULT_LIC_PKI_START+19
//}
#define GCC_RESULT_HOST_HAS_LEAVE							GCC_RESULT_LIC_PKI_START+20

//{ 09/27/2005, added by Folki for PKI
#define GCC_RESULT_CANT_CREATE_CONF_KEY					GCC_RESULT_LIC_PKI_START+21
//}

//{ 10/12/2005, added by folki
#define GCC_RESULT_BUFFER_NOT_ENOUGH						GCC_RESULT_LIC_PKI_START+22
//}

//{ 20060816, Folki+ for E2E encrypt
#define GCC_RESULT_CERT_GENERATE_FAILED					GCC_RESULT_LIC_PKI_START+23
//}

//kelvin,2006-11-22
#define GCC_RESULT_PKI_HOST_UNAVAILABLE                                 GCC_RESULT_LIC_PKI_START+24

//yardley 12092005, for license
#define  GCC_REASON_CONF_LICENSE_CHANGE             0x200

//yardley 02072006 for closing nbr session
#define GCC_REASON_NBR_LINK_FAIL                    0x201

//+Choice Eureka 3.8.1, Jan 25th, 2008
#define GCC_REASON_FORCE_FAILOVER                   0x202

#define GCC_REASON_HOST_KICKOFF    0x203


//////////////////////////////////////////////////////////////////////////////
// GCC Result Codes
//
typedef uint16 GCC_Result;

#define GCC_RESULT_SUCCESSFUL                   0
#define GCC_RESULT_NOT_PROVIDED					38
#define GCC_RESULT_ADDED_NODE_BUSY              1
#define GCC_RESULT_ALREADY_LOCKED               2
#define GCC_RESULT_ALREADY_UNLOCKED             3
#define GCC_RESULT_CHALLENGE_RESPONSE_REQUIRED  4
#define GCC_RESULT_CONNECTION_UNSUCCESSFUL      5
#define GCC_RESULT_DID_NOT_OWN_TOKEN            6
#define GCC_RESULT_DOMAIN_NOT_HIERARCHICAL      7
#define GCC_RESULT_DOMPARMS_UNACCEPTABLE        8
#define GCC_RESULT_ENTRY_NOT_FOUND              9
#define GCC_RESULT_ENTRY_DOES_NOT_EXIST         10
#define GCC_RESULT_FUNCTION_NOT_AVAILABLE       11
#define GCC_RESULT_GIVE_NOT_ACCEPTED            12
#define GCC_RESULT_INCONSISTENT_TYPE            13
#define GCC_RESULT_INDEX_ALREADY_EXISTS         14
#define GCC_RESULT_INDEX_ALREADY_OWNED          15
#define GCC_RESULT_INVALID_ADDING_MCU           16
#define GCC_RESULT_INVALID_CHALLENGE_RESPONSE   17
#define GCC_RESULT_INVALID_CONFERENCE           18
#define GCC_RESULT_INVALID_CONVENER_PASSWORD    19
#define GCC_RESULT_INVALID_NETWORK_ADDRESS      20
#define GCC_RESULT_INVALID_NETWORK_TYPE         21
#define GCC_RESULT_INVALID_PASSWORD             22
#define GCC_RESULT_INVALID_REQUESTER            23
#define GCC_RESULT_INVALID_USER                 24
#define GCC_RESULT_LOCKED_NOT_SUPPORTED         25
#define GCC_RESULT_LOWER_LAYER_DISCONNECT       26
#define GCC_RESULT_NAME_AND_MODIFIER_EXIST      27
#define GCC_RESULT_NETWORK_BUSY                 28
#define GCC_RESULT_NON_CONDUCTIBLE_CONFERENCE   29
#define GCC_RESULT_NOT_CONDUCTOR                30
#define GCC_RESULT_NOT_CONVENER_NODE            31
#define GCC_RESULT_NOT_IN_CONDUCTED_MODE        32
#define GCC_RESULT_NO_HANDLES_AVAILABLE         33
#define GCC_RESULT_NO_PORTS_AVAILABLE           34
#define GCC_RESULT_USERID_NOT_CHANGEABLE        35
#define GCC_RESULT_REGISTRY_FULL                36
#define GCC_RESULT_RESOURCES_UNAVAILABLE        37
#define GCC_RESULT_SYMMETRY_BROKEN              39
#define GCC_RESULT_TOKEN_ALREADY_OWNED          40
#define GCC_RESULT_TOO_MANY_HANDLES_REQUESTED   41
#define GCC_RESULT_USER_REJECTED                42
#define GCC_RESULT_CONGESTED                    43
#define GCC_RESULT_DOMAIN_DISCONNECTED          44
#define GCC_RESULT_NO_SUCH_DOMAIN               45
#define GCC_RESULT_PROVIDER_INITIATED           46
#define GCC_RESULT_UNSPECIFIED_FAILURE          47
#define GCC_RESULT_TOKEN_NOT_AVAILABLE          48
#define GCC_RESULT_TOO_MANY_TOKENS              49
#define GCC_RESULT_DOMAIN_MERGING               50
#define GCC_RESULT_NO_SUCH_USER                 51
#define GCC_RESULT_TIME_OUT                     52

#define GCC_RESULT_NOT_AUTHORIZED               100
#define GCC_RESULT_CONFERENCE_LOCKED            101
#define GCC_RESULT_TOO_MANY_ENTRIES             102

#define GCC_RESULT_APPSVR_UNAVAILABLE           103
#define GCC_RESULT_PING_APPSVR_FAILED           104
#define GCC_RESULT_PING_APPSVR_TIMEOUT          105
#define GCC_RESULT_INVOKE_APPSVR_FAILED         106
#define GCC_RESULT_INVOKE_APPSVR_TIMEOUT        107

//yardley for nbr
#define GCC_RESULT_NBR_SESSION_FAILED           108
#define GCC_RESULT_NBR_SESSION_ALREAD_EXIST     109
//end

//yardley for secure host key
#define GCC_RESULT_NOT_HOST_KEY_SEC_CONF		110
#define GCC_RESULT_NO_HOST_KEY					111
#define GCC_RESULT_HOSTKEY_NOT_AUTHORISED		112
//end

// andrew for chat server
#define GCC_RESULT_SESSION_NOT_EXIST		113
//end 

#define GCC_RESULT_CONFERENCE_UNAVAILABLE           114
#define GCC_RESULT_INVALID_PARAMETER           115

//COMERZHANG:REGID:2007:1011
#define GCC_RESULT_REG_ID_OK			120
#define GCC_RESULT_REG_ID_FAIL			121
#define GCC_RESULT_REG_ID_PEND		122
//COMERZHANG:REGID:2007:1011:end

//fix bug294400,kelvin 2008-6-20
#define GCC_RESULT_CONFERENCE_ALREADY_EXISTS  123

//for SPA, CB version compatibility check, kelvin 2008-11-12
#define GCC_RESULT_SVR_INCOMPATIBILE 124

//Henry add for unique session
#define GCC_RESULT_SESSION_ALREADY_EXIST		125
//end

#define GCC_RESULT_SESSION_JOIN_VERIFIED_FAIL		126

//////////////////////////////////////////////////////////////////////////////
// GCC_Config_Type
//
#define GCC_Config_Type_Secure_Flag				1
#define GCC_Config_Type_Session_Id				2
#define GCC_Config_Type_Connect_Type			3	// 0: TcpOnly, 1: HttpOnly, 2: Http & P2p,
#define GCC_Config_Type_Send_Msg_Uniform		4
#define GCC_Config_Type_Allocate_Handle			5	// DWORD*
#define GCC_Config_Type_Allocate_Handle_Async	6
#define GCC_Config_Type_APPREG_REQ           	7
#define GCC_Config_Type_Get_Cookie				8	// DWORD*
#define GCC_Config_Type_Get_Peer_Buffer_Size	9	// DWORD[MAX_NUM_PRIORITY]
#define GCC_Config_Type_Can_Send_Ds_Data        10
#define GCC_Config_Type_Set_Max_Throughput		11	// DWORD
#define GCC_Config_Type_Set_Proxy_User_Name		12	// char[GCC_MAX_PROXY_LENGTH]
#define GCC_Config_Type_Set_Proxy_Password		13	// char[GCC_MAX_PROXY_LENGTH]
#define GCC_Config_Type_Get_Proxy_Domain_REQ	14	// DWORD*
#define GCC_Config_Type_Get_Proxy_User_Name		15	// GCC_User_Data*, length=GCC_MAX_PROXY_LENGTH
#define GCC_Config_Type_Get_Proxy_Password		16	// GCC_User_Data*, length=GCC_MAX_PROXY_LENGTH
#define GCC_Config_Type_Get_Proxy_Realm			17	// GCC_User_Data*, length=GCC_MAX_PROXY_LENGTH

//{ 09/19/2005, added by Folki for PKI
// GCC_Provider_Config_Data.config_data must be a GCC_User_Data* pointer,
// and GCC_User_Data.data is just a pointer to conference key,app need
// allocate memory to save it
#define GCC_Config_Type_Get_Conference_Key		18 // GCC_Provider_Config_Data*
//}

//{ 10/10/2005, added by folki
#define GCC_Config_Type_Get_Conference_Type		19 // GCC_Provider_Config_Data*
//}

// budingc added at 10/28/2005 for file transfer of NBR2.
#define GCC_Config_Type_Get_Local_IP			20	// GCC_User_Data*, length=GCC_MAX_PROXY_LENGTH

#define GCC_Config_Type_Get_Proxy_Via			21	// GCC_User_Data*, length=GCC_MAX_PROXY_LENGTH

#define GCC_Config_Type_Set_Flag_Only_For_Create_Meeting	50
#define GCC_Config_Type_Set_Flag_Join_For_Create_Meeting	51
#define GCC_Config_Type_Get_Host_Passport						52

// 10/06/2008, Folki+ for SPA
#define GCC_Config_Type_Set_Xml_Param							53
#define GCC_Config_Type_Get_Buffered_Size					54

#define GCC_Ape_Config_Type_Get_Buffer_Size		101	// DWORD*

//<= Andrew+, 08/16/2005 16:14:25
// for NBR
typedef struct{
	uint32	conference_id;
	uint32  config_data;
}GCC_Provider_Config_Data;

//{ 07/16/2008,Connie for test tool
typedef struct{
	GCC_Node_ID dest_id;
	MCS_Priority priority;
}GCC_Provider_RTT_Calc_Req;
//}

#define GCC_Ape_Config_Type_Set_NBR_Record_Flag			102	// DWORD
#define GCC_Provider_Config_Type_Set_NBR_Record_Flag	GCC_Ape_Config_Type_Set_NBR_Record_Flag

//{ 09/19/2005, added by Folki for PKI
#define GCC_APE_Config_Type_PKI_All				103
#define GCC_APE_Config_Type_PKI_None			107
//}
//{ 02/15/2006, added by Folki for PKI
#define GCC_APE_Config_Type_PKI_Encrypt_This_Time				105
#define GCC_APE_Config_Type_PKI_Not_Encrypt_This_Time			106
//}

//<= Andrew+, 11/17/2005 10:12:22
#define GCC_Ape_Config_Type_Set_NBR_Record_Property   104

// 04/18/2006, Folki for host key security enhancement
#define GCC_Provider_Config_Type_Set_HostKey				108

// added by andrew for ST/AA log, 20060508
#define GCC_Provider_Config_Type_Set_TraceOutPath	110
#define GCC_Provider_Config_Type_Set_HoursPerFile	111	
#define GCC_Provider_Config_Type_Set_DaysTraceKeep	112	
#define GCC_Provider_Config_Type_Cleanup_Trace		113
#define GCC_Provider_Config_Type_Get_TraceFile_BuffSize		114
#define GCC_Provider_Config_Type_Get_TraceFiles		115
#define GCC_Provider_Config_Type_Set_TraceMode		116
//end

//{ 20061130, Folki+ for flow control
#define GCC_APE_Config_Type_ENABLE_FCN			120	// enable flow control notify
//}

//{ 06042007, Folki+ for distribute meeting
#define GCC_Provider_Config_Type_Get_Location_ID		121
#define GCC_Provider_Config_Type_Get_MMP_Location_ID	122
//}

//{ 09282007, Folki+ for eureka 3.8
#define GCC_Provider_Config_Type_Set_Ping_Flags		123		// GCC_Provider_Config_Data*
#define GCC_Provider_Config_Type_Get_Ping_Flags		124		// GCC_Provider_Config_Data*
#define GCC_Provider_Config_Type_Set_Parameters		125		// GCC_Provider_Config_Data*
//}

// for reset the NBR flag
#define GCC_Ape_Config_Type_Reset_NBR_Record_Flag	126

// 09/28/2008, Folki+ for SPA
#define GCC_Provider_Config_Type_Set_Xml_Parameters	127	// GCC_Provider_Config_Data*

#define GCC_Provider_Config_Type_Set_PAC_URL				128	// char*

//wallice11202007 add for sas
#define GCC_Provider_Config_Type_Start_Listen		130
#define GCC_APE_Config_Type_Set_Stream_Flag		131
#define GCC_Config_Type_CBRegApp_Cfm				132
//

// budingc 12/13/2006, for p2p.
#define GCC_Ape_Config_Type_Set_Send_Data_Type   150
#define GCC_Set_Send_Data_Type_Data_All_EX 1  // default value, all send_data_ex() are data
#define GCC_Set_Send_Data_Type_USE_Data_Once 2 // use GCC_Set_Send_Data_Type_Data_Once, config it one time before calling first send_data().
#define GCC_Set_Send_Data_Type_Data_Once 3 // config it before calling send_data() every time.
#define GCC_Set_Send_Data_Type_Control_Once 4 // default value if using GCC_Set_Send_Data_Type_Data_Once.

// budingc 10/07/2007, for p2p.
#define GCC_Provider_Config_Type_Set_P2P_Goby 151 // default value is (GCC_Set_P2P_BY_CB | GCC_Set_P2P_BY_P2P)
#define GCC_Set_P2P_APPS (1 << 0)
#define GCC_Set_P2P_AUDI (1 << 1)
#define GCC_Set_P2P_VIDE (1 << 2)
#define GCC_Set_P2P_ADVD (GCC_Set_P2P_AUDI | GCC_Set_P2P_VIDE)
#define GCC_Set_P2P_GOBY_CB (1 << 16)
#define GCC_Set_P2P_GOBY_P2P (1 << 17)
#define GCC_Set_P2P_GOBY_CB_OR_P2P (GCC_Set_P2P_GOBY_CB | GCC_Set_P2P_GOBY_P2P)

#define GCC_Provider_Config_Type_Start_P2P_Connnect 152 // CTpP2pConnOption*
#define GCC_Provider_Config_Type_Stop_P2P_Connnect 153 // CTpP2pConnOption*

//{ 07/16/2008 Connie for test tool
#define GCC_Provider_Config_Type_RTT_Calc_Request 154
//}

// budingc 9/11/2008, for attendee ack.
#define GCC_APE_Config_Type_Presenter_Enable_Sdin_Ack 155 // 1:enabled 0:disabled(default)
#define GCC_APE_Config_Type_Need_AS_PDU_Ack_For_This_Senddata 156 // uint32: pduid

#define GCC_CONF_FLAG_NEW_CRYPTOGRAPHIC		160 

enum{
	NBR_FLAG_BASE			= 0x01 << 0,
	NBR_FLAG_PRIVATE		= 0x01 << 1,
	NBR_FLAG_SERVER			= 0x01 << 2,
	NBR_FLAG_INDEX			= 0x01 << 3,
	NBR_FLAG_STATIC			= 0x01 << 4,
	NBR_FLAG_SERVER_ONLY	= 0x01 << 5,
	NBR_FLAG_DATA			= 0x01 << 6,

	NBR_FLAG_RECORD			= 0x01 << 7,
};
//}


//weixin, wms proxy
enum{
	EX_RECORD_FLAG_FOR_NBR		= 0x00 << 8,
	EX_RECORD_FLAG_FOR_SC		= 0x01 << 8,
	EX_RECORD_FLAG_FOR_NBRANDSC	= 0x02 << 8
};
//end

//{ 09292007, Folki+ for eureka 3.8 GDM ping to disable calc RTT.
// ping flags
#define GCC_PING_SECURE_FLAG				 0x01
#define GCC_PING_DISABLE_GDM_LOGIC		 0x02
#define GCC_PING_INTERNAL_FLAG			 0x04
//}

//{ 12/06/2007, Folki+ for supporing relay server
#define GCC_CONF_ACTION_START_P2P_CONN		1
#define GCC_CONF_ACTION_STOP_P2P_CONN		2
#define GCC_CONF_ACTION_START_RELAY_CONN	3
#define GCC_CONF_ACTION_STOP_RELAY_CONN	4

#define GCC_CONF_ACTION_RTT_CALC_REQ		5
#define GCC_CONF_ACTION_RTT_CALC_RSP		6

#define GCC_CONF_ACTION_ACT_INDICATION		7
//}

// budingc 9/11/2008, for attendee ack.
#define GCC_CONF_ACTION_ENABLE_SDIN_ACK 8 
#define GCC_CONF_ACTION_AS_PDU_SENDDATA_ACK 9 
#define GCC_CONF_ACTION_AS_PDU_SENDDATA_PDUID_FOR_ACK 10 

//for SPA project, kelvin 2008-6-26
#define GCC_CONF_ACTION_MDB_UPDATE              11
//for SPA, kelvin 2008-10-23
#define GCC_CONF_ACTION_SMAC_CHK_REQUEST        12
#define GCC_CONF_ACTION_SMAC_CHK_RESPONSE       13

//{ 10/19/2010, Folki+ for MSI taks
#define GCC_CONF_ACTION_WMSI_MONITOR_ACTION		14
#define GCC_CONF_ACTION_WMSI_REPORT_INDICATION	15
//added by sandy at 2012.04.18 for P2P Session log begin
#define GCC_CONF_ACTION_P2P_SESSION_INFO	16
//added by sandy at 2012.04.18 for P2P Session log end
//}

//added by Jack at 2013.04.09 for nbr oneTouch
#define GCC_CONF_ACTION_NBRCREATOR_CHK_REQUEST  17
#define GCC_CONF_ACTION_NBRCREATOR_CHK_RESPONSE 18
//added by sandy at 2014.1.26 for security batch 5 begin
#define GCC_CONF_ACTION_EJECT_NO_SECURE_USERS  19
//added by sandy at 2014.1.26 for security batch 5 end
//==> steven, 2014.2.17, for cmr begin
#define GCC_CONF_ACTION_CET_RSC_SYNC  20
#define GCC_CONF_ACTION_UPDATE_PRESENTER_SDK_VER  21
//<==
#define GCC_CONF_ACTION_WHITELIST_RSC_SYNC  22
#define GCC_CONF_ACTION_UPDATE_CB_VER  23


//for MPI, kelvin 2009-6-30
//->
#define GCC_MISC_MSG_MTGDB_INFO "MISC_MSG_MTGDB_INFO_EUREKA20090630"
//<-
// Andrew, audio license limit for artemis 1.1, 2009/11/06
#define GCC_MISC_MSG_LICENSE_INFO "MISC_MSG_LICENSE_INFO_EUREKA20091106"

//////////////////////////////////////////////////////////////////////////
// options
#define GCC_OPTION_ACS_ONE_TIME		0x02
#define GCC_OPTION_ACS_MULTI_TIMES		0x03
#define GCC_OPTION_ACS_NORMAL_MEETING	0X08 //	//oliver, 4/21/2010, for in-meeting security enhancement

//oliver, 6/3/2013, for task 17210 , replace MD5/SHA1 with SHA256

#define GCC_OPTION_HASH_SHA1   0
#define GCC_OPTION_HASH_SHA256   1
#define GCC_OPTION_HASH_HMACSHA256   2
//end


// 5/3/2011,oliver, fix bug https://qaforum.webex.com/bug/bugaction.asp?Ac=VD&BN=434354
#define PRESENTER_FLAG_NO_ASNBR_FIX	0x01
#define GCC_PRESENTER_FLAG_RSC_ID "GCC_PRESENTER_FLAG"

//end

//////////////////////////////////////////////////////////////////////////////
// Ping_Result
//
typedef uint16 Ping_Result;
#define PING_RESULT_SUCCESSFUL					0
#define PING_RESULT_CONFERENCE_NOT_EXIST		1
#define PING_RESULT_CONFERENCE_ALREADY_EXIST	2
#define PING_RESULT_CONFERENCE_NOT_AVAILABLE	3
#define PING_RESULT_CONFERENCE_LOCKED			4
#define PING_RESULT_NO_SERVER_AVAILABLE			5
#define PING_RESULT_TIME_OUT					6
#define PING_RESULT_UNKNOWN						7
#define PING_RESULT_SERVER_NOT_READY			8
#define PING_RESULT_CONFERENCE_NOT_READY		9
#define PING_RESULT_CONFERENCE_CLOSED_NO_USERS	10
//NEW added for new RA general ping
#define PING_RESULT_LOADFULL 							11
#define PING_RESULT_TESTING							12
#define PING_RESULT_SUSPENDED							13
#define PING_RESULT_RA_NOT_AVAIL						14
#define PING_RESULT_RA_EXCLUDED						15

// 08312007, Folki+
#define PING_RESULT_MZM_VERSION_NOT_COMPATIBLE	40

//////////////////////////////////////////////////////////////////////////////
// GCC_Enroll_Flag
//
typedef uint32 GCC_Enroll_Flag;
const GCC_Enroll_Flag GCC_ENROLL_ACTIVE							= 0x1;
const GCC_Enroll_Flag GCC_ENROLL_VISIBLE						= 0x2;
const GCC_Enroll_Flag GCC_ENROLL_RECEIVE_VISIBLE_ROSTER_REPORT	= 0x4;
const GCC_Enroll_Flag GCC_ENROLL_RECEIVE_ALL_ROSTER_REPORT		= (0x8|0x4);
const GCC_Enroll_Flag GCC_ENROLL_RECEIVE_LOCAL_ROSTER_ONLY		= 0x20;
const GCC_Enroll_Flag GCC_ENROLL_URGENT							= 0x10;
const GCC_Enroll_Flag GCC_ENROLL_PHANTOM	                     = 0x40;
const GCC_Enroll_Flag GCC_ENROLL_SECRET	                     = 0x80;
const GCC_Enroll_Flag GCC_ENROLL_NOLICENSE_CHECK	            = 0x100;
const GCC_Enroll_Flag GCC_ENROLL_NO_WRITE_LOG					= 0x200;

//{ 10/10/2005, added by folki for election host
const GCC_Enroll_Flag GCC_ENROLL_NORMAL_ATTENDEE_FLAG  = 0x200 << 1;
const GCC_Enroll_Flag GCC_ENROLL_NORMAL_HOST_FLAG      = 0x200 << 2;
const GCC_Enroll_Flag GCC_ENROLL_ALTERNATIVE_HOST_FLAG = 0x200 << 3;
//}


//weixin, wms proxy
const GCC_Enroll_Flag GCC_ENROLL_WEB_CHAT = 0x200 << 4;
//

//steven+
const GCC_Enroll_Flag GCC_ENROLL_PANELIST = 0x200 << 5;


// for backward compatible

#define GCC_MISC_MSG_TYPE_LICENSE_IND				1
#define GCC_Misc_Msg_Type_Allocate_Handle_Confirm	2
#define GCC_MISC_MSG_TYPE_APPREG_CONFIRM			3
#define GCC_MISC_MSG_TYPE_SESS_CREATE_IND			4
#define GCC_MISC_MSG_TYPE_CONFLOCK_IND				5
#define GCC_MISC_MSG_TYPE_CB_DISCONN_IND			6
#define GCC_MISC_MSG_TYPE_APPSVR_STATUS_CHANGED		7	// loword: app_type, hiword: 0: down 1: up
#define GCC_MISC_MSG_TYPE_PROXY_AUTH_REQ			8
#define GCC_MISC_MSG_TYPE_HTTP_RESPONSE_ERROR		9
//{ 10/03/2006, Folki
#define GCC_MISC_MSG_TYPE_PKI_IND					10
//}
//{ 20061130, Folki+ for flow control
#define GCC_MISC_MSG_TYPE_BUFF_FULL_IND					11
//}
//wallice add for sas
#define GCC_MISC_MSG_TYPE_CBREG_REQ			12

//07/16/2008 Connie
#define GCC_MISC_MSG_TYPE_RTT_RSP		13
// budingc 10/07/2007, for p2p.
#define GCC_MISC_MSG_TYPE_P2P_CONN_SUCCESS	20
#define GCC_MISC_MSG_TYPE_P2P_CONN_FAILED		21

// budingc 9/11/2008, for attendee ack.
#define GCC_MISC_MSG_TYPE_P2P_SEND_DATA_ACK	22
#define GCC_MISC_MSG_TYPE_AS_PDU_SENDDATA_ACK 23

// 08/19/2008, Folki+ for fixing bug 308388
#define GCC_MISC_MSG_TYPE_AS_REFRESH			30

//for MPI, kelvin 2009-6-30
#define GCC_MISC_MSG_TYPE_CONF_MISC             31

//Henry add
#define GCC_MISC_MSG_TYPE_H264_CMD 40
//end

//20120803, Steven, for qos.
#define GCC_MISC_MSG_TYPE_QOS_DATA_IND 41
//end

#define GCC_LICENSE_CONF_WARNING	1
#define GCC_LICENSE_CONF_EXPIRED	2
#define GCC_LICENSE_SESSION_WARNING	3
#define GCC_LICENSE_SESSION_EXPIRED	4
//{ 12/09/2005, added by folki
#define GCC_LICENSE_CONF_FULL			5
#define GCC_LICENSE_CONF_NOT_FULL	6
//==>22/04/2008, added by issac for simul meeting
#define GCC_LICENSE_HOST_SIMUL_MTG_EXCCEEDED	8
//}

//{ 10/03/2006, Folki
#define GCC_PKI_CONF_KEY_EXCHANGE_FAILED	7
#define GCC_LICENSE_CONF_WARNING_CLOSE_WITHOUT_HOST 9
//}
//////////////////////////////////////////////////////////////////////////////
// GCC_Session_Key
//
typedef struct
{
    GCC_App_Protocol_Type application_protocol_type;
    MCS_Channel_ID        session_id;
} GCC_Session_Key;

//////////////////////////////////////////////////////////////////////////////
// GCC_Resource_Type
//
typedef uint16 GCC_Resource_Type;

const GCC_Resource_Type GCC_RSC_TYPE_MASK   = 0xff;
const GCC_Resource_Type GCC_RSC_NONE        = 0;
const GCC_Resource_Type GCC_RSC_CHANNEL_ID  = 1;
const GCC_Resource_Type GCC_RSC_TOKEN_ID    = 2;
const GCC_Resource_Type GCC_RSC_PARAMETER   = 3;
const GCC_Resource_Type GCC_RSC_ENCRYPTION  = 4;
const GCC_Resource_Type GCC_RSC_SMAC        = 5;  // smac
const GCC_Resource_Type GCC_RSC_TIMESTAMP   = 6;   // ts
const GCC_Resource_Type GCC_RSC_USER_TICKET = 7;   // user ticket

//<= Andrew+, 08/17/2005 10:25:11
// for NBR
const GCC_Resource_Type GCC_RSC_START_RECORD= 8; //for NBR

//{ 09/19/2005 9:34, added by Folki for new license & PKI
const GCC_Resource_Type GCC_RSC_LIC_VALUE			= 9;
const GCC_Resource_Type GCC_RSC_PKI_ENCRYPTION_FLAG	= 10;
const GCC_Resource_Type GCC_RSC_USER_GID			= 11;
//}

//yardley 01.12.2006
const GCC_Resource_Type GCC_RSC_DWORD_VALUE			= 12;
//end


//weixin, wms proxy
#define SC_REPORT_FLAG_RSC_ID				"SC_REPORT_FLAG"
//oliver, Eureka 3.6, SC meeting, WebACD server DNS, format DNS_address:port
# define GCC_RSC_SC_WebACD_DNS_ID			"WebACD_Notify_DNS"
//end
// for local storage
#define PRIMARY_STORAGE_RSC_ID			"nbr_location1"
#define SECOND_STORAGE_RSC_ID			"nbr_location2"
// for global storage
#define PRIMARY_BACKUP_STORAGE_RSC_ID	"nbr_location3"
#define SECOND_BACKUP_STORAGE_RSC_ID	"nbr_location4"

#define NBR_TOKEN_RSC_ID		"nbr_token"
#define NBR_DURATION_RSC_ID     "nbr_record_duration"
#define NBR_MILLISECOND_STARTTIME_RSC_ID	"nbr_starttime_ms" //20111008 kun, +for nbr timeout bug
#define PKI_CERT_RSC_ID			"PKI_CERT"
#define PKI_CERT_KEY_RSC_ID     "PKI_CERT_&_KEY"

#define CET_CMR_HOST_ONCE_JOINED_RSC_ID     "CET_CMR_HOST_ONCE_JOINED_RSC_ID"

#define NEED_CHECK_PANELIST_KEY_RSC_ID     "NEED_CHECK_PANELIST_KEY_RSC_ID"

//Cloudy 04/24/2008
//for web chat failover issue in distributed meeting
#define WEB_CHAT_TOP_CB_RSC_ID     "top_cb_address"

//distributed meeting 1.0, kelvin 2007-6-26
//#define TOTAL_NUMBER_OF_ATTENDEES_RSC_ID     "PKI_TOTAL_NUMBER_OF_ATTENDEES"
//klevin 2007-7-3
#define HOST_PASSPORT_RSC_ID                   "Host_Passport_for_GDM"
//}

//yardley 01.12.2006
#define CONF_MAX_LICENSE_RSC_ID     "conf_max_license"
//end

//==> andrew 07-20-2007
#define CONF_MAX_ATTENDEE_NUM_RSC_ID		"max_attendee_num"
//<==

//yardley 03072006
#define LICENSE_CHANGE_FULL_RSC_ID "license_to_full"
//end

//yardley for secure host key, 04192006
#define HASH_OF_HOST_KEY_RSC_ID			"HashOfHostKeyEx"
#define HOST_KEY_RSC_ID					"HostKeyEx"
//end

//{ 12/21/2011, Folki + for Orion task, remove encrypt/decrypt, oliver, 5/21/2013, merged from orion branch for t29 task 17210
// non encrypt/decrypt, the data on resource is raw data
#define HASH_OF_HOST_KEY_V2_RSC_ID "HashOfHostKeyV2"
#define HOST_KEY_V2_RSC_ID "HostKeyV2"

//}
//oliver, 5/21/2013, for T29 task 17210
#define T29_CRYPTO_FLAG_RSC_ID "T29CryptoFlag"
#define RANDOM_STRING_RSC_ID   "randomstrings"

#define VER_NUM_RSC_ID				"VersionNumber"

//{ 06012007, Folki+ for distribute meeting
#define TOP_ZONE_ID_RSC_ID				"top_zone_id"
#define TOP_ZONE_DOMAIN_ID_RSC_ID	"top_zone_domain_id"
#define TOP_ZONE_LOCATION_ID_RSC_ID	"top_zone_loaction_id"
#define INTERNAL_TOP_CB_RSC_ID		"internal_top_cb"
//}
//added by sandy at 2014.1.26 for security batch 5 begin
#define IS_HARDCODED_KEY_RSC_ID                 "is_hardcoded_key"
#define CB_CHANNEL_ID_RSC_ID                 "cb_channel_id"
#define DYNAMIC_KEY_RSC_ID					"dynamic_key"
//added by sandy at 2014.1.26 for security batch 5 end
#define SMAC_TYPE_RSC_ID		"smac_type"
#define KEY_VER_RSC_ID		"key_version"

#define PRESENTER_CLIENT_SDK_VER_RSC_ID  "presenter_client_sdk_ver"

///comerzhang 20070718 for RACB
#define PRIMARY_DOMAIN_NAME_RSC_ID  "pri_meeting_domain"
#define RA_HOST_ID_RSC_ID  "ra_host_id"
///end
#define GLOBAL_MTG_DOMAIN_LIST_RSC_ID	"global_mtg_domain_list"
#define GDM_PARAMETERS					"gdm_parameters"
//COMERZHANG:REGID:2007:1011
#define REGISTRATION_ID_RSC_ID  "registration_id"
#define REGISTRATION_PROP_RSC_ID  "registration_prop"
#define Non_REG_CONFERNCE        	0x80000000   
#define REG_CONF_HOST 			0x80000001   
#define REG_CONF_ALT_HOST  	0x80000002   
#define REG_CONF_ATENDEE     	0x80000004  
#define REG_CONFERNCE        		0x80000008   ///only used between top cb and sub cb
//COMERZHANG:REGID:2007:1011:end

//2011-10-20 kun: 3.12.2 to fix bug 399491, adding a new resource in join response sent from top cb to sub cb
//type:    GCC_RSC_DWORD_VALUE
//format:  least 1 bit is valid, other bits reserved.
//value:   1->top cb fixed bug 399491, otherwise 0, default is 0
#define REG_CONF_TOP_VERSION	"top_cb_version"
#define REG_CONF_TOP_VERSION_MASK	0x1
#define CB_VERSION_SUPPORT_REGID_WITH_USERID 1

//{ 09292007, Folki+ for T27 task
#define REPORT_RECORD_FLAG_RSC_ID		"report_record_flag"
#define ACTION_INDICATION_RSC_ID		"action_indication"
//}

//{ 10/25/2007, Folki+ for P2P & Cascade
// P2P enable resource
// resource type: GCC_RSC_PARAMETER
// Data: stunt_svr1=addr1,stunt_svr2=addr2,stunt_svr3=addr3
#define P2P_INFO_RSC_ID					"p2p_info"
// Cascading enable resource
// resource type: GCC_RSC_PARAMETER
// Data: max_user=5,max_conn=5
#define CASCADE_INFO_RSC_ID				"cascade_info"
#define CASCADE_CLIENT_NAT_IP_RSC_ID	"cascade_client_NAT_IP"
//<--
//}

//fix t20 client fail to decode DWORD GCC resource,kelvin 2007-10-30
//format: <major version:3 decimals><minor version:3 decimals><revision number:3 decimals>
#define CLIENT_SDK_VER_RSC_ID "client_sdk_version"

//{ 12/20/2007, Folki+ for P2P
#define P2P_CONFIG_RSC_ID				"p2p_config"
#define TIME_TICK_COUNT_RSC_ID		"time_tick_count"
//}

//wallice add for sas
#define GCC_SESSION_TYPE_RSC_ID	"session_type"
#define CB_ADDRESS_RSC_ID	"cb_address"
#define TELEPHONY_RSC_ID	"TA_RSC_ID"
#define SAS_MCT_RSC_ID  "sas_mct_rsc_id"
#define FLASH_SCREEN_RSC_ID "FLASH_RSC_ID"
#define IMAGE_RSC_ID "IMAGE_RSC_ID"
#define FLASH_AUDIO_RSC_ID "FLASH_AUDIO_RSC_ID"
#define GCC_APPSVR_REDIRECT "gcc_appsvr_redirect"

//nbr2 pause/resume
#define NBR2_PLAYER_STATUS_RSC_ID "RSC_PLAYER_STATUS"
//add site_id, kelvin 2008-2-2
#define SITE_ID_RSC_ID "CONF_SITE_ID_RSC_ID"
//for SPA project, kelvin 2008-6-26
//->
#define MDB_UPDATE_RSC_ID   "MeetingDB_Update_CMD"

#define PRIORITY_RSC_ID				"priority"
#define RTT_CALC_TYPE_RSC_ID		"rtt_calc_type"
#define SPA_SMAC_CHK_CONF_ID_RSC_ID "SPA_SMAC_CHK_CONF_ID"
#define SPA_SMAC_CHK_CONF_NAME_RSC_ID "SPA_SMAC_CHK_CONF_NAME"
#define SPA_SMAC_CHK_CONF_KEY_RSC_ID "SPA_SMAC_CHK_CONF_KEY"
#define SPA_SMAC_CHK_CONF_PASS_RSC_ID "SPA_SMAC_CHK_CONF_PASS"
#define SPA_SMAC_CHK_SITE_ID_RSC_ID "SPA_SMAC_CHK_SITE_ID"
#define SPA_SMAC_CHK_USER_ID_RSC_ID "SPA_SMAC_CHK_USER_ID"
#define SPA_SMAC_CHK_USER_NAME_RSC_ID "SPA_SMAC_CHK_USER_NAME"
#define SPA_SMAC_CHK_CONN_HANDLE_RSC_ID "SPA_SMAC_CHK_CONN_HANDLE"
#define SPA_SMAC_CHK_RESULT_RSC_ID "SPA_SMAC_CHK_RESULT"

// budingc 9/11/2008, for attendee ack.
#define CONFIG_DATA_RSC_ID		"config_data_type"

//Henry add for unique session
#define GCC_RSC_ID_UNIQUE_SESSION "UNIQUE_SESSION"
//end

#define SERVER_COMPATIBILE_VERSION_RSC_ID "SERVER_COMPATIBILE_VERSION"
//<-
//oliver, 11-07-2008, for SPA, svr compatible
#define  SVR_COMP_VER_RSC_ID	"SVR_COMP_VER_RSC_ID"

//oliver, 02192009, Eureka 3.10.1 for Task13506 - billing and report for Click to Conference
#define SPECIAL_CLIENT_TYPE_RSC_ID "Special_client_type"
#define SPECIAL_CLIENT_JOIN_TRIGGER_RSC_ID "Special_client_join_trigger"    

//for MP, kelvin 2009-6-30
//->
#define MTGDB_INFO_UPDATE_HOSTNAME_RSC_ID "meeting_db_info_hostname"
#define MTGDB_INFO_UPDATE_DBNAME_RSC_ID   "meeting_db_info_dbname"
#define MTGDB_INFO_UPDATE_USERNAME_RSC_ID "meeting_db_info_username"
#define MTGDB_INFO_UPDATE_PASSWORD_RSC_ID "meeting_db_info_password"
//<-

// 12/09/2010 issac+
// carried by ccrq from SDK,according the value of ping_flag value in url of create_ping to MZM of SDK
#define GCC_CONF_FLAG_RSC_ID "conf_flag"
#define GCC_CONF_FLAG_AA_MEETING_DOMAIN 0x01

// issac

//added by sandy at 2012.04.18 for P2P Session log begin
#define P2P_SESSION_INFO_RSC_ID "p2p_session_info"
//added by sandy at 2012.04.18 for P2P Session log end



//oliver, 4/13/2010, for FR29, in-meeting security enhancement task
#define PRIVILEGE_TICKET_RSC_ID		"PRIVILEGE_TICKET"
#define MTG_SECURITY_PARAMS_RSC_ID	"MTG_SECURITY_PARAMS"
#define INTERNAL_HOST_KEY_RSC_ID	"INTERNAL_HOST_KEY"
#define PRESENTER_KEY_RSC_ID		"PRESENTER_KEY"

#define SESSION_AS_TICKET_RSC_ID		"SESSION_AS_TICKET"
#define SESSION_PD_TICKET_RSC_ID 	"SESSION_PD_TICKET"
#define SESSION_NBR_TICKET_RSC_ID	"SESSION_NBR_TICKET"
#define SESSION_FLASH_TICKET_RSC_ID	"SESSION_FLASH_TICKET"
#define SESSION_TELEP_TICKET_RSC_ID	"SESSION_TELEP_TICKET"
#define SESSION_FS_TICKET_RSC_ID		"SESSION_FS_TICKET"
#define SESSION_POLLING_TICKET_RSC_ID	"SESSION_POLLING_TICKET"
#define SESSION_NOTES_TICKET_RSC_ID	"SESSION_NOTES_TICKET"

#define PANELIST_KEY_RSC_ID			"PanelistKey"

//oliver, 4/13/2010, for FR29, webex 11 audio license limitation
#define GCC_ENCRYPTED_AUDIO_FLAG_RSC_ID "GCC_ENCRYPTED_AUDIO_FLAG"
//end
#define CB_SECURITY_PARAMS_RSC_ID        "CB_SECURITY_PARAMS"

#define SPECIAL_CLIENT_JOIN_TRIGGER_SESSION_NONE 0
#define SPECIAL_CLIENT_JOIN_TRIGGER_SESSION_ALL 1 
#define SPECIAL_CLIENT_JOIN_TRIGGER_SESSION_AS 2
#define SPECIAL_CLIENT_JOIN_TRIGGER_SESSION_ALL_EXCEPT_TEL 3

//The number for billable SessUserJoin and SessUserLeave is always 100 higher than the not billable.
//This allow the Engene's team(EDR) to distinguish the different between this one and PCNow billing event.
#define SPECIAL_CLIENT_BILLING_CHANGE_NUM	100

typedef enum
{
	 GENERAL_MEETING=0,
	 SC_MEETING,
	 NBR_MEETING,
	 SPECIAL_CLIENT_MEETING
}Sub_Meeting_Type;
//end
//MPI, kelvin 2009-3-10
#define INTERNAL_MEETING_FLAG_RSC_ID "Internal_Meeting_Flag"
//MPI,kelvin 2009-3-27
#define NEW_VERSION_SMAC_RSC_ID "NEW_VERSION_SMAC"

//"oliver, for Orion 1.0, 11/25/2011" merge from Orion for t29 task 17210
#define SMAC_EX_RSC_ID "SMAC_EX"
//end

#define TOP_CB_VER_INFO_RSC_ID "TOP_CB_VER_INFO"

#define CPAEX_OPT_AND_KEY_RSC_ID	"CPAEX_OPT_AND_KEY"

//{ 11/16/2010, Folki+ for WMSI report
#define WMSI_REPORT_RSC_ID				"WMSI_REPORT"
#define WMSI_ACTION_RSC_ID				"WMSI_ACTION"
//}
//added by sandy at 2012.03.19 for Eureka3.12.3 begin
#define GCC_NODE_LOGIN_TYPE_RSC_ID   "GCC_NODE_LOGIN_TYPE"
#define GCC_NODE_LOGIN_TYPE_UNKNOW    0  // unknown login user(default)
#define GCC_NODE_LOGIN_TYPE_INTERNAL    1  // internal login user
#define GCC_NODE_LOGIN_TYPE_EXTERNAL    2  // external login user
//added by sandy at 2012.03.19 for Eureka3.12.3 end

//added by Jack at 2013.03.01 for Qos control launch
#define QOS_CONTROL_RSC_ID "RSC_QOS_CONTROL"

//added by Jack at 2013.06.27 for Tandberg notify url
#define NOTIFY_URL_RSC_ID "RSC_NOTIFY_URL"
#define TPGW_IP_RSC_ID "RSC_TPGW_IP"
#define APPSVR_SESSION_TYPE_RSC_ID	"appsvr_session_type"
#define CET_MEETING_FLAG_RSC_ID "RSC_CET_FLAG"
#define CET_MEETING_DURATION_RSC_ID "RSC_CET_MEETING_DURATION"

//added by steven, for cet meeting, notify service start/stop
#define CET_NOTIFY_PORTABLE_DOC_RSC_ID "RSC_CET_NOTIFY_PORTABLE_DOC"
#define CET_NOTIFY_POLLING_RSC_ID      "RSC_CET_NOTIFY_POLLING"
#define CET_NOTIFY_WHITE_BOARD_RSC_ID  "RSC_CET_NOTIFY_WHITE_BOARD"
#define CET_NOTIFY_WEB_CONTENT_RSC_ID  "RSC_CET_NOTIFY_WEB_CONTENT"
#define CET_NOTIFY_MEETING_REFRESH_RSC_ID     "RSC_CET_NOTIFY_MEETING_REFRESH"

#define GCC_CHECK_PANELIST_ENROLL_FLAG_RSC_ID     "RSC_CHECK_PANELIST_ENROLL_FLAG"

#define GCC_JOIN_LOCK_CONFERENCE_TOKEN_RSC_ID     "RSC_JOIN_LOCK_CONFERENCE_TOKEN"
#define GCC_HOST_KICKOFF_LOCK_ATTENDEE_RSC_ID     "RSC_HOST_KICKOFF_LOCK_ATTENDEE"
#define GCC_VERIFIED_NEW_CLIENT_USER_ID_RSC_ID       "RSC_VERIFIED_NEW_CLIENT_USER"
#define GCC_VERIFIED_NEW_CLIENT_USER_ID_LIST_RSC_ID  "RSC_VEFIFIED_NEW_CLIENT_USER_LIST"
#define GCC_VERIFIED_OLD_CLIENT_USER_ID_RSC_ID       "RSC_VERIFIED_OLD_CLIENT_USER"
#define GCC_VERIFIED_OLD_CLIENT_USER_ID_LIST_RSC_ID  "RSC_VEFIFIED_OLD_CLIENT_USER_LIST"


#define GCC_CB_VER_RSC_ID  "RSC_CB_VER"

#define GCC_PAGE_VER_SYNC_RSC_ID                  "PAGE_VER_SYNC_RSC_ID"

#define GCC_CONF_LOCK_STATUS_RSC_ID                   "RSC_CONF_LOCK_STATUS_RSC_ID"

#define GCC_CONF_FAILOVER_RSC_ID                   "RSC_CONF_FAILOVER_RSC_ID"

#define GCC_CONF_AUTH_USER_CNT_RSC_ID		"GCC_CONF_AUTH_USER_CNT_RSC_ID"

#define GCC_CONF_ENABLE_NONLOGIN_USER_STAY_IN_LOBBY_RSC_ID		"GCC_CONF_ENABLE_NONLOGIN_USER_STAY_IN_LOBBY_RSC_ID"

//added by Jack at 2015.01.04 for PMR notify host feature
#define NOTIFY_HOST_RSC_ID 		"RSC_NOTIFY_HOST"

//added by Jack at 2015.02.04 for video callback feature
#define ENDPOINT_OUTDAIL_RSC_ID 		"RSC_ENDPOINT_OUTDAIL"
#define ENDPOINT_CANCEL_RSC_ID	 		"RSC_ENDPOINT_CANCEL"
#define ENDPOINT_DISCONNECT_RSC_ID	 	"RSC_ENDPOINT_DISCONNECT"
#define ENDPOINT_STATUS_RSC_ID	 		"RSC_ENDPOINT_STATUS"

//US57229: add by Witty at 2016.04.19 for return the meeting create/join time to client.
#define GCC_JOIN_MEETING_TIMESTAMP_RSC_ID   "RSC_JOIN_MEETING_TIMESTAMP"

//added by steven, for meeting type, cmr or vmr,2014.02.14
const uint32 MEETING_FLAG_VMR = 1;
const uint32 MEETING_FLAG_CMR = 2;
const uint32 MEETING_FLAG_PMR = 3;
//////////////////////////////////////////////////////////////////////////////
// GCC_Resource_Key
//
typedef struct
{
    char              rsc_id[GCC_MAX_RSC_ID_LENGTH];
    GCC_Resource_Type rsc_type;
} GCC_Resource_Key;

const uint32 CLIENT_VERSION_SUPPORT_PMR_SECURITY=3011027;
//MPI, kelvin 2009-3-24
//->
const uint8 SMAC_HASH_COUNT=4;

const uint8 SMAC_HASH_MD5=0;
const uint8 SMAC_HASH_SHA1=1;
const uint8 SMAC_HASH_SHA256=2;
const uint8 SMAC_HASH_HMACSHA256=3;

const uint32 SMAC_DIGEST_SIZE[SMAC_HASH_COUNT]={16,20,32,32};

#define SMAC_SIZE 16
#define MAX_SMAC_SIZE 20

//<-
//////////////////////////////////////////////////////////////////////////////
// GCC_Resource
// This structure is used to hold a single resource item.
//
#define GCC_User_Data MCS_User_Data
struct GCC_Resource
{
   GCC_Resource_Key rsc_key;
   union resource_info
   {
      MCS_Channel_ID       channel_id;
      MCS_Token_ID         token_id;
      GCC_User_Data        parameter;
      char                 s_mac [SMAC_SIZE /*16*/];
      uint32               timestamp;
      uint8                encryption;
	  //<= Andrew+, 08/17/2005 10:25:27
	  // for NBR
	  uint8				   start_record;
	  //}

	  //{ 09/19/2005 8:41,added by Folki for new license and PKI
	  uint8				   lic_flags; // added for license check
	  uint8				   pki_flag; // added for PKI
	  uint32			   user_GID; // user GID
	  //}

      //yardley 01.12.2006
      uint32			   dw_value; //GCC_RSC_DWORD_VALUE
      //end
   } u;
   GCC_Resource ()
   {
      rsc_key.rsc_id[0] = 0;
	  //oliver, 05132010, Eureka 3.11.5.1, add crash protection
	  u.parameter.length = 0;
	  u.parameter.data = NULL;
	  //end
   }
} ;


typedef enum
{
   GCC_Resource_Action_Add = 0,
   GCC_Resource_Action_Remove,
   GCC_Resource_Action_Modify,
   GCC_Resource_Action_Append,
   GCC_Resource_Action_Parameter,	///yardley for secure host key, 04212006
   GCC_Resource_Action_HostID_Add,	///comer add for ra agent, 09272007
   GCC_Resource_Action_HostID_Del,	///comer add for ra agent, 09272007
	GCC_Resource_Action_Mtg_Event,	///Folki+ fot T27 task
	GCC_Resource_Action_Token,
} GCC_Resource_Action;

typedef struct
{
   GCC_Resource*       rsc;
   GCC_Resource_Action action;
} GCC_Resource_Update_Record;

//{ 09/19/2005 9:36, added by Folki for new license
enum{
	NORMAL_ATTENDEE_FLAG  = 0x01 << 0,
	NORMAL_HOST_FLAG      = 0x01 << 1,
	ALTERNATIVE_HOST_FLAG = 0x01 << 2,
	NEED_NOLIC_CHECK      = 0x01 << 6,
	NEED_LIC_CHECK        = 0x01 << 7
};
//}

//////////////////////////////////////////////////////////////////////////////
// GCC_Node_Record
// This structure defines a single conference roster record.
// For MCU, node_name is the server ip address, user_id is the number of sub
// terminals.
//
 struct GCC_Node_Record
{
   GCC_Node_ID         node_id;
   GCC_Node_Type       node_type;
   char                node_name[GCC_MAX_CONF_USER_NAME_LENGTH];
   char                node_ip_addr[GCC_MAX_TRANSPORT_ADDR_LENGTH];
   uint32              capability_flag;
   uint32              user_id;
   GCC_Enroll_Flag     enroll_flag;
   uint8*              node_info;
   uint32              node_info_length;
   uint32			   inattention_time; //total inattention time
   uint32				random_num; //helps to indentify user join and user leave in failover case
   uint64              in_time;
   char                client_ip_addr[GCC_MAX_TRANSPORT_ADDR_LENGTH]; 
   GCC_Node_Record()
	{
		inattention_time = 0;
		random_num = 0;
	}
} ;



//////////////////////////////////////////////////////////////////////////////
// GCC_APE_Record
// This structure holds all the data associated with a single Application
// Protocol Entity(user application) enrolled into a specific session.
// for MCU, ape_id is the number of sub terminals apes.
//
typedef struct
{
   GCC_Node_ID         node_id;
   GCC_Node_Type       node_type;
   GCC_APE_ID          ape_user_id;
   GCC_Enroll_Flag     enroll_flag;
   uint8*              ape_info;
   uint32              ape_info_length;
} GCC_APE_Record;

typedef struct
{
   uint32              reason;
   WBXCONFID              conference_id;
   GCC_Session_Key     session_key;
   uint32              time_left;
} GCC_MiscMsg_LicenseInd;

typedef struct
{
   uint32 connection;
   uint16 result;
} GCC_MiscMsg_AppRegCfm;

typedef struct
{
   WBXCONFID conference_id;
   uint32 connection;
} GCC_MiscMsg_CbRegAppReq;

typedef struct
{
   uint16 result;	
   WBXCONFID conference_id;
   uint32 connection;
   GCC_App_Protocol_Type   svr_type;
   char svr_address[GCC_MAX_TRANSPORT_ADDR_LENGTH];
   uint16 svr_capacity;
} GCC_MiscMsg_CbRegAppCfm;

typedef struct
{
   uint32 connection;
   uint16 reason;
}GCC_MiscMsg_CbDisconnInd;

//{ 07/16/2008 connie for test tool
typedef struct{
	GCC_Node_ID dest_id;
	MCS_Priority priority;
	uint32 mtg_rtt;
}GCC_MiscMsg_RttCalcRsp;
//}
//Henry add
struct  GCC_MiscMsg_H264Cmd
{
	GCC_MiscMsg_H264Cmd()
	{
		channel_id = 0;
		cmd_type = 0;
		cmd_data = 0;
		force = false;
	}
	uint32 channel_id;
	uint32 cmd_type;
	uint32 cmd_data;
	boolean   force;
};


#define 	H264_FRAME_HEAD_MASK  0x00000001
#define 	H264_FRAME_TAIL_MASK  0x00000002
#define		ISFRAMEHEAD(x) 	(H264_FRAME_HEAD_MASK == ((x) & H264_FRAME_HEAD_MASK))
#define		ISFRAMETAIL(x) 	(H264_FRAME_TAIL_MASK == ((x) & H264_FRAME_TAIL_MASK))
#define		SETFRAMEHEAD(x) ((x) = ((x) | H264_FRAME_HEAD_MASK))
#define		SETFRAMETAIL(x) ((x) = ((x) | H264_FRAME_TAIL_MASK))
#define		SETNALSEQ(x,y)	((x) = ((x) | ((y)<<16)))
#define		GETNALSEQ(x)	((x) >> 16)
//end
typedef struct
{
   GCC_App_Protocol_Type   protocol_type;
   Transport_Address       destination_address;

} GCC_Config_AppRegReq;

//{ 10/03/2006, Folki
typedef struct
{
   uint32 conference_id;
   uint16 reason;
} GCC_MiscMsg_PkiInd;
//}

//{ 20060810, Folki+ for Eureka 4.0 Chat/Polling Cache Design
#ifndef NEW_CACHE_SUPPORT
#define NEW_CACHE_SUPPORT
#define HANDLE_NAME_LEN_MAX 64
typedef struct
{
   char     handle_name[HANDLE_NAME_LEN_MAX];
   uint32   handle_value;
}NameHandle;

typedef enum tagCacheAction
{
	//used for cache set request and cache set confirm
	CACHE_SET=0,
	CACHE_APPEND,
	CACHE_MODIFY,
	CACHE_RESET,
//the following three types are for retrieving confirm to client
	CACHE_RETRIEVE_BEGIN,
	CACHE_RETRIEVE_CONTINUE,
	CACHE_RETRIEVE_END,
	CACHE_SUBSCRIBE,
	CACHE_UNSUBSCRIBE
}CacheAction;

typedef enum tagCacheRequestType{
	CACHE_RETRIEVE_REQ_DATA=1,
	CACHE_RETRIEVE_REQ_SUBCRIBE,
	CACHE_RETRIEVE_REQ_DATAANDSUBCRIBE,
	CACHE_RETRIEVE_REQ_UNSUBSCRIBE
}CacheRequestType;

#define CACHE_ACTION_OPT_DATA_RETURN	0x01000000
#define CACHE_ACTION_OPT_DATA_NORETURN	0x02000000
#endif // NEW_CACHE_SUPPORT
//}

//////////////////////////////////////////////////////////////////////////
// PKI data
//{ 09/19/2005, added by Folki
#define GCC_CERT_FORMAT_PEM		0
#define GCC_CERT_FORMAT_DER		1
#define GCC_CERT_FORMAT_PKCS12	2
#define GCC_CERT_FORMAT_CAPI		3
#define GCC_CERT_FORMAT_PASSWD	4
#define GCC_CERT_FORMAT_E2E_ENCRYPT	5

#ifndef MD5_DIGEST_LENGTH
#define MD5_DIGEST_LENGTH 16
#endif
#ifndef SHA1_DIGEST_LENGTH
#define SHA1_DIGEST_LENGTH			20
#endif

#pragma pack(4)

struct User_Key{
	uint32	user_certificate_len;
	uint8*	user_certificate;
	uint32	user_private_key_len;
	uint8*	user_private_key;
	char*	private_key_passwd;	// password to protected the private key};
};

struct User_PKCS12Object{
	uint8*	pkcs12_content;
	uint32	pkcs12_length;
	char*	pkcs12_password;
};

//{ 10/28/2005, added by folki
typedef  int32 (*pfnEncryptKey)(
							uint8		bDER,
							uint8*	attendee_cert,
							uint32	attendee_cert_len,
							uint8*	session_key,
							uint32	session_key_len,
							uint8*	encrypted_key,
							uint32*	encrypted_key_len);

typedef int32(*pfnDecryptKey)(
							uint8*	encrypted_key,
							uint32	encrypted_key_len,
							uint8*	decrypted_key,
							uint32*	decrypted_key_len);

struct CAPI_Object
{
	pfnEncryptKey	EncryptFn;
	pfnDecryptKey	DecryptFn;
	uint8*			user_cert;
	uint32			cert_len;
	boolean			bDER;
};
//}

// 10/09/2005, modified by folki
struct PKI_Data{
	char*	root_certificate_list;		//root CA list, PEM format, as the format " issue1:cert1:issue2:cert2"
	uint8	user_certificate_format;	//0-PEM,1-DER,2- PKCS#12, 3: CAPI, 4: don't exchange key, all user create key by password
	union{
		User_Key 		  key;
		User_PKCS12Object pkcs;
		CAPI_Object		  capi;
		char*			  passwd;
		GCC_User_Data		mpw;
	}userinfo;
	uint16	conf_key_length;			//128 or 256 bits,default is 256
};

#pragma pack()

#ifndef __EUREKA_CLIENT_SDK_DEFINE__
#define __EUREKA_CLIENT_SDK_DEFINE__
typedef enum {
     CIPHER_BLOCK = 0,
     CIPHER_STREAM,
} GCC_Cipher_Mode;

enum{
	GCC_CONFERENCE_TYPE_NBR = 1,
	GCC_CONFERENCE_TYPE_LIC = 2,
	GCC_CONFERENCE_TYPE_PKI = 4,
};

//{ 11/16/2007, Folki+
// send data flags
#define GCC_SDF_GOBY_CB			(1 << 0)
#define GCC_SDF_GOBY_P2P		(1 << 1)
#define GCC_SDF_GOBY_CB_OR_P2P	(GCC_SDF_GOBY_CB | GCC_SDF_GOBY_P2P)
#define GCC_SDF_NEED_NBR		(1 << 2)    //Henry				

#define GCC_SD_VIA_CB			GCC_SDF_GOBY_CB
//}
#endif
//}

//wallice add for sas
typedef struct
{
   char	macc_address[GCC_MAX_MACC_ADDR_LENGTH];
   uint32  telephony_conference_id;
}GCC_SAS_Key;


//#define	GCC_MAX_MCT_CONF_ID	2000
//
//////////////////////////////////////////////////////////////////////////////
// class diagram
//
class GCC_Node_Controller_SAP_Sink;
class ARM_APE_Sink;

class GCC_Provider;
class ARM_APE;

//////////////////////////////////////////////////////////////////////////////
// GCC_Node_Controller_SAP_Sink
//
class GCC_Node_Controller_SAP_Sink
{
public :
   virtual GCC_Error on_ping_confirm(
      boolean                     to_create,
      WBXCONFID&                      conference_id,
      Transport_Address           cb_address,
      Transport_Address           gateway_address,
      Transport_Address           top_cb_address,
      Ping_Result                 result) { return GCC_ERROR_NOERR; }

   virtual GCC_Error on_conference_create_confirm(
      char*                       conference_name,
      char*                       conference_key,
      WBXCONFID                      conference_id,
      GCC_Node_ID                 local_node_id,
      GCC_Node_ID                 sup_node_id,
      GCC_Node_ID                 top_node_id,
      uint16                      num_of_resource,
      GCC_Resource**              resource_list,
      GCC_Result                  result) = 0;

   virtual GCC_Error on_conference_join_confirm(
      char*                       conference_name,
      char*                       conference_key,
      WBXCONFID                      conference_id,
      boolean                     conference_is_locked,
      GCC_Node_ID                 local_node_id,
      GCC_Node_ID                 sup_node_id,
      GCC_Node_ID                 top_node_id,
      uint16                      num_of_resource,
      GCC_Resource**              resource_list,
      GCC_Result                  result) = 0;

   virtual GCC_Error on_conference_disconnect_confirm(
      WBXCONFID&                      conference_id,
      GCC_Result                  result) = 0;

   virtual GCC_Error on_conference_disconnect_indication(
      WBXCONFID&                      conference_id,
      GCC_Reason                  reason,
      GCC_Node_ID                 disconnecting_node_id) = 0;

   virtual GCC_Error on_conference_terminate_confirm(
      WBXCONFID&                      conference_id,
      GCC_Result                  result) = 0;

   virtual GCC_Error on_conference_terminate_indication(
      WBXCONFID&                      conference_id,
      GCC_Node_ID                 requesting_node_id,
      GCC_Reason                  reason) = 0;

   virtual GCC_Error on_conference_lock_report_indication(
      WBXCONFID&                      conference_id,
      boolean                     conference_is_locked) = 0;

   virtual GCC_Error on_conference_parameter_change_indication(
      WBXCONFID&                      conference_id,
      uint16                      num_of_resource,
      GCC_Resource_Update_Record** update_rsc_list) = 0;

   virtual GCC_Error on_conference_eject_user_confirm(
      WBXCONFID&                      conference_id,
      GCC_Node_ID                 ejected_node_id,
      GCC_Result                  result) = 0;

   virtual GCC_Error on_conference_eject_user_indication(
      WBXCONFID&                      conference_id,
      GCC_Node_ID                 ejected_node_id,
      GCC_Reason                  reason) = 0;

   virtual GCC_Error on_conference_announce_presence_confirm(
      WBXCONFID&                      conference_id,
      GCC_Result                  result) = 0;

   virtual GCC_Error on_conference_roster_report_indication(
      WBXCONFID&                      conference_id,
      uint16                      number_of_total_nodes,
      uint16                      number_of_node_instances,
      uint16                      number_of_added_nodes,
      uint16                      number_of_removed_nodes,
      GCC_Node_Record**           node_list) = 0;

   virtual GCC_Error on_host_change_indication(
      WBXCONFID&                      conference_id,
      uint32                      host_node_id) = 0;

   virtual GCC_Error on_host_assign_confirm(
      WBXCONFID&                      conference_id,
      uint32                      recipient_node_id,
      GCC_Result                  result) = 0;

   virtual GCC_Error on_presentor_change_indication(
      WBXCONFID&                      conference_id,
      uint32                      presenter_node_id) = 0;

   virtual GCC_Error on_presentor_assign_confirm(
      WBXCONFID&                      conference_id,
      uint32                      recipient_node_id,
      GCC_Result                  result) = 0;

   virtual GCC_Error on_message_indication(
      WBXCONFID&                      conference_id,
      GCC_Node_ID                 from_node_id,
      GCC_Node_ID                 dest_node_id,
      uint8*                      message,
      uint32                      message_length) = 0;

   virtual GCC_Error on_session_create_confirm(
      WBXCONFID&                      conference_id,
      uint32                      req_handle,
      GCC_Session_Key*            session_key,
      uint16                      num_of_resource,
      GCC_Resource**              resource_list,
      GCC_Result                  result) = 0;

   virtual GCC_Error on_session_create_indication(
      WBXCONFID&                      conference_id,
      GCC_Session_Key*            session_key,
      uint16                      num_of_resource,
      GCC_Resource**              resource_list,
      GCC_Node_ID                 initiator_node) = 0;

   virtual GCC_Error on_session_close_indication(
      WBXCONFID&                      conference_id,
      GCC_Session_Key*            session_key,
      GCC_Reason                  reason) = 0;

   virtual GCC_Error on_flow_control_alarm(
      WBXCONFID&                      conference_id,
      MCS_Node_ID                 initiator_node,
      uint16                      number_of_nodes,
      MCS_Node_ID*                node_list,
      uint16                      number_of_priorities,
      MCS_Flow_Control_Alarm_Status* status) { return 0; }

   virtual GCC_Error on_misc_msg_indication(
      uint32                      msg_type,
      uint32                      msg_data
      ) { return 0; }

  

	//{ 11/12/2007, Folki+ for dynamic channel
	virtual GCC_Error on_channel_join_confirm(
		WBXCONFID&							conf_id,
		MCS_Channel_ID					chan_id,
		GCC_Result						result)
	{
		return 0;
	}
	//}
};

//////////////////////////////////////////////////////////////////////////////
// ARM_APE_Sink
//
class ARM_APE_Sink
{
public :
   virtual ARM_Error on_detach_indication(
      GCC_Session_Key*            session_key,
      GCC_Reason                  reason) = 0;

   virtual ARM_Error on_session_enroll_confirm(
      GCC_Session_Key*            session_key,
      GCC_Result                  result) = 0;

   virtual ARM_Error on_session_parameter_change_indication(
      GCC_Session_Key*            session_key,
      uint16                      num_of_resource,
      GCC_Resource_Update_Record** update_rsc_list) = 0;

   virtual ARM_Error on_data_indication(
      GCC_Session_Key*            session_key,
      MCS_User_ID                 sender_id,
      MCS_Channel_ID              channel_id,
      boolean                     uniform,
      MCS_Priority                priority,
      uint8*                      data,
      uint32                      data_length) = 0;
   virtual ARM_Error on_data_indication_h264_data(
	   GCC_Session_Key*            session_key,
	   MCS_User_ID                 sender_id,
	   MCS_Channel_ID              channel_id,
       MCS_Priority                priority,
	   uint8*              user_data,
	   uint32              user_data_length,
	   uint32               frame_tag,
	   uint32				data_type){return 0;}
	//jamie add for mobile gateway
   virtual ARM_Error on_data_indication_flv(
      GCC_Session_Key*            session_key,
      MCS_User_ID                 sender_id,
      MCS_Channel_ID              channel_id,
      boolean                     uniform,
      MCS_Priority                priority,
      uint8*                      data,
      uint32                      data_length,
      uint32               tag_flag) {return 0;}

   virtual ARM_Error on_applicaiton_roster_report_indication(
      GCC_Session_Key*            session_key,
      uint16                      number_of_total_entities,
      uint16                      number_of_entity_instances,
      uint16                      number_of_added_entities,
      uint16                      number_of_removed_entities,
      GCC_APE_Record**            entity_list) = 0;

   virtual ARM_Error on_token_grab_confirm(
      MCS_Token_ID                token_id,
      uint16                      result) = 0;

   virtual ARM_Error on_token_inhibit_confirm(
      MCS_Token_ID                token_id,
      uint16                      result) = 0;

   virtual ARM_Error on_token_test_confirm(
      MCS_Token_ID                token_id,
      uint16                      result) = 0;

   virtual ARM_Error on_token_please_indication(
      MCS_Token_ID                token_id,
      MCS_User_ID                 requestor) = 0;

   virtual ARM_Error on_token_give_indication(
      MCS_Token_ID                token_id,
      MCS_User_ID                 sender_id) = 0;

   virtual ARM_Error on_token_give_confirm(
      MCS_Token_ID                token_id,
      uint16                      result) = 0;

   virtual ARM_Error on_handle_allocate_confirm(
      uint16                      number_of_handles,
      uint32                      handle_value,
      GCC_Result                  result) = 0;

   virtual ARM_Error on_cache_set_confirm(
      uint32                      cache_handle,
      GCC_Result                  result) = 0;

   virtual ARM_Error on_cache_retrive_confirm(
      uint32                      cache_handle,
      GCC_Result                  result,
      uint8*                      data,
      uint32                      data_length) = 0;

   virtual ARM_Error on_flow_control_send_ready() { return 0; }

   virtual ARM_Error on_misc_msg_indication(
      uint32                      msg_type,
      uint32                      msg_data
      ) { return 0; }

   virtual ARM_Error on_data_indication_ex(
      GCC_Session_Key*            session_key,
      MCS_User_ID                 sender_id,
      MCS_Channel_ID              channel_id,
      boolean                     uniform,
      MCS_Priority                priority,
      uint8*                      data,
      uint32                      data_length,
      uint8*                      opt_data,
      uint32                      opt_data_length) { return 0; };

	//{ 20060810, Folki+ for Eureka 4.0 Chat/Polling Cache Design
	virtual ARM_Error on_namehandle_allocate_confirm(
      uint16					      number_of_handles,
      NameHandle*						name_handle_list,
      GCC_Result					   result){ return 0; };

	virtual ARM_Error on_cache_action_confirm_ex(
      uint32					cache_handle,
		CacheAction				cache_action,
		uint32					reqeust_idx,
		uint32					cache_id,
      GCC_Result				result){ return 0; };
	
	virtual ARM_Error on_cache_retrieve_confirm_ex(
		uint32							cache_handle,
		uint32							group_id,
		uint32							reqeust_idx,
		uint32							cache_id,
		CacheAction						cache_action,
		GCC_Result						result,
		MCS_Priority					priority,
		uint8*							data,
		uint32							data_length){ return 0; };
	//}
};

//////////////////////////////////////////////////////////////////////////
// GCC_Cache_Sink
//
class GCC_ARM_Cache_Sink
{
public:
	virtual ARM_Error on_namehandle_allocate_confirm(
      uint16					      number_of_handles,
      NameHandle*						name_handle_list,
      GCC_Result					   result) = 0;

	virtual ARM_Error on_cache_action_confirm_ex(
      uint32					cache_handle,
		CacheAction				cache_action,
		uint32					reqeust_idx,
		uint32					cache_id,
      GCC_Result				result) = 0;

	virtual ARM_Error on_cache_retrieve_confirm_ex(
		uint32							cache_handle,
		uint32							group_id,
		uint32							reqeust_idx,
		uint32							cache_id,
		CacheAction						cache_action,
		GCC_Result						result,
		MCS_Priority					priority,
		uint8*							data,
		uint32							data_length) = 0;
};



// --> andrew 2007-12-17, add for cascading task in T27
class CAS_APE_Sink
{
public :
	virtual GCC_Error on_detach_indication(
		GCC_Session_Key* session_key,
		GCC_Reason          reason) = 0;

	virtual GCC_Error on_data_indication_ex(
		GCC_Session_Key* session_key,
		MCS_User_ID         sender_id,
		MCS_Channel_ID      channel_id,
		boolean             uniform, //////
		MCS_Priority        priority,
		uint8*              user_data,
		uint32              user_data_length,
		uint8*              opt_data,
		uint32              opt_data_length) = 0;

	virtual GCC_Error on_data_indication(
		GCC_Session_Key* session_key,
		MCS_User_ID         sender_id,
		MCS_Channel_ID      channel_id,
		boolean             uniform, //////
		MCS_Priority        priority,
		uint8*              user_data,
		uint32              user_data_length) = 0;

	virtual GCC_Error on_enroll_confirm(
		GCC_Session_Key* session_key,
		GCC_Result          result) = 0;
};
class CAS_APE
{
public:
	virtual ARM_Error enroll_session(
		GCC_Session_Key*   session_key) = 0;
	
	virtual ARM_Error detach() = 0;
	
};
// <--andrew, 2007-12-17

//////////////////////////////////////////////////////////////////////////////
// GCC_Provider
//
class GCC_Provider
{
public :
   virtual GCC_Error destroy() = 0;

   virtual GCC_Error register_node_controller_application(
      void*                   gpc_cookie,
      void*                   gpc_interface,
      GCC_Node_Type           node_type,
      uint32                  capabilities_mask,
      GCC_Node_Controller_SAP_Sink* node_control_sap_sink) = 0;

  
	  
	virtual GCC_Error ping_request(
      boolean                 create_or_join,
      char*                   conference_name,
      char*                   conference_key,
      wbxConfId&              conference_id,
      uint32                  site_id,
      uint32                  user_id,
      uint16                  est_num_of_attendees,
      uint16                  num_of_ping_svrs,
      char**                  ping_server_list){return 0;};
	
	
	  
	virtual GCC_Error conference_create_request(
      char*                   conference_name,
      char*                   conference_key,
      wbxConfId&              conference_id,
      char*                   conference_password,
      boolean                 conference_is_locked,
      uint32                  site_id,
      uint32                  user_id,
      char*                   user_name,
      char*                   user_password,
      Transport_Address       local_address,
      Transport_Address       destination_address,
      Transport_Address       gateway_address,
      uint16                  num_of_resource,
      GCC_Resource**          resource_list,
      uint8*                  user_data,
      uint32                  user_data_length){return 0;};
   //{ 09/19/2005 8:45,added by Folki for supporting PKI
   

   
   
   
   virtual GCC_Error conference_join_request(
      char*                   conference_name,
      char*                   conference_key,
      wbxConfId&              conference_id,
      char*                   conference_password,
      uint32                  site_id,
      uint32                  user_id,
      char*                   user_name,
      GCC_Enroll_Flag         enroll_flag,
      Transport_Address       local_address,
      Transport_Address       destination_address,
      Transport_Address       gateway_address,
      Transport_Address       top_address,
      uint8*                  user_data,
      uint32                  user_data_length,
      uint16                  num_of_resource = 0,
      GCC_Resource**          resource_list = NULL
   ){return 0;};

 
	  
   virtual GCC_Error conference_announce_presence_request(
      wbxConfId&              conference_id,
      GCC_Enroll_Flag         enroll_flag,
      uint8*                  node_info,
      uint32                  node_info_length){return 0;};

  
   virtual GCC_Error conference_disconnect_request(
      wbxConfId&          conference_id, GCC_Reason reason = 0){return 0;};

	  
   virtual GCC_Error conference_terminate_request(
      wbxConfId&              conference_id,
      GCC_Reason              reason = 0){return 0;};

  
	  
   virtual GCC_Error conference_parameter_set_request(
      wbxConfId&              conference_id,
      uint16                  num_of_resource,
      GCC_Resource_Update_Record** update_rsc_list){return 0;};

   
	  
   virtual GCC_Error conference_eject_user_request(
      wbxConfId&              conference_id,
      GCC_Node_ID             ejected_node_id,
      GCC_Reason              reason){return 0;};

   
   virtual GCC_Error conference_lock_request(
      wbxConfId&              conference_id){return 0;};

  
	  
   virtual GCC_Error conference_unlock_request(
      wbxConfId&              conference_id){return 0;};
	  
   virtual GCC_Error conference_lock_request_s(WBXCONFID& conference_id,
											    uint32  num_of_res,
											    GCC_Resource** res_list){return 0;};
	  
   virtual GCC_Error conference_unlock_request_s(WBXCONFID& conference_id,
												  uint32  num_of_res,
												  GCC_Resource** res_list){return 0;};
												  
   virtual GCC_Error conference_terminate_request_s(WBXCONFID& conference_id,
												   GCC_Reason reason,
												   uint32  num_of_rsc,
												   GCC_Resource** rsc_list){return 0;};

	//{ 20070123, Folki, changed for new secure hostkey design


   virtual GCC_Error host_assign_request(
      wbxConfId&              conference_id,
      GCC_Node_ID             recipient_node_id,
		uint16						num_of_resource = 0,
		GCC_Resource**				resource_list = NULL){return 0;};
	//}


	  
   virtual GCC_Error presentor_assign_request(
      wbxConfId&              conference_id,
      GCC_Node_ID             recipient_node_id){return 0;};

   virtual GCC_Error presentor_assign_request(
		wbxConfId& conference_id, 
		GCC_Node_ID recipient_node_id, 
		uint32 option, 
		uint8* key, 
		uint32 key_len){return 0;};
	

	  
	  virtual GCC_Error send_message_request(
      wbxConfId&              conference_id,
      GCC_Node_ID             dest_node_id,
      uint8*                  message_data,
      uint32                  message_length
#ifndef __SERVER__	  
	  ,
      uint32                  flag = GCC_SDF_GOBY_CB
#endif
	  ){return 0;};

  
	  
   virtual GCC_Error session_create_request(
      wbxConfId&              conference_id,
      uint32                  req_handle,
      GCC_App_Protocol_Type   protocol_type,
      uint16                  num_of_resource,
      GCC_Resource**          resource_list,
      uint8*                  user_data,
      uint32                  user_data_length){return 0;};

   
	  
   virtual GCC_Error session_close_request(
      wbxConfId&              conference_id,
      GCC_Session_Key*        session_key,
      uint16                  num_of_resource = 0,
      GCC_Resource**          resource_list = NULL){return 0;};  
	  
   virtual GCC_Error flow_control_set(
      wbxConfId&              conference_id,
      MCS_Priority            priority,
      uint32                  yellow_alarm_buffer_size,
      uint32                  red_alarm_buffer_size){return 0;};

   
	
   virtual GCC_Error arm_ape_attach(
      wbxConfId&              conference_id,
      ARM_APE_Sink*           arm_ape_sink,
      ARM_APE**               arm_ape){return 0;};

   virtual GCC_Error config(
      uint32                  config_type,
      uint32                  config_data) = 0;
   //{ 09/19/2005, added by Folki for PKI
   virtual GCC_Error encrypt(
		uint32 conf_id,
		uint32 length, //in parameter
		const uint8* data, //in parameter
		uint32& encrypted_data_len, //out parameter
		uint8*& encrypted_data, //the encrypted data, out
		int cipher_mode = CIPHER_STREAM //in parameter
		){return 0;};

   virtual GCC_Error decrypt(
		uint32 conf_id,
		uint32 length, //in parameter
		uint8* data, //in parameter
		uint32& decrypted_data_len, //out parameter
		uint8*& decrypted_data, //decrypted data, out parameter
		int cipher_mode = CIPHER_STREAM //in parameter
		){return 0;};

	virtual void free_data(uint8* data){};
	//}

	//{ 10/09/2005, added by folki
	virtual GCC_Error verify_user_certificate(
		char*		root_CA_list,
		uint8		user_cert_format,
		uint8*	user_cert,
		uint32	user_cert_length,
		char*		password = NULL
		){return 0;};
	//}

	//{ 20070321, Folki+ for Eureka 4.0 Chat/Polling Cache Design
	virtual GCC_Error namehandle_allocate_request(
		wbxConfId&						conference_id,
		uint16							number_of_handles,
		NameHandle*						name_handle_list){return 0;};

	virtual GCC_Error cache_retrieve_request_ex(
		wbxConfId&							conference_id,
		uint32							cache_handle,
		uint32							cache_id,//0 is to get all cache data, 	>0 is to get one segment of cache data
		CacheRequestType				request_type,
		MCS_Priority					priority){return 0;};

	virtual GCC_Error cache_action_request_ex(
		wbxConfId&						conference_id,
		uint32							cache_handle,
		uint32							group_id,
		uint32							reqeust_idx,
		uint32							cache_id,
		CacheAction						action,
		uint32							option,
		MCS_Priority					priority,
		uint8*							data,
		uint32							data_length){return 0;};

	virtual GCC_Error set_cache_sink(
		wbxConfId&				conference_id,
		GCC_ARM_Cache_Sink*			sink){return 0;};

	
	//}

 /*  virtual GCC_Error app_server_register_request(
      GCC_App_Protocol_Type   protocol_type,
      Transport_Address       destination_address
      ) = 0;
   */

	//{ 11/12/2007, Folki+ for dynamic channel
	virtual GCC_Error channel_join_request(
		uint32			conf_id,
		MCS_Channel_ID chan_id
		){return GCC_ERROR_VERSION_NOT_SUPPORTED;}

	virtual GCC_Error channel_leave_request(
		uint32			conf_id,
		MCS_Channel_ID chan_id
		){return GCC_ERROR_VERSION_NOT_SUPPORTED;}
	//}
};

/////////////////////////////////////////////////////////////////////////////
// ARM_APE
//
class ARM_APE
{
public :
   virtual ARM_Error detach() = 0;

   // for session resource, only channel join/leave is allowed in this
   // function
   virtual ARM_Error session_enroll_request(
      GCC_Session_Key*            session_key,
      uint16                      num_of_resource,
      GCC_Resource_Update_Record** update_rsc_list,
      GCC_Enroll_Flag             enroll_flag,
      uint8*                      ape_info,
      uint32                      ape_info_length) = 0;

   // only parameter/token is allowed in this function
   virtual ARM_Error session_parameter_set_request(
      GCC_Session_Key*            session_key,
      uint16                      num_of_resource,
      GCC_Resource_Update_Record** update_rsc_list) = 0;

   virtual ARM_Error send_data_request(
      MCS_Channel_ID              channel_id,
      MCS_Priority                priority,
      uint8*                      data,
      uint32                      data_length,
      boolean                     uniform,
      uint32                      flag = GCC_SDF_GOBY_CB) = 0;
   //Henry add for telepresenter
   virtual ARM_Error send_data_request_h264_data(
	   MCS_Channel_ID              channel_id,
	   MCS_Priority                priority,
	   uint8					   data_type, //mouse or frame
	   uint32					   frame_tag, //sequence of frames	   
	   uint8*                      data,
	   uint32                      data_length,
	   uint32					   flags = GCC_SDF_GOBY_CB){return 0;}  
   virtual ARM_Error send_data_request_h264_cmd(
	   MCS_Channel_ID channel_id, 
	   MCS_Priority priority,
	   GCC_MiscMsg_H264Cmd* pCmd){return 0;}
   //weixin, 04192007, flash
   virtual ARM_Error send_data_request_flv(
        MCS_Channel_ID              channel_id,
        MCS_Priority                priority,
        uint8*                      data,
        uint32                      data_length,
        boolean                     uniform,
        uint32 						tag_flag){return 0;}

   virtual ARM_Error token_grab_request(
      MCS_Token_ID                token_id) = 0;

   virtual ARM_Error token_inhibit_request(
      MCS_Token_ID                token_id) = 0;

   virtual ARM_Error token_release_request(
      MCS_Token_ID                token_id) = 0;

   virtual ARM_Error token_test_request(
      MCS_Token_ID                token_id) = 0;

   virtual ARM_Error token_please_request(
      MCS_Token_ID                token_id) = 0;

   virtual ARM_Error token_give_request(
      MCS_Token_ID                token_id,
      MCS_User_ID                 receiver_id) = 0;

   virtual ARM_Error token_give_response(
      MCS_Token_ID                token_id,
      int32                       result) = 0;

   virtual ARM_Error handle_allocate_request(
      uint16                      number_of_handles) = 0;

   virtual ARM_Error cache_set_request(
      uint32                      cache_handle,
      uint32                      group_id,
      uint8*                      data,
      uint32                      data_length) = 0;

   virtual ARM_Error cache_set_first_request(
      uint32              cache_handle) = 0;

   virtual ARM_Error cache_clear_request(
      uint32                      cache_handle) = 0;

   virtual ARM_Error cache_clear_all_request(
      uint32                      group_id) = 0;

   virtual ARM_Error cache_retrive_request(
      uint32                      cache_handle) = 0;

   virtual ARM_Error cache_retrive_first_request(
      uint32              cache_handle) = 0;

   virtual ARM_Error cache_retrive_cancel_request(
      uint32              cache_handle) = 0;

   virtual ARM_Error cache_retrive_cancel_all_request(
      uint32              group_id) = 0;

   virtual ARM_Error flow_control_set(
      uint32              max_buffer_size) = 0;

   virtual ARM_Error flow_control_flush(
      MCS_Channel_ID		channel_id,
      MCS_Priority		priority) = 0;

   virtual MCS_User_ID get_ape_user_id() = 0;

   virtual GCC_Node_ID get_node_id() = 0;

   virtual GCC_Resource* get_session_resource(
      GCC_Session_Key*    session_key,
      GCC_Resource_Key*   rsc_key) = 0;

   virtual GCC_Error config(
      uint32                  config_type,
      uint32                  config_data) = 0;

   virtual ARM_Error send_data_request_ex(
      MCS_Channel_ID              channel_id,
      MCS_Priority                priority,
      uint8*                      data,
      uint32                      data_length,
      uint8*                      opt,
      uint32                      opt_length,
      boolean                     uniform,
      boolean                     bBuffer,//weixin, 02092006, buffer
      uint32                      flag = GCC_SDF_GOBY_CB) { return 0;}

	//{ 20060810, Folki+ for Eureka 4.0 Chat/Polling Cache Design
	virtual ARM_Error namehandle_allocate_request(
		uint16							number_of_handles,
		NameHandle*						name_handle_list) = 0;

	virtual ARM_Error cache_action_request_ex(
		uint32							cache_handle,
		uint32							group_id,
		uint32							reqeust_idx,
		uint32							cache_id,
		CacheAction						action,
		uint32							option,
		MCS_Priority               priority,
		uint8*							data,
		uint32							data_length) = 0;

	virtual ARM_Error cache_retrieve_request_ex(
		uint32						cache_handle,
		uint32						cache_id,//0 is to get all cache data, 	>0 is to get one segment of cache data
		CacheRequestType			request_type,
		MCS_Priority				priority) = 0;
	//}
};

extern "C" void gcc_create_provider(GCC_Provider** provider);
extern "C" void gcc_heart_beat();
extern "C" int gcc_start_ssr(boolean bRecord, char* file_path);
extern "C" void gcc_stop_ssr();
//Oliver,20070124, for GW project
extern "C" void gcc_create_provider_ex(GCC_Provider** provider); 
extern "C" void gcc_destroy_provider_ex(GCC_Provider* provider); 
//end


#ifdef MACOS
extern "C" unsigned char* wbx_MD5(const unsigned char *content_data, unsigned long content_data_length,
					unsigned char *result_data);
#endif

typedef struct
{
	uint16	num_of_ping_svrs;
	char**	ping_server_list;
} WbxArmMzmAddress;

typedef struct
{
	Transport_Address	destination_address;
	Transport_Address	gateway_address;
	Transport_Address	top_address;
} WbxArmCBAddress;

typedef struct
{
	boolean	mzm_or_cb;	// true for mzm, false for cb
	union
	{
		WbxArmMzmAddress	mzm_addr;
		WbxArmCBAddress		cb_addr;
	} u;
	uint16	connect_times;
	uint16	connect_timeout;	// in second
	uint16	reconnect_times;
	uint16	reconnect_timeout;	// in second
} WbxArmServerAddress;

typedef struct
{
	char*		conference_name;
	char*		conference_key;
	WBXCONFID		conference_id;
	char*		conference_password;
	uint32		site_id;
	uint32		user_id;
	char*		user_name;
	uint16		est_num_of_attendees;
} WbxArmConfAttribute;

typedef struct
{
	boolean		conference_is_locked;
	char*		user_password;
} WbxArmConfCreateOption;

typedef ARM_Error (*ArmCallback)(void* user_data, WBXCONFID& conference_id, uint16 msg, void* lparam1);

#define Arm_Callback_Message_Conf_Joined		1
#define Arm_Callback_Message_Conf_Rejoining		2
#define Arm_Callback_Message_Conf_Rejoined		3

typedef struct
{
	GCC_Result			result;
	boolean				create_or_join;
	GCC_Node_ID			local_node_id;
	GCC_Node_ID			sup_node_id;
	GCC_Node_ID			top_node_id;
	uint16				num_of_resource;
	GCC_Resource**		resource_list;
} WbxArmCallbackJoined;

typedef struct
{
	uint32				reason;
} WbxArmCallbackRejoining;

ARM_Error gcc_join_conference(
	Transport_Address			local_address,
	WbxArmServerAddress*		server_addr,
	WbxArmConfAttribute*		conf_attrib,
	boolean						create_or_join,	// true for create, false for join
	WbxArmConfCreateOption*		conf_create_option,
	uint16						num_of_resource,
	GCC_Resource**				resource_list,
	uint8*						user_data,
	uint32						user_data_length,
	GCC_Enroll_Flag				enroll_flag,
	uint8*						node_info,
	uint32						node_info_length,
	ArmCallback					callback,
	void*						user_defined);

ARM_Error gcc_rejoin_conference(
	uint32                  conference_id);

#endif /* __GCC_H__ */
