#ifndef CHANNELSCLASS_HPP
# define CHANNELSCLASS_HPP

# include "irc.hpp"

class Channels {
    private :
        std::string name;
        std::string topic;
        char        mode;
        std::vector<Client*> user_list;

    public :
        Channels(std::string name, Client* oper);
        ~Channels();

        void    add_user(Client* user);
        void    del_user(Client* user);
        int     is_oper(Client* user);

        std::string             getName() const;
        std::string             getTopic() const;
        std::vector<Client*>    getUserList() const;

        void    setTopic(std::string topic);
        void    setMode(char mode);
};

#endif