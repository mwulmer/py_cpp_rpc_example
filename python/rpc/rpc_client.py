import requests
import json


def rpc_call(url, method, params=None, timeout=100):
    """
    This function calls a method at an RPC server at the given url.
    :param url: The url must be a string consisting of address:port. Address is a hostname or an IP.
    :param method: The method you want to call at the remote server. Must be a string.
    :param params: The parameters you want to provide to the given method. Must be a dict.
    :param timeout: The function waits this amount of time for an answer from the server before terminating.
    :return: Returns the response from the server, returns None in case of an error.
    """
    headers = {'content-type': 'application/json'}

    payload = {
        "id": 1,
        "jsonrpc": "2.0",
        "method": method,
        "params": params,
    }
    print(payload)
    try:
        response = requests.post(url, data=json.dumps(payload), headers=headers, timeout=timeout).json()
    except requests.Timeout:
        print('Timeout, server has terminated or does not exist.')
        response = None
    except requests.ConnectionError:
        print('Connection error, target url not reachable.')
        response = None

    return response


if __name__ == '__main__':
    print(rpc_call('http://localhost:8900', 'hello_world', None))  # An example call without any arguments.
    params={'a': 2,'b': 6}
    print(rpc_call('http://localhost:8900', 'add', params))  # An example call with two arguments.
