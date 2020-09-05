#include "Riostream.h"
#include <stdio.h>

void Graph2()
{
    auto C = new TCanvas("simulation_data","simulation_data",1200, 600);
    auto mg = new TMultiGraph();
    
    //char graph_name[250];

    gStyle->SetOptTitle(kFALSE);
    gStyle->SetPalette(kSolar);

    double temp[5];
    //int index = 1;
    //int trig = 0;
    //Int_t t = 0;
    //int n = 0;

    TFile *f = new TFile("observed_edep.root", "RECREATE");
    TGraph *gEdep = new TGraph();
    //TGraph *gEdep_ch3 = new TGraph();

    for(int i = 0; i < 4; i++)
    {
         scanf("%lf,%lf", &temp[0], &temp[1]);

         gEdep -> SetPoint(gEdep->GetN(), temp[0], temp[1]);
     
          /*
         if(index == 2)
         {
              gEdep -> SetPoint(t, temp[0], temp[1]);
              trig = 1;
         }
               
         if(index == 1)
         {
               if(trig == 1)
               {
                    mg->Add(gEdep, "PL");
                    mg->Draw("A pmc plc");
                    t = 0;
               }
        
                    trig = 0;
                    gEdep -> SetPoint(t, temp[0], temp[1]);
          
               
               
         }
         */

          //t++;
               //gEdep_ch3 -> SetPoint(gEdep_ch3->GetN(), time, 1024 - temp[3]);

    }
      gEdep -> SetTitle("1GeV");
      mg->Add(gEdep, "PL");
      mg->Draw("A pmc plc");


          //gEdep -> SetTitle("ch2");
          //gEdep_ch3 -> SetTitle("ch3");
          //mg->Add(gEdep_ch2, "PL");
          

          //gEdep->Draw("PL");

          C->BuildLegend();
          //sprintf(graph_name, "/media/lsh/CosmicrayRnE/observed_data/simulation_data.png");
          C->SaveAs("simulation_data.png");

          
          
          //mg->RecursiveRemove(gEdep_ch2);
          //mg->RecursiveRemove(gEdep_ch3);

          //time = 0;

     //in.close();
     f -> Write();
     //n++;
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
