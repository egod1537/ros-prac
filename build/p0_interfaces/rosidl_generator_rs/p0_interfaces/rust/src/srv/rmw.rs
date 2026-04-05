#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "p0_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__p0_interfaces__srv__GetStatus_Request() -> *const std::ffi::c_void;
}

#[link(name = "p0_interfaces__rosidl_generator_c")]
extern "C" {
    fn p0_interfaces__srv__GetStatus_Request__init(msg: *mut GetStatus_Request) -> bool;
    fn p0_interfaces__srv__GetStatus_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetStatus_Request>, size: usize) -> bool;
    fn p0_interfaces__srv__GetStatus_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetStatus_Request>);
    fn p0_interfaces__srv__GetStatus_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetStatus_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetStatus_Request>) -> bool;
}

// Corresponds to p0_interfaces__srv__GetStatus_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetStatus_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub robot_name: rosidl_runtime_rs::String,

}



impl Default for GetStatus_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !p0_interfaces__srv__GetStatus_Request__init(&mut msg as *mut _) {
        panic!("Call to p0_interfaces__srv__GetStatus_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetStatus_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { p0_interfaces__srv__GetStatus_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { p0_interfaces__srv__GetStatus_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { p0_interfaces__srv__GetStatus_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetStatus_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetStatus_Request where Self: Sized {
  const TYPE_NAME: &'static str = "p0_interfaces/srv/GetStatus_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__p0_interfaces__srv__GetStatus_Request() }
  }
}


#[link(name = "p0_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__p0_interfaces__srv__GetStatus_Response() -> *const std::ffi::c_void;
}

#[link(name = "p0_interfaces__rosidl_generator_c")]
extern "C" {
    fn p0_interfaces__srv__GetStatus_Response__init(msg: *mut GetStatus_Response) -> bool;
    fn p0_interfaces__srv__GetStatus_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetStatus_Response>, size: usize) -> bool;
    fn p0_interfaces__srv__GetStatus_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetStatus_Response>);
    fn p0_interfaces__srv__GetStatus_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetStatus_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetStatus_Response>) -> bool;
}

// Corresponds to p0_interfaces__srv__GetStatus_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetStatus_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub battery: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub position: [f64; 3],


    // This member is not documented.
    #[allow(missing_docs)]
    pub found: bool,

}



impl Default for GetStatus_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !p0_interfaces__srv__GetStatus_Response__init(&mut msg as *mut _) {
        panic!("Call to p0_interfaces__srv__GetStatus_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetStatus_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { p0_interfaces__srv__GetStatus_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { p0_interfaces__srv__GetStatus_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { p0_interfaces__srv__GetStatus_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetStatus_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetStatus_Response where Self: Sized {
  const TYPE_NAME: &'static str = "p0_interfaces/srv/GetStatus_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__p0_interfaces__srv__GetStatus_Response() }
  }
}






#[link(name = "p0_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__p0_interfaces__srv__GetStatus() -> *const std::ffi::c_void;
}

// Corresponds to p0_interfaces__srv__GetStatus
#[allow(missing_docs, non_camel_case_types)]
pub struct GetStatus;

impl rosidl_runtime_rs::Service for GetStatus {
    type Request = GetStatus_Request;
    type Response = GetStatus_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__p0_interfaces__srv__GetStatus() }
    }
}


