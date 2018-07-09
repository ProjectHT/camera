#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Camera.o \
	${OBJECTDIR}/Clip.o \
	${OBJECTDIR}/HTTPRequest.o \
	${OBJECTDIR}/InfoCamera.o \
	${OBJECTDIR}/InfoVision.o \
	${OBJECTDIR}/Vision.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread -ldl `pkg-config --libs libavcodec-ffmpeg` `pkg-config --libs libavformat-ffmpeg` `pkg-config --libs libavutil-ffmpeg` `pkg-config --libs libswresample-ffmpeg` `pkg-config --libs libswscale-ffmpeg` `pkg-config --libs opencv`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/camera

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/camera: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/camera ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Camera.o: Camera.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags libavcodec-ffmpeg` `pkg-config --cflags libavformat-ffmpeg` `pkg-config --cflags libavutil-ffmpeg` `pkg-config --cflags libswresample-ffmpeg` `pkg-config --cflags libswscale-ffmpeg` `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Camera.o Camera.cpp

${OBJECTDIR}/Clip.o: Clip.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags libavcodec-ffmpeg` `pkg-config --cflags libavformat-ffmpeg` `pkg-config --cflags libavutil-ffmpeg` `pkg-config --cflags libswresample-ffmpeg` `pkg-config --cflags libswscale-ffmpeg` `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Clip.o Clip.cpp

${OBJECTDIR}/HTTPRequest.o: HTTPRequest.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags libavcodec-ffmpeg` `pkg-config --cflags libavformat-ffmpeg` `pkg-config --cflags libavutil-ffmpeg` `pkg-config --cflags libswresample-ffmpeg` `pkg-config --cflags libswscale-ffmpeg` `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/HTTPRequest.o HTTPRequest.cpp

${OBJECTDIR}/InfoCamera.o: InfoCamera.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags libavcodec-ffmpeg` `pkg-config --cflags libavformat-ffmpeg` `pkg-config --cflags libavutil-ffmpeg` `pkg-config --cflags libswresample-ffmpeg` `pkg-config --cflags libswscale-ffmpeg` `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InfoCamera.o InfoCamera.cpp

${OBJECTDIR}/InfoVision.o: InfoVision.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags libavcodec-ffmpeg` `pkg-config --cflags libavformat-ffmpeg` `pkg-config --cflags libavutil-ffmpeg` `pkg-config --cflags libswresample-ffmpeg` `pkg-config --cflags libswscale-ffmpeg` `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InfoVision.o InfoVision.cpp

${OBJECTDIR}/Vision.o: Vision.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags libavcodec-ffmpeg` `pkg-config --cflags libavformat-ffmpeg` `pkg-config --cflags libavutil-ffmpeg` `pkg-config --cflags libswresample-ffmpeg` `pkg-config --cflags libswscale-ffmpeg` `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vision.o Vision.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags libavcodec-ffmpeg` `pkg-config --cflags libavformat-ffmpeg` `pkg-config --cflags libavutil-ffmpeg` `pkg-config --cflags libswresample-ffmpeg` `pkg-config --cflags libswscale-ffmpeg` `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
