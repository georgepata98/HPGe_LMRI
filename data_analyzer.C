{
// Programul umple o singura histograma "combinedHisto" cu datele din histogramele dupa fiecare Run ale unei simulari.
    TCanvas *c1 = new TCanvas("c1", "canvas", 800, 600);
    TH1F *combinedHisto = nullptr;

    int num;
    string rootFileName, histoName;

    cout << "\n   Fisierele root trebuie sa fie in acelasi folder cu acest program !" << endl;
    cout << "Nr. de fisiere root facute dupa o simulare (egal cu nr. de Run-uri):\n     "; cin >> num;
    cout << "Numele fisierelor root (fara .root si fara a specifica ID-ul Run-ului):\n     "; cin >> rootFileName;
    cout << "Numele histogramelor din fisierele root ('Edep', din codul Geant4 in run.cc):\n     "; cin >> histoName;
    cout << "\n   ATENTIE: trebuie sa fie doar 1 histograma per fisier root !" << endl << endl;


    // Loop pe toate fisierele root cu cate 1 histograma fiecare
    // Se incarca histograma totala in combinedHisto, daca intr-o simulare sunt mai multe Run-uri
    for(int i=0; i<num; ++i)
    {
        TFile *files = TFile::Open((rootFileName + std::to_string(i) + ".root").c_str());
        if(!files) { return 1; }

        TH1F *histograms = (TH1F*)files->Get(histoName.c_str());  //numele histogramelor din fiecare fisier root
        if(!histograms)
        {
            cout << "\nEROARE: Nu s-a gasit histograma " << histoName << endl;
            return 1;
        }
        //else { histograms->Print(); }  //printeaza info generale din histograma curenta

        if(!combinedHisto)
        {
            combinedHisto = (TH1F*)histograms->Clone("combinedHisto");
            combinedHisto->SetDirectory(0);
        }
        else { combinedHisto->Add(histograms); }

        files->Close();
    }


    // Crearea unui fisier root cu histograma combinedHisto
    if(combinedHisto && num>1)
    {
        TFile outputFile("output_final.root", "RECREATE");
        combinedHisto->Write();
        outputFile.Close();
    }

    // Umplerea unui fisier text cu datele din combinedHisto
    string a;
    cout << "Incarcati datele din histograma finala intr-un fisier text? (da/nu): "; cin >> a;

    if(a=="da" || a=="yes" || a=="y")
    {
        fstream ofile;
        ofile.open("spectru_final.txt", ios::out);

        for(int i=1; i<=combinedHisto->GetNbinsX(); ++i)
        {
            ofile << i << " " << combinedHisto->GetBinContent(i) << " " << combinedHisto->GetBinError(i) << endl;
        }

        ofile.close();
    }

    // Integrala fotopicului si FEPE
    cout << "Se calculeaza eficacitatea absoluta de fotopic? (da/nu): "; cin >> a;
    if(a == "da" || a == "yes" || a == "y")
    {
        int nbins, bin_st, bin_dr, nr_particule;  // stanga si dreapta binilor de integrare
        double bin1_min, bin1_max, e_st, e_dr, bin_err, bin_width, sum=0;

        nbins = combinedHisto->GetNbinsX();
        // bin1_min si bin1_max sunt capetele primului bin
        bin1_min = combinedHisto->GetBinLowEdge(1);
        bin1_max = combinedHisto->GetBinLowEdge(2);
        bin_width = bin1_max-bin1_min;

        cout << "\nNr. de particule simulate: "; cin >> nr_particule;
        cout << "\nNr. de bini ai histogramei: " << nbins << "\nGrosime bin: " << bin_width << " [keV]" << endl;
        cout << "Intervalul de energii pe care se integreaza, in [keV]:" << endl;
        cout << "     E_stanga  = "; cin >> e_st;
        cout << "     E_dreapta = "; cin >> e_dr;

        // Daca bin_width=2 si e_st sau e_dr=6 atunci 6 apartine binului 6/2=3
        // Daca e_st sau e_dr=7 atunci 7 apartine binului 7/2+1=4
        if(e_st == (e_st/bin_width)*bin_width)
        {
            bin_st = e_st/bin_width;
        }
        else { bin_st = e_st/bin_width+1; }

        if(e_dr == (e_dr/bin_width)*bin_width)
        {
            bin_dr = e_dr/bin_width;
        }
        else { bin_dr = e_dr/bin_width+1; }


        for(int i=1; i<=combinedHisto->GetNbinsX(); ++i)  // parcurgere de la bin 1 la numar total de bini
        {
            if(i>=bin_st && i<=bin_dr)
            {
                bin_err = combinedHisto->GetBinError(i);
                sum += bin_err*bin_err;
            }
        }
        sum = TMath::Sqrt(sum);

        cout << "\nAria calculata si eficacitatea de detectie absoluta in intervalul ales:" << endl;
        cout << "     Arie = " << combinedHisto->Integral(bin_st, bin_dr) << " +/- " << sum << " [counts]" << endl;
        cout << "     Eficacitate_detectie(deltaE) = " << combinedHisto->Integral(bin_st, bin_dr) / nr_particule << " +/- " << sum / nr_particule << endl;
    }




    // Reprezentare grafica
    combinedHisto->SetTitle("Spectru gama detector HPGe LMRI");
    combinedHisto->GetXaxis()->SetTitle("Energy [keV]");
    combinedHisto->GetYaxis()->SetTitle("Counts");
    combinedHisto->Draw("hsit");
    c1->Update();

    return 0;
}
