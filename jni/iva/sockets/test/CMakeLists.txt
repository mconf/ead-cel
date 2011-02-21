
INCLUDE_DIRECTORIES(${EadCel_SOURCE_DIR} ${EadCel_SOURCE_DIR}/common ${EadCel_SOURCE_DIR}/thread ${EadCel_SOURCE_DIR}/sockets)

ADD_EXECUTABLE(socketsTest 
#gtest_igmp.cpp
#gtest_icmp.cpp
#gtest_multicastRecv.cpp
#gtest_multicastSend.cpp
#gtest_tcp.cpp
#gtest_tcpClient.cpp
#gtest_tcpServer.cpp
gtest_udp.cpp
#gtest_udpRecv.cpp
#gtest_udpSend.cpp
gtest_main.cpp
)

TARGET_LINK_LIBRARIES(socketsTest sockets common thread rt pthread gtest pcap)

