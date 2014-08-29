#ifndef __SERVER_H__
#define __SERVER_H__

#include "appframe/application.hpp"
#include "gce/xsocket/connectioninfo.hpp"
#include "gce/xsocket/active_reactor.hpp"
#include "app_processor.h"
#include <unistd.h>

class EchoServer : public Application
{
    public:
        EchoServer(int argc, char** argv);
        ~EchoServer();
        int get_home_path();

    protected:
        int impl_init();
        void run();
    
    private:
        gce::ActiveReactor<gce::ConnectionInfo>* _active_reactor;
        FixedSizeAllocator* _fix_size_allocator;
};

#endif //__SERVER_H__
