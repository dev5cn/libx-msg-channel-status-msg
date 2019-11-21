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

#include "XmsgChannelStatusUnSub.h"

XmsgChannelStatusUnSub::XmsgChannelStatusUnSub()
{

}

void XmsgChannelStatusUnSub::handle(shared_ptr<XmsgNeUsr> nu, const string& ap, shared_ptr<XmsgClient> client, SptrXitp trans, shared_ptr<XmsgChannelStatusUnSubReq> req)
{
	if (req->cgt().empty())
	{
		trans->endDesc(RET_FORMAT_ERROR, "channel global title array is empty");
		return;
	}
	if (req->cgt_size() == 1 && req->cgt(0) == "*")
	{
		shared_ptr<XmsgChannelStatusUnSubRsp> rsp(new XmsgChannelStatusUnSubRsp());
		XmsgMisc::insertKv(rsp->mutable_ext(), "accept", "true");
		trans->end(rsp);
		ChannelStatusMgr::instance()->future([ap, client]
		{
			ChannelStatusMgr::instance()->getSubPub()->unSub(ap, client->ccid);
		});
		return;
	}
	for (int i = 0; i < req->cgt_size(); ++i) 
	{
		SptrCgt cgt = ChannelGlobalTitle::parse(req->cgt(i));
		if (cgt == nullptr)
		{
			trans->endDesc(RET_FORMAT_ERROR, "some one channel global title format error: %s", req->cgt(i).c_str());
			return;
		}
		if (cgt->isGroup())
		{
			trans->endDesc(RET_UNSUPPORTED, "group channel status unsupported");
			return;
		}
	}
	shared_ptr<XmsgChannelStatusUnSubRsp> rsp(new XmsgChannelStatusUnSubRsp());
	XmsgMisc::insertKv(rsp->mutable_ext(), "accept", "true");
	trans->end(rsp);
	ChannelStatusMgr::instance()->future([ap, client, req]
	{
		ChannelStatusMgr::instance()->getSubPub()->unSub(ap, client->ccid, req);
	});
}

XmsgChannelStatusUnSub::~XmsgChannelStatusUnSub()
{

}

