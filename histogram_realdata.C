#include <stdio.h>
#include "Riostream.h"

#define MaxEdepNumber 500000

struct G4Data
{
    int particle = 0;
    int energy = 0;
    double total_edep_ch2 = 0.0;
    double total_edep_ch3 = 0.0;
};

G4Data g4data[MaxEdepNumber];
const char ProcessedDataDir[200] = {"/media/lsh/CosmicrayRnE/COSMICRAY_DATA/Processed"};

void histogram_realdata()
{
    FILE* fp_ch2;
    FILE* fp_ch3;
    int escape;
    char dir[150];
    char name[150];
    char graph_name[150];

    auto canvas_ch2 = new TCanvas("observated_data_ch2","observated_data_ch2",800, 600);
    auto canvas_ch3 = new TCanvas("observated_data_ch3","observated_data_ch3",800, 600);

    sprintf(dir, "%s/observated_data.txt", ProcessedDataDir);
    fp_mu = fopen64(dir, "r");

    TH1D* hist_mu_ch2 = new TH1D("mu-", "mu-", 50, 0, 5);
    TH1D* hist_mu_ch3 = new TH1D("mu-", "mu-", 50, 0, 5);

    escape = 0;
    if(fp_mu != nullptr)
    {
        while(!feof(fp_mu) && escape < MaxEdepNumber)
        {
            fscanf(fp_mu, "%d %lf %lf\n", &g4data[escape].energy, &g4data[escape].total_edep_ch2, &g4data[escape].total_edep_ch3);
            hist_mu_ch2 -> Fill(g4data[escape].total_edep_ch2);
            hist_mu_ch3 -> Fill(g4data[escape].total_edep_ch3);

            if(escape > 1 && g4data[escape - 1].energy != g4data[escape].energy)
            {
                canvas_ch2->cd();
                hist_mu_ch2 -> Draw();
                canvas_ch2->BuildLegend();
                sprintf(graph_name, "/media/lsh/CosmicrayRnE/simulationData/real-simulation/histogram/mu/_%dGeV_ch2.png", g4data[escape-1].energy);
                canvas_ch2->SaveAs(graph_name);
                hist_mu_ch2->Reset();

                canvas_ch3->cd();
                hist_mu_ch3 -> Draw();
                canvas_ch3->BuildLegend();
                sprintf(graph_name, "/media/lsh/CosmicrayRnE/simulationData/real-simulation/histogram/mu/_%dGeV_ch3.png", g4data[escape-1].energy);
                canvas_ch3->SaveAs(graph_name);
                hist_mu_ch3->Reset();
               // canvas -> clear();
            }
            escape++;
        }

    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    sprintf(dir, "%s/simulation_e.txt", SimulationDataDir);
    fp_e = fopen64(dir, "r");

    TH1D* hist_e_ch2 = new TH1D("e-", "e-", 50, 0, 5);
    TH1D* hist_e_ch3 = new TH1D("e-", "e-", 50, 0, 5);

    escape = 0;
    if(fp_e != nullptr)
    {
        while(!feof(fp_e) && escape < MaxEdepNumber)
        {
            fscanf(fp_e, "%d %lf %lf\n", &g4data[escape].energy, &g4data[escape].total_edep_ch2, &g4data[escape].total_edep_ch3);
            hist_e_ch2 -> Fill(g4data[escape].total_edep_ch2);
            hist_e_ch3 -> Fill(g4data[escape].total_edep_ch3);

            if(escape > 1 && g4data[escape - 1].energy != g4data[escape].energy)
            {
                canvas_ch2->cd();
                hist_e_ch2 -> Draw();
                canvas_ch2->BuildLegend();
                sprintf(graph_name, "/media/lsh/CosmicrayRnE/simulationData/real-simulation/histogram/e/_%dGeV_ch2.png", g4data[escape-1].energy);
                canvas_ch2->SaveAs(graph_name);
                hist_e_ch2->Reset();

                canvas_ch3->cd();
                hist_e_ch3 -> Draw();
                canvas_ch3->BuildLegend();
                sprintf(graph_name, "/media/lsh/CosmicrayRnE/simulationData/real-simulation/histogram/e/_%dGeV_ch3.png", g4data[escape-1].energy);
                canvas_ch3->SaveAs(graph_name);
                hist_e_ch3->Reset();
                //canvas -> clear();
            }
            escape++;
        }

    }
}
