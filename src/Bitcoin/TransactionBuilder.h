// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Transaction.h"
#include "TransactionPlan.h"
#include "UnspentSelector.h"
#include "../proto/Bitcoin.pb.h"
#include <TrustWalletCore/TWCoinType.h>

#include <algorithm>

namespace TW::Bitcoin {

class TransactionBuilderBase {
public:
    /// Plans a transaction by selecting UTXOs and calculating fees.
    TransactionPlan plan(const Bitcoin::Proto::SigningInput& input) const;

    /// Builds a transaction by selecting UTXOs and calculating fees.
    virtual void build(const TransactionPlan& plan, const std::string& toAddress,
                       const std::string& changeAddress, enum TWCoinType coin, TransactionBase& transaction) const = 0;
};

class TransactionBuilder: public TransactionBuilderBase {
public:
    TransactionBuilder() = default;

    /// Builds a transaction by selecting UTXOs and calculating fees.
    virtual void build(const TransactionPlan& plan, const std::string& toAddress,
                       const std::string& changeAddress, enum TWCoinType coin, TransactionBase& transaction) const;
};

} // namespace TW::Bitcoin
