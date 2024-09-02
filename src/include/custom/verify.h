#ifndef VERIFY_H
#define VERIFY_H

#include "json.h"
#include "curl.h"
#include "../../jwt/jwt.hpp"
#include <sys/ioctl.h>
#include <sys/socket.h>
<<<<<<< HEAD
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
=======
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

>>>>>>> 377ae5902800f3c14b45d3906ad1c300c98cd651
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

<<<<<<< HEAD
vector<string> Split(string input, char dlim);
int GetConnectedIp(std::string &buf);
std::string ReadFileToString(const std::string &filename);
bool is_interface_connected(const std::string &interface_name);
=======
vector<string>      split(string input, char dlim);
int                 getConnectedIp(std::string& ip);
bool is_interface_connected(const std::string &interface_name);
std::string         readFileToString(const std::string& filename) ;


>>>>>>> 377ae5902800f3c14b45d3906ad1c300c98cd651
#endif
