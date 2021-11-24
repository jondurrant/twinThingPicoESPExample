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


//MQTTConnection mqttConn;
//MQTTConnTask mqttTask;
//MQTTRouterPing mqttRouter;
MQTTRouterTwin mqttRouter;
MQTTAgent mqttAgent(512, 512);


char mqttTarget[] = MQTTHOST;
char mqttUser[] = MQTTUSER;
char mqttPwd[] = MQTTPASSWD;
lwesp_port_t mqttPort = MQTTPORT;

StateExample state;
ExampleAgentObserver agentObs;




void startMQTT(){

	mqttAgent.credentials(mqttUser, mqttPwd);
	mqttAgent.setObserver(&agentObs);
	mqttRouter.init(mqttAgent.getId(), &mqttAgent, &state);
	mqttAgent.setRouter(&mqttRouter);
	mqttAgent.start(tskIDLE_PRIORITY+1);
	mqttAgent.connect(mqttTarget, mqttPort, true);


	/*
	mqttAgent.credentials(mqttUser, mqttPwd);
	mqttRouter.init(mqttAgent.getId(), &mqttAgent);
	mqttAgent.setRouter(&mqttRouter);
	mqttAgent.start(tskIDLE_PRIORITY+1);
	mqttAgent.connect(mqttTarget, mqttPort);


	mqttTask.credentials(mqttUser, mqttPwd);
	mqttTask.setReconnect(true);
	mqttRouter.init(mqttTask.getId(), &mqttTask);
	mqttTask.setRouter(&mqttRouter);

	mqttTask.start(tskIDLE_PRIORITY);
	mqttTask.connect(mqttTarget, mqttPort);
	*/
}






lwespr_t lwesp_callback_func(struct lwesp_evt *evt){
	printf("Init Callback\n");
	switch(evt->type){
	case LWESP_EVT_INIT_FINISH:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_RESET_DETECTED:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_RESET:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_RESTORE:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_CMD_TIMEOUT:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_DEVICE_PRESENT:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_AT_VERSION_NOT_SUPPORTED:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_CONN_RECV:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_CONN_SEND:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_CONN_ACTIVE:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_CONN_ERROR:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_CONN_CLOSE:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_CONN_POLL:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_SERVER:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_WIFI_CONNECTED:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_WIFI_GOT_IP:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_WIFI_DISCONNECTED:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_WIFI_IP_ACQUIRED:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_STA_LIST_AP:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_STA_JOIN_AP:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_STA_INFO_AP:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_AP_CONNECTED_STA:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_AP_DISCONNECTED_STA:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_AP_IP_STA:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	case LWESP_EVT_DNS_HOSTBYNAME:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	/*
	case LWESP_EVT_PING:{
		LogDebug(("Callback LWESP_EVT_INIT_FINISH"));
		break;
	}
	*/
	default:{
		LogDebug(("Callback Other %d", evt->type));
		break;
	}
	}



	return lwespOK;

}

void ip2str(char *str, lwesp_ip_t *ip){
	sprintf(str, "%d:%d:%d:%d",
		(int)ip->addr.ip4.addr[0], (int)ip->addr.ip4.addr[1],
		(int)ip->addr.ip4.addr[2], (int)ip->addr.ip4.addr[3]);
}

void lwesp_cb(lwespr_t evt, void* pv){
	printf("Callbackr returned %d\n", evt);

	if (evt == lwespOK){
		lwesp_ip_t *ip = (lwesp_ip_t *) pv;
		char ipStr[20];
		ip2str(ipStr, ip);
		printf("IP is %s\n", ipStr);
	}


}


void
init_thread_old(void* pvParameters) {
	lwespr_t eres;
	char ipStr[16];

    /* Initialize ESP with default callback function */
    printf("Initializing LwESP\r\n");
    if (lwesp_init(lwesp_callback_func, 1) != lwespOK) {
        printf("Cannot initialize LwESP!\r\n");

    } else {
        printf("LwESP initialized!\r\n");


        if (lwesp_sta_has_ip()) {
        	printf("Already connected\r\n");
        	lwesp_ip_t ip;
			uint8_t is_dhcp;

			lwesp_sta_copy_ip(&ip, NULL, NULL, &is_dhcp);
			ip2str(ipStr, &ip);
			printf("Station IP address: %s\r\n", ipStr);
			printf("; Is DHCP: %d\r\n", (int)is_dhcp);


        } else {
        	char sid[] = SID;
        	char passwd[] = PASSWD;
        	if (lwesp_sta_join(sid, passwd, NULL, NULL, NULL, 1) == lwespOK) {
				 lwesp_ip_t ip;
				 uint8_t is_dhcp;

				 printf("Connected to %s network!\r\n", sid);
				 lwesp_sta_copy_ip(&ip, NULL, NULL, &is_dhcp);
				 ip2str(ipStr, &ip);
				 printf("Station IP address: %s\r\n", ipStr);
				 printf("; Is DHCP: %d\r\n", (int)is_dhcp);

			 } else {
				 printf("Connection error: %d\r\n", (int)eres);
				 return;
			 }
        }
        startMQTT();

        lwespr_t smartRes;
        //smartRes = lwesp_smart_set_config(1, NULL,  NULL, 1);
        smartRes = lwesp_hostname_set("LS1", NULL, NULL, 1);
        char host[20];
        smartRes = lwesp_hostname_get(host, 20, NULL, NULL, 1);
        switch(smartRes){
        case lwespOK:{
        	printf("Hostname is %s\n", host);
        	break;
        }
        case lwespERR: {
        	printf("Hostname general error\n");
        	break;
        }
        default: {
        	printf("Hostname failed %d\n", smartRes);
        }
        }

        lwesp_ip_t ip;
        smartRes = lwesp_dns_gethostbyname("pudev.local.jondurrant.com", &ip, lwesp_cb, &ip, 1);
        switch(smartRes){
		   case lwespOK:{
			printf("dns ok \n");
			ip2str(ipStr, &ip);
		    printf("IP address: %s\r\n", ipStr);
			break;
		   }
		   case lwespERR: {
			printf("dns general error\n");
			break;
		   }
		   default: {
			printf("dns failed %d\n", smartRes);
		   }
	    }
    }



    for (;;){
    	vTaskDelay(5000);

    }
}

void
init_thread(void* pvParameters) {
	//TwinTask xTwin;
	if (WifiHelper::connectToAp(SID, PASSWD)){
		mqttAgent.credentials(mqttUser, mqttPwd);
		mqttAgent.setObserver(&agentObs);
		mqttRouter.init(mqttAgent.getId(), &mqttAgent, &state);

		mqttAgent.setRouter(&mqttRouter);
		mqttAgent.connect(mqttTarget, mqttPort, true);

		mqttAgent.start(tskIDLE_PRIORITY+1);
		startMQTT();
	}

    for (;;){
    	vTaskDelay(5000);

    }
}



int main() {

	stdio_init_all();

	sleep_ms(3000);
	printf("******GO******\n");


	/**
	WifiAgent wifi(SID, PASSWD);
	wifi.start();
	startMQTT();
	**/


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
