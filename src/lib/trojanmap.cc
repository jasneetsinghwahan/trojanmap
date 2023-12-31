#include "trojanmap.h"
//#include "mapui.h"

//-----------------------------------------------------
// TODO: Students should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id. If id does not exist, return
 * -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(const std::string &id) { 
  return 0;
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist,
 * return -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string &id) {
  return 0;
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return
 * "NULL".
 *
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string &id) {
  return "";
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node. If id does not exist, return
 * an empty vector.
 *
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(const std::string &id) {
  return {};
}

/**
 * GetID: Given a location name, return the id.
 * If the node does not exist, return an empty string.
 * The location name must be unique, which means there is only one node with the name.
 *
 * @param  {std::string} name          : location name
 * @return {std::string}               : id
 */
std::string TrojanMap::GetID(const std::string &name) {
  std::string res = "";
  return res;
}

/**
 * GetPosition: Given a location name, return the position. If id does not
 * exist, return (-1, -1).
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::pair<double, double> results(-1, -1);
  // returns an empty string if the input is empty
  if (!name.size()) return results;
  auto itr = data.begin();
  bool match = false;
  for (; itr != data.end(); ++itr){
    // at each iteration, compare the data->second.name with the prefix
    if(itr->second.name.compare(0,itr->second.name.size(), name, 0,name.size()) == 0){
      match = true;
      break;
    }
  }
  if (match){
    results.first = itr->second.lat;
    results.second = itr->second.lon;
    //MapUI m;
    //m.PlotPoint(itr->second.lat, itr->second.lon);
  }

  return results;
}

/**
 * CalculateEditDistance: Calculate edit distance between two location names
 * @param  {std::string} a          : first string
 * @param  {std::string} b          : second string
 * @return {int}                    : edit distance between two strings
 */
int TrojanMap::CalculateEditDistance(std::string a, std::string b) {     
  int alen = a.size();
  int blen = b.size();
  std::vector<std::vector<int>> t(alen+1,std::vector<int>(blen+1,0));
  for (int i = 0; i <= alen; i++) t[i][0] = i;
  for (int j = 0; j <= blen; j++) t[0][j] = j;
  for (int i = 1; i < alen+1; i++){
    for (int j = 1; j < blen+1; j++){
      if(a[i-1] == b[j-1])
        t[i][j] = 0 + t[i-1][j-1];
      else {
        // i,j-1                - for insertion
        // i-1,j                - for deletion
        // i-1,j-1              - for replacement
        t[i][j] = 1 + std::min(t[i-1][j-1], std::min(t[i-1][j], t[i][j-1]));
      }
    }
  }
  return t[alen][blen];
  //return CalculateEditDistanceutil(a,b,alen-1,blen-1, t);
}

// sources:
// https://www.youtube.com/watch?v=l02UxPYRmCQ&list=PL_z_8CaSLPWekqhdCPmFohncHwz8TY2Go&index=2
// https://takeuforward.org/data-structure/edit-distance-dp-33/
int 
TrojanMap::CalculateEditDistanceutil(const std::string &a, 
                                    const std::string &b, 
                                    int i, int j, 
                                    std::vector<std::vector<int>> t){
  // base case
  if(i < 0) return j+1;
  if(j < 0) return i+1;
  // memoization
  if (t[i][j] != -1) return t[i][j];
  // if match
  if(a[i] == b[j])
    return t[i][j] = 0 + CalculateEditDistanceutil(a,b,i-1,j-1,t);
  else {
    // else
    // CalculateEditDistanceutil(a,b,i,j-1,t) - for insertion
    // CalculateEditDistanceutil(a,b,i-1,j,t) - for deletion
    // CalculateEditDistanceutil(a,b,i-1,j-1,t) - for replacement
    t[i][j] = 1 + std::min(CalculateEditDistanceutil(a,b,i,j-1,t), 
                            std::min(CalculateEditDistanceutil(a,b,i-1,j,t), CalculateEditDistanceutil(a,b,i-1,j-1,t)));
    return t[i][j];
  }
}

/**
 * FindClosestName: Given a location name, return the name with the smallest edit
 * distance.
 *
 * @param  {std::string} name          : location name
 * @return {std::string} tmp           : the closest name
 */
std::string TrojanMap::FindClosestName(std::string name) {
  std::string tmp = ""; // Start with a dummy word
  if (!name.size()) return tmp;
  std::string pre(name);
  transform(name.begin(),name.end(),pre.begin(),::tolower);
  auto itr = data.begin();
  int mindist = INT_MAX;
  int currdist;
  int i = 0;
  for (; itr != data.end(); ++itr){
    i++;
    std::string lcname(itr->second.name);
    if (!lcname.size()) continue;
    transform(itr->second.name.begin(),itr->second.name.end(),lcname.begin(),::tolower);
    currdist = CalculateEditDistance(pre,lcname);
    if(lcname == "Ralphs");
    if (mindist > currdist){
      mindist = currdist;
      tmp = itr->second.name;
    }
  }
  return tmp;
}

/**
 * Autocomplete: Given a partial name return all the possible locations with
 * partial name as the prefix. The function should be case-insensitive.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name) {
  std::vector<std::string> results;
  // returns an empty string if the input is empty
  if (!name.size()) return results;
  std::string pre(name);
  transform(name.begin(),name.end(),pre.begin(),::tolower);

  // use an iterator to iterate through the unordered map
  auto itr = data.begin();
  for (; itr != data.end(); ++itr){
    // at each iteration, compare the data->second.name with the prefix
    std::string lcname(itr->second.name);
    transform(itr->second.name.begin(),itr->second.name.end(),lcname.begin(),::tolower); 
    if(lcname.compare(0,pre.size(),pre) == 0) results.push_back(itr->second.name);
  }
  return results;
}

/**
 * GetAllCategories: Return all the possible unique location categories, i.e.
 * there should be no duplicates in the output.
 *
 * @return {std::vector<std::string>}  : all unique location categories
 * limitation: assumed that only one attribute exists for a location
 */
std::vector<std::string> TrojanMap::GetAllCategories() {
  std::vector<std::string> results;
  std::unordered_set<std::string> str_attr;
  auto itr = data.begin();
  for (; itr != data.end(); ++itr){
    if(!itr->second.attributes.empty()){    // if the attributes exist
      auto itr_attr = itr->second.attributes.begin();
      if(!(*itr_attr).empty()){             // check not needed
        str_attr.insert(*itr_attr);
      }
    }
  }
  auto itr2_attr = str_attr.begin();
  while(itr2_attr != str_attr.end()){
    results.push_back(*itr2_attr);
    ++itr2_attr;
  }
  return results;
}

/**
 * GetAllLocationsFromCategory: Return all the locations of the input category (i.e.
 * 'attributes' in data.csv). If there is no location of that category, return
 * (-1, -1). The function should be case-insensitive.
 *
 * @param  {std::string} category         : category name (attribute)
 * @return {std::vector<std::string>}     : ids
 */
std::vector<std::string> TrojanMap::GetAllLocationsFromCategory(
    std::string category) {
  std::vector<std::string> res;
  // if the input string is empty, then return (-1, -1)
  if (category.empty()) {
    res.push_back("-1, -1");
    return res;
  }

  // if the input category doesn't exactly matches (ignore case) then return (-1, -1)
  std::string pre(category);
  transform(category.begin(),category.end(),pre.begin(),::tolower);       // copy to another and convert to lower case
  std::vector<std::string> allcategorylist = TrojanMap::GetAllCategories();
  bool match = false;
  for (auto it = allcategorylist.begin(); it != allcategorylist.end(); ++it){
    std::string ith_category(*it);
    transform(ith_category.begin(), ith_category.end(), ith_category.begin(), ::tolower);   // convert to lower case
    if(ith_category == pre){
      match = true;
      break;
    }
  }
  if (match == false){
    res.push_back("-1, -1");
    return res;
  }

  // list all the id's for the input category
  auto itr = data.begin();
  for (; itr != data.end(); ++itr){
    if(!itr->second.attributes.empty()){        // if the attributes exist
      auto eachlocattr_itr = itr->second.attributes.begin();
      while(eachlocattr_itr != itr->second.attributes.end()){       // few locations  have multiple attributes
        std::string lowcasename(*eachlocattr_itr);                  // attributes matching is case insensitive
        transform(lowcasename.begin(),lowcasename.end(),lowcasename.begin(),::tolower);
        if(lowcasename == pre){
          res.push_back(itr->second.id);
        }
        ++eachlocattr_itr;
      }
    }
  }
  return res;
}

/**
 * GetLocationRegex: Given the regular expression of a location's name, your
 * program should first check whether the regular expression is valid, and if so
 * it returns all locations that match that regular expression.
 *
 * @param  {std::regex} location name      : the regular expression of location
 * names
 * @return {std::vector<std::string>}     : ids
 * sources for generating and manually checking the regex: https://regexr.com/
 */
std::vector<std::string> TrojanMap::GetLocationRegex(std::regex location) {
  std::vector<std::string> res;
  try {
    auto itr = data.begin();
    for (; itr != data.end(); ++itr){
        if(std::regex_search(itr->first, location))
          res.push_back(itr->first);
    }
  } catch (std::regex_error& e) {
    return res; 
  }
  return res;
}

/**
 * CalculateDistance: Get the distance between 2 nodes.
 * We have provided the code for you. Please do not need to change this function.
 * You can use this function to calculate the distance between 2 nodes.
 * The distance is in mile.
 * The distance is calculated using the Haversine formula.
 * https://en.wikipedia.org/wiki/Haversine_formula
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id,
                                    const std::string &b_id) {
  // Do not change this function
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2), 2.0) + cos(a.lat * M_PI / 180.0) *
                                           cos(b.lat * M_PI / 180.0) *
                                           pow(sin(dlon / 2), 2.0);
  double c = 2 * asin(std::min(1.0, sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations
 * inside the vector.
 * We have provided the code for you. Please do not need to change this function.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0; i < int(path.size()) - 1; i++) {
    sum += CalculateDistance(path[i], path[i + 1]);
  }
  return sum;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path
 * which is a list of id. Hint: Use priority queue.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 * 
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
  std::map<std::string, double> d;
  std::string srcid, destid;
  std::unordered_map<std::string, std::vector<std::string>> path;
  // get the ids from the names 
  auto data_itr = data.begin();  
  for (; data_itr != data.end(); ++data_itr){
    std::string currname = data_itr->second.name;
    d[data_itr->first] = DBL_MAX;
    if(!currname.empty()){
      if(currname == location1_name) {
        srcid = data_itr->first;
      }
      else if (currname == location2_name){
        destid = data_itr->first;
      }
    }
  }
  d[srcid] = 0;
  path[srcid].push_back(srcid);
  std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<std::pair<double, std::string>>> pq;

  pq.push(std::make_pair(0,srcid));
  while(!pq.empty()){
    auto t = pq.top();
    pq.pop();
    auto nodebeingvisited = t.second;
    if(nodebeingvisited == destid) break;
    std::vector<std::string> neighbors = data[nodebeingvisited].neighbors;
    for(int i = 0; i < neighbors.size(); ++i){
      double dist = CalculateDistance(nodebeingvisited, neighbors[i]);
      // nodes that are visited shall not meet this if condition, it is akin to 'visited'
      if(d[neighbors[i]] > d[nodebeingvisited] + dist){
        d[neighbors[i]] = d[nodebeingvisited] + dist;
        path[neighbors[i]] = path[nodebeingvisited];
        path[neighbors[i]].push_back(neighbors[i]);
        pq.push({d[neighbors[i]], neighbors[i]});
      }
    }
  }
  return path[destid];
}

std::map<std::string, std::set<std::string>> TrojanMap::GetPredecessors() {
  std::map<std::string, std::set<std::string>> pre;
  for (auto i = data.begin(); i != data.end(); i++) {
    for (auto j = i->second.neighbors.begin(); j != i->second.neighbors.end(); j++) {
        pre[*j].insert(i->first);
    }
  }
  return pre;
}

void pathVec(std::vector<int> &path, std::vector<int> &parent, int currNode)
{
  if (parent[currNode] == -1)
  {
    return;
  }
  path.push_back(parent[currNode]);
  pathVec(path, parent, parent[currNode]);
}
//void pathVec(std::vector<std::string> &path, std::map<std::string, std::string> &parent, std::string currNode)
//{
//  if (parent[currNode] == "")
//  {
//    return;
//  }
//  path.push_back(parent[currNode]);
//  pathVec(path, parent, parent[currNode]);
//}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest
 * path which is a list of id. Hint: Do the early termination when there is no
 * change on distance.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name) {
  std::vector<double> distance(data.size(), DBL_MAX);
  std::vector<double> distance_onepast(data.size(), DBL_MAX);
  std::string srcid, destid;
  std::vector<int> parent(data.size(),-1);
  std::vector<int> path;
  ///* get the ids from the names */
  auto data_itr = data.begin();  
  for (; data_itr != data.end(); ++data_itr){
    std::string currname = data_itr->second.name;
    if(!currname.empty()){
      if(currname == location1_name) {
        srcid = data_itr->first;
      }
      else if (currname == location2_name){
        destid = data_itr->first;
      }
    }
  }

  // string to ints and vice-versa for easier debugging and ability to work with vectors
  data_itr = data.begin();
  for (int i = 0; i < data.size(); i++){
    idxidopint[data_itr->first] = i;
    idxintopstr[i] = data_itr->first;
    data_itr++;
  }  

  auto pre = GetPredecessors();
  distance[idxidopint[srcid]] = 0;
  for (auto i = 0; i < data.size() - 1; ++i){
    for (auto v = 0; v < data.size(); ++v){       // loop over all the neighbors of this node
      for (auto u : pre[idxintopstr[v]]) {
        if(distance[v] > distance[idxidopint[u]] + CalculateDistance(idxintopstr[v], u)){
          distance[v] = distance[idxidopint[u]] + CalculateDistance(idxintopstr[v], u);
          parent[v] = idxidopint[u];
        } 
      }
    }
    if (i > 0 && distance_onepast == distance){
      break;
    }
    distance_onepast = distance;
  }
  path.push_back(idxidopint[destid]);
  pathVec(path, parent, idxidopint[destid]);
  // reverse and replace int ids with string ids
  std::vector<std::string> fwdpath;
  for (int i = path.size() - 1; i >= 0; i--)
  {
    fwdpath.push_back(idxintopstr[path[i]]);
  }
  return fwdpath;
}

/**
 * Traveling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path, 
 *                                                                      for example: {10.3, {{0, 1, 2, 3, 4, 0}, {0, 1, 2, 3, 4, 0}, {0, 4, 3, 2, 1, 0}}},
 *                                                                      where 10.3 is the total distance, 
 *                                                                      and the first vector is the path from 0 and travse all the nodes and back to 0,
 *                                                                      and the second vector is the path shorter than the first one,
 *                                                                      and the last vector is the shortest path.
 */
// Please use brute force to implement this function, ie. find all the permutations.
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Brute_force(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  std::priority_queue<std::pair<double, std::vector<std::string>>, std::vector<std::pair<double, std::vector<std::string>>>, std::greater<std::pair<double, std::vector<std::string>>>> allrecords;

  std::vector<std::string>::iterator data_itr = location_ids.begin();
  for (int i = 0; i < location_ids.size(); i++){
    idxidopint[*data_itr] = i;
    idxintopstr[i] = *data_itr;
    data_itr++;
  } 

  int start = idxidopint[location_ids[0]];    // '0' is agnostic, can be any other number
  std::vector<int> cur_path = {start};
  std::vector<int> min_path;
  records.first = DBL_MAX;
  int rstidx = 0;
  TSP_aux5(start, location_ids, start, 0.0, cur_path, rstidx, allrecords, false); 
  // need to sort the results in descending order of path length
  bool first = true;
  int pos = int(allrecords.size())-1;
  while(allrecords.size()){
    if (first){
      auto& minele = allrecords.top();
      records.first = minele.first;
      records.second.insert(records.second.begin(),minele.second);
      first = false;
      allrecords.pop();
      continue;
    }
    auto& ele = allrecords.top();
    records.second.insert(records.second.begin(),ele.second);
    allrecords.pop();
  }
  return records;
}


void TrojanMap::TSP_aux5(int start, 
                          std::vector<std::string> &location_ids,
                          int cur_node, double cur_cost,
                          std::vector<int> &cur_path, 
                          int &rstidx,
                          std::priority_queue<std::pair<double, std::vector<std::string>>, std::vector<std::pair<double, std::vector<std::string>>>, std::greater<std::pair<double, std::vector<std::string>>>> &allrecords,
                          bool bt){
  // If we are at a leaf, update min_cost and min_path.
  if (cur_path.size() == location_ids.size()) {
    double final_cost = cur_cost + CalculateDistance(idxintopstr[cur_node], idxintopstr[start]);
    std::vector<std::string> cur_pathstr(cur_path.size());
    // convert the path of ints to path of strings
    for (int i = 0; i < cur_path.size(); i++){
      cur_pathstr[i] = idxintopstr[cur_path[i]];
    }
    cur_pathstr.push_back(idxintopstr[cur_path[start]]);
    //allrecords.insert(std::make_pair<double, std::vector<std::string>>(final_cost, cur_pathstr));
    allrecords.push({final_cost, cur_pathstr});
    return;
  }
  // Early backtracking
  if (bt == true) {
    if (allrecords.size()){
      if (cur_cost > allrecords.top().first) {
        return;
      }
    }
  }
  // Else, evaluate all children.
  for (int i = 0; i < location_ids.size(); i++) {
    if (std::find(cur_path.begin(), cur_path.end(), i) == cur_path.end()) {
      cur_path.push_back(i);
      
      TSP_aux5(start, location_ids,i, cur_cost + CalculateDistance(idxintopstr[cur_node], idxintopstr[i]), cur_path, rstidx, allrecords, bt);

      cur_path.pop_back();
    }
  }
}

// Please use backtracking to implement this function
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  std::priority_queue<std::pair<double, std::vector<std::string>>, std::vector<std::pair<double, std::vector<std::string>>>, std::greater<std::pair<double, std::vector<std::string>>>> allrecords;

  // mapping std::string ids to int and vice-versa
  std::vector<std::string>::iterator data_itr = location_ids.begin();
  for (int i = 0; i < location_ids.size(); i++){
    idxidopint[*data_itr] = i;
    idxintopstr[i] = *data_itr;
    data_itr++;
  } 

  int start = idxidopint[location_ids[0]];    // '0' is agnostic, can be any other number
  std::vector<int> cur_path = {start};
  std::vector<int> min_path;
  records.first = DBL_MAX;
  int rstidx = 0;
  TSP_aux5(start, location_ids, start, 0.0, cur_path, rstidx, allrecords); 
  // need to sort the results in descending order of path length
  bool first = true;
  int pos = int(allrecords.size())-1;
  while(allrecords.size()){
    if (first){
      auto& minele = allrecords.top();
      records.first = minele.first;
      records.second.insert(records.second.begin(),minele.second);
      first = false;
      allrecords.pop();
      continue;
    }
    auto& ele = allrecords.top();
    records.second.insert(records.second.begin(),ele.second);
    allrecords.pop();
  }
  return records;
}


// Perform a 2-opt swap
void TrojanMap::do2Opt(std::vector<std::string> &path, int i, int j) {
  // Reverses the order of the elements in the range [first,last).
	std::reverse(begin(path) + i + 1, begin(path) + j + 1);
}

// Hint: https://en.wikipedia.org/wiki/2-opt
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_2opt(
      std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;
  std::priority_queue<std::pair<double, std::vector<std::string>>, std::vector<std::pair<double, std::vector<std::string>>>, std::greater<std::pair<double, std::vector<std::string>>>> allrecords; 
  
  // mapping std::string ids to int and vice-versa
  std::vector<std::string>::iterator data_itr = location_ids.begin();
  for (int i = 0; i < location_ids.size(); i++){
    idxidopint[*data_itr] = i;
    idxintopstr[i] = *data_itr;
    data_itr++;
  } 

  std::vector<std::string> ipath;      // std::vector is O(1) for indexing
  double curLength = 0;
  int plcCnt = int(location_ids.size());
  // update first path
  ipath = location_ids;
  ipath.push_back(location_ids[0]); 
  curLength = CalculatePathLength(location_ids) + CalculateDistance(location_ids[0], location_ids[plcCnt-1]);
  allrecords.push({curLength, ipath});
  double tenp10epsilon_ = std::pow(10,10)*DBL_EPSILON;
  //2-opt
  bool foundImprovement = true;
	while (foundImprovement) {
		foundImprovement = false;
		for (int i = 0; i <= plcCnt - 2; i++) {
			for (int j = i + 1; j <= plcCnt - 1; j++) {
        std::string dbgi = idxintopstr[i];
        std::string dbgip1 = idxintopstr[(i+1)%plcCnt];
        std::string dbgj = idxintopstr[j];
        std::string dbgjp1 = idxintopstr[(j+1)%plcCnt];
				double disitoip1 = CalculateDistance(idxintopstr[i], idxintopstr[(i+1)%plcCnt]);
				double disjtojp1 = CalculateDistance(idxintopstr[j], idxintopstr[(j+1)%plcCnt]);
				double disitoj = CalculateDistance(idxintopstr[i], idxintopstr[j]);
				double disip1tojp1 = CalculateDistance(idxintopstr[(i+1)%plcCnt], idxintopstr[(j+1)%plcCnt]);
        double lengthDelta = -disitoip1 - disjtojp1 + disitoj + disip1tojp1;
				// If the length of the path is reduced, do a 2-opt swap
        if ((lengthDelta < 0) && (std::fabs(lengthDelta) > tenp10epsilon_)) {
					do2Opt(location_ids, i, j);
					curLength += lengthDelta;
          // update each progressive path
          ipath = location_ids;
          ipath.push_back(location_ids[0]); 
          allrecords.push({curLength, ipath});
					foundImprovement = true;
          // mapping std::string ids to int and vice-versa
          data_itr = location_ids.begin();
          for (int i = 0; i < location_ids.size(); i++){
            idxidopint[*data_itr] = i;
            idxintopstr[i] = *data_itr;
            data_itr++;
          } 
				}
			}
		}
	}

  // need to sort the results in descending order of path length
  bool first = true;
  while(allrecords.size()){
    if (first){
      auto& minele = allrecords.top();
      records.first = minele.first;
      records.second.insert(records.second.begin(),minele.second);
      first = false;
      allrecords.pop();
      continue;
    }
    auto& ele = allrecords.top();
    records.second.insert(records.second.begin(),ele.second);
    allrecords.pop();
  }
  return records;
}

// This is optional
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_3opt(
      std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 * We have provided the code for you. Please do not need to change this function.
 * Example: 
 *   Input: "topologicalsort_locations.csv"
 *   File content:
 *    Name
 *    Ralphs
 *    KFC
 *    Chick-fil-A
 *   Output: ['Ralphs', 'KFC', 'Chick-fil-A']
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(
    std::string locations_filename) {
  std::vector<std::string> location_names_from_csv;
  std::fstream fin;
  fin.open(locations_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, word)) {
    location_names_from_csv.push_back(word);
  }
  fin.close();
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 * We have provided the code for you. Please do not need to change this function.
 * Example: 
 *   Input: "topologicalsort_dependencies.csv"
 *   File content:
 *     Source,Destination
 *     Ralphs,Chick-fil-A
 *     Ralphs,KFC
 *     Chick-fil-A,KFC
 *   Output: [['Ralphs', 'Chick-fil-A'], ['Ralphs', 'KFC'], ['Chick-fil-A', 'KFC']]
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(
    std::string dependencies_filename) {
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::fstream fin;
  fin.open(dependencies_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);
    std::vector<std::string> dependency;
    while (getline(s, word, ',')) {
      dependency.push_back(word);
    }
    dependencies_from_csv.push_back(dependency);
  }
  fin.close();
  return dependencies_from_csv;
}

/**
 * constructs directed acyclic graph
 * @param  {std::vector<std::vector<std::string>>} dependencies                                 : prerequisites
 * @param  {std::unordered_map<std::string, std::vector<std::string>>} &dag                     : results
*/
void TrojanMap::constructdag(std::unordered_map<std::string, std::vector<std::string>> &dag, const std::vector<std::vector<std::string>> &dependencies){
  std::vector<std::string> neighbor;
  for(int i = 0; i < dependencies.size(); ++i){
    const std::string &st = dependencies[i][0];
    const std::string &ed = dependencies[i][1];
    dag[st].push_back(ed);
  }
  return;
} 


/**
 * DeliveringTrojan: Given a vector of location names, it should return a
 * sorting of nodes that satisfies the given dependencies. If there is no way to
 * do it, return a empty vector.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(
    std::vector<std::string> &locations,
    std::vector<std::vector<std::string>> &dependencies) {
  std::vector<std::string> result;
  std::stack<std::pair<bool,int>> dfs;
  std::stack<int> postOrder;
  std::unordered_map<std::string, std::vector<std::string>> dag;

  constructdag(dag, dependencies);
  std::vector<bool> visited(locations.size(), false);

  // mapping std::string ids to int and vice-versa
  std::vector<std::string>::iterator db_itr = locations.begin();
  for (int i = 0; i < locations.size(); i++){
    idxidopint[*db_itr] = i;
    idxintopstr[i] = *db_itr;
    db_itr++;
  }  

  for(int i=0 ; i < locations.size() ; i++){
    if(!visited[i]){
        dfs.push(std::make_pair(false,i));
    }   
    while(!dfs.empty()){
      std::pair<bool,int> node=dfs.top();
      dfs.pop();
      if (node.first) {
          postOrder.push(node.second);
          continue;
      }
      if (visited[node.second]) {
          continue;
      }
      visited[node.second]=true;
      dfs.push(std::make_pair(true, node.second));
      const auto& newVec=dag[idxintopstr[node.second]]; //vector of neighboors
      for(const auto son: newVec){
          if(!visited[idxidopint[son]]){
              dfs.push(std::make_pair(false, idxidopint[son]));
          }
      }
    }
  }

  // populate the results only for the nodes mentioned in the locations list
  while(!postOrder.empty()) {
    //result.insert(result.begin(),idxintopstr[postOrder.top()]);
    result.push_back(idxintopstr[postOrder.top()]);
    postOrder.pop();
  }
  return result;     
}

/**
 * inSquare: Give a id retunr whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square) {
  Node pt = data[id];
  //bool match = false;
  //if (id == "6808089754" || id == "123161946")
  //  match = true;
  //match = false;
  if (pt.lon >= square[0] && pt.lon <= square[1] && pt.lat <= square[2] && pt.lat >= square[3])
    return true;
  return false;
}


/**
 * GetSubgraph: Give four vertexes of the square area, return a list of location
 * ids in the squares
 *
 * @param  {std::vector<double>} square         : four vertexes of the square
 * area
 * @return {std::vector<std::string>} subgraph  : list of location ids in the
 * square
 */
std::vector<std::string> TrojanMap::GetSubgraph(std::vector<double> &square) {
  // include all the nodes in subgraph
  std::vector<std::string> subgraph;
  std::unordered_map<std::string, Node>::iterator db_itr = data.begin();
  for (; db_itr != data.end(); ++db_itr){     // parse all the vertices
    std::string dbg_string = db_itr->first;
    if(inSquare(db_itr->first, square))
      subgraph.push_back(db_itr->first);
  }
  return subgraph;
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true
 * if there is a cycle path inside the square, false otherwise.
 *
 * @param {std::vector<std::string>} subgraph: list of location ids in the
 * square
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 * 
 */
bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square) {

  // preferred way 
  //std::unordered_map<std::string, bool> visited;
  //std::unordered_map<std::string, bool> on_stack;
  //std::stack<std::string> st;
  // make algo. work first way
  std::vector<bool> visited (subgraph.size(), false);
  std::stack<std::pair<int, int>> st;

  // mapping std::string ids to int and vice-versa
  std::unordered_map<std::string, Node>::iterator db_itr = data.begin();
  for (int i = 0; i < data.size(); i++){
    idxidopint[db_itr->first] = i;
    idxintopstr[i] = db_itr->first;
    db_itr++;
  }  

  for (int w = 0; w < subgraph.size(); w++) {

    if (visited[w])
      continue;
    st.push(std::make_pair(w, -1));
    visited[w] = true;

    while (!st.empty()) {
      int s = st.top().first;
      int f = st.top().second;
      st.pop();

      std::string nodeundercon = subgraph[s];
      for (const auto &v : data[nodeundercon].neighbors) {
        auto it_find = std::find(subgraph.begin(), subgraph.end(),v);
        // result wouldn't be found always, some nodes shall be outside the square
        if (it_find == subgraph.end())
          continue;
        auto index = std::distance(subgraph.begin(), it_find);
        if (!visited[index]) {
          st.push(std::make_pair(index,s));
          visited[index] = true;
        } else if (index != f) {
          return true;
        }
      }
    }
  }

  return false;
}

/**
 * FindNearby: Given a class name C, a location name L and a number r,
 * find all locations in class C on the map near L with the range of r and
 * return a vector of string ids
 *
 * @param {std::string} className: the name of the class
 * @param {std::string} locationName: the name of the location
 * @param {double} r: search radius
 * @param {int} k: search numbers
 * @return {std::vector<std::string>}: location name that meets the requirements
 */
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k) {
  std::vector<std::string> res;
  return res;
}

/**
 * Shortest Path to Visit All Nodes: Given a list of locations, return the shortest
 * path which visit all the places and no need to go back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::vector<std::string> }      : the shortest path
 */
std::vector<std::string> TrojanMap::TrojanPath(
      std::vector<std::string> &location_names) {
    std::vector<std::string> res;
    return res;
}

/**
 * Given a vector of queries, find whether there is a path between the two locations with the constraint of the gas tank.
 *
 * @param  {std::vector<std::pair<double, std::vector<std::string>>>} Q : a list of queries
 * @return {std::vector<bool> }      : existence of the path
 */
std::vector<bool> TrojanMap::Queries(const std::vector<std::pair<double, std::vector<std::string>>>& q) {
    std::vector<bool> ans(q.size());
    return ans;
}

/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * We have provided the code for you. Please do not need to change this function.
 */
void TrojanMap::CreateGraphFromCSVFile() {
  // Do not change this function
  std::fstream fin;
  fin.open("src/lib/data.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        if (isalpha(word[0])) n.attributes.insert(word);
        if (isdigit(word[0])) n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}
