#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

#include <gtest/gtest.h>


#include <exceptions.hpp>
#include <tensor.hpp>


TEST(TensorTests, TensorCreationNoSegfault){
  //Ensure the constructor doesn't generate a segfault.
  ASSERT_NO_FATAL_FAILURE(
      cnn_practice::Tensor<int>tensor (std::vector<int>{1,1,2,3,4,5,6,7,8,9})
  );
}

TEST(TensorTests, DisallowNoRank){
    ASSERT_THROW(
        cnn_practice::Tensor<int>(std::vector<int>()),
        cnn_practice::exceptions::ArgumentException
    );
}

TEST(TensorTests, DisallowShapesOfZeroSizeInAnyDimension){
    ASSERT_THROW(
        cnn_practice::Tensor<int> tensor(std::vector<int>{0}),
        cnn_practice::exceptions::ArgumentException
    );
}

TEST(TensorTests, ElementSet){
    auto set_element = [&](){
        cnn_practice::Tensor<int> tensor(std::vector<int>{1});
        tensor[0] = 10;
        std::cout << "Success";
        exit(0);
    }

    ASSERT_EXIT(
        set_element(),
        ::testing::ExitedWithCode(0),
        ""
    );
}

TEST(TensorTests, ElementGet){
  int test_int = 10;
  cnn_practice::Tensor<int> tensor(std::vector<int>{1});
  tensor[0] = test_int;
  ASSERT_EQ(tensor[0], test_int);
}

TEST(TensorTests, MultiDimensionalOperatorBracketsElementSet){
    auto set_element = [&]() {
        cnn_practice::Tensor<int> tensor(std::vector<int>{1,1,1})
        tensor[0][0][0] = 10;
        std::cout << "Success"
    };
    ASSERT_EXIT(
        set_element(),
        ::testing::ExitedWithCode(0),
        ""
    );
}

TEST(TensorTests, MultiDimensionalOperatorBracketsElementGet){
    int test_int = 10;
    cnn_practice::Tensor<int> tensor(std::vector<int>{1,1,1});
    tensor[0][0][0] = test_int;
    ASSERT_EQ(tensor[0][0][0], test_int);
}
//TEST(TensorTests, DotProduct){
//
//}