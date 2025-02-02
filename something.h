#pragma once
#include <iostream>
#include <boost/beast.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <boost/asio/impl/src.hpp>
#include <stdio.h>

namespace http = boost::beast::http;

const static std::string MAIN_API = "";
const static std::string API_ARGUMENTS = "/json/";
class client {
    static std::string getResponse(std::string ip) {
        boost::asio::io_context io;
        boost::asio::ip::tcp::resolver resolver(io);
        boost::asio::ip::tcp::socket socket(io);
        boost::asio::connect(socket, resolver.resolve(MAIN_API, "80"));

        http::request<http::string_body> req(http::verb::get, API_ARGUMENTS, 11);
        req.set(http::field::host, MAIN_API);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        http::write(socket, req);
        std::string response;
        {
            boost::beast::flat_buffer buffer;
            http::response<http::dynamic_body> res;
            http::read(socket, buffer, res);
            response = boost::beast::buffers_to_string(res.body().data());
        }
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        return response;
    };