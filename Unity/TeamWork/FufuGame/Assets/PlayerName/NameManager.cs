using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


using System.Text.RegularExpressions;

public class NameManager : MonoBehaviour 
{
	private XboxControllerCustom playerControllerCustom_;

	private KeyDeviceManager keyDevice_;
	private int writeCount_ = 0;
	private int useControllerNumber_ = 0;
	private bool isStartCorutine = false;


	void Awake () 
	{
		keyDevice_ = gameObject.AddComponent<KeyDeviceManager>();
		playerControllerCustom_ = this.GetComponent<XboxControllerCustom>();
    }
    void Start()
    {

        keyDevice_ = gameObject.AddComponent<KeyDeviceManager>();
        playerControllerCustom_ = this.GetComponent<XboxControllerCustom>();
    }
	
	// Update is called once per frame
	void Update () 
	{
		// HACK: 入れ子が多すぎる
		int maxNumber = playerControllerCustom_.UsePlayerNumCount();
		while (useControllerNumber_ < maxNumber)
		{
			if (int.Parse(gameObject.name.Replace("Player", "")) == playerControllerCustom_.UsePlayerNum()[useControllerNumber_])
			{
				if (!isStartCorutine)
				{

					UsedController();
				}
				isStartCorutine = true;
			}
			useControllerNumber_++;
		}
		IsKeyboard();
	}

	void UsedController()
	{
		StartCoroutine("UseControllerEmu");
	}

	void IsKeyboard()
	{
		if (!isStartCorutine)
		{
			if (int.Parse(gameObject.name.Replace("Player", "")) <= 1)
			{

				PlayerOneKeyCommand();
			}
			else
			{
				PlayerTwoKeyCommand();
			}
		}
		
	}

	void PlayerOneKeyCommand()
	{
		if (Input.GetKeyUp(KeyCode.D))
		{
			keyDevice_.Right();
		}
		if (Input.GetKeyUp(KeyCode.A))
		{
			keyDevice_.Left();
		}
		if (Input.GetKeyUp(KeyCode.W))
		{
			keyDevice_.Top();
		}
		if (Input.GetKeyUp(KeyCode.S))
		{
			keyDevice_.Bottom();
		}

		keyDevice_.CountJudge();


		if (Input.GetKeyUp(KeyCode.Space))
		{
			keyDevice_.Enter();
		}

		if (Input.GetKeyUp(KeyCode.V) && writeCount_ <= 0)
		{
			keyDevice_.Write();
			writeCount_++;
		}
	}

	void PlayerTwoKeyCommand()
	{
		if (Input.GetKeyUp(KeyCode.RightArrow))
		{
			keyDevice_.Right();
		}
		if (Input.GetKeyUp(KeyCode.LeftArrow))
		{
			keyDevice_.Left();
		}
		if (Input.GetKeyUp(KeyCode.UpArrow))
		{
			keyDevice_.Top();
		}
		if (Input.GetKeyUp(KeyCode.DownArrow))
		{
			keyDevice_.Bottom();
		}

		keyDevice_.CountJudge();


		if (Input.GetKeyUp(KeyCode.Return))
		{
			keyDevice_.Enter();
		}

		if (Input.GetKeyUp(KeyCode.B) && writeCount_ <= 0)
		{
			keyDevice_.Write();
			writeCount_++;
		}
	}

	IEnumerator UseControllerEmu()
	{
		while (true)
		{
			// Right
			if (playerControllerCustom_.Right())
			{
				keyDevice_.Right();
			}

			// Left
			if (playerControllerCustom_.Left())
			{
				keyDevice_.Left();
			}

			// Top
			if (playerControllerCustom_.Top())
			{
				keyDevice_.Top();
			}

			// Bottom
			if (playerControllerCustom_.Bottom())
			{
				keyDevice_.Bottom();
			}

			keyDevice_.CountJudge();

			if (playerControllerCustom_.Enter())
			{
				keyDevice_.Enter();
			}

			if (playerControllerCustom_.Write() && writeCount_ <= 0)
			{
				keyDevice_.Write();
				writeCount_++;
			}

			if (IsEnd())
			{
				StopCoroutine("UseController");
			}

			yield return new WaitForSeconds(0.150f);
		}
	}

	private bool IsEnd()
	{
		return writeCount_ >= 2;
	}
}
