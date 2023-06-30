#pragma once
#include <SFEX/SFEX.hpp>
#include <TGUI/TGUI.hpp>
#include <memory>

namespace sg
{

struct TGUIFontData
{
    std::string filename;
    tgui::Font tguiFontData;
    std::shared_ptr<tgui::BackendFontSFML> sfmlFontData;

    TGUIFontData();
    TGUIFontData(const std::string& fontFilename, tgui::BackendFontSFML* fontPtr);
    ~TGUIFontData();
};

class TGUIFontManager : public sfex::ManagerBase<TGUIFontData>
{
private:
public:
    ~TGUIFontManager();

    bool loadFromFile(const std::string& key, const std::string& filename);
};

}