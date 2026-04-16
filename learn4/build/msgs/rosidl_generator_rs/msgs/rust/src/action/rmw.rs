
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_Goal() -> *const std::ffi::c_void;
}

#[link(name = "msgs__rosidl_generator_c")]
extern "C" {
    fn msgs__action__Countdown_Goal__init(msg: *mut Countdown_Goal) -> bool;
    fn msgs__action__Countdown_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Countdown_Goal>, size: usize) -> bool;
    fn msgs__action__Countdown_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Countdown_Goal>);
    fn msgs__action__Countdown_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Countdown_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<Countdown_Goal>) -> bool;
}

// Corresponds to msgs__action__Countdown_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Countdown_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub target_seconds: i32,

}



impl Default for Countdown_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !msgs__action__Countdown_Goal__init(&mut msg as *mut _) {
        panic!("Call to msgs__action__Countdown_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Countdown_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Countdown_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Countdown_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "msgs/action/Countdown_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_Goal() }
  }
}


#[link(name = "msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_Result() -> *const std::ffi::c_void;
}

#[link(name = "msgs__rosidl_generator_c")]
extern "C" {
    fn msgs__action__Countdown_Result__init(msg: *mut Countdown_Result) -> bool;
    fn msgs__action__Countdown_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Countdown_Result>, size: usize) -> bool;
    fn msgs__action__Countdown_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Countdown_Result>);
    fn msgs__action__Countdown_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Countdown_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<Countdown_Result>) -> bool;
}

// Corresponds to msgs__action__Countdown_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Countdown_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for Countdown_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !msgs__action__Countdown_Result__init(&mut msg as *mut _) {
        panic!("Call to msgs__action__Countdown_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Countdown_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Countdown_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Countdown_Result where Self: Sized {
  const TYPE_NAME: &'static str = "msgs/action/Countdown_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_Result() }
  }
}


#[link(name = "msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "msgs__rosidl_generator_c")]
extern "C" {
    fn msgs__action__Countdown_Feedback__init(msg: *mut Countdown_Feedback) -> bool;
    fn msgs__action__Countdown_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Countdown_Feedback>, size: usize) -> bool;
    fn msgs__action__Countdown_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Countdown_Feedback>);
    fn msgs__action__Countdown_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Countdown_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<Countdown_Feedback>) -> bool;
}

// Corresponds to msgs__action__Countdown_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Countdown_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub remaining: i32,

}



impl Default for Countdown_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !msgs__action__Countdown_Feedback__init(&mut msg as *mut _) {
        panic!("Call to msgs__action__Countdown_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Countdown_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Countdown_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Countdown_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "msgs/action/Countdown_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_Feedback() }
  }
}


#[link(name = "msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "msgs__rosidl_generator_c")]
extern "C" {
    fn msgs__action__Countdown_FeedbackMessage__init(msg: *mut Countdown_FeedbackMessage) -> bool;
    fn msgs__action__Countdown_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Countdown_FeedbackMessage>, size: usize) -> bool;
    fn msgs__action__Countdown_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Countdown_FeedbackMessage>);
    fn msgs__action__Countdown_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Countdown_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<Countdown_FeedbackMessage>) -> bool;
}

// Corresponds to msgs__action__Countdown_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Countdown_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::Countdown_Feedback,

}



impl Default for Countdown_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !msgs__action__Countdown_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to msgs__action__Countdown_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Countdown_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Countdown_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Countdown_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "msgs/action/Countdown_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_FeedbackMessage() }
  }
}




#[link(name = "msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "msgs__rosidl_generator_c")]
extern "C" {
    fn msgs__action__Countdown_SendGoal_Request__init(msg: *mut Countdown_SendGoal_Request) -> bool;
    fn msgs__action__Countdown_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Countdown_SendGoal_Request>, size: usize) -> bool;
    fn msgs__action__Countdown_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Countdown_SendGoal_Request>);
    fn msgs__action__Countdown_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Countdown_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<Countdown_SendGoal_Request>) -> bool;
}

// Corresponds to msgs__action__Countdown_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Countdown_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::Countdown_Goal,

}



impl Default for Countdown_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !msgs__action__Countdown_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to msgs__action__Countdown_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Countdown_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Countdown_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Countdown_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "msgs/action/Countdown_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_SendGoal_Request() }
  }
}


#[link(name = "msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "msgs__rosidl_generator_c")]
extern "C" {
    fn msgs__action__Countdown_SendGoal_Response__init(msg: *mut Countdown_SendGoal_Response) -> bool;
    fn msgs__action__Countdown_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Countdown_SendGoal_Response>, size: usize) -> bool;
    fn msgs__action__Countdown_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Countdown_SendGoal_Response>);
    fn msgs__action__Countdown_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Countdown_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<Countdown_SendGoal_Response>) -> bool;
}

// Corresponds to msgs__action__Countdown_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Countdown_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for Countdown_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !msgs__action__Countdown_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to msgs__action__Countdown_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Countdown_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Countdown_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Countdown_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "msgs/action/Countdown_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_SendGoal_Response() }
  }
}


#[link(name = "msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "msgs__rosidl_generator_c")]
extern "C" {
    fn msgs__action__Countdown_GetResult_Request__init(msg: *mut Countdown_GetResult_Request) -> bool;
    fn msgs__action__Countdown_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Countdown_GetResult_Request>, size: usize) -> bool;
    fn msgs__action__Countdown_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Countdown_GetResult_Request>);
    fn msgs__action__Countdown_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Countdown_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<Countdown_GetResult_Request>) -> bool;
}

// Corresponds to msgs__action__Countdown_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Countdown_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for Countdown_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !msgs__action__Countdown_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to msgs__action__Countdown_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Countdown_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Countdown_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Countdown_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "msgs/action/Countdown_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_GetResult_Request() }
  }
}


#[link(name = "msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "msgs__rosidl_generator_c")]
extern "C" {
    fn msgs__action__Countdown_GetResult_Response__init(msg: *mut Countdown_GetResult_Response) -> bool;
    fn msgs__action__Countdown_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Countdown_GetResult_Response>, size: usize) -> bool;
    fn msgs__action__Countdown_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Countdown_GetResult_Response>);
    fn msgs__action__Countdown_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Countdown_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<Countdown_GetResult_Response>) -> bool;
}

// Corresponds to msgs__action__Countdown_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Countdown_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::Countdown_Result,

}



impl Default for Countdown_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !msgs__action__Countdown_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to msgs__action__Countdown_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Countdown_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__action__Countdown_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Countdown_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Countdown_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "msgs/action/Countdown_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__msgs__action__Countdown_GetResult_Response() }
  }
}






#[link(name = "msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__msgs__action__Countdown_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to msgs__action__Countdown_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct Countdown_SendGoal;

impl rosidl_runtime_rs::Service for Countdown_SendGoal {
    type Request = Countdown_SendGoal_Request;
    type Response = Countdown_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__msgs__action__Countdown_SendGoal() }
    }
}




#[link(name = "msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__msgs__action__Countdown_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to msgs__action__Countdown_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct Countdown_GetResult;

impl rosidl_runtime_rs::Service for Countdown_GetResult {
    type Request = Countdown_GetResult_Request;
    type Response = Countdown_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__msgs__action__Countdown_GetResult() }
    }
}


