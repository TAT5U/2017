using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class KeyDeviceManager : KeyManager 
{
    //public MusicManager MM;

	protected override void Start()
	{
		base.Start();

        //MM = GameObject.Find("MusicManager").GetComponent<MusicManager>();
	}

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

	public void Enter()
	{
        //MM.PlaySE(MusicManager.SE_SELECT.ok);
		if (charaStringCount_ == 49)
		{
			nameDisp.GetComponent<PlayerNameManager>().DeleteCharaString();
		}
		else
		{
			// GetComponentだと取得できないのでGetComponentInChildrenを使用する
			nameDisp.GetComponent<PlayerNameManager>().SetCharaName(charaString_[charaStringCount_].GetComponentInChildren<Text>().text);
		}
	}

	public void Write()
	{
        //MM.PlaySE(MusicManager.SE_SELECT.allOkSE);
        nameDisp.GetComponent<PlayerNameManager>().PlayerNameWrite();
	}

	public void CountJudge()
	{
		base.CountJudge();
	}
}
