#include "user.h"

User::User(const std::string& _username, const std::string& _private_key, Server* _server):
    username {_username},
    private_key {_private_key},
    server {_server}
{
    // std::cout << "User constructor\n";
}

const std::string& User::get_username() const
{
    return username;
}

bool User::send_text_message(const std::string& _text, const std::string& _receiver)
{
    // create a message, a pointer from base to the driven class
    Message* msg = new TextMessage {_text, username, _receiver};

    // sign message
    std::string signature = crypto::signMessage(private_key, "my data");

    bool sentmsg = server->create_message(msg, signature);
    delete msg;

    return sentmsg;
}

bool User::send_voice_message(const std::string& _receiver)
{
    // create a message, a pointer from base to the driven class
    Message* msg = new VoiceMessage {username, _receiver};

    // sign message
    std::string signature = crypto::signMessage(private_key, "my data");

    bool sentmsg = server->create_message(msg, signature);
    delete msg;

    return sentmsg;
}