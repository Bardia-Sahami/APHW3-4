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
    // check if we have a similar username
    for (size_t i {}; i < users.size(); i++) {
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

    return users[users.size()-1];
}

bool Server::create_message(Message* msg, const std::string& signature)
{
    // check if sender is available
    std::string username {msg->get_sender()};
    bool found_user = false;
    for(size_t i {}; i < users.size(); i++) {
        if (users[i].get_username().compare(username) == 0) {
            found_user = true;
            break;
        }
    }

    if (!found_user) {
        std::cout << "Sender not found\n";
        return false;
    }


    // check if receiver is available
    found_user = false;
    std::string username2 {msg->get_receiver()};
    for(size_t i {}; i < users.size(); i++) {
        if (users[i].get_username().compare(username2) == 0) {
            found_user = true;
            break;
        }
    }

    if (!found_user) {
        std::cout << "Receiver not found\n";
        return false;
    }


    // authenticate using keys
    std::string public_key = public_keys[username];
    bool authentic = crypto::verifySignature(public_key, "my data", signature);

    static std::vector<TextMessage> holdertxt;
    static std::vector<VoiceMessage> holdervc;
    Message* newmsg;
    if ((msg->get_type().compare("text") == 0) && authentic) {
        TextMessage txtmsg = *(static_cast<TextMessage*>(msg));
        newmsg = new TextMessage (txtmsg);
        holdertxt.push_back(txtmsg);
    } else if ((msg->get_type().compare("voice") == 0) && authentic){
        VoiceMessage vcmsg = *(static_cast<VoiceMessage*>(msg));
        newmsg = new VoiceMessage (vcmsg);
        holdervc.push_back(vcmsg); 
    }
    

    if (authentic) {
        if (msg->get_type() == "text") {
            messages.push_back(newmsg);
            // std::cout << msg->get_sender() << "->" << msg->get_receiver() << std::endl;
        } else {
            messages.push_back(newmsg);
            // std::cout << msg->get_sender() << "->" << msg->get_receiver() << std::endl;
        }
        return true;
    } else
        return false;
}

std::vector<Message*> Server::get_all_messages_from(const std::string& username) const
{
    std::vector<Message*> temp(messages.size());
    
    auto it {std::copy_if(messages.begin(), messages.end(), temp.begin(), [&username](Message* a){return a->get_sender() == username;})};
    temp.erase(it, temp.end());

    return temp;
}

std::vector<Message*> Server::get_all_messages_to(const std::string& username) const
{
    std::vector<Message*> temp (messages.size());
    auto it {std::copy_if(messages.begin(), messages.end(), temp.begin(), [&username](Message* a){return a->get_receiver().compare(username) == 0;})};
    temp.erase(it, temp.end());

    return temp;
}

std::vector<Message*> Server::get_chat(const std::string& user1, const std::string& user2) const
{
    std::vector<Message*> temp (messages.size());
    auto it {std::copy_if(messages.begin(), messages.end(), temp.begin(), [&user1, &user2](Message* a)
    {
        bool condition1 {(a->get_receiver().compare(user1) == 0) && (a->get_sender().compare(user2) == 0)};
        bool condition2 {(a->get_receiver().compare(user2) == 0) && (a->get_sender().compare(user1) == 0)};
        return (condition1 || condition2);
    })};
    temp.erase(it, temp.end());

    return temp;

}