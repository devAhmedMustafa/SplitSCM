#include "DeltaCompressor.h"

#include <stdexcept>

#include "../../lib/xdelta/xdelta3/xdelta3.h"

namespace Split {

    std::string DeltaCompressor::encode(const std::string& baseBytes, const std::string& targetBytes) {
        std::string deltaOut;

        unsigned char *input = nullptr, *output = nullptr;
        size_t outputSize = 0;

        int ret = xd3_encode_memory(
            (const unsigned char*)baseBytes.data(), baseBytes.size(),
            (const unsigned char*)targetBytes.data(), targetBytes.size(),
            output, &outputSize,
            XD3_DEFAULT_WINSIZE, 0
        );

        if (ret != 0) {
            if (output) free(output);
            throw std::runtime_error("Failed to encode delta: " + std::string(xd3_strerror(ret)));
        }

        deltaOut.assign(reinterpret_cast<char*>(output), outputSize);
        free(output);
        return deltaOut;
    }

    std::string DeltaCompressor::decode(const std::string& baseFile, std::string& outputFile) {

        std::string targetOut;

        unsigned char* output = nullptr;
        usize_t outputSize = 0;

        int red = xd3_decode_memory(
            (const unsigned char*)baseFile.data(), baseFile.size(),
            (const unsigned char*)targetOut.data(), targetOut.size(),
            output, &outputSize,
            XD3_DEFAULT_WINSIZE, 0
        );

        if (red != 0) {
            if (output) free(output);
            throw std::runtime_error("Failed to decode delta: " + std::string(xd3_strerror(red)));
        }

        targetOut.assign((char*)output, outputSize);
        free(output);
        return targetOut;
    }

}