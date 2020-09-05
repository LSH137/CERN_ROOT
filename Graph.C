#include "Riostream.h"
#include <stdio.h>

void Graph()
{
    auto C = new TCanvas("observed_data","observed_data",1200, 600);
    
    char graph_name[250];

    gStyle->SetOptTitle(kFALSE);
    gStyle->SetPalette(kSolar);

    Int_t temp[5];
    Int_t time = 0;
    int n = 0;

    TFile *f = new TFile("observed_edep.root", "RECREATE");
    TGraph *gEdep_ch2 = new TGraph();
    TGraph *gEdep_ch3 = new TGraph();

    while(1)
    {
         auto mg = new TMultiGraph();

         scanf("%d %d  %d %d %d", &temp[0], &temp[1], &temp[2], &temp[3], &temp[4]);

          for(int i = 0; i < 6; i++)
          {
               scanf("%d %d %d %d %d", &temp[0], &temp[1], &temp[2], &temp[3], &temp[4]);
          }

          for(int i = 0; i < 95; i++)
          {
               scanf("%d %d %d %d %d", &temp[0], &temp[1], &temp[2], &temp[3], &temp[4]);

               gEdep_ch2 -> SetPoint(gEdep_ch2->GetN(), time, 1024 - temp[2]);
               gEdep_ch3 -> SetPoint(gEdep_ch3->GetN(), time, 1024 - temp[3]);

               time = time + 10;
          }

          gEdep_ch2 -> SetTitle("ch2");
          gEdep_ch3 -> SetTitle("ch3");
          mg->Add(gEdep_ch2, "PL");
          mg->Add(gEdep_ch3, "PL");
          mg->Draw("A pmc plc");

          C->BuildLegend();
          sprintf(graph_name, "/media/lsh/CosmicrayRnE/observed_data/observed_data_%d.png", n);
          C->SaveAs(graph_name);

          
          
          //mg->RecursiveRemove(gEdep_ch2);
          //mg->RecursiveRemove(gEdep_ch3);

          time = 0;

     //in.close();
     f -> Write();
     n++;
    }

   

/*

    while (1) 
     {
          in >>year>>month>>day>>hour>>min>>sec>>peak1>>peak2;
          
          for(int i = 0; i < 95; i++)
               in>>edep[i];

          for(int i = 0; i < 95; i++)
               in>>edep_ch2[i];

          for(int i = 0; i < 95; i++)
               in>>edep_ch3[i];

          if (!in.good())
          {
            printf("error occur!!\n");
            break;
          }
          else
     	  //printf("time=%d,year=%d,month=%d,day=%d,hour=%d,totc=%d,fog=%d,lowc=%d,midc=%d,highc=%d\n",time,year,month,day,hour,totc,fog,lowc,midc,highc);

          for(int i = 0; i < 95; i++)
          {
               gEdep -> SetPoint(gEdep->GetN(), edep[i]);
               gEdep_ch2 -> SetPoint(gEdep_ch2->GetN(), edep_ch2[i]);
               gEdep_ch3 -> SetPoint(gEdep_ch3->GetN(), edep_ch3[i]);
          }
          
     
          h1 -> Fill(time);
          ntuple -> Fill(year,month,day,hour,peak1,peak2);
          nlines++;
     }
     printf("found %d data\n", nlines);

     gEdep->SetTitle("total edep");
     gEdep_ch2->SetTitle("ch2");
     gEdep_ch3->SetTitle("ch3");

     graph_totc->SetLineColor(kRed);
     graph_fog->SetLineColor(kBlue);
     graph_lowc->SetLineColor(kYellow);
     graph_midc->SetLineColor(kPink);
     graph_highc->SetLineColor(kGreen);

     graph_totc->SetMarkerColor(kRed);
     graph_fog->SetMarkerColor(kBlue);
     graph_lowc->SetMarkerColor(kYellow);
     graph_midc->SetMarkerColor(kPink);
     graph_highc->SetMarkerColor(kGreen);

     graph_totc->SetLineWidth(1);
     graph_fog->SetLineWidth(1);
     graph_lowc->SetLineWidth(1);
     graph_midc->SetLineWidth(1);
     graph_highc->SetLineWidth(1);
*/
     //mg->Add(gEdep, "PL");
     

     /*
     graph_fog -> Draw("same PLC PFC");
     graph_lowc -> Draw("same PLC PFC");
     graph_midc -> Draw("same PLC PFC");
     graph_highc -> Draw("same PLC PFC");
     */

}