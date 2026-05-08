
import time
import ethernet_socket as socket

from micropython import const
from ethernet_socket import htonl, htons
import json

SERVER_IP = (192, 168, 2, 82)
SERVER_PORT = const(5500)

class TCP_SOCK:
    """Socket Send implementation
    :param      iface   :WIZNET Object.
    :param int  timeout : Timeout in seconds for DHCP response.
    :param bool debug   : Enable debugging output.
    """

    def __init__(self, eth, response_timeout=30, debug=True):
        self._debug = debug
        self._response_timeout = response_timeout

        # Set socket interface
        socket.set_interface(eth)
        self._eth = eth
        self._sock = None

    def tcp_connect(self, ip_address=SERVER_IP, port=SERVER_PORT):
        try:
            self._sock = socket.socket(type=socket.SOCK_STREAM) #TCP
            print(self._sock)
        except RuntimeError:
            if self._debug:
                print("* TCP: Failed to allocate socket")
        else: #Nothing went wrong 
            self._sock.settimeout(self._response_timeout)
            try:
                self._sock.connect((ip_address, port))
            except MemoryError:
                self._sock.close()
                self._sock = None
            except OSError:
                self._sock.close()
                self._sock = None
            
    def Send_String(self, str):
        _BUFF = bytearray(len(str))
        _BUFF[:] = str.encode()
        self._sock.send(_BUFF)

    def Get_ByteArray(self):
        _BUFF = bytearray(0)
        rx_len = self._sock.recv_into(_BUFF)
        return _BUFF[:rx_len]
    
    
    def Get_String(self) -> str:
        _BUFF = bytearray(0)
        rx_len = self._sock.recv_into(_BUFF)
        str_rx = _BUFF.decode()
        return str_rx

    def Send_Json(self, json_data):
        hello_msg_str = "You rock!\n"
        str_data = json.dumps(json_data)
        _BUFF = bytearray(len(str_data))
        _BUFF[:] = b"\x00" * len(_BUFF)
        _BUFF[:] = str_data.encode()
        self._sock.send(_BUFF)

    def close(self):
        self._sock.close()