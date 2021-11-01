\ Model RAP
\ LP format - for model browsing. Use MPS format to capture full model detail.
Minimize
  3 assign[01,no_type_a] + 8.45 assign[01,no_type_b]
   + 2 assign[02,no_type_a] + 4.53 assign[02,no_type_b]
   + 4 assign[23,no_type_a] + 3.45 assign[23,no_type_b]
   + 2 assign[45,no_type_a] + 3.66 assign[45,no_type_b]
   + 2 assign[56,no_type_a] + 6.26 assign[56,no_type_b]
Subject To
 5: 3 assign[01,no_type_a] + 8.45 assign[01,no_type_b] >= 2.047
 6: 2 assign[02,no_type_a] + 4.53 assign[02,no_type_b] >= 3.478
 7: 4 assign[23,no_type_a] + 3.45 assign[23,no_type_b] >= 4.533
 8: 2 assign[45,no_type_a] + 3.66 assign[45,no_type_b] >= 3.375
 9: 2 assign[56,no_type_a] + 6.26 assign[56,no_type_b] >= 4.919
Bounds
Generals
 assign[01,no_type_a] assign[01,no_type_b] assign[02,no_type_a]
 assign[02,no_type_b] assign[23,no_type_a] assign[23,no_type_b]
 assign[45,no_type_a] assign[45,no_type_b] assign[56,no_type_a]
 assign[56,no_type_b]
End
