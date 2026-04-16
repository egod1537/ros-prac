// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from msgs:action/Countdown.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "msgs/action/countdown.hpp"


#ifndef MSGS__ACTION__DETAIL__COUNTDOWN__BUILDER_HPP_
#define MSGS__ACTION__DETAIL__COUNTDOWN__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "msgs/action/detail/countdown__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace msgs
{

namespace action
{

namespace builder
{

class Init_Countdown_Goal_target_seconds
{
public:
  Init_Countdown_Goal_target_seconds()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::msgs::action::Countdown_Goal target_seconds(::msgs::action::Countdown_Goal::_target_seconds_type arg)
  {
    msg_.target_seconds = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::action::Countdown_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::action::Countdown_Goal>()
{
  return msgs::action::builder::Init_Countdown_Goal_target_seconds();
}

}  // namespace msgs


namespace msgs
{

namespace action
{

namespace builder
{

class Init_Countdown_Result_message
{
public:
  Init_Countdown_Result_message()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::msgs::action::Countdown_Result message(::msgs::action::Countdown_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::action::Countdown_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::action::Countdown_Result>()
{
  return msgs::action::builder::Init_Countdown_Result_message();
}

}  // namespace msgs


namespace msgs
{

namespace action
{

namespace builder
{

class Init_Countdown_Feedback_remaining
{
public:
  Init_Countdown_Feedback_remaining()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::msgs::action::Countdown_Feedback remaining(::msgs::action::Countdown_Feedback::_remaining_type arg)
  {
    msg_.remaining = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::action::Countdown_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::action::Countdown_Feedback>()
{
  return msgs::action::builder::Init_Countdown_Feedback_remaining();
}

}  // namespace msgs


namespace msgs
{

namespace action
{

namespace builder
{

class Init_Countdown_SendGoal_Request_goal
{
public:
  explicit Init_Countdown_SendGoal_Request_goal(::msgs::action::Countdown_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::msgs::action::Countdown_SendGoal_Request goal(::msgs::action::Countdown_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::action::Countdown_SendGoal_Request msg_;
};

class Init_Countdown_SendGoal_Request_goal_id
{
public:
  Init_Countdown_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Countdown_SendGoal_Request_goal goal_id(::msgs::action::Countdown_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Countdown_SendGoal_Request_goal(msg_);
  }

private:
  ::msgs::action::Countdown_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::action::Countdown_SendGoal_Request>()
{
  return msgs::action::builder::Init_Countdown_SendGoal_Request_goal_id();
}

}  // namespace msgs


namespace msgs
{

namespace action
{

namespace builder
{

class Init_Countdown_SendGoal_Response_stamp
{
public:
  explicit Init_Countdown_SendGoal_Response_stamp(::msgs::action::Countdown_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::msgs::action::Countdown_SendGoal_Response stamp(::msgs::action::Countdown_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::action::Countdown_SendGoal_Response msg_;
};

class Init_Countdown_SendGoal_Response_accepted
{
public:
  Init_Countdown_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Countdown_SendGoal_Response_stamp accepted(::msgs::action::Countdown_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_Countdown_SendGoal_Response_stamp(msg_);
  }

private:
  ::msgs::action::Countdown_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::action::Countdown_SendGoal_Response>()
{
  return msgs::action::builder::Init_Countdown_SendGoal_Response_accepted();
}

}  // namespace msgs


namespace msgs
{

namespace action
{

namespace builder
{

class Init_Countdown_SendGoal_Event_response
{
public:
  explicit Init_Countdown_SendGoal_Event_response(::msgs::action::Countdown_SendGoal_Event & msg)
  : msg_(msg)
  {}
  ::msgs::action::Countdown_SendGoal_Event response(::msgs::action::Countdown_SendGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::action::Countdown_SendGoal_Event msg_;
};

class Init_Countdown_SendGoal_Event_request
{
public:
  explicit Init_Countdown_SendGoal_Event_request(::msgs::action::Countdown_SendGoal_Event & msg)
  : msg_(msg)
  {}
  Init_Countdown_SendGoal_Event_response request(::msgs::action::Countdown_SendGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_Countdown_SendGoal_Event_response(msg_);
  }

private:
  ::msgs::action::Countdown_SendGoal_Event msg_;
};

class Init_Countdown_SendGoal_Event_info
{
public:
  Init_Countdown_SendGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Countdown_SendGoal_Event_request info(::msgs::action::Countdown_SendGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_Countdown_SendGoal_Event_request(msg_);
  }

private:
  ::msgs::action::Countdown_SendGoal_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::action::Countdown_SendGoal_Event>()
{
  return msgs::action::builder::Init_Countdown_SendGoal_Event_info();
}

}  // namespace msgs


namespace msgs
{

namespace action
{

namespace builder
{

class Init_Countdown_GetResult_Request_goal_id
{
public:
  Init_Countdown_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::msgs::action::Countdown_GetResult_Request goal_id(::msgs::action::Countdown_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::action::Countdown_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::action::Countdown_GetResult_Request>()
{
  return msgs::action::builder::Init_Countdown_GetResult_Request_goal_id();
}

}  // namespace msgs


namespace msgs
{

namespace action
{

namespace builder
{

class Init_Countdown_GetResult_Response_result
{
public:
  explicit Init_Countdown_GetResult_Response_result(::msgs::action::Countdown_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::msgs::action::Countdown_GetResult_Response result(::msgs::action::Countdown_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::action::Countdown_GetResult_Response msg_;
};

class Init_Countdown_GetResult_Response_status
{
public:
  Init_Countdown_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Countdown_GetResult_Response_result status(::msgs::action::Countdown_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_Countdown_GetResult_Response_result(msg_);
  }

private:
  ::msgs::action::Countdown_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::action::Countdown_GetResult_Response>()
{
  return msgs::action::builder::Init_Countdown_GetResult_Response_status();
}

}  // namespace msgs


namespace msgs
{

namespace action
{

namespace builder
{

class Init_Countdown_GetResult_Event_response
{
public:
  explicit Init_Countdown_GetResult_Event_response(::msgs::action::Countdown_GetResult_Event & msg)
  : msg_(msg)
  {}
  ::msgs::action::Countdown_GetResult_Event response(::msgs::action::Countdown_GetResult_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::action::Countdown_GetResult_Event msg_;
};

class Init_Countdown_GetResult_Event_request
{
public:
  explicit Init_Countdown_GetResult_Event_request(::msgs::action::Countdown_GetResult_Event & msg)
  : msg_(msg)
  {}
  Init_Countdown_GetResult_Event_response request(::msgs::action::Countdown_GetResult_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_Countdown_GetResult_Event_response(msg_);
  }

private:
  ::msgs::action::Countdown_GetResult_Event msg_;
};

class Init_Countdown_GetResult_Event_info
{
public:
  Init_Countdown_GetResult_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Countdown_GetResult_Event_request info(::msgs::action::Countdown_GetResult_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_Countdown_GetResult_Event_request(msg_);
  }

private:
  ::msgs::action::Countdown_GetResult_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::action::Countdown_GetResult_Event>()
{
  return msgs::action::builder::Init_Countdown_GetResult_Event_info();
}

}  // namespace msgs


namespace msgs
{

namespace action
{

namespace builder
{

class Init_Countdown_FeedbackMessage_feedback
{
public:
  explicit Init_Countdown_FeedbackMessage_feedback(::msgs::action::Countdown_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::msgs::action::Countdown_FeedbackMessage feedback(::msgs::action::Countdown_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::action::Countdown_FeedbackMessage msg_;
};

class Init_Countdown_FeedbackMessage_goal_id
{
public:
  Init_Countdown_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Countdown_FeedbackMessage_feedback goal_id(::msgs::action::Countdown_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Countdown_FeedbackMessage_feedback(msg_);
  }

private:
  ::msgs::action::Countdown_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::action::Countdown_FeedbackMessage>()
{
  return msgs::action::builder::Init_Countdown_FeedbackMessage_goal_id();
}

}  // namespace msgs

#endif  // MSGS__ACTION__DETAIL__COUNTDOWN__BUILDER_HPP_
