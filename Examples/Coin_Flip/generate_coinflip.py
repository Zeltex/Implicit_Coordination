result_1 = """
_domain Pepper {
	_announce_enabled = false
	_types = [agent, heads, tails, side]
	_propositions = [
		coin(agent a, side s)
	]

	_action throw (tails t, heads h, agent agent) {
		_cost = 100
		_owner = agent agent
		_designated_events = [event0, event1]
		_event event0 { 
			_preconditions = ( TOP )
			_effect_add = [ coin(agent, t) ]
			_effect_delete = [ coin(agent, h), coin(agent, t) ]
		}
		_event event1 { 
			_preconditions = ( TOP )
			_effect_add = [ coin(agent, h) ]
			_effect_delete = [ coin(agent, t), coin(agent, h)]
		}
		_reachability = {
			agent = {
				(event0, event1)
			}
			_rest = {
				(event0, event1)
			}
		}
	}
}
_problem Coin_Flip {
	_objects = {
		agent = ["""
result_2 = """]
		heads = [h]
		tails = [t]
		side = [h, t]
	}
	_initial_state = [
	]
	_world w0 [ ]
	_goal = [AND(""" 
result_3 = """)]

	_designated_worlds = [ w0 ]
	_reflexivity = false  
	_reachability = {"""
nl = '\n'
t = '\t'
co = '{'
cc = '}'

for i in range(1,20):
	result = result_1
	for j in range(i):
		result += F"a{j}, "
	result = result[:-1] + result_2
	for j in range(i):
		result += F"OR(coin(a{j}, t), coin(a{j}, h)){nl}"
	result += result_3
	for j in range(i):
		result += F"a{j} = {co}(w0){cc}{nl}"
	result += "}\n}"
	with open(F"Coin_Flip_{i}.maepl", 'w') as f:
		f.write(result)
