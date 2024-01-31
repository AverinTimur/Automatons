#include "HEADERS.h"

class DFA
{
    private:
        enum states
        {
            Dead = 0,
            Zero = 1,
            One = 2,
        };

        states state = states::Zero;
        void read(char letter)
        {
            if(state == states::One)
            {
                if(letter == '0')
                {
                    state = states::Zero;
                }
                else
                {
                    state = states::Dead;
                }
            }
            else if(state == states::Zero)
            {
                if(letter == '1')
                {
                    state = states::One;
                }
                else
                {
                    state = states::Dead;
                }
            }
        }
    public:
        bool check(std::string text)
        {
            for(int i = 0; i < text.size(); i++)
            {
                read(text[i]);
            }

            if(state == states::One)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
};

class NFA
{
    private:
        enum states
        {
            START,
            
            START_S,
            START_T,
            START_A,
            START_R,
            START_END_T,

            STAIR_S,
            STAIR_T,
            STAIR_A,
            STAIR_I,
            STAIR_R,
        };

        std::vector<states> position = { states::START };
        void read(char letter)
        {
            std::vector<states> new_position = std::vector<states>();
            for(std::vector<states>::iterator it = position.begin(); it != position.end(); it++)
            {
                if(*it == states::START)
                {
                    if(letter == 'S')
                    {
                        new_position.push_back(states::START_S);
                        new_position.push_back(states::STAIR_S);
                    }
                }
                else if(*it == states::START_S)
                {
                    if(letter == 'T')
                    {
                        new_position.push_back(states::START_T);
                    }
                }
                else if(*it == states::START_T)
                {
                    if(letter == 'A')
                    {
                        new_position.push_back(states::START_A);
                    }
                }
                else if(*it == states::START_A)
                {
                    if(letter == 'R')
                    {
                        new_position.push_back(states::START_R);
                    }
                }
                else if(*it == states::START_R)
                {
                    if(letter == 'T')
                    {
                        new_position.push_back(states::START_END_T);
                    }
                }
                else if(*it == states::STAIR_S)
                {
                    if(letter == 'T')
                    {
                        new_position.push_back(states::STAIR_T);
                    }
                }
                else if(*it == states::STAIR_T)
                {
                    if(letter == 'A')
                    {
                        new_position.push_back(states::STAIR_A);
                    }
                }
                else if(*it == states::STAIR_A)
                {
                    if(letter == 'I')
                    {
                        new_position.push_back(states::STAIR_I);
                    }
                }
                else if(*it == states::STAIR_I)
                {
                    if(letter == 'R')
                    {
                        new_position.push_back(states::STAIR_R);
                    }
                }
            }

            position = new_position;
        }
    public:
        bool check(std::string text)
        {
            for(int i = 0; i < text.size(); i++)
            {
                read(text[i]);
            }

            for(states state : position)
            {
                if(state == states::START_END_T || state == states::STAIR_R)
                {
                    return true;
                }
            }

            return false;
        }
};

class E_NFA
{
    private:
        enum states
        {
            START,
            
            START_S,
            START_T,
            START_A,
            START_R,
            START_END_T,

            STAIR_S,
            STAIR_T,
            STAIR_A,
            STAIR_I,
            STAIR_R,
        };

        std::vector<states> position = { states::START };
        void read(char letter)
        {
            std::vector<states> new_position = std::vector<states>();
            for(std::vector<states>::iterator it = position.begin(); it != position.end(); it++)
            {
                if(*it == states::START)
                {
                    if(letter == 'S')
                    {
                        new_position.push_back(states::START_S);
                        new_position.push_back(states::STAIR_S);
                    }
                }
                else if(*it == states::START_S)
                {
                    if(letter == 'T')
                    {
                        new_position.push_back(states::START_T);
                    }
                }
                else if(*it == states::START_T)
                {
                    if(letter == 'A')
                    {
                        new_position.push_back(states::START_A);
                    }
                }
                else if(*it == states::START_A)
                {
                    if(letter == 'R')
                    {
                        new_position.push_back(states::START_R);
                    }
                }
                else if(*it == states::START_R)
                {
                    if(letter == 'T')
                    {
                        new_position.push_back(states::START_END_T);
                    }
                }
                else if(*it == states::STAIR_S)
                {
                    if(letter == 'T')
                    {
                        new_position.push_back(states::STAIR_T);
                    }
                }
                else if(*it == states::STAIR_T)
                {
                    if(letter == 'A')
                    {
                        new_position.push_back(states::STAIR_A);
                    }
                }
                else if(*it == states::STAIR_A)
                {
                    if(letter == 'I')
                    {
                        new_position.push_back(states::STAIR_I);
                    }
                }
                else if(*it == states::STAIR_I)
                {
                    if(letter == 'R')
                    {
                        new_position.push_back(states::STAIR_R);
                    }
                }
            }

            position = new_position;
        }
    public:
        bool check(std::string text)
        {
            for(int i = 0; i < text.size(); i++)
            {
                read(text[i]);
            }

            for(states state : position)
            {
                if(state == states::START_END_T || state == states::STAIR_R)
                {
                    return true;
                }
            }

            return false;
        }
};

class REGEX_PARSER
{
    private:
        struct state
        {
            bool is_enter;
            bool is_exit;

            state(){};
            state(bool is_enter, bool is_exit)
            {
                this->is_enter = is_enter;
                this->is_exit = is_exit;
            }
        };

        std::vector<char> get_polish_notation(std::string text)
        {
            std::vector<char> operators;
            std::vector<char> operands;
            
            bool is_last_element_letter = false;
            const std::map<char, int> priority = {{'.', 1}, {'+', 2}};
            for(std::string::iterator it = text.begin(); it != text.end(); it++)
            {
                if(priority.contains(*it))
                {
                    int order = priority.at(*it);

                    while(operators.size() != 0 && priority.contains(operators.back()) && priority.at(operators.back()) <= order)
                    {
                        operands.push_back(operators.back());
                        operators.pop_back();
                    }
                    operators.push_back(*it);
                    
                    is_last_element_letter = false;
                }
                else if(*it == '*')
                {
                    operands.push_back(*it);
                    is_last_element_letter = true;
                }
                else if(*it == '(')
                {
                    if(is_last_element_letter)
                    {
                        operators.push_back('.');
                    }
                    operators.push_back(*it);
                    is_last_element_letter = false;
                }
                else if(*it == ')')
                {
                    while(operators.back() != '(' && operators.size() != 0)
                    {
                        operands.push_back(operators.back());
                        operators.pop_back();
                    }

                    if(operators.size() == 0)
                    {
                        throw "Bracket Balance Error"; // MAKE ERROR
                    }
                    else
                    {
                        operators.pop_back();
                    }
                    is_last_element_letter = true;
                }
                else
                {
                    if(is_last_element_letter)
                    {
                        operands.push_back(*it);
                        operators.push_back('.');
                    }
                    else
                    {
                        operands.push_back(*it);    
                    }
                    is_last_element_letter = true;
                }
            }

            operands.insert(operands.end(), operators.begin(), operators.end());

            return operands;
        }
        std::tuple<std::map<state*, std::map<char, std::vector<state*>>>, state*> make_transition_table(std::vector<char> elements)
        {
            std::list<std::tuple<std::map<state*, std::map<char, std::vector<state*>>>, state*, std::vector<state*>>> tables = std::list<std::tuple<std::map<state*, std::map<char, std::vector<state*>>>, state*, std::vector<state*>>>();

            state* new_state_one;
            state* new_state_two;
            std::tuple<std::map<state*, std::map<char, std::vector<state*>>>, state*, std::vector<state*>> table_one;
            std::tuple<std::map<state*, std::map<char, std::vector<state*>>>, state*, std::vector<state*>> table_two;
            std::tuple<std::map<state*, std::map<char, std::vector<state*>>>, state*, std::vector<state*>> new_table;
            for(char element : elements)
            {
                if(element == '.')
                {
                    if(tables.size() < 2)
                    {
                        throw "Regex Error"; // MAKE ERROR
                    }

                    table_one = *(--(--tables.end()));
                    table_two = *(--tables.end());
                    new_state_one = new state(false, false);


                    std::vector<state*> a = std::get<2>(table_one);
                    while(std::get<2>(table_one).size() != 0)
                    {
                        std::get<0>(table_one)[std::get<2>(table_one).front()]['\0'].push_back(new_state_one);
                        std::get<2>(table_one).front()->is_exit = false;
                        std::get<2>(table_one).erase(std::get<2>(table_one).begin());
                    }

                    std::get<1>(table_two)->is_enter = false;
                    std::get<0>(table_one)[new_state_one]['\0'].push_back(std::get<1>(table_two));

                    std::get<0>(table_one).insert(std::get<0>(table_two).begin(), std::get<0>(table_two).end());
                    std::get<2>(table_one) = std::get<2>(table_two);

                    tables.pop_back();
                    tables.pop_back();
                    tables.push_back(table_one);
                }
                else if(element == '*')
                {
                    if(tables.size() < 1)
                    {
                        throw "Regex Error"; // MAKE ERROR
                    }

                    table_one = *(--tables.end());
                    new_state_one = std::get<1>(table_one);
                    for(state* it : std::get<2>(table_one))
                    {
                        std::get<0>(table_one)[it]['\0'].push_back(new_state_one);
                    }

                    std::get<1>(table_one)->is_exit = true;
                    std::get<2>(table_one).push_back(std::get<1>(table_one));
                    tables.pop_back();
                    tables.push_back(table_one);
                }
                else if(element == '+')
                {
                    if(tables.size() < 2)
                    {
                        throw "Regex Error"; // MAKE ERROR
                    }
                    new_state_one = new state(true, false);
                    table_one = *(--(--tables.end()));
                    table_two = *(--tables.end());

                    std::get<0>(table_one).insert(std::get<0>(table_two).begin(), std::get<0>(table_two).end());
                    std::get<0>(table_one)[new_state_one]['\0'].push_back(std::get<1>(table_one));
                    std::get<0>(table_one)[new_state_one]['\0'].push_back(std::get<1>(table_two));

                    std::get<1>(table_one)->is_enter = false;
                    std::get<1>(table_two)->is_enter = false;

                    std::get<1>(table_one) = new_state_one;
                    std::get<2>(table_one).insert( std::get<2>(table_one).end(), std::get<2>(table_two).begin(), std::get<2>(table_two).end());
                    
                    tables.pop_back();
                    tables.pop_back();
                    tables.push_back(table_one);
                }
                else
                {
                    new_state_one = new state(true, false);
                    new_state_two = new state(false, true);
                    tables.push_back(
                    {
                        {{
                            new_state_one,
                            {{
                                element,
                                { new_state_two }
                            }}
                        }},
                        new_state_one,
                        { new_state_two }
                    });
                }
            }

            if(tables.size() != 1)
            {
                throw "Regex Error"; // MAKE ERROR
            }

            return std::tuple(std::get<0>(*tables.begin()), std::get<1>(*tables.begin()));
        }
    
    public:
        std::string regex;
        std::tuple<std::map<state*, std::map<char, std::vector<state*>>>, state*> table;
        REGEX_PARSER(std::string regex) // ДОДЕЛАТЬ
        {
            this->regex = regex;
            std::vector<char> polish_notation = get_polish_notation(regex);

            table = make_transition_table(polish_notation);
        }

        bool check(std::string text) // ДОДЕЛАТЬ
        {
            std::map<state*, std::map<char, std::vector<state*>>> transitions = std::get<0>(table);
            std::vector<state*> states = {std::get<1>(table)};

            std::vector<state*> new_states;
            std::vector<state*> transition;
            bool is_array_changed;
            for(char letter : text)
            {
                is_array_changed = true;
                while(is_array_changed)
                {
                    is_array_changed = false;
                    new_states = states;
                    for(std::vector<state*>::iterator it = states.begin(); it != states.end(); it++)
                    {
                        for(state* e_it : transitions[*it]['\0'])
                        {
                            if(std::find(states.begin(), states.end(), e_it) == states.end())
                            {
                                new_states.push_back(e_it);
                                is_array_changed = true;
                            }
                        }
                    }
                    states = new_states;
                }
                states = new_states;
                
                new_states = {};
                for(std::vector<state*>::iterator it = states.begin(); it != states.end(); it++)
                {
                    transition = transitions[*it][letter];
                    new_states.insert(new_states.end(), transition.begin(), transition.end());
                }
                states = new_states;
            }

            for(state* corrent_state : states)
            {
                if(corrent_state->is_exit)
                {
                    return true;
                }
            }
            return false;
        }
};