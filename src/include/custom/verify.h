#ifndef VERIFY_H
#define VERIFY_H

#include "json.h"
#include "curl.h"
#include "../../jwt/jwt.hpp"
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

class Verify
{
    private:
        Json::Value         ver_json;
        CURL_Handler        curl_handle;
        Json::StyledWriter  writer;
        string              JsonStr;
        string              response;
        Json::Value         root;

    public:
        Verify(const char * _otac);
        Verify();
        bool                Set_Host_IP();
        void                Set_Post(const char* url);
        void                Request();
        Json::Value         Get_Root();
        std::string         Get_Response();
        Json::String        Get_Data();
        const char *        Get_Ip();
        
};


using namespace jwt::params;
class checkLicense {
public:
    checkLicense(const std::string _pub_key_path ,const std::string _token_path)
    : pub_key_path(_pub_key_path), token_path(_token_path) 
    {

    }
    void init();
    bool validateHostId(char * serial);
    

private:
    jwt::jwt_object     dec_obj;
    const std::string   pub_key_path;
    const std::string   token_path;
    string              payload;
    std::vector<string> v;
};

vector<string>      split(string input, char dlim);
int                 getConnectedIp(std::string& ip);
bool is_interface_connected(const std::string &interface_name);
std::string         readFileToString(const std::string& filename) ;


#endif
