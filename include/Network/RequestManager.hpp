#pragma once
#include <curl/curl.h>
#include <SFEX/General/Singleton.hpp>
#include <optional>
#include <iostream>

// TODO: Replace with something else
// Simple response object containing response data, response code and response success state.
// If the response is unsuccessfull, the error would be print out to data and response_code will set to zero.
struct Response
{
    std::string data;
    long response_code;
    bool request_successfull;
};

class RequestManager : public sfex::Singleton
{
private:
    static CURL* curl;

    static std::size_t write_func(char *ptr, size_t size, size_t nmemb, void *userdata);
    static RequestManager &instance();
public:
    RequestManager();
    ~RequestManager();

    static void init();
    static Response get(const std::string& url);
};
