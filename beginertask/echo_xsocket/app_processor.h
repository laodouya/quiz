#ifndef __APP_PROCESSOR_H__
#define __APP_PROCESSOR_H__

#include "gce/xsocket/connectioninfo.hpp"
#include "gce/xsocket/imessageprocessor.hpp"

using namespace gce;

class AppProcessor: public IMessageProcessor
{
    public:
        AppProcessor();
        ~AppProcessor();
        virtual void accept(ConnectionInfo& conn);
        virtual void remove(ConnectionInfo& conn);
        virtual void process_input(ConnectionInfo& conn, IDatagram& gram);
        virtual void process_output();
        //TODO int send_datagram(uint32_t connid, 
};


#endif //APP_PROCESSOR_H__
