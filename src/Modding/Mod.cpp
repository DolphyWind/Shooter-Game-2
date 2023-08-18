#include <Modding/Mod.hpp>

sfex::Multitype Mod::toJSON()
{
    sfex::MultitypeMap jsonMap;
    jsonMap["version"] = version.toString();
    jsonMap["authors"] = authors;
    jsonMap["title"] = title;
    jsonMap["description"] = description;
    jsonMap["dependencies"] = dependencies;
    jsonMap["underlyingName"] = underlyingName;
    jsonMap["entities"] = entities;

    return jsonMap;
}