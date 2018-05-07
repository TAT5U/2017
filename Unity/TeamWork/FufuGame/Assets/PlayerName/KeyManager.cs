using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KeyManager : MonoBehaviour 
{
	protected List<GameObject> charaString_ = new List<GameObject>();

	protected int charaStringCount_ = 0;

	protected GameObject nameDisp;

	private List<GameObject> right_, left_, top_, bottom_, enRouteRight_, enRouteLeft_;


	// Use this for initialization
	protected virtual void Start () 
	{
		foreach (Transform keyStringChild in transform.parent.transform)
		{
			if (keyStringChild.name != "Player1" && keyStringChild.name != "Player2")
			{
				charaString_.Add(keyStringChild.gameObject);
			}
		}
		GetComponent<RectTransform>().localPosition = charaString_[charaStringCount_].GetComponent<RectTransform>().localPosition;
		print(GetComponent<RectTransform>().localPosition.x);

		//name_ = gameObject.name;

		nameDisp = transform.root.Find(name + "Name").gameObject;

		SetFrameKeyString();
	}

	private void SetFrameKeyString()
	{
		right_ 		  = new List<GameObject>();
		left_ 		  = new List<GameObject>();
		top_		  = new List<GameObject>();
		bottom_ 	  = new List<GameObject>();
		enRouteRight_ = new List<GameObject>();
		enRouteLeft_  = new List<GameObject>();

		int count = 0;

		// Top
		while (count < 50)
		{
			if (charaString_[count].GetComponent<RectTransform>().localPosition.y == charaString_[0].GetComponent<RectTransform>().localPosition.y)
			{
				top_.Add(charaString_[count]);
			}
			if (charaString_[count].GetComponent<RectTransform>().localPosition.y == charaString_[20].GetComponent<RectTransform>().localPosition.y)
			{
				bottom_.Add(charaString_[count]);
			}
			if (charaString_[count].GetComponent<RectTransform>().localPosition.x == charaString_[29].GetComponent<RectTransform>().localPosition.x)
			{
				right_.Add(charaString_[count]);
			}
			if (charaString_[count].GetComponent<RectTransform>().localPosition.x == charaString_[0].GetComponent<RectTransform>().localPosition.x)
			{
				left_.Add(charaString_[count]);
			}
			if (charaString_[count].GetComponent<RectTransform>().localPosition.x == charaString_[4].GetComponent<RectTransform>().localPosition.x)
			{
				enRouteLeft_.Add(charaString_[count]);
			}
			if (charaString_[count].GetComponent<RectTransform>().localPosition.x == charaString_[25].GetComponent<RectTransform>().localPosition.x)
			{
				enRouteRight_.Add(charaString_[count]);
			}
			count++;
		}
	}

	protected bool TopJudge(GameObject target)
	{
		foreach (GameObject item in top_)
		{
			if (!MainJudgement(target, item))
			{
				return false;
			}
		}
		return true;
	}

	protected bool BottomJudge(GameObject target)
	{
		foreach (GameObject item in bottom_)
		{
			if (!MainJudgement(target, item))
			{
				return false;
			}
		}
		return true;
	}

	protected bool RightJudge(GameObject target)
	{
		foreach (GameObject item in right_)
		{
			if (!MainJudgement(target, item))
			{
				return false;
			}
		}
		return true;
	}

	protected bool LeftJudge(GameObject target)
	{
		foreach (GameObject item in left_)
		{
			if (!MainJudgement(target, item))
			{
				return false;
			}
		}
		return true;
	}

	protected bool EnRightJudge(GameObject target)
	{
		foreach (GameObject item in enRouteRight_)
		{
			if (!MainJudgement(target, item))
			{
				return false;
			}
		}
		return true;
	}

	protected bool EnLeftJudge(GameObject target)
	{
		foreach (GameObject item in enRouteLeft_)
		{
			if (!MainJudgement(target, item))
			{
				return false;
			}
		}
		return true;
	}

	protected bool MainJudgement(GameObject target, GameObject frame)
	{
		if (target.GetComponent<RectTransform>().localPosition == frame.GetComponent<RectTransform>().localPosition)
		{
			return false;
		}
		return true;
	}

	protected virtual void CountJudge()
	{
		GetComponent<RectTransform>().localPosition = charaString_[charaStringCount_].GetComponent<RectTransform>().localPosition;
	}
}
