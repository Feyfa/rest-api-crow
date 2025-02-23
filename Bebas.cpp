//msbuild Bebas.sln; .\x64\Debug\Bebas.exe`
#include <iostream>
#include "helpers/MyLogging/MyLogging.h"
#include <crow.h>

int main()
{   
    MyLogging logging;
    crow::logger::setHandler(&logging);

    CROW_LOG_INFO << "START APP";

    crow::SimpleApp app;

    /* METHOD GET */
    CROW_ROUTE(app, "/").
    methods("GET"_method)
    ([]() {
        CROW_LOG_INFO << "Ini Adalah Basic Route";
        return crow::response{200, "Ini Adalah Basic Route"};
    });

    CROW_ROUTE(app, "/home").
    methods("GET"_method)
    ([]() {
        CROW_LOG_INFO << "Home Page 123456789";
        return crow::response{200, "Home Page 123456789"};
    });
    /* METHOD GET */

    /* METHOD POST */
    CROW_ROUTE(app, "/post/<string>").
    methods("POST"_method)
    ([](const crow::request& request, std::string user_type) {
        crow::json::wvalue json_response;

        //ubah string json menjadi json
        std::string body = request.body;
        if (body.empty())
        {
            json_response.clear();
            json_response["status"] = "error";
            json_response["message"] = "Request body is empty.";
            return crow::response{ 500, json_response.dump() };
        }
        crow::json::rvalue json_request;
        json_request = crow::json::load(body);
        //ubah string json menjadi json

        //response json
        json_response["status"] = "success";
        json_response["data"]["user_type"] = user_type;

        std::string nama = json_request.has("nama") ? json_request["nama"].s() : std::string("");
        std::string email = json_request.has("email") ? json_request["email"].s() : std::string("");
        std::string phone = json_request.has("phone") ? json_request["phone"].s() : std::string("");
        if (nama.empty() || email.empty() || phone.empty())
        {
            json_response.clear();
            json_response["status"] = "error";

            std::string message = "";
            if (nama.empty())
            {
                message += "The field name is required. ";
            }
            if (email.empty())
            {
                message += "The field email is required. ";
            }
            if (phone.empty())
            {
                message += "The field phone is required. ";
            }
            json_response["message"] = message;

            return crow::response{ 422, json_response.dump() };
        }
        json_response["data"]["nama"] = nama;
        json_response["data"]["email"] = email;
        json_response["data"]["phone"] = phone;
        //response json

        return crow::response{200, json_response.dump()};
    });
    /* METHOD POST */

    app.bindaddr("127.0.0.1").port(8080).multithreaded().run();
}