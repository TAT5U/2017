using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KeyboardManager : KeyManager 
{
	// HACK: 冗長的
	public void Right()
	{
		if (!EnLeftJudge(gameObject))
		{
			charaStringCount_ += 21;
		}
		else if (RightJudge(gameObject))
		{
			charaStringCount_++;
		}
		else
		{
			charaStringCount_ -= 29;
		}
	}

	public void Left()
	{
		if (!EnRightJudge(gameObject))
		{
			charaStringCount_ -= 21;
		}
		else if (LeftJudge(gameObject))
		{
			charaStringCount_--;
		}
		else
		{
			charaStringCount_ += 29;
		}
	}

	public void Top()
	{
		if (TopJudge(gameObject))
		{
			charaStringCount_ -= 5;
		}
		else
		{
			charaStringCount_ += 20;
		}
	}

	public void Bottom()
	{
		if (BottomJudge(gameObject))
		{
			charaStringCount_ += 5;
		}
		else
		{
			charaStringCount_ -= 20;
		}
	}
}
