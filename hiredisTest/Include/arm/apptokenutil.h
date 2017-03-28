#ifndef _APPTOKENUTIL_H_
#define _APPTOKENUTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define	MAX_TOKEN_LENGTH		128

#define APPTOKEN_LOG_CRIT		0
#define APPTOKEN_LOG_ERROR		1
#define APPTOKEN_LOG_WARN		2
#define APPTOKEN_LOG_INFO		3
#define APPTOKEN_LOG_DEBUG		4

typedef void (*APPTOKEN_LOGGER_FUNC)(int level, const char * msg);

int AppTokenUtil_Init(APPTOKEN_LOGGER_FUNC logger_func);

int AppTokenUtil_MakeTicket(const char * appname, char * token);

int AppTokenUtil_VerifyTicket(const char * appname, const char * token);

#ifdef KM
#define TEST_SAFENET_ERR_REASON_MAX_LENGTH		1024
int AppTokenUtil_TestSafeNet(char * errReason);
#endif

#ifdef __cplusplus
}
#endif

#endif
