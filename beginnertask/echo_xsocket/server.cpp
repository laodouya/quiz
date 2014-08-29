#include "server.h"

//#include<iostream>

using namespace std;
using namespace gce;

EchoServer::EchoServer(int argc, char** argv):Application(argc,argv)
{
    //_home_path = "";
    _active_reactor = NULL;
}

EchoServer::~EchoServer()
{
    free(_active_reactor);
    free(_fix_size_allocator);
}

int EchoServer::get_home_path()
{
    char* path = getcwd(NULL, 0);
    if(NULL == path)
    {
        cerr<<"getcwd failed"<<endl;
        return -1;
    }
    
    _home_path = path;
    free(path);
    path = NULL;

    if(_home_path.empty())
    {
        cerr<<"getcwd empty"<<endl;
        return -1;
    }
    
    return 0;
}

int EchoServer::impl_init()
{
    int rv = 0;
    
    _fix_size_allocator = new FixedSizeAllocator(32*1024, 32*1024, 32*1024*1024); 
    _fix_size_allocator->init();
    
    _active_reactor = new ActiveReactor<ConnectionInfo>(_fix_size_allocator);
    rv = _active_reactor->init();
    if (rv<0)
    {
        cerr<<"active_reactor init fail"<<endl<<flush;
        return -1;
    }

    AppProcessor* app_processor = new AppProcessor();
    //add app acceptor
    rv = _active_reactor->add_acceptor(NULL, 10240, *app_processor, NULL);

    return 0;
}

void EchoServer::run()
{

}

int main(int argc, char* argv[])
{
    int ret = 0;
    EchoServer* server = new EchoServer(argc,argv);
    ret = server->init();
    
    if (0 == ret)
    {
        cout<<"start"<<endl;
        server->start();
    }
    else
    {
        cout<<"server init failed"<<endl;
    }

    delete server;
    return 0;
}
