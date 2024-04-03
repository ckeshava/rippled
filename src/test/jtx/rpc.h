//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2012, 2013 Ripple Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef RIPPLE_TEST_JTX_RPC_H_INCLUDED
#define RIPPLE_TEST_JTX_RPC_H_INCLUDED

#include <test/jtx/Env.h>
#include <tuple>

namespace ripple {
namespace test {
namespace jtx {

/** Set the expected result code for a JTx
    The test will fail if the code doesn't match.
*/
class rpc
{
private:
    std::optional<error_code_i> code_;
    std::optional<std::string> errorMessage_;
    std::optional<std::string> error_;
    std::optional<std::string> errorException_;

public:
    /// If there's an error code, we expect an error message
    explicit rpc(error_code_i code, std::optional<std::string> m = {})
        : code_(code), errorMessage_(m)
    {
    }

    ///  If there is not a code, we expect an exception message
    explicit rpc(std::string error, std::optional<std::string> exception = {})
        : error_(error), errorException_(exception)
    {
    }

    void
    operator()(Env&, JTx& jt) const
    {
        jt.ter = telENV_RPC_FAILED;
        if (code_)
            jt.rpcCode = {
                *code_,
                errorMessage_ ? *errorMessage_
                              : RPC::get_error_info(*code_).message.c_str()};
        if (error_)
            jt.rpcException = {*error_, errorException_};
    }
};

}  // namespace jtx
}  // namespace test
}  // namespace ripple

#endif
