# twinThingPicoESPExample

Raspberry Pi PICO or RP2040 as IoT device using [ESP-01S](https://behind-the-scenes.net/introducing-the-inexpensive-esp-01-wi-fi-module/) for Wifi access.

This is an example for using my IoT framework of [TwinThingsPicoESP](https://github.com/jondurrant/twinThingPicoESP) for RP2040. 


# Hardware
+ Raspberry Pico
+ ESP-01S (1Mb) running ESP-AT 2.1

## Connections:
PICO Uart0 on GPIO12 and 13

|pico|function|ESP-01S| function|
|----|--------|-------|---------|
|G12 | TX     | RX    | RX      |
|G13 | RX     | TX    | TX      |
|3.3 | 3.3v   | 3.3   | 3.3v    |
|GND |GND     | GND   | GND     |
|3.3 | 3.3v   | EN    | via 10k res|


## ESP-01S
I got very cheap pack of ESP-01S but they came with 1Mb flash. Latest version of ESP-AT, version 2.2, requires 2MB. 

Fortunatly Jandrassy has built a working 2.1 firmware for 1MB. This is on github at: https://github.com/jandrassy/WiFiEspAT

To reliably upload the firmware to ESP-01S requires the RST IO0 to get pulled to zero and the released. Some further inform on how to do this at: https://blog.tiga.tech/flashing-esphome-firmware-to-esp-01s/

I used the RPI 4 to upload the firmware and the esptool.py. I had to drop frequency to 40m and change upload mode to dout in the download.config file. Then use the command
esptool.py --port /dev/ttyS0 write_flash @download.config


# Dependancies
## C++
+ [lwesp](https://github.com/MaJerle/lwesp): library for talking to ESP-AT over serial
+ + [forkedlwesp](https://github.com/jondurrant/lwespFork) Forked to allow MQTT over SSL. 
+ [FreeRTOS-Kernel](https://github.com/FreeRTOS/FreeRTOS-Kernel): dependency for lwesp
+ [json-maker](https://github.com/rafagafe/json-maker)
+ [tiny-json](https://github.com/rafagafe/tiny-json)

I use lwesp directly for MQTT but had to fork it to allow MQTT over SSL.

Configuration for the libraries are within the src/port folders. They are complex libraries and need porting for the Pico.

## Python3
I've used the Paho python client to demonstrat that I could get the device to respond to: 
+ MQTT Ping - topic causing device to respond back
+ Get - get the state of the device
+ Set - set the state of the device

The Python test scripts are in the "py" folder. They expect environment variable for the MQTT Hub you are using.
+ MQTT_HOST - host name to connect to, may be localhost
+ MQTT_PORT - port that mqtt service is listen on. Default 1883
+ MQTT_USER - user for authentication, will also be used as Client ID
+ MQTT_PASSWD - password for authentication

they also expect a parameter on teh command line of the client id of the target device. i.e. python3 ping1.py deviceId


# Cloning and build
git clone --recurse-submodules https://github.com/jondurrant/RPIPicoRTOSMQTT

main.cpp include "Credentials.env" for the Wifi AP name and passwd, MQTT Host, Port, Username and password. I've not included this file in the repo. Please create one looking something like this:

``` C++
#define SID "SID"
#define PASSWD "PWD"

#define MQTTHOST "IP"
#define MQTTPORT 1883
#define MQTTUSER "jon"
#define MQTTPASSWD "PWD"
```


## To build:
``` bash
cd RPIPicoRTOSMQTT
mkdir build
cd build
cmake ..
make
make install (only work if you used my config setup in the Pico Intro course as does SWD upload of code direct from make).
```

For more on how I use a Raspberry PI to build, deploy code  and debug the Pico see my course on [Udemy](https://www.udemy.com/course/introduction-to-c-development-environment-for-raspberry-pico/?referralCode=875319E04F95C9EC3414)

# MQTT Server
Easy to use Mosquitto on a RPI4. Followed the docker install guide at: (https://docs.cedalo.com/streamsheets/2.4/installation/)

Alternatively use EMQX, which works nicely.

## Clients
You will need to setup users or enable anonamous access to MQTT

## Topic Structure
I've tried to condence literals a bit, nervous on memory usage. 

TNG/<ID>/ - THING / ID, same as user name in my example
TNG/<ID>/LC - LC is lifecycle and annouces connection and disconnection
TNG/<ID>/TPC - TOPIC, for messaging to a specific thing

Example assuming you name the pico as "pico"
+ TNG/pico/TPC/PING - ping re	quest sent to pico
+ TNG/pico/TPC/PONG - pong as response to the ping

Group topics also exist in the structure under.

GRP/<Group>/TPC/ - Topics to talk to group of devices

Examle:
GRP/ALL/TPC/PING - ping topic that all IoT devices listen for.


