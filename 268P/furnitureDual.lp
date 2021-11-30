\ Model Furniture
\ LP format - for model browsing. Use MPS format to capture full model detail.
Minimize
  400 price[mahogany] + 450 price[labor]
Subject To
 V[chair]: 5 price[mahogany] + 10 price[labor] >= 45
 V[table]: 20 price[mahogany] + 15 price[labor] >= 80
Bounds
End
