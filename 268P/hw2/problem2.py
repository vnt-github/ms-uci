from gurobipy import *
f = Model('Crops')
x = f.addVar(name="crop_a_acre")
y = f.addVar(name="crop_b_acre")
f.setObjective(140*x + 235*y, GRB.MAXIMIZE)
f.addConstr(x + y <= 150, 'total_land_available')
f.addConstr(x + 2*y <= 240 , 'total_days_to_crop')
f.addConstr(0.3*x + 0.1*y <= 30 , 'total_days_to_pick')
f.optimize()
for v in f.getVars():
    print(v.varName, v.x)

print(f'Optimal total profit {f.objVal}')