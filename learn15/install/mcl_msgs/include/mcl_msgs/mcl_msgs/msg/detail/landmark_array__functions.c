// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from mcl_msgs:msg/LandmarkArray.idl
// generated code does not contain a copyright notice
#include "mcl_msgs/msg/detail/landmark_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `landmarks`
#include "mcl_msgs/msg/detail/landmark__functions.h"

bool
mcl_msgs__msg__LandmarkArray__init(mcl_msgs__msg__LandmarkArray * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    mcl_msgs__msg__LandmarkArray__fini(msg);
    return false;
  }
  // landmarks
  if (!mcl_msgs__msg__Landmark__Sequence__init(&msg->landmarks, 0)) {
    mcl_msgs__msg__LandmarkArray__fini(msg);
    return false;
  }
  return true;
}

void
mcl_msgs__msg__LandmarkArray__fini(mcl_msgs__msg__LandmarkArray * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // landmarks
  mcl_msgs__msg__Landmark__Sequence__fini(&msg->landmarks);
}

bool
mcl_msgs__msg__LandmarkArray__are_equal(const mcl_msgs__msg__LandmarkArray * lhs, const mcl_msgs__msg__LandmarkArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // landmarks
  if (!mcl_msgs__msg__Landmark__Sequence__are_equal(
      &(lhs->landmarks), &(rhs->landmarks)))
  {
    return false;
  }
  return true;
}

bool
mcl_msgs__msg__LandmarkArray__copy(
  const mcl_msgs__msg__LandmarkArray * input,
  mcl_msgs__msg__LandmarkArray * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // landmarks
  if (!mcl_msgs__msg__Landmark__Sequence__copy(
      &(input->landmarks), &(output->landmarks)))
  {
    return false;
  }
  return true;
}

mcl_msgs__msg__LandmarkArray *
mcl_msgs__msg__LandmarkArray__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mcl_msgs__msg__LandmarkArray * msg = (mcl_msgs__msg__LandmarkArray *)allocator.allocate(sizeof(mcl_msgs__msg__LandmarkArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(mcl_msgs__msg__LandmarkArray));
  bool success = mcl_msgs__msg__LandmarkArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
mcl_msgs__msg__LandmarkArray__destroy(mcl_msgs__msg__LandmarkArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    mcl_msgs__msg__LandmarkArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
mcl_msgs__msg__LandmarkArray__Sequence__init(mcl_msgs__msg__LandmarkArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mcl_msgs__msg__LandmarkArray * data = NULL;

  if (size) {
    data = (mcl_msgs__msg__LandmarkArray *)allocator.zero_allocate(size, sizeof(mcl_msgs__msg__LandmarkArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = mcl_msgs__msg__LandmarkArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        mcl_msgs__msg__LandmarkArray__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
mcl_msgs__msg__LandmarkArray__Sequence__fini(mcl_msgs__msg__LandmarkArray__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      mcl_msgs__msg__LandmarkArray__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

mcl_msgs__msg__LandmarkArray__Sequence *
mcl_msgs__msg__LandmarkArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mcl_msgs__msg__LandmarkArray__Sequence * array = (mcl_msgs__msg__LandmarkArray__Sequence *)allocator.allocate(sizeof(mcl_msgs__msg__LandmarkArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = mcl_msgs__msg__LandmarkArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
mcl_msgs__msg__LandmarkArray__Sequence__destroy(mcl_msgs__msg__LandmarkArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    mcl_msgs__msg__LandmarkArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
mcl_msgs__msg__LandmarkArray__Sequence__are_equal(const mcl_msgs__msg__LandmarkArray__Sequence * lhs, const mcl_msgs__msg__LandmarkArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!mcl_msgs__msg__LandmarkArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
mcl_msgs__msg__LandmarkArray__Sequence__copy(
  const mcl_msgs__msg__LandmarkArray__Sequence * input,
  mcl_msgs__msg__LandmarkArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(mcl_msgs__msg__LandmarkArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    mcl_msgs__msg__LandmarkArray * data =
      (mcl_msgs__msg__LandmarkArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!mcl_msgs__msg__LandmarkArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          mcl_msgs__msg__LandmarkArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!mcl_msgs__msg__LandmarkArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
