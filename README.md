# Triplex
## Сворачивание в структуру
https://www.tbi.univie.ac.at/RNA/RNAplfold.1.html

bindMEG3/startVienna.sh - этот скрипт запускает RNAplfold из пакета Vienna

NR_002766_basepairs - связынные участки MEG3

MEG3sites - неспаренные участки ДНК


## Образование триплексов
http://bioinformatics.org.au/tools/triplexator/index.html

Для получения триплексов между всей MEG3 и случайновыбранными участками ДНК(_bkg.fna)

	sudo triplexator -l 10 -fm 0 -of 1 -od MEG3WithBkg -o triplexMEG3andBkg.tpx -ss data/_MEG3.fna -ds data/_bkg.fna 

Для получения триплексов между всей MEG3 и участками ДНК, которые соответствуют MEG3 пикам (_MEG3.peaks_wo_N.fna )
	
	sudo triplexator -l 10 -fm 0 -of 1 -od MEG3WithPeaks -o triplexMEG3andPeaks.tpx -ss data/_MEG3.fna -ds data/_MEG3.peaks_wo_N.fna 

Для получения триплексов между неспаренными участками MEG3 и случайновыбранными участками ДНК(_bkg.fna)

	sudo triplexator -l 10 -fm 0 -of 1 -od UnpairedSitesMEG3WithBkg -o triplexUnpairedSitesMEG3andBkg.tpx -ss bindMEG3/MEG3sites -ds data/_bkg.fna 

Для получения триплексов между неспаренными участками MEG3и участками ДНК, которые соответствуют MEG3 пикам (_MEG3.peaks_wo_N.fna )

	sudo triplexator -l 10 -fm 0 -of 1 -od UnpairedSitesMEG3WithPeaks -o triplexUnpairedSitesMEG3andPeaks.tpx -ss bindMEG3/MEG3sites -ds data/_MEG3.peaks_wo_N.fna 


