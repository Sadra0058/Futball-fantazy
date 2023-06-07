#pragma once

#include "Week.hpp"
#include "Team.hpp"
#include "Admin.hpp"
#include "User.hpp"
#include "Functions.hpp"

#include <map>
#include <algorithm>

enum
{
    POST,
    GET,
    PUT,
    DELETE
};

enum
{
    // DEFAULT
    TEAM_OF_THE_WEEK,
    PLAYERS,
    LEAGUE_STANDINGS,
    USERS_RANKING,
    MATCHES_RESULT_LEAGUE,
    // NO ACC
    SIGNUP,
    REGISTER_ADMIN,
    LOGIN,
    // USER
    SELL_PLAYER,
    BUY_PLAYER,
    SQUAD,
    // ADMIN
    CLOSE_TRANSFER_WINDOW,
    OPEN_TRANSFER_WINDOW,
    PASS_WEEK,
    // IN ACC
    LOGOUT
};

enum
{
    ADMIN,
    USER,
    IN_ACC,
    NO_ACC,
    DEFAULT,
};

enum
{
    ARG_T_NAME_REGISTER = 1,
    ARG_T_NAME_IN_REGISTER,
    ARG_PASS_REGISTER,
    ARG_PASS_IN_REGISTER,
    ARG_REGISTER_NUM = 5,
};

enum
{
    ARG_T_NAME_PLAYERS = 1,
    ARG_T_NAME_IN_PLAYERS,
    ARG_PLAYERS_NUM = 3,
};

struct Arg_get_players
{
    shared_ptr<Team> team;
    int Iroles;
    string Sroles;
    bool sort_by_rank = false;
};

const string ARG_CHAR = "?";
const string ERR_PERM = "Permission Denied";
const string ERR_BAD_REQ = "Bad Request";
const string ERR_NOT_FOUND = "Not Found";

const string ADMIN_NAME = "admin";
const string ADMIN_PASS = "123456";

class Data_base;

typedef void (Data_base::*Command_func_ptr)(vector<string> &);

typedef map<pair<int, int>, Command_func_ptr> Command_map;

typedef struct CURRENT
{
    int week = 0;
    int prem_state = DEFAULT;
    shared_ptr<Account> acc = nullptr;
} Current;

class Data_base
{
private:
    vector<shared_ptr<Week>> weeks;
    vector<shared_ptr<Team>> teams;
    vector<shared_ptr<User>> users;
    shared_ptr<Admin> admin;

    vector<Command_map> command_maps;
    void init_command_map();
    bool call_command_func(pair<int, int> &key, Command_map &command_map, vector<string> &arg);

    Current current;

    pair<int, int> make_command_code(pair<string, string> &command);

    // Commands
    void signup(vector<string> &arg);
    void check_signup_arg(vector<string> &arg);

    void login(vector<string> &arg);
    void check_login_arg(vector<string> &arg);

    void register_admin(vector<string> &arg);
    void check_register_admin_arg(vector<string> &arg);

    void logout(vector<string> &arg);
    void check_logout_arg(vector<string> &arg);

    void users_ranking(vector<string> &arg);

    void league_standings(vector<string> &arg);

    void get_players(vector<string> &arg);
    Arg_get_players make_arg_get_players(vector<string> &arg);
    void check_get_players_arg(vector<string> &arg);

    // Accessories

public:
    void manage_command(pair<string, string> &command, vector<string> &arg);

    void show()
    {
        vector<string> args;

        update_current_week();
        update_current_week();
        update_current_week();

        args.push_back("?");
        args.push_back("team");
        args.push_back("AFC_Bournemouth");
        // args.push_back("df");
        args.push_back("ranks");
        get_players(args);
    }

    void update_current_week();

    Data_base(const CSV_input &league_input, const vector<shared_ptr<CSV_input>> &weeks_input);
};
