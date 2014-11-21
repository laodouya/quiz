#include <magic.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
    const char * magicfile="/usr/share/file/magic";

    int flag = MAGIC_MIME_TYPE;
    magic_t magic = magic_open(flag);
    
    cout<<magic_version()<<endl;
    magic_load(magic, magicfile);
    
    ifstream in(argv[1], ios::in|ios::binary);
    int len = 1024;
    char* buff = new char[1024];
    in.read(buff, len);
    
    const char *ret = magic_buffer(magic, buff, len);
    
    if (NULL == ret)
    {
        cout<<"ret is null"<<endl;
        cout<<magic_error(magic)<<endl;
    }
    else
        printf("%s\n",ret);

    return 0;
}
