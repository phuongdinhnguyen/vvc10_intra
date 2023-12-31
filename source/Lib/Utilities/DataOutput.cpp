#include "DataOutput.h"
#include <string.h>
#include <string>
#include <iostream>

DataOutput::DataOutput() {}

void DataOutput::init() {
  // Extract time from clock
  time_t now = time(0);
  tm *   ltm = localtime(&now);

  currentTime.year  = std::to_string(1900 + ltm->tm_year);
  currentTime.month = std::to_string(1 + ltm->tm_mon);
  currentTime.day   = std::to_string(ltm->tm_mday);
  currentTime.hour  = std::to_string(ltm->tm_hour);
  currentTime.min   = std::to_string(ltm->tm_min);
  currentTime.sec   = std::to_string(ltm->tm_sec);

  std::string outputFileName = fileName + "_" + currentTime.year + "-" + currentTime.month + "-" + currentTime.day + "_"
                               + currentTime.hour + currentTime.min + currentTime.sec + ".txt";

  // Opening file and start writing
  file.open(outputFileName);

  // clear modeIdx aray
  memset(modeIdx, 0, (NUM_LUMA_MODE + 10) * sizeof(uint64_t));


  // File header
  file << "Video name: " << fileName << "\n";
  file << "Date and time running: " << currentTime.day << "-" << currentTime.month << "-" << currentTime.year << " at "
       << currentTime.hour << ":" << currentTime.min << ":" << currentTime.sec << std::endl;

  file << "Total input frames: " << totalInputFrame << std::endl;

  file << "ISP: " << intraConfig.ISP << std::endl;
  file << "MRL: " << intraConfig.MRL << std::endl;
  file << "MIP: " << intraConfig.MIP << std::endl;

  file.flush();   // operator "<<" only insert data to stream, not writing it, so we have to flush

  runSecondRound = true;
  printCUInfo    = 0;
}

// print to file
template<typename T> 
void DataOutput::print(T data){
  if (file.is_open()) {
    file << data;
    file.flush();
  }   
  else
    fprintf(stdout, "File is not open!");
}

// print to file 2
void DataOutput::printO(std::string _str)
{
  if (file.is_open())
  {
    file << _str;
    file.flush();
  }
  else
    fprintf(stdout, "File is not open!");
}

void DataOutput::saveNumFrameInput(std::string _num) {
  totalInputFrame = _num;
}

void DataOutput::saveIntraConfig(bool _ISP, bool _MRL, bool _MIP, std::string _fileName) 
{
  intraConfig.ISP = _ISP;
  intraConfig.MRL = _MRL;
  intraConfig.MIP = _MIP;

  fileName = _fileName;

}

void DataOutput::listingSelectedModes() 
{
  if (intraConfig.MTTISlice == 0) 
  {
    file << "BT and TT is disabled! \n";
  }
  file << "listing number of modes: \n";
  file << "run second round is: " << runSecondRound << std::endl;
  int totalModes = 0;
  for (int i = 0; i < 67; i++) 
  //if (modeIdx[i] > 0)
  {
    std::cout << "mode " << i << ": ";
    std::cout << modeIdx[i] << std::endl;

    file << "mode " << i << ": ";
    file << modeIdx[i] << std::endl;
    
    totalModes += (int)modeIdx[i];
  }
  file << "Total modes: " << totalModes << std::endl;
  std::cout << "Total modes: " << totalModes << std::endl;
  file.flush();
}

// print to console
void DataOutput::printC(std::string _str){
  if (file.is_open())
    fprintf(stdout, _str.c_str());
  else
    fprintf(stdout, "File is not open!");
}

std::string extractFileName(std::string dir)
{
  std::string tmp = dir;
  std::string res = dir;
  for (size_t i = tmp.length() - 1; i >= 0; i--)
  {
    if (tmp[i] == '\\')
    {
      res = tmp.substr(i + sizeof(char), tmp.length() - i - 1 - 4);
      break;
    }
  }

  return res;
}

void initIntraTime()
{
  intraTime = curTime - curTime;
}

void calcIntraTime(timeDuration _intraTime)
{
  intraTime += _intraTime;
}

std::string DataOutput::getVidName() 
{
  return fileName;
}