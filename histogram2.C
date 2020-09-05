#include <stdio.h>
#include "TH1.h"
#include "Riostream.h"


struct ObData
{
    long long int time;
    int total_edep_ch2 = 0.0;
    int total_edep_ch3 = 0.0;
};

ObData obdata;
const char DivideDataDir[200] = {"/media/lsh/CosmicrayRnE/COSMICRAY_DATA/Processed/result/divide"};
const char MeanDataDir[200] = {"/media/lsh/CosmicrayRnE/COSMICRAY_DATA/Processed/result/mean"};
int fileNumber;
char totalDir[250];

void histogram2()
{
    FILE* fp_data;
    FILE* fp_mean;
    char dir[150];
    char name[150];
    char graph_name[150];
    int error;
    double energy;
    double mean;

    scanf("%d", &fileNumber);

    printf("file number: %d\n", fileNumber);

    auto canvas_ch2 = new TCanvas("observated_data_ch2","observated_data_ch2",800, 600);
    auto canvas_ch3 = new TCanvas("observated_data_ch3","observated_data_ch3",800, 600);
    auto canvas = new TCanvas("observated_data","observated_data",800, 600);

    TH1D* hist_ch2 = new TH1D("total_edep_ch2", "total_edep_ch2", 600, 0, 6000);
    TH1D* hist_ch3 = new TH1D("total_edep_ch3", "total_edep_ch3", 600, 0, 6000);
    TH1D* hist_total = new TH1D("total_edep", "total_edep", 600, 0, 6000);



    for(int i = 0; i < fileNumber; i++)
    {
        sprintf(totalDir, "%s/_%d_edep.txt", DivideDataDir, i);
        fp_data = fopen(totalDir, "r");

        if(fp_data != nullptr)
        {
            while(!feof(fp_data))
            {
                error = fscanf(fp_data, "%lld %d %d\n", &obdata.time, &obdata.total_edep_ch2, &obdata.total_edep_ch3);
                if(error == EOF) 
                {
                    printf("error occur while scan data file");
                    break;
                }
                else
                {
                    hist_ch2 -> Fill(obdata.total_edep_ch2);
                    hist_ch3 -> Fill(obdata.total_edep_ch3);
                    hist_total -> Fill(obdata.total_edep_ch2);
                    hist_total -> Fill(obdata.total_edep_ch3);
                }
                
            }

            sprintf(dir, "%s/mean.txt", MeanDataDir);
            fp_mean = fopen(dir, "a");
            
            if(fp_mean != nullptr)
            {
                fprintf(fp_mean, "%lld %lf %lf %lf\n", obdata.time, hist_ch2->GetMean(), hist_ch3->GetMean(), hist_total->GetMean());

                fclose(fp_mean);
                //printf("=");
            }
            
            canvas_ch2->cd();
            hist_ch2 -> Draw();
            //canvas_ch2->BuildLegend();
            sprintf(graph_name, "/media/lsh/CosmicrayRnE/COSMICRAY_DATA/Processed/result/total/ch2/totalObEdep_%d_%llu-%llu_ch2.png", i, obdata.time - 3600, obdata.time);
            canvas_ch2->SaveAs(graph_name);
            hist_ch2->Reset();

            canvas_ch3->cd();
            hist_ch3 -> Draw();
            //canvas_ch3->BuildLegend();
            sprintf(graph_name, "/media/lsh/CosmicrayRnE/COSMICRAY_DATA/Processed/result/total/ch3/totalObEdep_%d_%llu-%llu_ch3.png", i, obdata.time - 3600, obdata.time);
            canvas_ch3->SaveAs(graph_name);
            hist_ch3->Reset();

            canvas->cd();
            hist_total -> Draw();
            //canvas_ch2->BuildLegend();
            sprintf(graph_name, "/media/lsh/CosmicrayRnE/COSMICRAY_DATA/Processed/result/total/total/totalObEdep_%d_%llu-%llu_total.png", i, obdata.time - 3600, obdata.time);
            canvas->SaveAs(graph_name);
            hist_total->Reset();
            
        }
        else{
            printf("ROOT: error occur while opening obEdep.txt\n");
        }
    }

}
