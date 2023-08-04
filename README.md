# 1. Overview
+ The nodes are given in the form of std::string. Instead of working with std::string as nodes, thereby, restricting the use of std::vector as a container (for which index are numerals,) for later half of functions, I mapped string IDs to int IDs and vice-versa and worked with ints and indexed into unordered_map<std::string, Node> data structure

+ Furthermore, other than travelling salesman, almost in every other function iterative form is used/preferred over recursive form. Because, at first go, shortest path (dijkstra) was implemented using recursion and it was taking infinite time to get results, for instance, while parsing 18000+ points, the recursion wouldn't be able to parse 500+ points in about 5 minutes, whereas changing to iterative form immediately improved the timing. Please note that recursion was giving correct results as it was tested pass on smaller total number of data points (7) by using a micro-version of carefully selected data points in the given dataset  



# 2. Detailed description of each function and its time complexity.
## Item 1: Autocomplete The Location Name (Phase 1)
+ What is the runtime of your algorithm? 
O(n) as the function iterates over all the elements in the unordered map

+ (Optional) Can you do it faster than `O(n)`?
TBD

| Query              | time spent |
| -------------------|------------|
| stAR               | 3 ms       |
| holy name          | 6 ms       |
| washington         | 8 ms       |

Current limitations: when I enter "school" then following errors comes:
```shell
terminate called after throwing an instance of 'std::invalid_argument'
  what():  stoi
Aborted (core dumped)
```
## Item 2-1: GetPosition
+ time complexity: upto linear
+ method: iterate through the entire map and at each iteration compare the database name (if name exists) withe the input name

| Query              | time spent |
| -------------------|------------|
| National Schools   | 2 ms       |
| Arco               | 3 ms       |
| Ramen KenJo        | 0 ms       |


## Item 2-2: EditDistance
+ time complexity: O(mn) where m and n are the lengths of the two given strings
+ method:
  + Initially recursive method was tried, but it was too slow, hence, tabulation method was chosen
  + we always try to find min of three operations i.e. replacement or insertion or deletion 

![editdistance_using_tabulation](https://github.com/ee538/sum23-trojanmap-jasneetsinghwahan/blob/main/report/editdistance_using_tabulation.jpg)

| Query              | prompt     | time spent | reply |
| -------------------|------------|------------|-------|
| help               | Shell      |    4 ms    |   y   |
| please             | Chase      |    4 ms    |   y   |
| thanks             | Chase      |    3 ms    |   n   |

## Item 3: Get All Categories
+ time complexity: O(n) where n are the number of elements in the database, please note that insertion in unordered_map is O(constant) complexity 
+ method:
  + data structure: unordered set was used to store the categories, as unordered map is implemented in stl with a characteristics that it doesn't stores duplicates
  + we always try to find min of three operations i.e. replacement or insertion or deletion 

## Item 4: Get All Locations In A Category
+ time complexity: O(n) as we perform 2 separate instances of parsing the entire database, once to construct the categories list and second time to parse each location for matching attribute same as category 

## Item 5: Get Locations Using A Regular Expression
+ method: we parse the entire database leading to time complexity of O(n) and for each element, we perform reg_ex search that has a complexity of O(n)
+ time complexity: total time complexity is O(nm) where n is the length of the database and m is the length of the string being matched 

## Item 6: Shortest Path (Phase 2)
### dijkstra
+ time complexity: O((|E|+|V|)log|V|) where E is the number of edges and V is the number of vertices, this time complexity is applicable since priority queue (min heap) was implemented

+ method: 
  + this algo. calculates the 
  + After not finding any way to work with std::string as indexes, since, I wasn't able to peek into the unordered_map in vsocde using gdb and within debug console, i took inspiration from this code https://github.com/ee538/final-project-Eric-Zheng29 where the author has converted all the stringnodes to ints and vice-versa and therefore used a simpler dat structure like a vector to peek into individiual values at debug time as well set break-points. 
  + Furthermore, i looked at the code to figure out how to draw the path https://github.com/dlwsdqdws/Trojan-Map/blob/master/src/lib/trojanmap.cc 

+ data structures: 
  + priority queue with a pair of distance (first element) and node name (std::string)
  + unordered_map (acting like a vector of vectors of strings) with nodename (std::string) as the key and vector of strings as the value to store the path for every other node from the source node 


### bellman-ford
+ time complexity: O(V*E) as we perform relaxation for all the edges n-1 times (one less than the number of nodes)
+ method: 
  + loop-over V-1 times into E times for each Node/Vertex where E comes from adjacency list and check the distances 
  + each time among the given parents, a parent is found to be the min., we update the parent of that node into parent vector
![bellman-ford_using_tabulation](https://github.com/ee538/sum23-trojanmap-jasneetsinghwahan/blob/main/report/bellman-ford_using_tabulation.jpg)
  + at last, we iterate parents backwards to get the path

### results
| Point A to Point B                                                            | Dijkstra  | Bellman Ford| Bellman Ford optimized|
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
+ time complexity: O(V + E)
+ method: 
  + iterative approach adopted instead of recursion
  + start with any node, this algo. is agnostic of teh starting node
  + mark the node as visited and for the starting node, mark its parents as -1 (indicating its the starting node)
  + enlist all its neighbours
  + visit each neighbor, if the neighbor is unvisited, then record its ID and its parent ID in the stack
  + if the neighbor is visited, then check, if neighbor ID's match the ID of the parent, if yes, its a cycle
  + algo. works for disconnected graph as well, as we traverse all the nodes
+ sources: https://stackoverflow.com/questions/31532887/detecting-cycle-in-an-undirected-graph-using-iterative-dfs

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
+ time complexity: 
+ data structure:
  + a special stack that stored a pair where first element was `true` for a parent and `false` for a child  
+ method: 
  + used iterative method for implementation
  > + In order to construct the postOrder list you need to know the time when your algorithm has finished processing the last child of node k.
  > + One way to figure out when you have popped the last child off the stack is to put special marks on the stack to indicate spots where the children of a particular node are starting. You could change the type of your dfs stack to vector<pair<bool,int>>. When the bool is set to true, it indicates a parent; false indicates a child.
  > + When you pop a "child pair" (i.e. one with the first member of the pair set to false) off the stack, you run the code that you currently have, i.e. push all their children onto the stack with your for loop. Before entering the for loop, however, you should push make_pair(true, node) onto the stack to mark the beginning of all children of this node.
  > + When you pop a "parent pair" off the stack, you push the parent index onto the postOrder, and move on:
  + references: https://stackoverflow.com/questions/20153488/topological-sort-using-dfs-without-recursion
### notes
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

```shell

Input: 
location_names = {"Foshay Learning Center", "Holy Name School", "National Schools", "Normandie Elementary School", "Saint Agnes Elementary School"}
dependencies = {{"Saint Agnes Elementary School","Foshay Learning Center"}, {"Foshay Learning Center","Holy Name School"}, {"Foshay Learning Center","National Schools"}, {"Saint Agnes Elementary School","National Schools"},{"National Schools","Normandie Elementary School"}}
Output: {"Saint Agnes Elementary School", "Foshay Learning Center","Holy Name School", "National Schools", "Normandie Elementary School"}


location_names = {"Saint Cecilia School", "Saint Patrick School", "Santa Barbara Avenue School", "Trinity Elementary School", "Twenty-Eight Street Elementary School", "Vermont Elementary School", "Wadsworth Elementary School"};
dependencies = {{"Saint Cecilia School","Saint Patrick School"}, {"Santa Barbara Avenue School","Saint Patrick School"}, {"Trinity Elementary School","Saint Patrick School"}, {"Twenty-Eight Street Elementary School","Saint Patrick School"},{"Twenty-Eight Street Elementary School","Vermont Elementary School"}, {"Wadsworth Elementary School","Vermont Elementary School"}} 
Output: {"Wadsworth Elementary School", "Twenty-Eight Street Elementary School", "Vermont Elementary School", "Trinity Elementary School", "Santa Barbara Avenue School", "Saint Cecilia School", "Saint Patrick School"}
```

## Item 9: Traveling Salesman (Phase 3)
### 2-opt
+ time complexity: 
  + outerloop: till the time we continue to find improvement, can be exponential to subquadratic (source: Tim Roughgarden, )
  + innerloop: replace `each` edge * with all `other` edges in a iteration (the two inner `for` loops) equalling to n*(n-3)/2 or O(n2) for inner loop
![travelling_salesman_2opt_loop_counter_values](https://github.com/ee538/sum23-trojanmap-jasneetsinghwahan/blob/main/report/tsp_2opt.png)

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
### inability to peek inside unordered_map, unordered_set, ordered_map, ordered_set inside debug console using gdb
- while using vscode with gdb, many attempts were made to to see the contents inside the data structures like unordered_map and ordered_map. Though the run and debug window shows the inside contents, but restricts it to 500 entries, that was insufficient at one time, after trying out various ways as listed here: https://stackoverflow.com/questions/40633787/cannot-evaluate-function-may-be-in-lined-error-in-gdb-for-stl-template-cont?noredirect=1&lq=1 and
https://stackoverflow.com/questions/40173061/gdb-stl-functions-still-show-as-inlined-after-disabling-optimizations and
https://github.com/microsoft/vscode-cpptools/issues/69, still I couldn't peek inside from debug console.
For instance, data("2613081566") would give a prompt of "Cannot evaluate function -- may be inlined", thus i have to use traditional methods like having debug variables etc.. 

### unable to set breakpoints for string literals
- tried this approach https://stackoverflow.com/questions/1740858/how-to-create-conditional-breakpoint-with-stdstring to edit break point to set for a speciifc string value, but it didn't work 