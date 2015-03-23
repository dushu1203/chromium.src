# Copyright 2014 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'variables': {
    'chromium_code': 1,
   },
  'targets': [
    {
      'target_name': 'ios_web',
      'type': 'static_library',
      'include_dirs': [
        '../..',
      ],
      'dependencies': [
        'ios_web_core',
        '../../base/base.gyp:base',
        '../../content/content.gyp:content_browser',
        '../../net/net.gyp:net',
        '../../ui/base/ui_base.gyp:ui_base',
        '../../ui/gfx/gfx.gyp:gfx',
      ],
      'sources': [
        'browser_state.cc',
        'load_committed_details.cc',
        'navigation/navigation_item_impl.h',
        'navigation/navigation_item_impl.mm',
        'navigation/nscoder_util.h',
        'navigation/nscoder_util.mm',
        'navigation/time_smoother.cc',
        'navigation/time_smoother.h',
        'net/cert_policy.cc',
        'net/certificate_policy_cache.cc',
        'net/request_group_util.h',
        'net/request_group_util.mm',
        'public/block_types.h',
        'public/browser_state.h',
        'public/browser_url_rewriter.h',
        'public/cert_policy.h',
        'public/certificate_policy_cache.h',
        'public/favicon_status.cc',
        'public/favicon_status.h',
        'public/favicon_url.cc',
        'public/favicon_url.h',
        'public/interstitials/web_interstitial.h',
        'public/interstitials/web_interstitial_delegate.h',
        'public/load_committed_details.h',
        'public/navigation_item.h',
        'public/referrer.h',
        'public/referrer_util.h',
        'public/referrer_util.cc',
        'public/security_style.h',
        'public/ssl_status.cc',
        'public/ssl_status.h',
        'public/string_util.h',
        'public/url_scheme_util.h',
        'public/url_util.h',
        'public/user_agent.h',
        'public/user_agent.mm',
        'public/user_metrics.h',
        'public/web_client.h',
        'public/web_client.mm',
        'public/web_state/crw_native_content.h',
        'public/web_state/crw_native_content_provider.h',
        'public/web_state/crw_web_controller_observer.h',
        'public/web_state/crw_web_delegate.h',
        'public/web_state/crw_web_user_interface_delegate.h'
        'public/web_state/crw_web_view_proxy.h'
        'public/web_state/js/crw_js_base_manager.h',
        'public/web_state/js/crw_js_early_script_manager.h',
        'public/web_state/js/crw_js_injection_evaluator.h',
        'public/web_state/js/crw_js_injection_manager.h',
        'public/web_state/js/crw_js_injection_receiver.h',
        'public/web_state/js/crw_js_message_manager.h',
        'public/web_state/url_verification_constants.h',
        'public/web_state/web_state_observer.h',
        'public/web_state/web_state_observer_bridge.h',
        'public/web_thread.h',
        'public/web_view_type.h',
        'string_util.cc',
        'url_scheme_util.mm',
        'url_util.cc',
        'user_metrics.cc',
        'weak_nsobject_counter.h',
        'weak_nsobject_counter.mm',
        'web_state/blocked_popup_info.h',
        'web_state/blocked_popup_info.mm',
        'web_state/crw_recurring_task_delegate.h',
        'web_state/js/crw_js_base_manager.mm',
        'web_state/js/crw_js_common_manager.h',
        'web_state/js/crw_js_common_manager.mm',
        'web_state/js/crw_js_early_script_manager.mm',
        'web_state/js/crw_js_injection_manager.mm',
        'web_state/js/crw_js_injection_receiver.mm',
        'web_state/js/crw_js_message_dynamic_manager.h',
        'web_state/js/crw_js_message_dynamic_manager.mm',
        'web_state/js/crw_js_message_manager.mm',
        'web_state/js/page_script_util.h',
        'web_state/js/page_script_util.mm',
        'web_state/web_state_observer.cc',
        'web_state/web_state_observer_bridge.mm',
        'web_state/wk_web_view_ssl_error_util.h',
        'web_state/wk_web_view_ssl_error_util.mm',
        'web_thread.cc',
        'web_thread_impl.cc',
        'web_thread_impl.h',
        'web_view_util.h',
        'web_view_util.mm',
      ],
    },
    # Target shared by ios_web and CrNet.
    {
      'target_name': 'ios_web_core',
      'type': 'static_library',
      'dependencies': [
        '../../base/base.gyp:base',
      ],
      'include_dirs': [
        '../..',
      ],
      'sources': [
        'crw_network_activity_indicator_manager.h',
        'crw_network_activity_indicator_manager.mm',
        'history_state_util.h',
        'history_state_util.mm',
      ],
    },
    {
      'target_name': 'js_resources',
      'type': 'none',
      'sources': [
        'web_state/js/resources/base.js',
        'web_state/js/resources/common.js',
        'web_state/js/resources/message.js',
        'web_state/js/resources/message_dynamic_ui.js',
        'web_state/js/resources/message_dynamic_wk.js',
      ],
      'link_settings': {
        'mac_bundle_resources': [
          '<(SHARED_INTERMEDIATE_DIR)/base.js',
          '<(SHARED_INTERMEDIATE_DIR)/common.js',
          '<(SHARED_INTERMEDIATE_DIR)/message.js',
          '<(SHARED_INTERMEDIATE_DIR)/message_dynamic_ui.js',
          '<(SHARED_INTERMEDIATE_DIR)/message_dynamic_wk.js',
        ],
      },
      'includes': [
        'js_compile.gypi'
      ],
    },
    {
      'target_name': 'test_support_ios_web',
      'type': 'static_library',
      'dependencies': [
        '../../content/content_shell_and_tests.gyp:test_support_content',
        'ios_web',
      ],
      'include_dirs': [
        '../..',
      ],
      'sources': [
        'public/test/crw_test_js_injection_receiver.h',
        'public/test/crw_test_js_injection_receiver.mm',
        'public/test/js_test_util.h',
        'public/test/js_test_util.mm',
        'public/test/test_browser_state.cc',
        'public/test/test_browser_state.h',
        'public/test/test_web_state.cc',
        'public/test/test_web_state.h',
        'public/test/test_web_thread.h',
        'public/test/test_web_thread_bundle.h',
        'test/test_web_thread.cc',
        'test/test_web_thread_bundle.cc',
      ],
    },
  ],
}
