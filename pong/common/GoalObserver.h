#pragma once

class GoalObserver {
 public:
  virtual ~GoalObserver() = default;

  enum class Side { Left, Right };
  virtual void onGoal(Side side) = 0;
};