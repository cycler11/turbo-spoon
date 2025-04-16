#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>

void save_order(const std::string &name, float amount, const std::string &date) {
    std::ofstream file("orders.txt", std::ios::app);
    if (file.is_open()) {
        file << name << "|" << amount << "|" << date << "\n";
        file.close();
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    char buffer[1024] = {0};
    int opt = 1;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);
    client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

    read(client_fd, buffer, 1024);
    std::cout << "Received: " << buffer << std::endl;


    std::string order_data(buffer);
    std::stringstream ss(order_data);
    std::string name, date;
    float amount;
    char delimiter;

    ss >> name >> delimiter >> amount >> delimiter >> date;
    
    save_order(name, amount, date);

    const char *response = "Order received and saved!";
    send(client_fd, response, strlen(response), 0);

    close(client_fd);
    close(server_fd);
    return 0;
}
