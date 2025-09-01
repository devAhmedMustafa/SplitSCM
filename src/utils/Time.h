//
// Created by Ahmed Mustafa on 8/13/2025.
//

#ifndef TIME_H
#define TIME_H

#include <string>
#include <ctime>

namespace Split::Time {

    inline std::string getCurrentTime() {
        time_t now = time(nullptr);
        char buf[64];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
        return std::string(buf);
    }

}

#endif //TIME_H
