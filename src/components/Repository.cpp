//
// Created by Ahmed Mustafa on 8/13/2025.
//

#include "Repository.h"

#include <filesystem>
#include <utility>

namespace Split {

    Repository::Repository(std::string name, const std::string &rootPath)
    : name(std::move(name)), rootPath(rootPath), index(rootPath) {
        history = CommitHistory();
    }

    void Repository::init() const {

        // Initialize the repository by creating necessary directories and files
        const std::string repoPath = rootPath + "/.split";
        std::filesystem::create_directories(repoPath);
    }

    void Repository::add(const std::string &filepath) {
        index.stageFile(filepath);
    }

    void Repository::commit(const std::string &message, const std::string &author) {
    }



}