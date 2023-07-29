#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

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