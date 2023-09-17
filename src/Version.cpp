#include <Version.hpp>

VersionParsingException::VersionParsingException(const std::string& msg): m_msg(msg)
{
}

VersionParsingException::VersionParsingException(const VersionParsingException& other) noexcept
{
    m_msg = other.m_msg;
}

const char* VersionParsingException::what() const noexcept
{
    return m_msg.c_str();
}

Version::Version(std::uint8_t major, std::uint8_t minor, std::uint8_t patch):
    m_major(major), m_minor(minor), m_patch(patch)
{}

Version::Version(const std::string& version)
{
    try
    {
        std::size_t first_dot = version.find('.', 0);
        std::size_t second_dot = version.find('.', first_dot + 1);
        std::size_t last_dot = version.find('.', second_dot + 1); // Possibly std::string::npos

        // Break original string into three strings
        std::string majorStr = version.substr(0, first_dot);
        std::string minorStr = version.substr(first_dot + 1, second_dot - first_dot - 1);
        if(last_dot == std::string::npos) last_dot = version.length();
        std::string patchStr = version.substr(second_dot + 1, last_dot - second_dot - 1);

        m_major = static_cast<std::uint8_t>( std::stoi(majorStr) );
        m_minor = static_cast<std::uint8_t>( std::stoi(minorStr) );
        m_patch = static_cast<std::uint8_t>( std::stoi(patchStr) );
    }
    catch (const std::exception& e)
    {
        throw VersionParsingException(e.what());
    }
}

Version::Version(std::uint32_t version)
{
    m_major = (version >> 16) & 0b11111111;
    m_minor = (version >> 8) & 0b11111111;
    m_patch = version & 0b11111111;
}

void Version::setMajor(std::uint8_t major)
{
    m_major = major;
}

void Version::setMinor(std::uint8_t minor)
{
    m_minor = minor;
}

void Version::setPatch(std::uint8_t patch)
{
    m_patch = patch;
}

std::uint8_t Version::getMajor() const
{
    return m_major;
}

std::uint8_t Version::getMinor() const
{
    return m_minor;
}

std::uint8_t Version::getPatch() const
{
    return m_patch;
}

std::uint32_t Version::toUint32() const
{
    return (m_major << 16) | (m_minor << 8) | m_patch;
}

std::size_t Version::toSizeType() const
{
    return static_cast<std::size_t>( toUint32() );
}

std::string Version::toString() const
{
    return
    std::to_string( static_cast<int>(m_major) ) + "." +
    std::to_string( static_cast<int>(m_minor) ) + "." +
    std::to_string( static_cast<int>(m_patch) );
}

Version::operator std::uint32_t() const
{
    return toUint32();
}

Version::operator std::size_t() const
{
    return toSizeType();
}

Version::operator std::string() const
{
    return toString();
}

bool Version::operator<(const Version& rhs) const
{
    return (toUint32() < rhs.toUint32());
}

bool Version::operator<=(const Version& rhs) const
{
    return (this->operator<(rhs) || this->operator==(rhs));
}

bool Version::operator==(const Version& rhs) const
{
    return (toUint32() == rhs.toUint32());
}

bool Version::operator!=(const Version& rhs) const
{
    return !(this->operator==(rhs));
}

bool Version::operator>=(const Version& rhs) const
{
    return !(this->operator<(rhs));
}

bool Version::operator>(const Version& rhs) const
{
    return (this->operator>=(rhs) && !this->operator==(rhs));
}

std::ostream& operator<<(std::ostream& o, const Version& ver)
{
    return (o << ver.toString());
}
