#include <iostream>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void print_menu() {
    std::cout << "=== Order Form ===" << std::endl;
    std::cout << "Enter your name: ";
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[1024] = {0};
    std::string name, date;
    float amount;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    print_menu();
    std::getline(std::cin, name);

    std::cout << "Enter order amount: ";
    std::cin >> amount;
    std::cin.ignore();  // Игнорировать оставшийся символ новой строки

    std::cout << "Enter order date (YYYY-MM-DD): ";
    std::getline(std::cin, date);

    std::string order = name + "|" + std::to_string(amount) + "|" + date;
    sendto(sockfd, order.c_str(), order.length(), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));

    socklen_t len = sizeof(servaddr);
    int n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&servaddr, &len);
    buffer[n] = '\0';
    std::cout << "Server response: " << buffer << std::endl;

    close(sockfd);
    return 0;
}
