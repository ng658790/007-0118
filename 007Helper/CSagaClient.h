#pragma once
#include "007Helper.h"
#include <RCF../../../RCF007Interface.hpp>
#include <RCF/RCF.hpp>
#include "openssl/rc4.h"
#include <PackReader.h>
#include "openssl/bio.h"
#include "openssl/rsa.h"
#include "openssl/pem.h"
#include "openssl/err.h"
#include "openssl/md5.h"
//传奇云 验证

#if !ANTI_DEBUG
#define  SAGA_CLOUDS		1
#endif



class CSagaClient : public IGameClient
{
public:
	CSagaClient();
	static CSagaClient* GetInstance();
	
	virtual void vHUD_Frame(double time);

	// @启动线程初始化
	VOID StartThreadRCFInit(ULONG uPort = 31251);


	// @效验远程变量
	BOOL SagaCheckVar();


	// @心跳维持
	void HeartBeat();

	// @版本验证
	BOOL SagaVersion();
	
	/*
	*	@发送客户端信息
	*	@Param：客户端进程名
	*	@Param: 版本号
	*/
	std::tuple<BOOL,std::string> SagaClient(std::string ProcessName,std::string Version);

	/*
	*	@获取远程变量
	*	@Param：远程变量名
	*/
	std::tuple<BOOL, std::string> SagaRemoteVar(std::string VarName);

	/*
	*	@客户端检查-维持心跳
	*/
	std::tuple<BOOL, std::string> SagaClientCheck(std::string Mac);



	// @公钥解密
	std::vector<BYTE> RsaPubDecrypt(std::vector<BYTE>& VecText, std::string& PubKey);
	// @公钥加密
	std::vector<BYTE> RsaPubEncrypt(std::string& Text, std::string& PubKey);

	std::vector<BYTE> SRC4Decode(std::vector<BYTE> CipherByte);
	std::vector<BYTE> SRC4Encrypt(std::vector<BYTE> CipherByte);
private:
	RCF::RcfInit*              m_pRcfInit;
	RcfClient<I_SagaService>*  m_pClient;
	static inline CSagaClient* m_pInstance = nullptr;
	ULONG                      m_uPort;
	std::string                m_RC4Key;
	ULONG	                   m_SagaVersion;
	std::string	               m_ClientSession;
	ULONG	                   m_ultimestamp;
	std::string				   m_RSAPub;
	std::string				   m_ErrStr;
	std::string				   m_ProxyName;
	std::string				   m_MAC;
};

class SagaProxyClient
{
public:
	SagaProxyClient();

	std::vector<BYTE> UMSG(std::vector<BYTE>& v);


private:


};