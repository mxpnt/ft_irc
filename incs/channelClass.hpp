#ifndef CHANNELCLASS_HPP
# define CHANNELCLASS_HPP

# include "irc.hpp"

class Channel {
    private :
        std::string name;
        std::string topic;
        char        mode;
        std::vector<Client*> user_list;

    public :
        Channel(std::string name, Client* oper);
        Channel(const Channel& x);
        ~Channel();

        Channel&    operator=(const Channel& x);

        void    add_user(Client* user);
        void    del_user(Client* user);
        int     is_oper(Client* user);
        void    multi_reply(Client* sender, std::string cmd, std::string dst, std::string description);

        std::string             getName() const;
        std::string             getTopic() const;
        char                    getMode() const;
        std::string             getSymbol() const;
        std::string             getUser() const;
        std::vector<Client*>    getUserList() const;

        void    setTopic(std::string topic);
        void    setMode(char mode);
};

#endif