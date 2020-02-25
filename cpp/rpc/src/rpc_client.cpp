#include "rpc_client.hpp"

#include <iostream>
#include <nlohmann/json.hpp>

CppHttpLibClientConnector::CppHttpLibClientConnector(const std::string &host, int port, double timeout) : _httpClient(host.c_str(), port), _timeout(timeout) {

}

std::string CppHttpLibClientConnector::Send(const std::string &request){
    this->_httpClient.set_timeout_sec(this->_timeout);
    auto res = this->_httpClient.Post("/", request, "application/json");
    if (!res || res->status != 200) {
        throw jsonrpccxx::JsonRpcException(-32003, "client connector error, received status != 200");
    }
    return res->body;
}

bool rpc_call(const std::string &address, unsigned port, const std::string &method, const jsonrpccxx::positional_parameter& request, nlohmann::json& response, long timeout, unsigned id){
    try{
        CppHttpLibClientConnector httpClient(address, port);
        jsonrpccxx::JsonRpcClient client(httpClient, jsonrpccxx::version::v2);
        response = client.CallMethod<nlohmann::json>(1,method,request);
        return true;
    }catch(const nlohmann::json::exception& e){
        std::cout<<e.what()<<std::endl;
        return false;
    }catch(const jsonrpccxx::JsonRpcException& e){
        std::cout<<e.what()<<std::endl;
        return false;
    }
}


int main(){

    nlohmann::json response;
    // Example for a call without arguments.
    rpc_call("localhost",8900,"hello_world",{},response);
    // Example for a call with two arguments of type double.
    rpc_call("localhost",8900,"add",{4.0,5.0},response);

    // Print the response.
    std::cout<<"Result is "<<response["result"]<<std::endl;
}
