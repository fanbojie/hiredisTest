#ifndef LITEBASE_OSADAPTER_H
#define LITEBASE_OSADAPTER_H

#include "Config.h"
#include "OSTypeDefine.h"

#ifdef __cplusplus
extern "C" {
#endif
    // �ֲ߳̾��洢��غ���
    // create��delete �����̰߳�ȫ��
    LITEBASE_DECL   int tlsKeyCreate(tls_key_t* key);
    LITEBASE_DECL   void tlsKeyDelete(tls_key_t* key);
    LITEBASE_DECL   void* tlsKeyGet(tls_key_t* key);
    LITEBASE_DECL   void tlsKeySet(tls_key_t* key, void* value);

    LITEBASE_DECL   void runOnce(base_once_t* guard, void (*callback)(void));

    LITEBASE_DECL   uint64_t hrTime();    
#ifdef __cplusplus
};
#endif

#endif
