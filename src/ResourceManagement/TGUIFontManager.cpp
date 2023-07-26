#include <ResourceManagement/TGUIFontManager.hpp>

TGUIFontData::TGUIFontData()
{
    
}

TGUIFontData::~TGUIFontData()
{
        
}

TGUIFontData::TGUIFontData(const std::string& fontFilename, tgui::BackendFontSFML* fontPtr)
{
    filename = fontFilename;
    sfmlFontData = std::shared_ptr<tgui::BackendFontSFML>(fontPtr);
    tguiFontData = tgui::Font(sfmlFontData, fontFilename);
}

TGUIFontManager::~TGUIFontManager()
{

}

bool TGUIFontManager::loadFromFile(const std::string& key, const std::string& filename)
{
    tgui::BackendFontSFML* backendFont = new tgui::BackendFontSFML();
    (*this)[key] = TGUIFontData();
    (*this)[key].filename = filename;
    bool is_successfull = backendFont->loadFromFile(filename);
    if(!is_successfull) return false;

    (*this)[key] = TGUIFontData(filename, backendFont);

    return true;
}
