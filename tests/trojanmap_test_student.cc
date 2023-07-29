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