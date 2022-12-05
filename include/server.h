#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include "message.h"
#include "crypto.h"
#include "user.h"
#include <exception>

class User;

class Server
{
public:
    Server() = default;
    const std::vector<User>& get_users() const;
    const std::map<std::string, std::string>& get_public_keys() const;
    const std::vector<Message*>& get_messages() const;
    const User& create_user(const std::string& username);
    bool create_message(Message* msg, const std::string& signature);

private:
    std::vector<User> users;                        // to store our users
    std::map<std::string, std::string> public_keys; // map usernames to their publickeys
    std::vector<Message*> messages;                 // to store all the messages sent by users
};


#endif //SERVER_H