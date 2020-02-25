#pragma once

#include <iostream>

#include <jsonrpccxx/server.hpp>
#include <httplib/httplib.h>


/**
 * This class provides an easy http interface for receiving messages. Just use it as it is.
 */
class CppHttpLibServerConnector {
public:
    explicit CppHttpLibServerConnector(jsonrpccxx::JsonRpcServer& server, std::string address, int port);
    virtual ~CppHttpLibServerConnector();

    bool start_listening();
    void stop_listening();

private:
    std::thread _thread;
    jsonrpccxx::JsonRpcServer& _server;
    httplib::Server _httpServer;
    std::string _address;
    int _port;
};

/**
 * This interface class demonstrates how to design an RPC server and use it.
 */
class Interface{
public:
    Interface();
    ~Interface();

    /**
     * Getter function for the RPC server.
     * @return Returns a pointer to the RPC server.
     */
    jsonrpccxx::JsonRpc2Server* get_server();

private:
    /**
     * Example function without arguments.
     * @return Returns an empty json object.
     */
    nlohmann::json hello_world();

    /**
     * Example function with two arguments of type double. It adds two numbers and returns the result.
     * @param a First number.
     * @param b Second number.
     * @return Returns a json object that contains the sum of the parameters a and b.
     */
    nlohmann::json add(const double a, const double b);

    /**
     * RPC server object.
     */
    jsonrpccxx::JsonRpc2Server* _rpc_server;

};

