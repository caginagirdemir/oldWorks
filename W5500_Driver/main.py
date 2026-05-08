from ethernet_main import WIZNET
from machine import Pin, SPI
import ethernet_socket as socket
import time

spi = SPI(2)
cs = Pin(5,Pin.OUT)
rst=Pin(34)

ethernet_obj = WIZNET(spi,cs,rst,hostname="NextIstasyonAdiBuraya", debug=False)

print("My IP address is:", ethernet_obj.pretty_ip(ethernet_obj.ip_address)) #Aldığı IP adresi

# Örnek fonksiyon kullanımları

data = {
  "name": "John",
  "age": 30,
  "city": "New York"
}
ethernet_obj.sendJson(data)

message = "Test string"
ethernet_obj.sendString(message)

retstr = str()
while(retstr != "test"):
    retstr = ethernet_obj.getString()
    print(retstr)
    time.sleep(1)


