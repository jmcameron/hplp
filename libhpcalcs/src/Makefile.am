## Process this file with automake to produce Makefile.in

AM_CFLAGS = -Wall -W

SUBDIRS = 

# libraries and files to compile and install
lib_LTLIBRARIES = libhpcalcs.la
libhpcalcs_includedir = $(includedir)/hplp
libhpcalcs_include_HEADERS = \
	hplibs.h export.h hpfiles.h hpcables.h hpcalcs.h hpopers.h \
	filetypes.h typesprime.h \
	prime_cmd.h

# build instructions
libhpcalcs_la_CPPFLAGS = -I$(top_srcdir)/intl \
	-DLOCALEDIR=\"$(datadir)/locale\" \
	@HIDAPI_CFLAGS@ \
	-DHPCALCS_EXPORTS
#	@HPCABLES_CFLAGS@ @HPFILES_CFLAGS@

if OS_WIN32
libhpcalcs_la_DEPENDENCIES = ../build/mingw/hpcalcs-rc.o
libhpcalcs_la_LDFLAGS = -no-undefined -version-info @LT_LIBVERSION@ -Wl,../build/mingw/hpcalcs-rc.o -lintl
libhpcalcs_la_LIBADD = $(LIBINTL) \
	@HIDAPI_LIBS@ -lintl
#	@HPCABLES_LIBS@ @HPFILES_LIBS@
else
libhpcalcs_la_LDFLAGS = -no-undefined -version-info @LT_LIBVERSION@
libhpcalcs_la_LIBADD = $(LIBINTL) \
	@HIDAPI_LIBS@
#	@HPCABLES_LIBS@ @HPFILES_LIBS@
endif

libhpcalcs_la_SOURCES = *.h \
	hpfiles.c hpcables.c hpcalcs.c hpopers.c \
	error.c logging.c utils.c type2str.c \
	filetypes.c typesprime.c \
	link_prime_hid.c link_nul.c \
	prime_rpkt.c prime_vpkt.c prime_cmd.c calc_prime.c \
	calc_none.c
