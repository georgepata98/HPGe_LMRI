// Programul calculeaza automat ariile fotopicurilor si FEPE pentru energiile din hpge_lmri
#include <TFile.h>
#include <TKey.h>
#include <TH1.h>
#include <TSystem.h>
#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <TList.h>
#include <TString.h>
#include <iostream>
#include <fstream>

void auto_analyzer()  // numele trebuie sa fie ca cel al fisierului
{
    TCanvas *c1 = nullptr;
	TString dir_path = ".";  // path-ul este folderul curent
    TSystemDirectory dir(dir_path, dir_path);  // in paranteza este logical name si path-ul (folderul curent)
    TList *files = dir.GetListOfFiles();  // lista cu fisiere din folderul curent
    if(!files)
    {
        cout << "\nNu s-au gasit fisiere in folderul curent !" << endl;
        return;
    }


    TIter next(files);
    TSystemFile *file;
    int nr_histograme=0;
	fstream textFile;  // fisierul text in care se adauga FEPE-urile

    // Iterare pe toate fisierele din folder

	textFile.open("rezultate_fepe.txt", ios::out);
    while((file = (TSystemFile*)next()))
    {
        TString fileName = file->GetName();  // nume fisier din folder
        if(!file->IsDirectory() && fileName.EndsWith(".root"))  // daca fisierul din folder nu e folder si are extensia .root
        {
            cout << "\nSe proceseaza fisierul ROOT " << fileName << " ..." << endl;

			TString filePath = Form("%s/%s", dir_path.Data(), fileName.Data());
			TFile *rootFile = TFile::Open(filePath);
            if(!rootFile || rootFile->IsZombie())
            {
                cout << "Nu s-a putut deschide fisierul " << fileName << " !" << endl;
                continue;
            }

            TIter keyIter(rootFile->GetListOfKeys());
            TKey *key;

            // Loop dupa key-urile din fisierul root

            while((key = (TKey*)keyIter()))
            {
                TObject *obj = key->ReadObj();
				TH1 *hist = nullptr;
				if(obj->InheritsFrom(TH1::Class()))
				{
					hist = (TH1*)obj;
				}
                cout << "Se analizeaza histograma " << hist->GetName() << " din " << fileName << " ..." << endl;
                int nbins, bin_st, bin_dr, nr_particule;  // bin_st si bin_dr sunt binii dupa care se integreaza
                double bin1_min, bin1_max, e_st, e_dr, bin_err, bin_width, sum=0;
                int distance, energy, aux=0;
				string auxName;
				

                nbins = hist->GetNbinsX();
                // capetele de energie ale primului bin
                bin1_min = hist->GetBinLowEdge(1);
                bin1_max = hist->GetBinLowEdge(2);
                bin_width = bin1_max - bin1_min;
                cout << "\n   Nr. bini ai histogramei: " << nbins << "\n   Grosime bin: " << bin_width << " [keV]" << endl;
				
                if(nr_histograme == 0)
                {
                    textFile << "Distanta [cm] | Energia [keV] | FEPE=fotopic/NPS | Incertitudine FEPE" << endl;
                }
				
				
                for(int i=0; i<=20; ++i)
                {
					distance = i;
                    if(i>=0 && i<=5)   { nr_particule=2000000; }
                    if(i>=6 && i<=10)  { nr_particule=6000000; }
                    if(i>=11 && i<=15) { nr_particule=20000000; }
                    if(i>=16 && i<=20) { nr_particule=60000000; }
                    for(int j=1; j<=28; ++j)
                    {
						if(j == 1)  { energy=40; e_st=38; e_dr=42; }
						if(j == 2)  { energy=60; e_st=58; e_dr=62; }
						if(j == 3)  { energy=80; e_st=78; e_dr=82; }
						if(j == 4)  { energy=100; e_st=98; e_dr=102; }
						if(j == 5)  { energy=120; e_st=118; e_dr=122; }
						if(j == 6)  { energy=130; e_st=128; e_dr=133; }
						if(j == 7)  { energy=140; e_st=138; e_dr=143; }
						if(j == 8)  { energy=150; e_st=148; e_dr=153; }
						if(j == 9)  { energy=200; e_st=198; e_dr=203; }
						if(j == 10) { energy=220; e_st=218; e_dr=223; }
						if(j == 11) { energy=240; e_st=238; e_dr=243; }
						if(j == 12) { energy=260; e_st=258; e_dr=263; }
						if(j == 13) { energy=280; e_st=278; e_dr=283; }
						if(j == 14) { energy=300; e_st=298; e_dr=303; }
						if(j == 15) { energy=350; e_st=348; e_dr=353; }
						if(j == 16) { energy=400; e_st=398; e_dr=403; }
						if(j == 17) { energy=450; e_st=448; e_dr=453; }
						if(j == 18) { energy=500; e_st=497; e_dr=503; }
						if(j == 19) { energy=600; e_st=597; e_dr=603; }
						if(j == 20) { energy=700; e_st=697; e_dr=703; }
						if(j == 21) { energy=800; e_st=797; e_dr=803; }
						if(j == 22) { energy=900; e_st=897; e_dr=903; }
						if(j == 23) { energy=1000; e_st=997; e_dr=1003; }
						if(j == 24) { energy=1100; e_st=1097; e_dr=1103; }
						if(j == 25) { energy=1200; e_st=1197; e_dr=1203; }
						if(j == 26) { energy=1300; e_st=1297; e_dr=1303; }
						if(j == 27) { energy=1400; e_st=1397; e_dr=1403; }
						if(j == 28) { energy=1600; e_st=1597; e_dr=1603; }
						
                        auxName = ("hpge_" + std::to_string(i) + "cm_" + std::to_string(energy) + "kev_Run0.root").c_str();
						if(fileName == auxName)
						{
							cout << "   Nr. de particule simulate: " << nr_particule << endl;
							aux = 1;
							break;
						}
                    }
					if(aux == 1) break;
                }
				cout << "   Intervalul de energii pe care se integreaza, in [keV]:" << endl;
                cout << "E_stanga  = " << e_st << "\nE_dreapta = " << e_dr << endl;

                for(int i=1; i<=nbins; ++i)
                {
                    if(bin1_min + i*bin_width < e_st) bin_st = i+1;
                    if(bin1_min + i*bin_width == e_st) bin_st = i;
                    if(bin1_min + i*bin_width < e_dr) bin_dr = i+1;
                    if(bin1_min + i*bin_width == e_dr) bin_dr = i;
                }
                cout << "=> bin_stanga  = " << bin_st << "\n=> bin dreapta = " << bin_dr << endl;

                for(int i=1; i<=nbins; ++i)
                {
                    if(i>=bin_st && i<=bin_dr)
                    {
                        bin_err = hist->GetBinError(i);
                        sum += bin_err*bin_err;
                    }
                }
                sum = TMath::Sqrt(sum);

                cout << "\n   Arie pic = " << hist->Integral(bin_st, bin_dr) << " +/- " << sum << " [counts]" << endl;
                cout << "   Eficacitate_detectie(deltaE) = " << hist->Integral(bin_st, bin_dr) / nr_particule << " +/- " << sum / nr_particule << endl;

                textFile << distance << " " << energy << " " << hist->Integral(bin_st, bin_dr) / nr_particule << " " << sum / nr_particule << endl;
				nr_histograme++;
            }


            rootFile->Close();
            delete rootFile;
        }
    }
	
	textFile.close();
    cout << "\nAu fost analizate " << nr_histograme << " histograme." << endl;
}