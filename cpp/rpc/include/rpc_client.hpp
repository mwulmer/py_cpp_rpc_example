#pragma once

#include <jsonrpccxx/client.hpp>
#include <httplib/httplib.h>


/**
 * This class provides an easy http interface for sending string-based messages to a url. Just use it as it is.
 */
class CppHttpLibClientConnector : public jsonrpccxx::IClientConnector {
public:
    explicit CppHttpLibClientConnector(const std::string &host, int port, double timeout=5);
    std::string Send(const std::string &request) override;
private:
    httplib::Client _httpClient;
    double _timeout;
};

/**
 * @brief This method can be used to call a method on a remote rpc server.
 * @param address The address of the server, i.e. a hostname or an IP address.
 * @param port The port at the server to which to connect.
 * @param method The method that is called on the server.
 * @param request The request must contain the arguments required by the indicated method in the right order.
 * @param response The response is a json struct and contains the answer from the server.
 * @param timeout The time the call waits for an answer until it terminates.
 * @param id Id of the call (not really important here)
 * @return Returns true if the call was successful, false otherwise (e.g. in case of timeout).
 */
bool rpc_call(const std::string& address, unsigned port, const std::string& method, const jsonrpccxx::positional_parameter &request,  nlohmann::json &response, long timeout=1000, unsigned id=0);
