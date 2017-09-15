/*
 *	 Author: bwilliams
 *  Created: Oct 22, 2010
 *
 *	Copyright (c) 2010 Vmware, Inc.  All rights reserved.
 *	-- VMware Confidential
 */

#ifndef _MaIntegration_CConfigEnv_h_
#define _MaIntegration_CConfigEnv_h_

using namespace Caf;

/// TODO - describe class
class CConfigEnv :
	public TCafSubSystemObjectRoot<CConfigEnv>,
	public IBean,
	public IConfigEnv {
public:
	CConfigEnv();
	virtual ~CConfigEnv();

	CAF_DECLARE_OBJECT_IDENTIFIER(_sObjIdConfigEnv)

	CAF_BEGIN_INTERFACE_MAP(CConfigEnv)
		CAF_INTERFACE_ENTRY(IBean)
		CAF_INTERFACE_ENTRY(IConfigEnv)
	CAF_END_INTERFACE_MAP()

public: // IBean
	virtual void initializeBean(
			const IBean::Cargs& ctorArgs,
			const IBean::Cprops& properties);

	virtual void terminateBean();

public: // IConfigEnv
	void initialize(
			const SmartPtrIPersistence& persistenceRemove);

	SmartPtrCPersistenceDoc getUpdated(
			const int32 timeout);

	void update(
			const SmartPtrCPersistenceDoc& persistence);

private:
	void savePersistenceAppconfig(
			const SmartPtrCPersistenceDoc& persistence,
			const std::string& configDir) const;

	void executeScript(
			const std::string& scriptPath,
			const std::string& scriptResultsDir) const;

	void removePrivateKey(
			const SmartPtrCPersistenceDoc& persistence,
			const SmartPtrIPersistence& persistenceRemove) const;

	SmartPtrCPersistenceDoc createPersistenceUpdated(
			const SmartPtrCPersistenceDoc& persistence) const;

	std::string calcListenerContext(
			const std::string& uriSchema,
			const std::string& configDir) const;

	void restartRunningListener() const;

private:
	bool _isInitialized;
	std::string _vcidPath;
	std::string _cacertPath;
	std::string _persistenceDir;
	std::string _scriptsDir;
	std::string _outputDir;
	std::string _configDir;
	std::string _persistenceAppconfigPath;

	std::string _startListenerScript;
	std::string _stopListenerScript;
	std::string _startMaScript;
	std::string _stopMaScript;

	SmartPtrCPersistenceDoc _persistence;
	SmartPtrCPersistenceDoc _persistenceUpdated;
	SmartPtrIPersistence _persistenceRemove;

private:
	CAF_CM_CREATE;
	CAF_CM_CREATE_LOG;
	CAF_CM_CREATE_THREADSAFE;
	CAF_CM_DECLARE_NOCOPY(CConfigEnv);
};

#endif // #ifndef _MaIntegration_CConfigEnv_h_
