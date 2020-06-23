#include <Arduino.h>
#include <FS.h>

void setup() {
  Serial.begin(115200);

  bool res = SPIFFS.begin();
  if (!res) {
    Serial.printf("SPIFFS error \n");
    while (true) {};
  }

  // 1. SPIFFS info
  FSInfo fs_info;
  SPIFFS.info(fs_info);
  Serial.println("SPIFFS info");
  Serial.println("totalBytes:" + String(fs_info.totalBytes));
  Serial.println("usedBytes:" + String(fs_info.usedBytes));
  Serial.println("blockSize:" + String(fs_info.blockSize));
  Serial.println("pageSize:" + String(fs_info.pageSize));
  Serial.println("maxOpenFiles:" + String(fs_info.maxOpenFiles));
  Serial.println("maxPathLength:" + String(fs_info.maxPathLength));

  // 2. SPIFFS File list
  Serial.println("");
  Serial.println("File list");
  Dir dir = SPIFFS.openDir("/");
  while( dir.next()) {
    String fn, fs;
    fn = dir.fileName();
    fn.remove(0, 1);
    fs = String(dir.fileSize());
    Serial.printf("<%s> size=%s\n", fn.c_str(), fs.c_str());
  }

  // 3. SPIFFS File read
  Serial.println("");
  Serial.println("File read");
//  char buf[8192];
  File fd = SPIFFS.open("/main.py", "r");
  int len = fd.available();
  Serial.printf("file size=%d\n", len);
  String str = fd.readString();
//  size_t st = fd.readBytes(buf, len);
//  Serial.printf("file read: %d\n", (int)st);
  Serial.println(str);
//  Serial.println(str);
  fd.close();
}

void loop() {
  sleep(1);
}