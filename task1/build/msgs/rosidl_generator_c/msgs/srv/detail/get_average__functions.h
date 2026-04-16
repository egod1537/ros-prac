// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from msgs:srv/GetAverage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "msgs/srv/get_average.h"


#ifndef MSGS__SRV__DETAIL__GET_AVERAGE__FUNCTIONS_H_
#define MSGS__SRV__DETAIL__GET_AVERAGE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "msgs/msg/rosidl_generator_c__visibility_control.h"

#include "msgs/srv/detail/get_average__struct.h"

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_type_hash_t *
msgs__srv__GetAverage__get_type_hash(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_runtime_c__type_description__TypeDescription *
msgs__srv__GetAverage__get_type_description(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_runtime_c__type_description__TypeSource *
msgs__srv__GetAverage__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
msgs__srv__GetAverage__get_type_description_sources(
  const rosidl_service_type_support_t * type_support);

/// Initialize srv/GetAverage message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * msgs__srv__GetAverage_Request
 * )) before or use
 * msgs__srv__GetAverage_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Request__init(msgs__srv__GetAverage_Request * msg);

/// Finalize srv/GetAverage message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
void
msgs__srv__GetAverage_Request__fini(msgs__srv__GetAverage_Request * msg);

/// Create srv/GetAverage message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * msgs__srv__GetAverage_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
msgs__srv__GetAverage_Request *
msgs__srv__GetAverage_Request__create(void);

/// Destroy srv/GetAverage message.
/**
 * It calls
 * msgs__srv__GetAverage_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
void
msgs__srv__GetAverage_Request__destroy(msgs__srv__GetAverage_Request * msg);

/// Check for srv/GetAverage message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Request__are_equal(const msgs__srv__GetAverage_Request * lhs, const msgs__srv__GetAverage_Request * rhs);

/// Copy a srv/GetAverage message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Request__copy(
  const msgs__srv__GetAverage_Request * input,
  msgs__srv__GetAverage_Request * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_type_hash_t *
msgs__srv__GetAverage_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_runtime_c__type_description__TypeDescription *
msgs__srv__GetAverage_Request__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_runtime_c__type_description__TypeSource *
msgs__srv__GetAverage_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
msgs__srv__GetAverage_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/GetAverage messages.
/**
 * It allocates the memory for the number of elements and calls
 * msgs__srv__GetAverage_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Request__Sequence__init(msgs__srv__GetAverage_Request__Sequence * array, size_t size);

/// Finalize array of srv/GetAverage messages.
/**
 * It calls
 * msgs__srv__GetAverage_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
void
msgs__srv__GetAverage_Request__Sequence__fini(msgs__srv__GetAverage_Request__Sequence * array);

/// Create array of srv/GetAverage messages.
/**
 * It allocates the memory for the array and calls
 * msgs__srv__GetAverage_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
msgs__srv__GetAverage_Request__Sequence *
msgs__srv__GetAverage_Request__Sequence__create(size_t size);

/// Destroy array of srv/GetAverage messages.
/**
 * It calls
 * msgs__srv__GetAverage_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
void
msgs__srv__GetAverage_Request__Sequence__destroy(msgs__srv__GetAverage_Request__Sequence * array);

/// Check for srv/GetAverage message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Request__Sequence__are_equal(const msgs__srv__GetAverage_Request__Sequence * lhs, const msgs__srv__GetAverage_Request__Sequence * rhs);

/// Copy an array of srv/GetAverage messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Request__Sequence__copy(
  const msgs__srv__GetAverage_Request__Sequence * input,
  msgs__srv__GetAverage_Request__Sequence * output);

/// Initialize srv/GetAverage message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * msgs__srv__GetAverage_Response
 * )) before or use
 * msgs__srv__GetAverage_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Response__init(msgs__srv__GetAverage_Response * msg);

/// Finalize srv/GetAverage message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
void
msgs__srv__GetAverage_Response__fini(msgs__srv__GetAverage_Response * msg);

/// Create srv/GetAverage message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * msgs__srv__GetAverage_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
msgs__srv__GetAverage_Response *
msgs__srv__GetAverage_Response__create(void);

/// Destroy srv/GetAverage message.
/**
 * It calls
 * msgs__srv__GetAverage_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
void
msgs__srv__GetAverage_Response__destroy(msgs__srv__GetAverage_Response * msg);

/// Check for srv/GetAverage message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Response__are_equal(const msgs__srv__GetAverage_Response * lhs, const msgs__srv__GetAverage_Response * rhs);

/// Copy a srv/GetAverage message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Response__copy(
  const msgs__srv__GetAverage_Response * input,
  msgs__srv__GetAverage_Response * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_type_hash_t *
msgs__srv__GetAverage_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_runtime_c__type_description__TypeDescription *
msgs__srv__GetAverage_Response__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_runtime_c__type_description__TypeSource *
msgs__srv__GetAverage_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
msgs__srv__GetAverage_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/GetAverage messages.
/**
 * It allocates the memory for the number of elements and calls
 * msgs__srv__GetAverage_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Response__Sequence__init(msgs__srv__GetAverage_Response__Sequence * array, size_t size);

/// Finalize array of srv/GetAverage messages.
/**
 * It calls
 * msgs__srv__GetAverage_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
void
msgs__srv__GetAverage_Response__Sequence__fini(msgs__srv__GetAverage_Response__Sequence * array);

/// Create array of srv/GetAverage messages.
/**
 * It allocates the memory for the array and calls
 * msgs__srv__GetAverage_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
msgs__srv__GetAverage_Response__Sequence *
msgs__srv__GetAverage_Response__Sequence__create(size_t size);

/// Destroy array of srv/GetAverage messages.
/**
 * It calls
 * msgs__srv__GetAverage_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
void
msgs__srv__GetAverage_Response__Sequence__destroy(msgs__srv__GetAverage_Response__Sequence * array);

/// Check for srv/GetAverage message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Response__Sequence__are_equal(const msgs__srv__GetAverage_Response__Sequence * lhs, const msgs__srv__GetAverage_Response__Sequence * rhs);

/// Copy an array of srv/GetAverage messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Response__Sequence__copy(
  const msgs__srv__GetAverage_Response__Sequence * input,
  msgs__srv__GetAverage_Response__Sequence * output);

/// Initialize srv/GetAverage message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * msgs__srv__GetAverage_Event
 * )) before or use
 * msgs__srv__GetAverage_Event__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Event__init(msgs__srv__GetAverage_Event * msg);

/// Finalize srv/GetAverage message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
void
msgs__srv__GetAverage_Event__fini(msgs__srv__GetAverage_Event * msg);

/// Create srv/GetAverage message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * msgs__srv__GetAverage_Event__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
msgs__srv__GetAverage_Event *
msgs__srv__GetAverage_Event__create(void);

/// Destroy srv/GetAverage message.
/**
 * It calls
 * msgs__srv__GetAverage_Event__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
void
msgs__srv__GetAverage_Event__destroy(msgs__srv__GetAverage_Event * msg);

/// Check for srv/GetAverage message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Event__are_equal(const msgs__srv__GetAverage_Event * lhs, const msgs__srv__GetAverage_Event * rhs);

/// Copy a srv/GetAverage message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Event__copy(
  const msgs__srv__GetAverage_Event * input,
  msgs__srv__GetAverage_Event * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_type_hash_t *
msgs__srv__GetAverage_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_runtime_c__type_description__TypeDescription *
msgs__srv__GetAverage_Event__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_runtime_c__type_description__TypeSource *
msgs__srv__GetAverage_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
msgs__srv__GetAverage_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/GetAverage messages.
/**
 * It allocates the memory for the number of elements and calls
 * msgs__srv__GetAverage_Event__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Event__Sequence__init(msgs__srv__GetAverage_Event__Sequence * array, size_t size);

/// Finalize array of srv/GetAverage messages.
/**
 * It calls
 * msgs__srv__GetAverage_Event__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
void
msgs__srv__GetAverage_Event__Sequence__fini(msgs__srv__GetAverage_Event__Sequence * array);

/// Create array of srv/GetAverage messages.
/**
 * It allocates the memory for the array and calls
 * msgs__srv__GetAverage_Event__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
msgs__srv__GetAverage_Event__Sequence *
msgs__srv__GetAverage_Event__Sequence__create(size_t size);

/// Destroy array of srv/GetAverage messages.
/**
 * It calls
 * msgs__srv__GetAverage_Event__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
void
msgs__srv__GetAverage_Event__Sequence__destroy(msgs__srv__GetAverage_Event__Sequence * array);

/// Check for srv/GetAverage message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Event__Sequence__are_equal(const msgs__srv__GetAverage_Event__Sequence * lhs, const msgs__srv__GetAverage_Event__Sequence * rhs);

/// Copy an array of srv/GetAverage messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_msgs
bool
msgs__srv__GetAverage_Event__Sequence__copy(
  const msgs__srv__GetAverage_Event__Sequence * input,
  msgs__srv__GetAverage_Event__Sequence * output);
#ifdef __cplusplus
}
#endif

#endif  // MSGS__SRV__DETAIL__GET_AVERAGE__FUNCTIONS_H_
