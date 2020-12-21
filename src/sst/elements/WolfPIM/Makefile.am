# -*- Makefile -*-
#
#


EXTRA_DIST = 

compdir = $(pkglibdir)
comp_LTLIBRARIES = libWolfPIM.la

libWolfPIM_la_SOURCES = \
	WolfPIM.cc \
	WolfPIM.h 

libWolfPIM_la_CPPFLAGS = $(MPI_CPPFLAGS) \
	$(LIBPHX_CPPFLAGS) -I$(top_srcdir)/src
libWolfPIM_la_LDFLAGS = -module -avoid-version \
	$(LIBPHX_LDFLAGS) $(LIBPHX_LIBDIR)
libWolfPIM_la_LIBADD = $(LIBPHX_LIB)

install-exec-hook:
	$(SST_REGISTER_TOOL) SST_ELEMENT_SOURCE     WolfPIM=$(abs_srcdir)
	$(SST_REGISTER_TOOL) SST_ELEMENT_TESTS      WolfPIM=$(abs_srcdir)/tests
