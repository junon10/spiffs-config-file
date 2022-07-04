/*
    Project: spiffs_config_file
    Microcontroller: ESP32
    Compiler: Arduino GCC
    Author: Junon M.
    Version: 1.0.0
    Date: 2022/07/04
*/



//----------------------------------------------------------------------------------------
// Inclusão da lib
//----------------------------------------------------------------------------------------
#include "scf.h"
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Definição do nome de arquivo
//----------------------------------------------------------------------------------------
#define DEFAULT_CONFIG_FILENAME  "config.ini"
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Declaração do objeto
//----------------------------------------------------------------------------------------
scf ini;
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Declaração das variáveis
//----------------------------------------------------------------------------------------
String TextVariable = "";
float FloatVariable = 0.f;
int IntegerVariable = 0;
String text = "";
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  
  ini.setFileName(DEFAULT_CONFIG_FILENAME);
  
  delay(1000);
}
//----------------------------------------------------------------------------------------
void loop() {

  if (Serial.available())
  {
    text = Serial.readStringUntil('\n');

    if (text.equalsIgnoreCase("read"))
    {
      text = "";
      readConfig();
    }
    else if (text.equalsIgnoreCase("save"))
    {
      text = "";
      TextVariable = "Example Text";
      FloatVariable = 12345.67f;
      IntegerVariable = 10;
      saveConfig();
    }else{
      Serial.println("\n\nType in serial monitor: read, or save\n");
    }
    
  }


}
//----------------------------------------------------------------------------------------
void LoadSetupDefaults(){
  TextVariable = "Default Values";
  FloatVariable = -1.0f;
  IntegerVariable = -1;  
}
//----------------------------------------------------------------------------------------
void readConfig()
{
  if (!ini.fileExists())
  {
    Serial.println("Load Setup Defaults!");
    LoadSetupDefaults();
    return;
  }

  TextVariable = ini.getStr("TextVariable");
  FloatVariable = ini.getFloat("FloatVariable");
  IntegerVariable = ini.getInt("IntegerVariable");

  Serial.println("\n\nFile contents read into variables: \n");
  Serial.println("TextVariable: " + TextVariable);
  Serial.print("FloatVariable: "); Serial.println(ini.float2String(FloatVariable));
  Serial.print("IntegerVariable: "); Serial.println(IntegerVariable, DEC);
  Serial.println();

}
//----------------------------------------------------------------------------------------
void saveConfig()
{
  String S = "";

  ini.putStr("TextVariable", TextVariable);
  ini.putFloat("FloatVariable", FloatVariable);
  ini.putInt("IntegerVariable", IntegerVariable);

  ini.commit();

  Serial.println("ok");
}
//----------------------------------------------------------------------------------------
