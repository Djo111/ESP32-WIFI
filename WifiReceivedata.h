    #include <WiFi.h>
 
   
const char* ssid = "Mi 9 Lite";
const char* password = "12345678@";


WiFiServer server(80);

double Kp = 0.0;
double Kd = 0.0;
double Ki = 0.0;
char str[20];
int16_t p;

void setupwificalib(){
//      if (!SPIFFS.begin()) {
//     Serial.println("Failed to mount file system");
//     return;
//   }
//   file = SPIFFS.open("/text.txt",FILE_WRITE);

Serial.begin(9600);
WiFi.begin(ssid, password);
// digitalWrite(16,0);
while (WiFi.status() != WL_CONNECTED)
{
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  //digitalWrite(16,1);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server started");
}



void mainwificalib(double& kp, double& ki, double& kd , int16_t pitch,int16_t roll){
     

 // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");

    // Wait for some data to arrive
   

    // Read the data
    String data = client.readStringUntil('\r');
    Serial.println("Received data: " + data);

    // Parse the data
    if (data.indexOf("kp_inc0") != -1) {
      Kp += 0.01;
    } else if (data.indexOf("kp_dec0") != -1) {
      Kp -= 0.01;
    } else if (data.indexOf("kp_inc1") != -1) {
      Kp += 0.1;
    } else if (data.indexOf("kp_dec1") != -1) {
      Kp -= 0.1;
    }else if (data.indexOf("kp_inc2") != -1) {
      Kp += 1;
    } else if (data.indexOf("kp_dec2") != -1) {
      Kp -= 1;
    }

    else if (data.indexOf("kd_inc0") != -1) {
      Kd += 0.001;
    } else if (data.indexOf("kd_dec0") != -1) {
      Kd -= 0.001;
    } else if (data.indexOf("kd_inc1") != -1) {
      Kd += 0.01;
    } else if (data.indexOf("kd_dec1") != -1) {
      Kd -= 0.01;
    } else if (data.indexOf("kd_inc2") != -1) {
      Kd += 1;
    }else if (data.indexOf("kd_dec2") != -1) {
      Kd -= 1;
    }
    
     else if (data.indexOf("ki_inc0") != -1) {
      Ki += 0.01;
    }else if (data.indexOf("ki_dec0") != -1) {
      Ki -= 0.01;
    } else if (data.indexOf("ki_inc1") != -1) {
      Ki += 0.1;
    }else if (data.indexOf("ki_dec1") != -1) {
      Ki -= 0.1;
    }else if (data.indexOf("ki_inc2") != -1) {
      Ki += 1;
    }else if (data.indexOf("ki_dec2") != -1) {
      Ki -= 1;
    }

    // Send a response
    p = pitch;
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<html><body>");
    client.println("<h1>Variables updated:</h1>");
    client.println("<form>");
    client.print("<p>kp = "); client.print(Kp); client.println("</p>");
    client.print("<button name=\"kp_inc0\" value=\"true\">+0.01</button>");
    client.print("<button name=\"kp_dec0\" value=\"true\">-0.01</button>");
    client.println("<br>");
    client.print("<button name=\"kp_inc1\" value=\"true\">+0.1</button>");
    client.print("<button name=\"kp_dec1\" value=\"true\">-0.1</button>");
    client.println("<br>");
    client.print("<button name=\"kp_inc2\" value=\"true\">+1</button>");
    client.print("<button name=\"kp_dec2\" value=\"true\">-1</button>");
    client.println("<br>");
    dtostrf(Kd, 1, 3, str);
    client.print("<p>kd = "); client.print(str); client.println("</p>");
    client.print("<button name=\"kd_inc0\" value=\"true\">+0.001</button>");
    client.print("<button name=\"kd_dec0\" value=\"true\">-0.001</button>");
    client.println("<br>");
    client.print("<button name=\"kd_inc1\" value=\"true\">+0.01</button>");
    client.print("<button name=\"kd_dec1\" value=\"true\">-0.01</button>");
    client.println("<br>");
    client.print("<button name=\"kd_inc2\" value=\"true\">+1</button>");
    client.print("<button name=\"kd_dec2\" value=\"true\">-1</button>");
    client.println("<br>");
    
    client.print("<p>ki = "); client.print(Ki); client.println("</p>");
    client.print("<button name=\"ki_inc0\" value=\"true\">+0.01</button>");
    client.print("<button name=\"ki_dec0\" value=\"true\">-0.01</button>");
    client.println("<br>");
    client.print("<button name=\"ki_inc1\" value=\"true\">+0.1</button>");
    client.print("<button name=\"ki_dec1\" value=\"true\">-0.1</button>");
    client.println("<br>");
    client.print("<button name=\"ki_inc2\" value=\"true\">+1</button>");
    client.print("<button name=\"ki_dec2\" value=\"true\">-1</button>");
    client.println("<br>");
    client.print("<h1>Pitch: </h1>");
    client.print(pitch);
    client.println("<br>");
    client.print("<h1>Roll: </h1>");
    client.print(roll);
    // client.print("<script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>");
    // client.print("<script>var chartData = {labels:[], datasets:[{label:'Sensor Value',data:[]}],};");
    // client.print("var chartOptions = {responsive:true,scales:{yAxes:[{ticks:{beginAtZero:true}}]},};");
    // client.print("var lineChart = new Chart(document.getElementById('chart').getContext('2d'),{type:'line',data:chartData,options:chartOptions});");
    // client.print("setInterval(function() {updateChart();}, 1000);");
    // client.print("function updateChart() {chartData.labels.push(new Date().toLocaleTimeString());chartData.datasets[0].data.push(" + String(pitch) + ");lineChart.update();}");
    // client.print("</script></head><body><h1>Real-time Chart</h1><canvas id=\"chart\" width=\"800\" height=\"400\"></canvas></body></html>");

    client.println("</form>");
    client.println("</body></html>");

    // Disconnect the client
    client.stop();
    Serial.println("Client disconnected");
    kp = Kp;
    kd = Kd;
    ki = Ki;
    
  }
}
