#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"
#include <gmock/gmock.h>

//TEST(TrojanMapTest, Autocompletecopied) {
//  TrojanMap m;
//  // Test the simple case
//  auto names = m.Autocomplete("Star");
//  std::unordered_set<std::string> gt = {"Starbucks", "Starbucks 1", "Starbucks 2", "Starbucks 3"}; // groundtruth for "star"
//  int success = 0;
//  for (auto& n: names) {
//    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
//    if (gt.count(n) > 0){
//      success++;
//    }
//  }
//  EXPECT_EQ(success, gt.size());
//  // Test the lower case
//  names = m.Autocomplete("star");
//  success = 0;
//  for (auto& n: names) {
//    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
//    if (gt.count(n) > 0){
//      success++;
//    }
//  }
//  EXPECT_EQ(success, gt.size());
//  // Test the lower and upper case 
//  names = m.Autocomplete("sTAR"); 
//  success = 0;
//  for (auto& n: names) {
//    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
//    if (gt.count(n) > 0){
//      success++;
//    }
//  }
//  EXPECT_EQ(success, gt.size());
//  // Test the upper case 
//  names = m.Autocomplete("STAR"); 
//  success = 0;
//  for (auto& n: names) {
//    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
//    if (gt.count(n) > 0){
//      success++;
//    }
//  }
//  EXPECT_EQ(success, gt.size());
//  // Test empty string
//  names = m.Autocomplete(""); 
//  success = 0;
//  for (auto& n: names) {
//    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
//    if (gt.count(n) > 0){
//      success++;
//    }
//  }
//  EXPECT_EQ(success, 0);
//
//}
//
//TEST(TrojanMapTest, FindPositioncopied) {
//  TrojanMap m;
//  
//  // Test Chick-fil-A
//  auto position = m.GetPosition("First Presbyterian Church");
//  std::pair<double, double> gt1(34.0321559, -118.2722841); // groundtruth for "First Presbyterian Church"
//  EXPECT_EQ(position, gt1);
//  // Test Ralphs
//  position = m.GetPosition("Ralphs");
//  std::pair<double, double> gt2(34.0317653, -118.2908339); // groundtruth for "Ralphs"
//  EXPECT_EQ(position, gt2);
//  // Test Target
//  position = m.GetPosition("Chevron 1");
//  std::pair<double, double> gt3(34.0336409, -118.2620798); // groundtruth for "Chevron 1"
//  EXPECT_EQ(position, gt3);
//  // Test Unknown
//  position = m.GetPosition("7th & Hi");
//  std::pair<double, double> gt4(-1, -1);
//  EXPECT_EQ(position, gt4);
//  // Test empty
//  position = m.GetPosition("");
//  std::pair<double, double> gt5(-1, -1);
//  EXPECT_EQ(position, gt4);
//}
//
//// Test CalculateEditDistance function
//TEST(TrojanMapTest, CalculateEditDistancecopied) {
//  TrojanMap m;
//  EXPECT_EQ(m.CalculateEditDistance("", "ros"), 3);
//  EXPECT_EQ(m.CalculateEditDistance("ros", ""), 3);
//  EXPECT_EQ(m.CalculateEditDistance("abc", "xyz"), 3);
//  EXPECT_EQ(m.CalculateEditDistance("", ""), 0);
//  EXPECT_EQ(m.CalculateEditDistance(" ", ""), 1);
//  EXPECT_EQ(m.CalculateEditDistance("starb uc", "starbucks"), 3);
//}
//
//// Test FindClosestName function
//TEST(TrojanMapTest, FindClosestNamecopied) {
//  TrojanMap m;
//  EXPECT_EQ(m.FindClosestName("Rolphs"), "Ralphs");
//  EXPECT_EQ(m.FindClosestName("starb uc"), "Starbucks");
//}
//
//// Test FindClosestName function
//TEST(TrojanMapTest, FindAllCategories) {
//  TrojanMap m;
//  std::vector<std::string> exp_rst = {"parcel_locker", "car_wash", "childcare", "yes", "driving_school", "dentist", "police", "charging_station", "copyshop", "theatre", "bicycle", "museum", "post_office", "library", "fuel", "hotel", "bank", "convenience", "parking", "clothes", "fast_food", "hairdresser", "restaurant", "yoga", "cafe", "clinic", "parking_entrance", "optician", "bakery", "shoes", "hospital", "beverages", "car_repair", "post_box", "tobacco", "attraction", "fountain", "confectionery", "car", "shoe_repair", "food_court", "artwork", "fabric", "gallery", "social_facility", "supermarket", "pharmacy", "department_store", "mobile_phone", "bar", "skate", "marketplace", "music", "beauty", "bicycle_rental", "bus_station", "school", "place_of_worship"};
//  std::vector<std::string> act_rst = m.GetAllCategories();
//  EXPECT_THAT(act_rst,::testing::Contains("school"));
//  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
//  EXPECT_EQ(act_rst.size(),58);
//}
//
//// Test FindClosestName function
//TEST(TrojanMapTest, GetAllLocationsFromCategory) {
//  TrojanMap m;
//  std::string categoryname = {"artwork"};
//  std::vector<std::string> exp_rst = {"2305853438","4399693645","4536993737","5237417648","6813379578"};
//  std::vector<std::string> act_rst = m.GetAllLocationsFromCategory(categoryname);
//  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
//  EXPECT_EQ(act_rst.size(),5);
//  categoryname = {"bank"};
//  act_rst = m.GetAllLocationsFromCategory(categoryname);
//  exp_rst = {"5237417651", "9591449441","9591449465"};
//  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
//  EXPECT_EQ(act_rst.size(),3);
//  categoryname = {"bnk"};
//  act_rst = m.GetAllLocationsFromCategory(categoryname);
//  exp_rst = {"-1, -1"};
//  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
//  EXPECT_EQ(act_rst.size(),1);
//  categoryname = {""};
//  act_rst = m.GetAllLocationsFromCategory(categoryname);
//  exp_rst = {"-1, -1"};
//  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
//  EXPECT_EQ(act_rst.size(),1);
//  categoryname = {"BANK"};
//  act_rst = m.GetAllLocationsFromCategory(categoryname);
//  exp_rst = {"5237417651", "9591449441","9591449465"};
//  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
//  EXPECT_EQ(act_rst.size(),3);
//}
//
//TEST(TrojanMapTest, GetLocationRegex){
//  TrojanMap m;
//  std::regex ip("9446678097");
//  std::vector<std::string> exp_rst = {"9446678097"};
//  std::vector<std::string> act_rst = m.GetLocationRegex(ip);
//  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
//  EXPECT_EQ(act_rst.size(),1);
//  ip = {"^94{1,2}6{1,2}7809\\d{1}"};
//  exp_rst = {"9446678097","9446678098","9446678099"};
//  act_rst = m.GetLocationRegex(ip);
//  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
//  EXPECT_EQ(act_rst.size(),exp_rst.size());
//}
//
//TEST(TrojanMapTest, CalculateShortestPath_dijkstracopied) {
//  TrojanMap m;
//  auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Ralphs");
//  std::vector<std::string> gt = {};
//  EXPECT_EQ(path, gt);
//  path = m.CalculateShortestPath_Dijkstra("Antioch Temple Baptist Church", "Divine Providence Convent");
//  gt = {"358850024", "122674584", "6816193741", "122674587", "6816193745", "277328088", "277328089", "277328090", "122674590", "1843466234", "4015377693", "6816180170", "6380132756", "6816180168", "1922565218", "2514542031", "4015377692", "6816193690", "123408740", "6816193692", "4015442011", "358850041"};
//  EXPECT_EQ(path, gt);
//  path = m.CalculateShortestPath_Dijkstra("Antioch Temple Baptist Church", "Jesus of Nazareth Undenominational Church");
//  gt = {"358850024", "122674584", "358850058"};
//  EXPECT_EQ(path, gt);
//  
//  // Test from Ralphs to Chick-fil-A
//  path = m.CalculateShortestPath_Dijkstra("Ralphs", "Chick-fil-A");
//  gt = {
//      "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920","6818427919",
//      "6818427918","6818427892","6818427898","6818427917","6818427916","7232024780","6813416145",
//      "6813416154","6813416153","6813416152","6813416151","6813416155","6808069740","6816193785",
//      "6816193786","123152294","4015203136","4015203134","4015203133","21098539","6389467809",
//      "4015203132","3195897587","4015203129","4015203127","6352865690","6813379589","6813379483",
//      "3402887081","6814958394","3402887080","602606656","4872897515","4399697589","6814958391",
//      "123209598","6787673296","122728406","6807762271","4399697304","4399697302","5231967015",
//      "1862347583","3233702827","4540763379","6819179753","6820935900","6820935901","6813379556",
//      "6820935898","1781230450","1781230449","4015405542","4015405543","1837212104","1837212107",
//      "2753199985","6820935907","1837212100","4015372458","6813411588","1837212101","6814916516",
//      "6814916515","6820935910","4547476733"}; // Expected path
//  // Print the path lengths
//  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
//  std::cout << "no. of nodes visited in actual: "  << path.size() << std::endl;
//  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
//  EXPECT_EQ(path, gt);
//  
//  // Reverse the input from Ralphs to Chick-fil-A
//  path = m.CalculateShortestPath_Dijkstra("Chick-fil-A", "Ralphs");
//  std::reverse(gt.begin(),gt.end()); // Reverse the path
//
//  // Print the path lengths
//  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
//  std::cout << "no. of nodes visited in actual: "  << path.size() << std::endl;
//  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
//}

//TEST(TrojanMapTest, CalculateShortestPath_dijkstramini) {
//  TrojanMap m;
//  std::vector<std::string> gt = {};
//  auto path = m.CalculateShortestPath_Dijkstra("Antioch Temple Baptist Church", "Jesus of Nazareth Undenominational Church");
//  gt = {"358850024", "122674584", "358850058"};
//  EXPECT_EQ(path, gt);
//}
//
//
//TEST(TrojanMapTest, CalculateShortestPath_bellmanfordcopied) {
//  TrojanMap m;
//  auto path = m.CalculateShortestPath_Bellman_Ford("Antioch Temple Baptist Church", "Jesus of Nazareth Undenominational Church");
//  std::vector<std::string> gt = {"358850024", "122674584", "358850058"};
//  EXPECT_EQ(path, gt);
//
//  path = m.CalculateShortestPath_Dijkstra("Antioch Temple Baptist Church", "Divine Providence Convent");
//  gt = {"358850024", "122674584", "6816193741", "122674587", "6816193745", "277328088", "277328089", "277328090", "122674590", "1843466234", "4015377693", "6816180170", "6380132756", "6816180168", "1922565218", "2514542031", "4015377692", "6816193690", "123408740", "6816193692", "4015442011", "358850041"};
//  EXPECT_EQ(path, gt);
//}

//TEST(TrojanMapTest, CycleDetectionmini) {
//  TrojanMap m;
//  
//  // Test case 1
//  std::vector<double> square1 = {-118.299, -118.264, 34.032, 34.011};
//  auto sub1 = m.GetSubgraph(square1);
//  bool result1 = m.CycleDetection(sub1, square1);
//  EXPECT_EQ(result1, true);
//  //std::vector<double> square1 = {-118.320, -118.250, 34.000, 34.040};
//
//  // Test case 2
//  std::vector<double> square2 = {-118.290, -118.289, 34.030, 34.020};
//  auto sub2 = m.GetSubgraph(square2);
//  bool result2 = m.CycleDetection(sub2, square2);
//  EXPECT_EQ(result2, false);
//
//  // following test case passed
//  // Test case 3
//  square1 = {-118.284007, -118.2819, 34.0366, 34.035};
//  sub1 = m.GetSubgraph(square1);
//  result1 = m.CycleDetection(sub1, square1);
//  EXPECT_EQ(result1, true);
//
//  // Test case 4
//  square1 = {-118.290, -118.288, 34.030, 34.0285};
//  sub1 = m.GetSubgraph(square1);
//  result1 = m.CycleDetection(sub1, square1);
//  EXPECT_EQ(result1, false);
//
//  // Test case 5
//  square1 = {-118.290, -118.288, 34.030, 34.0255};
//  sub1 = m.GetSubgraph(square1);
//  result1 = m.CycleDetection(sub1, square1);
//  EXPECT_EQ(result1, true);
//}

//TEST(TrojanMapTest, TopologicalSortmini) {
//  TrojanMap m;
//  
//  std::vector<std::string> location_names = {"Ralphs", "Chick-fil-A", "KFC"};
//  std::vector<std::vector<std::string>> dependencies = {{"Ralphs","KFC"}, {"Ralphs","Chick-fil-A"}, {"KFC","Chick-fil-A"}};
//  auto result = m.DeliveringTrojan(location_names, dependencies);
//  std::vector<std::string> gt ={"Ralphs", "KFC","Chick-fil-A"};
//  EXPECT_EQ(result, gt);
//}
//
//TEST(TrojanMapTest, TopologicalSortfull) {
//  TrojanMap m;
//  
//  std::vector<std::string> location_names = {"Foshay Learning Center", "Holy Name School", "National Schools", "Normandie Elementary School", "Saint Agnes Elementary School"};
//  std::vector<std::vector<std::string>> dependencies = {{"Saint Agnes Elementary School","Foshay Learning Center"}, {"Foshay Learning Center","Holy Name School"}, {"Foshay Learning Center","National Schools"}, {"Saint Agnes Elementary School","National Schools"},{"National Schools","Normandie Elementary School"}};
//  auto result = m.DeliveringTrojan(location_names, dependencies);
//  std::vector<std::string> gt ={"Saint Agnes Elementary School", "Foshay Learning Center","Holy Name School", "National Schools", "Normandie Elementary School"};
//  EXPECT_EQ(result, gt);
//
//
//  location_names = {"Saint Cecilia School", "Saint Patrick School", "Santa Barbara Avenue School", "Trinity Elementary School", "Twenty-Eight Street Elementary School", "Vermont Elementary School", "Wadsworth Elementary School"};
//  dependencies = {{"Saint Cecilia School","Saint Patrick School"}, {"Santa Barbara Avenue School","Saint Patrick School"}, {"Trinity Elementary School","Saint Patrick School"}, {"Twenty-Eight Street Elementary School","Saint Patrick School"},{"Twenty-Eight Street Elementary School","Vermont Elementary School"}, {"Wadsworth Elementary School","Vermont Elementary School"}};
//  result = m.DeliveringTrojan(location_names, dependencies);
//  gt = {"Wadsworth Elementary School", "Twenty-Eight Street Elementary School", "Vermont Elementary School", "Trinity Elementary School", "Santa Barbara Avenue School", "Saint Cecilia School", "Saint Patrick School"};
//  EXPECT_EQ(result, gt);
//
//}

// Test TSP function
TEST(TrojanMapTest, TSP1mini) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","8566227783","1873055993"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","1873055993","8566227783","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, TSP1full) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, TSPbtmini) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","8566227783","1873055993"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","1873055993","8566227783","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, TSPbtfull) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}