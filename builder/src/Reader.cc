#include "Reader.h"

#include <string>
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <cmath>

RN::Reader::Reader(int argc, char* argv[])
{
  for(int i=1; i<argc; i++)
    file_list.push_back(argv[i]);
  current_file=file_list.begin();
  time_offset=-time_incr;
  time=0;
  keep_going=true;
  
  NextFile();
}

RN::Reader::~Reader(){}

void RN::Reader::NextFile()
{
  if(current_file!=file_list.end())
  {
    time_offset += time + time_incr;
    delete file;

    file = new TFile((*current_file).c_str());
    procTree = (TTree*)file->Get("procData");
    slowTree = (TTree*)file->Get("slowTree");

    int out = 1;
    procTree->SetBranchAddress("target_4Minus2Mean1", &target_4Minus2Mean1);
    procTree->SetBranchAddress("veto_4Minus2Mean1", &veto_4Minus2Mean1);
    procTree->SetBranchAddress("time", &time);
    slowTree->SetBranchAddress("gateMean", &gateMean);
    slowTree->SetBranchAddress("gateDev", &gateDev);
    slowTree->GetEvent(0);

    mSize = procTree->GetEntries();
    mCurrentEvent=-1;

    current_file++;
  }
  else
    keep_going = false;
  return;
}

void RN::Reader::NextEvent()
{
  mCurrentEvent++;
  if(mCurrentEvent < mSize)
  {
    procTree->GetEvent(mCurrentEvent);
    if(!(mCurrentEvent%10000))
      std::cout << "File Progress: \033[32;1m" << std::floor( double(mCurrentEvent)/mSize*100.0 )
		<< "%\r\033[37;0m" << std::flush;
  }
  else
    NextFile();

  return;
}
