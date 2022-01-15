#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include <array>
#include "lwesp/lwesp.h"

#include "lwesp/apps/lwesp_mqtt_client_api.h"




//Local include file not in git repository, defining the credentials
#include "Credentials.env"
#ifndef SID
#define SID "sid"
#define PASSWD "passwd"
#endif
#ifndef MQTTHOST
#define MQTTHOST "MQTTSERVER"
#define MQTTPORT 1883
#define MQTTUSER "USER"
#define MQTTPASSWD "PASSWD"
#endif


#include "MQTTAgent.h"
#include "MQTTRouterPing.h"
#include "MQTTRouterTwin.h"

#include <WifiHelper.h>

#include "StateExample.h"
#include "ExampleAgentObserver.h"




void
init_thread(void* pvParameters) {
	char mqttTarget[] = MQTTHOST;
	lwesp_port_t mqttPort = MQTTPORT;
	char mqttUser[] = MQTTUSER;
	char mqttPwd[] = MQTTPASSWD;

	MQTTRouterTwin mqttRouter;
	StateExample state;
	ExampleAgentObserver agentObs;

	MQTTAgent mqttAgent(512, 512);
	TwinTask xTwin;
	MQTTPingTask xPing;

	//Connect to WiFi
	if (WifiHelper::connectToAp(SID, PASSWD)){
		char ips[16];
		char macs[15];
		WifiHelper::getIPAddressStr(ips);
		printf("WIFI IP %s\n", ips);
		if (WifiHelper::getMACAddressStr(macs)){
			printf("MAC %s\n", macs);
		} else {
			printf("MAC NOT AVAILABLE\n");
		}
		WifiHelper::syncRTCwithSNTP();


		//Set up the credentials so we have an ID for our thing
		mqttAgent.credentials(mqttUser, mqttPwd);
		mqttRouter.init(mqttAgent.getId(), &mqttAgent);

		//Twin agent to manage the state
		xTwin.setStateObject(&state);
		xTwin.setMQTTInterface(&mqttAgent);
		xTwin.start(tskIDLE_PRIORITY+1);

		//Start up a Ping agent to mange ping requests
		xPing.setInterface(&mqttAgent);
		xPing.start(tskIDLE_PRIORITY+1);

		//Give the router the twin and ping agents
		mqttRouter.setTwin(&xTwin);
		mqttRouter.setPingTask(&xPing);

		//Setup and start the mqttAgent
		mqttAgent.setObserver(&agentObs);
		mqttAgent.setRouter(&mqttRouter);
		mqttAgent.connect(mqttTarget, mqttPort, true, true);
		mqttAgent.start(tskIDLE_PRIORITY+1);

	}

    for (;;){
    	vTaskDelay(5000);

    }
}



int main() {

	stdio_init_all();

	sleep_ms(3000);
	printf("******GO******\n");


    BaseType_t atReturned;
	TaskHandle_t atHandle = NULL;

	atReturned = xTaskCreate(
					init_thread,
					"Init task",
					512,
					( void * ) 1,
					tskIDLE_PRIORITY+1,
					&atHandle );




    vTaskStartScheduler();
    while(1)
    {
        configASSERT(0);    /* We should never get here */
    }

}
