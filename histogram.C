#include <stdio.h>
#include "Riostream.h"

#define MaxEdepNumber 520000

struct G4Data
{
    int particle = 0;
    double energy = 0;
    double total_edep_ch2 = 0.0;
    double total_edep_ch3 = 0.0;
};

G4Data g4data[MaxEdepNumber];
const char SimulationDataDir[200] ={"/media/lsh/CosmicrayRnE/simulationData/real-simulation"};

void histogram()
{
    FILE* fp_mu;
    FILE* fp_e;
    int escape;
    char dir[150];
    char name[150];
    char graph_name[150];
    int chk = 0;

    auto canvas_ch2 = new TCanvas("simulation_data_ch2","simulation_data_ch2",800, 600);
    auto canvas_ch3 = new TCanvas("simulation_data_ch3","simulation_data_ch3",800, 600);
    auto canvas = new TCanvas("simulation_data_total","simulation_data_total",800, 600);
    auto canvas_ratio = new TCanvas("simulation_data_ratio","simulation_data_ratio",800, 600);
    auto canvas_diff = new TCanvas("simulation_data_difference","simulation_data_difference",800, 600);
    auto mg = new TMultiGraph();
    auto mg2 = new TMultiGraph();

    sprintf(dir, "%s/simulation_mu.txt", SimulationDataDir);
    fp_mu = fopen64(dir, "r");

    TH1D* hist_mu_ch2 = new TH1D("mu-_ch2", "mu-_ch2", 200, 0, 10000);
    TH1D* hist_mu_ch3 = new TH1D("mu-_ch3", "mu-_ch3", 200, 0, 10000);
    TH1D* hist_mu_total = new TH1D("mu-_total", "mu-_total", 200, 0, 10000);
    TGraph *graph_ratio_mu = new TGraph();
    TGraph *graph_ratio_e = new TGraph();

    TGraph *graph_diff_mu = new TGraph();
    TGraph *graph_diff_e = new TGraph();

    graph_ratio_mu->SetMarkerStyle(2);
    graph_ratio_e->SetMarkerStyle(2);

    graph_diff_mu->SetMarkerStyle(2);
    graph_diff_e->SetMarkerStyle(2);

    escape = 0;
    if(fp_mu != nullptr)
    {
        while(!feof(fp_mu) && escape < MaxEdepNumber)
        {
            fscanf(fp_mu, "%lf %lf %lf\n", &g4data[escape].energy, &g4data[escape].total_edep_ch2, &g4data[escape].total_edep_ch3);
            hist_mu_ch2 -> Fill(g4data[escape].total_edep_ch2);
            hist_mu_ch3 -> Fill(g4data[escape].total_edep_ch3);
            hist_mu_total -> Fill(g4data[escape].total_edep_ch2);
            hist_mu_total -> Fill(g4data[escape].total_edep_ch3);


            if(escape > 1 && g4data[escape - 1].energy != g4data[escape].energy)
            {
                graph_ratio_mu->SetPoint(graph_ratio_mu->GetN(), g4data[escape].energy, hist_mu_ch2->GetMean()/hist_mu_ch3->GetMean());
                graph_diff_mu->SetPoint(graph_diff_mu->GetN(), g4data[escape].energy, (hist_mu_ch2->GetMean())-(hist_mu_ch3->GetMean()));

                canvas_ch2->cd();
                hist_mu_ch2 -> Draw();
                //canvas_ch2->BuildLegend();
                sprintf(graph_name, "/media/lsh/CosmicrayRnE/simulationData/real-simulation/histogram/mu/ch2/_%fGeV_ch2.png", g4data[escape-1].energy);
                canvas_ch2->SaveAs(graph_name);
                hist_mu_ch2->Reset();

                canvas_ch3->cd();
                hist_mu_ch3 -> Draw();
                //canvas_ch3->BuildLegend();
                sprintf(graph_name, "/media/lsh/CosmicrayRnE/simulationData/real-simulation/histogram/mu/ch3/_%fGeV_ch3.png", g4data[escape-1].energy);
                canvas_ch3->SaveAs(graph_name);
                hist_mu_ch3->Reset();
               // canvas -> clear();

                canvas->cd();
                hist_mu_total -> Draw();
                //canvas_ch3->BuildLegend();
                sprintf(graph_name, "/media/lsh/CosmicrayRnE/simulationData/real-simulation/histogram/mu/total/_%fGeV_total.png", g4data[escape-1].energy);
                canvas->SaveAs(graph_name);
                hist_mu_total->Reset();

                chk = 1;
            }
            escape++;
        }

        graph_ratio_mu->SetTitle("mu-");
        graph_ratio_mu->SetLineColor(3);
        canvas_ratio->cd();
        mg->Add(graph_ratio_mu, "PL");

        graph_diff_mu->SetTitle("mu-");
        graph_diff_mu->SetLineColor(3);
        canvas_diff->cd();
        mg2->Add(graph_diff_mu, "PL");
        //graph_ratio_mu->Draw("APL");
        //canvas_ratio->BuildLegend();
        //sprintf(graph_name, "%s/edep_mean_mu.png", SimulationDataDir);
        //canvas_ratio->SaveAs(graph_name);
        //canvas_ratio->Clear();
    }
    else
    {
        printf("error\n");
    }
    

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    sprintf(dir, "%s/simulation_e.txt", SimulationDataDir);
    fp_e = fopen64(dir, "r");

    TH1D* hist_e_ch2 = new TH1D("e-_ch2", "e-_ch2", 200, 0, 10000);
    TH1D* hist_e_ch3 = new TH1D("e-_ch3", "e-_ch3", 200, 0, 10000);
    TH1D* hist_e_total = new TH1D("e-_total", "e-_total", 200, 0, 10000);

    escape = 0;
    if(fp_e != nullptr)
    {
        while(!feof(fp_e) && escape < MaxEdepNumber)
        {
            fscanf(fp_e, "%lf %lf %lf\n", &g4data[escape].energy, &g4data[escape].total_edep_ch2, &g4data[escape].total_edep_ch3);
            hist_e_ch2 -> Fill(g4data[escape].total_edep_ch2);
            hist_e_ch3 -> Fill(g4data[escape].total_edep_ch3);
            hist_e_total -> Fill(g4data[escape].total_edep_ch2);
            hist_e_total -> Fill(g4data[escape].total_edep_ch3);

            if(escape > 1 && g4data[escape - 1].energy != g4data[escape].energy)
            {
                graph_ratio_e->SetPoint(graph_ratio_e->GetN(), g4data[escape].energy, hist_e_ch2->GetMean()/hist_e_ch3->GetMean());
                graph_diff_e->SetPoint(graph_diff_e->GetN(), g4data[escape].energy, (hist_e_ch2->GetMean())-(hist_e_ch3->GetMean()));

                canvas_ch2->cd();
                hist_e_ch2 -> Draw();
                //canvas_ch2->BuildLegend();
                sprintf(graph_name, "/media/lsh/CosmicrayRnE/simulationData/real-simulation/histogram/e/ch2/_%fGeV_ch2.png", g4data[escape-1].energy);
                canvas_ch2->SaveAs(graph_name);
                hist_e_ch2->Reset();

                canvas_ch3->cd();
                hist_e_ch3 -> Draw();
                //canvas_ch3->BuildLegend();
                sprintf(graph_name, "/media/lsh/CosmicrayRnE/simulationData/real-simulation/histogram/e/ch3/_%fGeV_ch3.png", g4data[escape-1].energy);
                canvas_ch3->SaveAs(graph_name);
                hist_e_ch3->Reset();
                //canvas -> clear();

                canvas->cd();
                hist_e_total -> Draw();
                //canvas_ch3->BuildLegend();
                sprintf(graph_name, "/media/lsh/CosmicrayRnE/simulationData/real-simulation/histogram/e/total/_%fGeV_ch3.png", g4data[escape-1].energy);
                canvas->SaveAs(graph_name);
                hist_e_total->Reset();
            }
            escape++;
        }
        graph_ratio_e->SetTitle("e-");
        graph_ratio_e->SetLineColor(2);
        canvas_ratio->cd();
        mg->Add(graph_ratio_e, "PL");
        mg->SetTitle("simulation ratio:ch2/ch3; energy[GeV]; ratio");
        mg->Draw("A");

        canvas_ratio->BuildLegend();
        sprintf(graph_name, "%s/edep_ratio.png", SimulationDataDir);
        canvas_ratio->SaveAs(graph_name);

        graph_diff_e->SetTitle("e-");
        graph_diff_e->SetLineColor(2);
        canvas_diff->cd();
        mg2->Add(graph_diff_e, "PL");
        mg2->SetTitle("simulation difference:ch2-ch3; energy[GeV]; difference[MeV]");
        mg2->Draw("A");
        //graph_ratio_e->Draw("same");
        

        canvas_diff->BuildLegend();
        sprintf(graph_name, "%s/edep_diff.png", SimulationDataDir);
        canvas_diff->SaveAs(graph_name);        
    }

}
