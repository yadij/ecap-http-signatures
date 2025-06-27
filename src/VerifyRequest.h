
#ifndef _SRC_VerifyRequest_H_
#define _SRC_VerifyRequest_H_

#include <libecap/adapter/xaction.h>
#include <libecap/host/xaction.h>

namespace libhttpsignatures
{

// Verify a Signature header in HTTP Request.
class VerifyRequest: public libecap::adapter::Xaction
{
public:
    VerifyRequest(libecap::host::Xaction *h) : hostx(h) {}
    virtual ~VerifyRequest();

    /* libecap::adapter::Xaction API */
    virtual void start() override;
    virtual void stop() override { (void)hostx.release(); }
    virtual const libecap::Area option(const libecap::Name &) const override { return libecap::Area(); }
    virtual void visitEachOption(libecap::NamedValueVisitor &) const override {}
    virtual void abDiscard() override { noBodySupport(); }
    virtual void abMake() override { noBodySupport(); }
    virtual void abMakeMore() override { noBodySupport(); }
    virtual void abStopMaking() override { noBodySupport(); }
    virtual libecap::Area abContent(libecap::size_type, libecap::size_type) override { noBodySupport(); return libecap::Area(); }
    virtual void abContentShift(libecap::size_type)  override { noBodySupport(); }
    virtual void noteVbContentDone(bool) override { noBodySupport(); }
    virtual void noteVbContentAvailable() override { noBodySupport(); }

private:
    void noBodySupport() const;

    std::unique_ptr<libecap::host::Xaction> hostx;
};

} // namespace libhttpsignatures

#endif // _SRC_VerifyRequest_H_
