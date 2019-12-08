/*
  Copyright 2019 www.dev5.cn, Inc. dev5@qq.com
 
  This file is part of X-MSG-IM.
 
  X-MSG-IM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  X-MSG-IM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU Affero General Public License
  along with X-MSG-IM.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "XmsgChannelStatusMsg.h"
#include "mgr/XmsgImMgrNeNetLoad.h"
#include "mgr/XmsgImMgrNeXscServerQuery.h"
#include "mgr/XmsgImMgrNeXscWorkerCount.h"
#include "msg/XmsgChannelStatusQuery.h"
#include "msg/XmsgChannelStatusSub.h"
#include "msg/XmsgChannelStatusUnSub.h"
#include "ne/XmsgImGroupChannelStatusChanged.h"
#include "ne/XmsgImGroupChannelStatusPub.h"
#include "ne/XmsgImHlrChannelStatusChanged.h"
#include "ne/XmsgImHlrChannelStatusPub.h"
#include "ne/XmsgNeAuth.h"

XmsgChannelStatusMsg::XmsgChannelStatusMsg()
{

}

void XmsgChannelStatusMsg::init(shared_ptr<XmsgImN2HMsgMgr> priMsgMgr)
{
	X_MSG_H2N_PRPC_AFTER_AUTH(XmsgAp, XmsgChannelStatusQueryReq, XmsgChannelStatusQueryRsp, XmsgChannelStatusQuery::handle)
	X_MSG_H2N_PRPC_AFTER_AUTH(XmsgAp, XmsgChannelStatusSubReq, XmsgChannelStatusSubRsp, XmsgChannelStatusSub::handle)
	X_MSG_H2N_PRPC_AFTER_AUTH(XmsgAp, XmsgChannelStatusUnSubReq, XmsgChannelStatusUnSubRsp, XmsgChannelStatusUnSub::handle)
	X_MSG_H2N_PRPC_AFTER_AUTH(XmsgImHlr, XmsgImHlrChannelStatusPubReq, XmsgImHlrChannelStatusPubRsp, XmsgImHlrChannelStatusPub::handle)
	X_MSG_H2N_PRPC_AFTER_AUTH_UNI(XmsgImHlr, XmsgImHlrChannelStatusChangedNotice, XmsgImHlrChannelStatusChanged::handle)
	X_MSG_H2N_PRPC_AFTER_AUTH(XmsgImGroup, XmsgImGroupChannelStatusPubReq, XmsgImGroupChannelStatusPubRsp, XmsgImGroupChannelStatusPub::handle)
	X_MSG_H2N_PRPC_AFTER_AUTH_UNI(XmsgImGroup, XmsgImGroupChannelStatusChangedNotice, XmsgImGroupChannelStatusChanged::handle)
	X_MSG_N2H_PRPC_BEFOR_AUTH(priMsgMgr, XmsgNeAuthReq, XmsgNeAuthRsp, XmsgNeAuth::handle)
	X_MSG_N2H_PRPC_AFTER_AUTH(priMsgMgr, XmsgImMgrNeNetLoadReq, XmsgImMgrNeNetLoadRsp, XmsgImMgrNeNetLoad::handle)
	X_MSG_N2H_PRPC_AFTER_AUTH(priMsgMgr, XmsgImMgrNeXscServerQueryReq, XmsgImMgrNeXscServerQueryRsp, XmsgImMgrNeXscServerQuery::handle)
	X_MSG_N2H_PRPC_AFTER_AUTH(priMsgMgr, XmsgImMgrNeXscWorkerCountReq, XmsgImMgrNeXscWorkerCountRsp, XmsgImMgrNeXscWorkerCount::handle)
}

XmsgChannelStatusMsg::~XmsgChannelStatusMsg()
{

}
