#include "message.h"

Message::Message(const std::string& _type, const std::string& _sender, const std::string& _receiver):
    type {_type},
    sender {_sender},
    receiver {_receiver}
{
    // std::cout << "Constructor\n";
    // std::cout << "type: " << type << std::endl;
    // std::cout << "sender: " << sender << std::endl;
    // std::cout << "receiver: " << receiver << std::endl;
    // std::cout << "_type: " << _type << std::endl;
    // std::cout << "_sender: " << _sender << std::endl;
    // std::cout << "_receiver: " << _receiver << std::endl;
    std::time_t now = std::time(0);
    std::string _time = std::ctime(&now);
    _time.erase(_time.find_last_not_of(" \n\r\t")+1);
    time = _time;
}

Message::Message(): Message{"", "", ""}
{
    // std::cout << "Default Constructor\n";
    // std::cout << "type: " << type << std::endl;
    // std::cout << "sender: " << sender << std::endl;
    // std::cout << "receiver: " << receiver << std::endl;
}

const std::string& Message::get_type() const
{
    return type;
}

const std::string& Message::get_sender() const
{
    return sender;
}

const std::string& Message::get_receiver() const
{
    return receiver;
}

const std::string& Message::get_time() const
{
    return time;
}

void Message::print(std::ostream& os) const
{
    os << "*************************\n";
    os << get_sender() << " -> " << get_receiver() << "\n";
    os << "message type: " << get_type() << "\n";
    os << "message time: " << get_time() << "\n";
    os << "*************************\n";
}

TextMessage::TextMessage(const std::string& _text, const std::string& _sender, const std::string& _receiver):
    Message{"text", _sender, _receiver},
    text{_text}
{
    // std::cout << "Text Message Constructor\n";
}

void TextMessage::print(std::ostream &os) const
{
    os << "*************************\n";
    os << get_sender() << " -> " << get_receiver() << "\n";
    os << "message type: " << get_type() << "\n";
    os << "message time: " << get_time() << "\n";
    os << "text: " << text << "\n";
    os << "*************************\n";
}


const std::string& TextMessage::get_text() const
{
    return text;
}

VoiceMessage::VoiceMessage(const std::string& _sender, const std::string& _receiver):
    Message{"voice", _sender, _receiver}
{
    // std::cout << "Voice Message Constructor\n";
    srand (0);
    int rand;
    for (size_t i{}; i < 5; i++) {
        rand = std::rand() % 128;
        voice.push_back(rand);
    }
    // std::cout << static_cast<int>(voice[0]) << " " << static_cast<int>(voice[1]) << " " << static_cast<int>(voice[2]) << " " << static_cast<int>(voice[3]) << " " << static_cast<int>(voice[4]) << " " << std::endl;
    
}

void VoiceMessage::print(std::ostream &os) const
{
    os << "*************************\n";
    os << get_sender() << " -> " << get_receiver() << "\n";
    os << "message type: " << get_type() << "\n";
    os << "message time: " << get_time() << "\n";
    os << "voice: ";
    for (size_t i{}; i < 5; i++)
        os << static_cast<int>(voice[i]) << " ";
    os << "\n*************************\n";
}

const std::vector<unsigned char>& VoiceMessage::get_voice() const
{
    return voice;
}