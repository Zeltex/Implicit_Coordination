#pragma once

#include "General_Domain.hpp"
#include "Domain_Interface.hpp"
#include "Custom_Lexer.hpp"

namespace del {
    class Custom_Parser {
    public:
        Custom_Parser(Custom_Lexer* lexer);
        General_Domain get();
    private:
        General_Domain buffer;
        Custom_Lexer* lexer;
        size_t pointer;
        size_t value_pointer;
        size_t tokens_size;

        void must_match(const Token& token);
        void must_match(const std::vector<Token>& pattern);
        bool try_match(const std::vector<Token>& pattern);
        size_t get_ivalue(size_t argument_index);
        const std::string& get_svalue(size_t argument_index);
        bool get_bvalue(size_t argument_index);
        std::string token_to_string(Token token);

        void action_agent_reachability();
        void action_body();
        void action_reachability();
        void actions();
        void bracketed_input();
        void domain_body();
        void event_body();
        void formula();
        void formula_single();
        void input();
        void maepl();
        void objects();
        void ordered_variables();
        void problem_body();
        bool proposition_instance();
        void proposition_instances();
        void propositions();
        void reachability_body();
        void variables();
    };
}
