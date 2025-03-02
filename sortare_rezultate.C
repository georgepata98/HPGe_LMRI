{
    int len=0, card_distance=0, min=0, auxx=0, index=0;  // card_distance = nr. distante diferite
    double a, b, c, d;
    vector<double> distance, energy, fepe, ufepe;  // parametrii initiali din fisierul rezultate_fepe.txt
    vector<double> sort_distance1, sort_energy1, sort_fepe1, sort_ufepe1;  // parametrii sortati dupa cresterea distantei
    vector<double> sort_distance2, sort_energy2, sort_fepe2, sort_ufepe2;  // parametrii sortati dupa cresterea energiei
    vector<double> dist;
    vector<int> card_energy;  // nr. energii diferite per distanta diferita
    string prima_linie;
    ifstream ifile;  // fisier de input cu datele simulate
    ofstream ofile;  // fisier de output cu datele sortate


    ifile.open("rezultate_fepe.txt");
    getline(ifile, prima_linie);  // ia prima linie cu numele coloanelor (pentru a sari peste ea in loop-ul while)
    while(1)
    {
        ifile >> a >> b >> c >> d;
        if(ifile.eof()) break;
        distance.push_back(a);
        energy.push_back(b);
        fepe.push_back(c);
        ufepe.push_back(d);
        // cout << "v[" << len << "]:  " << distance[len] << " " << energy[len] << " " << fepe[len] << " " << ufepe[len] << endl;
        len++;
    }
    ifile.close();
    cout << "\nNumar total de FEPE simulate: " << len << endl;



    // Gasirea distantei minime si a nr. de distante diferite
    for(int i=0; i<len; i++)
    {
        for(int j=0; j<len; j++)
        {
            if(distance[i] <= distance[j])
            {
                min++;
            }
            if(i==0 && j==0)
            {
                dist.push_back(distance[i]);
                card_distance++;
            }
            for(int k=0; k<dist.size(); k++)
            {
                if(distance[j] != dist[k])
                {
                    auxx++;
                }
            }
            if(auxx == dist.size())
            {
                dist.push_back(distance[j]);
                card_distance++;
            }
            auxx=0;
        }
        if(min == len)
        {
            sort_distance1.push_back(distance[i]);
            sort_energy1.push_back(energy[i]);
            sort_fepe1.push_back(fepe[i]);
            sort_ufepe1.push_back(ufepe[i]);
        }
        min=0;
    }
    cout << "Numar distante diferite: " << card_distance << endl;


    for(int i=0; i<card_distance; i++)
    {
        card_energy.push_back(0);  // initializam cu 0 pe toate card_energy[i]
        // cout << card_energy[i] << endl;
    }


    // Prima sortare - dupa cresterea distantei
    while(1)
    {
        int aux = sort_distance1.size();
        if(aux == len) break;
        for(int i=0; i<len; i++)
        {
            for(int j=0; j<len; j++)
            {
                if(distance[i] <= distance[j])
                {
                    min++;
                }
            }
            if(min == len - aux)
            {
                sort_distance1.push_back(distance[i]);
                sort_energy1.push_back(energy[i]);
                sort_fepe1.push_back(fepe[i]);
                sort_ufepe1.push_back(ufepe[i]);
            }
            min=0;
        }
    }


    // Calcularea numarului de energii diferite la fiecare distanta
    for(int i=0; i<len; i++)
    {
        if(i>0)
        {
            if(sort_distance1[i] != sort_distance1[i-1])
            {
                for(int j=0; j<len; j++)
                {
                    if(sort_distance1[i-1] == sort_distance1[j])
                    {
                        if(sort_energy1[i-1] != sort_energy1[j])
                        {
                            card_energy[index]++;
                        }
                    }
                }
                card_energy[index]++;
                // cout << "Numar energii diferite la distanta " << sort_distance1[i-1] << ": " << card_energy[index] << endl;
                index++;
            }
        }
        if(i == len-1)
        {
            for(int j=0; j<len; j++)
            {
                if(sort_distance1[i] == sort_distance1[j])
                {
                    if(sort_energy1[i] != sort_energy1[j])
                    {
                        card_energy[index]++;
                    }
                }
            }
            card_energy[index]++;
            // cout << "Numar energii diferite la distanta " << sort_distance1[i] << ": " << card_energy[index] << endl;
            index++;
        }
    }


    // Sortarea finala - dupa cresterea energiei
    auxx = 0;
    for(int index=0; index<card_energy.size(); index++)
    {
        while(1)
        {
            int aux = 0;
            if(aux == card_energy[index]) break;
            for(int i=auxx; i<(auxx+card_energy[index]); i++)
            {
                for(int j=auxx; j<(auxx+card_energy[index]); j++)
                {
                    if(sort_distance1[i] == sort_distance1[j])
                    {
                        if(sort_energy1[i] <= sort_energy1[j])
                        {
                            min++;
                        }
                    }
                }
                if(min == card_energy[index])
                {
                    sort_distance2.push_back(sort_distance1[i]);
                    sort_energy2.push_back(sort_energy1[i]);
                    sort_fepe2.push_back(sort_fepe1[i]);
                    sort_ufepe2.push_back(sort_ufepe1[i]);
                }
            }
        }
        auxx += card_energy[index];
    }



    return 0;
}