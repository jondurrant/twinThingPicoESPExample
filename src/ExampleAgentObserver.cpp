/*
 * ExampleAgentObserver.cpp
 *
 *  Created on: 23 Nov 2021
 *      Author: jondurrant
 */

#include "ExampleAgentObserver.h"
#include "MQTTConfig.h"

ExampleAgentObserver::ExampleAgentObserver() {
	// TODO Auto-generated constructor stub

}

ExampleAgentObserver::~ExampleAgentObserver() {
	// TODO Auto-generated destructor stub
}

void ExampleAgentObserver::MQTTOffline(){

	LogInfo(("Offline"));
}

void ExampleAgentObserver::MQTTOnline(){
	LogInfo(("Online"));
}

void ExampleAgentObserver::MQTTSend(){
	LogInfo(("Send"));
}

void ExampleAgentObserver::MQTTRecv(){
	LogInfo(("Recv"));
}
