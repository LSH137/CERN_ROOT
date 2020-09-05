#include "Riostream.h"

void CSVtoROOT(){

    TString dir = gSystem -> UnixPathName(gInterpreter -> GetCurrentMacroName());
    dir.ReplaceAll("CSVtoROOT.C","");
    dir.ReplaceAll("/./","/");
    ifstream in;
    in.open(Form("%scloud.csv",dir.Data()));

    Int_t time,year,month,day,hour,totc,fog,lowc,midc,highc;
    Int_t nlines = 0;

    TFile *f = new TFile("cloud.root", "RECREATE");
    TH1F *h1 = new TH1F("h1", "time distribution", 100, -4, 4);
    TNtuple *ntuple = new TNtuple("ntuple", "cloud_data", "time:year:month:day:hour:totc:fog:lowc:midc:highc");

    while (1) 
     {
          in >>time>>year>>month>>day>>hour>>totc>>fog>>lowc>>midc>>highc;
          if (!in.good())
		 break;
          else
		printf("time=%d,year=%d,month=%d,day=%d,hour=%d,totc=%d,fog=%d,lowc=%d,midc=%d,highc=%d",time,year,month,day,hour,totc,fog,lowc,midc,highc);

          h1 -> Fill(time);
          ntuple -> Fill(time,year,month,day,hour,totc,fog,lowc,midc,highc);
          nlines++;
     }
     printf("found %d data\n", nlines);
     in.close();
     f -> Write();
}
