// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.
//

#include "../interface/TWTestUtilities.h"
#include <TrustWalletCore/TWCoinTypeConfiguration.h>
#include <gtest/gtest.h>


TEST(TWEnergyWebChainCoinType, TWCoinType) {
    auto symbol = WRAPS(TWCoinTypeConfigurationGetSymbol(TWCoinTypeEnergyWebChain));
    auto txId = WRAPS(TWStringCreateWithUTF8Bytes("0xc8e02581ef846ce6b0ab3344b0036ec395348775fac66e42fc8d1f172d512111"));
    auto txUrl = WRAPS(TWCoinTypeConfigurationGetTransactionURL(TWCoinTypeEnergyWebChain, txId.get()));
    auto accId = WRAPS(TWStringCreateWithUTF8Bytes("0xc0eE5F176eC4FbFD13cDD746fC62aA91e62F13e1"));
    auto accUrl = WRAPS(TWCoinTypeConfigurationGetAccountURL(TWCoinTypeEnergyWebChain, accId.get()));
    auto id = WRAPS(TWCoinTypeConfigurationGetID(TWCoinTypeEnergyWebChain));
    auto name = WRAPS(TWCoinTypeConfigurationGetName(TWCoinTypeEnergyWebChain));

    ASSERT_EQ(TWCoinTypeConfigurationGetDecimals(TWCoinTypeEnergyWebChain), 18);
    ASSERT_EQ(TWBlockchainEthereum, TWCoinTypeBlockchain(TWCoinTypeEnergyWebChain));

    assertStringsEqual(symbol, "EWT");
    assertStringsEqual(txUrl, "https://explorer.energyweb.org/tx/0xc8e02581ef846ce6b0ab3344b0036ec395348775fac66e42fc8d1f172d512111");
    assertStringsEqual(accUrl, "https://explorer.energyweb.org/address/0xc0eE5F176eC4FbFD13cDD746fC62aA91e62F13e1");
    assertStringsEqual(id, "energy-web-chain");
    assertStringsEqual(name, "Energy Web Chain");
}
