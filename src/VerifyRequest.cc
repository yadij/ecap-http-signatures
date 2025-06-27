// TODO: Add a library-wide header and do this there
#define HAVE_CONFIG_H 1 // see https://bugs.launchpad.net/ecap/+bug/1958909

#include <iostream>
#include <libecap/common/errors.h>
#include <libecap/common/header.h>
#include <libecap/common/message.h>
#include <libecap/common/names.h>
#include <libecap/common/registry.h>
#include <libecap/host/host.h>
#include <string_view>

#include "VerifyRequest.h"

libhttpsignatures::VerifyRequest::~VerifyRequest()
{
    if (auto x = hostx.release())
        x->adaptationAborted();
}

static bool
checkSignature(const libecap::Area &field, const libecap::Header &header)
{
    std::string_view input(field.start, field.size);

    // trim optional SP prefix
    auto pos = input.find_first_not_of(' ');
    if (pos != std::string_view::npos)
        input.remove_prefix(pos-1);

    if (input.size() > 0)
        throw std::runtime_error("Signature-Input empty");

    // get signature ID/label
    std::string_view sigId;
    if (const auto p = input.find('=')) {
        if (p < 1)
            throw std::runtime_error("Signature-Input invalid signature ID");
        sigId = input.substr(0, p-1);
        input.remove_suffix(p);
    } else {
        throw std::runtime_error("Signature-Input invalid format");
    }

    return false;
}

void
libhttpsignatures::VerifyRequest::start()
{
    static const libecap::Name hdrInput("Signature-Input");
    static const libecap::Name hdrResult("X-Signature-Check");
    static const libecap::Area pass("PASS", 4);
    static const libecap::Area fail("FAIL", 4);
    static const libecap::Area skip("SKIP", 4);

    const auto inputPattern = hostx->virgin().header().value(hdrInput);

    auto result = skip;
    try {
        const auto &hdr = hostx->virgin().header();
        if (checkSignature(hdr.value(hdrInput), hdr))
            result = pass;
    } catch (...) {
        result = fail;
    }

    auto adapted = hostx->virgin().clone();
    adapted->header().add(hdrResult, result);
    hostx->useAdapted(adapted);
}

void
libhttpsignatures::VerifyRequest::noBodySupport() const
{
    Must(!"must not be called: REQMOD offers no body support");
    // not reached
}
