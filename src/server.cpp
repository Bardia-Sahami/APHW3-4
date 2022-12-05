#include "server.h"

const std::vector<User>& Server::get_users() const
{
    return users;
}

const std::map<std::string, std::string>& Server::get_public_keys() const
{
    return public_keys;
}

const std::vector<Message*>& Server::get_messages() const
{
    return messages;
}

const User& Server::create_user(const std::string& username)
{
    size_t i {};
    for (i; i < users.size(); i++) {
        if (users[i].get_username().compare(username) == 0)
            throw std::logic_error{"User already registered"};
    }
    
    // make public key
    std::string public_key{}, private_key{};
    crypto::generate_key(public_key, private_key);

    // create new user
    User new_user {username, private_key, this};
    users.push_back(new_user);
    public_keys[username] = public_key;

    return users[i];
}

bool Server::create_message(Message* msg, const std::string& signature)
{
    // check if sender is available
    std::string username {msg->get_sender()};
    size_t i {};
    for(i; i < users.size(); i++) {
        if (users[i].get_username().compare(username) == 0)
            break;
    }

    if (i == users.size()) {
        std::cout << "Sender not found\n";
        return false;
    }
    // std::cout << "Sender " << username << " Found \n";
    // check if receiver is available
    i = 0;
    std::string username2 {msg->get_receiver()};
    for(i; i < users.size(); i++) {
        if (users[i].get_username().compare(username2) == 0)
            break;
    }

    if (i == users.size()) {
        std::cout << "Receiver not found\n";
        return false;
    }

    // std::cout << "Receiver " << username2 << " Found \n";

    std::string public_key = public_keys[username];


    bool authentic = crypto::verifySignature(public_key, "my data", signature);
    if (authentic) {
        messages.push_back(msg);
        return true;
    } else
        return false;
}