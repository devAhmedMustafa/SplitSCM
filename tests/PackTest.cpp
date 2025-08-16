//
// Created by Ahmed Mustafa on 8/15/2025.
//

#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include <stores/ObjectStore.h>

#include <stores/Pack.h>

TEST(PackTest, EncodeDecode) {
    std::string rootPath = "test_root";
    std::filesystem::create_directories(rootPath + "/.split");

    Split::Pack pack(rootPath);

    std::string originalContent = "This is a test content for encoding and decoding.";
    std::string baseContent = "This is the base content.";

    Split::ObjectStore blobsObjectStore(rootPath, "/blobs");

    auto baseHash = blobsObjectStore.storeBytesObject(baseContent);
    auto originalHash = blobsObjectStore.storeBytesObject(originalContent);

    // Encode the delta
    std::string encodedDelta = pack.encodeDelta(baseContent, originalContent, baseHash, originalHash);

    // Decode the content
    std::string decodedContent = pack.getDecodedContent(originalHash);

    // Check if the decoded content matches the original content
    EXPECT_EQ(decodedContent, originalContent);

    // Clean up files
    std::filesystem::remove_all(rootPath);
}