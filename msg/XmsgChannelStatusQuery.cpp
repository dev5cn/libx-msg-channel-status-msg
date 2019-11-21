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

#include "XmsgChannelStatusQuery.h"

XmsgChannelStatusQuery::XmsgChannelStatusQuery()
{

}

void XmsgChannelStatusQuery::handle(shared_ptr<XmsgNeUsr> nu, const string& ap, shared_ptr<XmsgClient> client, SptrXitp trans, shared_ptr<XmsgChannelStatusQueryReq> req)
{
	if (req->cgt().empty())
	{
		trans->endDesc(RET_FORMAT_ERROR, "channel global title array is empty");
		return;
	}
	ChannelStatusMgr::instance()->future([trans, req]
	{
		shared_ptr<XmsgChannelStatusQueryRsp> rsp(new XmsgChannelStatusQueryRsp());
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
			XmsgChannelStatusQuery::query4usr(req->cgt(i), rsp);
		}
		if (rsp->usrstatus().empty() && rsp->groupstatus().empty()) 
		{
			trans->end(RET_NO_RECORD);
			return;
		}
		trans->end(rsp);
	});

}

void XmsgChannelStatusQuery::query4usr(const string& cgt, shared_ptr<XmsgChannelStatusQueryRsp> rsp)
{
	map<string, string> usrClients;
	ChannelStatusMgr::instance()->query(cgt, usrClients);
	if (usrClients.empty())
		return;
	XmsgChannelStatusUsrStatus usrStatus;
	for (auto& it : usrClients)
	{
		string plat;
		string did;
		if (!XmsgMisc::parsePlatDid(it.first, plat, did))
		{
			LOG_FAULT("it`s a bug, plat + did format error: %s", it.first.c_str())
			continue;
		}
		auto client = usrStatus.add_client();
		client->set_plat(plat);
		client->set_did(did);
		client->set_status(it.second);
	}
	rsp->mutable_usrstatus()->insert(MapPair<string, XmsgChannelStatusUsrStatus>(cgt, usrStatus));
}

XmsgChannelStatusQuery::~XmsgChannelStatusQuery()
{

}
