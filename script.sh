cd bindMEG3/
g++ --std=c++11 bindMeg3WithProbability.cpp -o bindMEG3
./bindMEG3
cd ../
sudo triplexator/bin/triplexator -l 10 -fm 0 -of 1 -od MEG3WithBkg -o triplexMEG3andBkg.tpx -ss data/_MEG3.fna -ds data/_bkg.fna
sudo triplexator/bin/triplexator -l 10 -fm 0 -of 1 -od MEG3WithPeaks -o triplexMEG3andPeaks.tpx -ss data/_MEG3.fna -ds data/_MEG3.peaks_wo_N.fna
sudo triplexator/bin/triplexator -l 10 -fm 0 -of 1 -od UnpairedSitesMEG3WithBkg -o triplexUnpairedSitesMEG3andBkg.tpx -ss bindMEG3/MEG3sites -ds data/_bkg.fna
sudo triplexator/bin/triplexator -l 10 -fm 0 -of 1 -od UnpairedSitesMEG3WithPeaks -o triplexUnpairedSitesMEG3andPeaks.tpx -ss bindMEG3/MEG3sites -ds data/_MEG3.peaks_wo_N.fna
cd resultForMEG3
g++ --std=c++11 getDataForROC.cpp -o getAUC
./getAUC
cd ../resultForSitesMeg3
g++ --std=c++11 getDataForROC.cpp -o getAUC 
./getAUC
cd ../