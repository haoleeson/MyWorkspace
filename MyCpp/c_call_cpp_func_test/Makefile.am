# Makefile.am -- Process this file with automake to produce Makefile.in
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

INCLUDES = -I $(top_srcdir)

# AUTOMAKE_OPTION = foreign

# AM_CPPFLAGS = -I$(top_srcdir) -I$(srcdir)/../../hiredis/hiredis-0.14.0/debian/libhiredis-dev/usr/include -I$(top_srcdir) -I$(srcdir)/../common
AM_CPPFLAGS = -I$(top_srcdir)

# lib_LTLIBRARIES = libswsscommon.la

# INCLUDES = -I$(top_srcdir) -I$(srcdir)/../common \
#            -I$(srcdir)/../../hiredis/hiredis-0.14.0/debian/libhiredis-dev/usr/include

# SWSS_COMMON_DIR = ../common
# AM_CXXFLAGS = -I${SWSS_COMMON_DIR}

# CFLAGS_REDIS = -I$(srcdir)/../../hiredis/hiredis-0.14.0/debian/libhiredis-dev/usr/include
# CFLAGS_COMMON = -I$(top_srcdir) -I$(srcdir)/../common
# LIBNL_LIBS = -lnl-genl-3 -lnl-route-3 -lnl-3
LIBNL_CFLAGS = -I/usr/include/libnl3

# SWSS_COMMON_LIB = -L$(srcdir)/../common -lswsscommon


bin_PROGRAMS = mainexe

if DEBUG
DBGFLAGS = -g -DNDEBUG
else
DBGFLAGS = -ggdb -DDEBUG
endif

mainexe_SOURCES =                        \
        common_data_definition.cpp          \
        logctl_access_redis.cpp          \
        wrapper.cpp         \
        teamd.c       \
        main.c

mainexe_CFLAGS = $(DBGFLAGS) $(AM_CFLAGS) $(CFLAGS_REDIS) $(CFLAGS_COMMON) $(LIBNL_CFLAGS)
mainexe_CPPFLAGS = $(DBGFLAGS) $(AM_CPPFLAGS) $(CFLAGS_REDIS) $(CFLAGS_COMMON) $(LIBNL_CPPFLAGS)

mainexe_LDADD =  -lpthread $(LIBNL_LIBS)
