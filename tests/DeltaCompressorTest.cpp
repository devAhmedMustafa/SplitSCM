#include <gtest/gtest.h>
#include "utils/DeltaCompressor.h"

TEST(DeltaCompressorTest, CompressAndDecompress) {
    Split::DeltaCompressor compressor;

    const std::string original = "This is original test string for compression.";
    const std::string target = "This is target test string for compression.";

    const auto encoded = compressor.encode(original, target);
    ASSERT_FALSE(encoded.empty()) << "Encoded data should not be empty";
    ASSERT_NE(encoded, original) << "Encoded data should differ from original";
    ASSERT_NE(encoded, target) << "Encoded data should differ from target";

    auto decoded = compressor.decode(original, encoded);
    ASSERT_EQ(decoded, target) << "Decoded data should match target string";
    ASSERT_EQ(decoded.size(), target.size()) << "Decoded data size should match target size";
}