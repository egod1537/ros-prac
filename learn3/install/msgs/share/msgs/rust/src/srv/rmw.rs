#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__msgs__srv__Compute_Request() -> *const std::ffi::c_void;
}

#[link(name = "msgs__rosidl_generator_c")]
extern "C" {
    fn msgs__srv__Compute_Request__init(msg: *mut Compute_Request) -> bool;
    fn msgs__srv__Compute_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Compute_Request>, size: usize) -> bool;
    fn msgs__srv__Compute_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Compute_Request>);
    fn msgs__srv__Compute_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Compute_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<Compute_Request>) -> bool;
}

// Corresponds to msgs__srv__Compute_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Compute_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub a: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub b: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operation: rosidl_runtime_rs::String,

}



impl Default for Compute_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !msgs__srv__Compute_Request__init(&mut msg as *mut _) {
        panic!("Call to msgs__srv__Compute_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Compute_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__srv__Compute_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__srv__Compute_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__srv__Compute_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Compute_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Compute_Request where Self: Sized {
  const TYPE_NAME: &'static str = "msgs/srv/Compute_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__msgs__srv__Compute_Request() }
  }
}


#[link(name = "msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__msgs__srv__Compute_Response() -> *const std::ffi::c_void;
}

#[link(name = "msgs__rosidl_generator_c")]
extern "C" {
    fn msgs__srv__Compute_Response__init(msg: *mut Compute_Response) -> bool;
    fn msgs__srv__Compute_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Compute_Response>, size: usize) -> bool;
    fn msgs__srv__Compute_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Compute_Response>);
    fn msgs__srv__Compute_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Compute_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<Compute_Response>) -> bool;
}

// Corresponds to msgs__srv__Compute_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Compute_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub result: f64,

}



impl Default for Compute_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !msgs__srv__Compute_Response__init(&mut msg as *mut _) {
        panic!("Call to msgs__srv__Compute_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Compute_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__srv__Compute_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__srv__Compute_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { msgs__srv__Compute_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Compute_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Compute_Response where Self: Sized {
  const TYPE_NAME: &'static str = "msgs/srv/Compute_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__msgs__srv__Compute_Response() }
  }
}






#[link(name = "msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__msgs__srv__Compute() -> *const std::ffi::c_void;
}

// Corresponds to msgs__srv__Compute
#[allow(missing_docs, non_camel_case_types)]
pub struct Compute;

impl rosidl_runtime_rs::Service for Compute {
    type Request = Compute_Request;
    type Response = Compute_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__msgs__srv__Compute() }
    }
}


