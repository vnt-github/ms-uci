import gurobipy
resources, capacity = gurobipy.multidict({
    'mahogany': 400,
    'labor': 450
})

products, price = gurobipy.multidict({
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

shadowPrice = f.addVars(resources, name="price")
pro = f.addConstrs(((sum(bom[r,p]*shadowPrice[r] for r in resources) >= price[p] ) for p in products), name = 'V')
f.setObjective(shadowPrice.prod(capacity))

f.write('furnitureDual.lp')

f.optimize()

for v in f.getVars():
    if (abs(v.x) > 1e-6):
        print(v.varName, v.x)

print('total revenue', f.objVal)

for p in pro:
    if (abs(pro[p].Pi) > 1e-6):
        print(pro[p].ConstrName, pro[p].Pi)
