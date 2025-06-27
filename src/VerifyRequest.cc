// TODO: Add a library-wide header and do this there
#define HAVE_CONFIG_H 1 // see https://bugs.launchpad.net/ecap/+bug/1958909

#include <iostream>
#include <libecap/common/errors.h>
#include <libecap/common/header.h>
#include <libecap/common/message.h>
#include <libecap/common/names.h>
#include <libecap/common/registry.h>
#include <libecap/host/host.h>

#include "VerifyRequest.h"

libhttpsignatures::VerifyRequest::~VerifyRequest()
{
    if (auto x = hostx.release())
        x->adaptationAborted();
}

void
libhttpsignatures::VerifyRequest::start()
{
    static const libecap::Name name("X-Signature-Verify");
    static const libecap::Area result("SKIP", 4);

    auto adapted = hostx->virgin().clone();
    adapted->header().add(name, result);
    hostx->useAdapted(adapted);
}

void
libhttpsignatures::VerifyRequest::noBodySupport() const
{
    Must(!"must not be called: REQMOD offers no body support");
    // not reached
}
