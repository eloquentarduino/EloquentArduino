#include <M5StickC.h>
#include <WiFi.h>
#include <eDataStructures.h>
#include "model.h"

#define MAX_NETWORKS 10

using namespace Eloquent::DataStructures;


double features[MAX_NETWORKS];
Array<String, MAX_NETWORKS> knownNetworks("");


void scan();
void printFeatures();
void classify();


/**
 * 
 */
void setup() {
	Serial.begin(115200);
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();

	knownNetworks.push("RETE_WIRLESS_ EXT");
	knownNetworks.push("Salerno");
	knownNetworks.push("Infostrada-2.4GHz-***");
	knownNetworks.push("Infostrada-2.4GHz-***");
	knownNetworks.push("Infostrada-2.4GHz-***");
	knownNetworks.push("WOW FI - FASTWEB");
	knownNetworks.push("FASTWEB-***");
	knownNetworks.push("TP-Link_HOME_ext");
}

/**
 * 
 */
void loop() {
	scan();
	printFeatures();
	//classify();
	delay(3000);
}

/**
 * Convert networks' RSSIs to feature vector
 */
void scan() {
    int numNetworks = WiFi.scanNetworks();

    // assign RSSI to feature vector
    for (int i = 0; i < numNetworks; i++) {
        String ssid = WiFi.SSID(i);
        uint16_t networkIndex = knownNetworks.indexOf(ssid);

        if (!isnan(networkIndex))
            features[networkIndex] = WiFi.RSSI(i);
    }
}

/**
 *
 */
void printFeatures() {
    for (int i = 0; i < MAX_NETWORKS; i++) {
        Serial.print(features[i]);
        Serial.print(i == MAX_NETWORKS - 1 ? '\n' : '\t');
    }
}

/**
 *
 */
void classify() {
    Serial.print("You are in ");
    Serial.println(classIdxToName(predict(features)));
}