#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include "message.h"
#include "crypto.h"
#include "user.h"
#include <exception>
#include <algorithm>
#include <string>
#include <set>


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
    std::vector<Message*> get_all_messages_from(const std::string& username) const;
    std::vector<Message*> get_all_messages_to(const std::string& username) const;
    std::vector<Message*> get_chat(const std::string& user1, const std::string& user2) const;

    // static inline void sort_msgs(std::vector<Message*> msgs)
    // {
    //     static std::map<Message, long long int> m;
    //     int n {0};

    //     std::generate(msgs.begin(), msgs.end(), [msgs, &n, &m]() {
    //         std::string time = msgs[n]->get_time().substr((msgs[n]->get_time().end())-16, 11);
            
    //         std::string sec = time.substr(time.end()-2, 2);
    //         std::string min = time.substr(time.end()-5, 2);
    //         std::string hour = time.substr(time.end()-8, 2);
    //         std::string newtime = hour + min + sec;
    //         long long int newtime_i = std::stoi(newtime);
    //         m[*msgs[n]] = newtime_i;
    //         n++;});

    //     ...
    // };
    
private:
    std::vector<User> users;                        // to store our users
    std::map<std::string, std::string> public_keys; // map usernames to their publickeys
    std::vector<Message*> messages;                 // to store all the messages sent by users
};


#endif //SERVER_H