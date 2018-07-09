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
	${OBJECTDIR}/Http/HTTPRequest.o \
	${OBJECTDIR}/Vision/Camera.o \
	${OBJECTDIR}/Vision/Clip.o \
	${OBJECTDIR}/Vision/InfoCamera.o \
	${OBJECTDIR}/Vision/InfoVision.o \
	${OBJECTDIR}/Vision/Photo.o \
	${OBJECTDIR}/Vision/Vision.o \
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

${OBJECTDIR}/Http/HTTPRequest.o: Http/HTTPRequest.cpp
	${MKDIR} -p ${OBJECTDIR}/Http
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags libavcodec-ffmpeg` `pkg-config --cflags libavformat-ffmpeg` `pkg-config --cflags libavutil-ffmpeg` `pkg-config --cflags libswresample-ffmpeg` `pkg-config --cflags libswscale-ffmpeg` `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Http/HTTPRequest.o Http/HTTPRequest.cpp

${OBJECTDIR}/Vision/Camera.o: Vision/Camera.cpp
	${MKDIR} -p ${OBJECTDIR}/Vision
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags libavcodec-ffmpeg` `pkg-config --cflags libavformat-ffmpeg` `pkg-config --cflags libavutil-ffmpeg` `pkg-config --cflags libswresample-ffmpeg` `pkg-config --cflags libswscale-ffmpeg` `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vision/Camera.o Vision/Camera.cpp

${OBJECTDIR}/Vision/Clip.o: Vision/Clip.cpp
	${MKDIR} -p ${OBJECTDIR}/Vision
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags libavcodec-ffmpeg` `pkg-config --cflags libavformat-ffmpeg` `pkg-config --cflags libavutil-ffmpeg` `pkg-config --cflags libswresample-ffmpeg` `pkg-config --cflags libswscale-ffmpeg` `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vision/Clip.o Vision/Clip.cpp

${OBJECTDIR}/Vision/InfoCamera.o: Vision/InfoCamera.cpp
	${MKDIR} -p ${OBJECTDIR}/Vision
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags libavcodec-ffmpeg` `pkg-config --cflags libavformat-ffmpeg` `pkg-config --cflags libavutil-ffmpeg` `pkg-config --cflags libswresample-ffmpeg` `pkg-config --cflags libswscale-ffmpeg` `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vision/InfoCamera.o Vision/InfoCamera.cpp

${OBJECTDIR}/Vision/InfoVision.o: Vision/InfoVision.cpp
	${MKDIR} -p ${OBJECTDIR}/Vision
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags libavcodec-ffmpeg` `pkg-config --cflags libavformat-ffmpeg` `pkg-config --cflags libavutil-ffmpeg` `pkg-config --cflags libswresample-ffmpeg` `pkg-config --cflags libswscale-ffmpeg` `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vision/InfoVision.o Vision/InfoVision.cpp

${OBJECTDIR}/Vision/Photo.o: Vision/Photo.cpp
	${MKDIR} -p ${OBJECTDIR}/Vision
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags libavcodec-ffmpeg` `pkg-config --cflags libavformat-ffmpeg` `pkg-config --cflags libavutil-ffmpeg` `pkg-config --cflags libswresample-ffmpeg` `pkg-config --cflags libswscale-ffmpeg` `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vision/Photo.o Vision/Photo.cpp

${OBJECTDIR}/Vision/Vision.o: Vision/Vision.cpp
	${MKDIR} -p ${OBJECTDIR}/Vision
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags libavcodec-ffmpeg` `pkg-config --cflags libavformat-ffmpeg` `pkg-config --cflags libavutil-ffmpeg` `pkg-config --cflags libswresample-ffmpeg` `pkg-config --cflags libswscale-ffmpeg` `pkg-config --cflags opencv` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vision/Vision.o Vision/Vision.cpp

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
