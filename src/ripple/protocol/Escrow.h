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

#ifndef RIPPLE_PROTOCOL_ESCROW_H_INCLUDED
#define RIPPLE_PROTOCOL_ESCROW_H_INCLUDED

#include <ripple/protocol/LedgerEntryWrapper.h>

namespace ripple {

template <bool Writable>
class EscrowImpl final : public LedgerEntryWrapper<Writable>
{
private:
    using Base = LedgerEntryWrapper<Writable>;
    using SleT = typename Base::SleT;
    using Base::wrapped_;

    // This constructor is private so only the factory functions can
    // construct an EscrowImpl.
    EscrowImpl(std::shared_ptr<SleT>&& w) : Base(std::move(w))
    {
    }

    // Friend declarations of factory functions.
    //
    // For classes that contain factories we must declare the entire class
    // as a friend unless the class declaration is visible at this point.
    friend class ReadView;
    friend class ApplyView;

public:
    // Conversion operator from EscrowImpl<true> to EscrowImpl<false>.
    operator EscrowImpl<true>() const
    {
        return EscrowImpl<false>(
            std::const_pointer_cast<std::shared_ptr<STLedgerEntry const>>(
                wrapped_));
    }

    [[nodiscard]] std::optional<uint32_t>
    finishTime() const
    {
        return wrapped_->at(~sfFinishAfter);
    }

    [[nodiscard]] std::optional<uint32_t>
    cancelTime() const
    {
        return wrapped_->at(~sfCancelAfter);
    }

    [[nodiscard]] const std::optional<ripple::Slice>
    checkCondition() const
    {
        return wrapped_->at(~sfCondition);
    }

    [[nodiscard]] AccountID
    getEscrowRecipient() const
    {
        return wrapped_->at(sfDestination);
    }

    [[nodiscard]] AccountID
    accountID() const
    {
        return wrapped_->at(sfAccount);
    }

    // This function returns the appropriate page from inside a ledger object.
    [[nodiscard]] std::uint64_t
    getOwnerNode() const
    {
        return wrapped_->at(sfOwnerNode);
    }

    // Keshava: Should I explicitly specify the return type or use auto keyword?
    // returns ripple::OptionalProxy<ripple::STInteger<unsigned long long>>
    // but OptionalProxy is not accesible from this file
    [[nodiscard]] auto
    getRecipientNode() const
    {
        return wrapped_->at(~sfDestinationNode);
    }

    [[nodiscard]] STAmount
    amount() const
    {
        return wrapped_->at(sfAmount);
    }
};

using Escrow = EscrowImpl<true>;
using EscrowRd = EscrowImpl<false>;

}  // namespace ripple

#endif  // RIPPLE_PROTOCOL_ESCROW_H_INCLUDED
