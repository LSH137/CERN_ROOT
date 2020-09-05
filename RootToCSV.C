#include <iostream>
#include <cstdio>
#include "TFile.h"
#include "TTree.h"
#include <fstream>
#include <cstring>
#include <dirent.h>

using namespace std;

void RootToCSV()
{
  char file_name[5000][500] = {0};
  char root_file_name[500] = {0};
  char csv_file_name[500] = {0};
  char *p1,*p2;
  int ret;
  DIR *path;
  struct dirent *dir;
  int name_index = 0;
  //printf("type root file name ecept .root: ");
  //scanf("%s", file_name);


    path = opendir("/media/lsh/CosmicrayRnE/simulationData/real-simulation/root");
    if (path)
    {
        while ((dir = readdir(path)) != nullptr)
        {
            p1 = strtok(dir->d_name,".");
            p2 = strtok(nullptr,".");

            if(p2 != nullptr)
            {
                ret = strcmp(p2,"root");

                if(ret == 0)
                {
                    printf("%d.", name_index);

                    for(int i = 0; p1[i] != '\0'; i++)
                    {
                        file_name[name_index][i] = p1[i];
                        printf("%c", file_name[name_index][i]);
                    }
                    printf("\n");
                    name_index ++;
                }
            }

        }
        closedir(path);
    } else
        printf(">>error occur while get data file name\n");

    printf(">> start converting\n");

    for(int n = 0; n <  name_index; n++)
    {
      sprintf(root_file_name, "/media/lsh/CosmicrayRnE/simulationData/real-simulation/root/%s.root", file_name[n]);

      TFile *f = new TFile(root_file_name); // opens the root file

      if(f->IsZombie())
      {
        printf("error accor while opening data file\n");
        //exit(-1);
      }
      else 
      {
        printf("success for opening data file\n");
        TTree *tr = (TTree*)f->Get("step"); // creates the TTree object
        //tr -> Scan(); // prints the content on the screen

        double a,b; // create variables of the same type as the branches you want to access
      
        tr->SetBranchAddress("edep",&a); // for all the TTree branches you need this
        tr->SetBranchAddress("time",&b);
  
        sprintf(csv_file_name, "/media/lsh/CosmicrayRnE/simulationData/real-simulation/csv/%s.csv", file_name[n]);

        ofstream myfile;
        myfile.open (csv_file_name);
        //myfile << "time,edep\n";

        for (int i = 0; i < (tr->GetEntries()); i++)
        {
          // loop over the tree
          tr->GetEntry(i);
          //cout << a << "," << b << endl; //print to the screen
          myfile << a << "," << b <<"\n"; //write to file
        }

        myfile.close();
      }

      delete f;
    }

    printf("convert end");
}
