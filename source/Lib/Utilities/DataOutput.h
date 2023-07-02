#pragma once

#include <string.h>
#include <iostream>
#include <fstream>

#include <CommonLib/Unit.h>

#include <chrono>
#include <ctime>
#include <time.h>

#include <CommonLib/CommonDef.h>

//---------------- Typedef of variables counting time for intra ---------------- // 
typedef std::chrono::duration<double>                  timeDuration;
typedef std::chrono::high_resolution_clock::time_point timePoint;

#define curTime std::chrono::high_resolution_clock::now()
#define castTimeType std::chrono::duration_cast<std::chrono::duration<double>>

extern timeDuration intraTime;

std::string extractFileName(std::string dir);

//---------------- Function for counting time for intra ----------------------- //
void initIntraTime();
void calcIntraTime(timeDuration _intraTime);

typedef struct
{
  std::string sec;     // seconds of minutes from 0 to 61
  std::string min;     // minutes of hour from 0 to 59
  std::string hour;    // hours of day from 0 to 24
  std::string day;     // day of month from 1 to 31
  std::string month;   // month of year from 0 to 11
  std::string year;    // year since 1900
} Time; // Time struct for data out

typedef struct
{
  bool ISP;
  bool MRL;
  bool MIP;
  bool MTTISlice;
} IntraConfig;

class DataOutput
{
private:
  std::string   fileName;
  Time          currentTime;
  std::string   totalInputFrame;
  

public:
  std::ofstream file;
  uint64_t      modeIdx[NUM_LUMA_MODE + 10];
  IntraConfig   intraConfig;

  bool runSecondRound;
  bool printCUInfo = 0;

  DataOutput();
  DataOutput(std::string _dir);

  void init();
  template <typename T>
  void print(T _data); // print to file
  void printC(std::string _str); // print to console
  void printO(std::string _str); // print to file using fprintf

  void saveNumFrameInput(std::string _num);

  void saveIntraConfig(bool ISP, bool MRL, bool MIP, std::string _filename); 

  void printBlockPos(CodingUnit &cu);
  void printBlockSize(CodingUnit &cu);
  void printBlockData(CodingUnit &cu);

  void listingSelectedModes();

  std::string getVidName();

  bool intraDataOut = 0;
};

/*
  Using "extern" -> we can access this var from everywhere.
  Just need to add header file "DataOutput.h" to file you want to grab data.
*/
extern DataOutput dataO; 


