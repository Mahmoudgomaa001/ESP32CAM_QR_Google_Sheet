/* ------------------------------------------------------------------------
 * Created by: Tauseef Ahmad
 * Created on: 10 March, 2023
 *  
 * Tutorial: https://youtu.be/aNjkNmHRx4o
 * ------------------------------------------------------------------------
 * Download Resources
 * ------------------------------------------------------------------------
 * Preferences--> Aditional boards Manager URLs : 
 * For ESP8266 and NodeMCU - Board Version 2.6.3
 * http://arduino.esp8266.com/stable/package_esp8266com_index.json
 * ------------------------------------------------------------------------
 * HTTPS Redirect Library:
 * https://github.com/jbuszkie/HTTPSRedirect
 * Example Arduino/ESP8266 code to upload data to Google Sheets
 * Follow setup instructions found here:
 * https://github.com/StorageB/Google-Sheets-Logging
 * ------------------------------------------------------------------------*/


/****************************************************************************************************
 * setup Function
****************************************************************************************************/
void attensetup() {
  //----------------------------------------------------------
  // Serial.begin(9600);
  delay(10);
  Serial.println('\n');
  //----------------------------------------------------------
  // SPI.begin();
  //----------------------------------------------------------
  // //initialize lcd screen
  // lcd.init();
  // // turn on the backlight
  // lcd.backlight();
  // lcd.clear();
  // lcd.setCursor(0, 0);  //col=0 row=0
  // lcd.print("Connecting to");
  // lcd.setCursor(0, 1);  //col=0 row=0
  // lcd.print("WiFi...");
  //----------------------------------------------------------
  // Connect to WiFi
  // WiFi.begin(ssid, password);
  // Serial.print("Connecting to ");
  // Serial.print(ssid);
  // Serial.println(" ...");

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.print(".");
  // }
  // Serial.println('\n');
  // Serial.println("WiFi Connected!");
  // //Serial.print("IP address:\t");
  // Serial.println(WiFi.localIP());
  //----------------------------------------------------------
  // Use HTTPSRedirect class to create a new TLS connection
  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");
  //----------------------------------------------------------
  // lcd.clear();
  // lcd.setCursor(0, 0);  //col=0 row=0
  // lcd.print("Connecting to");
  // lcd.setCursor(0, 1);  //col=0 row=0
  // lcd.print("Google ");
  delay(5000);
  //----------------------------------------------------------
  Serial.print("Connecting to ");
  Serial.println(host);
  //----------------------------------------------------------
  // Try to connect for a maximum of 5 times
  bool flag = false;
  for (int i = 0; i < 5; i++) {
    int retval = client->connect(host, httpsPort);
    //*************************************************
    if (retval == 1) {
      flag = true;
      String msg = "Connected. OK";
      Serial.println(msg);
      // lcd.clear();
      // lcd.setCursor(0, 0);  //col=0 row=0
      // lcd.print(msg);
      delay(2000);
      break;
    }
    //*************************************************
    else
      Serial.println("Connection failed. Retrying...");
    //*************************************************
  }
  //----------------------------------------------------------
  if (!flag) {
    //____________________________________________
    // lcd.clear();
    // lcd.setCursor(0, 0);  //col=0 row=0
    // lcd.print("Connection fail");
    //____________________________________________
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    delay(5000);
    return;
    //____________________________________________
  }
  //----------------------------------------------------------
  delete client;     // delete HTTPSRedirect object
  client = nullptr;  // delete HTTPSRedirect object
  //----------------------------------------------------------
}

/****************************************************************************************************
 * loop Function
****************************************************************************************************/
void attenloop() {
  Serial.println("[TEST] loop() starts");
  //----------------------------------------------------------------
  static bool flag = false;
  if (!flag) {
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();
    flag = true;
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");
  }
  if (client != nullptr) {
    //when below if condition is TRUE then it takes more time then usual, It means the device
    //is disconnected from the google sheet server and it takes time to connect again
    //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
    if (!client->connected()) {
      int retval = client->connect(host, httpsPort);
      if (retval != 1) {
        Serial.println("Disconnected. Retrying...");
        // lcd.clear();
        // lcd.setCursor(0, 0);  //col=0 row=0
        // lcd.print("Disconnected.");
        // lcd.setCursor(0, 1);  //col=0 row=0
        // lcd.print("Retrying...");
        return;  //Reset the loop
      }
    }
    //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  } else {
    Serial.println("Error creating client object!");
    Serial.println("else");
  }
  //----------------------------------------------------------------
  // lcd.clear();
  // lcd.setCursor(0, 0);  //col=0 row=0
  // lcd.print("Scan your Tag");
  //Serial.println("[TEST] Scan Your Tag");
  /* Initialize MFRC522 Module */
  // mfrc522.PCD_Init();
  /* Look for new cards */
  /* Reset the loop if no new card is present on RC522 Reader */
  // if ( ! mfrc522.PICC_IsNewCardPresent()) {return;}
  /* Select one of the cards */
  // if ( ! mfrc522.PICC_ReadCardSerial()) {return;}
  /* Read data from the same block */
  Serial.println();
  Serial.println(F("Reading last data from RFID..."));
  //----------------------------------------------------------------
  String values = "", data;





  //creating payload - method 1
  //----------------------------------------------------------------
  // ReadDataFromBlock(blocks[0], readBlockData); //student id
  // data = String((char*)readBlockData); data.trim();
  student_id = strs[0];
  strs[0] = "";
  //----------------------------------------------------------------
  // ReadDataFromBlock(blocks[1], readBlockData); //first name
  // data = String((char*)readBlockData); data.trim();
  first_name = strs[1];
  strs[1] = "";
  //----------------------------------------------------------------
  // ReadDataFromBlock(blocks[2], readBlockData); //last name
  // data = String((char*)readBlockData); data.trim();
  last_name = strs[2];
  strs[2] = "";
  //----------------------------------------------------------------
  // ReadDataFromBlock(blocks[3], readBlockData); //phone number
  // data = String((char*)readBlockData); data.trim();
  phone_number = strs[3];
  strs[3] = "";
  //----------------------------------------------------------------
  // ReadDataFromBlock(blocks[4], readBlockData); //address
  // data = String((char*)readBlockData); data.trim();
  address = strs[4];
  strs[4] = "";
  //----------------------------------------------------------------
  values = "\"" + student_id + ",";
  values += first_name + ",";
  values += last_name + ",";
  values += phone_number + ",";
  values += address + "\"}";
  //----------------------------------------------------------------*/



  /*
  //creating payload - method 1
  //----------------------------------------------------------------
  ReadDataFromBlock(blocks[0], readBlockData); //student id
  data = String((char*)readBlockData); data.trim();
  student_id = data;
  //----------------------------------------------------------------
  ReadDataFromBlock(blocks[1], readBlockData); //first name
  data = String((char*)readBlockData); data.trim();
  first_name = data;
  //----------------------------------------------------------------
  ReadDataFromBlock(blocks[2], readBlockData); //last name
  data = String((char*)readBlockData); data.trim();
  last_name = data;
  //----------------------------------------------------------------
  ReadDataFromBlock(blocks[3], readBlockData); //phone number
  data = String((char*)readBlockData); data.trim();
  phone_number = data;
  //----------------------------------------------------------------
  ReadDataFromBlock(blocks[4], readBlockData); //address
  data = String((char*)readBlockData); data.trim();
  address = data; data = "";
  //----------------------------------------------------------------
  values = "\"" + student_id + ",";
  values += first_name + ",";
  values += last_name + ",";
  values += phone_number + ",";
  values += address + "\"}";
  //----------------------------------------------------------------*/
  // //creating payload - method 2 - More efficient
  // for (byte i = 0; i < total_blocks; i++) {
  //   // ReadDataFromBlock(blocks[i], readBlockData);
  //   //*************************************************
  //   if (i == 0) {
  //     data = String((char*)readBlockData);
  //     data.trim();
  //     student_id = data;
  //     values = "\"" + data + ",";
  //   }
  //   //*************************************************
  //   /*else if(i == total_blocks-1){
  //     data = String((char*)readBlockData);
  //     data.trim();
  //     values += data + "\"}";
  //   }*/
  //   //*************************************************
  //   else {
  //     data = String((char*)readBlockData);
  //     data.trim();
  //     values += data + ",";
  //   }
  // }
  // values += gate_number + "\"}";
  //----------------------------------------------------------------
  // Create json object string to send to Google Sheets
  // values = "\"" + value0 + "," + value1 + "," + value2 + "\"}"
  payload = payload_base + values;
  //----------------------------------------------------------------
  // lcd.clear();
  // lcd.setCursor(0, 0);  //col=0 row=0
  // lcd.print("Publishing Data");
  // lcd.setCursor(0, 1);  //col=0 row=0
  // lcd.print("Please Wait...");
  //----------------------------------------------------------------
  // Publish data to Google Sheets
  Serial.println("Publishing data...");
  Serial.println(payload);
  if (client->POST(url, host, payload)) {
    // do stuff here if publish was successful
    Serial.println("[OK] Data published.");
    // lcd.clear();
    // lcd.setCursor(0, 0);  //col=0 row=0
    // lcd.print("Student ID: " + student_id);
    // lcd.setCursor(0, 1);  //col=0 row=0
    // lcd.print("Thanks");
  }
  //----------------------------------------------------------------
  else {
    // do stuff here if publish was not successful
    Serial.println("Error while connecting");
    // lcd.clear();
    // lcd.setCursor(0, 0);  //col=0 row=0
    // lcd.print("Failed.");
    // lcd.setCursor(0, 1);  //col=0 row=0
    // lcd.print("Try Again");
  }
  //----------------------------------------------------------------
  // a delay of several seconds is required before publishing again
  Serial.println("[TEST] delay(5000)");
  delay(5000);
}


/****************************************************************************************************
 * 
****************************************************************************************************/
/****************************************************************************************************
 * ReadDataFromBlock() function
 ****************************************************************************************************/
// void ReadDataFromBlock(int blockNum, byte readBlockData[])
// {
//   //----------------------------------------------------------------------------
//   /* Prepare the ksy for authentication */
//   /* All keys are set to FFFFFFFFFFFFh at chip delivery from the factory */
//   for (byte i = 0; i < 6; i++) {
//     key.keyByte[i] = 0xFF;
//   }
//   //----------------------------------------------------------------------------
//   /* Authenticating the desired data block for Read access using Key A */
//   status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));
//   //----------------------------------------------------------------------------s
//   if (status != MFRC522::STATUS_OK){
//      Serial.print("Authentication failed for Read: ");
//      Serial.println(mfrc522.GetStatusCodeName(status));
//      return;
//   }
//   //----------------------------------------------------------------------------
//   else {
//     Serial.println("Authentication success");
//   }
//   //----------------------------------------------------------------------------
//   /* Reading data from the Block */
//   status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);
//   if (status != MFRC522::STATUS_OK) {
//     Serial.print("Reading failed: ");
//     Serial.println(mfrc522.GetStatusCodeName(status));
//     return;
//   }
//   //----------------------------------------------------------------------------
//   else {
//     readBlockData[16] = ' ';
//     readBlockData[17] = ' ';
//     Serial.println("Block was read successfully");
//   }
//   //----------------------------------------------------------------------------
// }



// String  str = "A1N c2 t120 d4 t0 b5 t0 a2 t368 e2 t452 1c t0 e1 t600";


void strSplit(String str, char separator) {
  int StringCount = 0;
  // Split the string into substrings
  while (str.length() > 0) {
    int index = str.indexOf(separator);
    if (index == -1)  // No space found
    {
      strs[StringCount++] = str;
      break;
    } else {
      strs[StringCount++] = str.substring(0, index);
      str = str.substring(index + 1);
    }
  }

  // Show the resulting substrings
  for (int i = 0; i < StringCount; i++) {
    Serial.print(i);
    Serial.print(": \"");
    Serial.print(strs[i]);
    Serial.println("\"");
  }
}

//
