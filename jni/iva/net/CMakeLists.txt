
ADD_LIBRARY(net STATIC 
NetHeader.cpp
NetHeaderAttr.cpp
NetHeaderAudio.cpp
NetHeaderVideo.cpp
NetPacket.cpp
NetQueue.cpp
NetQueueItem.cpp
NetRecv.cpp
NetRecvValidator.cpp
NetRedir.cpp
NetRedirItem.cpp
NetSend.cpp
NetStatistics.cpp
NetStorage.cpp
)
INCLUDE_DIRECTORIES(${EadCel_SOURCE_DIR} ${EadCel_SOURCE_DIR}/common ${EadCel_SOURCE_DIR}/thread ${EadCel_SOURCE_DIR}/sockets ${EadCel_SOURCE_DIR}/queue ${EadCel_SOURCE_DIR}/net)
TARGET_LINK_LIBRARIES(net)

ADD_SUBDIRECTORY(test)