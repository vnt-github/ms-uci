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


   input: Problem in CNF format
   output: An assignment with maximum satisfiability.
(1)  begin
(2)  for i ← 1 to ∞ do
(3)    T ← Random-Assignment();
(4)     for i ← 1   to  MAX-FLIPS  do
(5)      Ck  ← Random-Unsatisfied-Clause();
(6)     if  (∃ variable v ∈ Ck  with breakcount = 0)  then Chosen-Variable ←  v;
(7)     else  if  (random(0,1)  < pnoise)  then
(8)     Chosen-Variable← Random-Variable(Ck);
(9)     else
(10)      Chosen-Variable Random-Lowest-Break count(Ck);
(11)      end
(12)      end
(13)   end
(14)  end
