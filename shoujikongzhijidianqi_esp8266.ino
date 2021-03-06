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
/*这篇把8266作为TCPcleint，加入手机创建的tcpServer中来控制一个继电器*/

#include <ESP8266WiFi.h> 
  
#define relayPin 2               //继电器连接在8266的GPIO2上
const char *ssid = "Xiaomi";//这里是我的wifi，你使用时修改为你要连接的wifi ssid
const char *password = "12345687";//你要连接的wifi密码
const char *host = "192.168.0.60";//修改为手机的的tcpServer服务端的IP地址，即手机在路由器上的ip
WiFiClient client;
const int tcpPort = 8366;//修改为你建立的Server服务端的端口号

void setup()
{
	pinMode(relayPin, OUTPUT);
	Serial.begin(115200);
	delay(100);
	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");//写几句提示
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED)//WiFi.status() ，这个函数是wifi连接状态，返回wifi链接状态
										 //这里就不一一赘述它返回的数据了，有兴趣的到ESP8266WiFi.cpp中查看
	{
		delay(500);
		Serial.print(".");
	}//如果没有连通向串口发送.....

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());//WiFi.localIP()返回8266获得的ip地址
}


void loop()
{
	while (client.connected())//几个非连接的异常处理
	{
		if (!client.connect(host, tcpPort))
		{
			Serial.println("connection....");
			//client.stop();
			delay(500);
		}
	}
	while (client.available())//available()同ARDUINO，不解释了
	{
		char val = client.read();//read()同arduino
		if (val == 'a') {//pc端发送a和b来控制
			digitalWrite(relayPin, LOW);
		}
		if (val == 'b')
		{
			digitalWrite(relayPin, HIGH);
		}
	}
}
