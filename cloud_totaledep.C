#include "Riostream.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MaxEvent 86400

long long int MonthToDay(int year, int month)
{
    switch (month) {
        case 1:
            return 0;
        case 2:
            return 31;
        case 3:
        {
            if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) return MonthToDay(year, 2) + 29;
            else return MonthToDay(year, 2) + 28;
        }
        case 4:
            return 31 + MonthToDay(year, 3);
        case 5:
            return 30 + MonthToDay(year, 4);
        case 6:
            return 31 + MonthToDay(year, 5);
        case 7:
            return 30 + MonthToDay(year, 6);
        case 8:
            return 31 + MonthToDay(year, 7);
        case 9:
            return 31 + MonthToDay(year, 8);
        case 10:
            return 30 + MonthToDay(year, 9);
        case 11:
            return 31 + MonthToDay(year, 10);
        case 12:
            return 30 + MonthToDay(year, 11);
        default:
            return 0;
    }
}

class Time
{
public:
    Time()
    {
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minute = 0;
        sec = 0;
        time = 0;
    }

    ~Time()
    {
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minute = 0;
        sec = 0;
        time = 0;
    }

    void ConvertTime() // second past after 2019/1/1/0/0
    {
        unsigned long long int daypass;
        daypass = (year - 2019) * 365 + MonthToDay(year, month) + day;

        time = daypass * 86400 + hour * 3600 + minute * 60 + sec;
    }

    int year;
    int month;
    int day;
    int hour;
    int minute;
    int sec;
    unsigned long long int time;
};


int FileName(const char d[150], char(*file_name)[150], const char type[])
{
    DIR *path;
    char *p1,*p2;
    int ret;
    struct dirent *dir;
    int name_index = 0;

    //printf(">>success to enter FileName\n");
    //printf("FileName(): debug point 1\n");
    path = opendir(d);
    if (path)
    {
        //printf("FileName(): debug point 2\n");
        while ((dir = readdir(path)) != nullptr)
        {
            //printf("FileName(): debug point 3\n");
            p1 = strtok(dir->d_name,".");
            p2 = strtok(nullptr,".");

            if(p2 != nullptr)
            {
                //printf("FileName(): debug point 4\n");
                ret = strcmp(p2,type);

                if(ret == 0)
                {
                    //printf("FileName(): debug point 5\n");

                    strcpy(file_name[name_index], p1);
                    
                    printf("index:%d, %s\n", name_index, file_name[name_index]);

                    name_index ++;
                }
            }

        }
        closedir(path);
    } else
        printf(">>error occur while get data file name\n");

     //printf("FileName(): debug point 6\n");
    return name_index;
    //printf("||FileName end\n");
}

struct EdepData
{
    Time t;
    int edep_ch2;
    int edep_ch3;
};


struct CloudData
{
    Time t;
    int totc = 0;
    int fog = 0;
    int lowc = 0;
    int midc = 0;
    int highc = 0;
};



void cloud_totaledep()
{
    FILE* fp_cloud;
    FILE* fp_edep;
    EdepData edep;
    char graph_name[250];
    char file_name[400][150];
    char dir[250];
    int index_cloud = 0;
    int chk;
    int escape = 0;
    int nfile;
    const char Lv1DataDir[150] = {"/media/cosmicray/CosmicrayRnE/ObservedData/Lv1_data"};
    const char TXT[5] = {"txt"};
    auto cloudData = new CloudData[4000];
    auto canvas = new TCanvas("cloud_edep graph","cloud_edep graph",1200, 600);
    TFile *f = new TFile("cloud_edep graph.root", "RECREATE");
    TGraph *graph = new TGraph();

    fp_cloud = fopen64("/media/cosmicray/CosmicrayRnE/ObservedData/CloudData/2019_12_16to2020_6_20cloudData.txt", "r");

    nfile = FileName(Lv1DataDir, file_name, TXT);

    if(fp_cloud != nullptr)
    {
        while(!feof(fp_cloud))
        {
            fscanf(fp_cloud, "%d. %d. %d,%d:%d,%d%%,%d%%,%d%%,%d%%,%d%%", &cloudData[index_cloud].t.year, &cloudData[index_cloud].t.month, &cloudData[index_cloud].t.day, &cloudData[index_cloud].t.hour, &cloudData[index_cloud].t.minute, &cloudData[index_cloud].totc, &cloudData[index_cloud].fog, &cloudData[index_cloud].lowc, &cloudData[index_cloud].midc, &cloudData[index_cloud].highc);
            cloudData[index_cloud].t.ConvertTime();

            //if(cloudData[index_cloud].t.year != 0)
            //gcloud -> SetPoint(gcloud->GetN(), cloudData[index_cloud].t.time, cloudData[index_cloud].lowc);
            //printf("cloud>>%d: %d %d %d %d %d %d %d %d %d %d\n",cloudData[index_cloud].t.time, cloudData[index_cloud].t.year, cloudData[index_cloud].t.month, cloudData[index_cloud].t.day, cloudData[index_cloud].t.hour, cloudData[index_cloud].t.minute, cloudData[index_cloud].t.sec, cloudData[index_cloud].totc, cloudData[index_cloud].lowc, cloudData[index_cloud].midc, cloudData[index_cloud].highc);
            index_cloud++;
        }

        fclose(fp_cloud);
    }

    printf("\n-------------------debug point 1-------------------\n");
    for(int i = 0; i < nfile; i++)
    {
        //printf("\n-------------------debug point 2-------------------\n");
        sprintf(dir, "%s/%s.txt", Lv1DataDir, file_name[i]);
        fp_edep = fopen64(dir, "r");

        //printf("\n-------------------debug point 3-------------------\n");

        if(fp_edep != nullptr)
        {
            //printf("\n-------------------debug point 4-------------------\n");
            while(!feof(fp_edep) && escape <= MaxEvent)
            {
                //printf("\n-------------------debug point 5-------------------\n");
                fscanf(fp_edep, "%lld %d %d %d %d %d %d %d %d", &edep.t.time, &edep.t.year, &edep.t.month, &edep.t.day, &edep.t.hour, &edep.t.minute, &edep.t.sec, &edep.edep_ch2, &edep.edep_ch3);
                edep.t.ConvertTime();
                //printf("\n-------------------debug point 6-------------------\n");
                for(int i = 0; i < index_cloud; i++)
                {
                    //printf("\n-------------------debug point 7-------------------\n");
                    if(edep.t.time == cloudData[i].t.time)
                    {
                        //printf("\n-------------------debug point 8-------------------\n");
                        graph->SetPoint(graph->GetN(), cloudData[i].fog, (double)edep.edep_ch2/(double)edep.edep_ch3);
                        //printf("point!\n");
                    }

                }

                escape++;
            }
            fclose(fp_edep); 
            escape = 0;  
        }
        else
        {
            printf("error");
        }
        

        
    }
    //printf("\n-------------------debug point 9-------------------\n");

    canvas -> cd();
    graph -> SetTitle("ch2/ch3:fog");
    graph -> SetMarkerSize(2.0);
    graph -> SetMarkerStyle(31);
    graph -> Draw("AP");

    canvas->SaveAs("/media/cosmicray/CosmicrayRnE/ObservedData/CloudData/ch2/ch3fog.png");

    
    delete[] cloudData;
}
