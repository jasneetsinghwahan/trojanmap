#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"
#include <gmock/gmock.h>

TEST(TrojanMapTest, Autocompletecopied) {
  TrojanMap m;
  // Test the simple case
  auto names = m.Autocomplete("Star");
  std::unordered_set<std::string> gt = {"Starbucks", "Starbucks 1", "Starbucks 2", "Starbucks 3"}; // groundtruth for "star"
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test the lower case
  names = m.Autocomplete("star");
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test the lower and upper case 
  names = m.Autocomplete("sTAR"); 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test the upper case 
  names = m.Autocomplete("STAR"); 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test empty string
  names = m.Autocomplete(""); 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, 0);

}

TEST(TrojanMapTest, FindPositioncopied) {
  TrojanMap m;
  
  // Test Chick-fil-A
  auto position = m.GetPosition("First Presbyterian Church");
  std::pair<double, double> gt1(34.0321559, -118.2722841); // groundtruth for "First Presbyterian Church"
  EXPECT_EQ(position, gt1);
  // Test Ralphs
  position = m.GetPosition("Ralphs");
  std::pair<double, double> gt2(34.0317653, -118.2908339); // groundtruth for "Ralphs"
  EXPECT_EQ(position, gt2);
  // Test Target
  position = m.GetPosition("Chevron 1");
  std::pair<double, double> gt3(34.0336409, -118.2620798); // groundtruth for "Chevron 1"
  EXPECT_EQ(position, gt3);
  // Test Unknown
  position = m.GetPosition("7th & Hi");
  std::pair<double, double> gt4(-1, -1);
  EXPECT_EQ(position, gt4);
  // Test empty
  position = m.GetPosition("");
  std::pair<double, double> gt5(-1, -1);
  EXPECT_EQ(position, gt4);
}

// Test CalculateEditDistance function
TEST(TrojanMapTest, CalculateEditDistancecopied) {
  TrojanMap m;
  EXPECT_EQ(m.CalculateEditDistance("", "ros"), 3);
  EXPECT_EQ(m.CalculateEditDistance("ros", ""), 3);
  EXPECT_EQ(m.CalculateEditDistance("abc", "xyz"), 3);
  EXPECT_EQ(m.CalculateEditDistance("", ""), 0);
  EXPECT_EQ(m.CalculateEditDistance(" ", ""), 1);
  EXPECT_EQ(m.CalculateEditDistance("starb uc", "starbucks"), 3);
}

// Test FindClosestName function
TEST(TrojanMapTest, FindClosestNamecopied) {
  TrojanMap m;
  EXPECT_EQ(m.FindClosestName("Rolphs"), "Ralphs");
  EXPECT_EQ(m.FindClosestName("starb uc"), "Starbucks");
}

// Test FindClosestName function
TEST(TrojanMapTest, FindAllCategories) {
  TrojanMap m;
  std::vector<std::string> exp_rst = {"parcel_locker", "car_wash", "childcare", "yes", "driving_school", "dentist", "police", "charging_station", "copyshop", "theatre", "bicycle", "museum", "post_office", "library", "fuel", "hotel", "bank", "convenience", "parking", "clothes", "fast_food", "hairdresser", "restaurant", "yoga", "cafe", "clinic", "parking_entrance", "optician", "bakery", "shoes", "hospital", "beverages", "car_repair", "post_box", "tobacco", "attraction", "fountain", "confectionery", "car", "shoe_repair", "food_court", "artwork", "fabric", "gallery", "social_facility", "supermarket", "pharmacy", "department_store", "mobile_phone", "bar", "skate", "marketplace", "music", "beauty", "bicycle_rental", "bus_station", "school", "place_of_worship"};
  std::vector<std::string> act_rst = m.GetAllCategories();
  EXPECT_THAT(act_rst,::testing::Contains("school"));
  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
  EXPECT_EQ(act_rst.size(),58);
}

// Test FindClosestName function
TEST(TrojanMapTest, GetAllLocationsFromCategory) {
  TrojanMap m;
  std::string categoryname = {"artwork"};
  std::vector<std::string> exp_rst = {"2305853438","4399693645","4536993737","5237417648","6813379578"};
  std::vector<std::string> act_rst = m.GetAllLocationsFromCategory(categoryname);
  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
  EXPECT_EQ(act_rst.size(),5);
  categoryname = {"bank"};
  act_rst = m.GetAllLocationsFromCategory(categoryname);
  exp_rst = {"5237417651", "9591449441","9591449465"};
  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
  EXPECT_EQ(act_rst.size(),3);
  categoryname = {"bnk"};
  act_rst = m.GetAllLocationsFromCategory(categoryname);
  exp_rst = {"-1, -1"};
  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
  EXPECT_EQ(act_rst.size(),1);
  categoryname = {""};
  act_rst = m.GetAllLocationsFromCategory(categoryname);
  exp_rst = {"-1, -1"};
  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
  EXPECT_EQ(act_rst.size(),1);
  categoryname = {"BANK"};
  act_rst = m.GetAllLocationsFromCategory(categoryname);
  exp_rst = {"5237417651", "9591449441","9591449465"};
  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
  EXPECT_EQ(act_rst.size(),3);
}

TEST(TrojanMapTest, GetLocationRegex){
  TrojanMap m;
  std::regex ip("9446678097");
  std::vector<std::string> exp_rst = {"9446678097"};
  std::vector<std::string> act_rst = m.GetLocationRegex(ip);
  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
  EXPECT_EQ(act_rst.size(),1);
  ip = {"^94{1,2}6{1,2}7809\\d{1}"};
  exp_rst = {"9446678097","9446678098","9446678099"};
  act_rst = m.GetLocationRegex(ip);
  EXPECT_THAT(act_rst,::testing::UnorderedElementsAreArray(exp_rst));
  EXPECT_EQ(act_rst.size(),exp_rst.size());
}

TEST(TrojanMapTest, CalculateShortestPath_Dijkstracopied) {
  TrojanMap m;
  auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Ralphs");
  std::vector<std::string> gt = {};
  EXPECT_EQ(path, gt);
  path = m.CalculateShortestPath_Dijkstra("Antioch Temple Baptist Church", "Divine Providence Convent");
  gt = {"358850024", "122674584", "6816193741", "122674587", "6816193745", "277328088", "277328089", "277328090", "122674590", "1843466234", "4015377693", "6816180170", "6380132756", "6816180168", "1922565218", "2514542031", "4015377692", "6816193690", "123408740", "6816193692", "4015442011", "358850041"};
  EXPECT_EQ(path, gt);
  
  // Test from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Dijkstra("Ralphs", "Chick-fil-A");
  gt = {
      "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920","6818427919",
      "6818427918","6818427892","6818427898","6818427917","6818427916","7232024780","6813416145",
      "6813416154","6813416153","6813416152","6813416151","6813416155","6808069740","6816193785",
      "6816193786","123152294","4015203136","4015203134","4015203133","21098539","6389467809",
      "4015203132","3195897587","4015203129","4015203127","6352865690","6813379589","6813379483",
      "3402887081","6814958394","3402887080","602606656","4872897515","4399697589","6814958391",
      "123209598","6787673296","122728406","6807762271","4399697304","4399697302","5231967015",
      "1862347583","3233702827","4540763379","6819179753","6820935900","6820935901","6813379556",
      "6820935898","1781230450","1781230449","4015405542","4015405543","1837212104","1837212107",
      "2753199985","6820935907","1837212100","4015372458","6813411588","1837212101","6814916516",
      "6814916515","6820935910","4547476733"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "no. of nodes visited in actual: "  << path.size() << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Dijkstra("Chick-fil-A", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "no. of nodes visited in actual: "  << path.size() << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
}
