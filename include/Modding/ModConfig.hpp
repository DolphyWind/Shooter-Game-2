#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <SFEX/General/Multitype.hpp>
#include <Version.hpp>

class InvalidFieldException : public std::exception
{
public:
    InvalidFieldException(const std::string& msg="");
    const char * what() const noexcept override;
private:
    std::string m_msg;
};

struct EntityData
{
    EntityData(): name(), file(), hidden_in_mapmaker(false), one_instance_only(false), spawn_if_not_exists(false)
    {}

    bool operator==(const EntityData& other) const;

    std::string name;
    std::string file;
    bool hidden_in_mapmaker;
    bool one_instance_only;
    bool spawn_if_not_exists;

    void readFromJson(sfex::Multitype& jsonObj);
    sfex::Multitype convertToJson() const;
};

class ModConfig
{
public:
    sfex::Multitype toJSON();
    void loadFromString(const std::string& config);
    void loadFromFile(const std::string& filename);
    void printModConfig();
    static bool is_name_valid(const std::string& name);

    [[nodiscard]] std::string getModName() const;
    [[nodiscard]] Version getVersion() const;
    [[nodiscard]] std::vector<std::string> getAuthors() const;
    [[nodiscard]] std::string getTitle() const;
    [[nodiscard]] std::string getDescription() const;
    [[nodiscard]] std::vector<std::string> getDependencies() const;
    [[nodiscard]] std::vector<EntityData> getEntities() const;
private:
    Version version;
    std::vector<std::string> authors;
    std::string title;
    std::string description;
    std::vector<std::string> dependencies;
    std::string modname;
    std::vector<EntityData> entites;
};