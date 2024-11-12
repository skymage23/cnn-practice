#include <gtest/gtest.h>

#include <tensor.hpp>
#include <exceptions.hpp>

TEST(TensorTests, TensorCreationNoSegfault){
  //Ensure the constructor doesn't generate a segfault.
  ASSERT_EXIT(
      (cnn_practice::Tensor<int> tensor(10, [1,1,2,3,4,5,6,7,8,9]), exit(0)),
      ::testing::ExitedWithCode(0),
      ""
  );
}

TEST(TensorTests, DisallowNoRank){
    ASSERT_THROW(cnn_practice::Tensor<int> tensor(0,[0]), cnn_practice::exceptions::ArgumentException);
}

TEST(TensorTests, DisallowShapesOfZeroSizeInAnyDimension){
    ASSERT_THROW(cnn_practice::Tensor<int> tensor(1,[0]), cnn_practice::exceptions::ArgumentException);
}

TEST(TensorTests, ElementSet){
    ASSERT_EXIT(
        (
            cnn_practice::Tensor<int> tensor(1,[1]),
            tensor[0] = 10,
            exit(0)
        ),
        ::testing::ExitWithCode(0),
        ""
    );
}

TEST(TensorTests, ElementGet){
  int test_int = 10
  cnn_practice::Tensor<int> tensor(1, [1]);
  tensor[0] = test_int;
  ASSERT_EQ(tensor[0], test_int);
}

TEST(TensorTests, MultiDimensionalOperatorBracketsElementSet){
    ASSERT_EXIT(
        (
            cn_practice::Tensor<int> tensor(3,[1,1,1]),
            tensor[0][0][0] = 10
        ),
        ::testing::ExitWithCode(0),
        ""
    );
}

TEST(TensorTests, MultiDimensionalOperatorBracketsElementGet){
    int test_int = 10;
    cn_practice::Tensor<int> tensor(3,[1,1,1]);
    tensor[0][0][0] = test_int;
    ASSERT_EQ(tensor[0][0][0], test_int);
}
//TEST(TensorTests, DotProduct){
//
//}