from gurobipy import *
R = ["01", "02", "23", "45", "56"]
J = ["no_type_a", "no_type_b"]

combinations, ms = multidict({
    ("01", "no_type_a"): 3, ("01", "no_type_b"): 8.45,
    ("02", "no_type_a"): 2, ("02", "no_type_b"): 4.53,
    ("23", "no_type_a"): 4, ("23", "no_type_b"): 3.45,
    ("45", "no_type_a"): 2, ("45", "no_type_b"): 3.66,
    ("56", "no_type_a"): 2, ("56", "no_type_b"): 6.26
})

m = Model('RAP')

x = m.addVars(combinations, name='assign', vtype=GRB.INTEGER)

m.addConstr(3*x[("01", "no_type_a")] + 8.45*x[("01", "no_type_b")] >= 2.047, '5')
m.addConstr(2*x[("02", "no_type_a")] + 4.53*x[("02", "no_type_b")] >= 3.478, '6')
m.addConstr(4*x[("23", "no_type_a")] + 3.45*x[("23", "no_type_b")] >= 4.533, '7')
m.addConstr(2*x[("45", "no_type_a")] + 3.66*x[("45", "no_type_b")] >= 3.375, '8')
m.addConstr(2*x[("56", "no_type_a")] + 6.26*x[("56", "no_type_b")] >= 4.919, '9')

m.setObjective(x.prod(ms), GRB.MINIMIZE)
m.write('RAP.lp')

m.optimize()
for v in m.getVars():
    print(v.varName, v.x)
print(m.objVal)
