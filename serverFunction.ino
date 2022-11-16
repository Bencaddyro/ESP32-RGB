
void initSPIFFS(){
  if (!SPIFFS.begin())
  {
    Serial.println("Erreur SPIFFS...");
    exit(0);
  }
  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  while (file)
  {
    Serial.print("File: ");
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }
}

void initWifi(){
  WiFi.begin(ssid, password);
  Serial.print("Tentative de connexion...");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\n");
  Serial.println("Connexion etablie!");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());  
}

void initAccessPoint(){  
  Serial.println("Creation du point d'acces...");
  WiFi.softAP(a_ssid, a_password);
  
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.softAPIP());
}

void initServer(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/w3.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/w3.css", "text/css");
  });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/script.js", "text/javascript");
  });
  
  server.on("/iro.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/iro.min.js", "text/javascript");
  });

  server.on("/jquery.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/jquery.js", "text/javascript");
  });

  server.on("/on", HTTP_POST, [](AsyncWebServerRequest *request) {
    powerSwitch = 1;
    request->send(204);
  });

  server.on("/off", HTTP_POST, [](AsyncWebServerRequest *request) {
    powerSwitch = 0;
    toShutdown = 1;
    request->send(204);
  });

  server.on("/setPattern", HTTP_POST, [](AsyncWebServerRequest *request) {
    if(request->hasParam("pattern", true)) {
      String message;
      message = request->getParam("pattern", true)->value();
      patternStep = 0;
      patternCurrent = message.toInt();
      strip.fill(strip.Color(0, 0, 0));
    }
    request->send(204);
  });

  server.on("/setNumber", HTTP_POST, [](AsyncWebServerRequest *request) {
    if(request->hasParam("number", true)) {
      String message = request->getParam("number", true)->value();
      pixelNumber = message.toInt();
      strip.updateLength(pixelNumber);
    }
    request->send(204);
  });
  
  server.on("/getParameters", HTTP_POST, [](AsyncWebServerRequest *request) {
    int patternRequest = 0;
    if(request->hasParam("pattern", true)) {
      String message = request->getParam("pattern", true)->value();
      patternRequest = message.toInt();      
    }
    String parameters = "[";
    parameters += patternRequest;
    parameters += ", ";
    parameters += pixelNumber;
    for(int i=0 ; i<PARAM_SIZE ; i++){
      parameters += ", ";
      parameters += arrayParameters[patternRequest][i];
    }
    parameters += "]";
    request->send(200, "application/json", parameters);
  });

  server.on("/setParameters", HTTP_POST, [](AsyncWebServerRequest *request) {
    int patternRequest = 0;
    Serial.println("Set param for pattern");
    if(request->hasParam("pattern", true)) {
      String message = request->getParam("pattern", true)->value();
      patternRequest = message.toInt();
    }
    Serial.println(patternRequest);
    if(request->hasParam("0", true)) {
      String message = request->getParam("0", true)->value();
      uint32_t param = message.toInt();
      Serial.println("Param 0");
      Serial.println(param);
      arrayParameters[patternRequest][0] = param;
    }
    if(request->hasParam("1", true)) {
      String message = request->getParam("1", true)->value();
      uint32_t param = message.toInt();
      Serial.println("Param 1");
      Serial.println(param);
      arrayParameters[patternRequest][1] = param;
    }
    if(request->hasParam("2", true)) {
      String message = request->getParam("2", true)->value();
      uint32_t param = message.toInt();
      Serial.println("Param 2");
      Serial.println(param);
      arrayParameters[patternRequest][2] = param;
    }
    if(request->hasParam("3", true)) {
      String message = request->getParam("3", true)->value();
      uint32_t param = message.toInt();
      Serial.println("Param 3");
      Serial.println(param);
      arrayParameters[patternRequest][3] = param;
    }
    if(request->hasParam("4", true)) {
      String message = request->getParam("4", true)->value();
      uint32_t param = message.toInt();
      Serial.println("Param 4");
      Serial.println(param);
      arrayParameters[patternRequest][4] = param;
    }
    request->send(204);
  });

  
  server.begin();
  Serial.println("Serveur actif!");
}
