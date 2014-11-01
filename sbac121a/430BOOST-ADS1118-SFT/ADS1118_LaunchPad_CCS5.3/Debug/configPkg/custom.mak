## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e430 linker.cmd package/cfg/main_pe430.oe430

linker.cmd: package/cfg/main_pe430.xdl
	$(SED) 's"^\"\(package/cfg/main_pe430cfg.cmd\)\"$""\"C:/github/reflow-toaster/sbac121a/430BOOST-ADS1118-SFT/ADS1118_LaunchPad_CCS5.3/Debug/configPkg/\1\""' package/cfg/main_pe430.xdl > $@
