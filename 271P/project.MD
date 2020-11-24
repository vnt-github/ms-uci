WalkSAT for MAX-SAT
MAXWalkSAT(clauses, p, max_flips) returns a satisfying model or failure
	For i ← 1 to MAX_TRIES do
		For j ← 1 to max_flips do
			Model ← a random assignment of true/false to the symbols in clauses
			If model satisfies clauses return model
			If random(0, 1) < p then
				Flip value in the model of a randomly selected symbol from clause
			Else flip whichever symbol in clause maximizes the no of satisfied clause
	Return model
