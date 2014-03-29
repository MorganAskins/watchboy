#include "Writer.h"
#include <TFile.h>
#include <TTree.h>
#include <string>

RN::Writer::Writer(std::string fname)
{
  file = new TFile(fname.c_str(), "recreate");
  tree = new TTree("data", "event builder data");

  tree->Branch("target_total", &target_total);
  tree->Branch("veto_total", &veto_total);
  tree->Branch("target_cb", &target_cb);
  tree->Branch("veto_cb", &veto_cb);
  tree->Branch("time", &time);
}

RN::Writer::~Writer()
{
  delete tree;
  delete file;
}

void RN::Writer::Fill()
{
  tree->Fill();
}

void RN::Writer::Write()
{
  file->Write("", TObject::kOverwrite);
}
