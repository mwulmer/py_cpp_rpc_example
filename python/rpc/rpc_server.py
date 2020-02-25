from werkzeug.wrappers import Request, Response
from werkzeug.serving import run_simple

from jsonrpc import JSONRPCResponseManager, dispatcher


class RPCServer:
    """
    This class is a simple RPC server.
    """
    def __init__(self):
        run_simple("0.0.0.0", 8900, self.start_server)  # Bind the server to IP 0.0.0.0 and port 8900.

    @Request.application
    def start_server(self, request):
        response = JSONRPCResponseManager.handle(request.data, dispatcher)
        return Response(response.json, mimetype="application/json")

    @dispatcher.add_method
    def hello_world(**kwargs):
        """
        This function prints out "Hello world!". It requires no arguments and returns nothing.
        :param kwargs: Empty dict
        :return: No return
        """
        print("Hello World!")

    @dispatcher.add_method
    def add(**kwargs):
        """
        This function adds two numbers and returns the result.
        :param kwargs: A dict that should contain the numbers a and b.
        :return: Returns the sum of a and b in a dict.
        """
        if "a" not in kwargs:
            print("Missing argument: a")
            return {"result": None}
        if "b" not in kwargs:
            print("Missing argument: b")
            return {"result": None}
        print(str(kwargs["a"])+ " + " + str(kwargs["b"]) + " = " + str(kwargs["a"]+kwargs["b"]))
        return {"result" : kwargs["a"] + kwargs["b"]}


if __name__ == "__main__":
    rpc_server = RPCServer()  # After this call the server is up and running. You don't need to do anything else.
