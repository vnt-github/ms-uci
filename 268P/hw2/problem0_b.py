import gurobipy
resource, capacity = gurobipy.multidict({
    'mahogany': 400,
    'labor': 450
})

products, prices = gurobipy.multidict({
    'chair': 45,
    'table': 80
})

bom = {
    ('mahogany', 'chair'): 5,
    ('mahogany', 'table'): 20,
    ('labor', 'chair'): 10,
    ('labor', 'table'): 15
}

f = gurobipy.Model('Furniture')

make = f.addVars(products, name="make")
res = f.addConstr(
    ((sum(bom[r,p]*make[p] for p in products) <= capacity[r] for r in resource), 'R')
)

f.setObjective(make.prod(revenue), gurobipy.GRB.MAXIMIZE)

f.write('furniture.lp')
