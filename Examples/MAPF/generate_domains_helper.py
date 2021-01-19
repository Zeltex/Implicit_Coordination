
nl = '\n'
t = '\t'
co = '{'
cc = '}'
worlds = 16
output = ""
for agent in range(4):
	output += F"a{agent} = {co}{nl}"
	for i in range(worlds):
		for j in range(worlds):
			if ((i % 2 ** (agent + 1) < 2 ** agent and j % 2 ** (agent + 1) < 2 ** agent) or (i % 2 ** (agent + 1) >= 2 ** agent and j % 2 ** (agent + 1) >= 2 ** agent)):
				output += F"(w{i}, w{j}), "
		output += '\n'
	output += F"{cc}{nl}"
	
with open(F"temp.txt", 'w') as f:
	f.write(output)
