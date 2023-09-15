#include <Modding/ModConfig.hpp>

InvalidFieldException::InvalidFieldException(const std::string& msg): m_msg(msg)
{
}

const char* InvalidFieldException::what() const noexcept
{
    return m_msg.c_str();
}

void EntityData::readFromJson(sfex::Multitype& jsonObj)
{
    this->name = jsonObj["name"].as_string();
    if(!ModConfig::is_name_valid(this->name))
    {
        throw InvalidFieldException("Entity name can only contain ascii characters, numbers and underscore. Entity name cannot start with a number.");
    }

    this->file = jsonObj["file"].as_string();

    this->hidden_in_mapmaker = jsonObj["hidden_in_mapmaker"].as_bool();
    this->spawn_if_not_exists = jsonObj["spawn_if_not_exists"].as_bool();
    this->one_instance_only = jsonObj["one_instance_only"].as_bool();
}

sfex::Multitype EntityData::convertToJson() const
{
    sfex::MultitypeMap result;
    result["name"] = name;
    result["file"] = file;
    result["hidden_in_mapmaker"] = hidden_in_mapmaker;
    result["spawn_if_not_exists"] = spawn_if_not_exists;
    result["one_instance_only"] = one_instance_only;

    return result;
}

sfex::Multitype ModConfig::toJSON()
{
    sfex::MultitypeMap jsonMap;
    jsonMap["version"] = version.toString();
    jsonMap["authors"] = authors;
    jsonMap["title"] = title;
    jsonMap["description"] = description;
    jsonMap["dependencies"] = dependencies;
    jsonMap["modname"] = modname;

    std::vector<sfex::Multitype> entityJSONList;
    entityJSONList.reserve(entites.size());
    for(auto& e : entites)
    {
        entityJSONList.push_back(e.convertToJson());
    }
    jsonMap["entities"] = entityJSONList;


    return jsonMap;
}

void ModConfig::loadFromString(const std::string& config)
{
    sfex::Multitype json = sfex::Multitype::parse(config);

    std::string versionStr = json["version"].as_string();
    try
    {
        version = Version(versionStr);
    }
    catch (const VersionParsingException& vpe)
    {
        throw vpe;
    }
    authors = json["authors"].as_list<std::string>();
    if(authors.empty())
    {
        authors = {"Unknown author(s)"};
    }

    title = json["title"].as_string();
    if(title.empty())
    {
        title = "No title.";
    }

    description = json["description"].as_string();
    if(description.empty())
    {
        description = "No description.";
    }

    dependencies = json["dependencies"].as_list<std::string>();

    modname = json["modname"].as_string();
    if(!is_name_valid(modname))
    {
        throw InvalidFieldException("Mod name can only contain ascii characters, numbers and underscore. Mod name cannot start with a number.");
    }

    std::vector<sfex::Multitype> entityData = json["entities"].as_list();
    entites.clear();
    entites.reserve(entityData.size());

    for (auto& entityJson : entityData)
    {
        EntityData ed;
        ed.readFromJson(entityJson);
        entites.push_back(ed);
    }
}

void ModConfig::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        throw std::runtime_error("File does not exists!");
    }

    std::string fileContent = (std::stringstream() << file.rdbuf()).str();
    file.close();
    loadFromString(fileContent);
}

void ModConfig::printModConfig()
{
    std::cout << std::boolalpha;
    std::cout << "Name: " << modname << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Version: " << version << std::endl;

    std::cout << "Authors: ";
    for(auto& item : authors)
    {
        std::cout << item << ", ";
    }
    std::cout << std::endl;

    std::cout << "Dependencies: ";
    for(auto& item : dependencies)
    {
        std::cout << item << ", ";
    }
    std::cout << std::endl;

    std::cout << "Entities: " << std::endl;
    for (auto& e : entites)
    {
        std::cout << "\tName: " << e.name << std::endl;
        std::cout << "\tFile: " << e.file << std::endl;
        std::cout << "\thidden_in_mapmaker: " << e.hidden_in_mapmaker << std::endl;
        std::cout << "\tone_instance_only: " << e.one_instance_only << std::endl;
        std::cout << "\tspawn_if_not_exists: " << e.spawn_if_not_exists << std::endl;
        std::cout << std::endl;
    }
}

bool ModConfig::is_name_valid(const std::string& name)
{
    if(name.empty()) return false;
    for(auto& c : name)
    {
        if('a' <= c && c <= 'z') continue;
        if('A' <= c && c <= 'Z') continue;
        if('0' <= c && c <= '9') continue;
        if('_' == c) continue;

        return false;
    }
    if(std::isdigit(name[0])) return false;
    return true;
}

std::string ModConfig::getModName() const
{
    return modname;
}

Version ModConfig::getVersion() const
{
    return version;
}

std::vector<std::string> ModConfig::getAuthors() const
{
    return authors;
}

std::string ModConfig::getTitle() const
{
    return title;
}

std::string ModConfig::getDescription() const
{
    return description;
}

std::vector<std::string> ModConfig::getDependencies() const
{
    return dependencies;
}

std::vector<EntityData> ModConfig::getEntities() const
{
    return entites;
}