
ADD_LIBRARY(sockets STATIC 
Igmp.cpp
IgmpSender.cpp
IgmpPcap.cpp
#Icmp.cpp
NetworkInformation_linux.cpp
NetworkInformation.cpp
Socket.cpp
SocketCtx.cpp
SocketRaw.cpp
SocketException.cpp
SocketTCP.cpp
SocketUDP.cpp
SocketWrapper.cpp
)
INCLUDE_DIRECTORIES(${EadCel_SOURCE_DIR} ${EadCel_SOURCE_DIR}/common ${EadCel_SOURCE_DIR}/thread ${EadCel_SOURCE_DIR}/sockets)
TARGET_LINK_LIBRARIES(sockets)

ADD_SUBDIRECTORY(test)