#include <iostream>
#include <vector>
#include <thread>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

const int MAX_CLIENTS = 100;
const int BUFFER_SIZE = 1024;

struct client
{
    int socket_fd;
    string nickname;
};

vector<client> clients;

void broadcast_message(string message, int sender_socket)
{
    for (auto& c : clients)
    {
        if (c.socket_fd != sender_socket)
        {
            string output = "[" + c.nickname + "]: " + message;
            send(c.socket_fd, output.c_str(), output.length(), 0);
        }
    }
}

void handle_client_connection(int socket_fd)
{
    send(socket_fd, "Welcome to the chat room! Please enter your nickname: ", strlen("Welcome to the chat room! Please enter your nickname: "), 0);

    char buffer[BUFFER_SIZE];
    int bytes_received = recv(socket_fd, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received <= 0)
    {
        close(socket_fd);
        return;
    }

    buffer[bytes_received] = '\0';
    string nickname(buffer);

    client c;
    c.socket_fd = socket_fd;
    c.nickname = nickname;
    clients.push_back(c);

    string message = nickname + " has joined the chat room.";
    broadcast_message(message, socket_fd);

    while (true)
    {
        memset(buffer, 0, BUFFER_SIZE);
        bytes_received = recv(socket_fd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0)
        {
            close(socket_fd);

            for (auto it = clients.begin(); it != clients.end(); ++it)
            {
                if (it->socket_fd == socket_fd)
                {
                    string message = it->nickname + " has left the chat room.";
                    broadcast_message(message, -1);
                    clients.erase(it);
                    break;
                }
            }

            return;
        }

        buffer[bytes_received] = '\0';
        string message(buffer);

        message = nickname + ": " + message;
        broadcast_message(message, socket_fd);
    }
}

int main()
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8081);

    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    listen(server_socket, MAX_CLIENTS);

    cout << "[Server] Listening on port 8081..." << endl;

    while (true)
    {
        struct sockaddr_in client_address;
        socklen_t client_address_size = sizeof(client_address);

        int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);

        thread t(handle_client_connection, client_socket);
        t.detach();
    }

    close(server_socket);

    return 0;
}
