#ifndef RNREADER_h
#define RNREADER_h

#include <vector>
#include <string>
#include <TFile.h>
#include <TTree.h>

namespace RN
{
  class Reader
  {
    std::vector<std::string> file_list;
    std::vector<std::string>::iterator current_file;
    bool keep_going;

    TFile* file;
    TTree* procTree;
    TTree* slowTree;

    int mSize;
    int mCurrentEvent;
    static const unsigned long long time_incr = 250000000; // 1 second
  public:
    Reader(int argc, char* argv[]);
    ~Reader();

    void NextFile();
    void NextEvent();

    bool isAlive(){return keep_going;}

    // procTree
    double target_4Minus2Mean1[16];
    double veto_4Minus2Mean1[36];
    unsigned long long time;
    unsigned long long time_offset;
    // slowTree
    double gateMean[52];
    double gateDev[52];
  };
}
#endif
