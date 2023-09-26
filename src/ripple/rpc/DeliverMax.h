//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2023 Ripple Labs Inc.

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

#ifndef RIPPLE_RPC_DELIVERMAX_H_INCLUDED
#define RIPPLE_RPC_DELIVERMAX_H_INCLUDED

#include <ripple/protocol/Protocol.h>
#include <ripple/protocol/STAmount.h>
#include <ripple/protocol/TxFormats.h>

#include <functional>
#include <memory>

namespace Json {
class Value;
}

namespace ripple {

class ReadView;
class Transaction;
class TxMeta;
class STTx;

namespace RPC {

struct JsonContext;

struct Context;

/**
   Copy `Amount` field to `DeliverMax` field in transaction output JSON.
   This only applies to Payment transaction type, all others are ignored.

   When context.apiVersion > 1 will also remove `Amount` field, forcing users
   to access this value using new `DeliverMax` field only.
   @{
 */

void
insertDeliverMax(
    Json::Value& tx_json,
    RPC::Context const& context,
    TxType txnType);

/** @} */

}  // namespace RPC
}  // namespace ripple

#endif
