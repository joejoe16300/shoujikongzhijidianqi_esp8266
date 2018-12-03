// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       shoujikongzhijidianqi_esp8266.ino
    Created:	2018/11/21 19:52:33
    Author:     ndun-PC\ndun
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
/*��ƪ��8266��ΪTCPcleint�������ֻ�������tcpServer��������һ���̵���*/

#include <ESP8266WiFi.h> 
  
#define relayPin 2               //�̵���������8266��GPIO2��
const char *ssid = "Xiaomi";//�������ҵ�wifi����ʹ��ʱ�޸�Ϊ��Ҫ���ӵ�wifi ssid
const char *password = "12345687";//��Ҫ���ӵ�wifi����
const char *host = "192.168.0.60";//�޸�Ϊ�ֻ��ĵ�tcpServer����˵�IP��ַ�����ֻ���·�����ϵ�ip
WiFiClient client;
const int tcpPort = 8366;//�޸�Ϊ�㽨����Server����˵Ķ˿ں�

void setup()
{
	pinMode(relayPin, OUTPUT);
	Serial.begin(115200);
	delay(100);
	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");//д������ʾ
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED)//WiFi.status() �����������wifi����״̬������wifi����״̬
										 //����Ͳ�һһ׸�������ص������ˣ�����Ȥ�ĵ�ESP8266WiFi.cpp�в鿴
	{
		delay(500);
		Serial.print(".");
	}//���û����ͨ�򴮿ڷ���.....

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());//WiFi.localIP()����8266��õ�ip��ַ
}


void loop()
{
	while (client.connected())//���������ӵ��쳣����
	{
		if (!client.connect(host, tcpPort))
		{
			Serial.println("connection....");
			//client.stop();
			delay(500);
		}
	}
	while (client.available())//available()ͬARDUINO����������
	{
		char val = client.read();//read()ͬarduino
		if (val == 'a') {//pc�˷���a��b������
			digitalWrite(relayPin, LOW);
		}
		if (val == 'b')
		{
			digitalWrite(relayPin, HIGH);
		}
	}
}
