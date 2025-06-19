/*
Arduino library: spiffs_config_file
Author: Junon M.
Version: 1.0.0.3
Date: 2025/06/19
*/



//----------------------------------------------------------------------------------------
// Inclusão da lib
//----------------------------------------------------------------------------------------
#include "scf.h"
//----------------------------------------------------------------------------------------

#include <vector>
typedef std::vector<String> StringList;

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
String textVariable = "";
double doubleVariable = 0;
long longVariable = 0;
uint64_t uint64Variable = 0;
String text = "";
StringList ReadedArray, SavedArray;
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  
  ini.set_filename(DEFAULT_CONFIG_FILENAME);
  
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
      textVariable = "Writed Example Text";
      doubleVariable = -12345.678901234567;
      longVariable = -98765432;
      uint64Variable = 1234567890123456789;
      SavedArray.push_back("test1");
      SavedArray.push_back("test2");
      SavedArray.push_back("test3");
      saveConfig();
    }else{
      Serial.println("\n\nType in serial monitor: read, or save\n");
    }
    
  }


}
//----------------------------------------------------------------------------------------
void LoadSetupDefaults(){
  textVariable = "Loaded Default Values";
  doubleVariable = -1;
  longVariable = -1;
  uint64Variable = 1234567890;
  SavedArray.push_back("Value1");
  SavedArray.push_back("Value2");
  SavedArray.push_back("Value3");  
}
//----------------------------------------------------------------------------------------
void readConfig()
{
  if (!ini.file_exists())
  {
    Serial.println("Load Setup Defaults!");
    LoadSetupDefaults();
    return;
  }

  textVariable = ini.get_str("textVariable");
  doubleVariable = ini.get_double("doubleVariable");
  longVariable = ini.get_long("longVariable");
  uint64Variable = ini.get_uint64("uint64Variable");
  ReadedArray = ini.get_array_str("my_array");

  Serial.println("\n\nFile contents read into variables: \n");
  Serial.println("textVariable: " + textVariable);
  Serial.print("doubleVariable: "); Serial.println(String(doubleVariable, 12));
  Serial.print("longVariable: "); Serial.println(longVariable);
  Serial.print("uint64Variable: "); Serial.println(ini.uint64_2_string(uint64Variable));
  Serial.print("ReadedArray: ");
  for (int i = 0; i < ReadedArray.size(); i++) {
    Serial.println(ReadedArray[i]);
  }
  
  Serial.println();

}
//----------------------------------------------------------------------------------------
void saveConfig()
{
  String S = "";

  ini.set_str("textVariable", textVariable);
  ini.set_double("doubleVariable", doubleVariable);
  ini.set_long("longVariable", longVariable);
  ini.set_uint64("uint64Variable", uint64Variable);
  ini.set_array_str("my_array", SavedArray);
  
  ini.commit();

  Serial.println("ok");
}
//----------------------------------------------------------------------------------------
