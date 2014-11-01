# invoke SourceDir generated makefile for main.pe430
main.pe430: .libraries,main.pe430
.libraries,main.pe430: package/cfg/main_pe430.xdl
	$(MAKE) -f C:\github\reflow-toaster\sbac121a\430BOOST-ADS1118-SFT\ADS1118_LaunchPad_CCS5.3/src/makefile.libs

clean::
	$(MAKE) -f C:\github\reflow-toaster\sbac121a\430BOOST-ADS1118-SFT\ADS1118_LaunchPad_CCS5.3/src/makefile.libs clean

