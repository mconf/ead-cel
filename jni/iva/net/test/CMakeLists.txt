
INCLUDE_DIRECTORIES(${EadCel_SOURCE_DIR} ${EadCel_SOURCE_DIR}/common ${EadCel_SOURCE_DIR}/thread ${EadCel_SOURCE_DIR}/sockets ${EadCel_SOURCE_DIR}/queue ${EadCel_SOURCE_DIR}/net)

ADD_EXECUTABLE(netTest 
#gtest_fileTransferClient.cpp
#gtest_fileTransferServer.cpp
gtest_main.cpp
gtest_NetHeader.cpp
gtest_NetHeaderAttr.cpp
gtest_NetHeaderAudio.cpp
gtest_NetHeaderVideo.cpp
gtest_NetPacket.cpp
gtest_NetQueue.cpp
gtest_NetQueueItem.cpp
gtest_NetRecv.cpp
gtest_NetRecvAutomatic.cpp
gtest_NetSend.cpp
gtest_NetSendAndRecv.cpp
gtest_NetSendAutomatic.cpp
gtest_NetStatistics.cpp
gtest_NetStorage.cpp

)

TARGET_LINK_LIBRARIES(netTest net queue common thread sockets rt pthread gtest pcap)

