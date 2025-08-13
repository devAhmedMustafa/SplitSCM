//
// Created by Ahmed Mustafa on 8/13/2025.
//

#ifndef COMMITHISTORY_H
#define COMMITHISTORY_H

#include <stack>
#include <stdexcept>

#include "../components/Commit.h"

namespace Split {

    class CommitHistory {

        std::stack<Commit> commits;

    public:

        void addCommit(Commit& commit) {
            throw std::logic_error("Not implemented");
        }

        Commit& getCommit(const std::string& hash) {
            throw std::logic_error("Not implemented");
        }

        Commit& getLatest() {
            throw std::logic_error("Not implemented");
        }

    };

}

#endif //COMMITHISTORY_H
