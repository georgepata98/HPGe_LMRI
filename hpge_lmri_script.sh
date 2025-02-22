for i in {0..20}; do
    echo "Distanta sursa-detector $i [cm]"
    sed -i "6i /gps/pos/centre 0 0 $i cm" ../macros/gps.mac
    sed -i "7d" ../macros/gps.mac  # stergere fosta linia 6 devenita 7
    if [ $i -ge 0 ] && [ $i -le 5 ]; then
        sed -i "21i unsigned long long int totalEvents = 2000000;" ../main.cc
        sed -i "22d" ../main.cc
    fi
    if [ $i -ge 6 ] && [ $i -le 10 ]; then
        sed -i "21i unsigned long long int totalEvents = 6000000;" ../main.cc
        sed -i "22d" ../main.cc
    fi
    if [ $i -ge 11 ] && [ $i -le 15 ]; then
        sed -i "21i unsigned long long int totalEvents = 20000000;" ../main.cc
        sed -i "22d" ../main.cc
    fi
    if [ $i -ge 16 ] && [ $i -le 20 ]; then
        sed -i "21i unsigned long long int totalEvents = 60000000;" ../main.cc
        sed -i "22d" ../main.cc
    fi
    for j in {1..28}; do
        if [ $j -eq 1 ]; then
            sed -i "11i /gps/ene/mono 40 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=44;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=40
        fi
        if [ $j -eq 2 ]; then
            sed -i "11i /gps/ene/mono 60 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=66;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=60
        fi
        if [ $j -eq 3 ]; then
            sed -i "11i /gps/ene/mono 80 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=88;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=80
        fi
        if [ $j -eq 4 ]; then
            sed -i "11i /gps/ene/mono 100 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=110;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=100
        fi
        if [ $j -eq 5 ]; then
            sed -i "11i /gps/ene/mono 120 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=132;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=120
        fi
        if [ $j -eq 6 ]; then
            sed -i "11i /gps/ene/mono 130 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=143;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=130
        fi
        if [ $j -eq 7 ]; then
            sed -i "11i /gps/ene/mono 140 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=154;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=140
        fi
        if [ $j -eq 8 ]; then
            sed -i "11i /gps/ene/mono 150 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=165;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=150
        fi
        if [ $j -eq 9 ]; then
            sed -i "11i /gps/ene/mono 200 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=220;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=200
        fi
        if [ $j -eq 10 ]; then
            sed -i "11i /gps/ene/mono 220 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=242;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=220
        fi
        if [ $j -eq 11 ]; then
            sed -i "11i /gps/ene/mono 240 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=264;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=240
        fi
        if [ $j -eq 12 ]; then
            sed -i "11i /gps/ene/mono 260 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=286;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=260
        fi
        if [ $j -eq 13 ]; then
            sed -i "11i /gps/ene/mono 280 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=308;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=280
        fi
        if [ $j -eq 14 ]; then
            sed -i "11i /gps/ene/mono 300 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=330;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=300
        fi
        if [ $j -eq 15 ]; then
            sed -i "11i /gps/ene/mono 350 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=385;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=350
        fi
        if [ $j -eq 16 ]; then
            sed -i "11i /gps/ene/mono 400 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=440;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=400
        fi
        if [ $j -eq 17 ]; then
            sed -i "11i /gps/ene/mono 450 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=495;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=450
        fi
        if [ $j -eq 18 ]; then
            sed -i "11i /gps/ene/mono 500 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=550;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=500
        fi
        if [ $j -eq 19 ]; then
            sed -i "11i /gps/ene/mono 600 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=660;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=600
        fi
        if [ $j -eq 20 ]; then
            sed -i "11i /gps/ene/mono 700 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=770;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=700
        fi
        if [ $j -eq 21 ]; then
            sed -i "11i /gps/ene/mono 800 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=880;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=800
        fi
        if [ $j -eq 22 ]; then
            sed -i "11i /gps/ene/mono 900 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=990;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=900
        fi
        if [ $j -eq 23 ]; then
            sed -i "11i /gps/ene/mono 1000 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=1100;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=1000
        fi
        if [ $j -eq 24 ]; then
            sed -i "11i /gps/ene/mono 1100 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=1210;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=1100
        fi
        if [ $j -eq 25 ]; then
            sed -i "11i /gps/ene/mono 1200 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=1320;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=1200
        fi
        if [ $j -eq 26 ]; then
            sed -i "11i /gps/ene/mono 1300 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=1430;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=1300
        fi
        if [ $j -eq 27 ]; then
            sed -i "11i /gps/ene/mono 1400 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=1540;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=1400
        fi
        if [ $j -eq 28 ]; then
            sed -i "11i /gps/ene/mono 1600 keV" ../macros/gps.mac
            sed -i "43i G4int nbins, e0=0, e1=1760;" ../include/run.hh
            sed -i "44d" ../include/run.hh
            energy=1600
        fi
        sed -i "12d" ../macros/gps.mac  # stergere fosta linie 11
        cmake ..
        make -j8
        ./sim
        rm "checkpoint_Run0.txt" "sim"
        mv "histogram_Run0.root" ../results
        cd "../results"
        mv "histogram_Run0.root" "hpge_${i}cm_${energy}kev_Run0.root"
        cd "../build"
        sleep 3
    done
    sleep 3
done
