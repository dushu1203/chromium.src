# Copyright 2014 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'targets': [{
    'target_name': 'login',
    'type': '<(component)',
    'dependencies': [
      '<(DEPTH)/base/base.gyp:base',
    ],
    'defines': [
      'LOGIN_IMPLEMENTATION',
    ],
    'sources': [
      'login/base_screen_handler_utils.cc',
      'login/base_screen_handler_utils.h',
      'login/screens/screen_context.cc',
      'login/screens/screen_context.h',
    ],
  }],
}
