/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, reset_layout_when_child_removed) {
  YGNodeRef root = YGNodeNew();

  YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 100);
  YGNodeStyleSetHeight(root_child0, 100);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  YGNodeRemoveChild(root, root_child0);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeLayoutGetWidth(root_child0)));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeLayoutGetHeight(root_child0)));

  YGNodeFreeRecursive(root);
  YGNodeFreeRecursive(root_child0);
}

TEST(YogaTest, children_row_has_top_offset) {
  YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 800);
  YGNodeStyleSetHeight(root, 800);

  YGNodeRef child1 = YGNodeNew();
  YGNodeInsertChild(root, child1, 0);
  YGNodeStyleSetFlex(child1, 1.0f);

  YGNodeRef container = YGNodeNew();
  YGNodeInsertChild(root, container, 1);
  YGNodeStyleSetFlex(container, 1.0f);
  YGNodeStyleSetFlexDirection(container, YGFlexDirectionRow);

  YGNodeRef child2 = YGNodeNew();
  YGNodeInsertChild(container, child2, 0);
  YGNodeStyleSetFlex(child2, 1.0f);

  YGNodeRef child3 = YGNodeNew();
  YGNodeInsertChild(container, child3, 1);
  YGNodeStyleSetFlex(child3, 1.0f);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(child1));
  ASSERT_EQ(0, YGNodeLayoutGetTop(child1));

  ASSERT_EQ(0, YGNodeLayoutGetLeft(container));
  ASSERT_EQ(400, YGNodeLayoutGetTop(container));

  ASSERT_EQ(0, YGNodeLayoutGetLeft(child2));
  ASSERT_EQ(400, YGNodeLayoutGetTop(child2));

  ASSERT_EQ(400, YGNodeLayoutGetLeft(child3));
  ASSERT_EQ(400, YGNodeLayoutGetTop(child3));

  YGNodeFreeRecursive(root);
}
