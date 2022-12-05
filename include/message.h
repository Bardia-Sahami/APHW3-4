#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <stdlib.h>
#include <map>

class Message
{
public:
    Message(const std::string& type, const std::string& sender, const std::string& receiver);
    Message();

    const std::string&  get_type() const;
    const std::string&  get_sender() const;
    const std::string&  get_receiver() const;
    const std::string& get_time() const;
    virtual void print(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Message& c)
    {
        c.print(os);
        return os;
    }

private:
    std::string type;     // type of the message ("text", "voice", ...)
    std::string sender;   // the username who send this message
    std::string receiver; // the username whom this message is intended for
    std::string time;     // creation time of the message
};



class TextMessage : public Message
{
public:
    TextMessage(const std::string& text, const std::string& sender, const std::string& receiver);
    virtual void print(std::ostream& os) const override;
    const std::string& get_text() const;

private:
    std::string text;
};


class VoiceMessage : public Message
{
public:
    VoiceMessage(const std::string& sender, const std::string& receiver);
    virtual void print(std::ostream& os) const override;
    const std::vector<unsigned char>& get_voice() const;
private:
    std::vector<unsigned char> voice;
};



#endif //MESSAGE_H