CXX=g++
CXXFLAGS=-Wall -Wextra

all: tcp_server tcp_client udp_server udp_client

tcp_server: tcp_server.cpp
	$(CXX) $(CXXFLAGS) -o tcp_server tcp_server.cpp

tcp_client: tcp_client.cpp
	$(CXX) $(CXXFLAGS) -o tcp_client tcp_client.cpp

udp_server: udp_server.cpp
	$(CXX) $(CXXFLAGS) -o udp_server udp_server.cpp

udp_client: udp_client.cpp
	$(CXX) $(CXXFLAGS) -o udp_client udp_client.cpp

clean:
	rm -f tcp_server tcp_client udp_server udp_client
