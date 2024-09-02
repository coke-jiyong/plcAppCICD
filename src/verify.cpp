#include "include/custom/verify.h"
#include <fstream>
Verify::Verify(const char *_otac)
{
    ver_json["otac"] = _otac;
    ver_json["pcDeviceId"] = "127.0.0.1";
    ver_json["systemId"] = "1";
    ver_json["apiKey"] = "PLC_567052367261557962726962304c69424b374546433867766b4a314a33715851";
    // ver_json["plcDeviceId"] = "127.0.0.1";
}

Verify::Verify()
{
    // cout << "input parameter(otac)"<< endl;
    return;
}

bool Verify::SetHostIp()
{
    std::string buf = "";
    int result = GetConnectedIp(buf);

    if (result == -1)
    {
        return false;
    }

    if (buf[buf.length() - 1] == '\n')
    {
        buf.erase(buf.length() - 1, 1);
    }

    ver_json["plcDeviceId"] = buf.c_str();
    return true;
}

void Verify::SetPost(const char *url)
{
    if (!curl_handle.init())
    {
        return;
    }
    curl_handle.set_header_content("Content-Type", "application/json");
    json_str = writer.write(ver_json);
    curl_handle.set_post(json_str);
    curl_handle.set_server_info(url);
}

void Verify::Request()
{
    if (curl_handle.request())
    {
        return;
    }
    response = curl_handle.response();
    Json::Reader reader;
    reader.parse(response, root);
}

Json::Value Verify::GetRoot() { return root; }

std::string Verify::GetResponse() { return response; }

const char *Verify::GetIp() { return ver_json["plcDeviceId"].asCString(); }

Json::String Verify::GetData() { return ver_json.toStyledString(); }

bool CheckLicense::ValidateHostId(char *serial)
{
    if (dec_obj.has_claim("hostId"))
    {

        this->payload = this->dec_obj.payload().get_claim_value<std::string>("hostId"); // payload serialNumber
        if (payload.find('|') != string::npos)
        {
            this->v = Split(this->payload, '|');
            for (int i = 0; i < this->v.size(); i++)
            {
                if (!this->v[i].compare(serial))
                    return true;
            }
            throw std::runtime_error("Your serial number does not exist in the license file.");
        }
        else
        {
            if (!this->payload.compare(serial))
                return true;
            throw std::runtime_error("Your serial number does not exist in the license file.");
        }
    }

    throw std::runtime_error("The 'hostId' does not exist in the payload.");
}

void CheckLicense::Init()
{
    std::string pub_key = ReadFileToString(this->pub_key_path);
    std::string token = ReadFileToString(this->token_path);

    if (token == "")
    {
        throw std::runtime_error("Failed to read token file.");
    }
    if (pub_key == "")
    {
        throw std::runtime_error("Failed to read public-key file.");
    }

    try
    {
        this->dec_obj = jwt::decode(token, algorithms({"RS256"}), verify(true), secret(pub_key));
    }
    catch (jwt::InvalidAlgorithmError &e)
    {
        throw std::runtime_error(e.what());
    }
    catch (jwt::TokenExpiredError &e)
    {
        throw std::runtime_error(e.what());
    }
    catch (jwt::InvalidIssuerError &e)
    {
        throw std::runtime_error(e.what());
    }
    catch (jwt::InvalidAudienceError &e)
    {
        throw std::runtime_error(e.what());
    }
    catch (jwt::InvalidSubjectError &e)
    {
        throw std::runtime_error(e.what());
    }
    catch (jwt::InvalidIATError &e)
    {
        throw std::runtime_error(e.what());
    }
    catch (jwt::InvalidJTIError &e)
    {
        throw std::runtime_error(e.what());
    }
    catch (jwt::ImmatureSignatureError &e)
    {
        throw std::runtime_error(e.what());
    }
    catch (jwt::InvalidSignatureError &e)
    {
        throw std::runtime_error(e.what());
    }
    catch (jwt::TypeConversionError &e)
    {
        throw std::runtime_error(e.what());
    }
    catch (jwt::SignatureFormatError &e)
    {
        throw std::runtime_error(e.what());
    }
    catch (jwt::KeyNotPresentError &e)
    {
        throw std::runtime_error(e.what());
    }
    catch (jwt::InvalidKeyError &e)
    {
        throw std::runtime_error(e.what());
    }
    catch (jwt::DecodeError &e)
    {
        throw std::runtime_error(e.what());
    }
}

vector<string> Split(string input, char dlim)
{
    vector<string> result;
    stringstream ss;
    string stringBuffer;
    ss.str(input);

    while (getline(ss, stringBuffer, dlim))
    {
        result.push_back(stringBuffer);
    }

    return result;
}

int GetConnectedIp(std::string &ip)
{
    int sockfd;
    struct ifconf ifc;
    char buf[1024];
    struct ifreq *ifr;
    int num_interfaces;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        return -1;
    }

    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;

    if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0)
    {
        perror("ioctl(SIOCGIFCONF)");
        close(sockfd);
        return -1;
    }

    num_interfaces = ifc.ifc_len / sizeof(struct ifreq);
    ifr = ifc.ifc_req;

    for (int i = 0; i < num_interfaces; ++i)
    {
        std::string iface_name(ifr[i].ifr_name);
        if (!iface_name.compare("lo"))
        {
            continue;
        }
        if (is_interface_connected(iface_name))
        {
            // std::cout << iface_name << std::endl;
            if (ioctl(sockfd, SIOCGIFADDR, &ifr[i]) < 0)
            {
                perror("ioctl(SIOCGIFADDR)");
                close(sockfd);
                return -1;
            }

            struct sockaddr_in *addr = (struct sockaddr_in *)&ifr[i].ifr_addr;
            ip = inet_ntoa(addr->sin_addr);
            break;
        }
    }

    close(sockfd);
    return 0;
}

bool is_interface_connected(const std::string &interface_name)
{
    int sockfd;
    struct ifreq ifr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        return false;
    }

    std::memset(&ifr, 0, sizeof(ifr));
    std::strncpy(ifr.ifr_name, interface_name.c_str(), IFNAMSIZ - 1);

    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0)
    {
        perror("ioctl");
        close(sockfd);
        return false;
    }

    // close(sockfd);
    // std::cout << "[ " << interface_name << " ]" << std::endl;
    // std::cout << interface_name << " 활성화: " << std::boolalpha << ((ifr.ifr_flags & IFF_UP) != 0) << std::endl;

    // std::cout << interface_name << " 연결: " << std::boolalpha << ((ifr.ifr_flags & IFF_RUNNING) != 0) << std::endl
    //           << std::endl;
    if (((ifr.ifr_flags & IFF_UP) != 0) && ((ifr.ifr_flags & IFF_RUNNING) != 0))
    {
        return true;
    }
    return false;
}

std::string ReadFileToString(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}
