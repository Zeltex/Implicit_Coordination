
filename_counter = 1
nl = '\n'
t = '\t'
co = '{'
cc = '}'

def get_domain():
	result = r"""

_domain Pepper {
	_announce_enabled = false
	_types = [agent, pos]
	_propositions = [
		at(agent a, pos p)
		adj(pos p1, pos p2)
		goal(agent a, pos p)
		free(pos p)
		stopped(agent a)
	]

	_action move (pos from, pos to, agent agent) {
		_cost = 100
		_owner = agent agent
		_designated_events = [event0]
		_event event0 { 
			_preconditions = ( AND( at(agent, from), free(to), adj(from, to), NOT(stopped(agent))) )
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

	_action announce (pos p, agent agent) {
		_cost = 100
		_owner = agent agent
		_designated_events = [event0]
		_event event0 { 
			_preconditions = ( AND(at(agent, p), goal(agent, p), NOT(stopped(agent)) ))
			_effect_add = [ stopped(agent) ]
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

def print_1_agent():
	for i in range(2, 8):
		output = get_domain()
		output += '_problem MAPF_DU {\n'
		
		output += F"_objects = {co}{nl}{t}agent = [a0, a1]{nl}{t}pos = ["
		for k in range(2 * i - 1):
			output += F"c{k}, "
		output += F"x{i - 1}]{nl}{cc}{nl}{nl}"
		
		
		output += F"_initial_state = [{nl}{t}"
		for j in range(i * 2 - 2):
			output += F"adj(c{j}, c{j+1}), adj(c{j+1}, c{j}), "
		output +=  F"adj(c{i-1}, x{i-1}), adj(x{i-1}, c{i-1}){nl}]{nl}{nl}"
		for world in range(4):
			output += F"_world w{world} ["			
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
		output += F"_goal = [ AND(stopped(a0), stopped(a1))] {nl}"
		
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
		global filename_counter
		with open(F"p{filename_counter}.maepl", 'w') as f:
			f.write(output)
			filename_counter += 1
			
def print_2_agents():
	for i in range(3, 8):
		output = get_domain()
		output += '_problem MAPF_DU {\n'
		
		output += F"_objects = {co}{nl}{t}agent = [a0, a1, a2]{nl}{t}pos = ["
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
			
			
def print_3_agents():
	x_spots = [
		[1, 3, 5],
		[1, 4, 7],
		[2, 5, 8]
		]
	goals = [
		[['c0', 'x1'],['c1', 'x3'],['c3', 'x5'],['c5','c6']],
		[['c1', 'x1'],['c1', 'x4'],['c4', 'x7'],['c7','c8']],
		[['c0', 'x2'],['c2', 'x5'],['c5', 'x8'],['c8','c10']]
		]
	starts = [
		['c6', 'c5', 'c3', 'c1'],
		['c8', 'c7', 'c4', 'c1'],
		['c10', 'c8', 'c5', 'c2']
		]
	n_cells = [7, 9, 11]
	n_worlds = 16
	n_agents = 4
	file_names = ['p13', 'p14', 'p15']
	
	for i in range(len(file_names)):
		
	
		output = get_domain()
		output += '_problem MAPF_DU {\n'
		
		# Agents
		output += F"_objects = {co}{nl}{t}agent = ["
		for agent in range(n_agents):
			output += F"a{agent}, "
		output = output[:-2]
		
		# Pos
		output += F"]{nl}{t}pos = ["
		for k in range(n_cells[i]):
			output += F"c{k}, "
		for x in x_spots[i]:
			output += F"x{x}, "
		output = output[:-2]
		output += F"]{nl}{cc}{nl}"
		
		# Initial state
		output += F"_initial_state = [{nl}{t}"
		for j in range(n_cells[i]-1):
			output += F"adj(c{j}, c{j+1}), adj(c{j+1}, c{j}), "
		for j in range(len(x_spots[i])):
			output +=  F"adj(c{x_spots[i][j]}, x{x_spots[i][j]}), adj(x{x_spots[i][j]}, c{x_spots[i][j]}), "
		output = output[:-2]
		output += F"{nl}]{nl}{nl}"
		
		
		# Worlds
		for world in range(n_worlds):
			output += F"{nl}{t}_world w{world} ["
			for j in range(n_cells[i] + len(x_spots[i])):
				if j < n_cells[i]:
					cell = F"c{j}"
				else:
					cell = F"x{x_spots[i][j-n_cells[i]]}"
				if cell in starts[i]:
					output += F"at(a{starts[i].index(cell)}, {cell}), "
					continue
				output += F"free({cell}), "
				
			for agent in range(n_agents):
				goal_to_use = 0 if (world % 2 ** (agent + 1) < 2 ** agent) else 1
				if agent == 0:
					print(F"world {world}, goal_to_use {goal_to_use}")
				output += F"goal(a{agent}, {goals[i][agent][goal_to_use]}), "
					
						
					#if world % 2 ** (agent + 1) < 2 ** agent:
					#	if cell == goal_cell = goals[i][agent][0]:
					#		output += F"goal(a{agent}, {cell}), "
					#else:
				
			output = output[:-2] + ']'
		
		output += F"{nl}{t}{t}_goal = [ AND("
		for agent in range(n_agents):
			output += F"stopped(a{agent}), "
		output = output[:-2] 
		output += ")]\n\t"
		output += r"""
		_designated_worlds = [ w0 ]
		_reflexivity = false
"""
		output += "_reachability = {\n\t"
		for agent in range(4):
			output += F"{t}a{agent} = {co}{nl}"
			for k in range(n_worlds):
				output += "\t\t"
				for j in range(n_worlds):
					if ((k % 2 ** (agent + 1) < 2 ** agent and j % 2 ** (agent + 1) < 2 ** agent) or (k % 2 ** (agent + 1) >= 2 ** agent and j % 2 ** (agent + 1) >= 2 ** agent)):
						output += F"(w{k}, w{j}), "
				output += '\n'
			output += F"{t}{t}{cc}{nl}"
		output += '\t}\n}'
		print(F"index {i}")
		with open(F"{file_names[i]}.maepl", 'w') as f:
			f.write(output)
print_3_agents()