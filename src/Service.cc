
#define HAVE_CONFIG_H 1 // see https://bugs.launchpad.net/ecap/+bug/1958909

#include <iostream>
#include <libecap/adapter/service.h>
#include <libecap/common/registry.h>
#include <libecap/host/xaction.h>

#include "config.h"
#include "VerifyRequest.h"

namespace libhttpsignatures
{

// Verify HTTP Request Signature
class ReqmodVerify : public libecap::adapter::Service
{
public:
    virtual ~ReqmodVerify() {}

    /* libecap::adaptor::Service API */
    std::string uri() const override { return "ecap://" PROJECT_NAME "/" PROJECT_VER "/verify/request"; }
    std::string tag() const override { return PROJECT_NAME "/" PROJECT_VER "/verify/request"; }
    void describe(std::ostream &os) const override {
        os << "Verify HTTP Request Signature " << PROJECT_NAME << " v" << PROJECT_VER;
    }
    void configure(const libecap::Options &) override {}
    void reconfigure(const libecap::Options &) override {}
    bool wantsUrl(const char *) const override { return true; }
    libecap::adapter::Service::MadeXactionPointer makeXaction(libecap::host::Xaction *hostx) override {
        return libecap::adapter::Service::MadeXactionPointer(new libhttpsignatures::VerifyRequest(hostx));
    }
};

} // namespace libhttpsignatures

static bool
RegisterServices()
{
    return libecap::RegisterVersionedService(new libhttpsignatures::ReqmodVerify);
}

// create the adapter and register with libecap to reach the host application
static const auto Registered = RegisterServices();
