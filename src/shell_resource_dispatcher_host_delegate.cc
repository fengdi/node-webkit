// Copyright (c) 2012 Intel Corp
// Copyright (c) 2012 The Chromium Authors
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell co
// pies of the Software, and to permit persons to whom the Software is furnished
//  to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in al
// l copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IM
// PLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNES
// S FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
//  OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WH
// ETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "content/shell/shell_resource_dispatcher_host_delegate.h"

#include "content/shell/shell_login_dialog.h"

namespace content {

ShellResourceDispatcherHostDelegate::ShellResourceDispatcherHostDelegate() {
}

ShellResourceDispatcherHostDelegate::~ShellResourceDispatcherHostDelegate() {
}

bool ShellResourceDispatcherHostDelegate::AcceptAuthRequest(
    net::URLRequest* request,
    net::AuthChallengeInfo* auth_info) {
  // Why not give it a try?
  return true;
}

ResourceDispatcherHostLoginDelegate*
ShellResourceDispatcherHostDelegate::CreateLoginDelegate(
    net::AuthChallengeInfo* auth_info, net::URLRequest* request) {
  if (!login_request_callback_.is_null()) {
    login_request_callback_.Run();
    login_request_callback_.Reset();
    return NULL;
  }

#if !defined(OS_MACOSX) && !defined(TOOLKIT_GTK)
// TODO: implement ShellLoginDialog for other platforms, drop this #if
  return NULL;
#else
  return new ShellLoginDialog(auth_info, request);
#endif
}

}  // namespace content
