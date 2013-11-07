#pragma once

#include <rsb/converter/Converter.h>

namespace converter_tutorial {

/**
 * A simple converter for the SimpleImage struct. For educational use only.
 */
class SimpleImageConverter: public rsb::converter::Converter<std::string> {
public:
    SimpleImageConverter();

    std::string serialize(const rsb::AnnotatedData& data,
            std::string& wire);

    rsb::AnnotatedData deserialize(const std::string& wireSchema,
            const std::string& wire);
};

}