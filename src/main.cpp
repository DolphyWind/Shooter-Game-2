#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <fmt/core.h>
#include <clip/clip.h>
#include <pprint/pprint.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <curl/curl.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <effolkronium/random.hpp>
#include <Network/RequestManager.hpp>
#include <SFEX/General/Multitype.hpp>

int main(int argc, char** argv)
{
    sg::RequestManager::init();
    sg::Response out = sg::RequestManager::get("https://raw.githubusercontent.com/DolphyWind/DolphyWind/main/README.md");
    if(out.request_successfull)
    {
        std::cout << "Response code: " << out.response_code << std::endl;
        std::cout << out.data << std::endl;
    }
    else
    {
        std::cout << "An error has occured during a get request: " << out.data << std::endl;
    }

    return 0;
}
