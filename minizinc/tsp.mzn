% Solving Traveling Salesman Problem with ncities

% 
% Traveling Salesman Problem, integer programming model in MiniZinc.

% number of nodes 
int: n;

% set of arcs 
int: num_edges;
array[1..num_edges, 1..2] of 1..n: E;

% distance from node i to node j 
array[1..num_edges] of int: c;

% x[i,j] = 1 means that the salesman goes from node i to node j 
array[1..num_edges] of var 0..1: x;

% y[i,j] is the number of cars, which the salesman has after leaving
% node i and before entering node j; in terms of the network analysis,
% y[i,j] is a flow through arc (i,j) 
array[1..num_edges] of var int: y;

% the objective is to make the path length as small as possible 
var int: total = sum(i in 1..num_edges) (c[i] * x[i]);
solve :: int_search(
    [x[i] | i in 1..num_edges] ++
    [y[i] | i in 1..num_edges] ++
    [total],
   first_fail, % "occurrence",
   indomain_max,
   complete
   )
   minimize total;

constraint

   % the salesman leaves each node i exactly once 
   forall(i in 1..n) (
        sum(k in 1..num_edges where E[k,1] = i) (x[k]) = 1
   )

   /\

   % the salesman enters each node j exactly once 
   forall(j in 1..n) (
        sum(k in 1..num_edges where E[k,2] = j) (x[k]) = 1
   )

   /\

   % """
   % Constraints above are not sufficient to describe valid tours, so we
   % need to add constraints to eliminate subtours, i.e. tours which have
   % disconnected components. Although there are many known ways to do
   % that, I invented yet another way. The general idea is the following.
   % Let the salesman sells, say, cars, starting the travel from node 1,
   % where he has n cars. If we require the salesman to sell exactly one
   % car in each node, he will need to go through all nodes to satisfy
   % this requirement, thus, all subtours will be eliminated. 
   % 

   % if arc (i,j) does not belong to the salesman's tour, its capacity
   % must be zero; it is obvious that on leaving a node, it is sufficient
   % to have not more than n-1 cars 
   % """
   forall(k in 1..num_edges) (
      y[k] >= 0
      /\
      y[k] <= (n-1) * x[k]
   )

   /\
   % node[i] is a conservation constraint for node i 
   forall(i in 1..n) (
      % summary flow into node i through all ingoing arcs 
      (
      sum(k in 1..num_edges where E[k,2] = i) (y[k])
      % plus n cars which the salesman has at starting node 
      + (if i = 1 then n else 0 endif)
      )
      = % must be equal to 
      % summary flow from node i through all outgoing arcs 
      (
      sum(k in 1..num_edges where E[k,1] = i) (y[k])
      % plus one car which the salesman sells at node i 
      + 1
      )
   )

;

output [
   "total: " ++ show(total) ++ "\n" ++
   "x: " ++ show(x) ++ "\n" ++
   "y: " ++ show(y) ++ "\n"

];

