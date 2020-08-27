# End Node 

All end nodes in this version are based on ESP8266 in the future releases the functionality will be availible for ESP32 to.

## Terminology 
- **End Node** - A microcontroller with wifi and installed Agrobot firmware with it's own behavior.
- **End Node behavior** - The end node behavior is strongly dependent on the attached sensor set or hardware on it and installed firmware. In fact the installed firmware defines the **behavior** of the end node The behaviors are:
  - **Unified controller** - in this case firmware allows to atach custom non complex and non specific hardware that can be readed or controled wit simple software+hardware primitives like:
    - **Digital Read/Write**
    - **Analog Read**
    - **Compatability wit I2C, SPI, etc will be added in future releases**
  
    The data manipulation and hardware control in **unified controller** can be precessed with:  
    
    - **PWM** - read or write PWM with previously set parameters  
    - **Time Series** - execute action on timer expiration 
    - **On event** - execute action on event received from `MQTT` or on specified pin
  
  
  - **Water Level** -  in this case 
  - **Llight Control** - in this case 
  - **Nutrition Control** - in this case 
- **MQTT Subscriber** - the MQTT subscriber basicaly is data provider or receiver. One end node can be subscriber for multiplio input and output topics.
- **Data provider/receiver** - is an software shell for subscribtion on `MQTT` topics and is not strongly dependent to hardware data provider. The data can be emulated.
- **MQTT topic** - is unique for each endnode path for publishing an receiving data. The topic format looks like:
  ``` <topic name>/<end node MAC address>/<data reprovider or subscriber>/attributes```
  
  The topic names for one end node are:
  - **Config Topic** - `config`
  - **Identification Topic** - `whoami`
  - **Error messaging** - `/err/<end node MAC>/<err topic name>`
  - 

## Connection algorithm


1) On the first end node boot the end node enters to **Access Point Mode**. The user needs to connect to this Access Point with a smartphone for example and enter the:
   - **Wifi network credentials**
   - **Custom indentifer for end node** (optional)
   - **Mqtt configs like username and pass**
   - **Mqtt settings like port etc if he uses custom configs** (optional)
   - **Custom IP of broker** (optional)

    After entering this data and succsessful connection to the provided Wifi network the end node stops the **Access Point** and **Captive Portal** and starts to try to connect to the `MQTT` broker. 

    By default the **end node** is trying to access the `MQTT` broker on the `Default gateway` IP address. If several tryings to connect to the broker are fail the **end node** enters to the **Access Point** mode. 

    The end node will have the functional button to reset settings and enter to **Access Point** mode. Also this can be done from the `MQTT` broker by sending a specific command to `Config topic`.

2) After succsessfuly connection to the `MQTT` broker the end node publish it's own **behavior**, **configuration satatus** and **identification data** to the **Identification topic**. The data published to Identification topic is `JSON` formated telemetry info of the end node. 

```JSON 
{
    "mcuType": "<behavior>",
    "title": "<custom title>",
    "macAddr": "<mac address>",
    "isConfigured": false,
    "signalStreigth": "-35dbm",
    "batteryLevel": -1,
    "selfCheck":false,

}
```
3) If everything is OK the `MQTT` broker creates an unique topic paths for the connected end node `/<topic name>/<end node MAC address>/etc..` Each behavior has its own themes except the default ones 

4) If the previous step is succsessful the **end node** automatically subscribes to default and behavior specific topics for income or outcome configs and data. 

5) After the end node is connected and is configured the `MQTT` broker sends the new configuration to the `/config/<mac address>/`. If two end nodes need to comunicate to each other the topics to publish and subscribing need to be providet in config `JSON`.

```
+---------------------+                                  +---------------------+
|                     |                                  |                     |
| +-----------------+ |     endNode 1 MAC/out topic/     | +-----------------+ |
| |   Output topic  | | +------------------------------> | |   Input topic   | |
| |                 | |                                  | |                 | |
| +-----------------+ |                                  | +-----------------+ |
|                     |                                  |                     |
| +-----------------+ |     endNode 2 MAC/out topic/     | +-----------------+ |
| |   Input topic   | | <------------------------------+ | |   Output topic  | |
| |                 | |                                  | |                 | |
| +-----------------+ |                                  | +-----------------+ |
|                     |                                  |                     |
|                     |                                  |                     |
|     EndNode 1       |                                  |      EndNode 2      |
|                     |                                  |                     |
|                     |                                  |                     |
+---------------------+                                  +---------------------+

```

## Standart messages 

### Error message

```JSON
{
  "status":200,
  "errType": 1,
  "details":"error message"

}
```
as follows: 
  - **status** - http like error status
  - **errType** - type of error, the types are
    - 1 config error
    - 2 communication error
    - 3 hardware error
    - 4 internal error
    - 5 data error
  - **details**  -  error message (optional)

### Data message

```JSON
{
  "payload":23.55,
}
```

the payload is always a digit as follows:
  - 0/1 - boolean 
  - 00.00f - float
  - -1 - no data