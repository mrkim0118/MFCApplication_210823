#pragma once
#include "stdafx.h"
#include"Etc.h"

class CFileCtrl
{
public:
	CFileCtrl();
	~CFileCtrl();

	CEtc m_Etc;
	CFileFind m_finder;
private:

	BOOL m_bRet;
	CString m_strLog;


public:
	BOOL CopyFileFunc(CString strSrcPath, CString strDstPath, BOOL bExist = FALSE);
	BOOL DeleteFileFunc(CString strFilePath);

	BOOL CreateFolderFunc(CString strFolderPath);
	BOOL DeleteFilesInFolderFunc(CString strFolderPath);


	// 3��° �Ķ���� TRUE �ϰ�� ������ ������ ������ Fail , FALSE�� ��� �����.
};

