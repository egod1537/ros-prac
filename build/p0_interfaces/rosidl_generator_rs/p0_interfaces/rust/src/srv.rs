#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to p0_interfaces__srv__GetStatus_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetStatus_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub robot_name: std::string::String,

}



impl Default for GetStatus_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetStatus_Request::default())
  }
}

impl rosidl_runtime_rs::Message for GetStatus_Request {
  type RmwMsg = super::srv::rmw::GetStatus_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        robot_name: msg.robot_name.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        robot_name: msg.robot_name.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      robot_name: msg.robot_name.to_string(),
    }
  }
}


// Corresponds to p0_interfaces__srv__GetStatus_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetStatus_Response::default())
  }
}

impl rosidl_runtime_rs::Message for GetStatus_Response {
  type RmwMsg = super::srv::rmw::GetStatus_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        battery: msg.battery,
        position: msg.position,
        found: msg.found,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      battery: msg.battery,
        position: msg.position,
      found: msg.found,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      battery: msg.battery,
      position: msg.position,
      found: msg.found,
    }
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


