# 1. Overview
The nodes are given in the form of std::string. Instead of working with std::string as nodes, thereby, restricting the use of std::vector as a container (for which index are numerals,) for later half of functions, I mapped string IDs to int IDs and vice-versa and worked with ints and indexed into unordered_map<std::string, Node> data structure

Furthermore, other than travelling salesman, almost in every other function iterative form is used/preferred over recursive form. Because, at first go, shortest path (dijkstra) was implemented using recursion and it was taking infinite time to get results, for instance, while parsing 18000+ points, the recursion wouldn't be able to parse 500+ points in about 5 minutes, whereas changing to iterative form immediately improved the timing. Please note that recursion was giving correct results as it was tested pass on smaller total number of data points (7) by using a micro-version of carefully selected data points in the given dataset  



# 2. Detailed description of each function and its time complexity.
## Item 1: Autocomplete The Location Name (Phase 1)
- What is the runtime of your algorithm? 
O(n) as the function iterates over all the elements in the hash map 
- (Optional) Can you do it faster than `O(n)`?



## Item 6: Shortest Path (Phase 2)

 Point A to Point B                                                             | Dijkstra  | Bellman Ford| Bellman Ford optimized|
| --------------------                                                          | ----------|-------------|-----------------------|
| Antioch Temple Baptist Church to Jesus of Nazareth Undenominational Church    | 21ms      | 7839 ms     |-----------------------|
| Antioch Temple Baptist Church to Divine Providence Convent                    | 25ms      | 8879 ms     |
| Foshay Learning Center to Holy Name School                                    | 34ms      | 6569 ms     |
| National Schools to Normandie Elementary School                               | 108ms     | 8185 ms     |
| Saint Agnes Elementary School to Saint Cecilia School                         | 204ms     | 7758 ms     |
| Saint Patrick School to Santa Barbara Avenue School                           | 225ms     | 9653 ms     |
| Trinity Elementary School to Twenty-Eight Street Elementary School            | 40ms      | 8936 ms     |
| Twenty-Fourth Street Elementary School to Vermont Elementary School           | 50ms      | 9465 ms     |
| Wadsworth Elementary School to Washington Boulevard School                    | 253ms     | 10058 ms    |
| West Vernon Elementary School to Jefferson Senior High School                 | 158ms     | 9162 ms     |
| Dockweller Station Los Angeles Post Office to Saint Marks Lutheran Church     | 24ms      | 8075 ms     |
| Saint Patricks Catholic Church to Westvern Station Los Angeles Post Office    | 203ms     | 9745 ms     |
| Pilgrim Congregational Church to Second Baptist Church                        | 215 ms    | 10613 ms    |
| United Church of Christ Scientist to American Hungarian Baptist Church        | 263ms     | 10658 ms    |
| Grace Lutheran Church to Korean Presbyterian Church (나성한인연합장로교회)         | 105ms     | 9193 ms     |

## Item 7: Cycle Detection (Phase 2)
```shell
Input: square = {-118.299, -118.264, 34.032, 34.011}
Output: true

Input: square = {-118.290, -118.289, 34.030, 34.020}
Output: false

Input: square = {-118.284007, -118.2819, 34.0366, 34.035}
Output: true

Input: square = {-118.290, -118.288, 34.030, 34.0285}
Output: false

Input: square = {-118.290, -118.288, 34.030, 34.0255}
Output: true
```


## Item 8: Topological Sort (Phase 2)
- Only Directed Acyclic Graph have a valid topological ordering.
- Time Complexity is O(V+E), where V is the no. of Nodes/vertices and E is the number of Edges
- Tarjan's strongly connected component algo. can be used to find out id the DAG has a cycle
- Every Tree has a topological ordering since trees do not have any cycles
- One way to build the topological sort is to start from the leaves and list all the leaves first followed by their parents and traverse upto the root
- For a graph with recursion, 
  - pick an unvisited node, 
  - beginning with the selected node, do a Depth First Search (DFS) exploring only unvisited node
  - on the recursive callback of the DFS, add the current node to the topological ordering in the reverse order
- references: https://github.com/williamfiset/Algorithms/blob/master/slides/graphtheory/graph_theory_algorithms.pdf
- I have implemented the same without recursion:
- references: https://stackoverflow.com/questions/20153488/topological-sort-using-dfs-without-recursion
```shell
Input: 
location_names = {"Foshay Learning Center", "Holy Name School", "National Schools", "Normandie Elementary School", "Saint Agnes Elementary School"}
dependencies = {{"Saint Agnes Elementary School","Foshay Learning Center"}, {"Foshay Learning Center","Holy Name School"}, {"Foshay Learning Center","National Schools"}, {"Saint Agnes Elementary School","National Schools"},{"National Schools","Normandie Elementary School"}}
Output: {"Saint Agnes Elementary School", "Foshay Learning Center","Holy Name School", "National Schools", "Normandie Elementary School"}


location_names = {"Saint Cecilia School", "Saint Patrick School", "Santa Barbara Avenue School", "Trinity Elementary School", "Twenty-Eight Street Elementary School", "Vermont Elementary School", "Wadsworth Elementary School"};
dependencies = {{"Saint Cecilia School","Saint Patrick School"}, {"Santa Barbara Avenue School","Saint Patrick School"}, {"Trinity Elementary School","Saint Patrick School"}, {"Twenty-Eight Street Elementary School","Saint Patrick School"},{"Twenty-Eight Street Elementary School","Vermont Elementary School"}, {"Wadsworth Elementary School","Vermont Elementary School"}} 
Output: {"Wadsworth Elementary School", "Twenty-Eight Street Elementary School", "Vermont Elementary School", "Trinity Elementary School", "Santa Barbara Avenue School", "Saint Cecilia School", "Saint Patrick School"}
```

## Item 9: Travelling Salesman (Phase 3)

| Number of Places | Bruteforce | Bruceforce with backtracking |   2-opt    |
| -----------------|------------|------------------------------|------------|
|        5         |   0 ms     |             0 ms             |    0 ms    |
|        6         |   1 ms     |             0 ms             |    1 ms    |
|        7         |   21 ms    |             5 ms             |    0 ms    |
|        8         |   788 ms   |            27 ms             |    2 ms    | 

# 3. Time spent for each function.
# 4. Discussion, conclusion, and lessons learned.


## lessons learned
- start with a small testing set, since its easier to debug, for instance, in the travelling salesman problem with 2-opt, the algorithm was going into infinite loop and the distance was getting negative, even though the implementation was borrowed from wikipedia, after beginning with a 4 locations, the bug was found out 

## problems faced
- while using vscode with gdb, many attempts were made to to see the contents inside the data structures like unordered_map and ordered_map. Though the run and debug window shows the inside contents, but restricts it to 500 entries, that was insufficient at one time, after trying out various ways as listed here: https://stackoverflow.com/questions/40633787/cannot-evaluate-function-may-be-in-lined-error-in-gdb-for-stl-template-cont?noredirect=1&lq=1 and
https://stackoverflow.com/questions/40173061/gdb-stl-functions-still-show-as-inlined-after-disabling-optimizations and
https://github.com/microsoft/vscode-cpptools/issues/69, still I couldn't peek inside from debug console.
For instance, data("2613081566") would give a prompt of "Cannot evaluate function -- may be inlined", thus i have to use traditional methods like having debug variables etc.. 