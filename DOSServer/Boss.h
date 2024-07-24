// Boss.h: interface for the CBoss class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOSS_H__F24C01FC_C0DA_4FCB_988E_EF0FF54C06F9__INCLUDED_)
#define AFX_BOSS_H__F24C01FC_C0DA_4FCB_988E_EF0FF54C06F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBoss  
{
public:
	CBoss();
	virtual ~CBoss();
	//
	int getId();

protected:
	int nId;
};

#endif // !defined(AFX_BOSS_H__F24C01FC_C0DA_4FCB_988E_EF0FF54C06F9__INCLUDED_)
