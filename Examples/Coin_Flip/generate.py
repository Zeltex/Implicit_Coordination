result1 = """_domain Pepper {
	_types = [agent, number, tyControl]
	_propositions = [
		propControl(tyControl tc)
		prop(number n)
		adj(number n1, number n2)
		agentNumb(number n, agent a)
	]

	_action throw (number n1, number n2, tyControl tc, agent a) {
		_cost = 100
		_owner = agent a
		_designated_events = [event0, event1]
		_event event0 { 
			_preconditions = ( AND(AND(prop(n1), adj(n1, n2)), agentNumb(n1, a)) )
			_effect_add = [ prop(n2), propControl(tc) ]
			_effect_delete = [ prop(n1) ]
		}
		_event event1 { 
			_preconditions = ( AND(AND(prop(n1), adj(n1, n2)), agentNumb(n1, a)) )
			_effect_add = [ prop(n2) ]
			_effect_delete = [ prop(n1), propControl(tc) ]
		}
		_reachability = {
			a = {
				(event0, event0) = (TOP), 
				(event1, event1) = (TOP)
			}
			_rest = {
				(event0, event0) = (TOP),
				(event0, event1) = (TOP),
				(event1, event0) = (TOP),
				(event1, event1) = (TOP)
			}
		}
	}
}
_problem Coin_Flip {
	_objects = {
		agent = [a0, a1]
		number = ["""
result2 = """]
		tyControl = [p]
	}
	_initial_state = ["""
result3 = """]
	_world w0 [ prop(n1)]
	_goal = ["""
result4 = """]

	_designated_worlds = [ w0 ]
	_reachability = {
		a0 = {
			(w0, w0)
		},
		a1 = {
			(w0, w0)
		}
	}
}"""

for i in range(1,51):
	result = result1
	for j in range(i+1):
		result += F"n{j} "
	result += result2
	for j in range(i):
		result += F"adj(n{j} n{j+1}) "
		
	for j in range(i+1):
		result += F"agentNumb(n{j} a{j%2}) "
	
	result += result3 + F"prop(n{i})" + result4
	
	with open(F"Coin_Flip_{i}.maepl", 'w') as f:
		f.write(result)
			