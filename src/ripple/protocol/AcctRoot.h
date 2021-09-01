//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2021 Ripple Labs Inc.

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

#ifndef RIPPLE_PROTOCOL_ACCT_ROOT_H_INCLUDED
#define RIPPLE_PROTOCOL_ACCT_ROOT_H_INCLUDED

#include <ripple/protocol/LedgerEntryWrapper.h>
#include <ripple/protocol/STAccount.h>
#include <ripple/protocol/STAmount.h>

namespace ripple {

template <bool Writable>
class AcctRootImpl final : public LedgerEntryWrapper<Writable>
{
private:
    using Base = LedgerEntryWrapper<Writable>;
    using SleT = typename Base::SleT;
    using Base::wrapped_;

    // This constructor is private so only the factory functions can
    // construct an AcctRootImpl.
    AcctRootImpl(std::shared_ptr<SleT>&& w) : Base(std::move(w))
    {
    }

    // Friend declarations of factory functions.
    //
    // For classes that contain factories we must declare the entire class
    // as a friend unless the class declaration is visible at this point.
    friend class ReadView;
    friend class ApplyView;

public:
    AcctRootImpl(AcctRootImpl const&) = default;
    AcctRootImpl(AcctRootImpl&&) = default;

    AcctRootImpl&
    operator=(AcctRootImpl const& rhs)
    {
        Base::operator=(rhs);
        return *this;
    }

    AcctRootImpl&
    operator=(AcctRootImpl&& rhs)
    {
        Base::operator=(std::move(rhs));
        return *this;
    }

    ~AcctRootImpl() = default;

    // Conversion operator from AcctRootImpl<true> to AcctRootImpl<false>.
    operator AcctRootImpl<true>() const
    {
        return AcctRootImpl<false>(
            std::const_pointer_cast<std::shared_ptr<STLedgerEntry const>>(
                wrapped_));
    }

    [[nodiscard]] AccountID
    accountID() const
    {
        return wrapped_->at(sfAccount);
    }

    [[nodiscard]] std::uint32_t
    sequence() const
    {
        return wrapped_->at(sfSequence);
    }

    void
    setSequence(std::uint32_t seq)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        wrapped_->at(sfSequence) = seq;
    }

    [[nodiscard]] STAmount
    balance() const
    {
        return wrapped_->at(sfBalance);
    }

    void
    setBalance(STAmount const& amount)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        wrapped_->at(sfBalance) = amount;
    }

    [[nodiscard]] std::uint32_t
    ownerCount() const
    {
        return wrapped_->at(sfOwnerCount);
    }

    void
    setOwnerCount(std::uint32_t newCount)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        wrapped_->at(sfOwnerCount) = newCount;
    }

    [[nodiscard]] std::uint32_t
    previousTxnID() const
    {
        return wrapped_->at(sfOwnerCount);
    }

    void
    setPreviousTxnID(uint256 prevTxID)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        wrapped_->at(sfPreviousTxnID) = prevTxID;
    }

    [[nodiscard]] std::uint32_t
    previousTxnLgrSeq() const
    {
        return wrapped_->at(sfPreviousTxnLgrSeq);
    }

    void
    setPreviousTxnLgrSeq(std::uint32_t prevTxLgrSeq)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        wrapped_->at(sfPreviousTxnLgrSeq) = prevTxLgrSeq;
    }

    [[nodiscard]] std::optional<uint256>
    accountTxnID() const
    {
        return wrapped_->at(~sfAccountTxnID);
    }

    void
    setAccountTxnID(uint256 const& newAcctTxnID)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->setOptional(sfAccountTxnID, newAcctTxnID);
    }

    void
    clearAccountTxnID()
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->clearOptional(sfAccountTxnID);
    }

    [[nodiscard]] std::optional<AccountID>
    regularKey() const
    {
        return wrapped_->at(~sfRegularKey);
    }

    void
    setRegularKey(AccountID const& newRegKey)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->setOptional(sfRegularKey, newRegKey);
    }

    void
    clearRegularKey()
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->clearOptional(sfRegularKey);
    }

    [[nodiscard]] std::optional<uint128>
    emailHash() const
    {
        return wrapped_->at(~sfEmailHash);
    }

    void
    setEmailHash(uint128 const& newEmailHash)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->setOrClearBaseUintIfZero(sfEmailHash, newEmailHash);
    }

    [[nodiscard]] std::optional<uint256>
    walletLocator() const
    {
        return wrapped_->at(~sfWalletLocator);
    }

    void
    setWalletLocator(uint256 const& newWalletLocator)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->setOrClearBaseUintIfZero(sfWalletLocator, newWalletLocator);
    }

    [[nodiscard]] std::optional<std::uint32_t>
    walletSize() const
    {
        return wrapped_->at(~sfWalletSize);
    }

    [[nodiscard]] Blob
    messageKey() const
    {
        return this->getOptionalVL(sfMessageKey);
    }

    void
    setMessageKey(Blob const& newMessageKey)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->setOrClearVLIfEmpty(sfMessageKey, newMessageKey);
    }

    [[nodiscard]] std::optional<std::uint32_t>
    transferRate() const
    {
        return wrapped_->at(~sfTransferRate);
    }

    void
    setTransferRate(std::uint32_t newTransferRate)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->setOptional(sfTransferRate, newTransferRate);
    }

    void
    clearTransferRate()
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->clearOptional(sfTransferRate);
    }

    [[nodiscard]] Blob
    domain() const
    {
        return this->getOptionalVL(sfDomain);
    }

    void
    setDomain(Blob const& newDomain)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->setOrClearVLIfEmpty(sfDomain, newDomain);
    }

    [[nodiscard]] std::optional<std::uint8_t>
    tickSize() const
    {
        return wrapped_->at(~sfTickSize);
    }

    void
    setTickSize(std::uint8_t newTickSize)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->setOptional(sfTickSize, newTickSize);
    }

    void
    clearTickSize()
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->clearOptional(sfTickSize);
    }

    [[nodiscard]] std::optional<std::uint32_t>
    ticketCount() const
    {
        return wrapped_->at(~sfTicketCount);
    }

    void
    setTicketCount(std::uint32_t newTicketCount)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->setOptional(sfTicketCount, newTicketCount);
    }

    void
    clearTicketCount()
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->clearOptional(sfTicketCount);
    }

    [[nodiscard]] std::optional<AccountID>
    NFTokenMinter() const
    {
        return wrapped_->at(~sfNFTokenMinter);
    }

    void
    setNFTokenMinter(AccountID const& newMinter)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->setOptional(sfNFTokenMinter, newMinter);
    }

    void
    clearNFTokenMinter()
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->clearOptional(sfNFTokenMinter);
    }

    [[nodiscard]] std::optional<std::uint32_t>
    mintedNFTokens() const
    {
        return wrapped_->at(~sfMintedNFTokens);
    }

    void
    setMintedNFTokens(std::uint32_t newMintedCount)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->setOptional(sfMintedNFTokens, newMintedCount);
    }

    [[nodiscard]] std::optional<std::uint32_t>
    burnedNFTokens() const
    {
        return wrapped_->at(~sfBurnedNFTokens);
    }

    void
    setBurnedNFTokens(std::uint32_t newBurnedCount)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->setOptional(sfBurnedNFTokens, newBurnedCount);
    }

    [[nodiscard]] std::optional<std::uint32_t>
    firstNFTokenSequence() const
    {
        return wrapped_->at(~sfFirstNFTokenSequence);
    }

    void
    setFirstNFTokenSequence(std::uint32_t newFirstNFTokenSeq)
    {
        static_assert(Writable, "Cannot set member of const ledger entry.");
        this->setOptional(sfFirstNFTokenSequence, newFirstNFTokenSeq);
    }
};

using AcctRootRd = AcctRootImpl<false>;
using AcctRoot = AcctRootImpl<true>;

// clang-format off
#ifndef __INTELLISENSE__
static_assert(not std::is_default_constructible_v<AcctRootRd>);
static_assert(    std::is_copy_constructible_v<AcctRootRd>);
static_assert(    std::is_move_constructible_v<AcctRootRd>);
static_assert(    std::is_copy_assignable_v<AcctRootRd>);
static_assert(    std::is_move_assignable_v<AcctRootRd>);
static_assert(    std::is_nothrow_destructible_v<AcctRootRd>);

static_assert(not std::is_default_constructible_v<AcctRoot>);
static_assert(    std::is_copy_constructible_v<AcctRoot>);
static_assert(    std::is_move_constructible_v<AcctRoot>);
static_assert(    std::is_copy_assignable_v<AcctRoot>);
static_assert(    std::is_move_assignable_v<AcctRoot>);
static_assert(    std::is_nothrow_destructible_v<AcctRoot>);
#endif  // __INTELLISENSE__
// clang-format on

}  // namespace ripple

#endif  // RIPPLE_PROTOCOL_ACCT_ROOT_H_INCLUDED
