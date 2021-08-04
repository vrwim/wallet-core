// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include <TrustWalletCore/TWBitcoinSigHashType.h>
#include "TransactionInput.h"
#include "TransactionOutput.h"
#include "Bitcoin/Transaction.h"
#include "Bitcoin/Script.h"
#include "../Data.h"
#include "../proto/Decred.pb.h"

#include "Bitcoin/SignatureVersion.h"
#include <vector>

namespace TW::Decred {

enum class SerializeType : uint16_t { full, noWitness, onlyWitness };

class Transaction: public Bitcoin::TransactionBase {
public:
    /// Serialization format
    SerializeType serializeType = SerializeType::full;

    /// Transaction data format version
    // TODO remove uint16_t version = 1;

    /// A list of 1 or more transaction inputs or sources for coins
    std::vector<TransactionInput> inputs;

    /// A list of 1 or more transaction outputs or destinations for coins
    std::vector<TransactionOutput> outputs;

    /// The time when a transaction can be spent (usually zero, in which case it
    /// has no effect).
    // TODO remove uint32_t lockTime = 0;

    /// The block height at which the transaction expires and is no longer
    /// valid.
    uint32_t expiry = 0;

    Transaction()
        : TransactionBase()
        , inputs()
        , outputs() {}

    virtual void addInput(const Bitcoin::OutPoint& outPoint, const Bitcoin::Script& script, uint32_t sequence) {
        // Note: up-cast is used here
        if (dynamic_cast<const OutPoint*>(&outPoint) != nullptr) {
            TransactionInput input;
            input.previousOutput = dynamic_cast<const OutPoint&>(outPoint);
            input.sequence = sequence;
            input.script = script;
            inputs.emplace_back(input);
        }
    }

    virtual void addOutput(Bitcoin::Amount value, const Bitcoin::Script& lockingScript) {
        outputs.emplace_back(TransactionOutput(value, /* version: */ 0, lockingScript));
    }

    /// Whether the transaction is empty.
    virtual bool empty() const { return inputs.empty() && outputs.empty(); }

    /// Generates the signature pre-image.
    Data computeSignatureHash(const Bitcoin::Script& scriptCode, size_t index,
                              enum TWBitcoinSigHashType hashType) const;

    /// Generates the transaction hash.
    Data hash() const;

    /// Encodes the transaction into the provided buffer.
    void encode(Data& data) const;

    /// Converts to Protobuf model
    Proto::Transaction proto() const;

  private:
    Data computePrefixHash(const std::vector<TransactionInput>& inputsToSign,
                           const std::vector<TransactionOutput>& outputsToSign,
                           std::size_t signIndex, std::size_t index, enum TWBitcoinSigHashType hashType) const;
    Data computeWitnessHash(const std::vector<TransactionInput>& inputsToSign,
                            const Bitcoin::Script& signScript, std::size_t signIndex) const;

    void encodePrefix(Data& data) const;
    void encodeWitness(Data& data) const;
};

} // namespace TW::Decred
