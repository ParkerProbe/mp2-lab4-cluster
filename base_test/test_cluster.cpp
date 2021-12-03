#include "cluster.h"
#include "gtest.h"

TEST(Cluster, can_create_cluster)
{
  ASSERT_NO_THROW(Cluster a(800, 5, 0.5, 3));
}
TEST(Cluster, can_not_create_cluster_with_too_large_size_of_queue)
{
  ASSERT_ANY_THROW(Cluster a(450, 90, 0.6, 4));
}
TEST(Cluster, throw_when_create_cluster_with_negative_count_of_work_tacts)
{
  ASSERT_ANY_THROW(Cluster a(-200, 10, 0.5, 2));
}
TEST(Cluster, throw_when_create_cluster_with_invalid_num_of_processors)
{
  ASSERT_ANY_THROW(Cluster a(800, 8, 0.5, 87));
}
TEST(Cluster, throw_when_create_cluster_with_invalid_value_of_chance)
{
  ASSERT_ANY_THROW(Cluster a(800, 24, 1.1, 1));
}