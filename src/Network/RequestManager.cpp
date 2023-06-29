#include <Network/RequestManager.hpp>

namespace sg
{

CURL* RequestManager::curl = NULL;

RequestManager::RequestManager()
{
    // Initialize the curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    RequestManager::curl = curl_easy_init();

    // Throw std::bad_alloc if there is an error during allocation
    if(!RequestManager::curl)
    {
        throw std::bad_alloc();
    }
    curl_easy_setopt(RequestManager::curl, CURLOPT_WRITEFUNCTION, RequestManager::write_func);
}

RequestManager::~RequestManager()
{
    curl_easy_cleanup(RequestManager::curl);
    curl_global_cleanup();
}

RequestManager& RequestManager::instance()
{
    static RequestManager rm;
    return rm;
}

std::size_t RequestManager::write_func(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    std::string* data = (std::string*) userdata;
    *data = ptr;
    return size * nmemb;
}

void RequestManager::init()
{
    RequestManager& rm = RequestManager::instance();
}

Response RequestManager::get(const std::string &url)
{
    std::string out;
    long response_code;

    // Modify the curl options
    curl_easy_setopt(RequestManager::curl, CURLOPT_WRITEDATA, &out);
    curl_easy_setopt(RequestManager::curl, CURLOPT_URL, url.c_str());
    
    CURLcode res = curl_easy_perform(RequestManager::curl);
    if(res != CURLE_OK)
    {
        out = curl_easy_strerror(res);
        return {out, 0, false};
    }
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

    return Response{out, response_code, true};
}

}