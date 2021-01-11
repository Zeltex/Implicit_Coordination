
filename_counter = 1

String get_domain():
	result = r"""
_domain Pepper {
	_announce_enabled = false
	_types = [agent, pos]
	_propositions = [
		at(agent a, pos p)
		adj(pos p1, pos p2)
		goal(agent a, pos p)
		free(pos p)
	]

	_action move (pos from, pos to) {
		_cost = 100
		_owner = agent agent
		_designated_events = [event0]
		_event event0 { 
			_preconditions = ( AND( at(agent, from), free(to), adj(from, to)) )
			_effect_add = [ at(agent, to), free(from) ]
			_effect_delete = [ at(agent, from), free(to) ]
		}
		_reachability = {
			agent = {
				(event0 event0) = (TOP)
			}
			_rest = {
				(event0 event0) = (TOP)
			}
		}
	}

	_action announce (pos p) {
		_cost = 100
		_owner = agent agent
		_designated_events = [event0]
		_event event0 { 
			_preconditions = ( AND(at(agent, p), goal(agent, p)) )
			_effect_add = [  ]
			_effect_delete = [ ]
		}
		_reachability = {
			agent = {
				(event0 event0) = (TOP)
			}
			_rest = {
				(event0 event0) = (TOP)
			}
		}
	}
}
"""
	return result

for i in range(2, 8):
	
	
	nl = '\n'
	t = '\t'
	co = '{'
	cc = '}'
	output += '_problem MAPF_DU {\n'
	
	output += F"_objects = {co}{nl}{t}agent = [a0, a1]{nl}{t}pos = ["
	for k in range(2 * i - 1):
		output += F"c{k}, "
	output += F"x{i - 1}]{nl}{cc}{nl}"
	
	
	for world in range(4):
		output += F"_world w{world} ["
		for j in range(i * 2 - 2):
			output += F"adj(c{j}, c{j+1}), adj(c{j+1}, c{j}), "
		output +=  F"adj(c{i-1}, x{i-1}), adj(x{i-1}, c{i-1}), "
		
		for j in  range(i * 2 - 1):
			if j == 2 * i - 2:
				output += F"at(a0, c{j}), "
			elif j == i - 1:
				output += F"at(a1, c{j}), "
			else:
				output += F"free(c{j}), "
		output += F"free(x{i-1}), "
		if world == 0:
			output += F"goal(a0, c0), goal(a1, c{i-1})]"
		elif world == 1:
			output += F"goal(a0, x{i-1}), goal(a1, c{i-1})]"
		elif world == 2:
			output += F"goal(a0, c0), goal(a1, c{2 * i - 2})]"
		elif world == 3:
			output += F"goal(a0, x{i-1}), goal(a1, c{2 * i - 2})]"
		output += '\n\n'
	output += '_goal = [ OR( \n'
	output += F"{t}AND( goal(a0, c0), at(a0, c0), goal(a1, c{i - 1}), at(a1, c{i - 1})), {nl}"
	output += F"{t}AND( goal(a0, x{i - 1}), at(a0, x{i - 1}), goal(a1, c{i - 1}), at(a1, c{i - 1})), {nl}"
	output += F"{t}AND( goal(a0, c0), at(a0, c0), goal(a1, c{2 * i - 2}), at(a1, c{2 * i - 2})), {nl}"
	output += F"{t}AND( goal(a0, x{i - 1}), at(a0, x{i - 1}), goal(a1, c{2 * i - 2}), at(a1, c{2 * i - 2})) )] {nl}"
	
	output += r"""
	_designated_worlds = [ w0 ]
	_reflexivity = false
	_reachability = {
		a0 = {
		 (w0, w0), (w0, w2),
		 (w1, w1), (w1, w3),
		 (w2, w0), (w2, w2),
		 (w3, w1), (w3, w3), 
		 }
		a1 = {
		 (w0, w0), (w0, w1),
		 (w1, w0), (w1, w1),
		 (w2, w2), (w2, w3),
		 (w3, w2), (w3, w3), 
		 }
	}
}
"""
	
	with open(F"p{filename_counter - 1}.maepl", 'w') as f:
		f.write(output)
		filename_counter += 1