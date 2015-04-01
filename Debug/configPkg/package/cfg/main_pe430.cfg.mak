# invoke SourceDir generated makefile for main.pe430
main.pe430: .libraries,main.pe430
.libraries,main.pe430: package/cfg/main_pe430.xdl
	$(MAKE) -f C:\Users\ricardo\Dropbox\UFSM\CTISM\ccs_workspace\ir_transceiver/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\ricardo\Dropbox\UFSM\CTISM\ccs_workspace\ir_transceiver/src/makefile.libs clean

