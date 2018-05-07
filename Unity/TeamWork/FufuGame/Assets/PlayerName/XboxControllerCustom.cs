using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class XboxControllerCustom : PlayerController 
{
	private string number_;
	private int numberCount_;

	private bool isNotNumber_ = false;

	private int element = 1;

	private List<int> controllerNumberCount_ = new List<int>();


	void Start()
	{
		number_ = mode.ToString().Replace("PLAYER_", "");
		if (int.Parse(number_) <= 1)
		{
			isNotNumber_ = true;
		}
		numberCount_ = int.Parse(number_);

		string[] controllerNames = Input.GetJoystickNames();

		foreach (string name in controllerNames)
		{
			if (name != "")
			{
				controllerNumberCount_.Add(element);
			}
			element++;
		}

	}

	public List<int> UsePlayerNum()
	{
		return controllerNumberCount_;
	}
	public int UsePlayerNumCount()
	{
		return controllerNumberCount_.Count;
	}

	public bool Right()
	{
		if (isNotNumber_)
		{
			return Input.GetAxis("Horizontal") > 0.0f;
		}
		return Input.GetAxis("Horizontal" + numberCount_.ToString()) > 0.0f;
	}

	public bool Left()
	{
		if (isNotNumber_)
		{
			return Input.GetAxis("Horizontal") < 0.0f;
		}
		return Input.GetAxis("Horizontal" + numberCount_.ToString()) < 0.0f;
	}


	public bool Top()
	{
		if (isNotNumber_)
		{
			return Input.GetAxis("Vertical") < 0.0f;
		}
		return Input.GetAxis("Vertical" + numberCount_.ToString()) < 0.0f;
	}

	public bool Bottom()
	{
		if (isNotNumber_)
		{
			return Input.GetAxis("Vertical") > 0.0f;
		}
		return Input.GetAxis("Vertical" + numberCount_.ToString()) > 0.0f;
	}

	public bool Enter()
	{
		if (!Input.GetButton("Enter" + number_)) return false;
		return true;
	}

	public bool Write()
	{
		return Input.GetButton("Write" + number_);
	}
}
