#pragma once

#include "server_http.hpp"
#include <memory>
#include <boost/filesystem.hpp>
#include <stdexcept>
#include "Link.h"
#include <set>
#include <optional>


using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

std::optional<Link> print_inorder(Link  *p, int searchNumber) {
    if (p->node ==  searchNumber) {
            std::cout << "Found " << searchNumber << " on node " << p->node << std::endl;
            //std::cout << p->toString();
            return *p;
    } else {
        std::cout << "Didn't find " << searchNumber << " on node " << p->node << std::endl;
        for ( Link c : p->children) {
            auto o = print_inorder( &c, searchNumber);
            if ( o ) {
                //std::cout << o->toString();
                return o;
            }
        }
    }
    return {};
}

class WebServer
{
public:
        WebServer(Link * rootLink) : rootLink(rootLink)
        {
                server.config.port = 8080;
                std::cout << "Open your browser against: http://localhost:8080\n";
                server.resource["^/data$"]["GET"] =
                [rootLink](std::shared_ptr<HttpServer::Response> response,
                           std::shared_ptr<HttpServer::Request> request) {
                        std::stringstream stream;
                        stream << rootLink->toJson();

                        // Find length of content_stream (length received using content_stream.tellp())
                        stream.seekp(0, std::ios::end);

                        *response << "HTTP/1.1 200 OK\r\nContent-Length: " << stream.tellp() << "\r\n\r\n"
                                  << stream.rdbuf();
                };

                // Handle the click on a URL /fetch/1
                server.resource["^/fetch/([0-9]+)$"]["GET"] =
                [rootLink](std::shared_ptr<HttpServer::Response> response,
                           std::shared_ptr<HttpServer::Request> request) {
                        std::string number = request->path_match[1];
                        std::cout << "fetch node : " << number << std::endl;
                        //Link* l = rootLink.findChild(number);
                        //l->parseLinks();
                        //print_path(&rootLink);
                        auto o = print_inorder( rootLink, std::stoi( number ));
                        if (o) {
                            std::cout << "Parsing links on optional\n";
                            o->parseLinks();
                            std::cout << o->toString();
                        }

                        std::stringstream stream;
                        stream << rootLink->toJson();

                        // Find length of content_stream (length received using content_stream.tellp())
                        stream.seekp(0, std::ios::end);

                        *response << "HTTP/1.1 200 OK\r\nContent-Length: " << stream.tellp() << "\r\n\r\n"
                                  << stream.rdbuf();
                };

                server.default_resource["GET"] = [] (std::shared_ptr<HttpServer::Response> response,
                                                     std::shared_ptr<HttpServer::Request> request) {
                        try {
                                auto web_root_path = boost::filesystem::canonical("web");
                                auto path = boost::filesystem::canonical(web_root_path / request->path);
                                // Check if path is within web_root_path
                                if (std::distance(web_root_path.begin(), web_root_path.end()) >
                                    std::distance(path.begin(), path.end()) ||
                                    !std::equal(web_root_path.begin(), web_root_path.end(), path.begin()))
                                        throw std::invalid_argument("path must be within root path");
                                if (boost::filesystem::is_directory(path))
                                        path /= "index.html";

                                SimpleWeb::CaseInsensitiveMultimap header;

                                //    Uncomment the following line to enable Cache-Control
                                //    header.emplace("Cache-Control", "max-age=86400");

                                auto ifs = std::make_shared<std::ifstream>();
                                ifs->open(path.string(), std::ifstream::in | std::ios::binary | std::ios::ate);

                                if (*ifs) {
                                        auto length = ifs->tellg();
                                        ifs->seekg(0, std::ios::beg);

                                        header.emplace("Content-Length", to_string(length));
                                        response->write(header);

                                        // Trick to define a recursive function within this scope (for example purposes)
                                        class FileServer
                                        {
public:
                                                static void read_and_send(
                                                        const std::shared_ptr<HttpServer::Response> &response,
                                                        const std::shared_ptr<std::ifstream> &ifs)
                                                {
                                                        // Read and send 128 KB at a time
                                                        static std::vector<char> buffer(
                                                                131072); // Safe when server is running on one thread
                                                        std::streamsize read_length;
                                                        if ((read_length = ifs->read(&buffer[0], static_cast<std::streamsize>(
                                                                                             buffer.size()))
                                                                           .gcount()) > 0) {
                                                                response->write(&buffer[0], read_length);
                                                                if (read_length == static_cast<std::streamsize>(buffer.size())) {
                                                                        response->send(
                                                                                [response, ifs](const SimpleWeb::error_code &ec) {
                                                                                if (!ec)
                                                                                        read_and_send(response, ifs);
                                                                                else
                                                                                        std::cerr << "Connection interrupted" << std::endl;
                                                                        });
                                                                }
                                                        }
                                                }
                                        };
                                        FileServer::read_and_send(response, ifs);
                                } else
                                        throw std::invalid_argument("could not read file");
                        } catch (const std::exception &e) {
                                response->write(SimpleWeb::StatusCode::client_error_bad_request,
                                                "Could not open path " + request->path + ": " + e.what());
                        }
                };

                server.on_error = [] (std::shared_ptr<HttpServer::Request> /*request*/,
                                      const SimpleWeb::error_code & /*ec*/) {
                        // Handle errors here
                };

                // server.start();
        }
        void start() {
                server.start();
        }

private:
        Link * rootLink;
        HttpServer server;
};
