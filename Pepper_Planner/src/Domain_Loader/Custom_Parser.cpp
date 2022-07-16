#include "Custom_Parser.hpp"

#include <assert.h>

namespace del {
    Custom_Parser::Custom_Parser(Custom_Lexer* lexer)
        : lexer(lexer), 
        pointer(0), 
        value_pointer(0), 
        tokens_size(lexer->tokens.size()), 
        buffer(new General_Domain())
    {

        maepl();
    }

    std::unique_ptr<General_Domain> Custom_Parser::get()
    {
        return std::move(buffer);
    }

    bool Custom_Parser::try_match(const std::vector<Token>& pattern) 
    {
        if (pointer + pattern.size() > tokens_size) 
        {
            return false;
        }
        
        for (size_t i = 0; i < pattern.size(); i++) 
        {
            if (pattern[i] != lexer->tokens[pointer + i]) 
            {
                return false;
            }
        }

        value_pointer = pointer;
        pointer += pattern.size();
        return true;
    }

    void Custom_Parser::must_match(const Token& token)
    {
        must_match(std::vector<Token>{ token });
    }

    void Custom_Parser::must_match(const std::vector<Token>& pattern)
    {
        if (!try_match(pattern))
        {
            std::string error;
            error += "Syntax error line: " + lexer->line_numbers[pointer] + std::string(". Expected token") + (pattern.size() > 1 ? "s " : " ");
            for (auto& entry : pattern) 
            {
                error += token_to_string(entry) + " ";
            }
            
            if (pointer < lexer->tokens.size()) 
            {
                error += " Found " + token_to_string(lexer->tokens[pointer]);
            }
            
            error += "\n";
            assert(false);
            throw std::runtime_error(error);
        }
    }

    size_t Custom_Parser::get_ivalue(size_t argument_index) 
    {
        return lexer->values.at(value_pointer + argument_index).ival;
    }

    const std::string& Custom_Parser::get_svalue(size_t argument_index) 
    {
        return lexer->values.at(value_pointer + argument_index).sval;
    }

    bool Custom_Parser::get_bvalue(size_t argument_index) 
    {
        return lexer->values.at(value_pointer + argument_index).bval;
    }

    std::string Custom_Parser::token_to_string(Token token) 
    {
        switch (token) 
        {
            case Token::ACTION_DEF				: return "_action";
            case Token::ANNOUNCE_DEF			: return "_announce";
            case Token::COST_DEF				: return "_announce";
            case Token::DESIGNATED_EVENTS_DEF	: return "_designated_events";
            case Token::DESIGNATED_WORLDS_DEF	: return "_designated_worlds";
            case Token::DOMAIN_DEF				: return "_domain";
            case Token::EFFECT_ADD_DEF			: return "_effect_add";
            case Token::EFFECT_DELETE_DEF		: return "_effect_delete";
            case Token::EVENT_DEF				: return "_event";
            case Token::GOAL_DEF				: return "_goal";
            case Token::INIT_DEF				: return "initial_state";
            case Token::OBJECTS_DEF				: return "_objects";
            case Token::OWNER_DEF				: return "_owner";
            case Token::PRECONDITIONS_DEF		: return "_preconditions";
            case Token::PROBLEM_DEF				: return "_problem";
            case Token::PROPOSITIONS_DEF		: return "_propositions";
            case Token::REACHABILITY_DEF		: return "_reachability";
            case Token::REFLEXIVITY_DEF			: return "_reflexivity";
            case Token::REST_DEF				: return "_rest";
            case Token::TYPES_DEF				: return "_types";
            case Token::WORLD_DEF				: return "_world";
            case Token::LBRACK					: return "(|[|{";
            case Token::RBRACK					: return ")|]|}";
            case Token::BELIEVES				: return "BELIEF";
            case Token::AND						: return "AND";
            case Token::OR						: return "OR";
            case Token::NOT						: return "NOT";
            case Token::TOP						: return "TOP";
            case Token::NAME					: return "NAME";
            case Token::INTEGER					: return "INTEGER";
            case Token::TRUTH					: return "true|false";
            case Token::EQUALS					: return "=";
        }
    }

    void Custom_Parser::maepl() 
    {
        if (try_match({ Token::DOMAIN_DEF, Token::NAME, Token::LBRACK})) 
        {
            domain_body();
            must_match(Token::RBRACK);
            return maepl();
        }

        if (try_match({ Token::PROBLEM_DEF, Token::NAME, Token::LBRACK })) 
        {
            problem_body();
            must_match(Token::RBRACK);
            return maepl();
        }

        return;
    }

    void Custom_Parser::domain_body() {

        if (try_match({ Token::ANNOUNCE_DEF, Token::EQUALS, Token::TRUTH })) 
        {
            if (get_bvalue(2))
            {
                buffer->announce_enabled = true;
            }
            return domain_body();
        }

        if (try_match({ Token::TYPES_DEF, Token::EQUALS, Token::LBRACK })) 
        {
            variables();
            must_match(Token::RBRACK);
            buffer->types.set(buffer->variables_buffer);

            must_match({ Token::PROPOSITIONS_DEF, Token::EQUALS, Token::LBRACK });
            propositions();
            must_match(Token::RBRACK);

            return actions();
        }
        assert(false);
        throw "Syntax error line: " + lexer->line_numbers[pointer];
    }

    // Object def must come before world def and designated worlds def
    // Need to implement restrictions and proper error messages
    void Custom_Parser::problem_body() {
        if (try_match({Token::DOMAIN_DEF, Token:: EQUALS, Token:: NAME}))
		{
            return problem_body();
        }

        if (try_match({ Token:: OBJECTS_DEF, Token::EQUALS, Token:: LBRACK }))
		{
            objects();
            must_match(Token::RBRACK);
            return problem_body();
        }

        if (try_match({ Token:: INIT_DEF, Token:: EQUALS, Token:: LBRACK}))
		{
            problem_proposition_instances();
            buffer->rigid_propositions.set_and_consume(buffer->proposition_instance_buffer);
            must_match(Token::RBRACK);
            return problem_body();
        }

        if (try_match({ Token::WORLD_DEF, Token::NAME, Token::LBRACK }))
		{
            auto world_name = get_svalue(1);
            problem_proposition_instances();
            buffer->state.add_world(world_name, buffer->proposition_instance_buffer);
            must_match(Token::RBRACK);
            return problem_body();
        }

        if (try_match({ Token::GOAL_DEF, Token::EQUALS, Token::LBRACK }))
		{
            formula();
            buffer->goal = std::move(buffer->formula_buffer.get());
            must_match(Token::RBRACK);
            return problem_body();
        }

        if (try_match({ Token::DESIGNATED_WORLDS_DEF, Token::EQUALS, Token::LBRACK }))
		{
            variables();
            buffer->state.set_designated_worlds(buffer->variables_buffer);
            must_match(Token::RBRACK);
            return problem_body();
        }

        if (try_match({ Token::REACHABILITY_DEF, Token::EQUALS, Token::LBRACK }))
		{
            reachability_body();
            must_match(Token::RBRACK);
            return problem_body();
        }
    }

    void Custom_Parser::reachability_body() {
        if (try_match({ Token::NAME, Token::EQUALS, Token::LBRACK }))
		{
            auto name = get_svalue(0);
            bracketed_input();
            buffer->state.add_accessibility_relations(name, buffer->inputs_buffer, buffer->agents);
            must_match(Token::RBRACK);
            return reachability_body();
        }
        return;
    }

    void Custom_Parser::objects() {
        if (try_match({ Token::NAME, Token::EQUALS, Token::LBRACK }))
		{
            std::string type = get_svalue(0);
            variables();
            buffer->objects.add(type, buffer->variables_buffer, buffer->agents);
            must_match(Token::RBRACK);
            return objects();
        }
        return;
    }

    bool Custom_Parser::proposition_instance() {
        if (try_match({ Token::NAME, Token::LBRACK }))
		{
            std::string name = get_svalue(0);
            ordered_variables();
            buffer->proposition_instance_buffer.add(name, buffer->variables_buffer);
            must_match(Token::RBRACK);
            return true;
        }
        return false;
    }

    void Custom_Parser::bracketed_input() {
        if (try_match({ Token::LBRACK, Token::NAME, Token::NAME, Token::RBRACK }))
		{
            buffer->inputs_buffer.add(get_svalue(1), get_svalue(2));
            return bracketed_input();
        }
        return;
    }

    void Custom_Parser::input() {
        if (try_match({ Token::NAME, Token::NAME }))
		{
            buffer->inputs_buffer.add(get_svalue(0), get_svalue(1));
            return input();
        }
        return;
    }

    void Custom_Parser::action_body() {
        if (try_match({ Token::OWNER_DEF, Token::EQUALS, Token::NAME, Token::NAME }))
		{
            buffer->actions.set_owner(get_svalue(2), get_svalue(3));
            return action_body();
        }

        if (try_match({ Token::EVENT_DEF, Token::NAME, Token::LBRACK }))
		{
            
            buffer->events_buffer.start(get_svalue(1));
            event_body();
            must_match(Token::RBRACK);
            return action_body();
        }

        if (try_match({ Token::DESIGNATED_EVENTS_DEF, Token::EQUALS, Token::LBRACK }))
		{
            ordered_variables();
            buffer->actions.set_designated_events(buffer->variables_buffer);
            must_match(Token::RBRACK);
            return action_body();
        }

        if (try_match({ Token::REACHABILITY_DEF, Token::EQUALS, Token::LBRACK }))
		{
            action_reachability();

            // TODO -- If _rest not defined, add empty entry, important for agent size later on
            // TODO - Check if this still matters
            must_match(Token::RBRACK);
            return action_body();
        }

        if (try_match({ Token::COST_DEF, Token::EQUALS, Token::INTEGER }))
		{
            buffer->actions.set_cost(get_ivalue(2));
            return action_body();
        }
    }

    void Custom_Parser::action_reachability() {
        if (try_match({ Token::NAME, Token::EQUALS, Token::LBRACK }))
		{
            std::string agent_name = get_svalue(0);
            action_agent_reachability();
            buffer->actions.set_edge_conditions(agent_name, buffer->edge_condition_buffer);
            must_match(Token::RBRACK);
            return action_reachability();
        }

        if (try_match({ Token::REST_DEF, Token::EQUALS, Token::LBRACK }))
		{
            action_agent_reachability();
            buffer->actions.set_edge_conditions(REST_KEYWORD, buffer->edge_condition_buffer);
            must_match(Token::RBRACK);
            return action_reachability();
        }
        return;
    }

    void Custom_Parser::action_agent_reachability() {

        if (try_match({ Token::LBRACK, Token::NAME, Token::NAME, Token::RBRACK, Token::EQUALS, Token::LBRACK}))
		{
            std::string event0 = get_svalue(1);
            std::string event1 = get_svalue(2);
            formula();
            buffer->edge_condition_buffer.add(event0, event1, std::move(buffer->formula_buffer.get()));
            must_match(Token::RBRACK);
            action_agent_reachability();
        }
        return;

    }

    void Custom_Parser::event_body() {
        if (try_match({ Token::PRECONDITIONS_DEF, Token::EQUALS, Token::LBRACK }))
		{
            formula();
            buffer->events_buffer.set_preconditions(buffer->formula_buffer);
            must_match(Token::RBRACK);
            return event_body();
        }

        if (try_match({ Token::EFFECT_DELETE_DEF, Token::EQUALS, Token::LBRACK }))
		{
            domain_proposition_instances();
            buffer->events_buffer.set_delete_list(buffer->proposition_instance_buffer);
            must_match(Token::RBRACK);
            return event_body();
        }

        if (try_match({ Token::EFFECT_ADD_DEF, Token::EQUALS, Token::LBRACK }))
		{
            domain_proposition_instances();
            buffer->events_buffer.set_add_list(buffer->proposition_instance_buffer);
            must_match(Token::RBRACK);
            return event_body();
        }
    }

    bool Custom_Parser::formula() {
        if (proposition_instance()) {
            buffer->formula_buffer.push_pop_formula_prop(buffer->proposition_instance_buffer);
            return true;
        }

        if (try_match({ Token::AND, Token::LBRACK }))
        {
            buffer->formula_buffer.push_formula("And");
            if (!formula() || !formula())
            {
                // And must have exactly 2 children
                assert(false);
                exit(1);
            }
            must_match(Token::RBRACK);
            buffer->formula_buffer.pop_formula();
            return true;
        }

        if (try_match({ Token::OR, Token::LBRACK }))
		{
            buffer->formula_buffer.push_formula("Or");
            if (!formula() || !formula())
            {
                // And must have exactly 2 children
                assert(false);
                exit(1);
            }
            must_match(Token::RBRACK);
            buffer->formula_buffer.pop_formula();
            return true;
        }

        if (try_match({ Token::NOT, Token::LBRACK }))
		{
            buffer->formula_buffer.push_formula("Not");
            if (!formula())
            {
                // Not must have 1 child
                assert(false);
                exit(1);
            }
            must_match(Token::RBRACK);
            buffer->formula_buffer.pop_formula();
            return true;
        }

        if (try_match({ Token::TOP }))
		{
            buffer->formula_buffer.push_pop_formula_top();
            return true;
        }

        if (try_match({ Token::BELIEVES, Token::LBRACK, Token::NAME }))
		{
            auto agent = get_svalue(2);
            buffer->formula_buffer.push_formula("Believes");
            if (!formula())
            {
                // Believes must have 1 child
                assert(false);
                exit(1);
            }
            must_match(Token::RBRACK);
            buffer->formula_buffer.pop_formula_believes(buffer->agents, agent);
            return true;
        }

        return false;
    }

    void Custom_Parser::domain_proposition_instances() {
        if (try_match({ Token::NAME, Token::LBRACK }))
        {
            auto name = get_svalue(0);
            ordered_variables();
            buffer->proposition_instance_buffer.add(name, buffer->variables_buffer);
            must_match(Token::RBRACK);
            return domain_proposition_instances();
        }
        return;
    }

    void Custom_Parser::problem_proposition_instances() {
        if (try_match({ Token::NAME, Token::LBRACK }))
		{
            auto name = get_svalue(0);
            ordered_variables();
            buffer->proposition_instance_buffer.add(name, buffer->variables_buffer);
            must_match(Token::RBRACK);
            return problem_proposition_instances();
        }
        return;
    }

    void Custom_Parser::propositions() {
        if (try_match({ Token::NAME, Token::LBRACK }))
		{
            auto name = get_svalue(0);
            input();
            buffer->typed_propositions.add(name, buffer->inputs_buffer);
            must_match(Token::RBRACK);
            return propositions();
        }
        return;
    }

    void Custom_Parser::actions() {
        if (try_match({ Token::ACTION_DEF, Token::NAME, Token::LBRACK }))
		{
            buffer->actions.start(get_svalue(1));
            input();
            buffer->actions.set_input(buffer->inputs_buffer);
            must_match({ Token::RBRACK, Token::LBRACK });
            action_body();
            buffer->actions.set_events(buffer->events_buffer);
            buffer->actions.set_propositions_buffer(buffer->proposition_instance_buffer);
            must_match(Token::RBRACK);
            return actions();
        }
        return;
    }

    void Custom_Parser::variables() {
        if (try_match({ Token::NAME }))
		{
            buffer->variables_buffer.add(get_svalue(0));
            return variables();
        }
        return;
    }

    void Custom_Parser::ordered_variables() {
        if (try_match({ Token::NAME }))
		{
            buffer->variables_buffer.add(get_svalue(0));
            return ordered_variables();
        }
        if (try_match({ Token::REST_DEF }))
		{
            buffer->variables_buffer.add(get_svalue(0));
            return ordered_variables();
        }
        return;
    }
}
