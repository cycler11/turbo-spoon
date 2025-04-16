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
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    std::string name, date;
    float amount;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    print_menu();
    std::getline(std::cin, name);

    std::cout << "Enter order amount: ";
    std::cin >> amount;
    std::cin.ignore();  

    std::cout << "Enter order date (YYYY-MM-DD): ";
    std::getline(std::cin, date);

    std::string order = name + "|" + std::to_string(amount) + "|" + date;
    send(sock, order.c_str(), order.length(), 0);

    read(sock, buffer, 1024);
    std::cout << "Server response: " << buffer << std::endl;

    close(sock);
    return 0;
}
