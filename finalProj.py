import subprocess
from datetime import datetime
import socket
import requests

nq = False
sq = False
nb = False
sb = False
print(nq)
UDP_IP = "192.168.1.29" # The IP that is printed in the serial monitor from the ESP32
SHARED_UDP_PORT = 4210
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Internet  # UDP
sock.connect((UDP_IP, SHARED_UDP_PORT))


response = requests.get("https://api.weather.gov/gridpoints/OKX/34,32/forecast")
print(response.status_code)

json_data=response.json()
props=json_data['properties']
periods = props['periods']
val = periods[0]
temp = val['temperature']
temp = str(temp)
sock.send(temp.encode())

def loop():
    while(True):
        nq = False
        now = datetime.now().time()	
        time = now.strftime("%H:%M")
        timeconv = datetime.strptime(time, '%H:%M')
        data = sock.recv(2048)
        print(data)
        if (data.decode() == "qn"):
            nq = True
        # On north switch, yellow button push (checks upcoming uptown Q's)
        if(nq):
            result = str(subprocess.check_output(['sh', './NQ.sh']))
            first = result[7:12:1]
            second = result[13:18:1]
            firstconv = datetime.strptime(first, '%H:%M')
            secondconv = datetime.strptime(second, '%H:%M')
            split = ':'.join(str(firstconv-timeconv).split(':')[:2])
            split2 = ':'.join(str(secondconv-timeconv).split(':')[:2])
            train1 =("Uptown Q in" + split[2:5] + "minutes")
            train2 =("Uptown Q in" + split2[2:5] + "minutes") 
            print("Uptown Q in", split[2:5], "minutes")
            print("Uptown Q in", split2[2:5], "minutes")
            sock.send(train1.encode())
            sock.send(train2.encode())
        # On south switch, yellow button push (checks upcoming downtown Q's)
        if(data.decode() == "qs"):
            result = str(subprocess.check_output(['sh', './SQ.sh']))
            first = result[7:12:1]
            second = result[13:18:1]
            firstconv = datetime.strptime(first, '%H:%M')
            secondconv = datetime.strptime(second, '%H:%M')
            split = ':'.join(str(firstconv-timeconv).split(':')[:2])
            split2 = ':'.join(str(secondconv-timeconv).split(':')[:2])
            train1 =("Downtown Q in" + split[2:5] + "minutes")
            train2 =("Downtown Q in" + split2[2:5] + "minutes") 
            print("Downtown Q in", split[2:5], "minutes")
            print("Downtown Q in", split2[2:5], "minutes")
            sock.send(train1.encode())
            sock.send(train2.encode())
        #On orange button push (checks upcoming uptown B's)
        if(data.decode()== "bn"):
            result = str(subprocess.check_output(['sh', './NB.sh']))
            first = result[7:12:1]
            second = result[13:18:1]
            firstconv = datetime.strptime(first, '%H:%M')
            secondconv = datetime.strptime(second, '%H:%M')
            split = ':'.join(str(firstconv-timeconv).split(':')[:2])
            split2 = ':'.join(str(secondconv-timeconv).split(':')[:2])
            train1 =("Uptown B in" + split[2:5] + "minutes")
            train2 =("Uptown B in" + split2[2:5] + "minutes")  
            print("Uptown B in", split[2:5], "minutes")
            print("Uptown B in", split2[2:5], "minutes") 
            sock.send(train1.encode())
            sock.send(train2.encode())
        #On orange button push (checks upcoming downtown B's)
        if(data.decode() == "bs"):
            result = str(subprocess.check_output(['sh', './SB.sh']))
            first = result[7:12:1]
            second = result[13:18:1]
            firstconv = datetime.strptime(first, '%H:%M')
            secondconv = datetime.strptime(second, '%H:%M')
            split = ':'.join(str(firstconv-timeconv).split(':')[:2])
            split2 = ':'.join(str(secondconv-timeconv).split(':')[:2])
            print("Downtown B in", split[2:5], "minutes")
            train1 =("Downtown B in" + split[2:5] + "minutes") 
            train2 = ("Downtown B in" + split2[2:5] + "minutes")
            print("Downtown B in", split2[2:5], "minutes")
            sock.send(train1.encode())
            sock.send(train2.encode())
if __name__ == "__main__":
    sock.send('Hello ESP32'.encode())
    loop()