cc_library(
  name="BinaryUtils",
  hdrs=glob(["include/*.hpp"]),
  visibility = ["//visibility:public"],
)

cc_test(
  name = "BinaryUtilsTest",
  size = "small",
  srcs = ["tests/BinaryUtilsTest.cpp"],
  deps = ["@com_google_googletest//:gtest_main", ":BinaryUtils"],
)

