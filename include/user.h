#ifndef USER_H
#define USER_H

#include <iostream>
#include "message.h"
#include "crypto.h"
#include "server.h"

class Server;

class User
{
public:
    User(const std::string& _username, const std::string& _private_key, Server* _server);
    const std::string& get_username() const;
    bool send_text_message(const std::string& _text, const std::string& _receiver);
    bool send_voice_message(const std::string& _receiver);
private:
    std::string username;     // username of the user
    std::string private_key;  // private key of the user
    Server* const server;     // a pointer to the server for communications
};


#endif //USER_H