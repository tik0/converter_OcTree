#pragma once

#include <rsb/converter/Converter.h>

namespace converter_OcTree {

/**
 * A simple converter for the OcTree object.
 */
class OcTreeConverter: public rsb::converter::Converter<std::string> {
public:
    OcTreeConverter();

    std::string serialize(const rsb::AnnotatedData& data,
            std::string& wire);

    rsb::AnnotatedData deserialize(const std::string& wireSchema,
            const std::string& wire);
};

}
