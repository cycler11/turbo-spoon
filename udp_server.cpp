#include <iostream>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <fstream>
#include <sstream>

void save_order(const std::string &name, float amount, const std::string &date) {
    std::ofstream file("orders.txt", std::ios::app);
    if (file.is_open()) {
        file << name << "|" << amount << "|" << date << "\n";
        file.close();
    }
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    socklen_t len = sizeof(cliaddr);
    int n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&cliaddr, &len);
    buffer[n] = '\0';
    std::cout << "Received: " << buffer << std::endl;

    // Простой парсинг данных
    std::string order_data(buffer);
    std::stringstream ss(order_data);
    std::string name, date;
    float amount;
    char delimiter;

    ss >> name >> delimiter >> amount >> delimiter >> date;
    
    save_order(name, amount, date);

    const char *response = "Order received and saved!";
    sendto(sockfd, response, strlen(response), 0, (struct sockaddr*)&cliaddr, len);

    close(sockfd);
    return 0;
}
