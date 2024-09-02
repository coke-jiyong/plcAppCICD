///////////////////////////////////////////////////////////////////////////////
//
//  Copyright PHOENIX CONTACT Electronics GmbH
//
///////////////////////////////////////////////////////////////////////////////
#include "Arp/System/Um/Commons/UmAuthenticationResult.hpp"
#include "include/ExampleAuthenticationProvider.hpp"
#include "include/UmModuleEx.hpp"
#include "include/UmModuleExConfig.hpp"

#include "Arp/System/Rsc/Services/RscString.hxx"
#include "Arp/System/Commons/Services/Security/IDeviceIdentityValidatorService.hpp"
#include "Arp/System/Commons/Services/Security/IdentityValidationError.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"
using namespace Arp::System::Rsc;
using namespace Arp::System::Rsc::Services;
using namespace Arp::System::Commons::Services::Security;
using namespace std;

namespace Arp
{
    namespace System
    {
        namespace UmModuleEx
        {
            ExampleAuthenticationProvider::ExampleAuthenticationProvider(UmModuleEx &_mod)
                : mod(_mod)
            {
                bool LicenseResult = true;
                const RscString<4096> pem(this->PEM.c_str());
                RscString<80> id("IDevID");

                IDeviceIdentityValidatorService::Ptr ptr;

                try
                {
                    ptr = ServiceManager::GetService<IDeviceIdentityValidatorService>();
                    result = ptr->Validate(pem, id);
                }
                catch (Arp::Exception &e)
                {
                    // log.Debug("OTACLicenseCheck: Arp::Exception=[ {0} ]" , e.GetMessage());
                    error_string_arp = e.GetMessage().CStr();
                    LicenseResult = false;
                }

                if (result.Error != IdentityValidationError::None)
                {
                    LicenseResult = false;
                }

                char *serialNumber = result.SubjectSerialNumber.CStr();
                CheckLicense handle(pub_key_path, token_path);

                try
                {
                    handle.Init();
                    handle.ValidateHostId(serialNumber);
                }
                catch (std::runtime_error &e)
                {
                    // log.Debug("OTACLicenseCheck: std::runtime_error=[ {0} ]" , e.what());
                    error_string_std = e.what();
                    LicenseResult = false;
                }

                if (LicenseResult == false)
                {
                    mod.licenseCheckFail();
                }
            }

            UmAuthenticationResult ExampleAuthenticationProvider::AuthenticateUser(const String &username,
                                                                                   const String &password, SessionInfo &sessionInfo)
            {
                if (!mod.Started())
                {
                    return UmAuthenticationResult::Failed;
                }
                if (!mod.UserAuthStarted())
                {

                    if (!error_string_std.empty())
                    {
                        log.Debug("OTACAuthenticationProvider: License check failed - {0}", error_string_std);
                    }
                    if (!error_string_arp.empty())
                    {
                        log.Debug("OTACAuthenticationProvider: License check failed - {0}", error_string_arp);
                    }
                    if (result.Error != IdentityValidationError::None)
                    {
                        log.Debug("OTACAuthenticationProvider: License check failed - {0}", result.Error);
                    }

                    return UmAuthenticationResult::Failed;
                }

                log.Debug("OTACAuthenticationProvider: License check success.");
                const UserConfTag &userconf = mod.GetConfig()->userConf;
                Verify handler(password.CStr());
                if (!handler.SetHostIp())
                {
                    log.Debug("OTACAuthenticationProvider: SetHostIp failed.");
                    return UmAuthenticationResult::Failed;
                }
                handler.SetPost(userconf.url.CStr());
                handler.Request();
                Json::Value root = handler.GetRoot();

                log.Debug("OTACAuthenticationProvider: Host Address : {0}", handler.GetIp());
                log.Debug("OTACAuthenticationProvider: Server Address : {0}", userconf.url.CStr());
                log.Debug("OTACAuthenticationProvider: {0}", handler.GetResponse());

                return ResultCheck(root, username, sessionInfo);
            }

            UmAuthenticationResult ExampleAuthenticationProvider::ResultCheck(Json::Value Root, const String &inputUser, SessionInfo &sessionInfo)
            {
                const char *username = inputUser.CStr();
                if (Root["userId"] == username)
                {
                    if (Root["result"] == "SUCCESS")
                    {
                        list<String> roles;
                        String Roles(Root["userRoles"].asCString());
                        if (Roles.Find('|') != -1)
                        {
                            vector<string> result = Split(Roles, '|');

                            for (int i = 0; i < result.size(); i++)
                            {
                                roles.push_back(result[i]);
                            }
                            sessionInfo.SetRoles(roles);

                            return UmAuthenticationResult::Success;
                        }
                        roles = {Roles};
                        sessionInfo.SetRoles(roles);

                        return UmAuthenticationResult::Success;
                    }
                    else
                    {
                        return UmAuthenticationResult::WrongPassword;
                    }
                }
                return UmAuthenticationResult::Failed;
            }

            void ExampleAuthenticationProvider::OnSessionClose(SessionInfo &session)
            {
                String clientIpAdress;
                String accessToken;
                log.Debug("ExampleAuthenticationProvider: session closed, id={0}, session holding lock={1}, clientIp={2}, accessToken={3}, protocolObjName={4}, user={5}",
                          session.GetSecurityToken(), mod.GetLockedSession(), clientIpAdress, accessToken, session.GetProtocolObjName(), session.GetUserName());

                mod.UnlockSession(session);
            }

        }
    }
} // end of namespace Arp::System::UmModuleEx
