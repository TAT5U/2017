using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class ToJumpRetry : MonoBehaviour 
{
	public ConfigScript config;
	public PlayerScript player;
	public ClickManager clickManager_;

	[SerializeField]private SoundScript ui_;

	// 離したとき
	public void Click()
	{
		if (clickManager_.IsClickOK())
		{
			ui_.SoundPlay(3);
			StartCoroutine("Retry");
		}
		else
		{
			print("NG");
		}
	}

	private IEnumerator Retry()
	{
		while (true)
		{
			yield return new WaitForFixedUpdate();
			if (!ui_.IsPlaying())
			{
				config.SetBackName("Retry");
				SceneManager.LoadScene(0);
				break;
			}
		}
	}
}
