#ifndef CHANNELCLASS_HPP
# define CHANNELCLASS_HPP

# include "irc.hpp"

class Channel {
    private :
        string  name;
        string  topic;
        char    mode; //'r' -> public, 'i' -> invite only
        vector<Client*> user_list;
        vector<Client*> invite_list;

    public :
        Channel(string name, Client* oper);
        Channel(const Channel& x);
        ~Channel();

        Channel&    operator=(const Channel& x);

        void    add_user(Client* user);
        void    del_user(Client* user);
        int     is_oper(Client* user);
        int     already_joined(Client* user);
        int     check_invite(Client* user);
        void    del_invite(Client* user);
        void    multi_reply(Client* sender, string cmd, string description);

        string             getName() const;
        string             getTopic() const;
        char               getMode() const;
        string             getSymbol() const;
        string             getUsers() const;
        vector<Client*>    getUserList() const;

        void    setTopic(string topic);
        void    setMode(char mode);
};

#endif