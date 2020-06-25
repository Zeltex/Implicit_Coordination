for entry in ./dot/*
do
	if [[ $entry == *.dot ]]
	then
		dest=${entry%.dot}
		dest=${dest#"./dot/"}
		dot -Tpng $entry > ./png/${dest}.png
	fi
done
