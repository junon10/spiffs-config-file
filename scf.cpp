/*
    Project: spiffs_config_file
    Microcontroller: ESP32
    Compiler: Arduino GCC
    Author: Junon M.
    Version: 1.0.0
    Date: 2022/07/04
*/

#include <Arduino.h>
#include "scf.h"

#include "FS.h"
#include <SPIFFS.h>

//----------------------------------------------------------------------------------------
scf::scf() {
  _file_name = "/config.ini";
  _file_content = "";
}
//----------------------------------------------------------------------------------------
scf::~scf() {

}
//----------------------------------------------------------------------------------------
bool scf::fileExists() {
  return SPIFFS.exists(_file_name);
}
//----------------------------------------------------------------------------------------
void scf::setFileName(String FileName) {

  _file_name = FileName;
  
  if (_file_name[0] != '/') _file_name = "/" + _file_name;
  
  _file_content = "";

  SPIFFS.begin();
}
//----------------------------------------------------------------------------------------
String scf::float2String(float from)
{
  char sValue[30];
  sprintf(sValue, "%.9f", from);
  return String(sValue);
}
//----------------------------------------------------------------------------------------
void scf::write_txt_file(String path, String content)
{
  File f = SPIFFS.open(path, "w");
  f.write((uint8_t *)content.c_str(), content.length());
  f.close();
}
//----------------------------------------------------------------------------------------
String scf::getStr(String Label)
{
  FILE *arq;
  char Buff[100];
  char *result;
  int p1 = 0, p2 = 0, len = 0;
  String s = "", s1 = "", s2 = "";
  String fname = "";

  if (!_file_name.substring(0, sizeof("/spiffs")).equals("/spiffs")) {
    fname = "/spiffs" + _file_name;
  }

  arq = fopen(fname.c_str(), "rt");

  if (arq == NULL)  // Se houve erro na abertura
  {
    Serial.println("\n\nProblemas na abertura do arquivo\n\n");
    return "";
  }

  while (!feof(arq))
  {
    // O 'fgets' lê até 99 caracteres ou até encontrar '\n'
    result = fgets(Buff, 100, arq);

    // Se sim
    if (result)
    {
      // Copie o conteúdo da linha que foi lida para uma string
      s = Buff;

      // Tente localizar o separador
      p1 = s.indexOf("=");

      if (p1 != -1) // Se for localizado, execute
      {
        // Obtenha o tamanho do Rótulo (Label)
        len = p1 - 1;

        // Separe somente o Rótulo, isto é,
        // tudo que estiver antes do sinal de igual
        s1 = s.substring(0, len);

        // Tente localizar o Rótulo (label)
        p2 = s1.indexOf(Label.c_str());

        if (p2 != -1) // Se for localizado, execute
        {
          // Rótulo localizado, primeiro feche o arquivo
          fclose(arq);

          // Obtenha o tamanho total da string
          len = s.length();

          // Copie tudo que estiver depois do sinal de igual até
          // o final da linha
          s2 = s.substring(p1 + 1, len);

          // Remova espaços se tiver
          s2.trim();

          return s2;
        }
      }
    }
  }
  fclose(arq);
  return "";
}
//----------------------------------------------------------------------------------------
float scf::getFloat(String Label)
{
   return atof(scf::getStr(Label).c_str());
}
//----------------------------------------------------------------------------------------
int scf::getInt(String Label)
{
  return atoi(scf::getStr(Label).c_str());
}
//----------------------------------------------------------------------------------------
void scf::putStr(String Label, String Value)
{
  _file_content += Label + " = " + Value + "\n";
}
//----------------------------------------------------------------------------------------
void scf::putFloat(String Label, float Value)
{
  _file_content += Label + " = " + scf::float2String(Value) + "\n";
}
//----------------------------------------------------------------------------------------
void scf::putInt(String Label, int Value)
{
  _file_content += Label + " = " + String(Value) + "\n";
}
//----------------------------------------------------------------------------------------
void scf::commit()
{
  scf::write_txt_file(_file_name, _file_content);
  _file_content = "";
}
//----------------------------------------------------------------------------------------
