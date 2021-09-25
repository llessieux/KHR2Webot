#
# Standard Makefile for a Webots controller
#
# Author: Olivier.Michel@cyberbotics.com
# Date:   August 29th, 2006.
#
CPP_SOURCES=khr2.cpp rcb3_simulator.cpp KHR2_Interface.cpp KHR2_Data.cpp

ifndef WEBOTS_HOME_PATH
WEBOTS_HOME_PATH=$(WEBOTS_HOME)
endif

CFLAGS=`wx-config --cflags`
LIBRARIES=`wx-config --libs`

include $(WEBOTS_HOME_PATH)/projects/default/controllers/Makefile.include
