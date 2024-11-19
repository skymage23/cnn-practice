
/*
*  This file does not include constructor and destructors tests
*  because those need to override 
*)
*/
    
#include <gtest/gtest.h>
#include <internal/tensor/IndexCache.hpp>

TEST(IndexCacheTests, IndexCacheCreation){
    ASSERT_NO_FATAL_FAILURE(cnn_practice::IndexCache cache(10));
}

//Make sure memory is freed.
//This is a bit complex, as it 
TEST(IndexCacheTests, IndexCacheMemoryFreeOnDestruction){
    
}