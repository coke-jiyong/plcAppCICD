#ifndef VERIFY_H
#define VERIFY_H

#include "json.h"
#include "curl.h"
#include "../../jwt/jwt.hpp"
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>

#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

class Verify
{
private:
    Json::Value ver_json;
    CURL_Handler curl_handle;
    Json::StyledWriter writer;
    string json_str;
    string response;
    Json::Value root;

public:
    Verify(const char *_otac);
    Verify();
    bool SetHostIp();
    void SetPost(const char *url);
    void Request();
    Json::Value GetRoot();
    std::string GetResponse();
    Json::String GetData();
    const char *GetIp();
};

using namespace jwt::params;
class CheckLicense
{
public:
    CheckLicense(const std::string _pub_key_path, const std::string _token_path)
        : pub_key_path(_pub_key_path), token_path(_token_path)
    {
    }
    void Init();
    bool ValidateHostId(char *serial);

private:
    jwt::jwt_object dec_obj;
    const std::string pub_key_path;
    const std::string token_path;
    string payload;
    std::vector<string> v;
};

vector<string> Split(string input, char dlim);
int GetConnectedIp(std::string &buf);
std::string ReadFileToString(const std::string &filename);
bool IsInterfaceConnected(const std::string &interface_name);
#endif
