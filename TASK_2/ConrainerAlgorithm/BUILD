cc_library(
  name="ContainerAlgorithm",
  hdrs=glob(["include/*.hpp"]),
  visibility = ["//visibility:public"],
)

cc_test(
  name = "ContainerAlgorithmTests",
  size = "small",
  srcs = ["tests/ContrainerAlgorithmTests.cpp", "tests/RemoveDupsTests.hpp", "tests/UniqueImplTests.hpp"],
  deps = ["@com_google_googletest//:gtest_main", ":ContainerAlgorithm"],
)

