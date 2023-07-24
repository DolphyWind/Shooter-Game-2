#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <iostream>

namespace sg 
{

/// @brief A class for holding version information such as v1.0.0
class Version
{
public:
    Version() = default;
    // Parses version from string
    Version(std::uint8_t major, std::uint8_t minor, std::uint8_t patch);
    Version(const std::string& version);
    Version(std::uint32_t version);

    void setMajor(std::uint8_t newMajor);
    void setMinor(std::uint8_t newMinor);
    void setPatch(std::uint8_t newPatch);

    std::uint8_t getMajor() const;
    std::uint8_t getMinor() const;
    std::uint8_t getPatch() const;

    std::uint32_t toUint32() const;
    std::size_t toSizeType() const;
    std::string toString() const;

    operator std::uint32_t() const;
    operator std::size_t() const;
    operator std::string() const;

    bool operator<(const Version& rhs) const;
    bool operator<=(const Version& rhs) const;
    bool operator==(const Version& rhs) const;
    bool operator!=(const Version& rhs) const;
    bool operator>=(const Version& rhs) const;
    bool operator>(const Version& rhs) const;


private:
    std::uint8_t m_major;
    std::uint8_t m_minor;
    std::uint8_t m_patch;
};

std::ostream& operator<<(std::ostream& o, const Version& ver);

}