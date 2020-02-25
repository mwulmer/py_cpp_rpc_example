#include "rpc_server.hpp"


CppHttpLibServerConnector::CppHttpLibServerConnector(jsonrpccxx::JsonRpcServer &server, std::string address, int port) : _server(server), _address(address), _port(port) {
    this->_httpServer.Post("/", [&](const httplib::Request &req, httplib::Response &res) {
        res.status = 200;
//        std::cout<<"REQUEST: "<<req.body<<std::endl;
        res.set_content(server.HandleRequest(req.body), "application/json");
//        std::cout<<"RESPONSE: "<<res.body<<std::endl;
    });
}

CppHttpLibServerConnector::~CppHttpLibServerConnector(){
    this->stop_listening();
}

bool CppHttpLibServerConnector::start_listening(){
    if (this->_httpServer.is_running())
        return false;
    this->_thread = std::thread([this]() { this->_httpServer.listen(this->_address.c_str(), this->_port); });
    return true;
}

void CppHttpLibServerConnector::stop_listening(){
    if (this->_httpServer.is_running()) {
        this->_httpServer.stop();
        this->_thread.join();
    }
}

Interface::Interface(){
    // RPC server is created
    this->_rpc_server = new jsonrpccxx::JsonRpc2Server();

    // Functions are bound to the RPC server.
    this->_rpc_server->Add("hello_world", jsonrpccxx::GetHandle(&Interface::hello_world, *this),{});
    this->_rpc_server->Add("add", jsonrpccxx::GetHandle(&Interface::add, *this),{"a","b"});
}

Interface::~Interface(){
    delete this->_rpc_server;
}

nlohmann::json Interface::add(const double a, const double b){
    nlohmann::json response;
    response["result"]=a+b;
    return response;
}

nlohmann::json Interface::hello_world(){
    std::cout<<"Hello World"<<std::endl;
    // If the result is supposed to be empty, return an empty json object.
    return nlohmann::json();
}

jsonrpccxx::JsonRpc2Server* Interface::get_server(){
    return this->_rpc_server;
}

int main(){

    Interface interface;
    CppHttpLibServerConnector http_connector(*interface.get_server(),"0.0.0.0",8900);
    http_connector.start_listening();

    // At this point the server is up and running. Since it runs in its own thread we something like a while loop to keep it running.

    std::cout<<"Starting server. Terminate with Ctrl-C."<<std::endl;
    while(true);

    return 0;
}
