#include "DeltaCompressor.h"

#include <stdexcept>
#include "google/vcdecoder.h"
#include "google/vcencoder.h"


namespace Split {

    std::string DeltaCompressor::encode(const std::string& baseBytes, const std::string& targetBytes) {
        std::string deltaOut;

        open_vcdiff::VCDiffEncoder encoder(
            baseBytes.data(), baseBytes.size()
        );
        encoder.SetFormatFlags(open_vcdiff::VCD_FORMAT_INTERLEAVED);

        if (!encoder.Encode(targetBytes.data(), targetBytes.size(), &deltaOut)) {
            throw std::runtime_error("Failed to encode delta: ");
        }

        return deltaOut;
    }

    std::string DeltaCompressor::decode(const std::string& baseFile, std::string& outputFile) {

        std::string targetOut;

//        uint8_t output = 0;
//        usize_t outputSize = 0;
//
//        int red = xd3_decode_memory(
//            (const unsigned char*)baseFile.data(), baseFile.size(),
//            (const unsigned char*)targetOut.data(), targetOut.size(),
//            &output, &outputSize,
//            XD3_DEFAULT_WINSIZE, 0
//        );
//
//        if (red != 0) {
//            if (output) free(&output);
//            throw std::runtime_error("Failed to decode delta: " + std::string(xd3_strerror(red)));
//        }
//
//        targetOut.assign((char*)output, outputSize);
//        free(&output);
        return targetOut;
    }

}