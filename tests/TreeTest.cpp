//
// Created by Ahmed Mustafa on 8/16/2025.
//

#include <gtest/gtest.h>

#include <components/Tree.h>

using namespace Split;

TEST(TreeTest, SerializeDeserialize) {
    std::map<std::string, std::string> entries = {
        {"file1.txt", "hash1"},
        {"file2.txt", "hash2"},
        {"file3.txt", "hash3"}
    };

    const Tree originalTree(entries);
    const str serialized = originalTree.serialize();

    str expectedSerialized = "file1.txt:hash1\nfile2.txt:hash2\nfile3.txt:hash3\n";
    EXPECT_EQ(serialized, expectedSerialized);
}

TEST(TreeTest, DeserializeEmpty) {
    std::istringstream inputStream("");
    const Tree deserializedTree = Tree::deserialize(inputStream);
    EXPECT_EQ(deserializedTree.serialize(), "");
}

TEST(TreeTest, DeserializeWithEntries) {
    std::istringstream inputStream("file1.txt:hash1\nfile2.txt:hash2\nfile3.txt:hash3\n");
    Tree deserializedTree = Tree::deserialize(inputStream);

    std::map<std::string, std::string> expectedEntries = {
        {"file1.txt", "hash1"},
        {"file2.txt", "hash2"},
        {"file3.txt", "hash3"}
    };

    EXPECT_EQ(deserializedTree.serialize(), "file1.txt:hash1\nfile2.txt:hash2\nfile3.txt:hash3\n");
    for (const auto& entry : expectedEntries) {
        EXPECT_EQ(deserializedTree.getEntry(entry.first), entry.second);
    }
}