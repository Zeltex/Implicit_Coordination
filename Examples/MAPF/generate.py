filename_counter = 1
nl = '\n'
t = '\t'
co = '{'
cc = '}'


def get_domain():
    result = r"""

_domain Pepper {
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
			_preconditions = ( AND( AND( AND( at(agent, from), free(to)), adj(from, to)), NOT(stopped(agent)) ) )
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
			_preconditions = ( AND( AND(at(agent, p), goal(agent, p)), NOT(stopped(agent)) ))
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


def print_all():
    x_spots = [
        [1],
        [2],
        [3],
        [4],
        [5],
        [6],
        [7],
        [8],
        [9],
        [10],
        [1, 2],
        [1, 4],
        [2, 5],
        [2, 7],
        [3, 8],
        [3, 10],
        [4, 11],
        [4, 13],
        [5, 14],
        [1, 2, 3],
        [1, 3, 5],
        [1, 4, 7],
        [2, 5, 8],
        [2, 6, 10],
        [2, 7, 12],
        [3, 8, 13],
        [3, 9, 15]
    ]
    goals = [
        [['c0', 'x1'], ['c1', 'c2']],
        [['c0', 'x2'], ['c2', 'c4']],
        [['c0', 'x3'], ['c3', 'c6']],
        [['c0', 'x4'], ['c4', 'c8']],
        [['c0', 'x5'], ['c5', 'c10']],
        [['c0', 'x6'], ['c6', 'c12']],
        [['c0', 'x7'], ['c6', 'c14']],
        [['c0', 'x8'], ['c6', 'c16']],
        [['c0', 'x9'], ['c6', 'c18']],
        [['c0', 'x10'], ['c6', 'c20']],
        [['c0', 'x1'], ['c1', 'x2'], ['c2', 'c3']],
        [['c0', 'x1'], ['c1', 'x4'], ['c4', 'c5']],
        [['c0', 'x2'], ['c2', 'x5'], ['c5', 'c7']],
        [['c0', 'x2'], ['c2', 'x7'], ['c7', 'c9']],
        [['c0', 'x3'], ['c3', 'x8'], ['c8', 'c11']],
        [['c0', 'x3'], ['c3', 'x10'], ['c10', 'c13']],
        [['c0', 'x4'], ['c3', 'x11'], ['c11', 'c15']],
        [['c0', 'x4'], ['c3', 'x13'], ['c13', 'c17']],
        [['c0', 'x5'], ['c3', 'x14'], ['c14', 'c19']],
        [['c0', 'x1'], ['c1', 'x2'], ['c2', 'x3'], ['c3', 'c4']],
        [['c0', 'x1'], ['c1', 'x3'], ['c3', 'x5'], ['c5', 'c6']],
        [['c0', 'x1'], ['c1', 'x4'], ['c4', 'x7'], ['c7', 'c8']],
        [['c0', 'x2'], ['c2', 'x5'], ['c5', 'x8'], ['c8', 'c10']],
        [['c0', 'x2'], ['c2', 'x6'], ['c6', 'x10'], ['c10', 'c12']],
        [['c0', 'x2'], ['c2', 'x7'], ['c7', 'x12'], ['c12', 'c14']],
        [['c0', 'x3'], ['c3', 'x8'], ['c8', 'x13'], ['c13', 'c16']],
        [['c0', 'x3'], ['c3', 'x9'], ['c9', 'x15'], ['c15', 'c18']]
    ]
    starts = [
        ['c2', 'c1'],
        ['c4', 'c2'],
        ['c6', 'c3'],
        ['c8', 'c4'],
        ['c10', 'c5'],
        ['c12', 'c6'],
        ['c14', 'c7'],
        ['c16', 'c8'],
        ['c18', 'c9'],
        ['c20', 'c10'],
        ['c3', 'c2', 'c1'],
        ['c5', 'c4', 'c1'],
        ['c7', 'c5', 'c2'],
        ['c9', 'c7', 'c2'],
        ['c11', 'c8', 'c3'],
        ['c13', 'c10', 'c3'],
        ['c15', 'c11', 'c4'],
        ['c17', 'c13', 'c4'],
        ['c19', 'c14', 'c5'],
        ['c4', 'c3', 'c2', 'c1'],
        ['c6', 'c5', 'c3', 'c1'],
        ['c8', 'c7', 'c4', 'c1'],
        ['c10', 'c8', 'c5', 'c2'],
        ['c12', 'c10', 'c6', 'c2'],
        ['c14', 'c12', 'c7', 'c2'],
        ['c16', 'c13', 'c8', 'c3'],
        ['c18', 'c15', 'c9', 'c3']
    ]
    n_cells = [3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 4, 6, 8, 10, 12, 14, 16, 18, 20, 5, 7, 9, 11, 13, 15, 17, 19]
    file_names = [F"p{i}" for i in range(1, len(n_cells) + 1)]

    for i in range(len(file_names)):
        n_agents = len(starts[i])
        n_worlds = 2 ** n_agents

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
        for j in range(n_cells[i] - 1):
            output += F"adj(c{j}, c{j + 1}), adj(c{j + 1}, c{j}), "
        for j in range(len(x_spots[i])):
            output += F"adj(c{x_spots[i][j]}, x{x_spots[i][j]}), adj(x{x_spots[i][j]}, c{x_spots[i][j]}), "
        output = output[:-2]
        output += F"{nl}]{nl}{nl}"

        # Worlds
        for world in range(n_worlds):
            output += F"{nl}{t}_world w{world} ["
            for j in range(n_cells[i] + len(x_spots[i])):
                if j < n_cells[i]:
                    cell = F"c{j}"
                else:
                    cell = F"x{x_spots[i][j - n_cells[i]]}"
                if cell in starts[i]:
                    output += F"at(a{starts[i].index(cell)}, {cell}), "
                    continue
                output += F"free({cell}), "

            for agent in range(n_agents):
                goal_to_use = 0 if (world % 2 ** (agent + 1) < 2 ** agent) else 1
                output += F"goal(a{agent}, {goals[i][agent][goal_to_use]}), "

            # if world % 2 ** (agent + 1) < 2 ** agent:
            #	if cell == goal_cell = goals[i][agent][0]:
            #		output += F"goal(a{agent}, {cell}), "
            # else:

            output = output[:-2] + ']'

        output += F"{nl}{t}{t}_goal = [" 
        # AND("
        
        for agent in range(n_agents - 1):
            output += "AND( "
        for agent in range(n_agents):
            output += F"stopped(a{agent})"
            if agent == 0:
                output += ", "
            else:
                output += "), "
        output = output[:-2]
        output += "]\n\t"
        output += r"""
	_designated_worlds = [ w0 ]
"""
        output += "\t_reachability = {\n"

        for agent in range(n_agents):
            output += F"{t}{t}{t}a{agent} = {co}{nl}{t}{t}{t}"
            for k in range(n_worlds):
                for j in range(n_worlds):
                    if ((k % 2 ** (agent + 1) < 2 ** agent and j % 2 ** (agent + 1) < 2 ** agent) or (
                            k % 2 ** (agent + 1) >= 2 ** agent and j % 2 ** (agent + 1) >= 2 ** agent)):
                        output += F"(w{k}, w{j}), "
                output += F"{nl}{t}{t}{t}"
            output += F"{cc}{nl}"

        output += '\t}\n}'
        with open(F"{file_names[i]}.maepl", 'w') as f:
            f.write(output)


print_all()
