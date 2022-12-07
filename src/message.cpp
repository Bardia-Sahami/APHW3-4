#include "message.h"

Message::Message(const std::string& _type, const std::string& _sender, const std::string& _receiver):
    type {_type},
    sender {_sender},
    receiver {_receiver}
{

    std::time_t now = std::time(0);
    std::string _time = std::ctime(&now);
    _time.erase(_time.find_last_not_of(" \n\r\t")+1);
    time = _time;
}

Message::Message(): Message{"", "", ""}
{

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
    os << sender << " -> " << receiver << std::endl;
    os << "message type: " << type << std::endl;
    os << "message time: " << time << std::endl;
    os << "*************************\n";
}

TextMessage::TextMessage(const std::string& _text, const std::string& _sender, const std::string& _receiver):
    Message{"text", _sender, _receiver},
    text{_text}
{

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
    srand (0);
    int rand;
    for (size_t i{}; i < 5; i++) {
        rand = std::rand() % 128;
        voice.push_back(rand);
    }
    
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