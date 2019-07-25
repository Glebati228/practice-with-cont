#pragma once
#ifndef GCONT
#define GCONT

__interface IgContainble
{
public: 
	inline virtual int * gBegin() const;
	inline virtual int * gEnd() const;
};

#endif // !GCONT
