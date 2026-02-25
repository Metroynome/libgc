all: clean
	$(MAKE) -f ${CURDIR}/Makefile.ntsc
	$(MAKE) -f ${CURDIR}/Makefile.ntsc clean

	
clean:
	$(MAKE) -f ${CURDIR}/Makefile.ntsc clean
	rm -f -r lib/

install: clean
	$(MAKE) -f ${CURDIR}/Makefile.ntsc install
	$(MAKE) -f ${CURDIR}/Makefile.ntsc clean
	