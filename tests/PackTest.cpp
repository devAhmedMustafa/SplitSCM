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
    Split::Pack pack(rootPath);

    std::string originalContent = "This is a test content for encoding and decoding.";
    std::string baseContent = "This is the base content.";

    // Create files
    std::fstream baseFile("base.txt", std::ios::out);
    baseFile << baseContent;
    baseFile.close();

    Split::ObjectStore blobsObjectStore(rootPath, "/blobs");

    auto baseHash = blobsObjectStore.storeFileObject("base.txt");

    // Encode the delta
    std::string encodedDelta = pack.encodeDelta(baseContent, originalContent, baseHash);

    // Decode the content
    std::string decodedContent = pack.getDecodedContent(baseHash);

    // Check if the decoded content matches the original content
    EXPECT_EQ(decodedContent, originalContent);

    // Clean up files
    std::remove("base.txt");
    std::filesystem::remove_all(rootPath);
}