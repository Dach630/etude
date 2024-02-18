type lettreOuVide =
  |Some of char
  |None
  
type leaf =
    Leaf of (char option*char*int*string)

type node =
    Node of (int * (leaf list))

type tree = node list
;;