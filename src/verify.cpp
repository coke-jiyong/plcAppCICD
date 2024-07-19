#include "include/verify.h"

Verify::Verify(const char * _otac)
{
    ver_json["otac"] = _otac;
    ver_json["pcDeviceId"] = "127.0.0.1";
    ver_json["systemId"] = "1";
    ver_json["apiKey"] = "PLC_567052367261557962726962304c69424b374546433867766b4a314a33715851";
    //ver_json["plcDeviceId"] = "127.0.0.1";
}

Verify::Verify()
{
    //cout << "input parameter(otac)"<< endl;
    return;
}

bool Verify::Set_Host_IP()
{
    std::string buf = "";
    int result = getConnectedIp(buf);

    if(result == -1){ return false; }
    
    if(buf[buf.length()-1] == '\n') {
        buf.erase(buf.length()-1 , 1);
    }
    
    ver_json["plcDeviceId"] = buf.c_str();   
    return true;
}

void Verify::Set_Post(const char* url)
{
    if(!curl_handle.init()) {
        return;
    }
    curl_handle.set_header_content("Content-Type","application/json");
    JsonStr = writer.write(ver_json);
    curl_handle.set_post(JsonStr);
    curl_handle.set_server_info(url);
}

void Verify::Request()
{
    if (curl_handle.request()){
        return ;
    }
    response = curl_handle.response();
    Json::Reader reader;
    reader.parse(response, root);
}


Json::Value Verify::Get_Root(){ return root ; }

std::string Verify::Get_Response(){ return response ; }

const char* Verify::Get_Ip() { return ver_json["plcDeviceId"].asCString() ; }

Json::String Verify::Get_Data() { return ver_json.toStyledString() ; }



bool checkLicense::validateHostId(char * serial)
{   
    if (dec_obj.has_claim("hostId")) {
        
        this->payload = this->dec_obj.payload().get_claim_value<std::string>("hostId"); //payload serialNumber
        if (payload.find('|') != string::npos){
            this->v = split(this->payload , '|');
            for (int i = 0 ; i < this->v.size() ; i ++) {
                if(!this->v[i].compare(serial))
                    return true;
            }
            throw std::runtime_error("Your serial number does not exist in the license file.");
        }
        else{
            if(!this->payload.compare(serial))
                return true;
            throw std::runtime_error("Your serial number does not exist in the license file.");
        }
        
    }

    throw std::runtime_error("The 'hostId' does not exist in the payload.");
}

void checkLicense::init()
{   
    std::string pub_key = readFileToString(this->pub_key_path);
    std::string token = readFileToString(this->token_path);

    if(token == "") {
        throw std::runtime_error("Failed to read token file.");
    }
    if(pub_key == "") {
        throw std::runtime_error("Failed to read public-key file.");
    }
    
    try {
        this->dec_obj = jwt::decode(token, algorithms({"RS256"}), verify(true), secret(pub_key));
    }
	catch(jwt::InvalidAlgorithmError & e) {
		throw std::runtime_error(e.what());
	}
	catch(jwt::TokenExpiredError & e) {
		throw std::runtime_error(e.what());
	}
	catch(jwt::InvalidIssuerError & e) {
		throw std::runtime_error(e.what());
	}
	catch(jwt::InvalidAudienceError & e) {
		throw std::runtime_error(e.what());
	}
	catch(jwt::InvalidSubjectError & e) {
		throw std::runtime_error(e.what());
	}
	catch(jwt::InvalidIATError & e) {
		throw std::runtime_error(e.what());
	}
	catch(jwt::InvalidJTIError & e) {
		throw std::runtime_error(e.what());
	}
	catch(jwt::ImmatureSignatureError & e) {
		throw std::runtime_error(e.what());
	}
	catch(jwt::InvalidSignatureError & e) {
		throw std::runtime_error(e.what());
	}
	catch(jwt::TypeConversionError & e) {
		throw std::runtime_error(e.what());
	}
	catch(jwt::SignatureFormatError & e) {
		throw std::runtime_error(e.what());
	}
	catch(jwt::KeyNotPresentError & e) {
		throw std::runtime_error(e.what());
	}
	catch(jwt::InvalidKeyError & e) {
		throw std::runtime_error(e.what());
	}
	catch(jwt::DecodeError & e) {
		throw std::runtime_error(e.what());
	}
}





vector<string> split(string input, char dlim)
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




int getConnectedIp(std::string& buf) {

    std::string command = "ip -o link show | awk -F': ' '{print $2}' | awk -F'@' '{print $1}'";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) 
        return -1;
    
    char buffer[128];
    std::string result = "";

    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL) {
            result += buffer;
        }
    }
    pclose(pipe);

    // Parse the result and process each interface
    size_t pos = 0;
    std::string delimiter = "\n";
    std::string token;
    while ((pos = result.find(delimiter)) != std::string::npos) {
        token = result.substr(0, pos);
        std::string interface = token;

        // Check if the interface is connected
        std::string check_command = "ethtool " + interface + " 2>/dev/null | grep \"Link detected: yes\"";
        FILE* check_pipe = popen(check_command.c_str(), "r");
        if (!check_pipe) 
            return -1;
    
        char check_buffer[128];
        bool connected = false;
        while (!feof(check_pipe)) {
            if (fgets(check_buffer, 128, check_pipe) != NULL) {
                connected = true;
                break;
            }
        }
        pclose(check_pipe);
        
        if (connected) {
            if (interface != "lo") {
                // Get the IP address of the interface
                std::string ip_command = "ip addr show " + interface + " | grep \"inet\\b\" | awk '{print $2}' | cut -d/ -f1";
                FILE* ip_pipe = popen(ip_command.c_str(), "r");
                if (!ip_pipe) 
                    return -1;
    
                char ip_buffer[128];
                std::string ip_address = "";
                while (!feof(ip_pipe)) {
                    if (fgets(ip_buffer, 128, ip_pipe) != NULL) {
                        ip_address += ip_buffer;
                    }
                }
                pclose(ip_pipe);

                if (!ip_address.empty()) {
                    buf += ip_address;
                    return 0;
                }
            }    
        }
        // Move to the next interface
        result.erase(0, pos + delimiter.length());
    }
    return 0;
}


std::string readFileToString(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();  
    file.close();
    return buffer.str();  
}

