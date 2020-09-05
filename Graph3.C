#include "Riostream.h"
#include <stdio.h>

struct meanData
{
    long long int time = 0; 
    double ch2 = 0.0;
    double ch3 = 0.0;
    double total = 0.0;
};

struct date
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int sec;
};

meanData mean;
const char MeanDataDir[200] = {"/media/lsh/CosmicrayRnE/COSMICRAY_DATA/Processed/result/mean"};
char dir[250];
FILE* fp_mean;
char graph_name[250];

void Graph3()
{
    auto mg = new TMultiGraph();
    auto C = new TCanvas("observed_data","observed_data",1200, 600);
    auto C2 = new TCanvas("observed_data_ratio","observed_data_ratio",1200, 600);

    //gStyle->SetOptTitle(kFALSE);
    //gStyle->SetPalette(kSolar);

    sprintf(dir, "%s/mean.txt", MeanDataDir);
    fp_mean = fopen64(dir, "r");

    if(fp_mean != nullptr)
    {
        sprintf(dir, "%s/edep_histogram.root", MeanDataDir);
        TFile *f = new TFile(dir, "RECREATE");
        TGraph *gMean_ch2 = new TGraph();
        TGraph *gMean_ch3 = new TGraph();
        TGraph *gMean_total = new TGraph();
        TGraph *gMean_ratio = new TGraph();

        while(!feof(fp_mean))
        {
            fscanf(fp_mean, "%lld %lf %lf %lf", &mean.time, &mean.ch2, &mean.ch3, &mean.total);
            printf("%lld %f %f %f\n", mean.time, mean.ch2, mean.ch3, mean.total);

            gMean_ch2->SetPoint(gMean_ch2->GetN(), mean.time, mean.ch2);
            gMean_ch3->SetPoint(gMean_ch3->GetN(), mean.time, mean.ch3);
            gMean_total->SetPoint(gMean_total->GetN(), mean.time, mean.total);
            gMean_ratio->SetPoint(gMean_ratio->GetN(), mean.time, mean.ch2/mean.ch3);
        }

        gMean_ch2->SetTitle("ch2");
        gMean_ch3->SetTitle("ch3");
        gMean_total->SetTitle("total");
        gMean_ratio->SetTitle("ratio:ch2/ch3");

        C->cd();
        mg->Add(gMean_ch2, "PL");
        mg->Add(gMean_ch3, "PL");
        mg->Add(gMean_total, "PL");
        mg->Draw("A pmc plc");

        C->BuildLegend();
        sprintf(graph_name, "%s/edep_mean.png", MeanDataDir);
        C->SaveAs(graph_name);

        C2->cd();
        gMean_ratio->Draw();
        C2->BuildLegend();
        sprintf(graph_name, "%s/edep_ratio=ch2-ch3.png", MeanDataDir);
        C2->SaveAs(graph_name);


          
          
        //mg->RecursiveRemove(gMean_ch2);
        //mg->RecursiveRemove(gMean_ch3);

        //in.close();
        f -> Write();
        fclose(fp_mean);
    }

    
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
               gMean -> SetPoint(gMean->GetN(), edep[i]);
               gMean_ch2 -> SetPoint(gMean_ch2->GetN(), edep_ch2[i]);
               gMean_ch3 -> SetPoint(gMean_ch3->GetN(), edep_ch3[i]);
          }
          
     
          h1 -> Fill(time);
          ntuple -> Fill(year,month,day,hour,peak1,peak2);
          nlines++;
     }
     printf("found %d data\n", nlines);

     gMean->SetTitle("total edep");
     gMean_ch2->SetTitle("ch2");
     gMean_ch3->SetTitle("ch3");

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
     //mg->Add(gMean, "PL");
     

     /*
     graph_fog -> Draw("same PLC PFC");
     graph_lowc -> Draw("same PLC PFC");
     graph_midc -> Draw("same PLC PFC");
     graph_highc -> Draw("same PLC PFC");
     */
