//
//  $Id$
//
//  Copyright (c)1992-2013, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//    Description:    
//    Revisions:        Year-Month-Day      SVN-Author       Modification
//                        2014-03-27        fan_bojie            Create
//

#ifndef LITEBASE_BINARYBUFFER_H
#define LITEBASE_BINARYBUFFER_H

#include "Config.h"

namespace litebase
{
    namespace details
    {
        class LITEBASE_DECL CBinaryBuffer
        {
//             struct _BinaryBuffer
//             {
//                 int _pos;
//                 int _length;
//                 char* _buffer;
//             };

        public:
            CBinaryBuffer(int length);
            CBinaryBuffer();
            ~CBinaryBuffer();

            void resize(int size);
            void append(void* data, int size);
            void* dump(int pos=0);
            int getLength();
            int getSize();

        private:
            void updateLength(int length);

        private:
            int m_pos;
            int m_length;
            char* m_buffer;
        };
    }
}

#endif
